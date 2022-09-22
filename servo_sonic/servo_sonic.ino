//Uncomment below lines for Task02 and Task03
#include <Servo.h>   //Using built-in servo library with precise PWMs
Servo myservo;       //Creates an object of Servo
 
//Variables for pins and servo position "pos"
int pos = 0;    // variable to store the servo position 
const int echo = 9, Trig = 10;      //Pin connections for HC-SR04
const int Servo_control_pin = 30;   //Pin connection for Servo PWM, equivalent to PF1
const int SW2 = 17;                 //Pin number for Switch SW2

////////////////////////////////////////////////////
//Time Update Variables for Ultrasonic Sensor
long duration, cm;          //To measure pulse width and distance in cm
long distance = 0;          //To return distance of object

////////////////////////////////////////////////////
void setup() 
{ 
  Serial.begin(115200);     //Initialize Serial COM Port with 115200 buad rate
  pinMode(Trig, OUTPUT);    //Trigger is output since it will send 8 pulses at 40KHz from HC-SR04
  pinMode(echo, INPUT);     //Echo is input since it will detect the reflected wave from HC-SR04
  myservo.attach(Servo_control_pin);   //Attaches the servo PWM pin on PF1
  //pinMode(Servo_control_pin, OUTPUT);    //To produce PWM signal at PF1 pin for servo control
  pinMode(SW2, INPUT);      //State for SW2
} 

////////////////////////////////////////////////////
void loop() 
{ 
    //Task 01: PWM Gernation without using delay functions
    /*
    servo_0_Degree();
    delay(1000);
    servo_p90_Degree();
    delay(1000);
    servo_0_Degree();
    delay(1000);
    servo_m90_Degree();
    delay(1000);
    */

    //Task 02: Using <servo.h> library to control angular position
    /*
    if(digitalRead(SW2) == 0){
      for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(5);                        // waits 5ms for the servo to reach the position 
      } 
      
      for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
      {                                
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(5);                        // waits 5ms for the servo to reach the position 
      }
    }
    */
    
    

    //Task 03: Interfacing servo with ultrasonic sensor
    // /*
    Update_Ultra_Sonic(); //Update distance from ultrasonic sensor
    delay(500);
    
    if (cm>=0 and cm<=15){
      myservo.write(45);
      delay(5);
    }
    else if (cm>=15 and cm<=30){
      myservo.write(90);
      delay(5);
    }
    else if (cm>=30 and cm<=45){
      myservo.write(180);
      delay(5);
    }
    else{
      myservo.write(0);
      delay(5);
    }
    // */
} 


////////////////////////////////////////////////////
void servo_0_Degree(){
    //We use delayMicroseconds() instead of delay(ms)... 
    //...since delayMicroseconds() are more precise and give accurate PWM
    
    // Rotates servo to 0 degree, total pulse duration is 20ms
    digitalWrite(Servo_control_pin, HIGH);
    delayMicroseconds(1500); // High for 1.5ms, Duty Cycle of 7.5%
    digitalWrite(Servo_control_pin, LOW);
    delayMicroseconds(18500); // Off for remaining  18.5ms
}

void servo_p90_Degree(){
    // Rotates servo to +90 degree, total pulse duration is 20ms
    digitalWrite(Servo_control_pin, HIGH);
    delayMicroseconds(2000); // High for 2ms, Duty Cycle of 10%
    digitalWrite(Servo_control_pin, LOW);
    delayMicroseconds(18000); // Off for remaining  18ms
}

void servo_m90_Degree(){
    // Rotates servo to -90 degree, total pulse duration is 20ms
    digitalWrite(Servo_control_pin, HIGH);
    delayMicroseconds(1000); // High for 1ms, Duty Cycle of 5%
    digitalWrite(Servo_control_pin, LOW);
    delayMicroseconds(19000); // Off for remaining  19ms
}

////////////////////////////////////////////////////
void Update_Ultra_Sonic()
{
  //Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(echo, HIGH);   // Reads duration (microseconds) for which Echo pin reads HIGH till wave is reflected
  cm = microsecondsToCentimeters(duration); // convert the time into a distance, refer to function below
  
  //Sending through serial port to print on Monitor
  Serial.print("Distance=");
  Serial.print("\t");
  Serial.print(cm); 
  Serial.print(" cm");
  Serial.print("\n");
}

////////////////////////////////////////////////////
long microsecondsToCentimeters(long microseconds)
{
  //Gives the distance equivalent to time taken by pulse, speed of sound 340m/s
distance = 0.034 * microseconds;
return distance / 2;
}
