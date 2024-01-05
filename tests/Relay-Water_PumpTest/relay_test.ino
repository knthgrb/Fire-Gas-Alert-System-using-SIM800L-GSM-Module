#define RELAY_PIN 6  // Replace with the actual pin to which the relay module is connected

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Turn on the relay for 2 seconds
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("Relay ON");
  delay(5000);

  // Turn off the relay for 2 seconds
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Relay OFF");
  delay(2000);
}
