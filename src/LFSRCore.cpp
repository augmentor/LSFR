

#include <iostream>
#include <chrono>
#include <bitset>
#include <string>
#include "LFSR.h"
#include "test.h"

int main() 
{
    using namespace std;
    auto t1 = std::chrono::high_resolution_clock::now();
    cout << "TEST RESULT : " << (0 == RunSmallTest()? "PASSED" : "FAILED") << endl;
    auto t2 = std::chrono::high_resolution_clock::now();
    cout << "TEST TIME FOR 10 CALLS : " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " us" << endl;

    std::string UserInput("none");
  while ('q' != tolower(UserInput[0]))
    {
        uint64_t Seed = 1;
        uint64_t Steps = 1;
        cout << "Enter the seed : ";
        cin >> Seed;
        cout << "Enter the number of steps(shift) : ";
        cin >> Steps;
        t1 = std::chrono::high_resolution_clock::now();
        uint64_t State = rfsr42(Steps, Seed);
        t2 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 42; i++) 
        {
            cout << ((State >> i) & 1);
        }
        cout <<endl<< "Execution time : " << 0.001*std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " ms" << endl;
        cout << "Enter 'Q' or 'quit' to end the program : ";
        cin >> UserInput;
    }
    

    return 0;
}
