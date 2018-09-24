void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  while ((!SerialUSB) && (millis() < 30000)) {
    // Wait for SerialUSB or start after 30 seconds
  }
  SerialUSB.println("Starting sketch now");
}

void loop() {
  // put your main code here, to run repeatedly:
  SerialUSB.println("Hello World");
  delay(5000);
}
