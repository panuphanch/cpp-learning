#include <iostream>
#include <memory>
#include <exception>

class LeakDemonstration {
public:
    // Leak Pattern 1: Simple forget to delete
    void basicLeak() {
        int* data = new int[1000];
		delete[] data;
        // Oops! Forgot to delete[] data;
        // This is a memory leak!
    }
    
    // Leak Pattern 2: Exception safety issue
    void exceptionLeak() {
        int* data1 = new int[1000];
        int* data2 = new int[1000];
        
        try {
            // Some operation that might throw
            if (rand() % 2) {
                throw std::runtime_error("Something went wrong!");
            }
            
            // Normal cleanup
            delete[] data1;
            delete[] data2;
        }
        catch (...) {
			delete[] data1;
			delete[] data2;
            // Exception caught, but data1 and data2 leaked!
            // Should have cleanup here too
            throw;
        }
    }
    
    // Leak Pattern 3: Circular reference (with raw pointers)
    struct Node {
        int value;
        Node* next;
        Node* prev;
        
        Node(int v) : value(v), next(nullptr), prev(nullptr) {}
    };
    
    void circularLeak() {
        Node* node1 = new Node(1);
        Node* node2 = new Node(2);
        
        // Create circular reference
        node1->next = node2;
        node2->prev = node1;
        node2->next = node1;  // Circular!
        node1->prev = node2;
        
        // Even if we delete node1 and node2, they reference each other
        // Making it impossible for simple reference counting to work
        delete node1;  // This doesn't actually free the memory properly
        delete node2;  // if there are internal circular references
    }
    
    // Leak Pattern 4: Resource leak (file handles)
    void resourceLeak() {
        FILE* file = fopen("temp.txt", "w");
        if (file) {
            fprintf(file, "Some data");
            // Oops! Forgot to fclose(file);
            // File handle leaked!
        }
		fclose(file);
    }
};

int main() {
    LeakDemonstration demo;
    demo.basicLeak();
    try {
        demo.exceptionLeak();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    demo.circularLeak();
    demo.resourceLeak();
    return 0;
}