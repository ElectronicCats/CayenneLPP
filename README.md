# CayenneLPP _by Electronic Cats_ - Library for Arduino

![LibraryBuild](https://github.com/ElectronicCats/CayenneLPP/workflows/LibraryBuild/badge.svg?branch=master)

This is an Arduino Library for Arduino Compatible with Cayenne Low Power Payload with Extended Data Types.

CayenneLPP is a format designed by [myDevices](https://mydevices.com) to integrate LoRaWan nodes into their [IoT Platform](https://mydevices.com/capabilities). It is used to send sensor data in a packed way to [The Things Network platform](https://www.thethingsnetwork.org). You can read more on [myDevices CayenneLPP](https://docs.mydevices.com/docs/lorawan/cayenne-lpp)

## Description

CayenneLPP format is a quite well-optimized way to send sensor data over low bit rate connection, like LoRa. You may find, probably, a better way for your specific project but CayenneLPP is a standardized and proven format that packs data in a sufficient way. It implements basic sensor types specified by [OMA SpecWorks](https://www.omaspecworks.org), formerly IPSO Alliance.

<p align=center>
  <a href="https://github.com/ElectronicCats/CayenneLPP/wiki">
    <img src="https://github.com/ElectronicCats/CayenneLPP/assets/139595394/a17c04ef-8c5c-493c-bf1a-f3dd4037408a" width="200" height="104" />
  </a>
</p>

It supports multichannel data, which means that you can use it on multisensor devices.

> [!Warning]
> This version of the library includes several IPSO data types not included in the original work by [Johan Stokking](https://github.com/TheThingsNetwork/arduino-device-lib) or most of the forks and side works by other people, **these additional data types are not supported by myDevices Cayenne**. In addition, it includes a fully backward-compatible decoder in JavaScript, suitable for implementations with NodeRED or TTN, for instance. 

When using the decoder, you must install the [ArduinoJson 6.X](https://arduinojson.org/) library. You can find it in both the Arduino IDE and PlatformIO library managers.

## How to contribute <img src="https://electroniccats.com/wp-content/uploads/2018/01/fav.png" height="35"><img src="https://raw.githubusercontent.com/gist/ManulMax/2d20af60d709805c55fd784ca7cba4b9/raw/bcfeac7604f674ace63623106eb8bb8471d844a6/github.gif" height="30">
 Contributions are welcome! 

Please read the document  [**Contribution Manual**](https://github.com/ElectronicCats/electroniccats-cla/blob/main/electroniccats-contribution-manual.md)  which will show you how to contribute your changes to the project.

✨ Thanks to all our [contributors](https://github.com/ElectronicCats/CayenneLPP/graphs/contributors)! ✨

See  [**_Electronic Cats CLA_**](https://github.com/ElectronicCats/electroniccats-cla/blob/main/electroniccats-cla.md) for more information.

See the [**community code of conduct**](https://github.com/ElectronicCats/electroniccats-cla/blob/main/electroniccats-community-code-of-conduct.md)   for a vision of the community we want to build and what we expect from it.

## References

* [Cayenne Low Power Payload](https://mydevices.com/cayenne/docs/#lora-cayenne-low-power-payload)
* [IPSO data types](http://openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html#extlabel)

### Maintainer

Electronic Cats invests time and resources in providing this open-source design design, please support Electronic Cats and open-source hardware by purchasing products from Electronic Cats!

<a href="https://github.com/sponsors/ElectronicCats">
  <img src="https://electroniccats.com/wp-content/uploads/2020/07/Badge_GHS.png" height="104" />
</a>

## License

Based on the work of [Johan Stokking](https://github.com/TheThingsNetwork/arduino-device-lib).

The MIT License (MIT)
