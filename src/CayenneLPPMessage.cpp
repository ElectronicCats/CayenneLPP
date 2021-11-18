/*
 * CayenneLPP - CayenneLPP Message Struct
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef ARDUINO
#include "CayenneLPPMessage.h"

template <typename T>
std::optional<T> CayenneLPPMessage::getValue(uint8_t objectId) const {
    if (m_values.count(objectId) == 0) {
        return {};
    }

    if (!std::holds_alternative<T>(m_values.at(objectId))) {
        return {};
    }

    return { std::get<T>(m_values.at(objectId)) };
}

// Explicit template instantiation
template std::optional<float> CayenneLPPMessage::getValue(uint8_t) const;
template std::optional<uint32_t> CayenneLPPMessage::getValue(uint8_t) const;
template std::optional<std::array<float, 3>> CayenneLPPMessage::getValue(uint8_t) const;
template std::optional<std::array<uint8_t, 3>> CayenneLPPMessage::getValue(uint8_t) const;
#endif
