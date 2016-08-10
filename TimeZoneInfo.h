#ifndef __TIMEZONEINFO_H__
#define __TIMEZONEINFO_H__

#include <Arduino.h>

#pragma pack(push, 1)
typedef struct
{
  int32_t tt_gmtoff;
  int8_t tt_isdst;
  uint8_t tt_abbrind;
} ttinfo;
#pragma pack(pop)

class TimeZoneInfo
{
public:
  TimeZoneInfo();
  void setLocation_P(const byte* tzfile);
  int32_t utc2local(int32_t utc);
  int32_t local2utc(int32_t local);
  String getShortName(void); // e.g. CEST/CET
  boolean isDst(void);
private:
  int32_t findTimeInfo(int32_t t);
  uint32_t read32(unsigned long pos);
  uint8_t read8(unsigned long pos);
  byte* mTzFile;
  ttinfo mTimeInfo;
  unsigned long mCharPos;
  uint32_t mCharLen;
};

#endif
