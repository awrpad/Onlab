#include <mySD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

Adafruit_ST7735 tft = Adafruit_ST7735(16, 17, 23, 5, 9);
bool couldSetUpSD = false;
int counter = 0;

void setup() {
  Serial.begin(115200);
  
  tft.initR(INITR_18GREENTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(0x5FCC);
  tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.print("setup.");

  if(!SD.begin(13, 15, 2, 14)){
    tft.fillScreen(ST7735_RED);
    tft.setTextColor(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.print("Setting up the SD card was unsuccessful.");
    return;
  }
  else {
    couldSetUpSD = true;
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.print("SD SUCCESS.");
  }

  delay(2500);
}

void loop() {
  if(couldSetUpSD){
    if(counter % 2 == 0){
      tft.fillScreen(ST7735_GREEN);
    }
    else {
      tft.fillScreen(ST7735_YELLOW);
    }
    ++counter;

    delay(750);
  }
}
