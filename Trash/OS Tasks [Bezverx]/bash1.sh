#!/bin/bash
if [ $# -ne 3 ]
then

echo "Wrong count of arguments!"
echo "Example: ./bash1.sh / txt report.txt"
exit

else

echo "Scanning..."
find $1 -type f -name "*.$2" -exec basename {} ".$2" ';' 1>$3 2>/dev/null
echo "Scanning completed!"

fi
