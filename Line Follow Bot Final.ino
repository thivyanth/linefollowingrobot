#include <Servo.h>
#include <NewPing.h>
int Left = 0;
int Right = 0;
int front = 200;
int maxdis = 20;
const int trigPin = 2;
const int echoPin = 3;
const int rightmotorenb = 5;
const int leftmotorenb = 6;
const int rightLineSensor = 7;
const int leftLineSensor = 8;
const int servoPin = 9;
Servo myservo;
NewPing sonar(trigPin, echoPin, maxdis);
//---------------------Defining function--------------------------//
void push()
{
  myservo.write(0);
  delay(1000);
  myservo.write(90);
}
void move()
{
  analogWrite(rightmotorenb, front);
  analogWrite(leftmotorenb, front);  
}
void stop()
{
  analogWrite(leftmotorenb, 0);
  analogWrite(rightmotorenb, 0);

}
void turnLeft()
{
  analogWrite(leftmotorenb, front);
  analogWrite(rightmotorenb, 0);
}
void turnRight()
{
  analogWrite(rightmotorenb,front);
  analogWrite(leftmotorenb, 0);
}
//--------------------Setup---------------------------//
void setup() 
{
  pinMode(echoPin, INPUT);
  pinMode(rightLineSensor, INPUT);
  pinMode(leftLineSensor, INPUT);
  pinMode(trigPin, OUTPUT);  
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);
  Serial.begin(9600);
}
//--------------------loop---------------------------//
void loop() 
{
  unsigned int distance = sonar.ping_cm(); 
  Serial.println(distance);

  Left = digitalRead(leftLineSensor);
  Right = digitalRead(rightLineSensor);

  if (distance > 7 || distance == 0)
  {
    if (Left == 0 && Right == 0)
    {
      move();
    }
    else if(Left==0 && Right==1)
    {
      turnRight();
    }

    else if(Right==0 && Left==1)
    {
      turnLeft();      
    }
    else if (Left == 1 && Right == 1)
    {
      stop(); 
    }
    
  }
  else if (distance < 7 && distance != 0)
  {
    stop();
    delay(500);
    push();
    delay(500);
    move();
  } 
}
