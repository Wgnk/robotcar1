#include <Servo.h>
#include <AFMotor.h>
#include<NewPing.h>           
#define Echo A5
#define Trig A4
#define motor 10
#define Speed 250
#define spoint 103
//int Speed=250;
//NewPing sonar(Trig, Echo); 
/*#define RIGHT A1          // Right IR sensor connected to analog pin A2 of Arduino Uno:
#define LEFT A2
#define MAX_DISTANCE 200  
unsigned int distance_value= 0;    //Variable to store ultrasonic sensor distance:
unsigned int Right_Value = 0; //Variable to store Right IR sensor value:
unsigned int Left_Value = 0;  //Variable to store Left IR sensor value:
NewPing sonar(Trig,Echo, MAX_DISTANCE);  //NewPing setup of pins and maximum distance:

  */
char value;
int distance;
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;
Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);
 int pos=0; 
void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(motor);
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);

   //Serial.begin(9600); //initailize serial communication at 9600 bits per second:
 
}


void loop() {
  //Obstacle();
  Bluetoothcontrol();
  voicecontrol();
 human();
}
void Bluetoothcontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
  }
  if (value == 'U') {
    forward();
  } else if (value == 'D') {
    backward();
  } else if (value == 'L') {
    left();
  
  } else if (value == 'R') {
    right();
  
  } else if (value == 'S') {
    Stop();
  }
}
void Obstacle() {
  distance = ultrasonic();
  if (distance <=30) {
    Stop();
    backward();
    delay(100);
    Stop();
    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      left();
      delay(500);
      Stop();
      delay(200);
    } else if (L > R) {
      right();
      delay(500);
      Stop();
      delay(200);
    }
  
  } 
  else {
    forward();
    //Speed=Speed+50;
  }
}
void voicecontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
    if (value == '^') {
      forward();
    } else if (value == '-') {
      backward();
    } else if (value == '<') {
      L = leftsee();
      servo.write(spoint);
      if (L >= 10 ) {
        left();
        delay(500);
        Stop();
      } else if (L < 10) {
        Stop();
      }
    } else if (value == '>') {
      R = rightsee();
      servo.write(spoint);
      if (R >= 10 ) {
        right();
        delay(500);
        Stop();
      } else if (R < 10) {
        Stop();
      }
    } else if (value == '*') {
      Stop();
    }
  }
}
void human()
{ 
  long duration, Distance;
  
  // Send ultrasonic signal
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  // Receive ultrasonic signal
  duration = pulseIn(Echo, HIGH);
  
  // Calculate distance in cm
  Distance = duration * 0.034 / 2;
  
  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.println(Distance);
  
  // If human detected within a certain range (adjust range according to your need)
  if (Distance > 10 && Distance < 100) {
    // Adjust robot's movement based on human's position
    
    // Move forward if human is straight ahead
    if (Distance >= 30 && Distance <= 70) {
      forward();
    } 
    // Move backward if human is too close
    else if (Distance <= 30) {
      backward();
    } 
    // Turn left if human is detected on the left
    else if (Distance > 70 && Distance <= 100) {
      left();
    } 
    // Turn right if human is detected on the right
    else if (Distance >= 10 && distance < 60) {
      right();
    }
  } 
  // If human is not detected, stop
  else{
    Stop();
  }

}
// Ultrasonic sensor distance reading function
int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}
void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}
int rightsee() {
  servo.write(10);
  delay(800);
  Left = ultrasonic();
  return Left;
}
int leftsee() {
  servo.write(180);
  delay(800);
  Right = ultrasonic();
  return Right;
}
