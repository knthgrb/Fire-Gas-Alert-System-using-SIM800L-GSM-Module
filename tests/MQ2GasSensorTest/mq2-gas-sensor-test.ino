#define MQ2_ANALOG_PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(MQ2_ANALOG_PIN, INPUT);
}

void loop() {
  // Read analog value from MQ2 sensor
  int mq2AnalogValue = analogRead(MQ2_ANALOG_PIN);

  Serial.print("MQ2 Analog Value: ");
  Serial.println(mq2AnalogValue);

  delay(1000); // Adjust the delay as needed
}
