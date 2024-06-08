/*

Driving IGT (ignition trigger?) pin of a Toyota Sienna ignition coil-on-plug module

 */

#define IGT 3
#define POT A6
#define TRIGGER_TIME_US 2000
#define PRINT_PERIOD_MS 500

int knob = 0;
unsigned long next_print = 0;

void setup() {
  Serial.begin(115200);
  pinMode(IGT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  knob = 0;
  next_print = millis();
}

void loop() {
  knob = map(analogRead(POT), 0, 1023, 17, 120);

  if (millis() > next_print)
  {
    Serial.println(knob);
    next_print = millis() + PRINT_PERIOD_MS;
  }

  digitalWrite(IGT, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delayMicroseconds(TRIGGER_TIME_US);
  digitalWrite(IGT, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  // Arduino Nano potentiometer returns 0-1023
  // Time beween pulses derived from 1000 RPM (~120ms) to 7000 RPM redline (~17ms)
  delay(knob);
}
