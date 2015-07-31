#include "ECCAPP.h"

USHORT usGetTXTYPE_TRANSTYPE(USHORT inTxnType) {

    USHORT TransType;
    switch (inTxnType) {

        case TXTYPE_SIGNON:
            TransType = TransType_SIGNON;
            break;
        case TXTYPE_AUTOLOADENABLE:
        case TXTYPE_DEDUCT:
            TransType = TransType_VERIFY;
            break;
        case TXTYPE_ADD:
        case TXTYPE_SETVALUE:
        case TXTYPE_VOID:
        case TXTYPE_REFUND:
        case TXTYPE_AUTOLOAD://2014.06.26, kobe added it
            TransType = TransType_AUTH;
            break;
        case TXTYPE_LOCKCARD:
            TransType = TransType_LOCKCARDADVICE;
            break;
        case TXTYPE_REPORT:
            TransType = TransType_STATUSREPORT;
            break;
        case TXTYPE_DEBUG:
            TransType = TransType_DEBUG;
            break;
        case TXTYPE_SETTLEMENT:
            TransType = TransType_SETTLEMENT;
            break;
    }
    return TransType;
}

/*
#define TransStatus_REQ         0
#define TransStatus_RSP_FAIL    1      
#define TransStatus_RSP         2
#define TransStatus_RSP_FAIL    3 
#define TransStatus_ADVREQ      4
#define TransStatus_ADVRSP      5      
#define TransStatus_OK          6   */
USHORT usGetTransStatusSTR(int TransType, int TransStatus, STR * TransStatusSTR) {

    switch (TransType) {
        case TransType_AUTH:
            if (TransStatus == TransStatus_REQ)
                sprintf(TransStatusSTR, "AU_Q");
            else if (TransStatus == TransStatus_RSP)
                sprintf(TransStatusSTR, "AU_P");
            else if (TransStatus == TransStatus_ADVREQ)
                sprintf(TransStatusSTR, "ADV_Q");
            else if (TransStatus == TransStatus_ADVRSP)
                sprintf(TransStatusSTR, "ADV_P");
            break;
        case TransType_VERIFY:
            if (TransStatus == TransStatus_REQ)
                sprintf(TransStatusSTR, "VERIFY_Q");
            else if (TransStatus == TransStatus_RSP)
                sprintf(TransStatusSTR, "VERIFY_P");
            else if (TransStatus == TransStatus_ADVREQ)
                sprintf(TransStatusSTR, "ADV_Q");
            else if (TransStatus == TransStatus_ADVRSP)
                sprintf(TransStatusSTR, "ADV_P");
            break;

        case TransType_SIGNON:
            if (TransStatus == TransStatus_REQ)
                sprintf(TransStatusSTR, "SG_Q");
            else if (TransStatus == TransStatus_RSP)
                sprintf(TransStatusSTR, "SG_P");
            else if (TransStatus == TransStatus_ADVREQ)
                sprintf(TransStatusSTR, "SGADV_Q");
            else if (TransStatus == TransStatus_ADVRSP)
                sprintf(TransStatusSTR, "SGADV_P");
            break;
        case TransType_STATUSREPORT:
            if (TransStatus == TransStatus_REQ)
                sprintf(TransStatusSTR, "RE_Q");
            else if (TransStatus == TransStatus_RSP)
                sprintf(TransStatusSTR, "RE_P");

            break;


        case TransType_LOCKCARDADVICE:
            if (TransStatus == TransStatus_ADVREQ)
                sprintf(TransStatusSTR, "LC_Q");
            else if (TransStatus == TransStatus_ADVRSP)
                sprintf(TransStatusSTR, "LC_P");
            break;
        case TransType_DEBUG:
            sprintf(TransStatusSTR, "DEBUG");
            break;
        case TransType_SETTLEMENT:
            if (TransStatus == TransStatus_REQ)
                sprintf(TransStatusSTR, "SETTLE_Q");
            else if (TransStatus == TransStatus_RSP)
                sprintf(TransStatusSTR, "SETTLE_P");
            break;
        default:
            return d_Fail;
    }

    return d_OK;
}

void vGetTxTitleStr(BYTE TXTYPE, STR * Title) {

    switch (TXTYPE) {
        case TXTYPE_TMS:
            break;
        case TXTYPE_SIGNON:

            sprintf(Title, "%s", Title_SIGNON);
            break;
        case TXTYPE_ADD:
            sprintf(Title, "%s", Title_ADD);

            break;
        case TXTYPE_DEDUCT:
            sprintf(Title, "%s", Title_DEDUCT);

            break;
        case TXTYPE_VOID:
            sprintf(Title, "%s", Title_Cancle);

            break;
        case TXTYPE_SETVALUE:

            sprintf(Title, "%s", Title_SETVALUE);
            break;
        case TXTYPE_SETTLEMENT:
            sprintf(Title, "%s", Title_SETTLEMENT);
            break;
        case TXTYPE_AUTOLOADENABLE:
            break;
        case TXTYPE_REFUND:

            sprintf(Title, "%s", Title_Refund);
            break;
        case TXTYPE_LOCKCARD:break;
        case TXTYPE_REPORT:break;
        case TXTYPE_DEBUG:break;

            break;
        case TXTYPE_AUTOLOAD:

            sprintf(Title, "%s", Title_AUTOLOAD);
            break;
            break;
    }
}

void vGetTxInfo(BYTE TXTYPE) {

    switch (TXTYPE) {
        case TXTYPE_TMS:
            break;
        case TXTYPE_SIGNON:


            break;
        case TXTYPE_ADD:

            gTransData.ucMsgType = 0x02;
            gTransData.ucSubType = 0x30
                    ;
            break;
        case TXTYPE_DEDUCT:

            gTransData.ucMsgType = 0x01;
            gTransData.ucSubType = 0x00;
            break;
        case TXTYPE_VOID:

            gTransData.ucMsgType = 0x00;
            gTransData.ucSubType = 0x00;
            break;
        case TXTYPE_SETVALUE:
            gTransData.ucMsgType = 0x50;
            gTransData.ucSubType = 0x00;

            break;
        case TXTYPE_SETTLEMENT:
            break;
        case TXTYPE_AUTOLOADENABLE:
            gTransData.ucMsgType = 0x23;
            gTransData.ucSubType = 0x00;
            break;
        case TXTYPE_REFUND:
            gTransData.ucMsgType = 0x02;
            gTransData.ucSubType = 0x0B;
            break;
        case TXTYPE_LOCKCARD:break;
        case TXTYPE_REPORT:break;
        case TXTYPE_DEBUG:break;

            break;
        case TXTYPE_AUTOLOAD:
            gTransData.ucMsgType = 0x02;
            gTransData.ucSubType = 0x40;
            break;
    }
    return;
}

USHORT usInitTxData(BYTE TXTYPE) {
    TM_INFO tm;
    //gTXCardProfile=0;
    memset(gTransTitle, 0x00, sizeof (gTransTitle));
    memset(&gTransData, 0x00, sizeof (TRANS_DATA2));

    gSaveReversalflag = 0;
    gTransData.ucTXTYPE = TXTYPE;

    USHORT usRet = usGetCurrBatchSN(gTransData.ucBatchNo, &gTransData.usBATCHNO);
    if (usRet != d_OK) return usRet;

    // usRet=Config_GetData();
    //usRet= Sysinfo2_GetData();
    usGetCurrTransSN((int*) gTransData.usTXSN);

    // gTransData.usTXSN=GetTransSn(gConfig.TX.SERIALNO);
    gTransData.ulTerminalInvoiceNum = gTransData.usTXSN;
    //memcpy(gTransData.ulTerminalInvoiceNum, gTransData.usTXSN, sizeof (gTransData.ulTerminalInvoiceNum));
    
    //memcpy(gTransData.ulTMTxnSN, gTransData.usTXSN, sizeof (gTransData.usTXSN));
    gTransData.ulTMTxnSN = gTransData.usTXSN;

    memset(&tm, 0x00, sizeof (tm));
    usRet = usBuildTMInfo(&tm);
    if (usRet != d_OK) return d_ERR_Param;

    memcpy(gTransData.ucTxnData, tm.ucTMTxnDateTime, sizeof (gTransData.ucTxnData) - 1);
    memcpy(gTransData.ucTxnTime, &tm.ucTMTxnDateTime[8], sizeof (gTransData.ucTxnTime) - 1);
    memcpy(gTransData.ucTxnDateTime, tm.ucTMTxnDateTime, sizeof (tm.ucTMTxnDateTime));

    memcpy(gTransData.ucTMTxnDateTime, tm.ucTMTxnDateTime, sizeof (gTransData.ucTxnData) - 1);
    gTransData.ulSTCode = wub_str_2_long(tm.ucTMLocationID); //T5300
    fnASCTOBIN(gTransData.ucCPUSPID, gConfig.MERCHANT.MERCHANTID, 8, 3, DECIMAL); //新服務業者代碼 T4200

    //if(ecrObj.gData.isEcrTxn)
    // {
    //     ecrObj.posFld2EdcFld(&ecrObj);
    // }
    //else
    //{
    memcpy(gTransData.ucTMPOSID, tm.ucTMID, 2); //蝯垢璈?TM)璈?
    memcpy(gTransData.ucTMAgentNumber, tm.ucTMAgentNumber, sizeof (tm.ucTMAgentNumber)); //蝯垢璈?TM)?園??∩誨??     
    sprintf((BYTE *)gTransData.ucTMINVOICENO, "000000");
    memcpy(gTransData.ucTMTxnData, gTransData.ucTxnData, sizeof (gTransData.ucTxnData));
    memcpy(gTransData.ucTMTxnTime, gTransData.ucTxnTime, sizeof (gTransData.ucTxnTime));
    //}

    gTransData.ucSPID = gTransData.ucCPUSPID[0];

    /*  BYTE Data[20+1];
      memset(Data,0x00,sizeof(Data));
      usRet=GetConfigTag("MERCHANT","NewLocationID",Data);
      if(usRet==d_OK){
               fnASCTOBIN(gTransData.ucSubMerchantID,Data,5,2,DECIMAL);//新場站代碼
      }*/
    fnASCTOBIN(gTransData.ucSubMerchantID, gConfig.MERCHANT.NewLocationID, 5, 2, DECIMAL); //新場站代碼
    gTransData.ucLocationID = gTransData.ucSubMerchantID[0]; //location id �]�� new location id low byte     


    /* memset(Data,0x00,sizeof(Data));
     usRet=ECC_GetXMLTag3(ConfigXML,"DEVICE","READER", "CPU","CPUDEVICEID", Data);
      wub_str_2_hex(Data,(char *)&gTransData.ucCPUDeviceID, strlen(Data));
     */
    //for Settlement, Host responsed T3900=03, the reason was data fulled zero in T4100    
    wub_str_2_hex(gConfig.DEVICE.READER.CPU.CPUDEVICEID, (char *)gTransData.ucCPUDeviceID, strlen(gConfig.DEVICE.READER.CPU.CPUDEVICEID));
    if(TXTYPE==TXTYPE_SETTLEMENT){
        BYTE temp[16];
        memset(temp, 0x00, sizeof(temp));
        if(memcmp(gTransData.ucCPUDeviceID, temp, 6)==0) 
            myDebugPrinter(ERROR, "Settlement maybe fail, gConfig cpuDeviceID(%s)", gConfig.DEVICE.READER.CPU.CPUDEVICEID);
    }
    
    /* usRet=ECC_GetXMLTag3(ConfigXML,"DEVICE","READER", "MIFARE","DEVICEID", Data);
      wub_str_2_hex(Data,(char *)&gTransData.ucDeviceID, strlen(Data));
     */


    wub_str_2_hex(gConfig.DEVICE.READER.MIFARE_DEVICEID, (char *)gTransData.ucDeviceID, strlen(gConfig.DEVICE.READER.MIFARE_DEVICEID));

    /*    memset(Data,0x00,sizeof(Data));
        usRet=GetConfigTag("DEVICE","SAMSLOT",Data);
        if(usRet==d_OK){
             wub_str_2_hex(Data,&gSAMSlot,strlen(Data));
        }*/
    wub_str_2_hex(gConfig.DEVICE.SAMSLOT, &gSAMSlot, strlen(gConfig.DEVICE.SAMSLOT));


    gTransData.ucTXSTATUS = TransStatus_INIT;
    vGetTxTitleStr(TXTYPE, gTransTitle);
    vGetTxInfo(TXTYPE);

    sprintf(gTransData.ucRRN, "%s%06ld", gTransData.ucTxnData, gTransData.usTXSN);

    if (ecrObj.gData.isEcrTxn) {
        ecrObj.posFld2EdcFld(&ecrObj);
    }

    return 0;
}

USHORT usSaveTxData(TRANS_DATA2 * TransData) {
    /*
        FILE *fp =  fopen(TransDataFile, "ab+");
        if (fp ==  NULL) 
                 return d_Fail;
    
        int inRetVal = fseek(fp,0,SEEK_END);
        if(inRetVal != 0)
        {
            fclose(fp);
            return d_Fail;
         }
        fwrite((UCHAR *)TransData,sizeof(TRANS_DATA2),1,fp);
    
        fclose(fp);*/
    USHORT usRet = usAppendFile(TransDataFile, (UCHAR *) TransData, sizeof (TRANS_DATA2));
    if (usRet != d_OK) {
        FLASHERROR();
    }

    usRet = SaveBackupTxData(TransData);

    TransData->ucTXSTATUS = TransStatus_ADVREQ;
    //  USHORT usRet =SaveBackupTxData(TransData);
    usRet = BatchUpdateCounterData(TransData->ucTXTYPE, TransData->lTxnAmt);
    usRet = UpdateTransSN();
    //  usRet= Config_SetData();

    return d_OK;
}

USHORT usGetTxData(TRANS_DATA2 * TransData, ULONG TxSN) {

    ULONG offset;
    int iSize;
    int inRetVal;
    FILE *fp = fopen(TransDataFile, "r");
    if (fp == NULL)
        return d_Fail;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;

    if (TxSN == 0) {
        offset = ulFileSize - sizeof (TRANS_DATA2);
        fseek(fp, offset, SEEK_SET);
    } else {
        offset = (TxSN - 1) * sizeof (TRANS_DATA2);
        inRetVal = fseek(fp, offset, SEEK_SET);
        if (inRetVal != 0) {
            fclose(fp);
            return d_Fail;
        }
    }


    iSize = fread((BYTE *) TransData, sizeof (TRANS_DATA2), 1, fp);
    fclose(fp);
    if (iSize != sizeof (TRANS_DATA2)) return d_ERR_FILE_READ_FAIL;

    return d_OK;
}

USHORT usUpdataTxData(TRANS_DATA2 * TransData) {

    ULONG offset;
    int iSize;
    int inRetVal;
    TRANS_DATA2 TmpData;
    FILE *fp = fopen(TransDataFile, "r+");
    if (fp == NULL)
        return d_Fail;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;
    offset = 0;
    while (1) {
        fseek(fp, offset, SEEK_SET);
        iSize = fread((BYTE *) & TmpData, sizeof (TRANS_DATA2), 1, fp);

        if (TmpData.ulTerminalInvoiceNum == TransData->ulTerminalInvoiceNum) {
            fseek(fp, offset, SEEK_SET);
            fwrite((UCHAR *) TransData, sizeof (TRANS_DATA2), 1, fp);
            fclose(fp);
            return d_OK;
            // memcpy(&TransData,&TmpData,sizeof(TRANS_DATA2));
        }

        offset += sizeof (TRANS_DATA2);
        if (offset >= ulFileSize) return d_ERR_TX_CANNOT_FIND;
    }
    fclose(fp);
    return d_ERR_CANNOT_FINDTX;
}

USHORT usGetTxDataByInvoiceNum(TRANS_DATA2 * TransData, ULONG InvocieNum) {

    ULONG offset;
    int iSize;
    int inRetVal;
    TRANS_DATA2 TmpData;
    FILE *fp = fopen(TransDataFile, "r");
    if (fp == NULL)
        return d_Fail;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;
    offset = 0;
    while (1) {
        fseek(fp, offset, SEEK_SET);
        iSize = fread((BYTE *) & TmpData, sizeof (TRANS_DATA2), 1, fp);

        if (TmpData.ulTerminalInvoiceNum == InvocieNum) {
            memcpy(&TransData, &TmpData, sizeof (TRANS_DATA2));
        }

        offset += sizeof (TRANS_DATA2);
        if (offset >= ulFileSize) return d_ERR_TX_CANNOT_FIND;
    }
    fclose(fp);
    return d_OK;
}

USHORT CheckUnuploadTxCount() {

    ULONG offset;
    int iSize;
    int inRetVal;
    int iCount = 0;
    TRANS_DATA2 TransData;
    remove(SendFile);
    FILE *fp = fopen(TransDataFile, "r");
    if (fp == NULL)
        return 0;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return 0;
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return 0;
    offset = 0;
    while (1) {
        fseek(fp, offset, SEEK_SET);
        iSize = fread((BYTE *) & TransData, sizeof (TRANS_DATA2), 1, fp);
        // if(TransData.ucAdviceFLAG==0){
        if (TransData.ucTXSTATUS == TransStatus_ADVREQ) {
            iCount++;
        }

        offset += sizeof (TRANS_DATA2);
        if (offset >= ulFileSize) break;
    }
    fclose(fp);
    //   gUNUPLOADCOUNT=icount;
    return iCount;
}

USHORT BuildAdviceTxFile() {

    ULONG offset;
    int iSize;
    int inRetVal;
    int iCount = 0;
    TRANS_DATA2 TransData;
    remove(SendFile);
    FILE *fp = fopen(TransDataFile, "ab+");
    if (fp == NULL)
        return d_ERR_FILE_OPEN;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;
    offset = 0;

    USHORT usRet = ECC_WriteXmlHeader("TransXML", SendFile);
    while (1) {
        fseek(fp, offset, SEEK_SET);
        iSize = fread((BYTE *) & TransData, sizeof (TRANS_DATA2), 1, fp);
        // if(TransData.ucAdviceFLAG==0){
        if (TransData.ucTXSTATUS == TransStatus_ADVREQ) {
            vdBuildMessageType2(TransData.ucTXTYPE, TransData.ucTXSTATUS, (BYTE *) & TransData.ucMessageType); //Message Type ID 0100
            vdBuildProcessingCode2(&TransData, (BYTE *) TransData.ucProcessCode); //Processing Code 0300
            usRet = usBuildTXREQ(&TransData, SendFile);
        }
        iCount++;
        offset += sizeof (TRANS_DATA2);
        if (offset >= ulFileSize) break;
    }
    usRet = ECC_WriteXmlEND("TransXML", SendFile);
    fclose(fp);
    return iCount;
}

USHORT UpdateAdviceTxStatus() {

    TRANS_DATA2 tmpTransData;
    TRANS_DATA2 TransData;
    ezxml_t Trans, RecvXML;
    USHORT ret;
    SystemLog("UpdateAdviceTxStatus", "Start");
    gezxml_TMS = NULL;
    RecvXML = LoadXMLFile(RecvFile);
    if (RecvXML == NULL) {
        SystemLog("usUnPackResponData", "Load RecvFile Fail");
        return d_ERR_XMLError;
    }
    //  Trans = ezxml_get(RecvXML,"Trans",-1);
    Trans = RecvXML->child;
    while (Trans != NULL) {
        //   usUnFormatTransTag(TransData,Trans);
        usUnFormatTransTag2(&tmpTransData, Trans);
        if (atoi(tmpTransData.ucResponseCode) == 0) {
            ret = usGetTxDataByInvoiceNum(&TransData, tmpTransData.ulTerminalInvoiceNum);
            if (ret == d_OK) {
                usUnFormatTransTag2(&TransData, Trans);
                TransData.ucTXSTATUS = TransStatus_OK;
                ret = usUpdataTxData(&TransData);
            }
        }
        Trans = Trans->sibling;
    }
    ezxml_free(RecvXML);
    return d_OK;
}

USHORT GetLastTransData(TRANS_DATA2 *TransData) {
    SystemLog("GetLastTransData", "Start");
    ULONG offset;
    int iSize;
    int inRetVal;
    int iCount = 0;

    FILE *fp = fopen(TransDataFile, "r+");
    if (fp == NULL)
        return d_ERR_FILE_OPEN;
    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;
    offset = ulFileSize - sizeof (TRANS_DATA2);

    fseek(fp, offset, SEEK_SET);
    //fseek(fp,sizeof(TRANS_DATA2)+1,SEEK_END);      
    iSize = fread((BYTE *) TransData, sizeof (TRANS_DATA2), 1, fp);
    fclose(fp);
    /* if(iSize)
           return d_OK;
     else 
           return d_Fail;*/
    return d_OK;
}

USHORT SaveTCPDatatoSD(char* SendFILE, char * ReceiveData, int ReceiveDatalen) {

    STR path[64];
    STR filename[64];
    if (strcmp(gConfig.sDEBUG.SD.ENABLE, "0") == 0) return 0;
    USHORT ret;
    int iret;
    CTOS_RTC GetRTC;
    memset(filename, 0x00, sizeof (filename));

    ret = CTOS_RTCGet(&GetRTC);
    if (ret != 0) {
        return d_ERR_GETRTC;
    }
    memset(path, 0x00, sizeof (path));
    sprintf(path, "/media/mdisk/%04d/%02d/%02d/Trans/CMAS", GetRTC.bYear + 2000, GetRTC.bMonth, GetRTC.bDay);
    iret = CreateDir(path);
    memset(filename, 0x00, sizeof (filename));
    sprintf(filename, "%s/Send%02d%02d%02d.xml", path, GetRTC.bHour, GetRTC.bMinute, GetRTC.bSecond);
    iret = copyFiles((char *) SendFILE, filename);

    memset(filename, 0x00, sizeof (filename));
    sprintf(filename, "%s/Receive%02d%02d%02d.xml", path, GetRTC.bHour, GetRTC.bMinute, GetRTC.bSecond);
    ret = usWriteFile("Receive", ReceiveData, strlen(ReceiveData));

    iret = copyFiles((char *) "Receive", filename);
    remove("Receive");
    return 0;
}

USHORT CheckFLASHSTATUS() {
    USHORT ret = File_exist(SDFLASHSTATUS);
    if (ret == d_OK)
        MechineStatus |= Status_FLASH_ERROR;
    else {
        MechineStatus &= (~(Status_FLASH_ERROR));
    }

    return ret;
}

USHORT FLASHERROR() {
    STR filename[64];
    USHORT ret;
    memset(filename, 0x00, sizeof (filename));
    vdBuildMessageType2(gTransData.ucTXTYPE, gTransData.ucTXSTATUS, (BYTE *) & gTransData.ucMessageType);
    vdBuildProcessingCode2(&gTransData, (BYTE *) gTransData.ucProcessCode); //Processing Code 0300
    ret = usBuildTXREQ(&gTransData, SDFLASHSTATUS);

    return ret;
}

USHORT SaveBackupTxData(TRANS_DATA2 *TransData) {

    STR path[64];
    STR filename[64];
    STR TransFile[64];
    STR BatchTotalFile[64];
    STR time[32];
    USHORT ret;
    int iret;
    CTOS_RTC GetRTC;

    FILE * f;

    memset(filename, 0x00, sizeof (filename));
    memset(TransFile, 0x00, sizeof (TransFile));
    ret = CTOS_RTCGet(&GetRTC);
    if (ret != 0) {
        return d_ERR_GETRTC;
    }
    memset(path, 0x00, sizeof (path));
    sprintf(path, "/media/mdisk/%04d/%02d/%02d/Trans/DATA", GetRTC.bYear + 2000, GetRTC.bMonth, GetRTC.bDay);
    iret = CreateDir(path);

    BYTE ucBatchNo[8 + 1];
    USHORT usBatchSN;
    USHORT usRet = usGetCurrBatchSN(ucBatchNo, &usBatchSN);

    if (usRet != d_OK) return usRet;

    sprintf(BatchTotalFile, "%s/BatchTotal%s.dat", path, ucBatchNo);
    int size = sizeof (gBatchTotal);
    ret = usWriteFile(BatchTotalFile, (BYTE *) & gBatchTotal, size);

    sprintf(TransFile, "%s/Trans%s.dat", path, ucBatchNo);
    size = sizeof (TRANS_DATA2);
    ret = usAppendFile(TransFile, (BYTE *) TransData, size);

    memset(path, 0x00, sizeof (path));
    sprintf(path, "/media/mdisk/%04d/%02d/%02d/Trans/XML", GetRTC.bYear + 2000, GetRTC.bMonth, GetRTC.bDay);
    iret = CreateDir(path);
    memset(filename, 0x00, sizeof (filename));
    sprintf(filename, "%s/Batch%s.xml", path, ucBatchNo);
    vdBuildMessageType2(TransData->ucTXTYPE, TransData->ucTXSTATUS, (BYTE *) & TransData->ucMessageType); //Message Type ID 0100
    vdBuildProcessingCode2(TransData, (BYTE *) TransData->ucProcessCode); //Processing Code 0300
    usRet = usBuildTXREQ(TransData, filename);

}

USHORT GetBackupTxlogFile(STR *strYY, STR *strMM, STR *strDD, STR *strBatchNo, BYTE * Data, int *size) {
    STR filename[64];
    memset(filename, 0x00, sizeof (filename));
    sprintf(filename, "/media/mdisk/%s/%s/%s/Trans/Batch%s.xml", strYY, strMM, strDD, strBatchNo);
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL)
        return d_ERR_FILE_OPEN;
    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;


    *size = fread((BYTE *) Data, ulFileSize, 1, fp);
    fclose(fp);
    return d_OK;

}

USHORT BuildBatchUploadAdviceTxFile(char * filename) {

    ULONG offset;
    int iSize;
    int inRetVal;
    int iCount = 0;

    //  TRANS_DATA2 TransData;
    remove(SendFile);
    FILE *fp = fopen(filename, "ab+");
    if (fp == NULL)
        return d_ERR_FILE_OPEN;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    BYTE buffer[1024];
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    //   if(ulFileSize%sizeof(TRANS_DATA2)!=0) return d_ERR_FILE_SIZE_ERR;
    offset = 0;
    //buffer=malloc(ulFileSize); 
    USHORT usRet = ECC_WriteXmlHeader("TransXML", SendFile);
    USHORT getlen;
    fseek(fp, 0, SEEK_SET);

    do {
        if (ulFileSize - offset < 1024)
            getlen = ulFileSize - offset;
        else
            getlen = 1024;

        iSize = fread((BYTE *) buffer, 1, getlen, fp);
        // if(TransData.ucAdviceFLAG==0){
        usRet = usAppendFile(SendFile, buffer, iSize);
        offset += getlen;
    } while (offset < ulFileSize);

    fclose(fp);
    usRet = ECC_WriteXmlEND("TransXML", SendFile);

    return iCount;
}

//kobe added for debug

void myDebugPrinter(int level, const char* fmt, ...) {
    char szPrintBuffer[1024];
    char oneLine[64];
    char levelWords[32];
    int index = 0;
    int c = 0;
    int i = 0;
    va_list marker;

    memset(szPrintBuffer, 0x00, sizeof (szPrintBuffer));
    switch (level) {

        case DEBUG:
            if (gConfig.sDEBUG.PRINT.ENABLE == FALSE)
                return;
            sprintf(levelWords, "!DEBUG!");
            //index = strlen(szPrintBuffer);
            break;
        case WARN:
            sprintf(levelWords, "!!WARN!!");
            //index = strlen(szPrintBuffer);
            break;

        case ERROR:
            sprintf(levelWords, "!!!ERROR!!!");
            //index = strlen(szPrintBuffer);            
            break;
        default:
            return;
            break;
    }


    va_start(marker, fmt);
    vsprintf(szPrintBuffer, fmt, marker);
    va_end(marker);

    index = strlen(szPrintBuffer);
    c = ((index % 30) == 0) ? index / 30 : (index / 30) + 1; //caculate how much loop needed 
    sprintf(oneLine, "==========%s================", levelWords);
    CTOS_PrinterPutString(oneLine);
    for (i = 0; i < c; i++) {
        memset(oneLine, 0x00, 64);
        memcpy(oneLine, szPrintBuffer + (i * 30), 30);
        CTOS_PrinterPutString(oneLine);
    }
    CTOS_PrinterPutString("=====================================");
    CTOS_PrinterFline(64);

}
