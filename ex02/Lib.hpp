#pragma once

#include <string>
#include <sys/time.h>

class Lib {
	public:
		static int atoi(std::string str);
		static void start_timer(timeval *timer);
		static double stop_timer(const timeval *timer);
		static int jacobsthal(std::size_t num);

	private:
		Lib();
		Lib(const Lib &other);
		Lib &operator=(const Lib &other);
		~Lib();
};
