#!/bin/bash

# Check if two arguments are provided
if [[ $# -ne 2 ]]; then
  echo "Error: Please provide two arguments - write file path and write string."
  exit 1
fi

# Assign arguments to variables
writefile="$1"
writestr="$2"

# Create parent directories if they don't exist
mkdir -p "$(dirname "$writefile")"

# Write the string to the file
echo "$writestr" > "$writefile"

# Check if file creation was successful
if [[ ! -f "$writefile" ]]; then
  echo "Error: Could not write to file '$writefile'."
  exit 1
fi

echo "File '$writefile' created successfully."
