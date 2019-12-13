#include <string.h>
#include <stdio.h>

int main()
{
    char buffer[] = "Hello";

    for (int i=0; i<strlen(buffer); i++)
    {
        printf("%c ", buffer[i]);
    }
    printf("%s", buffer);
    return 0;
}
