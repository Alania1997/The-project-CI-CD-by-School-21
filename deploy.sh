#!/bin/bash

HOST="192.10.10.1"
USER="ellensem"

# Copy cat files
scp -o StrictHostKeyChecking=no -r ./src/cat/* $USER@$HOST:/usr/local/bin/cat/

# Check if the first scp command was successful
if [ $? -ne 0 ]; then
    echo "Error copying cat files."
    exit 1
fi

# Copy grep files
scp -o StrictHostKeyChecking=no -r ./src/grep/* $USER@$HOST:/usr/local/bin/grep/

# Check if the second scp command was successful
if [ $? -ne 0 ]; then
    echo "Error copying grep files."
    exit 1
fi

echo "Files successfully deployed."
