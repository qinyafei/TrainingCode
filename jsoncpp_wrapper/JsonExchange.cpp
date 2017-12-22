#include "stdafx.h"
#include "JsonExchange.h"
#include <map>
#include <fstream>

JsonExchange::JsonExchange(void)
{
}

JsonExchange::~JsonExchange(void)
{
}

//json--->jsonvalue
int JsonExchange::JsonFileToJsonValue(const char* filePath, JsonValue& val)
{
	if (filePath == NULL)
	{
		return -1;
	}

	JsonWrapper jsparser;
	if (jsparser.Parse(filePath) != 0)
	{
		return -1;
	}

	std::map<std::string, Json::Value> vec;
	jsparser.ReadAll(vec);
	typedef std::map<std::string, Json::Value>::iterator mapIter;
	for (mapIter it = vec.begin(); it != vec.end(); it++)
	{
		if (it->second.type() == Json::stringValue)
		{
			val[(std::string)(it->first)] = it->second.asString();
		}
		else
		{
			RValueToData(it->second, val[(std::string)it->first]);
		}
	}
	
	return 0;

}


//recursive
int JsonExchange::RValueToData(Json::Value& val, JsonValue& outData)
{
	int size = 0;
	switch (val.type())
	{
	case Json::stringValue:
		{
			outData = val.asString().c_str();
		}
		break;
	case Json::objectValue:
		{
			Json::Value::Members memNames;
			memNames = val.getMemberNames();
			size = memNames.size();
			for (int i = 0; i <size; i++)
			{
				//string 
				if (val[memNames[i]].type() == Json::stringValue)
				{
					outData[memNames[i]] = val[memNames[i]].asString();
				}
				else //arrary or obj must recursive
				{
					JsonValue data;
					if (RValueToData(val[memNames[i]], data) == 0)
						outData[memNames[i]] = data;
				}
			}
		}
		break;
	case Json::arrayValue:
		{
			unsigned int len = val.size();
			for (unsigned int i = 0; i < len; i++)
			{
				if (val[i].type() == Json::stringValue)
				{
					outData[i] = val[i].asString();
				}
				else
				{
					JsonValue data;
					if (RValueToData(val[i], data) == 0)
						outData[i] = data;
				}
			}
		}
		break;
	default:
		break;
	}

	return 0;
}

//recursive data to Json::Value
int JsonExchange::RDataToValue(JsonValue& data, Json::Value& outVal)
{
	switch (data.Type())
	{
	case js_string:
		{
			outVal = Json::Value(data.AsString());
		}
		break;
	case js_array:
		{
			int size = data.Size();
			for (int i = 0; i < size; i++)
			{
				if (data[i].Type() == js_string)
				{
					outVal[i] = Json::Value(data[i].AsString());
				}
				else
				{
					Json::Value val;
					if (RDataToValue(data[i], val) == 0)
						outVal[i] = val;

				}
			}
		}
		break;
	case js_dictionary:
		{
			JsonValue::MemberName mems;
			data.GetMemberNames(mems);
			for (int i = 0; i < mems.size(); i++)
			{
				if (data[mems[i]].Type() == js_string)
				{
					outVal[mems[i]] = data[mems[i]].AsString();
				}
				else
				{
					Json::Value val;
					if (RDataToValue(data[mems[i]], val) == 0)
						outVal[mems[i]] = val;
				}
			}
		}
		break;
	default:
		break;
	}

	return 0;
}


//jsonvalue--->json
int JsonExchange::JsonValueToJsonFile(JsonValue& val, const char* filePath)
{
	Json::Value outVal;
	int ret = RDataToValue(val, outVal);

	Json::StyledWriter writer;
	std::string jsonfile = writer.write(outVal);

	setlocale(LC_ALL, "chs");
	std::ofstream ofs;
	ofs.open(filePath);
	if (ofs.is_open())
	{
		ofs<<jsonfile;
	}
	setlocale(LC_ALL, "C");

	return 0;
}


//json-->string buffer
void JsonExchange::JsonToString(JsonValue& val, std::string& str)
{
	Json::Value outVal;
	int ret = RDataToValue(val, outVal);

	Json::StyledWriter writer;
	str = writer.write(outVal);

}


//string buffer-->json
void JsonExchange::StringToJson(const char* jsStr, JsonValue& val)
{
	JsonWrapper jswrap;
	if (jswrap.ParseString(jsStr) != 0)
	{
		return ;
	}

	std::map<std::string, Json::Value> vec;
	jswrap.ReadAll(vec);
	typedef std::map<std::string, Json::Value>::iterator mapIter;
	for (mapIter it = vec.begin(); it != vec.end(); it++)
	{
		if (it->second.type() == Json::stringValue)
		{
			val[(std::string)(it->first)] = it->second.asString();
		}
		else
		{
			RValueToData(it->second, val[(std::string)it->first]);
		}
	}

}