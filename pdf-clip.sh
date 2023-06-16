#!/bin/bash

mkdir -p unit$3/习题
pdftk Sol-Man-MOS4e.pdf cat $(($1 + 2))-$(($2 + 2)) output unit$3/习题/答案.pdf