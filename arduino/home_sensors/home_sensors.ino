// Home sensors.
// Rémy Mathieu - 2015

// We'll put the mcp on the PIN 0 if the arduino.
int MCP9701_ARDUINO_PIN = 0;

// Debug through the serial at 9600baud
void setup() {
 Serial.begin(9600);
}

void loop() {
  float res = 0.0f;
  // In one second, retrieve 5 times the voltage of the
  // MCP9701A put on the Arduino's pin.
  for (int i = 0; i < 5; i++) {  
    // Vref = 5.0    
    float reading = analogRead(MCP9701_ARDUINO_PIN)*5.0f/1024.0f;
    // the MCP9701A has 0° at 0.4mv
    float temp = reading - 0.4f;
    // 1° per 19.5mv
    temp = temp/0.0195f;
    
    res += temp;
    delay(200);
  }

  // Print the output on the serial.
  Serial.print(res/5.0f); Serial.println(" C");
}
