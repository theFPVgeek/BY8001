// BY8001 MP3 Player Library, Example Program 2; Playback From Folders Demo
// 
// This example sketch uses SoftwareSerial to communnicate with BY8001
// and plays tracks from folders using command Next Folder.
// and sends track file names to Arduino IDE for display on serial monitor 
//
// Recommend module ABC keypad mode set to '111' in order to support all serial commands 
// Uses Arduino's hardware serial port to connect to PC

// Requires 3.3V TTL level RX/TX such as Ardiuno Mini Pro (8Mhz, 3.3V)
// can use 5V/3.3V level shifter or try 1K ohm resistor on TX line as shown in BY8001 datasheet
//
// Connect Arduino's RX pin to BY8001's TX pin 3
// Connect Arduino's TX pin to BY8001's RX pin 2
//

#include <SoftwareSerial.h>
#include <BY8001.h>

// function prototype
bool checkFormp3IsStopped();

SoftwareSerial mp3Serial(10, 9);  // RX, TX
BY8001 mp3;  // creating an instance of class BY8001 and call it 'mp3'

void setup(){
  Serial.begin(9600);  // set serial monitor baud rate to Arduino IDE
  mp3Serial.begin(9600);  // BY8001 set to 9600 baud (required)  
  mp3.setup(mp3Serial); // tell BY8001 library which serial port to use. 
  
  delay(800);  // allow time for BY8001 cold boot; may adjust depending on flash storage size

  char * fwVersion = mp3.getFirmwareVersion();
  Serial.print("BY8001 module firmware version: "); Serial.println(fwVersion);

  int by8001_VolumeSetting = 15; //  Set volume to 15 (0-30 range) if not already set
  if ((int)mp3.getVolumeSetting() != by8001_VolumeSetting) mp3.setVolume(by8001_VolumeSetting);
  
  int volume = mp3.getVolumeSetting(); // just verifying has been set before serial print to console
  Serial.print("speaker volume setting: "); Serial.println(volume);
  
  mp3.playTrackFromFolder(1, 1); 
}

void loop(){
  static word totalTime, elapsedTime, playback;
  
  delay(900);

  if (checkFor_mp3IsStopped() == true){
    mp3.switchFolder(1); 
    char* trackFileName = mp3.getFileNameCurrentTrack();
    Serial.print("\n\nplaying file name: "); Serial.println(trackFileName);
    totalTime = mp3.getTotalTrackPlaybackTime();
    Serial.print("playback duration: "); Serial.print(totalTime); Serial.println(" seconds");
  }
  elapsedTime = mp3.getElapsedTrackPlaybackTime();
  playback = totalTime - elapsedTime;
  Serial.print(playback); Serial.print(",");
  
  delay(200);
}

// check if Mp3 Player is stopped
bool checkFor_mp3IsStopped() {
 if (mp3Serial.available() > 0){
   if (mp3.getPlaybackStatus() == 0){
     return true;
   }
 }
 else return false; 
}

/*   command usage:
  mp3.play();
  mp3.pause();
  mp3.nextTrack();
  mp3.previousTrack();
  mp3.increaseVolume();
  mp3.decreaseVolume();
  mp3.toggleStandbyMode();
  mp3.resetModule();
  mp3.fastForward();
  mp3.fastRewind();
  mp3.stopPlayback();
  mp3.setVolume(int volume);  // 0-30
  mp3.setEqualizerProfile(int equalizerProfile); // 0/1/2/3/4/5  Normal/Pop/Rock/Jazz/Classic/Bass
  mp3.setLoopPlaybackMode(int loopPlaybackMode); // 0/1/2/3/4 All/Folder/Single/Random/Disabled 
  mp3.switchFolder(int swDirection); // 0/1 Previous/Next
  mp3.switchDevice(int device); // 0/1 USB/TFcard
  mp3.playTrackByIndexNumber(word trackNumber); // 1-65535
  mp3.playTrackFromFolder(int folderNumber, int trackNumber);  00-99 folder, 001-255 track  
  mp3.playInsertionSpot(int trackNumber);  // TF device not supported
  mp3.playInsertionFromFolder(int folderNumber, int trackNumber);  // TF device not supported
  
  byte playbackStatus = mp3.getPlaybackStatus(); // 
  byte volumeSetting = mp3.getVolumeSetting();
  byte equalizerProfile = mp3.getEqualizerProfile();
  byte loopPlaybackMode = mp3.getLoopPlaybackMode();
  char* fwVersion = mp3.getModuleFirmwareVersion(); Serial.println("firmware ver.: " + fwVersion);
  word numOfTracksTF = mp3.getNumberOfTracksTF();
  word numOfTracksUSB = mp3.getNumberOfTracksUSB();
  byte playbackDevice = mp3.getCurrentPlaybackDevice();
  word currentTrackTF = mp3.getCurrentTrackTF();
  word currentTrackUSB = mp3.getCurrentTrackUSB();
  word elapsedTrackPlaybackTime = mp3.getElapsedTrackPlaybackTime();
  word totalTrackPlaybackTime = mp3.getTotalTrackPlaybackTime();
  char* trackFileName = mp3.getFileNameCurrentTrack(); Serial.print("track file name: "); Serial.println(trackFileName);
  word numTracksInFolder = mp3.getNumberOfTracksCurrentFolder();
  */
