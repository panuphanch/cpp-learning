#include <iostream>
#include <memory>

struct Node {
    int value;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // Using weak_ptr to break cycles
    
    Node(int v) : value(v) {}
    
    ~Node() {
        std::cout << "Node " << value << " is being destroyed\n";
    }
};

void demonstrateCircularLeak() {
    std::cout << "\n=== CIRCULAR REFERENCE LEAK DEMO ===\n";
    
    // Create two nodes with shared_ptr
    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);
    
    std::cout << "Initial reference counts:\n";
    std::cout << "node1 use_count: " << node1.use_count() << "\n";
    std::cout << "node2 use_count: " << node2.use_count() << "\n";
    
    // Create circular references using shared_ptr
    node1->next = node2;  // node2's ref count becomes 2
    node2->next = node1;  // node1's ref count becomes 2
    
    std::cout << "\nAfter creating circular references:\n";
    std::cout << "node1 use_count: " << node1.use_count() << "\n";
    std::cout << "node2 use_count: " << node2.use_count() << "\n";
    
    // When this function ends, node1 and node2 go out of scope
    // But their reference counts only drop to 1 (not 0)
    // So they never get destroyed -> MEMORY LEAK!
    std::cout << "\nFunction ending... watch for destructor calls\n";
}

void demonstrateFixedVersion() {
    std::cout << "\n=== FIXED VERSION (using weak_ptr) ===\n";
    
    auto node1 = std::make_shared<Node>(10);
    auto node2 = std::make_shared<Node>(20);
    
    // Use weak_ptr to break the cycle
    node1->next = node2;           // shared_ptr: normal ownership
    node2->prev = node1;           // weak_ptr: no ownership
    
    std::cout << "Reference counts with weak_ptr:\n";
    std::cout << "node1 use_count: " << node1.use_count() << "\n";
    std::cout << "node2 use_count: " << node2.use_count() << "\n";
    
    std::cout << "\nFunction ending... watch for destructor calls\n";
    // Now both objects will be properly destroyed
}

int main() {
    demonstrateCircularLeak();
    
    std::cout << "\n" << std::string(50, '=') << "\n";
    
    demonstrateFixedVersion();
    
    return 0;
}
