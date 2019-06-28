/***************************************************************************
*                                                                          *
* Filename: buicapi.h                                                      *
*                                                                          *
*                                                                          *
* Copyright (c) 1997 by Calvin E. Aiken and Marilyn O. Aiken               *
*            All rights reserved.                                          *
*                                                                          *
* These programs are the sole property of Calvin E. Aiken and Marilyn O.   *
* Aiken, aka Unisoft Imaging, and contain proprietary information.  These  *
* routines should not by used by anyone except Calvin E. Aiken and Marilyn *
* O. Aiken's customers in accoordance with terms of a license.             *
*                                                                          *
* - Modifications:                                                         *
*                                                                          *
*   ??????????????       BUICAPI.h original written by HTL in Italy        *
*   Sept  17, 1997  cea  Added USI display functions and TIFF support.     *
*                                                                          *
* - Subroutines and Functions                                              *
*                                                                          *
*  This module contains the structures and prototypes for the simple       *
*  MS-Windows Image Window Interface and the BUIC Scanner Dynamic Link     *
*  Library.  This software can be used from Visual Basic or a simple       *
*  MS-Windows application.                                                 *
*                                                                          *
***************************************************************************/
#ifdef LINUX
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef MAC
#include <malloc.h>
#endif

#define WINCALLBACK
#undef ASSEM
#undef COLORPROTOTYPES
#define O_BINARY 0
#define _O_BINARY 0
#undef MotorolaMemory

#ifndef FAR
#define FAR
#endif

#ifndef far 
#define far
#endif

#ifndef PASCAL
#define PASCAL
#endif

#ifndef HWND
#define HWND int
#endif

#ifndef HANDLE
#define HANDLE int
#endif

#ifndef LPSTR
#define LPSTR char *
#endif

#ifndef LPLONG
#define LPLONG long *
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef FARPROC
#define FARPROC
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef DWORD
#define DWORD unsigned int
#endif

#ifndef LPDWORD
#define LPDWORD unsigned int *
#endif

#ifndef LONG
#define LONG long
#endif

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef wsprintf
#define wsprintf sprintf
#endif

#ifndef LPCSTR
#define LPCSTR char *
#endif

#ifndef LPINT
#define LPINT int *
#endif

#define _huge
#define _O_RDONLY O_RDONLY
#define _O_CREAT O_CREAT
#define _O_WRONLY O_WRONLY
#define _O_TRUNC O_TRUNC
#define _S_IWRITE S_IWRITE
#define _S_IREAD S_IREAD
#define UINT     unsigned int
#define UCHAR    unsigned char
#define _open    open
#define _close   close
#define _write   write
#define _read    read
#define lstrcpyn strcpyn
#define lstrcpy  strcpy

#ifndef EJECT_TO_DEFAULT
#define EJECT_TO_DEFAULT 0
#endif

#ifndef PVOID
#define PVOID void *
#endif

#ifndef BOOL
#define BOOL int
#endif

#ifndef Sleep
#define Sleep(x) usleep(x * 1000)
#endif

#endif //LINUX

#ifdef __cplusplus
#define CFUNCTIONSDLLCALLS extern "C"
#else
#define CFUNCTIONSDLLCALLS
#endif

#define                     BUIC1000              2
#define                     BUIC1500              3
#define                     TS400               400
#define                     CX30                 30
#define                     TS200               200
#define                     TS205               205
#define                     TS215               215
#define                     TS220               220
#define                     TS230               230
#define                     TS240               240
#define                     TS300               300
#define                     TS300EBS            314
#define                     TS440               440
#define                     SB500               500
#define                     SB600               600
#define                     SB650M              651
#define                     BX7200             7200
#define                     TS240SF             250
#define                     TS500               501

#ifndef EJECT_TO_AUX
#define EJECT_TO_AUX 1
#endif

#define BUIC_SCAN_FRONT      1
#define BUIC_SCAN_BACK       2
#define BUIC_SCAN_BOTH       3
#define BUIC_SCAN_MICR       4
#define BUIC_SCAN_FRONT_MICR 5
#define BUIC_SCAN_BACK_MICR  6
#define BUIC_SCAN_BOTH_MICR  7

#define BUIC_SCAN_NONE_CODE      BUIC_SCAN_MICR
#define BUIC_SCAN_FRONT_CODE     BUIC_SCAN_FRONT_MICR
#define BUIC_SCAN_BACK_CODE      BUIC_SCAN_BACK_MICR
#define BUIC_SCAN_BOTH_CODE      BUIC_SCAN_BOTH_MICR


/*-----------------02-18-97 12:18pm-----------------
  BUICStatus - function checks to see if a check is present and ready
      to scan and returns an error status for information.

  PARAMETERS:
      NONE

  RETURN:
      1                       - Check(s) present in input hopper.
      0                       - No checks present in input hopper.
      B1000_START_ACQ         - Communication error.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICStatus(void);

/*-----------------10-02-09 11:28am-----------------
  BUICStatusDelay - function checks to see if a check is present and ready
      to scan and returns an error status for information.

  PARAMETERS:
      iIntervalMilliSec       - Delay between calls to BUICStatus if
                                feeder is empty.  Value Range 16 to 500.
      iTotalDelayMilliSec     - If this time is exceeded, then just return
                                empty feeder (0).
                                1 Second would be 1000
                                1 Minute would be 60000
                                1 Hour would be 60 * 60 * 1000 or 3600000

  RETURN:
      1                       - Check(s) present in input hopper.
      0                       - No checks present in input hopper.
      B1000_START_ACQ         - Communication error.
      BUIC_NOT_INIT           - Scanner not initialized.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICStatusDelay(
   int iIntervalMilliSec, int iTotalDelayMilliSec);

/*-----------------02-18-97 12:18pm-----------------
  BUICInit - function checks to see if name of program (DLL) is
      correct.  It then checks the ASPI interface to see if a SCSI
      controller is out there and working.

  PARAMETERS:
      NONE

  RETURN:
      TRUE                    - Everything initialized correctly.
      BUIC_ERROR_NOMANAGER    - No ASPI manager present.
      BUIC_ERROR_ILLEGALMODE  - Illegal mode for ASPI.
      BUIC_ERROR_OLDMANAGER   -
      BUIC_ERROR             -
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICInit(void);
/*-----------------02-18-97 12:18pm-----------------
  BUICInitPath - function checks to see if name of program (DLL) is
      correct.  It then checks the ASPI interface to see if a SCSI
      controller is out there and working.
      sDLLPath - Path of the DLL's.
      sIniFileName - File name and path of BUICScan.ini or new name.
      sCfgFileName - Path of ts4cfg.cfg or new name.

  PARAMETERS:
      NONE

  RETURN:
      TRUE                    - Everything initialized correctly.
      BUIC_ERROR_NOMANAGER    - No ASPI manager present.
      BUIC_ERROR_ILLEGALMODE  - Illegal mode for ASPI.
      BUIC_ERROR_OLDMANAGER   -
      BUIC_ERROR             -

   NOTE: This function is Obsolete and Users should review BUICInit and
         BUICSetParamString(...)
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICInitPath(char *sDLLPath,
   char *sIniFileName, char *sCfgFileName);

/*-----------------02-18-97 12:18pm-----------------
  BUICExit - function deinitializes the BUIC scanner.

  PARAMETERS:
      NONE

  RETURN:
      TRUE                    - Everything initialized correctly.
      BUIC_ERROR_NOINIT       - BUIC scanner was never initialized
                                so no need to uninitialize
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICExit(void);

/*-----------------02-18-97 12:18pm-----------------
  BUICDebug - function writes out messages.

  PARAMETERS:
      iState

  RETURN:
      TRUE                    - Everything initialized correctly.

  ACTION:
      Written debug message if iState is TRUE.  This method of debug
      does not really work, but is left for backward compatibility.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICDebug(int iState);
#define BUIC_DEBUG_OFF   0
#define BUIC_DEBUG_ON    1
/*-----------------02-18-97 12:18pm-----------------
  BUICSetParamString - function sets the path and/or
      filename (or string) for various parameters in
      the configuration files accessed by the scanners.
      Currently supported at time of original writing of
      function are sDLLPath, sIniFileName, sCfgPathName,
      sFirmwarePathName, and sFontFileName.

      iParameter - Parameter to be set or should I say string.
      sParameter - Currently a path and/or filename to set.

          CFG_DLLPATH, sDLLPath - Path of the DLL's.
          CFG_INIPATH, sIniFileName - File name and path of BUICScan.ini or new name.
          CFG_CFGPATH, sCfgPathName - Path Name to write ts4cfg.cfg and ts4cfg.tmp.

  PARAMETERS:
      NONE

  RETURN:
      TRUE                    - Everything initialized correctly.
      BUIC_ERROR             -
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICSetParamString(int iParameter, char *sString);
/*-----------------02-18-97 12:18pm-----------------
  BUICGetParamString - function gets the path and/or
      filename (or string) for various parameters in
      the configuration files accessed by the scanners.
      Currently supported at time of original writing of
      function are sDLLPath, sIniFileName, sCfgPathName,
      sFirmwarePathName, and sFontFileName.

      iParameter - Parameter to be set or should I say string.

          CFG_DLLPATH, sDLLPath - Path of the DLL's.
          CFG_INIPATH, sIniFileName - File name and path of BUICScan.ini or new name.
          CFG_CFGPATH, sCfgPathName - Path Name to write ts4cfg.cfg and ts4cfg.tmp.

  PARAMETERS:
      NONE

  RETURN:
      TRUE                    - Everything initialized correctly.
      BUIC_ERROR             -
--------------------------------------------------*/
CFUNCTIONSDLLCALLS char * PASCAL BUICGetParamString(int iParameter);

/*--------------------------------------------------------------
   This method of debug does not really work, but is left for
   backward compatibility.
---------------------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICDisplayAbout(void);

/*-----------------02-18-97 12:18pm-----------------
  BUICDisplayStatus - Shows status and returns error if
      BUIC scanner has not been initialized.  Does a SCSI Inquiry
      command and then puts up a Dialog Box with the status
      of the SCSI Inquiry.

  PARAMETERS:
      NONE

  RETURN:
      TRUE                    - Everything initialized correctly.
      BUIC_ERROR_NOINIT       - If scanner has not been initialized

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICDisplayStatus(void);

/***********************************************************************
  BUIC parameters - Use these definitions for BUICSetParam and BUICGetParam.
  Paramter definition will start with BPARAM or TBPARAM (TS400 unique)
  and valid values will start with BUIC.

***********************************************************************/
#define MAX_CFG_PARAMS       250   // Maximum parameter, # of parameters
#define MAX_CFG_STRING_PARAMS 20 // Maximum parameter, # of parameters
#define MAX_PARAMS            MAX_CFG_PARAMS  // Maximum parameter, # of parameters
#define BUIC_DEV_OFF           0  // OFF and ON can be used for all devices
#define BUIC_DEV_ON            1  // OFF and ON can be used for all devices
#define CFG_DEV_OFF            0  // OFF and ON can be used for all devices
#define CFG_DEV_ON             1  // OFF and ON can be used for all devices

/*-----------------08/03/00 03:05pm-----------------
 Two Color Light Parameters
--------------------------------------------------*/
#define CFG_FRONT_RIDO_ENABLE   61
#define CFG_FRONT_OUT_FORMAT    62
#define CFG_FRONT_INTENSITY     63
#define CFG_FRONT_CLIP_THRESH   64
#define CFG_FRONT_BW_THRESH     65
#define CFG_BACK_RIDO_ENABLE    66
#define CFG_BACK_OUT_FORMAT     67
#define CFG_BACK_INTENSITY      68
#define CFG_BACK_CLIP_THRESH    69
#define CFG_BACK_BW_THRESH      70

/*-----------------08/03/00 03:13pm-----------------
 Devices Parameters
--------------------------------------------------*/
#define CFG_DEV_DSP             55
#define TPARAM_DEV_DSP          CFG_DEV_DSP
#define CFG_DEV_EXT_READER      47
#define CFG_DEV_BADGE_READER     3
#define BPARAM_BADGE            CFG_DEV_BADGE_READER  // not used
#define CFG_DEV_ENDORSER         4
#define BPARAM_ENDORSER         CFG_DEV_ENDORSER      // Optional Capability
#define CFG_DEV_SORTER          32
#define BPARAM_SORTER           CFG_DEV_SORTER        // Optional Capability
#define CFG_DEV_PRINTER         31
#define BPARAM_PRINTER          CFG_DEV_PRINTER
#define CFG_DEV_DOUBLE_FEED      7
#define TPARAM_DOUBLEFEED_THICK CFG_DEV_DOUBLE_FEED
#define BPARAM_PHOTOCELL        CFG_DEV_DOUBLE_FEED
#define CFG_DEV_DF_CONTINUE      2  /* After a double feed, continue if */
                                    /*MICR is valid.  Otherwise, place  */
                                    /*document in output tray and return*/
                                    /*double feed error.                */

/*-----------------08/03/00 03:25pm-----------------
 MICR parameters
--------------------------------------------------*/
#define CFG_MICR_ENABLE          1
#define BPARAM_MAGNREADER       CFG_MICR_ENABLE  // BUIC1500 and TS400
#define CFG_MICR_FONT            2
#define BPARAM_MAGNTYPE         CFG_MICR_FONT
#define CFG_MICR_CMC7            0
#define CFG_MICR_E13B            1
#define CFG_MICR_AUTO            2
#define BUIC_CMC7               CFG_MICR_CMC7
#define BUIC_E13B               CFG_MICR_E13B
#define CFG_MICR_INITIAL_POS    14
#define CFG_MICR_END_POS        71

/*-----------------08/03/00 03:39pm-----------------
 AUX. READER parameters
--------------------------------------------------*/
#define CFG_AUXREADER_TYPE        72
#define CFG_AUXREADER_FONT        73
#define CFG_AUXREADER_INITIALPOS  74
#define CFG_AUXREADER_ENDPOS      75
#define CFG_AUXREADER_BAUDRATE    76
#define CFG_AUXREADER_PARITY      77
#define CFG_AUXREADER_CHARLENGTH  78
#define CFG_AUXREADER_STOPBIT     79

/*-----------------08/03/00 03:39pm-----------------
 SORTER parameters
--------------------------------------------------*/
#define CFG_SORTER_INPUT          49
#define CFG_SORTER_ALGORITHM      39
#define BUIC_SORTER_ALGORITHM     CFG_SORTER_ALGORITHM
/* Algorithm Options */
#define CFG_SORTER_ALG_NONE        0    // NONE
#define CFG_SORTER_ALG_PRESENT     1    // PRESENT OR VALID MICR
#define CFG_SORTER_ALG_EQUAL       2    // MICR == String1
#define CFG_SORTER_ALG_NOT_EQUAL   3    // MICR != String1
#define CFG_SORTER_ALG_GT_EQUAL    4    // MICR >= String1
#define CFG_SORTER_ALG_LT_EQUAL    5    // MICR <= String1
#define CFG_SORTER_ALG_BETWEEN     6    // (MICR >= String1) &&
                                        // (MICR <= String2)
#define CFG_SORTER_ALG_OUTSIDE     7    // (MICR <= String1
                                        // (MICR >= String2)
#define CFG_SORTER_ALG_EQUAL1OR2   8    // (MICR == String1) ||
                                        // (MICR == String2)
#define CFG_SORTER_ALG_NOTEQU1OR2  9    // (MICR != String1)
                                        // (MICR != String2)
#define BUIC_SORTER_ALG_NONE       CFG_SORTER_ALG_NONE        // NONE
#define BUIC_SORTER_ALG_PRESENT    CFG_SORTER_ALG_PRESENT     // PRESENT OR VALID MICR
#define BUIC_SORTER_ALG_EQUAL      CFG_SORTER_ALG_EQUAL       // MICR == String1
#define BUIC_SORTER_ALG_NOT_EQUAL  CFG_SORTER_ALG_NOT_EQUAL   // MICR != String1
#define BUIC_SORTER_ALG_GT_EQUAL   CFG_SORTER_ALG_GT_EQUAL    // MICR >= String1
#define BUIC_SORTER_ALG_LT_EQUAL   CFG_SORTER_ALG_LT_EQUAL    // MICR <= String1
#define BUIC_SORTER_ALG_BETWEEN    CFG_SORTER_ALG_BETWEEN     // (MICR >= String1) &&
                                                              // (MICR <= String2)
#define BUIC_SORTER_ALG_OUTSIDE    CFG_SORTER_ALG_OUTSIDE     // (MICR <= String1
                                                              // (MICR >= String2)
#define BUIC_SORTER_ALG_EQUAL1OR2  CFG_SORTER_ALG_EQUAL1OR2   // (MICR == String1) ||
                                                              // (MICR == String2)
#define BUIC_SORTER_ALG_NOTEQU1OR2 CFG_SORTER_ALG_NOTEQU1OR2  // (MICR != String1)
                                                              // (MICR != String2)
#define CFG_SORTER_INITSTRINGPOS  80
#define CFG_SORTER_ENDSTRINGPOS   81
#define CFG_SORTER_EJECTPOCKET    82
#define CFG_SORTER_STRING1        40
#define TBPARAM_SORTER_STRING1   CFG_SORTER_STRING1  // Teller TS400 and BUIC1500 ONLY
#define CFG_SORTER_STRING2        41
#define TBPARAM_SORTER_STRING2   CFG_SORTER_STRING2  // Teller TS400 and BUIC1500 ONLY

/*-----------------08/03/00 03:39pm-----------------
 IJ Printer Parameters
--------------------------------------------------*/
#define CFG_IJPRINTER_PRINTBMP     33
#define TBPARAM_PRINT_FILE         CFG_IJPRINTER_PRINTBMP     // Teller TS400 and BUIC1500 ONLY
#define CFG_IJPRINTER_BMPFILENAME  35
#define TBPARAM_PRINT_FILENAME     CFG_IJPRINTER_BMPFILENAME  // Teller TS400 and BUIC1500 ONLY
#define CFG_IJPRINTER_FONTFILENAME 83
#define CFG_IJPRINTER_INITIALPOS   84
#define CFG_IJPRINTER_SELECTION    85
#define CFG_IJPRINTER_INTENSITY    86
#define CFG_IJPRINTER_XPIXELD      87
#define CFG_IJPRINTER_CLEAN44      88
#define CFG_IJPRINTER_CLEAN18      89
#define CFG_IJPRINTER_CLEAN6       90
#define CFG_IJPRINTER_CLEAN2       91
#define CFG_IJPRINTER_BMP12FILENAME  112
#define CFG_IJPRINTER_FONT12FILENAME 113
#define CFG_IJPRINTER_PRINTPOS       114


/*-----------------08/03/00 03:39pm-----------------
 IMAGE Parameters
--------------------------------------------------*/
#define CFG_IMAGE_FORMAT           92
#define CFG_BMP_VERTICAL            1
#define CFG_BMP_HORIZONTAL          2
#define CFG_UNCOMP_TIFF_VERTICAL    3
#define CFG_UNCOMP_TIFF_HORIZONTAL  4
#define CFG_JPEG_VERTICAL           5
#define CFG_JPEG_HORIZONTAL         6
#define CFG_COMP_TIFF_VERTICAL      7
#define CFG_COMP_TIFF_HORIZONTAL    8
#define FORMAT_TIFF_UNCOMP          0
#define FORMAT_TIFF                 1
#define FORMAT_TIFF_REVERSE         9
/* Gray scale stored to BMP                          */
#define FORMAT_BMP                  3
/* Gray scale compressed to JPEG Gray (one component)*/
#define FORMAT_JPEGG                4
#define CFG_IMAGE_FRONTONLY         42
#define TBPARAM_ACQ_FRONTONLY       CFG_IMAGE_FRONTONLY
#define CFG_IMAGE_FRONTBACK         43
#define TBPARAM_ACQ_FRONTBACK       CFG_IMAGE_FRONTBACK
#define CFG_IMAGE_BW                23
#define CFG_IMAGE_BW_BW              0
#define CFG_IMAGE_BW_GRAY            1
#define BPARAM_GRAY                 CFG_IMAGE_BW
#define BUIC_MONO                   CFG_IMAGE_BW_BW
#define BUIC_GRAY                   CFG_IMAGE_BW_GRAY
#define TBPARAM_ACQ_BLACKWHITE      CFG_IMAGE_BW   // Teller TS400 and BUIC1500 ONLY
#define BUIC_BLACK                  CFG_IMAGE_BW_BW
#define BUIC_GRAY                   CFG_IMAGE_BW_GRAY
#define CFG_IMAGE_GRAY256LEVEL      45
#define CFG_IMAGE_GRAY256LEVEL_16   0
#define CFG_IMAGE_GRAY256LEVEL_256  1
#define TBPARAM_ACQ_256GRAY         CFG_IMAGE_GRAY256LEVEL  // Teller TS400 and BUIC1500 ONLY
#define BUIC_GRAY4                  CFG_IMAGE_GRAY256LEVEL_16
#define BUIC_GRAY8                  CFG_IMAGE_GRAY256LEVEL_256
#define CFG_IMAGE_RESOLUTION         6
#define CFG_IMAGE_RESOL_100X100      0
#define CFG_IMAGE_RESOL_200X100      3
#define CFG_IMAGE_RESOL_200X200      1
#define CFG_IMAGE_RESOL_200X100RAW   2
#define CFG_IMAGE_RESOL_300X300      4
#define CFG_IMAGE_RESOL_600X600      5
#define BPARAM_DPI                  CFG_IMAGE_RESOLUTION
#define BUIC_DPI100                 CFG_IMAGE_RESOL_100X100
#define BUIC_DPI200                 CFG_IMAGE_RESOL_200X200
#define BUIC_DPI200X100FAST         CFG_IMAGE_RESOL_200X100  // ONLY FOR Teller TS400 and BUIC1500
#define BUIC_DPI200X100             CFG_IMAGE_RESOL_200X100  // ONLY FOR Teller TS400 and BUIC1500
#define CFG_IMAGE_FRONT_BW_THRESH   11   /* Range from 0 to 15 */
#define BPARAM_FRONTTHRESHOLD       CFG_IMAGE_FRONT_BW_THRESH  // 0 to 14, start with 8 to 10.
#define CFG_IMAGE_BACK_BW_THRESH    12   /* Range from 0 to 15 */
#define BPARAM_REARTHRESHOLD        CFG_IMAGE_BACK_BW_THRESH // 0 to 14, start with 8 to 10.


/*-----------------08/03/00 03:39pm-----------------
 CLIP AREA Parameters
--------------------------------------------------*/
#define CFG_CLIPAREA_IMGRIGHT       19
#define BPARAM_WINDOWX1             CFG_CLIPAREA_IMGRIGHT   // ACQ: Img Right Teller TS400,Buic1500
#define CFG_CLIPAREA_IMGLEFT        21
#define BPARAM_WINDOWX2             CFG_CLIPAREA_IMGLEFT    // ACQ: Img Right Teller TS400,Buic1500
#define CFG_CLIPAREA_IMGBOTTOM      20
#define BPARAM_WINDOWY1             CFG_CLIPAREA_IMGBOTTOM  // ACQ: Img Bottom Teller TS400,Buic1500
#define CFG_CLIPAREA_IMGTOP         22
#define BPARAM_WINDOWY2             CFG_CLIPAREA_IMGTOP     // ACQ: Img Bottom Teller TS400,Buic1500

/*-----------------08/03/00 03:39pm-----------------
 RS232 Parameters
--------------------------------------------------*/
#define CFG_RS232_MODE              93
#define CFG_RS232_BAUDRATE          94
#define CFG_RS232_PARITY            95
#define CFG_RS232_CHARLENGTH        96
#define CFG_RS232_STOPBIT           97

/*-----------------08/03/00 03:39pm-----------------
 MISCELLANEOUS Parameters
--------------------------------------------------*/
#define CFG_MISC_DOUBLEFEEDLEN      98
#define CFG_MISC_MANUALFEED         51
#define TBPARAM_MANUALFEED          CFG_MISC_MANUALFEED

/*-----------------08/03/00 03:39pm-----------------
 DLL Config Parameters
--------------------------------------------------*/
#define CFG_DLLCONFIG_DLL_VERBOSE   99
#define CFG_DLLCONFIG_MEMORYDIM    100

/*-----------------08/03/00 03:39pm-----------------
 IMAGE CROPPING Parameters
--------------------------------------------------*/
#define CFG_IMAGECROPPING_ENABLE    36
#define TBPARAM_IMGCROP             CFG_IMAGECROPPING_ENABLE   // Teller TS400 and BUIC1500 ONLY

/*-----------------08/07/00 02:52pm-----------------
 SCSI
--------------------------------------------------*/
#define CFG_SCSI_ADAPTERS          101
#define CFG_SCSI_TARGETID          102
#define CFG_SCSI_ADAPTERID         103

#define CFG_SETUP_FORMAT            54
#define CFG_SETUP_ROTATION          37
#define TBPARAM_IMGROTATE           CFG_SETUP_ROTATION   // Teller TS400 and BUIC1500 ONLY
#define CFG_SETUP_FILENAMETERM     104
#define CFG_SETUP_TIFFMICRTAG      105
  #define CFG_TIFF_NOMICR            0
  #define CFG_TIFF_MICR              1
  #define CFG_TIFF_MIN               2
#define CFG_SETUP_BMPLOADONCE      106
#define CFG_SETUP_MICR_FORMAT      107
#define CFG_ORIGINAL_MICR            0
#define CFG_LESS_E_MICR              1
#define CFG_SPACES_MICR              2
#define CFG_ALL_INNER_SPACES         3
#define CFG_IMAGECROPPING_THRESH   108
#define CFG_MISC_IMAGEWAIT         109
#define CFG_SETUP_PHOTODELAY        24
#define BPARAM_PHOTODELAY          CFG_SETUP_PHOTODELAY
#define CFG_SETUP_DOC_THICKNESS     50
#define TBPARAM_ACQ_DOCTHICKNESS   CFG_SETUP_DOC_THICKNESS
#define CFG_MISC_JPEG_QUALITY      110
#define TPARAM_JPEG_QUALITY        CFG_MISC_JPEG_QUALITY
#define CFG_MISC_ENABLE_SCAN       111
#define TPARAM_ENABLE_SCAN         CFG_MISC_ENABLE_SCAN
#define CFG_SETUP_EDGEMICRSETTING  115  // 1 to 13 Threshold Setting for edge MICR
#define CFG_MISC_MICR_VERIFY       116  // Use OCR MICR VERIFY
#define CFG_MISC_MICR_VERIFY_LOG   117  // Use OCR MICR VERIFY & Log
#define CFG_MISC_MICR_GRAY_THRESHOLD   118  // MICR Gray to Bitonal Convert
#define CFG_MISC_DOUBLEFEEDDELAY       133  // Double Feed Delay
#define CFG_STATISTICS                 134  // Log Statistics about scanner
#define CFG_MISC_MICR_HONGKONG_RULES   142  // Assume OCR MICR is Good
#define CFG_MISC_PH_WHITE_THRESH       143  // PHOTO OUT White Threshold for TS220
#define CFG_MISC_PH_WHITE_TOLER        144  // PHOTO OUT White Tolerance for TS220
#define CFG_MISC_PH_ENABLE             145  // PHOTO OUT Enable for TS220

   // DCCScan Parameters December, 6, 2004
#define CFG_DCCSCAN_IQATESTS           146  //See IQAStatus Function Call
#define CFG_DCCSCAN_STARTCONTRAST      147  //Usually around 450
#define CFG_DCCSCAN_ENDCONTRAST        148  //Usually 450 to 900
#define CFG_DCCSCAN_INCCONTRAST        149  //Usually 100 to 600
#define CFG_JPEG_IMAGE_RESOLUTION      150  //100 or 200 dpi
#define CFG_DCCSCAN_MAXSPECKLES        151  //Application Depend, Check 1200 to 2000
#define CFG_DCCSCAN_MINMICRQUALITY     152  //MICR Quality 5 to 10
#define CFG_DCCSCAN_MAXBENTCORNER      153  //Number of pixels in a bent corner 60 to 200
#define CFG_DCCSCAN_MAXRAWDENSITY      154  //Usually 26 and up, but all business checks could be lower
#define CFG_DCCSCAN_MAXTIFFIMAGESIZE   155  //Maximum allowable Tiff Image Size in Kilobytes.
#define CFG_DCCSCAN_OPTIONS            156  //0 - Off
                                            //1 - try multiple EdgeDetection Contrast
                                            //2 - try simple thresholding
                                            //4 - despeckle the images
                                            //8  - save grayscale/color as BMP
                                            //16 - Group 4 Filter
                                            //32 - Return Floyd Steinberg Tiff
                                            //       as Grayscale
                                            //64 - Force EdgeDetect Images to 3.1% Density
                                            //128- Return grayscale/color as
                                            //     uncompressed image with a
                                            //     BUICMemHdr
                                            //256- Test rear image for density
                                            //512- Reduced image by a 5th (300 to 240)
                                            //1024-Test upside down images and return OCR MICR
                                            //2048-(0x800)Two MICR Mode On CX30
                                            //4096-(0x1000)Reduce image by 2/3 (300 to 200)
                                            //8192-(0x2000)Use Faster Simple Threshold on back Images
                                            //16384-(0x4000)Check Review side for MICR
                                            //32768-(0x8000) Reduce 600 dpi to 200 dpi
                                            //65536-(0x10000) Avoid "VOIDS" on Business Checks
                                            //131072-(0x20000) Second Pass MICR OCR
                                            //262144-(0x40000) Scale 600 dpi to 200 dpi front/back

#define CFG_MISC_MICR_LOWCONFIDENCE    157  //Return all Low Confidence characters as “@”.

#define CFG_IJPRINTER_PRINTSTRING   34
// Teller TS400 and BUIC1500 ONLY
#define TBPARAM_PRINT_STRING        CFG_IJPRINTER_PRINTSTRING
//#define TBPARAM_PRINT_IJSTRING        60  // Print IJ string, defined below
#define TBPARAM_REWINDDELAY     38   // Teller TS400 and BUIC1500 ONLY



#define BPARAM_CCDMODE           5
#define BUIC_ACQ_CCD_1MHZ        0
#define BUIC_ACQ_CCD_2MHZ        1

#define BPARAM_PHOTO             8
#define BPARAM_FRONTACQSTART     9
#define BPARAM_REARACQSTART     10
#define BUIC_THRESH_MIN          0
#define BUIC_THRESH_MAX         14
#define BPARAM_ACQLENGTH        13
#define BPARAM_STARTACQMAG      CFG_MICR_INITIAL_POS
#define BPARAM_STARTENDORSER    15
#define BPARAM_STOPMOTOR        16
#define BPARAM_SCANNERID        17
#define BPARAM_DOCHEIGHT        18

#define TBPARAM_DEV_INTERMICR  46
#define TBPARAM_EXTREADER_TYPE 47
#define BUIC_OCR                0
#define BUIC_MICR               1
#define TBPARAM_MICR_FONT      48
#define TBPARAM_SORTER_INPUT   49
#define BUIC_INT                0
#define BUIC_EXT                1
#define TBPARAM_FORTHANDBACK   52
#define TBPARAM_KIOSKMODE      53
#define TBPARAM_IMGFORMAT      54
#define TPARAM_MICR_ENABLE     56
#define CFG_MICR_FORMAT        57
#define TPARAM_MICR_FORMAT     CFG_MICR_FORMAT
#define MICR_FORMAT_NOSPACE     0
#define MICR_FORMAT_ALLSPACES   1
#define TPARAM_MICR_PROCESSOR  58
#define TBPARAM_OVERSCAN       59  // Teller TS400 ONLY
                                   // Setting overscan for right edge
#define TBPARAM_PRINT_IJSTRING 60  // Print IJ string

#define CFG_IMAGE_FRONTCOLOR    119
#define CFG_IMAGE_GRAYSCALEIMAGE  0  // Grayscale
#define CFG_IMAGE_COLORIMAGE      1  // Color Image
#define CFG_IMAGE_COLORIMAGERGB   2  // Special Color Image TS230 ONLY
#define CFG_IMAGE_GRAYPLUSUV      3  // TS240 UV ONLY Grayscale image with
                                         // white light + UV (ONE IMAGE)
#define CFG_IMAGE_UVONLY          4  // TS240 UV ONLY Grayscale UV image ONLY
#define CFG_IMAGE_DUALGRAYUV      5  // TS240 UV ONLY TWO IMAGES:  Grayscale
                                         // document image and UV image
#define CFG_IMAGE_FRONTRED      120
#define CFG_IMAGE_FRONTGREEN    121
#define CFG_IMAGE_FRONTBLUE     122
#define CFG_IMAGE_FRONTBOTTOM   123
#define CFG_IMAGE_FRONTTOP      124
#define CFG_IMAGE_FRONTCONTRAST 125
#define CFG_IMAGE_BACKCOLOR     126
#define CFG_IMAGE_BACKRED       127
#define CFG_IMAGE_BACKGREEN     128
#define CFG_IMAGE_BACKBLUE      129
#define CFG_IMAGE_BACKBOTTOM    130
#define CFG_IMAGE_BACKTOP       131
#define CFG_IMAGE_BACKCONTRAST  132
#define CFG_INIPATH             135
#define CFG_CFGPATH             136
#define CFG_DLLPATH             137
#define CFG_FIRMWAREPATH        138
#define CFG_RECONNECTDELAY      139
#define CFG_FONTPATH            CFG_IJPRINTER_FONTFILENAME
#define CFG_IJPRINTER_INTENSITY12 140
#define CFG_IJPRINTER_XPIXELD12   141
#define CFG_SCANNERTYPE           158
#define CFG_MICR_METHOD           159
#define CFG_MICR_METHOD_DEFAULT   0
#define CFG_MICR_METHOD_HTL       1
#define CFG_MICR_METHOD_US        2
#define CFG_MISC_SCANBATCH_ENABLE      160  //Enable TS230/TS440 BatchScan
#define CFG_MISC_FEED_SOLENOID   161  //Feed Solenoid Mode,
                                      // 0 - feed solenoid power once per batch
                                      // 1 - feed solenoid power one per check
                                      //     NOTE:  Solenoid will run hotter
#define CFG_MISC_DEBUG_MESSAGES  162
#define CFG_MISC_TS230_65        163  // USE ONLY IN TESTING MODE
                                      // CHANGES TS230-100 to TS230-65

#define CFG_MISC_PRINT_CARTRIDGE 164  // Default is 1, ONLY TS2xx products
                                      // If 1, BUICStatus checks for Print
                                      // Cartridge if Print ON and returns
                                      // error.  If 0, BUICStatus ignores
                                      // print cartridge message. 
                                      // If 2, then cartridge is tested and if
                                      // missing then CFG_DEV_PRINTER will always
                                      // be set to 0 (disabled).

#define CFG_MISC_DELAY_TS200     165  // Same as *.ini variable Delay TS200
                                      // but programmable from application
#define CFG_MISC_LOG_MESSAGES    166  // If set to 1, and debug one, then
                                      // messages saved to file also
#define CFG_MISC_SCANNER_TYPE    167  // Only for BUICGetParam function to
                                      // distinquish between TS230 & TS215
#define CFG_MISC_USB1            168  // Set to one is USB1 for longer delays
#define CFG_MISC_TS200_CK_FED    169  //
#define CFG_MISC_VIRTUAL         170  // Virtual endorse on for DCCScan
#define CFG_MISC_RED_FILTER      171  // Red Filter Options
#define CFG_MISC_USER1           172
#define CFG_MISC_USER2           173
#define CFG_MISC_USER3           174
#define CFG_MISC_USER4           175
#define CFG_MISC_USER5           176
#define CFG_SCOUTPATH            177
#define CFG_SCANNER_DISABLED     178   // Force scanner motor off
#define CFG_AMERICAN_MICR_RULES  179   // Check for more than two : or ; in MICR
#define CFG_REPORT_MICR_PARSE_ERROR 180   // Check for more than two OnUS in MICR
#define CFG_MISC_ADDITIONAL_BLINK   181   // Delay scanner reset for additional blinking
#define CFG_SCOUT_ENABLE            182
#define CFG_FEED_MSG_BEEP           183   // Beep when checks are loaded
#define CFG_MISC_FORCE_EJECT        184   // Force Operator to clear Jams by Eject
#define CFG_MISC_LATE_JAM_TEST      185   // Test TS4120 for late jam
#define CFG_REMOTE_MONITOR_LOG      186   // Write Status to Remote Log
#define CFG_MISC_MICR_DROP_SKIP     187   // Allow Mag Micr to OCR Drop Out
#define CFG_REMOTE_MONITOR_LOG_SIZE 188   // Maximum Remote Monitor File Size
#define CFG_IMAGE_PADBOTTOM         189   // Extra Scanlines at bottom
#define CFG_IMAGE_PADTOP            190   // Extra Scanlines at top
#define CFG_SCAN_MODE               191   // FOR CX30 ONLY:
#define CFG_SCAN_MODE_FORWARD         0   // 0 - Scan forward direction
                                          //     place check in OUTPUT tray
#define CFG_SCAN_MODE_REVERSE         1   // 1 - Scan forward direction,
                                          //     place check in INPUT tray
#define CFG_SCAN_MODE_HOLD            2   // 2 - Scan forward direction,
                                          //     HOLD check after reading.
                                          //     NEXT SCAN will place check
                                          //     in tray.
#define CFG_SCAN_MODE_KIOSK          3    // 3 - IF document is parked or
                                          //     Held on a CX30 ONLY and
                                          //     with KIOSK capability,
                                          //     document will be returned
                                          //     only far enough for small
                                          //     endorsement on far rear right
                                          //     edge and then put in forward
                                          //     or output TRAY.
#define CFG_DCCSCAN_MINLENGTH       192   // Check Minimum Length in 10th inches
                                          // Default is 40 for 4 inches.
#define CFG_MICR_GAIN               193   // FOR CX30 ONLY:  CX30 Manual Gain Setting,
                                          // Active if CFG_MICR_AGC is zero.
#define CFG_MICR_GAIN_DEFAULT       100   // FOR CX30 ONLY:  100 percent MICR Gain

#define CFG_MICR_AGC                194   // FOR CX30 ONLY: 0 - Use Manual Gain Setting,
                                          //                1 - Let DCCAPI Self Adjust
                                          //                    CFG_SCAN_MODE_HOLD Only
#define CFG_MISC_LATE_JAM_TEST_CX30 195   //0 - Default, 1 - Disable Late CX30
                                          //    JAM Test in Scan & Return Mode

#define CFG_FRANK_MODE              196
#define CFG_FRANK_MODE_OFF            0   /* NO FRANKING on any document    */
#define CFG_FRANK_MODE_ON             1   /* ALWAYS FRANKING, every document*/
#define CFG_FRANK_MODE_MICR           2   /* FRANK if the MICR has the value*/
                                          /* set in CFG_FRANK_BAD_QTY       */
                                          /* or less MICR @'s.              */
                                          /*I.e., if CFG_FRANK_BAD_QTY is   */
                                          /*set to 0, the Magneticly read   */
                                          /*MICR must have 0 @'s.           */
                                          /*If want to use Magnetic/OCR MICR*/
                                          /*select CFG_FRANK_MODE_EXTERNAL and  */
                                          /*user determines validity of MICR*/
#define CFG_FRANK_MODE_EXTERNAL       3   /*USER selects whether to Frank or*/
                                          /*not by calling DCCSetFrank.     */
                                          /*NOTE:  in this mode, the scanner*/
                                          /*will hold the document UNTIL it */
                                          /*receives the command DCCSetFrank.*/
                                          /*USER determines conditions for   */
                                          /*FRANKING.                        */
#define CFG_FRANK_BAD_QTY           197
#define CFG_FRANK_RIGHT_MARGIN      198
#define CFG_FRANK_LENGTH            199
#define CFG_DCCSCAN_REAR_THRESHOLD  200   /* 0 - Default Edge Detection Threshold 600, */
                                          /* Otherwise valid 200 to 900 */
#define CFG_FIRMW_LOAD_MODE         201   /* TS240 ONLY:  When to download firmware. Default: 2 */
  #define CFG_FIRMW_LOAD_MODE_DEFAULT 2   /* DEFAULT VALUE */
  #define CFG_FIRMW_LOAD_MODE_NO      0   /* No Dowload.  IN-flash firmware is used */
  #define CFG_FIRMW_LOAD_MODE_ALWAYS  1   /* Always download Firmware */
  #define CFG_FIRMW_LOAD_MODE_NEWER   2   /* Download if firmware with greater file
                                             version */
  #define CFG_FIRMW_LOAD_MODE_DIFF    3   /* Download if firmware different */
#define CFG_FILE_WRITE_ALLOWED      202   /* Write EEPROM.DAT to temp file or not*/
                                          /*Saves 2 seconds on boot up if firmware */
                                          /*already downloaded. Default: 1    */
  #define CFG_FILE_WRITE_ALLOWED_DEFAULT   1
  #define CFG_FILE_WRITE_ALLOWED_OFF   0
  #define CFG_FILE_WRITE_ALLOWED_ON    1
#define CFG_DIAG_DIALOG_MODE        203   /* Control Debug Dialog */
  #define CFG_DIAG_DIALOG_MODE_NEVER     0  /* Never popup Dialog */
  #define CFG_DIAG_DIALOG_MODE_ALWAYS    1  /* Always popup Debug Dialog-Testing Only */
  #define CFG_DIAG_DIALOG_MODE_ARMED     2  /* show the dialog only if armed with Alt Shift Key */
  #define CFG_DIAG_DIALOG_MODE_SH_FOCUS  6  /* (Default) Show the Dialog on Shift and Focus */

   // Read Only Informational Values about Attached Scanner 10.03
#define CFG_RO_300DPI_ABLE           204   /* 1 - 300 DPI Supported, 0 - No */
#define CFG_RO_AUTO_FEEDER           205   /* 1 - AutoFeeder, 0 - DropFeeder */
#define CFG_RO_SCANBATCH_ABLE        206   /* 1 - ScanBatch Available, 0 - no */
#define CFG_RO_PRINT_CARTRIDGE_LOADED 207   /* 1 - Carriage Installed, 0 - no */
#define CFG_RO_SORTER_ABLE           208   /* 1 - Sorter Available, 0 - no */
#define CFG_RO_DIR_ENDORSEMENT       209   /* 1 - Right Side Feed, 0 - Left Side Feed */
#define CFG_RO_FRANKER_INSTALLED     210   /* 0 - No Franker, 1 - Franker */
#define CFG_RO_DOCS_IN_TRACK         211   /* When Batch scanning, max number of documents in track */


#define CFG_DCCSCAN_FIX_IMAGES       212   /* Run Filter on Dirty Images */

#define CFG_RESERVED_BS              213

#define CFG_NONCRITICAL_TIMEOUT      214

#define CFG_PRINTER_HEAD             215   /* Type of print head */
  #define CFG_PRINTER_HEAD_1LINES      0   /* Default for no printer or one lines of print (12 pixels)*/
  #define CFG_PRINTER_HEAD_4LINES      1   /* Four lines of print */


#define CFG_CMC7OCR_BLACK            216   /* CMC7 OCR Black Maximum       */

#define CFG_DEV_USDOUBLEFEED         217   /* New Sensors for BX7200 */

#define CFG_SORT_MODE                218   /* Sort mode for BX7200   */
                                           /* Modes 0-5 Testing.           */
  #define CFG_SORT_MODE_NO_CHANGE      0   /* Stay in current position     */
  #define CFG_SORT_MODE_A_NOW          1   /* All documents forced to A    */
                                           /* or 0 Pocket                  */
  #define CFG_SORT_MODE_B_NOW          2   /* All documents forced to B    */
                                           /* or 1 Pocket                  */
  #define CFG_SORT_MODE_FLIPNEXT       5   /* Alternate pockets            */
  #define CFG_SORT_MODE_FLIPIFFULL     6   /* CASCADE, ROLLING pocket.     */
                                           /* IF output pocket becomes full*/
                                           /* instead of erroring, will    */
                                           /* cascade or roll to next      */
                                           /* pocket.  Flip to next pocket */
                                           /* if current pocket is full.   */
  #define CFG_SORT_MODE_WAITTOSORT     8   /* Wait for sort decision, but  */
                                           /* next check starts as soon as */
                                           /* sort decision is made instead*/
                                           /* of waiting on item to get to */
                                           /* output pocket.               */
  #define CFG_SORT_MODE_DOCSORT        9   /* Like 8 above, but defaults   */
                                           /* to Pocket A or 0 if sort     */
                                           /* decision is not received in  */
                                           /* time.                        */
  #define CFG_SORT_MODE_STOPTOSORT    10   /* Wait for sort decision,      */
                                           /* (single doc non-pipelined).  */
                                           /* USER selects document pocket */
                                           /* WARNING:  All Feeding, etc.  */
                                           /* will stop till pocket        */
                                           /* selection is received.       */

#define CFG_MICR_RESAMPLE            219   /* Increase Gain - retest MICR  */

#define CFG_PRINTER_ECONOMY_MODE     220   /* 0= default: Column 1 & 2 = 600DPI            */
                                           /* 1= Same as Mode 0                            */
                                           /* 2= Column 3 & 4 = 600DPI                     */
                                           /* 3= Column 1 - 4 = 600 DPI redundant printing */
                                           /* 4= Column 1 = 300DPI                         */
                                           /* 5= Column 3 = 300 DPI                        */
#define CFG_IMAGE_FRONT_UV_THRESH    221   // 0 to 14, start with 13       */

#define CFG_CLEAR_HALT_BX7200        222   // Calling this function causes User
                                           // Halt on the BX7200 to be cleared
#define CFG_BX7200_DF_NOIMAGES       223   // If DF on BX7200, don't return images

#define CFG_RO_SCANNER_STATUS        224   // Actual Scanner Status - Snapshot --
                                           //   Many of these status are handle
                                           //   immediately so users can not 
                                           //   depend on some of them.  Valid
                                           //   one are marked by star. 
                                           //   BX7200, CX30, TS240 Only
    #define CFG_RO_CMDCOMPLETE      0x00000001 // Can mean a scan or eject complete
    #define CFG_RO_POWERON          0x00000002 // Scanner Power On Flag is Set
    #define CFG_RO_SCANNING         0x00000004 // Scanner Active Scanning Mode
    #define CFG_RO_ERROR            0x00000008 // Current Error Exists
    #define CFG_RO_PHOTOFEEDER      0x00000010 // Documents in Track - Not valid always
    #define CFG_RO_PHOTOSYNC        0x00000020 // A photo sensor is busy -- JAM if track is stopped
    #define CFG_RO_PRTHEAD          0x00000040 //*Print Cartridge is installed
    #define CFG_RO_SCANENABLE       0x00000080 // Scanner Active or waiting on check
    #define CFG_RO_RDTRACK          0x00000100 // Not Used
    #define CFG_RO_BUSY             0x00000200 // Scanner Busy
    #define CFG_RO_DOUBLEFEED       0x00000400 // Double Feed Sensor Active
    #define CFG_RO_PHOTOJAM         0x00000800 // Document in optics
    #define CFG_RO_INTERLOCK        0x00001000 // Scanner Door Open -- UnSafe to Scan
    #define CFG_RO_MODESEL          0x00002000 // CX30 Door Closed
    #define CFG_RO_PHOTOPOCKET      0x00004000 // Not Used
    #define CFG_RO_POCKET_FULL_0    0x00008000 //*BX7200 Pocket 0 full
    #define CFG_RO_POCKET_FULL_1    0x00010000 //*BX7200 Pocket 1 full
    #define CFG_RO_INTRACK          0x00020000 //*CX30 Doc InTrack
    #define CFG_RO_RESERVED1        0x00040000 // unused
    #define CFG_RO_RESERVED2        0x00080000 // unused
    #define CFG_RO_MICRRDY          0x00100000 // MICR Signal Ready
    #define CFG_RO_IMGFRDY          0x00200000 // Front Image Ready
    #define CFG_RO_IMGRRDY          0x00400000 // Rear Image Ready
    #define CFG_RO_RS232RDY         0x00800000 // unused
    #define CFG_RO_RDYFOREARLYSCAN  0x01000000 // Scanner Ready to Start Next Doc
    #define CFG_RO_DOCINBUFFER      0x02000000 // Not Used
    #define CFG_RO_WAITINGSORTDEST  0x04000000 // Waiting for Pocket
    #define CFG_RO_EARLYMICRRDY     0x08000000 // Early MICR Ready
    #define CFG_RO_USERHALTED       0x10000000 // BX7200 User Halted Button Pressed
    #define CFG_RO_RESERVED3        0x20000000 // unused
    #define CFG_RO_USERSTART        0x40000000 // BX7200 Start Button Pressed
    #define CFG_RO_DEVCONNECTED     0x80000000 // Scanner Connected

#define CFG_SOFT_IMAGETOOLONG        225       // BX7200 Software Image Too Long Test
                                               // 0 - Disable, 1 - Enable

#define CFG_SKIP_4L_DELAY            226       // 0 - Default - Delay 3 seconds
                                               //     on BUICInit so 4L cartridge
                                               //     can heat up.
                                               // 1 - No Delay

#define CFG_DF_ENDORSE               227       // 0 - Default, On BX7200 don't
                                               //     endorse on DF items, 1 - Endorse on
                                               //     DF items

#define CFG_RO_DCCSCAN_MICR_CHG      228       // 0 - No, 1 - Magnetic MICR Updated
                                               //     by MICR OCR (Valid only on BX7200 when
                                               //     sorting)

#define CFG_RO_SORT_POCKET           229       // 0 - Unknown, 1 - Outside, 2 - Inside
                                               //     (Valid only on BX7200 when sorting)

#define CFG_RO_UV_ABLE               230       // 0  - Scanner does not support UltraVialet
                                               // 1 - UV Scanner

#define CFG_MISC_DFNS_ONLY           231      

#define CFG_AUTO_EJECT_ON_JAM        232       // 0 - Off, 1 AutoEjectJam, 2 AutuEjectDF, 3 Both

#define CFG_USE_ALT_STRING_FONT      233       // 0 - Default: Normal 12 bit endorsement font
                                               // 1 - Alternate: 12 bit endorsement font

#define CFG_UV_GRAYFACTOR            234       // 0 - Dynamic
                                               // 1 - 1 to 1 (Default)
                                               // 2 to 8 - Lighten UV Image Up
              
#define CFG_UV_ABSBLACK              235       // Force UV To zero (black)

#define CFG_UV_OVER128               236       // Percentage UV Over 50% Lite
                                               // 0  - 100

#define CFG_UV_ONEPERCENT            237       // UV Graylevel at least 1% Lite
                                               //  0 - 255

#define CFG_BX7200_MIN_ENV_LENGTH    238       // Default to 210
#define CFG_BX7200_MAX_ENV_LENGTH    239       // Default to 245
#define CFG_BX7200_ENV_DF_MODE       240       // Default to 0 - off, 1 - on
#define CFG_BX7200_ENV_DF_SORT       241       // Default to 0 - off, 1 - on

#define CFG_UV_GAINPLUSMINUS         242       // Default to 0, -9 to 9 Gray Grain Fudge factor


#define CFG_JAMCHECKENABLE           310   /* BX7200:                         */
#define CFG_PLUNGERPARKTICKS         311   /* BX7200:  Determines size of gap */

#define CFG_SPECIALMODE              312   /* Special mode for TS240. Internal use only.                  */
  #define CFG_SPECIALMODENORMAL        0
  #define CFG_SPECIALMODEFAST          1
  #define CFG_SPECIALMODELONG          2

#define CFG_SINGLE_FEED_MODE         313   /* Opposite of CFG_MISC_SCANBATCH_ENABLE */

#define CFG_TRANSPORT_MODE           314   /* TS500 Transport only */
  #define CFG_TRANSPORT_CHECK          0
  #define CFG_TRANSPORT_ID             1
#define CFG_AA_MODE                  315   /* Auto Align:  On or Off, TS500         */

#define MAX_IMAGE_LENGTH              5000

/*-----------------02-18-97 12:18pm-----------------
  BUICSetParam - Allows the user to change scanner
      parameters and then write them out to the BUICSCAN.ini
      file.

  PARAMETERS:
      iParam  - Parameter to change.
      iValue  - Value to change the parameter to.

  RETURN:
      TRUE                    - Everything initialized correctly.
      B1000_SEND_CONFIG       - BUIC Scanner did not like the parameter
                                and returned an error.
      -1                      - Parameter was not in acceptable range.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICSetParam(int iParam, int iValue);

/*-----------------02-18-97 12:18pm-----------------
  BUICGetParam - Allows the user to get a scanner
      parameter.

  PARAMETERS:
      iParam  - Parameter to change.

  RETURN:
      xxxx                    - Value of the parameter iParam.  Get
                                it out of the parameter block.  No
                                inquiry called at this time.
      BUIC_ERROR_BADPARAM     - Parameter was not in acceptable range.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICGetParam(int iParam);

/*-----------------02-18-97 12:18pm-----------------
  BUICReadConfig - Read the configuration file whose name
      was passed to this function.  Set up the parameter block
      using the values defined in the configuration file.

  PARAMETERS:
      lpFileName  - Name of the configuration file and path.

  RETURN:
      1                       - File found and downloaded.
      2                       - File not found going to defaults.
      BUIC_ERROR_BADFILENAME  - File not found or at least unreadable.
      E_NO_SCANNER            - No scanner available or not yet initialized.

------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICReadConfig(LPSTR lpFilename);

/*-----------------02-18-97 12:18pm-----------------
  BUICWriteConfig - Write a configuration file using
      the values in the parameter block.

  PARAMETERS:
      lpFileName  - Name of the configuration file and path.

  RETURN:
      TRUE                    - Everything okay.
      BUIC_ERROR_BADFILENAME  - File not found or at least unwritable.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICWriteConfig(LPSTR lpFilename);

/*-----------------02-18-97 12:18pm-----------------
  BUICScan - Scan one check and place the image
      in the files named by the passed parameters.
      iJobType specifies which images (information)
      is captured and stored.

  PARAMETERS:
      iJobType    -
                     1 - Front
                     2 - Back
                     3 - Front and Back
                     4 - MICR
                     5 - Front and MICR
                     6 - Back and MICR
                     7 - Front, Back and Micr
      lpFront     -  File name for front of the check image.
      lpLenFront  -  Length of the file (ASCII) for the front of the check image.
      lpBack      -  File name for back of the check image.
      lpLenBack   -  Length of the file (ASCII) for the back of the check image.
      lpCode      -  File name for MICR of the check.
      lpLenCode   -  Length of the file (ASCII) containing the MICR.

  RETURN:
      TRUE                    - Everything okay.
      BUIC_ERROR_NOINIT       - Have not initialized the scanner
                                before starting this scan.
      BUIC_ERROR_BADJOB       - Job type not within range of known types.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICScan(int iJobType,
                            LPSTR lpFront, LPSTR lpLenFront,
                            LPSTR lpBack, LPSTR lpLenBack,
                            LPSTR lpCode, LPSTR lpLenCode);

/*-----------------02-18-97 12:18pm-----------------
  BUICScanMemory - Scan one check and place the image
      in the memory specified by the passed parameters.
      iJobType specifies which images (information)
      is captured and stored.

  PARAMETERS:
      iJobType    -
                     1 - Front
                     2 - Back
                     3 - Front and Back
                     4 - MICR
                     5 - Front and MICR
                     6 - Back and MICR
                     7 - Front, Back and Micr
      lpFront     -  File name for front of the check image.
      lpLenFront  -  Length of the file (ASCII) for the front of the check image.
      lpBack      -  File name for back of the check image.
      lpLenBack   -  Length of the file (ASCII) for the back of the check image.
      lpCode      -  File name for MICR of the check.
      lpLenCode   -  Length of the file (ASCII) containing the MICR.

  RETURN:
      TRUE                    - Everything okay.
      BUIC_ERROR_NOINIT       - Have not initialized the scanner
                                before starting this scan.
      BUIC_ERROR_BADJOB       - Job type not within range of known types.

--------------------------------------------------*/
/*-----------------06-22-98 11:29am-----------------
 Eight byte header preceding image in memory.  When
 the image is returned from a Memory Scan, this eight
 byte image will be placed at the beginning of the
 memory and the image will immediately follow the
 image.  The eight byte header gives a brief description
 of the image size and makeup.
 --------------------------------------------------*/
#ifndef BUICMemHdrDEF
struct BUICMemHdr {
       short  hdrImageWidth;    /* image width in pixels        */
       short  hdrImageLength;   /* image length in pixels       */
       short  hdrBitsPixel;     /* Bits per pixel               */
       short  hdrDPI;           /* DPI used while reading image */
       };
#define BUICMemHdrDEF
#endif

CFUNCTIONSDLLCALLS int PASCAL BUICScanMemory(int iJobType,
                            char  *lpFront, LPLONG lplLenFront,
                            char  *lpBack, LPLONG lplLenBack,
                            LPSTR lpCode, LPINT lpiLenCode);

/*-----------------02-18-97 12:18pm-----------------
  BUICScanGray - Scan one check in gray scale mode
      and place the image in the files named by the
      passed parameters.  iJobType specifies which
      images (information) is captured and stored.

  PARAMETERS:
      iJobType    -
                     1 - Front
                     2 - Back
                     3 - Front and Back
                     4 - MICR
                     5 - Front and MICR
                     6 - Back and MICR
                     7 - Front, Back and Micr
      lpFront     -  File name for front of the check image.
      lpLenFront  -  Length of the file (ASCII) for the front of the check image.
      lpBack      -  File name for back of the check image.
      lpLenBack   -  Length of the file (ASCII) for the back of the check image.
      lpCode      -  File name for MICR of the check.
      lpLenCode   -  Length of the file (ASCII) containing the MICR.
      iImageFormat-  Select image format for front/back file (BMP, JPEG Gray)
                     Use FORMAT_BMP and FORMAT_JPEGG.

  RETURN:
      TRUE                    - Everything okay.
      BUIC_ERROR_NOINIT       - Have not initialized the scanner
                                before starting this scan.
      BUIC_ERROR_BADJOB       - Job type not within range of known types.
      BUIC_GRAYFILE           - Gray scale not supported.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICScanGray(int iJobType,
                            LPSTR lpFront, LPSTR lpLenFront,
                            LPSTR lpBack, LPSTR lpLenBack,
                            LPSTR lpCode, LPSTR lpLenCode,
                            int   iImageFormat);

/*-----------------02-18-97 12:18pm-----------------
  BUICScanMemoryGray - Scan one check and place the image
      in the memory specified by the passed parameters.
      iJobType specifies which images (information)
      is captured and stored.

  PARAMETERS:
      iJobType    -
                     1 - Front
                     2 - Back
                     3 - Front and Back
                     4 - MICR
                     5 - Front and MICR
                     6 - Back and MICR
                     7 - Front, Back and Micr
      lpFront     -  File name for front of the check image.
      lpLenFront  -  Length of the file (ASCII) for the front of the check image.
      lpBack      -  File name for back of the check image.
      lpLenBack   -  Length of the file (ASCII) for the back of the check image.
      lpCode      -  File name for MICR of the check.
      lpLenCode   -  Length of the file (ASCII) containing the MICR.
      iImageFormat-  Select image format for front/back file (BMP, JPEG Gray)
                     Use FORMAT_BMP and FORMAT_JPEGG.

  RETURN:
      TRUE                    - Everything okay.
      BUIC_ERROR_NOINIT       - Have not initialized the scanner
                                before starting this scan.
      BUIC_ERROR_BADJOB       - Job type not within range of known types.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICScanMemoryGray(int iJobType,
                            char  *lpFront, LPLONG lplLenFront,
                            char  *lpBack, LPLONG lplLenBack,
                            LPSTR lpCode, LPINT lpiLenCode,
                            int   iImageFormat);

/*-----------------June 4, 2010-----------------
  DCCScanLong - Scan one document on the TS240 in
    long document mode and place in image in either
    the front file name specified or the front file
    image memory specified.  Image will be saved in
    iFormatComp (format compression) compression format.
    MAXIMUM:  28800 Pixels (144 Inches) * 864 Pixel (4.2 inches) x 200 DPI

  PARAMETERS:
      sFrontFileName - File name for front image or NULL.
      pcFrontImage   - Memory pointer to put front image OR NULL.
      lpFront        - File name for front of the check image.
      iFormatComp    - Compression format.  ONLY FORMAT_TIFF and FORMAT_JPEGG

  RETURN:
      TRUE                    - Everything okay.
      BUIC_ERROR_NOINIT       - Have not initialized the scanner
                                before starting this scan.
      BUIC_ERROR_BADJOB       - Job type not within range of known types.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCScanLong(char *sFrontFileName, char *pcFrontImage,
    long *plFrontFileSize, int iFormatComp);

/*-----------------02-18-97 12:18pm-----------------
  BUICCompressImage - Compress image.

  PARAMETERS:
      psFileName  - Pointer to file name to store image.
      pchugeImage - Pointer to image stored in memory to be compressed.

  RETURN:
      TRUE                    - Everything okay.
      BUIC_ERROR_IMAGE_TYPE   - Only support 1 bit per pixel at this time.
      BUIC_ERROR_IMAGE_TYPE   - Image must be have dimensions greater than 0

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICCompressImage(char *psFileName, char  *pchugeImage);

/*-----------------02-18-97 12:18pm-----------------
  BUICCompressImageGray - Compress image grayscale.

  PARAMETERS:
      psFileName  - Pointer to file name to store image.
      pchugeImage - Pointer to image stored in memory to be compressed.
      iImageFormat- Select image format for front/back file (BMP, JPEG Gray)
                     Use FORMAT_BMP and FORMAT_JPEGG.

  RETURN:
      TRUE                    - Everything okay.
      BUIC_ERROR_IMAGE_TYPE   - Only support 1 bit per pixel at this time.
      BUIC_ERROR_IMAGE_TYPE   - Image must be have dimensions greater than 0

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICCompressImageGray(char *psFileName,
    char  *pchugeImage, int iImageFormat);

/*-----------------07-17-97 04:22pm-----------------
  funcFindBUICScanner - Does a SCSI inquiry command
      of all adapters and target ID's until it finds
      a BUIC scanner.

  PARAMETERS:
      wNumAdapters    Number of SCSI Host adapters on
                      system.

  RETURN:
      NONE

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int funcFindBUICScanner(unsigned int wNumSCSIAdapters,BYTE *pbAdapterID,
    BYTE *pbTargetID);


/*--------------------------------------------------------------
   This method of debug does not really work, but is left for
   backward compatibility.
---------------------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICFlashImage(HWND hwnd,char  *lpImage,int ClearScreen, int Scale);
#define BUIC_DISPLAYSCALE_100   1
#define BUIC_DISPLAYSCALE_FIT   2

/*--------------------------------------------------------------
   This method of debug does not really work, but is left for
   backward compatibility.
---------------------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICRotateImage(char  *lpImage,char  *lpNewImage, int Direction);
#define BUIC_ROTATE_RIGHT   1
#define BUIC_ROTATE_LEFT    2

/***************************************************************************
*                                                                          *
*  This function start the simple image child window.  The user            *
*  must pass the parent window, and associated window number.              *
*                                                                          *
*     Return:  0 OKAY, Other Error                                         *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL  BUICStartImageWindow(
   HWND hWnd,                          /* Parent Containing Window */
   short Window);                      /* Either 1 or 2            */


/***************************************************************************
*                                                                          *
*  This function closes the Image Window and releases system resources.    *
*                                                                          *
*     Return:  0 OKAY                                                      *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL  BUICCloseImageWindow(
   short Window);                      /* Either 1 or 2            */


/***************************************************************************
*                                                                          *
*  This the image window was started as a child window, then this call will*
*  force the child window to fill it's parent window.  This function is    *
*  called when the parent window is sized.                                 *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL  BUICSizeImageWindow(
   short Window);                      /* Either 1 or 2            */
CFUNCTIONSDLLCALLS int PASCAL BUICForceImageDisplay(int Window);

/***************************************************************************
*                                                                          *
*  This function specifies which image should be displayed and page.       *
*  Page Number is 1 to GetTiffPages().                                     *
*                                                                          *
*  Return:     0 OKAY,                                                     *
*              Negative - General Error                                    *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL  BUICSetImageMultPage(
   char *InputFile,             /* File Name */
   short Page,                      /* Page in File, 1 is first page */
   short Window);                   /* Either 1 or 2            */

/***************************************************************************
*                                                                          *
*  This function copies a file.                                            *
*                                                                          *
*  Return:     0 OKAY                                                      *
*              Negative - General Error                                    *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL  BUICCopyFile(char *InputFile,
   char *OutputFile);


/***************************************************************************
*                                                                          *
*  This function takes a TIff image and appends the second image onto the  *
*  file.                                                                   *
*                                                                          *
*  Return:     0 OKAY                                                      *
*              Negative - General Error                                    *
*                                                                          *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL  BUICCombineTIFFS(char *InputFile,
   char *AppendFile);


/***************************************************************************
*                                                                          *
*  This function takes the specified area out of an image and creates a new*
*  smaller image with a white margin around the image.  Margin is in percent
*  so under 5 percent is recomended.                                       *
*                                                                          *
*  Return:     0 OKAY                                                      *
*              Negative - General Error                                    *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL  BUICCropFile(char *InputFile,
      char *OutputFile, short Margin);


/***************************************************************************
*                                                                          *
*  Interface to handle multiple page tiffs.                                *
*                                                                          *
*  Return:     0 OKAY                                                      *
*              Negative - General Error                                    *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL  BUICGetTiffPages(char *InputFile);

/***************************************************************************
*  BUICGetMicrLine                                                         *
*                                                                          *
*  Get MICR line from TIFF file (Black/White or Bitonal image only).       *
*  Valid only if MICR was stored in comment field of TIFF file.            *
*                                                                          *
*  Return:     0                   - OKAY, MICR returned                   *
*              BUIC_ERROR_GET_MICR - No MICR Found                         *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL  BUICGetMicrLine(char *InputFile, short Page,
   char *MicrLine, short MicrLineSize);

/***************************************************************************
*  BUICSetMicrLine                                                         *
*                                                                          *
*  Set MICR line in a TIFF file (Black/White or Bitonal image only).       *
*  MICR will be stored in a comment field of TIFF file.                    *
*                                                                          *
*  Return:     0                        - OKAY, MICR returned              *
*              BUIC_ERROR_SAME_FILENAME - Input and output file same       *
*              BUIC_ERROR_IMAGETYPE     - Not a TIff File                  *
*              BUIC_ERROR_SETTING_MICR_TAG                                 *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL BUICSetMicrLine(char *InputFile, short Page,
   char *MicrLine, short MicrLineSize, char *OutputFile);

/***************************************************************************
*  BUICUpdateMicrLine                                                         *
*                                                                          *
*  Update or set MICR line in a TIFF file (Black/White or Bitonal image only).       *
*  MICR will be stored in a comment field of TIFF file.                    *
*                                                                          *
*  Return:     0                        - OKAY, MICR returned              *
*              BUIC_ERROR_SAME_FILENAME - Input and output file same       *
*              BUIC_ERROR_IMAGETYPE     - Not a TIff File                  *
*              BUIC_ERROR_SETTING_MICR_TAG                                 *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS short PASCAL BUICUpdateMicrLine(char *InputFile,
   char *MicrLine, short MicrLineSize);


/*-----------------07-17-97 04:22pm-----------------
  BUICGetScannerInfo - Get the vendor, product, and
      release of the SCSI device located at the
      adapter and target ID specified.  Create and
      display a Message Box if requested.

  PARAMETERS:
      bAdapterID      Pointer to the configured Adapter ID.
                      funcFindBUICScanner will look at this
                      SCSI address first, then search.
      bTargetID       Pointer to the configured target ID.
                      funcFindBUICScanner will look at this
                      SCSI address first, then search.
      *pcVendor       Pointer to address to return vendor
                      information.
      *pcProduct      Pointer to address to return product
                      information.
      *pcRelease      Pointer to address to return release
                      information.

  RETURN:
      BUIC1000              BUIC 1000 Scanner found
      TS400                 DST Teller Scanner found
       0                    Information for device found and returned.
      BUIC_ERROR_NOINIT     Invalid adapter or target ID, SCSI error.
      BUIC_ERROR_NODEVICE   No device found at specified location.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICGetScannerInfo(
    BYTE *pbAdapterID, BYTE *pbTargetID, char *pcVendor,
    char *pcProduct, char *pcRelease, int iMessageBox);

/*-----------------02-18-97 12:18pm-----------------
  funcTS400SetPrint - Function to set the requested
      ink jet printer value for the string or BMP file
      to print.

  PARAMETERS:
      iParameter    - Parameter to set.
            String   --- CFG_IJPRINTER_PRINTSTRING
            // Teller TS400 and BUIC1500 ONLY
            FileName of BMP ---  CFG_IJPRINTER_BMPFILENAME
            // Original Teller TS400
            TBPARAM_PRINT_IJSTRING 60  // Print IJ string
      iPosition     - Starting horizontal position (in printer pixels) for
                      the new string.
      pbInputString - If iParameter is CFG_IJPRINTER_PRINTSTRING, then
                      pbInputString is the string to print.  If
                      iParameter is CFG_IJPRINTER_BMPFILENAME, then
                      pbInputString is the file name of the BMP file to

         Old Param Names:
            TBPARAM_PRINT_STRING
            TBPARAM_PRINT_FILENAME

  RETURN:
      -1          -  Value out of range for the parameter requested.
       0 or 1     -  Value set for the parameter requested.

  ACTION:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS400SetPrint(int iParameter, int iInputValue,
    unsigned char *pbInputString);

/*-----------------02-18-97 12:18pm-----------------
  funcTS400SetSorter - Function to setup the sorter.

  PARAMETERS:
      iSortAlgorithm  - Sorter algorithm to select.
        TPARAM_SORTER_ALG_NONE      - None
        TPARAM_SORTER_ALG_PRESENT   - If MICR is present and all characters
                                      are valid.
        TPARAM_SORTER_ALG_EQUAL     - MICR =  String1
        TPARAM_SORTER_ALG_NOT_EQUAL - MICR != String1
        TPARAM_SORTER_ALG_GT_EQUAL  - MICR >= String1
        TPARAM_SORTER_ALG_LT_EQUAL  - MICR <= String1
        TPARAM_SORTER_ALG_BETWEEN   - String1 < MICR < String2
        TPARAM_SORTER_ALG_OUTSIDE   - MICR < String1 OR MICR > String2
        TPARAM_SORTER_ALG_EQUAL1OR2 - MICR == String1 OR MICR == String2
        TPARAM_SORTER_ALG_NOTEQU1OR2- MICR != String1 AND MICR != String2
      pbString1                     - ASCII String1 used in sort comparison
      pbString2                     - ASCII String2 used in sort comparison

  RETURN:
       BUIC_ERROR_BADPARAM -  iSortAlgorithm not valid.
       0 or 1     -  Value set for the parameter requested.

  ACTION:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS400SetSorter(int iSortAlgorithm,
    unsigned char *pbSortString1, unsigned char *pbSortString2);

/*-----------------02-18-97 12:18pm-----------------
  funcTS400SetLoadFont - Function to set the requested
      FONT File Name.

  PARAMETERS:
      iParameter  - Not used.
      iInputValue - Not used.
      pbInputFontFileName - ASCII string of Font file name complete
          with drive, path, filename and extension.


  RETURN:
       Error code (negative value)
       0 or 1     -  Value set for the parameter requested.

  ACTION:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS400SetLoadFont(int iParameter,
    int iInputValue, unsigned char *pbInputFontFileName);

/*-----------------02-18-97 12:18pm-----------------
 funcTS400ScanReadInit - This function sets up the
    scan by checking for operational errors, configuring
    the system, verifying a check is present, and
    allocating the necessary memory for the scan.

  PARAMETERS:
      NONE

  RETURN:
      0                       -
      Error < 0               - Error encountered while executing.
--------------------------------------------------*/
/*--------------------------------------------------------------
   This method of debug does not really work, but is left for
   backward compatibility.
---------------------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS400ScanReadInit(void);

/*-----------------02-18-97 12:18pm-----------------
 funcTS400ScanRead - This function reads in one
    document (check) from the TS400 scanner.

  PARAMETERS:
      iJobType          - 7 is front, back, and MICR.  Tells components
                          to return from front, back, and MICR.
      plFrontFileSize   - Pointer to return size of pcFrontFileName file
                          after image compression.
      plBackFileSize    - Pointer to return size of pcBackFileName file
                          after image compression.
      piCodeLine        - Pointer to location to return MICR (magnetic code).
      piCodeLineSize    - Pointer to location to return size of MICR
                          (magnetic code).
      pcFrontFileName   - File name of the image of the front of the check.
      pcBackFileName    - File name of the image of the back of the check.
      pchOutFrontImage  - Output image of the front with header.
      pchOutBackImage   - Output image of the back with header.
      iMemoryFormat     - 1 if returning image in memory or 0 if written to file
      iImageFormat      - 0 is black and white (bitonal) or FORMAT_BMP or
                          FORMAT_JPEG.  Valid only for file writing.

  RETURN:
      0                       -
      Error < 0               - Error encountered while executing.
--------------------------------------------------*/
/*--------------------------------------------------------------
   This method of debug does not really work, but is left for
   backward compatibility.
---------------------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS400ScanRead(
    int           iJobType,
    long          *plFrontFileSize,
    long          *plBackFileSize,
    char          *pcCodeLine,
    int           *piCodeLineSize,
    char          *pcFrontFileName,
    char          *pcBackFileName,
    char          *pchOutFrontImage,
    char          *pchOutBackImage,
    int           iMemory,
    int           iImageFormat);

/*-----------------02-18-97 12:18pm-----------------
 funcTS400ScanReadExit - This function deallocates
      the memory for the scan.

  PARAMETERS:
      NONE

  RETURN:
      0                       -
      Error < 0               - Error encountered while executing.
--------------------------------------------------*/
/*--------------------------------------------------------------
   This method of debug does not really work, but is left for
   backward compatibility.
---------------------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS400ScanReadExit(void);
/*-----------------02-18-97 12:18pm-----------------
  funcTS400GetScannerRunInfo - Returns SCSI information about
     the scanner vendor, product and release information as well
     as more indepth information about the approximate number of
     checks read and the number of minutes working.

  PARAMETERS:
      pstScannerInfo          - Structure to return Vendor, Product,
                                Release, Adapter ID, Target ID,
                                working minutes and documents.

  RETURN:
      0                       -
      Error < 0               - Error encountered while reading EE data.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS400GetScannerRunInfo(
	unsigned int *puiWorkMinutes, unsigned int *puiNumDocs);

/*-----------------02-18-97 12:18pm-----------------
  BUICEjectDocument - Eject document from TS400 Scanner or BUIC 1500.

  PARAMETERS:
      NONE

  RETURN:
      TRUE                    - Everything okay.
      EJECT_ERR               - Eject document command had error.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICEjectDocument(void);
/*-----------------02-18-97 12:18pm-----------------
  BUICEjectPocket - Eject document from TS400 Scanner or BUIC 1500.

  PARAMETERS:
      IF IN SCAN_MODE_FORWARD
      iDirection              = 0 is forward
      IF IN SCAN_MODE_REVERSE
      iDirection              = 1 is forward
                                0 is reverse
      IF IN SCAN_MODE_HOLD
      iDirection              = 1 is forward
                                0 is reverse
                                3 is kiosk
      iPocket                 = 0

  RETURN:
      TRUE                    - Everything okay.
      EJECT_ERR               - Eject document command had error.

--------------------------------------------------*/
#define EJECT_FORWARD 1
#define EJECT_REVERSE 0
#define EJECT_KIOSK   3
CFUNCTIONSDLLCALLS int PASCAL BUICEjectPocket(int iDirection, int iPocket);

CFUNCTIONSDLLCALLS int PASCAL BUICClearDocument(void);
/*-----------------01-21-99 02:36pm-----------------
 Complete acquisition when Host is sorting documents
 by selecting pocket for check and ejecting check.
 Pocket 1 and Pocket 0.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcSetPocket(int iPocket);
CFUNCTIONSDLLCALLS int PASCAL TS400SetPocket(int iPocket);
CFUNCTIONSDLLCALLS int PASCAL BX7200SetPocket(int iDocument, int iDestinationPocket);

/*-----------------04-08-98 11:07am-----------------
 funcLoadPrinterFont - Load font from font file
    to TS400 memory for use with dynamic
    printing BMP string.
 Parameters:
    pcPrinterFontFileName - Path and file name for
        a font file to upload to TS400 flash memory.
  Return:
    0 >=    Printer font file uploaded to TS400
            flash memory or not a TS400.
 E_OPEN_FONT_FILE - Incorrect name for font file,
            font file does not exist, or font file
            is invalid.
     SCSI_ERRORS - Errors while talking with SCSI
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcLoadPrinterFont(char *pcPrinterFontFileName);
/*-----------------04-08-98 11:07am-----------------
 funcLoadPrinterString - Load printer string to
    to TS400 memory for use with dynamic
    printing BMP string.  Must have uploaded font
    previously.
 Parameters:
    shPosition - Position to start uploading printer
        string.
    psString   - String to send to printer for endorsing.
    iMode      - Make 0 at this time.
  Return:
    0 >=    Printer font file uploaded to TS400
            flash memory or not a TS400.
 E_OPEN_FONT_FILE - Incorrect name for font file,
            font file does not exist, or font file
            is invalid.
     SCSI_ERRORS - Errors while talking with SCSI
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcSendPrinterString(short shPosition,
    char *psString, int iMode);
/*-----------------07-17-97 04:22pm-----------------
  funcSetUpCallBack - Set Up Call Back Routine for
      notification when an Event has occurred.

  PARAMETERS:
      dwEvent      - Event for which notification is required
                     TS200_CB_EVENT_SCAN      0x04
                     TS200_CB_EVENT_MICR      0x0100000
                     TS200_CB_EVENT_FRONT     0x0200000
                     TS200_CB_EVENT_BACK      0x0400000
                     TS200_CB_EVENT_VBMICR    0x40000000
                     TS200_CB_EVENT_USERSTART 0x20000000


                     OUTPUT_CB_EVENT          0xFFFFFFFF
                     Can be OR'ed together for combined event, i.e.
                     0x0700000 (MICR, Front, Back) will cause a call back
                     when the front, back, and MICR are available.
                     NOTE:  For best efficiency and code operation
                      select the event on the list that occurs last
                      so the events have completed before calling BUICScan.
      funcImageCallBack - Function to be called when dwEvent occurs.

  RETURN:
       TRUE
       TS2_CALLBACK_FULL    Too Many Call back functions on queue.
                            Only one is probably necessary.

--------------------------------------------------*/
/*-----------------11/22/00 09:57am-----------------
 TS200 Call Back Functions for
 funcSetUpCallBack(unsigned long dwEvent, FARPROC funcImageCallBack);
 for dwEvent.
 Can be OR'ed together for combined event, i.e.
  0x0700000 (MICR, Front, Back) will cause a call back
  when the front, back, and MICR are available.

--------------------------------------------------*/
#define TS200_CB_EVENT_SCAN      0x04
#define TS200_CB_EVENT_MICR      0x0100000
#define TS200_CB_EVENT_FRONT     0x0200000
#define TS200_CB_EVENT_BACK      0x0400000
#define TS200_CB_EVENT_USERSTART 0x20000000
#define TS200_CB_EVENT_VBMICR    0x40000000

#define OUTPUT_CB_EVENT          0xFFFFFFFF  // Replace OutputDebugString
                                             // with Call Back

#ifndef LINUX
CFUNCTIONSDLLCALLS int PASCAL funcSetUpCallBack(
   unsigned int dwEvent, FARPROC funcImageCallBack);
#else
CFUNCTIONSDLLCALLS int PASCAL funcSetUpCallBack(
   unsigned int dwEvent, int *funcImageCallBack(unsigned long));
#endif
/*-----------------07-17-97 04:22pm-----------------
  funcTS200Update - Update the TS200 by writing
      configuration to scanner or enabling scanner.

  PARAMETERS:
      iOptions     - Bottom bit (0x01) enables scanner
                     (or if 0, disables scanner)
                     Second bit (0x02) updates configuration
                     to scanner.

  RETURN:
      TRUE

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS200Update(int iOptions);
/*-----------------07-17-97 04:22pm-----------------
  funcTS200GetMICR - When the MICR call back function
  has notified the application the MICR is available,
  this function may be used to recover the MICR.

  PARAMETERS:
      psMICR       - Character pointer to memory for
                     storing (or returning) the MICR.
      iMaxMICR     - Number of bytes of memory in psMICR
                     or number of bytes of MICR to return.

  RETURN:
      TRUE

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS200GetMICR(char *psMICR, int iMaxMICR);

/*-----------------02-18-97 12:18pm-----------------
  CheckEndorsementStart - Functions allocates memory to handle the
      BitMap being created.

  PARAMETERS:
      iScannerType
      iBMPLength --- Pixels at 200 dpi - Size of Endorsement width-wise
                     Usually around 400 to 1200.  The smaller the better
                     since it will generate a smaller BMP which can be
                     sent the scanner faster.

  RETURN:
      TRUE                           - Everything initialized correctly.
      CHECKENDORSEMENT_PARAM_ERROR   - Invalid Scanner Type
      CHECKENDORSEMENT_MEMORY_ERROR  - Memory Allocation Error
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL CheckEndorsementStart(int iScannerType, int iBMPLength);
/*-----------------02-18-97 12:18pm-----------------
  CheckEndorsementEnd - Function writes endorsement buffer to a BMP file
                        and releases memory allocated in CheckEndorsementStart

  PARAMETERS:
      iScannerType
      BMPFileName --- Name of BMP file being used.

  RETURN:
      TRUE                                - Everything initialized correctly.
      CHECKENDORSEMENT_PARAM_ERROR        - Bad iScannerType
      CHECKENDORSEMENT_ROTATE_ERROR       - Error rotating image - memory?
      CHECKENDORSEMENT_BMP_FILE_ERROR     - Error writing BMP - FileName?
      CHECKENDORSEMENT_MIRROR_ERROR       - Error mirroring image - memory?
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL CheckEndorsementEnd(int iScannerType, char *BMPFileName);
CFUNCTIONSDLLCALLS HANDLE PASCAL CheckEndorsementEndhDIB(int iScannerType);
/*-----------------02-18-97 12:18pm-----------------
  CheckEndorsementInvert - Invert the text in the Endorse Buffer.

  PARAMETERS:
      iMode          0 - Whole Buffer, 1 - Size of Last Text Inserted

  RETURN:
      0
      CHECKENDORSEMENT_MEMORY_ERROR  - Memory Allocation Error
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL CheckEndorsementInvert(int iMode);
CFUNCTIONSDLLCALLS int PASCAL CheckEndorsementDoubleWide(int iMode);

/*-----------------02-18-97 12:18pm-----------------
  CheckEndorsementText - Function converts text to BitMap using
      True Type Fonts.

  PARAMETERS:
      iScannerType -
      iTextHeight  - Height in pixels
      iXOffset     - String Offset in pixels - Space before first character
                     in the string.
      iYOffset     - Offset in pixels to move text up/down
      iBold        - Bold characters or Not.  TRUE(1)/FALSE(0).
      iItalic      - Italic characters or Not.  TRUE(1)/FALSE(0).
      Font         - Pointer to name of a FONT.
      String       - Pointer to string to be translated to a BMP file.

      BMPFileName --- Name of BMP file being used.

  General Information about BMP's for different Digital Check Supported Scanners

      TS300, TS400 and BUIC1500 - use a BMP that is 32 bits high.
      That means a single line of text would use a text height of 32.
      One could also add two high height text lines using 16 bits for each.

      TS200 and TS300EBS - use a BMP that has 16 bits of printable area.
      One should use 16 for the text height.  Half Height text is not an
      option.

      Text characters usually have areas on top and below each character
      which might not be used for most alphanumeric characters.  Therefore,
      one could specify a text height of 36 and assume the last 4 rows were
      not being used by the characters the operator was wanting to endorse.
      One can also specify a negative YOffset and try to clip off the top
      character area that was not used.  This assending and desending
      character areas will vary between fonts and text heights.  The user
      must test to verify good results.  If a smaller text height is used,
      the total text length will get smaller also.

      Examples:

         VW_CheckEndorsementText(TS200_ENDORSE, 18, 0, 0, 0, 0, "Haettenschweiler",
            "Data to be Converted to a BMP");

         would encode using a true type font, "Haettenschweiler", start
         the string at the start of the buffer.

         VW_CheckEndorsementText(TS400_ENDORSE, 36, 0, -6, 0, 0, "Arial",
            "Data to be Converted to a BMP");

         would encode using a true type font, "Arial", start
         the string at the start of the buffer and drop the top 6 scanlines
         of the font.

  RETURN:
      TRUE                                - Everything initialized correctly.
      CHECKENDORSEMENT_TEXT_CONVERT_ERROR - Bad Font, offset, or textheight
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL CheckEndorsementText(int iScannerType,
   int iTextHeight, int iXOffset, int iYOffset, int iBold,
   int iItalic, char *Font, char *String);

CFUNCTIONSDLLCALLS int PASCAL CheckEndorsementStaticText(int iScannerType,
   int iTextHeight, char *String);

/*-----------------02-18-97 12:18pm-----------------
  CheckEndorsementImage

  PARAMETERS:
      iScannerType -
      iXOffset     - String Offset in pixels - Space before first character
                     in the string.
      iYOffset     - Offset in pixels to move text up/down
      pbImageBuf   - DCC uncompressed image buffer

  General Information about BMP's for different Digital Check Supported Scanners

      The TS240SF uses a BMP 150 lines high.

  RETURN:
      TRUE                                - Everything initialized correctly.
      CHECKENDORSEMENT_TEXT_CONVERT_ERROR - Bad Font, offset, or textheight
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL CheckEndorsementImage(int iScannerType,
   int iXOffset, int iYOffset, char *pbImageBuf);

/*-----------------02-18-97 12:18pm-----------------
  GetScannerType - Return type of scanner.

  PARAMETERS:
      NONE

  RETURN:
      TRUE                    - Everything initialized correctly.
      < 0                     - No BUIC scanner available.
      BUIC 1000               BUIC1000              2
      BUIC 1500               BUIC1500              3
      TS400                   TS400OLD             10
      TS400                   TS400               400
      TS200                   TS200               200
      TS300                   TS300               300
      EBS TS300               TS300EBS            314  300 + 0x0E
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL GetScannerType(void);

/***************************************************************************
*   funcConvGrayImageEdgeDetectBW -- This function takes a Gray Scale image*
*     returned from BUICScanMemoryGray and converts it to a bitonal        *
*     (black/white) image using some advanced methods for conversion to    *
*     improve gray scale to bitonal conversion.                            *
*     pcImage is a pointer to the grayscale image returned from            *
*        BUICScanMemoryGray                                                *
*     pszFileName is the full output file name                             *
*     iEdgeThreshold is the Edge Detection Threshold to use.  On 4 bit     *
*        grayscale images a value of 600 works, on 8 bit grayscale images  *
*        a lower value of 500 seems to work well.                          *
*     iTwoD  if B0 (1) the Two-Diminsional Algorithm is used               *
*            if B1 (2) the background is sampled and an amount of          *
*                 image data is always added.                              *
*            if B2 (4) the background is sampled and a low                 *
*                 amount of image data is added.  Better for backs of      *
*                 checks.                                                  *
*            if B3 (8) the background is made darker than default.         *
*            if B4 (0x10) the background is made lighter than default.     *
*            if B5 (0x20) the MICRLine background is resampled.            *
*            if B6 (0x40) shadow lines are removed before compression.     *
*            if B7 (0x80) check image density                              *
*            if B8 (0x100) crop left edge                                  *
*                                                                          *
***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL funcConvGrayImageEdgeDetectBW(
   char *pcImage, char *pszFileName, int iEdgeThreshold, int iTwoD);
/*-----------------08/01/07 11:00am-----------------
 funcConvGrayImageImageArea - Function to convert a
 gray scale image into a black/white (bitonal) image
 using a sample pixel difference algorithm.
 Parameters:
    pcImage       - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
    pszFileName   - Path and File Name for output image.
    pcImageBW     - Optional Uncompressed B/W Image
    iOptions      - Optional Processing
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcConvGrayImageArea(
   char *pcImage, char *pszFileName, char *pcImageBW, int iOptions);
/*-----------------02-18-97 12:18pm-----------------
  funcTS400ClearPrint - Function to clear the requested
      ink jet printer value for the string or BMP file
      to print.

  PARAMETERS:
      iStartPosition- Starting horizontal position (in printer pixels) for
                      clear area. FOR TS400, TS300 ONLY.  TS200 will
                      clear print area.
      iEndPosition  - Ending horizontal position (in printer pixels) for
                      the clear area. FOR TS400, TS300 ONLY.  TS200 will
                      clear print area.

  RETURN:
      -<0         -  Various Errors.
       0 or 1     -  Print area cleared between iStartPosition
                     and iEndPosition.

  ACTION:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcTS400ClearPrint(int iStartPosition, int iEndPosition);
/*-----------------01/24/02 02:17pm-----------------
  DCCAPIVersion() - Function to return current version
   of BUICAP32.dll

  PARAMETERS:
      None

  RETURN:
      Version in form of xxx (520) for x.xx (5.20), i.e. version
      is multiplied by 100.

  ACTION:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCAPIVersion();
CFUNCTIONSDLLCALLS int PASCAL DCCAPIDate(char *cDate);
/*-----------------01/24/02 02:17pm-----------------
  DCCAPISupportedScanners() - Function to return the scanners
    supported by this DLL.

  PARAMETERS:
      None

  RETURN:
      IF the LSB (Bit 0) is set, BUIC 1000 supported. (0x0001)
      If Bit 1   (Bit 1) is set, BUIC 1500 supported. (0x0002)
      If Bit 2   (Bit 2) is set, TS400 supported.     (0x0004)
      If Bit 3   (Bit 3) is set, TS200 supported.     (0x0008)
      If Bit 4   (Bit 4) is set, TS300 supported.     (0x0010)
      If Bit 5   (Bit 5) is set, TS300EBS supported.  (0x0020)
      If Bit 6   (Bit 6) is set, TS220 supported.     (0x0040)
      If Bit 7   (Bit 7) is set, TS230 supported.     (0x0080)
      If Bit 8   (Bit 8) is set, TS440 supported.     (0x0100)
      If Bit 9   (Bit 9) is set, CX30 supported.      (0x0200)
      If Bit 10  (Bit 10) is set, TS240 supported.    (0x0400)
      If Bit 11  (Bit 11) is set, SB series supported.(0x0800)

  ACTION:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCAPISupportedScanners();
/*-----------------07-17-97 04:22pm-----------------
  BUICGetScannerSerialNumber - Get the serial number
      of the scanner, number of documents, and time.

  PARAMETERS:
      *pcSerialNumber    Pointer to serial number
      *puiDocumentNumber Pointer to number of documents
                         to the nearest 10th document.
                         I.e. at every tenth document
                         the counter is updated by 10.
      *puiTime           Pointer to time in Minutes.
                         I.e.  to nearest 10 minutes.

  NOTE:  SCANNER UPDATES NUMBER of DOCUMENTS and TIME
    in MINUTES randomly updated.  Possibly every minute
    but possibly even a longer or shorter interval.  Therefore,
    number of documents and minutes is only an
    approximation since it is updated randomly and is
    only to the nearest 10.

  RETURN:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICGetScannerSerialNumber(char *pcSerialNumber,
    unsigned int *puiDocumentNumber, unsigned int *puiTime);

/*-----------------03/22/00 02:16pm-----------------
 funcConvImageToFile - Function to convert a gray scale
 image to either another gray scale or black/white (bitonal)
 image changing the number of bits or scaling down the image
 by a factor of 2.
 Parameters:
    pcImage       - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
    iThreshold    - If switching to Black/White (bitonal),
                    then select a threshold.
                    NOTE:  0x00 is white and 0xFF is Black.
                    Start possibly with 0x80 which is
                    half way between white and black.
    iScale        - 1 ---- No scaling.
                    2 ---- Scale image down by a factor
                           of two in both horizontal and
                           vertical direction.
    iOutputBits   - 8 ---- Bits per pixel of output image (Gray Scale).
                    4 ---- Bits per pixel of output image (Gray Scale).
                    1 ---- Bits per pixel of output image (Black/White).
                    0 ---- No Image.
    iImageFormat  - FORMAT_BMP (4 or 8 bits) or FORMAT_JPEGG (4 or 8 bits)
                    or FORMAT_TIFF (1 bit).
    pszFileName   - Path and File Name for output image.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcConvImageToFile(char *pcImage, int iThreshold, int iScale,
    int iOutputBits, int iImageFormat, char *pszFileName);

/*-----------------03/22/00 02:16pm-----------------
 funcGetHistogram - function to get the histogram of all the
 values of gray scale in an image.
 Parameters:
    pcImage       - Input image.
    iMethod       - 0 - Quick --- 8 vertical lines.
                  - 1 - Full  --- Complete Image.
    plGrayBytes   - 256 byte array to hold the number of
                    bytes with value 0L, 1L, ... 255L.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcGetHistogram(unsigned char *pcImage, int iMethod, long *plGrayBytes);

/*-----------------02/17/03 02:20pm------------------------------------------
  BUICAPICheckDensity - function to return number of pixels on within the
   area of a check.  This density is a good indication of whether the
   image is too light or too dark and requires a re-scan.
   Parameters:
      BlackBits   - number of black pixels in center of check after
         funcConvGrayImageEdgeDetectBW when option (0x80) is turned on.
      TotalBits   - number of total pixels in center of check

  RETURN:
      0 to 100, where is the percentage of black bits present unless
         funcConvGrayImageEdgeDetectBW is not called and then the results
         is always zero.

      If the return value is 5 or lower, then the image might be too light
      and a return value of 15 or higher, might be too dark.  Image density
      can be affected by document type so these values might need to be
      adjusted to for typical document type.
---------------------------------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL BUICAPICheckDensity(int *BlackBits, int *TotalBits);

/***************************************************************************/
/*                                                                         */
/* FindE13BMicr  uses OCR techniques on a TIFF check image in a file       */
/*    to determine the MICR.                                               */
/*                                                                         */
/*    szCheckFileName - Full path to TIFF Group 4 Image                    */
/*    iPage         - Page Number where 1 is the first page.                */
/*                    Page number will always be 1, except for Multi-Page  */
/*                    TIFFs.                                               */
/*    iRotate       - 0 -   0 Degrees, 1 -  90 Degrees,                    */
/*                    2 - 180 Degrees, 3 - 270 Degrees.                    */
/*    szOCRMicr    - Buffer to return the MICR detected using OCR methods. */
/*                   This buffer should be 128 bytes minimally.            */
/*    szOCRConfidence  - Buffer to return the confidence level for each    */
/*                   OCR character detected.  Higher numbers mean more     */
/*                   confidence, low numbers mean low confidence.          */
/*                   This buffer should be 128 bytes minimally.            */
/*    NOTE:  szOCRMicr and szOCRConfidence can be passed to function       */
/*          VerifyMicr to compare and possibly correct MICR                */
/*          detected by hardware MICR recognition.                         */
/*                                                                         */
/*    Return:                                                              */
/*       0 Okay                                                            */
/*       1 Invalid File                                                    */
/*       2 Invalid Header                                                  */
/*       3 Resolution not 200 or Image not 120 Lines                       */
/*       4 Memory Allocation Error                                         */
/*       5 Image Decompression Error                                       */
/*       6 Less than 5 characters found, so quitting.                      */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL FindE13BMicr(char *szCheckFileName, int iPage,
   int iRotate, char *szOCRMicr, char *szOCRConfidence);
CFUNCTIONSDLLCALLS int PASCAL FindE13BMicrMaxHeight(char *CheckFileName, 
   int iPage, int iRotate, char *szMicrBuffer, char *szConfidenceBuffer, 
   int iOffset);

/***************************************************************************/
/*                                                                         */
/* FindE13BMicrMem used OCR techniques on a TIFF check image in memory  in */
/*   the DCCAPI bitonal image format to determine the MICR.                */
/*                                                                         */
/*   pMem        - Pointer to a DCCAPI bitonal image buffer.               */
/*   szOCRMicr    - Buffer to return the MICR detected using OCR methods.  */
/*                   This buffer should be 128 bytes minimally.            */
/*   szOCRConfidence  - Buffer to return the confidence level for each     */
/*                   OCR character detected.  Higher numbers mean more     */
/*                   confidence, low numbers mean low confidence.          */
/*                   This buffer should be 128 bytes minimally.            */
/*   NOTE:  szOCRMicr and szOCRConfidence can be passed to function        */
/*          VerifyMicr to compare and possibly correct MICR                */
/*          detected by hardware MICR recognition.                         */
/*                                                                         */
/*    Return:                                                              */
/*       0 Okay                                                            */
/*       1 Invalid File                                                    */
/*       2 Invalid Header                                                  */
/*       3 Resolution not 200 or Image not 120 Lines                       */
/*       4 Memory Allocation Error                                         */
/*       5 Image Decompression Error                                       */
/*       6 Less than 5 characters found, so quiting.                       */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL FindE13BMicrMem(char *pMem,
   char *szOCRMicr, char *szOCRConfidence);
CFUNCTIONSDLLCALLS int PASCAL FindE13BMicrMemMaxHeight(char *pMem,
   char *szMicrBuffer, char *szConfidenceBuffer, int iOffset);
CFUNCTIONSDLLCALLS int PASCAL FindCMC7MicrMem(char *pMem,
   char *szMicrBuffer, char *szConfidenceBuffer);

/***************************************************************************/
/* This function always returns a zero at this time.                       */
/*                                                                         */
/* VerifyMicr:                                                             */
/*   szMagneticMicr  - MICR returned from a scanner that reads MICR.       */
/*   szOCRMicr       - MICR returned from OCRing an image of a check.      */
/*   szOCRConfidence - Confidence levels on each value of the OCRMicr.     */
/*   szResults       - Using szMagneticMicr, szOCRMicr, and                */
/*                     szOCRConfidence, this function returns the most     */
/*                     accurate MICR it can determine.  Fine tuned for     */
/*                     DCC check scanners.                                 */
/*   iMaxMagneticErrors - Maximum number of errors in szMagneticMicr before*/
/*                   aborting VerifyMicr recognition comparisions.  If     */
/*                   szMagneticMicr has so many errors, it is assumed the  */
/*                   check is non correctable.                             */
/*   NOTE:  szOCRMicr and szOCRConfidence are from FindE13BMicr and        */
/*                    FindE13BMicrMem.                                     */
/*                                                                         */
/*    Return:                                                              */
/*       0                                                                 */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL VerifyMicr(char *szMagneticMicr,
   char *szOCRMicr,
   char *szOCRMicrConfidence, char *szResults, int iMaxMagneticErrors);
CFUNCTIONSDLLCALLS int PASCAL VerifyMicrCMC7(char *MagneticMicr,
   char *OCRMicr, char *OCRMicrConfidence,
   char *Results, int iMaxMagneticErrors);

#define VERIFIEDNOTFIXED          1
#define VERIFIEDLEADINGBANK       2
#define VERIFIEDFIXEDMISSED       4
#define VERIFIED25FIXED           8
#define VERIFIEDREVIEW            16
#define VERIFIEDSAME              256

/* This function helps debug the UniSoft Imaging MICR OCR and is not       */
/* available to BUICAP32.DLL (DCCAPI) users.                               */
CFUNCTIONSDLLCALLS int PASCAL MicrStatus(
   unsigned int *TotalChecksOCR,
   unsigned int *TotalChecksUnOCR,
   unsigned int *TotalChecksVerified,
   unsigned int *Total2or5Fixed,
   unsigned int *TotalOtherFixed,
   unsigned int *TotalNotFixed,
   unsigned int *VerifiedMask);

/***************************************************************************/
/*                                                                         */
/* LastCheckMicrStatus - Returns a confidence level on the last            */
/*                       document or check's MICR from OCRing.             */
/*                                                                         */
/*    Return:                                                              */
/*       0 Check has MICR Errors that need to be corrected                 */
/*       1 Check has possible MICR Errors                                  */
/*       2 Check has no known problems                                     */
/*       3 Check MICR has been verified                                    */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL LastCheckMicrStatus();

/***************************************************************************/
/*                                                                         */
/* ConvertRGBToGray  This function converts color data into grayscale data */
/*                                                                         */
/* pbInputImage  - pointer to a color image with DCCAPI header.            */
/* pbOutputImage - pointer to buffer to put the grayscale image.           */
/* iBitsOutput   - 1 or 4 or 8                                             */
/* iThreshold    - if iBitsOutput equals 1, theshold 0 - 255 for converting*/
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL ConvertRGBToGray(unsigned char *pbInputImage,
    unsigned char *pbOutputImage, int iBitsOutput, int iThreshold);
CFUNCTIONSDLLCALLS int PASCAL ReadStatistics(char *cFileName,
    int iOffset, char *cLogFile);
CFUNCTIONSDLLCALLS int PASCAL BUICGraySaturate(unsigned char *pcImage,
  int iMin, int iMax, unsigned int iSpread, unsigned int iHistagram);

/***************************************************************************/
/*                                                                         */
/* SetStandardCheckSizes                                                   */
/*                                                                         */
/* User selectable document sizes to verify.                               */
/*                                                                         */
/* iCount         Documents sizes to check                                 */
/* iWidth         An array of widthes                                      */
/* iHeight        An array of heights                                      */
/* i10thError     How much error to allow.                                 */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL SetStandardCheckSizes(
   int iCount, int *iWidth, int *iHeight, int i10thError);
CFUNCTIONSDLLCALLS int PASCAL SetStandardCheckSizeIndex(
   int iCount, int iIndex, int iWidth, int iHeight, int i10thError);
/***************************************************************************/
/*                                                                         */
/* IQAStatus                                                               */
/*                                                                         */
/* General series of test to verify the quality of a scanned document.     */
/*                                                                         */
/* char *pszFileName                Full Path to image                     */
/* int   iPage                      Page Number, 1 is first page           */
/* int   iUpdate                    if 1, update image after removing      */
/*                                     speckles                            */
/* char *pszOutFileName             Filename to store updated image        */
/* int   iIQATests                  Flag of IQA tests to preform           */
/*     (Additional Crop?)            IQACROP            1     0x0001       */
/*     (Remove 1x1)                  IQACLEAN1          2     0x0002       */
/*     (Remove 2x2)                  IQACLEAN2          4     0x0004       */
/*     (Remove 3x3)                  IQACLEAN3          8     0x0008       */
/*     (Remove 4x4)                  IQACLEAN4          16    0x0010       */
/*     (Check Document Size)         IQASTANDARDSIZE    32    0x0020       */
/*     (See SetStandardCheckSizes)                                         */
/*     (Test Skew)                   IQASKEW            64    0x0040       */
/*     (Test Bent Corners)           IQACORNERS         128   0x0080       */
/*     (Test Solid Lines)            IQALINES           256   0x0100       */
/*     (Test MICR Quality)           IQAMICRQUALITY     512   0x0200       */
/*     (Test Endorsement)            IQAENDORSEMENT     1024  0x0400       */
/*     (Test Density of Raw image)   IQADENSITY         2048  0x0800       */
/*     (Set Compressed Image Size)   IQACOMPRESSEDSIZE  4096  0x1000       */
/*     (Test CAR Present)            IQACARPRESENT      8192  0x2000       */
/*     (Test LAR Present)            IQALARPRESENT     16384  0x4000       */
/*     (Test To Present)             IQATOPRESENT      32768  0x8000       */
/*     (Test Date Present)           IQADATEPRESENT    65536  0x10000      */
/*     (Test Signature Present)      IQASIGNPRESENT   131072  0x20000      */
/*     (Test Top Edge Double Feed)   IQADOUBLETOPEDGE 33554432 0x02000000  */
/*                                                                         */
/* int   iMaxSpeckles               Allowable number of speckles, of more  */
/*                                        then fail this test              */
/* int   iMinMICRQuality            1 to 10 - If MICR Quality is less      */
/*                                     then fail this test                 */
/* int   iMaxCorner                 Maximum allowable number of pixels     */
/*                                     in a corner                         */
/* char *MagneticMicr               String containing Magnetic MICR        */
/* char *OCRMicr                    String containing OCR MICR             */
/* char *OCRMicrConfidence          String containing OCR MICR Confidense  */
/* int   iEndorsementTop            Top area to search for endorsement     */
/* int   iEndorsementBottom         Bottom area to search for endorsement  */
/* int   iEndorsementHeight         Size of Endorsement characters in pixel*/
/* int   iMinEndorsementCharacters  Minimum number of Endrosement chars    */
/* int  *iDocStatus                 An Array of 32 statuses (longs) where  */
/*   byte     0 - Crop Amount on all edges                                 */
/*            1 - Speckles                                                 */
/*            2 - Check Size (-1 is unknown)                               */
/*            3 - Skew Factor                                              */
/*            4 - Top Left Corner                                          */
/*            5 - Top Right Corner                                         */
/*            6 - Bottom Left Corner                                       */
/*            7 - Bottom Right Corner                                      */
/*            8 - Stuck Line Number                                        */
/*            9 - MICR Quality (1 to 10)                                   */
/*           10 - Raw Density (Percent of Black Pixels                     */
/*                                                                         */
/* Return:                                                                 */
/*    0 - Passed all tests preformed                                       */
/*    1 - Black Edge Remain and Image should be cropped                    */
/*    2 - Too many speckles                                                */
/*   32 - Non standard document size                                       */
/*   64 - Skewed                                                           */
/*  128 - Corner too large                                                 */
/*  256 - Stuck Bits Present                                               */
/*  512 - MICR Quality too low                                             */
/* 1024 - Endorsement Missing                                              */
/*                                                                         */
/***************************************************************************/
#define IQACROP            1
#define IQACLEAN1          2
#define IQACLEAN2          4
#define IQACLEAN3          8
#define IQACLEAN4          16
#define IQASTANDARDSIZE    32
#define IQASKEW            64
#define IQACORNERS         128
#define IQALINES           256
#define IQAMICRQUALITY     512
#define IQAENDORSEMENT     1024
#define IQADENSITY         2048
#define IQACOMPRESSEDSIZE  4096
#define IQACARPRESENT      8192
#define IQALARPRESENT     16384
#define IQATOPRESENT      32768
#define IQADATEPRESENT    65536     // 0x00010000
#define IQASIGNPRESENT   131072     // 0x00020000
#define IQAMEMOPRESENT   262144     // 0x00040000
#define IQABLOB          524288     // 0x00080000
#define IQACARBON       1048576     // 0x00100000
#define IQASTREAKS      2097152     // 0x00200000
#define IQAFOCUS        4194304     // 0x00400000
#define IQACOUNTINSIDE  8388608     // 0x00800000
#define IQACLEANSIDES  16777216     // 0x01000000
#define IQADOUBLETOPEDGE  33554432  // 0x02000000
#define IQACLEANSIDES2    67108864   // 0x04000000

CFUNCTIONSDLLCALLS int PASCAL IQAStatus(char *pszFileName, int iPage,
   int iUpdate, char *pszOutFileName,
   int iIQATests,
   int iMaxSpeckles, int iMinMICRQuality, int iMaxCorner,
   char *MagneticMicr, char *OCRMicr, char *OCRMicrConfidence,
   int iEndorsementTop, int iEndorsementBottom,
   int iEndorsementHeight, int iMinEndorsementCharacters,
   int *iDocStatus);
//
// VB Programmers might find the next two functions easier to use
// than the complex "C" IQAStatus(...)
//
   // BW Function Call
CFUNCTIONSDLLCALLS int PASCAL IQAStatusStart(char *pszFileName, int iPage,
   int iUpdate, char *pszOutFileName,
   int iIQATests,
   int iMaxSpeckles, int iMinMICRQuality, int iMaxCorner,
   char *MagneticMicr, char *OCRMicr, char *OCRMicrConfidence,
   int iEndorsementTop, int iEndorsementBottom,
   int iEndorsementHeight, int iMinEndorsementCharacters);
   // Grayscale/Color Function Call
CFUNCTIONSDLLCALLS int PASCAL IQAStatusGrayStart(char *pszFileName, int iPage,
   int iUpdate, char *pszOutFileName,
   int iIQATests,
   int iMaxSpeckles, int iMinMICRQuality, int iMaxCorner,
   char *MagneticMicr, char *OCRMicr, char *OCRMicrConfidence,
   int iEndorsementTop, int iEndorsementBottom,
   int iEndorsementHeight, int iMinEndorsementCharacters);
   // Return Status for either IQAStatusStart or IQAStatusGrayStart
CFUNCTIONSDLLCALLS int PASCAL GetIQAStatus(int iIndex);
//
// Verify that the front and back images of a single document are the same size
// Can pass the data as memory buffers or compressed b/w Images
//
CFUNCTIONSDLLCALLS int PASCAL IQAVerifySizeDocument(
   unsigned char *pDCCMemoryFront, char *pFrontFileName,
   unsigned char *pDCCMemoryBack,  char *pBackFileName,
   int      i10thError);
CFUNCTIONSDLLCALLS int PASCAL IQAStatusGray(char *pszFileName, unsigned char *pMem,
   int iIQATests,
   int iMaxSpeckles, int iMinMICRQuality, int iMaxCorner,
   char *MagneticMicr, char *OCRMicr, char *OCRMicrConfidence,
   int iEndorsementTop, int iEndorsementBottom,
   int iEndorsementHeight, int iMinEndorsementCharacters,
   int *iDocStatus);

/*-----------------December 2, 2004-----------------
  DCCScan - Scan one check and place the images
      in the files named by the passed parameters.

  PARAMETERS:
      pszFrontTiff    -  Front Image File Name or NULL
      pszBackTiff     -  Back Image File Name or NULL
      pszFrontJPEG    -  Front Image File Name or NULL
      pszBackJPEG     -  Back Image File Name or NULL
      pszMICR         -  MICR Code Buffer (80 bytes)
      piFinalImageQuality - Final Weighted Image Quality if Front Tiff Requested
                           -1 if test not completed
      piFinalContrast      -200 to 1000 if EdgeDetection or 2 to 13 if Simple
                            Thresholding
      piDocStatus          - Copy of IQA Status Data if not a NULL Pointer.


  Other Variables (existing):
      JPEG Quality                        CFG_MISC_JPEG_QUALITY
      NonEdgeDetectionFrontThreshold      CFG_IMAGE_FRONT_BW_THRESH
      Magnetic MICR Errors                CFG_MISC_MICR_VERIFY
      4 bit, 8 bit, or 24 bit capture     CFG_IMAGE_GRAY256LEVEL,
                                          CFG_IMAGE_FRONTCOLOR

  Other Variables (new):
      CFG_DCCSCAN_IQATESTS           146  //See IQAStatus Function Call
      CFG_DCCSCAN_STARTCONTRAST      147  //Usually around 450
      CFG_DCCSCAN_ENDCONTRAST        148  //Usually 450 to 900
      CFG_DCCSCAN_INCCONTRAST        149  //Usually 100 to 600
      CFG_JPEG_IMAGE_RESOLUTION      150  //100 or 200 dpi
      CFG_DCCSCAN_MAXSPECKLES        151  //Application Depend, Check 1200 to 2000
      CFG_DCCSCAN_MINMICRQUALITY     152  //MICR Quality 5 to 10
      CFG_DCCSCAN_MAXBENTCORNER      153  //Number of pixels in a bent corner 60 to 200
      CFG_DCCSCAN_MAXRAWDENSITY      154  //Usually 26 and up, but all business checks could be lower
      CFG_DCCSCAN_MAXTIFFIMAGESIZE   155  //Maximum allowable Tiff Image Size in Kilobytes.
      CFG_DCCSCAN_OPTIONS            156  //Option Bit Settings
                                          //1 - try multiple EdgeDetection Contrast
                                          //2 - try simple thresholding
                                          //4 - save the despeckled Image
                                          //8 - Save Grayscale/color images as BMPs
                                          //16 - Group 4 Filter
                                          //32 - Return Floyd Steinberg Tiff
                                          //       as Grayscale
                                          //64 - Force EdgeDetect Images to 3.1% Density
                                          //128- Return grayscale/color as
                                          //     uncompressed image with a
                                          //     BUICMemHdr
                                          //256- Check the back image for
                                          //     Image Quality Problems.
                                          //512- Reduced image by a 5th (300 to 240)
                                          //1024-Check upside down document
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCScan(
      char *pszFrontTiff, char *pszBackTiff,
      char *pszFrontJPEG, char *pszBackJPEG,
      char *pszMICR,
      int  *piFinalImageQuality,
      int  *piFinalContrast,
      int  *piDocStatus);

/*-----------------November 16, 2006-----------------
  DCCScanGetOCRMicr - Return Last OCR MICR and Confidence Buffer.

  PARAMETERS:
      pszMICR         -  OCR Code Buffer (80 Bytes)
      pszMICRConf     -  OCR Confidence Buffer (80 Bytes)
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCScanGetOCRMicr(
   char *pszMICR, char *pszMICRConf);

/*-----------------December 2, 2004-----------------
  DCCLoadImage - Load a Tiff or JPEG image into a standard uncompressed
   memory buffer as if scanned.  Good for testing and re-thresholding images.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCLoadImage(
   char *pszImageName, int iPage,
   char *pcDCCImage,   int iMaxImageSize);

/*-----------------March 3, 2005-----------------
  DCCTiffToBMP - Convert a Tiff G4 image into a single bit BMP.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCTiffToBMP(
   char *pszImageName, int iPage,
   char *pszBMPName,   int iWidth, int iHeight);
/***************************************************************************/
/*                                                                         */
/* DCCBatchPrintString  This function reads in font file if it has not     */
/*                      already been read in.  It then proceeds to download*/
/*                      and save the string for the first check or document*/
/*                      If a %d is located in the string then iStartCounter*/
/*                      and iIncrement are used to download a continously  */
/*                      incrementing/decrementing counter string during    */
/*                      batch scanning on a DCC batch scanner, that is in  */
/*                      batch mode.                                        */
/*        NOTE:  CFG_MISC_SCANBATCH_ENABLE must be true.                   */
/*                                                                         */
/* pcPrintString - pointer to string with a %d for changing a variable.    */
/*                 Ex:  Document %5d batch 12/12/2004                      */
/*                      Document 1:  Document     1, batch 12/12/2004      */
/*                      Document 2:  Document     2, batch 12/12/2004      */
/*                      .                                                  */
/*                      .                                                  */
/*                      .                                                  */
/*                      .                                                  */
/*                      Document 9:  Document     9, batch 12/12/2004      */
/* dwStartPosition - Start position on check                               */
/* dwMode          -  0                                                    */
/*                    CLEAR_PREVIOUS    1                                  */
/*                    INVERT_COLOR      2                                  */
/* iStartCounter   - Value for first document for %d value or insertion    */
/* iIncrement      - Value to change iStartCounter for each document       */
/*                   NOTE: iIncrement can be a negative value for          */
/*                     decrementing, iIncrement is only a name             */
/*                     i.e. -5 is decremnt by 5 while +5 is increment by 5 */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL DCCBatchPrintString(
    char *pcPrintString, DWORD dwStartPosition,
    DWORD dwMode, int iStartCounter, int iIncrement);
/***************************************************************************/
/*                                                                         */
/* DCCBatchPrintBMP  This function reads in font file if it has not     */
/*                      already been read in.  It then proceeds to download*/
/*                      and save the string for the first check or document*/
/*                      If a %d is located in the string then iStartCounter*/
/*                      and iIncrement are used to download a continously  */
/*                      incrementing/decrementing counter string during    */
/*                      batch scanning on a DCC batch scanner, that is in  */
/*                      batch mode.                                        */
/*        NOTE:  CFG_MISC_SCANBATCH_ENABLE must be true.                   */
/*                                                                         */
/* pcPrintBMP  - pointer to string with a %d for changing a variable.    */
/*                 Ex:  Document %5d batch 12/12/2004                      */
/*                      Document 1:  Document     1, batch 12/12/2004      */
/*                      Document 2:  Document     2, batch 12/12/2004      */
/*                      .                                                  */
/*                      .                                                  */
/*                      .                                                  */
/*                      .                                                  */
/*                      Document 9:  Document     9, batch 12/12/2004      */
/* dwStartPosition - Start position on check                               */
/* dwMode          -  0                                                    */
/*                    CLEAR_PREVIOUS    1                                  */
/*                    INVERT_COLOR      2                                  */
/* iStartCounter   - Value for first document for %d value or insertion    */
/* iIncrement      - Value to change iStartCounter for each document       */
/*                   NOTE: iIncrement can be a negative value for          */
/*                     decrementing, iIncrement is only a name             */
/*                     i.e. -5 is decremnt by 5 while +5 is increment by 5 */
/*  iTextHeight   -  Maximum 12 for TS230 (Might use up to 15 to skip      */
/*                      assending and desending characters                 */
/*  iXOffset      -  0                                                     */
/*  iYOffset      -  0                                                     */
/*  iBold         -  1 for bold; otherwise 0                               */
/*  iItalic       -  1 for italic; otherwise 0                             */
/*  pcFont        -  Font Name                                             */
/*  pcBMPFileName -  Writeable location for BMP file.                      */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL DCCBatchPrintBMP(
    char *pcPrintString, DWORD dwStartPosition,
    DWORD dwMode, int iStartCounter, int iIncrement,
    int iTextHeight, int iXOffset, int iYOffset, int iBold,
    int iItalic,     char *pcFont);

/*

   Virtual Endorsements

*/
CFUNCTIONSDLLCALLS int PASCAL DCCVirtualEndorsement(char *pcDCCImage, char *pcVirtualString,
   int iTextHeight, int iLeft, int iTop,
   int iBold, int iItalic, int iRotate, int iDitherMode,
   int iRed, int iGreen, int iBlue, char *szFont);
/***************************************************************************/
/*                                                                         */
/* DCCScanVirtualEndorsement This function virtually adds text to images.       */
/*                      If a %d is located in the string then iStartCounter*/
/*                      and iIncrement are used to download a continously  */
/*                      incrementing/decrementing counter string during    */
/*                      virtual endorsing a document scanned by DCCScan    */
/*                      NOTE:  Front, back image selectable and multiple   */
/*                      line capability.                                   */
/*                                                                         */
/* pcVirtualString  - pointer to string.  String can optionally include    */
/*                      new lines and/or a %d for changing a variable.     */
/*                    NOTE: Maximum characters with expansion is 128.      */
/*                 Ex:  Document %5d batch 12/12/2004                      */
/*                      Document 1:  Document     1, batch 12/12/2006      */
/*                      Document 2:  Document     2, batch 12/12/2006      */
/*                      .                                                  */
/*                      .                                                  */
/*                      .                                                  */
/*                      .                                                  */
/*                      Document 9:  Document     9, batch 12/12/2006      */
/*                   NOTE:  A Null pointer or a Empty string and dwMode    */
/*                          of 1 or 2 disables front/back.                 */
/* dwStartPosition - NOT USED AT THIS TIME                                 */
/* dwMode          -  0 ---  Disable Front and Back                        */
/*                    1 ---  Front side of document                        */
/*                    2 ---  Back side of document                         */
/*                    3 ---  Front and back side of document               */
/*                    NOTE:  Selecting 3 would put the same string on front*/
/*                           and back.  Call this function once for each   */
/*                           unique string for different strings for front */
/*                           and back.                                     */
/*                                                                         */
/*  iStartCounter - Value for first document for %d value or insertion    */
/*  iIncrement    - Value to change iStartCounter for each document       */
/*                   NOTE: iIncrement can be a negative value for          */
/*                     decrementing, iIncrement is only a name             */
/*                     i.e. -5 is decremnt by 5 while +5 is increment by 5 */
/*  iTextHeight   -  Pixel height of text.  Minimum of 12.                 */
/*                     E.g. for text 1/6 of an inch tall at 200 DPI image, */
/*                          a value of 200/6 equal approximately 32        */
/*  iLeft         - Starting position in pixels from left edge of check */
/*                    To use the right edge as a reference, multiple the   */
/*                    position by -1.                                      */
/*  iTop          - Starting position in pixels from top edge of check     */
/*  iBold         -  1 for bold; otherwise 0                               */
/*  iItalic       -  1 for italic; otherwise 0                             */
/*  iRotate       -  1 for 90, 2 for 180, 3 for 270, otherwise 0           */
/*  iDitherMode   -                                                        */
/*  iRed          - Shade of Red for Color Images                          */
/*  iGreenGray    - If Gray Scale, then shade of gray; if RGB, then shade  */
/*                  of Green.                                              */
/*  iBlue         - Shade of Blue for Color Images or RGB.                 */
/*  szFont        -  Font Name                                             */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL DCCScanVirtualEndorsement(char *pcVirtualString,
    DWORD dwStartPosition, DWORD dwMode,
    int iStartCounter, int iIncrement,
    int iTextHeight, int iLeft, int iTop,
    int iBold, int iItalic, int iRotate, int iDitherMode,
    int iRed, int iGreenGray, int iBlue, char *szFont);

/***************************************************************************/
/*                                                                         */
/* DCCBatchPrintLimit   If the internal counter equals or greater than the */
/*                      the limit value, then the counter is set to reset  */
/*                                                                         */
/* iLimit               Counter Rollover Limit. If same as iReset, it is   */
/*                         disabled.                                       */
/* iReset               Counter reset Limit.                               */
/*                                                                         */
/* Example:                                                                */
/*                                                                         */
/*  DCCBatchPrintLimit(100, 0);                                            */
/*  DCCBatchPrintString("ScanDemo by 15's:  %7d", 1200,                    */
/*                    0x100, 0, 15);                                       */
/*                                                                         */
/*  Would print     ScanDemo by 15's:         0      on the first check    */
/*                  ScanDemo by 15's:        15      on the second check   */
/*                  ScanDemo by 15's:        30      on the third check    */
/*                  ScanDemo by 15's:        45      on the fourth check   */
/*                  ScanDemo by 15's:        60      on the fifth check    */
/*                  ScanDemo by 15's:        75      on the sixth check    */
/*                  ScanDemo by 15's:        90      on the seventh check  */
/*                  ScanDemo by 15's:         0      on the eighth check   */
/*                  ScanDemo by 15's:        15      on the ninth check    */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL DCCBatchPrintLimit(int iLimit, int iReset);

/***************************************************************************/
/*                                                                         */
/* DCCBatchPrintNextCounter   Return Next Batch Counter Setting.           */
/*                                                                         */
/***************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL DCCBatchPrintNextCounter();

/*-----------------December 2, 2004-----------------
  DCCGetSinglePageSize - return the size of a Tiff G4 or JPEG image in memory.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCGetSinglePageSize(unsigned char *pImagePtr);
/*-----------------02-18-97 12:18pm-----------------
  DCCSetPocket - Function to set destination pocket for
    scanner models that have sorter mechanism (currently
    only the TS440).
  PARAMETERS:
      int iDestinationPocket
          0 - Sends document to the default pocket
          1 - Sends document to the auxilary pocket.

  RETURN:
      0          - No Scanner Present
      1          - Success
      Error code - Failure.

  ACTION:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCSetPocket(int iDestinationPocket);
/*-----------------02-18-97 12:18pm-----------------
  DCCCleanMode - Function to turn on and off the motor so
    a cleaning cards can be used to clean the TS230 and TS4120
    scanners.
  PARAMETERS:
      int iMode
          0 - Motors Stops -- Return to mode scanning mode.
          1 - Motors start turning - scanning disabled.

  RETURN:
      0          - No Scanner Present
      1          - Success
      Error code - Failure.

  ACTION:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCCleanMode(int iMode);

/*-----------------02-18-97 12:18pm-----------------
  DCCSetFrank - Function to frank the current document ONLY
    scanner models that have franking mechanism (currently
    only the TS240).  To frank continuously or based on valid MICR,
    use BUICSetParam or the ini file to set FrankMode, FrankQtyBad,
    FrankRightMargin, and FrankLength.
  PARAMETERS:
      NOTE:  FrankMode mode must be 3 -- USER SET, by either BUICSetParam
          or by ini file.
      int iAction  ---- FUTURE PARAMETER
      int iFrankRightMargin --- FUTURE PARAMETER
          Defines distance from Right or Trailing
          Edge to the franked stamp imprint in units of 0.1mm.
          The default value is 5mm (iFrankRightMargin = 50 [50 * 0.1mm = 5mm]).
          A minimum margin specified in the mechanical configuration would
          override tis margin if iFrankRightMargin is less than
          MechFrankMinimumMargin.
      int iFrankLength --- FUTURE PARAMETER
          Defines the length of the franked stamp imprint
          in units of 0.1mm. If the length exceeds the actual check length
          measure in firmware (FW), the FW should prevent franking in the
          MechFrankMinimumMargin.  The default value of FrankLength is
          the circumference of the franker roller which is 27.96mm.

  RETURN:
      0          - No Scanner Present
      1          - Success
      Error code - Failure.

  ACTION:

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCSetFrank(int iAction, int iFrankRightMargin, int iFrankLength);

/*-----------------03/22/00 02:16pm-----------------
 funcImage200To120 - Function to convert a gray scale
      4/8 bit image at 200 DPI to 120 DPI.
 Parameters:
    pcImage       - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
    pcOutImage    - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcImage200To120(
   char *pcImage, char *pcOutImage);

/*-----------------04/11/08 02:16pm-----------------
 funcImage300To240 - Function to convert a gray scale
      4/8 bit image at 300 DPI to 240 DPI.
 Parameters:
    pcImage       - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
    pcOutImage    - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcImage300To240(
   char *pcImage, char *pcOutImage);

/*-----------------03/22/00 02:16pm-----------------
 funcImage300To200 - Function to convert a gray scale
      4/8 bit image at 300 DPI to 200 DPI.
 Parameters:
    pcImage       - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
    pcOutImage    - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcImage300To200(
   char *pcImage, char *pcOutImage);
/*-----------------03/22/00 02:16pm-----------------
 funcImage300To100 - Function to convert a gray scale
      4/8/24 bit image at 300 DPI to 100 DPI.
 Parameters:
    pcImage       - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
    pcOutImage    - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcImage300To100(
   char *pcImage, char *pcOutImage);

/*-----------------03/22/00 02:16pm-----------------
 funcImage300To120 - Function to convert a gray scale
      4/8/24 bit image at 300 DPI to 120 DPI.
 Parameters:
    pcImage       - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
    pcOutImage    - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcImage300To120(
   char *pcImage, char *pcOutImage);

/*-----------------03/22/00 02:16pm-----------------
 funcImage200To100 - Function to convert a gray scale
      4/8/24 bit image at 200 DPI to 100 DPI.
 Parameters:
    pcImage       - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
    pcOutImage    - Input image in check scanner format.
                    I.e., pass an image scanned in using
                    the TS400 memory scanner functions.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL funcImage200To100(
   char *pcImage, char *pcOutImage);

/*-----------------03/22/00 02:16pm-----------------
 DCCWriteMemoryData - Function to write data to a file.
 Parameters:
    pMemory    - The memory buffer that contains the data.
    iSize      - Number of bytes of data to write.
    szFileName - Output File Name
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCWriteMemoryData(
   char *pMemory, int iSize, char *szFileName);


/*-----------------02-18-97 12:18pm-----------------
  DCCScanSetSpecialDocument - Function to override DCCScan and handle
    documents based on their routing and account numbers in a special way.
    This function must be called once for every supported document type.

  PARAMETERS:
      int iCount      Total number of document types for special handling.
                      Changing this number will clear previous settings.
                      Must be 0 to 100.
      int iIndex      1 to iCount,
      char *szRouting Routing or Bank number, usually :123456789: in U.S.A.
      char *szAccount Optional Customer Account Number 123457 or blank string
      int iThreshold  1 - Edge Detection Thresholding
                      2 - Simple Thresholding
                      3 - Floyd Steinberg Threshold
      int iMin        Minimum Background white Pixels Required.  Valid from
                      10 to 80 and this requires the percentage of pixels
                      to be treated as white background.  This can be
                      increased to sometimes skip complex document backgrounds
                      that make edge detection thresholding too noisy.
      int iContrast   200 to 1024 when using threshold 1 (Edge Detection Algorithm),
                      2 to 13 when using threshold 2 (Simple Thresholding), and
                      ignored when threshold 3 (Floyd Steinberg Threshold).
      int iOptions    0-Off
                      1 - Group 4 Filter to get smaller Tiff Images
                      2 - Ignore Speckles when calculating Image Quality
                      4 - Remove Speckles
                      8 - Ignore Bent Corners when calculating Image Quality.
                          Some images have dark corners that always look bent.
                      16- Ignore Steaks since some complex documents have streaks.
                      Options can be combined (added), so 7 would turn on the
                         first three options.
                      32 - Ignore DF
                      64 - Ignore Compressed Side/Density
                      128 - Force DF
                      256 - Use OCR MICR

  RETURN:
      0          - Okay
      BUIC_ERROR_BADPARAM
      BUIC_ERROR_MEMORY_ALLOC

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCScanSetSpecialDocument(int iCount,
   int iIndex, char *szRouting, char *szAccount, int iThreshold, int iMin,
   int iContrast, int iOptions);

/*-----------------02-18-97 12:18pm-----------------
  DCCScanSetSpecialDocumentEx - Function to override DCCScan and handle
    documents based on their routing and account numbers in a special way.
    This function must be called once for every supported document type.

  PARAMETERS:
      int iCount      Total number of document types for special handling.
                      Changing this number will clear previous settings.
                      Must be 0 to 100.
      int iIndex      1 to iCount,
      char *szRouting Routing or Bank number, usually :123456789: in U.S.A.
      char *szAccount Optional Customer Account Number 123457 or blank string
      int iThreshold  1 - Edge Detection Thresholding
                      2 - Simple Thresholding
                      3 - Floyd Steinberg Threshold
      int iMin        Minimum Background white Pixels Required.  Valid from
                      10 to 80 and this requires the percentage of pixels
                      to be treated as white background.  This can be
                      increased to sometimes skip complex document backgrounds
                      that make edge detection thresholding too noisy.
      int iContrast   200 to 1024 when using threshold 1 (Edge Detection Algorithm),
                      2 to 13 when using threshold 2 (Simple Thresholding), and
                      ignored when threshold 3 (Floyd Steinberg Threshold).
      int iOptions    0-Off
                      1 - Group 4 Filter to get smaller Tiff Images
                      2 - Ignore Speckles when calculating Image Quality
                      4 - Remove Speckles
                      8 - Ignore Bent Corners when calculating Image Quality.
                          Some images have dark corners that always look bent.
                      16- Ignore Steaks since some complex documents have streaks.
                      Options can be combined (added), so 7 would turn on the
                         first three options.
                      32 - Ignore DF
                      64 - Ignore Compressed Side/Density
                      128 - Force DF
                      256 - Use OCR MICR
      int iSecondThreshold  
                      1 - Edge Detection Thresholding
                      2 - Simple Thresholding

      int iSecondContrast
                      200 to 1024 when using threshold 1 (Edge Detection Algorithm),
                      2 to 13 when using threshold 2 (Simple Thresholding).
      int iLeft       Left Edge of Second Threshold Area in 10th of inches
      int iTop        Top Edge of Second Threshold Area in 10th of inches
      int iRight      Right Edge of Second Threshold Area in 10th of inches
      int iBottom     Bottom Edge of Second Threshold Area in 10th of inches

  RETURN:
      0          - Okay
      BUIC_ERROR_BADPARAM
      BUIC_ERROR_MEMORY_ALLOC

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCScanSetSpecialDocumentEx(int iCount,
   int iIndex, char *szRouting, char *szAccount, int iThreshold, int iMin,
   int iContrast, int iOptions, int iSecondThreshold, int iSecondContrast,
   int iLeft, int iTop, int iRight, int iBottom);
   
/***********************************************************************
*
*  DCCResolveTwoPassMICR
*
*  Combining the results on a CX30 in SCAN, Park, and ScanAgain Mode
*
*  This takes two MICR lines of the same check and test them and combines
*  them if necessary.
*
*  Return:
*     0 - First MICR Line is used and second Ignored
*     1 - Second MICR Line is used and first Ignored
*     2 - Results of the two lines were combined.
*
*  Note: all buffers should be at least 80 characters long.
*
**********************************************************************/
CFUNCTIONSDLLCALLS int PASCAL DCCResolveTwoPassMICR(
   char *szFirstMICR, char *szSecondMICR, char *szFinalMICR);
/*************************************************************************
*
* DCCDiagnosticInfo
*
* Return low level diagnostic Information
*
* szInfo - a character buffer
* iLength - size of szInfo buffer in bytes
*
**************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL DCCDiagnosticInfo(char *szInfo, int iLength);
/*************************************************************************
*
* DCCAltBWImage
*
* Return 1 of 10 possible alternative BW images for a JPEG Image.
*
* pszJPEGImageName - JPEG File Name
* iPage            - 1
* iIndex           - 0 to 9
* pszTIFFImageName - Tiff Output File Name
* iImageQuality    - Calcalated Image Quality - 0 is good, lower better
*                    (Only calculated if piDocStatus is passed.)
* piDocStatus      - An Array of 32 integers for IQA test Status. NULL if
*                    don't want IQA ran.
*
**************************************************************************/
CFUNCTIONSDLLCALLS int PASCAL DCCAltBWImage(char *pszJPEGImageName, int iPage,
   int iIndex, char *pszTIFFImageName, int *iImageQuality, int *piDocStatus);


/*-----------------02-18-97 12:18pm-----------------
  DocketPortCalibrate - function to calibrate SB600 or SB500.

  PARAMETERS:
      iMode                   0 - Calibrate if not calibrated
                              1 - Force Calibration
      NONE

  RETURN:
      1                       - Check(s) present in input hopper.
      0                       - No checks present in input hopper.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DocketPortCalibrate(int iMode);

/*-----------------06-16-11 9:47am-----------------
  DCCSetSortTable - function to download a series of Sorting decisions
     which can be evaluated faster.


  PARAMETERS:
      iEnable                 - O Disable Sorting, 1 Enable sorting and set table
      iDefaultPocket          - Pockets 0 or 1 for BX7200 and TS4120
      iErrorPocket            - Pockets 0 or 1 for BX7200 and TS4120, if 2 Don't 
                                check for bad/missing MICR
      iItems                  - Number of sort conditions
      pSortBuffer             - Text buffer with sort logic
      iMaxSize                - Maximum number of bytes of text in sort logic


  RETURN:
      0                       - No error
      TS2_ERR_INVALID_FUNCTION- Scanner Model does not support this feature
      BUIC_ERROR_MEMORY_ALLOC - Could not allocate memory

  Example Call:
      DCCSetSortTable(0, 0, 0, 0, "", 0);  // Disable

        // Sort Checks from 12 Routine code to pocket 0, others to pocket 1
   static char szSortTable[] = 
   "0,:101000048:,, 0,:042000437:,, 0,:043000300:,, 0,:044000503:,, 0,:051000033:,, 0,:051900023:,, 0,:052000278:,, 0,:053000206:,, 0,:053900089:,, 0,:061000146:,, 0,:062000190:,, 0,:063000199:,, 0,:064000101:,, 0,:065000210:,,";
      DCCSetSortTable(1, 12, 1, szSortTable, sizeof(szSortTable));

   "Pocket,SortString1,SortString2, <optional CR LF>
    Pocket,SortString1,SortString2, <optional CR LF>
      ....
    Pocket,SortString1,SortString2, <optional CR LF>"
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCSetSortTable(int iEnableSort, 
   int iDefaultPocket, int iErrorPocket, 
   int iItems, char *pSortBuffer, int iMaxSize);

/*-----------------06-20-11 12:10pm-----------------
  DCCVerifyTiffCRC16 -- test whether DCC CRC16 is valid in Tiff Image.

  PARAMETERS:
     szFileName               - complete path to file
     iPage                    - Usually 1 for first page in file

  RETURN:
      0                       - No Match
      1                       - Match
      Negative                - Error Code

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCVerifyTiffCRC16(char *szFileName, int iPage);

/*-----------------09-13-11 12:10pm-----------------
  DCCTiffScale -- Scale a Tiff G4 Image to some unsupported size

  PARAMETERS:
     szInput                  - complete Path to Input File
     szOutput                 - complete Path to Output File
     iHScale                  - Scale 2048 pixels into xxx pixels (128 to 32000)
                                A value of 1024 would cuts the number of horizontal
                                pixels by 50%.  A value of 4096 would double the number
                                of horizontal pixels.
     iVScale                  - Scale 2048 pixels into xxx pixels (128 to 32000)

  RETURN:
      0                       - Okay
      1                       - Input File error
      3                       - Output File error
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCTiffScale(
   char *szInput, char *szOutput, int iHScale, int iVScale);

/*-----------------09-13-11 12:10pm-----------------
  EncryptSpecialDocuments - This encryptes routing numbers and account numbers
  so customer data is secure.

  PARAMETERS:
     szFileName               - complete Path to Input File (Usually buicscan.ini
                                  or dccalt.ini
     iClearRoutingAccount     - Clear Routing and Account numbers after successfully
                                  encrypting special document records.

  RETURN:
      0                       - No Special Document Records found
    -552                      - Routing Numbers were missing or corrupt
      1-200                   - Number of records encrypted
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL EncryptSpecialDocuments(
    char *szFileName, int iClearRoutingAccount);

/*-----------------02-18-97 12:18pm-----------------
  DCCScanUV - Getting the UV image and saving it.
    PARAMETERS:
      sFrontFileName - File name for front UV image or NULL.
      pcFrontImage   - Memory pointer to put front UV image OR NULL.
      plFrontFileSize- File size of UV image.
      iFormatComp    - Compression format.

  RETURN:
      TRUE                    - Everything okay.
      BUIC_ERROR_NOINIT       - Have not initialized the scanner
                                before starting this scan.
      BUIC_ERROR_BADJOB       - Job type not within range of known types.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCScanUV(char *sFrontFileName, 
    char *pcFrontImage, long *plFrontFileSize, int iFormatComp);


/*-----------------02-18-97 12:18pm-----------------
  IsDCCUSBScannerAvailable - Is a USB DCC Scanner Available, i.e
        on the bus and turned on and available for use.
    PARAMETERS:
      piDCCProductVID - Pointer to integer to contain VID of DCC product
      piDCCProductPID - Pointer to integer to contain PID of DCC product

  RETURN:
      0                       - No DCC scanner found on USB bus available
                              - OR procedure failed.
      1                       - DCC scanner found but not sure which
      CX30                    - CX30 found
      TS220                   - TS220 Found
      TS230                   - TS230 Found
      TS240                   - TS240 Found
      BX7200                  - BX7200 Found
      SB500                   - SB500 Found
      SB600                   - SB600 Found
      Etc.

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL IsDCCUSBScannerAvailable(
   int *piDCCProductVID, int *piDCCProductPID);


/*-----------------02-18-97 12:18pm-----------------
  DCCScaleImage -- DownScales a grayscale or bw image.

    PARAMETERS:
      szInputFile - Input File to scale/invert
      szOutputFile - Output File
      iOutDPI - Wanted DPI must be less than original DPI
      iInvert - Invert Image while scaling

  RETURN:
      0 or 1                  - Okay
      BUIC_ERROR_BADFILENAME  - Could not read Input Image, bad file or format
      BUIC_ERROR_BADPARAM     - Original DPI lower than Output DPI
      BUIC_ERROR_IMAGE_TYPE   - Not grayscale or b/w
      BUIC_ERROR_MEMORY_ALLOC - Memory Error
      BUIC_ERROR_FILE_IO      - File Input Error

--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCScaleImage(
   char *szInputFile, char *szOutputFile, int iOutDPI, int iInvert);

/*-----------------02-18-97 12:18pm-----------------
  DCCGetDescriptorData -- Gets BX7200 Only Data Structures -- Private

    PARAMETERS:
      DataType  -- // 2 Usually
      pData     -- Pointer to BX7200 Structures -- Private
      cbMax     -- Max Size
      pcbActual -- Actual Size

  RETURN:
--------------------------------------------------*/
CFUNCTIONSDLLCALLS BOOL PASCAL DCCGetDescriptorData(DWORD   DataType, 
   void  * pData, DWORD   cbMax, DWORD * pcbActual);

/*-----------------11-27-13  13:07-----------------
  DCCAdjustBatchCounter -- Modify the current Endorsement Counter Setting

    PARAMETERS:
      iMode     -- 0 Read Only, 1 Set, 2 Increment by iValue
                   3 Decrement by iValue, 4 Increment by Increment set in
                   DCCBatchPrintString or DCCBatchPrintBMP.
                   5 Decrement by Increment set in 
                   DCCBatchPrintString or DCCBatchPrintBMP.
      iValue    -- Used when iMode equal 1, 2, or 3

  RETURN:  Current iBatchCounter  Value.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCAdjustBatchCounter(int iMode, int iValue);

/*-----------------03-20-14  20:05-----------------
  DCCMicrReSetEndorsement -- Reset Endorsement String and Count of next
      item in BX7200 track while in SORTWAIT Mode.

    PARAMETERS:
      bDOCId    -- Document Number return from funcTS200GetMICR.
      szNewEndorsement - String of New Endorsement
      iCounter  -- Starting value printed on next document in track

  RETURN:  Error or Zero
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCMicrReSetEndorsement(unsigned char bDOCId,
   char *szNewEndorsement, int iCounter);

/*-----------------03-20-14  20:05-----------------
  DCCMicrGetFrontImageDIB -- Pull Front Image in DIB format on a BX7200
      while in SORTWAIT Mode.

    PARAMETERS:
      bDOCId    -- Document Number return from funcTS200GetMICR.
      pDIBPtr   -- Pointer to a Pointer at a DIB grayscale Image.

  RETURN:  Error or 1
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCMicrGetFrontImageDIB(unsigned char bDOCId,
        unsigned char **pDIBPtr);

/*-----------------03-21-14  08:27-----------------
  DCCMicrGetWidth10Inches -- Return Width of Image Based on MICR Samples
      on a BX7200 while in SORTWAIT Mode from MICR Callback Only.

    PARAMETERS:
      bDOCId    -- Document Number return from funcTS200GetMICR.

  RETURN:  Error or Image Width in 10th of Inches.
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCMicrGetWidth10Inches(unsigned char bDocID);

/*-----------------03-21-14  08:27-----------------
  DCCGetLastBatchCounter  -- Return Counter Number Associated with item
      that just finished DCCScan.

    PARAMETERS:

    RETURN:  Error (-1) or Counter Number
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCGetLastBatchCounter(void);

/*-----------------03-21-14  08:27-----------------
  DCCUVGain -- Change Gain of UV Grayscale Image and optionally set
        BlackLevel.

    PARAMETERS:

    RETURN:  Error (negative DCC Error Code) or 0
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCUVGain(char *szInputImage, char *szOutputImage,
        int iGainFactor, int iBlackLevel, int iGainPlusMinus);

CFUNCTIONSDLLCALLS int PASCAL DCCUVTiff(char *szInputImage, char *szOutputImage, 
        int iThreshold);

/*-----------------03-21-14  08:27-----------------
  DCCGetImageInfo -- Return Info about Image

    PARAMETERS:
        szInputFile -- Image File Name
        iWidth      -- Image Width
        iHeight     -- Image Height
        iDPI        -- DPI if valid
        iBits       -- Bits per pixel if valid

    RETURN:  Error (negative DCC Error Code) or 0
--------------------------------------------------*/
CFUNCTIONSDLLCALLS int PASCAL DCCGetImageInfo(char *szInputFile, 
        int *iWidth, int *iHeight, int *iDPI, int *iBits);


