#include "PmergeMe.hpp"

#include <algorithm>
#include <cstddef>

static void pmergeme_recursive(std::vector<unsigned>& v, unsigned track);
static void pairing(std::vector<unsigned>& v, unsigned track);
static void insertion(std::vector<unsigned>& v, unsigned track, std::size_t b_len);
static void binary_insertion(std::vector<unsigned>& v, unsigned track, std::size_t dtlb,
							 size_t& blb, size_t& alb);

void pmergeme(std::vector<unsigned>& vec) {
	pmergeme_recursive(vec, 1);
}

static void pmergeme_recursive(std::vector<unsigned>& v, unsigned track) {
	pairing(v, track);
	track *= 2;
	std::size_t b_len = v.size() / track;
	if (b_len > 1)
		pmergeme_recursive(v, track);
	b_len += v.size() % track / (track / 2);
	if (b_len > 1)
		insertion(v, track, b_len);
}

static void pairing(std::vector<unsigned>& v, unsigned track) {
	unsigned	step = track * 2;
	std::size_t len = v.size() / step * step;
	for (unsigned i = track - 1; i < len; i += step)
		if (v[i] > v[i + track])
			std::swap_ranges(v.begin() + (i + 1 - track), v.begin() + (i + 1), v.begin() + (i + 1));
}

static void insertion(std::vector<unsigned>& v, unsigned track, std::size_t b_len) {
	unsigned	k = 2;
	std::size_t lb = 1;
	std::size_t blb = 2;

	for (std::size_t t = 0; t < b_len; k += 1, lb = t) {
		t = ((1u << (k + 1)) + 1 - 2 * (k & 1)) / 3;
		if (t > b_len)
			t = b_len;
		std::size_t alb = 0;
		std::size_t lblb = blb;
		for (std::size_t tb = t - 1; tb >= lb; tb -= 1)
			binary_insertion(v, track, tb - lb, lblb, alb);
		blb += (alb + lblb - blb) * 2;
	}
}

static void binary_insertion(std::vector<unsigned>& v, unsigned track, std::size_t dtlb,
							 size_t& blb, size_t& alb) {
	unsigned						old_track = track / 2;
	std::vector<unsigned>::iterator itb_b =
		dtlb ? v.begin() + ((blb + alb) * old_track + dtlb * track) : v.begin() + blb * old_track;
	std::vector<unsigned>::iterator itb_e = itb_b + old_track;
	unsigned const&					val = itb_b[old_track - 1];
	if (itb_e > v.end())
		itb_e = v.end();
	std::size_t min_d = 0;
	std::size_t max_d = dtlb ? blb + alb : blb - 1;	 // bug (may be alb is extra)
	bool		gt;
	bool		same = false;
	while (min_d != max_d) {
		std::size_t		d = (min_d + max_d) / 2;
		unsigned const& dv = v[(d + (d >= blb) + 1) * old_track - 1];
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
		gt = val > v[(max_d + (max_d >= blb) + 1) * old_track - 1];
	if (max_d > blb || (max_d == blb && gt))
		alb += 1;
	else
		blb += 1;
	std::vector<unsigned>::iterator ito = v.begin() + ((max_d + (max_d >= blb) + gt) * old_track);
	std::rotate(ito, itb_b, itb_e);
}
