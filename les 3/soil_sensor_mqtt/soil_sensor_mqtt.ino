#include <SPI.h> // Libraries for the OLED display
#include <Wire.h> // i2c
#include <Adafruit_SSD1306.h> // oled library
#include <Adafruit_GFX.h> // oled graphics library
#include <WiFi.h> // wifi library
#include <PubSubClient.h> // mqtt library
#include <ArduinoJson.h> // json library

// Replace the next variables with your SSID/Password combination
const char* ssid = "ssid"; // wifi name
const char* password = "your password"; // wifi password 
WiFiClient espClient; // client object 

// MQTT setup 
PubSubClient client(espClient); // client object
const char* mqtt_server = "mqtt.eclipseprojects.io"; // Replace with your MQTT broker IP address
const char* mqtt_topic = "HAN/TBK/Plantmonitor/"; //MQTT topic
const char* client_name = "Sensor_2"; //MQTT client device name

 // Oled setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET 18 // Reset pin # ESP32-s2 Pico
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Oled object
#define SleftEEN_ADDRESS 0x3C  // i2c address
 
// Sensor setup
const int AirValue = 8080;   //Air calibration
const int WaterValue = 3000;  //Water calibration
const int SensorPin = 7;
int soilMoistureValue = 0;
int soilmoisturepercent=0;
 
 // timing vaiables (used to only publish to mqtt if interval has passed)
unsigned long lastTime = 0;
unsigned long interval = 5000; //mqtt interval

 
void setup() {
  Serial.begin(115200); // open serial port
  //Display setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, SleftEEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay(); // clear display

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT broker
  client.setServer(mqtt_server, 1883);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect(client_name)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
 
void loop() {

unsigned long currentTime = millis(); // timer
soilMoistureValue = analogRead(SensorPin);  //put Sensor into soil
Serial.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100); // map sensor values to human vlaues

if(soilmoisturepercent >=0 && soilmoisturepercent <= 100)
{
  Serial.print(soilmoisturepercent);
  Serial.println("%");
  
  display.clearDisplay();

  display.setCursor(20,0);  //oled display cursor position
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Soil Moisture");
  
  display.setCursor(64,24);  //oled display cursor position
  display.setTextSize(1);
  display.println(soilmoisturepercent);
  display.setCursor(70,24);
  display.setTextSize(1);
  display.println(" %");
  display.display(); // this displays the actual text
  delay(250);
}

// This code pubishes the code over MQTT, but only if a 5 second interval has passed. This is non-blocking instead of using 'delay'  
if (currentTime - lastTime >= interval) {
  lastTime = currentTime;

  // Create JSON object
  StaticJsonDocument<200> doc;
  doc["moisture"] = soilmoisturepercent;
  doc["device_ID"] = client_name;
    
  // Serialize JSON object to string
  char jsonBuffer[200];
  serializeJson(doc, jsonBuffer);

  // Publish JSON string to MQTT broker
  char s [80];
  strcpy(s, mqtt_topic);
  strcat(s, client_name);
  client.publish(s, jsonBuffer);
  delay(250);
  }

}