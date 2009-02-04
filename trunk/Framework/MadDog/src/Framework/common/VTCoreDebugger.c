#include "VTCoreDebugger.h"
#include <stdarg.h>
#include "hvm.h"

/**
 * Effects: Write info with format.
 * ����ʽдString
 **/
NTSTATUS NTAPI PrintDbgInfo (PUCHAR fmt,...)
{
	va_list args;
	va_start (args, fmt);
	return WriteDbgInfo(fmt,(PUCHAR) fmt, args);
}

/**
 * Effects: Initialize SpinLock, must be called before invoke WriteDbgInfo function
 * ��ʼ��д��Ϣ������,�����ڵ���WriteDbgInfo����ǰ����
 **/
void NTAPI PrintInfoInit()
{
	WriteInfoInit();
}

void NTAPI PrintInfoDispose()
{
	WriteInfoDispose();
}