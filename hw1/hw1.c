#include <stdio.h>

int main(int argc, char *argv[]) 
{
	char ch;
	FILE *ipf, *opf;

	ipf = fopen(argv[1], "r");
	opf = fopen(argv[2], "w");	
	
	while((ch = fgetc(ipf)) != EOF)
	{	
		fputc(ch, opf);
	}
	/*
	copy the character from the input file
	store the character in the ch variable
	put the character into the output file
	repeat the process until end of the file
	*/

	fclose(ipf);
	fclose(opf);

	return 0;
}
