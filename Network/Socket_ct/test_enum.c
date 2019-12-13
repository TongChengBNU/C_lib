#include <stdio.h>

int main()
{
    enum OPTION 
    {
        A=1,B=2,C=3 
    };
    enum OPTION option;
    // scanf("%d", &option);
    fprintf(stderr, "%d", option);
    return 0;
}
