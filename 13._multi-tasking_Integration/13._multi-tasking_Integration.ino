#include <Wire.h> 
#include <DHT.h>
#include <FastLED_NeoPixel.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include "home_secrets.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,16,2);  

        
// DigitalPin
#define MOTOR_INA1  8  //Pump motor Pin1
#define MOTOR_INA2  9  //Pump motor Pin2

#define DHTPIN 4   //DHT22 Pin
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


#define LIGHT 2
#define NUM_LEDS 8 
#define BRIGHTNESS 15
FastLED_NeoPixel<NUM_LEDS, LIGHT, NEO_GRB> strip; 
CRGB leds[NUM_LEDS];

int FAN = 6;

// AnalogPin

int lightPin = A0;
long int lightValue;

#define AIR A1     
#define AIR_LED_B_PIN -1
#define AIR_LED_R_PIN -1

int wetPin = A2;     
long int wetValue; 
int pump_sta = 0;

float temp;
int hum;

// -------------------------------MQTT SETTING----------------------------------//
//please enter your sensitive data in the Secret home_secrets.h
const char* ssid     = SECRET_SSID;
const char* pass = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char* broker = "mqtt.cetools.org";
int        port     = 1884;
const char topic1[]  = "student/CASAoo16/Qian(Ashley)/Environment data/temperature";
const char topic2[]  = "student/CASAoo16/Qian(Ashley)/Environment data/humidity";
const char topic3[]  = "student/CASAoo16/Qian(Ashley)/Environment data/illumination";
const char topic4[]  = "student/CASAoo16/Qian(Ashley)/Environment data/soil moisture";
const char topic5[]  = "student/CASAoo16/Qian(Ashley)/Judge/Temperature";
const char topic6[]  = "student/CASAoo16/Qian(Ashley)/Judge/Humidity";
const char topic7[]  = "student/CASAoo16/Qian(Ashley)/Judge/Illumination";
const char topic8[]  = "student/CASAoo16/Qian(Ashley)/Judge/Soil Mosture";
const char topic9[]  = "student/CASAoo16/Qian(Ashley)/Reflection system/air condition";
const char topic10[]  = "student/CASAoo16/Qian(Ashley)/Reflection system/fan";
const char topic11[]  = "student/CASAoo16/Qian(Ashley)/Reflection system/LED Matrix";
const char topic12[]  = "student/CASAoo16/Qian(Ashley)/Reflection system/Pump";
const char topic13[]  = "student/CASAoo16/Qian(Ashley)/LED indicator/temperature indicator";
const char topic14[]  = "student/CASAoo16/Qian(Ashley)/LED indicator/humidity indicator";
const char topic15[]  = "student/CASAoo16/Qian(Ashley)/LED indicator/illumination indicator";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;
int count = 0;
// ------------------------------MQTT SETTING END-------------------//


//----------------------Read Sensor Data Function-------------------//
void getSensor(){
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  
  //Caculate the wet value
  wetValue = analogRead(wetPin);
  wetValue *= 100;
  wetValue = wetValue/1023;

  lightValue = analogRead(lightPin);
  
  Serial.print("Temperature: ");  
  Serial.println(temp); 
  Serial.print("Humidity: ");
  Serial.println(hum); 
  Serial.print("Illumination: ");
  Serial.println(lightValue);  
  Serial.print("Soil moisture: ");
  Serial.println(wetValue); 
  Serial.println(); 
}
//---------------------Read Sensor Data Function END-------------------//


//-----------------------------Reflection Function---------------------//
// Temperature Reflection
void opencooler(){
  digitalWrite(AIR, HIGH);
}

void openheater(){
  digitalWrite(AIR, HIGH);
}

void closetemp(){
  digitalWrite(AIR, LOW);
}

//FAN Reflection
void openFAN(){
  digitalWrite(FAN,HIGH);
}

void closeFAN(){
  digitalWrite(FAN, LOW);
}

// Lightmatrix Reflection

void openlight(){
    strip.setPixelColor(8, 255, 0, 255);
    strip.show();
    delay(50);
  }

void closelight(){
  strip.clear();
  strip.show();
}

// Pump Reflection
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
//-------------------------Reflection Function END-------------------//


//--------------------------Judge Function---------------------------//
// Soil moisture judge
void pump_judge(){
  if( wetValue > 60 ){
    closePump();
  }else if( wetValue < 30 ){
    openPump();
  }
}

// Temperature judege
void temperature_judge(){
  if( temp < 20 ){
    openheater();
  }else if (temp >30){
    opencooler();
    }else{
      closetemp();
  }
}

// Humidity judege
void humidity_judge(){
  if( hum > 55 ){
    closeFAN();
  }else if (hum < 40){
    openFAN();
  }
}

// Light judege
void light_judge(){
  if( lightValue < 2100 ){
    openlight();
  }else if (lightValue > 16865){
    closelight();
  }
}
//--------------------------Judge Function END-------------------------//


//------------------------Visualisation Function----------------------//
// LCD visualisation
void update_lcd1602(){
    // First Line
    lcd.setCursor(0,0); 
    lcd.print("Mois");    
    lcd.print(wetValue);   
    lcd.print(" ");
    lcd.print("light");
    lcd.print(lightValue);
    
    // Second Line
    lcd.setCursor(0,1);
    lcd.print("Temp"); 
    lcd.print(temp);
    lcd.print(" ");
    lcd.print("Hum"); 
    lcd.print(hum); 
}

//LED indicator

void LED_indicator(){
  Temp_indicator();
  Hum_indicator();
  Light_indicator();
}

void Temp_indicator(){
  if(temp < 20){
    Serial.print("Temperature is too low."); 
    Serial.println(dht.readTemperature()); 
     digitalWrite(3, HIGH);
  }else if(temp > 30){
    Serial.print("Temperature is too high."); 
    digitalWrite(3, HIGH);
  }else{
    Serial.print("Temperature is suitable"); 
    digitalWrite(3, LOW);
  }
}

void Hum_indicator(){
  if(hum < 20){
    Serial.print("Humidity is too low."); 
    digitalWrite(5, HIGH);
  }else if(hum > 30){
    Serial.print("Humidity is too high."); 
    digitalWrite(5, HIGH);
  }else{
    Serial.print("Humidity is suitable"); 
    digitalWrite(5, LOW);
  }
}

void Light_indicator(){
  if(lightValue < 2100){
    Serial.print("Illumination is too low.");  
    digitalWrite(11, HIGH);
  }else if(lightValue > 16865){
    Serial.print("Illumination is too high."); 
    digitalWrite(11, HIGH);
  }else{
    Serial.print("Illumination is suitable"); 
    digitalWrite(11, LOW);
  }
}

void sendMQTT(){

    int lightValue = analogRead(A0);
    int moisture = analogRead(A2);
    float temp = dht.readTemperature(); 
    int hum = dht.readHumidity(); 
    
    mqttClient.beginMessage(topic1);
    mqttClient.print(String(temp));
    mqttClient.endMessage();

    mqttClient.beginMessage(topic2);
    mqttClient.print(String(hum));
    mqttClient.endMessage();

    mqttClient.beginMessage(topic3);
    mqttClient.print(String(lightValue));
    mqttClient.endMessage();

    mqttClient.beginMessage(topic4);
    mqttClient.print(String(wetValue));
    mqttClient.endMessage();

    mqttClient.beginMessage(topic5);
    if(temp < 20){
      mqttClient.print("Temperature is too low, please open the cooler."); 
    }else if(temp > 30){
      mqttClient.print("Temperature is too high, please open the heater"); 
    }else{
      mqttClient.print("Temperature is suitable, I enjoy it!"); 
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic6);
    if(hum < 40){
      mqttClient.print("Humidity is too low, please open the fan"); 
    }else if(hum > 55){
      mqttClient.print("Humidity is too high,please remove me to another place."); 
    }else{
      mqttClient.print("Humidity is suitable, I enjoy it!"); 
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic7);
    if(lightValue < 40){
      mqttClient.print("Illumination is too low, please open the fan"); 
    }else if(lightValue > 55){
      mqttClient.print("Illumination is too high,please remove me to another place."); 
    }else{
      mqttClient.print("Illumination is suitable, I enjoy it!"); 
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic8);
    if(wetValue < 40){
      mqttClient.print("Moisture is too low, please give me some water"); 
    }else if(wetValue > 55){
      mqttClient.print("Moisture is too high,I cann't breath."); 
    }else{
      mqttClient.print("Moisture is suitable, I enjoy it!"); 
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic9);
    int judgeair=analogRead(A1);
    if(judgeair = 1){
      mqttClient.print("ON");
    }else{
      mqttClient.print("OFF");
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic10);
    int judgefan=digitalRead(6);
    if(judgefan = 1){
      mqttClient.print("ON");
    }else{
      mqttClient.print("OFF");
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic11);
    int judgelight=digitalRead(2);
    if(judgelight = 1){
      mqttClient.print("ON");
    }else{
      mqttClient.print("OFF");
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic12);
    if(pump_sta = 1){
      mqttClient.print("ON");
    }else{
      mqttClient.print("OFF");
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic13);
    if(temp < 20 or temp > 30){
      mqttClient.print("ON");
    }else{
      mqttClient.print("OFF");
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic14);
    if(hum < 40 or hum > 55){
      mqttClient.print("ON");
    }else{
      mqttClient.print("OFF");
    }
    mqttClient.endMessage();

    mqttClient.beginMessage(topic15);
    if(lightValue < 2100 or lightValue > 16865){
      mqttClient.print("ON");
    }else{
      mqttClient.print("OFF");
    }
    mqttClient.endMessage();
}
  
//--------------------Visualisation Function END---------------------//


//--------------------------------SET UP----------------------------//
void setup(){
    Serial.begin(9600);
    delay(2000);
    
    lcd.init();//Initialise the LCD
    lcd.backlight();
    dht.begin(); //Initialise the DHT sensor
    
    pumpInit(); // initialize pump
    pinMode(FAN,OUTPUT); // initialize fan
    analogWrite(FAN, 0);
    pinMode(AIR,OUTPUT);
    digitalWrite(AIR, LOW); // initialize air
    strip.setBrightness(BRIGHTNESS);
    pinMode(LIGHT,OUTPUT);
    strip.begin();  // initialize strip (required!)
    strip.setBrightness(BRIGHTNESS);

    pinMode(3,OUTPUT); //Initialise the LED1
    pinMode(5,OUTPUT); //Initialise the LED2
    pinMode(11,OUTPUT); //Initialise the LED3

    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(500);
  }

  mqttClient.setUsernamePassword(mqttuser, mqttpass);

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

//------------------------------SET UP END--------------------------//


//----------------------------LOOP-----------------------------------//
void loop(){

    // Read data from sensors
    getSensor();  

    // Judge Function with reflection
    temperature_judge();
    humidity_judge();
    light_judge();
    pump_judge(); 

    // Visualisation Function
    update_lcd1602(); 
    LED_indicator();

    //MQTT Function
    mqttClient.poll();
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    }   
    sendMQTT();     
    delay(500);
}
//---------------------------LOOP END-------------------------------//
