#include<Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {

  // The begin call takes the width and height. This
  // Should match the number provided to the constructor.
  Serial.begin(9600);
  //Wire.begin(2,0);
  lcd.begin(16,2);
  lcd.init();

  // Turn on the backlight.
  lcd.backlight();

  // Move the cursor characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(1, 0);
  lcd.print("Nikita + ");
  
  delay(1000);

  lcd.setCursor(1, 1);      
  lcd.print("Maharshi");

  delay(2000);
  lcd.clear();

  lcd.print("Forever");
  lcd.setCursor(1, 1);      
  lcd.print("Love");

  
  
}

void loop() {
  
}
