#include <iostream>
#include <vector>

template<typename T>
class SimplePool {
private:
    static constexpr size_t POOL_SIZE = 1024;
    std::vector<T> pool;
    std::vector<T*> available;
    
public:
    SimplePool() : pool(POOL_SIZE) {
        // Initialize all slots as available
        for (auto& item : pool) {
            available.push_back(&item);
        }
    }
    
    T* allocate() {
        if (available.empty()) {
            throw std::bad_alloc();
        }
        T* ptr = available.back();
        available.pop_back();
        return ptr;
    }
    
    void deallocate(T* ptr) {
        available.push_back(ptr);
    }
    
    size_t available_count() const {
        return available.size();
    }
};

// Usage example
int main() {
    SimplePool<int> pool;
    
    // Fast allocation from pool
    int* p1 = pool.allocate();
    *p1 = 42;
    
    int* p2 = pool.allocate();
    *p2 = 100;
    
    std::cout << "Available slots: " << pool.available_count() << "\n";
    
    // Return to pool (no actual heap deallocation)
    pool.deallocate(p1);
    pool.deallocate(p2);
    
    std::cout << "Available slots: " << pool.available_count() << "\n";
    
    return 0;
}