#!/bin/bash

# Nota: revisa el README.md para ver como intalar gtest
# chmod +x ejecutar_tests.sh

g++ -o test tests/test_runner.cpp -lgtest -lpthread
./tests
rm -f tests
