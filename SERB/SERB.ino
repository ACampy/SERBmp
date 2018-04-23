/*
  Parses through an array containing a list of movements for the robot to complete while following lines
  that allow it to travel between nodes. Modeled after the following 8 node graph:
           A
          /|\ 
         / | \
        /  E  \
       D-H   F-B
        \  G  /
         \ | /
          \|/ 
           C

  Code for Serb Simple Routines from: https://cdn.instructables.com/ORIG/FKK/R8UT/FNNJYJIS/FKKR8UTFNNJYJIS.txt
  Code for Line Following provided by: Gregory Reis
*/
//---------------------------------------------------------------------------------
//ARDUINO CONTROLLED SERVO ROBOT (SERB) "PREAMBLE"
#include <Servo.h>

#define LEFTSERVOPIN  10            //Left Wheel
#define RIGHTSERVOPIN  9            //Right Wheel

Servo leftServo;
Servo rightServo;

int speed = 3;                      //Sets the speed of the robot (both servos) a percentage between 0 and 100
//------------------------------------------------------------------------------------------------------------
//ARDUINO CONTROLLED SERVO ROBOT (SERB) "ROUTINES"

/*Sets up your arduino to address your SERB using the included routines*/
void serbSetup(){
  setSpeed(speed);
  pinMode(LEFTSERVOPIN, OUTPUT);     //sets the left servo signal pin to output
  pinMode(RIGHTSERVOPIN, OUTPUT);    //sets the right servo signal pin to output
  leftServo.attach(LEFTSERVOPIN);    //attaches left servo
  rightServo.attach(RIGHTSERVOPIN);  //attaches right servo
  goStop();                          //stops the servos incase the internal timers are a little off
}

/*Sends the Robot Forward*/
void goForward(){
  leftServo.write(90 + speed);
  rightServo.write(90 - speed);
  //Serial.println("xxxxxxxx");
  Serial.flush();
}

/*Sends the Robot Backwards*/
void goBackward(){
  leftServo.write(90 - speed);
  rightServo.write(90 + speed);
}

/*Sends the Robot Right*/
void goRight(){
  leftServo.write(90 + speed);
  rightServo.write(90 + speed);
}

/*Robot Right in Reverse*/
void goRevRight(){
  leftServo.write(87 + speed);
  rightServo.write(90 + speed);
}

/*Sends the robot left*/
void goLeft(){
  leftServo.write(90 - speed);
  rightServo.write(90 - speed);
}
/*Robot Left in Reverse*/
void goRevLeft(){
  leftServo.write(90 + speed);
  rightServo.write(87 + speed);
}

/*Stops the Robot*/
void goStop(){
  leftServo.write(90);
  rightServo.write(90);
}
//------------------------------------------------------------------------------------------------------------
//SERVO ROBOT (SERB) MOVEMENT

/*Sets the speed of the robot between 0-(stopped) and 100-(full speed)*/
void setSpeed(int newSpeed){
  if (newSpeed >= 100){   //if speed is greater than 100 make it 100
    newSpeed = 100;
  }
  if (newSpeed <= 0){     //if speed is less than 0 make it 0
    newSpeed = 0;         
  }
  speed = newSpeed * 0.9; //scales the speed to be between 0 and 90
}

//Global Variables
int left, middle, right;  //IR Sensor Variables
int command, readySig;
int count = 0;

void setup(){
  Serial.begin(9600);
  serbSetup();

  command = 0;            //Determines what movements to do (from python code)
  readySig = 1;           //Signals to python that it can recieve next task
}

void loop(){
  //Reading IR Sensors 
  left = digitalRead(8);
  middle = digitalRead(4);
  right = digitalRead(2);

  //*****Array of Movement Commands for E -> C and E -> H*****
  int q [] = {2, 0, 3, 1, 4, 0, 3, 1, 4, 0 };   //E -> C
  //int q [] = {2, 0, 4, 1, 3, 0, 1, 0};        //E -> H

  //*************NON-WORKING PYSERIAL*************************
  /*
  Serial.println(command);
  if (Serial.available()){ // only send data back if data has been sent
      Serial.println("I'm ready");
      //Serial.println(command);
      command = Serial.read(); // read the incoming data
      //Serial.println(command);
  }
  */
  //***************GET NEXT COMMAND WHEN READY****************
  if (readySig == 1){
    command = q[count];
  }
  //********************WAIT FOR COMMAND**********************
  if (command == 0){
    goStop();
    readySig = 1;
    count++;
    Serial.println("Stop");
  }
  //**********************FOLLOW LINE*************************
  else if (command == 1){
    readySig = 0;
    Serial.println("Forward");

    if (left && (middle == 0) && (right == 0)){
      goLeft();
      delay(2);
    }
    else if ((left == 0) && (middle == 0) && right){
      goRight();
      delay(2);
    }
    else if ((left == 0) && middle && (right == 0)){
      goForward();
      delay(4);
    }
    else if ((left == 0) && (middle == 0) && (right  == 0)){
      goForward();
      delay(2);
    }
    else if ((left == 1) && (middle == 1) && (right  == 1)){
      goStop();
      delay(2);
      command = 0;
    }
    else{
      goForward();
      delay(2);
    }
  }
  //******************REVERSE FOLLOW LINE*******************
  else if (command == 2){
    readySig = 0;
    Serial.println("Back");

    if (left && (middle == 0) && (right == 0)){
      goRevRight();
      delay(2);
    }
    else if ((left == 0) && (middle == 0) && right){
      goRevLeft();
      delay(2);
    }
    else if ((left == 0) && middle && (right == 0)){
      goBackward();
      delay(2);
    }
    else if ((left == 0) && (middle == 0) && (right  == 0)){
      goBackward();
      delay(2);
    }
    else if ((left == 1) && (middle == 1) && (right  == 1)){
      goStop();
      delay(2);
      command = 0;
    }
    else{
      goBackward();
      delay(2);
    }
  }
  //***********************90 DEGREE TURN LEFT***************
  else if (command == 3){
    readySig = 0;
    Serial.println("Left");
    goLeft();
    delay (1900);
    command = 0;
  }
  //***********************90 DEGREE TURN RIGHT**************
  else if (command == 4){
    readySig = 0;
    Serial.println("Right");
    goRight();
    delay (1900);
    command = 0;
  }
  //***********************FAIL SAFE*************************
  else{
    goStop();
    Serial.println("Fail Safe");
    command = 0;
  }
} //End file
