#!/bin/bash

rm output.txt
COUNTER=0
while [  $COUNTER -lt 100 ]; do
    echo -ne "$COUNTER % complete..."\\r
    sleep 3
    ./a.out >> output.txt
    let COUNTER=COUNTER+1
done
