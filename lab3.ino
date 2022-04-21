#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
int button;
int bState, lastState, fanDirection;

int motor1 = 6;
int motor2 = 28;
int motorOn = 8;
int flag = 0;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  clock.begin();
  button = 10;
  lastState = 0;
  fanDirection = 0;
  lcd.setCursor(0, 1);
  lcd.print("C ");
  digitalWrite(motor1, 0);
  digitalWrite(motor2, 1);
  

}

void loop() {

  dt = clock.getDateTime();
  lcd.setCursor(0, 0);
  lcd.print(dt.hour);
  lcd.print(":");
    if (dt.minute < 10){
    lcd.print("0");
  }
  lcd.print(dt.minute);
  lcd.print(":");
  if (dt.second < 10){
    lcd.print("0");
  }
  lcd.print(dt.second);
  lcd.print("         ");

  
  bState = digitalRead(button);
  if ((bState == 1) && (lastState == 0)){
    lastState = 1;
    if (fanDirection == 0){
      fanDirection = 1;
      lcd.setCursor(0, 1);
      lcd.print("CC");
      lcd.setCursor(0, 0);
      digitalWrite(motor1, 1);
      digitalWrite(motor2, 0);
    }
    else{
      fanDirection = 0;
      lcd.setCursor(0, 1);
      lcd.print("C ");
      lcd.setCursor(0, 0);
      digitalWrite(motor1, 0);
      digitalWrite(motor2, 1);
    }
  }
  if ((bState == 0) && (lastState == 1)){
    lastState = 0;
  }
  Serial.println("Test");
  if ((dt.second == 0)&&(flag == 0)){
    analogWrite(motorOn, 255);
    Serial.println("On");
    flag = 1;
  }
  if ((dt.second == 30)&&(flag == 0)){
    digitalWrite(motorOn, 0);
    Serial.println("Off");
    flag = 1;
  }
  if ((dt.second != 0)&&(dt.second != 30)&&(flag == 1)){
    flag = 0;
  }
  
}
