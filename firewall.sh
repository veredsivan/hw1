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