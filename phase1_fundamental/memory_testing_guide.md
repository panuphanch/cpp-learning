# Memory Testing Guide

## Quick Reference: How to Test C++ Memory Management

### Method 1: AddressSanitizer (Recommended for Development)
```bash
# Compile with AddressSanitizer
g++ -std=c++17 -fsanitize=address -fsanitize=leak -g -O1 memory_test_cases.cpp -o memory_tests

# Run directly (no valgrind needed)
./memory_tests
```

**What AddressSanitizer catches:**
- Buffer overruns/underruns
- Use-after-free
- Double-free
- Memory leaks
- Stack buffer overflow

### Method 2: Valgrind (Recommended for Final Verification)
```bash
# Compile WITHOUT sanitizers
g++ -std=c++17 -g -O1 memory_test_cases.cpp -o memory_tests

# Run with Valgrind
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./memory_tests
```

**What Valgrind catches:**
- All memory errors (very comprehensive)
- Uninitialized memory reads
- Invalid memory access
- Memory leaks
- More subtle errors that ASan might miss

### Method 3: Both for Maximum Coverage
```bash
# Step 1: Test with AddressSanitizer
g++ -std=c++17 -fsanitize=address -g memory_test_cases.cpp -o memory_tests_asan
./memory_tests_asan

# Step 2: Test with Valgrind (recompile without ASan)
g++ -std=c++17 -g memory_test_cases.cpp -o memory_tests_valgrind
valgrind --leak-check=full ./memory_tests_valgrind
```

## Common Output Interpretations

### Good Output (No Issues):
- **ASan**: Program runs normally, no error messages
- **Valgrind**: "All heap blocks were freed -- no leaks are possible"

### Bad Output (Issues Found):
- **ASan**: Red error messages with stack traces
- **Valgrind**: "definitely lost", "possibly lost", or "invalid read/write"

## Tool Comparison

| Feature | AddressSanitizer | Valgrind |
|---------|------------------|----------|
| Speed | Fast (2-3x slower) | Slow (10-50x slower) |
| Setup | Compiler flag | Separate tool |
| Coverage | Good | Excellent |
| Development Use | ✓ Ideal | Sometimes |
| Final Testing | Good | ✓ Ideal |
| Real-time Feedback | ✓ Yes | Slower |

## Why Your Error Occurred

The error you saw happened because:
1. You compiled with `-fsanitize=address` (AddressSanitizer)
2. Then tried to run with `valgrind`
3. Both tools try to intercept memory operations
4. They conflict and cause crashes

**Rule**: Use one tool at a time, not both simultaneously!
