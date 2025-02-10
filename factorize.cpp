#include <iostream>
#include <vector>
#include <chrono>

// Function to factorize a number into its prime factors
std::vector<int> factorize(int n) {
    std::vector<int> factors;

    // Divide by 2 until n is odd
    while (n % 2 == 0) {
        factors.push_back(2);
        n = n / 2;
    }

    // Check for odd factors from 3 to sqrt(n)
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n = n / i;
        }
    }

    // If n is still greater than 2, it must be prime
    if (n > 2) {
        factors.push_back(n);
    }

    return factors;
}

int main() {
    int number;
    std::cout << "Number to factorize: ";
    std::cin >> number;

    auto start = std::chrono::high_resolution_clock::now();
    // Get the prime factors
    std::vector<int> factors = factorize(number);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Print the factors
    if (factors.size() == 1) {
        std::cout << number << " is a prime number!" << std::endl;
    } 
    else {
        std::cout << number << " { ";
        for (int factor : factors) {
            std::cout << factor << " ";
        }
        std::cout << "}";
        std::cout << std::endl;
    }
    std::cout << duration.count() << " milliseconds " << std::endl;
    return 0;
}