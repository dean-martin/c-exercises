#!/bin/bash
set -f; # disable glob matching for Exercise 5-10.
clear
EXERCISE=src/$1.c
if [ -e a.out ]; then
    rm a.out
fi

gcc $EXERCISE -lm -w

if [ $# -eq 2 ]; then
    echo "$2" | ./a.out
    exit 0
fi
if [ -f "./testdata/$1.txt" ]; then
    ./a.out <"./testdata/$1.txt" ${@: 2}
    exit 0
fi

./a.out ${@: 2}
