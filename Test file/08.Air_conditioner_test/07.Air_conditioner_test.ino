#define AIR_LED_R_PIN -1
#define AIR_LED_G_PIN A1     
#define AIR_LED_B_PIN -1

void setup() {
  Serial.begin(9600);
  pinMode(AIR_LED_R_PIN,OUTPUT);
  pinMode(AIR_LED_G_PIN,OUTPUT);
  digitalWrite(AIR_LED_R_PIN, LOW); 
  digitalWrite(AIR_LED_G_PIN, HIGH);
}

void loop() {
  digitalWrite(AIR_LED_G_PIN, LOW); 
  delay(5000);
  digitalWrite(AIR_LED_G_PIN, HIGH);
  delay(5000);
}
