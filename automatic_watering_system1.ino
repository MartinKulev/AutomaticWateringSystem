#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);

byte customChar[] = {
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000
}; 

void setup()
{
  lcd.init();
  lcd.backlight(); 
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
   
  //photoresistor
  double phValue = analogRead(A2);
  double phPercent = 100 - ((phValue - 49) * 100.00 / 920);  
  lcd.print(phPercent);
  lcd.print("%");
  lcd.setCursor(7, 0);
  lcd.print("|| ");
    
  //tmp sensor
  int tmpValue = analogRead(A1);
  double voltage = tmpValue / 1023.0 * 5000;
  double celsius = (voltage - 500) * 0.1;
  lcd.print(celsius);
  lcd.createChar(0, customChar);
  lcd.home();
  lcd.setCursor(14, 0);
  lcd.write(0);
  lcd.print("C");
  
  //soil mosture sensor
  int moistureValue = analogRead(A0);
  double moisturePercentage = (moistureValue /539.00) * 100;
  lcd.setCursor(0, 1);
  lcd.print(moisturePercentage);
  lcd.print("%");
  lcd.setCursor(7, 1);
  lcd.print("|| ");
  
  double litresWateringFormula = 99 - moisturePercentage;
  lcd.print(litresWateringFormula);
  lcd.print("L");
  delay(1000);
  
  //dc motor
  if(phValue < 800)
  {    
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    delay(litresWateringFormula * 100);
    digitalWrite(10, LOW);
  }
  delay(5000);
  lcd.clear(); 
}