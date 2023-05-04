#!/bin/bash

#magic numbers:
first_line=1
last_line=101
pass_limit=55

#checks input from stdin 
check=$(echo $1 | wc -c)
if [[ "$#" -ne 1 ]]; then
	echo "Wrong number of arguments" >&2
	exit 1
fi
grades=$1.txt 
if [[ ! -f $grades ]]; then
	echo "Course not found" >&2
	exit 1
fi
new_folder=$1_stat 
#delete folder if already exists
if [[ -d $new_folder ]]; then
	rm -r $new_folder
fi
mkdir $new_folder

#create hist with 10 bins
./hist.exe -n_bins 10 $grades > ./$new_folder/histogram.txt
#stores the relevant satistics in param
mean=$(./mean.exe $grades)
median=$(./median.exe $grades)
min=$(./min.exe $grades)
max=$(./max.exe $grades)

#create histogram with 100 bins
hundred_bins=$(./hist.exe -n_bins 100 "$grades")  

(( pass=0 ))
(( total=0 ))
for (( grade_line=$first_line; grade_line<=$last_line; grade_line++))
do
	line=$(echo "$hundred_bins" | sed "${grade_line-1}q;d")
	freq=$(echo "$line" | cut -f 2 | grep -oP '[0-9]+' | head -n 1)
	(( total=total+freq ))
	if [[ grade_line -ge $pass_limit ]]; then
		(( pass=pass+freq )) #pass counts freq's grades which >= 55
	fi
done

(( pass_ratio=pass*100 / total ))

echo -e "$mean\t$median\t$min\t$max\t$pass_ratio%" > \
./$new_folder/statistics.txt


