/*
 * CayenneLPP - CayenneLPP Polyline Codec
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef ARDUINO
#include "CayenneLPPPolyline.h"

#include <cmath>
#include <map>

const double scaleFactor = 10000.0;
const std::map<uint8_t, double> s_valueMap {
    //{ 224, 0.0 },       // 0.00001, reserved
    //{ 225, 0.0 },       // 0.000025, reserved
    //{ 226, 0.0 },       // 0.00005, reserved
    { 227, 1.0 },       // 0.0001
    { 228, 2.0 },       // 0.0002
    { 229, 5.0 },       // 0.0005
    { 230, 10.0 },      // 0.001
    { 231, 20.0 },      // 0.002
    { 232, 50.0 },      // 0.005
    { 233, 100.0 },     // 0.01
    { 234, 200.0 },     // 0.02
    { 235, 500.0 },     // 0.05
    { 236, 1000.0 },    // 0.1
    { 237, 2000.0 },    // 0.2
    { 238, 5000.0 },    // 0.5
    { 239, 10000.0 },   // 1.0
    //{ 240, 20000.0 },   // 2.0
    //{ 241, 50000.0 },   // 5.0
    //{ 255, 0.0 }      // reserved
};

struct InitialCoord {
    int32_t lat:24;
    int32_t lon:24;
};

struct DeltaCoord {
    int8_t dLat:4;
    int8_t dLon:4;
};

CayenneLPPPolyline::CayenneLPPPolyline(uint32_t size) : m_maxSize(size) {
}

std::vector<uint8_t> CayenneLPPPolyline::encode(const std::vector<Point>& coords,
                                                uint8_t factor,
                                                Simplification simplification) {
    reset();

    if (coords.size() < 2) {
        return {};
    }

    const double dFactor = getFactor(factor);

    // Apply Douglas–Peucker first
    auto coords2 = simplification == DouglasPeucker ? douglasPeucker(coords, dFactor/scaleFactor * 0.5) : coords;

    // Push initial item to init encoder
    pushFirst(coords2.front().first * scaleFactor / dFactor, coords2.front().second * scaleFactor / dFactor, factor);
    for (auto it = coords2.begin()+1; it != coords2.end() && m_buffer.size() < m_maxSize; ++it) {
        // Latitude -/+ 90
        // Longitude -/+ 180
        if (abs(it->first) > 90.0 || abs(it->second) > 180.0) {
            break;
        }

        // Push each item to encoder
        push(it->first * scaleFactor / dFactor, it->second * scaleFactor / dFactor, simplification == PerpendicularDistance);
    }
    // Write final header
    pushFirst(coords2.front().first * scaleFactor / dFactor, coords2.front().second * scaleFactor / dFactor, factor);

    return m_buffer;
}

std::vector<uint8_t> CayenneLPPPolyline::encode(const std::vector<Point>& coords,
                                                Precision precision,
                                                Simplification simplification) {
    return encode(coords, static_cast<uint8_t>(precision), simplification);
}

std::vector<std::pair<double, double>> CayenneLPPPolyline::decode(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 7) {
        return {};
    }

    const double dFactor = getFactor(buffer[1]);
    if (dFactor == 0.0) {
        return {};
    }

    std::vector<std::pair<double, double>> coords;
    //uint8_t size = buffer[0];
    int32_t prevLat = buffer[2] << 24 | buffer[3] << 16 | buffer[4] << 8;
    prevLat /= 256;
    prevLat *= dFactor;
    int32_t prevLon = buffer[5] << 24 | buffer[6] << 16 | buffer[7] << 8;
    prevLon /= 256;
    prevLon *= dFactor;
    coords.push_back( { prevLat / scaleFactor, prevLon / scaleFactor } );

    if (buffer.size() == 7) {
        return coords;
    }

    for (auto it = buffer.begin()+8; it != buffer.end(); ++it) {
        const auto dc = *(DeltaCoord*)&*it;
        const int dLat = dc.dLat * dFactor;
        const int dLon = dc.dLon * dFactor;
        coords.push_back( { (prevLat + dLat) / scaleFactor, (prevLon + dLon) / scaleFactor } );
        prevLat += dLat;
        prevLon += dLon;
    }

    return coords;
}

CayenneLPPPolyline::Stats CayenneLPPPolyline::getEncodeStats() const {
    return m_stats;
}

void CayenneLPPPolyline::reset() {
    m_buffer.clear();
    m_prevLat = 0.0;
    m_prevLon = 0.0;
    m_errLat = 0.0;
    m_errLon = 0.0;
    m_stats = {};
}

double CayenneLPPPolyline::getFactor(uint8_t factor) {
    if ( factor == 0) {
        return 0.0;
    } else if (factor < 200) {
        return factor;
    } else if (s_valueMap.count(factor)) {
        return s_valueMap.at(factor);
    } else {
        return 0.0;
    }
}

void CayenneLPPPolyline::push(double lat, double lon, bool optimize) {
    // Compute delta and correct error from previous rounding
    const double dLat = (lat - m_prevLat) + m_errLat;
    const double dLon = (lon - m_prevLon) + m_errLon;

    // Round values
    const int32_t roundLat = round(dLat);
    const int32_t roundLon = round(dLon);

    // Ignore items with zero delta
    if ((abs(roundLat) < 1) && (abs(roundLon) < 1)) {
        ++m_stats.removedCoords;
    // Delta fits into one nibble, push it
    } else if (abs(roundLat) < 8 && abs(roundLon) < 8) {
        writeDelta(roundLat, roundLon, optimize);
    // Delta is too big for one nibble. Compute intermediates.
    } else {
        ++m_stats.addedCoords;
        --m_stats.keptCoords;
        // Push intermediate. This is a simplified solution.
        // A more sophisticated computation can be found her: https://www.movable-type.co.uk/scripts/latlong.html
        // Please check the Intermediate point section.
        const double divisor = ceil(std::max(abs(dLat/7.0), abs(dLon/7.0)));
        push(m_prevLat + dLat / divisor, m_prevLon + dLon / divisor, optimize);
        // Push original lat/lon after intermediate.
        push(lat, lon, optimize);
        return;
    }

    // Compute error from rounding
    m_errLat = dLat - roundLat;
    m_errLon = dLon - roundLon;

    m_prevLat = lat;
    m_prevLon = lon;
}

void CayenneLPPPolyline::pushFirst(double lat, double lon, uint8_t factor) {
    const int32_t roundLat = round(lat);
    const int32_t roundLon = round(lon);

    writeHeader(roundLat, roundLon, factor);

    m_errLat = (lat - roundLat);
    m_errLon = (lon - roundLon);

    m_prevLat = lat;
    m_prevLon = lon;
}

void CayenneLPPPolyline::writeHeader(int32_t lat, int32_t lon, uint8_t factor) {
    m_buffer.resize(std::max(m_buffer.size(), 8UL));
    m_buffer[0] = m_buffer.size();
    m_buffer[1] = factor;
    m_buffer[2] = (lat >> 16); m_buffer[3] = (lat >> 8); m_buffer[4] = (lat);
    m_buffer[5] = (lon >> 16); m_buffer[6] = (lon >> 8); m_buffer[7] = (lon);
}

void CayenneLPPPolyline::writeDelta(int8_t lat, int8_t lon, bool optimize) {
    const DeltaCoord& prevDelta = (DeltaCoord&)m_buffer.back();
    const DeltaCoord currDelta { lat, lon };

    // This is a cheap optimization as an alternative to Douglas-Peucker
    // Check if the sum of this and next delta is within range
    const int8_t dLat = prevDelta.dLat + currDelta.dLat;
    const int8_t dLon = prevDelta.dLon + currDelta.dLon;
    if (optimize && m_buffer.size() > 8 && abs(dLat) < 8 && abs(dLon) < 8) {
        // Check if previous delta only differs slightly from straight line to current delta
        const double distance = abs(dLat * -1.0 * prevDelta.dLon + prevDelta.dLat * dLon) / sqrt(dLat * dLat + dLon * dLon);
        if (distance < 0.5) {
            ((DeltaCoord&)m_buffer.back()).dLat = dLat;
            ((DeltaCoord&)m_buffer.back()).dLon = dLon;
            ++m_stats.removedCoords;
            return;
        }
    }

    m_buffer.push_back(*(uint8_t*)(&currDelta));
    ++m_stats.keptCoords;
}

std::vector<CayenneLPPPolyline::Point> CayenneLPPPolyline::douglasPeucker(const std::vector<Point> &pointList, double epsilon) {
    if (pointList.size() < 2) {
        return {};
    }

    std::vector<Point> out;

    // Find the point with the maximum distance from line between start and end
    double dmax = 0.0;
    size_t index = 0;
    size_t end = pointList.size()-1;
    for (size_t i = 1; i < end; i++) {
        double d = distance(pointList[i], pointList[0], pointList[end]);
        if (d > dmax) {
            index = i;
            dmax = d;
        }
    }

    // If max distance is greater than epsilon, recursively simplify
    if (dmax > epsilon) {
        // Recursive call
        std::vector<Point> recResults1;
        std::vector<Point> recResults2;
        std::vector<Point> firstLine(pointList.begin(), pointList.begin()+index+1);
        std::vector<Point> lastLine(pointList.begin()+index, pointList.end());
        recResults1 = douglasPeucker(firstLine, epsilon);
        recResults2 = douglasPeucker(lastLine, epsilon);

        // Build the result list
        out.assign(recResults1.begin(), recResults1.end()-1);
        out.insert(out.end(), recResults2.begin(), recResults2.end());

        if (out.size() < 2) {
            return {};
        }
    } else {
        //Just return start and end points
        out.clear();
        out.push_back(pointList[0]);
        out.push_back(pointList[end]);
    }

    return out;
}

double CayenneLPPPolyline::distance(const Point& point, const Point& lineStart, const Point& lineEnd) {
    double dLat = lineEnd.first - lineStart.first;
    double dLon = lineEnd.second - lineStart.second;

    // Normalise
    const double mag = sqrt(dLat * dLat + dLon * dLon);
    if (mag > 0.0) {
        dLat /= mag; dLon /= mag;
    }

    const double pvx = point.first - lineStart.first;
    const double pvy = point.second - lineStart.second;

    // Get dot product (project pv onto normalized direction)
    const double pvdot = dLat * pvx + dLon * pvy;

    // Scale line direction vector
    const double dsx = pvdot * dLat;
    const double dsy = pvdot * dLon;

    // Subtract this from pv
    const double ax = pvx - dsx;
    const double ay = pvy - dsy;

    return sqrt(ax * ax + ay * ay);
}

#endif
