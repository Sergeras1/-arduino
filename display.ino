#include <Wire.h>                       
#include <LiquidCrystal_I2C.h> 
#include <DHT.h>                         

LiquidCrystal_I2C LCD(0x27,16,2);  
DHT dht(2, DHT11);                          

#define ledPin 13 // порт для подключения светодиода
#define RELAY_IN 3

unsigned long previousMillis = 0;     // Переменная для хранения времени последнего включения реле
const unsigned long interval = 8 * 1000; //2 * 24 * 60 * 60 * 1000; 
// Интервал в 2 дня в миллисекундах
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
   Serial.setTimeout(5);
}

void loop() {
   // считываем температуру (t) и влажность (h)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  unsigned long currentMillis = millis(); // Получаем текущее время
  
  if (currentMillis - previousMillis >= interval) { // Проверяем, прошло ли 2 дня с момента последнего включения реле
    previousMillis = currentMillis; // Обновляем время последнего включения
    digitalWrite(RELAY_IN, HIGH); // Включаем реле
    Serial.println("Реле включено");
    print(10, 0, "On");
    printInfo(h, t);
    delay(5000); // Дополнительная задержка для стабильности

    digitalWrite(RELAY_IN, LOW); // Включаем реле
    Serial.println("Реле выкл");
  
  }
  
  // выводим температуру (t) и влажность (h) на жк дисплей
  print(10, 0, "Off");
  printInfo(h, t);
  delay(1000);

  LCD.clear();
  delay(200);
}
