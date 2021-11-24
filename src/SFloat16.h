/*
 * CayenneLPP - CayenneLPP Message Struct
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef SFLOAT16_H
#define SFLOAT16_H

#include <cmath>
#include <cstdint>

class SFloat16 {
public:
    SFloat16();
    SFloat16(double d);
    SFloat16(uint16_t u);

    bool operator==(const SFloat16& other) const;

    SFloat16& operator=(double d);
    operator double() const;

    SFloat16& operator=(uint16_t u);
    operator uint16_t() const;

private:
    int16_t m_mantissa = 0;
    int8_t  m_exponent = 0;

};

#endif // SFLOAT16_H
