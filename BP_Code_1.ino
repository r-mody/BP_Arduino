#include <Wire.h>

void setup() {
 //I2C setup
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
  //Pnematic setup
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);

  //general delay
  delay(1000);
}


void loop() {
//Pump and solonoid controls
//  digitalWrite(6, HIGH); 
//  delay (10);
//  digitalWrite(7,HIGH);
//  delay (5000);
//  digitalWrite(7,LOW);
//  delay (10);
//  digitalWrite(6,LOW);
//  delay (5000);
 
//Reading pressure sensor  
  Wire.requestFrom(24, 4);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    float c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }

  delay(1000);
}
