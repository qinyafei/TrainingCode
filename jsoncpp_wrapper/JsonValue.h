#pragma once
#include <vector>
#include <map>
#include <string>

#include "JsException.h"


enum JsType
{
	js_invalid,
	js_string,
	js_array,
	js_dictionary,

};


class JsonValue
{
public:
	JsonValue(void);
	~JsonValue(void);

	//
	typedef std::vector<JsonValue> ArrayValue;
	typedef std::map<std::string, JsonValue> DictionaryValue;
	typedef std::vector<std::string> MemberName;


public:
	JsonValue(JsonValue const& val): _type(js_invalid){*this = val; }
	JsonValue(const std::string& val): _type(js_string)
	{
		_Value.jsString = new std::string(val);
	}

	JsonValue& operator=(const JsonValue& val);
	JsonValue& operator=(const char* val);
	
	//valid while array or dictionary
	JsonValue& operator[](int index);
	JsonValue& operator[](std::string& key);
	JsonValue& operator[](const char* key)
	{
		std::string ck(key);
		return operator[](ck);
	}

	//clean
	void Clean();
	//size
	int Size();
	//type
	JsType Type() { return _type; }
	//if Dictionary then get membername first
	int GetMemberNames(MemberName& member);
	//as string
	std::string AsString();

	//erase
	void Erase(int i);
	void Erase(const std::string& name);
private:
	JsType _type;

	union
	{
		std::string* jsString;
		ArrayValue* jsArray;
		DictionaryValue* jsDic;
	}_Value;
};
