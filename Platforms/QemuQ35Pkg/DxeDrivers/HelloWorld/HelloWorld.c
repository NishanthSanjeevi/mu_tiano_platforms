/** @file HelloWorld.c

  Copyright (c) Microsoft Corporation. All rights reserved.

  Hello World DXE Driver.
**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#define HELLO_WORLD_VARIABLE L"HelloWorld"

/**
 * Dxe Entry Point
**/

EFI_STATUS
EFIAPI
HelloWorldEntryPoint (
    IN EFI_HANDLE             ImageHandle,
    IN EFI_SYSTEM_TABLE       *SystemTable          
    )
{
    EFI_STATUS                Status;
    UINTN                     DataSize;
    UINT32                    VariableData;
    UINT32                    Attributes;    

    Attributes = 7;
    DataSize   = sizeof (UINT32);

    Status = gRT->GetVariable (
                   HELLO_WORLD_VARIABLE,
                   &gHelloWorldGuid,
                   NULL,
                   &DataSize,
                   (VOID *)(UINT8 *)&VariableData
                   );
    
    if(Status == EFI_SUCCESS) {
        VariableData = VariableData + 1;
        DEBUG ((DEBUG_INFO, "[%a] - Variable data found. Value=%d\n",__FUNCTION__,VariableData));
    } else {
        VariableData = 0;
        DEBUG ((DEBUG_INFO, "[%a] - Variable data not found. Initialise to zero. Erro=%r\n",__FUNCTION__,Status));
    }

    Status = gRT->SetVariable (
                   HELLO_WORLD_VARIABLE,
                   &gHelloWorldGuid,
                   Attributes,
                   DataSize,
                   (VOID *)(UINT8 *)&VariableData
                   );
    
    if(EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "[%a] - Failed to create HELLO_WORLD_VARIABLE : %r\n",__FUNCTION__, Status));
        return EFI_SUCCESS;
    }
    
    return Status;
}