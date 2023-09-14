#include <stdio.h>
#include <stdlib.h>
char a[20];
double expt()
{
    scanf("%s",a);
    switch(a[0])
    {
        case '+':
            return expt()+expt();
        case '-':
            return expt()-expt();
        case '*':
            return expt()*expt();
        case '/':
            return expt()/expt();
        default:
            return atof(a);
    }
    return a[0];
}
int main()
{
 
    double ans=0;
    ans=expt();
    printf("%lf\n",ans);
    return 0;
}