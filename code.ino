#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Password.h>
#include <Servo.h>
Servo Servo1;Servo Servo2;
int active = 0;
int passwd_pos = 7;int k = 0;int val1 = 0;int val2 = 0;int val3 = 0;int val4 = 0;
int val5 = 0;
int servoPin1 = 28;
int servoPin2 = 29;
Password password = Password("1234");
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
const int pir1 = A4;
const int pir2 = A5;
const int pir3 = A6;
const int pir4 = A15;
const int pir5 = A10;
const int trigPin = A0;
const int echoPin = A1;
const int gled = A3;
const int yled = A2;
const int buzz = 5;
int i = 0;
//for_keypadconst byte ROWS = 4;const byte COLS = 4;char keys[ROWS][COLS] = {{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},{'7', '8', '9', 'C'},{'*', '0', '#', 'D'}};byte rowPins[ROWS] = {6, 7, 8, 9};byte colPins[COLS] = {10, 11, 12, 13};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup() {lcd.begin(16, 2);Serial.begin (9600);pinMode(pir1, INPUT);
pinMode(pir2, INPUT);pinMode(pir3,INPUT);pinMode(pir4, INPUT);
pinMode(pir5, INPUT);pinMode(trigPin, OUTPUT);pinMode(echoPin, INPUT);
pinMode(buzz, OUTPUT);pinMode(gled, OUTPUT);pinMode(yled, OUTPUT);
keypad.addEventListener(keypadEvent);
lcd.setCursor(0, 0);
lcd.print("Security system");
lcd.setCursor(0, 1);
lcd.print("Miniproject");
delay(1600);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Created by");
lcd.setCursor(0, 1);
lcd.print("BIVEK SHAH");
delay(2000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("UNDER GUIDANCE");
lcd.setCursor(0, 1);
lcd.print("MS.SHOBHA P");
delay(2000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Enter Code");
Servo1.attach(servoPin1);
Servo2.attach(servoPin2);
}
void loop()
{ keypad.getKey();
if (active == 1){ultra();//pir();}
}
void keypadEvent(KeypadEvent eKey)
{switch (keypad.getState())
 {case PRESSED:lcd.setCursor((passwd_pos++), 1);
 switch (eKey) {case '#':passwd_pos  = 7;buzz1();checkPassword();
 break;
case '*':password.reset();buzz1();lcd.setCursor(0, 1);lcd.print("                 ");passwd_pos = 7;break;default:password.append(eKey);lcd.print("*");buzz1();}}}void checkPassword() {if (password.evaluate()) {Activated();password.reset();k = 0;}
else{wrongpin();}}void Activated(){active = 1;i++;lcd.setCursor(0, 0);
lcd.clear();lcd.print("SECURITY ACTIVE");digitalWrite(yled, HIGH);
digitalWrite(gled , LOW);if (i % 2 == 0){deactivated();}
return;}void deactivated(){active = 0;lcd.setCursor(0, 1);lcd.clear();
lcd.setCursor(0, 0);password.reset();lcd.clear();lcd.print("DEACTIVATED");
digitalWrite(yled, LOW);digitalWrite(gled, HIGH);exit;}void wrongpin(){lcd.clear();
lcd.setCursor(4, 0);lcd.print("WRONG PIN");
password.reset();k++;if (k >= 3){lcd.clear();
lcd.setCursor(5, 0);lcd.print("INTRUDER");alarm();k = 0;}}void buzz1(){digitalWrite(buzz, HIGH);delay(50);digitalWrite(buzz, LOW);}//sensorsvoid ultra(){
float duration, distance;digitalWrite(trigPin, LOW);delayMicroseconds(2);digitalWrite(trigPin, HIGH);delayMicroseconds(10);digitalWrite(trigPin, LOW);duration = pulseIn(echoPin, HIGH);distance = (duration / 2) * 0.0344;val1 = digitalRead(pir1);val2 = digitalRead(pir2);val3 = digitalRead(pir3);val4 = digitalRead(pir4);val5 = digitalRead(pir5);if (distance <= 25){ Serial.println("ultra");Servo1.write(120);Servo2.write(170);lcd.clear();lcd.setCursor(0, 0);
lcd.print("MOTION IN");lcd.setCursor(0, 1);lcd.print("BACKYARD");alarm();}else if (val1 == HIGH){ Serial.println("pir1");Servo1.write(120);Servo2.write(50);lcd.clear();lcd.setCursor(0, 0);lcd.print("MOTION IN");lcd.setCursor(0, 1);lcd.print("ROOM 3");alarm();val1 = LOW;}else if (val2 == HIGH){ Serial.println("pir2");Servo1.write(110);
Servo2.write(30);lcd.clear();lcd.setCursor(0, 0);lcd.print("MOTION IN");lcd.setCursor(0, 1);lcd.print("ROOM 1");alarm();val2 = LOW;} else if (val3 == HIGH){ Serial.println("pir3");Servo1.write(100);Servo2.write(60);lcd.clear();lcd.setCursor(0, 0);lcd.print("MOTION IN");lcd.setCursor(0, 1);lcd.print("ROOM 2");alarm();val3 = LOW;} else if (val4 == HIGH){ Serial.println("pir4");
Servo1.write(110);Servo2.write(0);lcd.clear();lcd.setCursor(0, 0);lcd.print("MOTION IN");lcd.setCursor(0, 1);lcd.print("GARAGE");alarm();val4 = LOW;} else if (val5 == HIGH){ Serial.println(val5);Servo1.write(110);Servo2.write(80);lcd.clear();lcd.setCursor(0, 0);lcd.print("MOTION IN");lcd.setCursor(0, 1);lcd.print("ROOM 4");alarm();val5 = LOW;}
else return;}void alarm(){while (!password.evaluate()){digitalWrite(buzz, HIGH);delay(50);digitalWrite(buzz, LOW);delay(50);Serial.println("AT alarm");/* if(active==1){ Serial.println("in ultra function");ultra();}*/Serial.println("AT key");keypad.getKey();}Serial.println("deactivated");deactivated();
Servo1.write(50);Servo2.write(20);i++;}
