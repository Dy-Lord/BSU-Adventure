#!/bin/bash

echo "Scanning..."
for file in `find . -maxdepth 1 -type f -name "*.txt"`
do

lines=`wc -l $file | cut -d ' ' -f 1`

if (( $lines % 2 == 0 ))
then

rm $file
if (($? == 0))
then
echo "File $file with $lines lines deleted!"
fi

fi

done

echo "Process completed!"
