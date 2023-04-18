#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET 18 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define SleftEEN_ADDRESS 0x3C 
 
const int AirValue = 8080;   //you need to replace this value with Value_1
const int WaterValue = 3000;  //you need to replace this value with Value_2
const int SensorPin = 7;
int soilMoistureValue = 0;
int soilmoisturepercent=0;
 
 
void setup() {
  Serial.begin(115200); // open serial port
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SleftEEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay(); // clear display
}
 
void loop() {
soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
Serial.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
if(soilmoisturepercent > 100)
{
  Serial.println("100 %");
  
  display.setCursor(20,0);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Soil Moisture");
  display.setCursor(20,16);  
  
  display.setCursor(30,24);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("100 %");
  display.display();
  
  delay(250);
  display.clearDisplay();
}
else if(soilmoisturepercent <0)
{
  Serial.println("0 %");
  
  display.setCursor(20,0);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Soil Moisture");
  display.setCursor(20,16);  
  
  display.setCursor(30,24);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("0 %");
  display.display();
 
  delay(250);
  display.clearDisplay();
}
else if(soilmoisturepercent >=0 && soilmoisturepercent <= 100)
{
  Serial.print(soilmoisturepercent);
  Serial.println("%");
  
  display.setCursor(20,0);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Soil Moisture");
  display.setCursor(20,16);  
  
  
  display.setCursor(64,24);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent);
  display.setCursor(70,24);
  display.setTextSize(1);
  display.println(" %");
  display.display();
 
  delay(250);
  display.clearDisplay();
}  
}