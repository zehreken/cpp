#include <iostream>
#include <deque> 
using namespace std;

int main()
{ 
    int testCount = 0;
    int testCounter = 0;
    scanf("%d", &testCount);
    
    while (testCounter < testCount)
    {
        int arraySize = 0;
        int subArraySize = 0;
        scanf("%d", &arraySize);
        scanf("%d", &subArraySize);
        deque<int> d;
        for (int i = 0; i < arraySize; ++i)
        {
            int a = 0;
            cin >> a;
            d.push_back(a);
            if (d.size() == subArraySize)
            {
                int max = 0;
                for (int i = 0; i < subArraySize; ++i)
                {
                    if (d[i] > max) max = d[i];
                }
                printf("%d ", max);
                d.pop_front();
            }
        }
        /*
        while (d.size() >= subArraySize)
        {
            int max = 0;
            for (int i = 0; i < subArraySize; ++i)
            {
                if (d[i] > max) max = d[i];
            }
            d.pop_front();
            printf("%d ", max);
        }
        //*/
        printf("\n");
        ++testCounter;
    }
    
    return 0;
}

