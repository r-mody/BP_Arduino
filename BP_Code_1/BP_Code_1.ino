#include <Wire.h>

//Array to be sent to pressure sensor
int Cmd[3]={0xAA, 0x00, 0x00};

//Global Varibles
int data[4]={0,0,0,0};
uint8_t data1=0;
int count = 0;
long int datasft1=0;
long int datasft2=0;
long int datasft3=0;
long int datacomb=0;
long int datacombfnl=0;
long int Pressure = 0;

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
  
  while (Wire.available()) { 
    //Serial.println(Wire.read());
    data1 = Wire.read();
    data[count]=data1;
    count=count+1;
    //delay(10);
  }
  //Serial.print("status=");         
  //Serial.println(data[0]);// First set of data is actually the status byte
  //Serial.println(data[1]);
  //Serial.println(data[2]);
  //Serial.println(data[3]);
  //Serial.println(data[4]);// Noise?
  //Serial.println(count);

  //Shifting data and OR-ing them
  datasft1 = data[1];
  datasft1 = datasft1<<16; 
  datasft2 = data[2];
  datasft2 = datasft2<<8;
  datasft3 = data[3];// Doesn't need to be shifted but replacing variable for consistancy

  datacomb = datasft1 | datasft2;
  datacombfnl = datacomb | datasft3;

  //Serial.println(datacombfnl);

  // Calculating the actual pressure based off data
  long int Output_Max = .225*pow(2,24);
  long int Output_Min = .025*pow(2,24);
  int P_Max = 300;
  int P_Min = 0;
  
  //Function from spec
  Pressure = (((datacombfnl-Output_Min)*(P_Max-P_Min))/(Output_Max-Output_Min))+P_Min;

  Serial.println(Pressure);
//  while (Pressure <-15){
//    
//    digitalWrite(6,HIGH);
//    digitalWrite(7,HIGH); 
//    delay(10); 
//  }
//  digitalWrite(7,LOW);
  

  delay(1000);
  count=0;
}
