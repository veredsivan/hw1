#!/bin/bash

#stors the input from stdin in packets variable 
read packets_file
sorted_packets=$(echo "$packets_file" | sort | uniq)

for packet in $sorted_packets
do
	rules_file=$(cat "$0")
	for rule in $rules_file
	do
		flag=0
		sed -i '/#/d' "$rule" #removes all comment lines
		num_command=$(($(grep -o ',' "$rule" | wc -l) + 1))
		for i in $num_command
		do
			awk -F, '{command=$(i)}'
			compare=$(cat packet|./firewall.exe "$command")
			if [["$packet" -neq "$compare" ]] 
			then
				break # cause command in rule faild, moving to the next rule 
			else 
				((flag++))
			fi
		done
		if [[$flag -eq $num_command]] 
		then 
			echo "$packet" # print out the packet that maches the rule
			break # cause rule succsses, moving to the next packet
		fi
	done
done