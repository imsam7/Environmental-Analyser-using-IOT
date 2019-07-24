#include "dht.h"  

int pinSoil2 = A0;
int pinSoil3 = A1;
int pinSoil = A2;
int pinMethane = A3;
int pinLDR = A4;
int pinDHT = A5; 
int motorPin = 6;
int motorPin2 = 8;
int motorPin3 = 10; 
unsigned long time;

dht DHT;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(13, OUTPUT);
}
double Light (int RawADC0)
{
  double Vout=RawADC0*0.0048828125;
  int lux=(25000/Vout-500)/10;
  return lux;
}

void loop() {
  
  DHT.read11(pinDHT);
  Serial.print("Temperature: ");
  Serial.print(DHT.temperature);
  Serial.println("C");  //print the temperature status
  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  Serial.println("%");  //print the humidity status

  int moisture = analogRead(pinSoil);
  moisture = map(moisture,1010,330,0,100);
  if(moisture>100)
  moisture=100;
  if(moisture<0)
  moisture=0;
  Serial.print("Soil moisture 1: ");
  Serial.print(moisture);
  Serial.println("%");  //print the soil moisture status

  int moisture2 = analogRead(pinSoil2);
  moisture2 = map(moisture2,1014,369,0,100);
  if(moisture2>100)
  moisture2=100;
  if(moisture2<0)
  moisture2=0;
  Serial.print("Soil moisture 2: ");
  Serial.print(moisture2);
  Serial.println("%");  //print the soil moisture status

  int moisture3 = analogRead(pinSoil3);
  moisture3 = map(moisture3,1014,334,0,100);
  if(moisture3>100)
  moisture3=100;
  if(moisture3<0)
  moisture3=0;
  Serial.print("Soil moisture 3: ");
  Serial.print(moisture3);
  Serial.println("%");  //print the soil moisture status

  int meth = analogRead(pinMethane)/2;
  Serial.print("Methane Level: ");
  Serial.print(meth);
  if(meth>400)
  Serial.println(" ->Irregular");
  else Serial.println(" ->Fine");
  
  Serial.print("Light Intensity:");
  Serial.print(int(Light(analogRead(pinLDR))));
  Serial.println(" Lux"); //print the light intensity
  Serial.println("");

  if(moisture<20)
      digitalWrite(motorPin, HIGH); // turn on motor1
  if(moisture>50)
       digitalWrite(motorPin, LOW); // turn of motor1
    
  if(moisture2<20)
      digitalWrite(motorPin2, HIGH); // turn on motor2
  if(moisture2>50)
      digitalWrite(motorPin2, LOW); // turn off motor2
  
  if(moisture3<20)
      digitalWrite(motorPin3, HIGH); // turn on motor3
  if(moisture3>50)
       digitalWrite(motorPin3, LOW); // turn off motor3
 
  delay(5000);
   
 // exit(0);  
}
