#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>


using namespace std;

void sieveOfEratosthenes(int limit) {
    // Create a boolean array to mark primes
    std::vector<bool> isPrime(limit + 1, true);

    // 0 and 1 are not prime numbers
    isPrime[0] = isPrime[1] = false;


    auto start = std::chrono::high_resolution_clock::now();
    // Apply the Sieve of Eratosthenes
    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            // Mark multiples of p as non-prime
            for (int i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto milli_duration =  duration.count();
   	int howmany = 0;
    
    char answer;
    std::cout << "Save data to file or print it? [S(ave)/P(rint)] ";
    cin >> answer;
    
    if (answer == 'S' || answer == 's') {
        ofstream Primes("Generated_Primes.txt");
        for (int p = 2; p <= limit; p++) {
            if (isPrime[p]) {
                howmany+=1;
                //std::cout << p << " ";
                Primes << p << " ";
            }
            
        }
        Primes << endl;
        Primes << howmany <<" Primes between 0 and " << limit << endl;
        Primes << "Process took " << milli_duration << " milliseconds"<< endl;
        Primes.close();
        cout << "Data Written to 'Generated_Primes' "<< endl;   
        
    }
    else if (answer == 'P' || answer == 'p') {
        for (int p = 2; p <= limit; p++) {
            if (isPrime[p]) {
                howmany+=1;
                std::cout << p << " ";
            }
        } 
        std::cout << std::endl << howmany << " Primes between 0 and " << limit << std::endl;
        std::cout << std::endl << "Process took " << milli_duration << " milliseconds"<< std::endl;

    }
    else {
        cout << "Invalid Answer!" << endl;
    }    
}

int main() {
    int limit;
    std::cout << "Enter an upper limit: ";
    std::cin >> limit;
    sieveOfEratosthenes(limit);
    return 0;
}