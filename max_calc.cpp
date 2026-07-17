#include <iostream>
#include <cmath>

int F(int n) {
	int sum = 0;
	for (int k = 1; k <= n; ++k) {
		double value = (3.0 / 4.0) * k;
		sum += static_cast<int>(ceil(log2(value)));
	}
	return sum;
}

int main(void) {
	std::cout << "Max Comps: " << F(101) << std::endl;
}