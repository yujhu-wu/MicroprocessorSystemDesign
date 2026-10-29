#include <LiquidCrystal.h>
#include <RTC.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/* Change these values to set the current initial time */
const byte seconds = 55;
const byte minutes = 59;
const byte hours = 23;
const byte day = 26;

void setup() {
     // set up the LCD's number of columns and rows
     lcd.begin(16, 2);

     // set the time and start counting
     RTC.settime(day, hours, minutes, seconds);
     //RTC.setmonth(2);
     RTC.startcounting();
}

void loop() {
     lcd.clear();
     lcd.print("2024 Counting...");
     lcd.setCursor(0, 1);

     // Format hours, minutes, and seconds with leading zeros if necessary
     int hour = RTC.gethours();
     int minute = RTC.getminutes();
     int second = RTC.getseconds();
     int currentDay = RTC.getday();

     // Print formatted time
     lcd.print(hour < 10 ? "0" : "");  // Add leading zero if needed
     lcd.print(hour);
     lcd.print(":");
     lcd.print(minute < 10 ? "0" : "");  // Add leading zero if needed
     lcd.print(minute);
     lcd.print(":");
     lcd.print(second < 10 ? "0" : "");  // Add leading zero if needed
     lcd.print(second);

     lcd.print("   11/");
     lcd.print(currentDay < 10 ? "0" : "");  // Add leading zero if needed
     lcd.print(currentDay);

     delay(1000);
}
