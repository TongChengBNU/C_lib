/************************************************************************
 > File Name: parse.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Tue 03 Dec 2019 06:42:02 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if( argc != 2)
	{
		fprintf(stderr, "Correct usage: parse <frame>\n");	
		exit(1);
	}

	FILE *frame_file = fopen(argv[1], "r");
	// if frame_file == NULL, then open failed;
	if(!frame_file)
	{
		fprintf(stderr, "Open frame failed;\n");	
		exit(1);	
	}
	int nFileEnd;
	nFileEnd = fseek(frame_file, 0L, SEEK_SET);
	printf("File length: %d\n", nFileEnd);

	
	return 0;
}
