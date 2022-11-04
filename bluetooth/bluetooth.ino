#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

//define the RGB pind
const int red = 30;
const int green = 39;
const int blue = 40;

int colorDetect=0;
char received;
 
void setup()  { 
  Serial.begin(9600);     //Start the serial comunication for the bluetooth module
  pinMode(red, OUTPUT);   //Red color pwm pin defined as output
  pinMode(green, OUTPUT); //Green color pwm pin defined as output
  pinMode(blue, OUTPUT);  //Blue color pwm pin defined as output
  
  //Give first value of the PWM 0, we start with the RGB LEDs off
  analogWrite(red,0);
  analogWrite(green,0);
  analogWrite(blue,0);

  myservo.attach(26);
 }
 
void loop()  { 
  if(Serial.available()>0){
    // read the bluetoot data and store it
    colorDetect = Serial.read();
    char Rec = char(colorDetect);
    if (Rec != '0')
    {
    Serial.println(Rec); //This is to visualise the received character on the serial monitor
    }  
  }
  chooseColor(colorDetect);
}



void chooseColor(char color){
  //LEDs off
  if (color == 'n')
  {
    analogWrite(red,0);
    analogWrite(green,0);
    analogWrite(blue,0);
    myservo.write(10);
    Serial.println("LED is OFF");
  }
  //White
  if (color == 'w')
  {
    analogWrite(red,255);
    analogWrite(green,255);
    analogWrite(blue,255);
    myservo.write(20);
    Serial.println("LED is ON");
  }
  //Red
  if (color == 'r')
  {
    analogWrite(red,255);
    analogWrite(green,0);
    analogWrite(blue,0);
    myservo.write(30);
  }
  //Green
  if (color == 'g')
  {
    analogWrite(red,0);
    analogWrite(green,255);
    analogWrite(blue,0);
    myservo.write(40);
  }
  //Blue
  if (color == 'b')
  {
    analogWrite(red,0);
    analogWrite(green,0);
    analogWrite(blue,255);
    myservo.write(50);
  }
  //Orange
  if (color == 'o')
  {
    analogWrite(red,255);
    analogWrite(green,153);
    analogWrite(blue,0);
    myservo.write(60);
  }
  //Violet
  if (color == 'v')
  {
    analogWrite(red,102);
    analogWrite(green,0);
    analogWrite(blue,153);
    myservo.write(70);
  }
  //Cyan
  if (color == 'c')
  {
    analogWrite(red,0);
    analogWrite(green,255);
    analogWrite(blue,255);
    myservo.write(80);
  }
  //Yellow 
  if (color == 'y')
  {
    analogWrite(red,255);
    analogWrite(green,204);
    analogWrite(blue,0);
    myservo.write(90);
  }
}
