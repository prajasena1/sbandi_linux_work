#!/home/sbandi/anaconda2/python2
import csv
import math
import os, sys
import calendar
import subprocess
from subprocess import PIPE, Popen
import matplotlib.pyplot as plt

if len(sys.argv) < 4:
    print "usage: %s year month geo_location" % (sys.argv[0])
    sys.exit(1)

try:
    data_year = int(sys.argv[1])
    mon = int(sys.argv[2])
    geo_loc = sys.argv[3]
except:
    print "please supply valid month ", sys.argv[1]
    sys.exit(2)

#execute the os command and return the output of command
def cmdline(command):
    process = Popen(
        args=command,
        stdout=PIPE,
        shell=True
    )
    return process.communicate()[0]

fc_dd_time_vs_ws = {}
data_type = 'sfc'

grib_data_dir="%4d_%s_grib" % (data_year, data_type)
grib_file="%s/%4d-%02d-%s.grib" % (grib_data_dir, data_year, mon, data_type)
output = cmdline("grib_get -p dataDate:s,dataTime:s,shortName:s -w shortName:s=10u/10v -l %s,1 %s" % (geo_loc, grib_file))
lines = output.split('\n')

for line in lines:
    if len(line) == 0:
        continue
    dd, tt, param, val = line.split()
    if param == '10u':
        u_val = val
    elif param == '10v':
        #convert m/s to km/h
        wind_speed_kmph = 3.6 * math.sqrt(float(u_val)**2+float(val)**2)
        fc_dd_time = float(dd[6:])+float(tt[0:2])/24.0 - 1.0
        fc_dd_time_vs_ws[fc_dd_time] = float(wind_speed_kmph)
    else:
        continue

sorted_vals = []
for k in sorted(fc_dd_time_vs_ws.keys()):
    sorted_vals.append(fc_dd_time_vs_ws[k])

print sorted(fc_dd_time_vs_ws.keys())
print sorted_vals

plt.plot(sorted(fc_dd_time_vs_ws.keys()), sorted_vals, 'b-', label='%d %s' % (data_year, calendar.month_name[mon]))
plt.title('wind speed in %d %s' % (data_year, calendar.month_name[mon]), size='large')
plt.xlabel('day of month %s' % (calendar.month_name[mon]))
plt.ylabel('wind speed in kmph')
plt.show()
