#include <iostream>

long long int factorial(int num){
	if (num == 1){
		return num;
	}
	else if (num == 0){
		return 1;
	}
	else {
		return factorial(num-1) * num;
	}
}


int main(int argc, char const *argv[])
{
	int num;
	std::cout << "enter a number : " ;
	std::cin >> num;
	std::cout << num ;
	std::cout << "! = ";

	long long int result = factorial(num);

	std::cout << result << std::endl;
	
	return 0;
}