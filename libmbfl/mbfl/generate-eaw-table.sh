#!/bin/sh
awk_exec=$1
source_dir=$2
file="$source_dir/eaw_table.h"
if [ ! -f "$file" ]
then
  "$awk_exec" -v TABLE_NAME=mbfl_eaw_table -f $source_dir/mk_eaw_tbl.awk $source_dir/EastAsianWidth.txt > $file
fi
