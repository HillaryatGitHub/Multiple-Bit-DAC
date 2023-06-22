#define MAX_4_BIT_NUM     15
#define MAX_6_BIT_NUM     63
#define MAX_8_BIT_NUM     255
#define MAX_10_BIT_NUM    1023
#define MAX_12_BIT_NUM    4095
#define POINTS 256 //number of points in a sine wave

int valSin; //sine wave is expressed in integer
int sampling_interval;
int upper_4_BIT = 4000; //upper limit is used to better serial plot result
int upper_6_BIT = 16000;
//upper_8_BIT = 64000; middle = 32000
//upper_10_BIT = 256000; middle = 128000
//upper_12_BIT = 1024000; middle = 512000

void setup() {
Serial.begin(9600);
DDRD = B11111111; // Port D at Arduino Uno (pin 0-7) --> 0 = INPUT & 1 = OUTPUT
DDRB = B001111; // Port B at Arduino Uno (pin 8-11)  --> "OO" means pin 12 & 11 is unused
}

void loop() {
for ( int i = 0; i < POINTS; i++) { //looping the value of i from 0 to 255 points of sine wave
  
  float x = (float)i / POINTS * 2 * PI; //x goes from the number of points & calculated with 360 degrees/cycle
  valSin = ((sin(x)+1)* MAX_6_BIT_NUM)/2;
  
  PORTD = valSin;
  PORTB = valSin >> 8; // Port B starts at 8 (shifting 8 steps to the right)

Serial.print(0); Serial.print(" ");
Serial.print(upper_6_BIT/2); Serial.print(" ");
Serial.print(upper_6_BIT); Serial.print(" ");

Serial.print(valSin/4); 
Serial.println(analogRead(A0));

//haven't figured out how to adjust the frequency ༼ つ ◕_◕ ༽つ  Feel free to contribute & update so we can grow together!
sampling_interval = 1000000/(40000*POINTS); //100 represents frequency & 1000000 compensates delay in microseconds
delayMicroseconds(sampling_interval); //set delay for analog value
  }
}
