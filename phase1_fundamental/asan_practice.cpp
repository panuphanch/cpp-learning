int main() {
	// 1. Buffer overflow
	int arr[10];
	// arr[10] = 42; // Writing out of bounds, undefined behavior

	// 2. Use after free
	int* ptr = new int(24);
	delete ptr;
	// *ptr = 42; // Using memory after it has been freed, undefined behavior

	// 3. Memory leak
	int* leak = new int(100);
}