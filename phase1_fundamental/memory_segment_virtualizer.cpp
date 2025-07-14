#include <iostream>

int global_initialized = 42;        // Initialized data segment
int global_uninitialized;          // BSS segment
const char* const_string = "Hello"; // Text segment (read-only)

void showMemorySegments() {
    static int static_var = 100;    // Initialized data segment
    int stack_var = 200;            // Stack
    int* heap_var = new int(300);   // Heap
    
    std::cout << "Text segment (approx):   " << (void*)showMemorySegments << "\n";
    std::cout << "Initialized data:        " << &global_initialized << "\n";
    std::cout << "Uninitialized (BSS):     " << &global_uninitialized << "\n";
    std::cout << "Stack variable:          " << &stack_var << "\n";
    std::cout << "Heap variable:           " << heap_var << "\n";
    
    delete heap_var;
}

int main() {
		std::cout << "Memory segments demonstration:\n";
		showMemorySegments();
		
		std::cout << "Constant string (text segment): " << const_string << "\n";
		
		return 0;
}