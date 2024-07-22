#include <math.h> 

//General Analogue Read variables
const int analogPin = A5;  // Analog input pin for PT100
int analogValue = 0;       //D_out Value for ADC

//Calibration Function 2 Variables
float theta_C = 0.0;    //Output Temperature in Celsius
float V_FR = 5.0;  //Reference Temperature or V_CC from Arduino
float D_out = 0.0;  //Analogue value read 0-1023
float S = -1.54;     //Sensitivity of PT100 = -1.54 mV/C

//Calibration Function 5 Variables
float V_int = 1.1;  //Internal reference of 1.1V for Arduino
float V_S = 5.0; //Supply Voltage from Arduino
float V_q = V_S/1024; //Resolution of ADC
float R_0 = 100; //ohms
float R_F = 1000; //ohms
float A = 3.9083*pow(10,-3);
float B = -5.775*pow(10,-7);

float V_F = 0; //Voltage appearing on R_F (will change)
float R_theta = 0; //ohms (will change)

void setup() {
  Serial.begin(9600);     // Start serial communication at 9600 bps
  pinMode(analogPin, INPUT); // configure Q0.1 as a OUTPUT
  //analogReference(INTERNAL); //

  //For Part 01 Uncomment
  //
  ADMUX &= 0x30;    // clear ref and mux bits
  ADMUX |= 0x40;    // ADC internal reference: 0x40 -> AVcc; 0xC0 -> 1.1 V
  ADMUX |= 0x00;    // select measured channel
  //    ADMUX |= 0x20;    // Left adjust ADC result
  //
  ADCSRA &=0x00;    // clear ADCSRA register
  ADCSRA |=0x07;    // prescaler = 2^n
  ADCSRA |= 0x20;   // ADC auto trigger enabled (free-running mode)
  ADCSRA |= 0x08;   // Enable ADC interrupt
  ADCSRA |= 0x80;   // Enable ADC
  delay(1000);
  ADCSRA |= 0x40;   // Start ADC conversion
}

void loop() {
  // Read the analog value
  analogValue = analogRead(analogPin);

  //Calibration Function for part 03
  D_out = analogValue;
  theta_C=(-A/(2*B)) - sqrt( ((A*A)/(4*(B*B))) - ((1/(R_0*B))*(R_0+R_F-(1024*R_F)/(D_out))) );   //

  //Calibration Function for part 04
  //

  //Send the analog value to the PC Serial Monitor
  Serial.print("D_out Value is: ");
  Serial.println(analogValue);

  Serial.print("Equivalent Temperature is: ");
  Serial.print(theta_C);
  Serial.print(" C ");

  delay(1000);  // Wait for a second (adjust as needed)
}
