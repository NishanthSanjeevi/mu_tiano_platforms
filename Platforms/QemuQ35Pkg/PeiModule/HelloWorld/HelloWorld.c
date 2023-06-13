/** @file HelloWorld.c

  Copyright (c) Microsoft Corporation. All rights reserved.

  Hello World PEIM Module.
**/

#include <PiPei.h>

#include <Library/DebugLib.h>
#include <Library/PeimEntryPoint.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/PeiServicesLib.h>

#define HELLO_WORLD_VARIABLE L"HelloWorld"

/**
  * PEIM Entry Point
**/

EFI_STATUS
EFIAPI
HelloWorldEntryPoint ( 
   IN          EFI_PEI_FILE_HANDLE            FileHandle,
   IN          CONST EFI_PEI_SERVICES         **PeiServices
)

{
  
  extern EFI_GUID gHelloWorldGuid;

  DEBUG ((DEBUG_INFO, "[%a] - Enter \n", __FUNCTION__));


  EFI_STATUS                         Status;
  UINT32                             *VariableData;       
  EFI_PEI_READ_ONLY_VARIABLE2_PPI    *VariablePpi; 
  UINT32                             DataSize;

  DataSize  = sizeof (UINT32);

  Status = PeiServicesLocatePpi (
           &gEfiPeiReadOnlyVariable2PpiGuid,  //Vendor Guid
           0,                                 //DataSize
           NULL,                              //Attributes
           (VOID **)&VariablePpi             //Data
           );

    if((Status == EFI_SUCCESS) && (VariablePpi != NULL)) {
        Status = VariablePpi->GetVariable (
                              VariablePpi,
                              HELLO_WORLD_VARIABLE,
                              &gHelloWorldGuid,
                              NULL,
                              &DataSize,
                              (VOID *) (UINT8 *)&VariableData
        );

        DEBUG ((DEBUG_INFO, "[%a] - Variable Status. Status=%r\n", __FUNCTION__,Status ));
        if(Status == EFI_SUCCESS) {
            DEBUG ((DEBUG_INFO, "[%a] - Variable data found, VariableData=%d\n", __FUNCTION__,VariableData));
        } else {
            DEBUG ((DEBUG_INFO, "[%a] - Variable data not found\n", __FUNCTION__));
        }
    } else {
        DEBUG ((DEBUG_INFO, "[%a] - Variable Ppi not found. Status=%r\n", __FUNCTION__,Status));
    }
    return EFI_SUCCESS;

}