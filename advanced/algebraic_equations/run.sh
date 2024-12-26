#!/bin/zsh

arr_size=$1
libname="../../lib/util"

gcc *.c ${libname}.a -o main -Wall

./main $arr_size

rm main
