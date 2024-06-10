/*

Driving IGT (ignition trigger?) pin of a Toyota Sienna ignition coil-on-plug module

 */

// Pin assignments
#define IGT 3
#define BUTTON 9
#define POT A6

// Time periods
#define TRIGGER_TIME_US 2000
#define PRINT_PERIOD_MS 500
#define BUTTON_DEBOUNCE_MS 500

// Modes to be cycled through via button press
#define ENGINE 0
#define ODE_TO_JOY 1
#define MODE_MAX 2

// Ode to Joy from Beethoven's Symphony #9
// Adapted from beginner piano arrangement by Benedict Westernra
// musophone.com

#define BAR_MS 1200
const uint16_t note_durations[5] = {
  BAR_MS,
  BAR_MS/2,
  BAR_MS/4,
  BAR_MS/8,
  BAR_MS/16
};

const uint16_t otj_notes[132] = {
  66, 2,
  66, 2,
  68, 2,
  69, 2,

  69, 2,
  68, 2,
  66, 2,
  65, 2,

  62, 2,
  62, 2,
  65, 2,
  66, 2,

  66, 2,
  65, 3,
  65, 1,
  65, 3,


  66, 2,
  66, 2,
  68, 2,
  69, 2,

  69, 2,
  68, 2,
  66, 2,
  65, 2,

  62, 2,
  62, 2,
  65, 2,
  66, 2,

  65, 2,
  62, 3,
  62, 1,
  62, 3,


  65, 2,
  65, 2,
  66, 2,
  62, 2,

  65, 2,
  66, 3,
  68, 3,
  66, 2,
  62, 2,

  65, 2,
  66, 3,
  68, 3,
  66, 2,
  65, 2,

  62, 2,
  65, 2,
  37, 2,
  66, 2,


  66, 2,
  66, 2,
  68, 2,
  69, 2,

  69, 2,
  68, 2,
  66, 2,
  65, 2,

  62, 2,
  62, 2,
  65, 2,
  66, 2,

  65, 2,
  65, 3,
  62, 0,
  62, 0,
};

// State variables
int mode = 0;
int knob = 0;
int button = 0;

// Timing trackers
unsigned long next_print = 0;
unsigned long button_debounce = 0;
unsigned long next_igt = 0;
unsigned long igt_wait = 0;

// Ode to Joy variables
uint8_t playing_note = 0;
uint8_t otj_current_note_index = 0;
unsigned long otj_end_note_ms = 0;
unsigned long otj_next_note_ms = 0;

void setup() {
  // Hardware setup
  Serial.begin(115200);
  pinMode(BUTTON, INPUT);
  pinMode(IGT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Start timing trackers
  next_print = millis();
  button_debounce = millis()+BUTTON_DEBOUNCE_MS;
}

void loop() {
  button = digitalRead(BUTTON);
  if (HIGH == button) {
    if (millis() > button_debounce) {
      // next mode
      mode = (mode + 1) % 2;
      Serial.print("New mode: ");
      Serial.println(mode);

      otj_current_note_index = 0;    }
    button_debounce = millis()+BUTTON_DEBOUNCE_MS;
  }

  if (ENGINE == mode) {
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
    knob = map(analogRead(POT), 0, 1023, 17, 120);
    delay(knob);
  } else if (ODE_TO_JOY == mode) {
    if (millis() > otj_next_note_ms) {
      switch(otj_notes[otj_current_note_index*2]) {
        case 37:
          igt_wait = 13931;
          break;
        case 62:
          igt_wait = 2905;
          break;
        case 65:
          igt_wait = 2388;
          break;
        case 66:
          igt_wait = 2202;
          break;
        case 68:
          igt_wait = 1907;
          break;
        case 69:
          igt_wait = 1772;
          break;
        default:
          Serial.println("Unknown note");
          break;
      }
      Serial.print("igt_wait ");
      Serial.println(igt_wait);
      otj_next_note_ms = millis() + note_durations[otj_notes[(otj_current_note_index*2)+1]];
      otj_current_note_index = (otj_current_note_index+1)%66;
    }

    digitalWrite(IGT, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(IGT, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delayMicroseconds(igt_wait);
  } else {
    Serial.println("Unknown mode, resetting to 0");
    mode = 0;
  }
}
