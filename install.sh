#!/bin/bash

# Installing the pre-requisites:
sudo apt update -y
sudo apt install gcc -y
sudo apt install libncurses5-dev -y


# Compiling:
gcc -Wall main.c functions.c structures.h -lncurses -o "snakeGame"
