/*
 * CayenneLPP - CayenneLPP Message Struct
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#ifndef CAYENNE_LPP_MESSAGE_H
#define CAYENNE_LPP_MESSAGE_H

#include <array>
#include <cstdint>
#include <map>
#include <optional>
#include <variant>
#include <vector>

class CayenneLPPMessage {
public:
  template <typename T>
  std::optional<T> getValue(uint8_t objectId) const;

  // Original LPPv1 data types
  float digitalInput = 0;
  float digitalOutput = 0;
  float analogInput = 0.0f;
  float analogOutput = 0.0f;
  float luminosity = 0;
  float presence = 0;
  float temperature = 0.0f;
  float relativeHumidity = 0.0f;
  std::array<float, 3> accelerometer;
  float barometricPressure = 0.0f;
  std::array<float, 3> gyrometer;
  std::array<float, 3> gps;

  // Additional data types
  uint32_t unixTime = 0;
  uint32_t genericSensor = 0;
  float voltage = 0.0f;
  float current = 0.0f;
  float frequency = 0;
  float percentage = 0;
  float altitude = 0.0f;
  float power = 0;
  float distance = 0.0f;
  float energy = 0.0f;
  float direction = 0.0f;
  float onOffSwitch = 0;
  float concentration = 0;
  std::array<uint8_t, 3> colour;

  // Non-IPSO data types
  std::vector<std::pair<double, double>> polyline;

private:
  std::map<uint8_t, std::variant<float, uint32_t, std::array<float, 3>, std::array<uint8_t, 3>>> m_values;

  friend class CayenneLPP;
};

#endif
