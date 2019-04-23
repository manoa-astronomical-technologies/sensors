#define NOFIELD 505L    // Analog output with no applied field, calibrate this

// Uncomment one of the lines below according to device in use A1301 or A1302
// This is used to convert the analog voltage reading to milliGauss
#define TOMILLIGAUSS 1953L  // For A1301: 2.5mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 1953mG
// #define TOMILLIGAUSS 3756L  // For A1302: 1.3mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 3756mG

void setup() 
{
  Serial.begin(9600);
}

void DoMeasurement()
{
// measure magnetic field
  int raw01 = analogRead(A0);   // Range : 0..1024
  int raw02 = analogRead(A1); 
  int raw03 = analogRead(A2);
  int raw04 = analogRead(A3);
  int raw05 = analogRead(A4);
//  Uncomment this to get a raw reading for calibration of no-field point
//  Serial.print("Raw reading: ");
//  Serial.println(raw);

  long compensated01 = raw01 - NOFIELD;
  long compensated02 = raw02 - NOFIELD;// adjust relative to no applied field 
  long compensated03 = raw03 - NOFIELD;
  long compensated04 = raw04 - NOFIELD;
  long compensated05 = raw05 - NOFIELD;
   
  long gauss01 = compensated01 * TOMILLIGAUSS / 1000;   // adjust scale to Gauss
  long gauss02 = compensated02 * TOMILLIGAUSS / 1000; 
  long gauss03 = compensated03 * TOMILLIGAUSS / 1000;
  long gauss04 = compensated04 * TOMILLIGAUSS / 1000;
  long gauss05 = compensated05 * TOMILLIGAUSS / 1000;
  
  Serial.println(gauss01);
  Serial.println(" Gauss #1 ");
  Serial.println(gauss02);
  Serial.println(" Gauss #2 ");
  Serial.println(gauss03);
  Serial.println(" Gauss #3 ");
  Serial.println(gauss04);
  Serial.println(" Gauss #4 ");
  Serial.println(gauss05);
  Serial.println(" Gauss #5 ");

  //if (gauss01 > 0)     Serial.println("(South pole)");
  //else if(gauss01 < 0) Serial.println("(North pole)");
  //else               Serial.println();


if (gauss01 > 100) {
  Serial.println("Position 1");
} else if (gauss02 > 100) {
  Serial.println("Position 2");
} else if (gauss03 > 100) {
  Serial.println("Position 3");
} else if (gauss04 > 100) {
  Serial.println("Position 4");
} else if (gauss05 > 100) {
  Serial.println("Position 5");
}

}
void loop() {
    DoMeasurement();
    delay(1000);
}
