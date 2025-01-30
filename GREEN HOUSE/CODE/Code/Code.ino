//initilisation of the constants
int motorFlag1 = 0;
int motorFlag2 = 1;
int sensorPin1 = A0;
int sensorPin2 = A3;
int sensorPin3 = A2;
int M1 = 10;       //the arduino pins under which the motor is connected
int M2 = 9;        //the arduino pins under which the motor is connected
int MaxTemp = 27;  // the maximum temperature that the crop being planted desire
int MinTemp = 23;  // the minimum temperature that the crops desire
int sensorValue1, sensorValue2, sensorValue3, total, Average, OLS, CLS, DES, i;
float per;
int limit = 860;
int TIME = 110;  // time taken to open the window as there are no limit switches involved

#include <LiquidCrystal.h>
#include <DHT.h>;

#define DHTPIN 13          // what pin we're connected to
#define DHTTYPE DHT22      // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);  //// Initialize DHT sensor for normal 16mhz Arduino

int val;
int tempPin = A0;
float hum;   //Stores humidity value
float temp;  //Stores temperature value

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  lcd.clear();
}
//void TEMPREAD()

void loop() {
  //OLS = digitalRead(6);
  //CLS = digitalRead(7);
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  sensorValue1 = analogRead(sensorPin1);
  Serial.println("AV1: ");
  Serial.println(sensorValue1);
  //lcd.setCursor(0, 0);
  //lcd.print("AV1:");
  //lcd.print(sensorValue1);
  sensorValue2 = analogRead(sensorPin2);
  Serial.println("AV2: ");
  Serial.println(sensorValue2);
  //lcd.setCursor(0, 1);
  //lcd.print("AV2:");
  //lcd.print(sensorValue2);
  sensorValue3 = analogRead(sensorPin3);
  Serial.println("AV3:");
  Serial.println(sensorValue3);
  /*lcd.setCursor(8, 0);
    lcd.print("AV3:");
    lcd.print(sensorValue3);*/
  total = sensorValue1 + sensorValue2 + sensorValue3;
  Average = total / 3;
  Serial.println("AVERAGE:");
  Serial.println(Average);
  DES = 950 - Average;
  per = (DES * 100) / 200;
  /*lcd.setCursor(0, 0);
  lcd.print(sensorValue1);
  lcd.setCursor(0, 1);
  lcd.print(sensorValue2);
  lcd.setCursor(8, 0);
  lcd.print(sensorValue3);
  lcd.setCursor(8, 1);
  lcd.print(Average);*/
  lcd.print("SOIL MOIST PER:");
  Serial.println("SOIL MOIST PER:");
  lcd.setCursor(4, 1);
  lcd.print(per);
  Serial.println(per);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hum:");
  lcd.print(hum);
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temp);
  delay(1000);
  TEMPERATURE();
  if (Average >= limit) {
    if (Average < 955) {
      digitalWrite(8, HIGH);
    } else {
      digitalWrite(8, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sensors Error");
      delay(2000);
      lcd.clear();
    }
  } else {
    digitalWrite(8, LOW);
  }
}
void TEMPERATURE() {
  if (temp >= MaxTemp) {
    if (motorFlag1 == 0) {
      digitalWrite(M1, HIGH);
      digitalWrite(M2, LOW);
      delay(TIME);
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      delay(TIME);
      motorFlag1++;
      motorFlag2 = 0;
    }
  } else {
    if (motorFlag2 == 0) {
      digitalWrite(M1, LOW);
      digitalWrite(M2, HIGH);
      delay(TIME);
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      delay(TIME);
      motorFlag2++;
      motorFlag1 = 0;
    }
  }
  lcd.clear();
}
