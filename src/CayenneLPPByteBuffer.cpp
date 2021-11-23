/*
 * CayenneLPP - CayenneLPP Message Struct
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef ARDUINO
#include "CayenneLPPByteBuffer.h"

#include "SFloat16.h"

CayenneLPPByteBuffer CayenneLPPByteBuffer::fromRawPointer(const uint8_t* raw, size_t size) {
    CayenneLPPByteBuffer out;
    out.m_buffer.resize(size);
    std::memcpy(out.m_buffer.data(), raw, size);

    return out;
}

CayenneLPPByteBuffer::CayenneLPPByteBuffer() {
}

template <typename T>
CayenneLPPByteBuffer& CayenneLPPByteBuffer::operator<<(T value) {
    // extend buffer
    m_buffer.resize(m_buffer.size() + sizeof(T));

    // add bytes (MSB first)
    for (size_t i = 1; i <= sizeof(T); ++i) {
        m_buffer[m_cursor + sizeof(T) - i] = (value & 0xFF);
        value >>= 8;
    }

    // update & return
    m_cursor += sizeof(T);
    return *this;
}

template <>
CayenneLPPByteBuffer& CayenneLPPByteBuffer::operator<<(uint8_t value) {
    m_buffer.push_back(value);

    // update & return
    ++m_cursor;
    return *this;
}

template <typename T>
CayenneLPPByteBuffer& CayenneLPPByteBuffer::operator>>(T& value) {
    if (m_buffer.size() < m_cursor + sizeof(T)) {
        return *this;
    }

    value = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        value = (value << 8) + m_buffer[m_cursor + i];
    }

    // update & return
    m_cursor += sizeof(T);
    return *this;
}

void CayenneLPPByteBuffer::reset() {
    m_cursor = 0;
    m_buffer.clear();
}

std::vector<uint8_t> CayenneLPPByteBuffer::buffer() const {
    return m_buffer;
}

// Explicit template instantiation
template CayenneLPPByteBuffer& CayenneLPPByteBuffer::operator<<(uint16_t);
template CayenneLPPByteBuffer& CayenneLPPByteBuffer::operator>>(uint16_t&);
template CayenneLPPByteBuffer& CayenneLPPByteBuffer::operator>>(uint8_t&);
#endif
