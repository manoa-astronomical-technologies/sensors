/* 
 * Description: MAT Code for Hall Effect
 * File Name: MAT_Hall-Effect
 * Author: gwann
 * Date: 02.27.2019
 */

#include <SPI.h>
#include <SD.h>

#define nofield   833       // Analog output with no applied field, calibrate this
#define voltage   5          // Voltage: 5V
#define adc       4096       // ADC bits (2E10 = 1024, 2E12 = 4096)
double sensitivity = 0.006; // Sensitivity 1.19mV

void setup() {
  Serial.begin(9600);
  pinMode(12,OUTPUT);
}

void Calc(){
// measure magnetic field
  int raw = analogRead(0);   // 10 Bit ADC will give 2E10 - 1024 Bits 

//  Uncomment this to get a raw reading for calibration of no-field point
  Serial.print("Raw reading: ");
  Serial.println(raw);

  // This prints out magnetic field in terms of Gauss (Units: G or GS) 
  //10 is the percision it will display
  double GAUSS = (voltage/sensitivity)/(adc);
//  Serial.print("GAUSS: ");
//  Serial.println(GAUSS,10);
  
  // This prints out magnetic field in terms of Gauss (Units: microT or uT) 
  //10 is the percision it will display
  double microT = GAUSS * pow(10,-4);
//  Serial.print("microTesla: ");
//  Serial.println(microT,10);

  //This calibrates the sensor using the raw reading with no magnetic field
  double calibrated = raw - nofield;             // This should ouput zero. 
  double GAUSS_cal = calibrated * GAUSS;   // adjust scale to mG / mGS
  double microT_cal = calibrated * microT;   // adjust scale to uT
  
  Serial.println(" Calibrated---------------- ");
  Serial.print(GAUSS_cal,10); Serial.println(" Gauss ");
  Serial.print(microT_cal,10); Serial.println(" microTesla ");

//  String dataString;
//  dataString += gauss;
//  dataString += " Gauss ";
  
  if (GAUSS_cal > 0) digitalWrite(12, HIGH);
  else if(GAUSS_cal < 0) digitalWrite(12, LOW);
  else digitalWrite(12, LOW); 

}

void loop(){
  
    delay(500);
    Calc();
    
  }

