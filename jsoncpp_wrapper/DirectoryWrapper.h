#pragma once
/*
  ÎÄ¼þ¼Ð²Ù×÷
*/

#include <string>

#include <direct.h>
#include <io.h>
#include <windows.h>



class DirectoryWrapper
{
public:
	DirectoryWrapper(void);
	~DirectoryWrapper(void);

public:
	//create folder
	bool create(const char* spath);
	//folder exist
	bool exist(const char* spath);
	//remove folder
	bool deletefolder(const char* spath);
	//get file extend
	void getfileextend(const char* spath, std::string& extend);
	//get current app path
	void getapppath(std::string& path);
	//get file absolute path
	void getfilefolder(const char* spath, std::string& folder);
	//get file name
	void getfilename(const char* spath, std::string& filename);

	void openfolder();
	
};
