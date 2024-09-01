### Arduino Code

```cpp
// Define pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Variables to store time and distance
long duration1, duration2;
float distance1, distance2;
float speed;

void setup() {
  // Initialize the Serial Monitor
  Serial.begin(9600);

  // Set the trigger and echo pins as output and input respectively
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Give some time for the sensor to stabilize
  delay(1000);
}

void loop() {
  // Measure the distance at point 1
  distance1 = getDistance();
  
  // Wait for a small time interval (e.g., 100ms)
  delay(100);
  
  // Measure the distance at point 2
  distance2 = getDistance();
  
  // Calculate the speed (distance/time)
  speed = (distance2 - distance1) / 0.1;  // 0.1 seconds is the delay time in seconds
  
  // Print the speed to the Serial Monitor
  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.println(" cm/s");

  // Optional: Add a delay before the next measurement
  delay(500);
}

// Function to get the distance from the ultrasonic sensor
float getDistance() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigger pin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo pin and calculate the distance
  duration1 = pulseIn(echoPin, HIGH);
  float distance = (duration1 * 0.034) / 2;  // Speed of sound wave divided by 2 (round trip)

  return distance; // Return the distance in cm
}
