#define TRIG_PIN 3  // PB3
#define ECHO_PIN 4  // PB4
#define RELAY_PIN 1 // PB1 (Relay control)

#define TANK_EMPTY_LEVEL 6  // Distance in cm (Pump ON threshold)
#define TANK_FULL_LEVEL 1    // Distance in cm (Pump OFF threshold)

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Start with pump OFF
}

long measureDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    long distance = duration * 0.034 / 2;  // Convert to cm
    return distance;
}

void loop() {
    long waterLevel = measureDistance();

    if (waterLevel > TANK_EMPTY_LEVEL) {
        digitalWrite(RELAY_PIN, HIGH);  // Turn ON pump
    } 
    else if (waterLevel <= TANK_FULL_LEVEL) {
        digitalWrite(RELAY_PIN, LOW); // Turn OFF pump
    }

    delay(100); // Delay for stability
}
