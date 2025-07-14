int main() {
    const int SIZE = 10 * 1024 * 1024 / sizeof(int); // 10MB worth of ints
    int huge_array[SIZE];  // Stack overflow on Windows, might work on Linux
    huge_array[0] = 42;    // If it doesn't crash immediately
    return 0;
}