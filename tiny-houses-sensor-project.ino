#include <Wire.h>
#include "Adafruit_MCP9808.h"

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define ONE_WIRE_BUS2 3
#define ONE_WIRE_BUS3 4
#define ONE_WIRE_BUS4 5

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor1 = Adafruit_MCP9808();
Adafruit_MCP9808 tempsensor2 = Adafruit_MCP9808();

OneWire oneWire(ONE_WIRE_BUS);
OneWire oneWire2(ONE_WIRE_BUS2);
OneWire oneWire3(ONE_WIRE_BUS3);
OneWire oneWire4(ONE_WIRE_BUS4);

DallasTemperature wptempsensor1(&oneWire);
DallasTemperature wptempsensor2(&oneWire2);
DallasTemperature wptempsensor3(&oneWire3);
DallasTemperature wptempsensor4(&oneWire4);

void setup() {
  Serial.begin(9600);
  Serial.println("MCP9808 demo");
  
  // Make sure the sensor is found, you can also pass in a different i2c
  // address with tempsensor.begin(0x19) for example
  if (!tempsensor1.begin(0x18)) {
    Serial.println("Couldn't find MCP9808 number 1!");
    while (1);
  }
  if (!tempsensor2.begin(0x19)) {
    Serial.println("Couldn't find MCP9808 number 2!");
    while (1);
  }
  
  wptempsensor1.begin();
  wptempsensor2.begin();
  wptempsensor3.begin();
  wptempsensor4.begin();
}

void loop() {
  // Read and print out the temperature, then convert to *F
  float c = tempsensor1.readTempC();
//  float f = c * 9.0 / 5.0 + 32;
  Serial.print("Temp 1: "); Serial.print(c); Serial.println("*C\t"); 
//  Serial.print(f); Serial.println("*F");
  
  c = tempsensor2.readTempC();
//  f = c * 9.0 / 5.0 + 32;
  Serial.print("Temp 2: "); Serial.print(c); Serial.println("*C\t"); 
//  Serial.print(f); Serial.println("*F");
  
  wptempsensor1.requestTemperatures();
  Serial.print("Waterproof Temp 1: ");
  Serial.print(wptempsensor1.getTempCByIndex(0));
  Serial.println("*C");
  
  wptempsensor2.requestTemperatures();
  Serial.print("Waterproof Temp 2: ");
  Serial.print(wptempsensor2.getTempCByIndex(0));
  Serial.println("*C");
  
  wptempsensor3.requestTemperatures();
  Serial.print("Waterproof Temp 3: ");
  Serial.print(wptempsensor3.getTempCByIndex(0));
  Serial.println("*C");
  
  wptempsensor4.requestTemperatures();
  Serial.print("Waterproof Temp 4: ");
  Serial.print(wptempsensor4.getTempCByIndex(0));
  Serial.println("*C");
  
  
  delay(250);
  
  Serial.println("Shutdown MCP9808.... ");
  tempsensor1.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere
  tempsensor2.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere
  
  delay(2000);
  
  Serial.println("wake up MCP9808.... "); // wake up MSP9808 - power consumption ~200 mikro Ampere
  tempsensor1.shutdown_wake(0);
  tempsensor2.shutdown_wake(0);
  
   
}
