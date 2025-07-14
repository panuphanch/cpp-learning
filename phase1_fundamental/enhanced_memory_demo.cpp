#include <iostream>
#include <vector>
#include <string>

class EnhancedMemoryDemo {
private:
    static int static_var;
    int member1;
    int member2;
    char member_array[100];
    
public:
    EnhancedMemoryDemo(int val1, int val2) : member1(val1), member2(val2) {
        // Initialize array
        for(int i = 0; i < 100; i++) {
            member_array[i] = 'A' + (i % 26);
        }
    }
    
    void analyzeMemoryLayout() {
        // Stack variables
        int local1 = 10;
        int local2 = 20;
        char local_array[50];
        
        // Heap variables
        int* heap1 = new int(100);
        int* heap2 = new int(200);
        int* heap_array = new int[10];
        
        // String (interesting case)
        std::string stack_string = "Hello World";
        std::string* heap_string = new std::string("Heap String");
        
        std::cout << "=== MEMORY LAYOUT ANALYSIS ===\n";
        
        std::cout << "\n1. STATIC/GLOBAL SEGMENT:\n";
        std::cout << "Static variable:     " << &static_var << "\n";
        
        std::cout << "\n2. STACK SEGMENT:\n";
        std::cout << "Local var 1:         " << &local1 << "\n";
        std::cout << "Local var 2:         " << &local2 << "\n";
        std::cout << "Local array:         " << (void*)local_array << "\n";
        std::cout << "Stack string obj:    " << &stack_string << "\n";
        std::cout << "This pointer:        " << this << " (object location)\n";
        
        std::cout << "\n3. OBJECT MEMBERS (follow parent):\n";
        std::cout << "Member 1:            " << &member1 << "\n";
        std::cout << "Member 2:            " << &member2 << "\n";
        std::cout << "Member array:        " << (void*)member_array << "\n";
        
        std::cout << "\n4. HEAP SEGMENT:\n";
        std::cout << "Heap var 1:          " << heap1 << " (points to " << *heap1 << ")\n";
        std::cout << "Heap var 2:          " << heap2 << " (points to " << *heap2 << ")\n";
        std::cout << "Heap array:          " << heap_array << "\n";
        std::cout << "Heap string obj:     " << heap_string << "\n";
        std::cout << "Heap string data:    " << (void*)heap_string->data() << "\n";
        
        std::cout << "\n5. ADDRESS ANALYSIS:\n";
        // Calculate distances to see memory organization
        std::cout << "Distance local1->local2: " << 
                     (char*)&local2 - (char*)&local1 << " bytes\n";
        std::cout << "Distance member1->member2: " << 
                     (char*)&member2 - (char*)&member1 << " bytes\n";
        std::cout << "Distance heap1->heap2: " << 
                     (char*)heap2 - (char*)heap1 << " bytes\n";
        
        // Cleanup
        delete heap1;
        delete heap2;
        delete[] heap_array;
        delete heap_string;
    }
};

int EnhancedMemoryDemo::static_var = 42;

// Function to demonstrate stack frame behavior
void demonstrateStackFrames(int depth) {
    int frame_var = depth * 10;
    std::cout << "Frame " << depth << " variable at: " << &frame_var 
              << " (value: " << frame_var << ")\n";
    
    if (depth > 0) {
        demonstrateStackFrames(depth - 1);
    }
}

void test_stack_order() {
    int a = 1;
    int b = 2; 
    int c = 3;
    
    printf("a: %p (value: %d)\n", &a, a);
    printf("b: %p (value: %d)\n", &b, b);  
    printf("c: %p (value: %d)\n", &c, c);
    
    // You'll see: a > b > c in address values
}

int main() {
    std::cout << "=== ENHANCED MEMORY DEMONSTRATION ===\n";
    
    // Test 1: Stack object
    std::cout << "\nTEST 1: Stack Object\n";
    EnhancedMemoryDemo stack_demo(10, 20);
    stack_demo.analyzeMemoryLayout();
    
		
    // Test 2: Heap object  
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "TEST 2: Heap Object\n";
    EnhancedMemoryDemo* heap_demo = new EnhancedMemoryDemo(30, 40);
    heap_demo->analyzeMemoryLayout();
    delete heap_demo;
    
    // Test 3: Stack frame demonstration
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "TEST 3: Stack Frame Growth\n";
    demonstrateStackFrames(5);

    test_stack_order();
    
    return 0;
}