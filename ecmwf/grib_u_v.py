from numpy import *
import sys,math,os
import argparse
from gribapi import *
 
grib_file_name = sys.argv[1]
if not os.path.isfile(grib_file_name):
    print "[ERROR] file %s does not exist" %(grib_file_name)
    sys.exit(1)

PARAMS = ["u","v"]

index_keys = ["date","time","shortName"]

iiduv = grib_index_new_from_file(grib_file_name,index_keys)
for date in grib_index_get(iiduv,'date'):
    grib_index_select(iiduv,'date',date)
    # iterate step
    for time in grib_index_get(iiduv,'time'):
        grib_index_select(iiduv,'time',time)
        for param in PARAMS:
            #grib_index_select(iiduv,'level',1)
            grib_index_select(iiduv,'shortName',param)
            gidp = grib_new_from_index(iiduv)
            values_lev[param] = grib_get_values(gidp)
            grib_release(gidp)
grib_index_release(iiduv)
