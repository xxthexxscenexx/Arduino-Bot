/* ultrasonic range sensor
 * This sketch reads an ultrasonic rangefinder and returns the
 * distance to the closest object in range. To do this, it sends a pulse
 * to the sensor to initiate a reading, then listens for a pulse 
 * to return.  The length of the returning pulse is proportional to 
 * the distance of the object from the sensor.
 * The circuit:
 * +V connection of the distance sensor attached to +5V
 * GND connection of the distance sensor attached to ground
 * TRIG connection of the distance sensor attached to digital pin 7
 * ECHO connection of the distance sensor attached to digital pin 4
 * The Parallax Ping))) sensor uses one pin to send and recieve information while
 * the one I bought sends and recieves info on two different pins. 
 * Adapted from code used for the Ping))) sensor. 
 */

const int pingPin = 7; // output of the sensor 
const int echoPin = 4; // input of the sensor 

void setup() 
{
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The ultrasonic sensor is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the ultrasonic sensor: a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // uses subfunction to convert time into distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  // print inches and centimeters to the serial monitor 
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the sensor, there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
