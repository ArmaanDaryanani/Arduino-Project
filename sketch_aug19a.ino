const int micPin = A1;
const int transducerPin = 9; // Must be a PWM pin

void setup() {
  pinMode(micPin, INPUT);
  pinMode(transducerPin, OUTPUT);
  analogReference(DEFAULT); // Set reference voltage for ADC

  Serial.begin(9600); // Start the serial communication
}

void loop() {
  int micValue = analogRead(micPin);
  int pwmValue = map(micValue, 0, 1023, 0, 255); // Convert 10-bit ADC value to 8-bit PWM value

  // Output the microphone value to Serial
  Serial.println(micValue);

  analogWrite(transducerPin, pwmValue);
  delayMicroseconds(125);  // Roughly 8kHz sample rate
}
