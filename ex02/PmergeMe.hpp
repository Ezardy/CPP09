#ifndef EX02_PMERGEME_HPP
#define EX02_PMERGEME_HPP

#include <deque>
#include <new>
#include <vector>

void pmergeme(std::vector<unsigned>& vec) throw(std::bad_alloc);
void pmergeme(std::deque<unsigned>& deq) throw(std::bad_alloc);
#endif
