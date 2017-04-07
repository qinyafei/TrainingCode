#include "stdafx.h"
#include "UnhandleException.h"
#include <dbghelp.h>
#include <string>
#pragma comment(lib, "dbghelp.lib")

void InstallUnhandleExceptionFilter()
{
	SetUnhandledExceptionFilter(LogUnhandleExceptionFilter); 
}
long __stdcall LogUnhandleExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo)
{	
	time_t  nowtime;
	time(&nowtime);
	tm pTime[1];
	localtime_s(pTime, &nowtime);
	TCHAR pszTime[128] = {0};
	_sntprintf_s(pszTime, 128, 127, _T("GIS.MAP-%4d.%02d.%02d_%02d.%02d.%02d"), pTime->tm_year+1900, pTime->tm_mon+1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
	TCHAR pszDmp[_MAX_PATH];
	TCHAR pszExe[_MAX_PATH];
	GetModuleFileName(NULL, pszExe, _MAX_PATH);
	TCHAR pszDrive[_MAX_DRIVE];
	TCHAR pszDir[_MAX_DIR];
	TCHAR pszFname[_MAX_FNAME];
	_tsplitpath_s(pszExe, pszDrive, _MAX_DRIVE, pszDir, _MAX_DIR, pszFname, _MAX_FNAME, NULL, 0);

	_tmakepath_s(pszDmp, _MAX_PATH, pszDrive, pszDir, pszTime, _T("dmp"));

	char pszLogInfo[_MAX_PATH] = {0};
#ifdef UNICODE
	char psza[_MAX_PATH] = {0};
	WideCharToMultiByte (CP_OEMCP,NULL,pszDmp,-1,psza,_MAX_PATH,NULL,FALSE);
	_snprintf_s(pszLogInfo, _MAX_PATH, _TRUNCATE, "wirte dump file: %s", psza);
#else
	_snprintf_s(pszLogInfo, _MAX_PATH, _TRUNCATE, "wirte dump file: %s", pszDmp);
#endif
	HANDLE hFile = ::CreateFile(pszDmp, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION ExInfo;

		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = ExceptionInfo;
		ExInfo.ClientPointers = NULL;

		// write the dump
		BOOL bOK = MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL );
		char temp[30] = {0};
		_snprintf_s(temp, 30, 29, "dumped is %d", bOK);
		::CloseHandle(hFile);
	}
	else
	{

	}
	//return EXCEPTION_CONTINUE_EXECUTION;
	return EXCEPTION_EXECUTE_HANDLER; 
}

