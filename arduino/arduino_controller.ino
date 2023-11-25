#include <Servo.h>

// Define Servo objects for each finger
Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;


void setup() {
  // Setup serial 
  Serial.begin(9600);

  // Attach Servo motors to corresponding pins
  servoThumb.attach(8);
  servoIndex.attach(9);
  servoMiddle.attach(10);
  servoRing.attach(11);
  servoPinky.attach(12);

  
}
void loop() {
    // Receive a message string from the python control script via serial 
    String str = receive(); 

    // Extract servo angles from the message string  
    int servo0_pos = 180 - str.substring(0, 3).toInt();
    int servo1_pos = 180 - str.substring(3, 6).toInt();
    int servo2_pos = 180 - str.substring(6, 9).toInt();
    int servo3_pos = str.substring(9, 12).toInt();
    int servo4_pos = str.substring(12, 15).toInt();
  
    // Drive the servo motors 
    servoThumb.write(servo0_pos);
    servoIndex.write(servo1_pos);
    servoMiddle.write(servo2_pos);
    servoRing.write(servo3_pos);
    servoPinky.write(servo4_pos);

    // Print the message string to serial for debugging
    Serial.print(str);
}

/*
 *  This function receives a string over serial from the python control script
 */
String receive() {

  String str = "";

  // Wait for the start of a message string
  char c = '0';
  while (c != '<') {
    while (Serial.available() <= 0) { /* busy wait*/ }
    c = Serial.read();  
  }

  // Start receiving 
  bool receiving = true; 
  
  while (receiving) {
      while (Serial.available() <= 0) { /* busy wait*/ }
    
      c = Serial.read(); 

      // Stop receiving on end of the message string 
      if (c == '>') {
        receiving = false; 
      }
      else {
        str += c; 
      }
  }
  
  return str;  
}
