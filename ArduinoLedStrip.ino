#include <FastLED.h>
#define NUM_LEDS 20
#define DATA_PIN 13

CRGB leds[NUM_LEDS];

CRGB colors[4];
int offset = 0;

byte result[5] = {
    B01010101,
    B01010101,
    B01010101,
    B01010101,
    B01010101
  };

void setup () {
  colors[0] = 0x000000;
  colors[1] = 0x100000;
  colors[2] = 0x001000;
  colors[3] = 0x000010;

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  for (int c = 1; c <= 3; c++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = colors[c];
      FastLED.show();
    }
    delay(200);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = colors[0];
    FastLED.show();
  }
  Serial.begin(9600);
  Serial.flush();
}

void loop () {
  //Read data from serial --> result
  if (Serial.available() > 0) {
    //Read first byte to obtain the type of the message
   byte bMessageType = Serial.read();
   int messageType = (int) bMessageType;
   
   if (messageType == 2 || true) {
     //the next five bytes are display bytes, read from buffer
     byte bufferMessage[5];
     for (int i = 0;i < 5; i++) {
       bufferMessage[i] = Serial.read();
       Serial.println((int) bufferMessage[i]);
     }
     
     for (int i = 0; i < 5; i++) {
        displayByte(bufferMessage[i], i*4);
     }
     FastLED.show();
   }
  }
  delay(10);
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





