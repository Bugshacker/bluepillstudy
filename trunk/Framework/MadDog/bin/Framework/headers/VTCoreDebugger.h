#pragma once

#include <ntddk.h>
#define Print(x) PrintDbgInfo x
/*************************Public Functions*****************/

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