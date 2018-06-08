#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void check_char(char c){
	switch(c){
		case 22:{
			printf("SYN\n");
			break;
		}
		case 1:{
			printf("SOH\n");
			break;
		}
	}
}

int main(int argc, char **argv){
	if (argc < 2){
		printf("%s <filename>\n", argv[0]);
		return -1;
	}
	FILE *in = fopen(argv[1], "r");
	if (in == NULL){
		perror("");
		return -1;
	}

	char *address = (char *)calloc(6, sizeof(char));
	char *data = (char *)calloc(100, sizeof(char));
	int count = 0;
	int val;
	char c;

	fread(&c, 1, 1, in);
	check_char(c);
	fread(&c, 1, 1, in);
	check_char(c);
	fread(&c, 1, 1, in);
	check_char(c);
	fread(&count, 1, sizeof(int), in);
	printf("COUTN = %d\n", count);
	fread(&val, 1, sizeof(int), in);
	printf("FLAG = %d\n", val);
	fread(&val, 1, sizeof(int), in);
	printf("RESP = %d\n", val);
	fread(&val, 1, sizeof(int), in);
	printf("SEQ = %d\n", val);
	fread(address, 1, 6, in);
	printf("ADDRESS = %0x %0x %0x %0x %0x %0x\n", address[0],
		address[1],
		address[2],
		address[3],
		address[4],
		address[5]);
	fread(&val, 1, sizeof(int), in);
	printf("CRC = %d\n", val);
	fread(data, 1, count, in);
	printf("DATA = %s\n", data);
	fread(&val, 1, sizeof(int), in);
	printf("CRC = %d\n", val);
	
	return 0;
}
