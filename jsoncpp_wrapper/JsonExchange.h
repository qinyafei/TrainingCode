#pragma once
#include "JsonWrapper.h"
#include "JsonValue.h"

/*
  ��json�ļ�����ת�����ڴ�ṹ
	��json�ļ���jsonvalue���ݶ���
	��jsonvalue����json�ļ���ʽ
*/
class JsonExchange
{
public:
	JsonExchange(void);
	~JsonExchange(void);

public:
	//json--->jsonvalue
	int JsonFileToJsonValue(const char* filePath, JsonValue& val);
	//jsonvalue--->json
	int JsonValueToJsonFile(JsonValue& val, const char* filePath);

	//json-->string buffer
	void JsonToString(JsonValue& val, std::string& str);
	//string buffer-->json
	void StringToJson(const char* jsStr, JsonValue& val);

private:
	//recursive
	int RValueToData(Json::Value& val, JsonValue& outData);
	//recursive data to Json::Value
	int RDataToValue(JsonValue& data, Json::Value& outVal);


};
