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

int RPN::addition(int a, int b) { return a + b; }
int RPN::subtraction(int a, int b) { return a - b; }
int RPN::multiplication(int a, int b) { return a * b; }
int RPN::division(int a, int b) {
	if (b == 0)
		throw std::runtime_error("Cannot divide by 0");
	return a / b; 
}

int RPN::calculate(std::string input) {
	if (input.empty())
		throw std::runtime_error("Empty input");
	
	std::stack<int> stack;

	for (std::size_t i = 0; i < input.size(); ++i) {
		if (std::isdigit(static_cast<unsigned char>(input[i]))) {
			stack.push(static_cast<int>(input[i] - '0'));
		}
		else {
			if (stack.size() < 2)
				throw std::runtime_error("Not enough digits");
			int b = stack.top();
			stack.pop();
			int a = stack.top();
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
