#include <time.h>
#include <stdio.h>

int main()
{
    time_t now;
    char buffer[1024];
    now = time(NULL);
    // printf("%s", ctime(&now));
    // buffer = ctime(&now);
    sprintf(buffer, "%s", ctime(&now));
    printf("%s", buffer);
    return 0;
}

