#!/bin/bash

clang++ -std=c++20 -c ../../src/cpp/All.cpp -O3 -I ../../src/include -D KONGKONG_OBJECTIVE_C_DISABLED
ar rcs Libklib.a All.o
