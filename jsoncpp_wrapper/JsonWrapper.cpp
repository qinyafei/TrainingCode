#include "stdafx.h"
#include "JsonWrapper.h"

#include <fstream>
#include <istream>
#include <sstream>

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\libJson.lib")
#else
#pragma comment(lib, "..\\Release\\libJson.lib")
#endif

using namespace std;

JsonWrapper::JsonWrapper()
{
	
}

JsonWrapper::~JsonWrapper(void)
{
}


int JsonWrapper::Parse(const char* cfilePath)
{
	if (cfilePath == NULL || strlen(cfilePath) == 0)
	{
		return -1;
	}

	m_cJsonFilePath = cfilePath;

	m_JsonRoot.clear();  // will contains the root value after parsing.
	Json::Reader reader;

	ifstream jsonfile;
	jsonfile.open(m_cJsonFilePath.c_str());
	bool parsingSuccessful = reader.parse( jsonfile, m_JsonRoot);
	if ( !parsingSuccessful )
	{
		return -1;
	}

  return 0;
}


int JsonWrapper::ParseString(const char* strBuffer)
{
	if (strBuffer == NULL || strlen(strBuffer) <= 0)
	{
		return -1;
	}

	std::stringstream strs;
	//sbuf.pubsetbuf(strBuffer, strlen(strBuffer));
	strs.str(std::string(strBuffer));
	//std::istream ifile(strs);
	Json::Reader fileread;
	if (!fileread.parse(strs, m_JsonRoot))
	{
		return -1;
	}

	return 0;
}


//write
int JsonWrapper::Write(const char* ckey, char* cvalue)
{
	if (m_cJsonFilePath.length() <= 0)
	{
		return -1;
	}

	
	Json::StyledWriter writer;
	Json::Value key;
	
	key[ckey] = cvalue;
  m_JsonRoot.append(key);
	std::string jsonfile = writer.write(m_JsonRoot);

	setlocale(LC_ALL, "chs");
	ofstream ofs;
	ofs.open(m_cJsonFilePath.c_str());
	if (ofs.is_open())
	{
		ofs<<jsonfile;
	}
	setlocale(LC_ALL, "C");

	return 0;
}


//read
int JsonWrapper::Read(const char* key, std::string& cvalue)
{
	if (key == NULL)
	{
		return -1;
	}

	Json::Value::iterator it;
	bool bret = false;
	for (it = m_JsonRoot.begin(); it != m_JsonRoot.end(); it++)
	{
		if ((*it).isMember(key) && (*it).type() == Json::stringValue)
		{
			cvalue = (*it).get(key, "").asString();
			break;
		}
	}


	return 0;
}


int JsonWrapper::Write(const char* ckey, Json::Value& vec)
{
	if (ckey == NULL)
	{
		return -1;
	}

	Json::StyledWriter writer;
	Json::Value key;

	key[ckey] = vec;
	m_JsonRoot.append(key);
	std::string jsonfile = writer.write(m_JsonRoot);

	ofstream ofs;
	ofs.open(m_cJsonFilePath.c_str());
	if (ofs.is_open())
	{
		ofs<<jsonfile;
	}
	
  return 0;

}


int JsonWrapper::Read(const char* ckey, Json::Value& vec)
{
	if (ckey == NULL)
	{
		return -1;
	}

	int size = m_JsonRoot.size();
	Json::Value vtemp;
	Json::Value v(Json::arrayValue);
	for (int i = 0; i < size; i++)
	{
		vtemp = m_JsonRoot[i];
		if (vtemp.isMember(ckey))
		{
			vec = vtemp.get(ckey, v);
			break;
		}	
	}

/*
	Json::Value v(Json::arrayValue);
  v = m_JsonRoot.get(ckey, v);
	//vec = m_JsonRoot[ckey];*/


	return 0;
}


int JsonWrapper::ReadAll(std::map<std::string, Json::Value>& vec)
{

	int size = m_JsonRoot.size();

	Json::Value::Members memNames;
	memNames = m_JsonRoot.getMemberNames();
	for (int i = 0; i < size; i++)
	{
		vec[memNames[i]] = m_JsonRoot[memNames[i]];
	}


	return 0;
}