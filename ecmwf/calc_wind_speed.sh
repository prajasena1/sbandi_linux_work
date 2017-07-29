#!/bin/bash

YEAR=$1
MON=$2
#fc_time 0000 0600 1200 1800
fc_time=$3
if [[ -n $4 ]]
then
    geo_loc_pref=$4
else
    geo_loc_pref=14.5764708,78.28036
fi

dir="${YEAR}_sfc_grib"
grib_file="${dir}/${YEAR}-${MON}-sfc.grib"
if [[ ! -r $grib_file ]]
then
    echo "$grib_file is not found"
    exit 1
fi

grib_ls -p shortName,dataDate,dataTime -w shortName:s=10u/10v,dataTime:i=$fc_time -l "${geo_loc_pref},1" $grib_file > data_from_grib.txt
grep ^10u data_from_grib.txt|awk '{print $2","$4}' > u_component_wind.csv
grep ^10v data_from_grib.txt|awk '{print $4}' > v_component_wind.csv
paste -d "," u_component_wind.csv v_component_wind.csv > wind_date_versus_uv.csv
rm -f data_from_grib.txt u_component_wind.csv v_component_wind.csv

exit 0
