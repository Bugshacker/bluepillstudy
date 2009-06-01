#include "HvCoreDebugger.h"
#include <stdarg.h>
#include "hvm.h"

/**
 * Effects: Write info with format.
 * ����ʽдString
 **/
NTSTATUS NTAPI DbgPrintInfo (PUCHAR fmt,...)
{
	va_list args;
	va_start (args, fmt);
	return WriteDbgInfo(fmt,(PUCHAR) fmt, args);
}

/**
 * Effects: Initialize SpinLock, must be called before invoke WriteDbgInfo function
 * ��ʼ��д��Ϣ������,�����ڵ���WriteDbgInfo����ǰ����
 **/
void NTAPI DbgInitComponent()
{
	WriteInfoInit();
}

void NTAPI DbgDisposeComponent()
{
	WriteInfoDispose();
}