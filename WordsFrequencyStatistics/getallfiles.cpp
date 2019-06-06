/*
the funtion to get the name of all the files and subfiles under the homepath
*/

#include"functions.h"
#include<io.h>
#include<iostream>
using namespace std;
void getallfiles(string homepath, vector<string>& files)
{
	//file handle
	long hFile = 0;
	//file info
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = (long)_findfirst(p.assign(homepath).append("\\*").c_str(), &fileinfo)) != -1)
	{
		//find all the file under the homepath, and assert this is not empty
		do
		{
			//if it is a dirctory, iterate
			//if it is a file, push to the files(list)
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getallfiles(p.assign(homepath).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(homepath).append("\\").append(fileinfo.name));
			}
		} while(_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

}
