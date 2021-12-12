/**
QIAN JIN
MON 6 DEC 2021
*/
#include "arduino.h"
#include "IRremote.h"
#include <FastLED_NeoPixel.h>


#define KAY_0 0xFF6897 
#define KAY_1 0xFF30CF
#define KAY_2 0xFF18E7
#define KAY_3 0xFF7A85
#define KAY_4 0xFF10EF
#define KAY_5 0xFF38C7
#define KAY_6 0xFF5AA5
#define KAY_7 0xFF42BD
#define KAY_8 0xFF4AB5
#define KAY_9 0xFF52AD 

#define AIR A1     
#define AIR_LED_B_PIN -1
#define MOTOR_INA1  8
#define MOTOR_INA2  9
#define LIGHT 2
#define NUM_LEDS 8 
#define BRIGHTNESS 5
FastLED_NeoPixel<NUM_LEDS, LIGHT, NEO_GRB> strip; 

CRGB leds[NUM_LEDS];

int FAN = 6;
int RECV_PIN = 7;  
int light_sta = 0;
int light_num = 0;
          
IRrecv irrecv(RECV_PIN);     
decode_results results; 


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  strip.setBrightness(BRIGHTNESS);
  Serial.println("EnabFAN IRin");
  pinMode(FAN,OUTPUT);
  pinMode(AIR,OUTPUT);
  analogWrite(FAN, 0); 
  digitalWrite(AIR, HIGH);
  pinMode(LIGHT,OUTPUT);
  strip.begin();  // initialize strip (required!)
  strip.setBrightness(BRIGHTNESS);
  pumpInit();
}

void loop() {
  if (irrecv.decode(&results)) {
    ir_remote_action();
    Serial.println(results.value, HEX);
    irrecv.resume();           // Receive the next value
    bool IRreceived = true;
  }
  delay(600);
}


void ir_remote_action(){
  switch(results.value){
    case KAY_1: digitalWrite(FAN,HIGH); irrecv.enableIRIn(); break;
    case KAY_2: digitalWrite(FAN,LOW); irrecv.enableIRIn(); break;
    case KAY_3: digitalWrite(AIR, LOW); irrecv.enableIRIn(); break;
    case KAY_4: digitalWrite(AIR, HIGH); irrecv.enableIRIn(); break;
    case KAY_5: openPump();;  irrecv.enableIRIn(); break;
    case KAY_6: closePump();  irrecv.enableIRIn(); break;   
    case KAY_7: colorWipe(strip.Color(255, 0, 0), 25); irrecv.enableIRIn(); break;
    case KAY_8: colorWipe(strip.Color(0, 0, 255), 25); irrecv.enableIRIn(); break;
    case KAY_9: colormode(); irrecv.enableIRIn(); break;
    case KAY_0: blank(1000); irrecv.enableIRIn(); break;
  }
}

void pumpInit(){
  pinMode( MOTOR_INA1,OUTPUT );
  pinMode( MOTOR_INA2,OUTPUT );
  analogWrite( MOTOR_INA1, 0 );
  analogWrite( MOTOR_INA2 , 0 );
}

void openPump(){
  analogWrite(MOTOR_INA1, 150);
  analogWrite(MOTOR_INA2 , 0);
}

void closePump(){
  analogWrite(MOTOR_INA1, 0);
  analogWrite(MOTOR_INA2 , 0);
}

void colorWipe(uint32_t color, unsigned long wait) {
  for (unsigned int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(50);
  }
}

void colormode(){
  theaterChase(strip.Color(0, 255, 255), 100, 3, 5);  // cyan
  theaterChase(strip.Color(255, 0, 255), 100, 3, 5);  // magenta
  theaterChase(strip.Color(255, 255, 0), 100, 3, 5);  // yellow

  rainbow(10, 3);
  blank(1000);
}

void theaterChase(uint32_t color, unsigned long wait, unsigned int groupSize, unsigned int numChases) {
  for (unsigned int chase = 0; chase < numChases; chase++) {
    for (unsigned int pos = 0; pos < groupSize; pos++) {
      strip.clear();  // turn off all LEDs
      for (unsigned int i = pos; i < strip.numPixels(); i += groupSize) {
        strip.setPixelColor(i, color);  // turn on the current group
      }
      strip.show();
      delay(wait);
    }
  }
}

void rainbow(unsigned long wait, unsigned int numLoops) {
  for (unsigned int count = 0; count < numLoops; count++) {
    // iterate through all 8-bit hues, using 16-bit values for granularity
    for (unsigned long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
      for (unsigned int i = 0; i < strip.numPixels(); i++) {
        unsigned long pixelHue = firstPixelHue + (i * 65536UL / strip.numPixels()); // vary LED hue based on position
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));  // assign color, using gamma curve for a more natural look
      }
      strip.show();
      delay(wait);
    }
  }
}

//Blanks the LEDs and waits for a short time.

void blank(unsigned long wait) {
  strip.clear();
  strip.show();
  delay(wait);
}
