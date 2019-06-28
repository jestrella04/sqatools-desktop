/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javascandemo1;

/**
 *
 * @author Tu & Mike
 * @March 31, 2015
 */

import java.io.UnsupportedEncodingException;
import java.util.Arrays;

//import java.io.IOException;
//import java.nio.file.Files;
//import java.nio.file.Path;
import java.io.File;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.io.IOException;

import DccScan.DccScanApi;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.logging.Level;
import java.util.logging.Logger;

public class JavaScanDemo1 {

    public static int dropScanMode = 0;
    public static int scanMethodFlag = 0;
    public static int prntFlag = 0;
    public static int uvFlag = 0;
    public static boolean getOCRMicrFlag = false;
    
    public static int begCtr = 0;
    public static int incCtr = 0; 
    public static int eRot = 0;
    public static int icount = 0;
    public static int ret = 0;
    public static int ans = 0;

    public static int[] aiDCCProductVID = {0};
    public static int [] aiDCCProductPID = {0};
    public static boolean specDocAddFlag = true;
           
    public static String sPath = "C:\\DCC\\APPS\\Java\\JavaScanDemo1\\JavaScanDemo1\\build\\classes\\BUICSCAN.INI";
    
    public static DccScanApi scanApi = new DccScanApi();
    public static FileWriter fileWriter = null;
    public static String endStr = "This is a test %04d of many.|Line 2|Line 3|Line 4";
    public static String[] asMICR = {"0"};
    public static String[] OCRMICR = {"0"};
    public static String[] OCRMICRCONF = {"0"};
    
    public static String[] asSerNum = {"0"};
    public static int[] aiNumDocs = {0};
    public static int[] aiScnTime = {0};


    public static byte[] abVirtualString = endStr.getBytes();
            // Create buffers for Scan To Memory (1 meg by default)
    public static byte[] abFrontTiffImageBuffer = new byte[1024*1024];
    public static byte[] abBackTiffImageBuffer = new byte[1024*1024];
    public static byte[] abFrontJPEGImageBuffer = new byte[1024*1024];
    public static byte[] abBackJPEGImageBuffer = new byte[1024*1024];
    public static byte[] abUVJPEGImageBuffer = new byte[1024*1024];
    public static byte[] abUVTiffImageBuffer = new byte[1024*1024];
            // Initialize variable to hold Image length, needed for writing to file
    public static int[] aiFrontTiffImageLength = {0};
    public static int[] aiBackTiffImageLength = {0}; 
    public static int[] aiFrontJPEGImageLength = {0}; 
    public static int[] aiBackJPEGImageLength = {0};
    public static int[] aiUVJPEGImageLength = {0};
    public static int[] aiUVTiffImageLength = {0};

    
            // Initialize variables to hold quality and Doc Status rom DCCScan
    public static int[] aiFinalImageQuality = {0};
    public static int[] aiFinalContrast = {0};
    public static int[] aiDocStatus = new int[32];
    
    //Set up to Append Doc Data to file on disk
    String filepath="C:\\Temp\\Images\\Scanbatdata.txt";
    File file = null;
    String newScanData; 
    BufferedWriter bwr;
    
    
            
    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        
        if (args.length == 0){
            System.out.println("No command Line Arguments have been passed!.");
            dropScanMode = 1; //0-OFF, 1-ON
            scanMethodFlag = 1; //1 = Scan to File, 2 = Scan To Memory, 3 = Scan Long Paper
            prntFlag=1;
            uvFlag=1;  //0 = UV image creation OFF, 1 = UV image creation = ON

        }
        else {
            //For ach Sring in the String array print out the string
            //Command line Arguments, in order
            try {
                dropScanMode = Integer.parseInt(args[0]);  //Off=0, ON=1
                    if(dropScanMode > 1){dropScanMode = 0;}
                scanMethodFlag = Integer.parseInt(args[1]);  //1= DCCSCANToFile, 2 = DCCSCANTOMEMORY, 3 = DCCSCANLONG
                    if(scanMethodFlag < 1 || scanMethodFlag > 3){scanMethodFlag = 1;}  //if less than 1 or greater than 3 default to 1
                prntFlag = Integer.parseInt(args[2]);  //1= Turn endorsing ON, 0= Turn endorsing off
                    
                    if(prntFlag > 1){prntFlag=0;}
                uvFlag = Integer.parseInt(args[3]);  //1= Turn UV ON, 0= Turn UV off
                    if(uvFlag > 1){uvFlag = 0;}
                } catch (NumberFormatException e) {
                    System.err.println("Argument" + args[0] + " must be an integer.");
                }
        } 
        System.out.println("dropScan on-1/off-0 = " + dropScanMode);
        System.out.println("Scan Mode = " + scanMethodFlag);
        System.out.println("Endorse on-1/off-0 = " + prntFlag);
        System.out.println("UV off-0/on-1 = " + uvFlag);
        
        JavaScanDemo1 demo = new JavaScanDemo1();
        //Select Endorse Method - 0 = No Endorse, 1 = PrintString, 2 = BMP Print, 3 = Virtual Endorse
        getOCRMicrFlag = true;
        begCtr = 1;
        incCtr = 1;
        eRot = 2;  //0=normal, 1=90. 2=180, 3=270
        

        System.out.println("Endorse Method " + prntFlag + " Selected");
        
       //demo.RunBatScan2File();
       demo.RunBatScan();
             
	return;
    }
    
    public void RunBatScan() {
            /*
            BuicInit
            SetParam for Batch mode
            SetParam for Image Wait to 0
            Repeat
            DccScan to scan an item  (to file or to memory)
            Drop feed one at a time
            Continous feed Until feeder empty  (the return code is -212 )
            BuicExit
            */
            
        try {
            
            System.out.println("----->Java testing SetParamString()" );
            
            ret = scanApi.DccApiVersion();
            System.out.println("API Version: " + ret);
            
            ret = scanApi.BuicSetParamString(135,sPath);
            if (ret < 0) {
                System.out.println("Failed to set Path to Scanner Configuration File. Path : "  + sPath);
                return;
            }
            System.out.println("Set Path to Scanner Configuration File. Path : "  + sPath);
            
            ret = scanApi.BuicInit();
            if (ret < 0) {
                System.out.println("Scanner did not initialize.  Error: " + ret);
                return;
            }
            if (ret > 0){
                System.out.println("Scanner Initialized");
            }
            
            ret = scanApi.IsDccUsbScannerAvailable(aiDCCProductVID, aiDCCProductPID);
            System.out.println("Scanner VID: " + aiDCCProductVID[0]);
            System.out.println("Scanner PID: " + aiDCCProductPID[0]);
            System.out.println("Scanner Model: " + ret);

            switch (ret) {
            case 240 : System.out.println("scannerType:" + "TS240"); break;
            case 30 : System.out.println("scannerType:" + "CX30");
                ret = scanApi.BuicSetParam(191,1);  // CX30 Scan mode setings 1 Scan & return, 0 Straight thru
                System.out.println("CX30 Set to Mode: " + ret);
                break;
            case 220 : System.out.println("scannerType:" + "TS220"); break;
            case 7200 : System.out.println("scannerType:" + "BX7200"); break;
            default :  System.out.println("scannerType:" + "Unknown"); break;
            }
            
            ret = scanApi.BuicGetScannerSerialNumber(asSerNum, aiNumDocs, aiScnTime);
            System.out.println("Ser Num: " + asSerNum[0]);
            System.out.println("Scanner Docs Scanned = " + aiNumDocs[0]);
            System.out.println("Scanner run time = " + aiScnTime[0]);

            ret = scanApi.GetScannerType();
            System.out.println("Scanner Type = " + ret);
            ret = scanApi.DccApiSupportedScanners();
            System.out.println("Supported Scanners = " + ret);
                  
        
            if (specDocAddFlag == true){
                int iCount = 1;
                int iIndex = 1;
                String szRouting = "052000278";  //Test Routing number
                String szAccount_1 = "531550";   //Test Account number
                int iThreshold = 2;
                int iMin = 10;
                int iContrast = 2;
                int iOptions = 8;

                int iSecondThreshold = 3;
                int iSecondContrast = 9;
                int iLeft = 0;
                int iTop = 0; 
                int iRight = 0; 
                int iBottom = 0;
                 
                ret = scanApi.DccScanSetSpecialDocumentEx(iCount, iIndex, szRouting, szAccount_1, iThreshold, iMin, iContrast, iOptions, iSecondThreshold, iSecondContrast, iLeft, iTop, iRight, iBottom);
                if (ret < 0) {
                    System.out.println("Failed to set Special Doc: 052000278,531550" + ret);
                    return;
                }
            }
            
            ret = scanApi.BuicSetParam(109,100);
            if (ret < 0) {
                System.out.println("Failed to set Default IMAGE WAIT mode");
                return;
            }
            
            ret = scanApi.BuicSetParam(160,1);
            if (ret < 0) {
                System.out.println("Failed to set Setting Scan Batch mode");
                return;
            }

            ret = scanApi.BuicSetParam(scanApi.CFG_DEV_PRINTER,1);   //Turn on PRINTER

            String endStr = "This is a test %04d of many.|Line 2|Line 3|Line 4";
            ret = scanApi.BuicGetParam(215);
            System.out.println("Print Head type: " + ret);
            if (ret == 4) { //Multiline print head
                System.out.println("Multi-Line Printer Detected");
                endStr = endStr.replace("|", "\n");
                System.out.println(endStr);
                abVirtualString = endStr.getBytes();
                //return;
            }
            switch(prntFlag){
                case 1:
                    //DCCBatchPrintBMP(sEndTxt, BMP_END_Offset, 0, StrtCtr, IncAmt, BMPTextHeight, left, top, bold, italic, "Arial")
                    ret = scanApi.DccBatchPrintBMP(abVirtualString,1200,0,begCtr,incCtr,17,0,1,1,0,"Arial");
                    System.out.println("BatchPrintString: " + endStr);
                    break;
                case 2:    
                    ret = scanApi.DccBatchPrintString(abVirtualString, 1200, 0, 100, 1);
                    System.out.println("BatchPrintSrting: " + endStr);
                    break;
                case 3:
                    System.out.println("Virtual Endorsement: " + endStr);
                    ret = scanApi.DccScanVirtualEndorsement(abVirtualString, 1, 2, begCtr, incCtr, 32, 1, 1, 1, 0, eRot, 0, 0, 0, 0, "Arial");
                    break;
                default:
                    System.out.println("Endorsement not set");
                    ret = scanApi.BuicSetParam(scanApi.CFG_DEV_PRINTER,0);   //Turn off PRINTER
                    break;
                }
            if (ret < 0){
                System.out.println("No Print Head detected, Endorse turned OFF");
                prntFlag = 0;
                ret = scanApi.BuicSetParam(scanApi.CFG_DEV_PRINTER,0);   //Turn off PRINTER
                }


            file = new File(filepath);
            fileWriter = new FileWriter(file,true);
            newScanData = "BatchScanData";
            bwr = new BufferedWriter(fileWriter);
            int icount = 0;
            
 // *************************  Begin Scan loop  **********************************************************************
            
            ret = scanLoop();
    
// ***********************************************  End of Scan loop  ***********************************************
            int docsDroppedCtr = 0;
            while (dropScanMode == 1 && docsDroppedCtr < 4){
            if (scanApi.BuicStatus() > 0) {
                try {
                        Thread.sleep(500);
                        System.out.println("Drop Status = " + scanApi.BuicStatus());
                        scanLoop();
                        docsDroppedCtr ++;
                   }
                catch (InterruptedException e) {
                    }
             }
           }
            
            ret = scanApi.BuicExit();
            if (ret < 0) {
                System.out.println("Failed to terminate the scanner");
                return;
            }
        
            System.out.println("The test program worked! Thank you for playing 2");
            
            System.out.println("Test of Global Var: " + prntFlag);
        }
        catch (IOException ex) {
              Logger.getLogger(JavaScanDemo1.class.getName()).log(Level.SEVERE, null, ex);
        }
        finally {
            try {
                fileWriter.close();
            }
            catch (IOException ex) {
                Logger.getLogger(JavaScanDemo1.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
    }

        int scanLoop() throws IOException{
           do 
            {
                icount++;   //Batch image counter reset between jobs
                String sFrontTiffFileName = ("C:\\Temp\\Images\\front" + icount + ".TIF");
                String sBackTiffFileName = ("C:\\Temp\\Images\\back" + icount + ".TIF");
                String sFrontJPEGFileName = ("C:\\Temp\\Images\\front" + icount + ".JPG");
                String sBackJPEGFileName = ("C:\\Temp\\Images\\back" + icount + ".JPG");
                String sUVJPEGFileName = ("C:\\Temp\\Images\\uv" + icount + ".JPG");
                String sFixedUVJPEGFileName = ("C:\\Temp\\Images\\uv" + icount + ".JPG");

                if(uvFlag == 1) {
                    if(scanMethodFlag == 1){
                        System.out.println("Starting UV Process");
                        ret = scanApi.BuicSetParam(scanApi.CFG_IMAGE_FRONTCOLOR,5);
                        ret = scanApi.BuicSetParam(scanApi.CFG_IMAGE_FRONT_UV_THRESH,4);
                        ret = scanApi.BuicGetParam(119);
                    }
                    if(ret != 5){
                        uvFlag = 0;
                        System.out.println("No UV Scanner ");
                    }
                }
           
                System.out.println("Scan Method = " + scanMethodFlag);
                switch (scanMethodFlag) {
                    case 1:
                        System.out.println("Scan to File");
                            
                        ret = scanApi.DccScanToFile(sFrontTiffFileName, sBackTiffFileName, sFrontJPEGFileName, sBackJPEGFileName, asMICR , aiFinalImageQuality, aiFinalContrast, aiDocStatus);
                        if(ret <0){
                            errHndler(ret);
                            break;
                        }
                        // Last Variable = output format 9 = Rev tif, 4 = jpg, 1 = tif
                        if(uvFlag == 1){
                            ret = scanApi.DccScanUV(sUVJPEGFileName, null, aiUVJPEGImageLength, 4);
                            System.out.println("UV Scan Function Return - " + ret);
                            if(ret <0){errHndler(ret);}
                            }
                        break;
                    case 2:
                        System.out.println("Scan to Memory");
                        ret = scanApi.DccScanToMemory(abFrontTiffImageBuffer, aiFrontTiffImageLength, abBackTiffImageBuffer, aiBackTiffImageLength, abFrontJPEGImageBuffer, aiFrontJPEGImageLength, abBackJPEGImageBuffer, aiBackJPEGImageLength,  asMICR , aiFinalImageQuality, aiFinalContrast, aiDocStatus);                                                                  
                        break;
                    case 3:
                        System.out.println("Scan Long Paper");
                        if (ret > 0){icount++;}   //Batch image counter reset between jobs
                       break;
                    default:
                        System.out.println("Scan Method not selected");
                        break;
                }
                
                if (ret >= 0) {
                    if (getOCRMicrFlag){
                        ret = scanApi.DccScanGetOcrMicr(OCRMICR, OCRMICRCONF);
                        System.out.println("OCR MICR: " + OCRMICR[0]);
                        System.out.println("OCR Conf: " + OCRMICRCONF[0]);
                    }
                    System.out.println("MICR = " +  asMICR[0]);  
                    System.out.println("FinalImageQuality = " +  aiFinalImageQuality[0]);  
                    System.out.println("FinalContrast = " +  aiFinalContrast[0]);
                
                    System.out.println("MICR for Doc " + icount + ": " + Arrays.toString(asMICR));
                    newScanData = "ScanData: DocID: " + icount + ", MICR: " + Arrays.toString(asMICR) + ", MICR Quality: " + aiDocStatus[9] + ", Image Quality: " + aiFinalImageQuality[0] ;
                    fileWriter.append(newScanData);
                    fileWriter.append(System.lineSeparator()); 
                    
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
                /*           11 - Compressed Image Size                                    */
                /*           12 - Car Present                                              */
                /*           13 - LAR Present                                              */
                /*           14 - Payee                                                    */
                /*           15 - Date Present                                             */
                /*           16 - Signature Present                                        */
                /*           17 - Memo Present                                             */
                /*           18 - BLOB Present                                             */
                /*           19 - Carbon Strip                                             */
                /*           20 - Streaks Present                                          */
                /*           21 - GrayScale Contrast                                       */
                /*           22 - Image Focus                                              */
                /*           23 - ImageSize 10th of inch                                   */
                /*           24 - DPI (Pixels per Inch)                                    */
                /*           25 - Skew in 10th of Degree                                   */
                /*           26 - Double Top Edge Status                                   */
                /*           27 - Endorsement Characters                                   */
                /*           28 - Speckles in Center                                       */
                /*           30 - Used in DCCAPI.c                                         */
                /*           31 - Used in DCCAPI.c                                         */
                    
                    for (int index=0; index <32; index++) {
                        System.out.println("DocStatus = " +  aiDocStatus[index]); 
                    }
                    
                    //Scan to memory selected and we want to write the image in memory to a disk file
                    //so we can QC image and display image from file.
                    if (scanMethodFlag == 2) {  
                        try {
                            byte[] abFrontTif = Arrays.copyOf(abFrontTiffImageBuffer, aiFrontTiffImageLength[0]);
                            writeSmallBinaryFile(abFrontTif, sFrontTiffFileName);

                            byte[] abBackTif = Arrays.copyOf(abBackTiffImageBuffer, aiBackTiffImageLength[0]);
                            writeSmallBinaryFile(abBackTif, sBackTiffFileName);

                            byte[] abFrontJPEG = Arrays.copyOf(abFrontJPEGImageBuffer, aiFrontJPEGImageLength[0]);
                            writeSmallBinaryFile(abFrontJPEG, sFrontJPEGFileName);

                            byte[] abBackJPEG = Arrays.copyOf(abBackJPEGImageBuffer, aiBackJPEGImageLength[0]);
                            writeSmallBinaryFile(abBackJPEG, sBackJPEGFileName);
                            //writeSmallBinaryFile(abUVFrontJPEG, sUVJPEGFileName);
                       }
                        catch (IOException e){
                            System.out.println("Error writing images");
                            e.printStackTrace();
                        }
                    }
                }
            
            } while (ret >= 0);
            icount--;
            return ret;
        }               
        
        void writeSmallBinaryFile (byte[] aBytes, String aFileName) throws IOException {
            Path path = Paths.get(aFileName);
            Files.write(path, aBytes); //creates, overwrites
        }  
         
        void errHndler (int ret){
             //String errMSG;
             
             switch(ret){
             case -100:
                System.out.println("Error Initializing Scanner");
                break;
             case -104:
                System.out.println("Unsupported Image Type,Incompatiable DPI and Image Format ");
                break;
             case -212:
                // ret = scanApi.BuicEjectDocument();
                System.out.println("No document detected in feeder");
                break;
             case -216:
                 System.out.println("Error feeding document, remove and reset document");
             case -125:
                System.out.println("Scanner not detected");
                break;
             case -220:
                System.out.println("Document Jam detected");
                break;
             default:
                System.out.println("Unknown scanner error:  " + ret);
            }
            if (ret != -212){
                ret = scanApi.BuicClearDocument();
                System.out.println("Documents cleared from memory.");
                ret = scanApi.BuicEjectDocument();
                System.out.println("Eject to clear errors.");
            }

         }
 
}

    