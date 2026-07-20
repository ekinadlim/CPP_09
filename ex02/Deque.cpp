#include "PmergeMe.hpp"

void PmergeMe::pair_and_split(const std::deque<dNode> &input, std::deque<dNode> &big, std::deque<dNode> &small) {
	for (std::size_t i = 0; i + 1 < input.size(); i += 2) {
		dNode bigNode;
		dNode smallNode;

		if (input[i].value <= input[i + 1].value) {
			bigNode.value = input[i + 1].value;
			smallNode.value = input[i].value;
			bigNode.groupId = input[i + 1].groupId;
			smallNode.groupId = input[i].groupId;
		}
		else {
			bigNode.value = input[i].value;
			smallNode.value = input[i + 1].value;
			bigNode.groupId = input[i].groupId;
			smallNode.groupId = input[i + 1].groupId;
		}
		
		bigNode.groupId.push_back(static_cast<int>(i / 2));
		smallNode.groupId.push_back(static_cast<int>(i / 2));
		big.push_back(bigNode);
		small.push_back(smallNode);
	}
}

std::deque<PmergeMe::dNode> PmergeMe::recursive(std::deque<dNode> input, std::size_t rec_level) {
	if (input.size() <= 1)
		return input;

	std::deque<dNode> big_deque;
	std::deque<dNode> small_deque;

	print_container("Input: ", input, DEBUG);
	pair_and_split(input, big_deque, small_deque);

	if (input.size() % 2) {
		dNode leftoverNode = input.back();
		leftoverNode.groupId.push_back(-1);
		small_deque.push_back(leftoverNode);
	}

	if (big_deque.size() != 1) {
		big_deque = recursive(big_deque, rec_level + 1);
	}
	std::deque<std::size_t> order = build_jacobsthal_order<std::deque<size_t> >(small_deque.size());
	for (std::size_t i = 0; i < small_deque.size(); ++i) {
		const dNode &node = small_deque[order[i]];
		int max_bound = get_big_index<std::deque<dNode> >(big_deque, node.groupId.back(), rec_level);
		if (max_bound == -1)
			max_bound = big_deque.size();
		std::size_t pos = binary_search<std::deque<dNode> >(big_deque, node.value, max_bound, _deq_comps);
		big_deque.insert(big_deque.begin() + pos, node);
	}
	return big_deque;
}

void PmergeMe::fja_deq() {
	std::deque<dNode> nodes;

	for (std::size_t i = 0; i < _deq.size(); ++i) {
		dNode n;
		n.value = _deq[i];
		nodes.push_back(n);
	}

	std::deque<dNode> sorted = recursive(nodes, 0);

	std::deque<int> result;
	for (std::size_t i = 0; i < sorted.size(); ++i)
		result.push_back(sorted[i].value);

	_deq = result;
}