int micPin = A0;
int testPin = A1;
int counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Started.");

  pinMode(testPin, OUTPUT);
  pinMode(micPin, INPUT);
}

void loop() {
  Serial.println(analogRead(micPin));
  if(counter % 2 == 0){
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(testPin, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(testPin, LOW);
  }

  ++counter;
  delay(250);
}
