#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
// LiquidCrystal_I2C lcd(0x27, 20, 4);

void initLCD(){
  lcd.init();
  lcd.noBacklight();
  //lcd.setCursor(0, 0);
  //lcd.print("Calibrating...");
}

void turnLCDBacklight(bool open){
  if(open)
    lcd.backlight();
  else
    lcd.noBacklight();
}

void clearLCD(){
  lcd.clear();
}

void setLCDText(String text, int x, int y) {
  lcd.setCursor(x, y);
  lcd.print(text);
}
void setLCDText(double value, int x, int y) {
  lcd.setCursor(x, y);
  lcd.print(value);
}
void setLCDText(float value, int x, int y) {
  lcd.setCursor(x, y);
  lcd.print(value);
}
void setLCDText(int value, int x, int y) {
  lcd.setCursor(x, y);
  lcd.print(value);
}
void setLCDText(char text, int x, int y) {
  lcd.setCursor(x, y);
  lcd.print(text);
}