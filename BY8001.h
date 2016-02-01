// BY8001.h, BY8001 Mp3 Player Function Library
// Date: June 2015
// Author: borland of Arduino forum 
// No affiliation with Balway Electronics Technology or Shenzhen Electronics Technology Ltd.
// Released in public domain. 

#ifndef BY8001_h
#define BY8001_h

#include <Arduino.h>

class BY8001 {
  public:
    BY8001();
    void setup(Stream& serial);
    
    void play();
    void pause();
    void nextTrack();
    void previousTrack();
    void increaseVolume();
    void decreaseVolume();
    void toggleStandbyMode();
    void resetModule();
    void fastForward();
    void fastRewind();
    void stopPlayback();
    void setVolume(int volume);
    void setEqualizerProfile(int equalizerProfile);
    void setLoopPlaybackMode(int loopPlaybackMode);
    void switchFolder(int swDirection);
    void switchDevice(int device);
    void playTrackByIndexNumber(word trackNumber);
    void playTrackFromFolder(int folderNumber, int trackNumber);
    void playInsertionSpot(int trackNumber);
    void playInsertionFromFolder(int folderNumber, int trackNumber);
    
    byte getPlaybackStatus();
    byte getVolumeSetting();
    byte getEqualizerProfile();
    byte getLoopPlaybackMode();
    char* getFirmwareVersion();
    word getNumberOfTracksTF();
    word getNumberOfTracksUSB();
    byte getCurrentPlaybackDevice();
    word getCurrentTrackTF();
    word getCurrentTrackUSB();
    word getElapsedTrackPlaybackTime();
    word getTotalTrackPlaybackTime();
    char* getFileNameCurrentTrack();
    word getNumberOfTracksCurrentFolder();
  
  private:
    Stream *mp3Serial;
    
    char receiveBuffer[15];
    byte sendBuffer[7];
    
    void sendCommand(byte cmd);
    void sendCommand(byte cmd, byte pmtr);
    void sendCommand(byte cmd, word pmtr);
    void sendCommand(byte cmd, byte pmtr1, byte pmtr2);
    void fillCheckCode();
    byte getCheckCode();
    void txFunc();
    void rxFunc(int length);
    word getReply(int length, int offset);
    
};
    
#endif