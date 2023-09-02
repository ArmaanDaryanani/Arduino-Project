#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>

TMRpcm audio;

const int buttonPin = 3;
const int ledPin = 6;
const int chipSelect = 10;

SoftwareSerial HM10(2, 4);
char appData;
bool isRecording = false;
byte terminationSequence[] = {0xFF, 0xFF, 0xFF, 0xFF};

void setup() {
  audio.speakerPin = 9;
  audio.CSPin = chipSelect;
  audio.setVolume(6);

  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.print(F("Initializing SD Card..."));
  if (!SD.begin(chipSelect)) {
    Serial.println(F("Failed"));
    return;
  }
  
  Serial.println(F("Done"));
  Serial.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
  Serial.println(F("HM10 loading: Serial start at 9600"));
  HM10.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && !isRecording) {
    audio.startRecording("test.wav", 8000, A1);
    isRecording = true;
    Serial.println(F("Started Recording"));
    //digitalWrite(ledPin, HIGH);
    delay(1000);  // Debounce delay
  }
  else if (buttonState == LOW && isRecording) {
    audio.stopRecording("test.wav");
    isRecording = false;
    Serial.println(F("Stopped Recording"));
    //digitalWrite(ledPin, LOW);
    delay(1000);  // Debounce delay
    Serial.println(F("Now playing back audio for debug"));
    audio.play("test.wav");

    while(audio.isPlaying()){}
    audio.stopPlayback();
    sendFile();
  }
}

void sendFile() {
  File myFile = SD.open("test.wav");
  if (!myFile) {
    Serial.println(F("Error opening wav file"));
    return;
  }

  byte buffer[300];  // Change buffer size back to 20
  unsigned long fileSize = myFile.size();
  unsigned long bytesSent = 0;

  while (myFile.available()) {
    int bytesRead = myFile.read(buffer, sizeof(buffer));
    HM10.write(buffer, bytesRead);
    bytesSent += bytesRead;

    float percentage = ((float)bytesSent / (float)fileSize) * 100;
    Serial.print(F("Sent: "));
    Serial.print(bytesSent);
    Serial.print(F(" bytes ("));
    Serial.print(percentage, 2);
    Serial.println(F("%)"));
  }

  HM10.write(terminationSequence, 4);
  Serial.println(F("Finished sending data"));
  myFile.close();
}
