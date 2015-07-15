
#include "ECCAPP.h"

  ezxml_t Tag, node2,node3,node4, node5,node6,node7,node8,node9,node10,node11,node12,node13,node14,node15;
USHORT CheckDeviceID(BYTE * DeviceID)
{
     BYTE buf[6];BYTE *tmpstr;	
     memset(buf,0x00,sizeof(buf));
     BYTE zero[6]={0x00,0x00,0x00,0x00,0x00,0x00};
   USHORT ret= GetBatchTotal_DevID((BYTE *)&buf);    
    if(ret!=d_OK) return ret;
   if(memcmp(buf,zero,6)==0)
   {
     usSetCurrBatchDevID2((BYTE *)&gTransData.ucCPUDeviceID);  
     GetBatchTotal_DevID((BYTE *)&buf);
   }
    if(memcmp(&buf,DeviceID,6)!=0)
          return d_Fail;
    return d_OK;  
}
USHORT UpdateSystemInfo()
{
	
	BYTE ucCPUSAMID[16+1],cpudeviceid[16+1],TerminalID[16+1],newspid[8+1],ReaderSN[8+1],deviceid[8+1],ReaderFWVersion[12+1],SAMID[16+1];	
	BYTE *buf;
	BYTE *tmpstr;	
        int result;
	
      
        memset(cpudeviceid,0x00,sizeof(cpudeviceid));
        wub_hex_2_str((char *)&gTransData.ucCPUDeviceID, (char *)&cpudeviceid, sizeof(gTransData.ucCPUDeviceID)); 
        USHORT usRet= GetBatchTotal(); 
         usRet =CheckDeviceID((BYTE *)&gTransData.ucCPUDeviceID);
        if(usRet!=d_OK){ 
              usRet=ShowMessage3line("系統檢查","請注意!!","讀卡機已變更!!","資料將重新設定。",TYPE_ECR_FORCE_TO_CONFIRM_0);
              if(usRet!=d_OK) return ;
              BYTE buff[10+1];
              memset(buff,0x00,sizeof(buff));
              if((result= ShowInputBox("","請輸入密碼",  buff,10,INPUT_TYPE_Number,'*')) != d_OK)
                  return result;
              //if(result != d_OK) return result;
              if(strcmp(buff,"70765909")!= 0){
                     usRet=ShowMessage3line("系統檢查","密碼錯誤，請注意!!","非設備維護人員","請勿任意變更設備。",TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);
                     return ;
              }
              usRet=ShowMessage3line("系統檢查","請注意!!","","資料將重新設定。",TYPE_ECR_FORCE_TO_CONFIRM_0);
              USHORT TXCount=CheckBatchCount();
              if(TXCount>0){
                       ECC_CheckAPResponseCode(d_ERR_BATCHNOTEMPTY);
                       usRet= Process_Settle();
                       if(usRet!=d_OK) return usRet;
              }
             SystemReset(); 
            
           
	}  
       
        //ret= ECC_SetXMLTag3(ConfigFile, "DEVICE","READER","CPU","CPUDEVICEID",cpudeviceid);
        wub_hex_2_str(gTransData.ucReaderFWVersion,ReaderFWVersion,sizeof(gTransData.ucReaderFWVersion));
        
        sprintf((BYTE *)&gConfig.DEVICE.READER.CPU.CPUDEVICEID,"%s",cpudeviceid);
        
        wub_hex_2_str(gTransData.ucDeviceID,deviceid,sizeof(gTransData.ucDeviceID));    
        
        sprintf((BYTE *)&gConfig.DEVICE.READER.MIFARE_DEVICEID,"%s",deviceid);
        
        wub_hex_2_str(gTransData.ucReaderSN,ReaderSN,sizeof(gTransData.ucReaderSN));
        
        sprintf(gConfig.DEVICE.READER.bREADERID,"%s",ReaderSN);
        
        wub_hex_2_str(gTransData.ucReaderFWVersion,ReaderFWVersion,sizeof(gTransData.ucReaderFWVersion));
        
        sprintf(gConfig.DEVICE.READER.bREADERFWVER,"%s",ReaderFWVersion);
        
        sprintf(gConfig.DEVICE.READER.MIFARE_SAMID,"%s",gTransData.ucSAMID);
        
        sprintf(gConfig.DEVICE.READER.CPU.SAMID,"%s",gTransData.ucCPUSAMID);
        
        //usRet=Config_SetData();
	usRet=GetDEVICEInfo();
        return d_OK;
}
long BYTE3Data2LONG(BYTE * data)
{
	long DestLong;
        memset(&DestLong,0x00,4);
        if(data[2] >= 0x80)
		memset(&DestLong,0xFF,sizeof(long));
	memcpy((BYTE *)&DestLong,data,3);
	return DestLong;
}

int inBuildResetOutput_2(int inTxnType,TRANS_DATA2 *Trans, Reset_APDU_In *DongleIn, Reset_APDU_Out *DongleOut)
{
	int inTMOutLen;
        USHORT ret;
//	Store_Data stStore_DataInfo_t;
        TermHost_t stTermHostInfo_t;

	TermPara_t stTermParaInfo_t;
       // CPUSAMInfo_t  stCPUSAMInfo_t;
      // LastSingOn_t  stLastSignOnInfo_t;
	
  
  
	Trans->ucHostSpecVersionNo=DongleOut->ucHostSpecVersionNo;
	memcpy(&Trans->ucReaderSN,&DongleOut->ucReaderID,sizeof(DongleOut->ucReaderID));   
	memcpy(&Trans->ucReaderFWVersion,&DongleOut->ucReaderFWVersion,sizeof(DongleOut->ucReaderFWVersion));

       memcpy(&Trans->ucSAMID,&DongleOut->ucSAMID,sizeof(DongleOut->ucSAMID));
  	memcpy(&Trans->ucSAMSN,&DongleOut->ucSAMSN,sizeof(DongleOut->ucSAMSN));  
  	memcpy(&Trans->ucSAMCRN,&DongleOut->ucSAMCRN,sizeof(DongleOut->ucSAMCRN));  
   // DebugPrint_hex(&DongleOut->ucSAMID,sizeof(DongleOut->ucSAMID),"ucSAMID",DebugMode_TX);          
  //  DebugPrint_hex(&DongleOut->ucSAMSN,sizeof(DongleOut->ucSAMSN),"ucSAMSN",DebugMode_TX);    
  // DebugPrint_hex(&DongleOut->ucSAMCRN,sizeof(DongleOut->ucSAMCRN),"ucSAMCRN",DebugMode_TX); 
    
  	memcpy(&Trans->ucDeviceID,&DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID));
        
	Trans->ucKeyVersion=DongleOut->ucSAMKeyVersion;
       
	memcpy(&Trans->ucSTAC,&DongleOut->ucSTAC,sizeof(DongleOut->ucSTAC));
 //DebugPrint_hex(&DongleOut->ucSTAC,sizeof(DongleOut->ucSTAC),"ucSTAC",DebugMode_TX);      
	memcpy(&Trans->ucCPUSAMID,&DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID));
//DebugPrint_hex(&DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),"ucCPUSAMID",DebugMode_TX);  
   
//5364
	memcpy(&Trans->CPUSAMINFOData.ucSAMVersion,&DongleOut->ucSAMVersion,sizeof(DongleOut->ucSAMVersion));
	memcpy(&Trans->CPUSAMINFOData.ucSAMUsageControl,&DongleOut->ucSAMUsageControl,sizeof(DongleOut->ucSAMUsageControl));
	memcpy(&Trans->CPUSAMINFOData.ucSAMAdminKVN,&DongleOut->ucSAMAdminKVN,sizeof(DongleOut->ucSAMAdminKVN));
	memcpy(&Trans->CPUSAMINFOData.ucSAMIssuerKVN,&DongleOut->ucSAMIssuerKVN,sizeof(DongleOut->ucSAMIssuerKVN));
	memcpy(&Trans->CPUSAMINFOData.ucTagListTable,&DongleOut->ucTagListTable,sizeof(DongleOut->ucTagListTable));
	
	memcpy(&Trans->CPUSAMINFOData.ucSAMIssuerSpecData,&DongleOut->ucSAMIssuerSpecData,sizeof(DongleOut->ucSAMIssuerSpecData));
//5365
	memcpy(&Trans->SAMtransInfoData.ucAuthCreditLimit,&DongleOut->ucAuthCreditLimit,sizeof(DongleOut->ucAuthCreditLimit));

	memcpy(&Trans->SAMtransInfoData.ucAuthCreditBalance,&DongleOut->ucAuthCreditBalance,sizeof(DongleOut->ucAuthCreditBalance));

	memcpy(&Trans->SAMtransInfoData.ucAuthCreditCumulative,&DongleOut->ucAuthCreditCumulative,sizeof(DongleOut->ucAuthCreditCumulative));
//DebugPrint_hex(&DongleOut->ucAuthCreditCumulative,sizeof(DongleOut->ucAuthCreditCumulative),"ucAuthCreditCumulative");  
	memcpy(&Trans->SAMtransInfoData.ucAuthCancelCreditCumulative,&DongleOut->ucAuthCancelCreditCumulative,sizeof(DongleOut->ucAuthCancelCreditCumulative));
//5366	
	memcpy(&Trans->ucSingleCreditTxnAmtLimit,&DongleOut->ucSingleCreditTxnAmtLimit,sizeof(DongleOut->ucSingleCreditTxnAmtLimit));
//DebugPrint_hex(&DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),"ucCPUDeviceID");  
	memcpy(&Trans->ucCPUDeviceID,&DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID));
        memcpy(&Trans->ucSTC,&DongleOut->ucSTC,sizeof(DongleOut->ucSTC));
//DebugPrint_hex(&Trans->ucSTC,sizeof(Trans->ucSTC),"ucSTC",DebugMode_TX);    
	memcpy(&Trans->ucRSAM,&DongleOut->ucRSAM,sizeof(DongleOut->ucRSAM));
//DebugPrint_hex(&DongleOut->ucRSAM,sizeof(DongleOut->ucRSAM),"ucRSAM",DebugMode_TX);          
	memcpy(&Trans->ucRHOST,&DongleOut->ucRHOST,sizeof(DongleOut->ucRHOST));
//DebugPrint_hex(&DongleOut->ucRHOST,sizeof(DongleOut->ucRHOST),"ucRHOST");          
	memcpy(&Trans->ucSATOKEN,&DongleOut->ucSATOKEN,sizeof(DongleOut->ucSATOKEN));
//DebugPrint_hex(&DongleOut->ucSATOKEN,sizeof(DongleOut->ucSATOKEN),"ucSATOKEN",DebugMode_TX);            
 //5369
 	Trans->ucSAMSignOnControlFlag = DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag4 |
					(DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag5<<4);
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////       
 //  TAG 6002 
        memset(&stTermHostInfo_t,0x00,sizeof(stTermHostInfo_t));
        memcpy(stTermHostInfo_t.ucOneDayQuota,DongleOut->stSAMParameterInfo_t.ucOneDayQuota,sizeof(Trans->stTermHostInfo_t.ucOneDayQuota));//One Day Quota
        stTermHostInfo_t.ucOneDayQuotaFlag = DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag0 |
						    (DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag1 << 4);//One Day Quota Flag
	stTermHostInfo_t.ucOnceQuotaFlag = DongleOut->stSAMParameterInfo_t.bOnceQuotaFlag2;//Once Quota Flag
	memcpy(stTermHostInfo_t.ucOnceQuota,DongleOut->stSAMParameterInfo_t.ucOnceQuota,sizeof(Trans->stTermHostInfo_t.ucOnceQuota));//Once Quota
	stTermHostInfo_t.ucCheckEVFlag = DongleOut->stSAMParameterInfo_t.bCheckEVFlag6;//Check EV Flag
	stTermHostInfo_t.ucAddQuotaFlag = DongleOut->stSAMParameterInfo_t.ucAddQuotaFlag;//Add Quota Flag
	memcpy(stTermHostInfo_t.ucAddQuota,DongleOut->stSAMParameterInfo_t.ucAddQuota,sizeof(stTermHostInfo_t.ucAddQuota));//Add Quota
	stTermHostInfo_t.ucCheckDeductFlag = DongleOut->stSAMParameterInfo_t.bCheckDeductFlag3;//Check Debit Flag
	memcpy(stTermHostInfo_t.ucCheckDeductValue,DongleOut->stSAMParameterInfo_t.ucCheckDeductValue,sizeof(stTermHostInfo_t.ucCheckDeductValue));//Check Debit
	stTermHostInfo_t.ucDeductLimitFlag = DongleOut->stSAMParameterInfo_t.bDeductLimitFlag7;//Deduct Limit Flag
	
        memcpy(stTermHostInfo_t.ucAPIVersion,API_VERSION,3);//API Version 
	 stTermHostInfo_t.ucAPIVersion[3] = 0x00;
	 memcpy( &Trans->stTermHostInfo_t,&stTermHostInfo_t,sizeof(TermHost_t));
	
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
      
        
        //TAG TermHost 6003       
	//memcpy(stTermParaInfo_t.ucRemainderAddQuota,DongleOut->ucRemainderAddQuota,sizeof(stTermParaInfo_t.ucRemainderAddQuota));//Remainder Add Quota
	memcpy(stTermParaInfo_t.ucDeMAC,DongleOut->ucDeMAC,sizeof(stTermParaInfo_t.ucDeMAC));//De MAC
       memcpy(stTermParaInfo_t.ucCancelCreditQuota,DongleOut->ucCancelCreditQuota,sizeof(stTermParaInfo_t.ucCancelCreditQuota));//
       memcpy( &Trans->stTermParaInfo_t,&stTermParaInfo_t,sizeof(stTermParaInfo_t));
  //4823
	Trans->ucOneDayQuotaWrite= DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite2 |
				     (DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite3<<4);//CPU One Day Quota Write Flag 4823
	
//4824
	  Trans->ucCPDReadFlag=DongleOut->stSAMParameterInfo_t.bCPDReadFlag0| DongleOut->stSAMParameterInfo_t.bCPDReadFlag1<<4;
        
//5370
	   memcpy( &Trans->CPULastSignonInfoData,&DongleOut->stLastSignOnInfo_t,sizeof(DongleOut->stLastSignOnInfo_t));	 
//DebugPrint_hex(&DongleOut->ucSTC,sizeof(DongleOut->ucSTC),"ucSTC",DebugMode_TX);  

         
        //vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
     // memcpy(stStore_DataInfo_t.ucDeviceID,DongleOut->ucDeviceID,sizeof(stStore_DataInfo_t.ucDeviceID));//Device ID
	//memcpy(stStore_DataInfo_t.ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(stStore_DataInfo_t.ucTxnDateTime));//Txn Date Time
	//memcpy(stStore_DataInfo_t.ucCPUDeviceID,DongleOut->ucCPUDeviceID,sizeof(stStore_DataInfo_t.ucCPUDeviceID));//CPU SP ID
	//memcpy(stStore_DataInfo_t.ucSTC,DongleOut->ucSTC,sizeof(stStore_DataInfo_t.ucSTC));//CPU SAM Txn Cnt
     //   vdSaveReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));       
	
       return(ret);
}


int inBuildSignOnOutput_2(int inTxnType,TRANS_DATA2 *Trans,SignOn_APDU_In *DongleIn,SignOn_APDU_Out *DongleOut)
{
        Store_Data stStore_DataInfo_t;
    
	 //4825
	Trans->ucCPUCreditBalanceChangeFlag=DongleOut->ucCreditBalanceChangeFlag;
	
	//5365
	memcpy(&Trans->SAMtransInfoData.ucAuthCreditLimit,&DongleOut->ucAuthCreditLimit,sizeof(DongleOut->ucAuthCreditLimit));
	memcpy(&Trans->SAMtransInfoData.ucAuthCreditBalance,&DongleOut->ucAuthCreditBalance,sizeof(DongleOut->ucAuthCreditBalance));
	memcpy(&Trans->SAMtransInfoData.ucAuthCreditCumulative,&DongleOut->ucAuthCreditCumulative,sizeof(DongleOut->ucAuthCreditCumulative));
	memcpy(&Trans->SAMtransInfoData.ucAuthCancelCreditCumulative,&DongleOut->ucAuthCancelCreditCumulative,sizeof(DongleOut->ucAuthCancelCreditCumulative));
	//6406
	memcpy(&Trans->CPUTermCrypto,&DongleOut->ucCACrypto,sizeof(DongleOut->ucCACrypto));

	   
	//////////////////////////////////////////////////////////////////////////////////
        
    
	return(0);
}

int inBuildSignOnQueryOutput_2(int inTxnType,SignOnQuery_APDU_Out *Trans,SignOnQuery_APDU_Out *DongleOut)
{  
   
	BYTE buf[16];
       
	memset(&buf,0x00,16);
	

	ULONG RemainderAddQuota =BYTE3Data2LONG((char *)&DongleOut->ucRemainderAddQuota);
	ULONG CancelCreditQuota =BYTE3Data2LONG((char *)&DongleOut->ucCancelCreditQuota);
  	BYTE anLastTxnDateTime[14];
	fnLongToUnix((unsigned char *)&anLastTxnDateTime,(unsigned long *)DongleOut->ucLastTxnDateTime,14);//最後一次SignOn成功時間
    
        
        sprintf(gConfig.STATUS.LastSignonDateTime,"%s",anLastTxnDateTime);
        vdUIntToAsc((BYTE*)&RemainderAddQuota,4,buf,10,' ',10);
        sprintf(gConfig.DEVICE.READER.RemainderAddQuota,"%s",buf);
        vdUIntToAsc((BYTE*)&CancelCreditQuota,4,buf,10,' ',10);
        sprintf(gConfig.DEVICE.READER.CancelCreditQuota,"%s",buf);
        
       
  
        memcpy(Trans,DongleOut,sizeof(SignOnQuery_APDU_Out));
    
	return(d_OK);
}



int inBuildTxnReqOnlineOutput_2(int inTxnType,TRANS_DATA2 *Trans,TxnReqOnline_APDU_In *DongleIn,TxnReqOnline_APDU_Out *DongleOut)
{

	//4800
	Trans->ucCPUPurseVersionNUM=DongleOut->ucPurseVersionNumber;
	Trans->ucBasicData_Autoloadflag=(BYTE)DongleOut->bAutoLoad;
	Trans->lAutoloadAMT= BYTE3Data2LONG((char *)&DongleOut->ucAutoLoadAmt);
	memcpy(&Trans->ucPID,&DongleOut->ucPID,sizeof(DongleOut->ucPID));
//         DebugPrint_hex(&DongleOut->ucPID,sizeof(DongleOut->ucPID),"ucPID",DebugMode_TX);  
//5302
	Trans->ucAdminKeyKVN=DongleOut->ucCPUAdminKeyKVN;
	Trans->ucCreditKeyKVN=DongleOut->ucCreditKeyKVN;
        Trans->ucDebitKeyKVN=DongleOut->ucCPUIssuerKeyKVN;
 DebugPrint_hex(&DongleOut->ucCreditKeyKVN,sizeof(DongleOut->ucCreditKeyKVN),"ucCreditKeyKVN",DebugMode_TX);  
//5305	
	Trans->ucSigntureKeyKVN=DongleOut->ucSignatureKeyKVN;
        
//4812
	memcpy(&Trans->ucCTC,&DongleOut->ucCTC,sizeof(DongleOut->ucCTC));
//  DebugPrint_hex(&DongleOut->ucCTC,sizeof(DongleOut->ucCTC),"ucCTC",DebugMode_TX);  
//4809	
	memcpy(&Trans->ucCPUTxnMode,&DongleOut->ucTxnMode,sizeof(DongleOut->ucTxnMode));
                 DebugPrint_hex(&DongleOut->ucTxnMode,sizeof(DongleOut->ucTxnMode),"ucTxnMode",DebugMode_TX);  
//4810
	memcpy(&Trans->ucCPUTQ,&DongleOut->ucTxnQuqlifier,sizeof(DongleOut->ucTxnQuqlifier));
          DebugPrint_hex(&DongleOut->ucTxnQuqlifier,sizeof(DongleOut->ucTxnQuqlifier),"ucTxnQuqlifier",DebugMode_TX);  
//4805
	memcpy(&Trans->ucCPUSubAreaCode,&DongleOut->ucSubAreaCode,sizeof(DongleOut->ucSubAreaCode));
//1400
	memcpy(&Trans->ucCardExpiryDate,&DongleOut->ucExpiryDate,sizeof(DongleOut->ucExpiryDate));
//0408
	// Trans->lEVafterTxn =BYTE3Data2LONG((char *)&DongleOut->ucEV);
        Trans->lEVBeforeTxn =BYTE3Data2LONG((char *)&DongleOut->ucEV);
 //         DebugPrint_hex(&DongleOut->ucEV,sizeof(DongleOut->ucEV),"lEVBeforeTxn",DebugMode_TX);   
//4811 ucTxnSN
 	Trans->ulSNBeforeTxn=BYTE3Data2LONG((char *)&DongleOut->ucTxnSN);
 // DebugPrint_hex(&DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),"ucTxnSN",DebugMode_TX); 
	Trans->ucBasicData_CardType=DongleOut->ucCardType;
	Trans->ucBasicData_CardProfile=DongleOut->ucPersonalProfile;
	memcpy(&Trans->ulProfileExpiryDate,&DongleOut->ucProfileExpiryDate,sizeof(DongleOut->ucProfileExpiryDate));
	/*2014.05.08, bruce added it*/
        memcpy(&Trans->ucCardVaildDate,&DongleOut->ucProfileExpiryDate,sizeof(DongleOut->ucProfileExpiryDate));
        Trans->ucAreaCode=DongleOut->ucAreaCode;
	memcpy(&Trans->ucCardID,&DongleOut->ucCardID,sizeof(&DongleOut->ucCardID));
// DebugPrint_hex(&DongleOut->ucCardID,sizeof(DongleOut->ucCardID),"ucCardID",DebugMode_TX);   
	Trans->ucChipIDLength=DongleOut->ucCardIDLen;
	Trans->lTxnAmt=BYTE3Data2LONG((char *)&DongleOut->ucTxnAmt);
      
 //DebugPrint_hex(&DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),"ucTxnAmt",DebugMode_TX);   
	Trans->ucHostSpecVersionNo=DongleOut->ucHostSpecVersionNo;
        memcpy(&Trans->ucReaderFWVersion,&DongleOut->ucReaderFWVersion,sizeof(DongleOut->ucReaderFWVersion));
	memcpy(&Trans->ucDeviceID,&DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID));
 //DebugPrint_hex(&DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),"ucDeviceID",DebugMode_TX);  
	memcpy(&Trans->ucCPUDeviceID,&DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID));
	memcpy(&Trans->ucCPUSPID,&DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID));
	memcpy(&Trans->ucSubMerchantID,&DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID));
	
 	Trans->ulDepositValue=BYTE3Data2LONG((char *)&DongleOut->ucDeposit);
	Trans->ucIssuerCode=DongleOut->ucIssuerCode;
	Trans->ucBankCode=DongleOut->ucBankCode;
        memcpy(&Trans->usLoyaltyCounter,&DongleOut->ucLoyaltyCounter,sizeof(Trans->usLoyaltyCounter));
        
 //DebugPrint_hex(&DongleOut->ucSAMID,sizeof(DongleOut->ucSAMID),"ucSAMID",DebugMode_TX);  
//  DebugPrint_hex(&DongleOut->ucSAMSN,sizeof(DongleOut->ucSAMSN),"ucSAMSN",DebugMode_TX);  
 //  DebugPrint_hex(&DongleOut->ucSAMCRN,sizeof(DongleOut->ucSAMCRN),"ucSAMCRN",DebugMode_TX);  
	memcpy(&Trans->ucSAMID,&DongleOut->ucSAMID,sizeof(DongleOut->ucSAMID));
	memcpy(&Trans->ucSAMSN,&DongleOut->ucSAMSN,sizeof(DongleOut->ucSAMSN));
	memcpy(&Trans->ucSAMCRN,&DongleOut->ucSAMCRN,sizeof(DongleOut->ucSAMCRN));
	Trans->ucKeyVersion=DongleOut->ucSAMKVN;
 //    DebugPrint_hex(&DongleOut->ucSTAC,sizeof(DongleOut->ucSTAC),"ucSTAC",DebugMode_TX);       
	memcpy(&Trans->ucSTAC,&DongleOut->ucSTAC,sizeof(DongleOut->ucSTAC));
      //  Trans->ulTerminalInvoiceNum= wub_str_2_long(DongleOut->ucTMSerialNumber);
      //  Trans->ulTerminalInvoiceNum= wub_str_2_long(DongleOut->ucTMSerialNumber);
	//memcpy(&Trans->ulTerminalTxnSN,&DongleOut->ucTMSerialNumber,sizeof(DongleOut->ucTMSerialNumber));
	Trans->ucMsgType=DongleOut->ucMsgType;
	Trans->ucSubType=DongleOut->ucSubType;

        memcpy(&Trans->ucCPUSAMID,&DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID));
      //              DebugPrint_hex(&DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),"ucCPUSAMID",DebugMode_TX);  
	memcpy(&Trans->ucCPUHostadminKVN,&DongleOut->ucHostAdminKVN,sizeof(DongleOut->ucHostAdminKVN));
    //             DebugPrint_hex(&DongleOut->ucHostAdminKVN,sizeof(DongleOut->ucHostAdminKVN),"ucHostAdminKVN",DebugMode_TX);  
	memcpy(&Trans->CPUTermCrypto,&DongleOut->ucTxnCrypto,sizeof(DongleOut->ucTxnCrypto));
 //DebugPrint_hex(&DongleOut->ucTxnCrypto,sizeof(DongleOut->ucTxnCrypto),"ucTxnCrypto",DebugMode_TX);  
/*	CardAVR_t CardAVR;ReaderAVRTM_t ReaderAVR;
	vdBuildCardAVRData(&CardAVR,
                        &DongleOut->stLastCreditTxnLogInfo_t,
                        DongleOut->ucCardID,
                        DongleOut->ucIssuerCode,
                        DongleOut->ucCPUSPID,
                        DongleOut->ucCPULocationID,
                        DongleOut->ucPID,
                       (BYTE *) &Trans->usLoyaltyCounter);//Card AVR Info
	memcpy(&Trans->ucCardAVRDATA,&CardAVR,sizeof(CardAVR));
	
	vdBuildReaderAVRData(&ReaderAVR,&DongleOut->stReaderAVRInfo_t);//Reader AVR Info
 */
        memcpy(&Trans->ucCardAVRDATA,&DongleOut->stLastCreditTxnLogInfo_t,sizeof(DongleOut->stLastCreditTxnLogInfo_t));
	memcpy(&Trans->ReaderAVRDATA,&DongleOut->stReaderAVRInfo_t,sizeof(DongleOut->stReaderAVRInfo_t));
	/*if(Trans->ucTXTYPE==TXTYPE_VOID){
            memcpy(&Trans->ucOrgTxnTerminalID,&DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID));
            ULONG orgtxsn=wub_str_2_long(DongleOut->ucTMSerialNumber);
            sprintf(Trans->ucOrgTxnRRN,"%s%06ld",gTransData.ucTxnData, orgtxsn);
            memcpy(&Trans->ucOrgTxnDate,&Trans->ucTxnData,sizeof(Trans->ucTxnData));
          
        }*/
/*
DebugPrint_hex(&DongleOut->ucCardID,sizeof(DongleOut->ucCardID),"ucCardID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),"ucIssuerCode",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),"ucTxnSN",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),"ucTxnAmt",DebugMode_TX);
DebugPrint_hex(&DongleOut->ucEV,sizeof(DongleOut->ucEV),"ucEV",DebugMode_TX); 
DebugPrint_hex(&Trans->usLoyaltyCounter,sizeof(Trans->usLoyaltyCounter),"usLoyaltyCounter",DebugMode_TX); 

DebugPrint_hex(&DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),"ucCPUDeviceID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),"ucCPUSPID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID),"ucCPULocationID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucPID,sizeof(DongleOut->ucPID),"ucPID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucPurseVersionNumber,sizeof(DongleOut->ucPurseVersionNumber),"ucPurseVersionNumber",DebugMode_TX);
DebugPrint_hex(&DongleOut->ucSubAreaCode,sizeof(DongleOut->ucSubAreaCode),"ucSubAreaCode",DebugMode_TX);
DebugPrint_hex(&DongleOut->ucBankCode,sizeof(DongleOut->ucBankCode),"ucBankCode",DebugMode_TX);
	*/
        return(d_OK);
}

int inBuildAuthTxnOnlineOutput_2(int inTxnType,TRANS_DATA2*Trans,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut)
{
    
        
	Trans->ulCardTxnSN=BYTE3Data2LONG((BYTE *)&DongleOut->ucTxnSN);
//        DebugPrint_hex(&DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),"AFTER ucTxnSN",DebugMode_TX);
 //       DebugPrint_hex(&Trans->ulCardTxnSN,sizeof(Trans->ulCardTxnSN),"AFTER ucTxnSN long",DebugMode_TX);
	Trans->lEVafterTxn =BYTE3Data2LONG((BYTE *)&DongleOut->ucEV);
 //  DebugPrint_hex(&DongleOut->ucEV,sizeof(DongleOut->ucEV),"AFTER ucEV",DebugMode_TX);
 //  DebugPrint_hex(&Trans->lEVafterTxn,sizeof(Trans->lEVafterTxn),"AFTER lEVafterTxn long",DebugMode_TX);
	memcpy(&Trans->CPUSignature,&DongleOut->ucSignature,sizeof(DongleOut->ucSignature));
	
	if(Trans->ucCPUPurseVersionNUM == MIFARE){
		memcpy(Trans->MAC,&DongleOut->ucMAC_HCrypto[2],sizeof(Trans->MAC));//MAC
		memcpy(Trans->CTAC,&DongleOut->ucMAC_HCrypto[10],sizeof(Trans->CTAC));//CTAC
		
	}else{
	
		Trans->ucCPUHashTYPE = DongleOut->ucMAC_HCrypto[0];//Hash Type
		Trans->ucCPUHostadminKVN = DongleOut->ucMAC_HCrypto[1];//Host Admin KVN
		memcpy(Trans->CPUMAC_HCrypto,&DongleOut->ucMAC_HCrypto[2],sizeof(Trans->CPUMAC_HCrypto));//CPU MAC
                
	}
	
	memcpy(&Trans->ucTxnDateTime,&DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime));
        BYTE tmp[14];
        memset(tmp,0x00,14);
        fnLongToUnix(tmp,(unsigned long *)DongleOut->ucTxnDateTime,14);
        memcpy(&Trans->ucTxnData,(unsigned long *)tmp,8);
        memcpy(&Trans->ucTxnTime,(unsigned long *)&tmp[8],6);
        //	DebugPrint_hex(&DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime)," AFTER ucTxnDateTime",DebugMode_TX);
	return(d_OK);
} 





int BuildTxnReqOfflineOutput_2(int inTxnType,TRANS_DATA2 *Trans,TxnReqOffline_APDU_In *DongleIn,TxnReqOffline_APDU_Out *DongleOut)
{



//4800
	Trans->ucCPUPurseVersionNUM=DongleOut->ucPurseVersionNumber;

	Trans->ucBasicData_Autoloadflag=(BYTE)DongleOut->bAutoLoad;
//0212
	Trans->lAutoloadAMT= BYTE3Data2LONG((BYTE *)&DongleOut->ucAutoLoadAmt);
//0211
	memcpy(&Trans->ucPID,&DongleOut->ucPID,sizeof(DongleOut->ucPID));
//5302
	Trans->ucAdminKeyKVN=DongleOut->ucCPUAdminKeyKVN;
	Trans->ucCreditKeyKVN=DongleOut->ucCreditKeyKVN;
        Trans->ucDebitKeyKVN=DongleOut->ucCPUIssuerKeyKVN;
//5305	
	Trans->ucSigntureKeyKVN=DongleOut->ucSignatureKeyKVN;

//4812
	memcpy(&Trans->ucCTC,&DongleOut->ucCTC,sizeof(DongleOut->ucCTC));
//4809	
	memcpy(&Trans->ucCPUTxnMode,&DongleOut->ucTxnMode,sizeof(DongleOut->ucTxnMode));
//4810
	memcpy(&Trans->ucCPUTQ,&DongleOut->ucTxnQuqlifier,sizeof(DongleOut->ucTxnQuqlifier));
//4805
	memcpy(&Trans->ucCPUSubAreaCode,&DongleOut->ucSubAreaCode,sizeof(DongleOut->ucSubAreaCode));
//1400
	memcpy(&Trans->ucCardExpiryDate,&DongleOut->ucExpiryDate,sizeof(DongleOut->ucExpiryDate));
//0408
	// Trans->lEVafterTxn =BYTE3Data2LONG((BYTE *)&DongleOut->ucEV);
          Trans->lEVBeforeTxn =BYTE3Data2LONG((char *)&DongleOut->ucEV);
           Trans->ulSNBeforeTxn=BYTE3Data2LONG((char *)&DongleOut->ucTxnSN);
//0213 ucTxnSN
 //	Trans->ulCardTxnSN=BYTE3Data2LONG((BYTE *)&DongleOut->ucTxnSN);

	Trans->ucBasicData_CardType=DongleOut->ucCardType;
	Trans->ucBasicData_CardProfile=DongleOut->ucPersonalProfile;
	memcpy(&Trans->ucCardVaildDate,&DongleOut->ucProfileExpiryDate,sizeof(DongleOut->ucProfileExpiryDate));
	Trans->ucAreaCode=DongleOut->ucAreaCode;
	memcpy(&Trans->ucCardID,&DongleOut->ucCardID,sizeof(DongleOut->ucCardID));
	Trans->ucChipIDLength=DongleOut->ucCardIDLen;
	Trans->lTxnAmt=BYTE3Data2LONG((BYTE *)&DongleOut->ucTxnAmt);
	Trans->ucHostSpecVersionNo=DongleOut->ucHostSpecVersionNo;
	memcpy(&Trans->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(Trans->ucReaderFWVersion));
	memcpy(&Trans->ucDeviceID,&DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID));
	memcpy(&Trans->ucCPUDeviceID,&DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID));
	memcpy(&Trans->ucCPUSPID,&DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID));
	memcpy(&Trans->ucSubMerchantID,&DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID));
	
 	Trans->ulDepositValue=BYTE3Data2LONG((BYTE *)&DongleOut->ucDeposit);
	Trans->ucIssuerCode=DongleOut->ucIssuerCode;
	
///////////////////////////////////////////////////////////////////////////////
	Trans->ucCPDReadFlag=DongleOut->ucCPDReadFlag;
	
	if(DongleOut->ucPurseVersionNumber == MIFARE)
	{
                Trans->ucBankCode=DongleOut->ucBankCode_HostAdminKVN;
		memcpy(Trans->ucSTAC,(unsigned char *)&DongleOut->ucSID_STAC,sizeof(DongleOut->ucSID_STAC));
		Trans->ucKeyVersion=DongleOut->ucCPDKVN_SAMKVN;
                memcpy(&Trans->usLoyaltyCounter,(unsigned char *)&DongleOut->ucCPD_SAMID[0],2);
                memcpy(Trans->ucSAMID,(unsigned char *)&DongleOut->ucCPD_SAMID[2],8);
		memcpy(Trans->ucSAMSN,(unsigned char *)&DongleOut->ucCPD_SAMID[10],4);
		memcpy(Trans->ucSAMCRN,(unsigned char *)&DongleOut->ucCPDRAN_SAMCRN,sizeof(DongleOut->ucCPDRAN_SAMCRN));
     		Trans->ucCPUHostadminKVN=0x00;
               
		memset(Trans->CPUTermCrypto,0x00,sizeof(Trans->CPUTermCrypto));//CACrypto敺?蝣?	
	}else{
		memset(&Trans->ucSTAC,0x00,sizeof(Trans->ucSTAC));//STAC
                memset(&Trans->ucKeyVersion,0x00,sizeof(Trans->ucKeyVersion));//
		memset(&Trans->ucSAMID,0x00,sizeof(Trans->ucSAMID));//SAM ID
		memset(&Trans->ucSAMSN,0x00,sizeof(Trans->ucSAMSN));//SAM SN
		memset(&Trans->ucSAMCRN,0x00,sizeof(Trans->ucSAMCRN));//SAM CRN
                
                memcpy(&Trans->ucCPUSAMID,(unsigned char *)&DongleOut->ucSID_STAC,8);
		memcpy((unsigned char *)&Trans->ucCPUHostadminKVN,&DongleOut->ucBankCode_HostAdminKVN,sizeof( DongleOut->ucBankCode_HostAdminKVN));
		memcpy((unsigned char *)&Trans->CPUTermCrypto,(unsigned char *)&DongleOut->ucSVCrypto,sizeof(DongleOut->ucSVCrypto));
	}	 
	//memcpy(&Trans->ulTerminalTxnSN,&DongleOut->ucTMSerialNumber,sizeof(DongleOut->ucTMSerialNumber));
	Trans->usTXSN= wub_str_2_long(DongleOut->ucTMSerialNumber);
	
	memcpy(&Trans->ucCardParameter_CardOneDayQuota,&DongleOut->ucCardOneDayQuota,sizeof(DongleOut->ucCardOneDayQuota));
	memcpy(&Trans->ucCardParameter_CardOneDayQuotaDate,&DongleOut->ucCardOneDayQuota,sizeof(DongleOut->ucCardOneDayQuota));
		


	/*CardAVR_t CardAVR;ReaderAVRTM_t ReaderAVR;
	vdBuildCardAVRData(&CardAVR,&DongleOut->stLastCreditTxnLogInfo_t,
                                DongleOut->ucCardID,
                                DongleOut->ucIssuerCode,
                                (BYTE *)&DongleOut->ucCPUSPID,
                                (BYTE *)&DongleOut->ucCPULocationID,
                                (BYTE *)&DongleOut->ucPID,
                                (BYTE *)&Trans->usLoyaltyCounter);//Card AVR Info*/
	memcpy(&Trans->ucCardAVRDATA,&DongleOut->stLastCreditTxnLogInfo_t,sizeof(DongleOut->stLastCreditTxnLogInfo_t));
/*

DebugPrint_hex(&DongleOut->ucMsgType,sizeof(DongleOut->ucMsgType),"ucMsgType",DebugMode_TX);  
DebugPrint_hex(&DongleOut->ucSubType,sizeof(DongleOut->ucSubType),"ucSubType",DebugMode_TX);  
DebugPrint_hex(&DongleOut->ucCardID,sizeof(DongleOut->ucCardID),"ucCardID",DebugMode_TX); 	
DebugPrint_hex(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),"ucPersonalProfile",DebugMode_TX);  
DebugPrint_hex(&DongleOut->ucCardID,sizeof(DongleOut->ucCardID),"ucCardID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),"ucIssuerCode",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),"ucTxnSN",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),"ucTxnAmt",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucEV,sizeof(DongleOut->ucEV),"ucEV",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucAreaCode,sizeof(DongleOut->ucAreaCode),"ucAreaCode",DebugMode_TX); 
DebugPrint_hex(&Trans->usLoyaltyCounter,sizeof(Trans->usLoyaltyCounter),"usLoyaltyCounter",DebugMode_TX); 

DebugPrint_hex(&DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),"ucCPUDeviceID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),"ucCPUSPID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID),"ucCPULocationID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucPID,sizeof(DongleOut->ucPID),"ucPID",DebugMode_TX); 
DebugPrint_hex(&DongleOut->ucPurseVersionNumber,sizeof(DongleOut->ucPurseVersionNumber),"ucPurseVersionNumber",DebugMode_TX);
DebugPrint_hex(&DongleOut->ucSubAreaCode,sizeof(DongleOut->ucSubAreaCode),"ucSubAreaCode",DebugMode_TX);
*/
	return(d_OK);
}
int inBuildAuthTxnOfflineOutPut_2(int inTxnType,TRANS_DATA2 *Trans,AuthTxnOffline_APDU_In *DongleIn,AuthTxnOffline_APDU_Out *DongleOut)
{//,TxnReqOffline_APDU_Out *TxnReqOut
  		
	Trans->ulCardTxnSN=BYTE3Data2LONG((BYTE *)&DongleOut->ucTxnSN);
       
//        DebugPrint_hex(&DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),"AFTER ucTxnSN",DebugMode_TX);
//        DebugPrint_hex(&Trans->ulCardTxnSN,sizeof(Trans->ulCardTxnSN),"AFTER ucTxnSN long",DebugMode_TX);

        Trans->lEVafterTxn =BYTE3Data2LONG((BYTE *)&DongleOut->ucEV);

        //         DebugPrint_hex(&DongleOut->ucEV,sizeof(DongleOut->ucEV),"AFTER ucEV",DebugMode_TX);
//        DebugPrint_hex(&Trans->lEVafterTxn,sizeof(Trans->lEVafterTxn),"AFTER lEVafterTxn long",DebugMode_TX);
	memcpy(&Trans->CPUSignature,&DongleOut->ucSignature,sizeof(DongleOut->ucSignature));
	
	if(Trans->ucCPUPurseVersionNUM == MIFARE){
               
		memcpy(Trans->MAC,&DongleOut->ucMAC_HCrypto[2],4);//MAC
	//	memcpy(Trans->CTAC,&DongleOut->ucMAC_HCrypto[10],sizeof(Trans->CTAC));//CTAC
		
	}else{
	
		Trans->ucCPUHashTYPE = DongleOut->ucMAC_HCrypto[0];//Hash Type
		Trans->ucCPUHostadminKVN = DongleOut->ucMAC_HCrypto[1];//Host Admin KVN
		memcpy(Trans->CPUMAC_HCrypto,&DongleOut->ucMAC_HCrypto[2],sizeof(Trans->CPUMAC_HCrypto));//CPU MAC
            
	}
  
	memcpy(&Trans->ucCardParameter_CardOneDayQuota,&DongleOut->ucCardOneDayQuota ,sizeof(DongleOut->ucCardOneDayQuota));
	memcpy(&Trans->ucCardParameter_CardOneDayQuotaDate,&DongleOut->ucCardOneDayQuota,sizeof(DongleOut->ucCardOneDayQuota));

	memcpy(&Trans->ucTxnDateTime,&DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime));
  
        BYTE tmp[14];
        memset(tmp,0x00,14);
        fnLongToUnix(tmp,(unsigned long *)DongleOut->ucTxnDateTime,14);
        memcpy(&Trans->ucTxnData,(unsigned long *)tmp,8);
        memcpy(&Trans->ucTxnTime,(unsigned long *)&tmp[8],6);
      
     
//DebugPrint_hex(&DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime),"ucTxnDateTime",DebugMode_TX);         
	return(d_OK);
}
int inBuildLockCardDataOutput1_2(TRANS_DATA2 *Trans,LockCard_APDU_Out_2 *DongleOut,BYTE ucLockReason)
{
	 //4800
	Trans->ucCPUPurseVersionNUM=DongleOut->ucPurseVersionNumber;

	//0211
		memcpy(&Trans->ucPID,&DongleOut->ucPID,sizeof(DongleOut->ucPID));
	//4812
		memcpy(&Trans->ucCTC,&DongleOut->ucCTC,sizeof(DongleOut->ucCTC));
	//0213
	Trans->ucBasicData_CardType=DongleOut->ucCardType;
	Trans->ucBasicData_CardProfile=DongleOut->ucPersonalProfile;
  
        Trans->ucIssuerCode=DongleOut->ucIssuerCode;
         
	memcpy(&Trans->ucCardID,&DongleOut->ucCardID,sizeof(&DongleOut->ucCardID));
		Trans->ucChipIDLength=DongleOut->ucCardIDLen;
    
	memcpy(&Trans->ucDeviceID,&DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID));//4101
	memcpy(&Trans->ucCPUDeviceID,&DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID));
	memcpy(&Trans->ucCPUSPID,&DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID));
	memcpy(&Trans->ucSubMerchantID,&DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID));
	
	Trans->ucLockReason=ucLockReason;
//	memcpy(&Trans->ucTxnDateTime,ucTxnDateTime,sizeof(Trans->ucTxnDateTime));
      Trans->ucPersonalProfileAuth=0x00;
      Trans->ucMicroPaymentSetting=0x00;

	return(d_OK);
}
int inBuildLockCardDataOutput2_2(TRANS_DATA2 *Trans,LockCard_APDU_Out_3 *DongleOut,BYTE ucLockReason)
{
	
//4800
	Trans->ucCPUPurseVersionNUM=DongleOut->ucPurseVersionNumber;

	Trans->ucBasicData_Autoloadflag=(BYTE)DongleOut->bAutoLoad;
//0212
	Trans->lAutoloadAMT= BYTE3Data2LONG((BYTE *)&DongleOut->ucAutoLoadAmt);
//0211
	memcpy(&Trans->ucPID,&DongleOut->ucPID,sizeof(DongleOut->ucPID));
//4805
	memcpy(&Trans->ucCPUSubAreaCode,&DongleOut->ucSubAreaCode,sizeof(DongleOut->ucSubAreaCode));
//1400
	
        
        Trans->ulDepositValue= BYTE3Data2LONG((BYTE *)&DongleOut->ucDeposit);
        
         memcpy(&Trans->ulProfileExpiryDate,&DongleOut->ucExpiryDate,sizeof(DongleOut->ucExpiryDate));
//0408
	 Trans->lEVafterTxn =BYTE3Data2LONG((BYTE *)&DongleOut->ucEV);
//0213 ucTxnSN
 	Trans->ulCardTxnSN=BYTE3Data2LONG((BYTE *)&DongleOut->ucTxnSN);
    Trans->CPUSAMINFOData.ucSAMIssuerKVN=DongleOut->ucCPUIssuerKeyKVN;
	Trans->ucBasicData_CardType=DongleOut->ucCardType;
	Trans->ucBasicData_CardProfile=DongleOut->ucPersonalProfile;
	memcpy(&Trans->ucCardVaildDate,&DongleOut->ucProfileExpiryDate,sizeof(DongleOut->ucProfileExpiryDate));
	Trans->ucAreaCode=DongleOut->ucAreaCode;
	memcpy(&Trans->ucCardID,&DongleOut->ucCardID,sizeof(&DongleOut->ucCardID));
	Trans->ucChipIDLength=DongleOut->ucCardIDLen;
	
	memcpy(&Trans->ucDeviceID,&DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID));
	memcpy(&Trans->ucCPUDeviceID,&DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID));
	memcpy(&Trans->ucCPUSPID,&DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID));
	memcpy(&Trans->ucSubMerchantID,&DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID));
	memcpy(&Trans->ucANOTHEREV,&DongleOut->ucEV2,sizeof(DongleOut->ucEV2));
	Trans->ucIssuerCode=DongleOut->ucIssuerCode;
	Trans->ucBankCode=DongleOut->ucBankCode;
	memcpy(&Trans->usLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(Trans->usLoyaltyCounter));
	/*
	CardAVR_t CardAVR;ReaderAVRTM_t ReaderAVR;
	vdBuildCardAVRData(&CardAVR,
                       &DongleOut->stLastCreditTxnLogInfo_t,
                         (BYTE *)&DongleOut->ucCardID,
                        DongleOut->ucIssuerCode,
                        (BYTE *)&DongleOut->ucCPUSPID,
                        (BYTE *)&DongleOut->ucCPULocationID,
                        (BYTE *)&DongleOut->ucPID,
                        (BYTE *)&Trans->usLoyaltyCounter);//Card AVR Info*/
	memcpy(&Trans->ucCardAVRDATA,&DongleOut->stLastCreditTxnLogInfo_t,sizeof(DongleOut->stLastCreditTxnLogInfo_t));

	Trans->ucPersonalProfileAuth=DongleOut->ucMifareSettingParameter;
	Trans->ucMicroPaymentSetting=DongleOut->ucCPUSettingParameter;
	Trans->ucLockReason=ucLockReason;
	//memcpy(&Trans->ucTxnDateTime,ucTxnDateTime,sizeof(Trans->ucTxnDateTime));

	return(d_OK);
}

int inBuildSetValueData_2(TRANS_DATA2 *Trans,SetValue_APDU_Out *DongleOut)
{
      
	return(d_OK);
}

int inBuildAuthSetValueData_2(TRANS_DATA2 *Trans,AuthSetValue_APDU_Out *DongleOut)
{
   return(d_OK);
}

USHORT  usFormatTransTag2(TRANS_DATA2 * TransData,BYTE * TAG,BYTE * NAME, ezxml_t TransLog)
{
    
    int iTag;
    char TagNUM[10];
    STR buf[256],buf5581_1[12+1],buf5581_2[12+1],buf_T558901[32];
    int i;
    USHORT ret;
   // ezxml_t Tag, node2,node3,node4, node5,node6,node7,node8,node9,node10,node11,node12,node13,node14,node15;
   // memset(gtmpstr,0x00,sizeof(gtmpstr));
    memset(TagNUM,0x00,sizeof(TagNUM));
    memset(buf,0x00,sizeof(buf));
    memcpy(TagNUM,TAG,strlen(TAG));

    iTag=atoi(&TagNUM[1]);
    ezxml_t node;
   // ezxml_t node=ezxml_add_child_d(TransLog,TAG,0);
   // if(NAME !=NULL)ezxml_set_attr_d(node,"name",NAME);
    switch(iTag){
       case 100: 
           ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucMessageType);	
          // ezxml_set_txt_d(node,TransData->ucMessageType); 
          break;
       case 200:  
         
           vdUIntToAsc2((BYTE *)&TransData->ucCardID,sizeof(TransData->ucCardID),(BYTE *)&buf,10);
        //   ezxml_set_txt_d(node,buf); 
           ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
          break;
       case 211:   
           if(TransData->ucCPUPurseVersionNUM != MIFARE)
           {    
              // vdIntToAsc((BYTE *)&TransData->ucPID,sizeof(TransData->ucPID),(BYTE *)&buf,16,' ',10);
               fnUnPack(TransData->ucPID,sizeof(TransData->ucPID)-1,buf);//Purse ID
           //ezxml_set_txt_d(node,buf);
              ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           }
           break;
       case 212:
	   wub_hex_2_str(&TransData->ucBasicData_Autoloadflag, (BYTE *)&buf, 1);
           //ezxml_set_txt_d(node,buf);
             ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           break;
       case 213:    
          wub_hex_2_str(&TransData->ucBasicData_CardType, (BYTE *)&buf, 1);
          //ezxml_set_txt_d(node,buf);
            ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           break;
       case 214:   
           wub_hex_2_str(&TransData->ucBasicData_CardProfile,(BYTE *) &buf, 1);
         //  ezxml_set_txt_d(node,buf);    
             ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           break;
       case 300:   
           
           // ezxml_set_txt_d(node,(BYTE *)&TransData->ucProcessCode);     
             ECC_ADDXMLNODE(TransLog,TAG,NAME, (BYTE *)&TransData->ucProcessCode);
           break;
       case 301:
	   	//ret= ECC_GetXMLTag3(ConfigFile,  "DEVICE","READER","READERFWVER", buf);
                
                ECC_ADDXMLNODE(TransLog,TAG,NAME, gConfig.DEVICE.READER.bREADERFWVER);	
          
           break;
       case 400:   
              sprintf((char *)buf, "%ld",TransData->lTxnAmt);
             ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
              //  ezxml_set_txt_d(node,buf);     
             break;
       case 403:  
	   	 sprintf((char *)buf, "%ld",TransData->lDeductAMT);
                   ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
             // ezxml_set_txt_d(node,buf);    
           break;
       case 407: 
	   	 sprintf((char *)buf, "%ld",TransData->lADDAMT);
                   ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           //  ezxml_set_txt_d(node,buf);  
           break;
       case 408: 
	   	sprintf((char *)buf, "%ld",TransData->lEVafterTxn);
               // vdIntToAsc2((BYTE *)&TransData->lEVafterTxn,sizeof(TransData->lEVafterTxn),(BYTE *)&buf,10);
                  ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
            // ezxml_set_txt_d(node,buf);  
           break;
       case 409: 
   	      sprintf((char *)buf, "%ld",TransData->lAutoloadAMT);
                ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           //  ezxml_set_txt_d(node,buf);  
           break;
         
       case 410:  
             sprintf((char *)buf, "%ld",TransData->lEVBeforeTxn);
            //    vdIntToAsc2((BYTE *)&TransData->lEVBeforeTxn,sizeof(TransData->lEVBeforeTxn),(BYTE *)&buf,10);
             ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           //  ezxml_set_txt_d(node,(BYTE *)&TransData->lEVBeforeTxn);  
           break;
       case 700:
	     ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTxnDateTime);	
            // ezxml_set_txt_d(node,TransData->ucTxnDateTime);  
           break;
       case 1100:
           // sprintf((char *)buf, "%6d",TransData->ulTerminalTxnSN);
           // memcpy(&TransData_STR.ucTerminalTxnSN,&buf,6);
         //  vdUIntToAsc((BYTE *)&TransData->ulTerminalTxnSN,sizeof(TransData->ulTerminalTxnSN),gTransData_STR.ucTerminalTxnSN,6,'0',10);
               sprintf(buf, "%06ld",TransData->ulTerminalInvoiceNum);
                ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
            //   ezxml_set_txt_d(node,buf);  
           break;
       case 1101:  
           sprintf(buf, "%06ld",TransData->ulTMTxnSN);  
           ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           //   ezxml_set_txt_d(node,buf);    
           break;
       case 1200:  
   		  ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTxnTime);	
             //ezxml_set_txt_d(node,TransData->ucTxnTime);  
           break;
       case 1201:  
   		  ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTMTxnTime);	
             //ezxml_set_txt_d(node,TransData->ucTxnTime);  
           break;
       case 1300:  
             ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTxnData);	
             //ezxml_set_txt_d(node,TransData->ucTxnData);  
           break;
        case 1301:  
             ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTMTxnData);	
             //ezxml_set_txt_d(node,TransData->ucTxnData);  
           break;
       case 1400: 
           	fnLongToUnix(buf,(unsigned long *)&TransData->ucCardExpiryDate,6);
                  ECC_ADDXMLNODE(TransLog,TAG,NAME, &buf[2]);	
             //ezxml_set_txt_d(node,&buf[2]);   
           break;
       case 1402:  
     		fnLongToUnix(buf,(unsigned long *)&TransData->ucCardVaildDate,8);
                  ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
          //   ezxml_set_txt_d(node,buf);    
           break;
       case 1403:  
	   	fnLongToUnix(buf,(unsigned long *)&TransData->ucCardVaildDateAfterSet,8);
                  ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
             //ezxml_set_txt_d(node,buf);    
           break;
       case 3700:    

             ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucRRN);	
             //ezxml_set_txt_d(node,TransData->ucRRN);  
           break;
       case 3701:
        
                ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTMINVOICENO);	
            //   ezxml_set_txt_d(node,buf);  
           break;
       case 3800: 
	   	  ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTxnAuthNum);	
            // ezxml_set_txt_d(node,TransData->ucTxnAuthNum);  
           break;
       case 3900:
           
           if(ecrObj.gData.isEcrTxn)//4-Bytes
             ECC_ADDXMLNODE(TransLog,TAG,NAME, ecrObj.ngData->responseCode);
           else//2-Bytes
             ECC_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucResponseCode);
            // ezxml_set_txt_d(node,TransData->ucResponseCode);  
           break;
      
       case 4100:
           // wub_hex_2_str((BYTE*)&TransData->ucCPUDeviceID,(BYTE*)&buf4100, 6);
         
              wub_hex_2_str((BYTE*)&TransData->ucCPUDeviceID,buf, 6);
           
            //fnBINTODEVASC(TransData->ucCPUDeviceID,TransData_STR.ucCPUDeviceID,sizeof(TransData_STR.ucCPUDeviceID),LEVEL2);//n_TXN Device ID
             ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            // ezxml_set_txt_d(node,buf4100_2);  
           break;
       case 4101:  
              wub_hex_2_str((BYTE*)&TransData->ucDeviceID,buf, 4);
              ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                         //ezxml_set_txt_d(node,buf);  
           break;
       case 4102:
         
           ECC_ADDXMLNODE(TransLog,TAG,NAME, gConfig.ETHERNET.LOCAL.IP);	
        
           break;
       case 4103:  
         
            ECC_ADDXMLNODE(TransLog,TAG,NAME, gConfig.DEVICE.EDC.MechineID);	
           break;
       case 4104: 
      
        
           ECC_ADDXMLNODE(TransLog,TAG,NAME, gConfig.DEVICE.READER.bREADERID);	
           
           break;
       case 4200:  
             vdUIntToAsc(TransData->ucCPUSPID,sizeof(TransData->ucCPUSPID),buf,8,'0',10);//CPU SP ID    
         
     	     ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
             //ezxml_set_txt_d(node,buf);  
           break;
    
       case 4210:  
	     vdUIntToAsc2(TransData->ucSubMerchantID,sizeof(TransData->ucSubMerchantID),buf,10);//CPU SP ID    
       	    ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
            //  ezxml_set_txt_d(node,buf);     
            break;
       case 4800:    
             if(TransData->ucCPUPurseVersionNUM == MIFARE){
                 sprintf(buf,"00");
             }else{
        	wub_hex_2_str(&TransData->ucCPUPurseVersionNUM,buf, 1);
             }
                ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);	
            //  ezxml_set_txt_d(node,buf);    
             
                break;
       case 4801: 
              wub_hex_2_str((BYTE *)&TransData->ucCardAVRDATA,(BYTE *)&buf, sizeof(TransData->ucCardAVRDATA));
               ECC_ADDXMLNODE(TransLog,TAG,NAME, buf);
            //  ezxml_set_txt_d(node,buf);      
               break;
       case 4802: 
               wub_hex_2_str(&TransData->ucIssuerCode,(BYTE *)&buf, 1);
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               //ezxml_set_txt_d(node,buf);       
               break;
       case 4803:  
	   	  wub_hex_2_str(&TransData->ucBankCode,(BYTE *)&buf, 1);
             // ezxml_set_txt_d(node,buf);   
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4804:  
             wub_hex_2_str(&TransData->ucAreaCode,(BYTE *)&buf, 1);
              //ezxml_set_txt_d(node,buf);    
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4805: 
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str((BYTE *)&TransData->ucCPUSubAreaCode,(BYTE *)&buf,2);
              //ezxml_set_txt_d(node,buf);  
              ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
               break;
       case 4806: 
             wub_hex_2_str((BYTE *)&TransData->ulProfileExpiryDate,(BYTE *)&buf, sizeof(TransData->ulProfileExpiryDate));
              //ezxml_set_txt_d(node,buf);       
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4807:   
	   	wub_hex_2_str((BYTE *)&TransData->ucNEWProfileExpiryDate,(BYTE *)&buf, sizeof(TransData->ucNEWProfileExpiryDate));
              //ezxml_set_txt_d(node,buf);     
                 ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                break;
       case 4808:  
	  	
		 sprintf(buf,"%06ld",TransData->ulCardTxnSN);
              //ezxml_set_txt_d(node,buf); 
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4809:   
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str(&TransData->ucCPUTxnMode,(BYTE *)&buf, sizeof(TransData->ucCPUTxnMode));
             // ezxml_set_txt_d(node,buf);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 4810:  
              if(TransData->ucCPUPurseVersionNUM != MIFARE){
                    wub_hex_2_str(&TransData->ucCPUTQ,(BYTE *)&buf, sizeof(TransData->ucCPUTQ));
                 // ezxml_set_txt_d(node,buf);     
                   ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              }
              break;
       case 4811:  
            // if(TransData->ucCPUPurseVersionNUM != MIFARE){
        	 sprintf(buf,"%06ld",TransData->ulSNBeforeTxn);
             // ezxml_set_txt_d(node,buf);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             //}
              break;
       case 4812: 
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str((BYTE *)&TransData->ucCTC,(BYTE *)&buf, sizeof(TransData->ucCTC));
              //ezxml_set_txt_d(node,buf);    
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);
             }	
              break;
       case 4813: 
            sprintf(buf,"%06d",TransData->usLoyaltyCounter);
              //ezxml_set_txt_d(node,buf);      
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4814:   
             sprintf(buf,"%06ld",TransData->ulDepositValue);
             // ezxml_set_txt_d(node,buf);    
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
        case 4817:
          
             sprintf(buf,"%d",TransData->usCustomerFee);
             // ezxml_set_txt_d(node,buf);  
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            break;
        case 4818:
		 wub_hex_2_str((BYTE *)&TransData->ucANOTHEREV,(BYTE *)&buf, sizeof(TransData->ucANOTHEREV));
             // ezxml_set_txt_d(node,buf);  
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
  	case 4819:
		 wub_hex_2_str(&TransData->ucLockReason,(BYTE *)&buf, 1);
             // ezxml_set_txt_d(node,buf);  
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
              
              
       case 4820:  
                 wub_hex_2_str(&TransData->ucHostSpecVersionNo,(BYTE *)&buf, 1);
	       // ezxml_set_txt_d(node,buf);      
                  ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                 break;
       case 4821:  
     		wub_hex_2_str((BYTE *)&TransData->CardOneDayQuota_BeforeTX,(BYTE *)&buf, sizeof(TransData->CardOneDayQuota_BeforeTX));
		wub_hex_2_str((BYTE *)&TransData->CardOneDayQuotaDate_BeforeTX,(BYTE *)&buf[sizeof(TransData->CardOneDayQuotaDate_BeforeTX)*2], sizeof(TransData->CardOneDayQuotaDate_BeforeTX));
             // ezxml_set_txt_d(node,buf);   
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4822:    
   
		wub_hex_2_str(&TransData->ucCardAutoloadParameters_AutoloadFlag,(BYTE *)&buf, sizeof(TransData->ucCardAutoloadParameters_AutoloadFlag));
		wub_hex_2_str(&TransData->ucCardAutoloadParameters_AutoloadValue,(BYTE *)&buf[sizeof(TransData->ucCardAutoloadParameters_AutoloadValue)*2], sizeof(TransData->ucCardAutoloadParameters_AutoloadValue));
	       //ezxml_set_txt_d(node,buf);   
                ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4823:   
 		wub_hex_2_str(&TransData->ucOneDayQuotaWrite,(BYTE *)&buf, 1);
		//ezxml_set_txt_d(node,buf);     
                 ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                 break;
       case 4824:    
	   	wub_hex_2_str(&TransData->ucCPDReadFlag,(BYTE *)&buf, 1);
          //    ezxml_set_txt_d(node,buf);   
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4825: 
	   	wub_hex_2_str(&TransData->ucCPUCreditBalanceChangeFlag,(BYTE *)&buf, 1);
             // ezxml_set_txt_d(node,buf);    
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4826:  

          	wub_hex_2_str(&TransData->ucChipIDLength,(BYTE *)&buf, 1);
           //   ezxml_set_txt_d(node,buf);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4827: 
	   	wub_hex_2_str((BYTE *)&TransData->CardOneDayQuota_BeforeTX,(BYTE *)&buf, sizeof(TransData->CardOneDayQuota_BeforeTX));
		wub_hex_2_str((BYTE *)&TransData->CardOneDayQuotaDate_BeforeTX,(BYTE *)&buf[sizeof(TransData->CardOneDayQuotaDate_BeforeTX)*2], sizeof(TransData->CardOneDayQuotaDate_BeforeTX));
              //ezxml_set_txt_d(node,buf);
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4828: 
	   	wub_hex_2_str((BYTE *)&TransData->ucPersonalProfileAuth,(BYTE *)&buf, 1);
		memset(buf,0x30,18);
		buf[20]=0x00;
              //ezxml_set_txt_d(node,buf);  
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4829:   
	   	wub_hex_2_str(&TransData->ucMicroPaymentSetting,(BYTE*)&buf, 1);
		memset(buf,0x30,30);
		buf[32]=0x00;
              //ezxml_set_txt_d(node,buf);   
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5301:   
           	wub_hex_2_str(&TransData->ucKeyVersion,(BYTE*)&buf, 1);
              //ezxml_set_txt_d(node,buf);    
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////			  
       case 5302:   
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
               sprintf(buf,"%02x%02x%02x",TransData->ucAdminKeyKVN,TransData->ucCreditKeyKVN,TransData->ucDebitKeyKVN);
             // ezxml_set_txt_d(node,buf);    
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 5303: 
               if(TransData->ucCPUPurseVersionNUM !=  MIFARE){ 
                wub_hex_2_str(&TransData->ucCPUHashTYPE,(BYTE*)&buf, 1);
             //ezxml_set_txt_d(node,buf);
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               }
              break;
       case 5304:   
            
              wub_hex_2_str(&TransData->ucCPUHostadminKVN,(BYTE*)&buf, 1);
              //ezxml_set_txt_d(node,buf);  
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);
           
              break;
       case 5305:  
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
            wub_hex_2_str(&TransData->ucSigntureKeyKVN,(BYTE*)&buf, 1);
           //   ezxml_set_txt_d(node,buf);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 5306:  
             wub_hex_2_str((BYTE *)&TransData->ucCPUEDC,(BYTE*)&buf, sizeof(TransData->ucCPUEDC));
            //  ezxml_set_txt_d(node,buf); 
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5307:  
            wub_hex_2_str((BYTE *)&TransData->ucRSAM,(BYTE*)&buf, sizeof(TransData->ucRSAM));
            //  ezxml_set_txt_d(node,buf);   
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5308:  
             wub_hex_2_str((BYTE *)&TransData->ucRHOST,(BYTE*)&buf, sizeof(TransData->ucRHOST));
             // ezxml_set_txt_d(node,buf);   
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5361:   
             wub_hex_2_str((BYTE *)&TransData->ucSAMID,(BYTE*)&buf, sizeof(TransData->ucSAMID));
             //ezxml_set_txt_d(node,buf);    
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5362:  
              wub_hex_2_str((BYTE *)&TransData->ucSAMSN,(BYTE*)&buf, sizeof(TransData->ucSAMSN));
             // ezxml_set_txt_d(node,buf);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5363:   
              wub_hex_2_str((BYTE *)&TransData->ucSAMCRN,(BYTE*)&buf, sizeof(TransData->ucSAMCRN));
             // ezxml_set_txt_d(node,(BYTE *)&buf);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5364:   
            wub_hex_2_str((BYTE *)&TransData->CPUSAMINFOData,(BYTE*)&buf, sizeof(TransData->CPUSAMINFOData));
             // ezxml_set_txt_d(node,(BYTE *)&buf);    
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5365:  
             wub_hex_2_str((BYTE *)&TransData->SAMtransInfoData,(BYTE*)&buf, sizeof(TransData->SAMtransInfoData));
             // ezxml_set_txt_d(node,(BYTE *)&buf); 
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5366:  
            wub_hex_2_str((BYTE *)&TransData->ucSingleCreditTxnAmtLimit,(BYTE*)&buf, sizeof(TransData->ucSingleCreditTxnAmtLimit));
            //  ezxml_set_txt_d(node,(BYTE*)&buf);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5367:   
            wub_hex_2_str((BYTE *)&TransData->CSAMPARA,(BYTE*)&buf, sizeof(TransData->CSAMPARA));
             // ezxml_set_txt_d(node,(BYTE *)&buf);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5368:
            wub_hex_2_str((BYTE *)&TransData->ucSTC,(BYTE*)&buf, sizeof(TransData->ucSTC));
           //    ezxml_set_txt_d(node,(BYTE *)&buf);  
                ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                break;
       case 5369:
               wub_hex_2_str((BYTE *)&TransData->ucSAMSignOnControlFlag,(BYTE*)&buf, sizeof(TransData->ucSAMSignOnControlFlag));
             //   ezxml_set_txt_d(node,(BYTE *)&buf); 
                 ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                break;
       case 5370:    
             wub_hex_2_str((BYTE *)&TransData->CPULastSignonInfoData,(BYTE*)&buf, sizeof(TransData->CPULastSignonInfoData));
             // ezxml_set_txt_d(node,(BYTE *)&buf); 
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
         case 5371:    
       	    wub_hex_2_str((BYTE *)&TransData->ucCPUSAMID,(BYTE*)&buf, sizeof(TransData->ucCPUSAMID));
            // ezxml_set_txt_d(node,(BYTE *)&buf); 
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;       
       case 5501:     
        
          //    ezxml_set_txt_d(node,TransData->ucBatchNo);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucBatchNo);	
              break;
       case 5503:   
	   
          sprintf(buf,"%010ld",TransData->ulSTCode);
         //  sprintf(buf,"%ld",TransData->ulSTCode);
           //   ezxml_set_txt_d(node,buf);   
            ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5504:   
           /*kobe added for ECR*/             
             ECC_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucTMPOSID);	
             break;
       case 5509:    
            wub_hex_2_str(&TransData->EDCTYPE,(BYTE *)&buf, sizeof(TransData->EDCTYPE));
              //ezxml_set_txt_d(node,buf);    
              ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5510:     
           /*kobe added for ECR*/              
              memcpy(&buf,&TransData->ucTMAgentNumber,4);
              buf[4]=0x00;
              ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            //  ezxml_set_txt_d(node,TransData->ucTMAgentNumber);     
              
              break;
       case 5514:     
           
            //  ezxml_set_txt_d(node,TransData->ucTMTxnDateTime); 
              ECC_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucTMTxnDateTime);	
              break;
     /*  case 5548:     
              ezxml_set_txt(node,TransData->ucTxnAmt);     break;
       case 5550:     
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 5581:  
           if(TransData->ucTXTYPE == TXTYPE_VOID){
           /*  for(i=0;i<6;i++)
             {
                buf5581_1[i]=TransData->ucOrgTxnTerminalID[5-i];
             }*/
            // fnUnPack((BYTE*)buf5581_1,6,buf5581_2);
                wub_hex_2_str((BYTE*)&TransData->ucOrgTxnTerminalID,buf, 6);
            // buf5581_2[12]=0x00;
            //fnBINTODEVASC(TransData->ucCPUDeviceID,TransData_STR.ucCPUDeviceID,sizeof(TransData_STR.ucCPUDeviceID),LEVEL2);//n_TXN Device ID
             ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
           }
           // wub_hex_2_str((BYTE *)&TransData->ucOrgTxnTerminalID,(BYTE *)&buf, sizeof(TransData->ucOrgTxnTerminalID));
              //ezxml_set_txt_d(node,buf);  
             // ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5582:   
             if(TransData->ucTXTYPE == TXTYPE_VOID){
            //  ezxml_set_txt_d(node,TransData->ucOrgTxnRRN);   
              ECC_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucOrgTxnRRN);	
             }
              break;
       case 5583:    
            if(TransData->ucTXTYPE == TXTYPE_VOID){
         
            //  ezxml_set_txt_d(node,TransData->ucOrgTxnDate);     
                ECC_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucOrgTxnDate);	
            }
              break;
       case 5588:     
                node=ezxml_add_child_d(TransLog,TAG,0);
                
                node13=ezxml_add_child_d(node,"T558801",0);
                ezxml_set_txt_d(node13,"01");   
                node14=ezxml_add_child_d(node,"T558803",0);
                
                ezxml_set_txt_d(node14,gConfig.CURRVERSION.SSL.VERSION);  
                
                
               node11=ezxml_add_child_d(TransLog,TAG,0);
                node2=ezxml_add_child_d(node11,"T558801",0);
                ezxml_set_txt_d(node2,"02");   

		node3=ezxml_add_child_d(node11,"T558802",0);
                ezxml_set_txt_d(node3,(STR * )&gConfig.CURRVERSION.BLC.TYPE);   
                 node4=ezxml_add_child_d(node11,"T558803",0);
              
                ezxml_set_txt_d(node4,(STR * )&gConfig.CURRVERSION.BLC.VERSION);  
                
                node5=ezxml_add_child_d(TransLog,TAG,0);
                node6=ezxml_add_child_d(node5,"T558801",0);
                ezxml_set_txt_d(node6,"03");   

			
                node7=ezxml_add_child_d(node5,"T558802",0);
	        ezxml_set_txt_d(node7,(STR * )gConfig.CURRVERSION.AP.NAME);  
               
             
                node8=ezxml_add_child_d(node5,"T558803",0); 
		ezxml_set_txt_d(node8,(STR * )gConfig.CURRVERSION.AP.VERSION);  
             
                
                node9=ezxml_add_child_d(TransLog,TAG,0);
                node10=ezxml_add_child(node9,"T558801",0);
                ezxml_set_txt_d(node10,"04");   
                        
              				
                node12=ezxml_add_child_d(node9,"T558803",0);
		ezxml_set_txt_d(node12,(STR * )gConfig.CURRVERSION.PARAMETER);   
              break;
       case 5589:     
               sprintf(buf_T558901,"T558901");
               node2=ezxml_add_child_d(node,buf_T558901,0);
               wub_hex_2_str(&TransData->ucDeductStatus,(BYTE *)&buf, sizeof(TransData->ucDeductStatus));
             //  ezxml_set_txt_d(node2,buf);     
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
     /*  case 5590:   
              ezxml_set_txt(node,TransData->ucTxnAmt);        break;*/
       case 5591:     
             
              sprintf(buf,"%06ld",TransData->ulSettle_TotleCnt);
              //ezxml_set_txt_d(node,buf);      
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5592:    
              sprintf(buf,"%ld",TransData->lSettle_TotleAmt);
              //ezxml_set_txt_d(node,buf);   
               //   ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);
               node=ezxml_add_child_d(TransLog,TAG,0);
               node2=ezxml_add_child_d(node,"T559201",0);
               ezxml_set_txt_d(node2,buf);     
               node3=ezxml_add_child_d(node,"T559202",0);
               ezxml_set_txt_d(node3,"0");                    
               node4=ezxml_add_child_d(node,"T559203",0);
               ezxml_set_txt_d(node4,"0");     
              break;
       case 5595:     
               node=ezxml_add_child_d(TransLog,TAG,0);
               node2=ezxml_add_child_d(node,"T559501",0);
               ezxml_set_txt_d(node2,gTMS_ParmVER);     
               node3=ezxml_add_child_d(node,"T559502",0);
               ezxml_set_txt_d(node3,gTMS_ParmID);                    
               node4=ezxml_add_child_d(node,"T559503",0);
               ezxml_set_txt_d(node4,gTMS_ParmData);     
               node5=ezxml_add_child_d(node,"T559504",0);
               ezxml_set_txt_d(node5,gTMS_ParmVaildStartDate); 
               node6=ezxml_add_child_d(node,"T559505",0);
               ezxml_set_txt_d(node6,gTMS_ParmVaildENDDate);   
               break;
       case 5596:    
               node=ezxml_add_child_d(TransLog,TAG,0);
               node2=ezxml_add_child_d(node,"T559601",0);
               ezxml_set_txt_d(node2,gTransfer_TotlePackCnt);     
               
              
               node3=ezxml_add_child_d(node,"T559602",0);
               ezxml_set_txt_d(node3,gTransfer_SendedPackCnt);    
               
             
               node4=ezxml_add_child_d(node,"T559603",0);
               ezxml_set_txt_d(node4,gTransfer_ReceivedPackCnt);
               
               
               node5=ezxml_add_child_d(node,"T559604",0);
               ezxml_set_txt_d(node5,gTransfer_SendPackSN);
               
               break;
       case 6000:   
             
               wub_hex_2_str((BYTE *)&TransData->ucReaderFWVersion,(BYTE *)&buf, sizeof(TransData->ucReaderFWVersion));
              // ezxml_set_txt_d(node,buf); 
                  ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 6001:   
               wub_hex_2_str((BYTE *)&TransData->ReaderAVRDATA,(BYTE *)&buf, sizeof(TransData->ReaderAVRDATA));
              //ezxml_set_txt_d(node,(BYTE *)&buf);    
                  ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                  break;
       case 6002:    
             wub_hex_2_str((BYTE *)&TransData->stTermHostInfo_t,(BYTE *)&buf, sizeof(TransData->stTermHostInfo_t));
            // ezxml_set_txt_d(node,(BYTE *)&buf);      
                ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             break;
       case 6003:     
              wub_hex_2_str((BYTE *)&TransData->stTermParaInfo_t,(BYTE *)&buf, sizeof(TransData->stTermParaInfo_t));
              //ezxml_set_txt_d(node,(BYTE *)&buf); 
                 ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 6004:    
	   	
	    
                  ECC_ADDXMLNODE(TransLog,TAG,NAME,gConfig.CURRVERSION.BLC.VERSION);	
                  break;
       case 6400:  
             if(TransData->ucCPUPurseVersionNUM == MIFARE){
             wub_hex_2_str((BYTE *)&TransData->ucSTAC,(BYTE *)&buf, sizeof(TransData->ucSTAC));
              //ezxml_set_txt_d(node,buf);      
                 ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 6401:  
            wub_hex_2_str((BYTE *)&TransData->HTAC,(BYTE *)&buf, sizeof(TransData->HTAC));
             //ezxml_set_txt_d(node,buf);         
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            break;
       case 6402:   
             if(TransData->ucCPUPurseVersionNUM == MIFARE){
                  wub_hex_2_str((BYTE *)&TransData->CTAC,(BYTE *)&buf, sizeof(TransData->CTAC));
            //  ezxml_set_txt_d(node,buf);        
                 ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 6403:   
             if(TransData->ucCPUPurseVersionNUM == MIFARE){
                 wub_hex_2_str((BYTE *)&TransData->MAC,(BYTE *)&buf, sizeof(TransData->MAC));
             // ezxml_set_txt_d(node,buf);   
                 ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 6404:   
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
                 wub_hex_2_str((BYTE *)&TransData->CPUMAC_HCrypto,(BYTE *)&buf, sizeof(TransData->CPUMAC_HCrypto));
              //ezxml_set_txt_d(node,buf);      
                 ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 6405:  
            if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str((BYTE *)&TransData->CPUSignature,(BYTE *)&buf, sizeof(TransData->CPUSignature));
                 //  ezxml_set_txt_d(node,buf);      
                ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            }
            break;
       case 6406:    
            if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str((BYTE *)&TransData->CPUTermCrypto,(BYTE *)&buf, sizeof(TransData->CPUTermCrypto));
            //  ezxml_set_txt_d(node,buf);   
              ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            }
              break;
       case 6407:   
            wub_hex_2_str((BYTE *)&TransData->HostCrypto,(BYTE *)&buf, sizeof(TransData->HostCrypto));
           
          // wub_hex_2_str((BYTE *)&TransData->ucHVCrypto_HTAC,(BYTE *)&buf, sizeof(TransData->ucHVCrypto_HTAC));
             // ezxml_set_txt_d(node,buf);   
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 6408:    
            wub_hex_2_str((BYTE *)&TransData->ucSATOKEN,(BYTE *)&buf, sizeof(TransData->ucSATOKEN));
              //ezxml_set_txt_d(node,buf);   
               ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	  
            break;
       case 6409:   
            wub_hex_2_str((BYTE *)&TransData->HostToken,(BYTE *)&buf, sizeof(TransData->HostToken));
              //ezxml_set_txt_d(node,buf); 
                 ECC_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                 break;
   
    }
  
  
    return d_OK;
}



USHORT  usFormatTransTag3(TRANS_DATA2 * TransData,BYTE * TAG,BYTE * NAME, BYTE * TransLog)
{
    
    int iTag;
    char TagNUM[10];
    STR buf[256],buf1[256],buf2[256],buf3[256];
    int i;
  
    USHORT ret;
   // ezxml_t Tag, node2,node3,node4, node5,node6,node7,node8,node9,node10,node11,node12,node13,node14,node15;
   // memset(gtmpstr,0x00,sizeof(gtmpstr));
    memset(TagNUM,0x00,sizeof(TagNUM));
    memset(buf,0x00,sizeof(buf));
    memcpy(TagNUM,TAG,strlen(TAG));

    iTag=atoi(&TagNUM[1]);
    ezxml_t node;
   // ezxml_t node=ezxml_add_child_d(TransLog,TAG,0);
   // if(NAME !=NULL)ezxml_set_attr_d(node,"name",NAME);
    switch(iTag){
       case 100: 
           myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucMessageType);	
          // ezxml_set_txt_d(node,TransData->ucMessageType); 
          break;
       case 200:  
         
           vdUIntToAsc2((BYTE *)&TransData->ucCardID,sizeof(TransData->ucCardID),(BYTE *)&buf,10);
        //   ezxml_set_txt_d(node,buf); 
           myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
          break;
       case 211:   
           if(TransData->ucCPUPurseVersionNUM != MIFARE)
           {    
              // vdIntToAsc((BYTE *)&TransData->ucPID,sizeof(TransData->ucPID),(BYTE *)&buf,16,' ',10);
               fnUnPack(TransData->ucPID,sizeof(TransData->ucPID)-1,buf);//Purse ID
           //ezxml_set_txt_d(node,buf);
              myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           }
           break;
       case 212:
	   wub_hex_2_str(&TransData->ucBasicData_Autoloadflag, (BYTE *)&buf, 1);
           //ezxml_set_txt_d(node,buf);
             myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           break;
       case 213:    
          wub_hex_2_str(&TransData->ucBasicData_CardType, (BYTE *)&buf, 1);
          //ezxml_set_txt_d(node,buf);
            myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           break;
       case 214:   
           wub_hex_2_str(&TransData->ucBasicData_CardProfile,(BYTE *) &buf, 1);
         //  ezxml_set_txt_d(node,buf);    
             myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           break;
       case 300:   
           
           // ezxml_set_txt_d(node,(BYTE *)&TransData->ucProcessCode);     
             myxml_ADDXMLNODE(TransLog,TAG,NAME, (BYTE *)&TransData->ucProcessCode);
           break;
       case 301:
	   	//ret= ECC_GetXMLTag3(ConfigFile,  "DEVICE","READER","READERFWVER", buf);
                
                myxml_ADDXMLNODE(TransLog,TAG,NAME, gConfig.DEVICE.READER.bREADERFWVER);	
          
           break;
       case 400:   
              sprintf((char *)buf, "%ld",TransData->lTxnAmt);
             myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
              //  ezxml_set_txt_d(node,buf);     
             break;
       case 403:  
	   	 sprintf((char *)buf, "%ld",TransData->lDeductAMT);
                   myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
             // ezxml_set_txt_d(node,buf);    
           break;
       case 407: 
	   	 sprintf((char *)buf, "%ld",TransData->lADDAMT);
                   myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           //  ezxml_set_txt_d(node,buf);  
           break;
       case 408: 
	   	sprintf((char *)buf, "%ld",TransData->lEVafterTxn);
               // vdIntToAsc2((BYTE *)&TransData->lEVafterTxn,sizeof(TransData->lEVafterTxn),(BYTE *)&buf,10);
                  myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
            // ezxml_set_txt_d(node,buf);  
           break;
       case 409: 
   	      sprintf((char *)buf, "%ld",TransData->lAutoloadAMT);
                myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           //  ezxml_set_txt_d(node,buf);  
           break;
         
       case 410:  
             sprintf((char *)buf, "%ld",TransData->lEVBeforeTxn);
            //    vdIntToAsc2((BYTE *)&TransData->lEVBeforeTxn,sizeof(TransData->lEVBeforeTxn),(BYTE *)&buf,10);
             myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           //  ezxml_set_txt_d(node,(BYTE *)&TransData->lEVBeforeTxn);  
           break;
       case 700:
	     myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTxnDateTime);	
            // ezxml_set_txt_d(node,TransData->ucTxnDateTime);  
           break;
       case 1100:
           // sprintf((char *)buf, "%6d",TransData->ulTerminalTxnSN);
           // memcpy(&TransData_STR.ucTerminalTxnSN,&buf,6);
         //  vdUIntToAsc((BYTE *)&TransData->ulTerminalTxnSN,sizeof(TransData->ulTerminalTxnSN),gTransData_STR.ucTerminalTxnSN,6,'0',10);
               sprintf(buf, "%06ld",TransData->ulTerminalInvoiceNum);
                myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
            //   ezxml_set_txt_d(node,buf);  
           break;
       case 1101:  
           sprintf(buf, "%06ld",TransData->ulTMTxnSN);  
           myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
           //   ezxml_set_txt_d(node,buf);    
           break;
       case 1200:  
   		  myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTxnTime);	
             //ezxml_set_txt_d(node,TransData->ucTxnTime);  
           break;
       case 1201:  
   		  myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTMTxnTime);	
             //ezxml_set_txt_d(node,TransData->ucTxnTime);  
           break;
       case 1300:  
             myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTxnData);	
             //ezxml_set_txt_d(node,TransData->ucTxnData);  
           break;
        case 1301:  
             myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTMTxnData);	
             //ezxml_set_txt_d(node,TransData->ucTxnData);  
           break;
       case 1400: 
           	fnLongToUnix(buf,(unsigned long *)&TransData->ucCardExpiryDate,6);
                  myxml_ADDXMLNODE(TransLog,TAG,NAME, &buf[2]);	
             //ezxml_set_txt_d(node,&buf[2]);   
           break;
       case 1402:  
     		fnLongToUnix(buf,(unsigned long *)&TransData->ucCardVaildDate,8);
                  myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
          //   ezxml_set_txt_d(node,buf);    
           break;
       case 1403:  
	   	fnLongToUnix(buf,(unsigned long *)&TransData->ucCardVaildDateAfterSet,8);
                  myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
             //ezxml_set_txt_d(node,buf);    
           break;
       case 3700:    

             myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucRRN);	
             //ezxml_set_txt_d(node,TransData->ucRRN);  
           break;
       case 3701:
        
                myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTMINVOICENO);	
            //   ezxml_set_txt_d(node,buf);  
           break;
       case 3800: 
	   	  myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucTxnAuthNum);	
            // ezxml_set_txt_d(node,TransData->ucTxnAuthNum);  
           break;
       case 3900:
           
           if(ecrObj.gData.isEcrTxn)//4-Bytes
             myxml_ADDXMLNODE(TransLog,TAG,NAME, ecrObj.ngData->responseCode);
           else//2-Bytes
             myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->ucResponseCode);
            // ezxml_set_txt_d(node,TransData->ucResponseCode);  
           break;
      
       case 4100:
           // wub_hex_2_str((BYTE*)&TransData->ucCPUDeviceID,(BYTE*)&buf4100, 6);
         
              wub_hex_2_str((BYTE*)&TransData->ucCPUDeviceID,buf, 6);
           
            //fnBINTODEVASC(TransData->ucCPUDeviceID,TransData_STR.ucCPUDeviceID,sizeof(TransData_STR.ucCPUDeviceID),LEVEL2);//n_TXN Device ID
             myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            // ezxml_set_txt_d(node,buf4100_2);  
           break;
       case 4101:  
              wub_hex_2_str((BYTE*)&TransData->ucDeviceID,buf, 4);
              myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                         //ezxml_set_txt_d(node,buf);  
           break;
       case 4102:
         
           myxml_ADDXMLNODE(TransLog,TAG,NAME, gConfig.ETHERNET.LOCAL.IP);	
        
           break;
       case 4103:  
         
            myxml_ADDXMLNODE(TransLog,TAG,NAME, gConfig.DEVICE.EDC.MechineID);	
           break;
       case 4104: 
           myxml_ADDXMLNODE(TransLog,TAG,NAME, gConfig.DEVICE.READER.bREADERID);	
           
           break;
           
        case 4107:
               myxml_ADDXMLNODE(TransLog,TAG,NAME, TransData->POSID);	
            break;    
       case 4200:  
             vdUIntToAsc(TransData->ucCPUSPID,sizeof(TransData->ucCPUSPID),buf,8,'0',10);//CPU SP ID    
         
     	     myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
             //ezxml_set_txt_d(node,buf);  
           break;
    
       case 4210:  
	     vdUIntToAsc2(TransData->ucSubMerchantID,sizeof(TransData->ucSubMerchantID),buf,10);//CPU SP ID    
       	    myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
            //  ezxml_set_txt_d(node,buf);     
            break;
       case 4800:    
             if(TransData->ucCPUPurseVersionNUM == MIFARE){
                 sprintf(buf,"00");
             }else{
        	wub_hex_2_str(&TransData->ucCPUPurseVersionNUM,buf, 1);
             }
                myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);	
            //  ezxml_set_txt_d(node,buf);    
             
                break;
       case 4801: 
              wub_hex_2_str((BYTE *)&TransData->ucCardAVRDATA,(BYTE *)&buf, sizeof(TransData->ucCardAVRDATA));
               myxml_ADDXMLNODE(TransLog,TAG,NAME, buf);
            //  ezxml_set_txt_d(node,buf);      
               break;
       case 4802: 
               wub_hex_2_str(&TransData->ucIssuerCode,(BYTE *)&buf, 1);
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               //ezxml_set_txt_d(node,buf);       
               break;
       case 4803:  
	   	  wub_hex_2_str(&TransData->ucBankCode,(BYTE *)&buf, 1);
             // ezxml_set_txt_d(node,buf);   
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4804:  
             wub_hex_2_str(&TransData->ucAreaCode,(BYTE *)&buf, 1);
              //ezxml_set_txt_d(node,buf);    
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4805: 
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str((BYTE *)&TransData->ucCPUSubAreaCode,(BYTE *)&buf,2);
              //ezxml_set_txt_d(node,buf);  
              myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
               break;
       case 4806: 
             wub_hex_2_str((BYTE *)&TransData->ulProfileExpiryDate,(BYTE *)&buf, sizeof(TransData->ulProfileExpiryDate));
              //ezxml_set_txt_d(node,buf);       
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4807:   
	   	wub_hex_2_str((BYTE *)&TransData->ucNEWProfileExpiryDate,(BYTE *)&buf, sizeof(TransData->ucNEWProfileExpiryDate));
              //ezxml_set_txt_d(node,buf);     
                 myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                break;
       case 4808:  
	  	
		 sprintf(buf,"%06ld",TransData->ulCardTxnSN);
              //ezxml_set_txt_d(node,buf); 
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4809:   
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str(&TransData->ucCPUTxnMode,(BYTE *)&buf, sizeof(TransData->ucCPUTxnMode));
             // ezxml_set_txt_d(node,buf);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 4810:  
              if(TransData->ucCPUPurseVersionNUM != MIFARE){
                    wub_hex_2_str(&TransData->ucCPUTQ,(BYTE *)&buf, sizeof(TransData->ucCPUTQ));
                 // ezxml_set_txt_d(node,buf);     
                   myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              }
              break;
       case 4811:  
            // if(TransData->ucCPUPurseVersionNUM != MIFARE){
        	 sprintf(buf,"%06ld",TransData->ulSNBeforeTxn);
             // ezxml_set_txt_d(node,buf);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             //}
              break;
       case 4812: 
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str((BYTE *)&TransData->ucCTC,(BYTE *)&buf, sizeof(TransData->ucCTC));
              //ezxml_set_txt_d(node,buf);    
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);
             }	
              break;
       case 4813: 
            sprintf(buf,"%06d",TransData->usLoyaltyCounter);
              //ezxml_set_txt_d(node,buf);      
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4814:   
             sprintf(buf,"%06ld",TransData->ulDepositValue);
             // ezxml_set_txt_d(node,buf);    
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
        case 4817:
          
             sprintf(buf,"%d",TransData->usCustomerFee);
             // ezxml_set_txt_d(node,buf);  
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            break;
        case 4818:
		 wub_hex_2_str((BYTE *)&TransData->ucANOTHEREV,(BYTE *)&buf, sizeof(TransData->ucANOTHEREV));
             // ezxml_set_txt_d(node,buf);  
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
  	case 4819:
		 wub_hex_2_str(&TransData->ucLockReason,(BYTE *)&buf, 1);
             // ezxml_set_txt_d(node,buf);  
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
              
              
       case 4820:  
                 wub_hex_2_str(&TransData->ucHostSpecVersionNo,(BYTE *)&buf, 1);
	       // ezxml_set_txt_d(node,buf);      
                  myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                 break;
       case 4821:  
     		wub_hex_2_str((BYTE *)&TransData->CardOneDayQuota_BeforeTX,(BYTE *)&buf, sizeof(TransData->CardOneDayQuota_BeforeTX));
		wub_hex_2_str((BYTE *)&TransData->CardOneDayQuotaDate_BeforeTX,(BYTE *)&buf[sizeof(TransData->CardOneDayQuotaDate_BeforeTX)*2], sizeof(TransData->CardOneDayQuotaDate_BeforeTX));
             // ezxml_set_txt_d(node,buf);   
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4822:    
   
		wub_hex_2_str(&TransData->ucCardAutoloadParameters_AutoloadFlag,(BYTE *)&buf, sizeof(TransData->ucCardAutoloadParameters_AutoloadFlag));
		wub_hex_2_str(&TransData->ucCardAutoloadParameters_AutoloadValue,(BYTE *)&buf[sizeof(TransData->ucCardAutoloadParameters_AutoloadValue)*2], sizeof(TransData->ucCardAutoloadParameters_AutoloadValue));
	       //ezxml_set_txt_d(node,buf);   
                myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4823:   
 		wub_hex_2_str(&TransData->ucOneDayQuotaWrite,(BYTE *)&buf, 1);
		//ezxml_set_txt_d(node,buf);     
                 myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                 break;
       case 4824:    
	   	wub_hex_2_str(&TransData->ucCPDReadFlag,(BYTE *)&buf, 1);
          //    ezxml_set_txt_d(node,buf);   
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4825: 
	   	wub_hex_2_str(&TransData->ucCPUCreditBalanceChangeFlag,(BYTE *)&buf, 1);
             // ezxml_set_txt_d(node,buf);    
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4826:  

          	wub_hex_2_str(&TransData->ucChipIDLength,(BYTE *)&buf, 1);
           //   ezxml_set_txt_d(node,buf);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4827: 
	   	wub_hex_2_str((BYTE *)&TransData->CardOneDayQuota_BeforeTX,(BYTE *)&buf, sizeof(TransData->CardOneDayQuota_BeforeTX));
		wub_hex_2_str((BYTE *)&TransData->CardOneDayQuotaDate_BeforeTX,(BYTE *)&buf[sizeof(TransData->CardOneDayQuotaDate_BeforeTX)*2], sizeof(TransData->CardOneDayQuotaDate_BeforeTX));
              //ezxml_set_txt_d(node,buf);
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 4828: 
	   	wub_hex_2_str((BYTE *)&TransData->ucPersonalProfileAuth,(BYTE *)&buf, 1);
		memset(buf,0x30,18);
		buf[20]=0x00;
              //ezxml_set_txt_d(node,buf);  
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 4829:   
	   	wub_hex_2_str(&TransData->ucMicroPaymentSetting,(BYTE*)&buf, 1);
		memset(buf,0x30,30);
		buf[32]=0x00;
              //ezxml_set_txt_d(node,buf);   
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5301:   
           	wub_hex_2_str(&TransData->ucKeyVersion,(BYTE*)&buf, 1);
              //ezxml_set_txt_d(node,buf);    
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////			  
       case 5302:   
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
               sprintf(buf,"%02x%02x%02x",TransData->ucAdminKeyKVN,TransData->ucCreditKeyKVN,TransData->ucDebitKeyKVN);
             // ezxml_set_txt_d(node,buf);    
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 5303: 
               if(TransData->ucCPUPurseVersionNUM !=  MIFARE){ 
                wub_hex_2_str(&TransData->ucCPUHashTYPE,(BYTE*)&buf, 1);
             //ezxml_set_txt_d(node,buf);
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               }
              break;
       case 5304:   
            
              wub_hex_2_str(&TransData->ucCPUHostadminKVN,(BYTE*)&buf, 1);
              //ezxml_set_txt_d(node,buf);  
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);
           
              break;
       case 5305:  
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
            wub_hex_2_str(&TransData->ucSigntureKeyKVN,(BYTE*)&buf, 1);
           //   ezxml_set_txt_d(node,buf);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 5306:  
             wub_hex_2_str((BYTE *)&TransData->ucCPUEDC,(BYTE*)&buf, sizeof(TransData->ucCPUEDC));
            //  ezxml_set_txt_d(node,buf); 
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5307:  
            wub_hex_2_str((BYTE *)&TransData->ucRSAM,(BYTE*)&buf, sizeof(TransData->ucRSAM));
            //  ezxml_set_txt_d(node,buf);   
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5308:  
             wub_hex_2_str((BYTE *)&TransData->ucRHOST,(BYTE*)&buf, sizeof(TransData->ucRHOST));
             // ezxml_set_txt_d(node,buf);   
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5361:   
             wub_hex_2_str((BYTE *)&TransData->ucSAMID,(BYTE*)&buf, sizeof(TransData->ucSAMID));
             //ezxml_set_txt_d(node,buf);    
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5362:  
              wub_hex_2_str((BYTE *)&TransData->ucSAMSN,(BYTE*)&buf, sizeof(TransData->ucSAMSN));
             // ezxml_set_txt_d(node,buf);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5363:   
              wub_hex_2_str((BYTE *)&TransData->ucSAMCRN,(BYTE*)&buf, sizeof(TransData->ucSAMCRN));
             // ezxml_set_txt_d(node,(BYTE *)&buf);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5364:   
            wub_hex_2_str((BYTE *)&TransData->CPUSAMINFOData,(BYTE*)&buf, sizeof(TransData->CPUSAMINFOData));
             // ezxml_set_txt_d(node,(BYTE *)&buf);    
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5365:  
             wub_hex_2_str((BYTE *)&TransData->SAMtransInfoData,(BYTE*)&buf, sizeof(TransData->SAMtransInfoData));
             // ezxml_set_txt_d(node,(BYTE *)&buf); 
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5366:  
            wub_hex_2_str((BYTE *)&TransData->ucSingleCreditTxnAmtLimit,(BYTE*)&buf, sizeof(TransData->ucSingleCreditTxnAmtLimit));
            //  ezxml_set_txt_d(node,(BYTE*)&buf);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5367:   
            wub_hex_2_str((BYTE *)&TransData->CSAMPARA,(BYTE*)&buf, sizeof(TransData->CSAMPARA));
             // ezxml_set_txt_d(node,(BYTE *)&buf);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5368:
            wub_hex_2_str((BYTE *)&TransData->ucSTC,(BYTE*)&buf, sizeof(TransData->ucSTC));
           //    ezxml_set_txt_d(node,(BYTE *)&buf);  
                myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                break;
       case 5369:
               wub_hex_2_str((BYTE *)&TransData->ucSAMSignOnControlFlag,(BYTE*)&buf, sizeof(TransData->ucSAMSignOnControlFlag));
             //   ezxml_set_txt_d(node,(BYTE *)&buf); 
                 myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                break;
       case 5370:    
             wub_hex_2_str((BYTE *)&TransData->CPULastSignonInfoData,(BYTE*)&buf, sizeof(TransData->CPULastSignonInfoData));
             // ezxml_set_txt_d(node,(BYTE *)&buf); 
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
         case 5371:    
       	    wub_hex_2_str((BYTE *)&TransData->ucCPUSAMID,(BYTE*)&buf, sizeof(TransData->ucCPUSAMID));
            // ezxml_set_txt_d(node,(BYTE *)&buf); 
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;       
       case 5501:     
        
          //    ezxml_set_txt_d(node,TransData->ucBatchNo);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucBatchNo);	
              break;
       case 5503:   
	   
          sprintf(buf,"%010ld",TransData->ulSTCode);
         //  sprintf(buf,"%ld",TransData->ulSTCode);
           //   ezxml_set_txt_d(node,buf);   
            myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5504:   
           /*kobe added for ECR*/             
             myxml_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucTMPOSID);	
             break;
       case 5509:    
            wub_hex_2_str(&TransData->EDCTYPE,(BYTE *)&buf, sizeof(TransData->EDCTYPE));
              //ezxml_set_txt_d(node,buf);    
              myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5510:     
           /*kobe added for ECR*/              
              memcpy(&buf,&TransData->ucTMAgentNumber,4);
              buf[4]=0x00;
              myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            //  ezxml_set_txt_d(node,TransData->ucTMAgentNumber);     
              
              break;
       case 5514:     
           
            //  ezxml_set_txt_d(node,TransData->ucTMTxnDateTime); 
              myxml_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucTMTxnDateTime);	
              break;
     /*  case 5548:     
              ezxml_set_txt(node,TransData->ucTxnAmt);     break;
       case 5550:     
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 5581:  
           if(TransData->ucTXTYPE == TXTYPE_VOID){
           /*  for(i=0;i<6;i++)
             {
                buf5581_1[i]=TransData->ucOrgTxnTerminalID[5-i];
             }*/
            // fnUnPack((BYTE*)buf5581_1,6,buf5581_2);
                wub_hex_2_str((BYTE*)&TransData->ucOrgTxnTerminalID,buf, 6);
            // buf5581_2[12]=0x00;
            //fnBINTODEVASC(TransData->ucCPUDeviceID,TransData_STR.ucCPUDeviceID,sizeof(TransData_STR.ucCPUDeviceID),LEVEL2);//n_TXN Device ID
             myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
           }
           // wub_hex_2_str((BYTE *)&TransData->ucOrgTxnTerminalID,(BYTE *)&buf, sizeof(TransData->ucOrgTxnTerminalID));
              //ezxml_set_txt_d(node,buf);  
             // myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5582:   
             if(TransData->ucTXTYPE == TXTYPE_VOID){
            //  ezxml_set_txt_d(node,TransData->ucOrgTxnRRN);   
              myxml_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucOrgTxnRRN);	
             }
              break;
       case 5583:    
            if(TransData->ucTXTYPE == TXTYPE_VOID){
         
            //  ezxml_set_txt_d(node,TransData->ucOrgTxnDate);     
                myxml_ADDXMLNODE(TransLog,TAG,NAME,TransData->ucOrgTxnDate);	
            }
              break;
       case 5588:     
           memset(buf,0x00,sizeof(buf));
           memset(buf1,0x00,sizeof(buf1));
           memset(buf2,0x00,sizeof(buf2));
           memset(buf3,0x00,sizeof(buf3));
          //   myxml_ADDXMLNODE(buf1,"T558801","","01");  
           //    myxml_ADDXMLNODE(buf3,"T558803","",gConfig.CURRVERSION.SSL.VERSION);  
           sprintf(buf1,"<T558801>01</T558801>");          
           sprintf(buf3,"<T558803>%s</T558803>",gConfig.CURRVERSION.SSL.VERSION);   
           sprintf(buf,"<T5588>%s%s</T5588>",buf1,buf3);
           strncat(TransLog,buf,strlen(buf));
           memset(buf,0x00,sizeof(buf));
           memset(buf1,0x00,sizeof(buf1));
           memset(buf2,0x00,sizeof(buf2));
           memset(buf3,0x00,sizeof(buf3));   
          //   myxml_ADDXMLNODE(buf1,"T558801","","02");
          //   myxml_ADDXMLNODE(buf2,"T558802","",gConfig.CURRVERSION.BLC.TYPE);
          //   myxml_ADDXMLNODE(buf3,"T558803","",gConfig.CURRVERSION.BLC.VERSION);
             sprintf(buf1,"<T558801>02</T558801>");   
             sprintf(buf2,"<T558802>%s</T558802>",gConfig.CURRVERSION.BLC.TYPE);   
             sprintf(buf3,"<T558803>%s</T558803>",gConfig.CURRVERSION.BLC.VERSION);  
             sprintf(buf,"<T5588>%s%s%s</T5588>",buf1,buf2,buf3);
             strncat(TransLog,buf,strlen(buf));
           memset(buf,0x00,sizeof(buf));
           memset(buf1,0x00,sizeof(buf1));
           memset(buf2,0x00,sizeof(buf2));
           memset(buf3,0x00,sizeof(buf3));   
            // myxml_ADDXMLNODE(buf1,"T558801","","03");
           //  myxml_ADDXMLNODE(buf2,"T558802","",gConfig.CURRVERSION.AP.NAME);
          //   myxml_ADDXMLNODE(buf3,"T558803","",gConfig.CURRVERSION.AP.VERSION);
              sprintf(buf1,"<T558801>03</T558801>");   
             sprintf(buf2,"<T558802>%s</T558802>",gConfig.CURRVERSION.AP.NAME);   
             sprintf(buf3,"<T558803>%s</T558803>",gConfig.CURRVERSION.AP.VERSION);  
             sprintf(buf,"<T5588>%s%s%s</T5588>",buf1,buf2,buf3);
             strncat(TransLog,buf,strlen(buf));
           memset(buf,0x00,sizeof(buf));
           memset(buf1,0x00,sizeof(buf1));
           memset(buf2,0x00,sizeof(buf2));
           memset(buf3,0x00,sizeof(buf3));  
           //  myxml_ADDXMLNODE(buf1,"T558801","","04");
          //   myxml_ADDXMLNODE(buf3,"T558803","",gConfig.CURRVERSION.PARAMETER);            
          //   sprintf(buf,"<T5588>%s%s</T5588>",buf1,buf3);
          //   strcat(TransLog,buf);
           sprintf(buf1,"<T558801>04</T558801>");          
           sprintf(buf3,"<T558803>%s</T558803>",gConfig.CURRVERSION.PARAMETER);   
           sprintf(buf,"<T5588>%s%s</T5588>",buf1,buf3);
           strncat(TransLog,buf,strlen(buf));
             /*
             node=ezxml_add_child_d(TransLog,TAG,0);
                
                node13=ezxml_add_child_d(node,"T558801",0);
                ezxml_set_txt_d(node13,"01");   
                node14=ezxml_add_child_d(node,"T558803",0);
                
                ezxml_set_txt_d(node14,gConfig.CURRVERSION.SSL.VERSION);  
                
                
               node11=ezxml_add_child_d(TransLog,TAG,0);
                node2=ezxml_add_child_d(node11,"T558801",0);
                ezxml_set_txt_d(node2,"02");   

		node3=ezxml_add_child_d(node11,"T558802",0);
                ezxml_set_txt_d(node3,(STR * )&gConfig.CURRVERSION.BLC.TYPE);   
                 node4=ezxml_add_child_d(node11,"T558803",0);
              
                ezxml_set_txt_d(node4,(STR * )&gConfig.CURRVERSION.BLC.VERSION);  
                
                node5=ezxml_add_child_d(TransLog,TAG,0);
                node6=ezxml_add_child_d(node5,"T558801",0);
                ezxml_set_txt_d(node6,"03");   

			
                node7=ezxml_add_child_d(node5,"T558802",0);
	        ezxml_set_txt_d(node7,(STR * )gConfig.CURRVERSION.AP.NAME);  
               
             
                node8=ezxml_add_child_d(node5,"T558803",0); 
		ezxml_set_txt_d(node8,(STR * )gConfig.CURRVERSION.AP.VERSION);  
             
                
                node9=ezxml_add_child_d(TransLog,TAG,0);
                node10=ezxml_add_child(node9,"T558801",0);
                ezxml_set_txt_d(node10,"04");   
                        
              				
                node12=ezxml_add_child_d(node9,"T558803",0);
		ezxml_set_txt_d(node12,(STR * )gConfig.CURRVERSION.PARAMETER); */
              break;
       case 5589:     
            /*   sprintf(buf_T558901,"T558901");
               node2=ezxml_add_child_d(node,buf_T558901,0);
               wub_hex_2_str(&TransData->ucDeductStatus,(BYTE *)&buf, sizeof(TransData->ucDeductStatus));
             //  ezxml_set_txt_d(node2,buf);     
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	*/
               break;
     /*  case 5590:   
              ezxml_set_txt(node,TransData->ucTxnAmt);        break;*/
       case 5591:     
             
              sprintf(buf,"%06ld",TransData->ulSettle_TotleCnt);
              //ezxml_set_txt_d(node,buf);      
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 5592:    
           
           sprintf(buf,"<T559201>%ld</T559201><T559202>0</T559202><T559203>0</T559203>",TransData->lSettle_TotleAmt);
           myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
      /*        sprintf(buf,"%ld",TransData->lSettle_TotleAmt);
              //ezxml_set_txt_d(node,buf);   
               //   myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);
               node=ezxml_add_child_d(TransLog,TAG,0);
               node2=ezxml_add_child_d(node,"T559201",0);
               ezxml_set_txt_d(node2,buf);     
               node3=ezxml_add_child_d(node,"T559202",0);
               ezxml_set_txt_d(node3,"0");                    
               node4=ezxml_add_child_d(node,"T559203",0);
               ezxml_set_txt_d(node4,"0");     */
              break;
       case 5595:    
             sprintf(buf,"<T559501>%s</T559501><T559502>%s</T559502><T559503>%s</T559503><T559504>%s</T559504><T559505>%s</T559505>",
                    gTMS_ParmVER,
                    gTMS_ParmID, 
                    gTMS_ParmData,
                    gTMS_ParmVaildStartDate,
                    gTMS_ParmVaildENDDate
                    );
            myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            /*   node=ezxml_add_child_d(TransLog,TAG,0);
               node2=ezxml_add_child_d(node,"T559501",0);
               ezxml_set_txt_d(node2,gTMS_ParmVER);     
               node3=ezxml_add_child_d(node,"T559502",0);
               ezxml_set_txt_d(node3,gTMS_ParmID);                    
               node4=ezxml_add_child_d(node,"T559503",0);
               ezxml_set_txt_d(node4,gTMS_ParmData);     
               node5=ezxml_add_child_d(node,"T559504",0);
               ezxml_set_txt_d(node5,gTMS_ParmVaildStartDate); 
               node6=ezxml_add_child_d(node,"T559505",0);
               ezxml_set_txt_d(node6,gTMS_ParmVaildENDDate);   */
               break;
       case 5596:    
             sprintf(buf,"<T559601>%s</T559601><T559602>%s</T559602><T559603>%s</T559603><T559604>%s</T559604>",
                    gTransfer_TotlePackCnt,
                    gTransfer_SendedPackCnt, 
                    gTransfer_ReceivedPackCnt,
                    gTransfer_SendPackSN);
            myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            /*   node=ezxml_add_child_d(TransLog,TAG,0);
               node2=ezxml_add_child_d(node,"T559601",0);
               ezxml_set_txt_d(node2,gTransfer_TotlePackCnt);     
               
              
               node3=ezxml_add_child_d(node,"T559602",0);
               ezxml_set_txt_d(node3,gTransfer_SendedPackCnt);    
               
             
               node4=ezxml_add_child_d(node,"T559603",0);
               ezxml_set_txt_d(node4,gTransfer_ReceivedPackCnt);
               
               
               node5=ezxml_add_child_d(node,"T559604",0);
               ezxml_set_txt_d(node5,gTransfer_SendPackSN);
               */
               break;
       case 6000:   
             
               wub_hex_2_str((BYTE *)&TransData->ucReaderFWVersion,(BYTE *)&buf, sizeof(TransData->ucReaderFWVersion));
              // ezxml_set_txt_d(node,buf); 
                  myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 6001:   
               wub_hex_2_str((BYTE *)&TransData->ReaderAVRDATA,(BYTE *)&buf, sizeof(TransData->ReaderAVRDATA));
              //ezxml_set_txt_d(node,(BYTE *)&buf);    
                  myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                  break;
       case 6002:    
             wub_hex_2_str((BYTE *)&TransData->stTermHostInfo_t,(BYTE *)&buf, sizeof(TransData->stTermHostInfo_t));
            // ezxml_set_txt_d(node,(BYTE *)&buf);      
                myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             break;
       case 6003:     
              wub_hex_2_str((BYTE *)&TransData->stTermParaInfo_t,(BYTE *)&buf, sizeof(TransData->stTermParaInfo_t));
              //ezxml_set_txt_d(node,(BYTE *)&buf); 
                 myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
              break;
       case 6004:    
	   	
	    
                  myxml_ADDXMLNODE(TransLog,TAG,NAME,gConfig.CURRVERSION.BLC.VERSION);	
                  break;
       case 6400:  
             if(TransData->ucCPUPurseVersionNUM == MIFARE){
             wub_hex_2_str((BYTE *)&TransData->ucSTAC,(BYTE *)&buf, sizeof(TransData->ucSTAC));
              //ezxml_set_txt_d(node,buf);      
                 myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 6401:  
            wub_hex_2_str((BYTE *)&TransData->HTAC,(BYTE *)&buf, sizeof(TransData->HTAC));
             //ezxml_set_txt_d(node,buf);         
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            break;
       case 6402:   
             if(TransData->ucCPUPurseVersionNUM == MIFARE){
                  wub_hex_2_str((BYTE *)&TransData->CTAC,(BYTE *)&buf, sizeof(TransData->CTAC));
            //  ezxml_set_txt_d(node,buf);        
                 myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 6403:   
             if(TransData->ucCPUPurseVersionNUM == MIFARE){
                 wub_hex_2_str((BYTE *)&TransData->MAC,(BYTE *)&buf, sizeof(TransData->MAC));
             // ezxml_set_txt_d(node,buf);   
                 myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 6404:   
             if(TransData->ucCPUPurseVersionNUM != MIFARE){
                 wub_hex_2_str((BYTE *)&TransData->CPUMAC_HCrypto,(BYTE *)&buf, sizeof(TransData->CPUMAC_HCrypto));
              //ezxml_set_txt_d(node,buf);      
                 myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
             }
              break;
       case 6405:  
            if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str((BYTE *)&TransData->CPUSignature,(BYTE *)&buf, sizeof(TransData->CPUSignature));
                 //  ezxml_set_txt_d(node,buf);      
                myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            }
            break;
       case 6406:    
            if(TransData->ucCPUPurseVersionNUM != MIFARE){
                wub_hex_2_str((BYTE *)&TransData->CPUTermCrypto,(BYTE *)&buf, sizeof(TransData->CPUTermCrypto));
            //  ezxml_set_txt_d(node,buf);   
              myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
            }
              break;
       case 6407:   
            wub_hex_2_str((BYTE *)&TransData->HostCrypto,(BYTE *)&buf, sizeof(TransData->HostCrypto));
           
          // wub_hex_2_str((BYTE *)&TransData->ucHVCrypto_HTAC,(BYTE *)&buf, sizeof(TransData->ucHVCrypto_HTAC));
             // ezxml_set_txt_d(node,buf);   
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
               break;
       case 6408:    
            wub_hex_2_str((BYTE *)&TransData->ucSATOKEN,(BYTE *)&buf, sizeof(TransData->ucSATOKEN));
              //ezxml_set_txt_d(node,buf);   
               myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	  
            break;
       case 6409:   
            wub_hex_2_str((BYTE *)&TransData->HostToken,(BYTE *)&buf, sizeof(TransData->HostToken));
              //ezxml_set_txt_d(node,buf); 
                 myxml_ADDXMLNODE(TransLog,TAG,NAME,buf);	
                 break;
   
    }
  
  
    return d_OK;
}

USHORT usUnFormatTransTag3(TRANS_DATA2 *TransData,char* NodeName,char * NodeData)
{
    int iTag;
    char TagNUM[10];
    BYTE tmpstr[128],tmpstr1[128],tmpstr2[128];
    int InfoType;
    int TagDatalen=0;
    memset(tmpstr,0x00,sizeof(tmpstr));
    memset(TagNUM,0x00,sizeof(TagNUM));
    memcpy(TagNUM,NodeName,strlen(NodeName));
    iTag=atoi(&TagNUM[1]);
   
    
  
    switch(iTag){
       case 100:  
           memcpy(&TransData->ucMessageType,NodeData,sizeof(TransData->ucMessageType));
          break;
       case 200: break;
       case 211:       
  	    wub_str_2_hex(NodeData, (BYTE *)&TransData->ucPID , strlen(NodeData));
           break;
       case 212:         
  	    wub_str_2_hex(NodeData, &TransData->ucBasicData_Autoloadflag ,strlen(NodeData));
          break;
       case 213:    
 	    wub_str_2_hex(NodeData, &TransData->ucBasicData_CardType , strlen(NodeData));
           break;
       case 214:   
 	    wub_str_2_hex(NodeData, &TransData->ucBasicData_CardProfile , strlen(NodeData));
           break;
       case 300:  
           memcpy(TransData->ucProcessCode,NodeData,6);
           break;
       case 301:break;
       case 400:   
            TransData->lTxnAmt=wub_str_2_long(NodeData);
             break;
       case 403:  
	    TransData->lDeductAMT=wub_str_2_long(NodeData);
            break;
       case 407:   
           TransData->lADDAMT=wub_str_2_long(NodeData);
           break;
       case 408: break;
       case 409:break;         
       case 410:break;
       case 700:
           break;
       case 1100:
           TransData->ulTerminalInvoiceNum=wub_str_2_long(NodeData);
           break;
       case 1101:
           TransData->ulTMTxnSN=wub_str_2_long(NodeData);
          break;
       case 1200:  
	   memcpy(gTxnTime,NodeData,strlen(NodeData));
           break;
        case 1201:
          memcpy( TransData->ucTMTxnTime,NodeData,sizeof( NodeData));
          break;
       case 1300:
          memcpy( gTxnData,NodeData,strlen( NodeData));
          break;
      case 1301:  
          memcpy(gTransData.ucTMTxnData,NodeData,sizeof( gTransData.ucTMTxnData));
          break;    
       //end
        case 1400:// ucCardExpiryDate YYMM
            break;
       case 1402: 
           break;
       case 1403:  
	   sprintf(tmpstr1,"%s000000",NodeData);
	   fngetUnixTimeCnt((BYTE *)&TransData->ucCardVaildDateAfterSet,(BYTE *)tmpstr1);
           break;
       case 3700:   
           memcpy(TransData->ucRRN,NodeData,sizeof(TransData->ucRRN));
           break;
       case 3800: 
           memcpy(TransData->ucTxnAuthNum,NodeData,sizeof(TransData->ucTxnAuthNum));
           break;
       case 3900:
           memcpy(TransData->ucResponseCode,NodeData,strlen(NodeData));
           break;
       case 3901:break;
       case 3902:break;
       case 3903:  
            memcpy(TransData->ucSVCSResponseCode,NodeData,sizeof(TransData->ucSVCSResponseCode));
           break;
       case 3911:break;
       case 4100:break;
       case 4101:break;
       case 4102:break;
       case 4103:break;
       case 4104:break;
       case 4200:break;
     /*  case 4201:    
           
             ezxml_set_txt(node,TransData->ucSubMerchantID);  
           break;
       case 4202:  
           
             ezxml_set_txt(node,TransData->ucCPUPurseVersionNUM);  
           break;
       case 4203:
              ezxml_set_txt(node,TransData->ucCardAVRDATA);  
           break;
       case 4204:  
              ezxml_set_txt(node,TransData->ucTxnAmt);  
           break;
       case 4205:   
              ezxml_set_txt(node,TransData->ucTxnAmt);     break;
       case 4206:  
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;
       case 4207: 
              ezxml_set_txt(node,TransData->ucTxnAmt);       break;
       case 4208:  
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;
       case 4209:  
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 4210:break;
       case 4800:break;
       case 4801:break;
       case 4802:break;
       case 4803:break;
       case 4804:break;
       case 4805:break;
       case 4806:break;
       case 4807:   
             wub_str_2_hex(NodeData, (BYTE *)&TransData->ucNEWProfileExpiryDate , strlen(NodeData));
	     break;
       case 4808:  //ulCardTxnSN
             TransData->ulCardTxnSN=wub_str_2_long(NodeData);
   	     break;
       case 4809:   //ucCPUTxnMode
             wub_str_2_hex(NodeData, &TransData->ucCPUTxnMode , strlen(NodeData));
	     break;
       case 4810:break;
       case 4811:break;
       case 4812:break;
       case 4813:break;
       case 4814: break;
  /*     case 4815: 
              ezxml_set_txt(node,TransData->ucTxnAmt);     
              break;
       case 4816:  
              ezxml_set_txt(node,TransData->ucTxnAmt);     
              break;*/
       case 4820:  //CPU SPEC VERSION NUMBER
            	break;
       case 4821: break;
       case 4822:break;
       case 4823:
           wub_str_2_hex(NodeData, &TransData->ucOneDayQuotaWrite , strlen(NodeData));
           break;
       case 4824: 
           wub_str_2_hex(NodeData, &TransData->ucCPDReadFlag , strlen(NodeData));
           break;
       case 4825:break;
       case 4826:break;
       case 4827:break;
       case 4828:break;
       case 4829:break;
       case 5301:break;
       case 5302:break;
       case 5303: 
           wub_str_2_hex(NodeData, &TransData->ucCPUHashTYPE , strlen(NodeData));
		 break;
       case 5304:break;
       case 5305:  
           break;
       case 5306:  
           wub_str_2_hex(NodeData,(BYTE *) &TransData->ucCPUEDC , strlen(NodeData));
	 break;
       case 5307:  
           wub_str_2_hex(NodeData,(BYTE *) &TransData->ucRSAM , strlen(NodeData));
		 break;
       case 5308:  
            
              break;
       case 5361:break;
       case 5362:break;
       case 5363:break;
       case 5364:break;
       case 5365:break;
       case 5366:break;
       case 5367: 
                wub_str_2_hex(NodeData, (BYTE *)&TransData->CSAMPARA , strlen(NodeData));	  
              break;
       case 5368:break;
       case 5369:
              wub_str_2_hex(NodeData, (BYTE *)&TransData->ucSAMSignOnControlFlag , strlen(NodeData));	  	
                break;
       case 5370:break;
        case 5371:break;
       case 5501:break;
       case 5503:break;
       case 5504:
           memcpy(TransData->ucTMPOSID,NodeData,strlen(NodeData));
           break;
       case 5509: 
           break;
       case 5510:
           memcpy(TransData->ucTMAgentNumber,NodeData,strlen(NodeData));   
           break;
       case 5514:     
	   break;
     /*  case 5548:     
              ezxml_set_txt(node,TransData->ucTxnAmt);     break;
       case 5550:     
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 5581:break;
       case 5582:break;
       case 5583:break;
       case 5588:     
            if(TransData->ucTXSTATUS==TransStatus_ADVREQ)
                break;
         
               memset(tmpstr1,0x00,sizeof(tmpstr1));
               TagDatalen= myxml_GetTag(NodeData,"T558801",tmpstr1);
               if(TagDatalen==0)
               {
                    SystemLog("usUnFormatTransTag","T558801 is NULL ");
                    break ;
               }
               InfoType=atoi(tmpstr1);
               switch(InfoType)
               {
               case 1:
                   memset(tmpstr1,0x00,sizeof(tmpstr1));
                   TagDatalen= myxml_GetTag(NodeData,"T558803",tmpstr1);                 
                   if(TagDatalen!=0)
                   {
                       sprintf(gConfig.TMS.SSL.VERSION,"%s",tmpstr1);
                   }                   
                   break;
                case 2:
                   memset(tmpstr1,0x00,sizeof(tmpstr1));
                   TagDatalen= myxml_GetTag(NodeData,"T558802",tmpstr1);                 
                   if(TagDatalen!=0)
                   {
                        sprintf(gConfig.TMS.BLC.TYPE,"%s",tmpstr1);
                   }                   
                   memset(tmpstr1,0x00,sizeof(tmpstr1));
                   TagDatalen= myxml_GetTag(NodeData,"T558803",tmpstr1);                 
                   if(TagDatalen!=0)
                   {
                        sprintf(gConfig.TMS.BLC.VERSION,"%s",tmpstr1);
                   }         
                   break;
                case 3:
                   memset(tmpstr1,0x00,sizeof(tmpstr1));
                   TagDatalen= myxml_GetTag(NodeData,"T558803",tmpstr1);                 
                   if(TagDatalen!=0)
                   {
                           sprintf(gConfig.TMS.AP.VERSION,"%s",tmpstr1);
                   } 
                   break;
                 case 4:
                   memset(tmpstr1,0x00,sizeof(tmpstr1));
                   TagDatalen= myxml_GetTag(NodeData,"T558803",tmpstr1);                 
                   if(TagDatalen!=0)
                   {
                            sprintf(gConfig.TMS.PARAMETER,"%s",tmpstr1);
                   } 
                   break;  
                }       
            
          
            
              break;
       case 5589: break;
    
       case 5591: 
	      TransData->ulSettle_TotleCnt=atol(NodeData);
	        break;
       case 5592:
           //TransData->lSettle_TotleAmt= wub_str_2_long(NodeData);
	     break;
       case 5595:     
              memset(tmpstr1,0x00,sizeof(tmpstr1));
              TagDatalen= myxml_GetTag(NodeData,"T559501",tmpstr1);                 
              if(TagDatalen!=0)
              {
                sprintf(gucTMS_ParmVER,"%s",tmpstr1);
              }    
              memset(tmpstr1,0x00,sizeof(tmpstr1));
              TagDatalen= myxml_GetTag(NodeData,"T559502",tmpstr1);                 
              if(TagDatalen!=0)
              {
                sprintf(gucTMS_ParmID,"%s",tmpstr1);
              }   
              memset(tmpstr1,0x00,sizeof(tmpstr1));
              TagDatalen= myxml_GetTag(NodeData,"T559503",tmpstr1);                 
              if(TagDatalen!=0)
              {
                sprintf(gucTMS_ParmData,"%s",tmpstr1);
              }   
               memset(tmpstr1,0x00,sizeof(tmpstr1));
              TagDatalen= myxml_GetTag(NodeData,"T559504",tmpstr1);                 
              if(TagDatalen!=0)
              {
                sprintf(gucTMS_ParmVaildStartDate,"%s",tmpstr1);
              }   
              memset(tmpstr1,0x00,sizeof(tmpstr1));
              TagDatalen= myxml_GetTag(NodeData,"T559505",tmpstr1);                 
              if(TagDatalen!=0)
              {
                sprintf(gucTMS_ParmVaildENDDate,"%s",tmpstr1);
              }   
              T5595GetParameter();
              
               break;
       case 5596:   
              memset(tmpstr1,0x00,sizeof(tmpstr1));
              TagDatalen= myxml_GetTag(NodeData,"T559601",tmpstr1);                 
              if(TagDatalen!=0)
              {
                sprintf(gTransfer_TotlePackCnt,"%s",tmpstr1);
              }   
               memset(tmpstr1,0x00,sizeof(tmpstr1));
              TagDatalen= myxml_GetTag(NodeData,"T559602",tmpstr1);                 
              if(TagDatalen!=0)
              {
                sprintf(gTransfer_SendedPackCnt,"%s",tmpstr1);
              }   
               memset(tmpstr1,0x00,sizeof(tmpstr1));
              TagDatalen= myxml_GetTag(NodeData,"T559603",tmpstr1);                 
              if(TagDatalen!=0)
              {
                sprintf(gTransfer_ReceivedPackCnt,"%s",tmpstr1);
              }   
               memset(tmpstr1,0x00,sizeof(tmpstr1));
              TagDatalen= myxml_GetTag(NodeData,"T559604",tmpstr1);                 
              if(TagDatalen!=0)
              {
                sprintf(gTransfer_SendPackSN,"%s",tmpstr1);
              }  
              break;
       case 6000:   
         //     usSetTagData(node,(char *)&TransData->ucReaderFWVersion);  
         break;
       case 6001:   
           //   usSetTagData(node,(char *)&TransData->ReaderAVRDATA);      
           break;
       case 6002:   
               
		wub_str_2_hex(NodeData, (BYTE *)&TransData->stTermHostInfo_t , strlen(NodeData));	
            
            break;
       case 6003:     
         //     usSetTagData(node,(BYTE *)&TransData->stTermParaInfo_t);    
         break;
       case 6004:    
          //    usSetTagData(node,(char *)&TransData->ucBLVersion);   
          break;
       case 6400:    
          //    usSetTagData(node,(char *)&TransData->ucSTAC);     
          break;
       case 6401:  
           wub_str_2_hex(NodeData, (BYTE *)&TransData->HTAC , strlen(NodeData));	  	
	   break;
       case 6402:   
        //      usSetTagData(node,(char *)&TransData->CTAC);   
           break;
       case 6403:   
      //        usSetTagData(node,(char *)&TransData->MAC);       
           break;
       case 6404:   
   //           usSetTagData(node,(char *)&TransData->CPUMAC_HCrypto); 
           break;
       case 6405:   
      //        usSetTagData(node,(char *)&TransData->CPUSignature);      
           break;
       case 6406:  
 		wub_str_2_hex(NodeData, (BYTE *)&TransData->CPUTermCrypto , strlen(NodeData));	 
           break;
       case 6407:   
                wub_str_2_hex(NodeData, (BYTE *)&TransData->HostCrypto , strlen(NodeData));	  	
	  break;
       case 6408:     
     //         usSetTagData(node,(char *)&TransData->ucSATOKEN);    
          break;
       case 6409:   
    	  wub_str_2_hex(NodeData, (BYTE *)&TransData->HostToken , strlen(NodeData));
          break;
    }
    return d_OK;
}


USHORT usUnFormatTransTag2(TRANS_DATA2 *TransData, ezxml_t node)
{
    int iTag;
    char TagNUM[10];
    BYTE tmpstr[128],tmpstr1[128],tmpstr2[128];
    int InfoType;
   
    memset(tmpstr,0x00,sizeof(tmpstr));
    memset(TagNUM,0x00,sizeof(TagNUM));
    memcpy(TagNUM,node->name,strlen(node->name));
    iTag=atoi(&TagNUM[1]);
   
    
  
    switch(iTag){
       case 100:   
           usGetTagData(node,(char *)&tmpstr); 
          memcpy(&TransData->ucMessageType,tmpstr,sizeof(TransData->ucMessageType));
          break;
       case 200:  
          // usGetTagData(node,(char *)&tmpstr); 
	 //   fnASCTOBIN((BYTE *)&TransData->ucCardID,(BYTE *)&tmpstr,strlen(tmpstr),7,DECIMAL);//新場站代碼
	  //TransData->ucCardID=wub_str_2_long(tmpstr);
          break;
       case 211:   
           usGetTagData(node,(char *)&tmpstr);
  	    wub_str_2_hex(tmpstr, (BYTE *)&TransData->ucPID , strlen(tmpstr));
		  
           break;
       case 212:
           usGetTagData(node,(char *)&tmpstr);
  	    wub_str_2_hex(tmpstr, &TransData->ucBasicData_Autoloadflag ,strlen(tmpstr));
		 
	
           break;
       case 213:    
	   usGetTagData(node,(char *)&tmpstr);
  	    wub_str_2_hex(tmpstr, &TransData->ucBasicData_CardType , strlen(tmpstr));
		
        
           break;
       case 214:   
	    usGetTagData(node,(char *)&tmpstr);
  	    wub_str_2_hex(tmpstr, &TransData->ucBasicData_CardProfile , strlen(tmpstr));
	

           break;
       case 300:  
            usGetTagData(node,(char *)&TransData->ucProcessCode);     
           break;
       case 301:
          
           break;
       case 400:   
             usGetTagData(node,(char *)&tmpstr);
		
		TransData->lTxnAmt=wub_str_2_long(tmpstr);
             break;
       case 403:  
	   	 usGetTagData(node,(char *)&tmpstr);
		
		 TransData->lDeductAMT=wub_str_2_long(tmpstr);
          
           break;
       case 407:   
	   	 usGetTagData(node,(char *)&tmpstr);
		
	 TransData->lADDAMT=wub_str_2_long(tmpstr);
           
           break;
       case 408: 
	   	 usGetTagData(node,(char *)&tmpstr);
	//	 TransData->lEVafterTxn=wub_str_2_long(tmpstr);
           break;
       case 409: 
	   	 usGetTagData(node,(char *)&tmpstr);
	//	 TransData->lAutoloadAMT=wub_str_2_long(tmpstr);
           break;
         
       case 410:  
	    usGetTagData(node,(char *)&tmpstr);
	//    TransData->lEVBeforeTxn=wub_str_2_long(tmpstr);
	     
           break;
       case 700:
	 
           break;
       case 1100:
	   	usGetTagData(node,(char *)&tmpstr);
		TransData->ulTerminalInvoiceNum=wub_str_2_long(tmpstr);
           
         
           break;
       case 1101:
           //20140320,kobe added for ECR
           usGetTagData(node,(char *)&tmpstr);		
           TransData->ulTMTxnSN=wub_str_2_long(tmpstr);
           //end
           break;
       case 1200:  
	   	usGetTagData(node,(char *)&gTxnTime);  
           break;

       //20140320, kobe added for ECR    
        case 1201:
           usGetTagData(node, TransData->ucTMTxnTime);
           break;
       //end
           
       case 1300:  
             usGetTagData(node,(char *)&gTxnData);  
           break;
       //20140320, kobe added for ECR 
        case 1301:  
             usGetTagData(node,gTransData.ucTMTxnData);  
           break;    
       //end
        case 1400:// ucCardExpiryDate YYMM
	   
        //     usSetTagData(node,(char *)&TransData->ucCardExpiryDate);   
           break;
       case 1402:  
	   	
       //      usSetTagData(node,(char *)&TransData->ucCardVaildDate);    
           break;
       case 1403:  
           usGetTagData(node,(char *)&tmpstr);   
		   sprintf(tmpstr1,"%s000000",tmpstr);
		   fngetUnixTimeCnt((BYTE *)&TransData->ucCardVaildDateAfterSet,(BYTE *)tmpstr1);
		   
           break;
       case 3700:    
             usGetTagData(node,(char *)&TransData->ucRRN);  
           break;
       case 3800: 
             usGetTagData(node,(char *)&TransData->ucTxnAuthNum);  
           break;
       case 3900:
             usGetTagData(node,(char *)&TransData->ucResponseCode);  
           break;
       case 3901: 
  
           break;
       case 3902: 
     
           break;
       case 3903:  
                 usGetTagData(node,(char *)&TransData->ucSVCSResponseCode);  
           break;
       case 3911: 
 
           break;
       case 4100:
       //      usSetTagData(node,(char *)&TransData->ucCPUDeviceID);  
           break;
       case 4101:  
      //       usSetTagData(node,(char *)&TransData->ucDeviceID);  
           break;
       case 4102:
        //     usSetTagData(node,(char *)&TransData->ucTerminalIP);  
           break;
       case 4103:  
    //         usSetTagData(node,(char *)&TransData->ucMechineID);   
           break;
       case 4104: 
    //         usSetTagData(node,(char *)&TransData->ucReaderSN);      
           
           break;
       case 4200:  
           
      //       usSetTagData(node,(char *)&TransData->ucCPUSPID);  
           break;
     /*  case 4201:    
           
             ezxml_set_txt(node,TransData->ucSubMerchantID);  
           break;
       case 4202:  
           
             ezxml_set_txt(node,TransData->ucCPUPurseVersionNUM);  
           break;
       case 4203:
              ezxml_set_txt(node,TransData->ucCardAVRDATA);  
           break;
       case 4204:  
              ezxml_set_txt(node,TransData->ucTxnAmt);  
           break;
       case 4205:   
              ezxml_set_txt(node,TransData->ucTxnAmt);     break;
       case 4206:  
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;
       case 4207: 
              ezxml_set_txt(node,TransData->ucTxnAmt);       break;
       case 4208:  
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;
       case 4209:  
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 4210:  
            //  usSetTagData(node,(char *)&TransData->ucSubMerchantID);     
            break;
       case 4800:    
        //      usSetTagData(node,(char *)&TransData->ucCPUPurseVersionNUM);    
        	break;
       case 4801: 
       //       usSetTagData(node,(char *)&TransData->ucCardAVRDATA);       
       	break;
       case 4802: 
      //        usSetTagData(node,(char *)&TransData->ucIssuerCode);      
      		break;
       case 4803:  
         //     usSetTagData(node,(char *)&TransData->ucBankCode);      
         	break;
       case 4804:  
	   	           //   usSetTagData(node,(char *)&TransData->ucAreaCode);      
	   	break;
       case 4805: 
         //     usSetTagData(node,(char *)&TransData->ucCPUSubAreaCode);   
         	break;
       case 4806: 
       //       usSetTagData(node,(char *)&TransData->ucProfileExpiryDate);   
       	break;
       case 4807:   
             usGetTagData(node,(char *)&tmpstr);   
		wub_str_2_hex(tmpstr, (BYTE *)&TransData->ucNEWProfileExpiryDate , strlen(tmpstr));
		
		 break;
       case 4808:  //ulCardTxnSN
              usGetTagData(node,(char *)&tmpstr);   
		
		TransData->ulCardTxnSN=wub_str_2_long(tmpstr);
		  break;
       case 4809:   //ucCPUTxnMode
              usGetTagData(node,(char *)&tmpstr);  
		 wub_str_2_hex(tmpstr, &TransData->ucCPUTxnMode , strlen(tmpstr));
		  break;
       case 4810:  //ucCPUTQ
               break;
       case 4811:  
               break;
       case 4812: //ucCTC
                  break;
       case 4813: //
                 break;
       case 4814:   
      break;
  /*     case 4815: 
              ezxml_set_txt(node,TransData->ucTxnAmt);     
              break;
       case 4816:  
              ezxml_set_txt(node,TransData->ucTxnAmt);     
              break;*/
       case 4820:  //CPU SPEC VERSION NUMBER
        //      usSetTagData(node,(char *)&TransData->ucHostSpecVersionNo);    
        	break;
       case 4821: 
          //    usSetTagData(node,(char *)&TransData->ucCardParameters);   
		break;
       case 4822:    
         //     usSetTagData(node,(char *)&TransData->ucCardAutoloadParameters);  
		break;
       case 4823:
                 usGetTagData(node,(char *)&tmpstr);       
		 wub_str_2_hex(tmpstr, &TransData->ucOneDayQuotaWrite , strlen(tmpstr));
             

		break;
       case 4824:    
                usGetTagData(node,(char *)&tmpstr);       
		 wub_str_2_hex(tmpstr, &TransData->ucCPDReadFlag , strlen(tmpstr));
             
             
        	break;
       case 4825:   
        //      usSetTagData(node,(char *)&TransData->ucCPUCreditBalanceChangeFlag);     
        	break;
       case 4826:   
              // usSetTagData(node,(char *)&TransData->ucChipIDLength);     
		break;
       case 4827:   
             // usSetTagData(node,(char *)&TransData->ucCPUCardParameters);     
		 break;
       case 4828:   
              //usSetTagData(node,(char *)&TransData->ucMifareSettingData);     
              break;
       case 4829:   
              //usSetTagData(node,(char *)&TransData->ucCPUCardSettingParameter);    
              break;
       case 5301:   
             // usSetTagData(node,(char *)&TransData->ucKeyVersion);     
		break;
       case 5302:    
      //        usSetTagData(node,(char *)&TransData->ucCPUCardKeyInfo);    
      		break;
       case 5303: 
              usGetTagData(node,(char *)&tmpstr);       
		 wub_str_2_hex(tmpstr, &TransData->ucCPUHashTYPE , strlen(tmpstr));
		 break;
       case 5304:   
       //       usSetTagData(node,(char *)&TransData->ucCPUHostadminKVN);   

		 break;
       case 5305:  
   //           usSetTagData(node,(char *)&TransData->ucSigntureKeyKVN);      break;
       case 5306:  
              usGetTagData(node,(char *)&tmpstr);   
		 wub_str_2_hex(tmpstr,(BYTE *) &TransData->ucCPUEDC , strlen(tmpstr));
		 break;
       case 5307:  
              usGetTagData(node,(char *)&tmpstr);  
		 wub_str_2_hex(tmpstr,(BYTE *) &TransData->ucRSAM , strlen(tmpstr));
		 break;
       case 5308:  
              usGetTagData(node,(char *)&tmpstr);    
	
		  break;
       case 5361:   
	   	  //usSetTagData(node,(char *)&TransData->ucSAMID);   
		  break;
       case 5362:  
             // usSetTagData(node,(char *)&TransData->ucSAMSN);      
			  break;
       case 5363:   
             // usSetTagData(node,(char *)&TransData->ucSAMCRN);     
			  break;
       case 5364:   
            //  usSetTagData(node,(BYTE *)&TransData->CPUSAMINFOData);     
			  break;
       case 5365:   
           //   usSetTagData(node,(BYTE *)&TransData->SAMtransInfoData);    
			  break;
       case 5366:  
           //   usSetTagData(node,(char *)&TransData->ucSingleCreditTxnAmtLimit);      
			  break;
       case 5367:   
              usGetTagData(node,(BYTE *)&tmpstr); 
                wub_str_2_hex(tmpstr, (BYTE *)&TransData->CSAMPARA , strlen(tmpstr));	  
              break;
       case 5368:
            //  usSetTagData(node,(char *)&TransData->ucSTC);   
		
                break;
       case 5369:
                usGetTagData(node,(char *)&tmpstr); 
		   wub_str_2_hex(tmpstr, (BYTE *)&TransData->ucSAMSignOnControlFlag , strlen(tmpstr));	  	
                break;
       case 5370:    
       	  
              break;
        case 5371:
            
            break;
       case 5501:     
            //  usSetTagData(node,(char *)&TransData->ucBatchNo);     

			  break;
       case 5503:   

			  break;
       case 5504:
           //20140320, kobe added for ECR
           usGetTagData(node,TransData->ucTMPOSID);
           break;
           //end
       case 5509:    
        		break;
       case 5510:
           //20140320, kobe added for ECR
           usGetTagData(node,TransData->ucTMAgentNumber);           
           //end
			  break;
       case 5514:     
			  break;
     /*  case 5548:     
              ezxml_set_txt(node,TransData->ucTxnAmt);     break;
       case 5550:     
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 5581:    
			  break;
       case 5582:     break;
       case 5583:   break;
       case 5588:     
            if(TransData->ucTXSTATUS==TransStatus_ADVREQ)
                break;
           while(1){
          
               sprintf(tmpstr,"T558801");
               node2 = ezxml_get(node, tmpstr,-1);
             
               if(node2==NULL)
               {
                    SystemLog("usUnFormatTransTag","T558801 is NULL ");
                    break ;
               }
             
               usGetTagData(node2,tmpstr1);
               InfoType=atoi(tmpstr1);
               switch(InfoType)
               {
               case 1:
                   sprintf(tmpstr,"T558803");
                   node2 = ezxml_get(node,tmpstr,-1);
                   if(node2!=NULL)
                   {
                       sprintf(gConfig.TMS.SSL.VERSION,"%s",ezxml_txt(node2));
                    
                   //    ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION","TMS","SSL","VERSION",gConfig.TMS.SSL.VERSION);
                    
                       
                   }       
                   
                   break;
                case 2:
                   sprintf(tmpstr,"T558802");
                   node2 = ezxml_get(node,tmpstr,-1);
                   if(node2!=NULL)
                   {
                    
                         sprintf(gConfig.TMS.BLC.TYPE,"%s",ezxml_txt(node2));
                         ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION","TMS","BLC","TYPE",gConfig.TMS.BLC.TYPE);
                   
                        
                   }   
                   sprintf(tmpstr,"T558803");
                   node2 = ezxml_get(node,tmpstr,-1);
                   if(node2!=NULL)
                   {   
                            sprintf(gConfig.TMS.BLC.VERSION,"%s",ezxml_txt(node2));
                             ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION","TMS","BLC","VERSION",gConfig.TMS.BLC.VERSION);
                        
                           
                   } 
                         break;
                case 3:
                        sprintf(tmpstr,"T558803");
                        node2 = ezxml_get(node,tmpstr,-1);
                        if(node2!=NULL)
                        {
                          
                              sprintf(gConfig.TMS.AP.VERSION,"%s",ezxml_txt(node2));
                               ECC_SetXMLTag3(VERSIONINFO_Path, "VERSION","TMS","AP","VERSION",gConfig.TMS.AP.VERSION);
                            
                        }   
                     break;
                 case 4:
                        sprintf(tmpstr,"T558803");
                        node2 = ezxml_get(node,tmpstr,-1);
                        if(node2!=NULL)
                        {
                            sprintf(gConfig.TMS.PARAMETER,"%s",ezxml_txt(node2));
                            ECC_SetXMLTag2(VERSIONINFO_Path, "VERSION","TMS","PARAMETER",gConfig.TMS.PARAMETER);
                           
                        }     
                       break;    
                   
                }       
            
              if(node->child==NULL)
                       break;
                   else
                       node=node->next;
              };    
              
              break;
       case 5589:     
            
               break;
     /*  case 5590:   
              ezxml_set_txt(node,TransData->ucTxnAmt);        break;*/
       case 5591: 
		usGetTagData(node,(char *)tmpstr);    
	   	 TransData->ulSettle_TotleCnt=atol(tmpstr);
	        break;
       case 5592:    
	   	usGetTagData(node,(char *)tmpstr);    
		//2014.04.17, kobe removed it 
                //TransData->lSettle_TotleAmt= wub_str_2_long(tmpstr);
		 break;
       case 5595:     
           while(1){
               sprintf(tmpstr,"T559501");
               node2 = ezxml_get(node, tmpstr,-1);
               if(node2!=NULL)
                          usGetTagData(node2,gucTMS_ParmVER);     
               
               sprintf(tmpstr,"T559502");
                node2 = ezxml_get(node, tmpstr,-1);
                 if(node2!=NULL)
                     usGetTagData(node2,gucTMS_ParmID);     
               
               sprintf(tmpstr,"T559503");
               node2 = ezxml_get(node,tmpstr,-1);
               if(node2!=NULL)
                    usGetTagData(node2,gucTMS_ParmData);     
               
               sprintf(tmpstr,"T559504");
                 node2 = ezxml_get(node, tmpstr,-1);
                if(node2!=NULL) usGetTagData(node2,gucTMS_ParmVaildStartDate);   
               
               sprintf(tmpstr,"T559505");
               node2 = ezxml_get(node, tmpstr,-1);
               if(node2!=NULL) usGetTagData(node2,gucTMS_ParmVaildENDDate);  
               
               T5595GetParameter();
                if(node->next==NULL)
                       break;
                   else
                       node=node->next;
              };       
               break;
       case 5596:    
              sprintf(tmpstr,"T559601");
               node2 = ezxml_get(node, tmpstr,-1);
                 if(node2!=NULL) usGetTagData(node2,gTransfer_TotlePackCnt);     
               
               sprintf(tmpstr,"T559602");
                node2 = ezxml_get(node,tmpstr,-1);
                 if(node2!=NULL) usGetTagData(node2,gTransfer_SendedPackCnt);    
               
               sprintf(tmpstr,"T559603");
                node2 = ezxml_get(node,tmpstr,-1);
                 if(node2!=NULL) usGetTagData(node2,gTransfer_ReceivedPackCnt);
               
               sprintf(tmpstr,"T559604");
               node2 = ezxml_get(node,tmpstr,-1);
                 if(node2!=NULL) usGetTagData(node2,gTransfer_SendPackSN);
               break;
       case 6000:   
         //     usSetTagData(node,(char *)&TransData->ucReaderFWVersion);  
         break;
       case 6001:   
           //   usSetTagData(node,(char *)&TransData->ReaderAVRDATA);      
           break;
       case 6002:   
                usGetTagData(node,(char *)&tmpstr); 
		wub_str_2_hex(tmpstr, (BYTE *)&TransData->stTermHostInfo_t , strlen(tmpstr));	
            
            break;
       case 6003:     
         //     usSetTagData(node,(BYTE *)&TransData->stTermParaInfo_t);    
         break;
       case 6004:    
          //    usSetTagData(node,(char *)&TransData->ucBLVersion);   
          break;
       case 6400:    
          //    usSetTagData(node,(char *)&TransData->ucSTAC);     
          break;
       case 6401:  
              usGetTagData(node,(char *)&tmpstr); 
		wub_str_2_hex(tmpstr, (BYTE *)&TransData->HTAC , strlen(tmpstr));	  	
			  break;
       case 6402:   
        //      usSetTagData(node,(char *)&TransData->CTAC);   

			  break;
       case 6403:   
      //        usSetTagData(node,(char *)&TransData->MAC);       
      break;
       case 6404:   
   //           usSetTagData(node,(char *)&TransData->CPUMAC_HCrypto);        

			  break;
       case 6405:   
      //        usSetTagData(node,(char *)&TransData->CPUSignature);      
      break;
       case 6406:     
             
                usGetTagData(node,(char *)&tmpstr);       
 		wub_str_2_hex(tmpstr, (BYTE *)&TransData->CPUTermCrypto , strlen(tmpstr));	 
       break;
       case 6407:   
              usGetTagData(node,(char *)&tmpstr);       
 		wub_str_2_hex(tmpstr, (BYTE *)&TransData->HostCrypto , strlen(tmpstr));	  	
			  break;
       case 6408:     
     //         usSetTagData(node,(char *)&TransData->ucSATOKEN);    
     break;
       case 6409:   
    		  usGetTagData(node,(char *)tmpstr);       
		  wub_str_2_hex(tmpstr, (BYTE *)&TransData->HostToken , strlen(tmpstr));
			  break;
   
    }

   
    return d_OK;
}


void T5595GetParameter()
{
   ezxml_t ezxml_tag,ezxml_VERSION;
   USHORT usRet;
     BYTE tmpstr[64];
     memset(tmpstr,0x00,sizeof(tmpstr));
  
     
  if(strcmp(gucTMS_ParmID,"TM01")==0){//TM PASSWORD
       // memset(gConfig.MERCHANT.PASSWORD,0x00,sizeof(gConfig.MERCHANT.PASSWORD)); 
       //  sprintf(gConfig.MERCHANT.PASSWORD,"%s",gucTMS_ParmData);
         //Config_SetData();
       //  SetMERCHANTInfo(); 
        SetFunctionpPassword("SIGNON",gucTMS_ParmData);
         return ;
    }else if(strcmp(gucTMS_ParmID,"TM02")==0){
         memset(gConfig.MERCHANT.MERCHANTID,0x00,sizeof(gConfig.MERCHANT.MERCHANTID)); 
         sprintf(gConfig.MERCHANT.MERCHANTID,"%s",gucTMS_ParmData);
         //Config_SetData();
        ECC_SetXMLTag(MERCHANTINFO_Path,"MERCHANT","MERCHANTID",gConfig.MERCHANT.MERCHANTID);
         // SetMERCHANTInfo(); 
          return ;
    }else if(strcmp(gucTMS_ParmID,"TM03")==0){
         memset(gConfig.MERCHANT.NewLocationID,0x00,sizeof(gConfig.MERCHANT.NewLocationID)); 
         sprintf(gConfig.MERCHANT.NewLocationID,"%s",gucTMS_ParmData);
          //Config_SetData();
         ECC_SetXMLTag(MERCHANTINFO_Path,"MERCHANT","NewLocationID",gConfig.MERCHANT.NewLocationID);
         // SetMERCHANTInfo(); 
          return ;
    }else if(strcmp(gucTMS_ParmID,"TM04")==0){
        memset(gConfig.MERCHANT.STCODE,0x00,sizeof(gConfig.MERCHANT.STCODE)); 
        sprintf(gConfig.MERCHANT.STCODE,"%s",gucTMS_ParmData);
         //Config_SetData();
        ECC_SetXMLTag(MERCHANTINFO_Path,"MERCHANT","STCODE",gConfig.MERCHANT.STCODE);
         // SetMERCHANTInfo(); 
       return ;
    }else if(strcmp(gucTMS_ParmID,"TM17")==0){
        memset(gConfig.TM.TITLE,0x00,sizeof(gConfig.TM.TITLE));   
        sprintf(gConfig.TM.TITLE,"%s",gucTMS_ParmData);
        ECC_SetXMLTag(TMINFO_Path,"TM","TITLE",gConfig.TM.TITLE); 
        //Config_SetData();
        // SetTMInfo(); 
          return ;
    }else if(strcmp(gucTMS_ParmID,"TM18")==0){
        memset(gConfig.TM.SUBTITLE,0x00,sizeof(gConfig.TM.SUBTITLE)); 
        sprintf(gConfig.TM.SUBTITLE,"%s",gucTMS_ParmData);
        //Config_SetData();
          ECC_SetXMLTag(TMINFO_Path,"TM","SUBTITLE",gConfig.TM.SUBTITLE); 
        //   SetTMInfo(); 
         return ;
    }else if(strcmp(gucTMS_ParmID,"TM10")==0){
        memset(gConfig.TMS.SSL.FTPPATH,0x00,sizeof(gConfig.TMS.SSL.FTPPATH)); 
        sprintf(gConfig.TMS.SSL.FTPPATH,"%s",gucTMS_ParmData);
        //Config_SetData();
        
         ECC_SetXMLTag3(VERSIONINFO_Path,"VERSION","TMS","SSL","FTPPATH",gConfig.TMS.SSL.FTPPATH);
         // SetVERSIONInfo(); 
        return ;
   }else if(strcmp(gucTMS_ParmID,"TM11")==0){
        memset(gConfig.TMS.BLC.FTPPATH,0x00,sizeof(gConfig.TMS.BLC.FTPPATH)); 
        sprintf(gConfig.TMS.BLC.FTPPATH,"%s",gucTMS_ParmData);
       //Config_SetData();
         ECC_SetXMLTag3(VERSIONINFO_Path,"VERSION","TMS","BLC","FTPPATH",gConfig.TMS.BLC.FTPPATH);
         // SetVERSIONInfo(); 
        return ;
   }else if(strcmp(gucTMS_ParmID,"TM12")==0){
        memset(gConfig.TMS.AP.FTPPATH,0x00,sizeof(gConfig.TMS.AP.FTPPATH)); 
        sprintf(gConfig.TMS.AP.FTPPATH,"%s",gucTMS_ParmData);
        ECC_SetXMLTag3(VERSIONINFO_Path,"VERSION","TMS","AP","FTPPATH",gConfig.TMS.AP.FTPPATH);
        //Config_SetData();
        //  SetVERSIONInfo(); 
        return ;
   }else if(strcmp(gucTMS_ParmID,"TM09")==0){
          return ;    
   }else if(strcmp(gucTMS_ParmID,"TM10")==0){    
         return ;
   }else{
   
        BYTE nodestr[256];
        memset(nodestr,0x00,sizeof(nodestr));
        myxml_ADDXMLNODE2(nodestr,gucTMS_ParmID,gucTMS_ParmData,"STARTDATE",gucTMS_ParmVaildStartDate,"ENDDATE",gucTMS_ParmVaildENDDate);	
        strcat(gTMSData,nodestr);
   
    
    /*
       ezxml_t ezxml_TMS =LoadXMLFile(TMSFILE);
       if(ezxml_TMS==NULL) 
            ezxml_TMS=ezxml_new_d("TMS");

       ezxml_VERSION = ezxml_get(ezxml_TMS, "VERSION",-1);
       if(ezxml_VERSION==NULL){
           
            ezxml_VERSION= ezxml_add_child_d(ezxml_TMS,"VERSION",0);
            ezxml_set_attr_d(ezxml_VERSION,"VER",gConfig.TMS.PARAMETER);     
       }

      ezxml_tag= ezxml_add_child_d(ezxml_VERSION,gucTMS_ParmID,0);
      ezxml_set_attr_d(ezxml_tag,"ENDDATE",gucTMS_ParmVaildENDDate);  
      ezxml_set_attr_d(ezxml_tag,"STARTDATE",gucTMS_ParmVaildStartDate); 
      ezxml_set_txt_d(ezxml_tag,gucTMS_ParmData);     

      usRet= ECC_WriteXMLFILE(TMSFILE,ezxml_TMS);
      ezxml_free(ezxml_TMS);*/
      memset(gucTMS_ParmID,0x00,sizeof(gucTMS_ParmID));
      memset(gucTMS_ParmVaildENDDate,0x00,sizeof(gucTMS_ParmVaildENDDate));
      memset(gucTMS_ParmVaildStartDate,0x00,sizeof(gucTMS_ParmVaildStartDate));
      memset(gucTMS_ParmData,0x00,sizeof(gucTMS_ParmData));    
      
      return ;
   }
 
}

USHORT usUnFormatTMSTag(ezxml_t Tag)
{   USHORT ret;
    BYTE tmpstr[64];
    ezxml_t configNode;
     int table,item;
    memset(tmpstr,0x00,sizeof(tmpstr));
//    if(strlen(Tag->txt)<=1) return d_OK; 
    
     if(strcmp(Tag->name,"TM05")==0){
      memset(gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP,0x00,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP));   
      memcpy(gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP,Tag->txt,strlen(Tag->txt));
      //Config_SetData();
      //SetETHERNETInfo(); 
      ECC_SetXMLTag3(ETHERNETINFO_Path,"ETHERNET","HOST_PRODUCTION","FTP","IP",gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP);
      return ret;
    }else if(strcmp(Tag->name,"TM06")==0){
      memset(gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT,0x00,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT));   
      memcpy(gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT,Tag->txt,strlen(Tag->txt));
     ECC_SetXMLTag3(ETHERNETINFO_Path,"ETHERNET","HOST_PRODUCTION","FTP","PORT",gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT);
      return ret;
    }else if(strcmp(Tag->name,"TM07")==0){
      memset(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID,0x00,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID)); 
      memcpy(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID,Tag->txt,strlen(Tag->txt));
      ECC_SetXMLTag3(ETHERNETINFO_Path,"ETHERNET","HOST_PRODUCTION","FTP","LOGINID",gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID);
      return ret;
    }else if(strcmp(Tag->name,"TM08")==0){
      memset(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD,0x00,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD)); 
      memcpy(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD,Tag->txt,strlen(Tag->txt));
      ECC_SetXMLTag3(ETHERNETINFO_Path,"ETHERNET","HOST_PRODUCTION","FTP","LOGINPASSWORD",gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD);
      //SetETHERNETInfo();
      return ret;
   
    }else  if(strcmp(Tag->name,"TM14")==0){
     
   //     memset(gConfig.ETHERNET.HOST_PRODUCTION.HOST.URLPORT,0x00,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.URLPORT));  
  //      memcpy(gConfig.ETHERNET.HOST_PRODUCTION.HOST.URLPORT,Tag->txt,strlen(Tag->txt));
   
          return ret;
    }else if(strcmp(Tag->name,"TM15")==0){
      
        memset(gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP,0x00,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP));  
        memcpy(gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP,Tag->txt,strlen(Tag->txt));
        ECC_SetXMLTag3(ETHERNETINFO_Path,"ETHERNET","HOST_PRODUCTION","HOST","IP",gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP);
      //  SetETHERNETInfo();    
          return ret;
    }else if(strcmp(Tag->name,"TM16")==0){
        memset(gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT,0x00,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT)  );
        memcpy(gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT,Tag->txt,strlen(Tag->txt));
        ECC_SetXMLTag3(ETHERNETINFO_Path,"ETHERNET","HOST_PRODUCTION","HOST","PORT",gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT);
        // SetETHERNETInfo();
          return ret;
    }else if(strcmp(Tag->name,"TM19")==0){
         
        memset(gConfig.TM.RECEIPTNUM,0x00,sizeof(gConfig.TM.RECEIPTNUM)); 
        memcpy(gConfig.TM.RECEIPTNUM,Tag->txt,strlen(Tag->txt));
       ECC_SetXMLTag(TMINFO_Path,"TM","RECEIPTNUM",gConfig.TM.RECEIPTNUM);
        //SetTMInfo();
        return ret;
    }else if(strcmp(Tag->name,"TM20")==0){
    
        memset(gConfig.TM.RECEIPTREMARK.STRING1,0x00,sizeof(gConfig.TM.RECEIPTREMARK.STRING1));
        memcpy(gConfig.TM.RECEIPTREMARK.STRING1,Tag->txt,strlen(Tag->txt));
         ECC_SetXMLTag2(TMINFO_Path,"TM","RECEIPTREMARK","STRING1",gConfig.TM.RECEIPTREMARK.STRING1);
        //SetTMInfo();
        return ret;
    }else if(strcmp(Tag->name,"TM21")==0){
        memset(gConfig.TM.RECEIPTREMARK.STRING2,0x00,sizeof(gConfig.TM.RECEIPTREMARK.STRING2));
        memcpy(gConfig.TM.RECEIPTREMARK.STRING2,Tag->txt,strlen(Tag->txt));
         ECC_SetXMLTag2(TMINFO_Path,"TM","RECEIPTREMARK","STRING2",gConfig.TM.RECEIPTREMARK.STRING2);
        //SetTMInfo();
        return ret;
    }else if(strcmp(Tag->name,"TM22")==0){
        memset(gConfig.TM.RECEIPTREMARK.STRING3,0x00,sizeof(gConfig.TM.RECEIPTREMARK.STRING3));
        memcpy(gConfig.TM.RECEIPTREMARK.STRING3,Tag->txt,strlen(Tag->txt));
         ECC_SetXMLTag2(TMINFO_Path,"TM","RECEIPTREMARK","STRING3",gConfig.TM.RECEIPTREMARK.STRING3);
        //SetTMInfo();
        return ret;
    }else if(strcmp(Tag->name,"TM23")==0){
     
        memset(gConfig.TM.RECEIPTREMARK.STRING4,0x00,sizeof(gConfig.TM.RECEIPTREMARK.STRING4));
        memcpy(gConfig.TM.RECEIPTREMARK.STRING4,Tag->txt,strlen(Tag->txt));
         ECC_SetXMLTag2(TMINFO_Path,"TM","RECEIPTREMARK","STRING4",gConfig.TM.RECEIPTREMARK.STRING4);
        //SetTMInfo();
          return ret;
    }else if(strcmp(Tag->name,"TM24")==0){
        memset(gConfig.TM.RECEIPTREMARK.STRING5,0x00,sizeof(gConfig.TM.RECEIPTREMARK.STRING5));
        memcpy(gConfig.TM.RECEIPTREMARK.STRING5,Tag->txt,strlen(Tag->txt));
         ECC_SetXMLTag2(TMINFO_Path,"TM","RECEIPTREMARK","STRING5",gConfig.TM.RECEIPTREMARK.STRING5);
        //SetTMInfo();
          return ret;
    }else if(strcmp(Tag->name,"TM25")==0){
        memset(gConfig.TX.SIGNONMAXTIME,0x00,sizeof(gConfig.TX.SIGNONMAXTIME));
        memcpy(gConfig.TX.SIGNONMAXTIME,Tag->txt,strlen(Tag->txt));
        ECC_SetXMLTag(TXINFO_Path,"TX","SIGNONMAXTIME",gConfig.TX.SIGNONMAXTIME);
       // SetTXInfo();
        return ret;
    }else if(strcmp(Tag->name,"TM26")==0){
       memset(gConfig.TX.OFFLINETXLIMIT,0x00,sizeof(gConfig.TX.OFFLINETXLIMIT));
       memcpy(gConfig.TX.OFFLINETXLIMIT,Tag->txt,strlen(Tag->txt));
       ECC_SetXMLTag(TXINFO_Path,"TX","OFFLINETXLIMIT",gConfig.TX.OFFLINETXLIMIT);
      //  SetTXInfo();
       return ret;
    }else if(strcmp(Tag->name,"TM27")==0){
        memset(gConfig.TX.FORCEONLINELIMIT,0x00,sizeof(gConfig.TX.FORCEONLINELIMIT));
        memcpy(gConfig.TX.FORCEONLINELIMIT,Tag->txt,strlen(Tag->txt));
        ECC_SetXMLTag(TXINFO_Path,"TX","FORCEONLINELIMIT",gConfig.TX.FORCEONLINELIMIT);
      //  SetTXInfo();
        return ret;
    }else if(strcmp(Tag->name,"TM28")==0){
        memset(gConfig.TX.OPERATIONMODE  ,0x00,sizeof(gConfig.TX.OPERATIONMODE ));
        memcpy(gConfig.TX.OPERATIONMODE,Tag->txt,strlen(Tag->txt));
        ECC_SetXMLTag(TXINFO_Path,"TX","OPERATIONMODE",gConfig.TX.OPERATIONMODE);
      //  SetTXInfo();
        return ret;
    }else if(strcmp(Tag->name,"TM29")==0){
        memset(tmpstr,0x00,sizeof(tmpstr));
   
        char *delim=",";
        char *p;int i=0;
        p=strtok(Tag->txt,delim);
        
        while(p!=NULL){ 
            //gConfig.TX.AMTTABLE[0].AMT[i++] = atoi(p);
            gConfig.TX.AMTTABLE[0].AMT[i] = atoi(p);  
            SetAMTTABLE(0,i,gConfig.TX.AMTTABLE[0].AMT[i]);
            i++;
            p = strtok (NULL, delim);
        };
      
       // SetTXInfo();
        return 0;
    }else if(strcmp(Tag->name,"TM40")==0){//2014.05.26, kobe modified TM32 to TM40
        memset(tmpstr,0x00,sizeof(tmpstr));
   
        char *delim=",";
        char *p;int i=0;
        p=strtok(Tag->txt,delim);
      
        while(p!=NULL){
            gConfig.TX.AMTTABLE[1].AMT[i] = atoi(p);  
            SetAMTTABLE(1,i,gConfig.TX.AMTTABLE[1].AMT[i]);
            i++;
            p=strtok(NULL,delim);
         };
      
        //SetTXInfo();
        return 0;        
     }else if(strcmp(Tag->name,"TM33")==0){
        memset(tmpstr,0x00,sizeof(tmpstr));
   
        char *delim=",";
        char *p;int i=0;
        
        p=strtok(Tag->txt,delim);
       
        while(p!=NULL){
           // gConfig.TX.AMTTABLE[2].AMT[i++] = atoi(p);
            gConfig.TX.AMTTABLE[2].AMT[i] = atoi(p);  
            SetAMTTABLE(2,i,gConfig.TX.AMTTABLE[2].AMT[i]);
            i++;
            p=strtok(NULL,delim);
             
        };
      //SetTXInfo();
        return 0;
    }else if(strcmp(Tag->name,"TM34")==0){
        memset(tmpstr,0x00,sizeof(tmpstr));
   
        char *delim=",";
        char *p;int i=0;
        
        p=strtok(Tag->txt,delim);
      
        while(p!=NULL){
           // gConfig.TX.AMTTABLE[3].AMT[i++] = atoi(p);
             gConfig.TX.AMTTABLE[3].AMT[i] = atoi(p);  
            SetAMTTABLE(3,i,gConfig.TX.AMTTABLE[3].AMT[i]);
            i++;
            p=strtok(NULL,delim);
        
        };
       //SetTXInfo();
        return 0;
        
     }else if(strcmp(Tag->name,"TM35")==0){
        memset(tmpstr,0x00,sizeof(tmpstr));
   
        char *delim=",";
        char *p;int i=0;          
        p = strtok(Tag->txt,delim);
    
        while(p!=NULL){
           // gConfig.TX.AMTTABLE[4].AMT[i++] = atoi(p);
            gConfig.TX.AMTTABLE[4].AMT[i] = atoi(p);  
            SetAMTTABLE(4,i,gConfig.TX.AMTTABLE[4].AMT[i]);
            i++;
            p = strtok(NULL,delim);
          
        };
      
      //SetTXInfo();
      return 0;
    }else if(strcmp(Tag->name,"TM36")==0){
        gConfig.TX.AMTTABLE[1].AREACODE=atoi(Tag->txt);
        ECC_SetXMLTag2(TXINFO_Path,"TX","AMTTABLE1","AREACODE", Tag->txt);
       //SetTXInfo();
        return 0;
    }else if(strcmp(Tag->name,"TM37")==0){
          gConfig.TX.AMTTABLE[2].AREACODE=atoi(Tag->txt);
         ECC_SetXMLTag2(TXINFO_Path,"TX","AMTTABLE2","AREACODE", Tag->txt);
          // SetTXInfo();
        return 0;
    }else if(strcmp(Tag->name,"TM38")==0){
          gConfig.TX.AMTTABLE[3].AREACODE=atoi(Tag->txt);
          ECC_SetXMLTag2(TXINFO_Path,"TX","AMTTABLE3","AREACODE", Tag->txt);
       // SetTXInfo();
        return 0;
    }else if(strcmp(Tag->name,"TM39")==0){
        gConfig.TX.AMTTABLE[4].AREACODE=atoi(Tag->txt);
         ECC_SetXMLTag2(TXINFO_Path,"TX","AMTTABLE4","AREACODE", Tag->txt);
       // SetTXInfo();
        return 0;
    }else if(strcmp(Tag->name,"TM30")==0){
       if(Tag->txt[0]==0x31)
           SetFunctionSwitch("ADDVALUE",TRUE);
       else
           SetFunctionSwitch("ADDVALUE",FALSE);
       
       if(Tag->txt[1]==0x31)
           SetFunctionSwitch("AUTOLOAD",TRUE);
        else
           SetFunctionSwitch("AUTOLOAD",FALSE);
       
       // if(gucTMS_ParmData[2]==0x31)
          // SetFunctionSwitch("");
       // else
            
        if(Tag->txt[3]==0x31)
           SetFunctionSwitch("DEDUCT",TRUE);
        else
             SetFunctionSwitch("DEDUCT",FALSE);
    //    if(gucTMS_ParmID[4]==0x31)
         //  SetFunctionSwitch("ADDVALUE");
        if(Tag->txt[5]==0x31)
           SetFunctionSwitch("CANCELTXN",TRUE);
        else
           SetFunctionSwitch("CANCELTXN",FALSE);

        if(Tag->txt[6]==0x31)
           SetFunctionSwitch("RETURN",TRUE);
        else
             SetFunctionSwitch("RETURN",FALSE);
       
        if(Tag->txt[7]==0x31)
           SetFunctionSwitch("SETDATA",TRUE);
        else
           SetFunctionSwitch("SETDATA",FALSE);
       
        if(Tag->txt[8]==0x31)
           SetFunctionSwitch("AUTOLOADENABLE",TRUE);
        else
           SetFunctionSwitch("AUTOLOADENABLE",FALSE);
  ////////////////////////////////////////////////////
     //  SetFunctionSwitch("AUTOLOADENABLE",TRUE);
      ////////////////////////////////////////////////////
      //  ConfigFunction_GetData();
        //Config_SetData();    
        return ; 
       
    }else if(strcmp(Tag->name,"TM31")==0){
          memset( gConfig.TX.MiniunitsADDVALUE,0x00,sizeof( gConfig.TX.MiniunitsADDVALUE));
          sprintf(gConfig.TX.MiniunitsADDVALUE,"%s",Tag->txt);
          ECC_SetXMLTag(TXINFO_Path,"TX","MiniunitsADDVALUE",gConfig.TX.MiniunitsADDVALUE);
        //  memcpy(gConfig.TX.MiniunitsADDVALUE,&Tag->txt,strlen(Tag->txt));
          return ret;
    }else if(strcmp(Tag->name,"TM41")==0){
       if(Tag->txt[0]==0x31)
           SetFunctionpPasswordSwitch("ADDVALUE",TRUE);
       else
           SetFunctionpPasswordSwitch("ADDVALUE",FALSE);
       ConfigFunction_GetData();
    }else if(strcmp(Tag->name,"TM42")==0){
       if(Tag->txt[0]==0x31)
           SetFunctionpPasswordSwitch("DEDUCT",TRUE);
        else
           SetFunctionpPasswordSwitch("DEDUCT",FALSE);
         return 0; 
   }else if(strcmp(Tag->name,"TM43")==0){    
           if(Tag->txt[0]==0x31)
           SetFunctionpPasswordSwitch("CANCELTXN",TRUE);
        else
           SetFunctionpPasswordSwitch("CANCELTXN",FALSE);       
             return 0; 
     }else if(strcmp(Tag->name,"TM44")==0){    
         if(Tag->txt[0]==0x31)
           SetFunctionpPasswordSwitch("RETURN",TRUE);
        else
             SetFunctionpPasswordSwitch("RETURN",FALSE);
            return 0; 
     }else if(strcmp(Tag->name,"TM45")==0){    
        if(Tag->txt[0]==0x31)
           SetFunctionpPasswordSwitch("SETTLE",TRUE);
        else
           SetFunctionpPasswordSwitch("SETTLE",FALSE);
           return 0; 
       
    }
    else if(memcmp(Tag->name,"ER",2)==0)
    {
        //2014.04.10 kobe added for ECR TMS update
        if(ecrObj.tmsUpdate)
            ecrObj.tmsUpdate(&ecrObj,Tag->name,Tag->txt);
    }else if(strcmp(Tag->name,"TM46")==0){ 
       memset(gConfig.ETHERNET.EthernetCHANNEL ,0x00,sizeof(gConfig.ETHERNET.EthernetCHANNEL ));
        if(Tag->txt[0]==0x30){
            sprintf(gConfig.ETHERNET.EthernetCHANNEL,"ETHERNET");
         }else if(Tag->txt[0]==0x31){
            sprintf(gConfig.ETHERNET.EthernetCHANNEL,"GPRS");
         }else if(Tag->txt[0]==0x32){
            sprintf(gConfig.ETHERNET.EthernetCHANNEL,"WIFI");
         } 
        ECC_SetXMLTag(ETHERNETINFO_Path,"ETHERNET","EthernetCHANNEL",gConfig.ETHERNET.EthernetCHANNEL);
             
    }else if(strcmp(Tag->name,"TM47")==0){  
        memset(gConfig.DEVICE.READER.bPORT ,0x00,sizeof(gConfig.DEVICE.READER.bPORT ));
        if(Tag->txt[0]==0x30){
            sprintf(gConfig.DEVICE.READER.bPORT,"COM2");
         }else if(Tag->txt[0]==0x31){
            sprintf(gConfig.DEVICE.READER.bPORT,"COM1");
         }else if(Tag->txt[0]==0x32){
            sprintf(gConfig.DEVICE.READER.bPORT,"Builtin");
         } 
        ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE","READER","PORT",gConfig.DEVICE.READER.bPORT);
    }else if(strcmp(Tag->name,"TM48")==0){
          memset( gConfig.DEVICE.PMPASSWORD,0x00,sizeof(gConfig.DEVICE.PMPASSWORD));
          sprintf(gConfig.DEVICE.PMPASSWORD,"%s",Tag->txt);
          ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE","PMPASSWORD",gConfig.DEVICE.PMPASSWORD);
    }else if(strcmp(Tag->name,"TM49")==0){ 
          memset( gConfig.DEVICE.SMPASSWORD,0x00,sizeof(gConfig.DEVICE.SMPASSWORD));
          sprintf(gConfig.DEVICE.SMPASSWORD,"%s",Tag->txt);
          ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE","SMPASSWORD",gConfig.DEVICE.SMPASSWORD);
    }else if(strcmp(Tag->name,"TM50")==0){ 
          memset( gConfig.DEVICE.MMPASSWORD,0x00,sizeof(gConfig.DEVICE.MMPASSWORD));
          sprintf(gConfig.DEVICE.MMPASSWORD,"%s",Tag->txt);
          ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE","MMPASSWORD",gConfig.DEVICE.MMPASSWORD);
    }else if(strcmp(Tag->name,"TM51")==0){ 
          memset( gConfig.DEVICE.DMPASSWORD,0x00,sizeof(gConfig.DEVICE.DMPASSWORD));
          sprintf(gConfig.DEVICE.DMPASSWORD,"%s",Tag->txt);
          ECC_SetXMLTag(DEVICEINFO_Path, "DEVICE","DMPASSWORD",gConfig.DEVICE.DMPASSWORD);
    }else if(strcmp(Tag->name,"TM52")==0){
        SetAMTTABLENAME(5,Tag->txt);
        return 0;
     }else if(strcmp(Tag->name,"TM53")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[5].AMT[i] = atoi(p);  
            SetAMTTABLE(5,i,gConfig.TX.AMTTABLE[5].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
     }else if(strcmp(Tag->name,"TM54")==0){
     
        SetAMTTABLENAME(6,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM55")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[6].AMT[i] = atoi(p);  
            SetAMTTABLE(6,i,gConfig.TX.AMTTABLE[6].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
      }else if(strcmp(Tag->name,"TM56")==0){
      
        SetAMTTABLENAME(7,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM57")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[7].AMT[i] = atoi(p);  
            SetAMTTABLE(7,i,gConfig.TX.AMTTABLE[7].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
     }else if(strcmp(Tag->name,"TM58")==0){
      
        SetAMTTABLENAME(8,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM59")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[8].AMT[i] = atoi(p);  
            SetAMTTABLE(8,i,gConfig.TX.AMTTABLE[8].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
      }else if(strcmp(Tag->name,"TM60")==0){
      
        SetAMTTABLENAME(9,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM61")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[9].AMT[i] = atoi(p);  
            SetAMTTABLE(9,i,gConfig.TX.AMTTABLE[9].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
      }else if(strcmp(Tag->name,"TM62")==0){
    
        SetAMTTABLENAME(10,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM63")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[10].AMT[i] = atoi(p);  
            SetAMTTABLE(10,i,gConfig.TX.AMTTABLE[10].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
      }else if(strcmp(Tag->name,"TM64")==0){
     
        SetAMTTABLENAME(11,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM65")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[11].AMT[i] = atoi(p);  
            SetAMTTABLE(11,i,gConfig.TX.AMTTABLE[11].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
     }else if(strcmp(Tag->name,"TM66")==0){
      
        SetAMTTABLENAME(12,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM67")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[12].AMT[i] = atoi(p);  
            SetAMTTABLE(12,i,gConfig.TX.AMTTABLE[12].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
      }else if(strcmp(Tag->name,"TM68")==0){
      
        SetAMTTABLENAME(13,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM69")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[13].AMT[i] = atoi(p);  
            SetAMTTABLE(13,i,gConfig.TX.AMTTABLE[13].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
      }else if(strcmp(Tag->name,"TM70")==0){
    
        SetAMTTABLENAME(14,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM71")==0){
         memset(tmpstr,0x00,sizeof(tmpstr));
         char *delim=",";
         char *p;int i=0;          
         p = strtok(Tag->txt,delim);
         while(p!=NULL){
      
            gConfig.TX.AMTTABLE[14].AMT[i] = atoi(p);  
            SetAMTTABLE(14,i,gConfig.TX.AMTTABLE[14].AMT[i]);
            i++;
            p = strtok(NULL,delim);
         };      
     
      return 0;
    }else if(strcmp(Tag->name,"TM72")==0){
      
        SetAMTTABLENAME(0,Tag->txt);
       // SetTXInfo();
        return 0;
      }else if(strcmp(Tag->name,"TM73")==0){
      
        SetAMTTABLENAME(1,Tag->txt);
       // SetTXInfo();
        return 0;
       }else if(strcmp(Tag->name,"TM74")==0){
      
        SetAMTTABLENAME(2,Tag->txt);
       // SetTXInfo();
        return 0;
    }else if(strcmp(Tag->name,"TM75")==0){
      
        SetAMTTABLENAME(3,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM76")==0){
   
        SetAMTTABLENAME(4,Tag->txt);
       // SetTXInfo();
        return 0;
     }else if(strcmp(Tag->name,"TM77")==0){
        strcpy(gConfig.TX.AUTOLOADLIMITAMT,Tag->txt);
        ECC_SetXMLTag(TXINFO_Path,"TX","AUTOLOADLIMITAMT",gConfig.TX.AUTOLOADLIMITAMT);
    
       // SetTXInfo();
        return 0;
     }
    return d_TAG_NOTFOUND;
}

    
USHORT UnpackTMSParameter()
{
    USHORT ret;
    BYTE log[128];
    int result;

    USHORT TXCount=CheckBatchCount();
       if(TXCount>0){ 
             return d_Fail;
    }
     ret = File_exist(TMSFILE);
     if(ret !=d_OK) return  ret;
     ezxml_t ezxml_TMS;
     ezxml_TMS= LoadXMLFile(TMSFILE);
     if(ezxml_TMS == NULL){    //找不到tms file 表示無資料更新  
        SystemLog("UnpackTMSParameter","LOAD TMS FILE XML STRUCT FAIL");
         return d_ERR_NOTNEEDUPDATEPARAMETER;
     }
   ezxml_t TMSVer = ezxml_get(ezxml_TMS,"VERSION",-1);
   if(TMSVer==NULL) return d_ERR_XMLError;
   int iTMSVerNO=atoi(ezxml_attr(TMSVer,"VER"));
 // int iTMSVerNO=atoi( gConfig.TMS.PARAMETER);
// ezxml_t ConfigVer = ezxml_get(gConfigDATA,"CURRVERSION",0,"PARAMETER",-1);
// if(ConfigVer==NULL) return d_ERR_XMLError;    
// BYTE CurrParameter[6+1];
// memset(CurrParameter,0x00,sizeof(CurrParameter));
// ret= GetConfigTag("CURRVERSION","PARAMETER",CurrParameter);
   
    int iConfigVerNO=atoi(gConfig.CURRVERSION.PARAMETER);
    //版本號相同 不需更新 delete tms file

    if(iTMSVerNO==iConfigVerNO||iTMSVerNO==0){ 
        remove(TMSFILE);
        return d_ERR_NOTNEEDUPDATEPARAMETER;
    }
  
    //2014.04.24, kobe added for ECR TMS update    
    if(ecrObj.gData.tmsUpdateFld)
        myFree((void**)&ecrObj.gData.tmsUpdateFld);      
    ecrObj.gData.tmsUpdateFld = calloc(1,sizeof(TMS_UPDATE_FIELD));
    //end
    
    unsigned long CurrTime,TmsTime;
    BYTE tmpdata[14+1];
    BYTE * TMSStartData;
   fnGetRTCUNIXDataTime(&CurrTime);
   ezxml_t tag=TMSVer->child;
    while(tag!=NULL)
    {

     TMSStartData=(BYTE *)ezxml_attr(tag,"STARTDATE");
     if(TMSStartData == NULL){    //找不到tms file 表示無資料更新  
        SystemLog("UnpackTMSParameter","TAG STARTDATE Not FOUND");
        tag=tag->sibling;
        continue;
      }
     sprintf(tmpdata,"%s000000",TMSStartData);
     fngetUnixTimeCnt((BYTE *)&TmsTime,(BYTE *)&tmpdata);
    //尚未生效 暫不更新 不刪檔案
    if(CurrTime<TmsTime){  
        // tag=tag->sibling;
        //continue;
        return d_ERR_NOTNEEDUPDATEPARAMETER;
    }
       ret=usUnFormatTMSTag(tag);
      
     //  if(ret==d_ERR_NOTNEEDUPDATEPARAMETER)
    //       continue;
     
       tag=tag->sibling;
      // tag=tag->next;
    } 
 
    
   BYTE tmpbuf[64];
  // SetConfigTag("CURRVERSION","PARAMETER",ezxml_attr(TMSVer,"VER"));
   sprintf(gConfig.CURRVERSION.PARAMETER,"%s",gConfig.TMS.PARAMETER); 
   ECC_SetXMLTag2(VERSIONINFO_Path,"VERSION","CURRVERSION","PARAMETER",gConfig.CURRVERSION.PARAMETER);
 //  SetConfigTag("CURRVERSION","PARAMETER",ezxml_attr(TMSVer,"VER"));
 
  // ret= Config_SetData();
   // ret=SetCURRVERSIONInfo();
   // ConfigFunction_GetData();  
   //2014.04.15, kobe added it,response to POS first and save TMS parameters for ECR
   if(ecrObj.gData.isEcrTxn)//ecr SignOn return first
   {   
       sprintf(ecrObj.ngData->responseCode,"0000");//success
       // response data
        if((result = ecrObj.successResponse(&ecrObj)) != d_OK && !ecrObj.ngData->response2Pos)
        {
            ecrObj.errorResponse(&ecrObj, result);            
        } 
   }
          
   if(ecrObj.ecrConfigSave)       
   {           
       if((result = ecrObj.ecrConfigSave(&ecrObj))!=d_OK)           
       {                           
           ecrObj.ecrOn=FALSE; //ecr run fail, close it                           
           CTOS_Beep();CTOS_Beep();                              
       }    

       if(ecrObj.gData.tmsUpdateFld) free(ecrObj.gData.tmsUpdateFld);
       ecrObj.gData.tmsUpdateFld=NULL;
   }
   //end
   
   sprintf(tmpbuf,"版本號:%s",ezxml_attr(TMSVer,"VER"));
   //ShowMessage3line("TMS","參數已更新",tmpbuf,"",Type_ComformAnykey);
   ret=ShowMessage3line("TMS","參數已更新!",tmpbuf,"是否列印參數",Type_ComformOK);
  if(ret==d_OK){
         PrintParameter();
 } 
  //ret= InitConfigData();
  Sysinfo2_InitConfigData();
   SendDebugFile(TMSFILE);
   SendDebugFile(ConfigXML);;
   ezxml_free(ezxml_TMS);
   remove(TMSFILE);
 
    return ret;
}

