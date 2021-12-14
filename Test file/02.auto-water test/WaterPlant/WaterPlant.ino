/*
 Qian Jin
 Wed 1 Dec 2021
*/
#include <Wire.h> 
#include <DHT.h>
        
#define MOTOR_INA1  8
#define MOTOR_INA2  9
#define LOW_TH 30
#define HIGH_TH 60


#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
int wetPin = A2;     
long int wetValue = 0;   
int pump_sta = 0;

void setup(){
    Serial.begin(9600);  
    dht.begin();
    pumpInit();
}

void loop(){
    getSensor();              
    pump_judge();      
    delay(6000);
}

void pump_judge(){
  if( wetValue > HIGH_TH ){
    closePump();
  }else if( wetValue < LOW_TH ){
    openPump();
  }
}

void getSensor(){
  wetValue = analogRead(wetPin);
  wetValue *= 100;
  wetValue = wetValue/1023;
    
  //dht.getTHValue(DHT11_PIN);

  Serial.print("Temperature: ");  
  Serial.println(dht.readTemperature()); 
  Serial.print("Humidity: ");
  Serial.println(dht.readHumidity());  
  Serial.print("Soil moisture: ");
  Serial.println(wetValue); 
  Serial.println(); 
}

void pumpInit(){
  pinMode( MOTOR_INA1,OUTPUT );
  pinMode( MOTOR_INA2,OUTPUT );
  analogWrite( MOTOR_INA1, 0 );
  analogWrite( MOTOR_INA2 , 0 );
}

void openPump(){
  pump_sta = 1;
  analogWrite(MOTOR_INA1, 150);
  analogWrite(MOTOR_INA2 , 0);
}

void closePump(){
  pump_sta = 0;
  analogWrite(MOTOR_INA1, 0);
  analogWrite(MOTOR_INA2 , 0);
}
