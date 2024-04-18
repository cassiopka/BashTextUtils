#!/bin/bash

if [ $# -lt 1 ]; then
    echo "At least one file must be present"
    exit 1
fi

default_flags=("-b" "-e" "-n" "-s" "-t")
gnu_flags=("--number-nonblank" "-Ev" "--number" "--squeeze-blank" "-Tv")
out_0=original_output.txt
out_1=my_output.txt
fails=0

echo
echo "____TESTING_DIFF____"

for i in ${!default_flags[@]} 
do
    cat ${default_flags[i]} $@ > $out_0
    ../cat/my_cat ${gnu_flags[i]} $@ > $out_1
    diff $out_0 $out_1
    if [ $? -eq 0 ]
    then
        echo $'\033[0;32m'"OK: ${gnu_flags[i]} $@"$'\033[0;m'
    else
        (( fails++ ))
        echo $'\033[0;31m'"FAIL: ${gnu_flags[i]} $@"$'\033[0;m'
    fi
done

echo "____RESULT: $fails FAILS____"
echo

rm -f $out_0 $out_1

exit 0

