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
#include <vector>

struct CayenneLPPMessage {

  // Original LPPv1 data types
  uint32_t digitalInput = 0;
  uint32_t digitalOutput = 0;
  float analogInput = 0.0f;
  float analogOutput = 0.0f;
  uint32_t luminosity = 0;
  uint32_t presence = 0;
  float temperature = 0.0f;
  float relativeHumidity = 0.0f;
  std::array<float, 3> accelerometer;
  float barometricPressure = 0.0f;
  std::array<float, 3> gyrometer;
  std::array<float, 3> gps;

  // Additional data types
  uint32_t unixTime = 0;
  float genericSensor = 0.0f;
  float voltage = 0.0f;
  float current = 0.0f;
  uint32_t frequency = 0;
  uint32_t percentage = 0;
  float altitude = 0.0f;
  uint32_t power = 0;
  float distance = 0.0f;
  float energy = 0.0f;
  float direction = 0.0f;
  uint32_t onOffSwitch = 0;
  uint32_t concentration = 0;
  std::array<uint8_t, 3> colour;

  // Non-IPSO data types
  std::vector<std::pair<double, double>> polyline;
};

#endif
