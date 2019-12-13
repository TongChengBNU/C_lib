#include <stdio.h>
#include <string.h>

int main()
{
    char buffer[1024];
    char cache[1024];

    fgets(buffer, 1024, stdin);
    strcpy(cache, buffer);
    fprintf(stdout, "%s", cache);

    if (strcmp(cache, buffer) == 0)
        printf("Identical;");

    return 0;

}
