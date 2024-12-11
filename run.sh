#!/bin/bash
set -f; # disable glob matching for Exercise 5-10.
clear
EXERCISE=src/$1.c
if [ -e a.out ]; then
    rm a.out
fi
if [ $# -eq 2 ]; then
    gcc $EXERCISE -lm && echo "$2" | ./a.out
else
    gcc $EXERCISE -lm && ./a.out ${@: 2}
fi
