
const int triggerPin = 25;
const int echoPin = 26;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200); // Starts the serial communication
  pinMode(triggerPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}


void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  delay(500);
}
