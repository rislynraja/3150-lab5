# 3150-lab5

instructions for use:
- in order to run, first make sure any necessary c/c++ extensions are installed
- in the terminal, run the line: 
    g++ -std=c++17 -Iinclude -o testvectors vectorslab.cpp vectorslabtest.cpp
- this line will compile the tests and put the results in a file called 'testvectors'
- in order to read the file, next run the following line in the terminal: ./testvectors


notes on files included:
- doctest.h - for testing
- vectorslab.h - definitions for all functions needed
- vectorslab.cpp - implementation of functions listed in header file
- vectorslabtest.cpp - testing and test cases for everything in vectorslabtest
- testfile.txt - testing file with sample vectors to be read