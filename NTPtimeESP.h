/*

   NTPtime for ESP8266
   This routine gets the unixtime from a NTP server and adjusts it to the time zone and the
   Middle European summer time if requested

  Author: Andreas Spiess V1.0 2016-6-28

  Based on work from John Lassen: http://www.john-lassen.de/index.php/projects/esp-8266-arduino-ide-webconfig

*/
#ifndef NTPtime_h
#define NTPtime_h

#include <Arduino.h>
#if defined(esp8266)||defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#if defined(esp32)||defined(ESP32)
#include <WiFi.h>
#endif
#include <WiFiUdp.h>

struct strDateTime
{
  byte hour;
  byte minute;
  byte second;
  int year;
  byte month;
  byte day;
  byte dayofWeek;
  boolean valid;
};

class NTPtime {
  public:
    NTPtime(String NTPtime);
    strDateTime getNTPtime(float _timeZone, boolean _DayLightSaving);
    void printDateTime(strDateTime _dateTime);
    bool setSendInterval(unsigned long _sendInterval);  // in seconds
    bool setRecvTimeout(unsigned long _recvTimeout);    // in seconds
    strDateTime ConvertUnixTimestamp( unsigned long _tempTimeStamp);

  private:
    bool _sendPhase;
    unsigned long _sentTime;
    unsigned long _sendInterval;
    unsigned long _recvTimeout;

    boolean summerTime(unsigned long _timeStamp );
    boolean daylightSavingTime(unsigned long _timeStamp);
    unsigned long adjustTimeZone(unsigned long _timeStamp, float _timeZone, byte _DayLightSavingSaving);
    WiFiUDP UDPNTPClient;
};
#endif
