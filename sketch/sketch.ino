#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>

// Define the pins for the RTC, buzzer, and LCD
const int RTC_SDA = 2;
const int RTC_SCL = 3;
const int buzzerPin = 7;
const int LCD_RS = 8;
const int LCD_EN = 9;
const int LCD_D4 = 10;
const int LCD_D5 = 11;
const int LCD_D6 = 12;
const int LCD_D7 = 13;

// Define the maximum number of alarms
const int maxAlarms = 15;

// Create an array to store the alarms
struct Alarm {
  int hour;
  int minute;
  bool enabled;
};
Alarm alarms[maxAlarms];

// Initialize the alarms
void initAlarms() {
  // Set the alarm times
  alarms[0].hour = 12;
  alarms[0].minute = 21;
  alarms[0].enabled = true;

  alarms[1].hour = 14;
  alarms[1].minute = 40;
  alarms[1].enabled = true;

  alarms[2].hour = 14;
  alarms[2].minute = 55;
  alarms[2].enabled = true;

  alarms[3].hour = 19;
  alarms[3].minute = 55;
  alarms[3].enabled = true;

  alarms[4].hour = 19;
  alarms[4].minute = 56;
  alarms[4].enabled = true;

  alarms[5].hour = 19;
  alarms[5].minute = 57;
  alarms[5].enabled = true;

  alarms[6].hour = 19;
  alarms[6].minute = 55;
  alarms[6].enabled = true;

  alarms[7].hour = 19;
  alarms[7].minute = 56;
  alarms[7].enabled = true;

  alarms[8].hour = 19;
  alarms[8].minute = 57;
  alarms[8].enabled = true;

  alarms[9].hour = 19;
  alarms[9].minute = 55;
  alarms[9].enabled = true;

  alarms[10].hour = 19;
  alarms[10].minute = 56;
  alarms[10].enabled = true;

  alarms[11].hour = 19;
  alarms[11].minute = 57;
  alarms[11].enabled = true;

  alarms[12].hour = 19;
  alarms[12].minute = 55;
  alarms[12].enabled = true;

  alarms[13].hour = 19;
  alarms[13].minute = 56;
  alarms[13].enabled = true;

  alarms[14].hour = 19;
  alarms[14].minute = 57;
  alarms[14].enabled = true;

  alarms[15].hour = 19;
  alarms[15].minute = 55;
  alarms[15].enabled = true;
}

// Check if an alarm is active
bool isAlarmActive(int alarmNumber) {
  return alarms[alarmNumber].enabled &&
         (hour() == alarms[alarmNumber].hour &&
          minute() == alarms[alarmNumber].minute);
}

// Sound the buzzer when an alarm is active
void soundAlarm(int alarmNumber) {
  digitalWrite(buzzerPin, HIGH);
  tone(buzzerPin, 262, 250);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}

// Create an instance of the LiquidCrystal object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  // Initialize the serial port
  Serial.begin(9600);

  // Initialize the RTC
  setSyncProvider(RTC.get);
  if(!RTC.isRunning()){
    Serial.println("RCT is NOT running!");
  }

  // Initialize the alarms
  initAlarms();

  // Set up the LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm System");
  lcd.setCursor(0, 1);
  lcd.print("Initialized");
  delay(2000);
  lcd.clear();
}

void loop() { 
  // Get the current date and time
  time_t now = RTC.get();
  tmElements_t tm;
  breakTime(now, tm);

  // Retrieve the day of the week
  String dayOfWeek = dayShortStr(weekday());

  //checking the days of the week to apply the alarms
    // Check if any of the alarms are active
  for (int i = 0; i < maxAlarms; i++) {
    if (isAlarmActive(i)) {
      soundAlarm(i);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alarm Active!");
      lcd.setCursor(0, 1);
      lcd.print("Alarm: ");
      lcd.print(i + 1);
      delay(1000);
      lcd.clear();
    }
  }

  // Display the current time on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  char timeStr[9];
  sprintf(timeStr, "%02d:%02d:%02d", hour(), minute(), second());
  lcd.print(timeStr);
  lcd.setCursor(0, 1);
  lcd.print("Day: ");
  lcd.print(dayOfWeek);
  delay(1000);
}