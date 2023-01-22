// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3; 

// Motor control pins
const int rightMotor1 = 5;
const int leftMotor1 = 6;
const int rightMotor2 = 10;
const int leftMotor2 = 12;
int Left = 0;
int Right = 0;

// Line sensor pins
const int rightLineSensor = 7;
const int leftLineSensor = 8;

// Servo control pin
const int servoPin = 9;

// LED pins
const int rightLED = 4;
const int leftLED = 5;

#include <Servo.h>
Servo myservo;

// start function to move the robot forward
// void moveForward()
// {
//   digitalWrite(rightMotor, 1);
//   digitalWrite(leftMotor, 1);
//   digitalWrite(rightLED, 0);
//   digitalWrite(leftLED, 0);
// }

// stop function to stop the robot
void stop()
{
  digitalWrite(rightMotor1, 0);
  digitalWrite(leftMotor1, 0);

  analogWrite(rightLED, 0);
  analogWrite(leftLED, 0);
}

// left function to make the robot turn left and turn on the left LED
void turnLeft()
{
   analogWrite(leftMotor1,0);
   analogWrite(leftMotor2,30);
   
   
   while(leftLineSensor ==0)
   {
    Left = digitalRead(leftLineSensor);
    Right = digitalRead(rightLineSensor);
    if(Right == 0)
    {
      int lprev = Left;
      int rprev = Right;
      stop();
      while( ( (lprev==Left) && (rprev==Right) ) == 1 )
      {
         Left = digitalRead(leftLineSensor);
         Right = digitalRead(rightLineSensor);
      }
    }
    analogWrite(rightMotor1,255);
    analogWrite(rightMotor2,0); 
   }
   analogWrite(leftMotor1,255);
   analogWrite(leftMotor2,0);
}

// right function to make the robot turn right and turn on the right LED
void turnRight()
{
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2,30);
   
   
  while(rightLineSensor == 0)
  {
    Left = digitalRead(leftLineSensor);
    Right = digitalRead(rightLineSensor);
    if(Left == 0)
    {
      int lprev = Left;
      int rprev = Right;
      stop();
      while( ( (lprev==Left) && (rprev==Right) ) == 1 )
      {
        Left = digitalRead(leftLineSensor);
        Right = digitalRead(rightLineSensor);
      }
    }
    analogWrite(leftMotor1,255);
    analogWrite(leftMotor2,0); 
  }
  analogWrite(rightMotor1,255);
  analogWrite(rightMotor2,0);
}

// function for ultrasonic sensor
void checkDistance()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  int duration = pulseIn(echoPin, HIGH);
  int distance = (duration * 0.034) / 2;

  // if distance is less than or equal to 10 cm, turn on the LED
  if (distance <= 10 && distance != 0)
  {
    digitalWrite(13, 1);
    myservo.write(135);
    delay(100);
    myservo.write(0);
  }
  else 
  {
    digitalWrite(13, 0);
  }  
}

void setup() 
{
  pinMode(echoPin, INPUT);
  pinMode(rightLineSensor, INPUT);
  pinMode(leftLineSensor, INPUT);
  
  pinMode(servoPin, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(trigPin, OUTPUT);  
}

void loop() 
{
  
  checkDistance(); // servo motor

  analogWrite(leftMotor1,255);
  analogWrite(leftMotor2,0);
  analogWrite(rightMotor1,255);
  analogWrite(rightMotor2,0);

  while(1)
  {
    Left = digitalRead(leftLineSensor);
    Right = digitalRead(rightLineSensor);
    
    if((Left==0 && Right==1) == 1)
    turnLeft();
    else if((Right==0 && Left==1) == 1)
    turnRight();
  } 
}
