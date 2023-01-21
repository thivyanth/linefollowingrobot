// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3; 

// Motor control pins
const int rightMotor = 5;
const int leftMotor = 6;

// Line sensor pins
const int rightLineSensor = 7;
const int leftLineSensor = 8;

// Servo control pin
const int servoPin = 9;

// LED pins
const int rightLED = 10;
const int leftLED = 11;

#include <Servo.h>
Servo myservo;

// start function to move the robot forward
void moveForward()
{
  digitalWrite(rightMotor, 1);
  digitalWrite(leftMotor, 1);
  digitalWrite(rightLED, 0);
  digitalWrite(leftLED, 0);
}

// stop function to stop the robot
void stop()
{
  digitalWrite(rightMotor, 0);
  digitalWrite(leftMotor, 0);
  digitalWrite(rightLED, 0);
  digitalWrite(leftLED, 0);
}

// left function to make the robot turn left and turn on the left LED
void turnLeft()
{
  digitalWrite(rightMotor, 1);
  digitalWrite(leftMotor, 0);
  digitalWrite(leftLED, 1);
}

// right function to make the robot turn right and turn on the right LED
void turnRight()
{
  digitalWrite(leftMotor, 1);
  digitalWrite(rightMotor, 0);
  digitalWrite(rightLED, 1);
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
    Servo.write(135);
    delay(100);
    Servo.write(0);
  }
  else 
  {
    digitalWrite(13, 0);
  }  
}

void setup() 
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(rightLineSensor, INPUT);
  pinMode(leftLineSensor, INPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
}

void loop() 
{
  
  checkDistance(); // servo motor

  // if both right and left sensors are on a line, move forward
  if (digitalRead(rightLineSensor) == 1 && digitalRead(leftLineSensor) == 1)
  {
    moveForward();
  }
  // if both right and left sensors are off the line, stop
  else if (digitalRead(rightLineSensor) == 0 && digitalRead(leftLineSensor) == 0)
  {
    stop();
  }
  // if only the right sensor is off the line, turn left
  else if (digitalRead(rightLineSensor) == 1 && digitalRead(leftLineSensor) == 0)
  {
    turnLeft();
  }
  // if only the left sensor is off the line, turn right
  else if (digitalRead(rightLineSensor) == 0 && digitalRead(leftLineSensor) == 1)
  {
    turnRight();
  }
    
}
