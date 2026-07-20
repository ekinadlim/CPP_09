#include "PmergeMe.hpp"

template <typename C>
C PmergeMe::build_jacobsthal_order(std::size_t num) {
	C order;
	order.push_back(0);
	if (num == 1)
		return order;

	std::size_t prev = 1;
	for (std::size_t k = 3; order.size() < num; ++k) {
		std::size_t curr = static_cast<std::size_t>(jacobsthal(k));
		std::size_t end = std::min(curr, num);

		while (end > prev && order.size() < num) {
			order.push_back(end - 1);
			--end;
		}
		prev = curr;
	}
	return order;
}

template <typename C>
int	PmergeMe::binary_search(const C &range, int num, std::size_t max, std::size_t &comparisonCount) {
	size_t min = 0;
	
	while (min < max) {
		std::size_t mid = min + (max - min) / 2;
		++comparisonCount;
		if (num <= range[mid].value)
			max = mid;
		else
			min = mid + 1;
	}
	return min;
}

template <typename C>
int PmergeMe::get_big_index(const C &big_vector, int groupId, std::size_t level) {
	print_container("Vector: ", big_vector, DEBUG);
	for (std::size_t i = 0; i < big_vector.size(); ++i) {
		if (level + 1 < big_vector[i].groupId.size() && big_vector[i].groupId[level] == groupId)
			return i;
	}
	return -1;
}

template <typename C>
void PmergeMe::print_container(std::string prefixMessage, const C &container, bool debugMode) {
	if (!_is_debug_mode && debugMode)
		return;
	std::cout << prefixMessage;
	for (std::size_t i = 0; i < container.size(); i++) {
		std::cout << " " << container[i];
	}
	std::cout << std::endl;
}
