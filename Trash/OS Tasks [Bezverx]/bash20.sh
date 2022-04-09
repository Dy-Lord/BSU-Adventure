#!/bin/bash

nums=($(seq 9))
i=9

rand=$[ $RANDOM % $i ]
num+=($(echo "${nums[$rand]}"))
nums=( ${nums[@]:0:$rand} ${nums[@]:(($rand+1))} )
nums+=(0)

for el in $(seq 3);do
    rand=$[ $RANDOM % $i ]
    num+=($(echo ${nums[$rand]}))
    nums=( ${nums[@]:0:$rand} ${nums[@]:(($rand+1))} )
    ((i--))
done

#echo ${num[@]}
echo "COWS and BULLS ( To exit press CTRL+C )"$'\n'
count=0

while :
do

cows=0
bulls=0
c=0
alert=0

echo "Enter a four-digit number without repeating digits:"$'\n'
read usernum
temp=($(echo $usernum | sed  's/\(.\)/\1 /g'))

for (( i=0 ; i<${#temp[@]}-1; i++ )); do
    for (( j=i+1 ; j<${#temp[@]}; j++ )); do
        if (( ${temp[i]} == ${temp[j]} )); then
        alert=1
        fi 
    done
done

if (( $alert == 1 )) || (( ${#temp[@]} != 4 )); then
echo "Moo-moo-moo! Incorrect number! Enter a four-digit number without repeating digits ;)"$'\n'
else

for n in ${temp[@]}; do
    for k in $(seq 0 3); do
    if (( $c == $k )) && (( $n == ${num[$k]})); then
        ((bulls++))
        break
    elif (( $n == ${num[$k]} )); then
        ((cows++))
        break
    fi
    done
((c++))
done

((count++))
if (( $bulls == 4)); then
echo "You won!"
echo "The hidden number - $usernum"
echo "Attempts - $count"
exit
fi

echo "Bulls - $bulls"
echo "Cows  - $cows"
echo "#$count Try again:)"$'\n'

fi

done
