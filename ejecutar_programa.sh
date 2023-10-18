#!/bin/bash

# Compile the C++ code
g++ -I./ -o game_program clases/*.h clases/*.cpp main.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Starting the game..."
    # input_file="input.txt"
    ./game_program  


else
    echo "Compilation failed. Please check your C++ code."
fi

# Clean up the compiled executable
rm -f game_program
