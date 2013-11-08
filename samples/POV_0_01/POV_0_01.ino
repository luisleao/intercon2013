//============================================================
// Arduino POV Display
//
// Author: Carlos Asmat
// Last Modified: August 17, 2007
//
// Description: this is a quick code for a POV display
//		implemented using the Arduino. It used 6 LEDs
//		connected to the pins.
//		See http://carlitoscontraptions.blogspot.com
//		for more details.
//============================================================

int pins[] = {7,6,5,4,3,2};	// an array of pin numbers
int col_len = 6;		// column lenght


//http://carlitoscontraptions.blogspot.com.br/2007/08/pov-prototype-part-2.html


#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(14, PIN, NEO_GRB + NEO_KHZ800);

uint32_t VERDE = strip.Color(0, 150, 0);
uint32_t PRETO = strip.Color(0, 0, 0);
uint32_t VERMELHO = strip.Color(255, 0, 0);


/*
timer1: 3
timer2: 15
timer3: 0
data: {1,0,0,0,0,1, 1,1,0,0,1,1, 0,1,1,1,1,0, 0,0,1,1,0,0}
frame_len: 4
frame_num: 1
*/


// customizable parameters
int timer1 = 10;		// time between columns
int timer2 = 3;  	        // time between frames
int timer3 = 3;                 // time between drawings
int frame_len = 12;		// frame length
int frame_num = 1;		// number of frames

// data corresponding to the image to be displayed
//sinewave
int data[] = {0,0,1,0,0,0, 0,1,0,0,0,0, 1,0,0,0,0,0, 1,0,0,0,0,0, 0,1,0,0,0,0, 0,0,1,0,0,0, 0,0,0,1,0,0, 0,0,0,0,1,0, 0,0,0,0,0,1, 0,0,0,0,0,1, 0,0,0,0,1,0, 0,0,0,1,0,0};


/*
sinewave

int timer1 = 3;			// time between columns
int timer2 = 3;		        // time between frames
int timer3 = 0;	                // time between drawings
int frame_len = 12;		// frame length
int frame_num = 1;		// number of frames
int data[] = {0,0,1,0,0,0, 0,1,0,0,0,0, 1,0,0,0,0,0, 1,0,0,0,0,0, 0,1,0,0,0,0, 0,0,1,0,0,0, 0,0,0,1,0,0, 0,0,0,0,1,0, 0,0,0,0,0,1, 0,0,0,0,0,1, 0,0,0,0,1,0, 0,0,0,1,0,0};

*/


//INTERCON

/*{
  
1,0,0,0,0,1,
1,1,1,1,1,1,
1,1,1,1,1,1,
1,0,0,0,0,1,

1,1,1,1,1,1,
0,1,1,0,0,0,
0,0,0,1,1,0,
1,1,1,1,1,1,


1,0,0,0,0,0,
1,1,1,1,1,1,
1,1,1,1,1,1,
1,0,0,0,0,0,


1,1,1,1,1,1,
1,0,1,1,0,1,
1,0,1,1,0,1,
1,0,0,0,0,1,


1,1,1,1,1,1,
1,0,1,1,0,0,
1,0,1,0,1,0,
1,1,1,0,0,1,


1,1,1,1,1,1,
1,0,0,0,0,1,
1,0,0,0,0,1,
1,0,0,0,0,1,

0,1,1,1,1,0,
1,0,0,0,0,1,
1,0,0,0,0,1,
0,1,1,1,1,0,

1,1,1,1,1,1,
0,1,1,0,0,0,
0,0,0,1,1,0,
1,1,1,1,1,1,



};
*/


void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  
/*  	int i;
	for (i = 0; i < col_len; i++)
		pinMode(pins[i], OUTPUT);	// set each pin as an output
*/

}

void loop()
{
	int a,b,c;
	
	// go through all data for all columns in each frame.
	for (a = 0; a < frame_num; a++)
	{
		for (b = 0; b < frame_len; b++)
		{
			for (c = 0; c < col_len; c++)
			{
                                strip.setPixelColor(c+5, data[a*frame_len*col_len + b*col_len + c] == 0 ? PRETO : VERMELHO);
                                strip.show();
			}
			delay(timer1);
		}
		for (c = 0; c < col_len; c++)
		{digitalWrite(pins[c], LOW);}
		delay(timer2);
	}
	delay(timer3);
}
