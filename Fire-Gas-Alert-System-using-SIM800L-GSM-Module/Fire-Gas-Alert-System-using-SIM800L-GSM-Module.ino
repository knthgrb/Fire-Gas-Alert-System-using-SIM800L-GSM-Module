#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define FLAME_SENSOR_PIN 6 // Replace with the actual pin to which the sensors are connected
#define MQ2_ANALOG_PIN A0
#define RX 10
#define TX 11

#define DHT_PIN 4
#define DHT_TYPE DHT11

//threshold values for gas and temperature
const int gasThreshold = 600; 
const float tempThreshold = 32.00;

const int ledPin = 7;
const int buzzerPin = 9;
const int relayPin = 5;

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial GSM(RX, TX);


void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  GSM.begin(9600);

  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(MQ2_ANALOG_PIN, INPUT);
  pinMode(DHT_PIN, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("FIRE PREVENTION");
  lcd.setCursor(4, 1);
  lcd.print("SYSTEM");

  digitalWrite(relayPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
  
  delay(1000);
}

void loop() {
  int flameValue = digitalRead(FLAME_SENSOR_PIN);
  int mq2AnalogValue = analogRead(MQ2_ANALOG_PIN);
  float temperature = dht.readTemperature();

  Serial.print("Flame Value: ");
  Serial.print(flameValue);
  Serial.print("     ");
  Serial.print("MQ2 Analog Value: ");
  Serial.print(mq2AnalogValue);
  Serial.print("     ");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println();

  lcd.clear();

  //FLAME
  lcd.print("Flame: ");
  flameValue == 0 ? lcd.print("Yes") : lcd.print("No");

  //TEMPERATURE
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.write(0xDF);
  lcd.print("C");
  delay(2000);
  lcd.clear();

  //GAS CONDITION
  lcd.print("Gas condition: ");
  lcd.setCursor(0, 1);
  if(mq2AnalogValue > gasThreshold){
    lcd.print("Gas detected");
  } else {
    lcd.print("No Gas Detected"); 
  }
  delay(2000);
  lcd.clear();

  if(flameValue == 0 || (flameValue == 0 && mq2AnalogValue > gasThreshold && temperature > tempThreshold) || (flameValue == 0 && temperature > tempThreshold)){
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(relayPin, HIGH);
    sendSMS("Emergency!! Fire Alarm!");
    Serial.println("Fire");
  } 
  else if(mq2AnalogValue > gasThreshold){
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(relayPin, HIGH);
    sendSMS("Gas detected");
    Serial.println("Gas warning!");
  }
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
  }

  delay(1000); // Adjust the delay as needed
}

//function to send message with sim800L gsm  module
void sendSMS(String message){
  GSM.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  GSM.println("AT+CMGS=\"+639xxxxxxxxx\""); //replace with recepient's phone number
  delay(100);
  GSM.println(message);
  delay(100);
  GSM.write(0x1A);
  delay(100);
}