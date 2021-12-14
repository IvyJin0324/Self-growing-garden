int motor = 6;
bool fan = true;


void setup() { 
  pinMode(motor,OUTPUT);
} 

void loop() { 
  if(fan == true) {
    digitalWrite(motor,HIGH);
  }
  else {
    digitalWrite(motor,LOW);
  }
} 
