#pragma once

#include <string>

class RPN {
	public:
		static float calculate(std::string input);
		

	private:
		RPN();
		~RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);

		static float addition(float a, float b);
		static float subtraction(float a, float b);
		static float multiplication(float a, float b);
		static float division(float a, float b);

};