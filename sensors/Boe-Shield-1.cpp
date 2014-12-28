
#include <Servo.h>

Servo servoLeft;          // Define left servo
Servo servoRight;         // Define right servo
const int trigPin = 5;    // output of the sensor 
const int echoPin = 6;    // input of the sensor 
int timer = 100;

void setup() { 
  servoLeft.attach(12);   // Set left servo to digital pin 12
  servoRight.attach(13);  // Set right servo to digital pin 13
  Serial.begin(9600);
} 

void loop() 
{              
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The ultrasonic sensor is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // uses subfunction to convert time into distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  // conditional to seek distance 
  if (inches > 5)
  {
    forward();
  }  
  else if (inches < 5) 
  {
    turnLeft();
  }
  
}

long microsecondsToInches(long microseconds)
{
  // 73.746 microseconds per inch 
  // divide by 2 to get the distance of the obstacle
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // speed of sound is 340 m/s or 29 microseconds per centimeter.
  // to find the distance of the take half of the distance travelled.
  return microseconds / 29 / 2;
}

// Motion routines for forward, reverse, turns, and stop
void forward() {
  //left at 180 and right at zero is forward 
  servoLeft.write(180);
  servoRight.write(0);
}

void turnLeft() {
  //left at zero and right at zero is left 
  servoLeft.write(0);
  servoRight.write(0);
}

