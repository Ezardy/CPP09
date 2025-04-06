#ifndef EX02_PMERGEME_HPP
#define EX02_PMERGEME_HPP

#include <deque>
#include <new>
#include <vector>

class PmergeMe {
public:
	static void sort(std::vector<unsigned>& vec) throw(std::bad_alloc);
	static void sort(std::deque<unsigned>& deq) throw(std::bad_alloc);

private:
	PmergeMe(void) throw();
	PmergeMe(PmergeMe const& other) throw();
	~PmergeMe(void) throw();

	PmergeMe& operator=(PmergeMe const& other) throw();
};
#endif
