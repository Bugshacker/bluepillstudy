/* 
 * Copyright holder: Invisible Things Lab
 * 
 * This software is protected by domestic and International
 * copyright laws. Any use (including publishing and
 * distribution) of this software requires a valid license
 * from the copyright holder.
 *
 * This software is provided for the educational use only
 * during the Black Hat training. This software should not
 * be used on production systems.
 *
 */

#include "dbgclient.h"

static PVOID g_DbgWindow = NULL;

static DbgSendCommand (
  ULONG uIoctlNumber,//Ҫִ�е�I/O control code
  PVOID pData,//DebugWindow�ֲ������ĵ�ַ
  ULONG uDataSize//�����DebugWindow��struct�Ĵ�С
)
{
  NTSTATUS Status;
  HANDLE hDbgClient;
  IO_STATUS_BLOCK Iosb;
  UNICODE_STRING DeviceName;
  OBJECT_ATTRIBUTES ObjectAttributes;

  RtlInitUnicodeString (&DeviceName, L"\\Device\\itldbgclient");//RtlInitUnicodeString��ʼ��һ��������Unicode String,���浽DeviceName�С�L��ʾ��Unicode����
  //The InitializeObjectAttributes macro initializes the opaque OBJECT_ATTRIBUTES structure, which specifies the properties of an object handle to routines that open handles.
  //OBJ_CASE_INSENSITIVE:If this flag is specified, a case-insensitive comparison is used when matching the ObjectName parameter against the names of existing objects. Otherwise, object names are compared using the default system settings. 
  InitializeObjectAttributes (&ObjectAttributes, &DeviceName, OBJ_CASE_INSENSITIVE, NULL, NULL);

  hDbgClient = 0;//DbgClient handle
  Status = ZwOpenFile (&hDbgClient, FILE_READ_ACCESS | FILE_WRITE_ACCESS, &ObjectAttributes, &Iosb, FILE_SHARE_READ, 0);//���豸L"\\Device\\itldbgclient"
  if (!NT_SUCCESS (Status)) {
    DbgPrint ("DbgSendCommand(): ZwOpenFile() failed with status 0x%08X\n", Status);
    return Status;
  }
  //����豸����Command
  Status = NtDeviceIoControlFile (hDbgClient,
                                  NULL, NULL, NULL, &Iosb, uIoctlNumber, pData, uDataSize, pData, uDataSize);
  if (!NT_SUCCESS (Status)) {
    DbgPrint ("DbgSendCommand(): NtDeviceIoControlFile() failed with status 0x%08X\n", Status);
    ZwClose (hDbgClient);//�ر�DbgClient handle
    return Status;
  }

  ZwClose (hDbgClient);
  return STATUS_SUCCESS;
}
//ע����һ��Debug���ڣ��о���Ӧ����ͨ�����������ע��Ϊһ���豸(FILE_DEVICE_UNKNOWN���豸��"\\Device\\itldbgclient")��������豸����һ���ڴ�ռ�
//Ȼ��������ڴ�ռ�������DbgPrintString����д�ַ���
NTSTATUS NTAPI DbgRegisterWindow (
  UCHAR bBpId
)
{
  NTSTATUS Status;
  DEBUG_WINDOW DebugWindow;
  //��һ��DbgRegisterWindow��һ��DbgUnregisterWindow ��ֻ������һ��g_DbgWindowȫ�ֱ�������ֵ
  //������һ��BluePill����ִ���ڼ�ֻ�ܴ���һ��DebugWindow
  g_DbgWindow = MmAllocatePages (DEBUG_WINDOW_IN_PAGES, NULL);//ΪDbgWindow������Ҫ�Ŀռ䣬��������һ��ҳ�������ַ
  //g_DbgWindow ��Debug���ڵ��׷���ҳ�������ַ
  if (!g_DbgWindow) {//����δ�ɹ�
    _KdPrint (("DbgRegisterWindow(): Failed to allocate %d pages for the debug messages window\n",
               DEBUG_WINDOW_IN_PAGES));
    return STATUS_INSUFFICIENT_RESOURCES;
  }

  DebugWindow.bBpId = bBpId;
  DebugWindow.pWindowVA = g_DbgWindow;//ʵ���϶���ҳ��˵��hostAddress��virturalAddress�����ͬ��,����������NewBluePill�Զ���������ַȥ˵��
  DebugWindow.uWindowSize = DEBUG_WINDOW_IN_PAGES * PAGE_SIZE;

  // memory will be freed on memory manager shutdown in case of error
  return DbgSendCommand (IOCTL_REGISTER_WINDOW, &DebugWindow, sizeof (DebugWindow));
}

NTSTATUS NTAPI DbgUnregisterWindow (
)
{
  DEBUG_WINDOW DebugWindow;

  DebugWindow.pWindowVA = g_DbgWindow;
  DebugWindow.uWindowSize = DEBUG_WINDOW_IN_PAGES * PAGE_SIZE;

  return DbgSendCommand (IOCTL_UNREGISTER_WINDOW, &DebugWindow, sizeof (DebugWindow));
}
//���ӡ���ڴ�ӡһ����Ϣ(pString)
VOID NTAPI DbgPrintString (
  PUCHAR pString//Ҫ��ӡ���ַ���
)
{
  if (g_DbgWindow) {

    if (!*(PUCHAR) g_DbgWindow) {//���ԭ�������������
      RtlZeroMemory (g_DbgWindow, DEBUG_WINDOW_IN_PAGES * PAGE_SIZE);
    }

    if (strlen ((PUCHAR) g_DbgWindow + 1) + strlen (pString) >= DEBUG_WINDOW_IN_PAGES * PAGE_SIZE)
      return;

    strcat ((PUCHAR) g_DbgWindow + 1, pString);
    *(PUCHAR) g_DbgWindow = 1;//��ʶ������
  }
}
