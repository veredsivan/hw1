#!/bin/bash
site="https://www.ynetnews.com/category/3082" 
data=$(wget --no-check-certificate -O - "$site" 2>/dev/null)
 #data stores the content of ynetnews website
list=$(echo "$data" | grep -oP\
 "https://(www)?.ynetnews.com/article/[0-9a-zA-Z]+")
  #filter all the relevant URL's
list_uniq=$(echo "$list" | sort | uniq) #removes duplicate values 
article_amount=$(echo "$list_uniq" | wc -l) #counts the number of files
echo $article_amount >> results.csv 
for line in $list_uniq; do 
	(( i = 0 ))
	counter=("" "" "" "") #array which stores incidence of each politican
	(( is_exist = 0 )) 
	#param which indicates if one of the names appear in article
	temp_data=$(wget --no-check-certificate -O - $line 2>/dev/null) 
	#contains the data of the specific article
	for name in Netanyahu Gantz Bennett Peretz; do
		counter[$i]=$(echo "$temp_data" | grep -oP $name | wc -w)
		 #counts incidence of each name
		 [[ ${counter[$i]} -ne 0 ]] && (( is_exist=1 )) 
		 #if one appread, then change the flag is_exist
		(( i++ ))
	done
	[[ $is_exist -eq 0 ]] && echo "$line, -" >> results.csv
	[[ $is_exist -ne 0 ]] && echo "$line, Netanyahu, ${counter[0]}, \
Gantz, ${counter[1]}, Bennett, ${counter[2]}, Peretz, ${counter[3]}"\
	  >> results.csv
done