/** @file ConsoleMsgDxe.c

    Copyright (c) Microsoft Corporation. All rights reserved.

    Console Msg DXE Driver.
**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MsPlatformDebugMessage.h>

#define CPUID_BRAND_STRING1  0x80000002
#define CPUID_BRAND_STRING2  0x80000003
#define CPUID_BRAND_STRING3  0x80000004
#define MAX_MESSAGE_LENGTH  64
STATIC CHAR8  DbgMessage[MAX_MESSAGE_LENGTH];

/**
   Dxe Entry Point
**/

//EFI_STATUS
//EFIAPI
//ConsoleMsgEntryPoint (
  //  IN EFI_HANDLE           ImageHandle,
    //IN EFI_SYSTEM_TABLE     *SystemTable
//)


CHAR8 *
EFIAPI
GetCpuBrand (
  VOID
  )
{
  // Needed length check, 3 CPUID calls with 4 DWORDs of chars and a NULL termination
  if (MAX_MESSAGE_LENGTH < ((3 * 4 * 4) + 1)) {
    ASSERT (FALSE);
    return NULL;
  }

  // Update CPUID data (ASCII chars) directly into mMessage buffer
  AsmCpuid (CPUID_BRAND_STRING1, (UINT32 *)&(DbgMessage[0x00]), (UINT32 *)&(DbgMessage[0x04]), (UINT32 *)&(DbgMessage[0x08]), (UINT32 *)&(DbgMessage[0x0C]));
  AsmCpuid (CPUID_BRAND_STRING2, (UINT32 *)&(DbgMessage[0x10]), (UINT32 *)&(DbgMessage[0x14]), (UINT32 *)&(DbgMessage[0x18]), (UINT32 *)&(DbgMessage[0x1C]));
  AsmCpuid (CPUID_BRAND_STRING3, (UINT32 *)&(DbgMessage[0x20]), (UINT32 *)&(DbgMessage[0x24]), (UINT32 *)&(DbgMessage[0x28]), (UINT32 *)&(DbgMessage[0x2C]));

  // Make sure mMessage is terminated and return
  DbgMessage[0x30] = 0x00;
  //DEBUG((DEBUG_INFO, "[%a] - Console Debug message : %r\n",__FUNCTION__))
  return DbgMessage;

}


VOID
EFIAPI
DisplayPlatformSpecificFwMessages (
  IN OUT UINT32  *Row
  )
{
  EFI_STATUS  Status;
  DEBUG((DEBUG_INFO,"[%a] - CPU Branding:  %d\n",Status,GetCpuBrand ()));
  //Print (L"\n");
}

