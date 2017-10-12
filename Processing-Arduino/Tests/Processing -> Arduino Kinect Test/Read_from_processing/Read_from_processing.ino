char val;
int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) { 
     Serial.println('heelo\n');
   }
   delay(10);
}
