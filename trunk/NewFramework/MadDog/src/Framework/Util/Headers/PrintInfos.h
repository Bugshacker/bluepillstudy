#pragma once

#include <ntddk.h>
#include "snprintf.h"

#define NUM_DEBUG_PAGES 20

extern PVOID g_debugWindowAddrVA;
typedef ULONG PRINTSPIN_LOCK, *PPRINTSPIN_LOCK;
#define DEBUG_WINDOW_TAG 'DBG'
/*************************Public Functions*****************/

/**
 * Effects: Write info with format.
 * ����ʽдString
 **/
NTSTATUS NTAPI WriteDbgInfo (PUCHAR fmt,...);

/**
 * Effects: Initialize SpinLock, must be called before invoke WriteDbgInfo function
 * ��ʼ��д��Ϣ������,�����ڵ���WriteDbgInfo����ǰ����
 **/
void NTAPI WriteInfoInit();

void NTAPI WriteInfoDispose();

/**************Private Functions**************/

static NTSTATUS _CreateDebugWindow(ULONG32 numContinuousPages);

static VOID _AppendStringToAddress(PUCHAR str,ULONG32 strLength);

/**
 * Effects: Append the string <str> into the end of the debug window
 * If the debug window not exists, then it will be created at first.
 * ��<str>��д�����Դ���ĩβ��������Դ��ڲ����ڣ��򴴽����Դ���
 **/
static NTSTATUS NTAPI _WriteInfo(PUCHAR str,ULONG32 strLength);