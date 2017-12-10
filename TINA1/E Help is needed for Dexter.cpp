#include <cmath>
#include<iostream>
using namespace std;
int main()
{
     int n;
     while (cin>>n)
     {
         cout << (int)log2(n) + 1 << endl;
     }
     return 0;
}