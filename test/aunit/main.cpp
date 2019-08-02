/*

CayenneLPP

AUnit Unit Tests

Copyright (C) 2019 by Xose Pérez <xose dot perez at gmail dot com>

The rpnlib library is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The rpnlib library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the rpnlib library.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <Arduino.h>
#include <CayenneLPP.h>
#include <AUnit.h>

using namespace aunit;

// -----------------------------------------------------------------------------
// Test class
// -----------------------------------------------------------------------------

class CustomTest: public TestOnce {

    protected:

        virtual void setup() override {
            lpp = new CayenneLPP(100);
            lpp->reset();
        }

        virtual void teardown() override {
            delete lpp;
        }

        virtual void compare(unsigned char depth, uint8_t * expected) {
            
            uint8_t * actual = lpp->getBuffer();
            
            PC_SERIAL.println();

            char buff[6];
            PC_SERIAL.print("Expected: ");
            for (unsigned char i=0; i<depth; i++) {
                snprintf(buff, sizeof(buff), "%02X ", expected[i]);
                PC_SERIAL.print(buff);
            }
            PC_SERIAL.println();
            PC_SERIAL.print("Actual  : ");
            for (unsigned char i=0; i<lpp->getSize(); i++) {
                snprintf(buff, sizeof(buff), "%02X ", actual[i]);
                PC_SERIAL.print(buff);
            }
            PC_SERIAL.println();
            
            assertEqual(depth, lpp->getSize());
            for (unsigned char i=0; i<depth; i++) {
                assertEqual(expected[i], actual[i]);
            }

        }

    CayenneLPP * lpp;

};

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

testF(CustomTest, test_temperature_two_channels) {
    lpp->addTemperature(3, 27.2);
    lpp->addTemperature(5, 25.5);
    uint8_t expected[] = {0x03,0x67,0x01,0x10,0x05,0x67,0x00,0xFF};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_temperature_reset) {
    lpp->addTemperature(3, 27.2);
    lpp->reset();
    lpp->addTemperature(5, 25.5);
    uint8_t expected[] = {0x05,0x67,0x00,0xFF};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_temperature_negative) {
    lpp->addTemperature(5, -4.7);
    uint8_t expected[] = {0x05,0x67,0xFF,0xD1};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_humidity) {
    lpp->addRelativeHumidity(2, 54);
    uint8_t expected[] = {0x02,0x68,0x6C};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_generic_sensor) {
    lpp->addGenericSensor(1, 998);
    uint8_t expected[] = {0x01,0x64,0x00,0x00,0x03,0xE6};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_accelerometer) {
    lpp->addAccelerometer(6, 1.234, -1.234, 0);
    uint8_t expected[] = {0x06,0x71,0x04,0xD2,0xFB,0x2E,0x00,0x00};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_voltage) {
    lpp->addVoltage(3, 224.56);
    uint8_t expected[] = {0x03,0x74,0x57,0xB8};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_current) {
    lpp->addCurrent(1, 0.237);
    uint8_t expected[] = {0x01,0x75,0x00,0xED};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_frequency) {
    lpp->addFrequency(1, 868100000);
    uint8_t expected[] = {0x01,0x76,0x33,0xBe,0x27,0xA0};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_altitude) {
    lpp->addAltitude(5, -17);
    uint8_t expected[] = {0x05,0x79,0xFF,0XEF};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_power) {
    lpp->addPower(5, 3450);
    uint8_t expected[] = {0x05,0x80,0x0D,0x7A};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_power_limit) {
    lpp->addPower(1, 0xFFFF);
    uint8_t expected[] = {0x01,0x80,0xFF,0xFF};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_distance) {
    lpp->addDistance(1, 0.034);
    uint8_t expected[] = {0x01,0x82,0x00,0x00,0x00,0x22};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_energy) {
    lpp->addEnergy(1, 7953.2);
    uint8_t expected[] = {0x01,0x83,0x00,0x79,0x5B,0x30};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_direction) {
    lpp->addDirection(1, 256);
    uint8_t expected[] = {0x01,0x84,0x01,0x00};
    compare(sizeof(expected), expected);
}

testF(CustomTest, test_gps) {
    lpp->addGPS(1, 42.3519, -87.9094, 10);
    uint8_t expected[] = {0x01,0x88,0x06,0x76,0x5e,0xf2,0x96,0x0a,0x00,0x03,0xe8};
    compare(sizeof(expected), expected);
}
 
testF(CustomTest, test_switch) {
    lpp->addSwitch(5, 1);
    uint8_t expected[] = {0x05,0x8E,0x01};
    compare(sizeof(expected), expected);
}

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------

void setup() {

    PC_SERIAL.begin(115200);
    while (!PC_SERIAL && millis() < 5000);

    Printer::setPrinter(&PC_SERIAL);
    //TestRunner::setVerbosity(Verbosity::kAll);

}

void loop() {
    TestRunner::run();
    delay(1);
}
