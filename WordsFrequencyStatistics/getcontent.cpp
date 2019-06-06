/*
the function transfer the content of a file to RAM at one time, and generate a head pointer buffer
*/

#include"functions.h"
void getcontent(string path, char *& buffer, long &size)
{
	FILE* fp;
	size_t result;
	errno_t err;
	buffer = NULL;
	//to open the file in the path
	err = fopen_s(&fp, path.c_str(), "rb");
	if (err != 0) {
		fputs("file open error", stderr);
		exit(1);
	}
	//to get the file size
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	//to get the same size space in the RAM
	buffer = (char*)malloc(sizeof(char)*size);
	if (buffer == NULL)
	{
		fputs("memory error", stderr);
		exit(2);
	}
	//to copy the file
	result = fread(buffer, 1, size, fp);
	if (result != size)
	{
		fputs("reading error", stderr);
		exit(3);
	}
	fclose(fp);

}
