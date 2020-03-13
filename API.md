# CayenneLPP API Reference

The `CayenneLPP` class enables Arduino devices to encode data with the Cayenne Lower Power Protocol (LPP). [Read more about Cayenne LPP](https://mydevices.com/cayenne/docs/#lora-cayenne-low-power-payload)

### Class: `CayenneLPP`

Include and instantiate the CayenneLPP class. The constructor takes the size of the allocated buffer. Depending on the LoRa frequency plan and data rate used, the maximum payload varies. It's safe to send up to 51 bytes of payload.

```c
#include <CayenneLPP.h>

CayenneLPP lpp(uint8_t size);
```

- `uint8_t size`: The maximum payload size to send, e.g. `51`.

### Example

```c
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
CayenneLPP lpp(51);

lpp.reset();
lpp.addTemperature(1, 22.5);
lpp.addBarometricPressure(2, 1073.21);
lpp.addGPS(3, 52.37365, 4.88650, 2);

ttn.sendBytes(lpp.getBuffer(), lpp.getSize());
```

See the [CayenneLPP](https://github.com/TheThingsNetwork/arduino-device-lib/blob/master/examples/CayenneLPP/CayenneLPP.ino) example.

### Method: `reset`

Resets the buffer.

```c
void reset(void);
```

### Method: `getSize`

Returns the size of the buffer.

```c
uint8_t getSize(void);
```

### Method: `getBuffer`

Returns a pointer to the buffer.

```c
uint8_t *getBuffer(void);
```

### Method: `copy`

Copies the internal buffer to a specified buffer and returns the copied size.

```c
uint8_t copy(uint8_t *buffer);
```

### Method: `decode`

Decodes a byte array into a JsonArray (requires ArduinoJson library). The result is an array of objects, each one containing channel, type, type name and value. The value can be a scalar or an object (for accelerometer, gyroscope and GPS data). The method call returns the number of decoded fields or 0 if error.

```c
uint8_t decode(uint8_t *buffer, uint8_t size, JsonArray& root);
```

Example output:

```
[
  {
    "channel": 1,
    "type": 136,
    "name": "gps",
    "value": {
      "latitude": 42.3518,
      "longitude": -87.9094,
      "altitude": 10
    }
  }
]
```

### Method: `decodeTTN`

Decodes a byte array into a JsonObject (requires ArduinoJson library). The result is a json objects, each object name contain name type plus channel. The value can be a scalar or an object (for accelerometer, gyroscope and GPS data). The method call returns the number of decoded fields or 0 if error.

```c
uint8_t decodeTTN(uint8_t *buffer, uint8_t size, JsonObject& root);
```

Example output:

```
{
  "gps_1": {
    "latitude": 42.3518,
    "longitude": -87.9094,
    "altitude": 10
  }
}
```


### Method: `getTypeName`

Returns a pointer to a C-string containing the name of the requested type.

```c
const char * getTypeName(uint8_t type);
```

### Methods: `add...`

Add data to the buffer. The `channel` parameter acts as a key for the data field. The data fields you send are dynamic; you can selectively send data as long as the channel matches.

```c
uint8_t addDigitalInput(uint8_t channel, uint32_t value);
uint8_t addDigitalOutput(uint8_t channel, uint32_t value);
uint8_t addAnalogInput(uint8_t channel, float value); // 3 decimals
uint8_t addAnalogOutput(uint8_t channel, float value); // 3 decimals
uint8_t addLuminosity(uint8_t channel, uint32_t value); // in luxes
uint8_t addPresence(uint8_t channel, uint32_t value);
uint8_t addTemperature(uint8_t channel, float value); // in celcius (1 decimal)
uint8_t addRelativeHumidity(uint8_t channel, float value); // in % (0.5% steps)
uint8_t addAccelerometer(uint8_t channel, float x, float y, float z); // 3 decimals for each axis
uint8_t addBarometricPressure(uint8_t channel, float value); // in hPa (1 decimal)
uint8_t addGyrometer(uint8_t channel, float x, float y, float z); // 2 decimals for each axis
uint8_t addGPS(uint8_t channel, float latitude, float longitude, float altitude); // lat & long with 4 decimals, altitude with 2 decimals

uint8_t addUnixTime(uint8_t channel, uint32_t value);

uint8_t addGenericSensor(uint8_t channel, float value);
uint8_t addVoltage(uint8_t channel, float value); // in volts (2 decimals)
uint8_t addCurrent(uint8_t channel, float value); // in amperes (3 decimals)
uint8_t addFrequency(uint8_t channel, uint32_t value); // in hertzs
uint8_t addPercentage(uint8_t channel, uint32_t value); // 0 to 100
uint8_t addAltitude(uint8_t channel, float value); // in meters
uint8_t addPower(uint8_t channel, uint32_t value); // in watts
uint8_t addDistance(uint8_t channel, float value); // in meters (3 decimals)
uint8_t addEnergy(uint8_t channel, float value); // in kWh (3 decimals)
uint8_t addDirection(uint8_t channel, float value); // in degrees
uint8_t addSwitch(uint8_t channel, uint32_t value); // 0 or 1

uint8_t CayenneLPP::addConcentration(uint8_t channel, uint32_t value); // 1 PPM unsigned - PPM means Parts per million 1PPM = 1 * 10 ^-6 = 0.000 001
uint8_t CayenneLPP::addColour(uint8_t channel, uint8_t r, uint8_t g, uint8_t b); // R: 255 G: 255 B: 255
```

### Method: `getError`

Returns the last error ID, once returned the error is reset to OK. Possible error values are:

* `LPP_ERROR_OK`: no error
* `LPP_ERROR_OVERFLOW`: When encoding, the latest field would have exceeded the internal buffer size. Try increasing the buffer size in the constructor. When decoding, the payload is not long enough to hold the expected data. Probably a size mismatch.
* `LPP_ERROR_UNKNOWN_TYPE`: When decoding, the decoded type does not match any of the supported ones.

```c
uint8_t getError(void);
```
