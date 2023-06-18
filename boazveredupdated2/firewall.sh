#!/bin/bash

# Store the input from stdin in packets_file variable
read packets_file
sorted_packets=$(echo "$packets_file" | sort | uniq)

for packet in $sorted_packets; do
    rules_file=$(cat "$0")
    for rule in $rules_file; do
        flag=0
        sed -i '/#/d' "$rule" # Removes all comment lines
        num_command=$(($(grep -o ',' "$rule" | wc -l) + 1))
        
        for ((i = 1; i <= num_command; i++)); do
            awk -F, '{command=$i; print command}'
            compare=$(cat "$packet" | ./firewall.exe "$command")
            
            if [[ "$packet" != "$compare" ]]; then
                break # Command in rule failed, moving to the next rule
            else
                ((flag++))
            fi
        done
        
        if [[ $flag -eq $num_command ]]; then
            echo "$packet" # Print out the packet that matches the rule
            break # Rule succeeded, moving to the next packet
        fi
    done
done
