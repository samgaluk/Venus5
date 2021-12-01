// AER E 361 Venus 5 Skeleton Balloon Altitude Control System Demonstration Code

/* IMPORT LIBRARIES */
#include <stdio.h>
#include <math.h>
#include <Arduino.h>
#include "Adafruit_CircuitPlayground.h"
// include library or libraries required for pressure sensor here

/* SETUP PROGRAM */
void setup() {
  Serial.println("FLIGHT CONTROL SYSTEM STARTUP");
  Serial.begin(115200);
  CircuitPlayground.begin();
  // insert startup conditions required for BME680 sensor here

  /* this segment of code will initialize the required constants, as well as the target altitude */
  Serial.println("Configuration Status: Standby");
  float g = 9.807; // gravitational acceleration in m/s2
  float M = 0.02896; // molar mass of Earth's air in kg/mol
  float R = 8.3143; // universal gas constant in (N*m)/(mol*K)
  float C = -(R/(M*g)); // combined above constants into a constant C for ease of calculations
  float alt; // initialize altitude variable in m
  float T; // initialize temperature variable in K
  float P; // initialize pressure variable in hPa
  float alt0 = 0; // initializing starting altitude at zero
  float alt_tgt = 3; // set above ground level (AGL) altitude target in meters
  Serial.println("Altitude Target Loaded");
  Serial.println("Configuration Status: Initialized");

  /* this segment of code will take the pressure and temperature conditions at ground level from the BME680 sensor */
  Serial.println("DAQ Staus: Standby");
  delay(10000); // delay set in order to give time to the operator to place the CPX on the ground and let the values settle
  float P0 = BME.pressure() // get pressure from BME sensor at ground level
  float T0 = BME.temp() // get temperature from BME sensor at ground level
  Serial.println("DAQ Status: Initialized");

  Serial.println("FLIGHT SEQUENCE START");
}

/* START MISSION PROFILE */
void loop() {
  // first instance of altitude measured at ground level
  alt = C*BME680.temp()*log(BME680.pressure()/P0);

  // while loop runs until altitude target is reached
  while (alt-alt0 < alt_tgt){
    T = BME680.temp(); // temperature is acquired from the BME sensor
    P = BME680.pressure(); // pressure is acquired from the BME sensor
    alt = C*T*log(P/P0); // altitude is calculated
    Serial.print("Altitude: "); // print current altitude, if using serial connection
    Serial.print(alt);
    delay(500);
  }
  // if altitude target is reached, print serial decleration and set LEDs to RED
  Serial.print("ALTITUDE TARGET REACHED");
  cp.pixels.fill((50, 0, 0));

  // while loop runs until CPX descends back below altitude target
  while(alt-alt0 >= alt_tgt){
    T = BME680.temp(); // temperature is acquired from the BME sensor
    P = BME680.pressure(); // pressure is acquired from the BME sensor
    alt = C*T*log(P/P0); // altitude is calculated
    Serial.print("Altitude: "); // print current altitude, if using serial connection
    Serial.print(alt);
    delay(500);
  }
  // if CPX descends below altitude target, print serial decleration and turn LEDs off
  Serial.print("DESCENT SEQUENCE START")
  cp.pixels.fill((0, 0, 0))
  
}
