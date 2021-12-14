#include "DHT.h"

#define LOW_T 20
#define HIGH_T 30
#define LOW_H 40
#define HIGH_H 55
#define LOW_L 2100
#define HIGH_L 16865

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin(); //Initialise the DHT sensor
  pinMode(3,OUTPUT); //Initialise the LED1
  pinMode(5,OUTPUT); //Initialise the LED2
  pinMode(11,OUTPUT); //Initialise the LED3
}
void loop()
{ 
    getSensor();              
    temperature_judge();
    humidity_judge();  
    light_judge();      
}

void getSensor(){
  
  float tempValue = dht.readTemperature(); 
  int humidityValue = dht.readHumidity(); 
}

//judge the temperature range and open/off LED indicator
void temperature_judge(){
  if( dht.readTemperature() > HIGH_T or dht.readTemperature() < LOW_T){
    Serial.print("Temperature is too hight/low"); 
    Serial.println(dht.readTemperature()); 
     digitalWrite(3, HIGH);
     delay(5000);
  }else{
    Serial.print("Temperature is suitable"); 
    Serial.println(dht.readTemperature());
    digitalWrite(3, LOW);
    delay(5000);
  }
}

//judge humidity range and open/off LED indicator
void humidity_judge(){
  if( dht.readHumidity() > HIGH_H or dht.readHumidity() < LOW_H){
    Serial.print("Humidity is too hight/low"); 
    Serial.println(dht.readHumidity());
    digitalWrite(5, HIGH);
    delay(5000);
  }else{
    Serial.print("Humidity is suitable"); 
    Serial.println(dht.readHumidity());
    digitalWrite(5, LOW);
    delay(5000);
  }
}

//judge environment light range and open/off LED indicator
void light_judge(){
  if( analogRead(A0) > HIGH_L or analogRead(A0) < LOW_L){
    Serial.print("Environment light is too hight/low:"); 
    Serial.println(analogRead(A0));
    digitalWrite(11, HIGH);
    delay(5000);
  }else{
    Serial.print("Environment light is suitable:"); 
    Serial.println(analogRead(A0));
    digitalWrite(11, LOW);
    delay(5000);
  }
}
