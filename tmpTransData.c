int inBuildResetOutput(int inTxnType,TRANS_DATA2 *APIOut, Reset_APDU_In *DongleIn, Reset_APDU_Out *DongleOut)
{
	int inTMOutLen;
        USHORT ret;
	Store_Data stStore_DataInfo_t;
        TermHost_t stTermHostInfo_t;
        TermPara_t stTermParaInfo_t;
        CPUSAMInfo_t  stCPUSAMInfo_t;
       	LastSingOn_t  stLastSignOnInfo_t;
	
        ezxml_t ezxml_Trans;
             
        inTMOutLen = sizeof(TRANS_DATA);
	
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID 0100
 
	vdBuildProcessingCode(inTxnType,0x00,0x00,0x00,APIOut->ucProcessCode);//Processing Code 0300
        //trans sn 1100
        
        fnLongToUnix(APIOut->ucTxnDateTime,(unsigned long *)DongleIn->ucTxnDateTime,14);// Txn Date Time
        memcpy(APIOut->ucTxnData,&APIOut->ucTxnDateTime,8); //1300
        APIOut->ucTxnData[8]=0x00;
        memcpy(APIOut->ucTxnTime,&APIOut->ucTxnDateTime[8],6); //1200
         APIOut->ucTxnTime[6]=0x00;
        wub_hex_2_str(DongleOut->ucDeviceID,(BYTE *)&APIOut->ucDeviceID,sizeof(DongleOut->ucDeviceID));//4101\
        inBuildTxnDataTime(DongleIn->ucTxnDateTime, &APIOut->ucTxnDateTime,&APIOut->ucTxnData, &APIOut->ucTxnTime);
         inBuildCPUDEVICEID((BYTE *)&DongleOut->ucCPUDeviceID, (BYTE* )&APIOut->ucCPUDeviceID);//4100
        //4102
       ezxml_t TAG = ezxml_get(gConfigDATA, "ETHERNET", 0, "LOCAL",0, "IP", -1);
       if(TAG !=NULL)  sprintf(APIOut->ucTerminalIP,"%s",TAG->txt);//4102
       
       TAG = ezxml_get(gConfigDATA, "DEVICE",0,"EDC",0,"MechineID",-1);
       if(TAG !=NULL)  sprintf(APIOut->ucMechineID,"%s",TAG->txt);//4103
     
       //4104
       wub_hex_2_str(DongleOut->ucReaderID,APIOut->ucReaderSN,sizeof(DongleOut->ucReaderID));
       
       
       ret=GetConfigTag("MERCHANT","MERCHANTID",APIOut->ucCPUSPID);// new location id 4200
       ret=GetConfigTag("MERCHANT","NewLocationID",APIOut->ucSubMerchantID);// new location id 4210
       //4813
        BYTE ucHostSpecVersionNo = DongleOut->ucHostSpecVersionNo;//CPU Spec. Version Number
	wub_hex_2_str(&ucHostSpecVersionNo,APIOut->ucHostSpecVersionNo,sizeof(ucHostSpecVersionNo));//4820
        
   
        BYTE ucOneDayQuotaWrite = DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite2 |
				     (DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite3<<4);//CPU One Day Quota Write Flag 4823
	wub_hex_2_str(&ucOneDayQuotaWrite,APIOut->ucOneDayQuotaWrite,sizeof(ucOneDayQuotaWrite)); 
      
        BYTE  bCPDReadFlag=DongleOut->stSAMParameterInfo_t.bCPDReadFlag0| DongleOut->stSAMParameterInfo_t.bCPDReadFlag1<<4;
        wub_hex_2_str((BYTE *)&bCPDReadFlag,(BYTE *)&APIOut->ucCPDReadFlag,sizeof(bCPDReadFlag));//4824
     //4825 cpu credit balance change flag
        
        
        wub_hex_2_str(&DongleOut->ucSAMKeyVersion,APIOut->ucKeyVersion,1);//5301
        APIOut->ucKeyVersion[0]=0x30;
        APIOut->ucKeyVersion[1]=0x31;
   
 
         wub_hex_2_str(DongleOut->ucRSAM,APIOut->ucRSAM,sizeof(DongleOut->ucRSAM));//5307
	
	
        wub_hex_2_str(DongleOut->ucRHOST,APIOut->ucRHOST,sizeof(DongleOut->ucRHOST));//5308

        wub_hex_2_str(DongleOut->ucSAMID,APIOut->ucSAMID,sizeof(DongleOut->ucSAMID));//5361
        wub_hex_2_str(DongleOut->ucSAMSN,APIOut->ucSAMSN,sizeof(DongleOut->ucSAMSN));//5362
        wub_hex_2_str(DongleOut->ucSAMCRN,APIOut->ucSAMCRN,sizeof(DongleOut->ucSAMCRN));//5363
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    // TAG 5364 
        stCPUSAMInfo_t.ucSAMVersion = DongleOut->ucSAMVersion;//SAM Version Number
   	memcpy(stCPUSAMInfo_t.ucSAMUsageControl,DongleOut->ucSAMUsageControl,sizeof(stCPUSAMInfo_t.ucSAMUsageControl));//SAM Usage Control
	stCPUSAMInfo_t.ucSAMAdminKVN = DongleOut->ucSAMAdminKVN;//SAM Admin KVN
	stCPUSAMInfo_t.ucSAMIssuerKVN = DongleOut->ucSAMIssuerKVN;//SAM Issuer KVN
	memcpy(stCPUSAMInfo_t.ucTagListTable,DongleOut->ucTagListTable,sizeof(stCPUSAMInfo_t.ucTagListTable));//SAM Tag List Table
	memcpy(stCPUSAMInfo_t.ucSAMIssuerSpecData,DongleOut->ucSAMIssuerSpecData,sizeof(stCPUSAMInfo_t.ucSAMIssuerSpecData));//SAM Issuer Spec Data
	wub_hex_2_str((BYTE *)&stCPUSAMInfo_t,(BYTE *)&APIOut->CPUSAMINFOData,sizeof(stCPUSAMInfo_t));
        //TAG 5365
         wub_hex_2_str(DongleOut->ucAuthCreditLimit,APIOut->SAMtransInfoData.ucAuthCreditLimit,sizeof(DongleOut->ucAuthCreditLimit));
        //memcpy(APIOut->ucAuthCreditLimit,DongleOut->ucAuthCreditLimit,sizeof(APIOut->ucAuthCreditLimit));//CPU Auth Credit Limit
	 wub_hex_2_str(DongleOut->ucAuthCreditBalance,APIOut->SAMtransInfoData.ucAuthCreditBalance,sizeof(DongleOut->ucAuthCreditBalance));
         //memcpy(APIOut->ucAuthCreditBalance,DongleOut->ucAuthCreditBalance,sizeof(APIOut->ucAuthCreditBalance));//CPU Auth Credit Balance
         wub_hex_2_str(DongleOut->ucAuthCreditCumulative,APIOut->SAMtransInfoData.ucAuthCreditCumulative,sizeof(DongleOut->ucAuthCreditCumulative));
        // memcpy(APIOut->ucAuthCreditCumulative,DongleOut->ucAuthCreditCumulative,sizeof(APIOut->ucAuthCreditCumulative));//CPU Auth Credit Cumulative
	 wub_hex_2_str(DongleOut->ucAuthCancelCreditCumulative,APIOut->SAMtransInfoData.ucAuthCancelCreditCumulative,sizeof(DongleOut->ucAuthCancelCreditCumulative));
       //  memcpy(APIOut->ucAuthCancelCreditCumulative,DongleOut->ucAuthCancelCreditCumulative,sizeof(APIOut->ucAuthCancelCreditCumulative));//CPU Auth Cancel Credit Cumulative
	
        
        //5366
         wub_hex_2_str(DongleOut->ucSingleCreditTxnAmtLimit,APIOut->ucSingleCreditTxnAmtLimit,sizeof(DongleOut->ucSingleCreditTxnAmtLimit));
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //CPU SAM Sign On Control Flag 5369
          BYTE ucSAMSignOnControlFlag = DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag4 |
					(DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag5<<4);
	
        wub_hex_2_str(&ucSAMSignOnControlFlag,APIOut->ucSAMSignOnControlFlag,sizeof(ucSAMSignOnControlFlag));
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        //TAG 5370
        wub_hex_2_str((BYTE *)&DongleOut->stLastSignOnInfo_t,(BYTE *)&APIOut->CPULastSignonInfoData,sizeof(DongleOut->stLastSignOnInfo_t));
       //5501 
        
        //5503
         ret=GetConfigTag("MERCHANT","STCODE",APIOut->ucSubMerchantID);// new location id 4200
        //5504
        memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(DongleIn->ucTMID));
        //5514     
         memcpy(APIOut->ucTMTxnDateTime,DongleIn->ucTMTxnDateTime,8);
        //5510
         memcpy(APIOut->ucTMAgentNumber,DongleIn->ucTMAgentNumber,sizeof(DongleIn->ucTMAgentNumber));

        
        //6000
        wub_hex_2_str(DongleOut->ucReaderFWVersion,APIOut->ucReaderFWVersion,sizeof(DongleOut->ucReaderFWVersion));
        //TAG 6001
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////       
        //  TAG 6002 
        memcpy(stTermHostInfo_t.ucOneDayQuota,DongleOut->stSAMParameterInfo_t.ucOneDayQuota,sizeof(APIOut->stTermHostInfo_t.ucOneDayQuota));//One Day Quota
        stTermHostInfo_t.ucOneDayQuotaFlag = DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag0 |
						    (DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag1 << 4);//One Day Quota Flag
	stTermHostInfo_t.ucOnceQuotaFlag = DongleOut->stSAMParameterInfo_t.bOnceQuotaFlag2;//Once Quota Flag
	memcpy(stTermHostInfo_t.ucOnceQuota,DongleOut->stSAMParameterInfo_t.ucOnceQuota,sizeof(APIOut->stTermHostInfo_t.ucOnceQuota));//Once Quota
	stTermHostInfo_t.ucCheckEVFlag = DongleOut->stSAMParameterInfo_t.bCheckEVFlag6;//Check EV Flag
	stTermHostInfo_t.ucAddQuotaFlag = DongleOut->stSAMParameterInfo_t.ucAddQuotaFlag;//Add Quota Flag
	memcpy(stTermHostInfo_t.ucAddQuota,DongleOut->stSAMParameterInfo_t.ucAddQuota,sizeof(stTermHostInfo_t.ucAddQuota));//Add Quota
	stTermHostInfo_t.ucCheckDeductFlag = DongleOut->stSAMParameterInfo_t.bCheckDeductFlag3;//Check Debit Flag
	memcpy(stTermHostInfo_t.ucCheckDeductValue,DongleOut->stSAMParameterInfo_t.ucCheckDeductValue,sizeof(stTermHostInfo_t.ucCheckDeductValue));//Check Debit
	stTermHostInfo_t.ucDeductLimitFlag = DongleOut->stSAMParameterInfo_t.bDeductLimitFlag7;//Deduct Limit Flag
	
        memcpy(stTermHostInfo_t.ucAPIVersion,API_VERSION,3);//API Version 
	stTermHostInfo_t.ucAPIVersion[3] = 0x00;
        wub_hex_2_str((BYTE *)&stTermHostInfo_t,(BYTE *)&APIOut->stTermHostInfo_t,sizeof(stTermHostInfo_t)); 
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
      
        
        //TAG TermHost 6003       
	
	memcpy(stTermParaInfo_t.ucDeMAC,DongleOut->ucDeMAC,sizeof(stTermParaInfo_t.ucDeMAC));//De MAC
        memcpy(stTermParaInfo_t.ucCancelCreditQuota,DongleOut->ucCancelCreditQuota,sizeof(stTermParaInfo_t.ucCancelCreditQuota));//
        wub_hex_2_str((BYTE *)&stTermParaInfo_t,(BYTE *)&APIOut->stTermParaInfo_t,sizeof(stTermParaInfo_t));
       //TAG 6004
           ret=GetConfigTag("BLC","VERSION",APIOut->ucBLVersion);//ucBLVersion 4002
       //6400
         wub_hex_2_str(DongleOut->ucSTAC,APIOut->ucSTAC,sizeof(DongleOut->ucSTAC));//6400
        
       //6408
         wub_hex_2_str(DongleOut->ucSATOKEN,APIOut->ucSATOKEN,sizeof(DongleOut->ucSATOKEN));
         
        wub_hex_2_str(DongleOut->ucCPUSAMID,APIOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID));
	wub_hex_2_str(DongleOut->ucSTC,APIOut->ucSTC,sizeof(DongleOut->ucSTC));

	

     
             
         
        vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
       	memcpy(stStore_DataInfo_t.ucDeviceID,DongleOut->ucDeviceID,sizeof(stStore_DataInfo_t.ucDeviceID));//Device ID
	memcpy(stStore_DataInfo_t.ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(stStore_DataInfo_t.ucTxnDateTime));//Txn Date Time
	memcpy(stStore_DataInfo_t.ucCPUDeviceID,DongleOut->ucCPUDeviceID,sizeof(stStore_DataInfo_t.ucCPUDeviceID));//CPU SP ID
	memcpy(stStore_DataInfo_t.ucSTC,DongleOut->ucSTC,sizeof(stStore_DataInfo_t.ucSTC));//CPU SAM Txn Cnt
        vdSaveReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));       

	ezxml_t TAG_READERID,TAG2,TAG3,TAG4,TAG_MerchantID,TAG6,TAG_DeviceID,TAG_STC;
	
	LoadConfigFile();
        TAG_MerchantID = ezxml_get(gConfigDATA,  "DEVICE",0,"MerchantID",-1);
	 if(TAG_MerchantID !=NULL){
                ezxml_set_txt(TAG_MerchantID,APIOut->ucCPUSPID);
        }
        TAG_STC = ezxml_get(gConfigDATA,  "DEVICE",0,"MIFARE",0,"STC", -1);
	 if(TAG_STC !=NULL){
                ezxml_set_txt(TAG_STC,APIOut->ucSTC);
        }
      
        TAG_DeviceID = ezxml_get(gConfigDATA,  "DEVICE",0,"MIFARE",0,"DEVICEID", -1);
	 if(TAG_DeviceID !=NULL){
                ezxml_set_txt(TAG_DeviceID,APIOut->ucDeviceID);
        }
	TAG_READERID = ezxml_get(gConfigDATA, "DEVICE",0,"READER",0,"READERID", -1);
	 if(TAG_READERID !=NULL){
                wub_hex_2_str(DongleOut->ucReaderID,APIOut->ucReaderSN,sizeof(DongleOut->ucReaderID));
                ezxml_set_txt(TAG_READERID,APIOut->ucReaderSN);
        }
 
	
	TAG2 = ezxml_get(gConfigDATA,  "DEVICE",0,"CPU",0,"DEVICEID", -1);
	 if(TAG2 !=NULL){
              ezxml_set_txt(TAG2, APIOut->ucCPUDeviceID);
         }
   
	
	TAG3 = ezxml_get(gConfigDATA, "DEVICE",0,"READER",0,"READERFWVER", -1);
	 if(TAG3 !=NULL){
	        ezxml_set_txt(TAG3,APIOut->ucReaderFWVersion);        
         }    
 
	TAG4 = ezxml_get(gConfigDATA,  "DEVICE",0,"READER",0,"MIFARE",0,"SAMID", -1);
	 if(TAG4 !=NULL){
                 ezxml_set_txt(TAG4,APIOut->ucSAMID);
         }
 
       SaveConfigFile(); 
       return(0);
}
int inBuildSignOnOutput(int inTxnType,TRANS_DATA2 *APIOut,SignOn_APDU_In *DongleIn,SignOn_APDU_Out *DongleOut)
{
        Store_Data stStore_DataInfo_t;
        vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	memset(APIOut,0x00,sizeof(TRANS_DATA));
        
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	
	vdBuildProcessingCode(inTxnType,0x00,0x00,0x00,APIOut->ucProcessCode);//Processing Code
        
        wub_hex_2_str(stStore_DataInfo_t.ucDeviceID,APIOut->ucDeviceID,sizeof(stStore_DataInfo_t.ucDeviceID));
        inBuildCPUDEVICEID((BYTE *)&stStore_DataInfo_t.ucCPUDeviceID, (BYTE *)&APIOut->ucCPUDeviceID);
	inBuildTxnDataTime((ULONG)stStore_DataInfo_t.ucTxnDateTime,(BYTE *)&APIOut->ucTxnDateTime,(BYTE *)&APIOut->ucTxnData, (BYTE *)&APIOut->ucTxnTime);	

        wub_hex_2_str(stStore_DataInfo_t.ucSTC,APIOut->ucSTC,sizeof(stStore_DataInfo_t.ucSTC));        
        wub_hex_2_str(&DongleOut->ucCreditBalanceChangeFlag,APIOut->ucCPUCreditBalanceChangeFlag,sizeof(DongleOut->ucCreditBalanceChangeFlag));        

        wub_hex_2_str(DongleOut->ucCACrypto,APIOut->CPUTermCrypto,sizeof(DongleOut->ucCACrypto));     
	//memcpy(APIOut->ucCACrypto,DongleOut->ucCACrypto,sizeof(APIOut->ucCACrypto));//CACrypto

	return(0);
}

int inBuildSignOnQueryOutput(int inTxnType,TRANS_DATA *APIOut,SignOnQuery_APDU_Out *DongleOut)
{
int inTMOutLen;
TermHost_t TermHost;
TermPara_t TermPara;
	inTMOutLen = sizeof(TRANS_DATA);

        wub_hex_2_str((unsigned char *)&DongleOut->ucAuthCreditLimit,(unsigned char *)&APIOut->SAMtransInfoData,3+3+3+3);     
/*	vdUIntToAsc(DongleOut->ucAuthCreditLimit,sizeof(DongleOut->ucAuthCreditLimit),APIOut->anAuthCreditLimit,sizeof(APIOut->anAuthCreditLimit),' ',10);
	vdUIntToAsc(DongleOut->ucAuthCreditBalance,sizeof(DongleOut->ucAuthCreditBalance),APIOut->anAuthCreditBalance,sizeof(APIOut->anAuthCreditBalance),' ',10);
	vdUIntToAsc(DongleOut->ucAuthCreditCumulative,sizeof(DongleOut->ucAuthCreditCumulative),APIOut->anAuthCreditCumulative,sizeof(APIOut->anAuthCreditCumulative),' ',10);
	vdUIntToAsc(DongleOut->ucAuthCancelCreditCumulative,sizeof(DongleOut->ucAuthCancelCreditCumulative),APIOut->anAuthCancelCreditCumulative,sizeof(APIOut->anAuthCancelCreditCumulative),' ',10);
 */
       BYTE  anCPDReadFlag = DongleOut->stSAMParameterInfo_t.bCPDReadFlag0 |
			       (DongleOut->stSAMParameterInfo_t.bCPDReadFlag1<<3);//CPU CPD Read
//			       (DongleOut->stSAMParameterInfo_t.bCPDReadFlag1<<1);//CPU CPD Read
        wub_hex_2_str(&anCPDReadFlag,APIOut->ucCPDReadFlag,1);     
	BYTE anOneDayQuotaWrite = DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite2 |
				     (DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite3<<1);//CPU One Day Quota Write Flag
        wub_hex_2_str(&anOneDayQuotaWrite,APIOut->ucOneDayQuotaWrite,1);  
        
	BYTE anSAMSignOnControlFlag = DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag4 |
					(DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag5<<4);//CPU SAM Sign On Control Flag
        wub_hex_2_str(&anSAMSignOnControlFlag,APIOut->ucSAMSignOnControlFlag,1);  
        
	TermHost.ucCheckEVFlag = DongleOut->stSAMParameterInfo_t.bCheckEVFlag6;//Check EV Flag
   	TermHost.ucDeductLimitFlag = DongleOut->stSAMParameterInfo_t.bDeductLimitFlag7;//Deduct Limit Flag
  	TermHost.ucOneDayQuotaFlag = DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag0 |
				   (DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag1 << 4);//One Day Quota Flag
       memcpy(&TermHost.ucOneDayQuota,&DongleOut->stSAMParameterInfo_t.ucOneDayQuota,sizeof(DongleOut->stSAMParameterInfo_t.ucOneDayQuota));
	//vdUIntToAsc(TermHost.ucOneDayQuota,sizeof(TermHost.ucOneDayQuota),DongleOut->stSAMParameterInfo_t.ucOneDayQuota,sizeof(DongleOut->stSAMParameterInfo_t.ucOneDayQuota),' ',10);//One Day Quota
        TermHost.ucOnceQuotaFlag = DongleOut->stSAMParameterInfo_t.bOnceQuotaFlag2;//Once Quota Flag

	 memcpy(&TermHost.ucOnceQuota,&DongleOut->stSAMParameterInfo_t.ucOneDayQuota,sizeof(TermHost.ucOnceQuota));
       // vdUIntToAsc(TermHost.ucOnceQuota,sizeof(TermHost.ucOnceQuota),DongleOut->stSAMParameterInfo_t.ucOnceQuota,sizeof(DongleOut->stSAMParameterInfo_t.ucOnceQuota),' ',10);//Once Quota
	TermHost.ucCheckDeductFlag = DongleOut->stSAMParameterInfo_t.bCheckDeductFlag3;//Check Debit Flag
	 memcpy(&TermHost.ucCheckDeductValue,&DongleOut->stSAMParameterInfo_t.ucCheckDeductValue,sizeof(TermHost.ucCheckDeductValue));
	//vdUIntToAsc(TermHost.ucCheckDeductValue,sizeof(TermHost.ucCheckDeductValue),DongleOut->stSAMParameterInfo_t.ucCheckDeductValue,sizeof(DongleOut->stSAMParameterInfo_t.ucCheckDeductValue),' ',10);//Check Debit
	TermHost.ucAddQuotaFlag = DongleOut->stSAMParameterInfo_t.ucAddQuotaFlag;//Add Quota Flag
	memcpy(&TermHost.ucAddQuota,&DongleOut->stSAMParameterInfo_t.ucAddQuota,sizeof(TermHost.ucAddQuota));
	//vdUIntToAsc(TermHost.ucAddQuota,sizeof(TermHost.ucAddQuota),DongleOut->stSAMParameterInfo_t.ucAddQuota,sizeof(DongleOut->stSAMParameterInfo_t.ucAddQuota),' ',10);//Add Quota
        //wub_hex_2_str((unsigned char *)&TermHost,(unsigned char *)&APIOut->stTermHostInfo_t,sizeof(TermHost));  
  	wub_hex_2_str((unsigned char *)&TermHost,(unsigned char *)&APIOut->stTermHostInfo_t,sizeof(TermHost));  
	//memcpy((unsigned char *)&APIOut->stTermHostInfo_t,(unsigned char *)&TermHost,sizeof(TermHost));        

	memcpy(&TermPara.ucRemainderAddQuota,&DongleOut->ucRemainderAddQuota,sizeof(TermPara.ucRemainderAddQuota));
	//vdUIntToAsc(TermPara.ucRemainderAddQuota,sizeof(TermPara.ucRemainderAddQuota),DongleOut->ucRemainderAddQuota,sizeof(DongleOut->ucRemainderAddQuota),' ',10);//Remainder Add Quota
	memcpy(&TermPara.ucCancelCreditQuota,&DongleOut->ucCancelCreditQuota,sizeof(TermPara.ucCancelCreditQuota));
	//vdUIntToAsc(TermPara.ucCancelCreditQuota,sizeof(TermPara.ucCancelCreditQuota),DongleOut->ucCancelCreditQuota,sizeof(DongleOut->ucCancelCreditQuota),' ',10);//Cancel Credit Quota
	//wub_hex_2_str((unsigned char *)&TermPara,(unsigned char *)&APIOut->stTermParaInfo_t,sizeof(TermPara));  
	wub_hex_2_str((unsigned char *)&TermPara,(unsigned char *)&APIOut->stTermParaInfo_t,sizeof(TermPara));  
	//memcpy((unsigned char *)&APIOut->stTermParaInfo_t,(unsigned char *)&TermPara,sizeof(TermPara));    
     //   vdUIntToAsc(&DongleOut->ucSPID,sizeof(DongleOut->ucSPID),APIOut->anSPID,sizeof(APIOut->anSPID),' ',10);//SP ID
	
	vdUIntToAsc(APIOut->ucCPUSPID,sizeof(APIOut->ucCPUSPID)-1,DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),' ',10);//CPU SP ID
  	BYTE anLastTxnDateTime[14];
        fnLongToUnix((unsigned char *)&anLastTxnDateTime,(unsigned long *)DongleOut->ucLastTxnDateTime,14);//最後一次SignOn成功時間
        LoadConfigFile();
        ezxml_t TAG_LastSignonDateTime = ezxml_get(gConfigDATA,  "STATUS",0,"LastSignonDateTim",-1);
	if(TAG_LastSignonDateTime !=NULL){
                ezxml_set_txt(TAG_LastSignonDateTime,anLastTxnDateTime);
        }
         SaveConfigFile();
	return(inTMOutLen);
}
int inBuildReadCardBasicDataOutput(int inTxnType,ReadCardBasicData_TM_Out *APIOut,ReadCardBasicData_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(ReadCardBasicData_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	APIOut->ucActivated = DongleOut->bActivated;//Activated Flag
	APIOut->ucBlocked = DongleOut->bBlocked;//Blocked Flag
	APIOut->ucRefunded = DongleOut->bRefunded;//Refunded Flag
	APIOut->ucAutoLoad = DongleOut->bAutoLoad;//AutoLoad Flag
	APIOut->ucCredit = DongleOut->bCredit;//Credit Flag
	APIOut->ucMerchantUseFlag = DongleOut->ucMerchantUseFlag;//Merchant Use Flag
	vdUIntToAsc(DongleOut->ucAutoLoadAmt,sizeof(DongleOut->ucAutoLoadAmt),APIOut->anAutoLoadAmt,sizeof(APIOut->anAutoLoadAmt),' ',10);//n_AutoLoad Amount
	fnUnPack(DongleOut->ucPID,sizeof(DongleOut->ucPID),APIOut->anPID);//Purse ID
	vdUIntToAsc(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->anCardID,sizeof(APIOut->anCardID),' ',10);//n_Card Physical ID
	fnUnPack(&DongleOut->ucAreaCode,sizeof(DongleOut->ucAreaCode),APIOut->anAreaCode);//an_Area Code
	fnUnPack(DongleOut->ucSubAreaCode,sizeof(DongleOut->ucSubAreaCode),APIOut->anSubAreaCode);//an_Sub Area Code
	fnLongToUnix(APIOut->anExpiryDate,(unsigned long *)DongleOut->ucExpiryDate,14);//Expiry Date
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->anEV,sizeof(APIOut->anEV),' ',10);//n_EV
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->anTxnSN,sizeof(APIOut->anTxnSN),' ',10);//n_TXN SNum
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->anCardType);//an_Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->anPersonalProfile);//an_Personal Profile
	fnLongToUnix(APIOut->anProfileExpiryDate,(unsigned long *)DongleOut->ucProfileExpiryDate,14);//Personal Profile Expiry Date
	vdIntToAsc(DongleOut->ucDeposit,sizeof(DongleOut->ucDeposit),APIOut->anDeposit,sizeof(APIOut->anDeposit),' ',10);//n_Deposit
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->anIssuerCode);//an_Issuer Code
	fnUnPack(&DongleOut->ucBankCode,sizeof(DongleOut->ucBankCode),APIOut->anBankCode);//an_Bank Code
	vdUIntToAsc(DongleOut->ucLoyaltyCounter,sizeof(DongleOut->ucLoyaltyCounter),APIOut->anLoyaltyCounter,sizeof(APIOut->anLoyaltyCounter),' ',10);//n_Loyalty Counter
	vdUIntToAsc(DongleOut->ucCardOneDayQuota,sizeof(DongleOut->ucCardOneDayQuota),APIOut->anCardOneDayQuota,sizeof(APIOut->anCardOneDayQuota),' ',10);//n_Card One Day Quota
	fngetDosDate(DongleOut->ucCardOneDayQuotaDate,APIOut->anCardOneDayQuotaDate);//Card One Day Quota Date
	if(DongleOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->anDebitTxnRecords,"06",sizeof(APIOut->anDebitTxnRecords));
	else
		vdUIntToAsc(&DongleOut->ucDebitTxnRecords,sizeof(DongleOut->ucDebitTxnRecords),APIOut->anDebitTxnRecords,sizeof(APIOut->anDebitTxnRecords),' ',10);//Debit Txn Records
	vdBuildReadCardBasicDataOutput2(0x02,&DongleOut->stLastCreditTxnLogInfo_t,&APIOut->stLastCreditTxnRecoredInfo_t);
	vdBuildReadCardBasicDataOutput2(0x01,&DongleOut->stLastDebitTxnLogInfo_t,&APIOut->stLastDebitTxnRecoredInfo_t);

	return(inTMOutLen);
}

void vdBuildReadCardBasicDataOutput2(BYTE ucMsgType,LastTxnLog_t *DongleOutLog,LastTxnRecored_t *APIOutRecored)
{
	vdUIntToAsc(DongleOutLog->ucTxnSN,sizeof(DongleOutLog->ucTxnSN),APIOutRecored->anTxnSN,sizeof(APIOutRecored->anTxnSN),' ',10);//n_TXN SNum
	fnLongToUnix(APIOutRecored->anTxnDateTime,(unsigned long *)DongleOutLog->ucTxnDateTime,14);//TXN Date Time
	fnUnPack(&DongleOutLog->ucSubType,sizeof(DongleOutLog->ucSubType),APIOutRecored->anSubType);//an_Sub Type
	vdCountEVBefore(DongleOutLog->ucTxnAmt,sizeof(DongleOutLog->ucTxnAmt),DongleOutLog->ucEV,sizeof(DongleOutLog->ucEV),APIOutRecored->anEVBeforeTxn,sizeof(APIOutRecored->anEVBeforeTxn),ucMsgType);//n_EV Before TXN
	vdUIntToAsc(DongleOutLog->ucTxnAmt,sizeof(DongleOutLog->ucTxnAmt),APIOutRecored->anTxnAmt,sizeof(APIOutRecored->anTxnAmt),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOutLog->ucEV,sizeof(DongleOutLog->ucEV),APIOutRecored->anEV,sizeof(APIOutRecored->anEV),' ',10);//n_EV After TXN
	vdUIntToAsc(DongleOutLog->ucCPUSPID,sizeof(DongleOutLog->ucCPUSPID),APIOutRecored->anCPUSPID,sizeof(APIOutRecored->anCPUSPID),' ',10);//CPU SP ID
	vdUIntToAsc(DongleOutLog->ucCPULocationID,sizeof(DongleOutLog->ucCPULocationID),APIOutRecored->anLocationID,sizeof(APIOutRecored->anLocationID),' ',10);//an_TXN Location ID
	fnBINTODEVASC(DongleOutLog->ucCPUDeviceID,APIOutRecored->anCPUDeviceID,sizeof(APIOutRecored->anCPUDeviceID),DongleOutLog->ucPurseVersionNumber_Index);//n_TXN Device ID
}

int inBuildTxnReqOnlineOutput(int inTxnType,TRANS_DATA *APIOut,TxnReqOnline_APDU_In *DongleIn,TxnReqOnline_APDU_Out *DongleOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;
      
	//APIOut->ucMsgType = DongleOut->ucMsgType;//Msg Type
	//APIOut->ucSubType = DongleOut->ucSubType;//Sub Type
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID  0100
	 
	vdBuildProcessingCode(inTxnType,DongleOut->ucMsgType,DongleOut->ucSubType,DongleOut->ucPersonalProfile,APIOut->ucProcessCode);//Processing Code
        wub_hex_2_str(DongleOut->ucDeviceID,APIOut->ucDeviceID,4);//4100

	USHORT ret=GetConfigTag("BLC","VERSION",APIOut->ucBLVersion);//ucBLVersion 6004
	inBuildTxnDataTime((ULONG)DongleIn->ucTxnDateTime, (BYTE *)&APIOut->ucTxnDateTime,(unsigned char *)&APIOut->ucTxnData, (unsigned char *)&APIOut->ucTxnTime);//0700
	wub_hex_2_str(&DongleOut->ucCardType,APIOut->ucBasicData_CardType,sizeof(DongleOut->ucCardType));//0213
	wub_hex_2_str(&DongleOut->ucPersonalProfile,APIOut->ucBasicData_CardProfile,sizeof(DongleOut->ucPersonalProfile));//0214
	wub_hex_2_str(&DongleOut->ucIssuerCode,APIOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode));//4802
	wub_hex_2_str(&DongleOut->ucBankCode,APIOut->ucBankCode,sizeof(DongleOut->ucBankCode));//4803
	wub_hex_2_str((unsigned char *)&DongleOut->ucLoyaltyCounter,APIOut->ucLoyaltyCounter,sizeof(DongleOut->ucLoyaltyCounter));//4813
	wub_hex_2_str((unsigned char *)&DongleOut->ucExpiryDate,APIOut->ucProfileExpiryDate,sizeof(DongleOut->ucExpiryDate));//4806
	wub_hex_2_str(&DongleOut->ucAreaCode,APIOut->ucAreaCode,sizeof(DongleOut->ucAreaCode));//4804

	
        //5504
        memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(DongleIn->ucTMID));
        //5514     
         memcpy(APIOut->ucTMTxnDateTime,DongleIn->ucTMTxnDateTime,8);
        //5510
        memcpy(APIOut->ucTMAgentNumber,&DongleIn->ucTMAgentNumber,sizeof(DongleIn->ucTMAgentNumber));
	memcpy(APIOut->ucTMTxnSN,&DongleOut->ucTMSerialNumber,sizeof(APIOut->ucTMTxnSN));//TM Serial Number
	memcpy(APIOut->ucTMLocationID,&DongleIn->ucTMLocationID,sizeof(APIOut->ucTMLocationID));//TM Location ID 5503
	wub_hex_2_str((unsigned char *)&DongleOut->ucSTAC,APIOut->ucSTAC,sizeof(DongleOut->ucSTAC));//6400
	wub_hex_2_str((unsigned char *)&DongleOut->ucSAMKVN,APIOut->ucKeyVersion,sizeof(DongleOut->ucSAMKVN));//5301
	wub_hex_2_str((unsigned char *)&DongleOut->ucSAMID,APIOut->ucSAMID,sizeof(DongleOut->ucSAMID));//5361
	wub_hex_2_str((unsigned char *)&DongleOut->ucSAMSN,APIOut->ucSAMSN,sizeof(DongleOut->ucSAMSN));//5362
	wub_hex_2_str((unsigned char *)&DongleOut->ucSAMCRN,APIOut->ucSAMCRN,sizeof(DongleOut->ucSAMCRN));//5363
	wub_hex_2_str((unsigned char *)&DongleOut->ucReaderFWVersion,APIOut->ucReaderFWVersion,sizeof(DongleOut->ucReaderFWVersion));//6000
	wub_hex_2_str((unsigned char *)&DongleOut->ucCardID,APIOut->ucCardID,sizeof(DongleOut->ucCardID));//6000
 //	sprintf((unsigned char *)APIOut->ucCardID,"%uld",DongleOut->ulCardID);//0200
//	sprintf((unsigned char *)APIOut->ucTxnAmt,"%ld",DongleOut->ucTxnAmt);//0400
//	inBuildCPUDEVICEID(&DongleOut->ucCPUDeviceID,&APIOut->ucCPUDeviceID);//4100
	wub_hex_2_str(&DongleOut->ucCardID,APIOut->ucCardID,sizeof(DongleOut->ucCardID));//6000
	wub_hex_2_str(&DongleOut->ucCPUSPID,APIOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID));//4200
	wub_hex_2_str(&DongleOut->ucCPULocationID,APIOut->ucSubMerchantID,sizeof(DongleOut->ucCPULocationID));//4200
	wub_hex_2_str(&DongleOut->ucPID,APIOut->ucPID,sizeof(DongleOut->ucPID));//0211
	wub_hex_2_str(&DongleOut->ucCTC,APIOut->ucCTC,sizeof(DongleOut->ucCTC));//4812
	wub_hex_2_str(&DongleOut->ucProfileExpiryDate,APIOut->ucProfileExpiryDate,sizeof(DongleOut->ucProfileExpiryDate));//4806
	wub_hex_2_str(&DongleOut->ucSubAreaCode,APIOut->ucCPUSubAreaCode,sizeof(DongleOut->ucSubAreaCode));//4805
	wub_hex_2_str(&DongleOut->ucTxnSN,APIOut->ucCardTxnSN,sizeof(DongleOut->ucTxnSN));//4808
	wub_hex_2_str(&DongleOut->ucEV,APIOut->ucEVafterTxn,sizeof(DongleOut->ucEV));//0408
	wub_hex_2_str(&DongleOut->ucDeposit,APIOut->ucDepositValue,sizeof(DongleOut->ucDeposit));//4814
	

	
	
	BYTE KeyInfo[3];
	memset(&KeyInfo,0x00,sizeof(KeyInfo));
	KeyInfo[0]=DongleOut->ucCPUAdminKeyKVN;//CPU Admin Key KVN
	KeyInfo[1]=DongleOut->ucCreditKeyKVN;//Credit Key KVN
	KeyInfo[2]=DongleOut->ucCPUIssuerKeyKVN;//CPU Issuer Key KVN or debit key KVN
	wub_hex_2_str(&KeyInfo,&APIOut->ucCPUCardKeyInfo,sizeof(KeyInfo));//5302
	
	wub_hex_2_str(&DongleOut->ucTxnMode,&APIOut->ucCPUTxnMode,sizeof(DongleOut->ucTxnMode));//4809
	
	wub_hex_2_str(&DongleOut->ucTxnQuqlifier,&APIOut->ucCPUTQ,sizeof(DongleOut->ucTxnQuqlifier));//4810
	wub_hex_2_str(&DongleOut->ucSignatureKeyKVN,&APIOut->ucSigntureKeyKVN,sizeof(DongleOut->ucSignatureKeyKVN));//5305
	wub_hex_2_str(&DongleOut->ucCPUSAMID,&APIOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID));//5305
	wub_hex_2_str(&DongleOut->ucHostAdminKVN,&APIOut->ucCPUHostadminKVN,sizeof(DongleOut->ucHostAdminKVN));//5304
	wub_hex_2_str(&DongleOut->ucPurseVersionNumber,&APIOut->ucCPUPurseVersionNUM,sizeof(DongleOut->ucPurseVersionNumber));//4800
	CardAVR_t CardAVR;ReaderAVRTM_t ReaderAVR;
	vdBuildCardAVRData(&CardAVR,&DongleOut->stLastCreditTxnLogInfo_t,DongleOut->ucCardID,DongleOut->ucIssuerCode,DongleOut->ucCPUSPID,DongleOut->ucCPULocationID,DongleOut->ucPID,APIOut->ucLoyaltyCounter);//Card AVR Info
	vdBuildReaderAVRData(&ReaderAVR,&DongleOut->stReaderAVRInfo_t);//Reader AVR Info

	
	wub_hex_2_str(&CardAVR,&APIOut->ucCardAVRDATA,sizeof(CardAVR));//4801
	wub_hex_2_str(&ReaderAVR,&APIOut->ReaderAVRDATA,sizeof(ReaderAVR));//6001
	wub_hex_2_str(&DongleOut->ucCardIDLen,&APIOut->ucChipIDLength,sizeof(DongleOut->ucCardIDLen));//4826
	
	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	memcpy(stStore_DataInfo_t.ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));
	vdSaveReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));

	return(inTMOutLen);
}

int inBuildAuthTxnOnlineOutput(int inTxnType,TRANS_DATA *APIOut,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;



	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,
				TxnReqOut->ucPersonalProfile,APIOut->ucProcessCode);//Processing Code
	
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->ucTerminalTxnSN,sizeof(APIOut->ucTerminalTxnSN),' ',10);//n_TXN SNum
	
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->ucProcessCode);//Processing Code

	
	unsigned int PVN ;
	wub_str_2_hex((BYTE *)&APIOut->ucCPUPurseVersionNUM , &PVN, 2);
	if(PVN== MIFARE){
		fnUnPack(DongleOut->ucMAC_HCrypto,10,&APIOut->MAC);//MAC 6403
		fnUnPack(DongleOut->ucMAC_HCrypto[10],8,&APIOut->CTAC);//MAC 6402
	}else{
	
		fnUnPack(&DongleOut->ucMAC_HCrypto[0],1,APIOut->ucCPUHashTYPE);//5303
		fnUnPack(&DongleOut->ucMAC_HCrypto[1],1,APIOut->ucCPUHostadminKVN);//5304
		fnUnPack(&DongleOut->ucMAC_HCrypto[2],16,APIOut->CPUMAC_HCrypto);//6404
	}

	
	fnUnPack(DongleOut->ucSignature,sizeof(DongleOut->ucSignature),&APIOut->CPUSignature);//Signature
	
	fnUnPack(DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),APIOut->ucCPUSAMID);//SAM ID
	
	
	fnLongToUnix(&APIOut->ucTxnDateTime,(unsigned long *)DongleOut->ucTxnDateTime,14);//TM Txn Date Time
	
	
	
	memset(APIOut->MAC,0x00,sizeof(APIOut->MAC));//MAC
//	memcpy(APIOut->ucConfirmCode,DongleOut->ucConfirmCode,sizeof(APIOut->ucConfirmCode));//Confirm Code
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->MAC,&DongleOut->ucMAC_HCrypto[10],sizeof(APIOut->MAC));//CTAC
	else
		memset(APIOut->MAC,0x00,sizeof(APIOut->MAC));//CTAC
		
	fnUnPack(DongleOut->ucEV,sizeof(DongleOut->ucEV),&APIOut->ucEVafterTxn);//ucEVafterTxn	
	fnUnPack(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),&APIOut->ucCardTxnSN);//ucEVafterTxn	
 	fnUnPack(DongleOut->ucSignature,sizeof(DongleOut->ucSignature),&APIOut->CPUSignature);//ucEVafterTxn	



	return(inTMOutLen);
}

int inBuildTxnReqOfflineOutput1(int inTxnType,TRANS_DATA *APIOut,TxnReqOffline_APDU_In *DongleIn,TxnReqOffline_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(TRANS_DATA);
	
	vdUIntToAsc(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->ucCardID,sizeof(APIOut->ucCardID),' ',10);//n_Card Physical ID
       wub_hex_2_str(DongleOut->ucDeviceID,APIOut->ucDeviceID,sizeof(DongleOut->ucDeviceID));
        
	inBuildCPUDEVICEID((BYTE*)&DongleOut->ucCPUDeviceID, (BYTE*)&APIOut->ucCPUDeviceID);
	inBuildTxnDataTime((ULONG)DongleIn->ucTxnDateTime,(BYTE*)&APIOut->ucTxnDateTime,(BYTE*)&APIOut->ucTxnData, (BYTE*)&APIOut->ucTxnTime);	
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->ucEVBeforeTxn,sizeof(APIOut->ucEVBeforeTxn)-1,' ',10);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->ucCardTxnSN,sizeof(APIOut->ucCardTxnSN)-1,' ',10);//n_TXN SNum
	vdUIntToAsc(DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),APIOut->ucTxnAmt,sizeof(APIOut->ucTxnAmt)-1,' ',10);//n_TXN AMT
        BYTE bautoload=DongleOut->bAutoLoad;
        wub_hex_2_str((unsigned char *)&bautoload,(unsigned char *)&APIOut->ucBasicData_Autoloadflag,sizeof(bautoload));
	//APIOut->ucAutoLoad = DongleOut->bAutoLoad;//AutoLoad Flag
	vdUIntToAsc(DongleOut->ucAutoLoadAmt,sizeof(DongleOut->ucAutoLoadAmt),APIOut->ucAutoloadAMT,sizeof(APIOut->ucAutoloadAMT)-1,' ',10);//n_AutoLoad Amount

	return(inTMOutLen);
} 

int BuildTxnReqOfflineOutput2(int inTxnType,TRANS_DATA *APIOut,TxnReqOffline_APDU_In *DongleIn,TxnReqOffline_APDU_Out *DongleOut)
{
int inTMOutLen;
BYTE ucLoyaltyCounter[2];

	inTMOutLen = sizeof(TRANS_DATA);
	
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	vdBuildProcessingCode(inTxnType,DongleOut->ucMsgType,DongleOut->ucSubType,DongleOut->ucPersonalProfile,APIOut->ucProcessCode);//Processing Code
	wub_hex_2_str(& DongleOut->ucPurseVersionNumber,(unsigned char *)&APIOut->ucCPUPurseVersionNUM,sizeof(DongleOut->ucPurseVersionNumber));
	vdIntToAsc(DongleOut->ucAutoLoadAmt,sizeof(DongleOut->ucAutoLoadAmt),APIOut->ucAutoloadAMT,sizeof(APIOut->ucAutoloadAMT),' ',10);//ucAutoloadAMT
	

	wub_hex_2_str(DongleOut->ucDeviceID,APIOut->ucDeviceID,sizeof(DongleOut->ucDeviceID));
	wub_hex_2_str(&DongleOut->ucCardType,(unsigned char *)&APIOut->ucBasicData_CardType,sizeof(DongleOut->ucCardType));
	wub_hex_2_str(&DongleOut->ucPersonalProfile,(unsigned char *)&APIOut->ucBasicData_CardProfile,sizeof(DongleOut->ucPersonalProfile));
      wub_hex_2_str((unsigned char *)&DongleOut->ucIssuerCode,(unsigned char *)&APIOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode));
      inBuildCardExpiryDateYYMM((unsigned long * )&DongleOut->ucExpiryDate,(unsigned char *)&APIOut->ucCardExpiryDate);  
      wub_hex_2_str(&DongleOut->ucAreaCode,(unsigned char *)&APIOut->ucAreaCode,sizeof(DongleOut->ucAreaCode));
	
       
	if(DongleOut->ucPurseVersionNumber == MIFARE)
	{
             wub_hex_2_str((unsigned char *)&DongleOut->ucSID_STAC,(unsigned char *)&APIOut->ucSTAC,sizeof(DongleOut->ucSID_STAC));
             wub_hex_2_str((unsigned char *)&DongleOut->ucCPDKVN_SAMKVN,(unsigned char *)&APIOut->ucKeyVersion,sizeof(DongleOut->ucCPDKVN_SAMKVN));
		wub_hex_2_str((unsigned char *)&DongleOut->ucCPD_SAMID[2],(unsigned char *)&APIOut->ucSAMID,8);
             wub_hex_2_str((unsigned char *)&DongleOut->ucCPD_SAMID[10],(unsigned char *)&APIOut->ucSAMSN,8);
		wub_hex_2_str((unsigned char *)&DongleOut->ucCPDRAN_SAMCRN,(unsigned char *)&APIOut->ucSAMCRN,sizeof(DongleOut->ucCPDRAN_SAMCRN));
        }
	else
	{
		memset(APIOut->ucSTAC,0x00,sizeof(APIOut->ucSTAC));//STAC
              memset(APIOut->ucKeyVersion,0x00,sizeof(APIOut->ucKeyVersion));//STAC
		memset(APIOut->ucSAMID,0x00,sizeof(APIOut->ucSAMID));//SAM ID
		memset(APIOut->ucSAMSN,0x00,sizeof(APIOut->ucSAMSN));//SAM SN
		memset(APIOut->ucSAMCRN,0x00,sizeof(APIOut->ucSAMCRN));//SAM CRN
	}
         wub_hex_2_str((unsigned char *)&DongleOut->ucReaderFWVersion,(unsigned char *)&APIOut->ucReaderFWVersion,sizeof(DongleOut->ucReaderFWVersion));
         wub_hex_2_str((unsigned char *)&DongleOut->ucCardID,(unsigned char *)&APIOut->ucCardID,sizeof(DongleOut->ucCardID));
	  wub_hex_2_str((unsigned char *)&DongleOut->ucCPUDeviceID,(unsigned char *)&APIOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID));
         wub_hex_2_str((unsigned char *)&DongleOut->ucCPUSPID,(unsigned char *)&APIOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID));
         inBuilducSubMerchantID((unsigned char *)&DongleOut->ucLocationID,(unsigned char *)&DongleOut->ucCPULocationID,(unsigned char *)&APIOut->ucSubMerchantID);
         
         wub_hex_2_str((unsigned char *)&DongleOut->ucPID,(unsigned char *)&APIOut->ucPID,sizeof(DongleOut->ucPID));
	  wub_hex_2_str((unsigned char *)&DongleOut->ucCTC,(unsigned char *)&APIOut->ucCTC,sizeof(DongleOut->ucCTC));
      
         inBuildDateYYDD((unsigned long *)&DongleOut->ucProfileExpiryDate,(unsigned char *)&APIOut->ucProfileExpiryDate);
	  wub_hex_2_str((unsigned char *)&DongleOut->ucProfileExpiryDate,(unsigned char *)&APIOut->ucProfileExpiryDate,sizeof(DongleOut->ucProfileExpiryDate));
         wub_hex_2_str((unsigned char *)&DongleOut->ucSubAreaCode,(unsigned char *)&APIOut->ucCPUSubAreaCode,sizeof(DongleOut->ucSubAreaCode));
         wub_hex_2_str((unsigned char *)&DongleOut->ucTxnSN,(unsigned char *)&APIOut->ucCardTxnSN,sizeof(DongleOut->ucTxnSN));
	  vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->ucEVafterTxn,sizeof(APIOut->ucEVafterTxn),' ',10);
         inBuildCPUKEYInfo(DongleOut->ucCPUAdminKeyKVN,DongleOut->ucCPUIssuerKeyKVN,DongleOut->ucCPUIssuerKeyKVN,(unsigned char *)&APIOut->CPUSAMINFOData);
         wub_hex_2_str((unsigned char *)&DongleOut->ucTxnMode,(unsigned char *)&APIOut->ucCPUTxnMode,sizeof(DongleOut->ucTxnMode));
	
         wub_hex_2_str((unsigned char *)&DongleOut->ucTxnQuqlifier,(unsigned char *)&APIOut->ucCPUTQ,sizeof(DongleOut->ucTxnQuqlifier));
	
        
	if(DongleOut->ucPurseVersionNumber == MIFARE){
                wub_hex_2_str(&DongleOut->ucCPD_SAMID[2],(unsigned char *)&APIOut->ucCPUSAMID,8);
	
	}else{
                wub_hex_2_str((unsigned char *)&DongleOut->ucSID_STAC,(unsigned char *)&APIOut->ucCPUSAMID,8);
		
        }
        
	if(DongleOut->ucPurseVersionNumber == MIFARE){
            memset(APIOut->ucCPUHostadminKVN ,0x00,sizeof(APIOut->ucCPUHostadminKVN));
        }else{
            wub_hex_2_str(&DongleOut->ucBankCode_HostAdminKVN,(unsigned char *)&APIOut->ucCPUHostadminKVN,sizeof( DongleOut->ucBankCode_HostAdminKVN));
	//	APIOut->ucHostAdminKVN = DongleOut->ucBankCode_HostAdminKVN;//Host Admin KVN
	}
        
        
	memcpy(APIOut->ucTMLocationID,DongleIn->ucTMLocationID,sizeof(APIOut->ucTMLocationID));//TM Location ID
	if(DongleOut->ucPurseVersionNumber == MIFARE)
		memset(APIOut->CPUTermCrypto,0x00,sizeof(APIOut->CPUTermCrypto));//CACrypto敺?蝣?
	else{
	wub_hex_2_str((unsigned char *)&DongleOut->ucSVCrypto,(unsigned char *)&APIOut->CPUTermCrypto,sizeof(DongleOut->ucSVCrypto));
	
        }
        wub_hex_2_str((unsigned char *)&DongleOut->ucCardOneDayQuota,(unsigned char *)&APIOut->ucPID,sizeof(DongleOut->ucPurseVersionNumber));

        
        memset(ucLoyaltyCounter,0x00,sizeof(ucLoyaltyCounter));
 	vdBuildCardAVRData(&APIOut->ucCardAVRDATA,&DongleOut->stLastCreditTxnLogInfo_t,DongleOut->ucCardID,DongleOut->ucIssuerCode,DongleOut->ucCPUSPID,DongleOut->ucCPULocationID,DongleOut->ucPID,ucLoyaltyCounter);//Card AVR Info
	
        wub_hex_2_str(&DongleOut->ucCardIDLen,(unsigned char *)&APIOut->ucChipIDLength,sizeof(DongleOut->ucCardIDLen));
	return(inTMOutLen);
}
int inBuildAuthTxnOfflineOutPut(int inTxnType,TRANS_DATA *APIOut,AuthTxnOffline_APDU_In *DongleIn,AuthTxnOffline_APDU_Out *DongleOut,TxnReqOffline_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
//	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,TxnReqOut->ucProcessCode);//Processing Code
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->ucTerminalTxnSN,sizeof(APIOut->ucTerminalTxnSN),' ',10);//n_TXN SNum
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->ucEVafterTxn,sizeof(APIOut->ucEVafterTxn),' ',10);//n_EV

	inBuildTxnDataTime(DongleOut->ucTxnDateTime, APIOut->ucTxnDateTime,APIOut->ucTxnData, APIOut->ucTxnTime);

	fnUnPack(DongleOut->ucSignature,sizeof(DongleOut->ucSignature),APIOut->CPUSignature);//Signature
	fnUnPack(DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),APIOut->ucCPUSAMID);//SAM ID
	
	
	if(TxnReqOut->ucPurseVersionNumber != MIFARE){
	
		fnUnPack(DongleOut->ucMAC_HCrypto,10,&APIOut->MAC);//MAC 6403
		//fnUnPack(DongleOut->ucMAC_HCrypto[10],8,&APIOut->CTAC);//MAC 6402
	}else{
	
		fnUnPack(&DongleOut->ucMAC_HCrypto[0],1,APIOut->ucCPUHashTYPE);//5303
		fnUnPack(&DongleOut->ucMAC_HCrypto[1],1,APIOut->ucCPUHostadminKVN);//5304
		fnUnPack(&DongleOut->ucMAC_HCrypto[2],16,APIOut->CPUMAC_HCrypto);//6404
	}

	return(inTMOutLen);
}
int inBuildLockCardDataOutput1(int inTxnType,TRANS_DATA *APIOut,LockCard_APDU_Out_2 *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason,BYTE *ucTMLocationID,BYTE *ucTMID)
{
        int inTMOutLen;
        BYTE bBLCName[50];   
        inTMOutLen = sizeof(TRANS_DATA);
	
      	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	vdBuildProcessingCode(inTxnType,0x00,0x00,0x00,(BYTE*)&APIOut->ucProcessCode);//Processing Code
     //   GetConfigTag("DEVICE","MERCHANTID",APIOut->ucCPUSPID);// new location id 4200  
    //   ret=GetConfigTag("DEVICE","NewLocationID",APIOut->ucSubMerchantID);// new location id 4210
	   //ezxml_t TAG_BLCVersion = ezxml_get(gConfigDATA, "BLC",0,"VERSION",-1);
        fnUnPack(&DongleOut->ucPurseVersionNumber,sizeof(DongleOut->ucPurseVersionNumber),APIOut->ucCPUPurseVersionNUM);//Purse Version Number
        fnUnPack(DongleOut->ucPID,sizeof(DongleOut->ucPID),APIOut->ucPID);//CPU Purse ID  
        fnUnPack(DongleOut->ucCTC,sizeof(DongleOut->ucCTC),APIOut->ucCTC);//CTC      
        vdUIntToAsc(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->ucCardID,sizeof(APIOut->ucCardID),' ',10);//n_Card Physical ID
        fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->ucDeviceID);//Device ID
        inBuildCPUDEVICEID(DongleOut->ucCPUDeviceID, APIOut->ucCPUDeviceID);
      //  fnUnPack(DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),APIOut->ucCPUDeviceID);//CPU Device ID
        vdUIntToAsc(DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),APIOut->ucCPUSPID,15,' ',10);

       
  	
	inBuildTxnDataTime2(ucTxnDateTime,(BYTE*)&APIOut->ucTxnDateTime,(BYTE*)&APIOut->ucTxnData, (BYTE*)&APIOut->ucTxnTime);
        fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->ucIssuerCode);//Issuer Code

        fnUnPack(&DongleOut->ucCardIDLen,sizeof(DongleOut->ucCardIDLen),APIOut->ucChipIDLength);//Card ID Len



        inBuilducSubMerchantID(&DongleOut->ucLocationID,(unsigned char *)&DongleOut->ucCPULocationID,(unsigned char *)&APIOut->ucSubMerchantID);

        fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->ucBasicData_CardType);//Card Type
        fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->ucBasicData_CardProfile);//Personal Profile


        fnUnPack(&ucLockReason,sizeof(ucLockReason),APIOut->ucLockReason);//Lock Reason
	return(inTMOutLen);
}
int inBuildLockCardDataOutput2(int inTxnType,TRANS_DATA *APIOut,LockCard_APDU_Out_3 *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason,BYTE *ucTMLocationID,BYTE *ucTMID)
{
int inTMOutLen;
BYTE bSpace[20];

	inTMOutLen = sizeof(TRANS_DATA);
	
	memset(bSpace,0x20,sizeof(bSpace));
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	vdBuildProcessingCode(inTxnType,DongleOut->ucMsgType,DongleOut->ucSubType,DongleOut->ucPersonalProfile,APIOut->ucProcessCode);//Processing Cod
	fnUnPack(&DongleOut->ucPurseVersionNumber,sizeof(DongleOut->ucPurseVersionNumber),APIOut->ucCPUPurseVersionNUM);//Purse Version Number t4800
	
	fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->ucDeviceID);//Device ID
	 inBuildTxnDataTime2(ucTxnDateTime,(BYTE*)&APIOut->ucTxnDateTime,(BYTE*)&APIOut->ucTxnData, (BYTE*)&APIOut->ucTxnTime);

	fnUnPack(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->ucCardID);//Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->ucIssuerCode);//Issuer Code
//	fnUnPack(&DongleOut->ucLocationID,sizeof(DongleOut->ucLocationID),APIOut->ucLocationID);//Location ID
	fnUnPack(&DongleOut->ucCardIDLen,sizeof(DongleOut->ucCardIDLen),APIOut->ucChipIDLength);//Card ID Len
	inBuildCPUDEVICEID(DongleOut->ucCPUDeviceID, APIOut->ucCPUDeviceID);
        
//	fnUnPack(DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),APIOut->unCPUDeviceID);//CPU Device ID
	fnUnPack(DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),APIOut->ucCPUSPID);//CPU SP ID
	fnUnPack(DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID),APIOut->ucSubMerchantID);//CPU Location ID
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->ucBasicData_CardType);//Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->ucBasicData_CardProfile);//Personal Profile
	fnUnPack(DongleOut->ucPID,sizeof(DongleOut->ucPID),APIOut->ucPID);//CPU Purse ID
	memset(APIOut->ucCTC,0x30,sizeof(APIOut->ucCTC));//CTC
	//fnUnPack(DongleOut->ucCTC,sizeof(DongleOut->ucCTC),APIOut->unCTC);//CTC
	fnUnPack(&ucLockReason,sizeof(ucLockReason),APIOut->ucLockReason);//Lock Reason
//	memset(APIOut->unBLCFileName,0x20,sizeof(APIOut->unBLCFileName));//BLC File Name
//	APIOut->unBLCIDFlag = 0x20;//BLC ID Flag
	memcpy(APIOut->ucTMLocationID,ucTMLocationID,sizeof(APIOut->ucTMLocationID));//TM Location ID
	memcpy(APIOut->ucTMID,ucTMID,sizeof(APIOut->ucTMID));//TM ID
//	memset(APIOut->unRFU,0x20,sizeof(APIOut->unRFU));//RFU

/*	fnUnPack(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->unEV);//EV
	fnUnPack(DongleOut->ucEV2,sizeof(DongleOut->ucEV2),APIOut->unCPUEV);//EV2
	fnUnPack(&DongleOut->ucMifareSettingParameter,sizeof(DongleOut->ucMifareSettingParameter),APIOut->unMSettingPar);//Mifare Setting Parameter
	fnUnPack(&DongleOut->ucCPUSettingParameter,sizeof(DongleOut->ucCPUSettingParameter),APIOut->unCSettingPar);//CPU Setting Parameter
	fnUnPack(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->unTxnSN);//Txn SN
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucTxnSN,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucTxnSN),APIOut->unVARTxnSN);//VAR Txn SN
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucTxnDateTime,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucTxnDateTime),APIOut->unVARTxnDateTime);//VAR Txn Date Time
	fnUnPack(&DongleOut->stLastCreditTxnLogInfo_t.ucSubType,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucSubType),APIOut->unVARSubType);//VAR Sub Type
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucTxnAmt,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucTxnAmt),APIOut->unVARTxnAmt);//VAR Txn Amt
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucEV,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucEV),APIOut->unVAREV);//VAR EV
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucCPUDeviceID,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucCPUDeviceID),APIOut->unVARDeviceID);//VAR Device ID
*/
	return(inTMOutLen);
}

USHORT  usFormatTransTag(TRANS_DATA * TransData,BYTE * TAG,BYTE * NAME, ezxml_t TransLog)
{
    int iTag;
    char TagNUM[10];
    //BYTE gtmpstr[32],gtmpstr1[32],gtmpstr2[32],gtmpstr3[32],gtmpstr4[32];	
   
    USHORT ret;
    ezxml_t Tag, node2,node3,node4, node5,node6,node7,node8,node9,node10,node11,node12;
    memset(gtmpstr,0x00,sizeof(gtmpstr));
    memset(TagNUM,0x00,sizeof(TagNUM));
    memcpy(TagNUM,TAG,strlen(TAG));
    iTag=atoi(&TagNUM[1]);

    ezxml_t node=ezxml_add_child_d(TransLog,TAG,0);
    if(NAME !=NULL)ezxml_set_attr_d(node,"name",NAME);
    switch(iTag){
       case 100: 
         
           ezxml_set_txt(node,TransData->ucMessageType); 
          break;
       case 200:  
       
           ezxml_set_txt(node,TransData->ucCardID); 
          break;
       case 211:   
        
           ezxml_set_txt(node,TransData->ucPID);
           break;
       case 212:
           ezxml_set_txt(node,TransData->ucBasicData_Autoloadflag);
           break;
       case 213:    
         
          ezxml_set_txt(node,TransData->ucBasicData_CardType);
           break;
       case 214:   
        
           ezxml_set_txt(node,TransData->ucBasicData_CardProfile);     
           break;
       case 300:   
         
              ezxml_set_txt(node,TransData->ucProcessCode);     
           break;
       case 301:
            Tag= ezxml_get(gConfigDATA, "DEVICE",0,"READER",0,"READERFWVER",-1);
            if(Tag !=NULL){
                 ezxml_set_txt(node,Tag->txt);     
            }
           break;
       case 400:   
              
             ezxml_set_txt(node,TransData->ucTxnAmt);     
             break;
       case 403:  
            ezxml_set_txt(node,TransData->ucDeductAMT);    
           break;
       case 407:   
             ezxml_set_txt(node,TransData->ucADDAMT);  
           break;
       case 408: 
             ezxml_set_txt(node,TransData->ucEVafterTxn);  
           break;
       case 409: 
            
             ezxml_set_txt(node,TransData->ucAutoloadAMT);  
           break;
         
       case 410:  
       
             ezxml_set_txt(node,TransData->ucEVBeforeTxn);  
           break;
       case 700:
             ezxml_set_txt(node,TransData->ucTxnDateTime);  
           break;
       case 1100:
          
             ezxml_set_txt(node,TransData->ucTerminalTxnSN);  
           break;
       case 1101:  
    
             ezxml_set_txt(node,TransData->ucTMTxnSN);    
           break;
       case 1200:  
    
             ezxml_set_txt(node,TransData->ucTxnTime);  
           break;
       case 1300:  
         
             ezxml_set_txt(node,TransData->ucTxnData);  
           break;
       case 1400: 
           
             ezxml_set_txt(node,TransData->ucCardExpiryDate);   
           break;
       case 1402:  
      
             ezxml_set_txt(node,TransData->ucCardVaildDate);    
           break;
       case 1403:  
             ezxml_set_txt(node,TransData->ucCardVaildDateAfterSet);    
           break;
       case 3700:    
             sprintf(TransData->ucRRN,"%s%s",TransData->ucTxnData,TransData->ucTerminalTxnSN);
        
             ezxml_set_txt(node,TransData->ucRRN);  
           break;
       case 3800: 
             ezxml_set_txt(node,TransData->ucTxnAuthNum);  
           break;
       case 3900:
             ezxml_set_txt(node,TransData->ucResponseCode);  
           break;
       case 3901: 
             ezxml_set_txt(node,TransData->ucCPUDeviceID);  
           break;
       case 3902: 
             ezxml_set_txt(node,TransData->ucDeviceID);  
           break;
       case 3903:  
             ezxml_set_txt(node,TransData->ucTerminalIP);  
           break;
       case 3911: 
             ezxml_set_txt(node,TransData->ucMechineID);  
           break;
       case 4100:
       
             ezxml_set_txt(node,TransData->ucCPUDeviceID);  
           break;
       case 4101:  
    
             ezxml_set_txt(node,TransData->ucDeviceID);  
           break;
       case 4102:
             
             ezxml_set_txt(node,TransData->ucTerminalIP);  
           break;
       case 4103:  
         
             ezxml_set_txt(node,TransData->ucMechineID);   
           break;
       case 4104: 
        
             ezxml_set_txt(node,TransData->ucReaderSN);      
           
           break;
       case 4200:  
     
             ezxml_set_txt(node,TransData->ucCPUSPID);  
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
     
              ezxml_set_txt(node,TransData->ucSubMerchantID);      break;
       case 4800:    
     
              ezxml_set_txt(node,TransData->ucCPUPurseVersionNUM);    break;
       case 4801: 
             
              ezxml_set_txt(node,TransData->ucCardAVRDATA);       break;
       case 4802: 
         
              ezxml_set_txt(node,TransData->ucIssuerCode);       break;
       case 4803:  
              ezxml_set_txt(node,TransData->ucBankCode);      break;
       case 4804:  
           
              ezxml_set_txt(node,TransData->ucAreaCode);      break;
       case 4805: 
        
              ezxml_set_txt(node,TransData->ucCPUSubAreaCode);       break;
       case 4806: 
           
              ezxml_set_txt(node,TransData->ucProfileExpiryDate);       break;
       case 4807:   
              ezxml_set_txt(node,TransData->ucNEWProfileExpiryDate);     break;
       case 4808:  
              ezxml_set_txt(node,TransData->ucCardTxnSN);      break;
       case 4809:   
        
              ezxml_set_txt(node,TransData->ucCPUTxnMode);     break;
       case 4810:  
          
              ezxml_set_txt(node,TransData->ucCPUTQ);      break;
       case 4811:  
         
              ezxml_set_txt(node,TransData->ucSNBeforeTxn);      break;
       case 4812: 
            TransData->ucCTC[sizeof(TransData->ucCTC)-1]=0x00;
              ezxml_set_txt(node,TransData->ucCTC);       break;
       case 4813: 
           
              ezxml_set_txt(node,TransData->ucLoyaltyCounter);       break;
       case 4814:   
             
              ezxml_set_txt(node,TransData->ucDepositValue);     break;
  /*     case 4815: 
              ezxml_set_txt(node,TransData->ucTxnAmt);       break;
       case 4816:  
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 4820:  
              ezxml_set_txt(node,TransData->ucHostSpecVersionNo);      break;
       case 4821: 
     
              ezxml_set_txt(node,TransData->ucCardParameters);       break;
       case 4822:    
   
              ezxml_set_txt(node,TransData->ucCardAutoloadParameters);    break;
       case 4823:   
              ezxml_set_txt(node,TransData->ucOneDayQuotaWrite);     break;
       case 4824:    
              ezxml_set_txt(node,TransData->ucCPDReadFlag);    break;
       case 4825:   
              ezxml_set_txt(node,TransData->ucCPUCreditBalanceChangeFlag);     break;
       case 4826:  
          
              ezxml_set_txt(node,TransData->ucChipIDLength);     break;
       case 4827:   
              ezxml_set_txt(node,TransData->ucCPUCardParameters);     break;
       case 4828:   
              ezxml_set_txt(node,TransData->ucMifareSettingData);     break;
       case 4829:   
              ezxml_set_txt(node,TransData->ucCPUCardSettingParameter);     break;
       case 5301:   
           
              ezxml_set_txt(node,TransData->ucKeyVersion);     break;
       case 5302:    
        
              ezxml_set_txt(node,(BYTE *)&TransData->ucCPUCardKeyInfo);    break;
       case 5303: 
              ezxml_set_txt(node,TransData->ucCPUHashTYPE);       break;
       case 5304:   
              ezxml_set_txt(node,TransData->ucCPUHostadminKVN);     break;
       case 5305:  
              ezxml_set_txt(node,TransData->ucSigntureKeyKVN);      break;
       case 5306:  
              ezxml_set_txt(node,TransData->ucCPUEDC);      break;
       case 5307:  
              ezxml_set_txt(node,TransData->ucRSAM);      break;
       case 5308:  
              ezxml_set_txt(node,TransData->ucRHOST);      break;
       case 5361:   
         
              ezxml_set_txt(node,TransData->ucSAMID);     break;
       case 5362:  
           
              ezxml_set_txt(node,TransData->ucSAMSN);      break;
       case 5363:   
           
              ezxml_set_txt(node,TransData->ucSAMCRN);     break;
       case 5364:   
              ezxml_set_txt(node,(BYTE *)&TransData->CPUSAMINFOData);     break;
       case 5365:   
              ezxml_set_txt(node,(BYTE *)&TransData->SAMtransInfoData);     break;
       case 5366:  
              ezxml_set_txt(node,TransData->ucSingleCreditTxnAmtLimit);      break;
       case 5367:   
              ezxml_set_txt(node,(BYTE *)&TransData->CSAMPARA);     
              break;
       case 5368:
                ezxml_set_txt(node,TransData->ucSTC);   
                break;
       case 5369:
                ezxml_set_txt(node,TransData->ucSAMSignOnControlFlag); 
                break;
       case 5370:    
              ezxml_set_txt(node,(BYTE *)&TransData->CPULastSignonInfoData); 
              break;
       case 5501:     
         
              ezxml_set_txt(node,TransData->ucBatchNo);      break;
       case 5503:   
       
              ezxml_set_txt(node,TransData->ucTMLocationID);        break;
       case 5504:   
         
              ezxml_set_txt(node,TransData->ucTMID);        break;
       case 5509:    
              ezxml_set_txt(node,TransData->EDCTYPE);       break;
       case 5510:     
         
              ezxml_set_txt(node,TransData->ucTMAgentNumber);      break;
       case 5514:     
           
              ezxml_set_txt(node,TransData->ucTMTxnDateTime);      break;
     /*  case 5548:     
              ezxml_set_txt(node,TransData->ucTxnAmt);     break;
       case 5550:     
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 5581:    
              ezxml_set_txt(node,TransData->ucOrgTxnTerminalID);       break;
       case 5582:     
              ezxml_set_txt(node,TransData->ucOrgTxnRRN);      break;
       case 5583:   
              ezxml_set_txt(node,TransData->ucOrgTxnDate);        break;
       case 5588:     
              
                node2=ezxml_add_child(node,"T558801",0);
                ezxml_set_txt(node2,"02");   

		node3=ezxml_add_child(node,"T558802",0);
                ret=  GetConfigTag("BLC","TYPE",(STR * )&gtmpstr1);
                if(ret==d_OK)   ezxml_set_txt(node3,(STR * )&gtmpstr1);   
                 node4=ezxml_add_child(node,"T558803",0);
                ret=  GetConfigTag("BLC","VERSION",(STR * )gtmpstr2);
                ezxml_set_txt(node4,gtmpstr2);  
                
                node5=ezxml_add_child(TransLog,TAG,0);
                node6=ezxml_add_child(node5,"T558801",0);
                ezxml_set_txt(node6,"03");   

			
                node7=ezxml_add_child(node5,"T558802",0);
                ret=  GetConfigTag("AP","NAME",(STR * )gtmpstr3);
                if(ret==d_OK)   ezxml_set_txt(node7,(STR * )gtmpstr3);  
               
             
                node8=ezxml_add_child(node5,"T558803",0); 
		   ret=  GetConfigTag("AP","VER",(STR * )gtmpstr4);
                if(ret==d_OK)   ezxml_set_txt(node8,(STR * )gtmpstr4);  
             
                
                node9=ezxml_add_child(TransLog,TAG,0);
                node10=ezxml_add_child(node9,"T558801",0);
                ezxml_set_txt(node10,"04");   
               
                node11=ezxml_add_child(node9,"T558802",0);
                ezxml_set_txt(node11,"");   
              				
                node12=ezxml_add_child(node9,"T558803",0);
		ret= GetParameterVer((STR * )gtmpstr4);		
		if(ret==d_OK)  
                    ezxml_set_txt(node12,(STR * )gtmpstr4);   
              break;
       case 5589:     
               sprintf(gtmpstr,"T558901");
               node2=ezxml_add_child(node,gtmpstr,0);
               ezxml_set_txt(node2,TransData->ucDeductStatus);     
               break;
     /*  case 5590:   
              ezxml_set_txt(node,TransData->ucTxnAmt);        break;*/
       case 5591:     
              ezxml_set_txt(node,TransData->ucSettle_TotleCnt);      break;
       case 5592:     
              ezxml_set_txt(node,TransData->ucSettle_TotleAmt);      break;
       case 5595:     
            
               node2=ezxml_add_child(node,"T559501",0);
               ezxml_set_txt(node2,TransData->ucTMS_ParmVER);     
               
             
               node3=ezxml_add_child(node,"T559502",0);
               ezxml_set_txt(node3,TransData->ucTMS_ParmID);     
               
               node4=ezxml_add_child(node,"T559503",0);
               ezxml_set_txt(node4,TransData->ucTMS_ParmData);     
               
             
               node5=ezxml_add_child(node,"T559504",0);
               ezxml_set_txt(node5,TransData->ucTMS_ParmVaildStartDate);   
               
              
               node6=ezxml_add_child(node,"T559505",0);
               ezxml_set_txt(node6,TransData->ucTMS_ParmVaildENDDate);   
               break;
       case 5596:    
              
               node2=ezxml_add_child(node,"T559601",0);
               ezxml_set_txt(node2,TransData->Transfer_TotlePackCnt);     
               
              
               node3=ezxml_add_child(node,"T559602",0);
               ezxml_set_txt(node3,TransData->Transfer_SendedPackCnt);    
               
             
               node4=ezxml_add_child(node,"T559603",0);
               ezxml_set_txt(node4,TransData->Transfer_ReceivedPackCnt);
               
               
               node5=ezxml_add_child(node,"559604",0);
               ezxml_set_txt(node5,TransData->Transfer_SendPackSN);
               break;
       case 6000:   
             
              ezxml_set_txt(node,TransData->ucReaderFWVersion);        break;
       case 6001:   
          
              ezxml_set_txt(node,(BYTE *)&TransData->ucCPUCardKeyInfo);        break;
       case 6002:    
              ezxml_set_txt(node,(BYTE *)&TransData->stTermHostInfo_t);       break;
       case 6003:     
              ezxml_set_txt(node,(BYTE *)&TransData->stTermParaInfo_t);      break;
       case 6004:    
        
              ezxml_set_txt(node,TransData->ucBLVersion);       break;
       case 6400:    
          
              ezxml_set_txt(node,TransData->ucSTAC);       break;
       case 6401:  
              ezxml_set_txt(node,TransData->HTAC);         break;
       case 6402:   
              ezxml_set_txt(node,TransData->CTAC);        break;
       case 6403:   
              ezxml_set_txt(node,TransData->MAC);        break;
       case 6404:   
              ezxml_set_txt(node,TransData->CPUMAC_HCrypto);        break;
       case 6405:   
              ezxml_set_txt(node,TransData->CPUSignature);        break;
       case 6406:    
          
              ezxml_set_txt(node,TransData->CPUTermCrypto);      break;
       case 6407:   
              ezxml_set_txt(node,TransData->HostCrypto);        break;
       case 6408:     
              ezxml_set_txt(node,TransData->ucSATOKEN);      break;
       case 6409:   
              ezxml_set_txt(node,TransData->HostToken);        break;
   
    }
        
    return d_OK;
}


USHORT usUnFormatTransTag(TRANS_DATA *TransData, ezxml_t node)
{
    int iTag;
    char TagNUM[10];
    BYTE tmpstr[64],tmpstr1[64],tmpstr2[64];
    int InfoType;
    ezxml_t Tag, node2 ;
    memset(tmpstr,0x00,sizeof(tmpstr));
    memset(TagNUM,0x00,sizeof(TagNUM));
    memcpy(TagNUM,node->name,strlen(node->name));
    iTag=atoi(&TagNUM[1]);

    
  
    switch(iTag){
       case 100:   
           usSetTagData(node,(char *)&TransData->ucMessageType); 
            
          break;
       case 200:  
           usSetTagData(node,(char *)&TransData->ucCardID); 
          break;
       case 211:   
           usSetTagData(node,(char *)&TransData->ucPID);
           break;
       case 212:
           usSetTagData(node,(char *)&TransData->ucBasicData_Autoloadflag);
           break;
       case 213:    
          usSetTagData(node,(char *)&TransData->ucBasicData_CardType);
           break;
       case 214:   
           usSetTagData(node,(char *)&TransData->ucBasicData_CardProfile);     
           break;
       case 300:   
              usSetTagData(node,(char *)&TransData->ucProcessCode);     
           break;
       case 301:
          
           break;
       case 400:   
             usSetTagData(node,(char *)&TransData->ucTxnAmt);     
             break;
       case 403:  
            usSetTagData(node,(char *)&TransData->ucDeductAMT);    
           break;
       case 407:   
             usSetTagData(node,(char *)&TransData->ucADDAMT);  
           break;
       case 408: 
             usSetTagData(node,(char *)&TransData->ucEVafterTxn);  
           break;
       case 409: 
             usSetTagData(node,(char *)&TransData->ucAutoloadAMT);  
           break;
         
       case 410:  
             usSetTagData(node,(char *)&TransData->ucEVBeforeTxn);  
           break;
       case 700:
             usSetTagData(node,(char *)&TransData->ucTxnDateTime);  
           break;
       case 1100:
             usSetTagData(node,(char *)&TransData->ucTerminalTxnSN);  
           break;
       case 1101:  
             usSetTagData(node,(char *)&TransData->ucTMTxnSN);    
           break;
       case 1200:  
             usSetTagData(node,(char *)&TransData->ucTxnTime);  
           break;
       case 1300:  
             usSetTagData(node,(char *)&TransData->ucTxnData);  
           break;
       case 1400: 
             usSetTagData(node,(char *)&TransData->ucCardExpiryDate);   
           break;
       case 1402:  
             usSetTagData(node,(char *)&TransData->ucCardVaildDate);    
           break;
       case 1403:  
             usSetTagData(node,(char *)&TransData->ucCardVaildDateAfterSet);    
           break;
       case 3700:    
             usSetTagData(node,(char *)&TransData->ucRRN);  
           break;
       case 3800: 
             usSetTagData(node,(char *)&TransData->ucTxnAuthNum);  
           break;
       case 3900:
             usSetTagData(node,(char *)&TransData->ucResponseCode);  
           break;
       case 3901: 
             usSetTagData(node,(char *)&TransData->ucCPUDeviceID);  
           break;
       case 3902: 
             usSetTagData(node,(char *)&TransData->ucDeviceID);  
           break;
       case 3903:  
             usSetTagData(node,(char *)&TransData->ucTerminalIP);  
           break;
       case 3911: 
             usSetTagData(node,(char *)&TransData->ucMechineID);  
           break;
       case 4100:
             usSetTagData(node,(char *)&TransData->ucCPUDeviceID);  
           break;
       case 4101:  
             usSetTagData(node,(char *)&TransData->ucDeviceID);  
           break;
       case 4102:
             usSetTagData(node,(char *)&TransData->ucTerminalIP);  
           break;
       case 4103:  
             usSetTagData(node,(char *)&TransData->ucMechineID);   
           break;
       case 4104: 
             usSetTagData(node,(char *)&TransData->ucReaderSN);      
           
           break;
       case 4200:  
           
             usSetTagData(node,(char *)&TransData->ucCPUSPID);  
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
              usSetTagData(node,(char *)&TransData->ucSubMerchantID);      break;
       case 4800:    
              usSetTagData(node,(char *)&TransData->ucCPUPurseVersionNUM);    break;
       case 4801: 
              usSetTagData(node,(char *)&TransData->ucCardAVRDATA);       break;
       case 4802: 
              usSetTagData(node,(char *)&TransData->ucIssuerCode);       break;
       case 4803:  
              usSetTagData(node,(char *)&TransData->ucBankCode);      break;
       case 4804:  
              usSetTagData(node,(char *)&TransData->ucAreaCode);      break;
       case 4805: 
              usSetTagData(node,(char *)&TransData->ucCPUSubAreaCode);       break;
       case 4806: 
              usSetTagData(node,(char *)&TransData->ucProfileExpiryDate);       break;
       case 4807:   
              usSetTagData(node,(char *)&TransData->ucNEWProfileExpiryDate);     break;
       case 4808:  
              usSetTagData(node,(char *)&TransData->ucCardTxnSN);      break;
       case 4809:   
              usSetTagData(node,(char *)&TransData->ucCPUTxnMode);     break;
       case 4810:  
              usSetTagData(node,(char *)&TransData->ucCPUTQ);      break;
       case 4811:  
              usSetTagData(node,(char *)&TransData->ucSNBeforeTxn);      break;
       case 4812: 
              usSetTagData(node,(char *)&TransData->ucCTC);       break;
       case 4813: 
              usSetTagData(node,(char *)&TransData->ucLoyaltyCounter);       break;
       case 4814:   
              usSetTagData(node,(char *)&TransData->ucDepositValue);     break;
  /*     case 4815: 
              ezxml_set_txt(node,TransData->ucTxnAmt);       break;
       case 4816:  
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 4820:  
              usSetTagData(node,(char *)&TransData->ucHostSpecVersionNo);      break;
       case 4821: 
              usSetTagData(node,(char *)&TransData->ucCardParameters);       break;
       case 4822:    
              usSetTagData(node,(char *)&TransData->ucCardAutoloadParameters);    break;
       case 4823:   
              usSetTagData(node,(char *)&TransData->ucOneDayQuotaWrite);     break;
       case 4824:    
              usSetTagData(node,(char *)&TransData->ucCPDReadFlag);    break;
       case 4825:   
              usSetTagData(node,(char *)&TransData->ucCPUCreditBalanceChangeFlag);     break;
       case 4826:   
              usSetTagData(node,(char *)&TransData->ucChipIDLength);     break;
       case 4827:   
              usSetTagData(node,(char *)&TransData->ucCPUCardParameters);     break;
       case 4828:   
              usSetTagData(node,(char *)&TransData->ucMifareSettingData);     break;
       case 4829:   
              usSetTagData(node,(char *)&TransData->ucCPUCardSettingParameter);     break;
       case 5301:   
              usSetTagData(node,(char *)&TransData->ucKeyVersion);     break;
       case 5302:    
              usSetTagData(node,(char *)&TransData->ucCPUCardKeyInfo);    break;
       case 5303: 
              usSetTagData(node,(char *)&TransData->ucCPUHashTYPE);       break;
       case 5304:   
              usSetTagData(node,(char *)&TransData->ucCPUHostadminKVN);     break;
       case 5305:  
              usSetTagData(node,(char *)&TransData->ucSigntureKeyKVN);      break;
       case 5306:  
              usSetTagData(node,(char *)&TransData->ucCPUEDC);      break;
       case 5307:  
              usSetTagData(node,(char *)&TransData->ucRSAM);      break;
       case 5308:  
              usSetTagData(node,(char *)&TransData->ucRHOST);      break;
       case 5361:   
              usSetTagData(node,(char *)&TransData->ucSAMID);     break;
       case 5362:  
              usSetTagData(node,(char *)&TransData->ucSAMSN);      break;
       case 5363:   
              usSetTagData(node,(char *)&TransData->ucSAMCRN);     break;
       case 5364:   
              usSetTagData(node,(BYTE *)&TransData->CPUSAMINFOData);     break;
       case 5365:   
              usSetTagData(node,(BYTE *)&TransData->SAMtransInfoData);     break;
       case 5366:  
              usSetTagData(node,(char *)&TransData->ucSingleCreditTxnAmtLimit);      break;
       case 5367:   
              usSetTagData(node,(BYTE *)&TransData->CSAMPARA);     
              break;
       case 5368:
                usSetTagData(node,(char *)&TransData->ucSTC);   
                break;
       case 5369:
                usSetTagData(node,(char *)&TransData->ucSAMSignOnControlFlag); 
                break;
       case 5370:    
              usSetTagData(node,(BYTE *)&TransData->CPULastSignonInfoData); 
              break;
       case 5501:     
              usSetTagData(node,(char *)&TransData->ucBatchNo);      break;
       case 5503:   
              usSetTagData(node,(char *)&TransData->ucTMLocationID);        break;
       case 5504:   
              usSetTagData(node,(char *)&TransData->ucTMID);        break;
       case 5509:    
              usSetTagData(node,(char *)&TransData->EDCTYPE);       break;
       case 5510:     
              usSetTagData(node,(char *)&TransData->ucTMAgentNumber);      break;
       case 5514:     
              usSetTagData(node,(char *)&TransData->ucTMTxnDateTime);      break;
     /*  case 5548:     
              ezxml_set_txt(node,TransData->ucTxnAmt);     break;
       case 5550:     
              ezxml_set_txt(node,TransData->ucTxnAmt);      break;*/
       case 5581:    
              usSetTagData(node,(char *)&TransData->ucOrgTxnTerminalID);       break;
       case 5582:     
              usSetTagData(node,(char *)&TransData->ucOrgTxnRRN);      break;
       case 5583:   
              usSetTagData(node,(char *)&TransData->ucOrgTxnDate);        break;
       case 5588:     
               sprintf(tmpstr,"T558801");
               node2 = ezxml_get(node, tmpstr,-1);
               if(node2==NULL)
               {
                    SystemLog("usUnFormatTransTag","T558801 is NULL ");
                    break ;
               }
               usSetTagData(node2,tmpstr1);
               InfoType=atoi(tmpstr1);
               switch(InfoType)
               {
                case 2:
                   sprintf(tmpstr,"T558802");
                   node2 = ezxml_get(node,tmpstr,-1);
                   if(node2!=NULL)
                   {
                       GetConfigTag("BLC","TYPE",tmpstr1);
                       if(strcmp(tmpstr1,node2->txt)!=0)
                       {     
                           SetConfigTag("BLC","TYPE",node2->txt);
                           SetConfigTag("BLC","UPDATEFLAG","1");
                       }
                   }  
                   sprintf(tmpstr,"T558803");
                   node2 = ezxml_get(node,tmpstr,-1);
                   if(node2!=NULL)
                   {
                       GetConfigTag("BLC","FILENAME",tmpstr1);
                       if(strcmp(tmpstr1,node2->txt)!=0)
                       {     
                           SetConfigTag("BLC","FILENAME",node2->txt);
                           SetConfigTag("BLC","UPDATEFLAG","1");
                       }
                   }  
                           
                   break;
                case 3:
                        sprintf(tmpstr,"T558802");
                        node2 = ezxml_get(node,tmpstr,-1);
                        if(node2!=NULL)
                        {
                            GetConfigTag("AP","NAME",tmpstr1);
                            if(strcmp(tmpstr1,node2->txt)!=0)
                            {     
                                SetConfigTag("AP","NAME",node2->txt);
                                SetConfigTag("AP","UPDATEFLAG","1");
                            }
                        }  
                        sprintf(tmpstr,"T558803");
                        node2 = ezxml_get(node,tmpstr,-1);
                        if(node2!=NULL)
                        {
                            GetConfigTag("AP","VER",tmpstr1);
                            if(strcmp(tmpstr1,node2->txt)!=0)
                            {     
                                SetConfigTag("AP","VER",node2->txt);
                                SetConfigTag("BLC","UPDATEFLAG","1");
                            }
                        }   
                     break;
                 case 4:
                    
                        sprintf(tmpstr,"T558803");
                        node2 = ezxml_get(node,tmpstr,-1);
                        if(node2!=NULL)
                        {
                            GetConfigTag("PARAMETER","VER",tmpstr1);
                            if(strcmp(tmpstr1,node2->txt)!=0)
                            {     
                                SetConfigTag("PARAMETER","VER",node2->txt);
                                SetConfigTag("PARAMETER","UPDATEFLAG","1");
                            }
                        }  
                               
                     break;    
                   
                }        
               SaveConfigFile();              
              break;
       case 5589:     
            
               break;
     /*  case 5590:   
              ezxml_set_txt(node,TransData->ucTxnAmt);        break;*/
       case 5591:     
             break;
       case 5592:     
                break;
       case 5595:     
               sprintf(tmpstr,"T559501");
               node2 = ezxml_get(node, "Trans", 0,tmpstr,-1);
               if(node2!=NULL)
               usSetTagData(node2,TransData->ucTMS_ParmVER);     
               
               sprintf(tmpstr,"T559502");
                node2 = ezxml_get(node, "Trans", 0,tmpstr,-1);
                 if(node2!=NULL)
                     usSetTagData(node2,TransData->ucTMS_ParmID);     
               
               sprintf(tmpstr,"T559503");
               node2 = ezxml_get(node, "Trans", 0,tmpstr,-1);
               if(node2!=NULL)
                    usSetTagData(node2,TransData->ucTMS_ParmData);     
               
               sprintf(tmpstr,"T559504");
                 node2 = ezxml_get(node, "Trans", 0,tmpstr,-1);
                if(node2!=NULL) usSetTagData(node2,TransData->ucTMS_ParmVaildStartDate);   
               
               sprintf(tmpstr,"T559505");
               node2 = ezxml_get(node, "Trans", 0,tmpstr,-1);
               if(node2!=NULL) usSetTagData(node2,TransData->ucTMS_ParmVaildENDDate);   
               break;
       case 5596:    
              sprintf(tmpstr,"T559601");
               node2 = ezxml_get(node, "Trans", 0,tmpstr,-1);
                 if(node2!=NULL) usSetTagData(node2,TransData->Transfer_TotlePackCnt);     
               
               sprintf(tmpstr,"T559602");
                node2 = ezxml_get(node, "Trans", 0,tmpstr,-1);
                 if(node2!=NULL) usSetTagData(node2,TransData->Transfer_SendedPackCnt);    
               
               sprintf(tmpstr,"T559603");
                node2 = ezxml_get(node, "Trans", 0,tmpstr,-1);
                 if(node2!=NULL) usSetTagData(node2,TransData->Transfer_ReceivedPackCnt);
               
               sprintf(tmpstr,"T559604");
               node2 = ezxml_get(node, "Trans", 0,tmpstr,-1);
                 if(node2!=NULL) usSetTagData(node2,TransData->Transfer_SendPackSN);
               break;
       case 6000:   
              usSetTagData(node,(char *)&TransData->ucReaderFWVersion);        break;
       case 6001:   
              usSetTagData(node,(char *)&TransData->ReaderAVRDATA);        break;
       case 6002:    
              usSetTagData(node,(BYTE *)&TransData->stTermHostInfo_t);       break;
       case 6003:     
              usSetTagData(node,(BYTE *)&TransData->stTermParaInfo_t);      break;
       case 6004:    
              usSetTagData(node,(char *)&TransData->ucBLVersion);       break;
       case 6400:    
              usSetTagData(node,(char *)&TransData->ucSTAC);       break;
       case 6401:  
              usSetTagData(node,(char *)&TransData->HTAC);         break;
       case 6402:   
              usSetTagData(node,(char *)&TransData->CTAC);        break;
       case 6403:   
              usSetTagData(node,(char *)&TransData->MAC);        break;
       case 6404:   
              usSetTagData(node,(char *)&TransData->CPUMAC_HCrypto);        break;
       case 6405:   
              usSetTagData(node,(char *)&TransData->CPUSignature);        break;
       case 6406:     
              usSetTagData(node,(char *)&TransData->CPUTermCrypto);      break;
       case 6407:   
              usSetTagData(node,(char *)&TransData->HostCrypto);        break;
       case 6408:     
              usSetTagData(node,(char *)&TransData->ucSATOKEN);      break;
       case 6409:   
              usSetTagData(node,(char *)&TransData->HostToken);        break;
   
    }
        
    return d_OK;
}