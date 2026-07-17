#include "PmergeMe.hpp"

void PmergeMe::pair_and_split(const std::vector<vNode> &input, std::vector<vNode> &big, std::vector<vNode> &small) {
	for (std::size_t i = 0; i + 1 < input.size(); i += 2) {
		vNode bigNode;
		vNode smallNode;

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

std::vector<PmergeMe::vNode> PmergeMe::recursive(std::vector<vNode> input, std::size_t rec_level) {
	if (input.size() <= 1)
		return input;

	std::vector<vNode> big_vector;
	std::vector<vNode> small_vector;
	big_vector.reserve(input.size() / 2);
	small_vector.reserve(input.size() / 2);

	print_container("Input: ", input, DEBUG);
	pair_and_split(input, big_vector, small_vector);

	if (input.size() % 2) {
		vNode leftoverNode = input.back();
		leftoverNode.groupId.push_back(-1);
		small_vector.push_back(leftoverNode);
	}

	if (big_vector.size() != 1) {
		big_vector = recursive(big_vector, rec_level + 1);
	}
	//std::cout << "\nRecursion Level: " << rec_level << std::endl;
	std::vector<std::size_t> order = build_jacobsthal_order<std::vector<std::size_t> >(small_vector.size());
	for (std::size_t i = 0; i < small_vector.size(); ++i) {
		const vNode &node = small_vector[order[i]];
		//std::cout << "Small to insert: " << node.value << std::endl;
		int max_bound = get_big_index<std::vector<vNode> >(big_vector, node.groupId.back(), rec_level);
		if (max_bound == -1)
			max_bound = big_vector.size();
		std::size_t pos = binary_search<std::vector<vNode> >(big_vector, node.value, max_bound, _vec_comps);
		big_vector.insert(big_vector.begin() + pos, node);
	}
	return big_vector;
}

void PmergeMe::fja_vec() {
	std::vector<vNode> nodes;
	nodes.reserve(_vec.size());

	for (std::size_t i = 0; i < _vec.size(); ++i) {
		vNode n;
		n.value = _vec[i];
		nodes.push_back(n);
	}

	std::vector<vNode> sorted = recursive(nodes, 0);

	std::vector<int> result;
	result.reserve(sorted.size());
	for (std::size_t i = 0; i < sorted.size(); ++i)
		result.push_back(sorted[i].value);

	_vec = result;
}