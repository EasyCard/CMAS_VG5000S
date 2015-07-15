#include "ECCAPP.h"
 

void ecrInitial(void *p1) {
    
    printf("[%s,%d] ecrInitial start\n",__FUNCTION__,__LINE__);
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    memset(ecr, 0x00, sizeof (ECR_OBJ));

    /*initial RS232 obj*/
    rs232Initial(&ecr->rs232);

    /*initial USB obj*/
    usbInitial(&ecr->usb);

    /*ecr 共用的 function，如果依據不同的version(normal, hospital)的話，在setting interface在做不同function的assigan*/
    ecr->ecrRun = inEcrRun;
    ecr->isDataIn = inIsDataIn;
    ecr->settingInterface = inEcrSettingInterface;
    ecr->clear = inClear;
    ecr->tmsUpdate = inTmsUpdate;
    ecr->ecrConfigSave = inEcrConfigSave;
    ecr->posFld2EdcFld = inPosFld2EdcFld;
    ecr->autoExeSignOn = inAutoExeSignOn;
    ecr->gotErrorMessageString = inGotErrorMessageString;
}

int inEcrRun(void *p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    int result;
    BYTE temp[64];
    BYTE log[256];
    if (!ecr->ecrOn)
        return FALSE;

    //recv data from RS232 or USB
    switch (ecr->interface) {
        case RS232:
            if (ecr->rs232.openComport) {
                result = ecr->rs232.openComport(&(ecr->rs232));
                if (result != d_OK) {
                    sprintf(temp, "openComport(%d) fail(%d)", ecr->rs232.protocal.comport, result);
                    CTOS_PrinterPutString(temp);
                }
            } else
                return RS232_PARAM_ERROR;
            break;

        case USB:
            //todo...
            //CTOS_PrinterPutString("inEcrRun Type(USB)");
            if (ecr->usb.open) {
                result = ecr->usb.open(&ecr->usb);
                if (result != d_OK) {
                    sprintf(temp, "open USB port fail(%d)", result);
                    CTOS_PrinterPutString(temp);
                }
            } else
                return USB_PARAM_ERROR;
            break;
            
        default:
            result = d_Fail;
            snprintf(log,sizeof(log),"ECR interface wrong(%d)",ecr->interface);                
            SystemLog("inEcrRun",log);
            break;
    }
    return result;

}

int inIsDataIn(void* p1) {

    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    ECR_NON_GLOBAL_DATA ecrData;
    int result;
    int recvLen;
    BYTE *data;
    
    BYTE log[2048];


    result = COMM_ESCAPE;
    data = 0x00;
    recvLen = 0;

    if (!ecr->ecrOn)
        return COMM_ESCAPE;

    //recv data from RS232 or USB
    switch (ecr->interface) {
        case RS232:
            if ((result = ecr->rs232.recvData(&(ecr->rs232))) != d_OK)
            {
                if(result != COMM_ESCAPE)
                {
                    sprintf(log,"(%d) recvResult(%04X), IN(%s)",ecr->interface, result, ecr->rs232.recvMsg);
                    SystemLog("ECR_inIsDataIn",log);
                    inClear(ecr);
                }
                return result;           
            }
            break;

        case USB:
            if ((result = ecr->usb.recvData(&(ecr->usb))) != d_OK)
            {
                if(result != COMM_ESCAPE)
                {
                    sprintf(log,"(%d) recvResult(%04X), IN(%s)",ecr->interface, result, ecr->usb.recvMsg);
                    SystemLog("ECR_inIsDataIn",log);
                    inClear(ecr);
                }
                
                return result;
            }
            break;
    }

    memset(&ecrData, 0x00, sizeof (ECR_NON_GLOBAL_DATA));
    ecr->ngData = &ecrData;
    ecr->gData.isEcrTxn = TRUE;
    gIDLE=FALSE;

    printf("[%s,%d] parse data...\n",__FUNCTION__,__LINE__);
    // parase data    
    if ((result = ecr->paraseData(ecr)) != d_OK) {
      
        sprintf(log,"paraseData data Result(%04X)",result);
        SystemLog("ECR_inIsDataIn",log);
        ecr->gotErrorMessageString(ecr, result);
        ecr->errorResponse(ecr, result);

        inClear(ecr);
        return d_OK;
        //return result;
    }

    printf("[%s,%d] process TXN\n",__FUNCTION__,__LINE__);
    /*process Txn, call Bruce function*/
    result = ecr->processTxn(ecr, NULL);
    if (strlen(ecr->ngData->responseCode) == 0) {
        switch (result) {
            case d_ERR_RESP_REJECT:
                snprintf(ecr->ngData->responseCode,sizeof(ecr->ngData->responseCode), "00%s", gTransData.ucResponseCode);
                break;
            default:
                snprintf(ecr->ngData->responseCode,sizeof(ecr->ngData->responseCode), "%04X", result);
                break;
        }
    }
    sprintf(log,"Txn RespCode(%s)",ecr->ngData->responseCode);       
    SystemLog("ECR_inIsDataIn",log);
    printf("[%s,%d] Txn RespCode(%s)\n",__FUNCTION__,__LINE__, ecr->ngData->responseCode);
    
    
    // for sure errMsg existed
    if(memcmp(ecr->ngData->responseCode,"0000",4) !=0 && strlen(ecr->ngData->errMsg)==0)
        ecr->gotErrorMessageString(ecr, result);
    
    if(memcmp(ecr->ngData->responseCode,"0000",4)==0)
    {
        // response data
        result = ecr->successResponse(ecr);
        sprintf(log,"Response Result(%04X)",result);
        SystemLog("ECR_inIsDataIn",log);
    }
    else
    {
        // response error data
        result = ecr->errorResponse(ecr, result);
        sprintf(log,"Response Error Result(%04X)",result);
        SystemLog("ECR_inIsDataIn",log);
    }
    
    printf("[%s,%d] response finish\n",__FUNCTION__,__LINE__);
    if (result != d_OK && !ecr->ngData->response2Pos) {
        ecr->errorResponse(ecr, result);
        inClear(ecr);
        return d_OK;
    }

    
    inClear(ecr);
    
    sprintf(log,"inIsDataIn return Result(%04x)", result);
    SystemLog("ECR_inIsDataIn",log);
    
    printf("[%s,%d] Txn process finish\n",__FUNCTION__,__LINE__);
    return result;

}

int inEcrSettingInterface(void* p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;

    ezxml_t root;
    ezxml_t device;
    ezxml_t interface;
    ezxml_t version;
    ezxml_t bkRoot;
    ezxml_t versionTag;
    ezxml_t autoSignonTag;
    ezxml_t rs232Tag;
    
    
    const char *deviceName;
    const char *deviceInterface;
    const char *ecrVersion;
    const char *autoSignOnFlag;
    const char *temp;
    
    char nowEnable[8];    
    char nowEcrVersion[8];
    char nowEcrInterface[8];
    char nowAutoSignon[8];
    RS232_PROTOCOL nowRS232;
    
    int updateApFlag;
    BOOL oldConfigExist;
    BYTE versionNo;
    BYTE buffer[64];

    ULONG fileSize;
    BYTE *fileData;
    FILE *fPtr, *fBkPtr;

    bkRoot=NULL;
    root=NULL;
    updateApFlag=0;
    oldConfigExist=FALSE;
    root = ezxml_parse_file(AROUND_DEVICE_CONFIG);
    
    
    if(1)
    {
        bkRoot = ezxml_parse_file(AROUND_DEVICE_CONFIG_BK);
        if(bkRoot==NULL) return d_ERR_XMLError;
        temp = ezxml_attr(bkRoot, "updateAp");
        updateApFlag = atoi(temp);
        
        if(root==NULL) oldConfigExist=FALSE;
        else oldConfigExist=TRUE;
        

        //backup orig settings
        if(updateApFlag == 1 && oldConfigExist == TRUE)
        {
            for (device = ezxml_child(root, "DEVICE"); device; device = device->next) {
                deviceName = ezxml_attr(device, "name");
                if (memcmp(deviceName, "ECR", 3) == 0) {                    
                    temp = ezxml_attr(device, "version");//backup now setting
                    snprintf(nowEcrVersion,sizeof(nowEcrVersion), "%s",temp);
                    temp = ezxml_attr(device, "interface");//backup now setting
                    //20150128 modified overflow bug for V15 by kobe
                    snprintf(nowEcrInterface,sizeof(nowEcrInterface), "%s",temp);
                    //sprintf(nowEcrInterface, "%s",temp);
                    temp = ezxml_attr(device, "enable");//backup now setting                    
                    sprintf(nowEnable, "%s",temp);
                    
                    //20141106, backup rs232 setting and autoSignFlag
                    versionTag = ezxml_child(device, nowEcrVersion);
                    if(versionTag)
                    {
                        //autoSignFlag
                        autoSignonTag = ezxml_child(versionTag, "AUTO_SIGNON");
                        if(autoSignonTag)
                        {
                            //20150128 modified overflow bug for V15 by kobe
                            snprintf(nowAutoSignon,sizeof(nowAutoSignon), "%s", autoSignonTag->txt);
                            //sprintf(nowAutoSignon, "%s", autoSignonTag->txt);
                        }
                        else
                            SystemLog("ECR_inEcrSettingInterface","Backup RS232 Setting, got autoSignonTag error");
                            
                        //backup rs232 setting                        
                        rs232Tag = ezxml_child(versionTag, "RS232");
                        if(rs232Tag){
                            memset(&nowRS232, 0x00, sizeof(RS232_PROTOCOL));
                            
                            nowRS232.comport = atoi(ezxml_attr(rs232Tag, "comport"));
                            nowRS232.baudRate = atol(ezxml_attr(rs232Tag, "baud_rate"));
                            nowRS232.dataBits = atoi(ezxml_attr(rs232Tag, "bits"));
                            
                            
                            nowRS232.parity = *(ezxml_attr(rs232Tag, "parity")+0);
                            
                            nowRS232.stopBits = atoi(ezxml_attr(rs232Tag, "stopbit"));
                        }
                        else
                            SystemLog("ECR_inEcrSettingInterface","Backup RS232 Setting, got rs232Tag error");
                    }
                    else
                        SystemLog("ECR_inEcrSettingInterface","Backup RS232 Setting, got versionTag error");
                    
                    
                }
            }        
        }        
    }
    
    //舊的不存在 or Config要更新
    if (oldConfigExist == FALSE || updateApFlag==1) {
        
        if(root) {ezxml_free(root); root=NULL;}        
        remove(AROUND_DEVICE_CONFIG);

        // get BackupFile size
        if ((fBkPtr = fopen(AROUND_DEVICE_CONFIG_BK, "r")) == NULL) return d_ERR_FILE_NOTEXIST;
        fseek(fBkPtr, 0L, SEEK_END);
        fileSize = ftell(fBkPtr);
        if (fileSize <= 0) {
            fclose(fBkPtr);
            if(bkRoot) ezxml_free(bkRoot);
            if(root) ezxml_free(root);
            return d_ERR_FILE_NOTEXIST;
        }
        if ((fileData = calloc(fileSize, sizeof (BYTE))) == NULL) {
            fclose(fBkPtr);
            if(bkRoot) ezxml_free(bkRoot);
            if(root) ezxml_free(root);
            return COMM_MEMORY_FAIL;
        }
        fseek(fBkPtr, 0L, SEEK_SET);
        fread(fileData, fileSize, sizeof (BYTE), fBkPtr);
        fclose(fBkPtr);

        if ((fPtr = fopen(AROUND_DEVICE_CONFIG, "w+")) == NULL) {
            myFree((void**)&fileData);
            if(bkRoot) ezxml_free(bkRoot);
            if(root) ezxml_free(root);
            return d_ERR_FILE_NOTEXIST;
        }

        fwrite(fileData, sizeof (BYTE), fileSize, fPtr);
        myFree((void**)&fileData);
        fclose(fPtr);

        if ((root = ezxml_parse_file(AROUND_DEVICE_CONFIG)) == NULL)
        {
            if(bkRoot) ezxml_free(bkRoot);
            if(root) ezxml_free(root);
            return d_ERR_XMLError;
        }
        //if(updateApFlag==1 && oldConfigExist==TRUE)
        if(oldConfigExist==TRUE)//copy orig setting to new config 
        {        
            for (device = ezxml_child(root, "DEVICE"); device; device = device->next) {
                deviceName = ezxml_attr(device, "name");
                if (memcmp(deviceName, "ECR", 3) == 0) {   
                    ezxml_set_attr_d(device, "enable", nowEnable);
                    ezxml_set_attr_d(device, "interface", nowEcrInterface);
                    if(memcmp(nowEcrVersion,"V1",2)==0) sprintf(nowEcrVersion,"VER0");//當初沒考量好，所以強制把外面流通V1改成VER0(悠遊卡版)
                    ezxml_set_attr_d(device, "version", nowEcrVersion);  
                    
                    //20141106, reserve RS232 setting
                    versionTag = ezxml_child(device, nowEcrVersion);
                    if(versionTag)
                    {
                        //autoSignFlag
                        autoSignonTag = ezxml_child(versionTag, "AUTO_SIGNON");
                        if(autoSignonTag)
                        {                            
                            memcpy(autoSignonTag->txt, nowAutoSignon, 1);                        
                        }
                        else
                            SystemLog("ECR_inEcrSettingInterface","Backup RS232 Setting, got autoSignonTag error");
                            
                        //backup rs232 setting
                        rs232Tag = ezxml_child(versionTag, "RS232");                        
                        if(rs232Tag){                            
                            
                            sprintf(buffer, "%d", nowRS232.comport);
                            ezxml_set_attr_d(rs232Tag, "comport", buffer);
                            
                            sprintf(buffer, "%ld", nowRS232.baudRate);
                            ezxml_set_attr_d(rs232Tag, "baud_rate", buffer);
                            
                            sprintf(buffer, "%d", nowRS232.dataBits);
                            ezxml_set_attr_d(rs232Tag, "bits", buffer);
                            
                            sprintf(buffer, "%c", nowRS232.parity);
                            ezxml_set_attr_d(rs232Tag, "parity", buffer);
                            
                            sprintf(buffer, "%d", nowRS232.stopBits);
                            ezxml_set_attr_d(rs232Tag, "stopbit", buffer);                                                                                    
                        }
                        else
                            SystemLog("ECR_inEcrSettingInterface","Backup RS232 Setting, got rs232Tag error");
                    }
                    else
                      SystemLog("ECR_inEcrSettingInterface","Reserve RS232 Setting, got versionTag error");  
                    
                }
            }
            //save config
            ECC_WriteXMLFILE(AROUND_DEVICE_CONFIG, root);                       
        }
        
        if(updateApFlag==1){
            //save backup config
            ezxml_set_attr_d(bkRoot, "updateAp", "0");
            ECC_WriteXMLFILE(AROUND_DEVICE_CONFIG_BK, bkRoot);
            
            if(bkRoot) {ezxml_free(bkRoot);bkRoot=NULL;}//free memory
            
            CTOS_PrinterPutString("Upgrade Config Success");
        }
    }

    if(bkRoot) {ezxml_free(bkRoot);bkRoot=NULL;}//free memory
    
    //SendDebugFile(AROUND_DEVICE_CONFIG);
    for (device = ezxml_child(root, "DEVICE"); device; device = device->next) {
        deviceName = ezxml_attr(device, "name");

        if (memcmp(deviceName, "ECR", 3) == 0) {

            ecr->ecrOn = (BYTE) atoi(ezxml_attr(device, "enable"));
            /*ecr version: normal, hospital*/
            ecrVersion = ezxml_attr(device, "version");
            version = ezxml_child(device, ecrVersion);
            
            
            if (version == NULL) {
                sprintf(buffer, "error!! ECR version(%s) not support", ecrVersion);
                CTOS_PrinterPutString(buffer);
                if(root) ezxml_free(root);
                return ECR_VERSION_NOT_SUPPORT;
            }
            versionNo = atoi(ecrVersion+3);//skip VER chars
            
            switch(versionNo)
            {
                case 0://Normal            
                    ecr->rs232.dataCheckType = ECR_VER_NORMAL; //normal version
                    ecr->usb.dataCheckType = ECR_VER_NORMAL; //normal version
                    ecr->version = ECR_VER_NORMAL;
                    ecr->autoSignOn = atoi(ezxml_child(version, "AUTO_SIGNON")->txt);
                    //todo...
                    ecr->paraseData = inParaseData;
                    ecr->errorResponse = inErrorResponse;
                    ecr->processTxn = inProcessTxn;
                    ecr->successResponse = inResponseXml2Pos;
                    ecr->menuFunctionSwitch = inMenuFunctionSwitch;
                    break;
                    
                case 1://Hospital 雙北醫院 醫令系統
                    ecr->rs232.dataCheckType = ECR_VER_HOSPITAL; //hospital version
                    ecr->usb.dataCheckType = ECR_VER_HOSPITAL; //hospital version
                    ecr->version = ECR_VER_HOSPITAL;
                    autoSignOnFlag = ezxml_child(version, "AUTO_SIGNON")->txt;
                    ecr->autoSignOn = atoi(ezxml_child(version, "AUTO_SIGNON")->txt);
                    //todo...                    
                    ecr->paraseData = inHospitalParaseData;//different STD version
                    ecr->errorResponse = inHospitalErrorResponse;
                    ecr->processTxn = inHospitalProcessTxn;//different STD version
                    ecr->successResponse = inHospitalSuccessResponse;
                    ecr->menuFunctionSwitch = inHospitalMenuFunctionSwitch;
                    break;
                    
                default:
            
                    sprintf(buffer, "error!! ECR version(%s) not support", ecrVersion);
                    CTOS_PrinterPutString(buffer);
                    if(root) ezxml_free(root);
                    return ECR_VERSION_NOT_SUPPORT;
                    break;           
            }

            /*rsere interface*/
            deviceInterface = ezxml_attr(device, "interface");
            interface = ezxml_child(version, deviceInterface);


            if (interface == NULL) {
                sprintf(buffer, "error!! ECR Interface(%s) not support", deviceInterface);
                CTOS_PrinterPutString(buffer);
                if(root) ezxml_free(root);
                return ECR_INTERFACE_NOT_SUPPORT;
            }
            if (memcmp(deviceInterface, "RS232", 5) == 0) {
                //CTOS_PrinterPutString("ECR Interface(RS232)");
                ecr->interface = RS232;

                ecr->rs232.protocal.comport = ((BYTE) atoi(ezxml_attr(interface, "comport"))) - 1;
                ecr->rs232.protocal.baudRate = atol(ezxml_attr(interface, "baud_rate"));
                ecr->rs232.protocal.dataBits = atoi(ezxml_attr(interface, "bits"));
                ecr->rs232.protocal.stopBits = atoi(ezxml_attr(interface, "stopbit"));
                ecr->rs232.protocal.parity = *(ezxml_attr(interface, "parity") + 0);
            } else if (memcmp(deviceInterface, "USB", 3) == 0) {
                //todo...
                ecr->interface = USB;
            } else {
                sprintf(buffer, "error!! ECR Interface(%s) not support", deviceInterface);
                CTOS_PrinterPutString(buffer);

                //ecr->ecrOn=FALSE;//close it
                if(root) ezxml_free(root);
                return ECR_INTERFACE_NOT_SUPPORT;
            }
        }
    }
    if(device==NULL)
    {
        SystemLog("ECR_inEcrSettingInterface","get Device TAG was NULL");
    }
    
    //SendDebugFile(AROUND_DEVICE_CONFIG);
    if(root) ezxml_free(root);
    return d_OK;
}

int inParaseData(void* p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    ezxml_t root, tm, subTag;
    const char *s;
    BYTE temp[16];
    BYTE log[2048];
    BYTE *recvMsg;
    BOOL fIsEDCSetting=FALSE;
    int recvSize;
    int i;
    int *checkTag;
    int SIGN_ON[] = {100, 300, 1101, 1201, 1301, 5504, 5510, 5595, 0};
    int DEDUCT[] = {100,300, 400, 1101, 1201, 1301, 3701, 5504, 5510, 0};
    int VOID[] = {100,300, 1101, 1201, 1301, 3701, 5504, 5510, 0};
    int ADD_VALUE[] = {100,300, 400, 1101, 1201, 1301, 3701, 5504, 5510, 0};
    int REFUND[] = {100,300, 400, 1101, 1201, 1301, 3701, 5504, 5510, 0};
    int AUTOLOAD_ENABLE[] = {100,300, 1101, 1201, 1301, 3701, 5504, 5510, 0};
    int SETTLE[] = {100,300, 1101, 1201, 1301, 5504, 5510, 0};
    int TXN_QUERY[] = {100,300, 3701, 0};
    int STATUS_REPORT[] = {100, 300, 0};
    int QUERY_BALANCE[] = {100, 300, 0};
    int EDC_REMOTE_SETTING[] = {300, 9999, 0};
    TXN_MUST_FIELD_TABLE data[] = {
        {"881999", SIGN_ON},
        {"811599", DEDUCT},
        {"811899", VOID}, //addValue void
        {"823899", VOID}, //deduct void
        {"811799", ADD_VALUE}, //deduct void
        {"851999", REFUND}, //refund
        {"814799", AUTOLOAD_ENABLE}, //refund
        {"900000", SETTLE}, //settle        
        {"999999", TXN_QUERY}, //query txn
        {"950007", STATUS_REPORT},//status report
        {"200000", QUERY_BALANCE},//query balance, 20141113 kobe added it
        {"999998", EDC_REMOTE_SETTING},
        {0x00, 0x00},
    };

    /*---------------------------------------------------------------------*/

    if (!ecr->ecrOn)
        return FALSE;

    switch (ecr->interface) {
        case RS232:
            recvMsg = ecr->rs232.recvMsg;
            recvSize = ecr->rs232.recvSize;
            break;
        case USB:
            recvMsg = ecr->usb.recvMsg;
            recvSize = ecr->usb.recvSize;
            break;

        default:

            return ECR_INTERFACE_NOT_SUPPORT;
            break;
    }
    recvMsg[recvSize] = 0x00;
    //snprintf(log,sizeof(log),"(%d) IN(%s)",ecr->interface,recvMsg);
    //SystemLog("ECR_inParaseData",log);
    
    root = ezxml_parse_str((recvMsg + 1), recvSize - 2);

    if (root->name == NULL) {
        //sprintf(ecr->ngData->errMsg,"not found root tag");
        return ECR_DATA_INCOMPLETE;
    }
    if (memcmp(root->name, "TM", 2) != 0) {
        //sprintf(ecr->ngData->errMsg,"not found root tag");
        ezxml_free(root);
        return ECR_FORMAT_ERROR;
    }


    //got T0300(pCode) first
    subTag = ezxml_get(root, "TRANS", 0, "T0300", -1);
    if(subTag == NULL){    
        ezxml_free(root);
        return ECR_DATA_INCOMPLETE;
    }// no T0300

    
    //forced to exe assignation pcode
    if (ecr->gData.forcedTxnPCode != 0x00 && atoi(subTag->txt) != ecr->gData.forcedTxnPCode)
    {
        switch(ecr->gData.forcedTxnPCode)
        {                
            case 881999:
                return 0x6305;//請重試登入動作!!!
                break;
            default:        
                return ECR_TXN_TYPE_WRONG;
                break;
        }
    }
    for (i = 0;; i++) {
        if (data[i].processingCode == 0x00) {
            ezxml_free(root);
            return ECR_TXN_TYPE_NOT_SUPPORT;
        } // got nothing

        if (memcmp(data[i].processingCode, subTag->txt, strlen(subTag->txt)) == 0) {
            checkTag = data[i].tag;
            break;
        }
    }

    //for EDC Setting...
    if(memcmp(subTag->txt,"999998", 6) ==0) fIsEDCSetting = TRUE;
    
    /*got subTag value*/
    for (i = 0;; i++) {
        if (checkTag[i] == 0) break;
        sprintf(temp, "T%04d", checkTag[i]);
        subTag = ezxml_get(root, "TRANS", 0, temp, -1);
        if (subTag == NULL)            
        {
            if(fIsEDCSetting==TRUE) continue;
            snprintf(ecr->ngData->errMsg,sizeof(ecr->ngData->errMsg), "not found tag(%s)", temp);
            ezxml_free(root);
            return ECR_DATA_INCOMPLETE;
        }
        inUnPackPosXml(ecr, subTag);
    }
    ezxml_free(root);
    
    SystemLog("ECR_inParaseData","End");
    return d_OK;
}

int inResponseXml2Pos(void*p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    ezxml_t edc, errXml;
    BYTE temp[16];
    BYTE buffer[512];
    BYTE log[1024];
    BYTE *toPosXmlStr, *sendBuffer;
    int i;
    int len;
    int result;
    int *responseTag;
    int SIGN_ON[] = {1100, 1101, 1200, 1201, 1300, 1301, 3700, 3800, 3900, 4100, 4101, 4102, 4103, 4104, 4200, 4210, 5501, 5503, 5504, 5510, 5588, 0};
    int DEDUCT[] = {200, 211, 212, 213, 214, 400, 408, 409, 410, 1101, 1200, 1201, 1300, 1301, 1402, 3700, 3701, 3800, 3900, 4100, 4101, 4102, 4103, 4104, 4200, 4210, 4800, 4801, 4802, 4803, 4804, 4805, 5501, 5503, 0};
    int VOID[] = {200, 211, 212, 213, 214, 400, 408, 409, 410, 1101, 1200, 1201, 1300, 1301, 1402, 3700, 3701, 3800, 3900, 4100, 4101, 4102, 4103, 4104, 4200, 4210, 4800, 4801, 4802, 4803, 4804, 4805, 5501, 5503, 0};
    int ADD_VALUE[] = {200, 211, 212, 213, 214, 400, 408, 409, 410, 1101, 1200, 1201, 1300, 1301, 1402, 3700, 3701, 3800, 3900, 4100, 4101, 4102, 4103, 4104, 4200, 4210, 4800, 4801, 4802, 4803, 4804, 4805, 5501, 5503, 0};
    int REFUND[] = {200, 211, 212, 213, 214, 400, 408, 409, 410, 1101, 1200, 1201, 1300, 1301, 1402, 3700, 3701, 3800, 3900, 4100, 4101, 4102, 4103, 4104, 4200, 4210, 4800, 4801, 4802, 4803, 4804, 4805, 5501, 5503, 0};
    int SETTLE[] = {1100, 1101, 1200, 1201, 1300, 1301, 3700, 3800, 3900, 4100, 4101, 4102, 4103, 4104, 4200, 4210, 5501, 5503, 5504, 5591, 5592, 0};
    int TXN_QUERY[] = {200, 211, 212, 213, 214, 400, 408, 409, 410, 1101, 1200, 1201, 1300, 1301, 1402, 3700, 3701, 3800, 3900, 4100, 4101, 4102, 4103, 4104, 4200, 4210, 4800, 4801, 4802, 4803, 4804, 4805, 5501, 5503, 0};
    int STATUS_REPORT[] = {1100, 1200, 1300, 3700, 3900, 4100, 4200, 4210, 5501, 5503, 5588, 0};
    int QUERY_BALANCE[] = {200, 211, 212, 213, 214, 409, 410, 1402, 3900, 4802, 4803, 4804, 4805, 0};
    int EDC_REMOTE_SETTING[] = {3900, 0};
    
    
    TXN_MUST_FIELD_TABLE data[] = {
        {"881999", SIGN_ON},
        {"811599", DEDUCT},
        {"811899", VOID},
        {"823899", VOID},
        {"811799", ADD_VALUE},
        {"851999", REFUND},
        {"900000", SETTLE},
        {"999999", TXN_QUERY},
        {"950007", STATUS_REPORT},
        {"200000", QUERY_BALANCE},
        {"999998", EDC_REMOTE_SETTING},
        {0x00, 0x00},
    };

    
    if (!ecr->ecrOn)
        return d_OK;

    if (ecr->ngData->response2Pos)
        return d_OK;

    
    SystemLog("ECR_inResponseXml2Pos","Start");
    for (i = 0;; i++) {
        if (data[i].processingCode == 0x00) {
            return ECR_TXN_TYPE_NOT_SUPPORT;
        } // got nothing

        //if(memcmp(data[i].processingCode,gTransData.ucProcessCode,strlen(data[i].processingCode)) == 0){
        if (memcmp(data[i].processingCode, ecr->ngData->pCode, strlen(data[i].processingCode)) == 0) {
            responseTag = data[i].tag;
            break;
        }
    }

    //root(EDC tag)
    edc = ezxml_new_d("EDC");
    if (edc == NULL)
        return d_ERR_XMLError;

    //
    ezxml_t trans = ezxml_add_child_d(edc, "TRANS", 0);

    //assigned T0100 first
    i=atoi(ecr->ngData->messageType)+10;
    sprintf(temp,"%04d",i);
    ECC_ADDXMLNODE(trans,"T0100",NULL, temp);	
    
    //T0300
    snprintf(temp,sizeof(temp),"%s",ecr->ngData->pCode);
    ECC_ADDXMLNODE(trans,"T0300",NULL, temp);
    
    
    for (i = 0;; i++) {
        if (responseTag[i] == 0) break;
        if (responseTag[i] == 409 && gAutoloadAMT == 0) continue;//0409，只有autoload才需要回傳此欄位
        
        sprintf(temp, "T%04d", responseTag[i]);
        if (responseTag[i] == 410 && gAutoloadAMT > 0)
        {
             sprintf((char *)buffer, "%ld",gTransData.lEVBeforeTxn-gAutoloadAMT);            
             ECC_ADDXMLNODE(trans,temp,NULL,buffer);	
        }
        else
        {                              
            usFormatTransTag2(&gTransData, temp, NULL, trans);
        }
    }

    
    //errMsg    
    /*
    sprintf(ecr->ngData->errMsg,"12ab測試");
    len = strlen(ecr->ngData->errMsg);
    memset(printBuf,0x00,sizeof(printBuf));
    for(i=0;i<len;i++)
    {
        sprintf(temp,"[%02x]",ecr->ngData->errMsg[i]);
        strcat(printBuf, temp);
    }
    CTOS_PrinterPutString(printBuf);
    */
    if(memcmp(ecr->ngData->responseCode,"0000",4)!=0 && strlen(ecr->ngData->errMsg)>0)
    {
        errXml=ezxml_add_child_d(trans,"ErrMsg",0);    
        ezxml_set_txt_d(errXml,ecr->ngData->errMsg);
    }
    
    //tip message
     errXml=ezxml_add_child_d(trans,"TipMsg",0);            
     ezxml_set_txt_d(errXml,ecr->ngData->tipMsg);
    
    toPosXmlStr = ezxml_toxml(edc);
//    printf("[%s,%d] response XML:(%s)\n",__FUNCTION__,__LINE__,toPosXmlStr);
    len = strlen(toPosXmlStr);
    if ((sendBuffer = calloc(len + 3, sizeof (BYTE))) == NULL) {
        ezxml_free(edc);
        myFree((void**)&toPosXmlStr);
        return COMM_MEMORY_FAIL;
    }
    printf("[%s,%d] sendBuffer len(%d)\n",__FUNCTION__,__LINE__,len+3);
    snprintf(sendBuffer,(len+3), "%c%s%c", STX, toPosXmlStr, ETX);
    //sprintf(sendBuffer, "%c%s%c", STX, toPosXmlStr, ETX);

    //CTOS_PrinterPutString("ResponseXML is =>");    
    //CTOS_PrinterPutString(toPosXmlStr);


    //response to POS via RS232 or USB
    

    
    switch (ecr->interface) {
        case RS232:
            //ecr->rs232.waitACK = TRUE;
            result = ecr->rs232.sendData(&ecr->rs232, sendBuffer, strlen(sendBuffer));
            printf("[%s,%d] send ok[%04x]\n",__FUNCTION__,__LINE__,result);
            break;
        case USB:
            //ecr->usb.waitACK = TRUE;
            result = ecr->usb.sendData(&ecr->usb, sendBuffer, strlen(sendBuffer));
            break;

        default:

            break;
    }
    
    sprintf(log,"(%d) sendResult(%04X)",ecr->interface,result);    
    //SystemLog("ECR_inResponseXml2Pos",log);    
    SystemLog("ECR_inResponseXml2Pos",toPosXmlStr);
    
    
    ecr->ngData->response2Pos = TRUE;
    myFree((void**)&sendBuffer);
    myFree((void**)&toPosXmlStr);
    ezxml_free(edc);
    
    SystemLog("ECR_inResponseXml2Pos","End");
    
    printf("[%s,%d] ResponseXML2POS finish\n",__FUNCTION__,__LINE__);
    return d_OK;
}

int inErrorResponse(void*p1, int errorCode) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    BYTE errMsg[256];
    BYTE *sendBuffer;
    BYTE *toPosErrXml;
    BYTE log[2048];
    ezxml_t edc;
    int result;
    int len;

    sprintf(log,"Start errCode(%04x)",errorCode);
    SystemLog("ECR_inErrorResponse",log);
    edc = ezxml_new_d("EDC");
    if (edc == NULL) return d_ERR_XMLError;
         
    ezxml_t trans = ezxml_add_child_d(edc, "TRANS", 0);
    
    //error code
    sprintf(errMsg, "%X", errorCode);

    //T3900
    ezxml_t errXml = ezxml_add_child_d(trans, "T3900", 0);
    ezxml_set_txt_d(errXml, errMsg);

    
    //errmsg T9999
    errXml=ezxml_add_child_d(trans,"ErrMsg",0);   
    ezxml_set_txt_d(errXml,ecr->ngData->errMsg);
    
    toPosErrXml = ezxml_toxml(edc);

    len = strlen(toPosErrXml) +3 ;
    if ((sendBuffer = calloc(len, sizeof (BYTE))) == NULL)
    {
        myFree((void**)&toPosErrXml);
        ezxml_free(edc);
        return COMM_MEMORY_FAIL;
    }        
    
    snprintf(sendBuffer,len, "%c%s%c", STX, toPosErrXml, ETX);
    //sprintf(sendBuffer, "%c%s%c", STX, toPosErrXml, ETX);

    switch (ecr->interface) {
        case RS232:
            //ecr->rs232.waitACK = TRUE;
            result = ecr->rs232.sendData(&ecr->rs232, sendBuffer, strlen(sendBuffer));
            break;
        case USB:
            //ecr->usb.waitACK = TRUE;
            result = ecr->usb.sendData(&ecr->usb, sendBuffer, strlen(sendBuffer));
            break;
    }

    //snprintf(log,sizeof(log),"(%d) sendResult(%04X), errOut(%s)",ecr->interface, result, toPosErrXml);                    
    snprintf(log,sizeof(log),"(%d) errMsgSendResult(%04X))",ecr->interface, result);                    
    SystemLog("ECR_inErrorResponse",log);
    
    ecr->ngData->response2Pos = TRUE;

            
    myFree((void**)&toPosErrXml);        
    ezxml_free(edc);
    myFree((void**)&sendBuffer);
    
    SystemLog("ECR_inErrorResponse","End");
    return d_OK;
}

int inUnPackPosXml(void *p1, ezxml_t node) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    int iTag;
    char tagName[32];
    BYTE tmpstr[128], tmpstr1[128], tmpstr2[128];

    ezxml_t node2;


    memset(tmpstr, 0x00, sizeof (tmpstr));
    memset(tagName, 0x00, sizeof (tagName));
    memcpy(tagName, node->name, strlen(node->name));
    iTag = atoi(tagName + 1);



    switch (iTag) {
        case 100:
            usGetTagData(node,(char *)tmpstr); 
            memcpy(ecr->ngData->messageType, tmpstr, sizeof (ecr->ngData->messageType) - 1);
            //memcpy(gTransData.ucMessageType,tmpstr,sizeof(gTransData.ucMessageType));
            
            break;

        case 300:

            usGetTagData(node, (char *) tmpstr);
            memcpy(ecr->ngData->pCode, tmpstr, sizeof (ecr->ngData->pCode) - 1);

            //memcpy(ecr->ngData->pCode,gTransData.ucProcessCode,sizeof(ecr->ngData->pCode)); 
            break;

        case 400:
            usGetTagData(node, (char *) tmpstr);
            ecr->ngData->txnAmt = wub_str_2_long(tmpstr);
            break;


        case 1101:
            //20140320,kobe added for ECR
            usGetTagData(node, (char *) tmpstr);
            ecr->ngData->tmTxnSn = wub_str_2_long(tmpstr);
            //end
            break;

            //20140320, kobe added for ECR    
        case 1201:
            usGetTagData(node, tmpstr);
            memcpy(ecr->ngData->tmTxnTime, tmpstr, sizeof (ecr->ngData->tmTxnTime) - 1);
            break;
            //end

            //20140320, kobe added for ECR 
        case 1301:
            usGetTagData(node, tmpstr);
            memcpy(ecr->ngData->tmTxnDate, tmpstr, sizeof (ecr->ngData->tmTxnDate) - 1);
            break;
            //end

        case 3701:
            usGetTagData(node, (char *) tmpstr);
            memcpy(ecr->ngData->tmInvoiceNo, tmpstr, sizeof (ecr->ngData->tmInvoiceNo) - 1);

            break;

        case 4200:
            usGetTagData(node, (char *) tmpstr);
            memcpy(ecr->ngData->merchantId, tmpstr, ((sizeof (ecr->ngData->tmInvoiceNo) - 1) > strlen(tmpstr)) ? strlen(tmpstr) : (sizeof (ecr->ngData->tmInvoiceNo) - 1));


            break;

        case 5503:
            usGetTagData(node, (char *) tmpstr);
            ecr->ngData->tmLocationId = wub_str_2_long(tmpstr);
            break;
        case 5504:
            //20140320, kobe added for ECR
            usGetTagData(node, (char *) tmpstr);
            memcpy(ecr->ngData->tmId, tmpstr, sizeof (ecr->ngData->tmId) - 1);
            break;
            //end

        case 5510:
            //20140320, kobe added for ECR
            usGetTagData(node, (char *) tmpstr);
            memcpy(ecr->ngData->tmAgentNumber, tmpstr, sizeof (ecr->ngData->tmAgentNumber) - 1);
            //end			  
            break;

        case 5595:

            node2 = node;
            if ((node2 = ezxml_child(node2, "T559502")) == NULL)
                return ECR_DATA_INCOMPLETE;
            if (memcmp(node2->txt, "PWD", 3) != 0)
                return ECR_DATA_WRONG;

            node2 = node;
            if ((node2 = ezxml_child(node2, "T559503")) == NULL)
                return ECR_DATA_INCOMPLETE;
            
            //20150128 modified overflow bug for V15 by kobe
            snprintf(ecr->ngData->pwd, sizeof(ecr->ngData->pwd),"%s", node2->txt);
            //sprintf(ecr->ngData->pwd, "%s", node2->txt);
            break;

        case 9999://EDC Ethernet setting
                
            node2 = node;
            if ((node2 = ezxml_child(node, "T999901")) == NULL)
                return ECR_DATA_INCOMPLETE;
            
            ecr->ngData->edcSetting.ethernet.setIt = TRUE;
            if (memcmp(node2->txt, "1", 1) == 0){
                //dhcp on
                ecr->ngData->edcSetting.ethernet.dhcp = TRUE;
            } else {
                //static IP
                ecr->ngData->edcSetting.ethernet.dhcp = FALSE;
                //local ip
                if ((node2 = ezxml_child(node, "T999902")) != NULL){
                    snprintf(ecr->ngData->edcSetting.ethernet.ip, sizeof(ecr->ngData->edcSetting.ethernet.ip),node2->txt);
                }
                
                //gateway
                if ((node2 = ezxml_child(node, "T999903")) != NULL){
                    snprintf(ecr->ngData->edcSetting.ethernet.gateway, sizeof(ecr->ngData->edcSetting.ethernet.gateway),node2->txt);
                }
                
                //mask
                if ((node2 = ezxml_child(node, "T999904")) != NULL){
                    snprintf(ecr->ngData->edcSetting.ethernet.mask, sizeof(ecr->ngData->edcSetting.ethernet.mask),node2->txt);
                }
                
                //dns
                if ((node2 = ezxml_child(node, "T999905")) != NULL){
                    snprintf(ecr->ngData->edcSetting.ethernet.dns, sizeof(ecr->ngData->edcSetting.ethernet.dns),node2->txt);
                }
            }
            
            break;
        default:

            break;
    }

}

int inProcessTxn(void *p1, void *p2) {

    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    int pCode;
    int result;
    BYTE log[256];

    result = COMM_ESCAPE;
    pCode = atoi(ecr->ngData->pCode);

    sprintf(log,"Start pCode(%d)",pCode);
    SystemLog("ECR_inProcessTxn",log);
    
    //CTOS_PrinterPutString(log);
    switch (pCode) {
        case 881999://signOn     
            printf("[%s,%d]Function_Signon start\n",__FUNCTION__,__LINE__ );
            result = Function_Signon();
            printf("[%s,%d]Function_Signon finish\n",__FUNCTION__,__LINE__ );
            //if(result==d_OK)
            //{                  
            //    result = inEcrRun(ecr); //reRun ECR
            //}                
            break;
        case 811599://deduct                
            printf("[%s,%d]Trans_Deduct start\n",__FUNCTION__,__LINE__ );
            result = Trans_Deduct();
            printf("[%s,%d]Trans_Deduct finish\n",__FUNCTION__,__LINE__ );
            break;

        case 811899://addValue void
        case 823899://deduct void
            printf("[%s,%d]Trans_Cancel start\n",__FUNCTION__,__LINE__ );
            result = Trans_Cancel();
            printf("[%s,%d]Trans_Cancel finish\n",__FUNCTION__,__LINE__ );
            break;

        case 811799://add Value      
            printf("[%s,%d]Trans_ADD start\n",__FUNCTION__,__LINE__ );
            result = Trans_ADD();
            printf("[%s,%d]Trans_ADD finish\n",__FUNCTION__,__LINE__ );
            break;
        case 851999://refund
            printf("[%s,%d]Trans_Refund start\n",__FUNCTION__,__LINE__ );
            result = Trans_Refund();
            printf("[%s,%d]Trans_Refund finish\n",__FUNCTION__,__LINE__ );
            break;

        case 814799://autoLoad enable
            //todo...
            printf("[%s,%d]Trans_AutoloadEnable start\n",__FUNCTION__,__LINE__ );
            result = Trans_AutoloadEnable();
            printf("[%s,%d]Trans_AutoloadEnable finish\n",__FUNCTION__,__LINE__ );
            break;

        case 900000://settle
            printf("[%s,%d]Process_Settle start\n",__FUNCTION__,__LINE__ );
            result = Process_Settle();
            printf("[%s,%d]Process_Settle finish\n",__FUNCTION__,__LINE__ );
            break;

        case 999999:
            printf("[%s,%d]inEcrQueryRecord start\n",__FUNCTION__,__LINE__ );
            result = inEcrQueryRecord(ecr);
            printf("[%s,%d]inEcrQueryRecord finish\n",__FUNCTION__,__LINE__ );
            break;

        case 950007:
            printf("[%s,%d]inEdcStatusReport start\n",__FUNCTION__,__LINE__ );
            result = inEdcStatusReport(ecr);
            printf("[%s,%d]inEdcStatusReport finish\n",__FUNCTION__,__LINE__ );
            break;
        
        case 200000:   
            
            memcpy(gTransData.ucProcessCode, "200000", 6);
            if((result = ShowBalance())==d_OK)
                vdCardBasicData2TransData(ecr);
            break;
            
        case 999998://remote EDC Setting    
            result = remoteSettingEDC(ecr);
            break;
            
        default:
            result = ECR_TXN_TYPE_NOT_SUPPORT;
            break;
    }

    sprintf(log,"End Result(%04X)",result);
    SystemLog("ECR_inProcessTxn",log);
    return result;
}

int inPosFld2EdcFld(void*p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;

    memcpy(gTransData.ucProcessCode, ecr->ngData->pCode, sizeof (gTransData.ucProcessCode) - 1); //0300

    gTransData.lTxnAmt = ecr->ngData->txnAmt; //0400
    gTransData.ulTMTxnSN = ecr->ngData->tmTxnSn; //1101
    
    //單機版也需要填入的欄位
    if(strlen(ecr->ngData->tmTxnTime) != 0)
        memcpy(gTransData.ucTMTxnTime, ecr->ngData->tmTxnTime, sizeof (gTransData.ucTMTxnTime)); //1201 ok
    
    if(strlen(ecr->ngData->tmTxnDate) != 0)
        memcpy(gTransData.ucTMTxnData, ecr->ngData->tmTxnDate, sizeof (gTransData.ucTMTxnData)); //1301 ok        
    
    if(strlen(ecr->ngData->tmInvoiceNo) != 0)
        memcpy(gTransData.ucTMINVOICENO, ecr->ngData->tmInvoiceNo, sizeof (gTransData.ucTMINVOICENO)); //3701 ok
    
    if(strlen(ecr->ngData->tmId) != 0)
        memcpy(gTransData.ucTMPOSID, ecr->ngData->tmId, sizeof (gTransData.ucTMPOSID)); //5504 ok    
    
    if(strlen(ecr->ngData->tmAgentNumber) !=0 )
        memcpy(gTransData.ucTMAgentNumber, ecr->ngData->tmAgentNumber, sizeof (gTransData.ucTMAgentNumber)); //5510 ok
    //單機版也需要填入的欄位-end
}

int inClear(void*p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;

    printf("[%s,%d] inClear start\n",__FUNCTION__,__LINE__);
    SystemLog("ECR_inClear","Start");
    //clear 
    memset(&gTransData, 0x00, sizeof (TRANS_DATA2));

    //CTOS_Beep();
    CTOS_Sound(3500, 100);
    CTOS_Sound(4500, 10);
    if (ecr->rs232.recvMsg) {
        //free(ecr->rs232.recvMsg);
        //ecr->rs232.recvMsg = NULL;
        SystemLog("ECR_inClear","Clean RS232 Msg");
        myFree((void**)&ecr->rs232.recvMsg);
        CTOS_RS232FlushRxBuffer(ecr->rs232.protocal.comport); //clear buffer of received port
        CTOS_RS232FlushTxBuffer(ecr->rs232.protocal.comport); //clear buffer of sended port
    }

    if (ecr->usb.recvMsg) {
        //free(ecr->usb.recvMsg);
        //ecr->usb.recvMsg = NULL;
        SystemLog("ECR_inClear","Clean USB Msg");
        myFree((void**)&ecr->usb.recvMsg);
        CTOS_USBTxFlush();
        CTOS_USBRxFlush();
    }

    if (ecr->gData.tmsUpdateFld) {
        //free(ecr->gData.tmsUpdateFld);
        //ecr->gData.tmsUpdateFld = NULL;
        myFree((void**)&ecr->gData.tmsUpdateFld);
    }

    // gData or ngData must be clean at flow end
    memset(&ecr->gData, 0x00, sizeof (ECR_GLOBAL_DATA)); //clear global data
    ecrObj.ngData = NULL; //non global data will disapear, set to NULL

    SystemLog("ECR_inClear","End");
    
    printf("[%s,%d] inClear end\n",__FUNCTION__,__LINE__);
    return d_OK;
}

int inTmsBecomeEffective(void *p1, void *p2) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    BYTE temp[64];

    
    
    if (ecr->gData.tmsUpdateFld) {
        //ER01 Switch, close first
        if (ecr->ecrOn) {
            switch (ecr->interface) {
                case RS232:
                    ecr->rs232.closeComport(&ecr->rs232);
                    break;
                case USB:
                    ecr->usb.close(&ecr->usb);
                    break;
            }
        }
        if (memcmp(ecr->gData.tmsUpdateFld->ER01, "ON", 2) == 0x00) ecr->ecrOn = TRUE;
        else if (memcmp(ecr->gData.tmsUpdateFld->ER01, "OFF", 3) == 0x00) ecr->ecrOn = FALSE;
        else {
            snprintf(temp,sizeof(temp), "TMS ER01 was UnKnowen Parameter(%s)", ecr->gData.tmsUpdateFld->ER01);
            SystemLog("inTmsBecomeEffective",temp);
            //CTOS_PrinterPutString(temp);
            return ECR_TMS_PARAMETERS_WRONG;
        }

        //ER02
        if (memcmp(ecr->gData.tmsUpdateFld->ER02, "USB", 3) == 0x00) ecr->interface = USB;
        else if (memcmp(ecr->gData.tmsUpdateFld->ER02, "RS232", 5) == 0x00) ecr->interface = RS232;
        else {
            snprintf(temp,sizeof(temp), "TMS ER02 was UnKnowen Parameter(%s)", ecr->gData.tmsUpdateFld->ER02);
            SystemLog("inTmsBecomeEffective",temp);
            //CTOS_PrinterPutString(temp);
            return ECR_TMS_PARAMETERS_WRONG;
        }
        
        //ER03
        ecr->version = atoi(ecr->gData.tmsUpdateFld->ER03);
        
         //20141106, autoSignOn flag
        if(strlen(ecr->gData.tmsUpdateFld->ER04) >0)
        {
            ecr->autoSignOn = (BOOL)atoi(ecr->gData.tmsUpdateFld->ER04);
        }
        
        if(ecr->interface==RS232)
        {
            //20141106, ER05, rs232 settings
            if(strlen(ecr->gData.tmsUpdateFld->ER05) >0)
            {
                 char *delim="_";        
                 char *p;int i=0;        
                 p=strtok(ecr->gData.tmsUpdateFld->ER05, delim);

                 if(p!=NULL)//comport
                 {
                     ecr->rs232.protocal.comport = ((BYTE) atoi(p)) - 1;
                     p = strtok (NULL, delim);
                 }   

                 if(p!=NULL) //baudrate
                 {
                     ecr->rs232.protocal.baudRate = atol(p);
                     p = strtok (NULL, delim);
                 }

                 if(p!=NULL)//bits
                 {
                     ecr->rs232.protocal.dataBits = atoi(p);
                     p = strtok (NULL, delim);
                 }

                 if(p!=NULL)//parity
                 {
                     ecr->rs232.protocal.parity = p[0];
                     p = strtok (NULL, delim);
                 }

                 if(p!=NULL)//stopbit
                 {
                     ecr->rs232.protocal.stopBits = atoi(p);
                     p = strtok (NULL, delim);
                 }                          
            }
        }
        
    } else
        return COMM_MEMORY_FAIL; //if come to here, it's not normal flow.

    return d_OK;

}

int inTmsUpdate(void *p1, BYTE*tag, BYTE *value) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;

    if (memcmp(tag, "ER01", 4) == 0) {
        //20150128 modified overflow bug for V15 by kobe
        //sprintf(ecr->gData.tmsUpdateFld->ER01, "%s", value);
        snprintf(ecr->gData.tmsUpdateFld->ER01,sizeof(ecr->gData.tmsUpdateFld->ER01), "%s", value);
        
    } else if (memcmp(tag, "ER02", 4) == 0) {
        //20150128 modified overflow bug for V15 by kobe
        snprintf(ecr->gData.tmsUpdateFld->ER02,sizeof(ecr->gData.tmsUpdateFld->ER02), "%s", value);
        //sprintf(ecr->gData.tmsUpdateFld->ER02, "%s", value);
    } else if (memcmp(tag, "ER03", 4) == 0) {
        //20150128 modified overflow bug for V15 by kobe
        snprintf(ecr->gData.tmsUpdateFld->ER03,sizeof(ecr->gData.tmsUpdateFld->ER03), "%s", value);
        //sprintf(ecr->gData.tmsUpdateFld->ER03, "%s", value);
    } else if (memcmp(tag, "ER04", 4) == 0) {//20141106
        //20150128 modified overflow bug for V15 by kobe
        snprintf(ecr->gData.tmsUpdateFld->ER04,sizeof(ecr->gData.tmsUpdateFld->ER04),"%s", value);
        //sprintf(ecr->gData.tmsUpdateFld->ER04, "%s", value);
    } else if (memcmp(tag, "ER05", 4) == 0) {//20141106
        //20150128 modified overflow bug for V15 by kobe
        snprintf(ecr->gData.tmsUpdateFld->ER05,sizeof(ecr->gData.tmsUpdateFld->ER05),"%s", value);
        //sprintf(ecr->gData.tmsUpdateFld->ER05, "%s", value);
    }
    else {
        //doto...        
    }
    return d_OK;
}

int inEcrConfigSave(void*p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;    
    ezxml_t root = ezxml_parse_file(AROUND_DEVICE_CONFIG), deviceTag;     
    ezxml_t versionTag;
    ezxml_t autoSignTag;
    ezxml_t rs232Tag;
    const char *deviceName;
    const char *version;
    BYTE temp[256];
    BYTE log[1024];
    int result;
    


    if (ecr->gData.tmsUpdateFld)//if true ,measn config save from singOn, otherwise config Save from manual setting comport
        if ((result = inTmsBecomeEffective(ecr, NULL)) != d_OK)//move signon tms data to ecr object
            return result;


    for (deviceTag = ezxml_child(root, "DEVICE"); deviceTag; deviceTag = deviceTag->next) {
        deviceName = ezxml_attr(deviceTag, "name");

        if (memcmp(deviceName, "ECR", 3) == 0) {
            //device attr-enable 
            sprintf(temp, "%d", ecr->ecrOn);
            ezxml_set_attr_d(deviceTag, "enable", temp);
            sprintf(temp,"VER%d",ecr->version);
            ezxml_set_attr_d(deviceTag, "version", temp);
                                    
            if (ecr->interface == USB) sprintf(temp, "USB");
            else sprintf(temp, "RS232");
            ezxml_set_attr_d(deviceTag, "interface", temp);
    
            if(1){
            //20141106, save rs232 settings and autosignon flag
            version = ezxml_attr(deviceTag, "version");
            versionTag = ezxml_child(deviceTag, version);
            if(versionTag)
            {
                autoSignTag = ezxml_child(versionTag, "AUTO_SIGNON");
                if(!autoSignTag) SystemLog("ECR_inEcrConfigSave","get autoSignTag error");
                else if(ecr->gData.tmsUpdateFld)
                {
                    if(strlen(ecr->gData.tmsUpdateFld->ER04)>0)
                    {
                        sprintf(temp,"%d",ecr->autoSignOn);
                        memcpy(autoSignTag->txt, temp, 1);
                    }
                }              
                else{/*nothing to do*/}                                                       

                if (ecr->interface == RS232)
                {
                    rs232Tag = ezxml_child(versionTag, "RS232");            
                    if(!rs232Tag) SystemLog("ECR_inEcrConfigSave","get rs232Tag error"); 
                    else if(ecr->gData.tmsUpdateFld)
                    {
                        if(strlen(ecr->gData.tmsUpdateFld->ER05)>0)
                        {
                            //comport
                            sprintf(temp,"%d",ecr->rs232.protocal.comport+1);
                            ezxml_set_attr_d(rs232Tag, "comport", temp);

                            //baud_rate
                            sprintf(temp,"%ld",ecr->rs232.protocal.baudRate);
                            ezxml_set_attr_d(rs232Tag, "baud_rate", temp);

                            //bits
                            sprintf(temp,"%d",ecr->rs232.protocal.dataBits);
                            ezxml_set_attr_d(rs232Tag, "bits", temp);

                            //parity
                            sprintf(temp,"%c",ecr->rs232.protocal.parity);
                            ezxml_set_attr_d(rs232Tag, "parity", temp);

                            //stopbit
                            sprintf(temp,"%d",ecr->rs232.protocal.stopBits);
                            ezxml_set_attr_d(rs232Tag, "stopbit", temp);
                        }
                    }
                    else{/*nothing to do*/}    
                }
            }
            }
            
        }
    }
    //save config
    result = ECC_WriteXMLFILE(AROUND_DEVICE_CONFIG, root);
    
    ezxml_free(root);
    if (result != d_OK) {
        sprintf(temp, "!!! 錯誤 !!!，儲存收銀機檔案失敗(%d)", result);
        CTOS_PrinterPutString(temp);
        CTOS_PrinterFline(64);
        CTOS_PrinterFline(64);
        return result;
    }


    //setting interface
    if ((result = inEcrSettingInterface(ecr)) != d_OK) {
        //ecrObj.ecrOn=FALSE;        
        sprintf(temp, "!!! 錯誤 !!!，設定連線失敗，請重開機(%d)", result);
        CTOS_PrinterPutString(temp);
        CTOS_PrinterFline(64);
        CTOS_PrinterFline(64);
        //MessageBox("收銀機連線模式","","設定連線失敗","請重開機","",d_MB_CHECK);
        return result;
    }

    //reRun ECR
    if ((result = inEcrRun(ecr)) != d_OK) {
        //CTOS_Beep();
        //ecr->ecrOn=FALSE;
        sprintf(temp, "!錯誤!，重啟收銀機連線失敗，請重開機(%d)", result);
        CTOS_PrinterPutString(temp);
        CTOS_PrinterFline(64);
        CTOS_PrinterFline(64);
        //result=MessageBox("收銀機連線模式","","重啟收銀機連線失敗","請重開機","",d_MB_CHECK);
        return result;
    }



    return result;
}

int inEcrQueryRecord(void*p1) {

    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    ULONG offset;
    int iSize;

    int batchCnt = 0;
    int oneBatchSize;

    ULONG ulFileSize;
    
    /*查詢有沒有帳*/
    USHORT ret= GetBatchTotal();   
    USHORT TXCount=CheckBatchCount();
     if(TXCount==0){                 
         return ECR_TXN_NO_SUCCESS_BEFORE;
     }
    
    //TRANS_DATA2 transData;
    FILE *fp = fopen(TransDataFile, "r+");

    if (fp == NULL)
        return d_ERR_FILE_OPEN;

    fseek(fp, 0L, SEEK_END);
    ulFileSize = ftell(fp);

    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;

    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;
    batchCnt = ulFileSize / sizeof (TRANS_DATA2);


    oneBatchSize = sizeof (TRANS_DATA2);
    while ((--batchCnt) >= 0) {
        offset = oneBatchSize * (batchCnt);
        fseek(fp, offset, SEEK_SET);
        iSize = fread((BYTE *) & gTransData, sizeof (TRANS_DATA2), 1, fp);

        
        if (memcmp(ecr->ngData->tmInvoiceNo, gTransData.ucTMINVOICENO, sizeof (gTransData.ucTMINVOICENO)) == 0) {        
                break;
        }

    }
    fclose(fp);

    if (batchCnt < 0)
        return ECR_TXN_NO_SUCCESS_BEFORE;

    return d_OK;
}

USHORT usEcrModifyComportUi(void) {
    ECR_OBJ *ecr = (ECR_OBJ*) & ecrObj;
    char debugLog[64];
    int result;
    BYTE origMode;
    BYTE origSwitch;

    Optionmenu_item MenuItem[3] = {
        { "RS232", FALSE},
        { "USB", FALSE},
        { "OFF", FALSE}
    };
    
    

    origMode = ecrObj.interface;
    origSwitch = ecrObj.ecrOn;
    if (ecr->ecrOn) {
        switch (origMode) {
            case RS232:
                MenuItem[0].checked = TRUE;
                break;
            case USB:
                MenuItem[1].checked = TRUE;
                break;
            default:
                MenuItem[2].checked = TRUE;
                break;
        }
    } else
        MenuItem[2].checked = TRUE;

    
    result = ECC_ShowCheckListMeun2("收銀機連線模式", (Optionmenu_item *) & MenuItem, 3, TRUE, TRUE);
  
    ecr->ecrOn = TRUE;
    if (MenuItem[0].checked == TRUE)
        ecrObj.interface = RS232;
    else if (MenuItem[1].checked == TRUE)
        ecrObj.interface = USB;
    else ecr->ecrOn = FALSE;

    
    //sprintf(debugLog, "user select (%d) mode", ecrObj.interface);

    //no modified, no needed to save conifg
    if ((origSwitch == ecr->ecrOn && ecr->ecrOn == FALSE) || (origSwitch == ecr->ecrOn && origMode == ecrObj.interface))
        return d_OK;
    else if (origSwitch == TRUE && origMode == RS232)
        result = ecr->rs232.closeComport(&ecr->rs232); //close RS232 comport first
    else if (origSwitch == TRUE && origMode == USB)
        result = ecr->usb.close(&ecr->usb); //close USB comport first

    //save config
    if ((result = inEcrConfigSave(ecr)) != d_OK) {
        CTOS_Beep();
        CTOS_Beep();
        ecr->ecrOn = FALSE;        
        return result;
    }

    //SendDebugFile(AROUND_DEVICE_CONFIG);
    return result;
}

int inEdcStatusReport(void*p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) & ecrObj;

    usInitTxData(TXTYPE_REPORT);

    return d_OK;
}

USHORT usEcrExceptionTestUi(void)
{
    ECR_OBJ *ecr = (ECR_OBJ*) & ecrObj;
    int result;
    char testTitle[] = "ECR例外測試";
    
    if(!ecr->ecrOn)
    {
        ShowMessage2line(testTitle,"","收銀機連線目前關閉",Type_ComformAnykey);
        return d_OK;
    }
    
    Optionmenu_item TestItem[3] = {
        { "壓力測試", FALSE},
        { "回應NAK", FALSE},
        { "No ACK", FALSE},
    };
    
    Optionmenu_item forceTestItem[2] = {
        { "Production", FALSE},
        { "Forced Test", FALSE}
    };
    
    TestItem[0].checked=(ecr->ecrForcedTest)?TRUE:FALSE;
    TestItem[1].checked=(ecr->rs232.exceptionTestMode==EX_RESP_NAK)?TRUE:FALSE;
    TestItem[2].checked=(ecr->rs232.exceptionTestMode==EX_RESP_NO_ACK)?TRUE:FALSE;
    
    result = ECC_ShowCheckListMeun2(testTitle, (Optionmenu_item *) & TestItem, 3, TRUE, TRUE);
    ecr->ecrForcedTest = (TestItem[0].checked==TRUE)?TRUE:FALSE;
    ecr->rs232.exceptionTestMode = (TestItem[1].checked==TRUE)?EX_RESP_NAK:(TestItem[2].checked==TRUE)?EX_RESP_NO_ACK:EX_NORMAL;
    
    if(ecr->ecrForcedTest==EX_RESP_NO_ACK) 
        CTOS_PrinterPutString("Exception Test Mode(Resp NO ACK)");
    
}

/*=========================================================================*/
//Hospital version function

int inHospitalParaseData(void* p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    ezxml_t root, tm, subTag;
    const char *s;
    BYTE temp[16];
    BYTE log[2048];
    //BYTE printBuf[1024];
    BYTE *recvMsg;
    //ECR_VER1_HOSPITAL_DEFINED_FIELD *custDiffineField;
    int recvSize;
    int i;
    int len;


    if (!ecr->ecrOn)
        return FALSE;

    switch (ecr->interface) {
        case RS232:
            recvMsg = ecr->rs232.recvMsg;
            recvSize = ecr->rs232.recvSize;
            break;
        case USB:
            recvMsg = ecr->usb.recvMsg;
            recvSize = ecr->usb.recvSize;
            break;

        default:

            return ECR_INTERFACE_NOT_SUPPORT;
            break;
    }


    recvMsg[recvSize] = 0x00;
        
    sprintf(log,"(%d) IN(%s)",ecr->interface,recvMsg);
    SystemLog("ECR_inParaseData",log);
    /*
    //print recv hex data
    BYTE printBuf[2048];
    memset(printBuf,0x00, sizeof(printBuf));
    for(i=0;i<recvSize;i++)
    {
        sprintf(temp,"[%02x]",recvMsg[i]);
        strcat(printBuf, temp);
        if((i+1)%4==0)
            strcat(printBuf, "\n");
    }
    CTOS_PrinterPutString("recv data:");
    CTOS_PrinterPutString(printBuf);
    */
    //check LRC
    int calculateLrcSize = recvSize-2;//no include STX and LRC
    BYTE lrc = btCalculateLrc(recvMsg+1,&calculateLrcSize);
    
    // debug LRC
    //sprintf(printBuf,"calculate LRC[%02x]",lrc);
    //CTOS_PrinterPutString(printBuf);

    if (memcmp(recvMsg+1, "01", 2) == 0) {//扣款
                
        //if ((custDiffineField = calloc(1 , sizeof(ECR_VER1_HOSPITAL_DEFINED_FIELD))) == NULL)
        //        return COMM_MEMORY_FAIL;        
        //(ECR_VER1_HOSPITAL_DEFINED_FIELD*)ecr->ngData->customerDefineField = custDiffineField;        
                
        i = 1;//STX                
        i += 2; //Trans_Item
        memcpy(ecr->ngData->pCode, "811599", 6); //0300
        
        //Trans_Amount
        memcpy(temp, recvMsg + i, 6);
        temp[6] = 0x00;
        //sprintf(printBuf,"Trans_Amount[%s]",temp); 
        //CTOS_PrinterPutString(printBuf);
        char *amt = strtok(temp, " ");
        ecr->ngData->txnAmt = wub_str_2_long(amt);
        i += 6;
        
        //Trans_Dpt,(LocationId)
        //memcpy(temp, recvMsg + i, 4);
        //temp[4] = 0x00;
        //ecr->ngData->tmLocationId = wub_str_2_long(temp); //5503
        i += 4;
        //sprintf(printBuf,"LocationId[%s]\n",temp);
        //CTOS_PrinterPutString(printBuf);
        
        //Trans_Turn
        i+=1;//skip
        
        
        //Trans_Room(TM_ID)   
        //memcpy(temp, recvMsg + i, 2);
        //temp[2] = 0x00;
        
        i += 2;
        //sprintf(printBuf,"TM_ID[%s]",temp);        
        //CTOS_PrinterPutString(printBuf);
        
        //Trans_Ro_No
        i+=11;
        
        //Trans_Usr_Id (AgentNo)        
        memcpy(ecr->ngData->tmAgentNumber, recvMsg+i+1, sizeof (ecr->ngData->tmAgentNumber) - 1);//just only cop 4 digits, so +1
        i+=5;
        
        //Trans_Sys_Id
        i+=2;
        
        //Print_status
        if(memcmp(recvMsg + i,"0",1)==0)//0:no print; 1:print
            sprintf(ecr->ngData->doesNeedToPrintReceipt,"NO");
        
       
        //get current edc txn SN        
        usGetCurrTransSN((int*)&ecr->ngData->tmTxnSn);
            

    }else if(memcmp(recvMsg+1, "05", 2)==0) {//餘額查詢
        memcpy(ecr->ngData->pCode, "200000", 6); //0300
    
    }
    else if(memcmp(recvMsg+1, "09", 2)==0) {//查詢狀態
        //just only response <ACK><ACK>
        ecr->ngData->response2Pos=TRUE;
    }    
    else
        return ECR_TXN_TYPE_NOT_SUPPORT;
    
    
    return d_OK;
}

BYTE btCalculateLrc(void *p1, void *p2)
{
    BYTE *data = (BYTE*) p1;
    int dataSize = *(int*)p2;
    int i;
    BYTE lrc;
    
    lrc=0x00;
    for(i=0; i<dataSize; i++)
    {
       lrc=lrc^data[i]; 
    }
    return lrc;
}

int inHospitalProcessTxn(void *p1, void *p2) {

    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    int pCode;
    int result;

    result = COMM_ESCAPE;
    pCode = atoi(ecr->ngData->pCode);

    switch (pCode) {
        case 881999://signOn                
            result = Function_Signon();                            
            break;
        case 811599://deduct                
            result = Trans_Deduct();
            break;

        /*    
        case 811899://addValue void
        case 823899://deduct void
            result = Trans_Cancel();
            break;

        case 811799://add Value      
            result = Trans_ADD();
            break;
        case 851999://refund
            result = Trans_Refund();
            break;

        case 814799://autoLoad enable
            //todo...
            result = Trans_AutoloadEnable();
            break;
         */      
        /*
        case 900000://settle
            result = Process_Settle();
            break;

        case 999999:
            result = inEcrQueryRecord(ecr);
            break;

        case 950007:
            result = inEdcStatusReport(ecr);
            break;
        */
        case 200000:            
            result = ShowBalance();
            break;
        default:
            result = ECR_TXN_TYPE_NOT_SUPPORT;
            break;
    }

    return result;
}

int inHospitalSuccessResponse(void *p1) {
    
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    int pCode;
    int p;
    int i;
    int getDataOfLrcSize;
   
    BYTE *recvMsg;
    BYTE out[256];
    BYTE temp[16];
    BYTE temp2[32];
    BYTE CardID[17+1];
    //BYTE printBuf[1024];
    
    if (!ecr->ecrOn)
        return d_OK;

    if (ecr->ngData->response2Pos)
        return d_OK;

    recvMsg = ecr->rs232.recvMsg;
    pCode = atoi(ecr->ngData->pCode);
    
    memset(out, 0x00, sizeof(out));
    memset(CardID,0x00,sizeof(CardID));
    p=0;
    out[p]=0x02;p+=1;//STX
    switch(pCode)
    {
        case 811599://deduct 
            //Response_Code(1)
            if(memcmp(ecr->ngData->responseCode,"0000",4)==0){
                strcat(out+p,"0");//Response_Code
            }
            else{
                if(memcmp(ecr->ngData->responseCode,"6402",4)==0 ||
                        memcmp(ecr->ngData->responseCode,"640C",4)==0 ||
                        memcmp(ecr->ngData->responseCode,"640D",4)==0 ||
                        memcmp(ecr->ngData->responseCode,"FF5A",4)==0) //3 超過額度   
                        strcat(out+p,"3");//Response_Code                
                else if(memcmp(ecr->ngData->responseCode,"0051",4)==0 ||
                   memcmp(ecr->ngData->responseCode,"9984",4)==0 ||
                   memcmp(ecr->ngData->responseCode,"6403",4)==0) //4 金額不足
                        strcat(out+p,"4");
                else if(memcmp(ecr->ngData->responseCode,"6104",4)==0)
                        strcat(out+p,"6");// 6 卡片未開卡
                else if(memcmp(ecr->ngData->responseCode,"6201",4)==0)//7
                        strcat(out+p,"7");//7 找不到卡片                
                else if(memcmp(ecr->ngData->responseCode,"6204",4)==0)
                        strcat(out+p,"9");//9 找到多張卡片
                else
                    strcat(out+p,"1");//此卡不適用本系統
            }
            p+=1;
            //Error code(2)
            //strcat(out+p,"00");p+=2;

            //Trans_Item(2)
            memcpy(out+p, "01", 2);p+=2;
            
            //Remains(6)
            memset(temp2,0x20, sizeof(temp));
            sprintf(temp,"%ld",gTransData.lEVafterTxn);
            memcpy(temp2+(((6-strlen(temp))<0)?0:(6-strlen(temp))),temp, strlen(temp));
            sprintf(out+p,"%s",temp2);p+=6;//Remains
            
            //Device_Id(9)
            //memset(temp2, 0x00, sizeof(temp2));
            //fnBINTODEVASC((char *)&gTransData.ucCPUDeviceID,temp2,16,LEVEL2);
            memset(temp2, 0x30, sizeof(temp2));
            i=strlen(gConfig.DEVICE.READER.MIFARE_DEVICEID);
            i=(i>0 && i<=9)?i:9;
            sprintf(temp2+9-i, gConfig.DEVICE.READER.MIFARE_DEVICEID, i);
            memcpy(out+p, temp2, 9);
            p+=9;
            
            //LocationId put all zero(6)
            memcpy(out+p, "000000", 6);p+=6;
            
            //Trans_Batch_No(4)
            sprintf(out+p,"%04d",gBatchTotal.usBatchSN);p+=4;//Trans_Batch_No
            
            //Trans_serial_No(4)
            sprintf(temp,"%04ld",gTransData.usTXSN);
            sprintf(out+p,"%s",temp);p+=4;//Trans_serial_No
            
            //Trans_Date,Trans_Time(14)
            sprintf(out+p,"%s%s",gTransData.ucTxnData,gTransData.ucTxnTime);p+=14;//Trans_Date + Trans_Time
            
            //Trans_Amount(6)
            memset(temp2,0x20, sizeof(temp));
            sprintf(temp,"%ld",gTransData.lTxnAmt);
            memcpy(temp2+(((6-strlen(temp))<0)?0:(6-strlen(temp))),temp, strlen(temp));
            sprintf(out+p,"%s",temp2);p+=6;//Trans_Amount
            
            //CSC_Card_Type
            sprintf(out+p,"%d",gTransData.ucBasicData_CardProfile);
            p+=1;
            
            //CSC_Card_ID
            //vdUIntToAsc2(gTransData.ucCardID,sizeof(gTransData.ucCardID),CardID,10);//n_Card Physical ID
            vdUIntToAsc((BYTE *)gBasicData.ucCardID,sizeof(gBasicData.ucCardID),(BYTE *)&CardID,17,'0',10);
            i=strlen(CardID);            
            memcpy(out+p, CardID+i-10, 10);p+=10;
            
            //科別~系統別
            memcpy(out+p,recvMsg+1+8, 25);p+=25;
  
            /*
            switch(gTransData.ucBasicData_CardProfile)
            {
                case 0x01://普通
                    sprintf(out+p,"1");
                    break;
                case 0x02://敬老一    
                    sprintf(out+p,"2");
                    break;
                case 0x03://敬老二                
                    sprintf(out+p,"3");
                    break;  
                case 0x04://愛心      
                    sprintf(out+p,"4");
                    break;  
                case 0x05://愛陪    
                    sprintf(out+p,"5");
                    break;
                    
                case 0x06://學生
                case 0x07://軍人
                case 0x08://警察
                    sprintf(out+p,"2");
                    break;
                case 0x09://兒童                
                    sprintf(out+p,"3");
                    break;
                default:
                    sprintf(out+p," ");
                    break;
            }*/
            
            out[p] = 0x03;p+=1;//ETX
            
            getDataOfLrcSize =(p-1);//no include STX
            out[p] = btCalculateLrc(out+1, &getDataOfLrcSize);p+=1;
                                        
            break;
            
        case 200000:
            if(memcmp(ecr->ngData->responseCode,"0000",4)==0){
                strcat(out+p,"0");//Response_Code
            }
            else{
                if(memcmp(ecr->ngData->responseCode,"6402",4)==0 ||
                        memcmp(ecr->ngData->responseCode,"640C",4)==0 ||
                        memcmp(ecr->ngData->responseCode,"640D",4)==0 ||
                        memcmp(ecr->ngData->responseCode,"FF5A",4)==0) //3 超過額度   
                        strcat(out+p,"3");//Response_Code                
                else if(memcmp(ecr->ngData->responseCode,"0051",4)==0 ||
                   memcmp(ecr->ngData->responseCode,"9984",4)==0 ||
                   memcmp(ecr->ngData->responseCode,"6403",4)==0) //4 金額不足
                        strcat(out+p,"4");
                else if(memcmp(ecr->ngData->responseCode,"6104",4)==0)
                        strcat(out+p,"6");// 6 卡片未開卡
                else if(memcmp(ecr->ngData->responseCode,"6201",4)==0)//7
                        strcat(out+p,"7");//7 找不到卡片                
                else if(memcmp(ecr->ngData->responseCode,"6204",4)==0)
                        strcat(out+p,"9");//9 找到多張卡片
                else
                    strcat(out+p,"1");//此卡不適用本系統
            }
            p+=1;  
            
            //Error code(2)
            //sprintf(out+p,"00");p+=2;
            
            //Trans_Item
            sprintf(out+p,"05");p+=2;

            //Remains
            memset(temp2,0x20, sizeof(temp));
            sprintf(temp,"%ld",BYTE3Data2LONG((char *)gBasicData.ucEV));                            
            memcpy(temp2+(((6-strlen(temp))<0)?0:(6-strlen(temp))),temp, strlen(temp));
            sprintf(out+p,"%s",temp2);p+=6;//Remains
            
            //CSC_Card_ID
            vdUIntToAsc((BYTE *)gBasicData.ucCardID,sizeof(gBasicData.ucCardID),(BYTE *)&CardID,17,'0',10);
            i=strlen(CardID);            
            memcpy(out+p, CardID+i-10, 10);p+=10;
            
            out[p] = 0x03;p+=1;//ETX
            
            getDataOfLrcSize=(p-1);//no include STX
            out[p] = btCalculateLrc(out+1, &getDataOfLrcSize);p+=1;
            
            break;
    
    }
    /*
    //debug response
    memset(printBuf, 0x00, sizeof(printBuf));            
    for(i=0;i<p;i++)        
    {        
        sprintf(temp,"[%02x]",out[i]);                
        strcat(printBuf, temp);                
        if((i+1)%5==0)                        
            strcat(printBuf, "\n");            
    }            
    CTOS_PrinterPutString("send data:");                    
    CTOS_PrinterPutString(printBuf);
    
    CTOS_PrinterPutString("Hospital Success Response OK");
    */
    
    //response to POS via RS232 or USB
    switch (ecr->interface) {
        case RS232:
            //ecr->rs232.waitACK = TRUE;
            ecr->rs232.sendData(&ecr->rs232, out, p);
            break;
        case USB:
            //ecr->usb.waitACK = TRUE;
            ecr->usb.sendData(&ecr->usb, out, p);
            break;

        default:

            break;
    }
    ecr->ngData->response2Pos = TRUE;
    return d_OK;
}

int inHospitalErrorResponse(void *p1, int errorCode) {
    
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    int result;
    //CTOS_PrinterPutString("Hospital Error Response OK");
    
    //20150128 modified overflow bug for V15 by kobe
    snprintf(ecr->ngData->responseCode,sizeof(ecr->ngData->responseCode),"%04x",errorCode);
    //sprintf(ecr->ngData->responseCode,"%04x",errorCode);
    result = ecr->successResponse(ecr);
    
    
    return d_OK;
}

int inAutoExeSignOn(void*p1)
{
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    
    int result=-1;
    BYTE retryTimes=2;
    
    while((retryTimes--)>0 && result != d_OK)                       
    {      
        result = Function_Signon();        
    }           
    if (result != d_OK)
        CTOS_TimeOutSet(TIMER_ID_1, 100*60);//1分鐘後 retry
    
    
    return result;
}

int inGotErrorMessageString(void*p1, int errcode)
{
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    USHORT ret;
    char str[10],line1[64],line2[64],line3[64],line4[64], tagName[16];
    char *msgstr1,*msgstr2,*msgstr3;
    char errorCodeTag[16];
    BYTE log[256];
    
   if (ecr->ngData->response2Pos)
        return d_OK;
    
    sprintf(log, "Start errCode(%04X)", errcode);
    SystemLog("ECR_inGotErrorMessageString",log);
    
    memset(str,0x00,sizeof(str));
    memset(line1,0x00,sizeof(line1));
    memset(line2,0x00,sizeof(line2));
    memset(line3,0x00,sizeof(line3));
    
    
    
    
    sprintf(errorCodeTag,"CODE%04X",errcode);
    
    ezxml_t ResponseCode=LoadXMLFile(ResponseCodeFile);
    ezxml_t codeNode= ezxml_get(ResponseCode,"ECR", 0,errorCodeTag,-1);
    sprintf(tagName,"ECR");
    if(codeNode ==NULL){
        sprintf(tagName,"AP");
        codeNode= ezxml_get(ResponseCode,tagName, 0,errorCodeTag,-1);
        if(codeNode == NULL)
        {
            sprintf(tagName,"READER");
            codeNode= ezxml_get(ResponseCode,tagName, 0,errorCodeTag,-1);
            if(codeNode == NULL)
            {
                sprintf(tagName,"CMAS");
                codeNode= ezxml_get(ResponseCode,tagName, 0,errorCodeTag,-1);
                if(codeNode == NULL)
                {                        
                    //20150128 modified overflow bug for V15 by kobe
                    snprintf(ecr->ngData->errMsg,sizeof(ecr->ngData->errMsg),"未定義之錯誤代碼:%04X",errcode);
                    //sprintf(ecr->ngData->errMsg,"未定義之錯誤代碼:%04X",errcode);                        
                    ezxml_free(ResponseCode);            
                    return errcode;
                }
            }            
        }
    }
     
    ezxml_t ErrSTR1= ezxml_get(ResponseCode,tagName, 0,errorCodeTag,0,"STRING1",-1);
    if(ErrSTR1!=NULL){
        msgstr1=ezxml_txt(ErrSTR1);  
        //20150128 modified overflow bug for V15 by kobe
        snprintf(line1,sizeof(line1),"%s",msgstr1); 
        //sprintf(line1,"%s",msgstr1); 
    }
   ezxml_t ErrSTR2= ezxml_get(ResponseCode,tagName, 0,errorCodeTag,0,"STRING2",-1);
   if(ErrSTR2!=NULL){
        msgstr2=ezxml_txt(ErrSTR2); 
        //20150128 modified overflow bug for V15 by kobe
        snprintf(line2,sizeof(line2),"%s",msgstr2); 
        //sprintf(line2,"%s",msgstr2); 
   }
   ezxml_t ErrSTR3= ezxml_get(ResponseCode,tagName, 0,errorCodeTag,0,"STRING3",-1);
   if(ErrSTR3!=NULL){
        msgstr3=ezxml_txt(ErrSTR3); 
        //20150128 modified overflow bug for V15 by kobe
        snprintf(line3,sizeof(line3),"%s",  msgstr3); 
        //sprintf(line3,"%s",  msgstr3); 
   }
                 
   //20150128 modified overflow bug for V15 by kobe
   snprintf(line4,sizeof(line4),"錯誤代碼:%04X",errcode); 
   //sprintf(line4,"錯誤代碼:%04X",errcode);
    
   snprintf(ecrObj.ngData->errMsg,sizeof(ecrObj.ngData->errMsg),"%s!%s!%s!%s",line1,line2,line3,line4);
   /* 
   if((strlen(line1)+strlen(line2)+strlen(line3)+strlen(line4)+4)>=sizeof(ecrObj.ngData->errMsg))
        sprintf(ecrObj.ngData->errMsg,"%s",line4);
    else
        sprintf(ecrObj.ngData->errMsg,"%s!%s!%s!%s",line1,line2,line3,line4);    
   */
    ezxml_free(ResponseCode);  // ezxml_free(codeNode); 
    
    SystemLog("ECR_inGotErrorMessageString","End");
    return ret;
}

int inMenuFunctionSwitch(void *p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    int i;
    
    extern menu_item TMI[];            
    for(i=0;i<menufunc_count;i++){
           GetFunction((FUNCTION_STRUCT *)&TMI[i]);
           if(strcmp(TMI[i].TagName,"INFORMATION")==0)//display INFORMATION
               TMI[i].visible=TRUE;
           else
               TMI[i].visible=FALSE;
    }    
}


int inHospitalMenuFunctionSwitch(void *p1) {
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    int i;
    
    extern menu_item TMI[];            
    for(i=0;i<menufunc_count;i++){
           GetFunction((FUNCTION_STRUCT *)&TMI[i]);
           if(strcmp(TMI[i].TagName,"SETTLE")==0)
               TMI[i].visible=TRUE;
           else
               TMI[i].visible=FALSE;
    }    
}

void myFree(void **p)
{
    if(*p) free(*p);
    *p=NULL;
    return;
}

void vdCardBasicData2TransData(void*p1)
{
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    
    gTransData.ucCPUPurseVersionNUM=gBasicData.ucPurseVersionNumber;
    
    //1400
    //gTransData.ucCardExpiryDate = 
    
    //0200, card ID
    memcpy(gTransData.ucCardID, gBasicData.ucCardID, sizeof(gBasicData.ucCardID));
    
    //0211,PID(Purse ID)
    memcpy(gTransData.ucPID, gBasicData.ucPID, sizeof(gBasicData.ucPID));
    
    
    //0212
    gTransData.ucBasicData_Autoloadflag=(BYTE)gBasicData.bAutoLoad;
    //0213
    gTransData.ucBasicData_CardType = gBasicData.ucCardType;
    
    //0214, personal profile
    gTransData.ucBasicData_CardProfile = gBasicData.ucPersonalProfile;
    
    //0409
    gTransData.lAutoloadAMT= BYTE3Data2LONG((char *)gBasicData.ucAutoLoadAmt);
    
    //0410, berore txm balance
    gTransData.lEVBeforeTxn = BYTE3Data2LONG((char *)gBasicData.ucEV);
    
    //1400
    memcpy(gTransData.ucCardExpiryDate, gBasicData.ucExpiryDate,sizeof(gBasicData.ucExpiryDate));
    
    //1402
    memcpy(gTransData.ucCardVaildDate,gBasicData.ucProfileExpiryDate,sizeof(gBasicData.ucProfileExpiryDate));
    
    //4802
    gTransData.ucIssuerCode = gBasicData.ucIssuerCode;
    
    //4803,bankcode
    gTransData.ucBankCode=gBasicData.ucBankCode;
    
    //4804
    gTransData.ucAreaCode=gBasicData.ucAreaCode;
    
    //4805
    memcpy(gTransData.ucCPUSubAreaCode, gBasicData.ucSubAreaCode,sizeof(gBasicData.ucSubAreaCode));
    
              
    //4806
    memcpy(gTransData.ulProfileExpiryDate,gBasicData.ucExpiryDate,sizeof(gBasicData.ucExpiryDate));
    
}

USHORT setEthernet(void *p1){
    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    USHORT ret=d_OK;
    USHORT result=d_OK;
    BYTE temp[32];
    
    sprintf(temp,"%d", ecr->ngData->edcSetting.ethernet.dhcp);
    ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_DHCP, temp, 1);
    
    if(ecr->ngData->edcSetting.ethernet.dhcp){
        ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_DHCP, "1", 1);
    } else {
        ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_DHCP, "0", 1);
    
        //local ip
        if(strlen(ecr->ngData->edcSetting.ethernet.ip)!=0){        
             ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_IP, ecr->ngData->edcSetting.ethernet.ip, strlen(ecr->ngData->edcSetting.ethernet.ip));
             if(ret != d_OK) strcat(ecr->ngData->errMsg,"ip fail.");
             result |= ret;
        }
        //gateway
        if(strlen(ecr->ngData->edcSetting.ethernet.gateway)!=0){
             ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_GATEWAY, ecr->ngData->edcSetting.ethernet.gateway, strlen(ecr->ngData->edcSetting.ethernet.gateway));
             if(ret != d_OK) strcat(ecr->ngData->errMsg,"gw fail.");
             result |= ret;
        }
        //mask
        if(strlen(ecr->ngData->edcSetting.ethernet.mask)!=0){        
             ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_MASK, ecr->ngData->edcSetting.ethernet.mask, strlen(ecr->ngData->edcSetting.ethernet.mask));
            if(ret != d_OK) strcat(ecr->ngData->errMsg,"mask fail.");
             result |= ret; 
        }
        //dns
        if(strlen(ecr->ngData->edcSetting.ethernet.dns)!=0){
             ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_DNSIP, ecr->ngData->edcSetting.ethernet.dns, strlen(ecr->ngData->edcSetting.ethernet.dns));
             if(ret != d_OK) strcat(ecr->ngData->errMsg,"dns fail.");
             result |= ret;
        }
    }
    
    return result;
}

USHORT remoteSettingEDC(void *p1){

    ECR_OBJ *ecr = (ECR_OBJ*) p1;
    USHORT result=d_OK;
    
    if(ecr->ngData->edcSetting.ethernet.setIt){
        result = setEthernet(ecr);
    }

    
    return result;
}