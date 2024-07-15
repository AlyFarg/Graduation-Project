#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>  // Use LiquidCrystal instead of LiquidCrystal_I2C

// Pin Definitions
#define STEP_PIN 2
#define DIR_PIN 3
#define ENABLE_PIN 4

// Stepper Motor Parameters
#define STEPS_PER_REVOLUTION_A  400 // Adjust according to your stepper motor specification
#define STEPS_PER_REVOLUTION_B -400 // Adjust according to your stepper motor specification

// Timing Parameters
#define STEP_DELAY 1000 // Delay between steps in microseconds

// LCD setup
const int rs = 10, en = 9, d4 = 8, d5 = 7, d6 = 6, d7 = 5; // Adjust these pins if needed
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
char park1_state;
char park2_state;

byte rowPins[ROWS] = {22, 24, 26, 28};  // Update pins to avoid conflict with LCD
byte colPins[COLS] = {A3, A2, A1, A0};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  Serial1.begin(9600);
  Serial2.begin(9600);
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows

  // Set the pins as outputs
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // Disable the motor initially
  digitalWrite(ENABLE_PIN, HIGH);
}

void loop() {
  char command = getCommandFromPython();
  switch (command) {
    case 'a':
      // Enable the motor
      digitalWrite(ENABLE_PIN, LOW);
      // Rotate clockwise
      digitalWrite(DIR_PIN, HIGH);
      for (int i = 0; i < STEPS_PER_REVOLUTION_A; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
        }
      // Stop the execution
      exit(0); // Exit the loop and stop the program
      break;
    case 'b':
      // Enable the motor
      digitalWrite(ENABLE_PIN, LOW);
      // Rotate clockwise
      digitalWrite(DIR_PIN, HIGH);
      for (int i = 0; i < STEPS_PER_REVOLUTION_B; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
        }
      // Stop the execution
      exit(0); // Exit the loop and stop the program
      break;
      }
  char key = keypad.getKey();
  lcd.setCursor(0, 0);
  lcd.print("Park car press #");
  lcd.setCursor(0, 1);
  lcd.print("Back car press *");
  if (key) {
  if (key == '#') {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Parking...");
  switch (command) {
    case 'a':
      // Enable the motor
      digitalWrite(ENABLE_PIN, LOW);
      // Rotate clockwise
      digitalWrite(DIR_PIN, HIGH);
      for (int i = 0; i < STEPS_PER_REVOLUTION_B; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
        }
      // Stop the execution
      exit(0); // Exit the loop and stop the program
      break;
    case 'b':
      // Enable the motor
      digitalWrite(ENABLE_PIN, LOW);
      // Rotate clockwise
      digitalWrite(DIR_PIN, HIGH);
      for (int i = 0; i < STEPS_PER_REVOLUTION_A; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
        }
      // Stop the execution
      exit(0); // Exit the loop and stop the program
      break;
      }
  } else if (key == '*') {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter place:");
  char place = getPlaceFromNumpad();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moving...");
  delay(1000);
  switch (place) {
    case '1':
      // Enable the motor
      digitalWrite(ENABLE_PIN, LOW);

      // Rotate clockwise
      digitalWrite(DIR_PIN, HIGH);
      for (int i = 0; i < STEPS_PER_REVOLUTION_A; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
      }
      // Stop the execution
      exit(0); // Exit the loop and stop the program
      break;
    case '2':
      // Enable the motor
      digitalWrite(ENABLE_PIN, LOW);
      // Rotate clockwise
      digitalWrite(DIR_PIN, HIGH);
      for (int i = 0; i < STEPS_PER_REVOLUTION_B; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
        }
      // Stop the execution
      exit(0); // Exit the loop and stop the program
      break;
    }
  }
}

  if (Serial.available() > 0) {
    char command = Serial.read();
    handleCommand(command);
  }
}

void handleCommand(char command) {
  switch (command) {
    case 'a':
      // Enable the motor
      digitalWrite(ENABLE_PIN, LOW);
      // Rotate clockwise
      digitalWrite(DIR_PIN, HIGH);
      for (int i = 0; i < STEPS_PER_REVOLUTION_A; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
      }
      // Stop the execution
      exit(0); // Exit the loop and stop the program
    break;
    case 'b':
      // Enable the motor
      digitalWrite(ENABLE_PIN, LOW);
      // Rotate clockwise
      digitalWrite(DIR_PIN, HIGH);
      for (int i = 0; i < STEPS_PER_REVOLUTION_B; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(STEP_DELAY);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(STEP_DELAY);
        }
      // Stop the execution
      exit(0); // Exit the loop and stop the program
    break;
  }
}

char getCommandFromPython() {
  while (Serial.available() == 0) {}
  return Serial.read();
}

char getPlaceFromNumpad() {
  char key = keypad.getKey();
  while (!key) {
    key = keypad.getKey();
  }
  return key;
}
void serialEvent1() {
  while (Serial1.available())
   {
    // get the new byte:
    park1_state = (char)Serial1.read();
  }
}
void serialEvent2() {
  while (Serial2.available())
   {
    // get the new byte:
    park2_state = (char)Serial2.read();
  }
}