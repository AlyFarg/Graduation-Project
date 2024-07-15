// Define the pins for the ultrasonic sensor, buzzer, and LEDs
#define trigPin 8         // Trigger pin for the ultrasonic sensor
#define echoPin 9         // Echo pin for the ultrasonic sensor

#define green_Led 11      // Green LED pin for indicating safe distance
#define red_Led 12        // Red LED pin for indicating close proximity

#define buzzer 10        // Buzzer pin for audio feedback

bool park_space2 = false;

void setup() {
  // Set the pinMode for all pins
  pinMode(trigPin, OUTPUT);        // Trigger pin as OUTPUT
  pinMode(echoPin, INPUT);         // Echo pin as INPUT
  pinMode(buzzer, OUTPUT);      // Buzzer pin as OUTPUT
  pinMode(green_Led, OUTPUT);      // Red LED pin as OUTPUT
  pinMode(red_Led, OUTPUT);    // Green LED pin as OUTPUT

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  float duration, distance;

  // Send a brief LOW pulse to the trigger pin to start the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);      // Send a brief HIGH pulse to trigger the sensor
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int dis=0;
  // Measure the duration of the echo pulse to calculate the distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;  // Calculate distance in centimeters
  // dis=((duration / 2) / 29.1)*1000;
  // Print the distance to the serial monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Based on the distance, control LEDs and buzzer for feedback
  if (distance <= 14 && distance > 4.5) {
    digitalWrite(green_Led, LOW);
    digitalWrite(red_Led, HIGH);
    tone(buzzer, 2000);  // Turn on the buzzer
    delay(300);
    digitalWrite(green_Led, LOW);
    digitalWrite(red_Led, LOW);
    noTone(buzzer);  // Turn off the buzzer
    delay(300);
    park_space2 = true;
  } else if (distance <= 4.5 && distance > 3) {
    digitalWrite(green_Led, LOW);
    digitalWrite(red_Led, HIGH);
    park_space2 = true;
  } else if (distance <= 3) {
    digitalWrite(green_Led, LOW);
    digitalWrite(red_Led, HIGH);
    tone(buzzer, 1000);  // Turn on the buzzer
    park_space2 = true;
  } else {
    digitalWrite(green_Led, HIGH);
    digitalWrite(red_Led, LOW);
    noTone(buzzer);  // Turn off the buzzer
    park_space2 = false;
  }
}
