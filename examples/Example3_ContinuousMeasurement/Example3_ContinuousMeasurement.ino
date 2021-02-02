/*
  Library for the Sensirion SDP3x Differential Pressure Sensor
  By: Paul Clark
  SparkFun Electronics
  Date: January 18th, 2021
  License: please see LICENSE.md for details

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/nnnnn
*/

#include "SparkFun_SDP3x_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SDP3x
#include <Wire.h>

SDP3X mySensor; //create an object of the SDP3X class

void setup()
{
  Serial.begin(115200);
  Serial.println(F("SDP3X Example"));

  Wire.begin();

  //mySensor.enableDebugging(); // Uncomment this line to print useful debug messages to Serial

  //Initialize sensor
  if (mySensor.begin() == false)
  {
    Serial.println(F("SDP3X not detected. Check connections. Freezing..."));
    while (1)
      ; // Do nothing more
  }

  //The SDP3x is temperature compensated both for differential pressure and for mass flow compensated differential pressure. In
  //use cases where the SDP3x is used to measure mass flow it is advised to use mass flow temperature compensation. In this
  //case no absolute pressure compensation is required.

  // In this example, we are going to request continuous differential pressure measurements
  // with mass flow temperature compensation and with averaging
  mySensor.startContinuousMeasurement(true, true); //Request continuous measurements with mass flow temperature compensation and with averaging
}

void loop()
{
  delay(1000); //Wait 1 second

  float diffPressure; // Storage for the differential pressure
  float temperature; // Storage for the temperature

  // Read the averaged differential pressure and temperature from the sensor
  mySensor.readMeasurement(&diffPressure, &temperature); // Read the measurement

  Serial.print(F("Differential pressure is: "));
  Serial.print(diffPressure, 2);
  Serial.print(F(" (Pa)  Temperature is: "));
  Serial.print(temperature, 2);
  Serial.println(F(" (C)"));
}
