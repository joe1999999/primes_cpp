#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


int how_many_primes(int limit){
  	// Create a boolean array to mark primes
    std::vector<bool> isPrime(limit + 1, true);

    // 0 and 1 are not prime numbers
    isPrime[0] = isPrime[1] = false;

    int howmany = 0;
    // Apply the Sieve of Eratosthenes
    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            // Mark multiples of p as non-prime
            for (int i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }

    for (int p = 2; p <= limit; p++) {
            if (isPrime[p]) {
                howmany+=1;
                //std::cout << p << std::endl;
                
            }
       }
    
     return howmany;


}

int main(int argc, char const *argv[])
{	
	 if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }

    int li = atoi(argv[1]);
    int previous_how = -1; // Initialize to a value that won't be returned by how_many_primes
    int count = 0;

    for (int i = 2; i <= li; i++) {
        int how = how_many_primes(i);

        if (how == previous_how) {
            count++; // Increment count if the value is the same as the previous one
        } else {
            if (count > 0) {
                // std::cout << "The value " << previous_how << " stayed the same " << count + 1 << " times." << std::endl;
                std::cout <<  count + 1 << " ";
            }
            previous_how = how;
            count = 0; // Reset count for the new value
        }

        //std::cout << how << std::endl;
    }

    // Print the count for the last sequence of the same 'how' value
    if (count > 0) {
        //std::cout << "The value " << previous_how << " stayed the same " << count + 1 << " times." << std::endl;
        std::cout <<  count + 1 << " ";
    }

}