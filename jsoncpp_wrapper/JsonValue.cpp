#include "stdafx.h"
#include "JsonValue.h"

#define DEFAULT_ARRAY_SIZE 2

JsonValue::JsonValue(void)
{
	_type = js_invalid;
}

JsonValue::~JsonValue(void)
{
	Clean();
}

JsonValue& JsonValue::operator=(const JsonValue& val)
{
	if (this == &val)
	{
		return *this;
	}

	//clean
	Clean();

	switch(val._type)
	{
	case js_string:
		{
			this->_Value.jsString = new std::string(*val._Value.jsString);
		}
		break;
	case js_array:
		{
			this->_Value.jsArray = new ArrayValue(*val._Value.jsArray);
		}
		break;
	case js_dictionary:
		{
			this->_Value.jsDic = new DictionaryValue(*val._Value.jsDic);
		}
		break;
	case js_invalid:
		break;
	}

	this->_type = val._type;
	return *this;

}

JsonValue& JsonValue::operator=(const char* val)
{
	return operator=(JsonValue(std::string(val)));
}

//
JsonValue& JsonValue::operator[](int index)
{
	if (_type == js_invalid)
	{
		_type = js_array;
		_Value.jsArray = new ArrayValue();
	}
	
	if (_type == js_array)
	{
		if (index >= _Value.jsArray->size())
			_Value.jsArray->resize(index+1);
	}
	else
	{
		throw JsException("type error : expected an array");
	}

	_Value.jsArray->at(index);

}


JsonValue& JsonValue::operator[](std::string& key)
{
	if (_type == js_invalid)
	{
		_type = js_dictionary;
		_Value.jsDic = new DictionaryValue();
	}
	else if (_type != js_dictionary)
	{
		throw JsException("type error : expected an dictionary");
	}

	return (*_Value.jsDic)[key];
}

//clean
void JsonValue::Clean()
{
	switch(_type)
	{
	case js_string:
		{
			delete _Value.jsString;
			_Value.jsString = NULL;
		}
		break;
	case js_array:
		{
			delete _Value.jsArray;
			_Value.jsArray = NULL;
		}
		break;
	case js_dictionary:
		{
			delete _Value.jsDic;
			_Value.jsDic = NULL;
		}
		break;
	case js_invalid:
		break;
	}
	_type = js_invalid;
}


int JsonValue::Size()
{
	switch (_type)
	{
	case js_string:
		return _Value.jsString->size();
		break;
	case js_array:
		return _Value.jsArray->size();
		break;
	case js_dictionary:
		return _Value.jsDic->size();
		break;
	}

	throw JsException("can't get size of js_invalid");
}

void JsonValue::Erase(int i)
{
	if (_type == js_array)
	{
		_Value.jsArray->erase(_Value.jsArray->begin() + i);
	}
}

void JsonValue::Erase(const std::string& name)
{
	if (_type == js_dictionary)
	{
		if (_Value.jsDic->find(name) != _Value.jsDic->end())
		{
			_Value.jsDic->erase(name);
		}
	}
}


int JsonValue::GetMemberNames(MemberName& member)
{
	if (_type != js_dictionary)
	{
		return -1;
	}

	DictionaryValue::iterator it;
	int len = 0;
	for (it = _Value.jsDic->begin(); it != _Value.jsDic->end(); it++)
	{
		member.push_back(it->first);
		len++;
	}

	return len;
}

std::string JsonValue::AsString()
{
	if (_type != js_string)
	{
		 return "";
	}

	return *(_Value.jsString);
}