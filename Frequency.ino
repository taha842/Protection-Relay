/*
  Analog Input
  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED)  connected to digital pin 13.
  The amount of time the LED will be on and off depends on
  the value obtained by analogRead().

  The circuit:
  Potentiometer attached to analog input 0
  center pin of the potentiometer to the analog pin
  one side pin (either one) to ground
  the other side pin to +5V
  LED anode (long leg) attached to digital output 13
  LED cathode (short leg) attached to ground

  Note: because most Arduinos have a built-in LED attached
  to pin 13 on the board, the LED is optional.


  Created by David Cuartielles
  Modified 16 Jun 2009
  By Tom Igoe

  http://arduino.cc/en/Tutorial/AnalogInput

*/
#include <math.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
#include "WProgram.h"
void setup();
void loop();
LiquidCrystal lcd(3, 4, 8, 9, 10, 11);
#define acosf   acos
int sensorPin = 0;    // select the input pin for the potentiometer
// select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int x = 0;
int i;
int y;
int z;
long a;
int b;
int k = 0;
long c;
int arr[250] ;
unsigned long time;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  time = millis();
  Serial.println(time);

  for (i = 0; i < 251; i = i + 1)
  {
    arr[i] = analogRead(sensorPin);
  }

  time = millis();
  Serial.println(time);

  // Print a message to the LCD.


  //for(i=0;i<251;i=i+1)
  //{
  //Serial.println(arr[i]);
  //}

  float f;


  for (i = 0; i < 251; i = i + 1)
  {
    if (arr[i] == 0 && arr[i + 1] != 0)
    {
      while (arr[i + 1] != 0)
      {
        k = k + 1;
        //Serial.println("k");
        i = i + 1;
      }
      break;
    }

  }
  f = 1000 / (2 * k * 0.112);
  Serial.println(k);
  Serial.println("FREQUENCY MEASURED IS");
  Serial.println(f);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Frequency is :");
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(f);

}

void loop() {

  // read the value from the sensor:

  // turn the ledPin on
  //digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:

  // turn the ledPin off:
  //digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  //delay(sensorValue);
}

int main(void)
{
  init();

  setup();

  for (;;)
    loop();

  return 0;
}


