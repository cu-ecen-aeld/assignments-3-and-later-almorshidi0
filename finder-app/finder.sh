#!/bin/bash

#Check if 2 arguements are provided
if [[ $# -ne 2 ]]; then
    echo "Error: Please provide two arguments - directory path and search string"
    exit 1
fi

#Assign arguements to variables
filesdir="$1"
searchstr="$2"

# Check if the directory exists
if [[ ! -d "$filesdir" ]]; then
    echo "Error: Directory '$filesdir' does not exist."
    exit 1
fi

#Initialize counters
filescounter=0
linescounter=0

#Count 
for file in "$filesdir"/*; do
    if [ -f "$file" ]; then
        ((filescounter++))
    
        if grep -q "$search" "$file"; then
            linescounter=$((linescounter + $(grep -c "$searchstr" "$file")))
        fi
    fi
done

echo "The number of files are $filescounter and the number of matching lines are $linescounter"
