/*
 * CayenneLPP - CayenneLPP Polyline Codec
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef CAYENNELPPPOLYLINE_H
#define CAYENNELPPPOLYLINE_H

#include <utility>
#include <vector>

struct DeltaCoord;

class CayenneLPPPolyline {
public:
    enum Precision : uint8_t {
        //Reserved    = 200,
        //Prec0_00001 = 224,
        //Prec0_000025 = 225,
        //Prec0_00005 = 226,
        Prec0_0001  = 227,
        Prec0_0002  = 228,
        Prec0_0005  = 229,
        Prec0_001   = 230,
        Prec0_002   = 231,
        Prec0_005   = 232,
        Prec0_01    = 233,
        Prec0_02    = 234,
        Prec0_05    = 235,
        Prec0_1     = 236,
        Prec0_2     = 237,
        Prec0_5     = 238,
        Prec1_0     = 239,
        //Prec2_0     = 240,
        //Prec5_0     = 241,
        //Reserved    = 242
    };

    /**
     * @brief The Simplification algorithm to apply
     */
    enum Simplification {
        None = 0,   ///< No simplifaction applied
        PerpendicularDistance = 1,  ///< A simple and fast algorithm
        DouglasPeucker = 2  ///< A sophisticated but complex algorithm
    };

    struct Stats {
        uint32_t keptCoords = 0;
        uint32_t addedCoords = 0;
        uint32_t removedCoords = 0;
    };

    using Point = std::pair<double, double>;

    CayenneLPPPolyline(uint32_t size);

    /**
     * @brief encode Encodes a set of GPS Coordinates into a byte buffer.
     *  The first pair of lat/lon will be encoded a a resolution of 0.0001 degrees, while subsequent
     *  pair will be encoded at lower resolutions as defined by a factor.
     * @param coords The set of coords to be serialized and compressed.
     * @param factor This factor is used as quantization factor for delta compression.
     *  A value of 1 results in a precision of 0.0001 degrees.
     *  This value scales linearly, so a value of 10 would result in a precision of 0.001 degrees.
     *  You can set values as high as 199.
     *  Special values start from 227 (see CayenneLPPPolyline::Precision).
     *  Values 200-226 and 240-255 are reserved for future usage.
     * @param simplification The simplification to apply to coordinates.
     * @return buffer The byte buffer which results from serialization.
     */
    std::vector<uint8_t> encode(const std::vector<Point>& coords,
                                uint8_t factor,
                                Simplification simplification = DouglasPeucker);

    /**
     * @brief encode Encodes a set of GPS Coordinates into a byte buffer.
     * @param coords The set of coords to be serialized and compressed.
     * @param precision This defines the precision for delta compression (see CayenneLPPPolyline::Precision).
     * @param simplification The simplification to apply to coordinates.
     * @return buffer The byte buffer which results from serialization.
     */
    std::vector<uint8_t> encode(const std::vector<Point>& coords,
                                Precision precision = Prec0_0001,
                                Simplification simplification = DouglasPeucker);

    /**
     * @brief decode Decodes a byte buffer back to a set of GPS Coordinates.
     * @param buffer The byte buffer to be deserialized.
     * @return coordinates The resulting coordinates from deserialization.
     */
    static std::vector<std::pair<double, double>> decode(const std::vector<uint8_t>& buffer);

    /**
     * @brief getEncodeStats Obtain some statistics from the encoding process.
     * @return stats The resulting statistics from encoding.
     */
    Stats getEncodeStats() const;

private:
    void reset();
    static double getFactor(uint8_t factor);
    void push(double lat, double lon, bool optimize);
    void pushFirst(double lat, double lon, uint8_t factor);

    void writeHeader(int32_t lat, int32_t lon, uint8_t factor);
    void writeDelta(int8_t lat, int8_t lon, bool optimize);

    static std::vector<Point> douglasPeucker(const std::vector<Point>& pointList, double epsilon);
    static double distance(const Point& point, const Point& lineStart, const Point& lineEnd);

    const uint32_t m_maxSize = 0;
    std::vector<uint8_t> m_buffer;

    double m_prevLat = 0.0;
    double m_prevLon = 0.0;

    double m_errLat = 0.0;
    double m_errLon = 0.0;

    Stats m_stats;
};

#endif // CAYENNELPPPOLYLINE_H
