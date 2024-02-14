#!/bin/bash

# Installing the pre-requisites:
sudo apt update -y
sudo apt install gcc -y
sudo apt install libncurses5-dev -y

# Compiling:
chmod +x compile.sh
./compile.sh