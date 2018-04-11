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
Serial.println("xxxxxxxx") ;
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

/*
   sends the robot left
*/
void goLeft() {
  leftServo.write(90 - speed);
  rightServo.write(90 - speed);
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serbSetup();

}

void loop() {

  goRight() ;
  delay(2050) ;
  goStop() ;
  delay(200) ;
/*
  int left, middle, right;

  left = digitalRead(8);   
  middle = digitalRead(4); 
  right = digitalRead(2); 
  
   if((left == 0) && middle && right) 
   {
    goLeft(); 
    delay(2);                                    
   }    
  else if(left && middle && (right == 0))
   {
    goRight();
    delay(2);
   }
   else if(left && (middle == 0) && right)
   {
      goForward(); 
      delay(2);
   }
   else if((left == 0) && (middle == 0) && (right  == 0))
   {
      goStop(); 
      delay(2);
   }
  else if((left == 1) && (middle == 1) && (right  == 1))
   {
      goStop(); 
      delay(2);
   }
  else
  {
    goForward(); 
    delay(2);
  } 
*/
//delay(200) ;

}


