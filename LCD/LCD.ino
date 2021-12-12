/*
 Qian Jin
 27 Nov 2021
 */
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
#include "DHT.h"
        
int pump_sta = 0;  

LiquidCrystal_I2C lcd(0x27,16,2); 

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int wetPin = A2;     
long int wetValue = 0; 
  

void setup(){
    Serial.begin(9600);  
    lcd.init();                      // initialize the lcd
    lcd.backlight();
    //Initialise the DHT sensor
    dht.begin();
}

void loop(){
    getSensor();                  
    update_lcd1602();  
    delay(1000);
}


void getSensor(){
    
  //dht.getTHValue(DHT11_PIN);

  Serial.print("Temperature: ");  
  Serial.println(dht.readTemperature()); 
  Serial.print("Humidity: ");
  Serial.println(dht.readHumidity());  
  Serial.print("Soil moisture: ");
  Serial.println(wetValue); 
  Serial.println(); 
}

void update_lcd1602(){
    lcd.setCursor(0,0); 
    lcd.print("Mois");    
    lcd.print(wetValue);   
    lcd.print(" ");
    lcd.print("Pump");
    if(wetValue<30){ 
      lcd.print("ON");
    }else{
      lcd.print("OFF");
    }
    
    lcd.setCursor(0,1);
    lcd.print("Temp"); 
    float temp = dht.readTemperature();  
    if(temp <= 99){
      lcd.print(temp);
    }else{lcd.print(99,0);}

    lcd.print(" ");
    lcd.print("Hum"); 
    int humidity = dht.readHumidity();
    if(humidity <= 99){
      lcd.print(humidity); 
    }else{
      lcd.print(99,0); 
    }
}
