#include <cstdlib>
#include <ctime>
#include <ios>
#include <iostream>
#include <limits>

#include "Errors.hpp"
#include "PmergeMe.hpp"

static void	  print_error(Errors error);
static Errors fill_with_input(std::vector<unsigned>& v, char const* const* const argv);

int main(int argc, char const* const* const argv) {
	Errors error;
	if (argc == 1)
		error = ERR_EMPTY_INPUT;
	else {
		try {
			std::vector<unsigned> v(argc - 1);
			if (!(error = fill_with_input(v, argv))) {
				std::deque<unsigned> d(v.begin(), v.end());
				std::cout << "Before: " << v[0];
				for (unsigned i = 1; i < v.size(); i += 1)
					std::cout << ' ' << v[i];
				std::cout << '\n';
				std::clock_t start = std::clock();
				if (static_cast<long>(start) == -1)
					error = ERR_TIME;
				else {
					PmergeMe::sort(v);
					std::clock_t end = std::clock();
					if (static_cast<long>(end) == -1)
						error = ERR_TIME;
					else {
						std::cout << "After:  " << v[0];
						for (unsigned i = 1; i < v.size(); i += 1)
							std::cout << ' ' << v[i];
						std::cout << "\nTime to process a range of " << v.size()
								  << " elements with std::vector: " << std::fixed
								  << (end - start) * 1000.0 / CLOCKS_PER_SEC << "ms\n";
						if (static_cast<long>(start = std::clock()) == -1)
							error = ERR_TIME;
						else {
							PmergeMe::sort(d);
							if (static_cast<long>(end = std::clock()) == -1)
								error = ERR_TIME;
							else
								std::cout << "Time to process a range of " << d.size()
										  << " elements with std::deque: " << std::fixed
										  << (end - start) * 1000.0 / CLOCKS_PER_SEC << "ms\n";
						}
					}
				}
			}
		} catch (std::bad_alloc const& e) {
			error = ERR_MEM;
		}
	}
	print_error(error);
	return error;
}

static Errors fill_with_input(std::vector<unsigned>& v, char const* const* const argv) {
	Errors error = ERR_NO;
	for (unsigned i = 0; error == ERR_NO && i < v.size(); i += 1) {
		char* end;
		long  val;
		val = std::strtol(argv[i + 1], &end, 10);
		if (val < 0 || val > std::numeric_limits<unsigned>::max())
			error = ERR_NUM_OUT_OF_RANGE;
		else if (*end)
			error = ERR_IS_NOT_NUM;
		else
			v[i] = static_cast<unsigned>(val);
	}
	return error;
}

static void print_error(Errors error) {
	if (error)
		std::cerr << "Error: ";
	switch (error) {
		case ERR_EMPTY_INPUT:
			std::cerr << "empty input";
			break;
		case ERR_NUM_OUT_OF_RANGE:
			std::cerr << "one or more elements are out of range";
			break;
		case ERR_IS_NOT_NUM:
			std::cerr << "one or more elements are not numbers";
			break;
		case ERR_MEM:
			std::cerr << "memory allocations failed";
			break;
		case ERR_TIME:
			std::cerr << "processor time is not available";
			break;
		default:
			break;
	}
	if (error)
		std::cerr << '\n';
}
