# CayenneLPP

This is an Arduino Library for Arduino Compatible with Cayenne Low Power Payload with Extended Data Types.

## Introduction

CayenneLPP is a format designed by [myDevices](https://mydevices.com/about/) to integrate LoRaWan nodes into their IoT platform [Cayenne](https://mydevices.com/cayenne/features/). It is used to send sensor data in a packed way to [The Things Network platform](https://www.thethingsnetwork.org). You can read more on https://mydevices.com/cayenne/docs/lora/#lora-cayenne-low-power-payload

## Description

CayenneLPP format is a quite well optimized way to send sensor data over low bit rate connection, like LoRa. You may find, probably, a better way for your specific project but CayenneLPP is a standarized and proven format that packs data in a suffiient way. It implements basic sensor types specified by [OMA SpecWorks](https://www.omaspecworks.org), formerly IPSO Alliance.

It supports multichannel data, which means that you can use it on multisensor devices.

This version of the library includes several IPSO data types not included in the original work by [Johan Stokking](https://github.com/TheThingsNetwork/arduino-device-lib) or most of the forks and side works by other people. In addition it includes fully backwards compatibly decoder in JavaScript, suitable for implementations with NodeRED or TTN, for instance.

## Dependencies

When using the decoder, you must install the [ArduinoJson 6.X](https://arduinojson.org/) library. You can find it in both the Arduino IDE and PlatformIO library managers.

## API

See [API.md](API.md).

## References

* [Cayenne Low Power Payload](https://mydevices.com/cayenne/docs/#lora-cayenne-low-power-payload)
* [IPSO data types](http://openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html#extlabel)

### Maintainer

Electronic Cats invests time and resources providing this open source design, please support Electronic Cats and open-source hardware by purchasing products from Electronic Cats!

## License

Based in the work of [Johan Stokking](https://github.com/TheThingsNetwork/arduino-device-lib).

The MIT License (MIT)
