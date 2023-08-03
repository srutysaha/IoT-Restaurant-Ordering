// include the library code:
#include <LiquidCrystal.h>

#include <RH_ASK.h>

#include <SPI.h> // Not actualy used but needed to compile

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
RH_ASK driver;

#define buzzer 2

void setup() {
  // set up the LCD's number of columns and rows:
  
   //Serial.begin(9600);  // Debugging only

    pinMode(buzzer, OUTPUT);
    lcd.begin(16, 2);
  // Print a message to the LCD.
  if (!driver.init())

         Serial.println("init failed");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
   uint8_t buf[17];

    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking

    {

      int i;

      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      Serial.print("Message: ");
      Serial.println((char*)buf);
      lcd.setCursor(0,0);
      lcd.print("T1:");
      lcd.print((char*)buf);               
    }
}
