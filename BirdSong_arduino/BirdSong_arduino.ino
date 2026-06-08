#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>

TMRpcm tmrpcm;

void setup() {
  tmrpcm.speakerPin = 9; // Для Arduino Nano/Uno это строго пин 9!
  
  Serial.begin(9600);
  
  if (!SD.begin(4)) {
    Serial.println("Ошибка инициализации SD-карты!");
    return;
  }else{
    Serial.println("SD ok!");
    return;
  }
  
  tmrpcm.volume(5);      // Громкость от 0 до 7
  tmrpcm.play("canary.wav");   // Воспроизведение файла
}

void loop() {
  // Код программы
}