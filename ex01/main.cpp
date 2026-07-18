#include "RPN.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <algorithm>


std::string validate_and_cleanup_input(std::string input) {
	input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end());
	return input;
}

int main(int argc, char **argv) {
	try {
	///////
	if (argc > 2)
		throw std::runtime_error("Too many arguments");
	else if (argc < 2)
		throw std::runtime_error("Need 1 argument");
	std::string input(argv[1]);

	input = validate_and_cleanup_input(input);

	int result = RPN::calculate(input);
	std::cerr << result << std::endl;
	////////
	} catch (std::exception & e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}