# TimeZoneInfo

With the use of the tzdata your project can now run in local time.
Getting UTC time is easy, (GPS, NTP, ..) but local time is not.
GMT plus x works mostly only for half of a year. (Daylight-Saving-Time) DST is evil!
You can't calculate it! This is why linux uses a database to make DST work.
So, why not using it for your Arduino?
It is a bit "heavy", prox. 4kB for the database of one location + the code to make it work.

**This is a 32-Bit version! Year 2038 will come fast!**

# Example


## UtctoLocal


```
TimeZoneInfo-Test

Berlin
UTC=00:59:57 27.03.2016
LOC=01:59:57 27.03.2016 CET

UTC=00:59:58 27.03.2016
LOC=01:59:58 27.03.2016 CET

UTC=00:59:59 27.03.2016
LOC=01:59:59 27.03.2016 CET

UTC=01:00:00 27.03.2016
LOC=03:00:00 27.03.2016 DST CEST

UTC=01:00:01 27.03.2016
LOC=03:00:01 27.03.2016 DST CEST

UTC=01:00:02 27.03.2016
LOC=03:00:02 27.03.2016 DST CEST


Los_Angeles
UTC=08:59:57 06.11.2016
LOC=01:59:57 06.11.2016 DST PDT

UTC=08:59:58 06.11.2016
LOC=01:59:58 06.11.2016 DST PDT

UTC=08:59:59 06.11.2016
LOC=01:59:59 06.11.2016 DST PDT

UTC=09:00:00 06.11.2016
LOC=01:00:00 06.11.2016 PST

UTC=09:00:01 06.11.2016
LOC=01:00:01 06.11.2016 PST

UTC=09:00:02 06.11.2016
LOC=01:00:02 06.11.2016 PST

Done.


```

# Database

Getting the tzfile-database is easy in linux.

Usualy these files are in /usr/share/zoneinfo.

## Converting to a C-header file:

1. With the "build-in" xxd-tool

    cd /usr/share/zoneinfo/Europe
    # Add PROGMEM, if no your are running out of RAM.
    xxd -i Berlin | sed -e 's/unsigned char/unsigned char PROGMEM/' > ~/Arduino/MyProject/Berlin.h

2. With my binhex-Tool

    ./binhex -f /usr/share/zoneinfo/America/Los_Angeles -p ZI_LA > ~/Arduino/MyProject/America_Los_Angeles.h


# License

GPLv2
