/** @file
  Pei Core Load Image Support

Copyright (c) 2006 - 2010, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "PeiMain.h"


EFI_PEI_LOAD_FILE_PPI   mPeiLoadImagePpi = {
  PeiLoadImageLoadImageWrapper
};


EFI_PEI_PPI_DESCRIPTOR     gPpiLoadFilePpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiLoadFilePpiGuid,
  &mPeiLoadImagePpi
};

/**

  Support routine for the PE/COFF Loader that reads a buffer from a PE/COFF file.
  The function is used for XIP code to have optimized memory copy.

  @param FileHandle      - The handle to the PE/COFF file
  @param FileOffset      - The offset, in bytes, into the file to read
  @param ReadSize        - The number of bytes to read from the file starting at FileOffset
  @param Buffer          - A pointer to the buffer to read the data into.

  @return EFI_SUCCESS - ReadSize bytes of data were read into Buffer from the PE/COFF file starting at FileOffset

**/
EFI_STATUS
EFIAPI
PeiImageRead (
  IN     VOID    *FileHandle,
  IN     UINTN   FileOffset,
  IN     UINTN   *ReadSize,
  OUT    VOID    *Buffer
  )
{
  CHAR8 *Destination8;
  CHAR8 *Source8;
  
  Destination8  = Buffer;
  Source8       = (CHAR8 *) ((UINTN) FileHandle + FileOffset);
  if (Destination8 != Source8) {
    CopyMem (Destination8, Source8, *ReadSize);
  }

  return EFI_SUCCESS;
}

/**

  Support routine for the PE/COFF Loader that reads a buffer from a PE/COFF file.
  The function is implemented as PIC so as to support shadowing.

  @param FileHandle      - The handle to the PE/COFF file
  @param FileOffset      - The offset, in bytes, into the file to read
  @param ReadSize        - The number of bytes to read from the file starting at FileOffset
  @param Buffer          - A pointer to the buffer to read the data into.

  @return EFI_SUCCESS - ReadSize bytes of data were read into Buffer from the PE/COFF file starting at FileOffset

**/
EFI_STATUS
EFIAPI
PeiImageReadForShadow (
  IN     VOID    *FileHandle,
  IN     UINTN   FileOffset,
  IN     UINTN   *ReadSize,
  OUT    VOID    *Buffer
  )
{
  volatile CHAR8  *Destination8;
  CHAR8           *Source8;
  UINTN           Length;

  Destination8  = Buffer;
  Source8       = (CHAR8 *) ((UINTN) FileHandle + FileOffset);
  if (Destination8 != Source8) {
    Length        = *ReadSize;
    while ((Length--) > 0) {
      *(Destination8++) = *(Source8++);
    }
  }

  return EFI_SUCCESS;
}

/**

  Support routine to get the Image read file function.

  @param ImageContext    - The context of the image being loaded

  @retval EFI_SUCCESS - If Image function location is found

**/
EFI_STATUS
GetImageReadFunction (
  IN      PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext
  )
{
  PEI_CORE_INSTANCE  *Private;
  VOID*  MemoryBuffer;

  Private = PEI_CORE_INSTANCE_FROM_PS_THIS (GetPeiServicesTablePointer ());
  
  if ((Private->PeiMemoryInstalled  && !(Private->HobList.HandoffInformationTable->BootMode == BOOT_ON_S3_RESUME))  &&
      (EFI_IMAGE_MACHINE_TYPE_SUPPORTED(EFI_IMAGE_MACHINE_X64) || EFI_IMAGE_MACHINE_TYPE_SUPPORTED(EFI_IMAGE_MACHINE_IA32))) {
    // 
    // Shadow algorithm makes lots of non ANSI C assumptions and only works for IA32 and X64 
    //  compilers that have been tested
    //
    if (Private->ShadowedImageRead == NULL) {
      MemoryBuffer = AllocatePages (0x400 / EFI_PAGE_SIZE + 1);
      ASSERT (MemoryBuffer != NULL);
      CopyMem (MemoryBuffer, (CONST VOID *) (UINTN) PeiImageReadForShadow, 0x400);
      Private->ShadowedImageRead = (PE_COFF_LOADER_READ_FILE) (UINTN) MemoryBuffer;
    }

    ImageContext->ImageRead = Private->ShadowedImageRead;
  } else {
    ImageContext->ImageRead = PeiImageRead;
  }

  return EFI_SUCCESS;
}
/**
  To check memory usage bit map arry to figure out if the memory range the image will be loaded in is available or not. If 
  memory range is avaliable, the function will mark the correponding bits to 1 which indicates the memory range is used.
  The function is only invoked when load modules at fixed address feature is enabled. 
  
  @param  Private                  Pointer to the private data passed in from caller
  @param  ImageBase                The base addres the image will be loaded at.
  @param  ImageSize                The size of the image
  
  @retval EFI_SUCCESS              The memory range the image will be loaded in is available
  @retval EFI_NOT_FOUND            The memory range the image will be loaded in is not available
**/
EFI_STATUS
CheckAndMarkFixLoadingMemoryUsageBitMap (
  IN  PEI_CORE_INSTANCE             *Private,
  IN  EFI_PHYSICAL_ADDRESS          ImageBase,
  IN  UINT32                        ImageSize
  )
{
   UINT32                             DxeCodePageNumber;
   UINT64                             ReservedCodeSize;
   EFI_PHYSICAL_ADDRESS               PeiCodeBase;
   UINT32                             BaseOffsetPageNumber;
   UINT32                             TopOffsetPageNumber;
   UINT32                             Index;
   UINT64                             *MemoryUsageBitMap;
   

   //
   // The reserved code range includes RuntimeCodePage range, Boot time code range and PEI code range.
   //
   DxeCodePageNumber = PcdGet32(PcdLoadFixAddressBootTimeCodePageNumber);
   DxeCodePageNumber += PcdGet32(PcdLoadFixAddressRuntimeCodePageNumber);
   ReservedCodeSize  = EFI_PAGES_TO_SIZE(DxeCodePageNumber + PcdGet32(PcdLoadFixAddressPeiCodePageNumber));
   PeiCodeBase       = Private->LoadModuleAtFixAddressTopAddress - ReservedCodeSize;
   
   //
   // Test the memory range for loading the image in the PEI code range.
   //
   if ((Private->LoadModuleAtFixAddressTopAddress - EFI_PAGES_TO_SIZE(DxeCodePageNumber)) < (ImageBase + ImageSize) ||
       (PeiCodeBase > ImageBase)) {         
     return EFI_NOT_FOUND; 
   }
   
   //
   // Test if the memory is avalaible or not.
   //
   MemoryUsageBitMap    = Private->PeiCodeMemoryRangeUsageBitMap;  
   BaseOffsetPageNumber = EFI_SIZE_TO_PAGES((UINT32)(ImageBase - PeiCodeBase));
   TopOffsetPageNumber  = EFI_SIZE_TO_PAGES((UINT32)(ImageBase + ImageSize - PeiCodeBase));
   for (Index = BaseOffsetPageNumber; Index < TopOffsetPageNumber; Index ++) {
     if ((MemoryUsageBitMap[Index / 64] & LShiftU64(1, (Index % 64))) != 0) {
       //
       // This page is already used.
       //
       return EFI_NOT_FOUND;  
     }
   }
   
   //
   // Being here means the memory range is available.  So mark the bits for the memory range
   // 
   for (Index = BaseOffsetPageNumber; Index < TopOffsetPageNumber; Index ++) {
     MemoryUsageBitMap[Index / 64] |= LShiftU64(1, (Index % 64));
   }
   return  EFI_SUCCESS;   
}
/**

  Get the fixed loadding address from image header assigned by build tool. This function only be called
  when Loading module at Fixed address feature enabled.

  @param ImageContext              Pointer to the image context structure that describes the PE/COFF
                                    image that needs to be examined by this function.
  @param Private                    Pointer to the private data passed in from caller

  @retval EFI_SUCCESS               An fixed loading address is assigned to this image by build tools .
  @retval EFI_NOT_FOUND             The image has no assigned fixed loadding address.

**/
EFI_STATUS
GetPeCoffImageFixLoadingAssignedAddress(
  IN OUT PE_COFF_LOADER_IMAGE_CONTEXT  *ImageContext,
  IN     PEI_CORE_INSTANCE             *Private
  )
{
   UINTN                              SectionHeaderOffset;
   EFI_STATUS                         Status;
   EFI_IMAGE_SECTION_HEADER           SectionHeader;
   EFI_IMAGE_OPTIONAL_HEADER_UNION    *ImgHdr;
   EFI_PHYSICAL_ADDRESS               FixLoaddingAddress;
   UINT16                             Index;
   UINTN                              Size;
   UINT16                             NumberOfSections;
   UINT64                             ValueInSectionHeader;
 

   FixLoaddingAddress = 0;
   Status = EFI_NOT_FOUND;

   //
   // Get PeHeader pointer
   //
   ImgHdr = (EFI_IMAGE_OPTIONAL_HEADER_UNION *)((CHAR8* )ImageContext->Handle + ImageContext->PeCoffHeaderOffset);
   if (ImageContext->IsTeImage) {
     //
     // for TE image, the fix loadding address is saved in first section header that doesn't point
     // to code section.
     //
     SectionHeaderOffset = sizeof (EFI_TE_IMAGE_HEADER);
     NumberOfSections = ImgHdr->Te.NumberOfSections;
   } else {
     SectionHeaderOffset = (UINTN)(
                                 ImageContext->PeCoffHeaderOffset +
                                 sizeof (UINT32) +
                                 sizeof (EFI_IMAGE_FILE_HEADER) +
                                 ImgHdr->Pe32.FileHeader.SizeOfOptionalHeader
                                 );
      NumberOfSections = ImgHdr->Pe32.FileHeader.NumberOfSections;
   }
   //
   // Get base address from the first section header that doesn't point to code section.
   //
   for (Index = 0; Index < NumberOfSections; Index++) {
     //
     // Read section header from file
     //
     Size = sizeof (EFI_IMAGE_SECTION_HEADER);
     Status = ImageContext->ImageRead (
                              ImageContext->Handle,
                              SectionHeaderOffset,
                              &Size,
                              &SectionHeader
                              );
     if (EFI_ERROR (Status)) {
       return Status;
     }

     Status = EFI_NOT_FOUND;

     if ((SectionHeader.Characteristics & EFI_IMAGE_SCN_CNT_CODE) == 0) {
       //
       // Build tool will save the address in PointerToRelocations & PointerToLineNumbers fields in the first section header
       // that doesn't point to code section in image header, as well as ImageBase field of image header. A notable thing is
       // that for PEIM, the value in ImageBase field may not be equal to the value in PointerToRelocations & PointerToLineNumbers because
       // for XIP PEIM, ImageBase field holds the image base address running on the Flash. And PointerToRelocations & PointerToLineNumbers
       // hold the image base address when it is shadow to the memory. And there is an assumption that when the feature is enabled, if a
       // module is assigned a loading address by tools, PointerToRelocations & PointerToLineNumbers fields should NOT be Zero, or
       // else, these 2 fileds should be set to Zero
       //
       ValueInSectionHeader = ReadUnaligned64((UINT64*)&SectionHeader.PointerToRelocations);
       if (ValueInSectionHeader != 0) {
         //
         // Found first section header that doesn't point to code section.
         //
         if ((INT64)PcdGet64(PcdLoadModuleAtFixAddressEnable) > 0) {
           //
           // When LMFA feature is configured as Load Module at Fixed Absolute Address mode, PointerToRelocations & PointerToLineNumbers field
           // hold the absolute address of image base runing in memory
           //
           FixLoaddingAddress = ValueInSectionHeader;
         } else {
           //
           // When LMFA feature is configured as Load Module at Fixed offset mode, PointerToRelocations & PointerToLineNumbers field
           // hold the offset relative to a platform-specific top address.
           //
           FixLoaddingAddress = (EFI_PHYSICAL_ADDRESS)(Private->LoadModuleAtFixAddressTopAddress + (INT64)ValueInSectionHeader);
         }
         //
         // Check if the memory range is avaliable.
         //
         Status = CheckAndMarkFixLoadingMemoryUsageBitMap (Private, FixLoaddingAddress, (UINT32) ImageContext->ImageSize);
         if (!EFI_ERROR(Status)) {
           //
           // The assigned address is valid. Return the specified loadding address
           //
           ImageContext->ImageAddress = FixLoaddingAddress;
         }
       }
       break;
     }
     SectionHeaderOffset += sizeof (EFI_IMAGE_SECTION_HEADER);
   }
   DEBUG ((EFI_D_INFO|EFI_D_LOAD, "LOADING MODULE FIXED INFO: Loading module at fixed address 0x%11p. Status= %r \n", (VOID *)(UINTN)FixLoaddingAddress, Status));
   return Status;
}
/**

  Loads and relocates a PE/COFF image into memory.
  If the image is not relocatable, it will not be loaded into memory and be loaded as XIP image.

  @param Pe32Data        - The base address of the PE/COFF file that is to be loaded and relocated
  @param ImageAddress    - The base address of the relocated PE/COFF image
  @param ImageSize       - The size of the relocated PE/COFF image
  @param EntryPoint      - The entry point of the relocated PE/COFF image

  @retval EFI_SUCCESS           The file was loaded and relocated
  @retval EFI_OUT_OF_RESOURCES  There was not enough memory to load and relocate the PE/COFF file

**/
EFI_STATUS
LoadAndRelocatePeCoffImage (
  IN  VOID                                      *Pe32Data,
  OUT EFI_PHYSICAL_ADDRESS                      *ImageAddress,
  OUT UINT64                                    *ImageSize,
  OUT EFI_PHYSICAL_ADDRESS                      *EntryPoint
  )
{
  EFI_STATUS                            Status;
  PE_COFF_LOADER_IMAGE_CONTEXT          ImageContext;
  PEI_CORE_INSTANCE                     *Private;

  Private = PEI_CORE_INSTANCE_FROM_PS_THIS (GetPeiServicesTablePointer ());

  ZeroMem (&ImageContext, sizeof (ImageContext));
  ImageContext.Handle = Pe32Data;
  Status              = GetImageReadFunction (&ImageContext);

  ASSERT_EFI_ERROR (Status);

  Status = PeCoffLoaderGetImageInfo (&ImageContext);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // When Image has no reloc section, it can't be relocated into memory.
  //
  if (ImageContext.RelocationsStripped && (Private->PeiMemoryInstalled) && (Private->HobList.HandoffInformationTable->BootMode != BOOT_ON_S3_RESUME)) {
    DEBUG ((EFI_D_INFO|EFI_D_LOAD, "The image at 0x%08x without reloc section can't be loaded into memory\n", (UINTN) Pe32Data));
  }

  //
  // Set default base address to current image address.
  //
  ImageContext.ImageAddress = (EFI_PHYSICAL_ADDRESS)(UINTN) Pe32Data;

  //
  // Allocate Memory for the image when memory is ready, boot mode is not S3, and image is relocatable.
  //
  if ((!ImageContext.RelocationsStripped) && (Private->PeiMemoryInstalled) && (Private->HobList.HandoffInformationTable->BootMode != BOOT_ON_S3_RESUME)) {
    if (PcdGet64(PcdLoadModuleAtFixAddressEnable) != 0) {
      Status = GetPeCoffImageFixLoadingAssignedAddress(&ImageContext, Private);
      if (EFI_ERROR (Status)){
        DEBUG ((EFI_D_INFO|EFI_D_LOAD, "LOADING MODULE FIXED ERROR: Failed to load module at fixed address. \n"));
        //
        // The PEIM is not assiged valid address, try to allocate page to load it.
        //
        ImageContext.ImageAddress = (EFI_PHYSICAL_ADDRESS)(UINTN) AllocatePages (EFI_SIZE_TO_PAGES ((UINT32) ImageContext.ImageSize));
      }
    } else {
      ImageContext.ImageAddress = (EFI_PHYSICAL_ADDRESS)(UINTN) AllocatePages (EFI_SIZE_TO_PAGES ((UINT32) ImageContext.ImageSize));
    }
    ASSERT (ImageContext.ImageAddress != 0);
    if (ImageContext.ImageAddress == 0) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Skip the reserved space for the stripped PeHeader when load TeImage into memory.
    //
    if (ImageContext.IsTeImage) {
      ImageContext.ImageAddress = ImageContext.ImageAddress +
                                  ((EFI_TE_IMAGE_HEADER *) Pe32Data)->StrippedSize -
                                  sizeof (EFI_TE_IMAGE_HEADER);
    }
  }

  //
  // Load the image to our new buffer
  //
  Status = PeCoffLoaderLoadImage (&ImageContext);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Relocate the image in our new buffer
  //
  Status = PeCoffLoaderRelocateImage (&ImageContext);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Flush the instruction cache so the image data is written before we execute it
  //
  if ((!ImageContext.RelocationsStripped) && (Private->PeiMemoryInstalled) && (Private->HobList.HandoffInformationTable->BootMode != BOOT_ON_S3_RESUME)) {
    InvalidateInstructionCacheRange ((VOID *)(UINTN)ImageContext.ImageAddress, (UINTN)ImageContext.ImageSize);
  }

  *ImageAddress = ImageContext.ImageAddress;
  *ImageSize    = ImageContext.ImageSize;
  *EntryPoint   = ImageContext.EntryPoint;

  return EFI_SUCCESS;
}

/**
  Loads a PEIM into memory for subsequent execution. If there are compressed
  images or images that need to be relocated into memory for performance reasons,
  this service performs that transformation.

  @param PeiServices      An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation
  @param FileHandle       Pointer to the FFS file header of the image.
  @param ImageAddressArg  Pointer to PE/TE image.
  @param ImageSizeArg     Size of PE/TE image.
  @param EntryPoint       Pointer to entry point of specified image file for output.
  @param AuthenticationState - Pointer to attestation authentication state of image.

  @retval EFI_SUCCESS      Image is successfully loaded.
  @retval EFI_NOT_FOUND    Fail to locate necessary PPI.
  @retval EFI_UNSUPPORTED  Image Machine Type is not supported.

**/
EFI_STATUS
PeiLoadImageLoadImage (
  IN     CONST EFI_PEI_SERVICES       **PeiServices,
  IN     EFI_PEI_FILE_HANDLE          FileHandle,
  OUT    EFI_PHYSICAL_ADDRESS         *ImageAddressArg,  OPTIONAL
  OUT    UINT64                       *ImageSizeArg,     OPTIONAL
  OUT    EFI_PHYSICAL_ADDRESS         *EntryPoint,
  OUT    UINT32                       *AuthenticationState
  )
{
  EFI_STATUS                  Status;
  VOID                        *Pe32Data;
  EFI_PHYSICAL_ADDRESS        ImageAddress;
  UINT64                      ImageSize;
  EFI_PHYSICAL_ADDRESS        ImageEntryPoint;
  UINT16                      Machine;
  EFI_SECTION_TYPE            SearchType1;
  EFI_SECTION_TYPE            SearchType2;

  *EntryPoint          = 0;
  ImageSize            = 0;
  *AuthenticationState = 0;

  if (FeaturePcdGet (PcdPeiCoreImageLoaderSearchTeSectionFirst)) {
    SearchType1 = EFI_SECTION_TE;
    SearchType2 = EFI_SECTION_PE32;
  } else {
    SearchType1 = EFI_SECTION_PE32;
    SearchType2 = EFI_SECTION_TE;
  }

  //
  // Try to find a first exe section (if PcdPeiCoreImageLoaderSearchTeSectionFirst
  // is true, TE will be searched first).
  //
  Status = PeiServicesFfsFindSectionData (
             SearchType1,
             FileHandle,
             &Pe32Data
             );
  //
  // If we didn't find a first exe section, try to find the second exe section.
  //
  if (EFI_ERROR (Status)) {
    Status = PeiServicesFfsFindSectionData (
               SearchType2,
               FileHandle,
               &Pe32Data
               );
    if (EFI_ERROR (Status)) {
      //
      // PEI core only carry the loader function fro TE and PE32 executables
      // If this two section does not exist, just return.
      //
      return Status;
    }
  }

  //
  // If memory is installed, perform the shadow operations
  //
  Status = LoadAndRelocatePeCoffImage (
    Pe32Data,
    &ImageAddress,
    &ImageSize,
    &ImageEntryPoint
  );

  ASSERT_EFI_ERROR (Status);


  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Got the entry point from the loaded Pe32Data
  //
  Pe32Data    = (VOID *) ((UINTN) ImageAddress);
  *EntryPoint = ImageEntryPoint;

  Machine = PeCoffLoaderGetMachineType (Pe32Data);

  if (!EFI_IMAGE_MACHINE_TYPE_SUPPORTED (Machine)) {
    if (!EFI_IMAGE_MACHINE_CROSS_TYPE_SUPPORTED (Machine)) {
      return EFI_UNSUPPORTED;
    }
  }

  if (ImageAddressArg != NULL) {
    *ImageAddressArg = ImageAddress;
  }

  if (ImageSizeArg != NULL) {
    *ImageSizeArg = ImageSize;
  }

  DEBUG_CODE_BEGIN ();
    CHAR8                              *AsciiString;
    CHAR8                              AsciiBuffer[512];
    INT32                              Index;
    INT32                              Index1;

    //
    // Print debug message: Loading PEIM at 0x12345678 EntryPoint=0x12345688 Driver.efi
    //
    if (Machine != EFI_IMAGE_MACHINE_IA64) {
      DEBUG ((EFI_D_INFO | EFI_D_LOAD, "Loading PEIM at 0x%11p EntryPoint=0x%11p ", (VOID *)(UINTN)ImageAddress, (VOID *)(UINTN)*EntryPoint));
    } else {
      //
      // For IPF Image, the real entry point should be print.
      //
      DEBUG ((EFI_D_INFO | EFI_D_LOAD, "Loading PEIM at 0x%11p EntryPoint=0x%11p ", (VOID *)(UINTN)ImageAddress, (VOID *)(UINTN)(*(UINT64 *)(UINTN)*EntryPoint)));
    }

    //
    // Print Module Name by PeImage PDB file name.
    //
    AsciiString = PeCoffLoaderGetPdbPointer (Pe32Data);

    if (AsciiString != NULL) {
      for (Index = (INT32) AsciiStrLen (AsciiString) - 1; Index >= 0; Index --) {
        if (AsciiString[Index] == '\\') {
          break;
        }
      }

      if (Index != 0) {
        for (Index1 = 0; AsciiString[Index + 1 + Index1] != '.'; Index1 ++) {
          AsciiBuffer [Index1] = AsciiString[Index + 1 + Index1];
        }
        AsciiBuffer [Index1] = '\0';
        DEBUG ((EFI_D_INFO | EFI_D_LOAD, "%a.efi", AsciiBuffer));
      }
    }

  DEBUG_CODE_END ();

  DEBUG ((EFI_D_INFO | EFI_D_LOAD, "\n"));

  return EFI_SUCCESS;

}


/**
  The wrapper function of PeiLoadImageLoadImage().

  @param This            - Pointer to EFI_PEI_LOAD_FILE_PPI.
  @param FileHandle      - Pointer to the FFS file header of the image.
  @param ImageAddressArg - Pointer to PE/TE image.
  @param ImageSizeArg    - Size of PE/TE image.
  @param EntryPoint      - Pointer to entry point of specified image file for output.
  @param AuthenticationState - Pointer to attestation authentication state of image.

  @return Status of PeiLoadImageLoadImage().

**/
EFI_STATUS
EFIAPI
PeiLoadImageLoadImageWrapper (
  IN     CONST EFI_PEI_LOAD_FILE_PPI  *This,
  IN     EFI_PEI_FILE_HANDLE          FileHandle,
  OUT    EFI_PHYSICAL_ADDRESS         *ImageAddressArg,  OPTIONAL
  OUT    UINT64                       *ImageSizeArg,     OPTIONAL
  OUT    EFI_PHYSICAL_ADDRESS         *EntryPoint,
  OUT    UINT32                       *AuthenticationState
  )
{
  return PeiLoadImageLoadImage (
           GetPeiServicesTablePointer (),
           FileHandle,
           ImageAddressArg,
           ImageSizeArg,
           EntryPoint,
           AuthenticationState
           );
}

/**
  Check whether the input image has the relocation.

  @param  Pe32Data   Pointer to the PE/COFF or TE image.

  @retval TRUE       Relocation is stripped.
  @retval FALSE      Relocation is not stripped.

**/
BOOLEAN
RelocationIsStrip (
  IN VOID  *Pe32Data
  )
{
  EFI_IMAGE_OPTIONAL_HEADER_PTR_UNION  Hdr;
  EFI_IMAGE_DOS_HEADER                 *DosHdr;

  ASSERT (Pe32Data != NULL);

  DosHdr = (EFI_IMAGE_DOS_HEADER *)Pe32Data;
  if (DosHdr->e_magic == EFI_IMAGE_DOS_SIGNATURE) {
    //
    // DOS image header is present, so read the PE header after the DOS image header.
    //
    Hdr.Pe32 = (EFI_IMAGE_NT_HEADERS32 *)((UINTN) Pe32Data + (UINTN) ((DosHdr->e_lfanew) & 0x0ffff));
  } else {
    //
    // DOS image header is not present, so PE header is at the image base.
    //
    Hdr.Pe32 = (EFI_IMAGE_NT_HEADERS32 *)Pe32Data;
  }

  //
  // Three cases with regards to relocations:
  // - Image has base relocs, RELOCS_STRIPPED==0    => image is relocatable
  // - Image has no base relocs, RELOCS_STRIPPED==1 => Image is not relocatable
  // - Image has no base relocs, RELOCS_STRIPPED==0 => Image is relocatable but
  //   has no base relocs to apply
  // Obviously having base relocations with RELOCS_STRIPPED==1 is invalid.
  //
  // Look at the file header to determine if relocations have been stripped, and
  // save this info in the image context for later use.
  //
  if (Hdr.Te->Signature == EFI_TE_IMAGE_HEADER_SIGNATURE) {
    if ((Hdr.Te->DataDirectory[0].Size == 0) && (Hdr.Te->DataDirectory[0].VirtualAddress == 0)) {
      return TRUE;
    } else {
      return FALSE;
    }
  } else if (Hdr.Pe32->Signature == EFI_IMAGE_NT_SIGNATURE)  {
    if ((Hdr.Pe32->FileHeader.Characteristics & EFI_IMAGE_FILE_RELOCS_STRIPPED) != 0) {
      return TRUE;
    } else {
      return FALSE;
    }
  }

  return FALSE;
}

/**
  Routine to load image file for subsequent execution by LoadFile Ppi.
  If any LoadFile Ppi is not found, the build-in support function for the PE32+/TE
  XIP image format is used.

  @param PeiServices     - An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation
  @param FileHandle      - Pointer to the FFS file header of the image.
  @param PeimState       - The dispatch state of the input PEIM handle.
  @param EntryPoint      - Pointer to entry point of specified image file for output.
  @param AuthenticationState - Pointer to attestation authentication state of image.

  @retval EFI_SUCCESS    - Image is successfully loaded.
  @retval EFI_NOT_FOUND  - Fail to locate necessary PPI
  @retval Others         - Fail to load file.

**/
EFI_STATUS
PeiLoadImage (
  IN     CONST EFI_PEI_SERVICES       **PeiServices,
  IN     EFI_PEI_FILE_HANDLE          FileHandle,
  IN     UINT8                        PeimState,
  OUT    EFI_PHYSICAL_ADDRESS         *EntryPoint,
  OUT    UINT32                       *AuthenticationState
  )
{
  EFI_STATUS              PpiStatus;
  EFI_STATUS              Status;
  UINTN                   Index;
  EFI_PEI_LOAD_FILE_PPI   *LoadFile;
  EFI_PHYSICAL_ADDRESS    ImageAddress;
  UINT64                  ImageSize;
  BOOLEAN                 IsStrip;

  IsStrip = FALSE;
  //
  // If any instances of PEI_LOAD_FILE_PPI are installed, they are called.
  // one at a time, until one reports EFI_SUCCESS.
  //
  Index = 0;
  do {
    PpiStatus = PeiServicesLocatePpi (
                  &gEfiPeiLoadFilePpiGuid,
                  Index,
                  NULL,
                  (VOID **)&LoadFile
                  );
    if (!EFI_ERROR (PpiStatus)) {
      Status = LoadFile->LoadFile (
                          LoadFile,
                          FileHandle,
                          &ImageAddress,
                          &ImageSize,
                          EntryPoint,
                          AuthenticationState
                          );
      if (!EFI_ERROR (Status)) {
        //
        // The shadowed PEIM must be relocatable.
        //
        if (PeimState == PEIM_STATE_REGISITER_FOR_SHADOW) {
          IsStrip = RelocationIsStrip ((VOID *) (UINTN) ImageAddress);
          ASSERT (!IsStrip);
          if (IsStrip) {
            return EFI_UNSUPPORTED;
          }
        }

        //
        // The image to be started must have the machine type supported by PeiCore.
        //
        ASSERT (EFI_IMAGE_MACHINE_TYPE_SUPPORTED (PeCoffLoaderGetMachineType ((VOID *) (UINTN) ImageAddress)));
        if (!EFI_IMAGE_MACHINE_TYPE_SUPPORTED (PeCoffLoaderGetMachineType ((VOID *) (UINTN) ImageAddress))) {
          return EFI_UNSUPPORTED;
        }
        return Status;
      }
    }
    Index++;
  } while (!EFI_ERROR (PpiStatus));

  return PpiStatus;
}


/**

  Install Pei Load File PPI.


  @param PrivateData     - Pointer to PEI_CORE_INSTANCE.
  @param OldCoreData     - Pointer to PEI_CORE_INSTANCE.

**/
VOID
InitializeImageServices (
  IN  PEI_CORE_INSTANCE   *PrivateData,
  IN  PEI_CORE_INSTANCE   *OldCoreData
  )
{
  if (OldCoreData == NULL) {
    //
    // The first time we are XIP (running from FLASH). We need to remember the
    // FLASH address so we can reinstall the memory version that runs faster
    //
    PrivateData->XipLoadFile = &gPpiLoadFilePpiList;
    PeiServicesInstallPpi (PrivateData->XipLoadFile);
  } else {
    //
    // 2nd time we are running from memory so replace the XIP version with the
    // new memory version.
    //
    PeiServicesReInstallPpi (PrivateData->XipLoadFile, &gPpiLoadFilePpiList);
  }
}




