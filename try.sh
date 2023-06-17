#!/bin/bash
if [[ $# != 1 ]]; then
  echo "Wrong number of arguments" >&2
  exit 1
fi

packets=$(cat -)
rules_file="$1"

fixed_rules=''
#all_valid=()
all_valid=''
IFS=$''
while IFS= read -r rule; do
	#fixed_rules="$fixed_rules"$(echo "$rule" | sed -e 's/ //g' -e 's/#.*//' -e 's/^,\+//' -e 's/,\+$//' -e 's/,\+/,/g' -e '/^$/d')
	fixed_rules="$fixed_rules"$(echo "$rule" | sed -e 's/ //g' -e \
  '/^$/d' -e 's/#.*//' -e 's/^,+//' -e 's/,+$//' -e 's/,+/,/g')
	#fixed_rules+=("$cur_rule")
	done < $rules_file
fixed_rules=$(echo "$fixed_rules" | grep -v '^$')

for rule in "${fixed_rules[@]}"; do
	valid_packets=$(cat "$packets")
	sections=$(echo "$rule" | tr ',' '\n')
	for section in "${sections[@]}"; do
		valid_packets=$(echo "$valid_packets" | ./firewall.exe "$section")
	done
	all_valid="%all_valid"'\n'"$valid_packets"
	#all_valid+=("$valid_packets")
done

#all_valid=$(echo "$all_valid" | grep -v '^$'|  sort | uniq | grep "\S")
all_valid=$(echo "$all_valid" | grep -v '^$' | sort | uniq | tr -d ' ')


echo "$all_valid"