#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int data_meta[] = {1, 2, 3, 4, 5};
	int *data = data_meta;
	printf("*data++: %d\n", *data++);
	printf("*(data++): %d\n", *(data++));
	printf("*data: %d\n", *data);
	printf("(*data)++: %d\n", (*data)++);
	printf("(*data)++: %d\n", (*data)++);
	return 0;
}
