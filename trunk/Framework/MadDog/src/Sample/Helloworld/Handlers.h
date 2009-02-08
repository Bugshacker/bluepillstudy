#pragma once
#include <ntddk.h>
#include "VTCore.h"
#include "VTUtilAPIs.h"
#include "Vmx/Vmcs.h"
#include "Vmx/Vmx.h"

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