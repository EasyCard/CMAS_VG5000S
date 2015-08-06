#include "ECCAPP.h"
#include <signal.h>

USHORT UpdateAP() {
    ULONG FileSize;
    BYTE *bData;
    USHORT ret;
    SystemLog("UpdateAP", "Start");

    //2014.04.11, kobe added for ECR, response to POS first
    int result;
    if (ecrObj.gData.isEcrTxn) {

        sprintf(ecrObj.ngData->responseCode, "0000");
        if ((result = ecrObj.successResponse(&ecrObj)) != d_OK && !ecrObj.ngData->response2Pos) {
            ecrObj.errorResponse(&ecrObj, result);
        }
        CTOS_Delay(1000); //enough time to response to POS

    }


    FileSize = File_GetLen(APFILE);
    if (FileSize > 0) {

        bData = malloc(FileSize);
        ret = usReadFileData(APFILE, &FileSize, bData);
        if (ret != d_OK) return ret;
        ShowMessage2line("程式更新", "更新中，請稍候!!", "請勿關閉電源", Type_ComformNONE);
        ret = CTOS_UpdateFromCAPs(bData, (DWORD) FileSize, PROGRAM_UPDATE_WHOLE);
        // if(ret!=d_OK)  return ret; 
        remove(APFILE);
        /*        USHORT   usAPIndex ;
         ret= CTOS_APFind  ("ECCAPP",&usAPIndex );   
            if(ret!=d_OK)   goto RUNAP; 
    
             CTOS_stCAPInfo   stInfo ;
            ret= CTOS_APGet  ( usAPIndex,&stInfo );      
     
            ret= CTOS_APDel  (usAPIndex) ;*/
    }
}

USHORT CheckNewVersionAP() {
    SystemLog("CheckNewVersionAP", "Start");
    USHORT ret;

    //  ret=File_exist(APFILE);
    //  if(ret=!d_OK) return d_Fail;

    //  ULONG size=File_GetLen(APFILE);
    //if(size<1000) return d_Fail;    
    if (gNEWAPFALG == TRUE) {
        USHORT TXCount = CheckBatchCount();
        if (TXCount > 0) {
            MessageBox("版本更新", "發現新版程式", "請先結帳!!", "", "", d_MB_CHECK);
            return d_Fail;
        }
        MessageBox("版本更新", "發現新版程式", "程式將進行更新", "", "", Type_wait2sec);
        ret = UpdateAP();

        //2014.04.11, kobe modified it for ECR
        //CTOS_SystemReset (  );         
        ezSystemReset();
    }
    return d_Fail;
}

USHORT CheckNewVersionFile() {
    SystemLog("CheckNewVersionFile", "Start");
    USHORT ret;

    int currversion, newversion;
    /* 
       ret = File_exist(TMSFILE);
       if(ret ==d_OK){
          MessageBox("檔案更新","重新開機","請稍候!!","","",NULL);
          CTOS_SystemReset ();
           return  ret;
       }*/
    currversion = atoi(gConfig.CURRVERSION.BLC.VERSION);
    newversion = atoi(gConfig.TMS.BLC.VERSION);
    if (newversion > currversion) {
        MessageBox("檔案更新", "重新開機", "請稍候!!", "", "", 0);

        //2014.04.11, kobe modified it for ECR
        //CTOS_SystemReset (  );                     
        ezSystemReset();
    }
    ///////////////////////////////////////////////////////////////////////////////  



    currversion = atoi(gConfig.CURRVERSION.AP.VERSION);
    newversion = atoi(gConfig.TMS.AP.VERSION);
    //if(strcmp( gConfig.TMS.AP.VERSION, gConfig.CURRVERSION.AP.VERSION)!=0)   
    if (newversion > currversion) {
        MessageBox("檔案更新", "重新開機", "請稍候!!", "", "", 0);
        //2014.04.11, kobe modified it for ECR
        //CTOS_SystemReset (  );                     
        ezSystemReset();
    }

    return d_Fail;
}

USHORT Process_ReBootCheckStatus() {
    SystemLog("Process_ReBootCheckStatus", "Start");
    USHORT ret;
    BYTE RS232STR[64];
    memset(RS232STR, 0x00, sizeof (RS232STR));

    if (InitReader() == d_OK) {
        ret = ResetDongle();
        if (ret != d_OK) {
            sprintf(RS232STR, "讀卡機測試:%x", ret);
        } else {
            sprintf(RS232STR, "讀卡機測試:正常");
        }

    }
    //  SystemCheck(RS232STR); 

    if (ecrObj.ecrOn)
        return d_OK;
    else {
        //   ret=Eth_SSLConnect_SOCKET(bgNETWORKChannel);
        //   if(ret!=d_OK) return ret;
        //  ret= Eth_SocketConnet(gHOSTIP,gHOSTPORT);
        //    if(ret==d_OK) {
        //  ret= SSLSocketConnect();
        //  if(ret!=d_OK) return ret;     

        //   Process_SendAdvice3(1);

        // ret= Function_Signon();   
        //   SSLSocketDisConnect();    
        //}else{
        //   MessageBox(gTransTitle,"","網路連線異常","請檢查並重啟設備","",d_MB_CHECK);
        // }    
    }
    return ret;

}

USHORT Process_CheckStatus() {
    SystemLog("Process_CheckStatus", "Start");

    USHORT ret = TestHostConnect();
    //if(ret!=d_OK)   MechineStatus |= Status_ETHERNET_Disconnect;
    ret = Process_SignOnRequest(&gTransData);
    if (ret != d_OK) {
        MessageBox(gTransTitle, "", "設備未登入", "無法進行交易", "", d_MB_CHECK);
        return ret;
    }

}

USHORT Process_DownloadBLC() {
    USHORT ret;
    SystemLog("Process_DownloadBLC", "Start");
    STR Downloadfile[128];
    BYTE urliplen;
    int currversion, newversion;
    STR bcurrversion[10], bnewversion[10];
    memset(bcurrversion, 0x00, sizeof (bcurrversion));
    memset(bnewversion, 0x00, sizeof (bnewversion));
    BYTE vernum[5 + 1];
    memset(vernum, 0x00, sizeof (vernum));

    currversion = atoi(gConfig.CURRVERSION.BLC.VERSION);

    newversion = atoi(gConfig.TMS.BLC.VERSION);
    if (newversion > currversion)
        // if(strcmp( gConfig.TMS.BLC.VERSION, gConfig.CURRVERSION.BLC.VERSION)!=0)     
    {

        if (strlen(gConfig.TMS.BLC.FTPPATH) <= 0) {
            return d_Fail;
        }


        ShowMessage("下載鎖卡名單", "DOWNLOADING..", Type_ComformNONE);
        ret = ECC_FTPGetFile2(BLCFILE, gConfig.TMS.BLC.FTPPATH);
        if (ret == 0) {
            ULONG lsize = File_GetLen(BLCFILE);
            if (lsize == 0) {
                ShowMessage3line("下載AP", "", "檔案下載失敗", "", Type_ComformAnykey);
            } else {

                BYTE str1[64], str2[64];
                sprintf(str1, "版本號:%s", gConfig.TMS.BLC.VERSION);
                sprintf(str2, "SIZE:%ld BYTE", lsize);
                ShowMessage3line("下載鎖卡名單", str1, str2, "DOWNLOAD OK", Type_wait2sec);
                memcpy(&gConfig.CURRVERSION.BLC.VERSION, &gConfig.TMS.BLC.VERSION, strlen(gConfig.TMS.BLC.VERSION));
                ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "VERSION", gConfig.CURRVERSION.BLC.VERSION);
                // Config_SetData();
                // SetVERSIONInfo();

            }
        } else {

            ShowMessage3line("下載鎖卡名單", "", "版本無需更新", "", Type_ComformAnykey);
        }
    }
    return d_OK;
}

USHORT Process_DownloadTMS() {
    USHORT ret = d_OK;
    SystemLog("Process_DownloadTMS", "Start");
    STR Downloadfile[128];
    BYTE urliplen;
    int currversion, newversion;
    STR bcurrversion[10], bnewversion[10];
    memset(bcurrversion, 0x00, sizeof (bcurrversion));
    memset(bnewversion, 0x00, sizeof (bnewversion));
    BYTE vernum[5 + 1];
    memset(vernum, 0x00, sizeof (vernum));

    File_exist(APFILE);
    remove(APFILE);

    currversion = atoi(gConfig.CURRVERSION.BLC.VERSION);

    newversion = atoi(gConfig.TMS.BLC.VERSION);
    if (newversion > currversion)
        // if(strcmp( gConfig.TMS.BLC.VERSION, gConfig.CURRVERSION.BLC.VERSION)!=0)     
    {

        if (strlen(gConfig.TMS.BLC.FTPPATH) <= 0) {
            return d_Fail;
        }


        ShowMessage("下載鎖卡名單", "DOWNLOADING..", Type_ComformNONE);
        ret = ECC_FTPGetFile2(BLCFILE, gConfig.TMS.BLC.FTPPATH);

        if (ret == 0) {
            ULONG lsize = File_GetLen(BLCFILE);
            if (lsize == 0) {
                ShowMessage3line("下載AP", "", "檔案下載失敗", "", Type_ComformNONE);
            } else {
                memcpy(&gConfig.CURRVERSION.BLC.VERSION, &gConfig.TMS.BLC.VERSION, strlen(gConfig.TMS.BLC.VERSION));
                ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "VERSION", gConfig.CURRVERSION.BLC.VERSION);
                //Config_SetData();   
                //SetVERSIONInfo();
                BYTE str1[64], str2[64];
                sprintf(str1, "版本號:%s", gConfig.TMS.BLC.VERSION);
                sprintf(str2, "SIZE:%ld BYTE", lsize);
                ShowMessage3line("下載鎖卡名單", str1, str2, "DOWNLOAD OK", Type_ComformNONE);
            }
        } else {
            ret = d_ERR_FTP_DL_FAIL;
            SystemLog("Process_DownloadTMS", "Download BLC File Fail");
            ShowMessage3line("下載鎖卡名單", "", "版本無需更新", "", Type_ComformNONE);
        }
    }
    ///////////////////////////////////////////////////////////////////////////////  
    memset(Downloadfile, 0x00, sizeof (Downloadfile));
    memset(vernum, 0x00, sizeof (vernum));
    // memcpy(vernum,&Downloadfile[3],5);


    gNEWAPFALG = FALSE;
    currversion = atoi(gConfig.CURRVERSION.AP.VERSION);
    newversion = atoi(gConfig.TMS.AP.VERSION);
    //if(strcmp( gConfig.TMS.AP.VERSION, gConfig.CURRVERSION.AP.VERSION)!=0)   
    if (newversion > currversion) {
        if (strlen(gConfig.TMS.AP.FTPPATH) <= 0) {
            return d_Fail;
        }
        ShowMessage("下載AP", "DOWNLOADING..", Type_ComformNONE);

        ret = ECC_FTPGetFile2(APFILE, gConfig.TMS.AP.FTPPATH);
        if (ret == 0) {
            ULONG lsize = File_GetLen(APFILE);
            if (lsize == 0) {
                ShowMessage3line("下載AP", "", "檔案下載失敗", "", Type_ComformNONE);
            } else {
                BYTE str1[64], str2[64];
                sprintf(str1, "版本號:%s", gConfig.TMS.AP.VERSION);
                sprintf(str2, "SIZE:%ld BYTE", lsize);
                ShowMessage3line("下載AP", str1, str2, "DOWNLOAD OK", Type_ComformNONE);
                gNEWAPFALG = TRUE;

            }
        } else {
            ret = d_ERR_FTP_DL_FAIL;
            SystemLog("Process_DownloadTMS", "Download AP File Fail");
            ShowMessage3line("下載AP", "", "版本無需更新", "", Type_ComformNONE);
        }
    }
    return ret;
}

USHORT Process_DownloadConfig() {
    STR line1[64], line2[64], line3[64], line4[64];
    SystemLog("Process_DownloadConfig", "Start");
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    //   CTOS_LCDTSelectFontSize(usFontSize);     
    CTOS_LCDTClearDisplay();

    ShowMessage2line("下載參數", "Config File", "下載中", Type_ComformNONE);
    USHORT ret = ECC_FTPGetFileforDebug(ConfigXML, "/parameter/config.xml");
    if (ret != d_OK) {
        ShowMessage2line("下載參數", "Config File", "下載失敗", Type_ComformAnykey);
        return 0;
    }
    ShowMessage2line("下載參數", "Config File", "下載完成", Type_ComformAnykey);
    return 0;
}

USHORT Process_DownloadScript() {
    STR line1[64], line2[64], line3[64], line4[64];
    SystemLog("Process_DownloadScript", "Start");
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    //   CTOS_LCDTSelectFontSize(usFontSize);     
    CTOS_LCDTClearDisplay();

    ShowMessage2line("下載參數", "script File", "下載中", Type_ComformNONE);
    USHORT ret = ECC_FTPGetFileforDebug(TestScrpitFile, "/script/TestScript.xml");
    if (ret != d_OK) {
        ShowMessage2line("下載參數", "script File", "下載失敗", Type_ComformAnykey);
        return;
    }
    ShowMessage2line("下載參數", "script File", "下載完成", Type_ComformAnykey);
    return;
}

/*
USHORT GetUnuploadTx(USHORT *Count)
{
     ULONG  offset;  
    int  iSize;
    TRANS_DATA2 TransData;
    USHORT icount;
      SystemLog("GetUnuploadTx","Start"); 
    FILE *fp =  fopen(TransDataFile, "rb+");
    if (fp ==  NULL) 
            return d_ERR_FILE_OPEN;
    
    fseek(fp, 0L, SEEK_END);
    ULONG    ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    
    if(ulFileSize%sizeof(TRANS_DATA2)!=0) return d_ERR_FILE_SIZE_ERR;
    offset=0;
  
   
     icount=0;
    
       do{
              fseek(fp,offset,SEEK_SET);      
              iSize=fread((BYTE *)&TransData,sizeof(TRANS_DATA2),1, fp);
           
              if( TransData.ucTXSTATUS==TransStatus_ADVREQ){
                 // gUnuploadTXs[icount]=offset;
                  icount++;
              }
              offset+=sizeof(TRANS_DATA2);
        }while(offset<ulFileSize); 
 *Count=icount;
    fclose(fp);
    return d_OK;
}*/

USHORT GetUnuploadTx2(USHORT *Count, long *UnuploadList) {
    ULONG offset;
    int iSize;
    TRANS_DATA2 TransData;
    USHORT icount;
    SystemLog("GetUnuploadTx", "Start");
    FILE *fp = fopen(TransDataFile, "rb+");
    if (fp == NULL)
        return d_ERR_FILE_OPEN;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;

    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;
    offset = 0;

    // memset(&TransData,0x00,sizeof(TransData));
    icount = 0;

    do {
        fseek(fp, offset, SEEK_SET);
        iSize = fread((BYTE *) & TransData, sizeof (TRANS_DATA2), 1, fp);

        if (TransData.ucTXSTATUS == TransStatus_ADVREQ) {
            UnuploadList[icount] = offset;
            icount++;
        }
        if (icount >= 1000) break;
        offset += sizeof (TRANS_DATA2);
    } while (offset < ulFileSize);
    *Count = icount;
    fclose(fp);
    // gUNUPLOADCOUNT=icount;
    return d_OK;
}

void *SendAdvice_Background(void) {
    ULONG offset;
    int iSize;
    int inRetVal;
    int iCount = 0;
    STR buf[64];
    BYTE temp[512];
    TRANS_DATA2 TransData;
    USHORT TotalCount;
    USHORT usRet;
    ULONG ulFileSize;
    FILE *fp;
    long UpLoadlist[1000];
    if (strcmp(gConfig.ETHERNET.EthernetCHANNEL, "GPRS") == 0) {
        usRet = SSLSocketConnect();
        if (usRet != d_OK) {
            printf("[%s,%d] thread sslConect fail\n", __FUNCTION__, __LINE__);
            pthread_exit("ssl connect fail");
            return;
        }

        usInitTxData(TXTYPE_REPORT);
        gTransData.ucTXSTATUS = TransStatus_REQ;
        usRet = Process_TransComm2(&gTransData, 0);
        ECC_CheckAPResponseCode(usRet);
        //    if(usRet!=d_OK)    return usRet;
        printf("[%s,%d] sendAdvice in Background start\n", __FUNCTION__, __LINE__);
        memset(buf, 0x00, sizeof (buf));

        memset(&UpLoadlist, 0x00, sizeof (UpLoadlist));
        usRet = GetUnuploadTx2(&TotalCount, (long*) &UpLoadlist);
        remove(SendFile);
        fp = fopen(TransDataFile, "r+");
        if (fp == NULL) {
            printf("[%s,%d] thread d_ERR_FILE_OPEN\n", __FUNCTION__, __LINE__);
            usRet = d_ERR_FILE_OPEN;
            pthread_exit("TransDataFile open fail");
            goto Disconnect;
        }

        fseek(fp, 0L, SEEK_END);

        ulFileSize = ftell(fp);
        if (ulFileSize <= 0) {
            printf("[%s,%d] thread ulFileSize <= 0\n", __FUNCTION__, __LINE__);
            fclose(fp);
            pthread_exit("advice file size <=0");
            goto Disconnect;
        }
        if (ulFileSize % sizeof (TRANS_DATA2) != 0) {
            printf("[%s,%d] thread d_ERR_FILE_SIZE_ERR\n", __FUNCTION__, __LINE__);
            fclose(fp);
            usRet = d_ERR_FILE_SIZE_ERR;
            pthread_exit("advice size mismatch");
            goto Disconnect;
        }
        if (TotalCount == 0) {
            printf("[%s,%d] thread TotalCount==0\n", __FUNCTION__, __LINE__);
            pthread_exit("no any advice existed");
            goto Disconnect;
        }
        /*
          if(TotalCount<gOFFLINETXLIMIT){ 
                    return d_OK;
             }*/
        offset = 0;
        //CTOS_EthernetOpen();   
        if (gIDLE == FALSE) {
            printf("[%s,%d] thread not in IDLE UI\n", __FUNCTION__, __LINE__);
            pthread_exit("not in IDLE now");
            goto Disconnect;
        }
    } else {
        printf("[%s,%d] sendAdvice in Background start\n", __FUNCTION__, __LINE__);
        memset(buf, 0x00, sizeof (buf));

        memset(UpLoadlist, 0x00, sizeof (UpLoadlist));
        usRet = GetUnuploadTx2(&TotalCount, (long*)UpLoadlist);
        remove(SendFile);
        fp = fopen(TransDataFile, "r+");
        if (fp == NULL) {
            printf("[%s,%d] thread d_ERR_FILE_OPEN\n", __FUNCTION__, __LINE__);
            usRet = d_ERR_FILE_OPEN;
            pthread_exit("TransDataFile open fail");
            return;
        }

        fseek(fp, 0L, SEEK_END);

        ulFileSize = ftell(fp);
        if (ulFileSize <= 0) {
            printf("[%s,%d] thread ulFileSize <= 0\n", __FUNCTION__, __LINE__);
            fclose(fp);
            pthread_exit("advice file size <=0");
            return;
        }
        if (ulFileSize % sizeof (TRANS_DATA2) != 0) {
            printf("[%s,%d] thread d_ERR_FILE_SIZE_ERR\n", __FUNCTION__, __LINE__);
            fclose(fp);
            usRet = d_ERR_FILE_SIZE_ERR;
            pthread_exit("advice size mismatch");
            return;
        }
        if (TotalCount == 0) {
            printf("[%s,%d] thread TotalCount==0\n", __FUNCTION__, __LINE__);
            pthread_exit("no any advice existed");
            return;
        }
        /*
          if(TotalCount<gOFFLINETXLIMIT){ 
                    return d_OK;
             }*/
        offset = 0;
        //CTOS_EthernetOpen();   
        if (gIDLE == FALSE) {
            printf("[%s,%d] thread not in IDLE UI\n", __FUNCTION__, __LINE__);
            pthread_exit("not in IDLE now");
            return;
        }
        printf("[%s,%d] advice ready to SSLSocketConnect\n",__FUNCTION__,__LINE__);
        usRet = SSLSocketConnect();
        if (usRet != d_OK) {
            printf("[%s,%d] thread sslConect fail\n", __FUNCTION__, __LINE__);
            pthread_exit("ssl connect fail");
            return;
        }


    }


    //   usRet= Eth_SSLConnect_SOCKET();
    //    if(usRet!=d_OK) return usRet;
    do {
        //      sprintf(buf,"%d/%d",iCount,TotalCount);
        //    ShowLine(0,40+40+16+10,Big_Font_Size,buf,FALSE);
        fseek(fp, UpLoadlist[iCount], SEEK_SET);
        iSize = fread((BYTE *) & TransData, sizeof (TRANS_DATA2), 1, fp);
        // if(TransData.ucAdviceFLAG==0){
        if (TransData.ucTXSTATUS == TransStatus_ADVREQ) {
            remove(SendFile);
            usRet = ECC_WriteXmlHeader("TransXML", SendFile);
            vdBuildMessageType2(TransData.ucTXTYPE, TransData.ucTXSTATUS, (BYTE *) & TransData.ucMessageType); //Message Type ID 0100
            vdBuildProcessingCode2((TRANS_DATA2 *) & TransData, (BYTE *) & TransData.ucProcessCode); //Processing Code 0300

            usRet = usBuildTXREQ(&TransData, SendFile);

            usRet = ECC_WriteXmlEND("TransXML", SendFile);
            //  usRet=  Eth_PutDeviecBackOnBase();
            if (gIDLE == FALSE)
                goto Disconnect;
            usRet = Process_TransComm2(&TransData, 0);

            //sprintf(temp, "trans result[%02X]",usRet);
            //CTOS_PrinterPutString(temp);

            // usRet= ECC_CheckAPResponseCode(usRet);

            //sprintf(temp, "check result[%02X]",usRet);
            //CTOS_PrinterPutString(temp);

            if (usRet != d_OK) {
                fclose(fp);
                //usRet= SSLSocketDisConnect();//20141114, kobe modified it
                //                        SSLSocketDisConnect();
                //    Eth_SSLDisconnect();

                goto Disconnect;
            }
            //  usRet= ECC_CheckCMASResponseCode(TransData.ucResponseCode);
            //    if(usRet==d_OK){
            if (strcmp(TransData.ucResponseCode, "00") == 0) {
                TransData.ucTXSTATUS = TransStatus_OK;
                fseek(fp, UpLoadlist[iCount], SEEK_SET);
                fwrite((UCHAR *) & TransData, sizeof (TRANS_DATA2), 1, fp);

            }

        }
        iCount++;
        //      printf("[%s,%d] sendAdvice no.%d\n",__FUNCTION__,__LINE__,iCount);
        //offset+=sizeof(TRANS_DATA2);
        if (iCount >= 100) break;
        printf("[%s,%d]loop\n",__FUNCTION__,__LINE__);
    } while (iCount < TotalCount);
    fclose(fp);




    // usRet= SSLSocketDisConnect();
Disconnect:
    //  Eth_SSLSocketDisConnect();       
    SSLSocketDisConnect();

    printf("[%s,%d] sendAdvice in Background end\n", __FUNCTION__, __LINE__);
    pthread_exit("send Advice finish");
}

USHORT Process_SendAdvice3(BYTE SettleFlag) {
    ULONG offset;
    int iSize;
    int inRetVal;
    int iCount = 0;
    STR buf[64];
    BYTE temp[512];
    TRANS_DATA2 TransData;
    USHORT TotalCount;
    memset(buf, 0x00, sizeof (buf));

    // gOFFLINETXLIMIT=5;
    long UpLoadlist[1000];
    memset(&UpLoadlist, 0x00, sizeof (UpLoadlist));
    USHORT usRet = GetUnuploadTx2(&TotalCount, (long *)UpLoadlist);
    if (SettleFlag != 1) {
        if (usRet == d_OK) {
            if (TotalCount < gOFFLINETXLIMIT) {
                // if(TotalCount<10){
                return d_OK;
            }
        }
    }

    if (TotalCount == 0) return d_OK;
    
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    CTOS_LCDGClearCanvas();
    ShowTitle(gTransTitle);
    ShowLine(0, 40 + 16, Big_Font_Size, "帳務資料上傳中.", FALSE);


    remove(SendFile);
    FILE *fp = fopen(TransDataFile, "r+");
    if (fp == NULL) {
        usRet = d_ERR_FILE_OPEN;
        goto Disconnect;
    }

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) {
        fclose(fp);
        return d_ERR_FILE_NOTEXIST;
    }
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) {
        fclose(fp);
        usRet = d_ERR_FILE_SIZE_ERR;
        return d_ERR_FILE_NOTEXIST;

    }
    offset = 0;
    //CTOS_EthernetOpen();   
    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
    usRet = SSLSocketConnect();
    if (usRet != d_OK) {
        return usRet;
    }
    ShowMessage2line(gTransTitle, "交易資料上傳中", "", Type_ComformNONE);
    //   usRet= Eth_SSLConnect_SOCKET();
    //    if(usRet!=d_OK) return usRet;
    do {
        sprintf(buf, "%d/%d", iCount, TotalCount);
        ShowLine(0, 40 + 40 + 16 + 10, Big_Font_Size, buf, FALSE);
        fseek(fp, UpLoadlist[iCount], SEEK_SET);
        iSize = fread((BYTE *) &TransData, sizeof (TRANS_DATA2), 1, fp);
        // if(TransData.ucAdviceFLAG==0){
        if (TransData.ucTXSTATUS == TransStatus_ADVREQ) {
            remove(SendFile);
            usRet = ECC_WriteXmlHeader("TransXML", SendFile);
            vdBuildMessageType2(TransData.ucTXTYPE, TransData.ucTXSTATUS, (BYTE *) & TransData.ucMessageType); //Message Type ID 0100
            vdBuildProcessingCode2((TRANS_DATA2 *) & TransData, (BYTE *) & TransData.ucProcessCode); //Processing Code 0300

            usRet = usBuildTXREQ(&TransData, SendFile);

            usRet = ECC_WriteXmlEND("TransXML", SendFile);
            usRet = Eth_PutDeviecBackOnBase();
            usRet = Process_TransComm2(&TransData, 0);

           

            if (usRet != d_OK) {
                fclose(fp);           
                goto Disconnect;
            }
            
            if (strcmp(TransData.ucResponseCode, "00") == 0) {
                TransData.ucTXSTATUS = TransStatus_OK;
                fseek(fp, UpLoadlist[iCount], SEEK_SET);
                fwrite((UCHAR *) &TransData, sizeof (TRANS_DATA2), 1, fp);

            }

        }
        iCount++;
        if (iCount >= 1000) break;
    } while (iCount < TotalCount);
    fclose(fp);
    // usRet= SSLSocketDisConnect();
Disconnect:
    //  Eth_SSLSocketDisConnect();       
    SSLSocketDisConnect();


    return d_OK;

}

void Thread_SendCurrentTxAdvice() {
    int kill_rc;
    while (1) {
        kill_rc = pthread_kill(thread_AfterTxSuccess, 0);
        if (kill_rc != ESRCH)
            continue;
        else
            break;
    }
    printf("[%s,%d] create Thread\n", __FUNCTION__, __LINE__);
    pthread_create(&thread_AfterTxSuccess, NULL, (void *) Process_SendCurrentTxAdvice, NULL); // 執行緒 SSLSocketConnect 
}

USHORT Process_SendCurrentTxAdvice() {
    USHORT usRet;
    if (gTransData.ucTXSTATUS != TransStatus_ADVREQ) {
        pthread_exit("Advice Not Need");
        return usRet;
    }
    usRet = SSLSocketConnect();
    if (usRet != d_OK) {
        //   MessageBox(gTransTitle,"","網路連線異常","請檢查並重試","",d_MB_CHECK);
        pthread_exit("SSLCONNECT FAIL");
        return usRet;
    }
    if (gTransData.ucTXSTATUS == TransStatus_ADVREQ) {
        usRet = Process_TransComm2(&gTransData, 0);
        if (usRet != d_OK) {
            pthread_exit("COMM Fail");
            return d_Fail;
        }
        if (strcmp(gTransData.ucResponseCode, "00") == 0) {
            gTransData.ucTXSTATUS = TransStatus_OK;
            usRet = usUpdataTxData(&gTransData);
        }
    }
DISCONNECT:
    SSLSocketDisConnect();
    pthread_exit("Process Finish");
    return usRet;

}

USHORT Process_SendCurrentTxAdvice2() {
    USHORT usRet;
    if (gTransData.ucTXSTATUS != TransStatus_ADVREQ) {

        return usRet;
    }

    if (gTransData.ucTXSTATUS == TransStatus_ADVREQ) {
        usRet = Process_TransComm2(&gTransData, 0);
        if (usRet != d_OK) {

            return d_Fail;
        }
        if (strcmp(gTransData.ucResponseCode, "00") == 0) {
            gTransData.ucTXSTATUS = TransStatus_OK;
            usRet = usUpdataTxData(&gTransData);
        }
    }

    return usRet;

}

USHORT Process_SendAdvice2(BYTE SettleFlag) {
    SystemLog("Process_SendAdvice2", "Start");
    ULONG offset;
    int iSize;
    int inRetVal;
    int iCount = 0;
    STR buf[64];
    TRANS_DATA2 TransData;
    int TotalCount;
    memset(buf, 0x00, sizeof (buf));
    TotalCount = CheckUnuploadTxCount();
    // if(SettleFlag==0){
    if (TotalCount < gOFFLINETXLIMIT) return d_OK;
    //   }

    USHORT DispLine1Y = 40 + 16, DispLine2Y = 120 + 16, DispLine3Y = 120 + 16;
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    CTOS_LCDGClearCanvas();
    ShowTitle(gTransTitle);
    ShowLine(0, 40 + 16, Big_Font_Size, "帳務資料上傳中.", FALSE);


    remove(SendFile);
    FILE *fp = fopen(TransDataFile, "r+");
    if (fp == NULL)
        return d_ERR_FILE_OPEN;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;
    offset = 0;
    USHORT usRet;

    do {
        sprintf(buf, "%d/%d", iCount, TotalCount);
        ShowLine(0, 40 + 40 + 16, Big_Font_Size, buf, FALSE);
        fseek(fp, offset, SEEK_SET);
        iSize = fread((BYTE *) & TransData, sizeof (TRANS_DATA2), 1, fp);
        // if(TransData.ucAdviceFLAG==0){
        if (TransData.ucTXSTATUS == TransStatus_ADVREQ) {
            remove(SendFile);
            usRet = ECC_WriteXmlHeader("TransXML", SendFile);
            vdBuildMessageType2(TransData.ucTXTYPE, TransData.ucTXSTATUS, (BYTE *) & TransData.ucMessageType); //Message Type ID 0100
            vdBuildProcessingCode2(&TransData, (BYTE *) TransData.ucProcessCode); //Processing Code 0300
            usRet = usBuildTXREQ(&TransData, SendFile);
            usRet = ECC_WriteXmlEND("TransXML", SendFile);
            usRet = Process_TransComm2(&TransData, 1);
            usRet = ECC_CheckAPResponseCode(usRet);
            if (usRet != d_OK) return usRet;
            usRet = ECC_CheckCMASResponseCode(TransData.ucResponseCode);
            if (usRet == d_OK) {

                TransData.ucTXSTATUS = TransStatus_OK;
                fseek(fp, offset, SEEK_SET);
                fwrite((UCHAR *) & TransData, sizeof (TRANS_DATA2), 1, fp);
                iCount++;

            }
        }

        offset += sizeof (TRANS_DATA2);

    } while (offset < ulFileSize);
    fclose(fp);
    return d_OK;

}

USHORT Process_SendOfflineTxAdvice() {
    SystemLog("Process_SendOfflineTxAdvice", "Start");
    int TotalCount = CheckUnuploadTxCount();
    if (TotalCount < gOFFLINETXLIMIT) return d_OK;

    USHORT ret = Process_SendAdvice3(0);

}

/*
USHORT Process_SendAdvice(BYTE SettleFlag)
{
   SystemLog("Process_SendAdvice","Start");
   USHORT TotalCount;   
   remove(SendFile);
   remove(RecvFile);
   USHORT  usRet= GetUnuploadTx(&TotalCount);
   if(SettleFlag!=1){
    if(usRet==d_OK){
      //  if(TotalCount<gOFFLINETXLIMIT){ 
          if(TotalCount<3){ 
            return d_OK;
        }
    }
   }
      
   if(TotalCount==0) return d_OK;  
      
    USHORT Uploadcount=BuildAdviceTxFile();
    if(Uploadcount==0) return d_OK;
  
   
    USHORT ret= SSLSocketSendandRecv();
    if(ret!=d_OK){
          SystemLogInt("Process_TransComm2", ret,"SSLSocketSendandRecv");
          return ret;
    }	
   // BatchUpdateInvoiceNum();
    SendDebugFile(SendFile);
    SendDebugFile(RecvFile);
    ret= UpdateAdviceTxStatus();
}*/
USHORT Process_SendReversal() {
    SystemLog("Process_SendReversal", "Start");
    TRANS_DATA2 ReversalData;
    ULONG ulret = File_GetLen(ReversalFile);
    if (ulret > 0)
        copyFiles(ReversalFile, SendFile);
    else
        return d_OK;
    // USHORT usRet=SendReceiveData_CallCOMMThread();
    // USHORT usRet= Eth_SSLSendandRecv_Socket();
    USHORT usRet = SSLSocketSendandRecv2(0);
    if (usRet != d_OK) {
        //        MechineStatus |= Status_ETHERNET_Disconnect;	
        SystemLogInt("Process_SendReversal", usRet, "SSLSocketSendandRecv2");
        return usRet;
    }
    //   MechineStatus = (~(Status_ETHERNET_Disconnect));


    SendDebugFile(SendFile);
    SendDebugFile(RecvFile);

    usRet = usUnPackResponData(&ReversalData);
    if (usRet != d_OK) return usRet;
    remove(ReversalFile);

    return d_OK;
}

USHORT Process_TransComm2(TRANS_DATA2 *TransData, BYTE dispstatus) {
    SystemLog("Process_TransComm", "Start");
    USHORT usRet;

    ezxml_t CMASRESP;
    /*
     usRet=Ethernet_Status_Check();
      if(usRet!=d_OK){
           if(dispstatus)  
                   MessageBox(gTransTitle,"","網路連線異常","請檢查並重試","",d_MB_CHECK);
          return usRet;
      }  */
    if (dispstatus)
        ShowStatusLine("資料準備中...");
    usRet = Process_SendReversal();
    if (usRet != d_OK) {
        SystemLogInt("Process_TransComm", usRet, "Process_SendReversal");
        return usRet;
    }
    vdBuildMessageType2(TransData->ucTXTYPE, TransData->ucTXSTATUS, (BYTE *) & TransData->ucMessageType); //Message Type ID 0100

    vdBuildProcessingCode2(TransData, (BYTE *) TransData->ucProcessCode); //Processing Code 0300

    SaveTransData(TransData);
    if (dispstatus)
        ShowStatusLine("資料上傳中...");
    // ShowMessage2line(gTransTitle,"網路傳輸","資料上傳中",Type_ComformNONE);
#ifdef TESTMODE
    if (gScrpitTesting == 1) {
        if (TransData->ucTXSTATUS == TransStatus_REQ) {
            CMASRESP = ezxml_get(gTestAction, "CMASRESPONSE", 0, "TransXML", -1);
        } else if (TransData->ucTXSTATUS == TransStatus_ADVREQ) {
            CMASRESP = ezxml_get(gTestAction, "CMASADVRESPONSE", 0, "TransXML", -1);
        }
        if (CMASRESP != NULL) {
            BYTE * strbuf;
            strbuf = ezxml_toxml(CMASRESP);
            usRet = usWriteFile(RecvFile, (BYTE *) strbuf, strlen(strbuf));
        } else {
            //usRet=Eth_SSLSendandRecv_Socket();
            usRet = SSLSocketSendandRecv2(dispstatus);
            // usRet= SSLSocketSendandRecv();

            //       usRet= Eth_SSLSocketSendandRecv(bgNETWORKChannel); 
            //usRet= Eth_SSLSocketSendandRecv_CURL();
            if (usRet != d_OK) {
                //MechineStatus |= Status_ETHERNET_Disconnect;	
                SystemLogInt("Process_TransComm", usRet, "SSLSocketSendandRecv");
                return usRet;
            }
            //  MechineStatus &= (~(Status_ETHERNET_Disconnect));
            //     BatchUpdateInvoiceNum();
            SendDebugFile(SendFile);
            Debug_SendData("Receive", gReceiveData, strlen(gReceiveData));

        }
    } else {
#endif     
        //    usRet=SendReceiveData_CallCOMMThread();
        usRet = SSLSocketSendandRecv2(dispstatus);
        //usRet=Eth_SSLSendandRecv_Socket();
        // usRet= SSLSocketSendandRecv();   
        //   usRet= GPRS_SSLSocketSendandRecv();
        //  usRet= Eth_SSLSocketSendandRecv(bgNETWORKChannel); 
        //   usRet= Eth_SSLSocketSendandRecv_CURL();
        //   CTOS_EthernetClose();
        // Eth_SSLDisconnect();
        if (usRet != d_OK) {
            SystemLogInt("Process_TransComm", usRet, "SSLSocketSendandRecv");
            return usRet;
        }

        //MechineStatus &= (~(Status_ETHERNET_Disconnect));
        SaveTCPDatatoSD(SendFile, gReceiveData, strlen(gReceiveData));
        SendDebugFile(SendFile);
        Debug_SendData("Receive", gReceiveData, strlen(gReceiveData));

#ifdef TESTMODE          
    }
#endif    
    if (dispstatus)
        ShowStatusLine("資料交換完成");

    usRet = usUnPackResponData(TransData);

    if (usRet != d_OK) return usRet;

    TransData->ucTXSTATUS++;

    remove(SendFile);

    return d_OK;
}
//thread專用

USHORT Process_TransComm(TRANS_DATA2 *TransData, BYTE dispstatus) {
    SystemLog("Process_TransComm", "Start");
    USHORT usRet;
    ezxml_t CMASRESP;
    if (dispstatus)
        ShowStatusLine("資料準備中...");


    usRet = Process_SendReversal();

    vdBuildMessageType2(TransData->ucTXTYPE, TransData->ucTXSTATUS, (BYTE *) & TransData->ucMessageType); //Message Type ID 0100
    vdBuildProcessingCode2(TransData, (BYTE *) TransData->ucProcessCode); //Processing Code 0300
    SaveTransData(TransData);
    if (dispstatus)
        ShowStatusLine("資料上傳中...");
    // ShowMessage2line(gTransTitle,"網路傳輸","資料上傳中",Type_ComformNONE);
#ifdef TESTMODE
    if (gScrpitTesting == 1) {
        if (TransData->ucTXSTATUS == TransStatus_REQ) {
            CMASRESP = ezxml_get(gTestAction, "CMASRESPONSE", 0, "TransXML", -1);
        } else if (TransData->ucTXSTATUS == TransStatus_ADVREQ) {
            CMASRESP = ezxml_get(gTestAction, "CMASADVRESPONSE", 0, "TransXML", -1);
        }
        if (CMASRESP != NULL) {
            BYTE * strbuf;
            strbuf = ezxml_toxml(CMASRESP);
            usRet = usWriteFile(RecvFile, (BYTE *) strbuf, strlen(strbuf));
        } else {
            //  usRet= SSLSocketSendandRecv2(dispstatus);
            usRet = WaitSSLSendReceive();
            if (usRet != d_OK) {
                //MechineStatus |= Status_ETHERNET_Disconnect;	
                SystemLogInt("Process_TransComm", usRet, "SSLSocketSendandRecv");
                return usRet;
            }
            //  MechineStatus &= (~(Status_ETHERNET_Disconnect));
            //     BatchUpdateInvoiceNum();
            SendDebugFile(SendFile);
            Debug_SendData("Receive", gReceiveData, strlen(gReceiveData));
        }
    } else {
#endif     

        //usRet= SSLSocketSendandRecv2(dispstatus);
        usRet = WaitSSLSendReceive();
        if (usRet != d_OK) {
            //MechineStatus |= Status_ETHERNET_Disconnect;	
            SystemLogInt("Process_TransComm", usRet, "SSLSocketSendandRecv");
            return usRet;
        }
        if (usRet != d_OK) {
            // MechineStatus |= Status_ETHERNET_Disconnect;	
            SystemLogInt("Process_TransComm", usRet, "SSLSocketSendandRecv");
            return usRet;
        }

        // MechineStatus &= (~(Status_ETHERNET_Disconnect));
        //     BatchUpdateInvoiceNum();
        SendDebugFile(SendFile);
        Debug_SendData("Receive", gReceiveData, strlen(gReceiveData));

#ifdef TESTMODE          
    }
#endif    
    if (dispstatus)
        ShowStatusLine("資料交換完成");
    usRet = usUnPackResponData(TransData);
    if (usRet != d_OK) return usRet;
    /*      if(strcmp(TransData->ucMessageType,gWaitMsgType)!=0)
          {
               SystemLog("Process_TransComm","Receive wrong message");
              return d_ERR_WRONG_MESSAGE; 
          }*/

    //  ShowMessage2line(gTransTitle,"網路傳輸","資料上傳完成",Type_ComformNONE);
    //ezxml_free(CMASRESP);


    TransData->ucTXSTATUS++;

    return d_OK;
}

USHORT Process_Settle() {
    Batch_Totle_STRUCT BatchTotal;
    SystemLog("Process_Settle", "Start");
    //USHORT usRet=Config_GetData();
    // USHORT usRet= Sysinfo2_GetData();
    int kill_rc;
    Reset_TM_In InData; //)cInputData
    USHORT ret = GetBatchTotal();
    sprintf(gTransTitle, "結帳");

    USHORT TXCount = CheckBatchCount();
    

    if (TXCount == 0) {
        ret = ShowMessage2line(gTransTitle, "目前無交易", "無需結帳!!", Type_ComformOK);
        //return d_OK;
        return ECR_NO_RECORD_NO_NEEDED_SETTLE;
    }

    //20141107, kobe modified, do not show ECR_UNUPLOADED_EXISTED_SETTLE_AGAIN directly
    if ((ret = Process_SendAdvice3(1)) != d_OK)
        return ret;
    //ret=  Process_SendAdvice3(1);
    //sprintf(temp, "ret(%02X)",ret);
    //CTOS_PrinterPutString(temp);
    // ret=pthread_create(&Thread_Comm, NULL,(void*) SSLSocketConnect_thread, NULL);   
    int TotalCount = CheckUnuploadTxCount();
    if (TotalCount != 0) {
        ret = ShowMessage2line(gTransTitle, "尚有交易未上傳", "請重試結帳!!", Type_ComformOK);
        //return d_OK;
        //CTOS_PrinterPutString("ECR_TRY_SETTLE_AGAIN");
        return ECR_TRY_SETTLE_AGAIN;
    }

    if (!ecrObj.gData.isEcrTxn)//2014.10.30, kobe added it, if merchant need detail, press'F4' to print before settle
        ret = CheckPrintTXDetail();



    ret = ShowMessage2line(gTransTitle, "是否確認進行結帳?", "", Type_ComformOK);
    if (ret != d_OK) {
        return ret;
    }
    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
    ret = SSLSocketConnect();
    if (ret != d_OK) {
        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
        return ret;
    }


    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    CTOS_LCDGClearCanvas();
    ShowTitle(gTransTitle);
    ShowLine(0, 40 + 16, Big_Font_Size, "結帳作業中.", FALSE);


    usInitTxData(TXTYPE_SETTLEMENT); //初始交易資料  
    gTransData.ulSettle_TotleCnt = gBatchTotal.TotleCnt;
    gTransData.lSettle_TotleAmt = gBatchTotal.TotleAMT;
    gTransData.ucTXSTATUS = TransStatus_REQ;

    /*while(1){
               kill_rc = pthread_kill(Thread_Comm,0);
               if(kill_rc==ESRCH) break;
             
            }*/
    ShowMessage2line(gTransTitle, "結帳作業中..", "請稍候。", Type_ComformNONE);
    ret = Eth_PutDeviecBackOnBase();
    ret = Process_TransComm2(&gTransData, 1);
    ECC_CheckAPResponseCode(ret);
    if (ret != d_OK) {
        ShowMessage2line(gTransTitle, "結帳失敗", "請重試", Type_ComformAnykey);
        goto DISCONNECT;
    }
    ret = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
    if (ret != d_OK) {
        goto DISCONNECT; //return ret;
    }
    ShowStatusLine("已完成");

    remove(SettleFile);
    PrintSettlementReceipt(&gBatchTotal);
    ret = usCloseBatch();
    if (ret == d_OK) {
        //  MessageBox(gTransTitle,"","結帳完成!!","","",d_MB_CHECK);
        CheckNewVersionAP();
        CheckMemoarystatus();
        if (ecrObj.ecrOn) ezSystemReset(); //kobe added for V15, forced reboot
        if (ShowMessage2line(gTransTitle, "結帳完成", "是否關機?", Type_ComformOK) == d_OK) {
            ezPowerOff();
        } else {
            ezSystemReset();
        }

        //     ret=UnpackTMSParameter();


        // CheckNewVersionAP();


    }
DISCONNECT:
    //   Eth_SSLSocketDisConnect();       
    SSLSocketDisConnect();
    if (ret == d_OK) {
        CTOS_Delay(1000);
        Function_Signon();
    }
    return ret;
}

USHORT CheckSignOnPassword() {
    BYTE buf[15 + 1];
    USHORT ret;
    SystemLog("CheckSignOnPassword", "Start");

    /*2014-03-31 kobe added for ECR needed pwd*/
    if (ecrObj.gData.isEcrTxn) {
        strcpy(buf, ecrObj.ngData->pwd);
    } else {
        memset(buf, 0x00, sizeof (buf));
        //   if(strlen(gConfig.MERCHANT.PASSWORD)<=0)  
        //          return d_ERR_NO_PASSWORD;            
        ret = ShowInputBox(gTransTitle, "請輸入登入密碼", buf, 15, INPUT_TYPE_Number, '*');
        if (ret != d_OK) {
            return d_ERR_USERCANCEL;
        }
    }


    /* if(strcmp(buf,gConfig.MERCHANT.PASSWORD)!=0)         
     {
         return d_ERR_WRONGPASSWORD ;
     }*/
    if (CheckFunctionpPassword("SIGNON", buf) != TRUE) {
        return d_ERR_WRONGPASSWORD;
    }
    return d_OK;
}

USHORT Process_StatusReport() {
    SystemLog("Process_StatusReport", "Start");
    USHORT usRet;
    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
    usRet = SSLSocketConnect();
    if (usRet != d_OK) {
        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
        return usRet;
    }
    usInitTxData(TXTYPE_REPORT);
    gTransData.ucTXSTATUS = TransStatus_REQ;
    usRet = Process_TransComm2(&gTransData, 1);
    ECC_CheckAPResponseCode(usRet);
    if (usRet != d_OK) return usRet;

    SSLSocketDisConnect();
    return usRet;
}

USHORT Process_SignOn()//sign on 交易
{
    SystemLog("Process_SignOn", "Start");
    int inOutLen, inRecvlen;
    STR * HostIP;
    int PORT, iret;
    USHORT usRet;
    int TotlePackCnt = 0;
    int SendedPackCnt = 0;
    int ReceivedPackCnt = 0;
    int SendPackSN = 0;
    SAMParaSetting_t SPSD;
    USHORT DispLine1Y = 40 + 16, DispLine2Y = 120 + 16, DispLine3Y = 120 + 16;
    Reset_TM_In InData; //)cInputData
    BYTE SignONflag = 1;

    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    //   CTOS_EthernetOpen();


    remove(TMSFILE);
    //  do{    
    //   while(1){
    usRet = usInitTxData(TXTYPE_SIGNON); //初始交易資料
    ECC_CheckAPResponseCode(usRet);
    if (usRet != d_OK) return usRet;

    CTOS_LCDGClearCanvas();
    ShowTitle(gTransTitle);


    ShowLine(0, 40 + 16, Big_Font_Size, "資料傳輸中.", FALSE);
    ShowStatusLine("Reader Reset...");

    // CTOS_LCDGTextOut(0,40+16,"讀卡機連線中...",Big_Font_Size,FALSE); 
    // CTOS_LCDGTextOut(0,120+16,"請稍候",Big_Font_Size,FALSE);     
    // ShowMessage2line(gTransTitle,"通訊中...","請稍候",Type_ComformNONE);
    sprintf(gTransfer_TotlePackCnt, "%08d", TotlePackCnt);
    sprintf(gTransfer_SendedPackCnt, "%08d", SendedPackCnt);
    sprintf(gTransfer_ReceivedPackCnt, "%08d", ReceivedPackCnt);
    sprintf(gTransfer_SendPackSN, "%08d", SendPackSN);

    iret = inPPR_Reset(1);
    usRet = ECC_CheckReaderResponseCode(iret);
    if (usRet != d_OK) return usRet;


    ShowStatusLine("通訊中...");

    gTransData.ucTXSTATUS = TransStatus_REQ;
    usRet = Process_TransComm2(&gTransData, 1);
    ECC_CheckAPResponseCode(usRet);
    if (usRet != d_OK) return usRet;

    ShowStatusLine("已完成");

    usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
    if (strcmp(gTransData.ucResponseCode, "19") == 0) {
        SetTransSN(gTransData.ulTerminalInvoiceNum);

    }
    if (usRet != d_OK) {

        return usRet;
    }

    /*    
    if(gDebugFTPFlag){
        gTransData.ucTXTYPE=TXTYPE_DEBUG;
        SaveTransData(&gTransData);
    }
     */
    TotlePackCnt = atoi(gTransfer_TotlePackCnt);
    SendedPackCnt = atoi(gTransfer_SendedPackCnt);
    ReceivedPackCnt = atoi(gTransfer_ReceivedPackCnt);
    SendPackSN = atoi(gTransfer_SendPackSN);
    ReceivedPackCnt++;
    //if(TotlePackCnt>0){
    //	if(TotlePackCnt==ReceivedPackCnt)
    //	{

    //	}
    //}else{
    ShowLine(0, 40 + 16, Big_Font_Size, "資料傳輸中..", FALSE);
    ShowStatusLine("Reader SignOn...");

    iret = inPPR_SignOn();
    // if(iret==0x6308)
    //   continue;
    usRet = ECC_CheckReaderResponseCode(iret);
    if (usRet != d_OK) return usRet;

    usRet = UpdateTransSN();
    //}
    //       break;
    // }            
    // CTOS_Delay(1000);
    // }while(TotlePackCnt>ReceivedPackCnt);    


    //  iret=wub_str_2_hex((char*)&TransData.CSAMPARA, (char *)&SPSD,sizeof(TransData.CSAMPARA)-1);
    // SignONflag=SPSD.ucSAMUpdateOption & 0x80;
    //  CTOS_Delay ( 1000 );  

    gTransData.ucTXSTATUS = TransStatus_ADVREQ;
    usRet = usGetCurrTransSN((int*) &gTransData.usTXSN);
    memcpy(&gTransData.ulTerminalInvoiceNum, &gTransData.usTXSN, sizeof (gTransData.ulTerminalInvoiceNum));
    sprintf(gTransData.ucRRN, "%s%06ld", gTransData.ucTxnData, gTransData.usTXSN);

    usRet = Process_TransComm2(&gTransData, 1);
    //    if(usRet!=d_OK) return usRet;
    //  CTOS_EthernetClose();
    SetRTC((BYTE *) & gTxnData, (BYTE *) & gTxnTime);
    //  MessageBox(gTransTitle,"","系統登入完成!!","","",d_MB_CHECK);

    CTOS_TimeOutSet(TIMER_ID_1, gSignOnlimit);
    return usRet;
}

USHORT uCheckSignOnTime(unsigned long * LastSignonTime) {
    SystemLog("uCheckSignOnTime", "Start");
    USHORT usRet;
    unsigned long RTCTime, diffTime;
    fnGetRTCUNIXDataTime(&RTCTime);

    diffTime = (RTCTime - *LastSignonTime);
    if (diffTime < (60 * 60 * 24))
        usRet = d_ERR_RESP_SIGNON;
    else usRet = d_OK;

    return usRet;
}

USHORT Process_SignOn2(void)//sign on 交易
{
    SystemLog("Process_SignOn", "Start");
    int inOutLen, inRecvlen;
    STR * HostIP;
    int PORT, iret;
    USHORT usRet;
    int TotlePackCnt = 0;
    int SendedPackCnt = 0;
    int ReceivedPackCnt = 0;
    int SendPackSN = 0;
    SAMParaSetting_t SPSD;
    USHORT DispLine1Y = 40 + 16, DispLine2Y = 120 + 16, DispLine3Y = 120 + 16;
    Reset_TM_In InData; //)cInputData
    BYTE SignONflag = 1;
    BYTE buffer[32];
    int kill_rc;
    /*usRet= Eth_SocketCheckConnectStatus();
    if(usRet!=d_OK) {
        usRet= Eth_SSLConnect_SOCKET();
        if(usRet!=d_OK) return usRet;
    }*/
    //  usRet= SSLSocketConnect();
    //  if(usRet!=d_OK) return usRet;
    usRet = Ethernet_Status_Check();
    if (usRet != d_OK) {
        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
        return usRet;
    }
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    ShowMessage2line(gTransTitle, "資料傳輸中..", "請稍候。", Type_ComformNONE);
    ShowLine(0, 40 + 16, Big_Font_Size, "主機連線中...", FALSE);
    remove(TMSFILE);
    USHORT mkHWSupport = Eth_CheckDeviceSupport();
    if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
        CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
    }
    do {
        //   while(1){

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        usRet = usInitTxData(TXTYPE_SIGNON); //初始交易資料

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        usRet = ECC_CheckAPResponseCode(usRet);
        if (usRet != d_OK) goto SSL_DISCONNECT;

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        CTOS_LCDGClearCanvas();
        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        ShowTitle(gTransTitle);


        ShowLine(0, 40 + 16, Big_Font_Size, "資料傳輸中.", FALSE);
        ShowStatusLine("Reader Reset...");

        // CTOS_LCDGTextOut(0,40+16,"讀卡機連線中...",Big_Font_Size,FALSE); 
        // CTOS_LCDGTextOut(0,120+16,"請稍候",Big_Font_Size,FALSE);     
        // ShowMessage2line(gTransTitle,"通訊中...","請稍候",Type_ComformNONE);
        sprintf(gTransfer_TotlePackCnt, "%08d", TotlePackCnt);
        sprintf(gTransfer_SendedPackCnt, "%08d", SendedPackCnt);
        sprintf(gTransfer_ReceivedPackCnt, "%08d", ReceivedPackCnt);
        sprintf(gTransfer_SendPackSN, "%08d", SendPackSN);

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        iret = inPPR_Reset(1);

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        usRet = ECC_CheckReaderResponseCode(iret);
        if (usRet != d_OK) goto SSL_DISCONNECT;

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        //2014.05.26, kobe added it
        //if((usRet = ResetDongle()) != d_OK)
        //    return usRet;

        ShowStatusLine("通訊中...");
        remove(SendFile);

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        gTransData.ucTXSTATUS = TransStatus_REQ;

        usRet = Process_TransComm2(&gTransData, 1);

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        usRet = ECC_CheckAPResponseCode(usRet);
        if (usRet != d_OK) goto SSL_DISCONNECT;
        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);


        ShowStatusLine("已完成");


        if (strcmp(gTransData.ucResponseCode, "19") == 0) {
            SetTransSN(gTransData.ulTerminalInvoiceNum + 1);
            continue;
        }

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
        if (usRet != d_OK) goto SSL_DISCONNECT;

        TotlePackCnt = atoi(gTransfer_TotlePackCnt);
        SendedPackCnt = atoi(gTransfer_SendedPackCnt);
        ReceivedPackCnt = atoi(gTransfer_ReceivedPackCnt);
        SendPackSN = atoi(gTransfer_SendPackSN);
        ReceivedPackCnt++;
        //if(TotlePackCnt>0){
        //	if(TotlePackCnt==ReceivedPackCnt)
        //	{

        //	}
        //}else{
        ShowLine(0, 40 + 16, Big_Font_Size, "資料傳輸中..", FALSE);
        ShowStatusLine("Reader SignOn...");

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        iret = inPPR_SignOn();

        if (iret == 0x6308) {// 2014.08.25, reader 回6308 表示需重作sigon 直接進continue
            usRet = UpdateTransSN();
            continue;
        }
        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);

        usRet = ECC_CheckReaderResponseCode(iret);
        if (usRet != d_OK) {
            goto SSL_DISCONNECT;
        }

        printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        usRet = UpdateTransSN();
        //Process_DownloadTMS();  //2014.07.30, V11fixed bug for Updated AP
        //UnpackTMSParameter();   //2014.07.30, V11fixed bug for Updated AP
        //}
        //       break;
        // }            

    } while ((TotlePackCnt > ReceivedPackCnt) || (strcmp(gTransData.ucResponseCode, "19") == 0));

    //  iret=wub_str_2_hex((char*)&TransData.CSAMPARA, (char *)&SPSD,sizeof(TransData.CSAMPARA)-1);
    // SignONflag=SPSD.ucSAMUpdateOption & 0x80;
    // CTOS_Delay ( 1000 );  

    gTransData.ucTXSTATUS = TransStatus_ADVREQ;
    usRet = usGetCurrTransSN((int*) &gTransData.usTXSN);
    memcpy(&gTransData.ulTerminalInvoiceNum, &gTransData.usTXSN, sizeof (gTransData.ulTerminalInvoiceNum));
    sprintf(gTransData.ucRRN, "%s%06ld", gTransData.ucTxnData, gTransData.usTXSN);

    remove(SendFile);

    usRet = ECC_WriteXmlHeader("TransXML", SendFile);

    vdBuildMessageType2(gTransData.ucTXTYPE, gTransData.ucTXSTATUS, (BYTE *) & gTransData.ucMessageType); //Message Type ID 0100

    vdBuildProcessingCode2((TRANS_DATA2 *) & gTransData, (BYTE *) & gTransData.ucProcessCode); //Processing Code 0300

    usRet = usBuildTXREQ(&gTransData, SendFile);

    usRet = ECC_WriteXmlEND("TransXML", SendFile);
    /*  while(1){
               kill_rc = pthread_kill(Thread_Comm,0);
               if(kill_rc==ESRCH) break;
               ShowMessage2line(gTransTitle,"資料傳輸中..","請稍候。",Type_ComformNONE);
      }*/
    usRet = Process_TransComm2(&gTransData, 1);


    // usRet= Process_TransComm(&gTransData);



    //    if(usRet!=d_OK) return usRet;
    //  CTOS_EthernetClose();
    SetRTC((BYTE *) & gTxnData, (BYTE *) & gTxnTime);
    //  MessageBox(gTransTitle,"","系統登入完成!!","","",d_MB_CHECK);
SSL_DISCONNECT:
    //  SSLSocketDisConnect();
    //Eth_SSLDisconnect();
    CTOS_TimeOutSet(TIMER_ID_1, gSignOnlimit);

    return usRet;
}

int Process_SignOnRequest(TRANS_DATA2 *TransData) {
    int inOutLen;
    SystemLog("Process_SignOnRequest", "Start");
    //    BYTE anLastTxnDateTime[14+1];

    int iret = inPPR_SignOnQuery();

    USHORT usRet = ECC_CheckReaderResponseCode(iret);

    if (usRet == d_OK) {
        usRet = uCheckSignOnTime((ULONG *) & gSOQ_OUT.ucLastTxnDateTime);

    }
    if (usRet == d_ERR_RESP_SIGNON) {
        Process_SignOn2();

        usRet = ECC_CheckReaderResponseCode(iret);
    }

    return usRet;
}

int iProcess_ReadCardBasicData() {
    int inOutLen;
    SystemLog("iProcess_ReadCardBasicData", "Start");
    gucLockReason = 0;

    //  ShowMessage2line(gTransTitle,"請將悠遊卡","放上讀卡機",Type_ComformNONE);  

    int inRetVal = inPPR_ReadCardBasicData();
    if (inRetVal == SW_ERROR) return inRetVal;


    if ((inRetVal == 0x6103) || (inRetVal == 0x640E) || (inRetVal == 0x610F) || (inRetVal == 0x6418))
        //if((inRetVal == 0x6103)||(inRetVal == 0x640E))
    {
        inRetVal = iProcess_LogLockCardData(inRetVal);
    } else if (inRetVal == 0x9000) {
        inRetVal = iProcess_CheckBlockCard((BYTE *) & gBasicData.ucCardID);
    }

    return inRetVal;
}


int iProcessWaitCard(void) {
    USHORT usRet;
    BYTE key;
    int inOutLen, iret;
    SystemLog("iProcessWaitCard", "Start");
    ShowTitle(gTransTitle);
    USHORT mkHWSupport = Eth_CheckDeviceSupport();
    if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
        CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
    }
    Setcolor(Color_white, Color_black);
    ShowLine(0, 40 + 50, Big_Font_Size, "請將悠遊卡.", FALSE);
    ShowLine(0, 40 + 50 * 2, Big_Font_Size, "放上讀卡機.", FALSE);
    ShowStatusLine("離開請按<X>離開");
    //  ShowMessage3line(gTransTitle,"請將悠遊卡","放上讀卡機","離開請按<X>離開",Type_ComformNONE);  

    do {
        mkHWSupport = Eth_CheckDeviceSupport();
        if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
            CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
        }
        //Sysinfo2_GetEDCSystemMemoryStatus();
        CTOS_LCDGTextOut(0, 240 - 18 - 18 - 25, gConfig.DEVICE.MEMORY.USEDRAMSIZE, d_FONT_9x18, FALSE);
        CTOS_KBDBufFlush();
        iret = inPPR_ReadCardNumber2();
        if (iret == 0x9000) {
            //     CTOS_Beep();
            printf("[%s,%d] got card, txn go~~~time(%lu)\n", __FUNCTION__, __LINE__, CTOS_TickGet());
            iret = iProcess_ReadCardBasicData();
            if (iret != 0x6201) {
                usRet = ECC_CheckReaderResponseCode(iret);
                return usRet;
            }

        }
        CTOS_KBDHit(&key);
        if (key == d_KBD_CANCEL)
            return d_ERR_USERCANCEL;
        CheckMemoarystatus();
    } while (1);
    return d_ERR_USERCANCEL;
}


int iProcessWaitCardwithTimer(int sec) {
    USHORT usRet;
    BYTE key;
    int inOutLen, iret;
    SystemLog("iProcessWaitCard", "Start");
    ShowTitle(gTransTitle);

    ShowLine(0, 40 + 50, Big_Font_Size, "請將悠遊卡.", FALSE);
    ShowLine(0, 40 + 50 * 2, Big_Font_Size, "放上讀卡機.", FALSE);
    ShowStatusLine("離開請按<X>離開");
    //  ShowMessage3line(gTransTitle,"請將悠遊卡","放上讀卡機","離開請按<X>離開",Type_ComformNONE);  
    ULONG ulTick;
    int timer = 0;
    ulTick = CTOS_TickGet();
    while (timer < sec) {

        timer = ((CTOS_TickGet() - ulTick) / 100);
        USHORT mkHWSupport = Eth_CheckDeviceSupport();
        if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
            CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
        }
        CTOS_KBDBufFlush();
        iret = inPPR_ReadCardNumber();
        if (iret == 0x9000) {
            CTOS_Beep();
            //  iret= iProcess_ReadCardBasicData( );
            iret = iProcess_CheckBlockCard((BYTE *) & gCardNumberInfo.ucCardID);
            // iret=0x9000;
            if (iret) {
                usRet = ECC_CheckReaderResponseCode(iret);
                return iret;
            }
        }
        CTOS_KBDHit(&key);
        if (key == d_KBD_CANCEL)
            return d_ERR_USERCANCEL;

        mkHWSupport = Eth_CheckDeviceSupport();
        if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
            CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
        }
    }
    return d_ERR_USERCANCEL;
}

int iProcess_LogLockCardData(int isw) {
    int iret;
    SystemLog("iProcess_LogLockCardData", "Start");
    BYTE ucLockReason;
    usInitTxData(TXTYPE_LOCKCARD);
    if (isw == 0x6103) {
        ucLockReason = 0x02;
        inBuildLockCardDataOutput1_2(&gTransData,
                (LockCard_APDU_Out_2 *) & cOutputData[OUT_DATA_OFFSET], ucLockReason);


    } else if (isw == 0x640E || isw == 0x610F || isw == 0x6418) {
        ucLockReason = isw % 256;
        inBuildLockCardDataOutput2_2(&gTransData,
                (LockCard_APDU_Out_3 *) & cOutputData[OUT_DATA_OFFSET], ucLockReason);
    } else if (isw == 0x6406) {
        // ucLockReason = 0x01;
        inBuildLockCardDataOutput1_2(&gTransData, (LockCard_APDU_Out_2 *) & cOutputData[OUT_DATA_OFFSET], gucLockReason);
    }

    gTransData.ucTXSTATUS = TransStatus_ADVREQ;
    usSaveTxData(&gTransData);
    Process_SendAdvice3(0);
    return isw;
}

int iProcess_LockCard(BYTE * CardID) {
    BYTE ucTxnDateTime[4];
    int iret = 0;
    usInitTxData(TXTYPE_LOCKCARD);
    fnGetRTCUNIXDataTime((ULONG *) & ucTxnDateTime);
    iret = inBLCLockCard(TXTYPE_LOCKCARD, CardID, ucTxnDateTime);
    if (iret == 0x9000) {
        iret = 0x6406;
        iProcess_LogLockCardData(iret);
        return iret;
    }
    return iret;
}

int iProcess_CheckBlockCard(BYTE * CardID) {
    TM_INFO TMInfo;
    SystemLog("iProcess_CheckBlockCard", "Start");
    BYTE ucCardID[10];
    memset(ucCardID, 0x00, sizeof (ucCardID));
    memcpy(ucCardID, CardID, 7);

    int iret = inCheckBLC(ucCardID);

    if (iret == SUCCESS) {
        /* BYTE ucTxnDateTime[4];
          usInitTxData( TXTYPE_LOCKCARD); 	
          fnGetRTCUNIXDataTime((ULONG *)&ucTxnDateTime);
         fngetUnixTimeCnt(ucTxnDateTime,TMInfo.ucTMTxnDateTime); //交易日期時間(UnixDateTime)
         iret=inBLCLockCard(TXTYPE_LOCKCARD,CardID,ucTxnDateTime);
         if(iret==0x9000){
              iret=0x6406;
              iProcess_LogLockCardData(iret);
              return iret;
         }*/
        gucLockReason = 0x01;
        iret = iProcess_LockCard(CardID);

    }
    return 0x9000;
}

void PrepareforAddvalue(int amt) {
    SystemLog("PrepareforAddvalue", "Start");
    gTransData.lTxnAmt = amt;
    gTransData.ucMsgType = 0x02;
    gTransData.ucSubType = 0x40;

    gTransData.ucCardAutoloadParameters_AutoloadFlag = gBasicData.bAutoLoad;

    memcpy(&gTransData.ucCardAutoloadParameters_AutoloadValue, &gBasicData.ucAutoLoadAmt, 2);

}

USHORT Process_Autoload(int amt) {
    SystemLog("Process_Autoload", "Start");
    USHORT usRet;
    int iret;
    long autoloadAMT, ev, addamt;
    int autoloadlimit = atoi(gConfig.TX.AUTOLOADLIMITAMT);
    int i = 0;
    BYTE temp[128];
    BYTE temp2[128];
    memset(temp2, 0x00, sizeof (temp2));

    ev = BYTE3Data2LONG((char *) gBasicData.ucEV);

    if (ev - amt >= 0)//2014.05.19, kobe modified that balance amt >=0
        return d_ERR_AUTOLOADNOTNEED;
    if (gBasicData.bAutoLoad != TRUE)
        return d_ERR_AUTOLOADNOTSUPPORT;
    memcpy((BYTE *) & autoloadAMT, (BYTE *) & gBasicData.ucAutoLoadAmt, sizeof (gBasicData.ucAutoLoadAmt));
    //20150522 bruce modify 自動加值金額可為卡片自動加值之倍數，上限為1000
    addamt = autoloadAMT;
    do {
        if ((addamt + ev) > amt) {
            break;
            //  return d_ERR_EVNOTENOGHT;
        } else {
            addamt += autoloadAMT;
        }
    } while (addamt < (autoloadlimit));
    if (addamt > autoloadlimit) return d_ERR_EVNOTENOGHT;

    if ((addamt + ev) < amt) return d_ERR_EVNOTENOGHT;

    USHORT RTCDOSDate;
    fnGetRTCDOSData((BYTE *) & RTCDOSDate);
    
    if ((memcmp((BYTE *) & RTCDOSDate, (BYTE *) & gBasicData.AutoloadDate, 2) == 0) && gBasicData.AutoloadCounter > 1)
        return d_ERR_AUTOLOADNOTALLOW;

    /* usRet=Eth_SSLConnect_SOCKET(); 
       if(usRet!=d_OK){
               MessageBox(gTransTitle,"","網路連線異常","請檢查並重試","",d_MB_CHECK);
               goto Disconnect;
       }  */
    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
    usRet = SSLSocketConnect();
    if (usRet != d_OK) {
        //  MessageBox(gTransTitle,"","網路連線異常","請檢查並重試","",d_MB_CHECK);
        ECC_CheckAPResponseCode(usRet);
        if (usRet != d_OK) return usRet;
        return usRet;
    }


    ShowMessage2line(gTransTitle, "交易進行中.", "請勿移動卡片", Type_ComformNONE);
    usInitTxData(TXTYPE_AUTOLOAD);
    PrepareforAddvalue(addamt);

    do {
        iret = inPPR_TxnReqOnline();
        if (iret == 0x6415 || iret == 0x9000) {
            if (iret == 0x6415) {
                gTransData.ucTXSTATUS = TransStatus_REQ;
                gSaveReversalflag = 1;

                usRet = Eth_PutDeviecBackOnBase();
                usRet = Process_TransComm2(&gTransData, 1);
                ECC_CheckAPResponseCode(usRet);
                if (usRet != d_OK) return usRet;

                ShowStatusLine("已完成");

                usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
                if (usRet != d_OK) {
                    remove(ReversalFile);
                    goto Disconnect;
                }
            }

            iret = inPPR_AuthTxnOnline();
            if (iret == 0x6088 || iret == 0x9970 || iret == 0x9969 || iret == 0x9968) {
                ShowMessage2line(gTransTitle, "交易未完成", "請放回卡片", Type_ComformNONE);
                iret = iProcess_ReadCardBasicData();
                continue;
            }
            usRet = ECC_CheckReaderResponseCode(iret);
            if (usRet != d_OK) goto Disconnect;
            remove(ReversalFile);
            gTransData.ucTXSTATUS = TransStatus_ADVREQ;
            usSaveTxData(&gTransData);
            gAutoloadAMT = gTransData.lTxnAmt;
            gEVBeforeAutoload = gTransData.lEVBeforeTxn;
            //PrintReceipt( );
            //    LastTransData.ucTXSTATUS=TransStatus_VOIDED;
            //   usUpdataTxData( &LastTransData);
            //ShowMessage2line(gTransTitle,"交易完成!!","",Type_RemoveCard); 
            //  Process_SendAdvice3(0);
        } else {
            usRet = ECC_CheckReaderResponseCode(iret);
        }
    } while (iret == 0x6088);
Disconnect:
    //  Eth_SSLSocketDisConnect();       
    SSLSocketDisConnect();
    return usRet;
}

USHORT Process_SendBackupTXLOGAdvice(STR * TxLogfile) {
    SystemLog("Process_SendAdvice3", "Start");
    ULONG offset;
    int iSize;
    int inRetVal;
    int iCount = 0;
    STR buf[64];
    TRANS_DATA2 TransData;
    USHORT TotalCount;
    memset(buf, 0x00, sizeof (buf));

    TotalCount = (File_GetLen(TxLogfile) / sizeof (TRANS_DATA2));
    if (TotalCount == 0) return d_OK;
    USHORT DispLine1Y = 40 + 16, DispLine2Y = 120 + 16, DispLine3Y = 120 + 16;
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    CTOS_LCDGClearCanvas();
    ShowTitle(gTransTitle);
    ShowLine(0, 40 + 16, Big_Font_Size, "帳務資料上傳中.", FALSE);
    // USHORT ret=pthread_create(&Thread_Comm, NULL, (void*)SSLSocketConnect_thread, NULL);   

    remove(SendFile);
    FILE *fp = fopen(TxLogfile, "r+");
    if (fp == NULL)
        return d_ERR_FILE_OPEN;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) {
        fclose(fp);
        return d_ERR_FILE_NOTEXIST;
    }
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) {
        fclose(fp);
        return d_ERR_FILE_SIZE_ERR;
    }
    offset = 0;
    //CTOS_EthernetOpen();   

    /*  USHORT usRet=Eth_SSLConnect_SOCKET(); 
          if(usRet!=d_OK){
                  MessageBox(gTransTitle,"","網路連線異常","請檢查並重試","",d_MB_CHECK);
                   return usRet;
          }*/
    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
    USHORT usRet;
    usRet = SSLSocketConnect();
    if (usRet != d_OK) {
        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
        return usRet;
    }

    iCount = 0;
    offset = 0;
    do {
        sprintf(buf, "%d/%d", iCount, TotalCount);
        ShowLine(0, 40 + 40 + 16 + 10, Big_Font_Size, buf, FALSE);

        fseek(fp, offset, SEEK_SET);

        iSize = fread((BYTE *) & TransData, 1, sizeof (TRANS_DATA2), fp);
        // if(TransData.ucAdviceFLAG==0){
        //  if( TransData.ucTXSTATUS==TransStatus_ADVREQ){
        TransData.ucTXSTATUS = TransStatus_ADVREQ;
        remove(SendFile);
        usRet = ECC_WriteXmlHeader("TransXML", SendFile);
        vdBuildMessageType2(TransData.ucTXTYPE, TransData.ucTXSTATUS, (BYTE *) & TransData.ucMessageType); //Message Type ID 0100
        vdBuildProcessingCode2((TRANS_DATA2 *) & TransData, (BYTE *) & TransData.ucProcessCode); //Processing Code 0300

        usRet = usBuildTXREQ(&TransData, SendFile);

        usRet = ECC_WriteXmlEND("TransXML", SendFile);
        usRet = Eth_PutDeviecBackOnBase();
        usRet = Process_TransComm2(&TransData, 1);

        usRet = ECC_CheckAPResponseCode(usRet);
        if (usRet != d_OK) {
            fclose(fp);
            //  usRet= SSLSocketDisConnect();
            goto Disconnect;
        }
        usRet = ECC_CheckCMASResponseCode(TransData.ucResponseCode);
        if (usRet == d_OK) {

            //     TransData.ucTXSTATUS=TransStatus_OK;
            //      fseek(fp,gUnuploadTXs[iCount],SEEK_SET);      
            //      fwrite((UCHAR *)&TransData,sizeof(TRANS_DATA2),1,fp);  


        }
        //   }
        iCount++;
        offset = iCount * sizeof (TRANS_DATA2);
        //offset+=sizeof(TRANS_DATA2);

    } while (iCount < TotalCount);
    fclose(fp);
Disconnect:
    //   Eth_SSLSocketDisConnect();       
    SSLSocketDisConnect();
    return usRet;

}
