#!/bin/bash

g++ -std=c++20 -c ../../src/cpp/All.cpp -O3 -I ../../src/include -D KLIB_OBJECTIVE_C_DISABLED
ar rcs Libklib.a All.o
