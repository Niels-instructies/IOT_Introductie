
#include <WiFi.h>

/*wire LEDs to pins 7 with appropriate resistors.
This should be about 40-50 ohms for an Arduino with
3.3V output on its IO pins*/ 
#define ledPin 7

// Replace the next variables with your SSID/Password combination
const char* ssid = "ssid";
const char* password = "password";

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
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  setup_wifi();
  pinMode(ledPin, OUTPUT);
  blink();
}

void loop() {
  
  if (client.connect(server, 80)) {
    Serial.print("Google is ONLINE at:  ");
    Serial.println(client.remoteIP());
    digitalWrite(ledPin, HIGH);
  }
  else if (!client.connected()) {
    Serial.println("Google is OFFLINE");
    digitalWrite(ledPin, LOW);
  }

  
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