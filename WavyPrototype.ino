/*
  Wavy Initial Prototype Code
  Student Name & ID: Ivy Sun 3183268
  Course Code & Titlel: DIGF-2015-001 Atelier II: Collaboration
  Instructor: Dr. Adam Tindale
  OCAD University
  Modified by Ivy Sun in Mar. - Apr. 2022
  Based on:
  Arduino Tutorials/References/Resources/Built-In Examples:
  
  Sample Code file "p06_LightTheremin" from Arduino Examples Library
  
  Sample Code file "Calibration" by David A Mellis, Tom Igoe and Zachary J. Fields from Arduino Built-In Examples Library
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Calibration
  
  https://www.arduino.cc/reference/en/language/functions/math/constrain/
  https://www.arduino.cc/en/Reference/Map
  https://www.arduino.cc/en/Reference/Millis
  https://www.arduino.cc/en/Reference/While
*/

#define PIN_PIEZO    9
#define PIN_BUTTON   2
#define PIN_LED      0
#define PIN_LDR      A0
#define PIN_POTI_MIN A1
#define PIN_POTI_MAX A2

// calibrate for the first five seconds after program runs
#define CALIBRATION_DURATION 5 // in seconds

// Pitch definitions in Hz
// These defines set the range of sound pitch frequencies when mapping to the sensor value
#define PITCH_MIN_LOWER 5
#define PITCH_MIN_UPPER 170
#define PITCH_MAX_LOWER 20
#define PITCH_MAX_UPPER 1000

// variable to hold sensor value
// variable to calibrate low value
// variable to calibrate high value
int sensorValue = 0, sensorMin = 700, sensorMax = 0;
int pitchMin = PITCH_MIN_LOWER, pitchMax = PITCH_MAX_LOWER;
unsigned long lastPressedButton = 0;
byte buttonState = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_POTI_MIN, INPUT);
  pinMode(PIN_POTI_MAX, INPUT);
  
  tone(PIN_PIEZO, 550);
  while (millis() < (CALIBRATION_DURATION * 1000)) {
    // read the input from PIN_LDR and store it in a variable
    sensorValue = analogRead(PIN_LDR);
    sensorMax = max(sensorValue, sensorMax);
    sensorMin = min(sensorValue, sensorMin);
  }
  noTone(PIN_PIEZO);
}

void loop()
{
  if ((millis() - lastPressedButton > 150) && digitalRead(PIN_BUTTON) == LOW) {
    lastPressedButton = millis();
    buttonState++;
    buttonState %= 7;
    // six modes of preset tempo in total
    // pressed time should at least an interval of 0.15 seconds
  }

  // map the sensor values to a wide range of pitches
  pitchMin = PITCH_MIN_LOWER + map(analogRead(PIN_POTI_MIN), 0, 1023, 0, PITCH_MIN_UPPER);
  pitchMin = constrain(pitchMin, PITCH_MIN_LOWER, PITCH_MIN_UPPER);
  pitchMax = PITCH_MAX_LOWER + map(analogRead(PIN_POTI_MAX), 0, 1023, 0, PITCH_MAX_UPPER);
  pitchMax = constrain(pitchMax, PITCH_MAX_LOWER, PITCH_MAX_UPPER);

  if (buttonState > 0) {
    digitalWrite(PIN_LED, HIGH);
    
    // read the input from PIN_LDR and store it in a variable
    sensorValue = analogRead(PIN_LDR);

    // apply the calibration to the sensor reading
    // map the sensor value to pitch
    sensorValue = map(sensorValue, sensorMin, sensorMax, pitchMin, pitchMax);

    // in case the sensor value is outside the range seen during calibration
    sensorValue = constrain(sensorValue, pitchMin, pitchMax);
    
    tone(PIN_PIEZO, sensorValue);

    if (buttonState == 2) {
      delay(160);
    } else if (buttonState == 3) {
      delay(50);
    }
    else if (buttonState == 4) {
      delay(250);
    }
    else if (buttonState == 5) {
      delay(400);
    }
    else if (buttonState == 6) {
      delay(100);
    }
  } else {
    noTone(PIN_PIEZO);
    digitalWrite(PIN_LED, LOW);
  }
}
