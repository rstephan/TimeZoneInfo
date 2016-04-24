#ifndef __TIMEZOMEINFO_H__
#define __TIMEZOMEINFO_H__

#include <Arduino.h>

class TimeZoneInfo
{
public:
  void setLocaltion_P(const byte* tzfile);
  int32_t utc2local(int32_t utc);
  int32_t local2utc(int32_t local);
  String getShortName(int32_t t); // e.g. CEST/CET
  boolean isDst(int32_t t);
private:
  void findTimeInfo(int32_t t);
  uint32_t read32(unsigned long pos);
  uint8_t read8(unsigned long pos);
  byte* mTzFile;
};

#endif
