#include "../test.hpp"

#include <algorithm>

#include "PmergeMe.hpp"

static bool pmergeme_vector_6(void);

static bool is_sorted(std::vector<unsigned> const& v);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {pmergeme_vector_6};
	size_t tests_count = sizeof(tests) / sizeof(tests[0]);
	for (size_t i = 0; success && i < tests_count; i += 1) {
		success = tests[i]();
		std::cout << '\n';
	}
	if (success)
		std::cout << "OK\n";
	return success;
}

// clang-format off

TEST_START(pmergeme_vector_6)
	TEST_LOGIC_START
		std::vector<unsigned>	v(6);

		v[0] = 2;
		v[1] = 4;
		v[2] = 6;
		v[3] = 5;
		v[4] = 1;
		v[5] = 3;
		pmergeme(v);
		TEST_ASSERT(is_sorted(v))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END
// clang-format on

static bool is_sorted(std::vector<unsigned> const& v) {
	std::vector<unsigned>::const_iterator it = v.begin();
	for (std::vector<unsigned>::const_iterator in = std::lower_bound(it + 1, v.end(), *it);
		 it != v.end() - 1 && in == it + 1; it += 1)
		in = std::lower_bound(in + 1, v.end(), *in);
	return it == v.end() - 1;
}
