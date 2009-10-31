#pragma once

#include <ntddk.h>
#include "snprintf.h"

#define NUM_DEBUG_PAGES 200

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