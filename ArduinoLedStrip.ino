#include <FastLED.h>
#define NUM_LEDS 20
#define DATA_PIN 13

CRGB leds[NUM_LEDS];

CRGB colors[4];
int offset = 0;

byte result[11] = {
    B00100001,
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B01000100
  };

void setup () {
  colors[0] = 0x000000;
  colors[1] = 0xFF0000;
  colors[2] = 0x00FF00;
  colors[3] = 0x0000FF;

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = colors[0];
    FastLED.show();
  }
  Serial.begin(9600);
  Serial.flush();
}

void loop () {
  //Read data from serial --> result
  
  //run through result array (1 configbyte, 10 displaybytes)
  for (int i = 1; i < 11; i++) {
    displayByte(result[i], i*4-4);
  }
  FastLED.show();
  delay(1000);
}

void displayByte(byte displayByte, int ledIndex) {
  leds[ledIndex] = colors[getIntFromByte(displayByte, 0, 2)];
  leds[ledIndex+1] = colors[getIntFromByte(displayByte, 2, 2)];
  leds[ledIndex+2] = colors[getIntFromByte(displayByte, 4, 2)];
  leds[ledIndex+3] = colors[getIntFromByte(displayByte, 6, 2)];
}

int getIntFromByte(byte value, int start, int length) {
  int result = 0;
  
  for (int i = 0; i < length; i++) {
    if (bitRead(value, i+start)) {
      result += pow(2, i);
    } 
  }
  
  return result;
}





