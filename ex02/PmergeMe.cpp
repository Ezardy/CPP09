#include "PmergeMe.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>

static void pmergeme_recursive(std::vector<unsigned>& v, std::size_t d_pos[], unsigned track);
static void pairing(std::vector<unsigned>& v, unsigned track);
static void insertion(std::vector<unsigned>& v, std::size_t d_pos[], unsigned track,
					  std::size_t b_len);
static void binary_insertion(std::vector<unsigned>& v, std::size_t d_pos[], unsigned track,
							 std::size_t tb, std::size_t lb, std::size_t& a_len,
							 std::size_t& d_len);

void pmergeme(std::vector<unsigned>& vec) throw(std::bad_alloc) {
	std::size_t* d_pos;
	if (vec.size() > 2) {
		std::size_t max_k = static_cast<std::size_t>(
			std::ceil(std::log(vec.size() * 3.0l / 2) / std::log(2.0l)) - 1);
		d_pos = new std::size_t[((1ul << (max_k + 1)) + 1 - 2 * (max_k & 1)) / 3
								- ((1ul << (max_k)) + 1 - 2 * (max_k - 1 & 1)) / 3 - 1];
	} else
		d_pos = NULL;
	pmergeme_recursive(vec, d_pos, 1);
	delete[] d_pos;
}

static void pmergeme_recursive(std::vector<unsigned>& v, std::size_t d_pos[], unsigned track) {
	pairing(v, track);
	std::size_t b_len = v.size() / track / 2;
	if (b_len > 1)
		pmergeme_recursive(v, d_pos, track * 2);
	b_len += v.size() % (track * 2) / track;
	if (b_len > 1)
		insertion(v, d_pos, track, b_len);
}

static void pairing(std::vector<unsigned>& v, unsigned track) {
	unsigned	step = track * 2;
	std::size_t len = v.size() / step * step;
	for (unsigned i = track - 1; i < len; i += step)
		if (v[i] > v[i + track])
			std::swap_ranges(v.begin() + (i + 1 - track), v.begin() + (i + 1), v.begin() + (i + 1));
}

struct SteppingAssigner {
	SteppingAssigner(std::size_t init, std::size_t step) : cur(init), step(step) {}

	void operator()(std::size_t& el) {
		el = cur;
		cur += step;
	}

private:
	std::size_t		  cur;
	std::size_t const step;
};

static void insertion(std::vector<unsigned>& v, std::size_t d_pos[], unsigned track,
					  std::size_t b_len) {
	std::size_t k = 2;
	std::size_t lb = 1;
	std::size_t d_len = 0;

	for (std::size_t t = 0; t < b_len; k += 1, lb = t) {
		t = ((1ul << (k + 1)) + 1 - 2 * (k & 1)) / 3;
		if (t > b_len)
			t = b_len;
		for (std::size_t tb = t - 1; tb >= lb; tb -= 1)
			std::rotate(v.begin() + (tb * 2 - 1) * track, v.begin() + tb * 2 * track,
						v.begin() + (tb * 2 + t - tb) * track);
		std::for_each(d_pos, d_pos + t - lb, SteppingAssigner(lb, track));
		std::size_t a_len = t - lb - 1;
		for (std::size_t tb = t - 1; tb >= lb; tb -= 1)
			binary_insertion(v, d_pos, track, tb, lb, a_len, d_len);
	}
}

struct Adder {
	Adder(std::size_t value) : value(value) {}

	void operator()(std::size_t& el) { el += value; }

private:
	std::size_t const value;
};

static void binary_insertion(std::vector<unsigned>& v, std::size_t d_pos[], unsigned track,
							 std::vector<unsigned>::reverse_iterator rit_e, std::size_t tb,
							 std::size_t lb, std::size_t& a_len, std::size_t& d_len) {
	std::size_t		min_d = 0;
	std::size_t		max_d = a_len + d_len;
	unsigned const& val = ;
	bool			gt;
	bool			same = false;
	while (min_d != max_d) {
		std::size_t		d = (min_d + max_d) / 2;
		unsigned const& dv = v[d_pos[d]];
		if (val <= dv)
			if (d == min_d) {
				same = true;
				gt = false;
				max_d = min_d;
			} else
				max_d = d - 1;
		else
			min_d = d + 1;
	}
	if (!same)
		gt = val > v[d_pos[max_d]];
	if (max_d < a_len || (max_d == a_len && !gt)) {
		std::for_each(d_pos, d_pos + (tb - lb + 1), Adder(track));
		a_len += 1;
	}
	// std::rotate(rit_b, rit_e, v.rend() - ())
	/*
	std::vector<unsigned>::iterator ito = v.begin() + ();
	std::rotate(ito, itb_b, itb_b + track);
	*/
}
