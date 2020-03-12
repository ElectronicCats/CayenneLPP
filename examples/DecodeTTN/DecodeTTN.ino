/*
  DecodeTTN.ino

  This code create a CayenneLPP package and decode to Json.

  created 22 October 2019
  by Luiz H. Cassettari
*/

#include <CayenneLPP.h>

void setup()
{
  DynamicJsonDocument jsonBuffer(1024);
  CayenneLPP lpp(160);

  JsonObject root = jsonBuffer.to<JsonObject>();

  Serial.begin(115200);
  Serial.println();

  lpp.reset();
  lpp.addDigitalInput(1, 0);
  lpp.addDigitalOutput(2, 1);
  lpp.addAnalogInput(3, 1.23f);
  lpp.addAnalogOutput(4, 3.45f);
  lpp.addLuminosity(5, 20304);
  lpp.addPresence(6, 1);
  lpp.addTemperature(7, 26.5f);
  lpp.addRelativeHumidity(8, 86.6f);
  lpp.addAccelerometer(9, 1.234f, -1.234f, 0.567f);
  lpp.addBarometricPressure(10, 1023.4f);
  lpp.addGyrometer(1, -12.34f, 45.56f, 89.01f);
  lpp.addGPS(1, -12.34f, 45.56f, 9.01f);

  lpp.addUnixTime(1, 135005160);
  
  lpp.addGenericSensor(1, 4294967295);
  lpp.addVoltage(1, 3.35);
  lpp.addCurrent(1, 0.321);
  lpp.addFrequency(1, 50);
  lpp.addPercentage(1, 100);
  lpp.addAltitude(1 , 50);
  lpp.addPower(1 , 50000);
  lpp.addDistance(1 , 10.555);
  lpp.addEnergy(1 , 19.055);
  lpp.addDirection(1 , 90);
  lpp.addSwitch(1 , 0);
  
  lpp.addPPM(1 , 512);
  lpp.addRGB(1 , 64, 128, 255);


  lpp.decodeTTN(lpp.getBuffer(), lpp.getSize(), root);
  
  serializeJsonPretty(root, Serial);
  Serial.println();

}

void loop()
{
}