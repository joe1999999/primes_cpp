#include <iostream>
#include <cmath>
#include <vector>

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to generate prime numbers up to a given limit
std::vector<int> generatePrimes(int limit) {
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Function to calculate the difference between square roots of consecutive primes
void calculateSquareRootDifferences(const std::vector<int>& primes) {
    for (size_t i = 1; i < primes.size(); ++i) {
        double sqrtCurrent = std::sqrt(primes[i]);
        double sqrtPrevious = std::sqrt(primes[i - 1]);
        double difference = sqrtCurrent - sqrtPrevious;
        //std::cout << "Difference between sqrt(" << primes[i] << ") and sqrt(" << primes[i - 1] << ") = " << difference << std::endl;
        std::cout << difference << " ";

    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }
    int limit = atoi(argv[1]);
    

    std::vector<int> primes = generatePrimes(limit);

    if (primes.size() < 2) {
        std::cout << "Not enough primes to calculate differences." << std::endl;
    } else {
        calculateSquareRootDifferences(primes);
    }

    return 0;
}