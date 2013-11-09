#include <avr/interrupt.h>

float wRadius = 0.015; //in m
float wPerim = 2 * PI * wRadius;
int timestep = 1000;

volatile int trigCount = 0;
                              
void setup(void)
{
    Serial.begin(9600);
    pinMode(2, INPUT);
    pinMode(13, OUTPUT);    
    digitalWrite(2, HIGH); 
    digitalWrite(13, LOW);
    attachInterrupt(0, pin2ISR, RISING);
}
                              
void loop()
{
    delay(timestep);
    Serial.println(trigCount);    
    Serial.println(trigCount*wPerim);
    trigCount = 0;
    digitalWrite(13, LOW);    
}

void pin2ISR(){
  trigCount++;
  digitalWrite(13, HIGH);
}


