#include <Wire.h>                       
#include <LiquidCrystal_I2C.h> 
#include <DHT.h>                         

LiquidCrystal_I2C LCD(0x27,16,2);  
DHT dht(2, DHT11);                          

#define RELAY_IN 3
#define soil A1

int sol;
int minSoil = 512;

int print(int a, int b, String text){
    LCD.setCursor(a, b);
    LCD.print(text);
   
}
void printInfo(int h, int t){
  LCD.setCursor(0, 0);
  LCD.print("Hum:");
  LCD.print(h);

  LCD.setCursor(0, 1);
  LCD.print("Temp:");
  LCD.print(t);
}

void setup() {
   LCD.init();            
   LCD.backlight();  
  
   dht.begin();         
   Serial.begin(9600);
  
   pinMode(RELAY_IN, OUTPUT);
   pinMode(soil, INPUT);
}

void loop() {
   // считываем температуру (t) и влажность (h)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  sol = analogRead(soil);
  Serial.println(sol);
if(sol > minSoil){
  Serial.println("Реле вкл");
  digitalWrite(RELAY_IN, HIGH);
  delay(5000);
}
  digitalWrite(RELAY_IN, LOW);
  // выводим температуру (t) и влажность (h) на жк дисплей
  print(10, 0, "Off");
  printInfo(h, t);
  delay(1000);

  LCD.clear();
  delay(200);
}
