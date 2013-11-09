#include <avr/interrupt.h>

float wRadius = 0.015; //in m
float wDiam = 2 * PI * wRadius;
int timestep = 1000;

volatile int trigCount = 0;
                              
void setup(void)
{
    Serial.begin(9600);
    pinMode(2, INPUT);
    digitalWrite(2, HIGH);    
    attachInterrupt(0, pin2ISR, RISING);
}
                              
void loop(void)
{
    delay(timestep);
    //Serial.println(trigCount);
    Serial.print("s:");
    Serial.println(trigCount*wDiam);
    trigCount = 0;  
}

void pin2ISR(){
  trigCount++;
}


