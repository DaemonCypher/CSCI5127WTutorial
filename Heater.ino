

#include <LiquidCrystal.h>                  //the liquid crystal library contains commands for printing to the display
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);    // tell the RedBoard what pins are connected to the display
#include <Servo.h>          //include the servo library


float voltage = 0;                          //the voltage measured from the TMP36
float degreesC = 0;                         //the temperature in Celsius, calculated from the voltage
float degreesF = 0;                         //the temperature in Fahrenheit, calculated from the voltage
Servo left;              //create a servo object
Servo right;              //create a servo object


void setup() {

  lcd.begin(16, 2);                         //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                              //clear the display
  left.attach(6);                           //tell the servo object that its servo is plugged into pin 6
  right.attach(5);                          //tell the servo object that its servo is plugged into pin 6

}

void loop() {

  voltage = analogRead(A0) * 0.004882813;   //convert the analog reading, which varies from 0 to 1023, back to a voltage value from 0-5 volts
  degreesC = (voltage - 0.5) * 100.0;       //convert the voltage to a temperature in degrees Celsius
  degreesF = degreesC * (9.0 / 5.0) + 32.0; //convert the voltage to a temperature in degrees Fahrenheit

  lcd.clear();                              //clear the LCD

  lcd.setCursor(0, 0);                      //set the cursor to the top left position
  lcd.print("Degrees C: ");                 //print a label for the data
  lcd.print(degreesC);                      //print the degrees Celsius

  lcd.setCursor(0, 1);                      //set the cursor to the lower left position
  lcd.print("Degrees F: ");                 //Print a label for the data
  lcd.print(degreesF);                      //print the degrees Fahrenheit

  delay(10000);                              //delay for 1 second between each reading (this makes the display less noisy)

if (degreesF > 78) {
    left.write(160);                        // move the left servo to 160 degrees
    delay(750);                             //delay for .75 second to allow the servo arms to move out of the way
    right.write(10);                        // move the right servo to 10 degrees
  } else if (degreesF < 60) {
    left.write(10);                         // move the left servo to 10 degrees
    delay(750);                             //delay for .75 second to allow the servo arms to move out of the way
    right.write(160);                       // move the right servo to 160 degrees
  } else {
    left.write(90);                         // reset both servos to a neutral position (90 degrees)
    delay(750);                             //delay for .75 second to allow the servo arms to move out of the way
    right.write(90);
  }
}

