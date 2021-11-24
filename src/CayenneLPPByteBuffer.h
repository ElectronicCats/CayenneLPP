/*
 * CayenneLPP - CayenneLPP Message Struct
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef CAYENNELPPBYTEBUFFER_H
#define CAYENNELPPBYTEBUFFER_H

#include <iostream>
#include <vector>

class CayenneLPPByteBuffer {
public:
    static CayenneLPPByteBuffer fromRawPointer(const uint8_t* raw, size_t size);
    CayenneLPPByteBuffer();

    template <typename T>
    CayenneLPPByteBuffer& operator<<(T value);

    template <typename T>
    CayenneLPPByteBuffer& operator>>(T& value);

    void reset();

    std::vector<uint8_t> buffer() const;

private:
    size_t m_cursor = 0;
    std::vector<uint8_t> m_buffer;
};

#endif // CAYENNELPPBYTEBUFFER_H
