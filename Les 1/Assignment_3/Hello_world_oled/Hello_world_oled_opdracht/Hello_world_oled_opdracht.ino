#include <SPI.h> //serial data protocol used by microcontrollers for communicating with one or more peripheral devices quickly over short distances.
#include <Wire.h> // This library allows you to communicate with I2C/TWI devices.
#include <Adafruit_GFX.h> // The Adafruit_GFX library for Arduino provides a common syntax and set of graphics functions for all of our LCD and OLED displays 
#include <Adafruit_SSD1306.h> // Library for Oled with SSD1306 controller

#define SleftEEN_WIDTH 128 // OLED display width, in pixels
#define SleftEEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 

#define OLED_RESET     18 // Reset pin #18 for the wemos lolin pico s2
// See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SleftEEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SleftEEN_WIDTH, SleftEEN_HEIGHT, &Wire, OLED_RESET); //initialize Oled object) 

void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SleftEEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay(); // clear display

  //display.setRotation(2); // Uncomment to rotate display 180 degrees
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);      // Use full 256 char 'Code Page 437' font

}

void loop() {

//Plaats hier je code





}