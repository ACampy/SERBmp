//---------------------------------------------------------------------------------
// START OF ARDUINO CONTROLLED SERVO ROBOT (SERB) "PREAMBLE"
#include <Servo.h>

#define LEFTSERVOPIN  10
#define RIGHTSERVOPIN  9

Servo leftServo;
Servo rightServo;

int speed = 3; //sets the speed of the robot (both servos) a percentage between 0 and 100

// END OF ARDUINO CONTROLLED SERVO ROBOT (SERB) PREAMBLE
//---------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//START OF ARDUINO CONTROLLED SERVO ROBOT (SERB) "ROUTINES"

/*
   sets up your arduino to address your SERB using the included routines
*/

void serbSetup() {
  setSpeed(speed);
  pinMode(LEFTSERVOPIN, OUTPUT);     //sets the left servo signal pin to output
  pinMode(RIGHTSERVOPIN, OUTPUT);    //sets the right servo signal pin to output
  leftServo.attach(LEFTSERVOPIN);    //attaches left servo
  rightServo.attach(RIGHTSERVOPIN);  //attaches right servo
  goStop();                          //stops the servos incase the internal timers are a little off
}




/*
   sends the robot forwards
*/
void goForward() {
  leftServo.write(90 + speed);
  rightServo.write(90 - speed);
//Serial.println("xxxxxxxx") ;
Serial.flush() ;
}

/*
   sends the robot backwards
*/
void goBackward() {
  leftServo.write(90 - speed);
  rightServo.write(90 + speed);
}

/*
   sends the robot right
*/
void goRight() {
  leftServo.write(90 + speed);
  rightServo.write(90 + speed);
}

  //Robot right in reverse
void goRevRight() {
  leftServo.write(87 + speed);
  rightServo.write(90 + speed);
}

/*
   sends the robot left
*/
void goLeft() {
  leftServo.write(90 - speed);
  rightServo.write(90 - speed);
}

  //Robot left in reverse 
void goRevLeft() {
  leftServo.write(90 - speed);
  rightServo.write(87 - speed);
}

/*
   stops the robot
*/
void goStop() {
  leftServo.write(90);
  rightServo.write(90);

  
}
//END OF ARDUINO CONTROLLED SERVO ROBOT (SERB) ROUTINES
//------------------------------------------------------------------------------------------------------------

/*
   sets the speed of the robot between 0-(stopped) and 100-(full speed)
   NOTE: speed will not change the current speed you must change speed
   then call one of the go methods before changes occur.
*/
void setSpeed(int newSpeed) {
  if (newSpeed >= 100) {
    newSpeed = 100; //if speed is greater than 100 make it 100
  }
  if (newSpeed <= 0) {
    newSpeed = 0; //if speed is less than 0 make it 0
  }
  speed = newSpeed * 0.9;                   //scales the speed to be between 0 and 90
}
//Global Variables
int i = 0;
int j = 10;
int left, middle, right; //IR Sesor Variables
int command, readySig;
int count = 0;



void setup() {
  // put your setup code here, to run once:
// put your setup code here, to run once:
  Serial.begin(9600);
  serbSetup();


}

void loop() {
  // put your main code here, to run repeatedly:
  left = digitalRead(8);   
  middle = digitalRead(4); 
  right = digitalRead(2);


if( count == 0){
  goLeft();
  delay (1900);
  count = 1;
}
else
  goStop();
  
}
