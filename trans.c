#include "ECCAPP.h"
#include <signal.h>

USHORT CheckResponseCode(STR * TYPE, USHORT Respcode) {
    USHORT ret;
    SystemLog("CheckResponseCode", "Start");
    char str[10], line1[64], line2[64], line3[64], line4[64];
    const char *actionstr, *numstr;
    char *msgstr1, *msgstr2, *msgstr3;
    memset(str, 0x00, sizeof (str));
    memset(line1, 0x00, sizeof (line1));
    memset(line2, 0x00, sizeof (line2));
    memset(line3, 0x00, sizeof (line3));
    char tmp[10];
    memset(tmp, 0x00, sizeof (tmp));
    sprintf(tmp, "CODE%04x", Respcode);
    vdToUpper(str, tmp);

    ezxml_t ResponseCode = LoadXMLFile(ResponseCodeFile);
    ezxml_t codeNode = ezxml_get(ResponseCode, TYPE, 0, str, -1);
    if (codeNode == NULL) {
        SystemLog("CheckResponseCode", "XML Get RESPONSE CODE FAIL.");
        SystemLog("UNDEFINEDRESPOSECODE", str);

        sprintf(line4, "錯誤代碼:%s", str);
        ErrorMessageBox("錯誤訊息", "未定義之錯誤代碼", "", "", line4, d_MB_CHECK);
        //2014.04.28, kobe added it for POS to display errorMeg    
        if (ecrObj.gData.isEcrTxn) {
            if (strlen(ecrObj.ngData->errMsg) == 0)
                sprintf(ecrObj.ngData->errMsg, "未定義之錯誤代碼");
        }
        ezxml_free(ResponseCode);
        return d_FAIL;
    }
    /*   actionstr=ezxml_attr(codeNode, "action");
       if(strcmp(actionstr,"OK")==0)
       {    
           ezxml_free(ResponseCode); 
           return d_OK;
       }else if(strcmp(actionstr,"FAIL")==0){
           SystemLog("CheckResponseCode",str);
           ret=d_FAIL;
       }else{ 
            SystemLog("CheckResponseCode",str);
        
           ret=d_ERR_RESP_REJECT;
       }*/

    actionstr = ezxml_attr(codeNode, "action");
    if (strcmp(actionstr, "OK") == 0) {

        ezxml_free(ResponseCode);
        return d_OK;
    } else if (strcmp(actionstr, "LOCK") == 0) {
        SystemLog("CheckResponseCode", str);
        BYTE ucCardID[7];
        memset(ucCardID, 0x00, sizeof (ucCardID));
        gucLockReason = 0x03;
        memcpy(ucCardID, gTransData.ucCardID, 7);
        iProcess_LockCard(ucCardID);
        ret = d_ERR_RESP_LOCKCARD;
    } else if (strcmp(actionstr, "RETRY") == 0) {
        SystemLog("CheckResponseCode", str);
        //if(gTransData.ucTXTYPE==TXTYPE_SIGNON)
        //     return ret;
        // else
        ret = d_ERR_RESP_RETRY;
        //  return ret;
    } else if (strcmp(actionstr, "SVCS") == 0) {
        USHORT SVCSRspCode = atoi(gTransData.ucSVCSResponseCode);
        ret = CheckResponseCode("SVCS", SVCSRspCode);
        return ret;
    } else {
        SystemLog("CheckResponseCode", str);
        ret = d_ERR_RESP_REJECT;
    }



    ezxml_t ErrSTR1 = ezxml_get(ResponseCode, TYPE, 0, str, 0, "STRING1", -1);
    if (ErrSTR1 != NULL) {
        msgstr1 = ezxml_txt(ErrSTR1);
        sprintf(line1, "%s", msgstr1);
    }
    ezxml_t ErrSTR2 = ezxml_get(ResponseCode, TYPE, 0, str, 0, "STRING2", -1);
    if (ErrSTR2 != NULL) {
        msgstr2 = ezxml_txt(ErrSTR2);
        sprintf(line2, "%s", msgstr2);
    }
    ezxml_t ErrSTR3 = ezxml_get(ResponseCode, TYPE, 0, str, 0, "STRING3", -1);
    if (ErrSTR3 != NULL) {
        msgstr3 = ezxml_txt(ErrSTR3);
        sprintf(line3, "%s", msgstr3);
    }



    numstr = ezxml_attr(codeNode, "num");
    sprintf(line4, "錯誤代碼:%s", numstr);

    ErrorMessageBox("錯誤訊息", line1, line2, line3, line4, d_MB_CHECK);

    ezxml_free(ResponseCode);

    //2014.04.28, kobe added it for POS to display errorMeg                
    if (ecrObj.gData.isEcrTxn) {
        if (strlen(ecrObj.ngData->errMsg) == 0)
            sprintf(ecrObj.ngData->errMsg, "%s!%s!%s!%s", line1, line2, line3, line4);
    }
    return ret;
}

USHORT CheckSVCSResponseCode(STR * TYPE, BYTE *Respcode) {
    USHORT ret;
    SystemLog("CheckSVCSResponseCode", "Start");
    char str[10], line1[64], line2[64], line3[64], line4[64];
    const char *actionstr, *numstr;
    char *msgstr1, *msgstr2, *msgstr3;
    memset(str, 0x00, sizeof (str));
    memset(line1, 0x00, sizeof (line1));
    memset(line2, 0x00, sizeof (line2));
    memset(line3, 0x00, sizeof (line3));
    char tmp[10];
    memset(tmp, 0x00, sizeof (tmp));
    sprintf(tmp, "CODE00%s", Respcode);
    vdToUpper(str, tmp);

    ezxml_t ResponseCode = LoadXMLFile(ResponseCodeFile);
    ezxml_t codeNode = ezxml_get(ResponseCode, "SVCS", 0, str, -1);
    if (codeNode == NULL) {
        SystemLog("CheckSVCSResponseCode", "XML Get RESPONSE CODE FAIL.");
        SystemLog("UNDEFINEDRESPOSECODE", str);

        sprintf(line4, "錯誤代碼:%s", str);
        ErrorMessageBox("錯誤訊息", "未定義之錯誤代碼", "", "", line4, d_MB_CHECK);
        //2014.04.28, kobe added it for POS to display errorMeg    
        if (ecrObj.gData.isEcrTxn) {
            if (strlen(ecrObj.ngData->errMsg) == 0)
                sprintf(ecrObj.ngData->errMsg, "未定義之錯誤代碼");
        }
        ezxml_free(ResponseCode);
        return -1;
    }
    /*   actionstr=ezxml_attr(codeNode, "action");
       if(strcmp(actionstr,"OK")==0)
       {    
           ezxml_free(ResponseCode); 
           return d_OK;
       }else if(strcmp(actionstr,"FAIL")==0){
           SystemLog("CheckResponseCode",str);
           ret=d_FAIL;
       }else{ 
            SystemLog("CheckResponseCode",str);
        
           ret=d_ERR_RESP_REJECT;
       }*/

    actionstr = ezxml_attr(codeNode, "action");
    if (strcmp(actionstr, "OK") == 0) {
        ezxml_free(ResponseCode);
        return d_OK;
    } else if (strcmp(actionstr, "LOCK") == 0) {
        SystemLog("CheckSVCSResponseCode", str);
        BYTE ucCardID[7];
        memset(ucCardID, 0x00, sizeof (ucCardID));
        gucLockReason = 0x03;
        memcpy(ucCardID, gTransData.ucCardID, 7);
        iProcess_LockCard(ucCardID);
        ret = d_ERR_RESP_LOCKCARD;
    } else if (strcmp(actionstr, "RETRY") == 0) {
        SystemLog("CheckSVCSResponseCode", str);
        //if(gTransData.ucTXTYPE==TXTYPE_SIGNON)
        //     return ret;
        // else
        ret = d_ERR_RESP_RETRY;
        //  return ret;
    } else if (strcmp(actionstr, "SVCS") == 0) {
        USHORT SVCSRspCode = atoi(gTransData.ucSVCSResponseCode);
        ret = CheckResponseCode("SVCS", SVCSRspCode);
        return ret;
    } else {
        SystemLog("CheckSVCSResponseCode", str);
        ret = d_ERR_RESP_REJECT;
    }



    ezxml_t ErrSTR1 = ezxml_get(ResponseCode, "SVCS", 0, str, 0, "STRING1", -1);
    if (ErrSTR1 != NULL) {
        msgstr1 = ezxml_txt(ErrSTR1);
        sprintf(line1, "%s", msgstr1);
    }
    ezxml_t ErrSTR2 = ezxml_get(ResponseCode, "SVCS", 0, str, 0, "STRING2", -1);
    if (ErrSTR2 != NULL) {
        msgstr2 = ezxml_txt(ErrSTR2);
        sprintf(line2, "%s", msgstr2);
    }
    ezxml_t ErrSTR3 = ezxml_get(ResponseCode, "SVCS", 0, str, 0, "STRING3", -1);
    if (ErrSTR3 != NULL) {
        msgstr3 = ezxml_txt(ErrSTR3);
        sprintf(line3, "%s", msgstr3);
    }



    numstr = ezxml_attr(codeNode, "num");
    sprintf(line4, "錯誤代碼:%s", numstr);

    ErrorMessageBox("錯誤訊息", line1, line2, line3, line4, d_MB_CHECK);

    ezxml_free(ResponseCode);

    //2014.04.28, kobe added it for POS to display errorMeg                
    if (ecrObj.gData.isEcrTxn) {
        if (strlen(ecrObj.ngData->errMsg) == 0)
            sprintf(ecrObj.ngData->errMsg, "%s!%s!%s!%s", line1, line2, line3, line4);
    }
    return ret;
}

USHORT CheckCMASResponseCode(char * Respcode) {
    USHORT ret;
    char str[10], line1[64], line2[64], line3[64], line4[64];
    const char *actionstr, *numstr;
    char *msgstr1, *msgstr2, *msgstr3;
    SystemLog("CheckCMASResponseCode", "Start");
    memset(str, 0x00, sizeof (str));
    memset(line1, 0x00, sizeof (line1));
    memset(line2, 0x00, sizeof (line2));
    memset(line3, 0x00, sizeof (line3));
    USHORT rspcode = atoi(Respcode);
    char tmp[10];
    memset(tmp, 0x00, sizeof (tmp));
    sprintf(tmp, "CODE%02d", rspcode);
    vdToUpper(str, tmp);
    ezxml_t ResponseCode = LoadXMLFile(ResponseCodeFile);
    ezxml_t codeNode = ezxml_get(ResponseCode, "CMAS", 0, str, -1);
    if (codeNode == NULL) {
        SystemLog("CheckResponseCode", "XML Get RESPONSE CODE FAIL.");
        SystemLog("UNDEFINEDRESPOSECODE", str);

        sprintf(line4, "錯誤代碼:%s", str);
        ErrorMessageBox("錯誤訊息", "未定義之錯誤代碼", "", "", line4, d_MB_CHECK);
        ezxml_free(ResponseCode);

        //2014.04.28, kobe added it for POS to display errorMeg    
        if (ecrObj.gData.isEcrTxn) {
            if (strlen(ecrObj.ngData->errMsg) == 0)
                sprintf(ecrObj.ngData->errMsg, "未定義之錯誤代碼");
        }
        return rspcode;
    }
    /////若系統回應19 交易重覆 則自動將序號改為系統回覆的
    /*  if(strcmp(Respcode,"19")==0)
      {
               SetTransSN(gTransData.ulTerminalInvoiceNum);
            
      } */
    actionstr = ezxml_attr(codeNode, "action");
    if (strcmp(actionstr, "OK") == 0) {
        ezxml_free(ResponseCode);
        return d_OK;
    } else if (strcmp(actionstr, "LOCK") == 0) {
        SystemLog("CheckResponseCode", str);
        BYTE ucCardID[7];
        gucLockReason = 0x03;
        memset(ucCardID, 0x00, sizeof (ucCardID));
        memcpy(ucCardID, gTransData.ucCardID, 7);
        iProcess_LockCard(ucCardID);
        ret = d_ERR_RESP_LOCKCARD;
    } else if (strcmp(actionstr, "RETRY") == 0) {
        SystemLog("CheckResponseCode", str);
        //if(gTransData.ucTXTYPE==TXTYPE_SIGNON)
        //     return ret;
        // else
        ret = d_ERR_RESP_RETRY;
        //  return ret;
    } else if (strcmp(actionstr, "SVCS") == 0) {
        //USHORT SVCSRspCode=atoi(gTransData.ucSVCSResponseCode);        
        ret = CheckSVCSResponseCode("SVCS", gTransData.ucSVCSResponseCode);
        return ret;
    } else {
        SystemLog("CheckResponseCode", str);
        ret = d_ERR_RESP_REJECT;
    }

    ezxml_t ErrSTR1 = ezxml_get(ResponseCode, "CMAS", 0, str, 0, "STRING1", -1);
    if (ErrSTR1 != NULL) {
        msgstr1 = ezxml_txt(ErrSTR1);
        sprintf(line1, "%s", msgstr1);
    }
    ezxml_t ErrSTR2 = ezxml_get(ResponseCode, "CMAS", 0, str, 0, "STRING2", -1);
    if (ErrSTR2 != NULL) {
        msgstr2 = ezxml_txt(ErrSTR2);
        sprintf(line2, "%s", msgstr2);
    }
    ezxml_t ErrSTR3 = ezxml_get(ResponseCode, "CMAS", 0, str, 0, "STRING3", -1);
    if (ErrSTR3 != NULL) {
        msgstr3 = ezxml_txt(ErrSTR3);
        sprintf(line3, "%s", msgstr3);
    }



    numstr = ezxml_attr(codeNode, "num");
    sprintf(line4, "錯誤代碼:%s", numstr);

    ErrorMessageBox("錯誤訊息", line1, line2, line3, line4, d_MB_CHECK);
    // ezxml_free(ErrSTR3);   ezxml_free(ErrSTR2);   ezxml_free(ErrSTR3); 
    ezxml_free(ResponseCode); // ezxml_free(codeNode); 


    //2014.04.28, kobe added it for POS to display errorMeg                
    if (ecrObj.gData.isEcrTxn) {
        if (strlen(ecrObj.ngData->errMsg) == 0)
            sprintf(ecrObj.ngData->errMsg, "%s!%s!%s!%s", line1, line2, line3, line4);
    }
    return ret;
}

/*USHORT SaveTransData(ezxml_t trans)
{
    STR * xmlstr;
    int indatalen;
    BYTE MessageLength[2],len;

    USHORT    usRet= ECC_WriteXmlHeader("TransXML",SendFile);
        TransData.ucTXSTATUS=TransStatus_REQ;
        usRet= usBuildTXREQ(&TransData);
        usRet= ECC_WriteXmlEND("TransXML",SendFile);
			
	
    FILE *f = fopen(SendFile, "w+");
    if (f == NULL)   return d_Fail;
	
    xmlstr=ezxml_toxml(trans); 
  
    fseek(f,0,SEEK_SET);
    
    fwrite(xmlstr,strlen(xmlstr),1,f);
    
    fclose(f);
    return d_OK;
}*/

USHORT SaveReversalFile(TRANS_DATA2 *TransData) {
    TRANS_DATA2 ReversalData;
    remove(ReversalFile);
    memcpy(&ReversalData, TransData, sizeof (TRANS_DATA2));
    sprintf((BYTE *) & ReversalData.ucMessageType, "0400");
    USHORT usRet = ECC_WriteXmlHeader("TransXML", ReversalFile);
    usRet = usBuildTXREQ(&ReversalData, ReversalFile);
    usRet = ECC_WriteXmlEND("TransXML", ReversalFile);
    return usRet;
}

USHORT SaveTransData(TRANS_DATA2 *TransData) {
    remove(SendFile);
    if (gSaveReversalflag) {
        SaveReversalFile(TransData);
        gSaveReversalflag = 0;
    }
    if (TransData->ucTXTYPE == TXTYPE_SETTLEMENT && (File_exist(SettleFile) == d_OK)) {
        rename(SettleFile, SendFile);
        return d_OK;
    }

    USHORT usRet = ECC_WriteXmlHeader("TransXML", SendFile);
    usRet = usBuildTXREQ(TransData, SendFile);
    usRet = ECC_WriteXmlEND("TransXML", SendFile);

    if (TransData->ucTXTYPE == TXTYPE_SETTLEMENT) {
        int iret = copyFiles(SendFile, SettleFile);
    }


    return usRet;
}

USHORT Function_Signon() {
    BYTE buf[15 + 1];
    USHORT ret;
    BYTE Initflag = 0;
    void *threadResult;
    unsigned long ltmp;
    unsigned int itmp;
    memset(buf, 0x00, sizeof (buf));
    sprintf(gTransTitle, "系統登入");
    /* ret=Eth_SSLConnect_SOCKET(); 
      if(ret!=d_OK){
              MessageBox(gTransTitle,"","網路連線異常","請檢查並重試","",d_MB_CHECK);
              return ret;
      }*/

    //  ret=pthread_create(&Thread_Comm, NULL,(void*) SSLSocketConnect_thread, NULL);    // 執行緒 SSLSocketConnect 
    //ret=pthread_create(&Thread_Comm, NULL, &SSLSocketConnect_thread, NULL);    // 執行緒 SSLSocketConnect 

    printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
    /*kobe tested thread
     int result = pthread_join(thread_SendAdvice, &threadResult);
     if(result != 0){
         printf("[%s,%d] thread_SendAdvice join fail(%d)\n ",__FUNCTION__,__LINE__,result);
         //return d_NO;
     }
     printf("[%s,%d] join OK, return msg(%s)\n",__FUNCTION__,__LINE__,(char*)threadResult);
     //end*/
    BYTE baMsg[64];
    ret = SSLSocketConnect();
    printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
    if (ret != d_OK) {
        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
        /*    ret = CTOS_TCP_GPRSOpen("\x00\x00\x00\x00", APN, ID, PW);
              ret = GPRS_WaitIOProcess(ret);
              if (ret != d_OK) {
                  sprintf(baMsg, "%04X", ret);
                  MessageBox("通訊網路","通訊網路無法連線" ,"請重試..","",baMsg,d_MB_CHECK);
                  return ret;
              }*/
        Eth_Init();
        return ret;
    }

    //   CTOS_Delay(500);
    //ret=Config_GetData();
    // ret=Connect_CallCOMMThread();
    //  if(ret!=d_OK) return ret;
    //add by bruce 20140905 6608不允許再作交易
    if (gConfig.DEVICE.READER.bREADERSTATUS == READERSTATUS_LOCK) {
        MessageBox(gTransTitle, "讀卡機故障6608", "", "無法進行交易", "請報修!!", d_MB_CHECK);
        ret = 0x6608;
        goto DISCONNECT;
        //  return ret; 

    }

    if (gScrpitTesting == 1 || (ecrObj.ecrOn == TRUE && ecrObj.autoSignOn == TRUE)) {
        /*no needed to check PWD*/
    } else {
        //if(  gScrpitTesting!=1  && (ecrObj.ecrOn==TRUE && ecrObj.autoSignOn==FALSE)){
        ret = CheckSignOnPassword();
        if (ret != d_OK) {
            ECC_CheckAPResponseCode(ret);
            goto DISCONNECT;
            //  return ret; 
        }
    }
    printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
    //   CTOS_EthernetOpen();
    do {
        ret = Process_SignOn2(); //sign on 交易
        if (ret == d_OK) {
            SetRTC((BYTE *) & gTxnData, (BYTE *) & gTxnTime);
            MechineStatus &= (~(Status_SignOnFail));
            ECC_CheckAPResponseCode(ret);
            //2014.04.07, kobe modified for ECR 
            //ret=UnpackTMSParameter();


            ret = Process_DownloadTMS(); //2014.07.30, V11fixed bug for Updated AP
            ret = UnpackTMSParameter(); //2014.07.30, V11fixed bug for Updated AP
            CheckNewVersionAP(); //shit! bruceLin marked it, fxxk...

            //     Process_DownloadTMS();
            //CheckNewVersionFile();//2014.07.30, V11 fixed bug for Updated AP
            //     CheckNewVersionAP();//2014.07.30, V11 fixed bug for Updated AP
            break;
        } else {
            MechineStatus |= Status_SignOnFail;
        }
    } while (ret == d_ERR_RESP_RETRY);

    printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
    //2014.08.06, kobe fixed SIGNONMAXTIME must work
    CTOS_TimeOutSet(TIMER_ID_1, gSignOnlimit);
DISCONNECT:
    //   Eth_SSLSocketDisConnect();       
    SSLSocketDisConnect();
    printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
    return ret;
}

USHORT Function_Signon_forMaintenance() {
    BYTE buf[15 + 1];
    USHORT ret;
    //BYTE keyinflag=0;
    unsigned long ltmp;
    unsigned int itmp;
    memset(buf, 0x00, sizeof (buf));
    /*   ret=Eth_SSLConnect_SOCKET(); 
      if(ret!=d_OK){
              MessageBox(gTransTitle,"","網路連線異常","請檢查並重試","",d_MB_CHECK);
              return ret;
      }*/
    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
    ret = SSLSocketConnect();
    if (ret != d_OK) {
        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
        return ret;
    }

    //    ret=pthread_create(&Thread_Comm, NULL,(void*)SSLSocketConnect_thread, NULL);    // 執行緒 SSLSocketConnect 
    /*   ret=ShowMessage3line("TMS","","是否列印參數","",Type_Comform0);
       if(ret==d_OK){
                 PrintParameter();
       }*/
    int TotalCount = CheckUnuploadTxCount();
    if (TotalCount != 0) {
        ret = ShowMessage2line(gTransTitle, "尚有交易未上傳", "請先結帳!!", Type_ComformOK);
        CTOS_Delay(2000); //for ECR version, delay 2sec for Maintenance Engineer
        ret = d_OK;
        goto DISCONNECT;
    }
    ret = ShowInputBox(gTransTitle, "請輸入特店代號", buf, 15, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        //  SetConfigTag("MERCHANT","MERCHANTID", buf);
        sprintf(gConfig.MERCHANT.MERCHANTID, "%s", buf);
        ECC_SetXMLTag(MERCHANTINFO_Path, "MERCHANT", "MERCHANTID", gConfig.MERCHANT.MERCHANTID);

    }

    /*     
         memset(buf,0x00,sizeof(buf));
         ShowInputBox(gTransTitle,"請輸入分公司代號",buf ,8,INPUT_TYPE_Number,0);
         if(ret==d_OK){

               //SetConfigTag("MERCHANT","NewLocationID", buf);
               sprintf(gConfig.MERCHANT.NewLocationID,"%s",buf);
         }
     */
    memset(buf, 0x00, sizeof (buf));
    ShowInputBox(gTransTitle, "請輸入分店代號", buf, 15, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        //  SetConfigTag("MERCHANT","STCODE", buf);
        sprintf(gConfig.MERCHANT.STCODE, "%s", buf);
        ECC_SetXMLTag(MERCHANTINFO_Path, "MERCHANT", "STCODE", gConfig.MERCHANT.STCODE);
    }


    // SetMERCHANTInfo(); 
    // ret= Config_SetData();  
    //  ret=SetMERCHANTInfo();
    // CTOS_EthernetOpen();
    do {
        ret = Process_SignOn2(); //sign on 交易
        if (ret == d_OK) {
            SetRTC((BYTE *) & gTxnData, (BYTE *) & gTxnTime);
            MechineStatus &= (~(Status_SignOnFail));
            ECC_CheckAPResponseCode(ret);
            
            ret = Process_DownloadTMS(); //2014.07.30, V11fixed bug for Updated AP
            ret = UnpackTMSParameter(); //2014.07.30, V11fixed bug for Updated AP            
            CheckNewVersionAP();
            //           CheckNewVersionFile();
            break;
        } else {
            MechineStatus |= Status_SignOnFail;
        }
    } while (ret == d_ERR_RESP_RETRY);
    //  ret= SSLSocketDisConnect();

    //2014.08.06, kobe fixed SIGNONMAXTIME must work
    CTOS_TimeOutSet(TIMER_ID_1, gSignOnlimit);

DISCONNECT:
    //  Eth_SSLSocketDisConnect();       
    SSLSocketDisConnect();
    return ret;
}

USHORT ShowBalance() {
    long ev;
    USHORT usRet;
    BYTE EVSTR[17 + 1], cardID[17 + 1]; //2014.06.25, kobe changed EVSTR size from 6 to 17

    sprintf(gTransTitle, "餘額查詢");
    gucLCDControlFlag = 0;
    ShowMessage2line(gTransTitle, "請將悠遊卡", "放上讀卡機", Type_ComformNONE);
    int iret = iProcess_ReadCardBasicData();
    if (iret) usRet = ECC_CheckReaderResponseCode(iret);
    if (usRet != d_OK) return usRet;
    memset(cardID, 0x00, sizeof (cardID));
    vdUIntToAsc((BYTE *) gBasicData.ucCardID, sizeof (gBasicData.ucCardID), (BYTE *) & cardID, 17, ' ', 10);
    ev = BYTE3Data2LONG((char *) gBasicData.ucEV);
    sprintf(EVSTR, "%17ld", ev);

    //2014.06.25, kobe added it for Hospital ECR Version
    /*
    if(ecrObj.gData.isEcrTxn)     
    {     
         //if process come to "print receipt" means that txn was success 
         sprintf(ecrObj.ngData->responseCode,"0000");
         if((result = ecrObj.successResponse(&ecrObj)) != d_OK && !ecrObj.ngData->response2Pos)
        {
            ecrObj.errorResponse(&ecrObj, result);            
        }     
    }
    else//20141112, kobe added it, ecr txn no needed to show balance, for NewTaipeiCity Hospital    
     */
    if (!ecrObj.gData.isEcrTxn)
        ShowMessage4line(gTransTitle, "卡片晶片碼", cardID, "可用餘額", EVSTR, Type_RemoveCard);

    return d_OK;
}

USHORT ShowTXBalance(int amt) {
    long ev;

    STR line1[32], line2[32];
    memset(line1, 0x00, sizeof (line1));
    memset(line2, 0x00, sizeof (line2));



    USHORT usRet;
    gucLCDControlFlag = 1;
    int iret = iProcess_ReadCardBasicData();
    if (iret) usRet = ECC_CheckReaderResponseCode(iret);
    if (usRet != d_OK) return usRet;

    // vdUIntToAsc((BYTE *)gBasicData.ucCardID,sizeof(gBasicData.ucCardID),(BYTE *)&cardID,17,' ',10);
    if (gScrpitTesting == 1) return d_OK;
    //2014-04-01, kobe added for ECR
    if (ecrObj.gData.isEcrTxn) return d_OK;

    ev = BYTE3Data2LONG((char *) gBasicData.ucEV);

    sprintf(line1, "可用餘額  %ld", ev);
    sprintf(line2, "交易金額  %d", amt);
    USHORT ret = ShowMessage2line(gTransTitle, line1, line2, Type_Comform0);
    if (ret != d_OK) {
        MessageBox(gTransTitle, "", "使用者中斷交易", "", "", d_MB_CHECK);
        return d_ERR_USERCANCEL;
    }

    return ret;
}

USHORT InputAMT(int TxType, USHORT *amt) {
    long ev;
    int inputamt;
    BYTE cardID[17 + 1];
    BYTE Buffer[5 + 1];
    STR line1[32], line2[32];
    memset(line1, 0x00, sizeof (line1));
    memset(line2, 0x00, sizeof (line2));
    USHORT usRet;
    gucLCDControlFlag = 1;
    int iret;
    USHORT Miniunit;
    BYTE tmpstr[64];
    gCardRemainEV = 0;
    memset(Buffer, 0x00, sizeof (Buffer));
    do {
        sprintf(line1, " ");
        sprintf(line2, "交易金額:");
        usRet = ShowInputBox2(gTransTitle, line1, line2, Buffer, 5, 0, 0);
        if (usRet != d_OK) {
            return d_ERR_USERCANCEL;
        }
        inputamt = atoi(Buffer);
        if (inputamt > 10000) {
            MessageBox(gTransTitle, "", "交易金額不得超過一萬", "請重新輸入", "", d_MB_CHECK);
            continue;
        }


        if (TxType == TXTYPE_REFUND) {
            if (inputamt == 0) {
                MessageBox(gTransTitle, "", "交易金額不得為零元", "請重新輸入", "", d_MB_CHECK);
                continue;
            }
        } else if (TxType == TXTYPE_ADD) {
            Miniunit = atoi(gConfig.TX.MiniunitsADDVALUE);
            if (inputamt % Miniunit != 0) {
                sprintf(tmpstr, "加值金額需為%d元倍數", Miniunit);
                usRet = MessageBox(gTransTitle, tmpstr, "請重新輸入金額", "", "", d_MB_CHECK);
                continue;
            } else if (inputamt > 10000) {
                sprintf(tmpstr, "加值金額不得超過一萬");
                usRet = MessageBox(gTransTitle, tmpstr, "請重新輸入金額", "", "", d_MB_CHECK);
                continue;
            } else if (inputamt == 0) {
                sprintf(tmpstr, "加值金額不得為零元");
                usRet = MessageBox(gTransTitle, tmpstr, "請重新輸入金額", "", "", d_MB_CHECK);
                continue;
            }
        }
        break;
    } while (1);

    *amt = inputamt;
    if (gScrpitTesting == 1) return d_OK;
    return d_OK;

}

USHORT ShowBalanceAndInputAmt(int TxType, USHORT *amt) {
    long ev;
    int inputamt;
    BYTE cardID[17 + 1];
    BYTE Buffer[5 + 1];
    STR line1[32], line2[32];
    memset(line1, 0x00, sizeof (line1));
    memset(line2, 0x00, sizeof (line2));


    USHORT usRet;
    gucLCDControlFlag = 1;
    //  


    int iret;
    USHORT Miniunit;
    BYTE tmpstr[64];
    gCardRemainEV = 0;
    memset(Buffer, 0x00, sizeof (Buffer));
    do {
        /* ShowMessage2line(gTransTitle,"請將悠遊卡","放上讀卡機",Type_ComformNONE);  
         iret = iProcess_ReadCardBasicData( );
         if(iret)   usRet=ECC_CheckReaderResponseCode(iret);
         if(usRet!=d_OK) return usRet;*/
        usRet = iProcessWaitCard();
        if (usRet != d_OK) {
            return usRet;
        }
        ev = BYTE3Data2LONG((char *) gBasicData.ucEV);
        sprintf(line1, "可用餘額  %ld", ev);
        sprintf(line2, "交易金額:");

        usRet = ShowInputBox2(gTransTitle, line1, line2, Buffer, 5, 0, 0);

        if (usRet != d_OK) {
            return d_ERR_USERCANCEL;
        }
        inputamt = atoi(Buffer);

        if (inputamt > 10000) {
            MessageBox(gTransTitle, "", "交易金額不得超過一萬", "請重新輸入", "", d_MB_CHECK);
            continue;
        }


        if (TxType == TXTYPE_REFUND) {
            if (inputamt == 0) {
                MessageBox(gTransTitle, "", "交易金額不得為零元", "請重新輸入", "", d_MB_CHECK);
                continue;
            }
        } else if (TxType == TXTYPE_ADD) {
            Miniunit = atoi(gConfig.TX.MiniunitsADDVALUE);
            if (inputamt % Miniunit != 0) {
                sprintf(tmpstr, "加值金額需為%d元倍數", Miniunit);
                usRet = MessageBox(gTransTitle, tmpstr, "請重新輸入金額", "", "", d_MB_CHECK);
                continue;
            } else if (inputamt > 10000) {
                sprintf(tmpstr, "加值金額不得超過一萬");
                usRet = MessageBox(gTransTitle, tmpstr, "請重新輸入金額", "", "", d_MB_CHECK);
                continue;
            } else if (inputamt == 0) {
                sprintf(tmpstr, "加值金額不得為零元");
                usRet = MessageBox(gTransTitle, tmpstr, "請重新輸入金額", "", "", d_MB_CHECK);
                continue;
            }
        }
        break;
    } while (1);

    *amt = inputamt;
    if (gScrpitTesting == 1) return d_OK;
    /*  usRet= ShowTXBalance(inputamt);
      if(usRet!=d_OK){
          MessageBox(gTransTitle,"","使用者中斷交易","","",d_MB_CHECK);
          return d_ERR_USERCANCEL;
      }*/


    return d_OK;

}
//modify by bruce

USHORT CheckCardProfile(int PersonalProfile, int CardType) {
    /* 2014.04.25, modified by bruce
 if(PersonalProfile==5)
 { 
     if(CardType!=0x0a)
        gTXCardProfile=0;
     else
        gTXCardProfile=PersonalProfile;
 }else{
         gTXCardProfile=PersonalProfile;
 }
     */
    unsigned long UnixSec, profileexpdate;

    memcpy(&profileexpdate, &gBasicData.ucProfileExpiryDate, 4);
    if (PersonalProfile != 0) {
        fnGetRTCUNIXDataTime(&UnixSec);
        if (UnixSec > profileexpdate) {
            PersonalProfile = 0;
        }
    }
    gTXCardProfile = PersonalProfile;
    /*
   
        if(PersonalProfile==4){
                                   if(memcmp(&gBasicData.SocialSecuityCode,nullid,6)!=0)//比對身份證字號非空值
                                   {
                                           if(memcmp(&gSSC,&csctx.SocialSecuityCode,6)==0)//比對身份證字號
                                           {	
                                                   flag=true;
                                                   memset(&gSSC,0x00,6);
                                           }
                                   }
                      }else if(csctx.profile==2 || csctx.profile==3){
                                   memcpy(&gSSC,&csctx.SocialSecuityCode,6);
                      }else{
                                   memset(&gSSC,0x00,6);
                      }    
     */

    return d_OK;
}

USHORT GetCard_PersonalProfile(BYTE *strPersonalProfileName) {

    switch (gTXCardProfile) {
        case 0:
            sprintf(strPersonalProfileName, "普通卡");
            break;
        case 1:
            sprintf(strPersonalProfileName, "敬老卡(一)");
            break;
        case 2:
            sprintf(strPersonalProfileName, "敬老卡(一)");
            break;
        case 3:
            sprintf(strPersonalProfileName, "愛心卡");
            break;
        case 4:
            sprintf(strPersonalProfileName, "愛心陪伴卡");
            break;
        case 5:
            sprintf(strPersonalProfileName, "學生卡");
            break;

        case 8:
            sprintf(strPersonalProfileName, "優待卡");
            break;

        default:
            sprintf(strPersonalProfileName, "普通卡");
            break;
    }
    return d_OK;
}
//modify by burce

USHORT GetAutoDeductAmt() {
    int i;
    USHORT amt = 0;
    BYTE line1[32], line2[32], line3[32];
    unsigned long UnixSec, profileexpdate;
    memcpy(&profileexpdate, &gBasicData.ucProfileExpiryDate, 4);
    if (gBasicData.ucPersonalProfile != 0) {
        fnGetRTCUNIXDataTime(&UnixSec);
        if (UnixSec > profileexpdate) {
            gTXCardProfile = 0;
        } else {
            gTXCardProfile = gBasicData.ucPersonalProfile;
        }
    } else {
        gTXCardProfile = gBasicData.ucPersonalProfile;
    }
    /*
    //2014.05.13 kobe added sizeOfAmtTable
        int sizeOfAmtTable = sizeof(gConfig.TX.AMTTABLE)/sizeof(AMTTABLE_STRUCT);
        for(i=0;i<sizeOfAmtTable;i++){
             if(gBasicData.ucAreaCode==gConfig.TX.AMTTABLE[i].AREACODE){    
               amt=gConfig.TX.AMTTABLE[i].AMT[gTXCardProfile];
               //return amt;
               break;
             }
        }
     */
    //   if(amt==0){
    amt = gConfig.TX.AMTTABLE[gSelectTable].AMT[gTXCardProfile];
    //   }
    ULONG ev = BYTE3Data2LONG((char *) gBasicData.ucEV);
    BYTE strPersonalProfileName[32];
    memset(strPersonalProfileName, 0x00, sizeof (strPersonalProfileName));
    //     CheckCardProfile(gBasicData.ucPersonalProfile,gBasicData.ucCardType);
    GetCard_PersonalProfile(strPersonalProfileName);

    sprintf(line1, "卡片種類  %s", strPersonalProfileName);
    sprintf(line2, "可用餘額  %ld", ev);
    sprintf(line3, "交易金額  %d", amt);

    ShowMessage3line(gTransTitle, line1, line2, line3, Type_ComformNONE);



    return amt;

}

void *Process_AfterTXSueeess() {

    gTransData.ucTXSTATUS = TransStatus_ADVREQ;
    usSaveTxData(&gTransData);
    PrintReceipt();

    if (bgNETWORKChannel == CHANNEL_ETHERNET) {//接實体網路時，購貨交易advice 採背景上傳
        if (gTransData.ucTXTYPE == TXTYPE_DEDUCT) {
            //  Thread_SendCurrentTxAdvice();  
        } else {
            Process_SendCurrentTxAdvice2();
        }
    }


    // SSLSocketDisConnect();    
    //Process_SendAdvice3(0);
    // pthread_exit(NULL);
}

USHORT Trans_Deduct()//購貨交易
{
    //   BYTE Buffer[sizeof(ReadCardBasicData_TM_Out)];
    //  ReadCardBasicData_TM_Out BasicData;
    USHORT usRet;

    if ((strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) || (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)) {
        usRet = Trans_Deduct_Auto();
        return usRet;
    }

    char operationMode[16];
    int ret;
    gucLockReason = 0;


    BYTE line[64];
    USHORT mkHWSupport;
    USHORT amt = 0;

    memset(gTransTitle, 0x00, sizeof (gTransTitle));
    sprintf(gTransTitle, "購貨");

    if ((usRet = checkTxnLimit() != d_OK))
        return usRet;

    //2014.04.21, kobe added for ECR      
    if (ecrObj.gData.isEcrTxn) sprintf(operationMode, "ECR_TXN");
    else sprintf(operationMode, "%s", gConfig.TX.OPERATIONMODE);



    if (strcmp(operationMode, "BARCODESCANNER") == 0)
        CTOS_USBSelectMode(d_USB_HOST_MODE);


    //2014.04.21, kobe modified it(gConfig.TX.OPERATIONMODE to operationMode)
    if (strcmp(operationMode, "AUTO_FIX") == 0) {
        SelectAuto_FixDeductAMT();
    }
    //modify by bruce 
    // long ev;
    // int amt=0;


    //int iret;
    //int item=0;
    memset(gTransTitle, 0x00, sizeof (gTransTitle));
    sprintf(gTransTitle, "購貨");

    Reader_CLEAR_LED();
    BYTE BarCode[20 + 1];

    int i = 0;
    int iret;

    gTXCardProfile = 0;

    memset(BarCode, 0x00, sizeof (BarCode));
    /*ULONG tstart,tend;
     BYTE tmp[32];
    tstart  = CTOS_TickGet();*/
    if ((strcmp(operationMode, "MANUAL") == 0) || (strcmp(operationMode, "BARCODESCANNER") == 0)) {

        usRet = ShowBalanceAndInputAmt(TXTYPE_DEDUCT, &amt);
        //usRet=InputAMT(TXTYPE_DEDUCT,&amt);
        if (usRet != d_OK) {
            goto DISCONNECT;

        }

        if (strcmp(gConfig.TX.OPERATIONMODE, "BARCODESCANNER") == 0) {
            usRet = ShowInputBox2(gTransTitle, "", "請刷條碼", BarCode, 20, 2, 0);
            if (usRet != d_OK) {
                usRet = d_ERR_USERCANCEL;
                goto DISCONNECT;
            }

            CTOS_USBSelectMode(d_USB_DEVICE_MODE);
        }/*else if(strcmp(gConfig.TX.OPERATIONMODE,"MANUAL")==0){
                
               
                iret= iProcessWaitCardwithTimer(20);
                if(iret!=0x9000){
                    goto START;
                    
                }
            }*/
    } else if (strcmp(operationMode, "ECR_TXN") == 0) { //2014.09.19,kobe added for response waitting card timeout                               
        iret = iProcess_ReadCardBasicData();
        if (iret) usRet = ECC_CheckReaderResponseCode(iret);
        if (usRet != d_OK) {
            goto DISCONNECT;
        }

    }



    if (ecrObj.gData.isEcrTxn) {
        amt = ecrObj.ngData->txnAmt;
        if (amt > 10000 || amt == 0) {
            usRet = ECR_TXN_AMT_WRONG;
            goto DISCONNECT;
        }//return ECR_TXN_AMT_WRONG;    
    }

    if (GetFunctionSwitch("AUTOLOAD")) {
        gAutoloadAMT = 0;
        if ((gBasicData.bAutoLoad == TRUE)) {
            Process_Autoload(amt);
        }
    }
    mkHWSupport = Eth_CheckDeviceSupport();
    if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
        CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
    }

    ShowMessage2line(gTransTitle, "交易進行中.", "請勿移動卡片", Type_ComformNONE);

    //   CTOS_Delay(500);//2014.07.31, fixed that when reade cleaned flash, no response to EDC  
    usInitTxData(TXTYPE_DEDUCT);


    gTransData.lTxnAmt = amt;
    gTransData.ucBasicData_CardProfile = gTXCardProfile;
    if (strcmp(operationMode, "BARCODESCANNER") == 0) {
        memcpy(gTransData.ucTMINVOICENO, BarCode, sizeof (BarCode));
    }

    BYTE baMsg[16];
    while (1) {
        usRet = (USHORT) inPPR_TxnReqOffline(); //2014.04.22, kobe modified for ECR 
        if (usRet == 0x6415 || usRet == 0x9000) {
            /*記錄交易前卡片餘額，備交易retry判斷用*/
            memset(&gCardRemainEV, 0x00, sizeof (gCardRemainEV));
            memcpy(&gCardRemainEV, (BYTE *) & gTransData.lEVBeforeTxn, sizeof (gTransData.lEVBeforeTxn));


            if (usRet == 0x6415) {
                gTransData.ucTXSTATUS = TransStatus_REQ;
                gSaveReversalflag = 1;

                ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
                usRet = SSLSocketConnect();
                if (usRet != d_OK) {
                    MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
                    goto DISCONNECT;
                }
                usRet = Process_TransComm2(&gTransData, 1);
                SSLSocketDisConnect();

                ECC_CheckAPResponseCode(usRet);
                if (usRet != d_OK) {
                    ShowMessage2line(gTransTitle, "通訊異常", "請重試交易", Type_ComformOK);
                    goto DISCONNECT;
                }
                SetTransSN(gTransData.ulTerminalInvoiceNum);
                usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
                if (usRet != d_OK) {
                    goto DISCONNECT;
                }
            }
            usRet = (USHORT) inPPR_AuthTxnOffline();
            if (usRet != 0x9000) {
                if (usRet == 0x6088 || usRet == 0x9969 || usRet == 0x9968 || usRet == 6004) {
                    ShowMessage2line(gTransTitle, "交易未完成", "請放回卡片", Type_ComformNONE);
                    continue;
                }

                if (usRet == 0x9970) {
                    do {
                        CTOS_Beep();
                        ret = (USHORT) iProcess_ReadCardBasicData();
                        if (ret != 0x9000) {
                            CTOS_PrinterPutString("9970讀卡機接收失敗，請確認!!");
                            //    PrintDateTime((STR *)&gTransData.ucTxnData,(STR *)&gTransData.ucTxnTime);
                        }
                    } while (ret != 0x9000);
                    //      if(memcmp(&gCardRemainEV,&gBasicData.ucEV,3)!=0)//若卡片餘額不等於交易前卡片餘額 則retry重確認交易是否完成
                    continue;
                }
                usRet = ECC_CheckReaderResponseCode(usRet);
                if (usRet != d_OK) {
                    goto DISCONNECT;
                }
            }
            /*             tend  = CTOS_TickGet();    
                     sprintf(tmp,"tend-tstart=%ld",  tend-tstart);      
                     CTOS_PrinterPutString(tmp);*/
            mkHWSupport = Eth_CheckDeviceSupport();
            if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
                CTOS_CLLEDSet(0x0f, d_CL_LED_GREEN);
            }
            remove(ReversalFile);

            CTOS_Beep();
            CTOS_Beep();
            sprintf(line, "卡片餘額  %ld", gTransData.lEVafterTxn);
            ShowMessage3line(gTransTitle, "交易完成...", line, "請記得帶走卡片.", Type_ComformNONE);
            Process_AfterTXSueeess();


            ShowSystemMemoryStatus("Process_AfterTXSueeess 1");
            ShowMessage3line(gTransTitle, "交易完成...", line, "請記得帶走卡片.", Type_RemoveCard);
            gAutoloadAMT = 0;
            gEVBeforeAutoload = 0;

            if (gScrpitTesting == 1) {
                goto DISCONNECT;
            }
        } else {
            ECC_CheckReaderResponseCode(usRet);
            if (gScrpitTesting == 1) {
                goto DISCONNECT;
            }
        }
        break;
    }

    USHORT TotalCount;
DISCONNECT:

    CheckMemoarystatus();
    return usRet;
}

USHORT Trans_Deduct2()//購貨交易
{

    char operationMode[16];
    int ret;
    gucLockReason = 0;
    USHORT usRet;

    BYTE line[64];
    BYTE tmp[32];
    ULONG tstart, tend, t1, t2, t3, t4;
    // usRet=Config_GetData();
    memset(gTransTitle, 0x00, sizeof (gTransTitle));
    sprintf(gTransTitle, "購貨");
    // ret=pthread_create(&Thread_Comm, NULL, (void*)SSLSocketConnect_thread, NULL);    // 執行緒 SSLSocketConnect 

    if ((usRet = checkTxnLimit() != d_OK))
        return usRet;

    USHORT amt = 0;

    //2014.04.21, kobe added for ECR      
    if (ecrObj.gData.isEcrTxn) sprintf(operationMode, "ECR_TXN");
    else sprintf(operationMode, "%s", gConfig.TX.OPERATIONMODE);



    if (strcmp(operationMode, "BARCODESCANNER") == 0)
        CTOS_USBSelectMode(d_USB_HOST_MODE);


    //2014.04.21, kobe modified it(gConfig.TX.OPERATIONMODE to operationMode)
    if (strcmp(operationMode, "AUTO_FIX") == 0) {
        SelectAuto_FixDeductAMT();
    } else if (strcmp(operationMode, "AUTO_BYTYPE") == 0) {
        SelectAMTTABLE();
    }
    //modify by bruce 
    // long ev;
    // int amt=0;


    //int iret;
    //int item=0;
    memset(gTransTitle, 0x00, sizeof (gTransTitle));
    sprintf(gTransTitle, "購貨");



    /*
        usRet= ShowTXBalance(amt);
        if(usRet!=d_OK){
                return d_ERR_USERCANCEL; 
         }   
     */
START:
    Reader_CLEAR_LED();
    BYTE BarCode[20 + 1];

    int i = 0;
    int iret;
    do {
        //modify by bruce 
        tstart = CTOS_TickGet();
        gTXCardProfile = 0;
        //end
        memset(BarCode, 0x00, sizeof (BarCode));
        //   ret=pthread_create(&Thread_Comm, NULL, (void*)SSLSocketConnect_thread2, NULL);    // 執行緒 SSLSocketConnect 

        if ((strcmp(operationMode, "MANUAL") == 0) || (strcmp(operationMode, "BARCODESCANNER") == 0)) {

            // usRet= ShowBalanceAndInputAmt(TXTYPE_DEDUCT,&amt);
            usRet = InputAMT(TXTYPE_DEDUCT, &amt);
            if (usRet != d_OK) {
                goto DISCONNECT;
            }

            if (strcmp(gConfig.TX.OPERATIONMODE, "BARCODESCANNER") == 0) {
                usRet = ShowInputBox2(gTransTitle, "", "請刷條碼", BarCode, 20, 2, 0);
                if (usRet != d_OK) {
                    usRet = d_ERR_USERCANCEL;
                    goto START;
                }
                CTOS_USBSelectMode(d_USB_DEVICE_MODE);
            } else if (strcmp(gConfig.TX.OPERATIONMODE, "MANUAL") == 0) {
                iret = iProcessWaitCardwithTimer(20);
                if (iret != 0x9000) {
                    goto START;
                }
            }
        } else if (strcmp(operationMode, "ECR_TXN") == 0) { //2014.09.19,kobe added for response waitting card timeout                               
            iret = iProcess_ReadCardBasicData();
            if (iret) usRet = ECC_CheckReaderResponseCode(iret);
            if (usRet != d_OK) {
                goto DISCONNECT;
            }

        } else {

            if (strcmp(operationMode, "AUTO_FIX") == 0) {
                //modify by bruce                         
                //   int i=atoi( gConfig.TX.AMTTABLE[0].AREACODE);
                int i = gConfig.TX.AMTTABLE[0].AREACODE;
                amt = gConfig.TX.AMTTABLE[0].AMT[i];

                memset(gTransTitle, 0x00, sizeof (gTransTitle));
                sprintf(gTransTitle, "購貨-%d元", amt);

            }
            if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
                memset(gTransTitle, 0x00, sizeof (gTransTitle));
                sprintf(gTransTitle, "購貨-%s", gConfig.TX.AMTTABLE[gSelectTable].NAME);
            }
            usRet = iProcessWaitCard();
            if (usRet != d_OK) {
                if (usRet == d_ERR_USERCANCEL)
                    goto START;
                else
                    continue;
            }
            if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {

                amt = GetAutoDeductAmt();
            }
        }
        if (strcmp(operationMode, "AUTO_BYTYPE") != 0)
            ShowMessage2line(gTransTitle, "交易進行中.", "請勿移動卡片", Type_ComformNONE);

        if (ecrObj.gData.isEcrTxn) {
            amt = ecrObj.ngData->txnAmt;
            if (amt > 10000 || amt == 0) {
                usRet = ECR_TXN_AMT_WRONG;
                goto START;
            }//return ECR_TXN_AMT_WRONG;    
        }

        if (GetFunctionSwitch("AUTOLOAD")) {
            gAutoloadAMT = 0;
            if ((gBasicData.bAutoLoad == TRUE)) {
                Process_Autoload(amt);
            }
        }
        ShowMessage2line(gTransTitle, "交易進行中.", "請勿移動卡片", Type_ComformNONE);


        //   CTOS_Delay(500);//2014.07.31, fixed that when reade cleaned flash, no response to EDC  
        usInitTxData(TXTYPE_DEDUCT);

        gTransData.lTxnAmt = amt;
        gTransData.ucBasicData_CardProfile = gTXCardProfile;
        if (strcmp(operationMode, "BARCODESCANNER") == 0) {
            memcpy(gTransData.ucTMINVOICENO, BarCode, sizeof (BarCode));
        }

        //      unsigned long ulTick,pStart,p1,p2;
        BYTE baMsg[16];
        while (1) {
            //int iret= inPPR_TxnReqOffline();//2014.04.22, kobe removed it, always return "usRet" Variable

            usRet = (USHORT) inPPR_TxnReqOffline(); //2014.04.22, kobe modified for ECR

            if (usRet == 0x6415 || usRet == 0x9000) {
                /*記錄交易前卡片餘額，備交易retry判斷用*/
                memset(&gCardRemainEV, 0x00, sizeof (gCardRemainEV));
                memcpy(&gCardRemainEV, (BYTE *) & gTransData.lEVBeforeTxn, sizeof (gTransData.lEVBeforeTxn));


                if (usRet == 0x6415) {
                    gTransData.ucTXSTATUS = TransStatus_REQ;
                    gSaveReversalflag = 1;
                    /* while(1){
                             kill_rc = pthread_kill(Thread_Comm,0);
                             if(kill_rc==ESRCH) break;
                             ShowMessage2line(gTransTitle,"交易進行中..","請勿移動卡片",Type_ComformNONE);
                      }*/
                    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
                    usRet = SSLSocketConnect();
                    if (usRet != d_OK) {
                        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
                        goto START;
                    }
                    usRet = Process_TransComm2(&gTransData, 1);
                    SSLSocketDisConnect();
                    CTOS_Delay(500);
                    ECC_CheckAPResponseCode(usRet);
                    if (usRet != d_OK) {
                        ShowMessage2line(gTransTitle, "通訊異常", "請重試交易", Type_ComformOK);
                        goto START;
                    }
                    SetTransSN(gTransData.ulTerminalInvoiceNum);
                    usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
                    if (usRet != d_OK) {
                        goto START;
                    }
                }

                usRet = (USHORT) inPPR_AuthTxnOffline();


                if (usRet != 0x9000) {
                    if (usRet == 0x6088 || usRet == 0x9969 || usRet == 0x9968 || usRet == 6004) {
                        ShowMessage2line(gTransTitle, "交易未完成", "請放回卡片", Type_ComformNONE);
                        continue;
                    }

                    if (usRet == 0x9970) {
                        do {
                            CTOS_Beep();
                            ret = (USHORT) iProcess_ReadCardBasicData();
                            if (ret != 0x9000) {
                                CTOS_PrinterPutString("9970讀卡機接收失敗，請確認!!");
                                //    PrintDateTime((STR *)&gTransData.ucTxnData,(STR *)&gTransData.ucTxnTime);
                            }
                        } while (ret != 0x9000);
                        //      if(memcmp(&gCardRemainEV,&gBasicData.ucEV,3)!=0)//若卡片餘額不等於交易前卡片餘額 則retry重確認交易是否完成
                        continue;
                    }
                    usRet = ECC_CheckReaderResponseCode(usRet);
                    if (usRet != d_OK) {
                        goto START;
                    }
                }
                //PrintReceipt( );

                // STR Line[15+1];
                // sprintf( Line,"交易完成");
                // WaitRemoveCard("交易完成.","請記得帶走卡片."); 

                //pthread_create(&thread_AfterTxSuccess, NULL,(void*) Process_AfterTXSueeess, NULL);    // 執行緒 SSLSocketConnect  
                // Reader_FINISHED_LED();
                USHORT mkHWSupport = Eth_CheckDeviceSupport();
                if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
                    CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
                }

                sprintf(line, "卡片餘額  %ld", gTransData.lEVafterTxn);
                ShowMessage3line(gTransTitle, "交易完成...", line, "請記得帶走卡片.", Type_ComformNONE);
                remove(ReversalFile);
                Process_AfterTXSueeess();

                CTOS_Beep();
                CTOS_Beep();
                //  PrintReceipt();                        
                ShowMessage3line(gTransTitle, "交易完成...", line, "請記得帶走卡片.", Type_RemoveCard);
                gAutoloadAMT = 0;
                gEVBeforeAutoload = 0;
                /*tend  = CTOS_TickGet();    

                sprintf(tmp,"tend-tstart=%ld",  tend-tstart);      
                CTOS_PrinterPutString(tmp); */
                goto START;
                //  Process_SendCurrentTxAdvice();
                //  SSLSocketDisConnect();    

                /*  while(1){
                         kill_rc = pthread_kill(thread_AfterTxSuccess,0);
                         if(kill_rc==ESRCH) break;
                   }*/
                // SSLSocketDisConnect();        


            } else {
                ECC_CheckReaderResponseCode(usRet);


            }

            break;
        }
        if ((strcmp(operationMode, "MANUAL") == 0) ||
                (strcmp(operationMode, "BARCODESCANNER") == 0) ||
                (ecrObj.gData.isEcrTxn == TRUE))
            break;
    } while (1);
    USHORT TotalCount;
DISCONNECT:


    CheckMemoarystatus();
    return usRet;
}

USHORT Trans_Deduct_Auto()//購貨交易
{
    //   BYTE Buffer[sizeof(ReadCardBasicData_TM_Out)];
    //  ReadCardBasicData_TM_Out BasicData;
    int inOutLen, inRecvlen;
    char operationMode[16];
    ULONG tstart, tend;
    int ret;
    gucLockReason = 0;
    USHORT usRet;
    BYTE tmp[32];
    //  ULONG tstart,tend,t1,t2,t3,t4;
    int amt = 0;
    BYTE line[64];
    BYTE line1[64], line2[64], line3[64];
    USHORT mkHWSupport;
    // usRet=Config_GetData();
    memset(gTransTitle, 0x00, sizeof (gTransTitle));
    sprintf(gTransTitle, "購貨");

    if ((usRet = checkTxnLimit() != d_OK))
        return usRet;

    sprintf(operationMode, "%s", gConfig.TX.OPERATIONMODE);


    if (strcmp(operationMode, "AUTO_FIX") == 0) {
        SelectAuto_FixDeductAMT();
    } else if (strcmp(operationMode, "AUTO_BYTYPE") == 0) {
        SelectAMTTABLE();
    }

    memset(gTransTitle, 0x00, sizeof (gTransTitle));
    sprintf(gTransTitle, "購貨");


    Reader_CLEAR_LED();
    BYTE BarCode[20 + 1];

START:
    do {
        gTXCardProfile = 0;
        memset(BarCode, 0x00, sizeof (BarCode));
        if (strcmp(operationMode, "AUTO_FIX") == 0) {
            int i = gConfig.TX.AMTTABLE[0].AREACODE;
            amt = gConfig.TX.AMTTABLE[0].AMT[i];

            memset(gTransTitle, 0x00, sizeof (gTransTitle));
            sprintf(gTransTitle, "購貨-%d元", amt);

        } else if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
            memset(gTransTitle, 0x00, sizeof (gTransTitle));
            sprintf(gTransTitle, "購貨-%s", gConfig.TX.AMTTABLE[gSelectTable].NAME);
        }
        gucLCDControlFlag = 1;
        tstart = CTOS_TickGet();
        usRet = iProcessWaitCard();
        if (usRet != d_OK) {
            if (usRet == d_ERR_USERCANCEL)
                goto DISCONNECT;
            else
                continue;
        }
        if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
            amt = GetAutoDeductAmt();
        }
        ShowMessage2line(gTransTitle, "交易進行中.", "請勿移動卡片", Type_ComformNONE);


        if (GetFunctionSwitch("AUTOLOAD")) {
            gAutoloadAMT = 0;
            if ((gBasicData.bAutoLoad == TRUE)) {
                Process_Autoload(amt);
            }
        }
        mkHWSupport = Eth_CheckDeviceSupport();
        if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
            CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
        }
        usInitTxData(TXTYPE_DEDUCT);
        if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
            sprintf(gTransData.POSID, "%s", gConfig.TX.AMTTABLE[gSelectTable].NAME);
        }
        gTransData.lTxnAmt = amt;
        gTransData.ucBasicData_CardProfile = gTXCardProfile;

        BYTE baMsg[16];
        while (1) {
            usRet = (USHORT) inPPR_TxnReqOffline(); //2014.04.22, kobe modified for ECR
            if (usRet == 0x6415 || usRet == 0x9000) {
                /*記錄交易前卡片餘額，備交易retry判斷用*/
                memset(&gCardRemainEV, 0x00, sizeof (gCardRemainEV));
                memcpy(&gCardRemainEV, (BYTE *) & gTransData.lEVBeforeTxn, sizeof (gTransData.lEVBeforeTxn));


                if (usRet == 0x6415) {
                    gTransData.ucTXSTATUS = TransStatus_REQ;
                    gSaveReversalflag = 1;
                    /* while(1){
                             kill_rc = pthread_kill(Thread_Comm,0);
                             if(kill_rc==ESRCH) break;
                             ShowMessage2line(gTransTitle,"交易進行中..","請勿移動卡片",Type_ComformNONE);
                      }*/
                    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
                    usRet = SSLSocketConnect();
                    if (usRet != d_OK) {
                        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
                        goto START;
                    }
                    usRet = Process_TransComm2(&gTransData, 1);
                    SSLSocketDisConnect();
                    //    CTOS_Delay(500);
                    ECC_CheckAPResponseCode(usRet);
                    if (usRet != d_OK) {
                        ShowMessage2line(gTransTitle, "通訊異常", "請重試交易", Type_ComformOK);
                        goto START;
                    }
                    SetTransSN(gTransData.ulTerminalInvoiceNum);
                    usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
                    if (usRet != d_OK) {
                        goto START;
                    }
                }
                usRet = (USHORT) inPPR_AuthTxnOffline();
                if (usRet != 0x9000) {
                    if (usRet == 0x6088 || usRet == 0x9969 || usRet == 0x9968 || usRet == 6004) {
                        ShowMessage2line(gTransTitle, "交易未完成", "請放回卡片", Type_ComformNONE);
                        continue;
                    }

                    if (usRet == 0x9970) {
                        do {
                            CTOS_Beep();
                            ret = (USHORT) iProcess_ReadCardBasicData();
                            if (ret != 0x9000) {
                                CTOS_PrinterPutString("9970讀卡機接收失敗，請確認!!");
                                //    PrintDateTime((STR *)&gTransData.ucTxnData,(STR *)&gTransData.ucTxnTime);
                            }
                        } while (ret != 0x9000);
                        //      if(memcmp(&gCardRemainEV,&gBasicData.ucEV,3)!=0)//若卡片餘額不等於交易前卡片餘額 則retry重確認交易是否完成
                        continue;
                    }
                    usRet = ECC_CheckReaderResponseCode(usRet);
                    if (usRet != d_OK) {
                        goto START;
                    }
                }
                /*tend  = CTOS_TickGet();    
                sprintf(tmp,"tend-tstart=%ld",  tend-tstart);      
                CTOS_PrinterPutString(tmp); 
                 */ //      PrintReceipt( );

                // STR Line[15+1];
                // sprintf( Line,"交易完成");
                // WaitRemoveCard("交易完成.","請記得帶走卡片."); 
                mkHWSupport = Eth_CheckDeviceSupport();
                if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
                    CTOS_CLLEDSet(0x0f, d_CL_LED_GREEN);
                }
                remove(ReversalFile);
                CTOS_Beep();
                CTOS_Beep();
                BYTE strPersonalProfileName[32];
                memset(strPersonalProfileName, 0x00, sizeof (strPersonalProfileName));
                GetCard_PersonalProfile(strPersonalProfileName);
                sprintf(line, "卡片餘額  %ld", gTransData.lEVafterTxn);
                sprintf(line1, "卡片種類  %s", strPersonalProfileName);
                sprintf(line3, "交易金額  %ld", gTransData.lTxnAmt);
                ShowMessage3line(gTransTitle, line1, line3, line, Type_ComformNONE);
                Process_AfterTXSueeess();
                ShowSystemMemoryStatus("Process_AfterTXSueeess 1");

                ShowMessage3line(gTransTitle, line1, line3, line, Type_RemoveCard);

                gAutoloadAMT = 0;
                gEVBeforeAutoload = 0;

                if (gScrpitTesting == 1) {
                    goto DISCONNECT;
                }

            } else {
                usRet = ECC_CheckReaderResponseCode(usRet);
                if (usRet != d_OK) {
                    goto START;
                }
            }

            break;
        }
        USHORT TotalCount;
        TotalCount = CheckUnuploadTxCount();
        if (TotalCount > gFORCEONLINELIMIT) {
            usRet = d_ERR_BATCHNOTEMPTY;
            ECC_CheckAPResponseCode(usRet);
            return usRet;
        }

        CheckMemoarystatus();
    } while (1);

DISCONNECT:
    return usRet;
}

USHORT Trans_Cancel() {
    int iret;
    long ev;

    TRANS_DATA2 LastTransData;
    USHORT usRet;

    sprintf(gTransTitle, "%s", Title_Cancle);
    if ((usRet = checkTxnLimit() != d_OK))
        return usRet;


    USHORT ret = ShowMessage2line(gTransTitle, "是否進行取消?", "請確認!", Type_ComformOK);
    if (ret != d_OK) return ret;

    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
    ret = SSLSocketConnect();
    if (ret != d_OK) {
        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
        return ret;
    }

    ret = GetLastTransData(&LastTransData);
    /* 
     iret= iProcess_ReadCardBasicData();
     usRet=ECC_CheckReaderResponseCode(iret);
     if(usRet!=d_OK) return usRet;
     */

    ShowMessage2line(gTransTitle, "交易進行中.", "請放上卡片", Type_ComformNONE);
    usInitTxData(TXTYPE_VOID);
    memcpy(&gTransData.ucOrgTxnTerminalID, &LastTransData.ucCPUDeviceID, sizeof (gTransData.ucOrgTxnTerminalID));
    memcpy(&gTransData.ucOrgTxnDate, &LastTransData.ucTxnData, sizeof (gTransData.ucOrgTxnDate));
    memcpy(&gTransData.ucOrgTxnRRN, &LastTransData.ucRRN, sizeof (gTransData.ucOrgTxnRRN));

    do {

        // gTransData.ulTMTxnSN=0;
        USHORT mkHWSupport = Eth_CheckDeviceSupport();
        if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
            CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
        }
        iret = inPPR_TxnReqOnline();
        if (iret == 0x6415 || iret == 0x9000) {
            if (iret == 0x6415) {
                gTransData.ucTXSTATUS = TransStatus_REQ;

                gSaveReversalflag = 1;
                /*  while(1){
                                  kill_rc = pthread_kill(Thread_Comm,0);
                                  if(kill_rc==ESRCH) break;
                                  ShowMessage2line(gTransTitle,"交易進行中..","請勿移動卡片",Type_ComformNONE);
                  }*/
                ShowMessage2line(gTransTitle, "交易進行中..", "請勿移動卡片", Type_ComformNONE);
                ret = Eth_PutDeviecBackOnBase();
                ret = Process_TransComm2(&gTransData, 1);
                ECC_CheckAPResponseCode(ret);
                if (ret != d_OK) {
                    goto Disconnect;
                }
                ShowStatusLine("已完成");

                ret = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
                if (ret != d_OK) {
                    remove(ReversalFile);
                    goto Disconnect;
                }
            }

            iret = inPPR_AuthTxnOnline();
            if (iret == 0x6088 || iret == 0x9969 || iret == 0x9968 || iret == 0x6004) {
                ShowMessage2line(gTransTitle, "交易未完成", "請放回卡片", Type_ComformNONE);
                Reader_ERR_LED();
                iret = iProcess_ReadCardBasicData();

                continue;
            }

            if (iret == 0x9970) {//2014.08.25, 每個交易的Auth 之後 檢查  讀卡機當機後 需讀basicdata 直到讀出來為止，再判斷是否要進retry

                do {
                    Reader_ERR_LED();
                    CTOS_Beep();
                    ret = (USHORT) iProcess_ReadCardBasicData();
                    if (ret != 0x9000) {
                        CTOS_PrinterPutString("9970讀卡機接收失敗，請確認!!");
                        //    PrintDateTime((STR *)&gTransData.ucTxnData,(STR *)&gTransData.ucTxnTime);
                    }
                } while (ret != 0x9000);
                //   if(memcmp(&gCardRemainEV,&gBasicData.ucEV,3)!=0)//若卡片餘額不等於交易前卡片餘額 則retry重確認交易是否完成
                continue;
            }


            ret = ECC_CheckReaderResponseCode(iret);
            if (ret != d_OK) {
                goto Disconnect;
            }
            BYTE tmpstr[64];

            sprintf(tmpstr, "卡片餘額  %ld", gTransData.lEVafterTxn);
            ShowMessage3line(gTransTitle, "交易完成...", tmpstr, "請記得帶走卡片.", Type_ComformNONE);
            //   pthread_create(&thread_AfterTxSuccess, NULL, (void*)Process_AfterTXSueeess, NULL);    // 執行緒 SSLSocketConnect    
            // Reader_FINISHED_LED();
            USHORT mkHWSupport = Eth_CheckDeviceSupport();
            if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
                CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
            }
            Process_AfterTXSueeess();
            remove(ReversalFile);
            //PrintReceipt( );

            //    LastTransData.ucTXSTATUS=TransStatus_VOIDED;
            //   usUpdataTxData( &LastTransData);
            ShowMessage3line(gTransTitle, "交易完成...", tmpstr, "請記得帶走卡片.", Type_RemoveCard);
            // Process_SendAdvice3(0);
            // gTransData.ucTXSTATUS=TransStatus_ADVREQ;
            // usSaveTxData(&gTransData);
            // Process_SendAdvice3(0);
        } else {
            ret = ECC_CheckReaderResponseCode(iret);

        }
    } while (iret == 0x6088);
Disconnect:
    //    Eth_SSLSocketDisConnect();   

    SSLSocketDisConnect();

    CheckMemoarystatus();
    return ret;
}

USHORT Trans_Refund() {
    USHORT usRet;
    int iret;
    long ev;

    //usRet=Config_GetData();
    BYTE Buffer[sizeof (ReadCardBasicData_TM_Out)];
    ReadCardBasicData_TM_Out BasicData;
    int ret;
    sprintf(gTransTitle, "%s", Title_Refund);

    if ((usRet = checkTxnLimit() != d_OK))
        return usRet;

    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);
    ret = SSLSocketConnect();
    if (ret != d_OK) {
        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
        return ret;
    }
    //  usRet=pthread_create(&Thread_Comm, NULL, (void*)SSLSocketConnect_thread, NULL);    // 執行緒 SSLSocketConnect 
    STR line1[32], line2[32];
    int amt = 0;
    memset(Buffer, 0x00, sizeof (Buffer));

    USHORT mkHWSupport = Eth_CheckDeviceSupport();
    if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
        CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
    }
    ShowMessage2line(gTransTitle, "交易進行中...", "請放上卡片", Type_ComformNONE);
    iret = iProcess_ReadCardBasicData();
    if (iret) usRet = ECC_CheckReaderResponseCode(iret);
    if (usRet != d_OK) {
        return usRet;
    }

    if (ecrObj.gData.isEcrTxn) {
        amt = ecrObj.ngData->txnAmt;
        if (amt > 10000 || amt == 0) return ECR_TXN_AMT_WRONG;
    } else {
        do {

            ev = BYTE3Data2LONG((char *) gBasicData.ucEV);
            sprintf(line1, "可用餘額:%ld", ev);
            sprintf(line2, "請輸入退貨金額:");
            usRet = ShowInputBox2(gTransTitle, line1, line2, Buffer, 5, 0, 0);
            if (usRet != d_OK) {
                usRet = d_ERR_USERCANCEL;
                goto Disconnect;

            }

            amt = atoi(Buffer);
            if (amt > 10000) {
                MessageBox(gTransTitle, "", "交易金額不得超過一萬", "請重新輸入", "", d_MB_CHECK);
                continue;
            } else if (amt == 0) {
                MessageBox(gTransTitle, "", "交易金額不得為零元", "請重新輸入", "", d_MB_CHECK);
                continue;
            } else {
                break;
            }

        } while (1);
    }

    ShowMessage2line(gTransTitle, "交易進行中.", "請勿移動卡片", Type_ComformNONE);
    usInitTxData(TXTYPE_REFUND);
    gTransData.lTxnAmt = amt;

    do {

        // gTransData.ulTMTxnSN=0;

        iret = inPPR_TxnReqOnline();
        if (iret == 0x6415 || iret == 0x9000) {
            if (iret == 0x6415) {
                gTransData.ucTXSTATUS = TransStatus_REQ;

                gSaveReversalflag = 1;
                usRet = Eth_PutDeviecBackOnBase();
                /*   while(1){
                                   kill_rc = pthread_kill(Thread_Comm,0);
                                   if(kill_rc==ESRCH) break;
                                   ShowMessage2line(gTransTitle,"交易進行中..","請勿移動卡片",Type_ComformNONE);
                   }*/
                usRet = Process_TransComm2(&gTransData, 1);
                ECC_CheckAPResponseCode(usRet);
                if (usRet != d_OK) {
                    goto Disconnect;
                }
                ShowStatusLine("已完成");

                usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
                if (usRet != d_OK) {
                    remove(ReversalFile);
                    goto Disconnect;
                }
            }

            iret = inPPR_AuthTxnOnline();
            if (iret != 0x9000) {
                if (iret == 0x6088 || iret == 0x9969 || iret == 0x9968 || iret == 6004) {
                    ShowMessage2line(gTransTitle, "交易未完成", "請放回卡片", Type_ComformNONE);
                    Reader_ERR_LED();
                    continue;
                }
                /*2014.07.24, version_11,fixed bug
                 iret = iProcess_ReadCardBasicData();
                  if(iret!=0x9000){
                      //無法確認是否已扣款，報警處理
                  }
              //   if(memcmp(&gCardRemainEV,&gBasicData.ucEV,3)!=0)//若卡片餘額不等於交易前卡片餘額 則retry重確認交易是否完成
                      continue;
                 */


                if (usRet == 0x9970) {//2014.08.25, 每個交易的Auth 之後 檢查  讀卡機當機後 需讀basicdata 直到讀出來為止，再判斷是否要進retry
                    Reader_ERR_LED();
                    do {
                        CTOS_Beep();
                        ret = (USHORT) iProcess_ReadCardBasicData();
                        if (ret != 0x9000) {
                            CTOS_PrinterPutString("9970讀卡機接收失敗，請確認!!");
                            //    PrintDateTime((STR *)&gTransData.ucTxnData,(STR *)&gTransData.ucTxnTime);
                        }
                    } while (ret != 0x9000);
                    //        if(memcmp(&gCardRemainEV,&gBasicData.ucEV,3)!=0)//若卡片餘額不等於交易前卡片餘額 則retry重確認交易是否完成
                    continue;

                }
                usRet = ECC_CheckReaderResponseCode(iret);
                if (usRet != d_OK) {

                    goto Disconnect;
                }
            }
            //Reader_FINISHED_LED();
            USHORT mkHWSupport = Eth_CheckDeviceSupport();
            if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
                CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
            }
            remove(ReversalFile);
            BYTE tmpstr[64];

            sprintf(tmpstr, "卡片餘額  %ld", gTransData.lEVafterTxn);
            ShowMessage3line(gTransTitle, "交易完成...", tmpstr, "請記得帶走卡片.", Type_ComformNONE);
            // pthread_create(&thread_AfterTxSuccess, NULL,(void*)Process_AfterTXSueeess, NULL);    // 執行緒 SSLSocketConnect  
            Process_AfterTXSueeess();
            // PrintReceipt( );
            //    LastTransData.ucTXSTATUS=TransStatus_VOIDED;
            //   usUpdataTxData( &LastTransData);
            ShowMessage3line(gTransTitle, "交易完成...", tmpstr, "請記得帶走卡片.", Type_RemoveCard);
            // Process_SendCurrentTxAdvice();
            /*while(1){
                 kill_rc = pthread_kill(thread_AfterTxSuccess,0);
                 if(kill_rc==ESRCH) break;
             }*/
            //gTransData.ucTXSTATUS=TransStatus_ADVREQ;
            //usSaveTxData(&gTransData);
            //Process_SendAdvice3(0);
        } else {
            usRet = ECC_CheckReaderResponseCode(iret);
        }
    } while (iret == 0x6088);
Disconnect:
    //Eth_SSLSocketDisConnect();       
    SSLSocketDisConnect();

    CheckMemoarystatus();
    return usRet;

}

USHORT Trans_ADD() {
    USHORT usRet;
    int iret;
    long ev;
    int ret;
    BYTE Buffer[sizeof (ReadCardBasicData_TM_Out)];
    STR tmpstr[64];

    sprintf(gTransTitle, "%s", Title_ADD);

    if ((usRet = checkTxnLimit() != d_OK))
        return usRet;


    ShowMessage2line(gTransTitle, "網路連線中", "請稍候", Type_ComformNONE);

    ret = SSLSocketConnect();
    if (ret != d_OK) {
        MessageBox(gTransTitle, "", "網路連線異常", "請檢查並重試", "", d_MB_CHECK);
        return ret;
    }



    STR line1[32], line2[32];
    int amt = 0;
    memset(Buffer, 0x00, sizeof (Buffer));
    memset(line1, 0x00, sizeof (line1));
    memset(line2, 0x00, sizeof (line2));
    USHORT Miniunit;
    USHORT mkHWSupport = Eth_CheckDeviceSupport();
    if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
        CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
    }
    ShowMessage2line(gTransTitle, "交易進行中.", "請放上卡片", Type_ComformNONE);
    Miniunit = atoi(gConfig.TX.MiniunitsADDVALUE);
    iret = iProcess_ReadCardBasicData();
    if (iret) usRet = ECC_CheckReaderResponseCode(iret);
    if (usRet != d_OK) {
        goto Disconnect;
    }

    if (ecrObj.gData.isEcrTxn) {
        amt = ecrObj.ngData->txnAmt;
        if (amt % Miniunit != 0 || amt > 10000 || amt == 0) return ECR_TXN_AMT_WRONG;
    } else {
        do {

            ev = BYTE3Data2LONG((char *) gBasicData.ucEV);
            sprintf(line1, "可用餘額:%ld", ev);
            sprintf(line2, "請輸入加值金額:");
            usRet = ShowInputBox2(gTransTitle, line1, line2, Buffer, 5, 0, 0);
            if (usRet != d_OK) {
                usRet = d_ERR_USERCANCEL;
                goto Disconnect;
            }

            //Miniunit =atoi(gConfig.TX.MiniunitsADDVALUE);         
            amt = atoi(Buffer);
            if (amt % Miniunit != 0) {
                sprintf(tmpstr, "加值金額需為%d元倍數", Miniunit);
                usRet = MessageBox(gTransTitle, tmpstr, "請重新輸入金額", "", "", d_MB_CHECK);
                continue;
            } else if (amt > 10000) {
                sprintf(tmpstr, "加值金額不得超過一萬");
                usRet = MessageBox(gTransTitle, tmpstr, "請重新輸入金額", "", "", d_MB_CHECK);
                continue;
            } else if (amt == 0) {
                sprintf(tmpstr, "加值金額不得為               零元");
                usRet = MessageBox(gTransTitle, tmpstr, "請重新輸入金額", "", "", d_MB_CHECK);
                continue;
            } else {
                break;
            }
        } while (1);
    }
    /*
    iret= iProcess_ReadCardBasicData();
    usRet=ECC_CheckReaderResponseCode(iret);
    if(usRet!=d_OK) return usRet;
     */
    ShowMessage2line(gTransTitle, "交易進行中..", "請勿移動卡片", Type_ComformNONE);
    usInitTxData(TXTYPE_ADD);
    gTransData.lTxnAmt = amt;

    do {

        // gTransData.ulTMTxnSN=0;

        iret = inPPR_TxnReqOnline();
        if (iret == 0x6415 || iret == 0x9000) {
            if (iret == 0x6415) {
                gTransData.ucTXSTATUS = TransStatus_REQ;

                gSaveReversalflag = 1;
                /*    while(1){
                         kill_rc = pthread_kill(Thread_Comm,0);
                         if(kill_rc==ESRCH) break;
              
                    }  */
                ShowMessage2line(gTransTitle, "交易進行中...", "請勿移動卡片", Type_ComformNONE);
                usRet = Eth_PutDeviecBackOnBase();
                usRet = Process_TransComm2(&gTransData, 1);
                ECC_CheckAPResponseCode(usRet);
                if (usRet != d_OK) goto Disconnect;
                ShowStatusLine("已完成");

                usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
                if (usRet != d_OK) {
                    remove(ReversalFile);
                    goto Disconnect;
                }
            }

            iret = inPPR_AuthTxnOnline();
            if (iret != 0x9000) {
                if (iret == 0x6088 || iret == 0x9969 || iret == 0x9968 || iret == 6004) {
                    ShowMessage2line(gTransTitle, "交易未完成", "請放回卡片", Type_ComformNONE);
                    continue;
                }
                /*2014.07.24, version_11,fixed bug
                 iret = iProcess_ReadCardBasicData();
                  if(iret!=0x9000){
                      //無法確認是否已扣款，報警處理
                  }
          //       if(memcmp(&gCardRemainEV,&gBasicData.ucEV,3)!=0)//若卡片餘額不等於交易前卡片餘額 則retry重確認交易是否完成
                      continue;
                 */
                if (iret == 0x9970) {//2014.08.25, 每個交易的Auth 之後 檢查  讀卡機當機後 需讀basicdata 直到讀出來為止，再判斷是否要進retry
                    do {
                        CTOS_Beep();
                        ret = (USHORT) iProcess_ReadCardBasicData();
                        if (ret != 0x9000) {
                            CTOS_PrinterPutString("9970讀卡機接收失敗，請確認!!");
                            //    PrintDateTime((STR *)&gTransData.ucTxnData,(STR *)&gTransData.ucTxnTime);
                        }
                    } while (ret != 0x9000);
                    //          if(memcmp(&gCardRemainEV,&gBasicData.ucEV,3)!=0)//若卡片餘額不等於交易前卡片餘額 則retry重確認交易是否完成
                    continue;

                }
                usRet = ECC_CheckReaderResponseCode(iret);
                //   usRet=CheckReaderResponseCode(iret);
                if (usRet != d_OK) {

                    goto Disconnect;
                }
            }
            //  Reader_FINISHED_LED();
            USHORT mkHWSupport = Eth_CheckDeviceSupport();
            if ((mkHWSupport & d_MK_HW_CONTACTLESS) == d_MK_HW_CONTACTLESS) {
                CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
            }
            remove(ReversalFile);

            sprintf(tmpstr, "卡片餘額  %ld", gTransData.lEVafterTxn);
            ShowMessage3line(gTransTitle, "交易完成...", tmpstr, "請記得帶走卡片.", Type_ComformNONE);
            // pthread_create(&thread_AfterTxSuccess, NULL, (void*)Process_AfterTXSueeess, NULL);    // 執行緒 SSLSocketConnect  
            Process_AfterTXSueeess();
            // PrintReceipt( );
            //    LastTransData.ucTXSTATUS=TransStatus_VOIDED;
            //   usUpdataTxData( &LastTransData);
            ShowMessage3line(gTransTitle, "交易完成...", tmpstr, "請記得帶走卡片.", Type_RemoveCard);
            //    Process_SendCurrentTxAdvice();
            /*   int kill_rc;
               while(1){
                   kill_rc = pthread_kill(thread_AfterTxSuccess,0);
                   if(kill_rc==ESRCH) break;
               }*/
            //gTransData.ucTXSTATUS=TransStatus_ADVREQ;
            //usSaveTxData(&gTransData);
            //Process_SendAdvice3(0);
        } else {
            usRet = ECC_CheckReaderResponseCode(iret);

        }
    } while (iret == 0x6088);
Disconnect:
    //  Eth_SSLSocketDisConnect();       
    SSLSocketDisConnect();


    CheckMemoarystatus();
    return usRet;

}

USHORT Trans_AutoloadEnable() {
    USHORT usRet;
    int iret;
    long ev;

    sprintf(gTransTitle, Title_AUTOLOADENABLE);

    if ((usRet = checkTxnLimit() != d_OK))
        return usRet;

    USHORT ret = ShowMessage2line(gTransTitle, "是否進行自動加值啟用?", "請確認!", Type_ComformOK);
    if (ret != d_OK) {
        return ret;
    }


    ShowMessage2line(gTransTitle, "", "交易進行中...", Type_ComformNONE);
    usInitTxData(TXTYPE_AUTOLOADENABLE);


    do {

        // gTransData.ulTMTxnSN=0;

        iret = inPPR_TxnReqOnline();
        if (iret == 0x6415 || iret == 0x9000) {
            if (iret == 0x6415) {
                gTransData.ucTXSTATUS = TransStatus_REQ;

                gSaveReversalflag = 1;
                usRet = Process_TransComm2(&gTransData, 1);
                ECC_CheckAPResponseCode(usRet);
                if (usRet != d_OK) return usRet;
                ShowStatusLine("已完成");

                usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
                if (usRet != d_OK) {
                    remove(ReversalFile);
                    return usRet;
                }
            }

            iret = inPPR_AuthTxnOnline();
            if (iret == 0x6088 || iret == 0x9969 || iret == 0x9968) {
                ShowMessage2line(gTransTitle, "交易未完成", "請放回卡片", Type_ComformNONE);
                iret = iProcess_ReadCardBasicData();
                continue;
            }

            if (iret == 0x9970) {//2014.08.25, 每個交易的Auth 之後 檢查  讀卡機當機後 需讀basicdata 直到讀出來為止，再判斷是否要進retry
                do {
                    CTOS_Beep();
                    ret = (USHORT) iProcess_ReadCardBasicData();
                    if (ret != 0x9000) {
                        CTOS_PrinterPutString("9970讀卡機接收失敗，請確認!!");
                        //    PrintDateTime((STR *)&gTransData.ucTxnData,(STR *)&gTransData.ucTxnTime);
                    }
                } while (ret != 0x9000);
                //  if(memcmp(&gCardRemainEV,&gBasicData.ucEV,3)!=0)//若卡片餘額不等於交易前卡片餘額 則retry重確認交易是否完成
                continue;
            }


            usRet = ECC_CheckReaderResponseCode(iret);
            if (usRet != d_OK) return usRet;


            remove(ReversalFile);
            gTransData.ucTXSTATUS = TransStatus_ADVREQ;
            usSaveTxData(&gTransData);
            PrintReceipt();

            ShowMessage2line(gTransTitle, "交易完成!!", "", Type_RemoveCard);
            Process_SendAdvice3(0);
        } else {
            usRet = ECC_CheckReaderResponseCode(iret);
        }
    } while (iret == 0x6088);

    CheckMemoarystatus();
    return usRet;
}

USHORT Trans_SetValue(void) {
    USHORT usRet;
    int iret;
    long ev;



    sprintf(gTransTitle, "展期");

    USHORT ret = ShowMessage2line(gTransTitle, "是否進行卡片有效期展期?", "請確認!", Type_ComformOK);
    if (ret != d_OK) {
        return ret;
    }

    if ((usRet = checkTxnLimit() != d_OK))
        return usRet;



    usInitTxData(TXTYPE_SETVALUE);


    do {

        // gTransData.ulTMTxnSN=0;
        iret = inPPR_SetValue();
        if (iret == 0x6415 || iret == 0x9000) {
            if (iret == 0x6415) {
                gTransData.ucTXSTATUS = TransStatus_REQ;

                gSaveReversalflag = 1;
                usRet = Process_TransComm2(&gTransData, 1);
                ECC_CheckAPResponseCode(usRet);
                if (usRet != d_OK) return usRet;
                ShowStatusLine("已完成");

                usRet = ECC_CheckCMASResponseCode(gTransData.ucResponseCode);
                if (usRet != d_OK) {
                    remove(ReversalFile);
                    return usRet;
                }
            }

            iret = inPPR_AuthSetValue();
            if (iret == 0x6088 || iret == 0x9969 || iret == 0x9968) {
                ShowMessage2line(gTransTitle, "交易未完成", "請放回卡片", Type_ComformNONE);
                iret = iProcess_ReadCardBasicData();
                continue;
            }
            usRet = ECC_CheckReaderResponseCode(iret);
            if (usRet != d_OK) return usRet;


            remove(ReversalFile);
            gTransData.ucTXSTATUS = TransStatus_ADVREQ;
            usSaveTxData(&gTransData);
            PrintReceipt();

            ShowMessage2line(gTransTitle, "交易完成!!", "", Type_RemoveCard);
            Process_SendAdvice3(0);
        } else {
            usRet = ECC_CheckReaderResponseCode(iret);
        }
    } while (iret == 0x6088);

    CheckMemoarystatus();
    return usRet;
}

USHORT checkTxnLimit() {


    USHORT usRet;
    if (gBatchTotal.TotleCnt >= gBATCHTXLIMIT) {
        usRet = d_ERR_BATCH_LIMIT_SETTLE_FIRST;
        ECC_CheckAPResponseCode(usRet);
        return usRet;
    }

    //add by bruce 20140905 6608不允許再作交易
    if (gConfig.DEVICE.READER.bREADERSTATUS == READERSTATUS_LOCK) {
        usRet = d_ERR_READER_6608;
        ECC_CheckReaderResponseCode(usRet);
        return usRet;
    }

    if (File_exist(SettleFile) == d_OK) {
        usRet = d_ERR_PRE_SETTLE_FAIL_TRY_AGAIN;
        ECC_CheckAPResponseCode(usRet);
        return usRet;
    }


    USHORT TotalCount;
    TotalCount = CheckUnuploadTxCount();
    if (TotalCount > gFORCEONLINELIMIT) {
        usRet = d_ERR_BATCHNOTEMPTY;
        ECC_CheckAPResponseCode(usRet);
        return usRet;
    }

    return d_OK;
}

