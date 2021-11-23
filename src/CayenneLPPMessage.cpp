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

// TODO: check if return type can by auto deduced (via auto return type).
template <typename T>
std::optional<T> CayenneLPPMessage::getValue(uint8_t objectId) const {
    // Check if message holds object
    if (m_values.count(objectId) == 0) {
        return {};
    }

    // Check if object is of given type
    // TODO: introduce checking if object type can be casted to given alternative.
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
template std::optional<std::vector<std::pair<double, double>>> CayenneLPPMessage::getValue(uint8_t) const;
template std::optional<CayenneLPPPowerMeasurement> CayenneLPPMessage::getValue(uint8_t) const;

#endif
