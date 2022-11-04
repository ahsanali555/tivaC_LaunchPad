// Motor A, TivaC and L298N connections
int enA = 26;   //ENABLE pin (PD3) for Motor A to provide PWM 
int in1 = 11;   //IN1 pin (PA2) for Motor A for direction
int in2 = 12;   //IN2 pin (PA3) for Motor A for direction
const int SW2 = 17;   //Pin number for Switch SW2
bool direction = true;

void setup() {
  Serial.begin(115200); //Serial initializing for Debugging
  //Specify pinMode for enA, in1 and in2 below
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  
  //Initialize SW2 Switch as Input
  pinMode(SW2, INPUT_PULLUP);  //State for SW2 with pullUp resistor
}

void loop() {
    // Make the motor run clockwise direction
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    //Varying Speed for motor
    zeroP_Speed();
    delay(2000);
    twentyFiveP_Speed();
    delay(2000);
    fiftyP_Speed();
    delay(2000);
    seventyFiveP_Speed();
    delay(2000);
    hundredP_Speed();
    delay(2000);

    //Varying Direction of motor
    //changeDirection();   //Will Update direction depending upon SW2 State
    
    //Varying Speed for motor
//    analogWrite(enA, 0);
//    delay(2000);
//    analogWrite(enA, 64);
//    delay(2000);
//    analogWrite(enA, 128);
//    delay(2000);
//    analogWrite(enA, 192);
//    delay(2000);
//    analogWrite(enA, 255);
//    delay(2000);
}

void tenP_Speed() {
    //Generates PWM of 50Hz with Duty Cycle of 10%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(2000); // High for 2ms, Duty Cycle of 10%
      digitalWrite(enA, LOW);
      delayMicroseconds(18000); // Off for remaining  18ms
  }
}

void zeroP_Speed() {
    //Generates PWM of 50Hz with Duty Cycle of 0%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(0); // High for 0ms, Duty Cycle of 0%
      digitalWrite(enA, LOW);
      delayMicroseconds(20000); // Off for remaining  20ms
  }
}

void twentyFiveP_Speed() {
    //Generates PWM of 50Hz with Duty Cycle of 25%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(5000); // High for 5ms, Duty Cycle of 25%
      digitalWrite(enA, LOW);
      delayMicroseconds(15000); // Off for remaining  15ms
  }
}

void fiftyP_Speed() {
    //Generates PWM of 50Hz with Duty Cycle of 50%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(10000); // High for 10ms, Duty Cycle of 50%
      digitalWrite(enA, LOW);
      delayMicroseconds(10000); // Off for remaining  10ms
  }
}

void seventyFiveP_Speed() {
    //Generates PWM of 50Hz with Duty Cycle of 75%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(15000); // High for 15ms, Duty Cycle of 75%
      digitalWrite(enA, LOW);
      delayMicroseconds(5000); // Off for remaining  5ms
  }
}

void hundredP_Speed() {
    //Generates PWM of 50Hz with Duty Cycle of 100%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(20000); // High for 20ms, Duty Cycle of 100%
      digitalWrite(enA, LOW);
      delayMicroseconds(0); // Off for remaining  0ms
  }
}


void changeDirection(){
    if(digitalRead(SW2) == 0){
      if(direction==true){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        direction=false;
        analogWrite(enA, 128);
        }
      else if(direction==false){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        direction=true;
        analogWrite(enA, 255);
        } 
    }
    delay(1000);  
}
