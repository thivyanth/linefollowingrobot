int usout = 2;
int usin = 3; 
int lm29 = 4;
int rhs = 7;
int lhs = 8;

int rm = 5;
int lm = 6;

#include <Servo.h>
Servo myservo;
#define servopin 9
int angle = 0;

void start()
{
  digitalWrite(rm, 1);
  digitalWrite(lm, 1);
}

void stop()
{
  digitalWrite(rm, 0);
  digitalWrite(lm, 0);
}

void left()
{
  digitalWrite(rm, 1);
  digitalWrite(lm, 0);
}

void right()
{
  digitalWrite(lm, 1);
  digitalWrite(rm, 0);
}

void us(int trigpin, int echopin)
{
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  
  int duration = pulseIn(echopin, HIGH);

  int distance = (duration * 0.034) / 2;


  if (distance <= 10 && distance != 0)
  {
    digitalWrite(13, 1);
  }
  else 
  {
    digitalWrite(13, 0);
  }  
}

void setup() 
{
  pinMode(usout, OUTPUT);
  pinMode(usin, INPUT);
  pinMode(lm29, OUTPUT);
  pinMode(rhs, INPUT);
  pinMode(lhs, INPUT);
}

void loop() 
{
  if (rhs == 1 && lhs == 1)
  {
    start();
  }
  else if (rhs == 0 && lhs == 0)
  {
    stop();
  }
  else if (rhs == 1 && lhs == 0)
  {
    left();
  }
  else if (rhs == 0 && lhs == 1)
  {
    right();
  }
  
  us(usout, usin);   
}
