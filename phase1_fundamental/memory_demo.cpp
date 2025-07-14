#include <iostream>
#include <vector>

class MemoryDemo {
private:
    static int static_var;          // Data segment
    int member_var;                 // Part of object (stack or heap)
    
public:
    void demonstrateMemoryLayout() {
        int local_var = 42;         // Stack
        int* heap_var = new int(100); // Heap
        
        std::cout << "Addresses:\n";
        std::cout << "Static variable: " << &static_var << "\n";
        std::cout << "Local variable:  " << &local_var << "\n";
        std::cout << "Member variable: " << &member_var << "\n";
        std::cout << "Heap variable:   " << heap_var << "\n";
        std::cout << "Object address:  " << this << "\n";
        
        // Don't forget to clean up!
        delete heap_var;
    }
};

int MemoryDemo::static_var = 10;

int main() {
    MemoryDemo demo;        // Stack object
    demo.demonstrateMemoryLayout();
    
    MemoryDemo* heap_demo = new MemoryDemo(); // Heap object
    heap_demo->demonstrateMemoryLayout();
    delete heap_demo;       // Manual cleanup required
    
    return 0;
}