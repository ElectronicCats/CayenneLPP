/**
 * Example of ABP device
 * Authors: 
 *        Ivan Moreno
 *        Eduardo Contreras
 *  June 2019
 * 
 * This code is beerware; if you see me (or any other collaborator 
 * member) at the local, and you've found our code helpful, 
 * please buy us a round!
 * Distributed as-is; no warranty is given.
 */
#include <lorawan.h>
#include<CayenneLPP.h>

CayenneLPP lpp(51);

//ABP Credentials 
const char *devAddr = "00000000";
const char *nwkSKey = "00000000000000000000000000000000";
const char *appSKey = "00000000000000000000000000000000";

const unsigned long interval = 10000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent
unsigned int counter = 0;     // message counter

char myStr[50];
char outStr[255];
byte recvStatus = 0;

const sRFM_pins RFM_pins = {
  .CS = 20,
  .RST = 9,
  .DIO0 = 0,
  .DIO1 = 1,
  .DIO2 = 2,
  .DIO5 = 15,
};

void setup() {
  // Setup loraid access
  Serial.begin(115200);
  delay(2000);
  if(!lora.init()){
    Serial.println("RFM95 not detected");
    delay(5000);
    return;
  }

  // Set LoRaWAN Class change CLASS_A or CLASS_C
  lora.setDeviceClass(CLASS_A);

  // Set Data Rate
  lora.setDataRate(SF8BW125);

  // set channel to random
  lora.setChannel(MULTI);
  
  // Put ABP Key and DevAddress here
  lora.setNwkSKey(nwkSKey);
  lora.setAppSKey(appSKey);
  lora.setDevAddr(devAddr);
}

void loop() {
  // Check interval overflow
  if(millis() - previousMillis > interval) {
    previousMillis = millis(); 

    printVariables();

    Serial.print("Sending: ");
    lora.sendUplink((char *)lpp.getBuffer(), lpp.getSize(), 0, 1);
  }

  recvStatus = lora.readData(outStr);
  if(recvStatus) {
    Serial.println(outStr);
  }
  
  // Check Lora RX
  lora.update();
}

void printVariables()
{
  lpp.reset();

  int humidity = random(0,300);
  Serial.print(F(",humidity="));
  Serial.print(humidity, 1);
  lpp.addRelativeHumidity(3, humidity);

  int temp = random(0,200);
  Serial.print(F(",tempf="));
  Serial.print(temp, 1);
  lpp.addTemperature(4, temp);

  int pressure = random(0,2000);
  Serial.print(F(",pressure="));
  Serial.print((pressure/100.0), 2);
  lpp.addBarometricPressure(7,(pressure/100.0));

  int batt_lvl = random(0,3.3);
  Serial.print(F(",batt_lvl="));
  Serial.print(batt_lvl, 2);
  lpp.addAnalogInput(8, batt_lvl);
}