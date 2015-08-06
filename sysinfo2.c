
#include "ECCAPP.h"
#include "sysinfo2.h"

USHORT GetField(STR * File, STR * Node1Name, STR *ItemName, STR * TEXT) {
    USHORT ret = ECC_GetXMLTag(File, Node1Name, ItemName, TEXT);
    if (ret != d_OK) {
        ret = ECC_GetXMLTag(ConfigXML, Node1Name, ItemName, TEXT);
        if (ret == d_OK)ECC_SetXMLTag(File, Node1Name, ItemName, TEXT);
    }
    return d_OK;
}

ezxml_t SetField(ezxml_t RootNode, STR * Node1Name, STR *ItemName, STR * TEXT) {
    STR msgstr[64];
    RootNode = ezxml_get(RootNode, Node1Name, 0, ItemName, -1);
    if (RootNode == NULL) {
        sprintf(msgstr, "Get XML %s %s Tag Fail", "PRINT", "ENABLE");
        SystemLog("ECC_GetXMLTag", msgstr);
        return NULL;
    }
    RootNode = ezxml_set_txt(RootNode, TEXT);
    return RootNode;
}

USHORT GetField2L(STR * File, STR * Node1Name, STR * Node2Name, STR *ItemName, STR * TEXT) {

    USHORT ret = ECC_GetXMLTag2(File, Node1Name, Node2Name, ItemName, TEXT);
    if (ret != d_OK) {
        ret = ECC_GetXMLTag2(ConfigXML, Node1Name, Node2Name, ItemName, TEXT);
        if (ret == d_OK)ECC_SetXMLTag2(File, Node1Name, Node2Name, ItemName, TEXT);
    }
    return d_OK;
}

ezxml_t SetField2L(ezxml_t RootNode, STR * Node1Name, STR * Node2Name, STR *ItemName, STR * TEXT) {
    STR msgstr[64];
    RootNode = ezxml_get(RootNode, Node1Name, 0, Node2Name, 0, ItemName, -1);
    if (RootNode == NULL) {
        sprintf(msgstr, "Get XML %s %s Tag Fail", "PRINT", "ENABLE");
        SystemLog("ECC_GetXMLTag", msgstr);
        return NULL;
    }
    RootNode = ezxml_set_txt(RootNode, TEXT);
    return RootNode;
}

USHORT GetField3L(STR * File, STR * Node1Name, STR * Node2Name, STR * Node3Name, STR *ItemName, STR * TEXT) {
    USHORT ret = ECC_GetXMLTag3(File, Node1Name, Node2Name, Node3Name, ItemName, TEXT);
    if (ret != d_OK) {
        ret = ECC_GetXMLTag3(ConfigXML, Node1Name, Node2Name, Node3Name, ItemName, TEXT);
        if (ret == d_OK)ECC_SetXMLTag3(File, Node1Name, Node2Name, Node3Name, ItemName, TEXT);
    }
    return d_OK;
}

ezxml_t SetField3L(ezxml_t RootNode, STR * Node1Name, STR * Node2Name, STR * Node3Name, STR *ItemName, STR * TEXT) {
    STR msgstr[64];
    RootNode = ezxml_get(RootNode, Node1Name, 0, Node2Name, Node3Name, 0, ItemName, -1);
    if (RootNode == NULL) {
        sprintf(msgstr, "Get XML %s %s Tag Fail", "PRINT", "ENABLE");
        SystemLog("ECC_GetXMLTag", msgstr);
        return NULL;
    }
    RootNode = ezxml_set_txt(RootNode, TEXT);
    return RootNode;
}

USHORT GetDEBUGInfo() {
    USHORT ret = ECC_CheckXML(DEBUGINFO_Path);
    if (ret == FALSE)
        ResetSysInfoData(DEBUGINFO_Path, "DEBUG");

    ret = GetField2L(DEBUGINFO_Path, "DEBUG", "PRINT", "ENABLE", gConfig.sDEBUG.PRINT.ENABLE);
    if (ret != d_OK) return ret;
    ret = GetField2L(DEBUGINFO_Path, "DEBUG", "FTP", "ENABLE", gConfig.sDEBUG.FTP.ENABLE);
    if (ret != d_OK) return ret;
    ret = GetField2L(DEBUGINFO_Path, "DEBUG", "SD", "ENABLE", gConfig.sDEBUG.SD.ENABLE);
    if (ret != d_OK) return ret;
    ret = GetField2L(DEBUGINFO_Path, "DEBUG", "FTP", "IP", gConfig.sDEBUG.FTP.IP);
    if (ret != d_OK) return ret;
    ret = GetField2L(DEBUGINFO_Path, "DEBUG", "FTP", "ID", gConfig.sDEBUG.FTP.bID);
    if (ret != d_OK) return ret;
    ret = GetField2L(DEBUGINFO_Path, "DEBUG", "FTP", "PASSWORD", gConfig.sDEBUG.FTP.PASSWORD);
    if (ret != d_OK) return ret;
    ret = GetField2L(DEBUGINFO_Path, "DEBUG", "SD", "ENABLE", gConfig.sDEBUG.SD.ENABLE);
    if (ret != d_OK) return ret;
    return d_OK;
}

USHORT SetDEBUGInfo() {
    STR msgstr[64];



    USHORT ret = ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "PRINT", "ENABLE", gConfig.sDEBUG.PRINT.ENABLE);

    ret = ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "FTP", "ENABLE", gConfig.sDEBUG.FTP.ENABLE);
    ret = ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "SD", "ENABLE", gConfig.sDEBUG.SD.ENABLE);

    ret = ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "FTP", "IP", gConfig.sDEBUG.FTP.IP);

    ret = ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "FTP", "ID", gConfig.sDEBUG.FTP.bID);


    ret = ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "FTP", "PASSWORD", gConfig.sDEBUG.FTP.PASSWORD);

    ret = ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "SD", "ENABLE", gConfig.sDEBUG.SD.ENABLE);

    return d_OK;

}

USHORT GetTXInfo() {
    BYTE tmp[36];
    BYTE table[16];
    
    BYTE amtname[16];
    int tableindex = 0, amtindex = 0;
    USHORT ret = ECC_CheckXML(TXINFO_Path);
    if (ret == FALSE)
        ResetSysInfoData(TXINFO_Path, "TX");
    //ret= usGetCurrTransSN(gConfig.TX.SERIALNO);
    ret = GetTransSn(gConfig.TX.SERIALNO);
    ret = GetField(TXINFO_Path, "TX", "SERIALNO", gConfig.TX.SERIALNO);
    if (ret != d_OK) return d_ERR_XMLError;

    ret = GetField(TXINFO_Path, "TX", "SIGNONMAXTIME", gConfig.TX.SIGNONMAXTIME);
    if (ret != d_OK) return ret;

    ret = GetField(TXINFO_Path, "TX", "OFFLINETXLIMIT", gConfig.TX.OFFLINETXLIMIT);
    if (ret != d_OK) return ret;

    ret = GetField(TXINFO_Path, "TX", "FORCEONLINELIMIT", gConfig.TX.FORCEONLINELIMIT);
    if (ret != d_OK) return ret;

    ret = GetField(TXINFO_Path, "TX", "MiniunitsADDVALUE", gConfig.TX.MiniunitsADDVALUE);
    if (ret != d_OK) return ret;

    ret = GetField(TXINFO_Path, "TX", "AUTOLOADLIMITAMT", gConfig.TX.AUTOLOADLIMITAMT);
    if (ret != d_OK) return ret;

    ret = GetField(TXINFO_Path, "TX", "OPERATIONMODE", gConfig.TX.OPERATIONMODE);
    if (ret != d_OK) return ret;


    for (tableindex = 0; tableindex < 15; tableindex++) {
        sprintf(table, "AMTTABLE%d", tableindex);
        memset(tmp, 0x00, sizeof(tmp));
        ret = GetField2L(TXINFO_Path, "TX", table, "AREACODE", tmp);
        gConfig.TX.AMTTABLE[tableindex].AREACODE = atoi(tmp);
        
        memset(tmp, 0x00, sizeof(tmp));
        ret = GetField2L(TXINFO_Path, "TX", table, "NAME", tmp);
        sprintf(gConfig.TX.AMTTABLE[tableindex].NAME, "%s", tmp);
        //printf("[%s,%d] got xml config to gConfig.TX.AMTTABLE[%d], areaCode(%d), name(%s)\n",__FUNCTION__,__LINE__,tableindex, gConfig.TX.AMTTABLE[tableindex].AREACODE, gConfig.TX.AMTTABLE[tableindex].NAME);
        
        for (amtindex = 0; amtindex < 10; amtindex++) {
            sprintf(amtname, "AMT%d", amtindex);
            memset(tmp, 0x00, sizeof(tmp));
            ret = GetField2L(TXINFO_Path, "TX", table, amtname, tmp);
            gConfig.TX.AMTTABLE[tableindex].AMT[amtindex] = atoi(tmp);
            //printf("[%s,%d] i(%d)=%d\n",__FUNCTION__,__LINE__,amtindex,gConfig.TX.AMTTABLE[tableindex].AMT[amtindex]);
        }
        
    }
    return d_OK;
}

USHORT SetAUTOFIXMODE_SelectAMT(USHORT index) {
    BYTE tableindex[8 + 1];
    sprintf(tableindex, "%d", index);
    return ECC_SetXMLTag2(TXINFO_Path, "TX", "AMTTABLE0", "AREACODE", tableindex);
}

USHORT SetAMTTABLE(USHORT table, USHORT index, USHORT amt) {
    BYTE tablename[16 + 1];
    BYTE tableindex[8 + 1];
    BYTE amtstr[8 + 1];
    sprintf(tablename, "AMTTABLE%d", table);
    sprintf(tableindex, "AMT%d", index);
    sprintf(amtstr, "%d", amt);

    return ECC_SetXMLTag2(TXINFO_Path, "TX", tablename, tableindex, amtstr);
}

USHORT SetAMTTABLENAME(USHORT table, BYTE * name) {
    BYTE tablename[16 + 1];
    BYTE tableindex[8 + 1];
    BYTE amtstr[8 + 1];
    sprintf(tablename, "AMTTABLE%d", table);
    sprintf(tableindex, "NAME");
    sprintf(gConfig.TX.AMTTABLE[table].NAME, "%s", name);
    return ECC_SetXMLTag2(TXINFO_Path, "TX", tablename, tableindex, name);
}

USHORT SetTXInfo() {

    BYTE tmpstr[36];

    USHORT ret = ECC_SetXMLTag(TXINFO_Path, "TX", "SERIALNO", gConfig.TX.SERIALNO);
    ret = SAVETransSn(gConfig.TX.SERIALNO);
    ret = ECC_SetXMLTag(TXINFO_Path, "TX", "SIGNONMAXTIME", gConfig.TX.SIGNONMAXTIME);

    ret = ECC_SetXMLTag(TXINFO_Path, "TX", "OFFLINETXLIMIT", gConfig.TX.OFFLINETXLIMIT);

    ret = ECC_SetXMLTag(TXINFO_Path, "TX", "FORCEONLINELIMIT", gConfig.TX.FORCEONLINELIMIT);

    ret = ECC_SetXMLTag(TXINFO_Path, "TX", "MiniunitsADDVALUE", gConfig.TX.MiniunitsADDVALUE);

    ret = ECC_SetXMLTag(TXINFO_Path, "TX", "AUTOLOADLIMITAMT", gConfig.TX.AUTOLOADLIMITAMT);
    ret = ECC_SetXMLTag(TXINFO_Path, "TX", "OPERATIONMODE", gConfig.TX.OPERATIONMODE);


    BYTE table[16];
    BYTE tablename[36];
    BYTE amtname[16];
    int tableindex, amtindex = 0;
    for (tableindex = 0; tableindex < 15; tableindex++) {
        sprintf(table, "AMTTABLE%d", tableindex);

        sprintf(tmpstr, "%d", gConfig.TX.AMTTABLE[tableindex].AREACODE);
        ret = ECC_SetXMLTag2(TXINFO_Path, "TX", tablename, "AREACODE", tmpstr);
        sprintf(tmpstr, "%s", gConfig.TX.AMTTABLE[tableindex].NAME);
        ret = ECC_SetXMLTag2(TXINFO_Path, "TX", tablename, "NAME", tmpstr);
        for (amtindex = 0; amtindex < 10; amtindex++) {
            sprintf(amtname, "AMT%d", amtindex);
            sprintf(tmpstr, "%d", gConfig.TX.AMTTABLE[tableindex].AMT[amtindex]);
            ret = ECC_SetXMLTag2(TXINFO_Path, "TX", tablename, amtname, tmpstr);
        }
    }
    return d_OK;
}

USHORT GetDEVICEInfo() {
    USHORT ret = ECC_CheckXML(DEVICEINFO_Path);
    if (ret == FALSE)
        ResetSysInfoData(DEVICEINFO_Path, "DEVICE");

    ret = GetField(DEVICEINFO_Path, "DEVICE", "SSLEnable", gConfig.DEVICE.SSLEnable);
    if (ret != d_OK) return ret;
    ret = GetField(DEVICEINFO_Path, "DEVICE", "SAMSLOT", gConfig.DEVICE.SAMSLOT);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "PORT", gConfig.DEVICE.READER.bPORT);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "BAUDRATE", gConfig.DEVICE.READER.bBAUDRATE);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "PARITY", gConfig.DEVICE.READER.bPARITY);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "DATABITS", gConfig.DEVICE.READER.bDATABITS);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "STOPBITS", gConfig.DEVICE.READER.bSTOPBITS);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "HostSpecVersionNo", gConfig.DEVICE.READER.bHostSpecVersionNo);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "READERID", gConfig.DEVICE.READER.bREADERID);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "READERFWVER", gConfig.DEVICE.READER.bREADERFWVER);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_SAMID", gConfig.DEVICE.READER.MIFARE_SAMID);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_SAMSN", gConfig.DEVICE.READER.MIFARE_SAMSN);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_SAMKEYVER", gConfig.DEVICE.READER.MIFARE_SAMKEYVER);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_DEVICEID", gConfig.DEVICE.READER.MIFARE_DEVICEID);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "RemainderAddQuota", gConfig.DEVICE.READER.RemainderAddQuota);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "CancelCreditQuota", gConfig.DEVICE.READER.CancelCreditQuota);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_DEVICEID", gConfig.DEVICE.READER.MIFARE_DEVICEID);
    if (ret != d_OK) return ret;

    //  ret= GetField2L(DEVICEINFO_Path, "DEVICE","READER","READERSTATUS",gConfig.DEVICE.READER.bREADERSTATUS);
    //    if(ret!=d_OK) return ret; 

    ret = GetField3L(DEVICEINFO_Path, "DEVICE", "READER", "CPU", "SAMVER", gConfig.DEVICE.READER.CPU.SAMVER);
    if (ret != d_OK) return ret;

    ret = GetField3L(DEVICEINFO_Path, "DEVICE", "READER", "CPU", "SAMID", gConfig.DEVICE.READER.CPU.SAMID);
    if (ret != d_OK) return ret;

    ret = GetField3L(DEVICEINFO_Path, "DEVICE", "READER", "CPU", "CPUDEVICEID", gConfig.DEVICE.READER.CPU.CPUDEVICEID);
    if (ret != d_OK) return ret;


    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "ECR", "PORT", gConfig.DEVICE.ECR.bPORT);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "ECR", "BAUDRATE", gConfig.DEVICE.ECR.bBAUDRATE);
    if (ret != d_OK) return ret;
    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "ECR", "PARITY", gConfig.DEVICE.ECR.bPARITY);
    if (ret != d_OK) return ret;

    ret = GetField2L(DEVICEINFO_Path, "DEVICE", "ECR", "DATABITS", gConfig.DEVICE.ECR.bDATABITS);
    if (ret != d_OK) return ret;
    ret = GetField(DEVICEINFO_Path, "DEVICE", "PMPASSWORD", gConfig.DEVICE.PMPASSWORD);
    ret = GetField(DEVICEINFO_Path, "DEVICE", "SMPASSWORD", gConfig.DEVICE.SMPASSWORD);
    ret = GetField(DEVICEINFO_Path, "DEVICE", "MMPASSWORD", gConfig.DEVICE.MMPASSWORD);
    ret = GetField(DEVICEINFO_Path, "DEVICE", "DMPASSWORD", gConfig.DEVICE.DMPASSWORD);
    return d_OK;

}

USHORT SetDEVICEInfo() {

    USHORT ret = ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE", "SSLEnable", gConfig.DEVICE.SSLEnable);


    ret = ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE", "SAMSLOT", gConfig.DEVICE.SAMSLOT);

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "PORT", gConfig.DEVICE.READER.bPORT);

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "PARITY", gConfig.DEVICE.READER.bPARITY);

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "DATABITS", gConfig.DEVICE.READER.bDATABITS);

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "HostSpecVersionNo", gConfig.DEVICE.READER.bHostSpecVersionNo);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "READERID", gConfig.DEVICE.READER.bREADERID);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "READERFWVER", gConfig.DEVICE.READER.bREADERFWVER);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_SAMID", gConfig.DEVICE.READER.MIFARE_SAMID);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_SAMSN", gConfig.DEVICE.READER.MIFARE_SAMSN);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_SAMKEYVER", gConfig.DEVICE.READER.MIFARE_SAMKEYVER);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_DEVICEID", gConfig.DEVICE.READER.MIFARE_DEVICEID);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "RemainderAddQuota", gConfig.DEVICE.READER.RemainderAddQuota);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "CancelCreditQuota", gConfig.DEVICE.READER.CancelCreditQuota);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "MIFARE_DEVICEID", gConfig.DEVICE.READER.MIFARE_DEVICEID);
    if (ret != d_OK) return ret;

    //    ret= ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE","READER","READERSTATUS",gConfig.DEVICE.READER.bREADERSTATUS);
    //     if(ret!=d_OK) return ret; 

    ret = ECC_SetXMLTag3(DEVICEINFO_Path, "DEVICE", "READER", "CPU", "SAMVER", gConfig.DEVICE.READER.CPU.SAMVER);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag3(DEVICEINFO_Path, "DEVICE", "READER", "CPU", "SAMID", gConfig.DEVICE.READER.CPU.SAMID);
    if (ret != d_OK) return ret;

    ret = ECC_SetXMLTag3(DEVICEINFO_Path, "DEVICE", "READER", "CPU", "CPUDEVICEID", gConfig.DEVICE.READER.CPU.CPUDEVICEID);
    if (ret != d_OK) return ret;



    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "ECR", "PORT", gConfig.DEVICE.ECR.bPORT);

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "ECR", "BAUDRATE", gConfig.DEVICE.ECR.bBAUDRATE);

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "ECR", "PARITY", gConfig.DEVICE.ECR.bPARITY);

    ret = ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "ECR", "DATABITS", gConfig.DEVICE.ECR.bDATABITS);

    ret = ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE", "PMPASSWORD", gConfig.DEVICE.PMPASSWORD);
    ret = ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE", "SMPASSWORD", gConfig.DEVICE.SMPASSWORD);
    ret = ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE", "MPMPASSWORD", gConfig.DEVICE.MMPASSWORD);
    ret = ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE", "DMPASSWORD", gConfig.DEVICE.DMPASSWORD);
    return d_OK;
}

USHORT GetTMInfo() {
    USHORT ret = ECC_CheckXML(TMINFO_Path);
    if (ret == FALSE)
        ResetSysInfoData(TMINFO_Path, "TM");

    ret = GetField(TMINFO_Path, "TM", "ID", gConfig.TM.bID);
    if (ret != d_OK) return ret;
    ret = GetField(TMINFO_Path, "TM", "AgentNumber", gConfig.TM.AgentNumber);
    if (ret != d_OK) return ret;
    ret = GetField(TMINFO_Path, "TM", "TITLE", gConfig.TM.TITLE);
    if (ret != d_OK) return ret;
    ret = GetField(TMINFO_Path, "TM", "SUBTITLE", gConfig.TM.SUBTITLE);
    if (ret != d_OK) return ret;
    ret = GetField(TMINFO_Path, "TM", "RECEIPTNUM", gConfig.TM.RECEIPTNUM);
    if (ret != d_OK) return ret;
    ret = GetField(TMINFO_Path, "TM", "RECEIPTTYPE1", gConfig.TM.RECEIPTTYPE1);
    if (ret != d_OK) return ret;
    ret = GetField(TMINFO_Path, "TM", "RECEIPTTYPE2", gConfig.TM.RECEIPTTYPE2);
    if (ret != d_OK) return ret;
    ret = GetField2L(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING1", gConfig.TM.RECEIPTREMARK.STRING1);
    if (ret != d_OK) return ret;
    ret = GetField2L(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING2", gConfig.TM.RECEIPTREMARK.STRING2);
    if (ret != d_OK) return ret;
    ret = GetField2L(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING3", gConfig.TM.RECEIPTREMARK.STRING3);
    if (ret != d_OK) return ret;
    ret = GetField2L(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING4", gConfig.TM.RECEIPTREMARK.STRING4);
    if (ret != d_OK) return ret;
    ret = GetField2L(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING5", gConfig.TM.RECEIPTREMARK.STRING5);
    if (ret != d_OK) return ret;

    return d_OK;
}

USHORT SetTMInfo() {

    USHORT ret = ECC_SetXMLTag(TMINFO_Path, "TM", "AgentNumber", gConfig.TM.AgentNumber);

    ret = ECC_SetXMLTag(TMINFO_Path, "TM", "AgentNumber", gConfig.TM.AgentNumber);

    ret = ECC_SetXMLTag(TMINFO_Path, "TM", "TITLE", gConfig.TM.TITLE);

    ret = ECC_SetXMLTag(TMINFO_Path, "TM", "RECEIPTNUM", gConfig.TM.RECEIPTNUM);

    ret = ECC_SetXMLTag(TMINFO_Path, "TM", "SUBTITLE", gConfig.TM.SUBTITLE);

    ret = ECC_SetXMLTag(TMINFO_Path, "TM", "RECEIPTTYPE1", gConfig.TM.RECEIPTTYPE1);

    ret = ECC_SetXMLTag(TMINFO_Path, "TM", "RECEIPTTYPE2", gConfig.TM.RECEIPTTYPE2);

    ret = ECC_SetXMLTag2(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING1", gConfig.TM.RECEIPTREMARK.STRING1);

    ret = ECC_SetXMLTag2(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING2", gConfig.TM.RECEIPTREMARK.STRING2);

    ret = ECC_SetXMLTag2(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING3", gConfig.TM.RECEIPTREMARK.STRING3);

    ret = ECC_SetXMLTag2(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING4", gConfig.TM.RECEIPTREMARK.STRING4);

    ret = ECC_SetXMLTag2(TMINFO_Path, "TM", "RECEIPTREMARK", "STRING5", gConfig.TM.RECEIPTREMARK.STRING5);

    return d_OK;
}

USHORT GetMERCHANTInfo() {
    USHORT ret = ECC_CheckXML(MERCHANTINFO_Path);
    if (ret == FALSE)
        ResetSysInfoData(MERCHANTINFO_Path, "MERCHANT");

    ret = GetField(MERCHANTINFO_Path, "MERCHANT", "MERCHANTID", gConfig.MERCHANT.MERCHANTID);
    if (ret != d_OK) return ret;
    ret = GetField(MERCHANTINFO_Path, "MERCHANT", "NewLocationID", gConfig.MERCHANT.NewLocationID);
    if (ret != d_OK) return ret;
    ret = GetField(MERCHANTINFO_Path, "MERCHANT", "STCODE", gConfig.MERCHANT.STCODE);
    if (ret != d_OK) return ret;
    return d_OK;
}

USHORT SetMERCHANTInfo() {

    USHORT ret = ECC_SetXMLTag(MERCHANTINFO_Path, "MERCHANT", "MERCHANTID", gConfig.MERCHANT.MERCHANTID);

    ret = ECC_SetXMLTag(MERCHANTINFO_Path, "MERCHANT", "NewLocationID", gConfig.MERCHANT.NewLocationID);

    ret = ECC_SetXMLTag(MERCHANTINFO_Path, "MERCHANT", "STCODE", gConfig.MERCHANT.STCODE);



    return d_OK;
}

USHORT GetBATCHInfo() {
    USHORT ret = ECC_CheckXML(BATCHINFO_Path);
    if (ret == FALSE)
        ResetSysInfoData(BATCHINFO_Path, "BATCH");

    ret = GetField(BATCHINFO_Path, "BATCH", "NO", gConfig.BATCH.NO);
    if (ret != d_OK) return ret;
    ret = GetBatchSN(gConfig.BATCH.NO);
    return d_OK;
}

USHORT SetBATCHInfo() {

    ECC_SetXMLTag(BATCHINFO_Path, "BATCH", "NO", gConfig.BATCH.NO);
    SAVEBatchSN(gConfig.BATCH.NO);
    return d_OK;
}

USHORT GetETHERNETInfo() {
    USHORT ret = ECC_CheckXML(ETHERNETINFO_Path);
    if (ret == FALSE)
        ResetSysInfoData(ETHERNETINFO_Path, "ETHERNET");

    ret = GetField(ETHERNETINFO_Path, "ETHERNET", "CONNECTHOST", gConfig.ETHERNET.CONNECTHOST);
    if (ret != d_OK) return ret;


    ret = GetField(ETHERNETINFO_Path, "ETHERNET", "NETWORKMODE", gConfig.ETHERNET.NETWORKMODE);
    if (ret != d_OK) return ret;

    ret = GetField(ETHERNETINFO_Path, "ETHERNET", "EthernetCHANNEL", gConfig.ETHERNET.EthernetCHANNEL);
    if (ret != d_OK) return ret;

    ret = GetField2L(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "IP", gConfig.ETHERNET.LOCAL.IP);
    if (ret != d_OK) return ret;

    ret = GetField2L(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "MASK", gConfig.ETHERNET.LOCAL.MASK);
    if (ret != d_OK) return ret;

    ret = GetField2L(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "GATEWAY", gConfig.ETHERNET.LOCAL.GATEWAY);
    if (ret != d_OK) return ret;
    ret = GetField2L(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "DNS", gConfig.ETHERNET.LOCAL.DNS);
    if (ret != d_OK) return ret;
    ret = GetField2L(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "MAC", gConfig.ETHERNET.LOCAL.MAC);
    if (ret != d_OK) return ret;

    ret = GetField2L(ETHERNETINFO_Path, "ETHERNET", "GPRS", "SIMSLOT", gConfig.ETHERNET.GPRS.SIMSLOT);
    if (ret != d_OK) return ret;

    ret = GetField2L(ETHERNETINFO_Path, "ETHERNET", "GPRS", "PINCODE", gConfig.ETHERNET.GPRS.PINCODE);
    if (ret != d_OK) return ret;

    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "HOST", "URL", gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "HOST", "IP", gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "HOST", "VIPIP", gConfig.ETHERNET.HOST_PRODUCTION.HOST.VIPIP);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "HOST", "PORT", gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "FTP", "URL", gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "FTP", "IP", gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "FTP", "LOGINID", gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "FTP", "LOGINPASSWORD", gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD);
    if (ret != d_OK) return ret;

    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "HOST", "URL", gConfig.ETHERNET.HOST_TESTING.HOST.URL);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "HOST", "IP", gConfig.ETHERNET.HOST_TESTING.HOST.IP);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "HOST", "VIPIP", gConfig.ETHERNET.HOST_TESTING.HOST.VIPIP);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "HOST", "PORT", gConfig.ETHERNET.HOST_TESTING.HOST.PORT);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "FTP", "URL", gConfig.ETHERNET.HOST_TESTING.FTP.URL);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "FTP", "IP", gConfig.ETHERNET.HOST_TESTING.FTP.IP);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "FTP", "LOGINID", gConfig.ETHERNET.HOST_TESTING.FTP.LOGINID);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "FTP", "LOGINPASSWORD", gConfig.ETHERNET.HOST_TESTING.FTP.LOGINPASSWORD);
    if (ret != d_OK) return ret;


    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "HOST", "URL", gConfig.ETHERNET.HOST_DEVELOP.HOST.URL);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "HOST", "IP", gConfig.ETHERNET.HOST_DEVELOP.HOST.IP);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "HOST", "VIPIP", gConfig.ETHERNET.HOST_DEVELOP.HOST.VIPIP);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "HOST", "PORT", gConfig.ETHERNET.HOST_DEVELOP.HOST.PORT);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "FTP", "URL", gConfig.ETHERNET.HOST_DEVELOP.FTP.URL);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "FTP", "IP", gConfig.ETHERNET.HOST_DEVELOP.FTP.IP);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "FTP", "LOGINID", gConfig.ETHERNET.HOST_DEVELOP.FTP.LOGINID);
    if (ret != d_OK) return ret;
    ret = GetField3L(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "FTP", "LOGINPASSWORD", gConfig.ETHERNET.HOST_DEVELOP.FTP.PORT);
    if (ret != d_OK) return ret;
}

USHORT SetETHERNETInfo() {

    ECC_SetXMLTag(ETHERNETINFO_Path, "ETHERNET", "CONNECTHOST", gConfig.ETHERNET.CONNECTHOST);


    ECC_SetXMLTag(ETHERNETINFO_Path, "ETHERNET", "EthernetCHANNEL", gConfig.ETHERNET.EthernetCHANNEL);


    ECC_SetXMLTag(ETHERNETINFO_Path, "ETHERNET", "NETWORKMODE", gConfig.ETHERNET.NETWORKMODE);

    ECC_SetXMLTag2(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "IP", gConfig.ETHERNET.LOCAL.IP);


    ECC_SetXMLTag2(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "MASK", gConfig.ETHERNET.LOCAL.MASK);


    ECC_SetXMLTag2(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "GATEWAY", gConfig.ETHERNET.LOCAL.GATEWAY);

    ECC_SetXMLTag2(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "DNS", gConfig.ETHERNET.LOCAL.DNS);

    ECC_SetXMLTag2(ETHERNETINFO_Path, "ETHERNET", "LOCAL", "MAC", gConfig.ETHERNET.LOCAL.MAC);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "HOST", "URL", gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "HOST", "IP", gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "HOST", "VIPIP", gConfig.ETHERNET.HOST_PRODUCTION.HOST.VIPIP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "HOST", "PORT", gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "FTP", "URL", gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "FTP", "IP", gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "FTP", "VIPIP", gConfig.ETHERNET.HOST_PRODUCTION.FTP.VIPIP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "FTP", "LOGINID", gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_PRODUCTION", "FTP", "LOGINPASSWORD", gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "HOST", "URL", gConfig.ETHERNET.HOST_TESTING.HOST.URL);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "HOST", "IP", gConfig.ETHERNET.HOST_TESTING.HOST.IP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "HOST", "VIPIP", gConfig.ETHERNET.HOST_TESTING.HOST.VIPIP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "HOST", "PORT", gConfig.ETHERNET.HOST_TESTING.HOST.PORT);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "FTP", "URL", gConfig.ETHERNET.HOST_TESTING.FTP.URL);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "FTP", "IP", gConfig.ETHERNET.HOST_TESTING.FTP.IP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "FTP", "VIPIP", gConfig.ETHERNET.HOST_TESTING.FTP.VIPIP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "FTP", "LOGINID", gConfig.ETHERNET.HOST_TESTING.FTP.LOGINID);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_TESTING", "FTP", "LOGINPASSWORD", gConfig.ETHERNET.HOST_TESTING.FTP.LOGINPASSWORD);


    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "HOST", "URL", gConfig.ETHERNET.HOST_DEVELOP.HOST.URL);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "HOST", "IP", gConfig.ETHERNET.HOST_DEVELOP.HOST.IP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "HOST", "VIPIP", gConfig.ETHERNET.HOST_DEVELOP.HOST.VIPIP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "HOST", "PORT", gConfig.ETHERNET.HOST_DEVELOP.HOST.PORT);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "FTP", "URL", gConfig.ETHERNET.HOST_DEVELOP.FTP.URL);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "FTP", "IP", gConfig.ETHERNET.HOST_DEVELOP.FTP.IP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "FTP", "VIPIP", gConfig.ETHERNET.HOST_DEVELOP.FTP.VIPIP);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "FTP", "LOGINID", gConfig.ETHERNET.HOST_DEVELOP.FTP.LOGINID);

    ECC_SetXMLTag3(ETHERNETINFO_Path, "ETHERNET", "HOST_DEVELOP", "FTP", "LOGINPASSWORD", gConfig.ETHERNET.HOST_DEVELOP.FTP.LOGINPASSWORD);

    return d_OK;
}

USHORT GetVERSIONInfo() {
    USHORT ret = ECC_CheckXML(VERSIONINFO_Path);
    if (ret == FALSE)
        ResetSysInfoData(VERSIONINFO_Path, "VERSION");

    ret = GetField2L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "PARAMETER", gConfig.CURRVERSION.PARAMETER);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "AP", "NAME", gConfig.CURRVERSION.AP.NAME);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "AP", "VERSION", gConfig.CURRVERSION.AP.VERSION);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "AP", "GeneratedDateTime", gConfig.CURRVERSION.AP.GeneratedDateTime);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "AP", "Company", gConfig.CURRVERSION.PARAMETER);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "VERSION", gConfig.CURRVERSION.BLC.VERSION);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "NAME", gConfig.CURRVERSION.BLC.NAME);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "TYPE", gConfig.CURRVERSION.BLC.TYPE);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "UPDATETIME", gConfig.CURRVERSION.BLC.UPDATETIME);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "VERSION", gConfig.CURRVERSION.SSL.VERSION);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "CAFILENAME1", gConfig.CURRVERSION.SSL.CAFILENAME1);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "CAEXPIRYDAY1", gConfig.CURRVERSION.SSL.CAEXPIRYDAY1);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "CAFILENAME2", gConfig.CURRVERSION.SSL.CAFILENAME2);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "CAEXPIRYDAY2", gConfig.CURRVERSION.SSL.CAEXPIRYDAY2);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "READERFW", "NAME", gConfig.CURRVERSION.READERFW.NAME);
    if (ret != d_OK) return ret;
    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "READERFW", "VERSION", gConfig.CURRVERSION.READERFW.VERSION);
    if (ret != d_OK) return ret;
    ret = GetField3L(VERSIONINFO_Path, "VERSION", "CURRVERSION", "READERFW", "FTPPATH", gConfig.CURRVERSION.READERFW.FTPPATH);
    if (ret != d_OK) return ret;



    ret = GetField2L(VERSIONINFO_Path, "VERSION", "TMS", "PARAMETER", gConfig.TMS.PARAMETER);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "AP", "NAME", gConfig.TMS.AP.NAME);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "AP", "VERSION", gConfig.TMS.AP.VERSION);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "AP", "GeneratedDateTime", gConfig.TMS.AP.GeneratedDateTime);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "AP", "Company", gConfig.TMS.PARAMETER);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "AP", "FTPPATH", gConfig.TMS.AP.FTPPATH);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "BLC", "VERSION", gConfig.TMS.BLC.VERSION);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "BLC", "NAME", gConfig.TMS.BLC.NAME);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "BLC", "TYPE", gConfig.TMS.BLC.TYPE);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "BLC", "FTPPATH", gConfig.TMS.BLC.FTPPATH);
    if (ret != d_OK) return ret;
    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "BLC", "UPDATETIME", gConfig.TMS.BLC.UPDATETIME);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "VERSION", gConfig.TMS.SSL.VERSION);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "FTPPATH", gConfig.TMS.SSL.FTPPATH);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "CAFILENAME1", gConfig.TMS.SSL.CAFILENAME1);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "CAEXPIRYDAY1", gConfig.TMS.SSL.CAEXPIRYDAY1);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "CAFILENAME2", gConfig.TMS.SSL.CAFILENAME2);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "CAEXPIRYDAY2", gConfig.TMS.SSL.CAEXPIRYDAY2);
    if (ret != d_OK) return ret;

    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "READERFW", "NAME", gConfig.TMS.READERFW.NAME);
    if (ret != d_OK) return ret;
    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "READERFW", "VERSION", gConfig.TMS.READERFW.VERSION);
    if (ret != d_OK) return ret;
    ret = GetField3L(VERSIONINFO_Path, "VERSION", "TMS", "READERFW", "FTPPATH", gConfig.TMS.READERFW.FTPPATH);
    if (ret != d_OK) return ret;


    return d_OK;
}

USHORT SetVERSIONInfo() {

    ECC_SetXMLTag2(VERSIONINFO_Path, "VERSION", "CURRVERSION", "PARAMETER", gConfig.CURRVERSION.PARAMETER);


    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "AP", "NAME", gConfig.CURRVERSION.AP.NAME);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "AP", "VERSION", gConfig.CURRVERSION.AP.VERSION);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "AP", "GeneratedDateTime", gConfig.CURRVERSION.AP.GeneratedDateTime);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "VERSION", gConfig.CURRVERSION.BLC.VERSION);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "NAME", gConfig.CURRVERSION.BLC.NAME);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "TYPE", gConfig.CURRVERSION.BLC.TYPE);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "BLC", "UPDATETIME", gConfig.CURRVERSION.BLC.UPDATETIME);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "VERSION", gConfig.CURRVERSION.SSL.VERSION);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "CAFILENAME1", gConfig.CURRVERSION.SSL.CAFILENAME1);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "CAEXPIRYDAY1", gConfig.CURRVERSION.SSL.CAEXPIRYDAY1);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "CAFILENAME2", gConfig.CURRVERSION.SSL.CAFILENAME1);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "SSL", "CAEXPIRYDAY2", gConfig.CURRVERSION.SSL.CAEXPIRYDAY1);


    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "READERFW", "NAME", gConfig.CURRVERSION.READERFW.NAME);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "READERFW", "VERSION", gConfig.CURRVERSION.READERFW.VERSION);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "CURRVERSION", "READERFW", "FTPPATH", gConfig.CURRVERSION.READERFW.FTPPATH);



    ECC_SetXMLTag2(VERSIONINFO_Path, "VERSION", "TMS", "PARAMETER", gConfig.TMS.PARAMETER);


    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "AP", "NAME", gConfig.TMS.AP.NAME);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "AP", "VERSION", gConfig.TMS.AP.VERSION);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "AP", "GeneratedDateTime", gConfig.TMS.AP.GeneratedDateTime);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "BLC", "VERSION", gConfig.TMS.BLC.VERSION);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "BLC", "NAME", gConfig.TMS.BLC.NAME);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "BLC", "TYPE", gConfig.TMS.BLC.TYPE);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "BLC", "UPDATETIME", gConfig.TMS.BLC.UPDATETIME);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "VERSION", gConfig.TMS.SSL.VERSION);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "CAFILENAME1", gConfig.TMS.SSL.CAFILENAME1);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "CAEXPIRYDAY1", gConfig.TMS.SSL.CAEXPIRYDAY1);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "CAFILENAME2", gConfig.TMS.SSL.CAFILENAME1);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "SSL", "CAEXPIRYDAY2", gConfig.TMS.SSL.CAEXPIRYDAY1);


    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "READERFW", "NAME", gConfig.TMS.READERFW.NAME);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "READERFW", "VERSION", gConfig.TMS.READERFW.VERSION);

    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION", "TMS", "READERFW", "FTPPATH", gConfig.TMS.READERFW.FTPPATH);



    return d_OK;
}

void Sysinfo2_GetData() {

    GetDEBUGInfo();
    GetTMInfo();
    GetTXInfo();
    GetMERCHANTInfo();
    GetDEVICEInfo();
    GetBATCHInfo();
    GetETHERNETInfo();
    GetVERSIONInfo();

}

void Sysinfo2_SetData() {
    SetDEBUGInfo();
    SetTMInfo();
    SetTXInfo();
    SetMERCHANTInfo();
    SetDEVICEInfo();
    SetBATCHInfo();
    SetETHERNETInfo();
    SetVERSIONInfo();

}

USHORT ResetSysInfoData(STR * FileName, STR * TagName) {
    STR msgstr[64];
    ezxml_t configfile = ezxml_parse_file(ConfigXML);
    ezxml_t ConfigNode = ezxml_get(configfile, TagName, -1);
    
    //printf("[%s,%d] ResetSysInfoData start\n",__FUNCTION__,__LINE__);
    if (ConfigNode == NULL) {
        sprintf(msgstr, "Get XML %s Tag Fail", TagName);
        SystemLog("ECC_GetXMLTag", msgstr);
        return d_ERR_XMLError;
    }
    //for debug 
    //BYTE *test  = ezxml_toxml(ConfigNode);
    //printf("[%s,%d] write (%s) in file(%s), data:%s\n",__FUNCTION__,__LINE__, TagName, FileName, test);
    //for debug end
    
    USHORT ret = ECC_WriteXMLFILE2(FileName, ConfigNode, "EDC");
    ezxml_free(configfile);
}

USHORT Sysinfo2_GetEDCSystemMemoryStatus() {
    USHORT ret;
    ULONG ulUsedDiskSize, ulTotalDiskSize, ulUsedRamSize, ulTotalRamSize;
    ret = CTOS_SystemMemoryStatus(&ulUsedDiskSize, &ulTotalDiskSize, &ulUsedRamSize, &ulTotalRamSize);
    if (ret != d_OK)
        return ret;
    sprintf(gConfig.DEVICE.MEMORY.USEDDISKSIZE, "%ld", ulUsedDiskSize);
    sprintf(gConfig.DEVICE.MEMORY.TOTALDISKSIZE, "%ld", ulTotalDiskSize);
    sprintf(gConfig.DEVICE.MEMORY.USEDRAMSIZE, "%ld", ulUsedRamSize);
    sprintf(gConfig.DEVICE.MEMORY.TOTALRAMSIZE, "%ld", ulTotalRamSize);

    return ret;
}

USHORT Sysinfo2_InitConfigData() {

    printf("[%s,%d] Sysinfo2_InitConfigData start", __FUNCTION__, __LINE__);
    Sysinfo2_GetData();

    USHORT ret = ConfigFunction_GetData();

    Sysinfo2_GetEDCSystemMemoryStatus();

    GetEDCINFO();

    ret = GetHOSTINFO();

    ret = GetFTPINFO();

    ret = GetRS232Setting();

    int tmp = 0;
    tmp = atoi(gConfig.TX.SIGNONMAXTIME);
    gSignOnlimit = (tmp * 60 * 60 * 100);
    gDebugPrintFlag = atoi(gConfig.sDEBUG.PRINT.ENABLE);
    gDebugFTPFlag = atoi(gConfig.sDEBUG.FTP.ENABLE);
    gFORCEONLINELIMIT = atoi(gConfig.TX.FORCEONLINELIMIT);
    gBATCHTXLIMIT = 1000;
    gOFFLINETXLIMIT = atoi(gConfig.TX.OFFLINETXLIMIT);
    sprintf(gCAFile, "ck1.cer");

    // SSL load object 
    int Filesize;

    ret = Get_SSLCA();

    //    ret= Config_SetData();
    return ret;
}

void RemoveSysInfoFile() {
    remove(DEBUGINFO_Path);
    remove(MERCHANTINFO_Path);
    remove(TXINFO_Path);
    remove(DEVICEINFO_Path);
    remove(TMINFO_Path);
    remove(ETHERNETINFO_Path);
    remove(VERSIONINFO_Path);
}