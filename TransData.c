#include "ECCAPP.h"

void inBuildTxnDataTime2(BYTE *ucTxnDateTime, STR * strTxnDataTime, STR * strTxnData, STR *strTxnTime) {
    fnLongToUnix(strTxnDataTime, (unsigned long *) &ucTxnDateTime, 14); // Txn Date Time

    memcpy(strTxnData, &strTxnDataTime, 8); //1300
    strTxnData[8] = 0x00;
    memcpy(strTxnTime, &strTxnDataTime[8], 6); //1200
    strTxnTime[6] = 0x00;

}

void inBuildTxnDataTime(unsigned long ucTxnDateTime, STR * strTxnDataTime, STR * strTxnData, STR *strTxnTime) {
    fnLongToUnix(strTxnDataTime, (unsigned long *) &ucTxnDateTime, 14); // Txn Date Time
    memcpy(strTxnData, &strTxnDataTime, 8); //1300
    strTxnData[8] = 0x00;
    memcpy(strTxnTime, &strTxnDataTime[8], 6); //1200
    strTxnTime[6] = 0x00;

}

void inBuildCPUDEVICEID(BYTE *ucHEX_CPUDEVICEID, BYTE *ucSTR_CPUDEVICEID) {
    BYTE NDID[12 + 1];
    BYTE NSPD[15 + 1];
    BYTE tmp[3];
    UINT ispid;
    /*     memcpy(tmp,&ucHEX_CPUDEVICEID[3],3);
          ispid=atoi(tmp);
          sprintf(NEWSPID,"%015d",ispid);
     */
    wub_hex_2_str(ucHEX_CPUDEVICEID, (BYTE *) & NDID, 6); //4100

    int i, j;
    for (i = 0, j = 11; i < 12; i++, j--) {
        ucSTR_CPUDEVICEID[i] = NDID[j];
    }

    ucSTR_CPUDEVICEID[12] = 0;
}

void inBuilducSubMerchantID(BYTE * LocationID, BYTE *NewLocationID, BYTE * SubMerchantID) {

    fnUnPack(LocationID, 1, (unsigned char *) SubMerchantID); //Location ID

    fnUnPack(NewLocationID, 3, (unsigned char *) &SubMerchantID[2]); //CPU Location ID

}

void inBuildCardExpiryDateYYMM(unsigned long *ulExpiryDate, BYTE *bExpirydate) {
    BYTE expirydate[14];
    fnLongToUnix((unsigned char *) &expirydate, ulExpiryDate, 14);
    memcpy(bExpirydate, &expirydate, 4);
}

void inBuildDateYYDD(unsigned long *ulDate, BYTE *bDate) {
    BYTE datestr[14];
    fnLongToUnix((unsigned char *) &datestr, ulDate, 14);
    memcpy(bDate, &datestr, 8);
}

void inBuildCPUKEYInfo(BYTE AdminKeyKVN, BYTE CPUKeyKVN, BYTE IssuerKeyKVN, BYTE * KeyInfo) {
    BYTE buf[3 + 1];
    buf[0] = AdminKeyKVN;
    buf[1] = CPUKeyKVN;
    buf[2] = IssuerKeyKVN;
    buf[3] = 0;
    wub_hex_2_str((unsigned char *) &buf, KeyInfo, 3);
}

USHORT usParseTransFormat() {
    if (gTransFormatDATA == NULL) {
        gTransFormatDATA = ezxml_parse_file(TransFormatFile);
        if (gTransFormatDATA == NULL) {
            return d_ERR_XMLError;
        }
    }
    return d_OK;
}

USHORT usBuildTXREQ(TRANS_DATA2 * TransData, BYTE * FileName) {

    ezxml_t TransFormat;
    char *attr, *attr_name;
    USHORT ret;
    BYTE TransStatusSTR[12];
    BYTE TXReqData[1024 * 5];
    BYTE nodestr[1024];
    //  attr=malloc(16);
    // attr_name=malloc(12);
    memset(TransStatusSTR, 0x00, sizeof (TransStatusSTR));

    memset(TXReqData, 0x00, sizeof (TXReqData));

    ret = usParseTransFormat();
    if (ret != d_OK) return ret;

    TransFormat = ezxml_get(gTransFormatDATA, "TransFormat", 0, "TAGDEF", -1);
    TransFormat = TransFormat->child;
    if (TransFormat == NULL)
        return d_ERR_XMLError;


    int TransType = usGetTXTYPE_TRANSTYPE(TransData->ucTXTYPE);
    ret = usGetTransStatusSTR(TransType, TransData->ucTXSTATUS, TransStatusSTR);

    while (TransFormat != NULL) {
        memset(nodestr, 0x00, sizeof (nodestr));
        attr = (char*) ezxml_attr(TransFormat, (const char *) TransStatusSTR);
        if (attr != NULL) {
            if (TransType == TransType_DEBUG) {
                //		attr_name=ezxml_attr(TransFormat,(const char *)"name");
            } else {
                attr_name = NULL;
            }

            if ((strcmp(attr, "M") == 0) || (strcmp(attr, "C") == 0)) {
                //usFormatTransTag2(TransData,TransFormat->name,attr_name,Trans);
                usFormatTransTag3(TransData, TransFormat->name, NULL, nodestr);
                strcat(TXReqData, nodestr);
            }
            // 
        }
        TransFormat = TransFormat->sibling;
    }

    BYTE *Transstr = malloc(strlen(TXReqData) + 100);
    sprintf(Transstr, "<Trans>%s</Trans>", TXReqData);
    ret = usAppendFile(FileName, Transstr, strlen(Transstr));
    free(Transstr);

    ezxml_free(TransFormat);
    //ezxml_free( gTransFormatDATA); 


    return d_OK;
}

USHORT usBuildTXREQ2(TRANS_DATA2 * TransData, BYTE * FileName) {

    ezxml_t TransFormat, Trans;
    char *attr, *attr_name;
    USHORT ret;
    BYTE *TransStatusSTR;
    TransStatusSTR = malloc(12);
    //  attr=malloc(16);
    // attr_name=malloc(12);
    memset(TransStatusSTR, 0x00, sizeof (TransStatusSTR));

    Trans = ezxml_new_d("Trans");
    if (Trans == NULL) return d_ERR_XMLError;

    ret = usParseTransFormat();
    if (ret != d_OK) return ret;

    TransFormat = ezxml_get(gTransFormatDATA, "TransFormat", 0, "TAGDEF", -1);
    TransFormat = TransFormat->child;
    if (TransFormat == NULL)
        return d_ERR_XMLError;


    int TransType = usGetTXTYPE_TRANSTYPE(TransData->ucTXTYPE);
    ret = usGetTransStatusSTR(TransType, TransData->ucTXSTATUS, TransStatusSTR);

    while (TransFormat != NULL) {

        attr = (char*) ezxml_attr(TransFormat, (const char *) TransStatusSTR);
        if (attr != NULL) {
            if (TransType == TransType_DEBUG) {
                //		attr_name=ezxml_attr(TransFormat,(const char *)"name");
            } else {
                attr_name = NULL;
            }

            if ((strcmp(attr, "M") == 0) || (strcmp(attr, "C") == 0)) {
                //usFormatTransTag2(TransData,TransFormat->name,attr_name,Trans);
                usFormatTransTag2(TransData, TransFormat->name, NULL, Trans);
            }
            // 
        }
        TransFormat = TransFormat->sibling;
    }

    // Trans= ezxml_insert(Trans,TransXML1, 0);
    //   if(Trans==NULL) return d_ERR_XMLError;
    char * DATA = ezxml_toxml(Trans);
    ret = usAppendFile(FileName, DATA, strlen(DATA));



    free(TransStatusSTR);
    ezxml_free(TransFormat);
    //ezxml_free( gTransFormatDATA); 


    return d_OK;
}

USHORT usUnPackResponData(TRANS_DATA2 * TransData) {


    USHORT ret;
    size_t Size;

    BYTE TagData[1024 * 20], ItemName[256], ItemData[256];
    int TagDatalen, DataLen, TagLen;

    memset(gTMSData, 0x00, sizeof (gTMSData));

    /* ULONG filelen= File_GetLen(RecvFile);
     bData=malloc(filelen);
     ret=usReadFileData(RecvFile,&Size,bData);
     if(ret!=d_OK) goto exit;   */
    int offset = 0;

    TagDatalen = myxml_GetTag(gReceiveData, "Trans", TagData);
    DataLen = TagDatalen;
    //  if(ret!=d_OK) goto exit;
    while (1) {
        memset(ItemName, 0x00, sizeof (ItemName));
        memset(ItemData, 0x00, sizeof (ItemData));
        TagLen = myxml_GetFirstTag(&TagData[offset], DataLen, (BYTE *) & ItemName, (BYTE*) & ItemData);
        if (TagLen == 0) {
            if (offset >= TagDatalen)
                break;
            else
                ret = d_ERR_XMLError;
            return ret;
        }
        usUnFormatTransTag3(TransData, ItemName, ItemData);
        DataLen -= TagLen;
        offset += TagLen;
    }



    if (strlen(gTMSData) > 0) {
        BYTE *buff = malloc(strlen(gTMSData) + 100);
        sprintf(buff, "<TMS><VERSION VER=\"%s\">%s</VERSION></TMS>", gConfig.TMS.PARAMETER, gTMSData);
        ret = usAppendFile(TMSFILE, buff, strlen(buff));
        free(buff);
    }
    ret = d_OK;

    return ret;
}

USHORT usGetTagData(ezxml_t xml, char *txt) {
    if (xml->txt == NULL) return d_Fail;

    strcpy(txt, xml->txt);

    return 0;
}

