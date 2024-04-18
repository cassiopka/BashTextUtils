#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage: ./test_diff.sh cat|grep <input_data>.txt"
    exit 1
fi

fails=0

echo
echo "____TESTING_RETURN_CODE____"

while IFS= read line
do  
    $1 $line > /dev/null 2>&1
    out_0=$?
    "../$1/my_$1" $line > /dev/null 2>&1
    out_1=$?
    if [ $out_0 -eq $out_1 ] || ([ $out_0 -eq 2 ] && [ $out_1 -eq 255 ])
    then
        echo $'\033[0;32m'"OK: $out_0 : $out_1	<--- $line"$'\033[0;m'
    else
        (( fails++ ))
        echo $'\033[0;31m'"FAIL: $out_0 : $out_1	<--- $line"$'\033[0;m'
    fi
done < $2

echo "____RESULT: $fails FAILS____"
echo

exit 0