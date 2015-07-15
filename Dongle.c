

#include <ctosapi.h>
#include "gvar.h"
#include "sysinfo.h"
#include "menu.h"
#include "wub_lib.h"
#include "comm.h"
#include "ezxml.h"
#include "Dongle.h"
#include "Apdu.h"
#include "Function.h"
#include "trans.h"
#include "Com.h"
#include "ECCAPP.h"
typedef struct {
	const char* file;
	int fd;
} interface_t;


char trans_name_[50];
//const char* trans_name_ = 0;
char working_file_[128] = { 0 };
int tm_out_size_ = 0;
int ret_ = AP_FAILURE;
BYTE tm_out_[2048];
//int fd_ = DEFAULT_LOG_FILENO;

int inCMD_STATUS = Status_START;//1.0.5.6
BYTE  cInputData[256];	//input pArguments data
char gCurrentFolder[100];
char gBlcFileFolder[100];
char gInputPath[100];
/*
BYTE   bTMInputData[TXN_INPUT_DATA_LEN];
//BYTE   cAPDU[256]; //APDU COMMAND DATA
BYTE   cAPDU[300];
BYTE   cOutputData[300]; //output data
BYTE   cAPDUHeader[5]; //CLA INS P1 P2
int inInputLen,inLC,inLE;//LC LE
int iTxnTimeout;
*/
Store_Data stStore_DataInfo_t;
BYTE gsBlackListVersion[30];
//TxnReqOnline_APDU_Out srTxnReqOnlineOut;
/*
#define d_ERR_RESP_LOCKCARD     9699 
#define d_ERR_RESP_REJECT       9698    
#define d_ERR_RESP_ABORT        9697
#define d_ERR_RESP_REBOOT       9696
#define d_ERR_RESP_SECURTERR    9695
#define d_ERR_RESP_SIGNON       9694*/


USHORT ResetDongle()
{
      //add by bruce 20140905 6608不允許再作交易
    if(gConfig.DEVICE.READER.bREADERSTATUS==READERSTATUS_LOCK){
          MessageBox(gTransTitle,"讀卡機故障6608","","無法進行交易","請報修!!",d_MB_CHECK);
      //return 0x6088;//2014.12.08, kobe modified 6088 to 6608         
          return 0x6608; 
     }
    int  iret=inPPR_Reset(1); 
    USHORT ret=ECC_CheckReaderResponseCode(iret);	        
    if(ret!=d_OK){    
        return ret; 
    }   
    UpdateSystemInfo();
    return d_OK;
}
USHORT CheckReaderResponseCode(USHORT Respcode)
{
  
    SystemLog("CheckReaderResponseCode","Start");
    USHORT ret;
   
    char str[10],line1[64],line2[64],line3[64],line4[64];
    const char *actionstr, *numstr;
    char *msgstr1,*msgstr2,*msgstr3;
    memset(str,0x00,sizeof(str));
    memset(line1,0x00,sizeof(line1));
    memset(line2,0x00,sizeof(line2));
    memset(line3,0x00,sizeof(line3));
    char tmp[10];
    memset(tmp,0x00,sizeof(tmp));
   sprintf(tmp,"CODE%02x",Respcode);
    vdToUpper(str,tmp);
    
     
   // ezxml_t ResponseCode;
     ezxml_t   ReaderResponseCode=LoadXMLFile(ResponseCodeFile);
   /*  ezxml_t ResponseCode = ezxml_parse_file(ResponseCodeFile);
    if(ResponseCode ==NULL){
        SystemLog("LoadXMLFile","ezxml_parse_file FAIL. ");
       return NULL;
    }*/
 
    ezxml_t codeNode= ezxml_get(ReaderResponseCode,"READER", 0,str,-1);
    if(codeNode ==NULL){
            SystemLog("CheckResponseCode","XML Get RESPONSE CODE FAIL.");
            SystemLog("UNDEFINEDRESPOSECODE",str);
          
            sprintf(line4,"錯誤代碼:%s",str);
            ErrorMessageBox("錯誤訊息","未定義之錯誤代碼","","",line4,d_MB_CHECK);
            //2014.04.28, kobe added it for POS to display errorMeg
            if(ecrObj.gData.isEcrTxn)
            {
                if(strlen(ecrObj.ngData->errMsg)==0)
                        sprintf(ecrObj.ngData->errMsg,"未定義之錯誤代碼");
            }
           ezxml_free(ReaderResponseCode);
           return Respcode;
    }
 
  
    actionstr=ezxml_attr(codeNode, "action");
    if(strcmp(actionstr,"OK")==0)
    {   
         // Reader_FINISHED_LED();
        USHORT mkHWSupport=Eth_CheckDeviceSupport();
        if(( mkHWSupport & d_MK_HW_CONTACTLESS)==d_MK_HW_CONTACTLESS)
        {   
           CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
        }
          ezxml_free(ReaderResponseCode); 
        return d_OK;
    }
    else if(strcmp(actionstr,"REBOOT")==0){
        
        ret=d_ERR_RESP_REBOOT;
    }else if(strcmp(actionstr,"REJECT")==0){ 
         Reader_ERR_LED();
         ret=d_ERR_RESP_REJECT;
     }else if(strcmp(actionstr,"LOCKCARD")==0){   
         Reader_ERR_LED();
         ret=d_ERR_RESP_LOCKCARD;
     }else if(strcmp(actionstr,"SECURTERR")==0){
        Reader_ERR_LED();
         ret=d_ERR_RESP_SECURTERR;   
     }else if(strcmp(actionstr,"SECURTERR2")==0){ 
      //   gConfig.DEVICE.READER.bREADERSTATUS=READERSTATUS_LOCK;
     //    Config_SetData();
        Reader_ERR_LED();
         ret=d_ERR_RESP_SECURTERR;   
     }else if(strcmp(actionstr,"SIGNON")==0){    
         ret=d_ERR_RESP_SIGNON;       
    }else{ //ABORT or other
        Reader_ERR_LED();
          ret=d_ERR_RESP_ABORT;
    }
       
    ezxml_t ErrSTR1= ezxml_get(ReaderResponseCode,"READER", 0,str,0,"STRING1",-1);
   
    if(ErrSTR1!=NULL){
        msgstr1=ezxml_txt(ErrSTR1);  sprintf(line1,"%s",msgstr1); 
    }
       
   ezxml_t ErrSTR2= ezxml_get(ReaderResponseCode,"READER", 0,str,0,"STRING2",-1);
   if(ErrSTR2!=NULL){
        msgstr2=ezxml_txt(ErrSTR2); sprintf(line2,"%s",msgstr2); 
   }
  
   ezxml_t ErrSTR3= ezxml_get(ReaderResponseCode,"READER", 0,str,0,"STRING3",-1);
   if(ErrSTR3!=NULL){
        msgstr3=ezxml_txt(ErrSTR3); sprintf(line3,"%s",msgstr3); 
   }
   

  
            
    numstr=ezxml_attr(codeNode, "num");
    sprintf(line4,"錯誤代碼:%s",numstr);
    
    ErrorMessageBox("錯誤訊息",line1,line2,line3,line4,d_MB_CHECK);
  //  ezxml_free(ErrSTR3); ezxml_free(ErrSTR2); ezxml_free(ErrSTR1); ezxml_free(codeNode);
    ezxml_free(ReaderResponseCode);
  
    //2014.04.28, kobe added it for POS to display errorMeg    
   if(ecrObj.gData.isEcrTxn)
   {
       if(strlen(ecrObj.ngData->errMsg)==0)                
           sprintf(ecrObj.ngData->errMsg,"%s!%s!%s!%s",line1,line2,line3,line4);
   }
   return Respcode;
}
int inPPR_Reset(BYTE ONLINEFLAG)
{
    
       SystemLog("inPPR_Reset","Start");
        int  inRetVal,inSendLen,inReceLen;
        inCMD_STATUS=Status_RESET;
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
        if(ONLINEFLAG)
                memcpy(cAPDUHeader,"\x80\x01\x00\x00",4);//online
        else
                memcpy(cAPDUHeader,"\x80\x01\x00\x01",4); //offline
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(Reset_APDU_In);
	inLE = sizeof(Reset_APDU_Out) - 2;
	
	inSendLen  = inReaderCommand(inCMD_STATUS);
        tTxnTimeout = DEFAULT_TIMEOUT;
    
#ifdef TESTMODE  
   inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_Reset",sizeof(Reset_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else   
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
	inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000)
            inBuildResetOutput_2(inCMD_STATUS,(TRANS_DATA2 *)&gTransData,(Reset_APDU_In *)&cAPDU[IN_DATA_OFFSET],(Reset_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
      
	return(inRetVal);
}

int inPPR_SignOn()
{
   
      SystemLog("inPPR_SignOn","Start");
	int  inRetVal,inSendLen,inReceLen;

	//TRACE_("inPPR_SignOn()");
	inCMD_STATUS=Status_SIGNON;
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x02\x00\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(SignOn_APDU_In);
	inLE = sizeof(SignOn_APDU_Out) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_SignOn",sizeof(SignOn_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else   
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
        if(inRetVal == 0x9000)
		inBuildSignOnOutput_2(inCMD_STATUS,(TRANS_DATA2 *)&gTransData,(SignOn_APDU_In *)&cAPDU[IN_DATA_OFFSET],(SignOn_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);

	//	*inOutLen = inBuildSignOnData(inAPIStatus,(SignOn_TM_Out *)lpOutData,(SignOn_APDU_In *)&cAPDU[IN_DATA_OFFSET],(SignOn_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
 

   
	return(inRetVal);
}

int inPPR_SignOnQuery()
{
 
     SystemLog("inPPR_SignOnQuery","Start");
        int inRetVal,inSendLen,inReceLen,ret;
	inCMD_STATUS=Status_SIGNONQUERY;
	TRACE_("inPPR_SignOnQuery()");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x03\x00\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = 0;
	inLE = sizeof(SignOnQuery_APDU_Out) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;//DEFAULT_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_SignOnQuery",sizeof(SignOnQuery_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else    
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
        ret=inRetVal;
	if(inRetVal == 0x9000 || inRetVal == 0x6304 || inRetVal == 0x6305)
        {
             inBuildSignOnQueryOutput_2(inCMD_STATUS,&gSOQ_OUT,(SignOnQuery_APDU_Out *)&cOutputData);
        }	
  
	return inRetVal;
}
int inPPR_ReadCardBasicData()
{
    SystemLog("inPPR_ReadCardBasicData","Start");
  
 BYTE tmp[32];
 ULONG t1,t2;
 t1  = CTOS_TickGet();    
        int inRetVal,inSendLen,inReceLen;
        inCMD_STATUS=Status_READCARDBASICDATA;
	//TRACE_("inPPR_ReadCardBasicData()");
	memset(&gBasicData,0x00,sizeof(ReadCardBasicData_APDU_Out));
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x51\x04\x00",4);
	//inInputLen = inGetTMInDataLen(inAPIStatus);
	inLC = sizeof(ReadCardBasicData_APDU_In);
	inLE = sizeof(ReadCardBasicData_APDU_Out) - 2;
	tTxnTimeout = SEARCH_CARD_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);

#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_ReadCardBasic",sizeof(ReadCardBasicData_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}
       
#else 
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	 if((inRetVal == 0x6103)||(inRetVal == 0x640E)||(inRetVal == 0x640F))
        {
            // inRetVal= iProcess_LogLockCardData(inRetVal);
            //todo 存鎖卡記錄
        }else if(inRetVal == 0x9000){
                memset(&gBasicData,0x00,sizeof(ReadCardBasicData_APDU_Out));
		memcpy(&gBasicData,&cOutputData[OUT_DATA_OFFSET],sizeof(ReadCardBasicData_APDU_Out));
        }
	//	*inOutLen = inBuildReadCardBasicDataOutput(inAPIStatus,(ReadCardBasicData_TM_Out *)lpOutData,(ReadCardBasicData_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);

	return(inRetVal);
}
int inPPR_TxnReqOnline()
{
    SystemLog("inPPR_TxnReqOnline","Start");
    // CTOS_PrinterPutString("PPR_TxnReqOnline");  
      int  inRetVal,inSendLen,inReceLen;
	inCMD_STATUS=Status_TXNREQONLINE;
	
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x11\x01\x00",4);

	inLC = sizeof(TxnReqOnline_APDU_In);
	inLE = sizeof(TxnReqOnline_APDU_Out) - 2;
	tTxnTimeout = SEARCH_CARD_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_TxnReqOnline",sizeof(TxnReqOnline_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else 
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif

inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if((inRetVal == 0x6103)||(inRetVal == 0x640E)||(inRetVal == 0x640F)||(inRetVal == 0x6418))
        {
             inRetVal= iProcess_LogLockCardData(inRetVal);
          
        }else if(inRetVal == 0x9000||inRetVal == 0x6415){
	
		inBuildTxnReqOnlineOutput_2(inCMD_STATUS,(TRANS_DATA2*)&gTransData,
								(TxnReqOnline_APDU_In *)&cAPDU[IN_DATA_OFFSET],
								(TxnReqOnline_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
	}

	return(inRetVal);
}

int inPPR_AuthTxnOnline()
{
     SystemLog("inPPR_AuthTxnOnline","Start");
   // CTOS_PrinterPutString("PPR_AuthTxnOnline");  
	int  inRetVal,inSendLen;
	TxnReqOnline_APDU_Out srTxnReqOut;
	USHORT inReceLen;
	inCMD_STATUS=Status_AUTHTXNONLINE;
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x11\x02\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);

	inLC = sizeof(AuthTxnOnline_APDU_In);
	inLE = sizeof(AuthTxnOnline_APDU_Out) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_AuthTxnOnline",sizeof(AuthTxnOnline_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else   
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000)
	{
		//vdLoadReqData(TXN_REQ_DATA,(BYTE *)&srTxnReqOut,sizeof(TxnReqOnline_APDU_Out));
		inBuildAuthTxnOnlineOutput_2(inCMD_STATUS,(TRANS_DATA2*)&gTransData,
								(AuthTxnOnline_APDU_In *)&cAPDU[IN_DATA_OFFSET],
								(AuthTxnOnline_APDU_Out *)&cOutputData[OUT_DATA_OFFSET],&srTxnReqOut);
	}

	return(inRetVal);
}

int inPPR_TxnReqOffline( )
{
      SystemLog("inPPR_TxnReqOffline","Start");
     // CTOS_PrinterPutString("PPR_TxnReqOffline");  
	int inRetVal,inSendLen,inReceLen;
	BYTE ucTxnDateTime[4];
	USHORT usReceLen;
	inCMD_STATUS=Status_TXNREQOFFLINE;
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x32\x01\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(TxnReqOffline_APDU_In);
	inLE = sizeof(TxnReqOffline_APDU_Out) - 2;
	tTxnTimeout = SEARCH_CARD_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_TxnReqOffline",sizeof(TxnReqOffline_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else   
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
        if((inRetVal == 0x6103)||(inRetVal == 0x640E)||(inRetVal == 0x640F)|| (inRetVal == 0x6418))
      {
             inRetVal= iProcess_LogLockCardData(inRetVal);
          
      }else if(inRetVal == 0x9000||inRetVal == 0x6415){
		//vdSaveReqData(TXN_REQ_DATA,(BYTE *)&cOutputData[OUT_DATA_OFFSET],sizeof(TxnReqOffline_APDU_Out));
		 BuildTxnReqOfflineOutput_2(inCMD_STATUS,&gTransData,(TxnReqOffline_APDU_In *)&cAPDU[IN_DATA_OFFSET],(TxnReqOffline_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
      }
      return(inRetVal);
}

int inPPR_AuthTxnOffline()
{
     SystemLog("inPPR_AuthTxnOffline","Start");
  //   CTOS_PrinterPutString("PPR_AuthTxnOffline");  
int inRetVal,inSendLen,inReceLen;
//TxnReqOffline_APDU_Out srTxnReqOut;
USHORT usReceLen;

        inCMD_STATUS=Status_AUTHTXNOFFLINE;
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x32\x02\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(AuthTxnOffline_APDU_In);
	inLE = sizeof(AuthTxnOffline_APDU_Out) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;
    
	inSendLen  = inReaderCommand(inCMD_STATUS);

#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_AuthTxnOffline",sizeof(AuthTxnOffline_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else   
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif

        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000)
	{ 
		//vdLoadReqData(TXN_REQ_DATA,(BYTE *)&srTxnReqOut,sizeof(TxnReqOffline_APDU_Out));

                inBuildAuthTxnOfflineOutPut_2(inCMD_STATUS,&gTransData,(AuthTxnOffline_APDU_In *)&cAPDU[IN_DATA_OFFSET],(AuthTxnOffline_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);//,&srTxnReqOut
	}

	return(inRetVal);
}

int inPPR_LockCard()
{
     SystemLog("inPPR_LockCard","Start");
int inRetVal,inSendLen,inReceLen;
USHORT usReceLen;
	TRACE_("inPPR_LockCard()");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x41\x01\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(LockCard_APDU_In_2);
	inLE = sizeof(LockCard_APDU_Out_2) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_LockCard",sizeof(LockCard_APDU_Out_2));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else   
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000)
	{
	//	vdLoadReqData(TXN_INPUT_DATA,bTMInputData,TXN_INPUT_DATA_LEN);
		 inBuildLockCardDataOutput1_2((TRANS_DATA2 *)&gTransData,
                         (LockCard_APDU_Out_2 *)&cOutputData[OUT_DATA_OFFSET],
                         0x03);
	}

	return(inRetVal);
}

int inPPR_ReadDongleDeduct(BYTE *lpOutData,int *inOutLen)
{
      SystemLog("inPPR_ReadDongleDeduct","Start");
int  inRetVal,inSendLen;
USHORT inReceLen;
	TRACE_("inPPR_ReadDongleDeduct()");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x51\x05\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(ReadDongleDeduct_APDU_In);
	inLE = sizeof(ReadDongleDeduct_APDU_Out) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_ReadDongleDeduct",sizeof(ReadDongleDeduct_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else 
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000)
	{
		inBuildReadDongleDeductData(inCMD_STATUS,(ReadDongleDeduct_TM_Out *)lpOutData,(ReadDongleDeduct_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
	}

	return(inRetVal);
}



int inPPR_ReadCardDeduct(BYTE *lpOutData,int *inOutLen)
{
int  inRetVal,inSendLen,inReceLen;
 SystemLog("inPPR_ReadCardDeduct","Start");
	TRACE_("inPPR_ReadCardDeduct()");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x51\x06\x01",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(ReadCardDeduct_APDU_In);
	inLE = sizeof(ReadCardDeduct_APDU_Out) - 2;
	tTxnTimeout = SEARCH_CARD_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_ReadCardDeduct",sizeof(ReadCardDeduct_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000)
		inBuildReadCardDeductData(Status_READCARDDEDUCT,(ReadCardDeduct_TM_Out *)lpOutData,(ReadCardDeduct_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);

	return(inRetVal);
}

int inPPR_ReadCodeVersion(BYTE *lpOutData,int *inOutLen)
{
int  inRetVal,inSendLen,inReceLen;
 SystemLog("inPPR_ReadCodeVersion","Start");
	TRACE_("inPPR_ReadCodeVersion()");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x51\x01\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = 0x00;
	inLE = sizeof(ReadCodeVersion_APDU_Out) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_ReadCodeVersion",sizeof(ReadCodeVersion_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
	inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000)
		*inOutLen = inBuildReadCodeVersionData(Status_READCODEVERSION,(ReadCodeVersion_TM_Out *)lpOutData,(ReadCodeVersion_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);

	return(inRetVal);
}

int inPR_Reboot(BYTE *lpOutData,int *inOutLen)
{
int  inRetVal,inSendLen,inReceLen;

	 SystemLog("inPR_Reboot","Start");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x86\x01\x00\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = 0x00;
	inLE = sizeof(Reboot_APDU_Out) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
 
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PR_Reboot",0);
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	return(inRetVal);
}



int inPPR_SetValue()
{
int inRetVal,inSendLen,inReceLen;
BYTE ucTxnDateTime[4];

	 SystemLog("inPPR_SetValue","Start");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x31\x01\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(SetValue2_APDU_In);
	inLE = sizeof(SetValue2_APDU_Out) - 2;
	tTxnTimeout = SEARCH_CARD_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_SetValue",sizeof(SetValue2_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        
        
      inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
      if((inRetVal == 0x6103)||(inRetVal == 0x640E)||(inRetVal == 0x640F)|| (inRetVal == 0x6418))
      {
             inRetVal= iProcess_LogLockCardData(inRetVal);
          
      }else if(inRetVal == 0x9000||inRetVal == 0x6415){
		//vdSaveReqData(TXN_REQ_DATA,(BYTE *)&cOutputData[OUT_DATA_OFFSET],sizeof(TxnReqOffline_APDU_Out));
		 BuildTxnReqOfflineOutput_2(inCMD_STATUS,&gTransData,(TxnReqOffline_APDU_In *)&cAPDU[IN_DATA_OFFSET],(TxnReqOffline_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
                inBuildSetValueData_2((TRANS_DATA2 *)&gTransData,(SetValue_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
      }

	return(inRetVal);
}

int inPPR_AuthSetValue()
{
int inRetVal,inSendLen,inReceLen;
SetValue2_APDU_Out srTxnReqOut;

	 SystemLog("inPPR_AuthSetValue","Start");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x31\x02\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(AuthSetValue2_APDU_In);
	inLE = sizeof(AuthSetValue2_APDU_Out) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_AuthSetValue",sizeof(AuthSetValue2_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000)
	{
		inBuildAuthSetValueData_2((TRANS_DATA2 *)&gTransData,(AuthSetValue_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
	}

	return(inRetVal);
}


int inPPR_AutoloadEnable(BYTE *lpOutData,int *inOutLen)
{
int  inRetVal,inSendLen,inReceLen;

	 SystemLog("inPPR_AutoloadEnable","Start");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x11\x01\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(TxnReqOnline_APDU_In);
	inLE = sizeof(TxnReqOnline_APDU_Out) - 2;
	tTxnTimeout = SEARCH_CARD_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_AutoloadEnable",sizeof(TxnReqOnline_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x6103)
	{
		BYTE ucLockReason = 0x02;
		//vdLoadReqData(TXN_INPUT_DATA,bTMInputData,TXN_INPUT_DATA_LEN);
		//因為TxnReqOnline_TM_In會等於AutoloadEnable2_TM_In,因此沿用inBuildLockCardData1()
		*inOutLen = inBuildLockCardData1(inCMD_STATUS,(LockCard_TM_Out_2 *)lpOutData,(LockCard_APDU_Out_2 *)&cOutputData[OUT_DATA_OFFSET],((TxnReqOnline_APDU_In *)&cAPDU[IN_DATA_OFFSET])->ucTxnDateTime,ucLockReason,((TxnReqOnline_TM_In *)bTMInputData)->ucTMLocationID,((TxnReqOnline_TM_In *)bTMInputData)->ucTMID);
	}
	else if(inRetVal == 0x640E || inRetVal == 0x610F || inRetVal == 0x6418)
	{
		BYTE ucLockReason = inRetVal % 256;
		//vdLoadReqData(TXN_INPUT_DATA,bTMInputData,TXN_INPUT_DATA_LEN);
		//因為TxnReqOnline_TM_In會等於AutoloadEnable2_TM_In,因此沿用inBuildLockCardData2()
		*inOutLen = inBuildLockCardData2(inCMD_STATUS,(LockCard_TM_Out_2 *)lpOutData,(LockCard_APDU_Out_3 *)&cOutputData[OUT_DATA_OFFSET],((TxnReqOnline_APDU_In *)&cAPDU[IN_DATA_OFFSET])->ucTxnDateTime,ucLockReason,((TxnReqOnline_TM_In *)bTMInputData)->ucTMLocationID,((TxnReqOnline_TM_In *)bTMInputData)->ucTMID);
	}
	else if(inRetVal == 0x9000)
	{
		vdSaveReqData(TXN_REQ_DATA,(BYTE *)&cOutputData[OUT_DATA_OFFSET],sizeof(TxnReqOnline_APDU_Out));
		*inOutLen = inBuildTxnReqOnlineData1(inCMD_STATUS,(TxnReqOnline_TM_Out_1 *)lpOutData,(TxnReqOnline_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
	}
	else if(inRetVal == 0x6415)
	{
		vdSaveReqData(TXN_REQ_DATA,(BYTE *)&cOutputData[OUT_DATA_OFFSET],sizeof(TxnReqOnline_APDU_Out));
		*inOutLen = inBuildAutoloadEnableData2(inCMD_STATUS,(AutoloadEnable2_TM_Out *)lpOutData,(TxnReqOnline_APDU_In *)&cAPDU[IN_DATA_OFFSET],(TxnReqOnline_APDU_Out *)&cOutputData[OUT_DATA_OFFSET]);
	}

	return(inRetVal);
}

int inPPR_AuthAutoloadEnable(BYTE *lpOutData,int *inOutLen)
{
int inRetVal,inSendLen,inReceLen;
TxnReqOnline_APDU_Out srTxnReqOut;

	 SystemLog("inPPR_AuthAutoloadEnable","Start");
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x11\x02\x00",4);
	inInputLen = inGetTMInDataLen(inCMD_STATUS);
	inLC = sizeof(AuthTxnOnline_APDU_In);
	inLE = sizeof(AuthTxnOnline_APDU_Out) - 2;
	tTxnTimeout = DEFAULT_TIMEOUT;
	inSendLen  = inReaderCommand(inCMD_STATUS);
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"PPR_AuthAutoloadEnable",sizeof(AuthTxnOnline_APDU_In));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000)
	{
		//vdLoadReqData(TXN_REQ_DATA,(BYTE *)&srTxnReqOut,sizeof(TxnReqOnline_APDU_Out));
		*inOutLen = inBuildAuthAutoloadEnableData2(inCMD_STATUS,(AuthAutoloadEnable2_TM_Out *)lpOutData,(AuthTxnOnline_APDU_In *)&cAPDU[IN_DATA_OFFSET],(AuthTxnOnline_APDU_Out *)&cOutputData[OUT_DATA_OFFSET],&srTxnReqOut);
	}

	return(inRetVal);
}

int inPPR_ReadCardNumber()
{
        int inRetVal,inSendLen,inReceLen;
        inCMD_STATUS=Status_ReadCardNumber;
	 SystemLog("inPPR_ReadCardNumber","Start");
	memset(&gBasicData,0x00,sizeof(ReadCardBasicData_APDU_Out));
	memset(cAPDUHeader,0x00,sizeof(cAPDUHeader));
	memcpy(cAPDUHeader,"\x80\x51\x02\x02",4);
	//inInputLen = inGetTMInDataLen(inAPIStatus);
	inLC = 0x04;
	inLE = 0x09;
	tTxnTimeout = DEFAULT_TIMEOUT;
     
	inSendLen  = inReaderCommand(inCMD_STATUS);

#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"inPPR_ReadCardNumber",sizeof(ReadCardNumber_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else 
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
     
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000){
                memcpy(&gCardNumberInfo,&cOutputData,sizeof(ReadCardNumber_APDU_Out));
              //  inOutLen=sizeof(ReadCardNumber_APDU_Out);
        }
     
	return(inRetVal);
}

int inPPR_ReadCardNumber2()
{
        int inRetVal,inSendLen,inReceLen;
        inCMD_STATUS=Status_ReadCardNumber;
	inLC = 0x04;
	inLE = 0x09;
	tTxnTimeout = DEFAULT_TIMEOUT;
        
        int inCnt = 3;
        memset(cAPDU,0,sizeof(cAPDU));
	memcpy(&cAPDU[inCnt],"\x80\x51\x02\x02",4);
	inCnt += 4;
	
	cAPDU[inCnt++] = inLC;//Lc
      
        memset(&cAPDU[inCnt],0x00,sizeof(3));
        inCnt+=3;
        cAPDU[inCnt++]=0x00;
        cAPDU[inCnt++] = inLE;//Le
		
	cAPDU[2] = inCnt - 3;//LEN
	cAPDU[inCnt++] = checksum(inCnt,cAPDU);//EDC
	//inSendLen  = inReaderCommand(inCMD_STATUS);
inSendLen=inCnt;
#ifdef TESTMODE  
        inRetVal = inTSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout,"inPPR_ReadCardNumber",sizeof(ReadCardNumber_APDU_Out));
	if(inRetVal != SUCCESS){
		return inRetVal;
	}

#else 
	inRetVal = inSendRecvAPDU(cAPDU,inSendLen,cOutputData,(int *)&inReceLen,tTxnTimeout);
	if(inRetVal != SUCCESS){
		return inRetVal;
        }
#endif
     
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	if(inRetVal == 0x9000){
                memcpy(&gCardNumberInfo,&cOutputData,sizeof(ReadCardNumber_APDU_Out));
              //  inOutLen=sizeof(ReadCardNumber_APDU_Out);
        }
     
	return(inRetVal);
}