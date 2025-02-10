#include <iostream>
#include <cmath>

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= std::sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to print gaps between consecutive primes up to a given limit
void printPrimeGaps(int limit) {
    int previousPrime = 2; // Start with the first prime number
    for (int i = 3; i <= limit; i++) {
        if (isPrime(i)) {
            int gap = i - previousPrime;
            std::cout << gap << ",";
            previousPrime = i; // Update the previous prime
        }
    }
}

int main(int argc, char const *argv[]) {
     if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }
    int limit = atoi(argv[1]);
    

    if (limit < 2) {
        std::cout << "There are no primes below 2." << std::endl;
    } else {
        printPrimeGaps(limit);
    }

    return 0;
}