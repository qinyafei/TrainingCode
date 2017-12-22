#pragma once

#include <string>
#include "json.h"
#include "reader.h"
#include "value.h"

#include <map>

/*
   json¿âÉÏ²ã·â×°
*/
class JsonWrapper
{
public:
	JsonWrapper();
	~JsonWrapper(void);

public:
	int Parse(const char* cfilePath);
	int ParseString(const char* strBuffer);
	//write
	int Write(const char* ckey, char* cvalue);

	int Write(const char* ckey, Json::Value& vec);
  //read
	int Read(const char* ckey, std::string& cvalue);
	int Read(const char* ckey, Json::Value& vec);

	int ReadAll(std::map<std::string, Json::Value>& vec);

public:
	std::string m_cJsonFilePath;
	Json::Value m_JsonRoot;
};
