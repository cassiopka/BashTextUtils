#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage: ./test_diff.sh cat|grep <input_data>.txt"
    exit 1
fi

out_0=original_output.txt
out_1=my_output.txt
fails=0

echo
echo "____TESTING_DIFF____"

while IFS= read line
do
    $1 $line > $out_0
    "../$1/my_$1" $line > $out_1    
    diff $out_0 $out_1
    if [ $? -eq 0 ]
    then
        echo $'\033[0;32m'"OK: $line"$'\033[0;m'
    else
        (( fails++ ))
        echo $'\033[0;31m'"FAIL: $line"$'\033[0;m'
    fi
done < $2

echo "____RESULT: $fails FAILS____"
echo

rm -f $out_0 $out_1

exit 0