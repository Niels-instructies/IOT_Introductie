// here we connect the LED
const int ledPin = ?;

void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure ledPin as output
  pinMode(ledPin, OUTPUT);
}

void loop() {

  serial.println("aan");
  digitalWrite(ledPin, HIGH);

  delay();
    
}
