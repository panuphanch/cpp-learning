#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::cout << "C++ WSL Setup Test\n";
    
    // Test stack allocation
    int stack_var = 42;
    std::cout << "Stack variable: " << stack_var << std::endl;
    
    // Test heap allocation
    int* heap_var = new int(100);
    std::cout << "Heap variable: " << *heap_var << std::endl;
    // delete heap_var;
    
    // Test smart pointer
    auto smart_ptr = std::make_unique<int>(200);
    std::cout << "Smart pointer: " << *smart_ptr << std::endl;
    
    // Test container
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Vector size: " << vec.size() << std::endl;
    
    return 0;
}