/*
 * CayenneLPP - CayenneLPP Message Struct
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef ARDUINO
#include "CayenneLPPPowerMeasurement.h"

#include "CayenneLPPByteBuffer.h"

CayenneLPPPowerMeasurement CayenneLPPPowerMeasurement::fromRawPointer(const uint8_t* raw) {
    CayenneLPPPowerMeasurement out;
    // First: get flags
    out.m_flags = std::bitset<6>(raw[0]);
    auto buffer = CayenneLPPByteBuffer::fromRawPointer(raw + 1, 2 + 1 + out.m_flags.count() * 2);
    // Second: get mandatory fields
    uint16_t val;
    buffer >> val;
    out.m_values[0] = val;

    // Third: get optional fields
    for (size_t i = 0; i < out.m_flags.size(); ++i) {
        if (out.m_flags.test(i)) {
            buffer >> val;
            out.m_values[i+1] = val;
        }
    }

    return out;
}

CayenneLPPPowerMeasurement::CayenneLPPPowerMeasurement() {
}

bool CayenneLPPPowerMeasurement::operator==(const CayenneLPPPowerMeasurement& other) const {
    return m_values == other.m_values;
}

uint32_t CayenneLPPPowerMeasurement::encodedSize() const {
    return 2 + 1 + m_flags.count() * 2;
}

void CayenneLPPPowerMeasurement::addCurrentPower(double value) {
    m_values[0] = value;
}

void CayenneLPPPowerMeasurement::addMinMeasuredPower(double value) {
    m_flags.set(0);
    m_values[1] = value;
}

void CayenneLPPPowerMeasurement::addMaxMeasuredPower(double value) {
    m_flags.set(1);
    m_values[2] = value;
}

void CayenneLPPPowerMeasurement::addMinRangePower(double value) {
    m_flags.set(2);
    m_values[3] = value;
}

void CayenneLPPPowerMeasurement::addMaxRangePower(double value) {
    m_flags.set(3);
    m_values[4] = value;
}

void CayenneLPPPowerMeasurement::addExportEnergy(double value) {
    m_flags.set(4);
    m_values[5] = value;
}

void CayenneLPPPowerMeasurement::addImportEnergy(double value) {
    m_flags.set(5);
    m_values[6] = value;
}

double CayenneLPPPowerMeasurement::currentPower() const {
    return *m_values.at(0);
}

std::optional<double> CayenneLPPPowerMeasurement::minMeasuredPower() const {
    return m_values.at(1);
}

std::optional<double> CayenneLPPPowerMeasurement::maxMeasuredPower() const {
    return m_values.at(2);
}

std::optional<double> CayenneLPPPowerMeasurement::minRangePower() const {
    return m_values.at(3);
}

std::optional<double> CayenneLPPPowerMeasurement::maxRangePower() const {
    return m_values.at(4);
}

std::optional<double> CayenneLPPPowerMeasurement::exportEnergy() const {
    return m_values.at(5);
}

std::optional<double> CayenneLPPPowerMeasurement::importEnergy() const {
    return m_values.at(6);
}

std::vector<uint8_t> CayenneLPPPowerMeasurement::encode() const {
    CayenneLPPByteBuffer buffer;
    // First: push flags
    buffer << (uint8_t)(m_flags.to_ulong() & 0xFF);
    // Second: mandatory fields
    buffer << (uint16_t)*m_values[0];

    // Third: optional fields
    for (size_t i = 0; i < m_flags.size(); ++i) {
        if (m_flags.test(i)) {
            buffer << (uint16_t)*m_values[i+1];
        }
    }

    return buffer.buffer();
}

#endif
