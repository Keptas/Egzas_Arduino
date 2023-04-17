const int LIGHT_SENSOR_PIN = A0;
const int TEMPERATURE_SENSOR_PIN = A1;
const int IR_PIN = 2;
const int POTENTIOMETER_PIN = A2;
const int SERVO_PIN = 5;
const int WEIGHT_SENSOR_PIN = 6;
const int LED1_PIN = 7;
const int LED2_PIN = 8;
const int LED3_PIN = 9;
const int LED4_PIN = 10;
const int Y = 10;
const int TEMPERATURE_THRESHOLD = 20;
const int ADC_RESOLUTION = 1023;
const float RESISTOR = 10000.0; // 10kΩ
const float VOLTAGE_REF = 5.0;
void setup() {
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(TEMPERATURE_SENSOR_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(WEIGHT_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED4_PIN, LOW);
}

void loop() {
  // 1. Sviesos jutiklis
 /* int lightLevel = analogRead(LIGHT_SENSOR_PIN);
  if (lightLevel < 10) {
    digitalWrite(LED4_PIN, LOW);
     
  } else {
    digitalWrite(LED4_PIN, HIGH);
  }
	Serial.print(lightLevel + ".\n");*/
  
  
  int sensorValue = analogRead(LIGHT_SENSOR_PIN);
  float voltage = (sensorValue / (float)ADC_RESOLUTION) * VOLTAGE_REF;
  float resistance = RESISTOR * ((VOLTAGE_REF / voltage) - 1);

  // Apskaičiuoti šviesos lygį naudojant fotorezistoriaus charakteristikas (priklauso nuo jūsų fotorezistoriaus)
  // Čia naudojamas pavyzdinis skaičiavimas: lux = 500 / (resistance / 1000.0)
  // Jums gali tekti pritaikyti šią formulę, kad atitiktų jūsų fotorezistorių.
  float lux = 500 / (resistance / 1000.0);

  if (lux > 10) {
    digitalWrite(LED4_PIN, HIGH);
  } else {
    digitalWrite(LED4_PIN, LOW);
  }

  delay(200);
  
  
  
  
  
  // 2. Temperaturos daviklis
  int temperatureRaw = analogRead(TEMPERATURE_SENSOR_PIN);
  float temperature = (temperatureRaw / 1023.0) * 5.0 * 100;
  if (temperature > TEMPERATURE_THRESHOLD) {
   // Serial.print("Jungiam kondiske\n");
  } else if (temperature < TEMPERATURE_THRESHOLD) {
   // Serial.print("Jungiam sildytuva\n ");
  }

  // 3. Infraraudonųjų spindulių daviklis
  if (digitalRead(IR_PIN) == HIGH) {
    delay(5000);
    // Uždaryti garažo vartus
  }

  // 4. Potenciometras
  int angle = map(analogRead(POTENTIOMETER_PIN), 0, 1023, 0, 360);
  Serial.print(angle);
  Serial.print("\n");
  if (angle == Y) {
    analogWrite(SERVO_PIN, Y * 2);
  }

  // 5. Svorio jutiklis
  if (digitalRead(WEIGHT_SENSOR_PIN) == LOW) {
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    delay(3000);
    digitalWrite(LED1_PIN, LOW);
    
    delay(2000);
    digitalWrite(LED2_PIN, LOW);
    
    delay(1000);
    digitalWrite(LED3_PIN, LOW);
  }
}
