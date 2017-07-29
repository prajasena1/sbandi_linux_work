#!/bin/bash

COLOR_DEFAULT="\033[0m"
COLOR_RED="\033[31m"
COLOR_GREEN="\033[32m"
COLOR_BROWN="\033[33m"
COLOR_BLUE="\033[34m"
COLOR_MAGENTA="\033[35m"
COLOR_CYAN="\033[36m"
COLOR_LIGHTGRAY="\033[37m"

declare -a GEO_DATA
GEO_DATA=(
`cat geo_loc.txt`
)
PROCESS_ITEM_FIELDS=4
PROCESS_ITEM_COUNT=$((${#GEO_DATA[@]}/${PROCESS_ITEM_FIELDS}))

while (true)
do
    clear
    date
    echo -e "${COLOR_BLUE}\nEnter the time YYYYMM or YYYY. Enter more than one by space separated: ${COLOR_DEFAULT}\c"
    read time_userinput
    unset time_arg_type
    unset time_arg
    for time_val in `echo $time_userinput`
    do
        if [[ -n "${time_arg}" ]]
        then
            time_arg="${time_arg}:$time_val"
        else
            time_arg="$time_val"
            if [[ ${#time_val} -eq 4 ]]
            then
                time_arg_type="--time_yyyy"
            else
                time_arg_type="--time_yyyymm"
            fi
        fi
    done
    nl geo_loc.txt
    echo -e "${COLOR_MAGENTA}Select the geo location number(s) from above. Enter multiple locations by space separated : ${COLOR_DEFAULT}\c"
    read loc_pref_userinput
    unset geo_loc_arg
    unset loc_name_arg
    for loc_pref in `echo $loc_pref_userinput`
    do
        let loc_pref=${loc_pref}-1
        item_offset=$((${loc_pref}*${PROCESS_ITEM_FIELDS}))
        place_name=${GEO_DATA[$((${item_offset}+0))]}
        place_lat=${GEO_DATA[$((${item_offset}+1))]}
        place_lon=${GEO_DATA[$((${item_offset}+2))]}
        place_alt=${GEO_DATA[$((${item_offset}+3))]}
        if [[ -n "$geo_loc_arg" ]]
        then
            geo_loc_arg="${geo_loc_arg}:${place_lat},${place_lon}"
            loc_name_arg="${loc_name_arg}:${place_name}($place_alt)"
        else
            geo_loc_arg="${place_lat},${place_lon}"
            loc_name_arg="${place_name}($place_alt)"
        fi
    done

    echo "time choice $time_arg and location choice $loc_name_arg"

    python ./plot_wind_speed.py ${time_arg_type} "${time_arg}" --geo_loc  "${geo_loc_arg}" --loc_names "${loc_name_arg}"
done

