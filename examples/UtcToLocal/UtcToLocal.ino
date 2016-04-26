/*
@brief Test the UTC conversion

@note Need <Time.h> from http://www.pjrc.com/teensy/td_libs_Time.html

@atuhor Stephan Ruloff
@date 25.04.2016
@copyright GPLv2
*/

#include <TimeZoneInfo.h>
#include <Time.h>

#include "Europe_Berlin.h"
#include "America_Los_Angeles.h"


TimeZoneInfo tzi;


void Print2Digit(int val)
{
  if (val < 10) {
    Serial.print("0");
  }
  Serial.print(val);
}

void PrintTime(time_t t)
{
  Print2Digit(hour(t));
  Serial.print(":");
  Print2Digit(minute(t));
  Serial.print(":");
  Print2Digit(second(t));
  Serial.print(" ");
  Print2Digit(day(t));
  Serial.print(".");
  Print2Digit(month(t));
  Serial.print(".");
  Serial.print(year(t));
}

void PrintTimeInfo(time_t utc)
{
  time_t local;

  Serial.print("UTC=");
  PrintTime(utc);
  Serial.println();

  local = tzi.utc2local(utc);
  Serial.print("LOC=");
  PrintTime(local);
  if (tzi.isDst()) {
     Serial.print(" DST");
  }
  Serial.print(" ");
  Serial.print(tzi.getShortName());
  Serial.println(); 
}

void setup()
{
  uint8_t i;
  time_t utc;

  Serial.begin(115200);
  Serial.println("TimeZoneInfo-Test");
  Serial.println();

  tzi.setLocation_P(ZI_DATA);
  Serial.println(ZI_NAME);
  utc = 1459040400L - 3;
  for (i = 0 ; i < 6; i++) {
    PrintTimeInfo(utc);
    Serial.println();
    utc++;
    delay(1000);
  }

  Serial.println();
  tzi.setLocation_P(ZI_LA_DATA);
  Serial.println(ZI_LA_NAME);
  utc = 1478422800L - 3;
  for (i = 0 ; i < 6; i++) {
    PrintTimeInfo(utc);
    Serial.println();
    utc++;
    delay(1000);
  }

  Serial.println("Done.");
}

void loop()
{
}
