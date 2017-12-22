#ifndef _JSEXCEPTION_H
#define _JSEXCEPTION_H
#include <string>

/*
  exception class for json value
*/
class JsException
{
public:

	JsException(const char* sError, int nCode = -1):
	m_ErrorStr(sError), m_nErrorCode(nCode){}

public:
	const char* getMessage() { return m_ErrorStr.c_str(); }
	int   getCode() { return m_nErrorCode; }
private:
	//error string
	std::string m_ErrorStr;
  //error code
	int m_nErrorCode;
};

#endif