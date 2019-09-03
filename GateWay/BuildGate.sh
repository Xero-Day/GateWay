#!/bin/sh

cd src/
g++ -std=c++11 -Wall -Werror -Wextra Gates.cpp Simul.cpp FileP.cpp Gateway.cpp -o GateWay
cd ..
mv src/GateWay bin/
