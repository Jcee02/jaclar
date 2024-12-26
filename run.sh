#!/bin/zsh

filename="test_util"
staticlib="lib/jaclarv1.0"
gcc -o $filename ${filename}.c ${staticlib}.a -Wall

./$filename

