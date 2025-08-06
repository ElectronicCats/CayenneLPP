// Adapted from https://developer.mbed.org/teams/myDevicesIoT/code/Cayenne-LPP/

// Copyright © 2017 The Things Network
// Use of this source code is governed by the MIT license that can be found in the LICENSE file.

#include "CayenneLPP.h"

#ifndef ARDUINO
#include <cstdlib>
#include <cstring>
#endif

// ----------------------------------------------------------------------------

CayenneLPP::CayenneLPP(uint8_t size) : _maxsize(size)
#ifndef ARDUINO
  , _polyline(size - 2)
#endif
{
  _buffer = (uint8_t *)malloc(size);
  _cursor = 0;
}

CayenneLPP::~CayenneLPP(void) {
  free(_buffer);
}

void CayenneLPP::reset(void) {
  _cursor = 0;
}

uint8_t CayenneLPP::getSize(void) {
  return _cursor;
}

uint8_t *CayenneLPP::getBuffer(void) {
  return _buffer;
}

uint8_t CayenneLPP::copy(uint8_t *dst) {
  memcpy(dst, _buffer, _cursor);
  return _cursor;
}

uint8_t CayenneLPP::getError() {
  uint8_t error = _error;
  _error = LPP_ERROR_OK;
  return error;
}

// ----------------------------------------------------------------------------

bool CayenneLPP::isType(uint8_t type) {

  switch (type) {
#ifndef CAYENNE_DISABLE_DIGITAL_INPUT
    case LPP_DIGITAL_INPUT:
#endif
#ifndef CAYENNE_DISABLE_DIGITAL_OUTPUT
    case LPP_DIGITAL_OUTPUT:
#endif
#ifndef CAYENNE_DISABLE_ANALOG_INPUT
    case LPP_ANALOG_INPUT:
#endif
#ifndef CAYENNE_DISABLE_ANALOG_OUTPUT
    case LPP_ANALOG_OUTPUT:
#endif
#ifndef CAYENNE_DISABLE_GENERIC_SENSOR
    case LPP_GENERIC_SENSOR:
#endif
#ifndef CAYENNE_DISABLE_LUMINOSITY
    case LPP_LUMINOSITY:
#endif
#ifndef CAYENNE_DISABLE_PRESENCE
    case LPP_PRESENCE:
#endif
#ifndef CAYENNE_DISABLE_TEMPERATURE
    case LPP_TEMPERATURE:
#endif
#ifndef CAYENNE_DISABLE_RELATIVE_HUMIDITY
    case LPP_RELATIVE_HUMIDITY:
#endif
#ifndef CAYENNE_DISABLE_ACCELEROMETER
    case LPP_ACCELEROMETER:
#endif
#ifndef CAYENNE_DISABLE_BAROMETRIC_PRESSUE
    case LPP_BAROMETRIC_PRESSURE:
#endif
#ifndef CAYENNE_DISABLE_VOLTAGE
    case LPP_VOLTAGE:
#endif
#ifndef CAYENNE_DISABLE_CURRENT
    case LPP_CURRENT:
#endif
#ifndef CAYENNE_DISABLE_FREQUENCY
    case LPP_FREQUENCY:
#endif
#ifndef CAYENNE_DISABLE_PERCENTAGE
    case LPP_PERCENTAGE:
#endif
#ifndef CAYENNE_DISABLE_ALTITUDE
    case LPP_ALTITUDE:
#endif
#ifndef CAYENNE_DISABLE_POWER
    case LPP_POWER:
#endif
#ifndef CAYENNE_DISABLE_DISTANCE
    case LPP_DISTANCE:
#endif
#ifndef CAYENNE_DISABLE_ENERGY
    case LPP_ENERGY:
#endif
#ifndef CAYENNE_DISABLE_DIRECTION
    case LPP_DIRECTION:
#endif
#ifndef CAYENNE_DISABLE_UNIX_TIME
    case LPP_UNIXTIME:
#endif
#ifndef CAYENNE_DISABLE_GYROMETER
    case LPP_GYROMETER:
#endif
#ifndef CAYENNE_DISABLE_GPS
    case LPP_GPS:
#endif
#ifndef CAYENNE_DISABLE_SWITCH
    case LPP_SWITCH:
#endif
#ifndef CAYENNE_DISABLE_CONCENTRATION
    case LPP_CONCENTRATION:
#endif
#ifndef CAYENNE_DISABLE_COLOUR
    case LPP_COLOUR:
#endif
#ifndef ARDUINO
    case LPP_POLYLINE:
#endif
      return true;
  }

  return false;
}

const char * CayenneLPP::getTypeName(uint8_t type) {

    switch (type) {

#ifndef CAYENNE_DISABLE_DIGITAL_INPUT
        case LPP_DIGITAL_INPUT:
          return "digital_in";
#endif

#ifndef CAYENNE_DISABLE_DIGITAL_OUTPUT
        case LPP_DIGITAL_OUTPUT:
          return "digital_out";
#endif

#ifndef CAYENNE_DISABLE_ANALOG_INPUT
        case LPP_ANALOG_INPUT:
          return "analog_in";
#endif

#ifndef CAYENNE_DISABLE_ANALOG_OUTPUT
        case LPP_ANALOG_OUTPUT:
          return "analog_out";
#endif

#ifndef CAYENNE_DISABLE_GENERIC_SENSOR
        case LPP_GENERIC_SENSOR:
          return "generic";
#endif

#ifndef CAYENNE_DISABLE_LUMINOSITY
        case LPP_LUMINOSITY:
          return "luminosity";
#endif

#ifndef CAYENNE_DISABLE_PRESENCE
        case LPP_PRESENCE:
          return "presence";
#endif

#ifndef CAYENNE_DISABLE_TEMPERATURE
        case LPP_TEMPERATURE:
          return "temperature";
#endif

#ifndef CAYENNE_DISABLE_RELATIVE_HUMIDITY
        case LPP_RELATIVE_HUMIDITY:
          return "humidity";
#endif

#ifndef CAYENNE_DISABLE_ACCELEROMETER
        case LPP_ACCELEROMETER:
          return "accelerometer";
#endif

#ifndef CAYENNE_DISABLE_BAROMETRIC_PRESSUE
        case LPP_BAROMETRIC_PRESSURE:
          return "pressure";
#endif

#ifndef CAYENNE_DISABLE_VOLTAGE
        case LPP_VOLTAGE:
          return "voltage";
#endif

#ifndef CAYENNE_DISABLE_CURRENT
        case LPP_CURRENT:
          return "current";
#endif

#ifndef CAYENNE_DISABLE_FREQUENCY
        case LPP_FREQUENCY:
          return "frequency";
#endif

#ifndef CAYENNE_DISABLE_PERCENTAGE
        case LPP_PERCENTAGE:
          return "percentage";
#endif

#ifndef CAYENNE_DISABLE_ALTITUDE
        case LPP_ALTITUDE:
          return "altitude";
#endif

#ifndef CAYENNE_DISABLE_POWER
        case LPP_POWER:
          return "power";
#endif

#ifndef CAYENNE_DISABLE_DISTANCE
        case LPP_DISTANCE:
          return "distance";
#endif

#ifndef CAYENNE_DISABLE_ENERGY
        case LPP_ENERGY:
          return "energy";
#endif

#ifndef CAYENNE_DISABLE_DIRECTION
        case LPP_DIRECTION:
          return "direction";
#endif

#ifndef CAYENNE_DISABLE_UNIX_TIME
        case LPP_UNIXTIME:
          return "time";
#endif

#ifndef CAYENNE_DISABLE_GYROMETER
        case LPP_GYROMETER:
          return "gyrometer";
#endif

#ifndef CAYENNE_DISABLE_GPS
        case LPP_GPS:
          return "gps";
#endif

#ifndef CAYENNE_DISABLE_SWITCH
        case LPP_SWITCH:
          return "switch";
#endif

#ifndef CAYENNE_DISABLE_CONCENTRATION
        case LPP_CONCENTRATION:
          return "concentration";
#endif

#ifndef CAYENNE_DISABLE_COLOUR
        case LPP_COLOUR:
          return "colour";
#endif

        default:
          return nullptr;
    }

}

uint8_t CayenneLPP::getTypeSize(uint8_t type) {

  switch (type) {

#ifndef CAYENNE_DISABLE_DIGITAL_INPUT
    case LPP_DIGITAL_INPUT:
      return LPP_DIGITAL_INPUT_SIZE;
#endif

#ifndef CAYENNE_DISABLE_DIGITAL_OUTPUT
    case LPP_DIGITAL_OUTPUT:
      return LPP_DIGITAL_OUTPUT_SIZE;
#endif

#ifndef CAYENNE_DISABLE_ANALOG_INPUT
    case LPP_ANALOG_INPUT:
      return LPP_ANALOG_INPUT_SIZE;
#endif

#ifndef CAYENNE_DISABLE_ANALOG_OUTPUT
    case LPP_ANALOG_OUTPUT:
      return LPP_ANALOG_OUTPUT_SIZE;
#endif

#ifndef CAYENNE_DISABLE_GENERIC_SENSOR
    case LPP_GENERIC_SENSOR:
      return LPP_GENERIC_SENSOR_SIZE;
#endif

#ifndef CAYENNE_DISABLE_LUMINOSITY
    case LPP_LUMINOSITY:
      return LPP_LUMINOSITY_SIZE;
#endif

#ifndef CAYENNE_DISABLE_PRESENCE
    case LPP_PRESENCE:
      return LPP_PRESENCE_SIZE;
#endif

#ifndef CAYENNE_DISABLE_TEMPERATURE
    case LPP_TEMPERATURE:
      return LPP_TEMPERATURE_SIZE;
#endif

#ifndef CAYENNE_DISABLE_RELATIVE_HUMIDITY
    case LPP_RELATIVE_HUMIDITY:
      return LPP_RELATIVE_HUMIDITY_SIZE;
#endif

#ifndef CAYENNE_DISABLE_ACCELEROMETER
    case LPP_ACCELEROMETER:
      return LPP_ACCELEROMETER_SIZE;
#endif

#ifndef CAYENNE_DISABLE_BAROMETRIC_PRESSUE
    case LPP_BAROMETRIC_PRESSURE:
      return LPP_BAROMETRIC_PRESSURE_SIZE;
#endif

#ifndef CAYENNE_DISABLE_VOLTAGE
    case LPP_VOLTAGE:
      return LPP_VOLTAGE_SIZE;
#endif

#ifndef CAYENNE_DISABLE_CURRENT
    case LPP_CURRENT:
      return LPP_CURRENT_SIZE;
#endif

#ifndef CAYENNE_DISABLE_FREQUENCY
    case LPP_FREQUENCY:
      return LPP_FREQUENCY_SIZE;
#endif

#ifndef CAYENNE_DISABLE_PERCENTAGE
    case LPP_PERCENTAGE:
      return LPP_PERCENTAGE_SIZE;
#endif

#ifndef CAYENNE_DISABLE_ALTITUDE
    case LPP_ALTITUDE:
      return LPP_ALTITUDE_SIZE;
#endif

#ifndef CAYENNE_DISABLE_POWER
    case LPP_POWER:
      return LPP_POWER_SIZE;
#endif

#ifndef CAYENNE_DISABLE_DISTANCE
    case LPP_DISTANCE:
      return LPP_DISTANCE_SIZE;
#endif

#ifndef CAYENNE_DISABLE_ENERGY
    case LPP_ENERGY:
      return LPP_ENERGY_SIZE;
#endif

#ifndef CAYENNE_DISABLE_DIRECTION
    case LPP_DIRECTION:
      return LPP_DIRECTION_SIZE;
#endif

#ifndef CAYENNE_DISABLE_UNIX_TIME
    case LPP_UNIXTIME:
      return LPP_UNIXTIME_SIZE;
#endif

#ifndef CAYENNE_DISABLE_GYROMETER
    case LPP_GYROMETER:
      return LPP_GYROMETER_SIZE;
#endif

#ifndef CAYENNE_DISABLE_GPS
    case LPP_GPS:
      return LPP_GPS_SIZE;
#endif

#ifndef CAYENNE_DISABLE_SWITCH
    case LPP_SWITCH:
      return LPP_SWITCH_SIZE;
#endif

#ifndef CAYENNE_DISABLE_CONCENTRATION
    case LPP_CONCENTRATION:
      return LPP_CONCENTRATION_SIZE;
#endif

#ifndef CAYENNE_DISABLE_COLOUR
    case LPP_COLOUR:
      return LPP_COLOUR_SIZE;
#endif

    default:
      return 0;
  }
}

uint32_t CayenneLPP::getTypeMultiplier(uint8_t type) {

  switch (type) {

#ifndef CAYENNE_DISABLE_DIGITAL_INPUT
    case LPP_DIGITAL_INPUT:
      return LPP_DIGITAL_INPUT_MULT;
#endif

#ifndef CAYENNE_DISABLE_DIGITAL_OUTPUT
    case LPP_DIGITAL_OUTPUT:
      return LPP_DIGITAL_OUTPUT_MULT;
#endif

#ifndef CAYENNE_DISABLE_ANALOG_INPUT
    case LPP_ANALOG_INPUT:
      return LPP_ANALOG_INPUT_MULT;
#endif

#ifndef CAYENNE_DISABLE_ANALOG_OUTPUT
    case LPP_ANALOG_OUTPUT:
      return LPP_ANALOG_OUTPUT_MULT;
#endif

#ifndef CAYENNE_DISABLE_GENERIC_SENSOR
    case LPP_GENERIC_SENSOR:
      return LPP_GENERIC_SENSOR_MULT;
#endif

#ifndef CAYENNE_DISABLE_LUMINOSITY
    case LPP_LUMINOSITY:
      return LPP_LUMINOSITY_MULT;
#endif

#ifndef CAYENNE_DISABLE_PRESENCE
    case LPP_PRESENCE:
      return LPP_PRESENCE_MULT;
#endif

#ifndef CAYENNE_DISABLE_TEMPERATURE
    case LPP_TEMPERATURE:
      return LPP_TEMPERATURE_MULT;
#endif

#ifndef CAYENNE_DISABLE_RELATIVE_HUMIDITY
    case LPP_RELATIVE_HUMIDITY:
      return LPP_RELATIVE_HUMIDITY_MULT;
#endif

#ifndef CAYENNE_DISABLE_ACCELEROMETER
    case LPP_ACCELEROMETER:
      return LPP_ACCELEROMETER_MULT;
#endif

#ifndef CAYENNE_DISABLE_BAROMETRIC_PRESSUE
    case LPP_BAROMETRIC_PRESSURE:
      return LPP_BAROMETRIC_PRESSURE_MULT;
#endif

#ifndef CAYENNE_DISABLE_VOLTAGE
    case LPP_VOLTAGE:
      return LPP_VOLTAGE_MULT;
#endif

#ifndef CAYENNE_DISABLE_CURRENT
    case LPP_CURRENT:
      return LPP_CURRENT_MULT;
#endif

#ifndef CAYENNE_DISABLE_FREQUENCY
    case LPP_FREQUENCY:
      return LPP_FREQUENCY_MULT;
#endif

#ifndef CAYENNE_DISABLE_PERCENTAGE
    case LPP_PERCENTAGE:
      return LPP_PERCENTAGE_MULT;
#endif

#ifndef CAYENNE_DISABLE_ALTITUDE
    case LPP_ALTITUDE:
      return LPP_ALTITUDE_MULT;
#endif

#ifndef CAYENNE_DISABLE_POWER
    case LPP_POWER:
      return LPP_POWER_MULT;
#endif

#ifndef CAYENNE_DISABLE_DISTANCE
    case LPP_DISTANCE:
      return LPP_DISTANCE_MULT;
#endif

#ifndef CAYENNE_DISABLE_ENERGY
    case LPP_ENERGY:
      return LPP_ENERGY_MULT;
#endif

#ifndef CAYENNE_DISABLE_DIRECTION
    case LPP_DIRECTION:
      return LPP_DIRECTION_MULT;
#endif

#ifndef CAYENNE_DISABLE_UNIX_TIME
    case LPP_UNIXTIME:
      return LPP_UNIXTIME_MULT;
#endif

#ifndef CAYENNE_DISABLE_GYROMETER
    case LPP_GYROMETER:
      return LPP_GYROMETER_MULT;
#endif

#ifndef CAYENNE_DISABLE_SWITCH
    case LPP_SWITCH:
      return LPP_SWITCH_MULT;
#endif

#ifndef CAYENNE_DISABLE_CONCENTRATION
    case LPP_CONCENTRATION:
      return LPP_CONCENTRATION_MULT;
#endif

#ifndef CAYENNE_DISABLE_COLOUR
    case LPP_COLOUR:
      return LPP_COLOUR_MULT;
#endif

    default:
      return 0;
  }
}

bool CayenneLPP::getTypeSigned(uint8_t type) {

  switch (type) {

#ifndef CAYENNE_DISABLE_ANALOG_INPUT
    case LPP_ANALOG_INPUT:
#endif
#ifndef CAYENNE_DISABLE_ANALOG_OUTPUT
    case LPP_ANALOG_OUTPUT:
#endif
#ifndef CAYENNE_DISABLE_TEMPERATURE
    case LPP_TEMPERATURE:
#endif
#ifndef CAYENNE_DISABLE_ACCELEROMETER
    case LPP_ACCELEROMETER:
#endif
#ifndef CAYENNE_DISABLE_ALTITUDE
    case LPP_ALTITUDE:
#endif
#ifndef CAYENNE_DISABLE_GYROMETER
    case LPP_GYROMETER:
#endif
#ifndef CAYENNE_DISABLE_GPS
    case LPP_GPS:
#endif
      return true;
  }
  return false;
}

// ----------------------------------------------------------------------------

template <typename T> uint8_t CayenneLPP::addField(uint8_t type, uint8_t channel, T value) {

  // Check type
  if (!isType(type)) {
    _error = LPP_ERROR_UNKOWN_TYPE;
    return 0;
  }

  // Type definition
  uint8_t size = getTypeSize(type);
  uint32_t multiplier = getTypeMultiplier(type);
  bool is_signed = getTypeSigned(type);

  // check buffer overflow
  if ((_cursor + size + 2) > _maxsize) {
    _error = LPP_ERROR_OVERFLOW;
    return 0;
  }

  // check sign
  bool sign = value < 0;
  if (sign) value = -value;

  // get value to store
  uint32_t v = value * multiplier;

  // format an uint32_t as if it was an int32_t
  if (is_signed & sign) {
    uint32_t mask = (1 << (size * 8)) - 1;
    v = v & mask;
    if (sign) v = mask - v + 1;
  }

  // header
  _buffer[_cursor++] = channel;
  _buffer[_cursor++] = type;

  // add bytes (MSB first)
  for (uint8_t i=1; i<=size; i++) {
    _buffer[_cursor + size - i] = (v & 0xFF);
    v >>= 8;
  }

  // update & return _cursor
  _cursor += size;
  return _cursor;

}

#ifndef CAYENNE_DISABLE_DIGITAL_INPUT
uint8_t CayenneLPP::addDigitalInput(uint8_t channel, uint32_t value) {
  return addField(LPP_DIGITAL_INPUT, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_DIGITAL_OUTPUT
uint8_t CayenneLPP::addDigitalOutput(uint8_t channel, uint32_t value) {
  return addField(LPP_DIGITAL_OUTPUT, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_ANALOG_INPUT
uint8_t CayenneLPP::addAnalogInput(uint8_t channel, float value) {
  return addField(LPP_ANALOG_INPUT, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_ANALOG_OUTPUT
uint8_t CayenneLPP::addAnalogOutput(uint8_t channel, float value) {
  return addField(LPP_ANALOG_OUTPUT, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_GENERIC_SENSOR
uint8_t CayenneLPP::addGenericSensor(uint8_t channel, float value)  {
  return addField(LPP_GENERIC_SENSOR, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_LUMINOSITY
uint8_t CayenneLPP::addLuminosity(uint8_t channel, uint32_t value) {
  return addField(LPP_LUMINOSITY, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_PRESENCE
uint8_t CayenneLPP::addPresence(uint8_t channel, uint32_t value) {
  return addField(LPP_PRESENCE, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_TEMPERATURE
uint8_t CayenneLPP::addTemperature(uint8_t channel, float value) {
  return addField(LPP_TEMPERATURE, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_RELATIVE_HUMIDITY
uint8_t CayenneLPP::addRelativeHumidity(uint8_t channel, float value) {
  return addField(LPP_RELATIVE_HUMIDITY, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_VOLTAGE
uint8_t CayenneLPP::addVoltage(uint8_t channel, float value) {
  return addField(LPP_VOLTAGE, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_CURRENT
uint8_t CayenneLPP::addCurrent(uint8_t channel, float value) {
  return addField(LPP_CURRENT, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_FREQUENCY
uint8_t CayenneLPP::addFrequency(uint8_t channel, uint32_t value) {
  return addField(LPP_FREQUENCY, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_PERCENTAGE
uint8_t CayenneLPP::addPercentage(uint8_t channel, uint32_t value) {
  return addField(LPP_PERCENTAGE, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_ALTITUDE
uint8_t CayenneLPP::addAltitude(uint8_t channel, float value) {
  return addField(LPP_ALTITUDE, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_POWER
uint8_t CayenneLPP::addPower(uint8_t channel, float value) {
  return addField(LPP_POWER, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_DISTANCE
uint8_t CayenneLPP::addDistance(uint8_t channel, float value) {
  return addField(LPP_DISTANCE, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_ENERGY
uint8_t CayenneLPP::addEnergy(uint8_t channel, float value) {
  return addField(LPP_ENERGY, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_BAROMETRIC_PRESSUE
uint8_t CayenneLPP::addBarometricPressure(uint8_t channel, float value) {
  return addField(LPP_BAROMETRIC_PRESSURE, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_UNIX_TIME
uint8_t CayenneLPP::addUnixTime(uint8_t channel, uint32_t value) {
  return addField(LPP_UNIXTIME, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_DIRECTION
uint8_t CayenneLPP::addDirection(uint8_t channel, float value) {
  return addField(LPP_DIRECTION, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_SWITCH
uint8_t CayenneLPP::addSwitch(uint8_t channel, uint32_t value) {
  return addField(LPP_SWITCH, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_CONCENTRATION
uint8_t CayenneLPP::addConcentration(uint8_t channel, uint32_t value) {
  return addField(LPP_CONCENTRATION, channel, value);
}
#endif

#ifndef CAYENNE_DISABLE_COLOUR
uint8_t CayenneLPP::addColour(uint8_t channel, uint8_t r, uint8_t g, uint8_t b)
{
  // check buffer overflow
  if ((_cursor + LPP_COLOUR_SIZE + 2) > _maxsize) {
    _error = LPP_ERROR_OVERFLOW;
    return 0;
  }
  _buffer[_cursor++] = channel;
  _buffer[_cursor++] = LPP_COLOUR;
  _buffer[_cursor++] = r;
  _buffer[_cursor++] = g;
  _buffer[_cursor++] = b;


  return _cursor;
}
#endif

#ifndef CAYENNE_DISABLE_ACCELEROMETER
uint8_t CayenneLPP::addAccelerometer(uint8_t channel, float x, float y, float z) {

  // check buffer overflow
  if ((_cursor + LPP_ACCELEROMETER_SIZE + 2) > _maxsize) {
    _error = LPP_ERROR_OVERFLOW;
    return 0;
  }

  int16_t vx = x * LPP_ACCELEROMETER_MULT;
  int16_t vy = y * LPP_ACCELEROMETER_MULT;
  int16_t vz = z * LPP_ACCELEROMETER_MULT;

  _buffer[_cursor++] = channel;
  _buffer[_cursor++] = LPP_ACCELEROMETER;
  _buffer[_cursor++] = vx >> 8;
  _buffer[_cursor++] = vx;
  _buffer[_cursor++] = vy >> 8;
  _buffer[_cursor++] = vy;
  _buffer[_cursor++] = vz >> 8;
  _buffer[_cursor++] = vz;

  return _cursor;

}
#endif

#ifndef CAYENNE_DISABLE_GYROMETER
uint8_t CayenneLPP::addGyrometer(uint8_t channel, float x, float y, float z) {

  // check buffer overflow
  if ((_cursor + LPP_GYROMETER_SIZE + 2) > _maxsize) {
    _error = LPP_ERROR_OVERFLOW;
    return 0;
  }

  int16_t vx = x * LPP_GYROMETER_MULT;
  int16_t vy = y * LPP_GYROMETER_MULT;
  int16_t vz = z * LPP_GYROMETER_MULT;

  _buffer[_cursor++] = channel;
  _buffer[_cursor++] = LPP_GYROMETER;
  _buffer[_cursor++] = vx >> 8;
  _buffer[_cursor++] = vx;
  _buffer[_cursor++] = vy >> 8;
  _buffer[_cursor++] = vy;
  _buffer[_cursor++] = vz >> 8;
  _buffer[_cursor++] = vz;

  return _cursor;
}
#endif

#ifndef CAYENNE_DISABLE_GPS
uint8_t CayenneLPP::addGPS(uint8_t channel, float latitude, float longitude, float altitude) {

  // check buffer overflow
  if ((_cursor + LPP_GPS_SIZE + 2) > _maxsize) {
    _error = LPP_ERROR_OVERFLOW;
    return 0;
  }

  int32_t lat = latitude * LPP_GPS_LAT_LON_MULT;
  int32_t lon = longitude * LPP_GPS_LAT_LON_MULT;
  int32_t alt = altitude * LPP_GPS_ALT_MULT;

  _buffer[_cursor++] = channel;
  _buffer[_cursor++] = LPP_GPS;
  _buffer[_cursor++] = lat >> 16;
  _buffer[_cursor++] = lat >> 8;
  _buffer[_cursor++] = lat;
  _buffer[_cursor++] = lon >> 16;
  _buffer[_cursor++] = lon >> 8;
  _buffer[_cursor++] = lon;
  _buffer[_cursor++] = alt >> 16;
  _buffer[_cursor++] = alt >> 8;
  _buffer[_cursor++] = alt;

  return _cursor;

}
#endif


#ifndef ARDUINO
uint8_t CayenneLPP::addPolyline(uint8_t channel,
                                const std::vector<std::pair<double, double>>& coords,
                                CayenneLPPPolyline::Precision precision,
                                CayenneLPPPolyline::Simplification simplification) {

    // check buffer overflow for minimum size
    if ((_cursor + LPP_MIN_POLYLINE_SIZE + 2) > _maxsize) {
      _error = LPP_ERROR_OVERFLOW;
      return 0;
    }

    // encode coordinates
    auto buffer = _polyline.encode(coords, precision, simplification);

    // check buffer overflow for encoded size
    if ((_cursor + buffer.size() + 2) > _maxsize) {
      _error = LPP_ERROR_OVERFLOW;
      return 0;
    }

    _buffer[_cursor++] = channel;
    _buffer[_cursor++] = LPP_POLYLINE;
    std::memcpy(_buffer+_cursor, buffer.data(), buffer.size());
    _cursor += buffer.size();

    return _cursor;
}
#endif

// ----------------------------------------------------------------------------

float CayenneLPP::getValue(uint8_t * buffer, uint8_t size, uint32_t multiplier, bool is_signed) {

    uint32_t value = 0;
    for (uint8_t i=0; i<size; i++) {
      value = (value << 8) + buffer[i];
    }

    int sign = 1;
    if (is_signed) {
      uint32_t bit = 1ul << ((size * 8) - 1);
      if ((value & bit) == bit) {
        value = (bit << 1) - value;
        sign = -1;
      }
    }

    return sign * ((float) value / multiplier);

}

uint32_t CayenneLPP::getValue32(uint8_t * buffer, uint8_t size) {

    uint32_t value = 0;
    for (uint8_t i=0; i<size; i++) {
      value = (value << 8) + buffer[i];
    }

    return value;

}

#if defined(ARDUINO) || defined(IDF_VER)
uint8_t CayenneLPP::decode(uint8_t *buffer, uint8_t len, JsonArray& root) {

  uint8_t count = 0;
  uint8_t index = 0;

  while ((index + 2) < len) {

    count++;

    // Get channel #
    uint8_t channel = buffer[index++];

    // Get data type
    uint8_t type = buffer[index++];
    if (!isType(type)) {
      _error = LPP_ERROR_UNKOWN_TYPE;
      return 0;
    }

    // Type definition
    uint8_t size = getTypeSize(type);
    uint32_t multiplier = getTypeMultiplier(type);
    bool is_signed = getTypeSigned(type);

    // Check buffer size
    if (index + size > len) {
      _error = LPP_ERROR_OVERFLOW;
      return 0;
    }

    // Init object
    JsonObject data = root.add<JsonObject>();
    data["channel"] = channel;
    data["type"] = type;
#ifdef ARDUINO
    data["name"] = String(getTypeName(type));
#else
    data["name"] = std::string(getTypeName(type));
#endif
    
    // Parse types
	if (false) {
	}
#ifndef CAYENNE_DISABLE_COLOUR
	else if (LPP_COLOUR == type) {

      JsonObject object = data["value"].to<JsonObject>();
      object["r"] = getValue(&buffer[index], 1, multiplier, is_signed);
      object["g"] = getValue(&buffer[index+1], 1, multiplier, is_signed);
      object["b"] = getValue(&buffer[index+2], 1, multiplier, is_signed);

    }
#endif
#ifndef CAYENNE_DISABLE_ACCELEROMETER
	else if (LPP_ACCELEROMETER == type) {
      JsonObject object = data["value"].to<JsonObject>();
      object["x"] = getValue(&buffer[index], 2, multiplier, is_signed);
      object["y"] = getValue(&buffer[index+2], 2, multiplier, is_signed);
      object["z"] = getValue(&buffer[index+4], 2, multiplier, is_signed);
    }
#endif
#ifndef CAYENNE_DISABLE_GYROMETER
	else if (LPP_GYROMETER == type) {
      JsonObject object = data["value"].to<JsonObject>();
      object["x"] = getValue(&buffer[index], 2, multiplier, is_signed);
      object["y"] = getValue(&buffer[index+2], 2, multiplier, is_signed);
      object["z"] = getValue(&buffer[index+4], 2, multiplier, is_signed);
    }
#endif
#ifndef CAYENNE_DISABLE_GPS
	else if (LPP_GPS == type) {
      JsonObject object = data["value"].to<JsonObject>();
      object["latitude"] = getValue(&buffer[index], 3, 10000, is_signed);
      object["longitude"] = getValue(&buffer[index+3], 3, 10000, is_signed);
      object["altitude"] = getValue(&buffer[index+6], 3, 100, is_signed);
    }
#endif
#ifndef CAYENNE_DISABLE_GENERIC_SENSOR
	else if (LPP_GENERIC_SENSOR == type) {
      data["value"] = getValue32(&buffer[index], size);
    }
#endif
#ifndef CAYENNE_DISABLE_UNIX_TIME
	else if (LPP_UNIXTIME == type) {
      data["value"] = getValue32(&buffer[index], size);
    }
#endif
	else {
      data["value"] = getValue(&buffer[index], size, multiplier, is_signed);
    }

    index += size;

  }

  return count;

}

uint8_t CayenneLPP::decodeTTN(uint8_t *buffer, uint8_t len, JsonObject& root) {

  uint8_t count = 0;
  uint8_t index = 0;

  while ((index + 2) < len) {

    count++;

    // Get channel #
    uint8_t channel = buffer[index++];

    // Get data type
    uint8_t type = buffer[index++];
    if (!isType(type)) {
      _error = LPP_ERROR_UNKOWN_TYPE;
      return 0;
    }

    // Type definition
    uint8_t size = getTypeSize(type);
    uint32_t multiplier = getTypeMultiplier(type);
    bool is_signed = getTypeSigned(type);

    // Check buffer size
    if (index + size > len) {
      _error = LPP_ERROR_OVERFLOW;
      return 0;
    }

    // Init object
#ifdef ARDUINO
    String name = String(getTypeName(type)) + "_" + channel;
#else
    std::string name = std::string(getTypeName(type)) + "_" + std::to_string(channel);
#endif

    // Parse types
	if (false) {
	}
#ifndef CAYENNE_DISABLE_COLOUR
	else if (LPP_COLOUR == type) {
      JsonObject object = root[name].to<JsonObject>();
      object["r"] = getValue(&buffer[index], 1, multiplier, is_signed);
      object["g"] = getValue(&buffer[index+1], 1, multiplier, is_signed);
      object["b"] = getValue(&buffer[index+2], 1, multiplier, is_signed);

    }
#endif
#ifndef CAYENNE_DISABLE_ACCELEROMETER
	else if (LPP_ACCELEROMETER == type) {

      JsonObject object = root[name].to<JsonObject>();
      object["x"] = getValue(&buffer[index], 2, multiplier, is_signed);
      object["y"] = getValue(&buffer[index+2], 2, multiplier, is_signed);
      object["z"] = getValue(&buffer[index+4], 2, multiplier, is_signed);

    }
#endif
#ifndef CAYENNE_DISABLE_GYROMETER
	else if (LPP_GYROMETER == type) {

      JsonObject object = root[name].to<JsonObject>();
      object["x"] = getValue(&buffer[index], 2, multiplier, is_signed);
      object["y"] = getValue(&buffer[index+2], 2, multiplier, is_signed);
      object["z"] = getValue(&buffer[index+4], 2, multiplier, is_signed);

    }
#endif
#ifndef CAYENNE_DISABLE_GPS
	else if (LPP_GPS == type) {

      JsonObject object = root[name].to<JsonObject>();
      object["latitude"] = getValue(&buffer[index], 3, 10000, is_signed);
      object["longitude"] = getValue(&buffer[index+3], 3, 10000, is_signed);
      object["altitude"] = getValue(&buffer[index+6], 3, 100, is_signed);

    }
#endif
#ifndef CAYENNE_DISABLE_GENERIC_SENSOR
	else if (LPP_GENERIC_SENSOR == type) {
      root[name] = getValue32(&buffer[index], size);
    }
#endif
#ifndef CAYENNE_DISABLE_UNIX_TIME
	else if (LPP_UNIXTIME == type) {
      root[name] = getValue32(&buffer[index], size);
    }
#endif
	else {

      root[name] = getValue(&buffer[index], size, multiplier, is_signed);

    }

    index += size;

  }

  return count;

}
#endif
// Non Arduino frameworks
#ifndef ARDUINO
uint8_t CayenneLPP::decode(uint8_t *buffer, uint8_t len, std::map<uint8_t, CayenneLPPMessage> &messageMap) {

  uint8_t count = 0;
  uint8_t index = 0;

  while ((index + 2) < len) {

    count++;

    // Get channel #
    uint8_t channel = buffer[index++];

    // Get data type
    uint8_t type = buffer[index++];
    if (!isType(type)) {
      _error = LPP_ERROR_UNKOWN_TYPE;
      return 0;
    }

    // Type definition
    uint8_t size = getTypeSize(type);
    uint32_t multiplier = getTypeMultiplier(type);
    bool is_signed = getTypeSigned(type);

    // Check buffer size
    if (index + size > len) {
      _error = LPP_ERROR_OVERFLOW;
      return 0;
    }

    // Parse types
    switch (type) {
    case LPP_DIGITAL_INPUT:
      messageMap[channel].digitalInput = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_DIGITAL_OUTPUT:
      messageMap[channel].digitalOutput = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_ANALOG_INPUT:
      messageMap[channel].analogInput = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_ANALOG_OUTPUT:
      messageMap[channel].analogOutput = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_LUMINOSITY:
      messageMap[channel].luminosity = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_PRESENCE:
      messageMap[channel].presence = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_TEMPERATURE:
      messageMap[channel].temperature = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_RELATIVE_HUMIDITY:
      messageMap[channel].relativeHumidity = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_BAROMETRIC_PRESSURE:
      messageMap[channel].barometricPressure = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_VOLTAGE:
      messageMap[channel].voltage = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_CURRENT:
      messageMap[channel].current = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_FREQUENCY:
      messageMap[channel].frequency = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_PERCENTAGE:
      messageMap[channel].percentage = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_ALTITUDE:
      messageMap[channel].altitude = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_CONCENTRATION:
      messageMap[channel].concentration = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_POWER:
      messageMap[channel].power = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_DISTANCE:
      messageMap[channel].distance = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_ENERGY:
      messageMap[channel].energy = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_DIRECTION:
      messageMap[channel].direction = getValue(&buffer[index], size, multiplier, is_signed);
      break;
    case LPP_SWITCH:
      messageMap[channel].onOffSwitch = getValue(&buffer[index], size, multiplier, is_signed);
      break;

#ifndef CAYENNE_DISABLE_COLOUR
    case LPP_COLOUR:
      messageMap[channel].colour[0] = getValue(&buffer[index], 1, multiplier, is_signed);
      messageMap[channel].colour[1] = getValue(&buffer[index+1], 1, multiplier, is_signed);
      messageMap[channel].colour[2] = getValue(&buffer[index+2], 1, multiplier, is_signed);
      break;
#endif
#ifndef CAYENNE_DISABLE_ACCELEROMETER
    case LPP_ACCELEROMETER:
      messageMap[channel].accelerometer[0] = getValue(&buffer[index], 2, multiplier, is_signed);
      messageMap[channel].accelerometer[1] = getValue(&buffer[index+2], 2, multiplier, is_signed);
      messageMap[channel].accelerometer[2] = getValue(&buffer[index+4], 2, multiplier, is_signed);
      break;
#endif
#ifndef CAYENNE_DISABLE_GYROMETER
    case LPP_GYROMETER:
      messageMap[channel].gyrometer[0] = getValue(&buffer[index], 2, multiplier, is_signed);
      messageMap[channel].gyrometer[1] = getValue(&buffer[index+2], 2, multiplier, is_signed);
      messageMap[channel].gyrometer[2] = getValue(&buffer[index+4], 2, multiplier, is_signed);
      break;
#endif
#ifndef CAYENNE_DISABLE_GPS
    case LPP_GPS:
      messageMap[channel].gps[0] = getValue(&buffer[index], 3, 10000, is_signed);
      messageMap[channel].gps[1] = getValue(&buffer[index+3], 3, 10000, is_signed);
      messageMap[channel].gps[2] = getValue(&buffer[index+6], 3, 100, is_signed);
      break;
#endif
#ifndef CAYENNE_DISABLE_GENERIC_SENSOR
    case LPP_GENERIC_SENSOR:
      messageMap[channel].genericSensor = getValue32(&buffer[index], size);
      break;
#endif
#ifndef CAYENNE_DISABLE_UNIX_TIME
    case LPP_UNIXTIME:
      messageMap[channel].unixTime = getValue32(&buffer[index], size);
      break;
#endif
#ifndef ARDUINO
    case LPP_POLYLINE: {
      size = buffer[index];
      const std::vector<uint8_t> buffer2(&buffer[index], &buffer[index] + size);
      messageMap[channel].polyline = _polyline.decode(buffer2);
      break;
    }
#endif
    default:
      return 0;
      break;
    }

    index += size;

  }

  return count;

}
#endif
