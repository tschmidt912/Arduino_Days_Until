// Days Until
// A quick program to display the days until an event on a 8 character 7 segment display

// Coded by Tim Schmidt - 12/13/2022

/*
  Hardware
  Arduino Pro Micro
  MH-Real-Time Clock Modules-2
  MAX7219 8 character 7 segement display

  Libraries
  LEDControl      ->  https://www.arduinolibraries.info/libraries/led-control
  Virtuabotix RTC ->  https://drive.google.com/file/d/1GDuLWUANun5toL-XsEaFfaw2tv0mvhjB/view
    
*/

/*
  Pin Connections
  Arduino   MAX7219
  5V        VCC
  GND       GND
  D7        DIN
  D8        CS       
  D10       CLK
*/

#include "LedControl.h"
#include "virtuabotixRTC.h"

// defines for 7 seg
#define DIN 7
#define CLK 10
#define CS 8

// defines for RTC
#define CLK_R 15
#define DAT   14
#define RST   16

LedControl led = LedControl(DIN, CLK, CS, 1);  // 1 -> 1 8 character module
virtuabotixRTC clock(CLK_R, DAT, RST); 

void LED_setup() {
  led.shutdown(0, false);  // wake up the 0th module
  led.setIntensity(0, 8);  // set moderate intensity (max 15);
  led.clearDisplay(0);     // clear the 0th display
}

void clock_setup(){
  clock.setDS1302Time(0, 19, 0, 3, 14, 12, 2022);
}

// display all characters and justify appropriately
void display_number(unsigned long int in = 0) {
  String in_s = String(in);
  unsigned char l_string = in_s.length();
  unsigned char LSB_loc = 4 - (l_string / 2);

  led.clearDisplay(0);

  for (char i = 0; i < l_string; i++) {
    led.setDigit(0, LSB_loc + i, in_s[l_string - i - 1] - '0', false);
    // delay(10);
  }
}

void setup() {
  LED_setup();
  // clock_setup();
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  clock.updateTime();
  display_number(clock.seconds);
  // while(1);
}
