#include "PmergeMe.hpp"
#include "Lib.hpp"

#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <time.h>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }
PmergeMe& PmergeMe::operator=(const PmergeMe &other) { (void)other;	return (*this); }
PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(int argc, char** argv, bool setDebugMode)
	: _vec_comps(0), _deq_comps(0), _is_debug_mode(setDebugMode), _num_count(argc - 1) {
	timeval timer;
	double vec_time;
	double deq_time;

	parse_numbers(argv);

	std::vector<int> correct_sorted_vec(_vec);
	std::sort(correct_sorted_vec.begin(), correct_sorted_vec.end());

	print_container("Before:\t", _vec);

	Lib::start_timer(&timer);
	fja_vec();
	vec_time = Lib::stop_timer(&timer);

	Lib::start_timer(&timer);
	fja_deq();
	deq_time = Lib::stop_timer(&timer);

	print_container("After:\t", _vec);

	print_timer(vec_time, "vector");
	print_timer(deq_time, "deque ");
	//std::cout << "comparisons " << _vec_comps << std::endl;
}

void PmergeMe::parse_numbers(char **argv) {
	if (_num_count < MIN_ARG)
		throw std::runtime_error("Arg count should be higher than minimum.");
	else if (_num_count > MAX_ARG)
		throw std::runtime_error("Arg count should be lower than maximum.");

	std::string str_arg;
	int num;
	for (size_t i = 1; i <= _num_count; i++) {
		str_arg = std::string(argv[i]);
		if (!str_arg.empty()) {
			num = Lib::atoi(str_arg);

			if (std::find(_vec.begin(), _vec.end(), num) != _vec.end())
				throw std::runtime_error("Duplicate numbers are not accepted");
			
			_vec.push_back(num);
			_deq.push_back(num);
		}
	}
}

int PmergeMe::jacobsthal(std::size_t num) {
	if (num <= 1)
		return num;
	std::size_t a = 0, b = 1, c;
	for (std::size_t i = 2; i <= num; ++i) {
		c = b + 2 * a;
		a = b;
		b = c;
	}
	return b;
}

void PmergeMe::print_timer(double time, std::string containerName) {
	std::cout
		<< "Time to process a range of " << _num_count
		<< " elements with std::" << containerName
		<< " : " << time << " us" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const PmergeMe::vNode& node) {
	os << node.value;
	return os;
}

std::ostream& operator<<(std::ostream& os, const PmergeMe::dNode& node) {
	os << node.value;
	return os;
}