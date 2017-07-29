#!/usr/bin/env python
import sys, time
import calendar
from ecmwfapi import ECMWFDataServer
from random import randint

if len(sys.argv) < 2:
    print "usage: download_sfc.py year"
    sys.exit(1)

#pressure level
level_type = "pl"

COLOR_GREEN="\033[32m"
COLOR_RED="\033[31m"
COLOR_BROWN="\033[33m"
COLOR_MAGENTA="\033[35m"
COLOR_CYAN="\033[36m"
COLOR_LIGHTGRAY="\033[37m"
BOLD_ON="\033[1m"
DARKER_ON="\033[2m"
UNDERLINE_ON="\033[4m"
STRIKE_ON="\033[7m"
COLOR_DEFAULT="\033[0m"

try:
    data_year = int(sys.argv[1])
except:
    print "please supply valid year ", sys.argv[1]
    sys.exit(2)

server = ECMWFDataServer()

def download_grib_files(data_year, data_month):
    mon_dd_first, mon_dd_last = calendar.monthrange(data_year, data_month)
    print "for year %d month %d mon_dd_first %d mon_dd_last %d" % (data_year, data_month, mon_dd_first, mon_dd_last)
    server.retrieve({
        'stream'    : "oper",
        'levtype'   : level_type,
        'param'     : "130.128/131.128/132.128/135.128/248.128",
        'dataset'   : "interim",
        'step'      : "0",
        'area'      : "40/60/1/100",
        'grid'      : "0.25/0.25",
        'time'      : "0000/0600/1200/1800",
        'date'      : "%d-%02d-%02d/to/%d-%02d-%02d" % (data_year, data_month, mon_dd_first, data_year, data_month, mon_dd_last),
        'type'      : "an",
        'class'     : "ei",
        'RESOL'     : "AV",
        'target'    : "%d-%02d-%s.grib" % (data_year, data_month, level_type)
    })

for mon in range(1,12+1):
    print COLOR_GREEN, "getting %s for year %d month %d" % (level_type, data_year, mon), COLOR_DEFAULT
    download_grib_files(data_year, mon)
    sleep_sec = randint(10,300)
    print COLOR_BROWN, "sleep for %d" % (sleep_sec), COLOR_DEFAULT
    time.sleep(sleep_sec)

