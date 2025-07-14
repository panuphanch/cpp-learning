#include <iostream>
#include <chrono>
#include <vector>

class PerformanceTest {
public:
    static void compareStackVsHeap(const int iterations = 1000000) {        
        // Test 1: Stack allocation
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            int stack_array[100];
            stack_array[0] = i;  // Use the array
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto stack_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Test 2: Heap allocation
				
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            int* heap_array = new int[100];
            heap_array[0] = i;  // Use the array
            delete[] heap_array;
        }
        end = std::chrono::high_resolution_clock::now();
        auto heap_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Stack allocation time: " << stack_time.count() << " microseconds\n";
        std::cout << "Heap allocation time:  " << heap_time.count() << " microseconds\n";
        std::cout << "Heap is " << (double)heap_time.count() / stack_time.count() 
                  << "x slower than stack\n";
    }
};

int main() {
		PerformanceTest::compareStackVsHeap(10);
		PerformanceTest::compareStackVsHeap(1000);
		PerformanceTest::compareStackVsHeap(1000000);
		return 0;
}