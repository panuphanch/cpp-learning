# C++ Learning Repository: Memory Safety & Modern Practices

A structured learning path through C++ fundamentals with emphasis on memory safety, RAII principles, and modern C++ practices.

## 🎯 Learning Objectives

- Master memory management and debugging techniques
- Understand RAII (Resource Acquisition Is Initialization) principles  
- Learn smart pointer usage and move semantics
- Practice exception-safe programming
- Build thread-safe applications

## 📁 Repository Structure

### Phase 1: Memory Fundamentals (`phase1_fundamental/`)
Foundation concepts with focus on memory management and debugging:

- **Memory Debugging**: Practice with AddressSanitizer and Valgrind
- **Memory Pools**: Custom allocator implementations
- **Stack/Heap Safety**: Understanding memory layout and limits
- **Performance Analysis**: Comparing debugging tools

**Key Files:**
- `memory_demo.cpp` - Basic memory management examples
- `memory_pool.cpp` - Custom allocator implementation
- `test_memory.sh` - Automated testing with multiple tools
- `performance_comparison.cpp` - Tool performance analysis

### Phase 2: RAII & Smart Pointers (`phase2_memory_safety/`)
Advanced memory safety using modern C++ features:

#### **Week 3: RAII Fundamentals**
- Exception safety guarantees
- Resource management patterns
- Scope-based cleanup
- RAII violations and solutions

#### **Week 4: Smart Pointers**
- `unique_ptr`: Exclusive ownership
- `shared_ptr`: Shared ownership with reference counting
- `weak_ptr`: Breaking circular references
- Custom deleters and factories

#### **Week 5: Move Semantics**
- Move constructors and operators
- Perfect forwarding
- Move-only types
- Performance optimization

## 🔧 Build System

### CMake Configuration (Phase 2)
```bash
cd phase2_memory_safety/
mkdir -p build && cd build
cmake ..
make
ctest  # Run automated tests
```

### Manual Compilation
```bash
# Phase 1 (C++17)
g++ -std=c++17 -g -Wall -Wextra -pthread program.cpp -o program

# Phase 2 (C++20)  
g++ -std=c++20 -g -Wall -Wextra -pthread program.cpp -o program
```

## 🛡️ Memory Testing & Debugging

### Primary: AddressSanitizer
Fast runtime detection of memory errors:
```bash
g++ -std=c++17 -fsanitize=address -fsanitize=leak -g -O1 program.cpp -o program
./program
```

### Secondary: Valgrind  
Comprehensive memory analysis:
```bash
g++ -std=c++17 -g -O0 program.cpp -o program  # No sanitizers
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program
```

### Enhanced Warnings
```bash
g++ -std=c++17 -g -Wall -Wextra -Wpedantic -Wconversion -Wshadow program.cpp -o program
```

### Automated Testing
- `phase1_fundamental/test_memory.sh` - Comprehensive testing
- `phase1_fundamental/test_both_tools.sh` - Tool comparison

**⚠️ Important**: Never use AddressSanitizer and Valgrind simultaneously.

## 🏗️ Code Architecture & Patterns

### Core Principles
- **RAII**: Constructor acquires, destructor releases
- **Exception Safety**: Guaranteed cleanup during exceptions
- **Thread Safety**: Proper mutex usage with scoped locking
- **Move Semantics**: Efficient resource transfer

### Daily Exercise Structure
Each week builds upon previous concepts:
- **Week 3**: Daily RAII exercises with increasing complexity
- **Week 4**: Smart pointer progression (unique → shared → weak)
- **Week 5**: Move semantics and performance optimization

## 🚀 Getting Started

1. **Clone and explore**: Start with `phase1_fundamental/memory_demo.cpp`
2. **Run tests**: Use provided scripts to verify your environment
3. **Follow progression**: Complete phases sequentially
4. **Debug actively**: Use both AddressSanitizer and Valgrind
5. **Build with CMake**: Use the automated build system for Phase 2

## 📋 Development Workflow

1. Write code following RAII principles
2. Test with AddressSanitizer during development (`-O1`)
3. Verify with Valgrind for comprehensive checking (`-O0`)
4. Use CMake Debug configuration for automatic tool integration
5. Run automated tests with CTest
6. Check `output/` directories for compiled binaries

## 🎓 Learning Path

### Beginner
- Start with `phase1_fundamental/memory_demo.cpp`
- Practice with memory testing scripts
- Understand stack vs heap allocation

### Intermediate  
- Master RAII patterns in `week3/`
- Learn smart pointer usage in `week4/`
- Explore exception safety mechanisms

### Advanced
- Implement move semantics in `week5/`
- Build thread-safe applications
- Optimize performance with modern C++ features

## 📊 Testing Standards

All code must meet these requirements:
- ✅ Zero memory leaks (verified by both tools)
- ✅ Exception safety maintained
- ✅ Thread safety for concurrent code  
- ✅ Proper RAII implementation

## 🔍 Key Features

- **Comprehensive Testing**: Multiple debugging tools and automated scripts
- **Progressive Learning**: Each phase builds upon previous knowledge
- **Real-world Examples**: Practical applications, not toy programs
- **Modern C++**: Focus on C++17/20 features and best practices
- **Memory Safety**: Emphasis on leak-free, exception-safe code

---

*This repository emphasizes learning through practical implementation of memory-safe C++ patterns rather than theoretical examples.*