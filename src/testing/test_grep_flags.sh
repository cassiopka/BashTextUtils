#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Patterns and files to match them must be present"
    exit 1
fi

out_0=original_output.txt
out_1=my_output.txt
fails=0

echo
echo "____TESTING_GREP_FLAGS_PAIRS____"

for flag1 in c h i l n o s v
do
    for flag2 in c h i l n o s v
    do
        if [ $flag1 != $flag2 ]
        then
            grep "-$flag1$flag2" $@ > $out_0
            ../grep/my_grep "-$flag1$flag2" $@ > $out_1
            diff $out_0 $out_1
            if [ $? -eq 0 ]
            then
                echo $'\033[0;32m'"OK: -$flag1$flag2 $@"$'\033[0;m'
            else
                (( fails++ ))
                echo $'\033[0;31m'"FAIL: -$flag1$flag2 $@"$'\033[0;m'
            fi
        fi
    done
done

echo "____RESULT: $fails FAILS____"
echo

rm -f $out_0 $out_1

exit 0