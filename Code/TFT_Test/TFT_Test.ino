//Works Board ESP32 2.0.11, updated to 3.0.1 and stopped it from working, 2.0.17 no worky, 2.0.13 works
//Works Lib TFT_ESPI 2.5.34

/*
0x0000	Black
0xFFFF	White
0xBDF7	Light Gray
0x7BEF	Dark Gray
0xF800	Red
0xFFE0	Yellow
0xFBE0	Orange
0x79E0	Brown
0x7E0	Green
0x7FF	Cyan
0x1F	Blue
0xF81F	Pink
*/
#define White     0xFFFF
#define Black     0x0000

/*
 #define TFT_WIDTH 240
 #define TFT_HEIGHT 280
*/

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "bigFont.h"
#include "midleFont.h"
#include "smallFont.h"
//#include "valueFont.h"
#include "DotFont.h"

//#define KILL 11   //Needed for power on
//#define CHARGE 9  //GPIO for monitoring when plugged into USB-C

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
TFT_eSprite sprite = TFT_eSprite(&tft);

void setup(void)
 {
  //pinMode(KILL, OUTPUT);
  //digitalWrite(KILL, HIGH);

  //pinMode(CHARGE, INPUT);
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  sprite.createSprite(280,240);
}

String text;
int i=0;

void draw()
{
  sprite.fillSprite(Black);
  sprite.setTextColor(White, Black);
  sprite.loadFont(DotFont); 
  sprite.drawString(text,100,120);
  sprite.pushSprite(0, 0);
}

void loop() 
{
  text=String(i);
  draw();
  delay(100);
  
  i++;
  if(i==10) i=0;
}
