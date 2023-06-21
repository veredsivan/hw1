#!/bin/bash

rules_file="$1"
packets=$(cat)
new_rules=$(sed -e 's/ //g' -e '/^$/d' -e 's/#.*//' -e 's/^,+//' -e 's/,+$//' -e 's/,+/,/g' "$rules_file" | grep -v '^$')

good_packets=''

IFS=$'\n' read -d '' -r -a arr <<< "$new_rules"

for line in "${arr[@]}"; do
  is_ok="$packets"
  IFS=',' read -ra rule_parts <<< "$line"

  for rule in "${rule_parts[@]}"; do
    is_ok=$(./firewall.exe "$rule" <<< "$is_ok")
  done

  good_packets+="\n$is_ok"
done

good_packets=$(echo -e "$good_packets" | grep -v '^$' | tr -d ' ' | sort -u)

echo -e "$good_packets"