const int flameSensorPin = 2; // Replace with the actual pin number connected to the flame sensor

void setup() {
  Serial.begin(9600);
  pinMode(flameSensorPin, INPUT);
}

void loop() {
  int flameValue = digitalRead(flameSensorPin);

  if (flameValue == HIGH) {
    Serial.println("Flame detected!");
  } else {
    Serial.println("No flame detected.");
  }

  delay(1000); // Adjust the delay based on your requirements
}
