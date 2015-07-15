//# include <direct.h>
# include "ECCAPP.h"

USHORT usBuildTMInfo(TM_INFO *tm)
{

     USHORT ret;
     CTOS_RTC SetRTC;
     BYTE LOCATION_ID;
     USHORT NEW_LOCATION_ID;
     BYTE  Data[32];
      memcpy(&tm->ucTMLocationID, &gConfig.MERCHANT.STCODE,strlen(gConfig.MERCHANT.STCODE));
      memcpy (&tm->ucTMID, &gConfig.TM.bID,strlen(gConfig.TM.bID));
      memcpy(&tm->ucTMAgentNumber, &gConfig.TM.AgentNumber,sizeof(&gConfig.TM.AgentNumber));
     
      memset(Data,0x00,sizeof(Data));
       ret = CTOS_RTCGet(&SetRTC);
       if(ret==0){
           sprintf(Data,"%04d%02d%02d%02d%02d%02d",SetRTC.bYear + 2000,SetRTC.bMonth,SetRTC.bDay,SetRTC.bHour,SetRTC.bMinute,SetRTC.bSecond);
           memcpy(tm->ucTMTxnDateTime,Data,sizeof(tm->ucTMTxnDateTime));  
       }

       return ret;
}

int inBuildResetCommand(Reset_APDU_In *bAPDUReq)
{
       
       USHORT ret;
     
       BYTE LOCATION_ID;
       USHORT NEW_LOCATION_ID;
       BYTE Data[128];
     
       //終端機(TM)店號
       sprintf(Data,"%010ld",gTransData.ulSTCode);

       memcpy(bAPDUReq->ucTMLocationID,Data,sizeof(bAPDUReq->ucTMLocationID));
//DebugPrint_hex(&bAPDUReq->ucTMLocationID,sizeof(bAPDUReq->ucTMLocationID),"bAPDUReq->ucTMLocationID",DebugMode_TX);  
       memcpy(&bAPDUReq->ucTMID,&gTransData.ucTMPOSID,sizeof(bAPDUReq->ucTMID));//終端機(TM)機號
    //   memset(&bAPDUReq->ucTMID,0x00,sizeof(bAPDUReq->ucTMID));
//DebugPrint_hex(&bAPDUReq->ucTMID,sizeof(bAPDUReq->ucTMID),"bAPDUReq->ucTMID",DebugMode_TX);
       memcpy(&bAPDUReq->ucTMTxnDateTime,&gTransData.ucTxnDateTime,sizeof(bAPDUReq->ucTMTxnDateTime));//終端機(TM)交易日期時間
    //   memcpy(&bAPDUReq->ucTMSerialNumber,&gTransData.uylTMTxnSN,sizeof(bAPDUReq->ucTMSerialNumber));//終端機(TM)交易序號
//DebugPrint_hex(&bAPDUReq->ucTMTxnDateTime,sizeof(bAPDUReq->ucTMTxnDateTime),"bAPDUReq->ucTMTxnDateTime",DebugMode_TX);  
       sprintf(Data,"%06ld",gTransData.ulTMTxnSN);
       memcpy(bAPDUReq->ucTMSerialNumber,Data,sizeof(bAPDUReq->ucTMSerialNumber));
 
       memcpy(&bAPDUReq->ucTMAgentNumber,&gTransData.ucTMAgentNumber,sizeof(bAPDUReq->ucTMAgentNumber));//終端機(TM)收銀員代號
       fngetUnixTimeCnt((BYTE *)&bAPDUReq->ucTxnDateTime,(BYTE *)&gTransData.ucTxnDateTime); //交易日期時間(UnixDateTime)
 //DebugPrint_hex(&bAPDUReq->ucTxnDateTime,sizeof(bAPDUReq->ucTxnDateTime),"bAPDUReq->ucTxnDateTime",DebugMode_TX);    
        bAPDUReq->ucLocationID =gTransData.ucLocationID;
        memcpy(& bAPDUReq->ucCPULocationID,gTransData.ucSubMerchantID,sizeof(gTransData.ucSubMerchantID));
      //  bAPDUReq->ucSPID =gTransData.ucSPID;
        bAPDUReq->ucSPID=0x00;
      //  memcpy(&bAPDUReq->ucCPUSPID,&gTransData.ucCPUSPID,sizeof(gTransData.ucCPUSPID));
       memset(&bAPDUReq->ucCPUSPID,0x00,sizeof(bAPDUReq->ucCPUSPID));       
       memset(Data,0x00,sizeof(Data));
       wub_str_2_hex(gConfig.DEVICE.SAMSLOT, bAPDUReq->ucSAMSlot, 2);
     
	return(sizeof(Reset_APDU_In));
}

int inBuildSignOnCommand(SignOn_APDU_In *bAPDUReq)
{
        unsigned int iret;
        TermHost_t  TermHost;
  
        memcpy(&bAPDUReq->ucHTAC,&gTransData.HTAC,sizeof(gTransData.HTAC));
        memcpy(&bAPDUReq->ucHATOKEN,&gTransData.HostToken,sizeof(gTransData.HostToken));
       memcpy((unsigned char *)&bAPDUReq->stSAMParaSettingInfo_t,(unsigned char *)&gTransData.CSAMPARA,sizeof(gTransData.CSAMPARA));
       //bAPDUReq->stSAMParaSettingInfo_t.ucSAMUpdateOption=0x00; //2014.08.25, apdu.c line64 sigon 更新參數flag打開
      
	bAPDUReq->stSAMParameterInfo_t.bCPDReadFlag0 =gTransData.ucCPDReadFlag;
	bAPDUReq->stSAMParameterInfo_t.bCPDReadFlag1 = gTransData.ucCPDReadFlag>>4;
	bAPDUReq->stSAMParameterInfo_t.bOneDayQuotaWrite2 = gTransData.ucOneDayQuotaWrite;
	bAPDUReq->stSAMParameterInfo_t.bOneDayQuotaWrite3 = gTransData.ucOneDayQuotaWrite>>4;
	bAPDUReq->stSAMParameterInfo_t.bSAMSignOnControlFlag4 =gTransData.ucSAMSignOnControlFlag;
	bAPDUReq->stSAMParameterInfo_t.bSAMSignOnControlFlag5 =gTransData.ucSAMSignOnControlFlag>>4;
        
     
	bAPDUReq->stSAMParameterInfo_t.bCheckEVFlag6 =  gTransData.stTermHostInfo_t.ucCheckEVFlag;
	bAPDUReq->stSAMParameterInfo_t.bDeductLimitFlag7 =  gTransData.stTermHostInfo_t.ucDeductLimitFlag;
	bAPDUReq->stSAMParameterInfo_t.bOneDayQuotaFlag0 =  gTransData.stTermHostInfo_t.ucOneDayQuotaFlag;
	bAPDUReq->stSAMParameterInfo_t.bOneDayQuotaFlag1 =  gTransData.stTermHostInfo_t.ucOneDayQuotaFlag >> 4;
	bAPDUReq->stSAMParameterInfo_t.bOnceQuotaFlag2 =  gTransData.stTermHostInfo_t.ucOnceQuotaFlag;
	bAPDUReq->stSAMParameterInfo_t.bCheckDeductFlag3 = gTransData.stTermHostInfo_t.ucCheckDeductFlag;
        
	memcpy(bAPDUReq->stSAMParameterInfo_t.ucOneDayQuota, gTransData.stTermHostInfo_t.ucOneDayQuota,sizeof(bAPDUReq->stSAMParameterInfo_t.ucOneDayQuota));//One Day Quota
	memcpy(bAPDUReq->stSAMParameterInfo_t.ucOnceQuota, gTransData.stTermHostInfo_t.ucOnceQuota,sizeof(bAPDUReq->stSAMParameterInfo_t.ucOnceQuota));//Once Quota
	memcpy(bAPDUReq->stSAMParameterInfo_t.ucCheckDeductValue,gTransData.stTermHostInfo_t.ucCheckDeductValue,sizeof(bAPDUReq->stSAMParameterInfo_t.ucCheckDeductValue));//Check Deduct Value
	bAPDUReq->stSAMParameterInfo_t.ucAddQuotaFlag = gTransData.stTermHostInfo_t.ucAddQuotaFlag;//Add Quota Flag
	memcpy(bAPDUReq->stSAMParameterInfo_t.ucAddQuota,gTransData.stTermHostInfo_t.ucAddQuota,sizeof(bAPDUReq->stSAMParameterInfo_t.ucAddQuota));//Add Quota

	bAPDUReq->ucHashType=gTransData.ucCPUHashTYPE;
//DebugPrint_hex(&bAPDUReq->ucHashType,sizeof(bAPDUReq->ucHashType),"ucHashType"); 
	memcpy((unsigned char *)&bAPDUReq->ucCPUEDC,(unsigned char *)&gTransData.ucCPUEDC,sizeof(bAPDUReq->ucCPUEDC));//EDC,Hash Value
//DebugPrint_hex(&bAPDUReq->ucCPUEDC,sizeof(bAPDUReq->ucCPUEDC),"ucCPUEDC"); 
        return(sizeof(SignOn_APDU_In));
}

int inBuildReadCardBasicDataCommand(ReadCardBasicData_APDU_In *bAPDUReq)
{
    	
	bAPDUReq->ucLCDControlFlag=gucLCDControlFlag;
	
	return(sizeof(ReadCardBasicData_APDU_In));
}

int inBuildTxnReqOnlineCommand(TxnReqOnline_APDU_In *bAPDUReq)
{
   
       bAPDUReq->ucMsgType=gTransData.ucMsgType;
	bAPDUReq->ucSubType=gTransData.ucSubType;   
         BYTE Data[10+1];
   DebugPrint_hex(&gTransData.ucMsgType,sizeof(gTransData.ucMsgType),"ucMsgType",DebugMode_TX);   
   DebugPrint_hex(&gTransData.ucSubType,sizeof(gTransData.ucSubType),"ucSubType",DebugMode_TX);   
       memcpy(&bAPDUReq->ucTxnAmt,&gTransData.lTxnAmt,sizeof(bAPDUReq->ucTxnAmt));
	bAPDUReq->ucReadPurseFlag=gTransData.ucReadPurseFlag;
	
        sprintf(Data,"%010ld",gTransData.ulSTCode);
       memcpy(bAPDUReq->ucTMLocationID,Data,sizeof(bAPDUReq->ucTMLocationID));
        DebugPrint_hex(bAPDUReq->ucTMLocationID,sizeof(bAPDUReq->ucTMLocationID),"ucTMLocationID",1);  
       memcpy(&bAPDUReq->ucTMID,&gTransData.ucTMPOSID,sizeof(bAPDUReq->ucTMID));//終端機(TM)機號
       
       memcpy(&bAPDUReq->ucTMTxnDateTime,&gTransData.ucTxnDateTime,sizeof(bAPDUReq->ucTMTxnDateTime));//終端機(TM)交易日期時間
    //   memcpy(&bAPDUReq->ucTMSerialNumber,&gTransData.uylTMTxnSN,sizeof(bAPDUReq->ucTMSerialNumber));//終端機(TM)交易序號
     
       //2014.06.23, kobe marked it 
       //sprintf(bAPDUReq->ucTMSerialNumber,"%06ld",gTransData.ulTMTxnSN);
       //2014.06.23, kobe changed ulTMTxnSN to ulTxnSN
       sprintf(bAPDUReq->ucTMSerialNumber,"%06ld",gTransData.usTXSN);
       
     //  sprintf(bAPDUReq->ucTMSerialNumber,"000000");
       memcpy(&bAPDUReq->ucTMAgentNumber,&gTransData.ucTMAgentNumber,sizeof(bAPDUReq->ucTMAgentNumber));//終端機(TM)收銀員代號
       fngetUnixTimeCnt((BYTE *)bAPDUReq->ucTxnDateTime,(BYTE *)&gTransData.ucTxnDateTime); //交易日期時間(UnixDateTime)
      DebugPrint_hex(bAPDUReq->ucTxnDateTime,sizeof(bAPDUReq->ucTxnDateTime),"ucTxnDateTime",DebugMode_TX);   
	
	memset(bAPDUReq->ucRFU,0x00,sizeof(bAPDUReq->ucRFU));//保留
	
	return(sizeof(TxnReqOnline_APDU_In));
}


int inBuildAuthTxnOnlineCommand(AuthTxnOnline_APDU_In *bAPDUReq)
{
     
       
        BYTE DateStr[14+1];
	  memset(DateStr,0x00,sizeof(DateStr));
 	if(gTransData.ucTXTYPE==TXTYPE_SETVALUE){
		memcpy(bAPDUReq->ucExpiryDate,&gTransData.ucCardVaildDateAfterSet,sizeof(bAPDUReq->ucExpiryDate));//Expiry Date
		memcpy(bAPDUReq->ucProfileExpiryDate,&gTransData.ucNEWProfileExpiryDate,sizeof(bAPDUReq->ucProfileExpiryDate));//Profile Expiry Date
		fnLongToUnix(DateStr,(unsigned long *)bAPDUReq->ucProfileExpiryDate,14);
		fngetDosDateCnt(DateStr,bAPDUReq->ucProfileExpiryDateDOS);//Profile Expiry Date(DOS)
	}else{
		memset(bAPDUReq->ucExpiryDate,0x00,sizeof(bAPDUReq->ucExpiryDate));//Expiry Date
		memset(bAPDUReq->ucProfileExpiryDate,0x00,sizeof(bAPDUReq->ucProfileExpiryDate));//Profile Expiry Date
		memset(bAPDUReq->ucProfileExpiryDateDOS,0x00,sizeof(bAPDUReq->ucProfileExpiryDateDOS));//Profile Expiry Date(DOS)
	}
	
	if(gTransData.ucCPUPurseVersionNUM== MIFARE)
		memset(bAPDUReq->ucTxnToken,0x00,sizeof(bAPDUReq->ucTxnToken));//Txn Token
	else{
		//memcpy((unsigned char *)bAPDUReq->ucTxnToken,(unsigned char *)&gTransData.CPUTermCrypto,sizeof(gTransData.CPUTermCrypto));
              //  wub_str_2_hex((unsigned char *)&gTransData.HostToken,(unsigned char *)bAPDUReq->ucHTAC,sizeof(gTransData.HostToken));
            memcpy((unsigned char *)bAPDUReq->ucTxnToken,(unsigned char *)&gTransData.HostToken,sizeof(gTransData.HostToken));
            wub_str_2_hex((unsigned char *)&gTransData.CPUTermCrypto,(unsigned char *)bAPDUReq->ucHTAC,sizeof(gTransData.CPUTermCrypto));
	}
	
        if(gTransData.ucCPUPurseVersionNUM == LEVEL2)
		memset(bAPDUReq->ucHTAC,0x00,sizeof(bAPDUReq->ucHTAC));//HTAC
	else
		memcpy((unsigned char *)bAPDUReq->ucHTAC,(unsigned char *)&gTransData.HTAC,sizeof(gTransData.HTAC));
   	bAPDUReq->ucLCDControlFlag=gTransData.ucLCDControlFlag;
	memset(bAPDUReq->ucRFU,0x00,sizeof(bAPDUReq->ucRFU));//保留

	return(sizeof(AuthTxnOnline_APDU_In));
}


int inBuildTxnReqOfflineCommand(TxnReqOffline_APDU_In *bAPDUReq)
{
   
	bAPDUReq->ucMsgType=gTransData.ucMsgType;
	bAPDUReq->ucSubType=gTransData.ucSubType;   
       
   	memcpy(&bAPDUReq->ucTxnAmt,&gTransData.lTxnAmt,sizeof(bAPDUReq->ucTxnAmt));
       bAPDUReq->ucReadPurseFlag=gTransData.ucReadPurseFlag;
       sprintf(bAPDUReq->ucTMLocationID,"%010ld",gTransData.ulSTCode);
       memcpy(&bAPDUReq->ucTMID,&gTransData.ucTMPOSID,sizeof(bAPDUReq->ucTMID));//終端機(TM)機號
       memcpy(&bAPDUReq->ucTMTxnDateTime,&gTransData.ucTxnDateTime,sizeof(bAPDUReq->ucTMTxnDateTime));//終端機(TM)交易日期時間
    
       //2014.6.23, kobe marked it
       //sprintf(bAPDUReq->ucTMSerialNumber,"%ld",gTransData.ulTMTxnSN);
       //2014.06.23, kobe changed ulTMTxnSN to usTXSN
       sprintf(bAPDUReq->ucTMSerialNumber,"%ld",gTransData.usTXSN);
       
       memcpy(&bAPDUReq->ucTMAgentNumber,&gTransData.ucTMAgentNumber,sizeof(bAPDUReq->ucTMAgentNumber));//終端機(TM)收銀員代號
       fngetUnixTimeCnt(bAPDUReq->ucTxnDateTime,(BYTE *)&gTransData.ucTxnDateTime); //交易日期時間(UnixDateTime)
        
	
	memset(bAPDUReq->ucRefundFee,0x00,sizeof(bAPDUReq->ucRefundFee));//Refund Fee
	memset(bAPDUReq->ucBrokenFee,0x00,sizeof(bAPDUReq->ucBrokenFee));//Broken Fee
	bAPDUReq->ucLCDControlFlag = 0x00;//LCD Control Flag
	memset(bAPDUReq->ucRFU,0x00,sizeof(bAPDUReq->ucRFU));//保留
 //DebugPrint_hex(&gTransData.ucMsgType,sizeof(gTransData.ucMsgType),"ucMsgType",DebugMode_TX);   
// DebugPrint_hex(&gTransData.ucSubType,sizeof(gTransData.ucSubType),"ucSubType",DebugMode_TX); 
// DebugPrint_hex(&gTransData.ucCardID,sizeof(gTransData.ucCardID),"ucCardID",DebugMode_TX); 
 //DebugPrint_hex(&gTransData.ucTxnAmt,sizeof(gTransData.ucTxnAmt),"ucTxnAmt",DebugMode_TX); 
 //DebugPrint_hex(&gTransData.ulSTCode,sizeof(gTransData.ulSTCode),"ulSTCode",DebugMode_TX); 
 //DebugPrint_hex(&gTransData.ucTMPOSID,sizeof(gTransData.ucTMPOSID),"ucTMID",DebugMode_TX); 
// DebugPrint_hex(&bAPDUReq->ucTxnDateTime,sizeof(bAPDUReq->ucTxnDateTime),"ucTxnDateTime",DebugMode_TX); 
	return(sizeof(TxnReqOffline_APDU_In));
}

int inBuildAuthTxnOfflineCommand(AuthTxnOffline_APDU_In *bAPDUReq)
{
        BYTE ucPurseVersionNumber;
    
	if(gTransData.ucCPUPurseVersionNUM== MIFARE)
             	memcpy((unsigned char *)&bAPDUReq->ucHVCrypto_HTAC,(unsigned char *)&gTransData.HTAC,sizeof(gTransData.HTAC));
	else
             memcpy((unsigned char *)&bAPDUReq->ucHVCrypto_HTAC,(unsigned char *)&gTransData.HostCrypto,sizeof(gTransData.HostCrypto));
		//memcpy((unsigned char *)&bAPDUReq->ucHVCrypto_HTAC,(unsigned char *)&gTransData.CPUMAC_HCrypto,sizeof(gTransData.CPUMAC_HCrypto));
      bAPDUReq->ucLCDControlFlag=gTransData.ucLCDControlFlag;
	
	memset(bAPDUReq->ucRFU,0x00,sizeof(bAPDUReq->ucRFU));

	return(sizeof(AuthTxnOffline_APDU_In));
}



int inBuildLockCardCommand(LockCard_APDU_In_2 *bAPDUReq)
{

	bAPDUReq->ucMsgType = 0x22;//Msg Type
	bAPDUReq->ucSubType = 0x00;//Sub Type
	memcpy((unsigned char *)&bAPDUReq->ucCardID,(unsigned char *)gTransData.ucCardID,sizeof(gTransData.ucCardID));
       
	fngetUnixTimeCnt(bAPDUReq->ucTxnDateTime,gTransData.ucTMTxnDateTime); //交易日期時間(UnixDateTime)
	bAPDUReq->ucLockReason = gTransData.ucLockReason;//Lock Reason

	return(sizeof(LockCard_APDU_In_2));
}
/*
int inBuildReadDongleDeductCommand(ReadDongleDeduct_APDU_In *bAPDUReq,ReadDongleDeduct_TM_In *bTMIn)
{

	fnASCTOBIN(bAPDUReq->ucLogSeqNo,bTMIn->anLogSeqNo,5,2,DECIMAL);//讀取第幾筆Log

	return(sizeof(ReadDongleDeduct_APDU_In));
}
 */



int inBuildReadCardDeductCommand(ReadCardDeduct_APDU_In *bAPDUReq)
{

	//bAPDUReq->ucLogIndex = gTransData.ucLogIndex;//讀取第幾組Log

	return(sizeof(ReadCardDeduct_APDU_In));
}
int inBuildReadCardCommand(ReadCardNumber_APDU_In * bAPDUReq)
{
 
   memset(&bAPDUReq->ucTXNAMT,0x00,sizeof(bAPDUReq->ucTXNAMT));
   bAPDUReq->LCDContralFalg=0x00;
   return(sizeof(ReadCardNumber_APDU_In));
}