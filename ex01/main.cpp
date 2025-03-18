#include <iostream>
#include <new>

#include "RPN.hpp"

int main(int argc, char const* const* const argv) {
	int error;

	if (argc != 2) {
		error = 1;
		std::cerr << "Error: Wrong argument count\n";
	} else {
		try {
			std::cout << RPN::calculate(argv[1]) << '\n';
			error = 0;
		} catch (RPN::RPNException const& e) {
			std::cerr << "Error: " << e.what() << '\n';
			error = 2;
		} catch (std::bad_alloc const& e) {
			std::cerr << "System error: " << e.what() << '\n';
			error = 3;
		}
	}
	return error;
}
