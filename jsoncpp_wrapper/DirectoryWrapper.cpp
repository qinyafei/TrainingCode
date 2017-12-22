#include "stdafx.h"
#include "DirectoryWrapper.h"



DirectoryWrapper::DirectoryWrapper(void)
{
}

DirectoryWrapper::~DirectoryWrapper(void)
{
}


bool DirectoryWrapper::create(const char* spath)
{
	if (spath == NULL)
	{
		return false;
	}

	_mkdir(spath);

	return true;
}


bool DirectoryWrapper::exist(const char* spath)
{
	if (spath == NULL || _access(spath, 0) == -1)
	{
		return false;
	}

	return true;
}


bool DirectoryWrapper::deletefolder(const char* spath)
{
	if (spath == NULL)
	{
		return false;
	}

	_rmdir(spath);

	return true;
}


void DirectoryWrapper::getfileextend(const char* spath, std::string& extend)
{
	std::string filepath = spath;
	int pos = filepath.find_last_of(".");
	if (pos > 0)
	{
		extend = filepath.substr(pos + 1, filepath.length());
	}

}


void DirectoryWrapper::getapppath(std::string& path)
{
	char buf[256] = {0};
	int dw = ::GetModuleFileName(NULL, buf, MAX_PATH);
	if(dw != 0)
	{
		std::string temp = buf;
		int pos = temp.find_last_of("\\");

		path = temp.substr(0, pos + 1);
	}

}


void DirectoryWrapper::getfilefolder(const char* spath, std::string& folder)
{
	std::string filepath = spath;
	int pos = filepath.find_last_of("\\");
	if (pos > 0)
	{
		folder = filepath.substr(0, pos + 1);
	}

}


//get file name
void DirectoryWrapper::getfilename(const char* spath, std::string& filename)
{
	std::string filepath = spath;
	int pos = filepath.find_last_of("\\");
	if (pos > 0)
	{
		filename = filepath.substr(pos + 1, filepath.length() - pos);
	}

}


void DirectoryWrapper::openfolder()
{

}
