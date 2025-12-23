#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <SD_MMC.h>
#include <AudioFileSourceSD_MMC.h>
#include <AudioFileSourceID3.h>
#include <AudioGeneratorMP3.h>

#define IIS_ENABLE 0 

#ifdef IIS_ENABLE
  #include <AudioOutputI2S.h>
#else
  #include <AudioOutputI2SNoDAC.h>
#endif

// SDMMC Pins for ESP32 Wrover
#define SD_MMC_CMD 15 
#define SD_MMC_CLK 14 
#define SD_MMC_D0  2  

// I2S Pins
#define I2S_BCLK   26
#define I2S_DOUT   22
#define I2S_LRC    25

AudioGeneratorMP3 *mp3 = nullptr;
AudioFileSourceID3 *id3 = nullptr;
AudioFileSourceSD_MMC *file = nullptr;

#ifdef IIS_ENABLE
  AudioOutputI2S *out = nullptr;
#else
  AudioOutputI2SNoDAC *out = nullptr;
#endif

// Callback to display track info in Serial Monitor
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string) {
  (void)cbData;
  Serial.printf("Metadata %s: ", type);
  Serial.println(string);
}

void setup() {
  WiFi.mode(WIFI_OFF); 
  Serial.begin(115200);
  delay(1000);

  // Initialize SD Card
  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
  if (!SD_MMC.begin("/sdcard", true)) { // true = 1-bit mode
      Serial.println("SD Card Mount Failed!");
      return;
  }
  Serial.println("SD Card Mounted. Starting MP3...");

  audioLogger = &Serial;
  
  // 1. Open the file from SD
  file = new AudioFileSourceSD_MMC("/music/01.mp3");
  
  // 2. Setup ID3 tags
  id3 = new AudioFileSourceID3(file);
  id3->RegisterMetadataCB(MDCallback, (void*)"ID3TAG");

  // 3. Setup Audio Output
  #ifdef IIS_ENABLE
    out = new AudioOutputI2S();
  #else
    out = new AudioOutputI2SNoDAC();
  #endif

  out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  out->SetGain(1.0); // Volume 0.0 to 4.0

  // 4. Start Generator
  mp3 = new AudioGeneratorMP3();
  if (!mp3->begin(id3, out)) {
      Serial.println("Could not start MP3 generator. Check if /music/01.mp3 exists.");
  }
}

void loop() {
  if (mp3 && mp3->isRunning()) {
    if (!mp3->loop()) {
      mp3->stop();
      Serial.println("Playback Stopped.");
    }
  } else {
    // Optional: add logic here to play the next song
    delay(1000);
  }
}