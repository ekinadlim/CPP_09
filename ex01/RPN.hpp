#pragma once

#include <string>

class RPN {
	public:
		static int calculate(std::string input);
		

	private:
		RPN();
		~RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);

		static int addition(int a, int b);
		static int subtraction(int a, int b);
		static int multiplication(int a, int b);
		static int division(int a, int b);

};