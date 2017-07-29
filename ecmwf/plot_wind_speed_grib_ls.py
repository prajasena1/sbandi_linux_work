#!/home/sbandi/anaconda2/python2
import csv
import math
import os, sys
import calendar
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

fc_dd_time_vs_ws = {}

for fc_time in ['0000', '0600', '1200', '1800']:
    os.system("./calc_wind_speed.sh %04d %02d %s %s" % (data_year, mon, fc_time, geo_loc))
    reader = csv.reader(open('wind_date_versus_uv.csv', 'r'))
    for row in reader:
        dd,u,v = row    
        #convert m/s to km/h
        wind_speed_kmph = 3.6 * math.sqrt(float(u)**2+float(v)**2)
        fc_dd_time = float(dd[6:])+float(fc_time[0:2])/24.0 - 1.0
        #print "%d %s %.2f" % (int(dd), fc_time, wind_speed_kmph)
        fc_dd_time_vs_ws[fc_dd_time] = float(wind_speed_kmph)

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
