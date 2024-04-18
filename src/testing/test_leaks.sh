#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage: ./test_leaks.sh cat|grep <input_data>.txt"
    exit 1
fi

log=leaks_logs.txt
fails=0

echo
echo "____TESTING_LEAKS____"

while IFS= read line
do
    leaks -atExit -- "./my_$1" $line > $log
    if [ $? -eq 0 ]
    then
        echo $'\033[0;32m'"OK: $line"$'\033[0;m'
    else
        (( fails++ ))
        echo $'\033[0;31m'"FAIL: $line"
        cat $log | grep LEAK:
        $'\033[0;m'
    fi
done < $2

echo "____RESULT: $fails FAILS____"
echo

rm -f $log

exit 0