#include <M5Stack.h>

#define NOTE_D0 -1
#define NOTE_D1 294
#define NOTE_D2 330
#define NOTE_D3 350
#define NOTE_D4 393
#define NOTE_D5 441
#define NOTE_D6 495
#define NOTE_D7 556

#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278

#define NOTE_DH1 589
#define NOTE_DH2 661
#define NOTE_DH3 700
#define NOTE_DH4 786
#define NOTE_DH5 882
#define NOTE_DH6 990
#define NOTE_DH7 112


void setup() {

  // Initialize the M5Stack object
  M5.begin();
  
  Serial.println("M5Stack Speaker test:\r\n");
  M5.Speaker.setVolume(8);
}

void loop() {
  M5.update();
  
  if(M5.BtnA.wasPressed()) {
    //M5.Lcd.printf("wasPressed A \r\n");
    Serial.println("A was pressed.");
    M5.Speaker.beep();
  }

  if(M5.BtnB.wasPressed())
  {
    //M5.Lcd.printf("wasPressed B \r\n");
    Serial.println("B was pressed.");
    M5.Speaker.tone(3000, 200); //frequency 3000, durtion 200ms
  }

  if(M5.BtnC.wasPressed())
  {
    //M5.Lcd.printf("wasPressed C \r\n");
    Serial.println("C was pressed.");
    M5.Speaker.tone(440, 200);
    M5.Speaker.tone(493, 200);
    M5.Speaker.tone(523, 200);
    M5.Speaker.tone(493, 200);
    M5.Speaker.tone(523, 200);
    M5.Speaker.tone(440, 200);
  }
}
