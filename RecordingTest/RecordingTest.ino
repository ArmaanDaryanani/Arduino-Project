int buttonPin = 3;
int buttonState = 0;
int microphonePin = A0;
int ledPin = 6;
const int chipSelect = 10;
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
TMRpcm audio;

void setup() 
{
  audio.speakerPin = 9;
  audio.CSPin = chipSelect;
  audio.setVolume(6);
  
  Serial.begin(9600);
  pinMode(buttonPin, OUTPUT);
  pinMode(microphonePin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.print("Initializing SD Card...");
  if(!SD.begin())
  {
    Serial.println("Initialization failed");
    return;
  }

  Serial.println("Initialization done");

}

void loop() 
{
  int microphoneVal = analogRead(microphonePin);
  buttonState = digitalRead(buttonPin);

  if(buttonState > 0)
  {
    Serial.println(microphoneVal);
    audio.startRecording("test.wav",16000,A0);
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(1000);
    audio.stopRecording("test.wav");
    //audio.play("test.wav");
    delay(6000);

    for(int i = 0; i < 5; i++)
    {
      audio.play("test.wav");
      delay(6000);
    }
    

  }
  
  
  


}

/*
 * Arduino will record data from the microphone while button is held.
 * It will then store that data in the SD card
 * after a button press, it will play the recording back through the transducer.
 */
