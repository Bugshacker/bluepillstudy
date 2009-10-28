#pragma once
#include <ntddk.h>
#include "HvCore.h"

#define VMX_EXCEPTION_PAGEFAULT		( 1 << 14)
#define VMX_EXCEPTION_INT1			( 1 << 1)
#define VMX_EXCEPTION_INT3			( 1 << 3)
NTSTATUS HvmSetupVMControlBlock (
    PCPU Cpu,
    PVOID GuestEip,
    PVOID GuestEsp
);

//+++++++++++++++++++++Inner Functions++++++++++++++++++++++++

// make the ctl code legal
static ULONG32 NTAPI VmxAdjustControls (
    ULONG32 Ctl,
    ULONG32 Msr
);

/**
 * effects: �������VMCB��Guest״̬�����еĶ�ѡ��������
 */
static NTSTATUS NTAPI VmxFillGuestSelectorData (
    PVOID GdtBase,
    ULONG Segreg,//SEGREGSö���еĶ�ѡ����ţ���������ҪFill�ĸ���ѡ����
    USHORT Selector
);