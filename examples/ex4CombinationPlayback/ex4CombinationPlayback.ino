// BY8001 MP3 Player Library, Example Program 4; Combination Playback Demo
// Date: June 2015
// Author: borland of Arduino forum 
// No affiliation with Balway Electronics Technology or Shenzhen Electronics Technology Ltd.
// Released in public domain. 
//
// This example uses SoftwareSerial to communnicate with BY8001...
// and demonstrates combination playback list feature. 
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

SoftwareSerial mp3Serial(10, 9);  // RX, TX
BY8001 mp3;  // creating an instance of class BY8001 and call it 'mp3'

void setup(){
  
  mp3Serial.begin(9600);  // BY8001 set to 9600 baud (required)  
  mp3.setup(mp3Serial); // tell BY8001 library which serial port to use. 
  
  delay(800);  // allow time for BY8001 cold boot; may adjust depending on flash storage size

  int by8001_VolumeSetting = 15; //  Set volume to 15 (0-30 range) if not already set
  if ((int)mp3.getVolumeSetting() != by8001_VolumeSetting) mp3.setVolume(by8001_VolumeSetting);
  
  // Combination Playback setup and command by.... stream of play track by index number commands
  word comboPlaybackList[10] = {1,2,3,4,5,1,2,3,4,5}; // BY8001 supports list length up to 10 tracks, index up to 65,535 
  for (int i=0; i<10; i++) mp3.playTrackByIndexNumber(comboPlaybackList[i]);

  // Note: Sending any commands during combination play cancels playback list

}

void loop(){
  // do some non-mp3 stuff here...
}

/*   command set usage:
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
