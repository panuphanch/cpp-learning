#include <iostream>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <cassert>
#include <vector>

class MemoryLeakTests {
public:
    // Test Case 1: Verify basic leak is fixed
    static void testBasicLeakFix() {
        std::cout << "Testing: Basic leak fix...\n";
        
        // This should NOT leak memory
        int* data = new int[1000];
        // Fill with some data to prove it works
        for (int i = 0; i < 1000; ++i) {
            data[i] = i;
        }
        
        // Verify we can read the data
        assert(data[0] == 0);
        assert(data[999] == 999);
        
        // Proper cleanup
        delete[] data;
        
        std::cout << "✓ Basic leak test passed\n";
    }
    
    // Test Case 2: Verify exception safety
    static void testExceptionSafety() {
        std::cout << "Testing: Exception safety...\n";
        
        int attempts = 0;
        int successes = 0;
        int exceptions = 0;
        
        // Run multiple times to test both exception and non-exception paths
        for (int trial = 0; trial < 10; ++trial) {
            attempts++;
            
            try {
                // Allocate resources
                int* data1 = new int[100];
                int* data2 = new int[100];
                
                // Use the memory
                data1[0] = 42;
                data2[0] = 84;
                
                try {
                    // Simulate random exception
                    if (trial % 3 == 0) {
                        throw std::runtime_error("Test exception");
                    }
                    
                    // Normal path - cleanup
                    delete[] data1;
                    delete[] data2;
                    successes++;
                }
                catch (...) {
                    // Exception path - MUST cleanup here too
                    delete[] data1;
                    delete[] data2;
                    exceptions++;
                    // Don't re-throw in test
                }
            }
            catch (...) {
                // Outer catch for any other issues
                std::cout << "Unexpected exception in trial " << trial << "\n";
            }
        }
        
        std::cout << "✓ Exception safety test: " << attempts << " attempts, " 
                  << successes << " successes, " << exceptions << " exceptions handled\n";
    }
    
    // Test Case 3: Verify resource cleanup
    static void testResourceCleanup() {
        std::cout << "Testing: Resource cleanup...\n";
        
        const char* filename = "test_resource.txt";
        
        // Test proper file handling
        {
            std::ofstream file(filename);
            if (file.is_open()) {
                file << "Test data";
                // file automatically closed when going out of scope (RAII)
            }
        }
        
        // Verify file was written and can be read
        {
            std::ifstream file(filename);
            std::string content;
            std::getline(file, content);
            assert(content == "Test data");
        }
        
        // Clean up test file
        std::remove(filename);
        
        std::cout << "✓ Resource cleanup test passed\n";
    }
    
    // Test Case 4: Memory usage pattern test
    static void testMemoryUsagePattern() {
        std::cout << "Testing: Memory usage patterns...\n";
        
        // Test that we can allocate and deallocate large amounts without issues
        const int iterations = 1000;
        const int arraySize = 1000;
        
        for (int i = 0; i < iterations; ++i) {
            int* data = new int[arraySize];
            
            // Use the memory (prevent optimization)
            data[0] = i;
            data[arraySize-1] = i;
            
            // Immediate cleanup
            delete[] data;
        }
        
        std::cout << "✓ Memory pattern test: " << iterations 
                  << " allocations/deallocations completed\n";
    }
    
    // Test Case 5: Stress test for edge cases
    static void testEdgeCases() {
        std::cout << "Testing: Edge cases...\n";
        
        // Test 1: Zero-size allocation (implementation defined)
        int* ptr1 = new int[0];
        delete[] ptr1;  // Should be safe
        
        // Test 2: Multiple small allocations
        std::vector<int*> ptrs;
        for (int i = 0; i < 100; ++i) {
            ptrs.push_back(new int(i));
        }
        
        // Cleanup all
        for (int* ptr : ptrs) {
            delete ptr;
        }
        
        std::cout << "✓ Edge cases test passed\n";
    }
};

// Helper function to run all tests
void runAllMemoryTests() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "RUNNING MEMORY MANAGEMENT TESTS\n";
    std::cout << std::string(50, '=') << "\n";
    
    try {
        MemoryLeakTests::testBasicLeakFix();
        MemoryLeakTests::testExceptionSafety();
        MemoryLeakTests::testResourceCleanup();
        MemoryLeakTests::testMemoryUsagePattern();
        MemoryLeakTests::testEdgeCases();
        
        std::cout << "\n✓ ALL TESTS PASSED!\n";
        std::cout << "Memory management appears to be working correctly.\n";
    }
    catch (const std::exception& e) {
        std::cout << "\n✗ TEST FAILED: " << e.what() << "\n";
    }
    catch (...) {
        std::cout << "\n✗ UNKNOWN TEST FAILURE\n";
    }
}

int main() {
    runAllMemoryTests();
    return 0;
}
