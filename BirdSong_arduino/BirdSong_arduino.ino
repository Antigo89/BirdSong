#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#define TESTMODE
#define LED_ACTIVATE

#define KEY_PIN 2
#define AUDIO_PIN 9 //9 or 10

TMRpcm tmrpcm;
volatile bool playmode = false;

void keyIsr(void){
  if(playmode){
    playmode = false;
  }else{
    playmode = true;
  }
}

void setup() {
  tmrpcm.speakerPin = AUDIO_PIN;
  #ifdef TESTMODE
  Serial.begin(9600);
  #endif
  pinMode(KEY_PIN, INPUT_PULLUP);
  attachInterrupt(0, keyIsr, FALLING);

  if (!SD.begin(4)) {
    #ifdef TESTMODE
    Serial.println("Ошибка инициализации SD-карты!");
    #endif
  }else{
    #ifdef TESTMODE
    Serial.println("SD init");
    #endif
  }
  tmrpcm.quality(1);
  tmrpcm.volume(5);
    
}

void loop() {
  if(playmode){
    if(!tmrpcm.isPlaying()){
      digitalWrite(AUDIO_PIN, LOW);
      if (SD.exists("canary.wav")) {
        #ifdef TESTMODE
        Serial.println("Play canary.wav");
        #endif
        
        tmrpcm.play("canary.wav");
      }
    }
  }else{
    tmrpcm.stopPlayback();
    digitalWrite(AUDIO_PIN, LOW);
  }
  #ifdef TESTMODE
  Serial.print("playmode = ");
  Serial.println(playmode);
  #endif
  _delay_ms(1000);
}