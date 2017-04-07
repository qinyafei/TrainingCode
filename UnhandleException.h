#pragma once

long WINAPI LogUnhandleExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo);

void InstallUnhandleExceptionFilter();