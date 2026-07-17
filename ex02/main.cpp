#include "PmergeMe.hpp"

#include <iostream>
#include <exception>

int main(int argc, char **argv) {
	try {
	/////////
	PmergeMe pmm(argc, argv);

	/////////
	} catch (std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

