#include <Wire.h>

//Array to be sent to pressure sensor
int Cmd[3]={0xAA, 0x00, 0x00};

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
  Wire.beginTransmission(0x18); 
                              
  Wire.write(Cmd[0]);
  Wire.write(Cmd[1]);
  Wire.write(Cmd[2]);               
  Wire.endTransmission();

  delay (10);
  
  Wire.requestFrom(0x18, 4);    // request 4 bytes from slave device 0x18

  while (Wire.available()) { // slave may send less than requested
    uint8_t c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  Serial.println();
  delay(1000);
}
