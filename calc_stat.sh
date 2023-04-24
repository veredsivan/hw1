#!/bin/bash

if [[ $# != 1 ]]; then
  echo "Wrong number of arguments" >&2
  exit -1
fi 

if ! find . -type f -name "$1.txt" | grep -q .; then
	echo "Course not found" >&2
	exit -1
fi 

if ! find . -type d -name "$1_stat" | grep -q .; then
	mkdir $1_stat
else
	rm -r ./$1_stat
	mkdir $1_stat
fi

./hist/hist.exe -n_bins 10 "$1.txt" > $1_stat/histogram.txt

the_mean=$(./mean/mean.exe "$1.txt")
the_median=$(./median/median.exe "$1.txt")
the_min=$(./min/min.exe "$1.txt")
the_max=$(./max/max.exe "$1.txt")

the_grades=$(./hist/hist.exe -n_bins 100 "$1.txt")

echo "$the_grades"
(( count_fail=0 ))
#echo "count=$count"

for (( i=1; i<=55; i++))
do
	line=$(echo "$the_grades" | sed "${i-1}q;d")
	num=$(echo "$line" | cut -f 2 | grep -oP '[0-9]+' | head -n 1)
	(( count_fail=count_fail+num ))
done

(( count_succ=0 ))

for (( i=56; i<=101; i++))
do
	line=$(echo "$the_grades" | sed "${i-1}q;d")
	num=$(echo "$line" | cut -f 2 | grep -oP '[0-9]+' | head -n 1)
	(( count_succ=count_succ+num ))
done

(( count_all=count_fail+count_succ ))
(( pass_perc= count_succ*100 ))
(( pass_perc= pass_perc / count_all ))
echo -e "$the_mean\t$the_median\t$the_min\t$the_max\t$pass_perc%" > $1_stat/statistics.txt

#echo "$pass_perc" >> $1_stat/statistics.txt


