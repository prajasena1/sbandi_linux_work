#!/home/sbandi/anaconda2/python2
import csv
import math
import os, sys
import calendar
import subprocess
import argparse
import calendar
from subprocess import PIPE, Popen
import matplotlib.pyplot as plt

#global variables
data_type = 'sfc'

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

#execute the os command and return the output of command
def cmdline(command):
    process = Popen(
        args=command,
        stdout=PIPE,
        shell=True
    )
    return process.communicate()[0]

#time_arg expected format YYYYMM
def get_grib_data_and_plot_month(time_arg, geo_loc_arg, loc_names_arg):
    time_list = time_arg.split(':')
    geo_loc_list = geo_loc_arg.split(':')
    loc_names = loc_names_arg.split(':')

    use_loc_names = True
    for time_val  in time_list:
    #{
        data_year = int (time_val[0:4])
        mon = int(time_val[4:])

        loc_counter = 0
        for geo_loc in geo_loc_list:
        #{
            fc_dd_time_vs_ws = {}

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

            if len(loc_names) > loc_counter and len(loc_names[loc_counter]) > 0:
                loc_name = loc_names[loc_counter]
            else:
                use_loc_names = False
                loc_name = geo_loc
            plt.plot(sorted(fc_dd_time_vs_ws.keys()), sorted_vals, label='%s %s %d' % (loc_name, calendar.month_name[mon], data_year))
            loc_counter = 1 + loc_counter
        #}
    #}
    if use_loc_names:
        title = 'wind speed %s %s' % (time_list, loc_names_arg)
    else:
        title = 'wind speed %s %s' % (time_list, geo_loc_list)
    plt.title(title, size='large')
    plt.xlabel('day of month %s' % (calendar.month_name[mon]))
    plt.ylabel('wind speed in kmph')
    plt.legend(loc=0)
    plt.show()


#time_arg expected format YYYY
def get_grib_data_and_plot_year(time_arg, geo_loc_arg, loc_names_arg):
    time_list = time_arg.split(':')
    geo_loc_list = geo_loc_arg.split(':')
    loc_names = []
    if loc_names_arg:
        loc_names = loc_names_arg.split(':')

    use_loc_names = True
    for time_val  in time_list:
    #{
        data_year = int (time_val)
        loc_counter = 0
        for geo_loc in geo_loc_list:
        #{
            fc_dd_time_vs_ws = {}
            for mon in range(1, 12+1):
            #{
                first_week_day, total_days_month = calendar.monthrange(data_year, mon)

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
                        dd_in_year = float(mon+float(fc_dd_time)/total_days_month)
                        fc_dd_time_vs_ws[dd_in_year] = float(wind_speed_kmph)
                    else:
                        continue

            #}

            sorted_vals = []
            for k in sorted(fc_dd_time_vs_ws.keys()):
                sorted_vals.append(fc_dd_time_vs_ws[k])

            #print sorted(fc_dd_time_vs_ws.keys())
            #print sorted_vals
            if len(loc_names) > loc_counter and len(loc_names[loc_counter]) > 0:
                loc_name = loc_names[loc_counter]
            else:
                use_loc_names = False
                loc_name = geo_loc
            plt.plot(sorted(fc_dd_time_vs_ws.keys()), sorted_vals, label='%s Full Year %d' % (loc_name, data_year))
            loc_counter = 1 + loc_counter
        #}
    #}
    if use_loc_names:
        title = 'wind speed %s %s' % (time_list, loc_names_arg)
    else:
        title = 'wind speed %s %s' % (time_list, geo_loc_list)
    plt.title(title, size='large')
    plt.xlabel('day of year-month %s' % (calendar.month_name[mon]))
    plt.ylabel('wind speed in kmph')
    plt.legend(loc=0)
    plt.show()

def main():
    global g_time_arg, g_geo_loc

    # Argument parsing
    parser = argparse.ArgumentParser(description="Plot Wind Speed of location(s) at time(s)")
    parser.add_argument("--time_yyyymm", help="Month and Year of time per which wind speed plot is required. Separate multiple times by Colon", action="store",
                        dest="time_yyyymm_arg", type=str)
    parser.add_argument("--time_yyyy", help="Year of time per which wind speed plot is required. Separate multiple times by Colon", action="store",
                        dest="time_yyyy_arg", type=str)
    parser.add_argument("--loc_names", help="location names corresponding to geo location for readability of plot", action="store",
                        dest="loc_names", type=str)
    parser.add_argument("--geo_loc", help="latitude and longitude of location(s). Separate lat and long by comma. Separate locations by Colon", action="store",
                        dest="geo_loc", type=str, required=True)

    cli_args = parser.parse_args()
    geo_loc_arg = cli_args.geo_loc
    loc_names_arg = cli_args.loc_names

    if not cli_args.time_yyyymm_arg and not cli_args.time_yyyy_arg:
        print COLOR_RED, "\nSupply one of --time_yyyymm --time_yyyy\n", COLOR_DEFAULT
        #print help and exit
        parser.parse_args(['-h'])

    if cli_args.time_yyyymm_arg:
        get_grib_data_and_plot_month(cli_args.time_yyyymm_arg, geo_loc_arg, loc_names_arg)
    elif cli_args.time_yyyy_arg:
        get_grib_data_and_plot_year(cli_args.time_yyyy_arg, geo_loc_arg, loc_names_arg)

if __name__=="__main__":
    main()
