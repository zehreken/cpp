#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    vector<int> bigInt(20000, 0); // holds each digit of the big integer, digit significancy increases with index
    bigInt[0] = 1;
    int n;
    cin >> n;
    int bigDigit = 0;
    for (int j = 2; j <= n; ++j)
    {
        for (int i = 0; i < bigInt.size(); ++i)
        {
            int digit = bigInt[i];
            digit = digit * j + bigDigit;
            bigDigit = 0;
            bigInt[i] = digit % 10;
            if (digit >= 10)
            {
                digit = digit / 10;
                bigDigit = digit;
            }
        }
    }
    bool start = false;
    for (int i = bigInt.size() - 1; i >= 0; --i)
    {
        if (bigInt[i] != 0) start = true;
        if (start) cout << bigInt[i];
    }
    cout << endl;
    cout << bigInt[bigInt.size() - 1] << endl;
    
    return 0;
}
