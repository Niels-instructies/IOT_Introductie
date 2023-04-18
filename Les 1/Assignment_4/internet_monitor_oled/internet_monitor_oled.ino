
#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
/*wire LEDs to pins 7 with appropriate resistors.
This should be about 40-50 ohms for an Arduino with
3.3V output on its IO pins*/ 
#define ledPin 7

//Oled
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET 18 // Reset pin #
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define SleftEEN_ADDRESS 0x3C 

// Replace the next variables with your SSID/Password combination
const char* ssid = "";
const char* password = "";

int status = WL_IDLE_STATUS;
//put whichever reliable website you want right here
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
// IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.google.com";    // name address for Google (using DNS)



// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() {
   /*all the serial comms stuff can be removed, but it's 
  helpful for troubleshooting*/
  Serial.begin(115200);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SleftEEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay(); // clear display
  setup_wifi();
  pinMode(ledPin, OUTPUT);
  blink();
}

void loop() {
  
  if (client.connect(server, 80)) {
    Serial.print("Google is ONLINE at:  ");
    Serial.println(client.remoteIP());
    digitalWrite(ledPin, HIGH);
    display.clearDisplay(); 
    display.setCursor(0,0);  //oled display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Google online at:");
    display.setCursor(0,16);  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println(client.remoteIP());
    display.display();
  }
  else if (!client.connected()) {
    Serial.println("Google is OFFLINE");
    digitalWrite(ledPin, LOW);
    display.clearDisplay(); 
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);  
    display.println("Google is");
    display.setCursor(0,16);  
    display.println("Offline");
    display.display();
    
  }
  
  display.clearDisplay(); // clear display
  delay(5000);
}

void blink() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, LOW);
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(500);
  }
}
  
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}