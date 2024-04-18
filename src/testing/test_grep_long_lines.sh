#!/bin/bash

program=../testing/create_long_line
fname=long_lines.txt
pname=long_patterns.txt
out_0=original_output.txt
out_1=my_output.txt
fails=0

gcc -Wall -Wextra -Werror -std=c11 $program.c -o $program
$program $fname 97 1000000
$program $fname 98 1000000
$program $fname 99 1000000
$program $fname 100 1000000
$program $pname 100 5000
$program $pname 101 5000

echo
echo "____TESTING_LONG_LINES____"

grep -f $pname $fname > $out_0
code_0=$?
"../grep/my_grep" -f $pname $fname > $out_1
code_1=$?

if [ $code_0 -eq $code_1 ]
then
    echo $'\033[0;32m'"OK: output codes are the same: $code_0 : $code_1"$'\033[0;m'
else 
    echo $'\033[0;31m'"FAIL: output codes differ: $code_0 : $code_1"$'\033[0;m'
fi

diff $out_0 $out_1      
if [ $? -eq 0 ]
then
    echo $'\033[0;32m'"OK: outputs are the same"$'\033[0;m'
else
    echo $'\033[0;31m'"FAIL: outputs differ"$'\033[0;m'
fi

echo

rm -f $program $pname $fname $out_0 $out_1 

exit 0