#!/bin/bash

program=../testing/create_ascii_plus
fname=file3.txt
out_0=original_output.txt
out_1=my_output.txt
fails=0

gcc -Wall -Wextra -Werror -std=c11 $program.c -o $program
$program $fname

echo
echo "____TESTING_ASCII_PLUS____"

cat $fname > $out_0
"../cat/my_cat" $fname > $out_1
diff $out_0 $out_1      

if [ $? -eq 0 ]
then
    echo $'\033[0;32m'"OK: $fname"$'\033[0;m'
else
    (( fails++ ))
    echo $'\033[0;31m'"FAIL: $fname"$'\033[0;m'
fi

cat -e $fname > $out_0
"../cat/my_cat" -e $fname > $out_1
diff $out_0 $out_1      

if [ $? -eq 0 ]
then
    echo $'\033[0;32m'"OK: -e $fname"$'\033[0;m'
else
    (( fails++ ))
    echo $'\033[0;31m'"FAIL: -e $fname"$'\033[0;m'
fi

echo "____RESULT: $fails FAILS____"
echo

rm -f $program $fname $out_0 $out_1 

exit 0