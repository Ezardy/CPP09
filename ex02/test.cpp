#include "../test.hpp"

#include <algorithm>

#include "PmergeMe.hpp"

static bool pmergeme_vector_0(void);
static bool pmergeme_vector_1(void);
static bool pmergeme_vector_2(void);
static bool pmergeme_vector_3(void);
static bool pmergeme_vector_4(void);
static bool pmergeme_vector_5(void);
static bool pmergeme_vector_6(void);
static bool pmergeme_vector_21(void);
static bool pmergeme_vector_nonunique(void);
static bool pmergeme_vector_15000(void);

static bool pmergeme_deque_0(void);
static bool pmergeme_deque_1(void);
static bool pmergeme_deque_2(void);
static bool pmergeme_deque_3(void);
static bool pmergeme_deque_4(void);
static bool pmergeme_deque_5(void);
static bool pmergeme_deque_6(void);
static bool pmergeme_deque_21(void);
static bool pmergeme_deque_nonunique(void);
static bool pmergeme_deque_15000(void);

static bool is_sorted(std::vector<unsigned> const& v);
static bool is_sorted(std::deque<unsigned> const& v);

struct UnsignedSequence {
public:
	UnsignedSequence() : a(0), i(0), step(1) {}

	UnsignedSequence(unsigned i) : a(0), i(0), step(i) {}

	unsigned operator()(void) {
		if (i == step) {
			i = 0;
			a += 1;
		} else
			i += 1;
		return a;
	}

private:
	unsigned a;
	unsigned i;
	unsigned step;
};

int main() {
	bool success = true;
	bool (*tests[])(void) = {
		pmergeme_vector_0,		  pmergeme_vector_1,   pmergeme_vector_2,
		pmergeme_vector_3,		  pmergeme_vector_4,   pmergeme_vector_5,
		pmergeme_vector_6,		  pmergeme_vector_21,  pmergeme_vector_nonunique,
		pmergeme_vector_15000,	  pmergeme_deque_0,	   pmergeme_deque_1,
		pmergeme_deque_2,		  pmergeme_deque_3,	   pmergeme_deque_4,
		pmergeme_deque_5,		  pmergeme_deque_6,	   pmergeme_deque_21,
		pmergeme_deque_nonunique, pmergeme_deque_15000};
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
TEST_START(pmergeme_deque_15000)
	TEST_LOGIC_START
		std::deque<unsigned>	d(15000);

		std::generate(d.begin(), d.end(), UnsignedSequence());
		std::random_shuffle(d.begin(), d.end());
		PmergeMe::sort(d);
		TEST_ASSERT(is_sorted(d))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_deque_nonunique)
	TEST_LOGIC_START
		std::deque<unsigned>	d(301);

		std::generate(d.begin(), d.end(), UnsignedSequence(5));
		std::random_shuffle(d.begin(), d.end());
		PmergeMe::sort(d);
		TEST_ASSERT(is_sorted(d))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_deque_21)
	TEST_LOGIC_START
		std::deque<unsigned>	d(21);

		std::generate(d.begin(), d.end(), UnsignedSequence());
		std::random_shuffle(d.begin(), d.end());
		PmergeMe::sort(d);
		TEST_ASSERT(is_sorted(d))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_deque_6)
	TEST_LOGIC_START
		std::deque<unsigned>	d(6);
		std::deque<unsigned>	dt(6);
		std::generate(d.begin(), d.end(), UnsignedSequence());

		do {
			dt.assign(d.begin(), d.end());
			PmergeMe::sort(dt);
			TEST_ASSERT(is_sorted(dt))
		} while (std::next_permutation(d.begin(), d.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_deque_5)
	TEST_LOGIC_START
		std::deque<unsigned>	d(5);
		std::deque<unsigned>	dt(5);
		std::generate(d.begin(), d.end(), UnsignedSequence());

		do {
			dt.assign(d.begin(), d.end());
			PmergeMe::sort(dt);
			TEST_ASSERT(is_sorted(dt))
		} while (std::next_permutation(d.begin(), d.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_deque_4)
	TEST_LOGIC_START
		std::deque<unsigned>	d(4);
		std::deque<unsigned>	dt(4);
		std::generate(d.begin(), d.end(), UnsignedSequence());

		do {
			dt.assign(d.begin(), d.end());
			PmergeMe::sort(dt);
			TEST_ASSERT(is_sorted(dt))
		} while (std::next_permutation(d.begin(), d.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_deque_3)
	TEST_LOGIC_START
		std::deque<unsigned>	d(3);
		std::deque<unsigned>	dt(3);
		std::generate(d.begin(), d.end(), UnsignedSequence());

		do {
			dt.assign(d.begin(), d.end());
			PmergeMe::sort(dt);
			TEST_ASSERT(is_sorted(dt))
		} while (std::next_permutation(d.begin(), d.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_deque_2)
	TEST_LOGIC_START
		std::deque<unsigned>	d(2);
		std::deque<unsigned>	dt(2);
		std::generate(d.begin(), d.end(), UnsignedSequence());

		do {
			dt.assign(d.begin(), d.end());
			PmergeMe::sort(dt);
			TEST_ASSERT(is_sorted(dt))
		} while (std::next_permutation(d.begin(), d.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_deque_1)
	TEST_LOGIC_START
		std::deque<unsigned>	d(1);
		d[0] = 56;
		PmergeMe::sort(d);
		TEST_ASSERT(is_sorted(d))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_deque_0)
	TEST_LOGIC_START
		std::deque<unsigned>	d;
		PmergeMe::sort(d);
		TEST_ASSERT(d.empty())
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_15000)
	TEST_LOGIC_START
		std::vector<unsigned>	v(15000);

		std::generate(v.begin(), v.end(), UnsignedSequence());
		std::random_shuffle(v.begin(), v.end());
		PmergeMe::sort(v);
		TEST_ASSERT(is_sorted(v))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_nonunique)
	TEST_LOGIC_START
		std::vector<unsigned>	v(301);

		std::generate(v.begin(), v.end(), UnsignedSequence(5));
		std::random_shuffle(v.begin(), v.end());
		PmergeMe::sort(v);
		TEST_ASSERT(is_sorted(v))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_21)
	TEST_LOGIC_START
		std::vector<unsigned>	v(21);

		std::generate(v.begin(), v.end(), UnsignedSequence());
		std::random_shuffle(v.begin(), v.end());
		PmergeMe::sort(v);
		TEST_ASSERT(is_sorted(v))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_6)
	TEST_LOGIC_START
		std::vector<unsigned>	v(6);
		std::vector<unsigned>	vt(6);
		std::generate(v.begin(), v.end(), UnsignedSequence());

		do {
			vt.assign(v.begin(), v.end());
			PmergeMe::sort(vt);
			TEST_ASSERT(is_sorted(vt))
		} while (std::next_permutation(v.begin(), v.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_5)
	TEST_LOGIC_START
		std::vector<unsigned>	v(5);
		std::vector<unsigned>	vt(5);
		std::generate(v.begin(), v.end(), UnsignedSequence());

		do {
			vt.assign(v.begin(), v.end());
			PmergeMe::sort(vt);
			TEST_ASSERT(is_sorted(vt))
		} while (std::next_permutation(v.begin(), v.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_4)
	TEST_LOGIC_START
		std::vector<unsigned>	v(4);
		std::vector<unsigned>	vt(4);
		std::generate(v.begin(), v.end(), UnsignedSequence());

		do {
			vt.assign(v.begin(), v.end());
			PmergeMe::sort(vt);
			TEST_ASSERT(is_sorted(vt))
		} while (std::next_permutation(v.begin(), v.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_3)
	TEST_LOGIC_START
		std::vector<unsigned>	v(3);
		std::vector<unsigned>	vt(3);
		std::generate(v.begin(), v.end(), UnsignedSequence());

		do {
			vt.assign(v.begin(), v.end());
			PmergeMe::sort(vt);
			TEST_ASSERT(is_sorted(vt))
		} while (std::next_permutation(v.begin(), v.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_2)
	TEST_LOGIC_START
		std::vector<unsigned>	v(2);
		std::vector<unsigned>	vt(2);
		std::generate(v.begin(), v.end(), UnsignedSequence());

		do {
			vt.assign(v.begin(), v.end());
			PmergeMe::sort(vt);
			TEST_ASSERT(is_sorted(vt))
		} while (std::next_permutation(v.begin(), v.end()));
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_1)
	TEST_LOGIC_START
		std::vector<unsigned>	v(1);
		v[0] = 56;
		PmergeMe::sort(v);
		TEST_ASSERT(is_sorted(v))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pmergeme_vector_0)
	TEST_LOGIC_START
		std::vector<unsigned>	v;
		PmergeMe::sort(v);
		TEST_ASSERT(v.empty())
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

static bool is_sorted(std::deque<unsigned> const& v) {
	std::deque<unsigned>::const_iterator it = v.begin();
	for (std::deque<unsigned>::const_iterator in = std::lower_bound(it + 1, v.end(), *it);
		 it != v.end() - 1 && in == it + 1; it += 1)
		in = std::lower_bound(in + 1, v.end(), *in);
	return it == v.end() - 1;
}
