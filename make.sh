#!/bin/bash

gcc -O3 -c Functions.c -o Functions.o
gcc -O3 -c IO.c -o IO.o
gcc -O3 -c Main.c -o Main.o
gcc -O3 -lm *.o -o Executable
rm *.o

