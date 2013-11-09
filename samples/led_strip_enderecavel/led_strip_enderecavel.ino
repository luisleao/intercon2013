
int magnetSensorPin = 2;








int current_pixel = 0;
int current_pixel2 = 0;


#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(14, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(9600);
  pinMode(magnetSensorPin, INPUT); 

  // built-in pull-up resistor
  digitalWrite(magnetSensorPin, HIGH); 
  
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  /*
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  delay(100);
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  delay(100);
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  delay(100);
  */
  rainbow(30);
  //
  
/*
   int magnetReading = digitalRead(magnetSensorPin);
  
   //Serial.print("Digital reading = ");
   if(magnetReading) {
     
     //Serial.println("HIGH (no magnet)");
    rainbowCycle(5);
    //rainbowCycle2(20, strip.Color(0, 255, 0), strip.Color(50, 0, 0));
    // rainbowCycle2(100, strip.Color(255, 255, 255), strip.Color(0, 0, 0));
     
   }
   else {
     
     //Serial.println("LOW (magnet)");
     rainbowCycle2(1, strip.Color(255, 255, 255), strip.Color(50, 50, 50));
     
   }
   //delay(10);
*/
  
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      //strip.show();
      //delay(wait);
  }
  strip.show();
  delay(wait);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) { //strip.numPixels()
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle2(uint8_t wait, uint32_t colorA, uint32_t colorB) {
  uint16_t i, j;

  for(i=0; i< strip.numPixels(); i++) {
    
    strip.setPixelColor(i, current_pixel == i ? colorA : colorB);
    
    if (i == strip.numPixels() - current_pixel2) {
      strip.setPixelColor(i, strip.Color(0, 255, 0));
    }
      
  }
  strip.show();
  delay(wait);
  current_pixel++;
  current_pixel2++;
  
  current_pixel = current_pixel % strip.numPixels();
  current_pixel2 = current_pixel2 % strip.numPixels();
}




// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

