
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

#include "DHT.h"

#define DHTPIN 2     

#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
void setup() {
  Serial.begin(9600);
  
  lcd.begin(16,2);
  dht.begin();
}

void loop() {
  
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  

  int f = (t * 9.0)/ 5.0 + 32.0;

    
  lcd.setCursor(0, 0);
 
   
  lcd.print("P1nesap IoT");
  lcd.setCursor(0,1);
  lcd.print("Weather Monitor");
  delay(5000);
  lcd.clear();
  
 
  

   lcd.print("Temp: ");
     lcd.print(f);
     lcd.print("F  ");
     lcd.print(t);
     lcd.print("C");
     
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
    delay(5000);
    lcd.clear();
    
  lcd.setCursor(0,0);
  if ((f) >= 85 && (h) >= 51)  {
    lcd.print("Hot and humid...");
    lcd.setCursor(0,1);
    lcd.print("Drink water.");
  }
  else if ((f) <= 85 && (f) >= 64 && (h) <= 51) {
    lcd.print("Perfect!");
    lcd.setCursor(0,1);
    lcd.print("Warm and dry.");
  }
  
  else if ((f) <= 85 && (f) >= 64 && (h) >= 51) {
    lcd.print("Warm and moist,");
    lcd.setCursor(0,1);
    lcd.print("Sounds yummy.");
  }
  else if ((f) >= 50 && (f) <= 64  && (h) >= 51) {
    lcd.print("Cool and damp...");
    lcd.setCursor(0,1);
    lcd.print("Raincoat?");
  }
  
  else if ((f) >= 50 && (f) <= 64 && (h) <= 51) {
    lcd.print("Cool and dry.");
    lcd.setCursor(0,1);
    lcd.print("Wear a sweater.");
  }
  else if ((f) >= 33 && (f) <= 50 && (h) <= 51) {
    lcd.print("Cool and dry,");
    lcd.setCursor(0,1);
    lcd.print("On the brisk side.");
  }
  else if ((f) >= 33 && (f) <= 50 && (h) >= 51) {
    lcd.print("Raw weather...");
    lcd.setCursor(0,1);
    lcd.print("Read a book.");
  }
  
  else if ((f) >= 17 && (f) <= 33 && (h) <= 51) {
    lcd.print("Ah, winter cold");
    lcd.setCursor(0,1);
    lcd.print("Dress in layers.");
  }
  else if ((f) < 17 ) {
    lcd.print("OK, now it's");
    lcd.setCursor(0,1);
    lcd.print("REALLY cold!");
  }
 
  else {
    lcd.print("Alert: alien");
    lcd.setCursor(0,1);
    lcd.print("atmosphere!");
  }
  delay(5000);
  lcd.clear();
}
