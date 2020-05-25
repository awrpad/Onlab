#define SPEAKER_PIN 25
#define TONE_PIN_CHANNEL 0
#define SDA_PIN 19
#define SCL_PIN 18

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <MPU9250_asukiaaa.h>
//#include "esp32-hal-ledc.h"
#include <Wire.h>

Adafruit_ST7735 tft = Adafruit_ST7735(16, 17, 23, 5, 9);
MPU9250_asukiaaa mpu;

int counter = 0;

void setup() {
  pinMode(27,INPUT);
  digitalWrite(27,HIGH);
  tft.initR(INITR_18GREENTAB);
  tft.fillScreen(ST7735_CYAN);
  tft.setTextColor(0x5FCC);
  tft.setTextSize(1);
  //tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.print("setup.");
  delay(350);

  ledcSetup(TONE_PIN_CHANNEL, 0, 13);
  ledcAttachPin(SPEAKER_PIN, TONE_PIN_CHANNEL);

  tft.print(".");
  delay(350);

  ledcWriteTone(TONE_PIN_CHANNEL, 440);
  delay(200);
  ledcWriteTone(TONE_PIN_CHANNEL, 0);
  ledcWriteTone(TONE_PIN_CHANNEL, 562);
  delay(200);
  ledcWriteTone(TONE_PIN_CHANNEL, 0);
  digitalWrite(SPEAKER_PIN, 0);
  
  tft.print(".");
  delay(250);

  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.setWire(&Wire);
  mpu.beginAccel();
  mpu.beginMag();

  tft.setCursor(0, 12);
  tft.print("setup DONE.");
  tft.fillScreen(ST7735_BLACK);
  bociBoci();
  //bociBoci();
}

void loop() {
  /*if(counter % 2 == 0){
    tft.fillScreen(ST7735_BLACK);
  }
  else {
    tft.fillScreen(ST7735_WHITE);
  }*/
  tft.fillRect(0, 0, 30, 35, ST7735_BLACK);

  //++counter;

  mpu.accelUpdate();
  tft.setCursor(0, 0);
  tft.print(mpu.accelX());
  tft.setCursor(0, 12);
  tft.print(mpu.accelY());
  tft.setCursor(0, 24);
  tft.print(mpu.accelZ());
  
  delay(200);
}

void bociBoci(){
  playTone(293);
  playTone(349);
  playTone(293);
  playTone(349);
  playTone(440);
  playTone(440);
}

void playTone(int freq){
  ledcWriteTone(TONE_PIN_CHANNEL, freq);
  delay(200);
  ledcWriteTone(TONE_PIN_CHANNEL, 0);
}
