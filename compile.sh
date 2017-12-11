#! /bin/sh

g++ main.cpp -o main -I include/ src/*.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system
