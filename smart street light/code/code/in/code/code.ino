// IN

// Define the pins for the ultrasonic sensor, and LEDs
#define trigPin 12      // Trigger pin for the ultrasonic sensor
#define echoPin 11      // Echo pin for the ultrasonic sensor

#define led2 2  
#define led3 3  
#define led4 4  
#define led5 5  
#define led6 6


void setup() {
  // Set the pinMode for all pins
  pinMode(trigPin, OUTPUT);       // Trigger pin as OUTPUT
  pinMode(echoPin, INPUT);        // Echo pin as INPUT
  pinMode(led2, OUTPUT);  
  pinMode(led3, OUTPUT);  
  pinMode(led4, OUTPUT);  
  pinMode(led5, OUTPUT);  

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
  if (distance <= 38 && distance > 29) {
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    delay(300);
  } else if (distance <= 29 && distance > 21) {
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    delay(300);
  } else if (distance <= 21 && distance > 18) {
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    delay(300);
  } else if (distance <= 18 && distance > 12) {
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    delay(300);
  } else if (distance <= 12 && distance > 7) {
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    delay(300);
  } else if (distance <= 7) {
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    delay(3000);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);    
  } else if(distance > 46 ){
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }

}
