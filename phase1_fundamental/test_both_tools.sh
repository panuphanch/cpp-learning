#!/bin/bash

echo "=== DEMONSTRATING MEMORY DEBUGGING TOOLS ==="
echo

# Clean up any existing binaries
rm -f memory_tests_valgrind memory_tests_asan

echo "1. Compiling for Valgrind (no sanitizers)..."
g++ -std=c++17 -g -O0 memory_test_cases.cpp -o memory_tests_valgrind
if [ $? -eq 0 ]; then
    echo "✓ Valgrind version compiled successfully"
else
    echo "✗ Valgrind compilation failed"
    exit 1
fi

echo
echo "2. Compiling for AddressSanitizer..."
g++ -std=c++17 -fsanitize=address -fsanitize=leak -g -O1 memory_test_cases.cpp -o memory_tests_asan
if [ $? -eq 0 ]; then
    echo "✓ AddressSanitizer version compiled successfully"
else
    echo "✗ AddressSanitizer compilation failed"
    exit 1
fi

echo
echo "3. Running with Valgrind..."
echo "================================================"
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./memory_tests_valgrind

echo
echo
echo "4. Running with AddressSanitizer..."
echo "================================================"
./memory_tests_asan

echo
echo "=== ANALYSIS ==="
echo "Both tools should report no memory leaks if our fixes are correct!"
