#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int a = 8888;
    int count;
    char buffer[1024];
    char cmd[] = " Start\0";

    sprintf(buffer, "%d", a);
    sprintf(buffer, "%d", a);
    strcat(buffer, cmd);

    fprintf(stdout, "%s\n", buffer);
    fprintf(stdout, "%ld\n", sizeof(buffer));
    fflush(stdout);
    return 0;
}
