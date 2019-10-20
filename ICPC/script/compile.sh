#/bin/bash
for file in `find | grep -E "\.(c|h)pp$"`
do
    echo compiling $file
    if ! g++ -std=c++14 -Wall -Wextra -c $file -o /dev/null ; then
        echo compile error on $file
        exit -1
    fi
    echo ok
done
