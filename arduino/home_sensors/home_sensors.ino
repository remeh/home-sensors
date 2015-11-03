/*
 * Home sensors.
 * Copyright © 2015 Rémy Mathieu
 */

/*
 * Consts
 */

/* Write frequency */
#define WRITE_FREQUENCY 30000

/* Set to false to not bip on presence */
#define BIP true

/* We'll put the mcp on the PIN 0 if the arduino. */
#define MCP9701_ARDUINO_INPUT_PIN (0)
/* Light sensor */
#define LIGHT_INPUT_PIN (1)
/* Presence sensor */
#define PIR_INPUT_PIN (2)

/* Buzzer output signal */
#define BUZZER_OUTPUT_PIN (9)

/*
 * Globals
 */

float resTemp = 0.0f;
float resLight = 0.0f;
bool pir = false;

unsigned long next_write = 0;

/*
 * Code
 */

void setup() {
    #ifdef BIP
        pinMode(BUZZER_OUTPUT_PIN, OUTPUT);
    #endif

    /* We'll use the serial as a communication
     * to the other board */
    Serial.begin(9600);
}

void loop() {
    // MCP9701A put on the Arduino's pin.
    resTemp += readTemperature();
    resLight += readLight();

    bool oldPir = pir;
    pir = readPir();

    if (oldPir != pir) {
        // immediate trigger of a write.
        write();
    }

    /* We wanna write every 30 seconds */
    if (next_write < millis()) {
        write();
    }

    /* Don't consume too much power */
    delay(500);
}

/* Sends data to the Olimex through the serial */
void write() {
    #ifdef BIP
        analogWrite(BUZZER_OUTPUT_PIN, 340);
        delay(30);
    #endif

    Serial.print("T"); Serial.print(resTemp); Serial.print(" ");
    Serial.print("L"); Serial.print(resLight); Serial.print(" ");
    Serial.print("P"); Serial.println(pir ? "1" : "0");
    next_write = millis()+WRITE_FREQUENCY;

    #ifdef BIP
        analogWrite(BUZZER_OUTPUT_PIN, 0);
    #endif
}

bool readPir() {
    if (analogRead(PIR_INPUT_PIN) > 500) {
        return true;
    }
    return false;
}

float readLight() {
    float reading = analogRead(LIGHT_INPUT_PIN);
    return (reading/1024.0f)*100.0f;
}

float readTemperature() {
    /* Vref = 5.0 */
    float reading = analogRead(MCP9701_ARDUINO_INPUT_PIN)*5.0f/1024.0f;

    /* the MCP9701A has 0° at 0.4mv */
    float temp = reading - 0.4f;
    /* 1° per 19.5mv */
    temp = temp/0.0195f;

    return temp;
}
