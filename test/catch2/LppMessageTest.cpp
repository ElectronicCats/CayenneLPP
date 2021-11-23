/*
 * CayenneLPP - Catch2 Unit Tests
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#include <catch2/catch_test_macros.hpp>

#include <CayenneLPP.h>

TEST_CASE("CayenneLPPMessage parameters A-C are decoded", "[LppMessage]") {
    CayenneLPPMessage in;
    in.accelerometer[0] = 1.0;
    in.accelerometer[1] = 2.0;
    in.accelerometer[2] = 3.0;
    in.altitude = 4.0;
    in.analogInput = 5.0;
    in.analogOutput = 6.0;
    in.barometricPressure = 7.0;
    in.colour[0] = 8;
    in.colour[1] = 9;
    in.colour[2] = 10;
    in.concentration = 11;
    in.current = 12.0;

    CayenneLPP clpp(255);
    clpp.addAccelerometer(0, in.accelerometer[0], in.accelerometer[1], in.accelerometer[2]);
    clpp.addAltitude(0, in.altitude);
    clpp.addAnalogInput(0, in.analogInput);
    clpp.addAnalogOutput(0, in.analogOutput);
    clpp.addBarometricPressure(1, in.barometricPressure);
    clpp.addColour(1, in.colour[0], in.colour[1], in.colour[2]);
    clpp.addConcentration(1, in.concentration);
    clpp.addCurrent(1, in.current);

    std::map<uint8_t, CayenneLPPMessage> out;
    clpp.decode(clpp.getBuffer(), clpp.getSize(), out);
    REQUIRE(out.size() == 2);
    REQUIRE(in.accelerometer == out[0].accelerometer);
    REQUIRE(in.altitude == out[0].altitude);
    REQUIRE(in.analogInput == out[0].analogInput);
    REQUIRE(in.analogOutput == out[0].analogOutput);
    REQUIRE(in.barometricPressure == out[1].barometricPressure);
    REQUIRE(in.colour[0] == out[1].colour[0]);
    REQUIRE(in.colour[1] == out[1].colour[1]);
    REQUIRE(in.colour[2] == out[1].colour[2]);
    REQUIRE(in.concentration == out[1].concentration);
    REQUIRE(in.current == out[1].current);
}

TEST_CASE("CayenneLPPMessage parameters D-O are decoded", "[LppMessage]") {
    CayenneLPPMessage in;
    in.digitalInput = 13;
    in.digitalOutput = 14;
    in.direction = 15.0;
    in.distance = 16.0;
    in.energy = 17.0;
    in.frequency = 18;
    in.genericSensor = 19.0;
    in.gps = { 20.0, 21.0, 22.0 };
    in.gyrometer = { 23.0, 24.0, 25.0 };
    in.luminosity = 26;
    in.onOffSwitch = 27;

    CayenneLPP clpp(255);
    clpp.addDigitalInput(2, in.digitalInput);
    clpp.addDigitalOutput(2, in.digitalOutput);
    clpp.addDirection(2, in.direction);
    clpp.addDistance(2, in.distance);
    clpp.addEnergy(3, in.energy);
    clpp.addFrequency(4, in.frequency);
    clpp.addGenericSensor(5, in.genericSensor);
    clpp.addGPS(5, in.gps.at(0), in.gps.at(1), in.gps.at(2));
    clpp.addGyrometer(5, in.gyrometer.at(0), in.gyrometer.at(1), in.gyrometer.at(2));
    clpp.addLuminosity(6, in.luminosity);
    clpp.addSwitch(7, in.onOffSwitch);

    std::map<uint8_t, CayenneLPPMessage> out;
    clpp.decode(clpp.getBuffer(), clpp.getSize(), out);
    REQUIRE(out.size() == 6);
    REQUIRE(in.digitalInput == out[2].digitalInput);
    REQUIRE(in.digitalOutput == out[2].digitalOutput);
    REQUIRE(in.direction == out[2].direction);
    REQUIRE(in.distance == out[2].distance);
    REQUIRE(in.energy == out[3].energy);
    REQUIRE(in.frequency == out[4].frequency);
    REQUIRE(in.genericSensor == out[5].genericSensor);
    REQUIRE(in.gps == out[5].gps);
    REQUIRE(in.gyrometer == out[5].gyrometer);
    REQUIRE(in.luminosity == out[6].luminosity);
    REQUIRE(in.onOffSwitch == out[7].onOffSwitch);
}

TEST_CASE("CayenneLPPMessage parameters P-V are decoded", "[LppMessage]") {
    CayenneLPPMessage in;
    in.percentage = 28;
    in.power = 29;
    in.presence = 30;
    in.relativeHumidity = 31.0;
    in.temperature = 32.0;
    in.unixTime = 33;
    in.voltage = 34.0;

    CayenneLPP clpp(255);
    clpp.addPercentage(8, in.percentage);
    clpp.addPower(8, in.power);
    clpp.addPresence(8, in.presence);
    clpp.addRelativeHumidity(9, in.relativeHumidity);
    clpp.addTemperature(10, in.temperature);
    clpp.addUnixTime(11, in.unixTime);
    clpp.addVoltage(12, in.voltage);

    std::map<uint8_t, CayenneLPPMessage> out;
    clpp.decode(clpp.getBuffer(), clpp.getSize(), out);
    REQUIRE(out.size() == 5);
    REQUIRE(in.percentage == out[8].percentage);
    REQUIRE(in.power == out[8].power);
    REQUIRE(in.presence == out[8].presence);
    REQUIRE(in.relativeHumidity == out[9].relativeHumidity);
    REQUIRE(in.temperature == out[10].temperature);
    REQUIRE(in.unixTime == out[11].unixTime);
    REQUIRE(in.voltage == out[12].voltage);
}
