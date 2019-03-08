// Adapted from https://developer.mbed.org/teams/myDevicesIoT/code/Cayenne-LPP/

// Copyright © 2017 The Things Network
// Use of this source code is governed by the MIT license that can be found in the LICENSE file.

#include "CayenneLPP.h"

CayenneLPP::CayenneLPP(uint8_t size) : maxsize(size)
{
  buffer = (uint8_t *)malloc(size);
  cursor = 0;
}

CayenneLPP::~CayenneLPP(void)
{
  free(buffer);
}

void CayenneLPP::reset(void)
{
  cursor = 0;
}

uint8_t CayenneLPP::getSize(void)
{
  return cursor;
}

uint8_t *CayenneLPP::getBuffer(void)
{
  //    uint8_t[cursor] result;
  //    memcpy(result, buffer, cursor);
  //    return result;
  return buffer;
}

uint8_t CayenneLPP::copy(uint8_t *dst)
{
  memcpy(dst, buffer, cursor);
  return cursor;
}

uint8_t CayenneLPP::addDigitalInput(uint8_t channel, uint8_t value)
{
  if ((cursor + LPP_DIGITAL_INPUT_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_DIGITAL_INPUT;
  buffer[cursor++] = value;

  return cursor;
}

uint8_t CayenneLPP::addDigitalOutput(uint8_t channel, uint8_t value)
{
  if ((cursor + LPP_DIGITAL_OUTPUT_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_DIGITAL_OUTPUT;
  buffer[cursor++] = value;

  return cursor;
}

uint8_t CayenneLPP::addAnalogInput(uint8_t channel, float value)
{
  if ((cursor + LPP_ANALOG_INPUT_SIZE) > maxsize)
  {
    return 0;
  }

  int16_t val = value * 100;
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_ANALOG_INPUT;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addAnalogOutput(uint8_t channel, float value)
{
  if ((cursor + LPP_ANALOG_OUTPUT_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t val = value * 100;
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_ANALOG_OUTPUT;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addLuminosity(uint8_t channel, uint16_t lux)
{
  if ((cursor + LPP_LUMINOSITY_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_LUMINOSITY;
  buffer[cursor++] = lux >> 8;
  buffer[cursor++] = lux;

  return cursor;
}

uint8_t CayenneLPP::addGenericValue (uint8_t channel, float value) {
    if ((cursor + LPP_GENERIC_SENSOR_SIZE) > maxsize)
    {
        return 0;
    }
    float val = value;
    uint8_t *ptr = (uint8_t *)&val;

    buffer[cursor++] = channel;
    buffer[cursor++] = LPP_GENERIC_SENSOR;

#if BYTE_ORDER == LITTLE_ENDIAN
    buffer[cursor++] = ptr[3];
    buffer[cursor++] = ptr[2];
    buffer[cursor++] = ptr[1];
    buffer[cursor++] = ptr[0];
#elif
    buffer[cursor++] = ptr[0];
    buffer[cursor++] = ptr[1];
    buffer[cursor++] = ptr[2];
    buffer[cursor++] = ptr[3];
#endif

    return cursor;
}

uint8_t CayenneLPP::addPresence(uint8_t channel, uint8_t value)
{
  if ((cursor + LPP_PRESENCE_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_PRESENCE;
  buffer[cursor++] = value;

  return cursor;
}

uint8_t CayenneLPP::addTemperature(uint8_t channel, float celsius)
{
  if ((cursor + LPP_TEMPERATURE_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t val = celsius * 10;
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_TEMPERATURE;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addRelativeHumidity(uint8_t channel, float rh)
{
  if ((cursor + LPP_RELATIVE_HUMIDITY_SIZE) > maxsize)
  {
    return 0;
  }
  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_RELATIVE_HUMIDITY;
  buffer[cursor++] = rh * 2;

  return cursor;
}

uint8_t CayenneLPP::addAccelerometer(uint8_t channel, float x, float y, float z)
{
  if ((cursor + LPP_ACCELEROMETER_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t vx = x * 1000;
  int16_t vy = y * 1000;
  int16_t vz = z * 1000;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_ACCELEROMETER;
  buffer[cursor++] = vx >> 8;
  buffer[cursor++] = vx;
  buffer[cursor++] = vy >> 8;
  buffer[cursor++] = vy;
  buffer[cursor++] = vz >> 8;
  buffer[cursor++] = vz;

  return cursor;
}

uint8_t CayenneLPP::addBarometricPressure(uint8_t channel, float hpa)
{
  if ((cursor + LPP_BAROMETRIC_PRESSURE_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t val = hpa * 10;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_BAROMETRIC_PRESSURE;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addVoltage (uint8_t channel, float voltage) {
    if ((cursor + LPP_VOLTAGE_SIZE) > maxsize)
    {
        return 0;
    }
    float val = voltage;
    uint8_t *ptr = (uint8_t *)&val;

    buffer[cursor++] = channel;
    buffer[cursor++] = LPP_VOLTAGE;

#if BYTE_ORDER == LITTLE_ENDIAN
    buffer[cursor++] = ptr[3];
    buffer[cursor++] = ptr[2];
    buffer[cursor++] = ptr[1];
    buffer[cursor++] = ptr[0];
#elif
    buffer[cursor++] = ptr[0];
    buffer[cursor++] = ptr[1];
    buffer[cursor++] = ptr[2];
    buffer[cursor++] = ptr[3];
#endif

    return cursor;
}

uint8_t CayenneLPP::addPercentage (uint8_t channel, float percent) {
    if ((cursor + LPP_PERCENTAGE_SIZE) > maxsize)
    {
        return 0;
    }
    float val = percent;
    uint8_t *ptr = (uint8_t *)&val;

    buffer[cursor++] = channel;
    buffer[cursor++] = LPP_PERCENTAGE;

#if BYTE_ORDER == LITTLE_ENDIAN
    buffer[cursor++] = ptr[3];
    buffer[cursor++] = ptr[2];
    buffer[cursor++] = ptr[1];
    buffer[cursor++] = ptr[0];
#elif
    buffer[cursor++] = ptr[0];
    buffer[cursor++] = ptr[1];
    buffer[cursor++] = ptr[2];
    buffer[cursor++] = ptr[3];
#endif

    return cursor;
}

uint8_t CayenneLPP::addUnixTime(uint8_t channel, uint32_t unixtime)
{
  if ((cursor + LPP_UNIXTIME_SIZE) > maxsize)
  {
    return 0;
  }
  int32_t val = unixtime;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_UNIXTIME;
  buffer[cursor++] = val >> 24;
  buffer[cursor++] = val >> 16;
  buffer[cursor++] = val >> 8;
  buffer[cursor++] = val;

  return cursor;
}

uint8_t CayenneLPP::addGyrometer(uint8_t channel, float x, float y, float z)
{
  if ((cursor + LPP_GYROMETER_SIZE) > maxsize)
  {
    return 0;
  }
  int16_t vx = x * 100;
  int16_t vy = y * 100;
  int16_t vz = z * 100;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_GYROMETER;
  buffer[cursor++] = vx >> 8;
  buffer[cursor++] = vx;
  buffer[cursor++] = vy >> 8;
  buffer[cursor++] = vy;
  buffer[cursor++] = vz >> 8;
  buffer[cursor++] = vz;

  return cursor;
}

uint8_t CayenneLPP::addGPS(uint8_t channel, float latitude, float longitude, float meters)
{
  if ((cursor + LPP_GPS_SIZE) > maxsize)
  {
    return 0;
  }
  int32_t lat = latitude * 10000;
  int32_t lon = longitude * 10000;
  int32_t alt = meters * 100;

  buffer[cursor++] = channel;
  buffer[cursor++] = LPP_GPS;

  buffer[cursor++] = lat >> 16;
  buffer[cursor++] = lat >> 8;
  buffer[cursor++] = lat;
  buffer[cursor++] = lon >> 16;
  buffer[cursor++] = lon >> 8;
  buffer[cursor++] = lon;
  buffer[cursor++] = alt >> 16;
  buffer[cursor++] = alt >> 8;
  buffer[cursor++] = alt;

  return cursor;
}
