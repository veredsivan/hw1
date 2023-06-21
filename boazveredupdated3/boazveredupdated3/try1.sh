#!/bin/bash

rules_file="$1"
packets=$(cat)
fixed_rules=$(sed -e 's/ //g' -e '/^$/d' -e 's/#.*//' -e 's/^,+//' -e 's/,+$//' -e 's/,+/,/g' "$rules_file" | grep -v '^$')
output=''

while IFS= read -r line; do
  all_valid="$packets"
  IFS=',' read -ra rule_array <<< "$line"

  for rule in "${rule_array[@]}"; do
    all_valid=$(echo "$all_valid" | ./firewall.exe "$rule")
  done

  output+="\n$all_valid"
done <<< "$fixed_rules"

output=$(echo -e "$output" | grep -v '^$' | tr -d ' ' | sort -u | sed '1{/^ *$/d}')
echo -e "$output"

#!/bin/bash


packets_file=$(cat)
sorted_packets=$(echo "$packets_file" | sort | uniq)
for packet in $sorted_packets
do
	#rules_file=$(cat "$1")
	rules_file=$(sed -i '/^&/d' $1)
	for rule in $rules_file
	do
		flag=0
		fixed_rule=$(sed '/#/d' <<< "$rule") #removes all comment lines
		fixed_rule=${fixed_rule// /}
		num_command=$(($(echo "fixed_rule" | grep -o ',' | wc -l) + 1))
		
		for i in $num_command
		do
			awk -F, '{command=$(i)}'


			#command=$(echo "$command" | sed 's/,$//')
			echo -e "$command"
			compare=$(echo "$packet"|./firewall.exe "$command")
			echo "$compare"
			if [[ "$packet"!="$compare" ]] 
			then
				
				break # cause command in rule faild, moving to the next rule 
			else 
				((flag++))
			fi
		done
		if [[ $flag -eq $num_command ]] 
		then 
			echo "$packet" # print out the packet that maches the rule
			break # cause rule succsses, moving to the next packet
		fi
	done
done