 // ESP32 + 1.44" TFT v2.1                                  // 2017.02.08 macsbug
// http://www.sipatechmeetup.com/media/uploads/arduinoesp32dev.pdf
#include <Adafruit_GFX.h>                                  // Core graphics library
#include <Adafruit_ST7735.h>                               // Hardware-specific library
//#include <mySD.h>
#define LED_BUILTIN 22
Adafruit_ST7735 tft = Adafruit_ST7735(16, 17, 23, 5, 9); // CS,A0,SDA,SCK,RESET
float r, x1, ya, z1, x2, y2, z2, x3, y3, z3;               //
int f[8][2], x, y;                                         // Draw box, x, y center
int c[8][3] = {                                            // Cube
 {-20,-20, 20},{20,-20, 20},{20,20, 20},{-20,20, 20},
 {-20,-20,-20},{20,-20,-20},{20,20,-20},{-20,20,-20} };
// File root;
int line = 0;
 
void setup(void) {
  pinMode(27,INPUT);//Backlight:27
  digitalWrite(27,HIGH);//New version added to backlight control
  tft.initR(INITR_18GREENTAB);                             // 1.44 v2.1
  tft.fillScreen(ST7735_BLACK);                            // CLEAR
  tft.setTextColor(0x5FCC);                                // GREEN
  tft.setRotation(1);                                      // 
  x = tft.width() /2; x = x + 14;                          // x Center Calculat
  y = tft.height()/2;                                      // y Center Calculate
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}
 
void loop(){
  tft.fillScreen(ST7735_BLACK);
  
  for(int i = 0; i < 100; ++i){
    tft.drawLine(10,20,30,i,ST7735_GREEN);
  }
  delay(1000);
  tft.fillScreen(ST7735_BLUE);
  delay(750);
  tft.fillScreen(ST7735_BLACK); 

  for(int i = 0; i < 100; ++i){
    tft.drawLine(10,20,i,40,ST7735_GREEN);
  }
  delay(1000);
  tft.fillScreen(ST7735_GREEN);
  delay(750);
  tft.fillScreen(ST7735_BLACK); 

  for(int i = 0; i < 100; ++i){
    tft.drawLine(10,i,30,40,ST7735_GREEN);
  }
  delay(1000);
  tft.fillScreen(ST7735_CYAN);
  delay(750);
  tft.fillScreen(ST7735_BLACK);

  for(int i = 0; i < 100; ++i){
    tft.drawLine(i,20,30,40,ST7735_GREEN);
  }
  delay(1000);
  tft.fillScreen(ST7735_ORANGE);
  delay(750);
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);
  printTFT("Some value:", ST7735_WHITE);
  printTFT("22", ST7735_GREEN);
  printTFT("Other tested value:", ST7735_WHITE);
  printTFT("135", ST7735_BLUE);
  printTFT("Test thing:", ST7735_WHITE);
  printTFT("6.7", ST7735_CYAN);
 
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

void printTFT(char *text, int color){
  tft.setTextColor(color);
  tft.setCursor(0, line);
  tft.print(text);
  line += 13;
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  
  if(line > 128){
    line = 0;
    tft.fillScreen(ST7735_BLACK);
  }
}
