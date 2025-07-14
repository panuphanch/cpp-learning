#include <iostream>

int main() {
    // Intentional memory leak for testing
    int* leak = new int(42);
    std::cout << "Created leak: " << *leak << std::endl;
    // Note: intentionally NOT deleting leak
    
    return 0;
}