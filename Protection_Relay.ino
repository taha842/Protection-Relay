/*******Over Current Relay (OCR)*******
   Author @ Engr. Muhammad Taha
   Contact : +92-334-3992626
   *******Projexel**********
*/

#include <Wire.h>                         // Include Wire Library
#include <SPI.h>                          // Include SPI Protocol Library
#include <LiquidCrystal_I2C.h>            // Include LCD Library
#include "EmonLib.h"                      // Include Current Sensor Library                      

EnergyMonitor emon1;                     // Initiliaze Current Sensor
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Initiliaze LCD

float Gen_Current ;                    // Declare Generator Current Variable
float OverCurrent = 6.0;              // Declare Generator OverCurrent Variable (You Can Change Over Current Limit Here)
float CutoffCurrent = 8.0;            // Declare Generator UnderCurrent Variable(You Can Change Short Circuit Limit Here)
float RefCurrent = 0.099;               // Declare Generator Refrence Current Variable ( You Can Chnage Refrence Current Here)

const int RelayPin = 2;                // Declare Relay Pin
bool RelayStatus;                      // Relay Status (High / Low)

void setup()                           // Setup Loop Which Run Only Once When Controller Will Start
{
  SPI.begin();
  lcd.begin(20, 4);                    // Initiliaze LCD Communication
  Serial.begin(9600);                  // Initiliaze Serial Monitor Communication
  emon1.current(1, 16.0);              // Current: input pin, calibration.
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, LOW);
  Get_Current();
  lcd.clear();                        // LCD Clear
  lcd.setCursor(0, 0);                // Set Lcd Cursor (Position)
  lcd.print("   NED UNIVERSITY   ");  // Print This On LCD
  lcd.setCursor(0, 2);                // Set Lcd Cursor (Position)
  lcd.print("Loading.");              // Print This On LCD
  delay(800);
  lcd.setCursor(8, 2);                // Set Lcd Cursor (Position)
  lcd.print(".");                     // Print This On
  delay(800);
  lcd.setCursor(9, 2);                // Set Lcd Cursor (Position)
  lcd.print(".");                     // Print This On
  delay(800);
  lcd.setCursor(10, 2);               // Set Lcd Cursor (Position)
  lcd.print(".");                     // Print This On
  delay(800);
  lcd.setCursor(8, 2);                // Set Lcd Cursor (Position)
  lcd.print(".");                     // Print This On
  lcd.clear();                          // LCD Clear

}

void loop()                             // Loop Which Run in Controller again & again
{
  Get_Current();                        // Call Get Current Function to Measure Current
  lcd.setCursor(0, 0);                  // Set Lcd Cursor (Position)
  lcd.print("   NED UNIVERSITY   ");    // Print This On LCD

  if ( (Gen_Current > RefCurrent ) && (Gen_Current < OverCurrent) && (Gen_Current < CutoffCurrent) ) // Stable condition where current in between Over and Cutoff limits
  {
    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print(Gen_Current);
  }

  else if ((Gen_Current > RefCurrent ) && (Gen_Current > OverCurrent) && (Gen_Current < CutoffCurrent )) //Over current condition
  {
    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print(Gen_Current);
    lcd.setCursor(0, 2);
    lcd.print(" Over Current Fault ");
    delay(2500);
    Get_Current();
    if ((Gen_Current > RefCurrent ) && (Gen_Current > OverCurrent) && (Gen_Current < CutoffCurrent ))
    {
      digitalWrite(RelayPin, HIGH);
      while (1)
      { lcd.setCursor(0, 1);
        lcd.print("Current: ");
        lcd.print(Gen_Current);
        lcd.setCursor(0, 2);
        lcd.print(" Over Current Trip ");
        lcd.setCursor(0, 3);
        lcd.print(" Fault Occur ");
        delay(500);
      }
    }
    lcd.clear();                          // LCD Clear
  }

  else if ((Gen_Current > RefCurrent ) && (Gen_Current > OverCurrent ) && (Gen_Current > CutoffCurrent)) // Short Circuit Current Condition
  {
    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print(Gen_Current);
    lcd.setCursor(0, 2);
    lcd.print(" Short Circuit Fault ");
    delay(2500);
    Get_Current();
    if ((Gen_Current > CutoffCurrent) || (Gen_Current > OverCurrent))
    {
      digitalWrite(RelayPin, HIGH);
      while (1)
      { lcd.setCursor(0, 1);
        lcd.print("Current: ");
        lcd.print(Gen_Current);
        lcd.setCursor(0, 2);
        lcd.print(" Short Circuit Trip ");
        lcd.setCursor(0, 3);
        lcd.print(" Fault Occur ");
        delay(500);
      }
    }
    lcd.clear();                          // LCD Clear
  }
  else if (Gen_Current < RefCurrent )
  {
    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print("0.00");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print("0.00");
  }

  RelayStatus = digitalRead(RelayPin);
  if (RelayStatus == HIGH)
  {
    while (1) { }
  }
}

void Get_Current()  // Current measuring function
{
  double Irms1 = emon1.calcIrms(5588);  // Calculate Irms only
  Gen_Current = Irms1;                 // Store Irms value in Gen_Current Variable
  Serial.print("Current: ");          // Current: print on serial montior
  Serial.println(Irms1, 4);           // Irms Value print on serial montior
}


