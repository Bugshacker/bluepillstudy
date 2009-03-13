#pragma once

#include <ntddk.h>

//+++++++++++++++++++++Definitions+++++++++++++++++++++++++++

#ifdef USE_DEBUG_LIBRUARY
#define Print(x) WriteDbgInfo x
#else
#define Print(x) {}
#endif
#define HvmPrint(x) DbgPrint x

//+++++++++++++++++++++Public Functions++++++++++++++++++++++++

/**
 * Effects: Write info with format.
 * ����ʽдString
 **/
NTSTATUS NTAPI PrintDbgInfo (PUCHAR fmt,...);

/**
 * Effects: Initialize SpinLock, must be called before invoke WriteDbgInfo function
 * ��ʼ��д��Ϣ������,�����ڵ���WriteDbgInfo����ǰ����
 **/
void NTAPI PrintInfoInit();

void NTAPI PrintInfoDispose();