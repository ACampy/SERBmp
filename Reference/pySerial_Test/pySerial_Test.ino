void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // set the baud rate
  Serial.println("Ready"); // print "Ready" once

}

void loop() {
  // put your main code here, to run repeatedly:

  int inByte;
  while (Serial.available() > 0) { // only send data back if data has been sent
     inByte = Serial.read(); // read the incoming data
     Serial.println("1");
  }

  
  if ( inByte)
  {
    Serial.println(inByte); // send the data back in a new line so that it is not all one long line
  }
  else
  {
    Serial.write("we goofed \n");
  }
  delay(100);
}
