#include <Wire.h>

const int SW_pin = 26; // digital pin connected to switch output
const int X_pin = 29; // analog pin connected to X output
const int Y_pin = 28; // analog pin connected to Y output

int x_pos = 0;
int y_pos = 0;
byte x = 0;

void setup()
{
  Serial.begin(9600);           // start serial for output
  Wire.begin(); // join i2c bus (address optional for master)
  
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);
  pinMode(SW_pin, INPUT_PULLUP);
}



void loop()
{
  x_pos =  analogRead(X_pin);
  y_pos =  analogRead(Y_pin);
  Serial.println(x_pos);
  Serial.println(y_pos);
  //readJoystick();
  
  if (2048<=x_pos && x_pos<=4096 && 0<=y_pos && y_pos<=2048){
    firstQuadrant();
    Serial.println("1st");
    delay(500);
  }
  else if(0<=x_pos && x_pos<=2048 && 0<=y_pos && y_pos<=2048){
    secondQuadrant();
    Serial.println("2nd");
    delay(500);
  }
  else if(0<=x_pos && x_pos<=2048 && 2048<=y_pos && y_pos<=4096){
    thirdQuadrant();
    Serial.println("3rd");
    delay(500);
  }
  else if(2048<=x_pos && x_pos<=4096 && 2048<=y_pos && y_pos<=4096){
    fourthQuadrant();
    Serial.println("4th");
    delay(500);
  }

  delay(500);
}

void sendString(){
  Wire.beginTransmission(2);  // transmit to device #4
  Wire.write("Hello ");        // sends six bytes
  Wire.endTransmission();     // stop transmitting
}

void firstQuadrant(){
  Wire.beginTransmission(2);  // transmit to device #4
  Wire.write(45);              // sends one byte  
  Wire.endTransmission();     // stop transmitting
}

void secondQuadrant(){
  Wire.beginTransmission(2);  // transmit to device #4
  Wire.write(90);              // sends one byte  
  Wire.endTransmission();     // stop transmitting
}

void thirdQuadrant(){
  Wire.beginTransmission(2);  // transmit to device #4
  Wire.write(135);              // sends one byte  
  Wire.endTransmission();     // stop transmitting
}

void fourthQuadrant(){
  Wire.beginTransmission(2);  // transmit to device #4
  Wire.write(180);              // sends one byte  
  Wire.endTransmission();     // stop transmitting
}

void readJoystick(){
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
}
