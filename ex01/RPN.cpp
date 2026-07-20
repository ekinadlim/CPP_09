#include "RPN.hpp"
#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <stack>

RPN::RPN() {}
RPN::~RPN() {}
RPN::RPN(const RPN &other) { (void)other; }
RPN& RPN::operator=(const RPN &other) { (void)other; return (*this); }

float RPN::addition(float a, float b) { return a + b; }
float RPN::subtraction(float a, float b) { return a - b; }
float RPN::multiplication(float a, float b) { return a * b; }
float RPN::division(float a, float b) {
	if (b == 0)
		throw std::runtime_error("Cannot divide by 0");
	return a / b; 
}

float RPN::calculate(std::string input) {
	if (input.empty())
		throw std::runtime_error("Empty input");
	
	std::stack<float> stack;

	for (std::size_t i = 0; i < input.size(); ++i) {
		if (std::isdigit(static_cast<unsigned char>(input[i]))) {
			stack.push(static_cast<float>(input[i] - '0'));
		}
		else {
			if (stack.size() < 2)
				throw std::runtime_error("Not enough digits");
			float b = stack.top();
			stack.pop();
			float a = stack.top();
			stack.pop();
			switch (input[i]) {
				case '+': stack.push(addition(a, b)); break;
				case '-': stack.push(subtraction(a, b)); break;
				case '*': stack.push(multiplication(a, b)); break;
				case '/': stack.push(division(a, b)); break;
				default: throw std::runtime_error("Invalid character");
			}
		}
	}
	
	if (stack.size() != 1)
		throw std::runtime_error("Operator missing");

	return stack.top();
}
