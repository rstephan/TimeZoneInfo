/**
@brief TimeZoneInfo
With the use of the tzdata your project can now run in local time.
Getting UTC time is easy, (GPS, NTP, ..) but local time is not.
GMT+x works mostly only for half of a year. (Daylight-Saving-Time) DST is evil!
You can't calculate it! This is why linux uses a database to make DST work.
So, why not using it for your Arduino?
It is a bit "heavy", prox. 4kB for the database of one location + the code to make it work.

@warning This is a 32-Bit version! Year 2038 will come fast!

@author Stephan Ruloff
@date 24.04.2016
@copyright GPLv2
*/

#include "TimeZoneInfo.h"


TimeZoneInfo::TimeZoneInfo()
{
  mTzFile = 0;
  mCharPos = 0;
  mCharLen = 0;
  memset(&mTimeInfo, 0, sizeof(mTimeInfo));
}

void TimeZoneInfo::setLocation_P(const byte* tzfile)
{
  mTzFile = (byte*)tzfile;
  mCharPos = 0;
  mCharLen = 0;
  memset(&mTimeInfo, 0, sizeof(mTimeInfo));
}

int32_t TimeZoneInfo::utc2local(int32_t utc)
{
  int32_t offs;

  offs = findTimeInfo(utc);

  return utc + offs;
}

int32_t TimeZoneInfo::local2utc(int32_t local)
{
  int32_t offs;

  offs = findTimeInfo(local);

  return local - offs;
}

// e.g. CEST/CET
String TimeZoneInfo::getShortName(void)
{
  uint32_t pos = mTimeInfo.tt_abbrind;
  String s;
  uint8_t c;
  uint8_t nullCnt = 0;

  if (mCharPos) {
    while (pos < mCharLen) {
      c = read8(mCharPos + pos);
      if (c == 0) {
        break;
      } else {
        s += (char)c;
      }
      pos++;
    }
  }

  return s;
}

boolean TimeZoneInfo::isDst(void)
{
  return mTimeInfo.tt_isdst != 0;
}

uint32_t TimeZoneInfo::read32(unsigned long pos)
{
  uint32_t val = 0;
  
  val += (uint32_t)pgm_read_byte(&mTzFile[pos + 0]) << 24;
  val += (uint32_t)pgm_read_byte(&mTzFile[pos + 1]) << 16;
  val += (uint32_t)pgm_read_byte(&mTzFile[pos + 2]) << 8;
  val += (uint32_t)pgm_read_byte(&mTzFile[pos + 3]);
  
  return val;
}

uint8_t TimeZoneInfo::read8(unsigned long pos)
{
  uint8_t val = 0;
  
  val = (uint32_t)pgm_read_byte(&mTzFile[pos]);
  
  return val;
}

int32_t TimeZoneInfo::findTimeInfo(int32_t t)
{
  uint32_t magic;
  uint32_t gmtcnt;
  uint32_t stdcnt;
  uint32_t leapcnt;
  uint32_t timecnt;
  uint32_t typecnt;
  uint32_t charcnt;
  uint32_t i;
  uint32_t valTime;
  uint32_t valTimeOld;
  uint32_t valIndex;
  boolean found = false;
  unsigned long pos;
  
  magic = read32(0);
  if (magic != 0x545a6966) {
    return 0;
  }
  gmtcnt = read32(20);
  stdcnt = read32(24);
  leapcnt = read32(28);
  timecnt = read32(32);
  typecnt = read32(36);
  charcnt = read32(40);
  
  valTimeOld = read32(44);
  for (i = 1; i < timecnt; i++) {
    valTime = read32(44 + (i * 4));
    if (valTimeOld <= t && t < valTime) {
      found = true;
      i--;
      break;
    }
    valTimeOld = valTime;
  }
  if (found) {
    valIndex = read8(44L + (timecnt * 4) + i);
    if (valIndex < typecnt) {
      pos = 44L + (timecnt * 4) + timecnt + (sizeof(ttinfo) * valIndex);
      mTimeInfo.tt_gmtoff = read32(pos);
      mTimeInfo.tt_isdst = read8(pos + 4);
      mTimeInfo.tt_abbrind = read8(pos + 5);
      mCharPos = 44L + (timecnt * 5) + (sizeof(ttinfo) * typecnt) + (8 * leapcnt);
      mCharLen = charcnt;
    }
  }
  
  return mTimeInfo.tt_gmtoff;
}
