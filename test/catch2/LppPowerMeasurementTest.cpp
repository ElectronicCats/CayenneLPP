/*
 * CayenneLPP - Catch2 Unit Tests
 *
 * Copyright (C) 2021 by Manuel Weichselbaumer <mincequi@web.de>
 *
 * Use of this source code is governed by the MIT license that can be found in the LICENSE file.
 *
 */

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <CayenneLPP.h>
#include <CayenneLPPMessage.h>
#include <CayenneLPPPowerMeasurement.h>

using namespace Catch;

TEST_CASE("Encode and decode without optionals", "[LppPowerMeasurement]") {
    CayenneLPPPowerMeasurement pm;
    pm.addCurrentPower(-3.0);
    auto buffer = pm.encode();
    REQUIRE(buffer.size() == 3);
    auto out = CayenneLPPPowerMeasurement::fromRawPointer(buffer.data());
    REQUIRE(out.currentPower() == -3.0);
    REQUIRE(out.exportEnergy() == std::nullopt);
    REQUIRE(out.importEnergy() == std::nullopt);
    REQUIRE(out.maxMeasuredPower() == std::nullopt);
    REQUIRE(out.maxRangePower() == std::nullopt);
    REQUIRE(out.minMeasuredPower() == std::nullopt);
    REQUIRE(out.minRangePower() == std::nullopt);
}

TEST_CASE("Encode and decode with optional", "[LppPowerMeasurement]") {
    CayenneLPPPowerMeasurement pm;
    pm.addCurrentPower(1.0);
    pm.addExportEnergy(-3.0);
    auto buffer = pm.encode();
    REQUIRE(buffer.size() == 5);

    auto out = CayenneLPPPowerMeasurement::fromRawPointer(buffer.data());
    REQUIRE(out.currentPower() == 1.0);
    REQUIRE(*out.exportEnergy() == -3.0);
}

TEST_CASE("Encode and decode with optionals", "[LppPowerMeasurement]") {
    CayenneLPPPowerMeasurement pm;
    pm.addCurrentPower(1.0);
    pm.addExportEnergy(2.0);
    pm.addImportEnergy(-3.0);
    pm.addMaxMeasuredPower(4.0);
    pm.addMaxRangePower(-5.0);
    pm.addMinMeasuredPower(6.0);
    pm.addMinRangePower(7.0);
    auto buffer = pm.encode();
    REQUIRE(buffer.size() == 15);

    auto out = CayenneLPPPowerMeasurement::fromRawPointer(buffer.data());
    REQUIRE(out.currentPower() == 1.0);
    REQUIRE(*out.exportEnergy() == 2.0);
    REQUIRE(*out.importEnergy() == -3.0);
    REQUIRE(*out.maxMeasuredPower() == 4.0);
    REQUIRE(*out.maxRangePower() == -5.0);
    REQUIRE(*out.minMeasuredPower() == 6.0);
    REQUIRE(*out.minRangePower() == 7.0);
}

TEST_CASE("Encode and decode special numbers", "[LppPowerMeasurement]") {
    CayenneLPPPowerMeasurement pm;
    pm.addCurrentPower(-2045.0);
    pm.addExportEnergy(-2046.0);
    pm.addImportEnergy(2047.0);
    pm.addMaxMeasuredPower(2048.0);
    pm.addMaxRangePower(-2054.0);
    pm.addMinMeasuredPower(2055.0);
    auto buffer = pm.encode();
    auto out = CayenneLPPPowerMeasurement::fromRawPointer(buffer.data());
    REQUIRE(out.currentPower() == -2045.0);
    REQUIRE(out.exportEnergy() == -2050.0);
    REQUIRE(out.importEnergy() == 2050.0);
    REQUIRE(out.maxMeasuredPower() == 2050.0);
    REQUIRE(out.maxRangePower() == -2050.0);
    REQUIRE(out.minMeasuredPower() == 2060.0);
}

TEST_CASE("Encode and decode small numbers", "[LppPowerMeasurement]") {
    CayenneLPPPowerMeasurement pm;
    pm.addCurrentPower(-0.2);
    pm.addExportEnergy(-0.00001);
    pm.addImportEnergy(0.00005);
    pm.addMaxMeasuredPower(0.9);
    pm.addMaxRangePower(-0.1234);
    pm.addMinMeasuredPower(0.0002045);
    auto buffer = pm.encode();
    auto out = CayenneLPPPowerMeasurement::fromRawPointer(buffer.data());
    REQUIRE(out.currentPower() == -0.2);
    REQUIRE(out.exportEnergy() == -0.00001);
    REQUIRE(out.importEnergy() == Approx(0.00005));
    REQUIRE(out.maxMeasuredPower() == 0.9);
    REQUIRE(out.maxRangePower() == Approx(-0.1234));
    REQUIRE(out.minMeasuredPower() == Approx(0.0002045));
}

TEST_CASE("PowerMeasurement fits in buffer", "[LppPowerMeasurement]") {
    CayenneLPP lpp(10);
    CayenneLPPPowerMeasurement powMea;
    powMea.addCurrentPower(1.0);
    REQUIRE(lpp.addColour(1, 2, 3, 4) == 5);
    REQUIRE(lpp.addPowerMeasurement(2, powMea) == 10);
    REQUIRE(lpp.getError() == LPP_ERROR_OK);
}

TEST_CASE("PowerMeasurement exceeds buffer", "[LppPowerMeasurement]") {
    CayenneLPP lpp(10);
    CayenneLPPPowerMeasurement powMea;
    powMea.addExportEnergy(1.0);
    REQUIRE(lpp.addColour(1, 2, 3, 4) == 5);
    REQUIRE(lpp.addPowerMeasurement(2, powMea) == 0);
    REQUIRE(lpp.getError() == LPP_ERROR_OVERFLOW);
}

TEST_CASE("Decode PowerMeasurement from message", "[LppPowerMeasurement]") {
    CayenneLPP lpp(18);
    CayenneLPPPowerMeasurement powMea;
    REQUIRE(lpp.addColour(1, 2, 3, 4) == 5);
    powMea.addCurrentPower(1.0);
    powMea.addExportEnergy(-2.0);
    powMea.addImportEnergy(-100.0);
    REQUIRE(lpp.addPowerMeasurement(2, powMea) == 14);
    REQUIRE(lpp.addAltitude(3, -5.0) == 18);

    const std::vector<uint8_t> buffer(lpp.getBuffer(), lpp.getBuffer()+lpp.getSize());
    std::map<uint8_t, CayenneLPPMessage> messages;
    REQUIRE(lpp.decode(lpp.getBuffer(), lpp.getSize(), messages) == 3);
    REQUIRE(messages.at(2).powerMeasurement == powMea);
    REQUIRE(messages.at(2).getValue<CayenneLPPPowerMeasurement>(LPP_POWER_MEASUREMENT) == powMea);
}
