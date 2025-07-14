#include <iostream>
#include <memory>

/*
	Identify all 6 problems in the code above
	Write corrected versions of each problematic section
	Create your own examples of safe pointer usage
*/

// DANGEROUS CODE - Find all the problems!
class UnsafePointerDemo {
public:
    void demonstrateProblems() {
        // Problem 1: Uninitialized pointer
        int* ptr1;
		int value1 = 10;
		ptr1 = &value1;
        std::cout << *ptr1 << std::endl;  // Undefined behavior!
        
        // Problem 2: Dangling pointer
        // int* ptr2 = createDanglingPointer();
        // std::cout << *ptr2 << std::endl;  // Undefined behavior!
		// delete ptr2;                      // Memory leak, as ptr2 points to freed memory
		std::unique_ptr<int> danglingPtr = createDanglingPointer();
		std::cout << *danglingPtr << std::endl;  // Safe usage, but dangling pointer if used after this scope
        
        // Problem 3: Memory leak
        int* ptr3 = new int(42);
		delete ptr3;
        ptr3 = new int(100);  // Original memory leaked!
        delete ptr3;          // Only deletes second allocation
        
        // Problem 4: Double deletion
        int* ptr4 = new int(200);
		std::cout << *ptr4 << std::endl;
        delete ptr4;
        // delete ptr4;       // Undefined behavior!
        
        // Problem 5: Array/scalar mismatch
        int* arr = new int[10];
		arr[0] = 42;  // Initialize first element
		std::cout << *arr << std::endl;  // Accessing first element of the array
		std::cout << arr[0] << std::endl;
        // delete arr;        // Should be delete[]!
        delete[] arr;         // Correct way
        
        // Problem 6: Use after free
        int* ptr5 = new int(300);
        delete ptr5;
        // *ptr5 = 400;       // Undefined behavior!
    }
    
private:
    std::unique_ptr<int> createDanglingPointer() {
        // int* local_var = new int(42);
        // return local_var;    // Returns address of local variable!
		std::unique_ptr<int> local_var(new int(42));
		return local_var;
    }
};

int main() {
    UnsafePointerDemo* demo = new UnsafePointerDemo();
	demo->demonstrateProblems();

	delete demo;
    
    return 0;
}