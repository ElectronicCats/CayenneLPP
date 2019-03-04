# CayenneLPP

This is an Arduino Library for Arduino Compatible with Cayenne Low Power Payload

## Introduction

CayenneLPP is a format designed by [myDevices](https://mydevices.com/about/) to integrate LoRaWan nodes into their IoT platform [Cayenne](https://mydevices.com/cayenne/features/). It is used to send sensor data in a packed way to [The Things Network platform](https://www.thethingsnetwork.org). You can read more on https://mydevices.com/cayenne/docs/lora/#lora-cayenne-low-power-payload

## Description
CayenneLPP format is a quite well optimized way to send sensor data over low bit rate connection, like LoRa. You may find, probably, a better way for your specific project but CayenneLPP is a standarized and proven format that packs data in a suffiient way. It implements basic sensor types specified by [OMA SpecWorks](https://www.omaspecworks.org), formerly IPSO Alliance.

For instance, it can transmit GPS data in 11 bytes, or 8 port digital I/O in 4 bytes.

In addition, it supports multichannel data. It means that you can use it on multisensor devices.

## Documentation

* [Cayenne Low Power Payload](https://mydevices.com/cayenne/docs/#lora-cayenne-low-power-payload)
* [API](https://github.com/sabas1080/CayenneLPP/blob/master/API.md)
* [CayenneLPP Decoder](https://github.com/gmag11/CayenneLPPdec)

Based in the work of [Johan Stokking](https://github.com/TheThingsNetwork/arduino-device-lib)

Electronic Cats invests time and resources providing this open source design, please support Electronic Cats and open-source hardware by purchasing products from Electronic Cats!

