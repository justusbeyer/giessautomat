// Configuration
const uint8_t PIN_PUMP = 2;
const uint8_t PIN_SENSOR_POWER = 4;
const uint8_t PIN_SENSOR_ANALOG_IN = A0;

void setup() {
  /* Set up pins */

  // Pump: The pin connects to a FET which provides power to the pump
  pinMode(PIN_PUMP, OUTPUT);

  // Sensor Power: We only power the sensor to save energy and
  // prevent unnecessary currents in the soil leading to corrosion.
  pinMode(PIN_SENSOR_POWER, OUTPUT);

  // Sensor Analog in: Thats the sensor´s voltage carrying
  // information on the degree of water in the soil
  pinMode(PIN_SENSOR_ANALOG_IN, INPUT);

  /* Debugging via serial */
  Serial.begin(115200);
}


void loop() {

  /* Measure the water content of the soil */
  
  // Power up the sensor
  digitalWrite(PIN_SENSOR_POWER, HIGH);
  
  // Wait for the sensor to wake up and sense.
  delay(500);

  // Read the sensor value
  uint16_t moistureLevel = analogRead(PIN_SENSOR_ANALOG_IN);

  // Power down the sensor
  digitalWrite(PIN_SENSOR_POWER, LOW);

  // Debug out
  Serial.print("Moisture: ");
  Serial.println(moistureLevel);

  if (/*moistureLevel is too low*/moistureLevel > 650) {
    // give it a sip of water
    digitalWrite(PIN_PUMP, HIGH);
    delay(500);
    digitalWrite(PIN_PUMP, LOW);
  }

  // Look again in 10 seconds
  delay(60000);
}
