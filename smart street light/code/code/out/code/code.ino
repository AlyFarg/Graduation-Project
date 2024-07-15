// out

// Define the pins for the ultrasonic sensor, and LEDs
#define trigPin 12      // Trigger pin for the ultrasonic sensor
#define echoPin 11      // Echo pin for the ultrasonic sensor

#define led5 5  
#define led6 6  
#define led7 7  
#define led8 8  
#define led9 9  

void setup() {
  // Set the pinMode for all pins
  pinMode(trigPin, OUTPUT);       // Trigger pin as OUTPUT
  pinMode(echoPin, INPUT);        // Echo pin as INPUT
  pinMode(led5, OUTPUT);  
  pinMode(led6, OUTPUT);  
  pinMode(led7, OUTPUT);  
  pinMode(led8, OUTPUT);  
  pinMode(led9, OUTPUT);  

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  long duration, distance;

  // Send a brief LOW pulse to the trigger pin to start the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Send a brief HIGH pulse to trigger the sensor
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse to calculate the distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;  // Calculate distance in centimeters

  // Print the distance to the serial monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // Based on the measured distance, control LEDs to indicate proximity levels.
  if (distance <= 4) {
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
    delay(300);
  } else if (distance <= 7 && distance > 4.5) {
    digitalWrite(led5, LOW);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
    delay(300);
  } else if (distance <= 13 && distance > 7.5) {
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
    delay(300);
  } else if (distance <= 15 && distance > 13.5) {
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, HIGH);
    digitalWrite(led9, LOW);
    delay(300);
  } else if (distance <= 18 && distance > 15.5) {
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, HIGH);
    digitalWrite(led9, LOW);
    delay(300);
  } else if (distance <= 23 && distance > 18.5) {
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, HIGH);
    digitalWrite(led9, HIGH);
    delay(300);
  } else {
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
  }

}
