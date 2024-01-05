#include<SoftwareSerial.h>

SoftwareSerial GSM(10, 11); //RX, TX

void setup() {
  Serial.begin(9600);

  Serial.print("Sending message...");
  GSM.begin(9600);

  sendSMS("hello");
}

void loop() {
  

}

void sendSMS(String message){
  GSM.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  GSM.println("AT+CMGS=\"+639XXXXXXXXXX\""); //replace with recepient number
  delay(100);
  GSM.println(message);
  delay(100);
  GSM.write(0x1A);
  delay(100);
}
