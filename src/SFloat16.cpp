/*
 * CayenneLPP - CayenneLPP Message Struct
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef ARDUINO

#include "SFloat16.h"

enum SpecialValues {
    PosInfinity = 0x07FE,
    NaN = 0x07FF,
    NRes = 0x0800,
    Reserved = 0x0801,
    NegInfinity = 0x0802
};

SFloat16::SFloat16() {
}

SFloat16::SFloat16(double d) {
    *this = d;
}

SFloat16::SFloat16(uint16_t u) {
    *this = u;
}

bool SFloat16::operator==(const SFloat16& other) const {
    return m_mantissa == other.m_mantissa && m_exponent == other.m_exponent;
}

SFloat16& SFloat16::operator=(double d) {
    if (abs(d) == 0) {
        m_mantissa = 0;
        m_exponent = 0;
    } else if (std::isnan(d)) {
        m_mantissa = NaN;
        m_exponent = 0;
    } else if (std::isinf(d) && d > 0.0) {
        m_mantissa = PosInfinity;
        m_exponent = 0;
    } else if (std::isinf(d) && d < 0.0) {
        m_mantissa = NegInfinity;
        m_exponent = 0;
    } else {
        m_exponent = 0;
        // Scale down
        while (abs(d) >= PosInfinity) {
            d *= 0.1;
            ++m_exponent;
        }
        // Scale up
        while (abs(d) < PosInfinity * 0.1) {
            d *= 10.0;
            --m_exponent;
        }
        m_mantissa = round(d);
    }

    return *this;
}

SFloat16::operator double() const {
    if (m_mantissa == PosInfinity) {
        return std::numeric_limits<double>::infinity();
    } else if (m_mantissa == NegInfinity) {
        return -std::numeric_limits<double>::infinity();
    } else if (m_mantissa == NaN) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return m_mantissa * pow(10.0, m_exponent);
    }
}

SFloat16& SFloat16::operator=(uint16_t u) {
    m_mantissa = u & 0xFFF;
    m_exponent = u >> 12;

    if (m_mantissa >= 0x0800) {
        m_mantissa = -((0x0FFF + 1) - m_mantissa);
    }
    if (m_exponent >= 0x0008) {
        m_exponent = -((0x000F + 1) - m_exponent);
    }

    return *this;
}

SFloat16::operator uint16_t() const {
    return (m_exponent << 12) | (m_mantissa & 0xFFF);
}

#endif
