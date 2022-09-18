////////////////////////////////////////////////////
//Ultrasonic Pins Definition, here we specify pin usage for our tivaC Board

const int echo = 9, Trig = 10;  //Pin connections for HC-SR04
const int LED1 = 11;          //Specify Pin for LED1
const int SW2 = 17;
const int SW1 = 31;

////////////////////////////////////////////////////
//Time Update Variables

long duration, cm;                          //To measure pulse width and distance in cm
long distance = 0;                         //To return distance of object
unsigned long LastUpdateMicrosecs = 0;    
unsigned long LastUpdateMillisecs = 0;
unsigned long CurrentMicrosecs = 0;
unsigned long MicrosecsSinceLastUpdate = 0;
float SecondsSinceLastUpdate = 0;


////////////////////////////////////////////////////
//Initializing Pins Function

void setup()
{
  Serial.begin(115200);     //Initialize Serial COM Port with 115200 buad rate
  pinMode(Trig, OUTPUT);    //Trigger is output since it will send 8 pulses at 40KHz from HC-SR04
  pinMode(echo, INPUT);     //Echo is input since it will detect the reflected wave from HC-SR04
  pinMode(LED1, OUTPUT);    //Pin for LED1 should output HIGH(on) or LOW(off)
  pinMode(SW1, INPUT);      //State for SW1
  pinMode(SW2, INPUT);      //State for SW2
}


////////////////////////////////////////////////////
//Main Loop that will keep on running, it is similar to int main()
void loop()
{
    Update_Ultra_Sonic();
    LED_Control();
    delay(200);           //Delay between prints on Serial Monitor
}

////////////////////////////////////////////////////
//Will update ultrasonic sensors through Serial port

void Update_Ultra_Sonic()
{
  //Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  //digitalRead(anypin/switch) //Use this function to read the state of any Pin/Switch i.e. SW1 and SW2

  duration = pulseIn(echo, HIGH);   // Reads duration (microseconds) for which Echo pin reads HIGH till wave is reflected
  cm = microsecondsToCentimeters(duration); // convert the time into a distance, refer to function below
  
  //Sending through serial port to print on Monitor
  Serial.print("Distance=");
  Serial.print("\t");
  Serial.print(cm); 
  Serial.print(" cm");
  Serial.print("\n");
}

void LED_Control(){
  if(digitalRead(SW1) == HIGH){
    digitalWrite(LED1, HIGH);   //Turns on the LED
    delay(200);   //in Milliseconds
    digitalWrite(LED1, LOW);   //Turns on the LED
    }
}

////////////////////////////////////////////////////
//Conversion of microsecond to centimeter
long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.

// Speed of Sound:    340 m/s = 0.034 cm/us
// Use the formula:     distance(cm) = speed(cm/us) * time(us)
// Write distance formula here
distance = 0.034 * microseconds;
// We take half of the distance travelled since its a reflected wave
return distance / 2;
}
