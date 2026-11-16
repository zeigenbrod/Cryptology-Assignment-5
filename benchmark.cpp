#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bigint.h"

using namespace std;




int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./bench_bigint bench_inputs.txt [iterations]\n";
        return 1;
    }

    int iterations = 200;
    if (argc > 2) {
        iterations = stoi(argv[2]);
    }

    vector<int> bitSizes;
    vector<vector<uint8_t>> numbersA;
    vector<vector<uint8_t>> numbersB;

    ifstream file(argv[1]);
    int bits;
    string a, b;



    while (file >> bits >> a >> b) {
        bitSizes.push_back(bits);
        numbersA.push_back(bigint_init(a));
        numbersB.push_back(bigint_init(b));
    }

    uint64_t checksum = 0;

    for (int size = 0; size < 3; size++) {
        int currentBits = 256 << size;  
        
        int count = 0;

        for (int i = 0; i < bitSizes.size(); i++) {
            if (bitSizes[i] == currentBits) count++;
        }

        if (count == 0) continue;

        for (int i = 0; i < bitSizes.size(); i++) {
            if (bitSizes[i] == currentBits) {
                vector<uint8_t> result = bigint_multiply(numbersA[i], numbersB[i]);
                
                checksum += result.size();
            }
        }

        auto start = chrono::steady_clock::now();

        for (int i = 0; i < iterations; i++) {
            for (int j = 0; j < bitSizes.size(); j++) {
                if (bitSizes[j] == currentBits) {
                    vector<uint8_t> result = bigint_multiply(numbersA[j], numbersB[j]);
                    checksum += result.size() + result[0];
                }
            }
        }

        auto stop = chrono::steady_clock::now();

        double elapsed = chrono::duration<double, nano>(stop - start).count();
        double total = iterations * count;

        cout << currentBits << " " << elapsed / total << "\n";
    }

    return 0;
}