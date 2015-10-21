// Home sensors.
// Rémy Mathieu - 2015

// We'll put the mcp on the PIN 0 if the arduino.
int MCP9701_ARDUINO_PIN = 0;
int LIGHT_PIN = 1;

// Debug through the serial at 9600baud
void setup() {
    Serial.begin(9600);
    Serial.println("Initiating sensors loop.");
}

void loop() {
    float resTemp = 0.0f;
    float resLight = 0.0f;

    // In one second, retrieve 5 times the voltage of the
    // MCP9701A put on the Arduino's pin.
    for (int i = 0; i < 5; i++) {
        resTemp += readTemperature();
        resLight += readLight();
        delay(200);
    }

    // Print the output on the serial.
    Serial.print("Temp: "); Serial.print(resTemp/5.0f); Serial.println(" C");
    Serial.print("Light: "); Serial.print(resLight/5.0f); Serial.println(" %");
}

float readLight() {
    float reading = analogRead(LIGHT_PIN);
    return (reading/1024.0f)*100.0f;
}

float readTemperature() {
    // Vref = 5.0
    float reading = analogRead(MCP9701_ARDUINO_PIN)*5.0f/1024.0f;

    // the MCP9701A has 0° at 0.4mv
    float temp = reading - 0.4f;
    // 1° per 19.5mv
    temp = temp/0.0195f;

    return temp;
}
