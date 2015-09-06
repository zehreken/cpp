#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

vector<int> calcBigInt()
{
    
}

// Tn+2 = (Tn+1)^2 + Tn
int calcExpTerm(int firstTerm, int secondTerm, int expTerm)
{
    vector<int> bigInt(20000, 0);
    bigInt[0] = 1;
    int bigDigit = 0;
    
    int nTerm, nplusoneTerm, nplustwoTerm;
    nTerm = firstTerm;
    nplusoneTerm = secondTerm;
    for (int i = 2; i < expTerm; ++i)
    {
        for (int j = 0; j < bigInt.size(); ++j)
        {
            int digit = bigInt[i];
            // digit = digit
        }
        nplustwoTerm = pow(nplusoneTerm, 2) + nTerm;
        nTerm = nplusoneTerm;
        nplusoneTerm = nplustwoTerm;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int firstTerm, secondTerm, expTerm;
    string input;
    cin >> firstTerm;
    cin >> secondTerm;
    cin >> expTerm;
    
    cout << calcExpTerm(firstTerm, secondTerm, expTerm) << endl;
    
    return 0;
}
