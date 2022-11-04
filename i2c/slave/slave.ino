#include <Wire.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Wire.begin(2);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  myservo.write(x);
  Serial.println(x);         // print the integer
}
