#!/bin/bash

# your need install g++

g++ -std=c++0x \
    -pthread \
    -I src/ \
    src/main.cpp \
    src/neos_fun_game.cpp \
    src/base_handler.cpp \
    src/time_handler.cpp \
    src/game_handler.cpp \
    src/set_handler.cpp \
    src/tcp_ip_server.cpp \
    -o neos_fun_game_service # ouput file