#include <SoftwareSerial.h> //bluetooth

#define BUTTON_PIN 2 //button to digital pin 2
#define MIC_PIN A1 //analog pin to A0
#define BT_RX_PIN 10 //bluetooth rx pin 10
#define BT_TX_PIN 11 //blueooth tx pin 11
#define TRANSDUCER_PIN 3 //transducer pin

const int microphonePin = A1;
int microphoneValue = 0;
int baseline = 0;
float multiplier = 5.0;

const int maxSamples = 500;
int audioSamples[maxSamples];
int sampleIndex = 0;
int mic = 0;
int amplitude = 0;

SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN); //software serial port for bluetooth

void setup()
{
  pinMode(TRANSDUCER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); //button pin as input with internal pull-up resistor
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop()
{
  /*for (sampleIndex = 0; sampleIndex < maxSamples; sampleIndex++)
  {
    audioSamples[sampleIndex] = analogRead(microphonePin);
    delayMicroseconds(125); //for sampling rate of 8kHz
  }*/

  

  mic = analogRead(microphonePin);
  amplitude = abs(mic - baseline);
  
  Serial.println(amplitude);

  analogWrite(TRANSDUCER_PIN, amplitude);

  //Play back the response through the bone conductor transducer
  /*for (sampleIndex = 0; sampleIndex < maxSamples; sampleIndex++)
  {
    analogWrite(TRANSDUCER_PIN, audioSamples[sampleIndex] / 4);
    Serial.println(audioSamples[sampleIndex]);
    delayMicroseconds(125);
  }
  delay(1000);*/
  
  if (digitalRead(BUTTON_PIN) == LOW) //check if button is pressed
  {
    delay(10); //debounce

    if (digitalRead(BUTTON_PIN) == LOW) //check again if button is pressed
    {
      /**microphone recording process(might look different)**/
      //....

      //sends recorded data to smartphone
      BTSerial.write("Your recorded data"); //replace with actual data

      //add mechanism to detect when transmission is done
      //...

      //Await a response from the smartphone
      while (!BTSerial.available()); //Wait until theres data in the bluetooth serial buffer

      //Read response from the smartphone
      String response = BTSerial.readString();



    }

    delay(50); //loop delay to reduce CPU usage, might need adjusting
  }



}
