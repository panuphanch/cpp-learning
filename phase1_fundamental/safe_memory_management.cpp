#include <memory>
#include <iostream>

class Resource {
public:
    Resource() { std::cout << "Resource Acquired\n"; }
    ~Resource() { std::cout << "Resource Released\n"; }

		void modifyValue(int& value) {
			value *= 2;
		}

		void processData(const int* data, size_t size) {
			for (size_t i = 0; i < size; ++i) {
				// Read-only access
				std::cout << data[i] << " ";
			}
			std::cout << std::endl;
		}

		using Operation = int (*)(int, int);

		static int add(int a, int b) { return a + b; }
		static int substract(int a, int b) { return a - b; }

		static void calculateAndPrint(Operation op, int a, int b) {
			int result = op(a, b);
			std::cout << "Result: " << result << std::endl;
		}
};

int main() {
    {
        std::unique_ptr<Resource> res(new Resource());
				int value = 10;
				res->modifyValue(value);
				std::cout << "Modified Value: " << value << std::endl;

				int data[] = {1, 2, 3, 4, 5};
				res->processData(data, sizeof(data) / sizeof(data[0]));

				Resource::calculateAndPrint(Resource::add, 5, 3);
				Resource::calculateAndPrint(Resource::substract, 5, 3);
    }
    return 0;
}