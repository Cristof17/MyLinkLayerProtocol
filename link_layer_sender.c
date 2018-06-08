#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct address{
	char first;
	char second;
	char third;
	char forth;
	char fifth;
	char sixth;
} ADDRESS;

int main(int argc, char **argv){

	if (argc < 2){
		printf("%s <filename>\n", argv[0]);
		return -1;
	}
	FILE *in = fopen(argv[1], "w+");
	if (in == NULL){
		perror("");
		return -1;
	}

	ADDRESS address = {0x0A, 0x0B, 0x0C, 0x0D, 0xE, 0x0F};
	char *data = "Welcome from the planet of freshly made protocols";
	int count = strlen(data); //10 chars am in date
	int val = 0;
	int crc = 20; //random
	char syn = 22; //SYN
	char soh = 1; //SOH
	
	fwrite(&syn, 1, 1, in); //SYN
	fwrite(&syn, 1, 1, in); //SYN
	fwrite(&soh, 1, 1, in); //SOH
	fwrite(&count, 1, sizeof(int), in); //COUNT
	val = 0;
	fwrite(&val, 1, sizeof(int), in); //FLAG
	fwrite(&val, 1, sizeof(int), in); //RESP
	fwrite(&val, 1, sizeof(int), in); //SEQ
	fwrite(&address, 1, sizeof(ADDRESS), in); //ADDRESS
	fwrite(&crc, 1, sizeof(int), in); //CRC
	fwrite(data, 1, strlen(data), in); //DATA
	fwrite(&crc, 1, sizeof(int), in); //CRC
	return 0;
}
