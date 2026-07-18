#include "BitcoinExchange.hpp"

#include <iostream>

#define B_ON "\e[1m"
#define B_OFF "\e[0m"

int main(int argc, char **argv) {
	(void)argc;
	try {
		char data_file_name[] = "data.csv";
		BitcoinExchange btcex(argv[1], data_file_name);
	}
	catch (std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
