#!/bin/bash

# Script to concatenate all files into output.txt using ripgrep, excluding node_modules

OUTPUT_FILE="output.txt"

# Clear the output file if it exists
> "$OUTPUT_FILE"

echo "Starting file concatenation with ripgrep..."
echo "Excluding node_modules and monitor directories..."

# Use ripgrep to list files, excluding node_modules and other unwanted files
rg . --line-number --heading \
    --glob '!data/**' \
    --glob '!.git/**' \
    --glob '!*.DS_Store' \
    --glob '!*.md' \
    --glob '!out.sh' \
    --glob "!$OUTPUT_FILE" > $OUTPUT_FILE

if [ -f ".env" ]; then
    echo "" >> "$OUTPUT_FILE"
    echo "///// END OF OTHER FILES, \".env\" file is next" >> "$OUTPUT_FILE"
    echo ".env" >> "$OUTPUT_FILE"
    cat ".env" >> "$OUTPUT_FILE"
fi

echo "Done! All files concatenated into $OUTPUT_FILE"
# ./out.sh # Assuming this is meant to be run after the script completes
