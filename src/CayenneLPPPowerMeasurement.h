/*
 * CayenneLPP - CayenneLPP Message Struct
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef CAYENNE_LPP_POWER_MEASUREMENT_H
#define CAYENNE_LPP_POWER_MEASUREMENT_H

#include <array>
#include <bitset>
#include <optional>

#include "SFloat16.h"

class CayenneLPPPowerMeasurement {
public:
    static CayenneLPPPowerMeasurement fromRawPointer(const uint8_t* raw);

    CayenneLPPPowerMeasurement();

    bool operator==(const CayenneLPPPowerMeasurement& other) const;

    uint32_t encodedSize() const;

    void addCurrentPower(double value);
    void addMinMeasuredPower(double value);
    void addMaxMeasuredPower(double value);
    void addMinRangePower(double value);
    void addMaxRangePower(double value);
    void addExportEnergy(double value);
    void addImportEnergy(double value);

    double currentPower() const;
    std::optional<double> minMeasuredPower() const;
    std::optional<double> maxMeasuredPower() const;
    std::optional<double> minRangePower() const;
    std::optional<double> maxRangePower() const;
    std::optional<double> exportEnergy() const;
    std::optional<double> importEnergy() const;

    std::vector<uint8_t> encode() const;

private:
    std::array<std::optional<SFloat16>, 7> m_values;
    std::bitset<6> m_flags;
};

#endif // CAYENNE_LPP_POWER_MEASUREMENT_H
