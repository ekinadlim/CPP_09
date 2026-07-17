#include "Lib.hpp"

#include <limits>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <time.h>

int Lib::atoi(std::string str) {
	std::string::size_type index = str.find_first_not_of("0123456789");

	if (index != std::string::npos)
		throw std::runtime_error(str + " is a bad input.");

	long num = 0;
	std::stringstream ss(str);
	ss >> num;
	if (num > std::numeric_limits<int>().max())
		throw std::runtime_error(str + " overflows.");
	return static_cast<int>(num);
}

void Lib::start_timer(timeval *timer) {
	gettimeofday(timer, NULL);
}

double Lib::stop_timer(const timeval *timer) {
	timeval end;
	gettimeofday(&end, NULL);
	return (end.tv_sec - timer->tv_sec) * 1000000 + (end.tv_usec - timer->tv_usec);
}