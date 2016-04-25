/*
@brief Test the UTC conversion

@notice Need <Time.h> from http://www.pjrc.com/teensy/td_libs_Time.html

@atuhor Stephan Ruloff
@date 25.04.2016
@copyright GPLv2
*/

#include <TimeZoneInfo.h>
#include <Time.h>

#include "Europe_Berlin.h"

TimeZoneInfo tzi;

void PrintTime(char* str, time_t t)
{
  Serial.print(str);
  Serial.print(hour(t));
  Serial.print(":");
  Serial.print(minute(t));
  Serial.print(":");
  Serial.print(second(t));
  Serial.print(" ");
  Serial.print(day(t));
  Serial.print(".");
  Serial.print(month(t));
  Serial.print(".");
  Serial.print(year(t));
  Serial.println();
}

void setup()
{
  uint8_t i;
  time_t utc;
  time_t local;
  
  Serial.begin(115200);
  Serial.println("TimeZoneInfo-Test");
  
  tzi.setLocation_P(ZI_DATA);
  
  utc = 1459040397L;
  for (i = 0 ; i < 6; i++) {
    PrintTime("UTC=", utc);
    local = tzi.utc2local(utc);
    PrintTime("LOC=", local);
    Serial.println();
    utc++;
    delay(1000);
  }
  Serial.println("Done.");
}

void loop()
{
}
