#include <iostream>


int sumOfEvenSquares(int upperLim){
	
	if (upperLim % 2 == 0){
		return sumOfEvenSquares(upperLim-1) + (upperLim * upperLim);
	}
	else if (upperLim % 2 != 0 && upperLim != 1){
		return sumOfEvenSquares(upperLim - 1);
	} 
	else {
		return 0;
	}
}


int main(int argc, char const *argv[])
{
	/* code */
	int num, result;
	std::cout << "Enter a number : ";
	std::cin >> num; 
	result = sumOfEvenSquares(num);
	std:: cout << result << std::endl;

	return 0;
}