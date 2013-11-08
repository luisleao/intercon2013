//simple POV display with 7 leds and 1 tilt sensor
//by phil (www.telalab.org) philteta@gmail.com
//7x5 ascii font from TVout Lib
// version 0.5

#include "font7x5.h"
#include <avr/pgmspace.h>

int delinterchar = 800 ;//delay between 2 char
int delinterpoint = 400; //delay between 2 points of a char

#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);



uint32_t VERDE = strip.Color(0, 150, 0);
uint32_t PRETO = strip.Color(0, 0, 0);


#define led1 6
#define led2 7
#define led3 8
#define led4 9
#define led5 10
#define led6 11
#define led7 12


#define sensorPin 2
#define policex 5
#define nbleds 7
int boucle = 0;
#define repet 10 //number of repetition before changing message
char texte[]  = "Hi"; // data to write on startup
char texte2[] = "BEER INSIDE"; // data to write after "repet" writing of the first message
unsigned long lasttimeloop;
unsigned long timeloop;


int a = 0;
int leds[nbleds] = {
  led1,led2,led3,led4,led5,led6,led7};

void setup()   
{                
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  

  lasttimeloop = micros();
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}



void alloff()
{
  
  colorWipe(0, 0);
}


void loop()                     
{
  if (true || digitalRead(2)==LOW) //tilt sensor triggerd
  {
    
    timeloop = micros() - lasttimeloop; //time between two "shakes"
    lasttimeloop = micros();
    if (timeloop>5000000) timeloop = 1000000; //limitation for loop time
    delay(50);

    //if (boucle< (repet + 1))
    //{
      delinterchar = timeloop/(sizeof(texte)*policex*policex);
      delinterpoint = delinterchar/2;
      for (a=0;a<sizeof(texte)-1;a++)
      {
        displayChar(texte[a]);
        alloff();
        delayMicroseconds(delinterchar);
      }
    //}
/*
    if (boucle>repet)
    {
      delinterchar = timeloop/(sizeof(texte2)*policex*policex);
      delinterpoint = delinterchar/2;
      for (a=0;a<sizeof(texte2)-1;a++)
      {
        displayChar(texte2[a]);
        alloff();
        delayMicroseconds(delinterchar);
      }
    }
    boucle++;
    if (boucle> ((repet*2)+1)) boucle = 0;
*/
  }
}

void displayChar(char c)
{
  c = c - 32;
  for (int i = 7;i>2;i--)
  {
    for (int j = 0;j<7;j++) 
    {
      
      strip.setPixelColor(j, bitRead(pgm_read_byte_near(charbook + (7*c+j)),i) == 1 ? VERDE : PRETO);
      //if (bitRead(pgm_read_byte_near(charbook + (7*c+j)),i) == 1)  digitalWrite(leds[j], HIGH);
      //else digitalWrite(leds[j], LOW);
    }
     strip.show();
    delayMicroseconds(delinterpoint);
  }
  
}

