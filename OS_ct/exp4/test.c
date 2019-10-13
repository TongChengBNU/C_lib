#include <time.h>
#include <stdio.h>

int main()
{
    time_t now;
    now = time(NULL);
    printf("%s", ctime(&now));
    return 0;
}

