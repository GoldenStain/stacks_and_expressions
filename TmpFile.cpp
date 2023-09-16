#include <stdio.h>
#include <stdlib.h>
using namespace std;

inline int read()
{
    int x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') 
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

int main()
{
    int n = read();
    printf("%d\n", n);
    return 0;
}