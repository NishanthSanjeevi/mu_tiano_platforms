/** @file ConsoleMsgDxe.c

    Copyright (c) Microsoft Corporation. All rights reserved.

    Console Msg DXE Driver.
**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>

/**
   Dxe Entry Point
**/

EFI_STATUS
EFIAPI
ConsoleMsgEntryPoint (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)


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
  //DbgMessage[0x30] = 0x00;
  DEBUG((DEBUG_INFO, "[%a] - Console Debug message : %r\n",__FUNCTION__))
  //return DbgMessage;
}

//{
  //  DEBUG ((DEBUG_ERROR, "[%a] - Console Debug message : %r\n",__FUNCTION__));
    //return EFI_SUCCESS;
//}