/* The package we send:
 * 
 * +-----------+ 
 * |    - 1    |
 * | sample[0] |
 * | sample[1] |
 *  ˇˇˇˇˇˇˇˇˇˇˇ
 *      ...
 *  ^^^^^^^^^^^
 * | sample[n] |
 * |elapsedTime|
 * |    - 3    |
 * +-----------+
 * 
 */
// Constants and variables for the package
const int sampleCount = 500, offset = 1, timeLength = 1, trail = 1;
const int packageSize = offset + sampleCount + timeLength + trail;
int package[packageSize];

int micInPin = A2;
int sendEnablePin = 7;
int a = 0;

void setup() {
  Serial.begin(115200);
  pinMode(sendEnablePin, INPUT);

  // The array should start with one -1
  for(int i = 0; i < offset; ++i){
    package[i] = -1;
  }

  // The array should end with one -3
  for(int i = offset + sampleCount + timeLength; i < packageSize; ++i){
    package[i] = -3;
  }
}

void loop() {
  int startTime = millis();
  for(int i = offset; i < sampleCount + offset; ++i){
    package[i] = analogRead(micInPin);
  }
  package[packageSize - trail - 1] = millis() - startTime;
 
  // Send the data only if the reciever is asking for it
  if(digitalRead(sendEnablePin) == 1){
    for(int i = 0; i < packageSize; ++i){
      Serial.println(package[i]);
    }
  }
}
