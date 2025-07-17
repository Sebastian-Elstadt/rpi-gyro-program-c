#!/bin/bash
mkdir -p bin
gcc main.c src/*.c -I include -o bin/emsys_program