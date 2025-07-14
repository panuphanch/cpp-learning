#!/bin/bash

echo "=== C++ Memory Testing Script ==="
echo "This script demonstrates proper usage of different memory debugging tools"
echo ""

# Source file to test
SOURCE_FILE="memory_test_cases.cpp"

if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: $SOURCE_FILE not found!"
    exit 1
fi

echo "Testing file: $SOURCE_FILE"
echo ""

# Method 1: AddressSanitizer (ASan) - Fast, integrated with compiler
echo "1. Testing with AddressSanitizer (ASan)..."
echo "   - Pros: Fast, catches many errors immediately, good for development"
echo "   - Cons: Some overhead, may miss certain types of errors"
echo ""

g++ -std=c++17 -fsanitize=address -fsanitize=leak -g -O1 "$SOURCE_FILE" -o memory_tests_asan

if [ $? -eq 0 ]; then
    echo "✓ Compiled successfully with AddressSanitizer"
    echo "Running with ASan..."
    ./memory_tests_asan
    echo ""
else
    echo "✗ Compilation failed with AddressSanitizer"
    echo ""
fi

# Method 2: Valgrind - Comprehensive but slower
echo "2. Testing with Valgrind..."
echo "   - Pros: Very comprehensive, catches subtle errors, no recompilation needed"
echo "   - Cons: Slower execution, requires separate installation"
echo ""

# Compile without sanitizers for Valgrind
g++ -std=c++17 -g -O1 "$SOURCE_FILE" -o memory_tests_valgrind

if [ $? -eq 0 ]; then
    echo "✓ Compiled successfully for Valgrind"
    echo "Running with Valgrind..."
    
    # Check if valgrind is installed
    if command -v valgrind &> /dev/null; then
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./memory_tests_valgrind
    else
        echo "Valgrind not found. Install with: sudo apt-get install valgrind"
        echo "Running without Valgrind:"
        ./memory_tests_valgrind
    fi
    echo ""
else
    echo "✗ Compilation failed for Valgrind"
    echo ""
fi

# Method 3: Basic compilation with warnings
echo "3. Basic compilation with enhanced warnings..."
g++ -std=c++17 -g -Wall -Wextra -Wpedantic -Wconversion -Wshadow "$SOURCE_FILE" -o memory_tests_basic

if [ $? -eq 0 ]; then
    echo "✓ Compiled successfully with warnings"
    echo "Running basic version..."
    ./memory_tests_basic
    echo ""
else
    echo "✗ Compilation failed"
    echo ""
fi

# Cleanup
echo "Cleaning up compiled files..."
rm -f memory_tests_asan memory_tests_valgrind memory_tests_basic

echo "=== Testing Complete ==="
echo ""
echo "SUMMARY:"
echo "- Use AddressSanitizer during development for quick feedback"
echo "- Use Valgrind for thorough final testing"
echo "- Always compile with warnings enabled"
