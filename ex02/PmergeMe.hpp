#pragma once

#include <vector>
#include <deque>
#include <string>

#include <iostream>

#define MAX_ARG 3500
#define MIN_ARG 2
#define DEBUG 1

class PmergeMe {
	public:
		PmergeMe(int argc, char **argv, bool setDebugMode = 0);
		~PmergeMe();

		struct vNode {
			int value;
			std::vector<int> groupId;
		};

		struct dNode {
			int value;
			std::vector<int> groupId;
		};

	private:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);

		std::vector<int> 	_vec;
		std::deque<int> 	_deq;
		std::size_t				_vec_comps;
		std::size_t				_deq_comps;

		bool				_is_debug_mode;
		std::size_t _num_count;

		void parse_numbers(char **argv);

		// Universal Functions
		int jacobsthal(std::size_t num);
		template<typename C> C 		build_jacobsthal_order(std::size_t num);
		template<typename C> int 	get_big_index(const C &big_vector, int groupId, std::size_t level);
		template<typename C> int 	binary_search(const C &range, int num, std::size_t max, std::size_t &comparisonCount);

		// Vector
		void fja_vec();
		void pair_and_split(const std::vector<vNode> &input, std::vector<vNode> &big_vector, std::vector<vNode> &small_vector);
		std::vector<vNode> recursive(std::vector<vNode> input, std::size_t rec_level);
		
		// Deque
		void fja_deq();
		void pair_and_split(const std::deque<dNode> &input, std::deque<dNode> &big_vector, std::deque<dNode> &small_vector);
		std::deque<dNode> recursive(std::deque<dNode> input, std::size_t rec_level);

		void print_timer(double time, std::string con);
		template<typename C> void print_container(std::string prefixMessage, const C &container, bool debugMode = 0);
};

std::ostream& operator<<(std::ostream& os, const PmergeMe::vNode& node);
std::ostream& operator<<(std::ostream& os, const PmergeMe::dNode& node);

#include "PmergeMe.tpp"
