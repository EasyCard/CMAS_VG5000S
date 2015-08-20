
#include "ECCAPP.h"
/*
USHORT SaveBatchStoreFile( ezxml_t BatchStore )
{
   
    char filename[13+5+6+1+3+1];
    BYTE  tmpfile[3+1]="tmp";
    CTOS_RTC SetRTC;
    memset(filename,0x00,sizeof(filename));
    USHORT ret = CTOS_RTCGet(&SetRTC);
    if(ret!=0){
         return d_ERR_GETRTC;
    }
    sprintf(filename,"/media/mdisk/BATCH%02d%02d%02d.xml",SetRTC.bYear ,SetRTC.bMonth,SetRTC.bDay);
    ret=ECC_WriteXMLFILE(filename,gBatchStore);
   
    
    return d_OK;
    
}
USHORT OpenBatchStoreFile(ezxml_t BatchStore )
{
    char filename[13+5+6+1+3+1];
  
    CTOS_RTC SetRTC;
    memset(filename,0x00,sizeof(filename));
    USHORT    ret = CTOS_RTCGet(&SetRTC);
    if(ret!=0){
         return d_ERR_GETRTC;
    }
    sprintf(filename,"/media/mdisk/BATCH%02d%02d%02d.xml",SetRTC.bYear ,SetRTC.bMonth,SetRTC.bDay);
     ret=File_exist(filename);
    if(ret==d_ERR_FILE_NOTEXIST)
    {
 
         BatchStore=ezxml_new("BATCHSTORE");
         ret=ECC_WriteXMLFILE(filename,BatchStore);
    }else{
        BatchStore= ezxml_parse_file(filename); 
    }
    return d_OK;
    
}
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

USHORT Disp_BatchData(Batch_Totle_STRUCT *BatchTotal) {

    STR LINE[7][64 + 1];
    memset(LINE, 0x00, sizeof (LINE));
    //    STR Line[6][64];  
    sprintf((BYTE *) & LINE[0], "交易總筆數:%ld,總額:%ld", BatchTotal->TotleCnt, BatchTotal->TotleAMT);
    //   sprintf(LINE1,"交易總額    :%ld",BatchTotal->TotleNET);
    int offset = 1;
    if (GetFunctionSwitch("ADDVALUE")) {
        sprintf((BYTE *) & LINE[offset], "加值總筆數:%06ld,總額:%ld", BatchTotal->ADDCnt, BatchTotal->ADDAMT);
        offset++;
        if (GetFunctionSwitch("CANCELTXN")) {
            sprintf((BYTE *) & LINE[offset], "取消總筆數:%06ld,總額:%ld", BatchTotal->ADDVOIDCnt, BatchTotal->ADDVOIDAMT);
            offset++;
        }

    }
    if (GetFunctionSwitch("DEDUCT")) {
        sprintf((BYTE *) & LINE[offset], "購貨總筆數:%06ld,總額:%ld", BatchTotal->DEDUCTCnt, BatchTotal->DEDUCTAMT);
        offset++;
        if (GetFunctionSwitch("CANCELTXN")) {
            sprintf((BYTE *) & LINE[offset], "取消總筆數:%06ld,總額:%ld", BatchTotal->DEDUCTVOIDCnt, BatchTotal->DEDUCTVOIDAMT);
            offset++;
        }

    }

    if (GetFunctionSwitch("RETURN")) {
        sprintf((BYTE *) & LINE[offset], "退貨總筆數:%06ld,總額:%ld", BatchTotal->REFUNDCnt, BatchTotal->REFUNDAMT);
        offset++;
    }
    if (GetFunctionSwitch("AUTOLOAD")) {
        sprintf((BYTE *) & LINE[offset], "自動加值總筆數:%06ld,總額:%ld", BatchTotal->AUTOLOADCnt, BatchTotal->AUTOLOADAMT);
        offset++;
    }

    //   sprintf((BYTE *)&LINE[offset],"鎖卡總筆數:%ld",BatchTotal->BLACKCARDCNT);
    offset++;
    //   USHORT    ret= Displaymuiltlie(d_LCD_FONT_12x24,gTransTitle,&Line);
    STR * Line[] = {"", LINE[0], LINE[1], LINE[2], LINE[3], LINE[4], LINE[5], LINE[6], "退出請按(X)"};
    BYTE key = Displaymuiltlie(d_LCD_FONT_12x24, "總帳查詢", Line);
    if (key == d_KBD_CANCEL) {
        return d_OK;
    }
    return d_ERR_USERCANCEL;

}

USHORT SAVEBatchSN(STR* batchNo) {
    USHORT ret = usWriteFile(BatchSnFile, batchNo, strlen(batchNo));
    if(ret!=d_OK) myDebugFile((char*)__FUNCTION__,__LINE__,"write BatchSnFile fail(%d)", ret);
    ret = usWriteFile(SDBatchSnFile, batchNo, strlen(batchNo));
    if(ret!=d_OK) myDebugFile((char*)__FUNCTION__,__LINE__,"write SDBatchSnFile fail(%d)", ret);
    return ret;
}

USHORT GetBatchSN(STR* batchNo) {
    ULONG iSize;
    USHORT ret = usReadFileData(BatchSnFile, &iSize, batchNo);
    if (ret != d_OK) {
        ret = usReadFileData(SDBatchSnFile, &iSize, batchNo);
        if (ret != d_OK) {
            sprintf(batchNo, "0");
        } else {
            ret = usWriteFile(BatchSnFile, batchNo, strlen(batchNo));
        }
        SAVEBatchSN(batchNo);
    }
    return d_OK;
}

USHORT usUpdateBatchSN() {
    BYTE ucBatchNo[8 + 1];
    USHORT usBatchSN;
    USHORT usRet = usGetCurrBatchSN(ucBatchNo, &usBatchSN);
    if (usRet != d_OK) return usRet;
    usBatchSN++;
    if (usBatchSN >= 100)
        usBatchSN = 1;
    memset(gConfig.BATCH.NO, 0x00, sizeof (gConfig.BATCH.NO));
    sprintf(gConfig.BATCH.NO, "%d", usBatchSN);
    usRet = SAVEBatchSN(gConfig.BATCH.NO);
    // ECC_SetXMLTag(BATCHINFO_Path,"BATCH","NO",gConfig.BATCH.NO);
    // Config_SetData();
    // SetBATCHInfo();

    return d_OK;
}

USHORT usCloseBatch(void) {

    //  remove(BatchTotleFile);   

    remove(TransDataFile);
    // USHORT ret= InitBatchTotal(); //modify v0008
    UpdateTransSN();
    usUpdateBatchSN();
    CTOS_FileDelete(BatchTotleFile);
    // ret= Config_SetData();
    USHORT ret = InitBatchTotal(); //modify v0008

    return ret;
}

USHORT Show_BatchData() {

    USHORT ret = GetBatchTotal();
    Disp_BatchData(&gBatchTotal);
    return 0;
}

USHORT CheckBatchCount() {
    USHORT TXCount;

    if (gBatchTotal.TotleCnt == 0)
        TXCount = 0;
    else
        TXCount = gBatchTotal.TotleCnt;

    return TXCount;
}

USHORT InitBatchTotal() {

    CTOS_RTC SetRTC;

    USHORT ret = CTOS_RTCGet(&SetRTC);
    if (ret != 0) {
        return d_ERR_GETRTC;
    }
    memset(&gBatchTotal, 0x00, sizeof (gBatchTotal));
    BYTE BatchNoStr[8 + 1];
    memset(BatchNoStr, 0x00, sizeof (BatchNoStr));
    GetBatchSN(gConfig.BATCH.NO);
    gBatchTotal.usBatchSN = atoi(gConfig.BATCH.NO);
    if (gBatchTotal.usBatchSN >= 100)
        gBatchTotal.usBatchSN = 1;
    if (gBatchTotal.usBatchSN == 0) {
        gBatchTotal.usBatchSN = 1;
        sprintf(gConfig.BATCH.NO, "%d", gBatchTotal.usBatchSN);
        // Config_SetData();
        GetBATCHInfo();

        gBatchTotal.usBatchSN = atoi(gConfig.BATCH.NO);
        ret = CTOS_FileDelete(BatchTotleFile);
        // remove(SDBatchTotleFile);  
    }

    sprintf(BatchNoStr, "%02d%02d%02d%02d", SetRTC.bYear, SetRTC.bMonth, SetRTC.bDay, gBatchTotal.usBatchSN);
    memcpy(gBatchTotal.ucBatchSN, BatchNoStr, sizeof (BatchNoStr) - 1);
    ret = usSetCurrBatchDevID2(gTransData.ucCPUDeviceID); //2014.10.16, kobe opened it, fixed that device ID(all zero)at second settle receipt
    // unsigned int iret= wub_str_2_hex(&gConfig.DEVICE.READER.CPU.CPUDEVICEID,&gBatchTotal.DEVICEID, strlen(&gConfig.DEVICE.READER.CPU.CPUDEVICEID));
    SAVEBatchSN(gConfig.BATCH.NO);
    SavetBatchTotal();
    return d_OK;
}

USHORT GetBatchTotal() {

    ULONG iSize = sizeof (Batch_Totle_STRUCT);

    USHORT ret = CTOS_ReadFile(BatchTotleFile, (BYTE *) & gBatchTotal, &iSize);
    if (ret != d_OK || iSize != sizeof (gBatchTotal)) {
        ret = InitBatchTotal();
    }
    return ret;
}

USHORT usSetCurrBatchDevID2(BYTE * DeviceID) {

    USHORT ret;
    memcpy(gBatchTotal.DEVICEID, DeviceID, 6);
    SavetBatchTotal();
    return d_OK;
}

USHORT GetBatchTotal_DevID(BYTE * DeviceID) {

    memcpy(DeviceID, gBatchTotal.DEVICEID, 6);
    return d_OK;
}

/*
 *#define TXTYPE_DEDUCT            3                
#define TXTYPE_VOID                4
#define TXTYPE_SETVALUE            5
#define TXTYPE_SETTLEMENT          6
#define TXTYPE_AUTOLOADENABLE      7
#define TXTYPE_REFUND              8
#define TXTYPE_LOCKCARD            9         
#define TXTYPE_REPORT              10    
 */

USHORT BatchUpdateCounterData(BYTE TxType, int AMT) {



    if (TxType == TXTYPE_DEDUCT) {
        gBatchTotal.TotleCnt++;
        gBatchTotal.TotleAMT += AMT;
        gBatchTotal.DEDUCTCnt++;
        gBatchTotal.DEDUCTAMT += AMT;
        gBatchTotal.DEDUCTNETAMT += AMT;
        gBatchTotal.DEDUCTNETCnt++;
        if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
            gBatchTotal.CntByProfile[gTXCardProfile]++;
            gBatchTotal.AMTByProfile[gTXCardProfile] += AMT;
        }
    } else if (TxType == TXTYPE_VOID) {
        gBatchTotal.TotleCnt++;
        gBatchTotal.TotleAMT += AMT;
        if (gTransData.ucMsgType == 0x02) {
            gBatchTotal.DEDUCTVOIDCnt++;
            gBatchTotal.DEDUCTVOIDAMT += AMT;
            gBatchTotal.DEDUCTNETAMT -= AMT;
            gBatchTotal.DEDUCTNETCnt++;
        } else if (gTransData.ucMsgType == 0x0b) {
            gBatchTotal.ADDVOIDCnt++;
            gBatchTotal.ADDVOIDAMT += AMT;
            gBatchTotal.ADDVALUENETAMT -= AMT;
            gBatchTotal.ADDVALUENETCnt++;
        }
    } else if (TxType == TXTYPE_ADD) {
        gBatchTotal.TotleCnt++;
        gBatchTotal.TotleAMT += AMT;
        gBatchTotal.ADDCnt++;
        gBatchTotal.ADDAMT += AMT;
        gBatchTotal.ADDVALUENETAMT += AMT;
        gBatchTotal.ADDVALUENETCnt++;
    } else if (TxType == TXTYPE_REFUND) {
        gBatchTotal.TotleCnt++;
        gBatchTotal.TotleAMT += AMT;
        gBatchTotal.REFUNDCnt++;
        gBatchTotal.REFUNDAMT += AMT;
        gBatchTotal.DEDUCTNETAMT -= AMT;
        gBatchTotal.DEDUCTNETCnt++;
    } else if (TxType == TXTYPE_LOCKCARD) {
        gBatchTotal.BLACKCARDCNT++;
    } else if (TxType == TXTYPE_AUTOLOAD) {
        gBatchTotal.TotleCnt++;
        gBatchTotal.TotleAMT += AMT;
        gBatchTotal.AUTOLOADCnt++;
        gBatchTotal.AUTOLOADAMT += AMT;
        // gBatchTotal.TotleNET+=AMT;
    } else if (TxType == TXTYPE_AUTOLOADENABLE) {
        gBatchTotal.AUTOLOADENABLECNT++;

    } else if (TxType == TXTYPE_SETVALUE) {
        gBatchTotal.SETVALUECNT++;

    }

    USHORT ret = SavetBatchTotal();

    return ret;
}

USHORT usGetCurrBatchSN(BYTE * bBatchSN, USHORT * usBatchSN) {

    USHORT ret = GetBatchTotal(); //add 20140121
    if (ret != d_OK) return ret; //add 20140121

    memcpy(bBatchSN, gBatchTotal.ucBatchSN, 8);
    bBatchSN[8] = 0x00;
    *usBatchSN = gBatchTotal.usBatchSN;

    return d_OK;
}

USHORT SavetBatchTotal() {

    int size = sizeof (gBatchTotal);
    USHORT ret = CTOS_WriteFile(BatchTotleFile, (BYTE *) & gBatchTotal, size);
    if (ret != d_OK) {
        myDebugFile((char*)__FUNCTION__,__LINE__,"save BatchTotleFile fail(%d)",ret);
        return ret;
    }
        // ret= SaveBackupBatchData();
    //ret= usWriteFile(SDBatchTotleFile,&gBatchTotal,size);
    return ret;
}

USHORT SaveBackupBatchData() {

    STR path[32];
    STR filename[64];
    STR *xmlstr;
    STR time[32];
    USHORT ret;
    int iret;
    CTOS_RTC GetRTC;
    ezxml_t event;
    FILE * f;


    ret = CTOS_RTCGet(&GetRTC);
    if (ret != 0) {
        return d_ERR_GETRTC;
    }
    memset(path, 0x00, sizeof (path));
    sprintf(path, "/media/mdisk/%04d/%02d/%02d/Trans/DATA", GetRTC.bYear + 2000, GetRTC.bMonth, GetRTC.bDay);


    BYTE ucBatchNo[8 + 1];
    USHORT usBatchSN;
    ret = usGetCurrBatchSN(ucBatchNo, &usBatchSN);

    if (ret != d_OK) return ret;
    memset(filename, 0x00, sizeof (filename));

    sprintf(filename, "%s/BatchTotal%s.dat", path, ucBatchNo);

    int size = sizeof (gBatchTotal);
    ret = usWriteFile(filename, (BYTE *) & gBatchTotal, size);
    return ret;
}

USHORT BackupBatchDataUpload() {

    USHORT ret;
    char year[4 + 1], month[2 + 1], day[2 + 1], BatchNO[8 + 1];
    memset(BatchNO, 0x00, sizeof (BatchNO));
    int MaxLen;
    BYTE tmpbuf[5];
    Batch_Totle_STRUCT BatchTotal;
    TRANS_DATA2 TransData;
    STR path[64];
    memset(path, 0x00, sizeof (path));
    STR filename[64];
    memset(filename, 0x00, sizeof (filename));
    sprintf(gTransTitle, "交易補登上傳");
    MaxLen = 4;
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    ret = ShowInputBox(gTransTitle, "請輸入西元年(4碼)", tmpbuf, MaxLen, 0, 0);
    sprintf(year, "%04d", atoi(tmpbuf));
    MaxLen = 2;
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    ret = ShowInputBox(gTransTitle, "請輸入月份", tmpbuf, MaxLen, 0, 0);
    sprintf(month, "%02d", atoi(tmpbuf));
    MaxLen = 2;
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    ret = ShowInputBox(gTransTitle, "請輸入日期", tmpbuf, MaxLen, 0, 0);
    sprintf(day, "%02d", atoi(tmpbuf));
    sprintf(path, "/media/mdisk/%s/%s/%s/Trans/DATA/", year, month, day);

    DIR * theFolder;
    struct dirent *next_file;
    ULONG iSize = 0;
    theFolder = opendir(path);

    if (theFolder == NULL) return d_Fail;
    while (next_file = readdir(theFolder)) {
        // build the full path for each file in the folder        

        //   CTOS_PrinterPutString(filepath);
        if (memcmp(next_file->d_name, "Trans", 5) == 0) {
            memcpy(BatchNO, &next_file->d_name[5], 8);
            sprintf(filename, "%s%s", path, next_file->d_name);

            ret = Process_SendBackupTXLOGAdvice(filename);


            ShowLine(0, 40 + 16, Big_Font_Size, "結帳作業中.", FALSE);

            sprintf(filename, "%sBatchTotal%s.dat", path, BatchNO);
            iSize = sizeof (Batch_Totle_STRUCT);
            USHORT ret = usReadFileData(filename, &iSize, (BYTE *) & BatchTotal);
            if (ret != d_OK) {
                continue;
            }

            usInitTxData(TXTYPE_SETTLEMENT); //初始交易資料  
            sprintf(gTransData.ucBatchNo, "%s", BatchNO);
            gTransData.ulSettle_TotleCnt = BatchTotal.TotleCnt;
            gTransData.lSettle_TotleAmt = BatchTotal.TotleAMT;
            gTransData.ucTXSTATUS = TransStatus_REQ;

            ret = Process_TransComm2(&gTransData, 1);
            remove(SettleFile);
            PrintSettlementReceipt(&BatchTotal);
        }
    }
}

