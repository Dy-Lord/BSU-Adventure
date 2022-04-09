#!/bin/bash

echo "Starting bash..."
if [ $# -ne 1 ]
then

echo "Wrong count of arguments!"
echo "Example: ./bash13.sh /home"
exit

else

IFS='/'
read -ra path <<< "$1"
unset IFS
lastpath=${path[${#path[@]}-1]}
prepath=${1%"$lastpath"}

for dir in  $(find $1 -type f 2>/dev/null);do

tdir=${dir#"$prepath"}
IFS='/'
read -ra tokens <<< "$tdir"
unset IFS
unset 'tokens[${#tokens[@]}-1]'
nums=0
mult=0

for token in "${tokens[@]}";do
 
temp=$(echo "$token" | sed 's/[^0-9]*//g')
if [ "$temp" = "$token" ] && [ "$token" != "" ];then
    if (( $nums == 0 ));then
      nums=1
    else 
       mult=1
    fi
fi
done

if (( $nums == 1 )) && (( $mult == 0 ));then
  echo $(find $dir -type f -exec readlink -f {} \;)
fi

done

echo "Bash completed!"
fi

