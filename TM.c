#include "ECCAPP.h"

int inBuildResetData(int inTxnType,Reset_TM_Out *APIOut,Reset_APDU_In *DongleIn,Reset_APDU_Out *DongleOut)
{
	int inTMOutLen;
        USHORT ret;
	Store_Data stStore_DataInfo_t;
        
	inTMOutLen = sizeof(Reset_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,0x00,APIOut->ucProcessignCode);//Processing Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List Version
//	inCnt++;//Msg Type
//	inCnt++;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucDeviceID[2];//Service Provider
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleIn->ucTMTxnDateTime,sizeof(APIOut->ucTMTxnDateTime));//TM Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleIn->ucTMSerialNumber,sizeof(APIOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleIn->ucTMAgentNumber,sizeof(APIOut->ucTMAgentNumber));//TM Agent Number
	memcpy(APIOut->ucSTAC,DongleOut->ucSTAC,sizeof(APIOut->ucSTAC));//S-TAC
	APIOut->ucKeyVersion = DongleOut->ucSAMKeyVersion;//Key Version
	memcpy(APIOut->ucSAMID,DongleOut->ucSAMID,sizeof(APIOut->ucSAMID));//SAM ID
	memcpy(APIOut->ucSAMSN,DongleOut->ucSAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
	memcpy(APIOut->ucSAMCRN,DongleOut->ucSAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader Firmward Version
	memcpy(APIOut->ucNetManagementWorkCode,NETWORK_MANAGEMENT_CODE,sizeof(APIOut->ucNetManagementWorkCode));//Network Management Code
	APIOut->stTermHostInfo_t.ucOneDayQuotaFlag = DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag0 |
						    (DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag1 << 4);//One Day Quota Flag
	memcpy(APIOut->stTermHostInfo_t.ucOneDayQuota,DongleOut->stSAMParameterInfo_t.ucOneDayQuota,sizeof(APIOut->stTermHostInfo_t.ucOneDayQuota));//One Day Quota
	APIOut->stTermHostInfo_t.ucOnceQuotaFlag = DongleOut->stSAMParameterInfo_t.bOnceQuotaFlag2;//Once Quota Flag
	memcpy(APIOut->stTermHostInfo_t.ucOnceQuota,DongleOut->stSAMParameterInfo_t.ucOnceQuota,sizeof(APIOut->stTermHostInfo_t.ucOnceQuota));//Once Quota
	APIOut->stTermHostInfo_t.ucCheckEVFlag = DongleOut->stSAMParameterInfo_t.bCheckEVFlag6;//Check EV Flag
	APIOut->stTermHostInfo_t.ucAddQuotaFlag = DongleOut->stSAMParameterInfo_t.ucAddQuotaFlag;//Add Quota Flag
	memcpy(APIOut->stTermHostInfo_t.ucAddQuota,DongleOut->stSAMParameterInfo_t.ucAddQuota,sizeof(APIOut->stTermHostInfo_t.ucAddQuota));//Add Quota
	APIOut->stTermHostInfo_t.ucCheckDeductFlag = DongleOut->stSAMParameterInfo_t.bCheckDeductFlag3;//Check Debit Flag
	memcpy(APIOut->stTermHostInfo_t.ucCheckDeductValue,DongleOut->stSAMParameterInfo_t.ucCheckDeductValue,sizeof(APIOut->stTermHostInfo_t.ucCheckDeductValue));//Check Debit
	APIOut->stTermHostInfo_t.ucDeductLimitFlag = DongleOut->stSAMParameterInfo_t.bDeductLimitFlag7;//Deduct Limit Flag
	memcpy(APIOut->stTermHostInfo_t.ucAPIVersion,API_VERSION,3);//API Version
	APIOut->stTermHostInfo_t.ucAPIVersion[3] = 0x00;
#ifdef MARKET_7_11
	APIOut->stTermHostInfo_t.ucAPIVersion[3] = 0x01;
#endif
//	inLen = sizeof(APIOut->ucTermHostInfo_t.ucRFU);//RFU
	//memcpy(APIOut->stTermParaInfo_t.ucRemainderAddQuota,DongleOut->ucRemainderAddQuota,sizeof(APIOut->stTermParaInfo_t.ucRemainderAddQuota));//Remainder Add Quota
	memcpy(APIOut->stTermParaInfo_t.ucDeMAC,DongleOut->ucDeMAC,sizeof(APIOut->stTermParaInfo_t.ucDeMAC));//De MAC
//	inLen = sizeof(APIOut->stTermParaInfo_t.ucRFU);//RFU
//	inLen = sizeof(APIOut->);//CPU Card ID
//	inLen = sizeof(APIOut->);//CPU Txn Amt
	memcpy(APIOut->ucCPUDeviceID,DongleOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucCPUSPID,&DongleOut->ucCPUDeviceID[3],sizeof(APIOut->ucCPUSPID));//CPU SP ID
//	inLen = sizeof(APIOut->);//CPU EV Before Txn
	memcpy(APIOut->ucCPUSAMID,DongleOut->ucCPUSAMID,sizeof(APIOut->ucCPUSAMID));//CPU SAM ID
	memcpy(APIOut->ucSTC,DongleOut->ucSTC,sizeof(APIOut->ucSTC));//CPU SAM Txn Cnt
	APIOut->stCPUSAMInfo_t.ucSAMVersion = DongleOut->ucSAMVersion;//SAM Version Number
	memcpy(APIOut->stCPUSAMInfo_t.ucSAMUsageControl,DongleOut->ucSAMUsageControl,sizeof(APIOut->stCPUSAMInfo_t.ucSAMUsageControl));//SAM Usage Control
	APIOut->stCPUSAMInfo_t.ucSAMAdminKVN = DongleOut->ucSAMAdminKVN;//SAM Admin KVN
	APIOut->stCPUSAMInfo_t.ucSAMIssuerKVN = DongleOut->ucSAMIssuerKVN;//SAM Issuer KVN
	memcpy(APIOut->stCPUSAMInfo_t.ucTagListTable,DongleOut->ucTagListTable,sizeof(APIOut->stCPUSAMInfo_t.ucTagListTable));//SAM Tag List Table
	memcpy(APIOut->stCPUSAMInfo_t.ucSAMIssuerSpecData,DongleOut->ucSAMIssuerSpecData,sizeof(APIOut->stCPUSAMInfo_t.ucSAMIssuerSpecData));//SAM Issuer Spec Data
	memcpy(APIOut->ucRSAM,DongleOut->ucRSAM,sizeof(APIOut->ucRSAM));//CPU RSAM
	memcpy(APIOut->ucRHOST,DongleOut->ucRHOST,sizeof(APIOut->ucRHOST));//CPU RHOST
	memcpy(APIOut->ucAuthCreditLimit,DongleOut->ucAuthCreditLimit,sizeof(APIOut->ucAuthCreditLimit));//CPU Auth Credit Limit
	memcpy(APIOut->ucAuthCreditBalance,DongleOut->ucAuthCreditBalance,sizeof(APIOut->ucAuthCreditBalance));//CPU Auth Credit Balance
	memcpy(APIOut->ucAuthCreditCumulative,DongleOut->ucAuthCreditCumulative,sizeof(APIOut->ucAuthCreditCumulative));//CPU Auth Credit Cumulative
	memcpy(APIOut->ucAuthCancelCreditCumulative,DongleOut->ucAuthCancelCreditCumulative,sizeof(APIOut->ucAuthCancelCreditCumulative));//CPU Auth Cancel Credit Cumulative
	memcpy(APIOut->ucSingleCreditTxnAmtLimit,DongleOut->ucSingleCreditTxnAmtLimit,sizeof(APIOut->ucSingleCreditTxnAmtLimit));//CPU Single Credit Txn Amt Limit
	memcpy(APIOut->ucTMLocationID,DongleIn->ucTMLocationID,sizeof(APIOut->ucTMLocationID));//CPU TM Location ID
	memcpy(APIOut->ucSATOKEN,DongleOut->ucSATOKEN,sizeof(APIOut->ucSATOKEN));//CPU SA TOKEN
	memcpy(APIOut->stLastSignOnInfo_t.ucPreCPUDeviceID,DongleOut->stLastSignOnInfo_t.ucPreCPUDeviceID,sizeof(APIOut->stLastSignOnInfo_t));//CPU Last Sign On Info
	APIOut->ucSAMSignOnControlFlag = DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag4 |
					(DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag5<<4);//CPU SAM Sign On Control Flag
	APIOut->ucHostSpecVersionNo = DongleOut->ucHostSpecVersionNo;//CPU Spec. Version Number
	APIOut->ucOneDayQuotaWrite = DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite2 |
				     (DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite3<<1);//CPU One Day Quota Write Flag
	APIOut->ucCPDReadFlag = DongleOut->stSAMParameterInfo_t.bCPDReadFlag0 |
			       (DongleOut->stSAMParameterInfo_t.bCPDReadFlag1<<3);//CPU CPD Read
//			       (DongleOut->stSAMParameterInfo_t.bCPDReadFlag1<<1);//CPU CPD Read

	
	
               
	
	return(inTMOutLen);
}

int inBuildSignOnData(int inTxnType,SignOn_TM_Out *APIOut,SignOn_APDU_In *DongleIn,SignOn_APDU_Out *DongleOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(SignOn_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,0x00,APIOut->ucProcessignCode);//Processing Code
//	inCnt++;//Msg Type
//	inCnt++;//Sub Type
	memcpy(APIOut->ucDeviceID,stStore_DataInfo_t.ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	memcpy(APIOut->ucTxnDateTime,stStore_DataInfo_t.ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	memcpy(APIOut->ucConfirmCode,DongleOut->ucStatusCode,sizeof(APIOut->ucConfirmCode));//Confirm Code
//	inLen = sizeof(APIOut->);//CPU Card ID
	memcpy(APIOut->ucCPUDeviceID,stStore_DataInfo_t.ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucSTC,stStore_DataInfo_t.ucSTC,sizeof(APIOut->ucSTC));//CPU SAM Txn Cnt
	APIOut->ucCreditBalanceChangeFlag = DongleOut->ucCreditBalanceChangeFlag;//Credit Balance Change Flag
	memcpy(APIOut->ucCACrypto,DongleOut->ucCACrypto,sizeof(APIOut->ucCACrypto));//CACrypto

	return(inTMOutLen);
}

int inBuildSignOnQueryData(int inTxnType,SignOnQuery_TM_Out *APIOut,SignOnQuery_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(SignOnQuery_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(DongleOut->ucAuthCreditLimit,sizeof(DongleOut->ucAuthCreditLimit),APIOut->anAuthCreditLimit,sizeof(APIOut->anAuthCreditLimit),' ',10);
	vdUIntToAsc(DongleOut->ucAuthCreditBalance,sizeof(DongleOut->ucAuthCreditBalance),APIOut->anAuthCreditBalance,sizeof(APIOut->anAuthCreditBalance),' ',10);
	vdUIntToAsc(DongleOut->ucAuthCreditCumulative,sizeof(DongleOut->ucAuthCreditCumulative),APIOut->anAuthCreditCumulative,sizeof(APIOut->anAuthCreditCumulative),' ',10);
	vdUIntToAsc(DongleOut->ucAuthCancelCreditCumulative,sizeof(DongleOut->ucAuthCancelCreditCumulative),APIOut->anAuthCancelCreditCumulative,sizeof(APIOut->anAuthCancelCreditCumulative),' ',10);
	APIOut->anCPDReadFlag = DongleOut->stSAMParameterInfo_t.bCPDReadFlag0 |
			       (DongleOut->stSAMParameterInfo_t.bCPDReadFlag1<<3);//CPU CPD Read
//			       (DongleOut->stSAMParameterInfo_t.bCPDReadFlag1<<1);//CPU CPD Read
	APIOut->anOneDayQuotaWrite = DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite2 |
				     (DongleOut->stSAMParameterInfo_t.bOneDayQuotaWrite3<<1);//CPU One Day Quota Write Flag
	APIOut->anSAMSignOnControlFlag = DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag4 |
					(DongleOut->stSAMParameterInfo_t.bSAMSignOnControlFlag5<<4);//CPU SAM Sign On Control Flag
	APIOut->anCheckEVFlag = DongleOut->stSAMParameterInfo_t.bCheckEVFlag6;//Check EV Flag
	APIOut->anDeductLimitFlag = DongleOut->stSAMParameterInfo_t.bDeductLimitFlag7;//Deduct Limit Flag
	APIOut->anOneDayQuotaFlag = DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag0 |
				   (DongleOut->stSAMParameterInfo_t.bOneDayQuotaFlag1 << 4);//One Day Quota Flag
	vdUIntToAsc(DongleOut->stSAMParameterInfo_t.ucOneDayQuota,sizeof(DongleOut->stSAMParameterInfo_t.ucOneDayQuota),APIOut->anOneDayQuota,sizeof(APIOut->anOneDayQuota),' ',10);//One Day Quota
	APIOut->anOnceQuotaFlag = DongleOut->stSAMParameterInfo_t.bOnceQuotaFlag2;//Once Quota Flag
	vdUIntToAsc(DongleOut->stSAMParameterInfo_t.ucOnceQuota,sizeof(DongleOut->stSAMParameterInfo_t.ucOnceQuota),APIOut->anOnceQuota,sizeof(APIOut->anOnceQuota),' ',10);//Once Quota
	APIOut->anCheckDeductFlag = DongleOut->stSAMParameterInfo_t.bCheckDeductFlag3;//Check Debit Flag
	vdUIntToAsc(DongleOut->stSAMParameterInfo_t.ucCheckDeductValue,sizeof(DongleOut->stSAMParameterInfo_t.ucCheckDeductValue),APIOut->anCheckDeductValue,sizeof(APIOut->anCheckDeductValue),' ',10);//Check Debit
	APIOut->anAddQuotaFlag = DongleOut->stSAMParameterInfo_t.ucAddQuotaFlag;//Add Quota Flag
	vdUIntToAsc(DongleOut->stSAMParameterInfo_t.ucAddQuota,sizeof(DongleOut->stSAMParameterInfo_t.ucAddQuota),APIOut->anAddQuota,sizeof(APIOut->anAddQuota),' ',10);//Add Quota
	vdUIntToAsc(DongleOut->ucRemainderAddQuota,sizeof(DongleOut->ucRemainderAddQuota),APIOut->anRemainderAddQuota,sizeof(APIOut->anRemainderAddQuota),' ',10);//Remainder Add Quota
	vdUIntToAsc(DongleOut->ucCancelCreditQuota,sizeof(DongleOut->ucCancelCreditQuota),APIOut->anCancelCreditQuota,sizeof(APIOut->anCancelCreditQuota),' ',10);//Cancel Credit Quota
	vdUIntToAsc(&DongleOut->ucSPID,sizeof(DongleOut->ucSPID),APIOut->anSPID,sizeof(APIOut->anSPID),' ',10);//SP ID
	vdUIntToAsc(DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),APIOut->anCPUSPID,sizeof(APIOut->anCPUSPID),' ',10);//CPU SP ID
	fnLongToUnix(APIOut->anLastTxnDateTime,(unsigned long *)DongleOut->ucLastTxnDateTime,14);//最後一次SignOn成功時間

	return(inTMOutLen);
}

int inBuildReadCardBasicDataData(int inTxnType,ReadCardBasicData_TM_Out *APIOut,ReadCardBasicData_APDU_Out *DongleOut)
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
	vdBuildReadCardBasicData2(0x02,&DongleOut->stLastCreditTxnLogInfo_t,&APIOut->stLastCreditTxnRecoredInfo_t);
	vdBuildReadCardBasicData2(0x01,&DongleOut->stLastDebitTxnLogInfo_t,&APIOut->stLastDebitTxnRecoredInfo_t);

	return(inTMOutLen);
}

void vdBuildReadCardBasicData2(BYTE ucMsgType,LastTxnLog_t *DongleOutLog,LastTxnRecored_t *APIOutRecored)
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

int inBuildTxnReqOnlineData1(int inTxnType,TxnReqOnline_TM_Out_1 *APIOut,TxnReqOnline_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(TxnReqOnline_TM_Out_1);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->anCardID,sizeof(APIOut->anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(DongleOut->ucDeviceID,APIOut->anDeviceID,sizeof(APIOut->anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(DongleOut->ucCPUDeviceID,APIOut->anCPUDeviceID,sizeof(APIOut->anCPUDeviceID),LEVEL2);//n_TXN Device ID
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->anEVBeforeTxn,sizeof(APIOut->anEVBeforeTxn),' ',10);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->anTxnSN,sizeof(APIOut->anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),APIOut->anTxnAmt,sizeof(APIOut->anTxnAmt),' ',10);//n_TXN AMT
	APIOut->ucAutoLoad = DongleOut->bAutoLoad;//AutoLoad Flag
	vdUIntToAsc(DongleOut->ucAutoLoadAmt,sizeof(DongleOut->ucAutoLoadAmt),APIOut->anAutoLoadAmt,sizeof(APIOut->anAutoLoadAmt),' ',10);//n_AutoLoad Amount

	return(inTMOutLen);
}

int inBuildTxnReqOnlineData2(int inTxnType,TxnReqOnline_TM_Out_2 *APIOut,TxnReqOnline_APDU_In *DongleIn,TxnReqOnline_APDU_Out *DongleOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	inTMOutLen = sizeof(TxnReqOnline_TM_Out_2);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,DongleOut->ucMsgType,DongleOut->ucSubType,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List
	APIOut->ucMsgType = DongleOut->ucMsgType;//Msg Type
	APIOut->ucSubType = DongleOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucSPID;//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
	APIOut->ucLocationID = DongleOut->ucLocationID;//Location ID
	APIOut->ucBankCode = DongleOut->ucBankCode;//Bank Code
	memcpy(APIOut->ucLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucLoyaltyCounter));//Loyalty Counter
	memcpy(APIOut->ucExpiryDate,DongleOut->ucExpiryDate,sizeof(APIOut->ucExpiryDate));//Expiry Date
	APIOut->ucAreaCode = DongleOut->ucAreaCode;//Area Code
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleIn->ucTMTxnDateTime,sizeof(APIOut->ucTMTxnDateTime));//TM Txn Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(APIOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleIn->ucTMAgentNumber,sizeof(APIOut->ucTMAgentNumber));//TM Agent Number
	memcpy(APIOut->ucSTAC,DongleOut->ucSTAC,sizeof(APIOut->ucSTAC));//STAC
	APIOut->ucKeyVersion = DongleOut->ucSAMKVN;//SAM KVN
	memcpy(APIOut->ucSAMID,DongleOut->ucSAMID,sizeof(APIOut->ucSAMID));//SAM ID
	memcpy(APIOut->ucSAMSN,DongleOut->ucSAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
	memcpy(APIOut->ucSAMCRN,DongleOut->ucSAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader FW Version
	memcpy(APIOut->ucCardID,DongleOut->ucCardID,sizeof(APIOut->ucCardID));//Card ID
	memcpy(APIOut->ucTxnAmt,DongleOut->ucTxnAmt,sizeof(APIOut->ucTxnAmt));//Txn Amt
	memcpy(APIOut->ucCPUDeviceID,DongleOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucCPUSPID,DongleOut->ucCPUSPID,sizeof(APIOut->ucCPUSPID));//CPU SP ID
	memcpy(APIOut->ucCPULocationID,DongleOut->ucCPULocationID,sizeof(APIOut->ucCPULocationID));//CPU Location ID
	memcpy(APIOut->ucPID,DongleOut->ucPID,sizeof(APIOut->ucPID));//CPU Purse ID
	memcpy(APIOut->ucCTC,DongleOut->ucCTC,sizeof(APIOut->ucCTC));//CPU CTC
	memcpy(APIOut->ucProfileExpiryDate,DongleOut->ucProfileExpiryDate,sizeof(APIOut->ucProfileExpiryDate));//Profile Expiry Date
	memcpy(APIOut->ucSubAreaCode,DongleOut->ucSubAreaCode,sizeof(APIOut->ucSubAreaCode));//Sub Area Code
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN,sizeof(APIOut->ucTxnSN));//Txn SN
	memcpy(APIOut->ucEV,DongleOut->ucEV,sizeof(APIOut->ucEV));//EV
	memcpy(APIOut->ucDeposit,DongleOut->ucDeposit,sizeof(APIOut->ucDeposit));//Deposit
	APIOut->ucCPUAdminKeyKVN = DongleOut->ucCPUAdminKeyKVN;//CPU Admin Key KVN
	APIOut->ucCreditKeyKVN = DongleOut->ucCreditKeyKVN;//Credit Key KVN
	APIOut->ucCPUIssuerKeyKVN = DongleOut->ucCPUIssuerKeyKVN;//CPU Issuer Key KVN
	APIOut->ucTxnMode = DongleOut->ucTxnMode;//Txn Mode
	APIOut->ucTxnQuqlifier = DongleOut->ucTxnQuqlifier;//Txn Quqlifier
	APIOut->ucSignatureKeyKVN = DongleOut->ucSignatureKeyKVN;//Signature Key KVN
	memcpy(APIOut->ucCPUSAMID,DongleOut->ucCPUSAMID,sizeof(APIOut->ucCPUSAMID));//CPU SAM ID
	APIOut->ucHostAdminKVN = DongleOut->ucHostAdminKVN;//Host Admin KVN
	APIOut->ucPurseVersionNumber = DongleOut->ucPurseVersionNumber;//Purse Version Number
	memcpy(APIOut->ucTMLocationID,DongleIn->ucTMLocationID,sizeof(APIOut->ucTMLocationID));//TM Location ID
	memcpy(APIOut->ucCACrypto,DongleOut->ucTxnCrypto,8);//CACrypto前8碼
	memset(&APIOut->ucCACrypto[8],0x00,8);//CACrypto後8碼
	vdBuildCardAVRData(&APIOut->stCardAVRInfo_t,&DongleOut->stLastCreditTxnLogInfo_t,DongleOut->ucCardID,DongleOut->ucIssuerCode,DongleOut->ucCPUSPID,DongleOut->ucCPULocationID,DongleOut->ucPID,APIOut->ucLoyaltyCounter);//Card AVR Info
	vdBuildReaderAVRData(&APIOut->stReaderAVRInfo_t,&DongleOut->stReaderAVRInfo_t);//Reader AVR Info
	//memcpy(&APIOut->stReaderAVRInfo_t,&DongleOut->stReaderAVRInfo_t,sizeof(APIOut->stReaderAVRInfo_t));//Reader AVR Info
	APIOut->ucCardIDLen = DongleOut->ucCardIDLen;//Card ID Len

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	memcpy(stStore_DataInfo_t.ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));
	vdSaveReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));

	return(inTMOutLen);
}

int inBuildTxnReqOnlineData3(int inTxnType,CardSale_TM_Out *APIOut,TxnReqOnline_APDU_In *DongleIn,TxnReqOnline_APDU_Out *DongleOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	inTMOutLen = sizeof(CardSale_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,DongleOut->ucMsgType,DongleOut->ucSubType,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List
	APIOut->ucMsgType = DongleOut->ucMsgType;//Msg Type
	APIOut->ucSubType = DongleOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucSPID;//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
	APIOut->ucLocationID = DongleOut->ucLocationID;//Location ID
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleIn->ucTMTxnDateTime,sizeof(APIOut->ucTMTxnDateTime));//TM Txn Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(APIOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleIn->ucTMAgentNumber,sizeof(APIOut->ucTMAgentNumber));//TM Agent Number
	memcpy(APIOut->ucSTAC,DongleOut->ucSTAC,sizeof(APIOut->ucSTAC));//STAC
	APIOut->ucKeyVersion = DongleOut->ucSAMKVN;//SAM KVN
	memcpy(APIOut->ucSAMID,DongleOut->ucSAMID,sizeof(APIOut->ucSAMID));//SAM ID
	memcpy(APIOut->ucSAMSN,DongleOut->ucSAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
	memcpy(APIOut->ucSAMCRN,DongleOut->ucSAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader FW Version
	memcpy(APIOut->ucCardID,DongleOut->ucCardID,sizeof(APIOut->ucCardID));//Card ID
	memcpy(APIOut->ucTxnAmt,DongleOut->ucTxnAmt,sizeof(APIOut->ucTxnAmt));//Txn Amt
	memcpy(APIOut->ucCPUDeviceID,DongleOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucCPUSPID,DongleOut->ucCPUSPID,sizeof(APIOut->ucCPUSPID));//CPU SP ID
	memcpy(APIOut->ucCPULocationID,DongleOut->ucCPULocationID,sizeof(APIOut->ucCPULocationID));//CPU Location ID
	memcpy(APIOut->ucPID,DongleOut->ucPID,sizeof(APIOut->ucPID));//CPU Purse ID
	memcpy(APIOut->ucCTC,DongleOut->ucCTC,sizeof(APIOut->ucCTC));//CPU CTC
	memcpy(APIOut->ucSubAreaCode,DongleOut->ucSubAreaCode,sizeof(APIOut->ucSubAreaCode));//Sub Area Code
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN,sizeof(APIOut->ucTxnSN));//Txn SN
	memcpy(APIOut->ucEV,DongleOut->ucEV,sizeof(APIOut->ucEV));//EV
	memcpy(APIOut->ucDeposit,DongleOut->ucDeposit,sizeof(APIOut->ucDeposit));//Deposit
	APIOut->ucCPUAdminKeyKVN = DongleOut->ucCPUAdminKeyKVN;//CPU Admin Key KVN
	APIOut->ucCreditKeyKVN = DongleOut->ucCreditKeyKVN;//Credit Key KVN
	APIOut->ucCPUIssuerKeyKVN = DongleOut->ucCPUIssuerKeyKVN;//CPU Issuer Key KVN
	APIOut->ucTxnMode = DongleOut->ucTxnMode;//Txn Mode
	APIOut->ucTxnQuqlifier = DongleOut->ucTxnQuqlifier;//Txn Quqlifier
	memcpy(APIOut->ucCPUSAMID,DongleOut->ucCPUSAMID,sizeof(APIOut->ucCPUSAMID));//CPU SAM ID
	APIOut->ucHostAdminKVN = DongleOut->ucHostAdminKVN;//Host Admin KVN
	APIOut->ucPurseVersionNumber = DongleOut->ucPurseVersionNumber;//Purse Version Number
	memcpy(APIOut->ucTMLocationID,DongleIn->ucTMLocationID,sizeof(APIOut->ucTMLocationID));//TM Location ID
	memcpy(APIOut->ucCACrypto,DongleOut->ucTxnCrypto,8);//CACrypto前8碼
	memset(&APIOut->ucCACrypto[8],0x00,8);//CACrypto後8碼
	vdBuildReaderAVRData(&APIOut->stReaderAVRInfo_t,&DongleOut->stReaderAVRInfo_t);//Reader AVR Info
	//memcpy(&APIOut->stReaderAVRInfo_t,&DongleOut->stReaderAVRInfo_t,sizeof(APIOut->stReaderAVRInfo_t));//Reader AVR Info
	APIOut->ucCardIDLen = DongleOut->ucCardIDLen;//Card ID Len

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	memcpy(stStore_DataInfo_t.ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));
	vdSaveReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));

	return(inTMOutLen);
}

int inBuildTxnReqOnlineData4(int inTxnType,CancelTxn_TM_Out *APIOut,TxnReqOnline_APDU_Out *DongleOut,BYTE ucMsgType)
{
int inTMOutLen;

	inTMOutLen = sizeof(CancelTxn_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	if(ucMsgType == 0x0B || ucMsgType == 0x02)
		memcpy(APIOut->ucDataLen,"310",sizeof(APIOut->ucDataLen));
	else if(ucMsgType == 0x09)
		memcpy(APIOut->ucDataLen,"252",sizeof(APIOut->ucDataLen));
	vdUIntToAsc(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->anCardID,sizeof(APIOut->anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(DongleOut->ucDeviceID,APIOut->anDeviceID,sizeof(APIOut->anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(DongleOut->ucCPUDeviceID,APIOut->anCPUDeviceID,sizeof(APIOut->anCPUDeviceID),LEVEL2);//n_TXN Device ID
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->anEVBeforeTxn,sizeof(APIOut->anEVBeforeTxn),' ',10);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->anTxnSN,sizeof(APIOut->anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),APIOut->anTxnAmt,sizeof(APIOut->anTxnAmt),' ',10);//n_TXN AMT
	APIOut->ucAutoLoad = DongleOut->bAutoLoad;//AutoLoad Flag
	vdUIntToAsc(DongleOut->ucAutoLoadAmt,sizeof(DongleOut->ucAutoLoadAmt),APIOut->anAutoLoadAmt,sizeof(APIOut->anAutoLoadAmt),' ',10);//n_AutoLoad Amount

	return(inTMOutLen);
}

void vdBuildCardAVRData(CardAVR_t *APIOutData,LastTxnLog_t *DongleOutLog,BYTE *ucCardID,BYTE ucIssuerCode,BYTE *ucCPUSPID,BYTE *ucCPULocationID,BYTE *ucPID,BYTE *ucLoyaltyCounter)
{

	APIOutData->ucMsgType = 0x0C;
	APIOutData->ucPurseVersionNumber = DongleOutLog->ucPurseVersionNumber_Index;//Purse Version Number 2
	memcpy(APIOutData->ucTxnSN,DongleOutLog->ucTxnSN,sizeof(APIOutData->ucTxnSN));//Txn SN 
	memcpy(APIOutData->ucTxnDateTime,DongleOutLog->ucTxnDateTime,sizeof(APIOutData->ucTxnDateTime));//Txn Date Time
	APIOutData->ucSubType = DongleOutLog->ucSubType;//Sub Type
	memcpy(APIOutData->ucTxnAmt,DongleOutLog->ucTxnAmt,sizeof(APIOutData->ucTxnAmt));//Txn Amt
	memcpy(APIOutData->ucEV,DongleOutLog->ucEV,sizeof(APIOutData->ucEV));//EV
	memcpy(APIOutData->ucCardID,ucCardID,sizeof(APIOutData->ucCardID));//Card ID
	APIOutData->ucIssuerCode = ucIssuerCode;//Issuer Code
	memcpy(APIOutData->ucCPUSPID,DongleOutLog->ucCPUSPID,sizeof(APIOutData->ucCPUSPID));//CPU SP ID
	//memcpy(APIOutData->ucCPUSPID,ucCPUSPID,sizeof(APIOutData->ucCPUSPID));//CPU SP ID
	memcpy(APIOutData->ucCPULocationID,DongleOutLog->ucCPULocationID,sizeof(APIOutData->ucCPULocationID));//CPU Location ID
	//memcpy(APIOutData->ucCPULocationID,ucCPULocationID,sizeof(APIOutData->ucCPULocationID));//CPU Location ID
	memcpy(APIOutData->ucPID,ucPID,sizeof(APIOutData->ucPID));//Loyalty Counter
	memcpy(APIOutData->ucCPUDeviceID,DongleOutLog->ucCPUDeviceID,sizeof(APIOutData->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOutData->ucLoyaltyCounter,ucLoyaltyCounter,sizeof(APIOutData->ucLoyaltyCounter));//Loyalty Counter

}

void vdBuildReaderAVRData(ReaderAVRTM_t *APIOutData,ReaderAVRAPDU_t *DongleOutLog)
{
	APIOutData->ucMsgType = DongleOutLog->ucMsgType;
	APIOutData->ucSubType = DongleOutLog->ucSubType;
	memcpy(APIOutData->ucDeviceID,DongleOutLog->ucDeviceID,sizeof(APIOutData->ucDeviceID));
	memcpy(APIOutData->ucCPUDeviceID,DongleOutLog->ucCPUDeviceID,sizeof(APIOutData->ucCPUDeviceID));
	memcpy(APIOutData->ucTxnDateTime,DongleOutLog->ucTxnDateTime,sizeof(APIOutData->ucTxnDateTime));
	APIOutData->ucPurseVersionNumber = DongleOutLog->ucPurseVersionNumber;
	memcpy(APIOutData->ucCardID,DongleOutLog->ucCardID,sizeof(APIOutData->ucCardID));
	memcpy(APIOutData->ucTxnSN,DongleOutLog->ucTxnSN,sizeof(APIOutData->ucTxnSN));
	memcpy(APIOutData->ucEV,DongleOutLog->ucEV,sizeof(APIOutData->ucEV));
	memcpy(APIOutData->ucStatusCode,DongleOutLog->ucStatusCode,sizeof(APIOutData->ucStatusCode));
	memcpy(APIOutData->ucPID,DongleOutLog->ucPID,sizeof(APIOutData->ucPID));
	memcpy(APIOutData->ucSignature,DongleOutLog->ucSignature,sizeof(APIOutData->ucSignature));
	memcpy(APIOutData->ucSAMID,DongleOutLog->ucSAMID,sizeof(APIOutData->ucSAMID));
	memcpy(APIOutData->ucMAC_HCrypto,DongleOutLog->ucMAC_HCrypto,sizeof(APIOutData->ucMAC_HCrypto));
	APIOutData->ucCardIDLen = DongleOutLog->ucCardIDLen;
}

int inBuildAuthTxnOnlineData(int inTxnType,AuthTxnOnline_TM_Out *APIOut,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthTxnOnline_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.anCardID,sizeof(APIOut->stSTMC_t.anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stSTMC_t.anDeviceID,sizeof(APIOut->stSTMC_t.anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(TxnReqOut->ucCPUDeviceID,APIOut->stSTMC_t.anCPUDeviceID,sizeof(APIOut->stSTMC_t.anCPUDeviceID),LEVEL2);//n_TXN Device ID
	vdCountEVBefore(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEVBeforeTxn,sizeof(APIOut->stSTMC_t.anEVBeforeTxn),TxnReqOut->ucMsgType);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.anTxnSN,sizeof(APIOut->stSTMC_t.anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),APIOut->stSTMC_t.anTxnAmt,sizeof(APIOut->stSTMC_t.anTxnAmt),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEV,sizeof(APIOut->stSTMC_t.anEV),' ',10);//n_EV
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->stSTMC_t.anProcessignCode);//Processing Code
	fnUnPack(&TxnReqOut->ucMsgType,sizeof(TxnReqOut->ucMsgType),APIOut->stSTMC_t.unMsgType);//Msg Type
	fnUnPack(&TxnReqOut->ucSubType,sizeof(TxnReqOut->ucSubType),APIOut->stSTMC_t.unSubType);//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stSTMC_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucSPID,sizeof(TxnReqOut->ucSPID),APIOut->stSTMC_t.unSPID);//SP ID
	fnUnPack(DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime),APIOut->stSTMC_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stSTMC_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stSTMC_t.unPersonalProfile);//Personal Profile
	fnUnPack(&TxnReqOut->ucLocationID,sizeof(TxnReqOut->ucLocationID),APIOut->stSTMC_t.unLocationID);//Location ID
	fnUnPack(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.unCardID);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stSTMC_t.unIssuerCode);//Issuer Code
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->stSTMC_t.unBankCode);//Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->stSTMC_t.unLoyaltyCounter);//Loyalty Counter
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		fnUnPack(DongleOut->ucMAC_HCrypto,10,APIOut->stSTMC_t.unMAC);//MAC
	else
		memset(APIOut->stSTMC_t.unMAC,0x30,sizeof(APIOut->stSTMC_t.unMAC));//MAC
	fnUnPack(TxnReqOut->ucExpiryDate,sizeof(TxnReqOut->ucExpiryDate),APIOut->stSTMC_t.unOrgExpiryDate);//Org Expiry Date
	fnUnPack(DongleIn->ucExpiryDate,sizeof(DongleIn->ucExpiryDate),APIOut->stSTMC_t.unNewExpiryDate);//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stSTMC_t.unAreaCode);//Area Code
	fnUnPack(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),APIOut->stSTMC_t.unTxnAmt);//Txn Amt
	fnUnPack(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.unEV);//EV
	fnUnPack(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.unTxnSN);//Txn SN
	fnUnPack(TxnReqOut->ucCPUDeviceID,sizeof(TxnReqOut->ucCPUDeviceID),APIOut->stSTMC_t.unCPUDeviceID);//CPU Device ID
	fnUnPack(TxnReqOut->ucCPUSPID,sizeof(TxnReqOut->ucCPUSPID),APIOut->stSTMC_t.unCPUSPID);//CPU SP ID
	fnUnPack(TxnReqOut->ucCPULocationID,sizeof(TxnReqOut->ucCPULocationID),APIOut->stSTMC_t.unCPULocationID);//CPU Location ID
	fnUnPack(TxnReqOut->ucPID,sizeof(TxnReqOut->ucPID),APIOut->stSTMC_t.unPID);//Purse ID
	fnUnPack(TxnReqOut->ucCTC,sizeof(TxnReqOut->ucCTC),APIOut->stSTMC_t.unCTC);//CTC
	fnUnPack(TxnReqOut->ucProfileExpiryDate,sizeof(TxnReqOut->ucProfileExpiryDate),APIOut->stSTMC_t.unOrgProfileExpiryDate);//Org Profile Expiry Date
	fnUnPack(DongleIn->ucProfileExpiryDate,sizeof(DongleIn->ucProfileExpiryDate),APIOut->stSTMC_t.unNewProfileExpiryDate);//New Profile Expiry Date
	fnUnPack(TxnReqOut->ucSubAreaCode,sizeof(TxnReqOut->ucSubAreaCode),APIOut->stSTMC_t.unSubAreaCode);//Sub Area Code
	fnUnPack(TxnReqOut->ucTxnSN,sizeof(TxnReqOut->ucTxnSN),APIOut->stSTMC_t.unTxnSNBeforeTxn);//Txn SN Before Txn
	fnUnPack(TxnReqOut->ucEV,sizeof(TxnReqOut->ucEV),APIOut->stSTMC_t.unEVBeforeTxn);//EV Before Txn
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stSTMC_t.unDeposit);//Deposit
	fnUnPack(&TxnReqOut->ucTxnMode,sizeof(TxnReqOut->ucTxnMode),APIOut->stSTMC_t.unTxnMode);//Txn Mode
	fnUnPack(&TxnReqOut->ucTxnQuqlifier,sizeof(TxnReqOut->ucTxnQuqlifier),APIOut->stSTMC_t.unTxnQuqlifier);//Txn Quqlifier
	fnUnPack(&TxnReqOut->ucSignatureKeyKVN,sizeof(TxnReqOut->ucSignatureKeyKVN),APIOut->stSTMC_t.unSignatureKeyKVN);//Signature Key KVN
	fnUnPack(DongleOut->ucSignature,sizeof(DongleOut->ucSignature),APIOut->stSTMC_t.unSignature);//Signature
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
		fnUnPack(&DongleOut->ucMAC_HCrypto[0],1,APIOut->stSTMC_t.unHashType);//Hash Type
	else
		memset(APIOut->stSTMC_t.unHashType,0x30,sizeof(APIOut->stSTMC_t.unHashType));
	fnUnPack(DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),APIOut->stSTMC_t.unCPUSAMID);//SAM ID
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
	{
		fnUnPack(&DongleOut->ucMAC_HCrypto[1],1,APIOut->stSTMC_t.unHostAdminKVN);//Host Admin KVN
		fnUnPack(&DongleOut->ucMAC_HCrypto[2],16,APIOut->stSTMC_t.unCPUMAC);//MAC
	}
	else
	{
		memset(APIOut->stSTMC_t.unHostAdminKVN,0x30,sizeof(APIOut->stSTMC_t.unHostAdminKVN));
		memset(APIOut->stSTMC_t.unCPUMAC,0x30,sizeof(APIOut->stSTMC_t.unCPUMAC));//MAC
	}
	fnUnPack(&TxnReqOut->ucPurseVersionNumber,sizeof(TxnReqOut->ucPurseVersionNumber),APIOut->stSTMC_t.unPurseVersionNumber);//Purse Version Number
	fnUnPack(&TxnReqOut->ucCardIDLen,sizeof(TxnReqOut->ucCardIDLen),APIOut->stSTMC_t.unCardIDLen);//Card ID Len
	memcpy(APIOut->stSTMC_t.ucTMLocationID,stStore_DataInfo_t.ucTMLocationID,sizeof(stStore_DataInfo_t.ucTMLocationID));//TM Location ID
	memcpy(APIOut->stSTMC_t.ucTMID,stStore_DataInfo_t.ucTMID,sizeof(stStore_DataInfo_t.ucTMID));//TM ID
	fnLongToUnix(APIOut->stSTMC_t.ucTMTxnDateTime,(unsigned long *)DongleOut->ucTxnDateTime,14);//TM Txn Date Time
	memcpy(APIOut->stSTMC_t.ucTMSerialNumber,stStore_DataInfo_t.ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->stSTMC_t.ucTMAgentNumber,stStore_DataInfo_t.ucTMAgentNumber,sizeof(stStore_DataInfo_t.ucTMAgentNumber));//TM Agent Number
	//帳務資料結束
	//Congirm資料開始
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",79);//Data Len
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	APIOut->ucMsgType = TxnReqOut->ucMsgType;//Msg Type
	APIOut->ucSubType = TxnReqOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,TxnReqOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	memcpy(APIOut->ucTxnDateTime,DongleOut->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->ucMAC,DongleOut->ucMAC_HCrypto,sizeof(APIOut->ucMAC));//MAC
	else
		memset(APIOut->ucMAC,0x00,sizeof(APIOut->ucMAC));//MAC
	memcpy(APIOut->ucConfirmCode,DongleOut->ucConfirmCode,sizeof(APIOut->ucConfirmCode));//Confirm Code
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->ucCTAC,&DongleOut->ucMAC_HCrypto[10],sizeof(APIOut->ucMAC));//CTAC
	else
		memset(APIOut->ucCTAC,0x00,sizeof(APIOut->ucMAC));//CTAC
	memcpy(APIOut->ucCardID,TxnReqOut->ucCardID,sizeof(APIOut->ucCardID));//Card ID
	memcpy(APIOut->ucEV,DongleOut->ucEV,sizeof(APIOut->ucEV));//EV
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN,sizeof(APIOut->ucTxnSN));//Txn SN
	memcpy(APIOut->ucCPUDeviceID,TxnReqOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucPID,TxnReqOut->ucPID,sizeof(APIOut->ucPID));//Purse ID
	memcpy(APIOut->ucSignature,DongleOut->ucSignature,sizeof(APIOut->ucSignature));//Signature
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
	{
		APIOut->ucHashType = DongleOut->ucMAC_HCrypto[0];//Hash Type
		APIOut->ucHostAdminKVN = DongleOut->ucMAC_HCrypto[1];//Host Admin KVN
		memcpy(APIOut->ucCPUMAC,&DongleOut->ucMAC_HCrypto[2],sizeof(APIOut->ucCPUMAC));//CPU MAC
	}
	else
	{
		APIOut->ucHashType = 0x00;
		APIOut->ucHostAdminKVN = 0x00;
		memset(APIOut->ucCPUMAC,0x00,sizeof(APIOut->ucCPUMAC));//CPU MAC
	}

	return(inTMOutLen);
}

int inBuildTxnReqOfflineData1(int inTxnType,TxnReqOffline_TM_Out_1 *APIOut,TxnReqOffline_APDU_In *DongleIn,TxnReqOffline_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(TxnReqOffline_TM_Out_1);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->anCardID,sizeof(APIOut->anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(DongleOut->ucDeviceID,APIOut->anDeviceID,sizeof(APIOut->anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(DongleOut->ucCPUDeviceID,APIOut->anCPUDeviceID,sizeof(APIOut->anCPUDeviceID),LEVEL2);//n_TXN Device ID
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->anEVBeforeTxn,sizeof(APIOut->anEVBeforeTxn),' ',10);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->anTxnSN,sizeof(APIOut->anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),APIOut->anTxnAmt,sizeof(APIOut->anTxnAmt),' ',10);//n_TXN AMT
	APIOut->ucAutoLoad = DongleOut->bAutoLoad;//AutoLoad Flag
	vdUIntToAsc(DongleOut->ucAutoLoadAmt,sizeof(DongleOut->ucAutoLoadAmt),APIOut->anAutoLoadAmt,sizeof(APIOut->anAutoLoadAmt),' ',10);//n_AutoLoad Amount

	return(inTMOutLen);
}

int inBuildTxnReqOfflineData2(int inTxnType,TxnReqOffline_TM_Out_2 *APIOut,TxnReqOffline_APDU_In *DongleIn,TxnReqOffline_APDU_Out *DongleOut)
{
int inTMOutLen;
BYTE ucLoyaltyCounter[2];

	inTMOutLen = sizeof(TxnReqOffline_TM_Out_2);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,DongleOut->ucMsgType,DongleOut->ucSubType,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List
	APIOut->ucMsgType = DongleOut->ucMsgType;//Msg Type
	APIOut->ucSubType = DongleOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucSPID;//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
	memcpy(APIOut->ucExpiryDate,DongleOut->ucExpiryDate,sizeof(APIOut->ucExpiryDate));//Expiry Date
	APIOut->ucAreaCode = DongleOut->ucAreaCode;//Area Code
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleIn->ucTMTxnDateTime,sizeof(APIOut->ucTMTxnDateTime));//TM Txn Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(APIOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleIn->ucTMAgentNumber,sizeof(APIOut->ucTMAgentNumber));//TM Agent Number
	if(DongleOut->ucPurseVersionNumber == MIFARE)
	{
		memcpy(APIOut->ucSTAC,DongleOut->ucSID_STAC,sizeof(APIOut->ucSTAC));//STAC
		APIOut->ucKeyVersion = DongleOut->ucCPDKVN_SAMKVN;//SAM KVN
		memcpy(APIOut->ucSAMID,&DongleOut->ucCPD_SAMID[2],sizeof(APIOut->ucSAMID));//SAM ID
		memcpy(APIOut->ucSAMSN,&DongleOut->ucCPD_SAMID[10],sizeof(APIOut->ucSAMSN));//SAM SN
		memcpy(APIOut->ucSAMCRN,DongleOut->ucCPDRAN_SAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	}
	else
	{
		memset(APIOut->ucSTAC,0x00,sizeof(APIOut->ucSTAC));//STAC
		APIOut->ucKeyVersion = 0;//SAM KVN
		memset(APIOut->ucSAMID,0x00,sizeof(APIOut->ucSAMID));//SAM ID
		memset(APIOut->ucSAMSN,0x00,sizeof(APIOut->ucSAMSN));//SAM SN
		memset(APIOut->ucSAMCRN,0x00,sizeof(APIOut->ucSAMCRN));//SAM CRN
	}
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader FW Version
	memcpy(APIOut->ucCardID,DongleOut->ucCardID,sizeof(APIOut->ucCardID));//Card ID
	memcpy(APIOut->ucTxnAmt,DongleOut->ucTxnAmt,sizeof(APIOut->ucTxnAmt));//Txn Amt
	memcpy(APIOut->ucCPUDeviceID,DongleOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucCPUSPID,DongleOut->ucCPUSPID,sizeof(APIOut->ucCPUSPID));//CPU SP ID
	memcpy(APIOut->ucCPULocationID,DongleOut->ucCPULocationID,sizeof(APIOut->ucCPULocationID));//CPU Location ID
	memcpy(APIOut->ucPID,DongleOut->ucPID,sizeof(APIOut->ucPID));//CPU Purse ID
	memcpy(APIOut->ucCTC,DongleOut->ucCTC,sizeof(APIOut->ucCTC));//CPU CTC
	memcpy(APIOut->ucProfileExpiryDate,DongleOut->ucProfileExpiryDate,sizeof(APIOut->ucProfileExpiryDate));//Profile Expiry Date
	memcpy(APIOut->ucSubAreaCode,DongleOut->ucSubAreaCode,sizeof(APIOut->ucSubAreaCode));//Sub Area Code
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN,sizeof(APIOut->ucTxnSN));//Txn SN
	memcpy(APIOut->ucEV,DongleOut->ucEV,sizeof(APIOut->ucEV));//EV
	APIOut->ucCPUAdminKeyKVN = DongleOut->ucCPUAdminKeyKVN;//CPU Admin Key KVN
	APIOut->ucCreditKeyKVN = DongleOut->ucCreditKeyKVN;//Credit Key KVN
	APIOut->ucCPUIssuerKeyKVN = DongleOut->ucCPUIssuerKeyKVN;//CPU Issuer Key KVN
	APIOut->ucTxnMode = DongleOut->ucTxnMode;//Txn Mode
	APIOut->ucTxnQuqlifier = DongleOut->ucTxnQuqlifier;//Txn Quqlifier
	if(DongleOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->ucCPUSAMID,&DongleOut->ucCPD_SAMID[2],sizeof(APIOut->ucCPUSAMID));//CPU SAM ID
	else
		memcpy(APIOut->ucCPUSAMID,DongleOut->ucSID_STAC,sizeof(APIOut->ucCPUSAMID));//CPU SAM ID
	if(DongleOut->ucPurseVersionNumber == MIFARE)
		APIOut->ucHostAdminKVN = 0x00;//Host Admin KVN
	else
		APIOut->ucHostAdminKVN = DongleOut->ucBankCode_HostAdminKVN;//Host Admin KVN
	APIOut->ucPurseVersionNumber = DongleOut->ucPurseVersionNumber;//Purse Version Number
	memcpy(APIOut->ucTMLocationID,DongleIn->ucTMLocationID,sizeof(APIOut->ucTMLocationID));//TM Location ID
	if(DongleOut->ucPurseVersionNumber == MIFARE)
		memset(APIOut->ucCACrypto,0x00,sizeof(APIOut->ucCACrypto));//CACrypto後8碼
	else
		memcpy(APIOut->ucCACrypto,DongleOut->ucSVCrypto,sizeof(APIOut->ucCACrypto));//CACrypto
	memcpy(APIOut->ucCardOneDayQuota,DongleOut->ucCardOneDayQuota,sizeof(APIOut->ucCardOneDayQuota));//Card One Day Quota
	memcpy(APIOut->ucCardOneDayQuotaDate,DongleOut->ucCardOneDayQuotaDate,sizeof(APIOut->ucCardOneDayQuotaDate));//Card One Day Quota Date
	memset(ucLoyaltyCounter,0x00,sizeof(ucLoyaltyCounter));
	vdBuildCardAVRData(&APIOut->stCardAVRInfo_t,&DongleOut->stLastCreditTxnLogInfo_t,DongleOut->ucCardID,DongleOut->ucIssuerCode,DongleOut->ucCPUSPID,DongleOut->ucCPULocationID,DongleOut->ucPID,ucLoyaltyCounter);//Card AVR Info
	APIOut->ucCardIDLen = DongleOut->ucCardIDLen;//Card ID Len

	return(inTMOutLen);
}

int inBuildAuthTxnOfflineData(int inTxnType,AuthTxnOffline_TM_Out *APIOut,AuthTxnOffline_APDU_In *DongleIn,AuthTxnOffline_APDU_Out *DongleOut,TxnReqOffline_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthTxnOffline_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.anCardID,sizeof(APIOut->stSTMC_t.anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stSTMC_t.anDeviceID,sizeof(APIOut->stSTMC_t.anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(TxnReqOut->ucCPUDeviceID,APIOut->stSTMC_t.anCPUDeviceID,sizeof(APIOut->stSTMC_t.anCPUDeviceID),LEVEL2);//n_TXN CPU Device ID
	vdCountEVBefore(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEVBeforeTxn,sizeof(APIOut->stSTMC_t.anEVBeforeTxn),TxnReqOut->ucMsgType);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.anTxnSN,sizeof(APIOut->stSTMC_t.anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),APIOut->stSTMC_t.anTxnAmt,sizeof(APIOut->stSTMC_t.anTxnAmt),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEV,sizeof(APIOut->stSTMC_t.anEV),' ',10);//n_EV
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->stSTMC_t.anProcessignCode);//Processing Code
	fnUnPack(&TxnReqOut->ucMsgType,sizeof(TxnReqOut->ucMsgType),APIOut->stSTMC_t.unMsgType);//Msg Type
	fnUnPack(&TxnReqOut->ucSubType,sizeof(TxnReqOut->ucSubType),APIOut->stSTMC_t.unSubType);//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stSTMC_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucSPID,sizeof(TxnReqOut->ucSPID),APIOut->stSTMC_t.unSPID);//SP ID
	fnUnPack(DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime),APIOut->stSTMC_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stSTMC_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stSTMC_t.unPersonalProfile);//Personal Profile
	fnUnPack(&TxnReqOut->ucLocationID,sizeof(TxnReqOut->ucLocationID),APIOut->stSTMC_t.unLocationID);//Location ID
	fnUnPack(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.unCardID);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stSTMC_t.unIssuerCode);//Issuer Code
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
	{
		fnUnPack(&TxnReqOut->ucBankCode_HostAdminKVN,1,APIOut->stSTMC_t.unBankCode);//Bank Code
		fnUnPack(TxnReqOut->ucCPD_SAMID,2,APIOut->stSTMC_t.unLoyaltyCounter);//Loyalty Counter
		fnUnPack(DongleOut->ucMAC_HCrypto,10,APIOut->stSTMC_t.unMAC);//MAC
	}
	else
	{
		memset(APIOut->stSTMC_t.unBankCode,0x30,sizeof(APIOut->stSTMC_t.unBankCode));//Bank Counter
		memset(APIOut->stSTMC_t.unLoyaltyCounter,0x30,sizeof(APIOut->stSTMC_t.unLoyaltyCounter));//Loyalty Counter
		memset(APIOut->stSTMC_t.unMAC,0x30,sizeof(APIOut->stSTMC_t.unMAC));//MAC
	}
	fnUnPack(TxnReqOut->ucExpiryDate,sizeof(TxnReqOut->ucExpiryDate),APIOut->stSTMC_t.unOrgExpiryDate);//Org Expiry Date
	//memset(APIOut->stSTMC_t.unOrgExpiryDate,0x30,sizeof(APIOut->stSTMC_t.unOrgExpiryDate));//Org Expiry Date
	memset(APIOut->stSTMC_t.unNewExpiryDate,0x30,sizeof(APIOut->stSTMC_t.unNewExpiryDate));//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stSTMC_t.unAreaCode);//Area Code
	fnUnPack(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),APIOut->stSTMC_t.unTxnAmt);//Txn Amt
	fnUnPack(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.unEV);//EV
	fnUnPack(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.unTxnSN);//Txn SN
	fnUnPack(TxnReqOut->ucCPUDeviceID,sizeof(TxnReqOut->ucCPUDeviceID),APIOut->stSTMC_t.unCPUDeviceID);//CPU Device ID
	fnUnPack(TxnReqOut->ucCPUSPID,sizeof(TxnReqOut->ucCPUSPID),APIOut->stSTMC_t.unCPUSPID);//CPU SP ID
	fnUnPack(TxnReqOut->ucCPULocationID,sizeof(TxnReqOut->ucCPULocationID),APIOut->stSTMC_t.unCPULocationID);//CPU Location ID
	fnUnPack(TxnReqOut->ucPID,sizeof(TxnReqOut->ucPID),APIOut->stSTMC_t.unPID);//Purse ID
	fnUnPack(TxnReqOut->ucCTC,sizeof(TxnReqOut->ucCTC),APIOut->stSTMC_t.unCTC);//CTC
	fnUnPack(TxnReqOut->ucProfileExpiryDate,sizeof(TxnReqOut->ucProfileExpiryDate),APIOut->stSTMC_t.unOrgProfileExpiryDate);//Org Profile Expiry Date
	//memset(APIOut->stSTMC_t.unOrgProfileExpiryDate,0x30,sizeof(APIOut->stSTMC_t.unOrgProfileExpiryDate));//Org Profile Expiry Date
	memset(APIOut->stSTMC_t.unNewProfileExpiryDate,0x30,sizeof(APIOut->stSTMC_t.unNewProfileExpiryDate));//New Profile Expiry Date
	fnUnPack(TxnReqOut->ucSubAreaCode,sizeof(TxnReqOut->ucSubAreaCode),APIOut->stSTMC_t.unSubAreaCode);//Sub Area Code
	fnUnPack(TxnReqOut->ucTxnSN,sizeof(TxnReqOut->ucTxnSN),APIOut->stSTMC_t.unTxnSNBeforeTxn);//Txn SN Before Txn
	fnUnPack(TxnReqOut->ucEV,sizeof(TxnReqOut->ucEV),APIOut->stSTMC_t.unEVBeforeTxn);//EV Before Txn
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stSTMC_t.unDeposit);//Deposit
	fnUnPack(&TxnReqOut->ucTxnMode,sizeof(TxnReqOut->ucTxnMode),APIOut->stSTMC_t.unTxnMode);//Txn Mode
	fnUnPack(&TxnReqOut->ucTxnQuqlifier,sizeof(TxnReqOut->ucTxnQuqlifier),APIOut->stSTMC_t.unTxnQuqlifier);//Txn Quqlifier
	fnUnPack(&TxnReqOut->ucSignatureKeyKVN,sizeof(TxnReqOut->ucSignatureKeyKVN),APIOut->stSTMC_t.unSignatureKeyKVN);//Signature Key KVN
	fnUnPack(DongleOut->ucSignature,sizeof(DongleOut->ucSignature),APIOut->stSTMC_t.unSignature);//Signature
	fnUnPack(DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),APIOut->stSTMC_t.unCPUSAMID);//SAM ID
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
	{
		fnUnPack(&DongleOut->ucMAC_HCrypto[0],1,APIOut->stSTMC_t.unHashType);//Hash Type
		fnUnPack(&DongleOut->ucMAC_HCrypto[1],1,APIOut->stSTMC_t.unHostAdminKVN);//Host Admin KVN
		fnUnPack(&DongleOut->ucMAC_HCrypto[2],16,APIOut->stSTMC_t.unCPUMAC);//MAC
	}
	else
	{
		memset(APIOut->stSTMC_t.unHashType,0x30,sizeof(APIOut->stSTMC_t.unHashType));
		memset(APIOut->stSTMC_t.unHostAdminKVN,0x30,sizeof(APIOut->stSTMC_t.unHostAdminKVN));
		memset(APIOut->stSTMC_t.unCPUMAC,0x30,sizeof(APIOut->stSTMC_t.unCPUMAC));//MAC
	}
	fnUnPack(&TxnReqOut->ucPurseVersionNumber,sizeof(TxnReqOut->ucPurseVersionNumber),APIOut->stSTMC_t.unPurseVersionNumber);//Purse Version Number
	fnUnPack(&TxnReqOut->ucCardIDLen,sizeof(TxnReqOut->ucCardIDLen),APIOut->stSTMC_t.unCardIDLen);//Card ID Len
	memcpy(APIOut->stSTMC_t.ucTMLocationID,stStore_DataInfo_t.ucTMLocationID,sizeof(stStore_DataInfo_t.ucTMLocationID));//TM Location ID
	memcpy(APIOut->stSTMC_t.ucTMID,stStore_DataInfo_t.ucTMID,sizeof(stStore_DataInfo_t.ucTMID));//TM ID
	fnLongToUnix(APIOut->stSTMC_t.ucTMTxnDateTime,(unsigned long *)DongleOut->ucTxnDateTime,14);//TM Txn Date Time
	memcpy(APIOut->stSTMC_t.ucTMSerialNumber,stStore_DataInfo_t.ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->stSTMC_t.ucTMAgentNumber,stStore_DataInfo_t.ucTMAgentNumber,sizeof(stStore_DataInfo_t.ucTMAgentNumber));//TM Agent Number
	//帳務資料結束,加值重送資料開始
	memcpy(APIOut->unVARMsgType,"0C",2);//VAR Msg Type
	fnUnPack(&TxnReqOut->stLastCreditTxnLogInfo_t.ucPurseVersionNumber_Index,sizeof(TxnReqOut->stLastCreditTxnLogInfo_t.ucPurseVersionNumber_Index),APIOut->unVARPurseVersionNumber);//VAR PurseVersion Number
	fnUnPack(TxnReqOut->stLastCreditTxnLogInfo_t.ucTxnSN,sizeof(TxnReqOut->stLastCreditTxnLogInfo_t.ucTxnSN),APIOut->unVARTxnSN);//VAR Txn SN
	fnUnPack(TxnReqOut->stLastCreditTxnLogInfo_t.ucTxnDateTime,sizeof(TxnReqOut->stLastCreditTxnLogInfo_t.ucTxnDateTime),APIOut->unVARTxnDateTime);//VAR Txn Date Time
	fnUnPack(&TxnReqOut->stLastCreditTxnLogInfo_t.ucSubType,sizeof(TxnReqOut->stLastCreditTxnLogInfo_t.ucSubType),APIOut->unVARSubType);//VAR Sub Type
	fnUnPack(TxnReqOut->stLastCreditTxnLogInfo_t.ucTxnAmt,sizeof(TxnReqOut->stLastCreditTxnLogInfo_t.ucTxnAmt),APIOut->unVARTxnAmt);//VAR Txn Amt
	fnUnPack(TxnReqOut->stLastCreditTxnLogInfo_t.ucEV,sizeof(TxnReqOut->stLastCreditTxnLogInfo_t.ucEV),APIOut->unVAREV);//VAR EV
	fnUnPack(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->unVARCardID);//VAR Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->unVARIssuerCode);//VAR Issuer Code
	fnUnPack(TxnReqOut->stLastCreditTxnLogInfo_t.ucCPUSPID,sizeof(TxnReqOut->stLastCreditTxnLogInfo_t.ucCPUSPID),APIOut->unVARCPUSPID);//VAR CPU SP ID
	fnUnPack(TxnReqOut->stLastCreditTxnLogInfo_t.ucCPULocationID,sizeof(TxnReqOut->stLastCreditTxnLogInfo_t.ucCPULocationID),APIOut->unVARCPULocationID);//VAR CPU Location ID
	fnUnPack(TxnReqOut->ucPID,sizeof(TxnReqOut->ucPID),APIOut->unVARPID);//VAR Purse ID
	fnUnPack(TxnReqOut->stLastCreditTxnLogInfo_t.ucCPUDeviceID,sizeof(TxnReqOut->stLastCreditTxnLogInfo_t.ucCPUDeviceID),APIOut->unVARCPUDeviceID);//VAR CPU Device ID
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		fnUnPack(TxnReqOut->ucCPD_SAMID,2,APIOut->unVARLoyaltyCounter);//VAR Loyalty Counter
	else
		memset(APIOut->unVARLoyaltyCounter,0x30,sizeof(APIOut->unVARLoyaltyCounter));//VAR Loyalty Counter
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->unVARPersonalProfile);//VAR Personal Profile
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		fnUnPack(&TxnReqOut->ucBankCode_HostAdminKVN,1,APIOut->unVARBankCode);//VAR Bank Code
	else
		memset(APIOut->unVARBankCode,0x30,sizeof(APIOut->unVARBankCode));//VAR Bank Counter
	fnUnPack(&TxnReqOut->ucCardIDLen,sizeof(TxnReqOut->ucCardIDLen),APIOut->unVARCardIDLen);//VAR Card ID Len
	//以上為加值當下資料
	//以下為重送當下資料
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->unVAR2DeviceID);//VAR Device ID
	fnUnPack(&TxnReqOut->ucSPID,sizeof(TxnReqOut->ucSPID),APIOut->unVAR2SPID);//VAR SP ID
	fnUnPack(&TxnReqOut->ucLocationID,sizeof(TxnReqOut->ucLocationID),APIOut->unVAR2LocationID);//VAR SP ID
	fnUnPack(TxnReqOut->ucCPUDeviceID,sizeof(TxnReqOut->ucCPUDeviceID),APIOut->unVAR2CPUDeviceID);//VAR CPU Device ID
	fnUnPack(TxnReqOut->ucCPUSPID,sizeof(TxnReqOut->ucCPUSPID),APIOut->unVAR2CPUSPID);//VAR CPU SP ID
	fnUnPack(TxnReqOut->ucCPULocationID,sizeof(TxnReqOut->ucCPULocationID),APIOut->unVAR2CPULocationID);//VAR CPU Location ID

	return(inTMOutLen);
}

int inBuildLockCardData1(int inTxnType,LockCard_TM_Out_2 *APIOut,LockCard_APDU_Out_2 *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason,BYTE *ucTMLocationID,BYTE *ucTMID)
{
int inTMOutLen;
BYTE bBLCName[50];

	inTMOutLen = sizeof(LockCard_TM_Out_2);
	memset(APIOut,0x00,inTMOutLen);
	fnUnPack(&DongleOut->ucPurseVersionNumber,sizeof(DongleOut->ucPurseVersionNumber),APIOut->unPurseVersionNumber);//Purse Version Number
	sprintf((char *)APIOut->unMsgType,"22");//Msg Type
	sprintf((char *)APIOut->unSubType,"00");//Sub Type
	fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->unDeviceID);//Device ID
	fnUnPack(&DongleOut->ucSPID,sizeof(DongleOut->ucSPID),APIOut->unSPID);//SP ID
	fnUnPack(ucTxnDateTime,sizeof(APIOut->unTxnDateTime) / 2,APIOut->unTxnDateTime);//Txn Date Time
	fnUnPack(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->unCardID);//Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->unIssuerCode);//Issuer Code
	fnUnPack(&DongleOut->ucLocationID,sizeof(DongleOut->ucLocationID),APIOut->unLocationID);//Location ID
	fnUnPack(&DongleOut->ucCardIDLen,sizeof(DongleOut->ucCardIDLen),APIOut->unCardIDLen);//Card ID Len
	fnUnPack(DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),APIOut->unCPUDeviceID);//CPU Device ID
	fnUnPack(DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),APIOut->unCPUSPID);//CPU SP ID
	fnUnPack(DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID),APIOut->unCPULocationID);//CPU Location ID
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->unCardType);//Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->unPersonalProfile);//Personal Profile
	fnUnPack(DongleOut->ucPID,sizeof(DongleOut->ucPID),APIOut->unPID);//CPU Purse ID
	fnUnPack(DongleOut->ucCTC,sizeof(DongleOut->ucCTC),APIOut->unCTC);//CTC
	fnUnPack(&ucLockReason,sizeof(ucLockReason),APIOut->unLockReason);//Lock Reason
	if(ucLockReason == 0x01)
	{
		memset(bBLCName,0x00,sizeof(bBLCName));
		sprintf((char *)bBLCName,"%s.BIG",gsBlackListVersion);
		vdPad(bBLCName,APIOut->unBLCFileName,sizeof(APIOut->unBLCFileName),TRUE,0x20);//BLC File Name
		//vdPad(gsBlackListVersion,APIOut->unBLCFileName,sizeof(APIOut->unBLCFileName),TRUE,0x20);//BLC File Name
		APIOut->unBLCIDFlag = gsBlackListVersion[20];//BLC ID Flag
		if(APIOut->unBLCIDFlag == 0x00)
			APIOut->unBLCIDFlag = 0x20;
	}
	else
	{
		memset(APIOut->unBLCFileName,0x20,sizeof(APIOut->unBLCFileName));//BLC File Name
		APIOut->unBLCIDFlag = 0x20;//BLC ID Flag
	}
	memcpy(APIOut->unTMLocationID,ucTMLocationID,sizeof(APIOut->unTMLocationID));//TM Location ID
	memcpy(APIOut->unTMID,ucTMID,sizeof(APIOut->unTMID));//TM ID
	memset(APIOut->unRFU,0x20,sizeof(APIOut->unRFU));//RFU
	memset(APIOut->unEV,0x30,sizeof(APIOut->unEV));//EV
	memset(APIOut->unCPUEV,0x30,sizeof(APIOut->unCPUEV));//CPU EV
	memset(APIOut->unMSettingPar,0x30,sizeof(APIOut->unMSettingPar));//M SettingPar
	memset(APIOut->unCSettingPar,0x30,sizeof(APIOut->unCSettingPar));//C SettingPar
	memset(APIOut->unTxnSN,0x30,sizeof(APIOut->unTxnSN));//Txn SN
	memset(APIOut->unVARTxnSN,0x30,sizeof(APIOut->unVARTxnSN));//VAR Txn SN
	memset(APIOut->unVARTxnDateTime,0x30,sizeof(APIOut->unVARTxnDateTime));//VAR Txn Date Time
	memset(APIOut->unVARSubType,0x30,sizeof(APIOut->unVARSubType));//VAR Sub Type
	memset(APIOut->unVARTxnAmt,0x30,sizeof(APIOut->unVARTxnAmt));//VAR Txn Amt
	memset(APIOut->unVAREV,0x30,sizeof(APIOut->unVAREV));//VAR EV
	memset(APIOut->unVARDeviceID,0x30,sizeof(APIOut->unVARDeviceID));//VAR Device ID

	return(inTMOutLen);
}

int inBuildLockCardData2(int inTxnType,LockCard_TM_Out_2 *APIOut,LockCard_APDU_Out_3 *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason,BYTE *ucTMLocationID,BYTE *ucTMID)
{
int inTMOutLen;
BYTE bSpace[20];

	inTMOutLen = sizeof(LockCard_TM_Out_2);
	memset(APIOut,0x00,inTMOutLen);
	memset(bSpace,0x20,sizeof(bSpace));
	fnUnPack(&DongleOut->ucPurseVersionNumber,sizeof(DongleOut->ucPurseVersionNumber),APIOut->unPurseVersionNumber);//Purse Version Number
	sprintf((char *)APIOut->unMsgType,"22");//Msg Type
	sprintf((char *)APIOut->unSubType,"00");//Sub Type
	fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->unDeviceID);//Device ID
	fnUnPack(&DongleOut->ucSPID,sizeof(DongleOut->ucSPID),APIOut->unSPID);//SP ID
	fnUnPack(ucTxnDateTime,sizeof(APIOut->unTxnDateTime) / 2,APIOut->unTxnDateTime);//Txn Date Time
	fnUnPack(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->unCardID);//Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->unIssuerCode);//Issuer Code
	fnUnPack(&DongleOut->ucLocationID,sizeof(DongleOut->ucLocationID),APIOut->unLocationID);//Location ID
	fnUnPack(&DongleOut->ucCardIDLen,sizeof(DongleOut->ucCardIDLen),APIOut->unCardIDLen);//Card ID Len
	fnUnPack(DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),APIOut->unCPUDeviceID);//CPU Device ID
	fnUnPack(DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),APIOut->unCPUSPID);//CPU SP ID
	fnUnPack(DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID),APIOut->unCPULocationID);//CPU Location ID
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->unCardType);//Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->unPersonalProfile);//Personal Profile
	fnUnPack(DongleOut->ucPID,sizeof(DongleOut->ucPID),APIOut->unPID);//CPU Purse ID
	memset(APIOut->unCTC,0x30,sizeof(APIOut->unCTC));//CTC
	//fnUnPack(DongleOut->ucCTC,sizeof(DongleOut->ucCTC),APIOut->unCTC);//CTC
	fnUnPack(&ucLockReason,sizeof(ucLockReason),APIOut->unLockReason);//Lock Reason
	memset(APIOut->unBLCFileName,0x20,sizeof(APIOut->unBLCFileName));//BLC File Name
	APIOut->unBLCIDFlag = 0x20;//BLC ID Flag
	memcpy(APIOut->unTMLocationID,ucTMLocationID,sizeof(APIOut->unTMLocationID));//TM Location ID
	memcpy(APIOut->unTMID,ucTMID,sizeof(APIOut->unTMID));//TM ID
	memset(APIOut->unRFU,0x20,sizeof(APIOut->unRFU));//RFU

	fnUnPack(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->unEV);//EV
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

	return(inTMOutLen);
}

int inBuildLockCardData3(int inTxnType,LockCard_TM_Out_2 *APIOut,TxnReqOffline_APDU_Out *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason,BYTE *ucTMLocationID,BYTE *ucTMID)
{
#if 0
int inTMOutLen;
BYTE bSpace[20];

	inTMOutLen = sizeof(LockCard_TM_Out_2);
	memset(APIOut,0x00,inTMOutLen);
	memset(bSpace,0x20,sizeof(bSpace));
	fnUnPack(&DongleOut->ucPurseVersionNumber,sizeof(DongleOut->ucPurseVersionNumber),APIOut->unPurseVersionNumber);//Purse Version Number
	sprintf((char *)APIOut->unMsgType,"22");//Msg Type
	sprintf((char *)APIOut->unSubType,"00");//Sub Type
	fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->unDeviceID);//Device ID
	fnUnPack(&DongleOut->ucSPID,sizeof(DongleOut->ucSPID),APIOut->unSPID);//SP ID
	fnUnPack(ucTxnDateTime,sizeof(APIOut->unTxnDateTime) / 2,APIOut->unTxnDateTime);//Txn Date Time
	fnUnPack(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->unCardID);//Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->unIssuerCode);//Issuer Code
	fnUnPack(&DongleOut->ucLocationID,sizeof(DongleOut->ucLocationID),APIOut->unLocationID);//Location ID
	fnUnPack(&DongleOut->ucCardIDLen,sizeof(DongleOut->ucCardIDLen),APIOut->unCardIDLen);//Card ID Len
	fnUnPack(DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),APIOut->unCPUDeviceID);//CPU Device ID
	fnUnPack(DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),APIOut->unCPUSPID);//CPU SP ID
	fnUnPack(DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID),APIOut->unCPULocationID);//CPU Location ID
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->unCardType);//Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->unPersonalProfile);//Personal Profile
	fnUnPack(DongleOut->ucPID,sizeof(DongleOut->ucPID),APIOut->unPID);//CPU Purse ID
	fnUnPack(DongleOut->ucCTC,sizeof(DongleOut->ucCTC),APIOut->unCTC);//CTC
	fnUnPack(&ucLockReason,sizeof(ucLockReason),APIOut->unLockReason);//Lock Reason
	memset(APIOut->unBLCFileName,0x20,sizeof(APIOut->unBLCFileName));//BLC File Name
	APIOut->unBLCIDFlag = 0x20;//BLC ID Flag
	memcpy(APIOut->unTMLocationID,ucTMLocationID,sizeof(APIOut->unTMLocationID));//TM Location ID
	memcpy(APIOut->unTMID,ucTMID,sizeof(APIOut->unTMID));//TM ID
	memset(APIOut->unRFU,0x20,sizeof(APIOut->unRFU));//RFU

	return(inTMOutLen);
#else
	return(0);
#endif
}

int inBuildLockCardData4(int inTxnType,LockCard_TM_Out_1 *APIOut,TxRefund_APDU_Out *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason)
{
int inTMOutLen;
BYTE bSpace[20];

	inTMOutLen = sizeof(LockCard_TM_Out_1);
	memset(APIOut,0x00,inTMOutLen);
	memset(bSpace,0x20,sizeof(bSpace));
	sprintf((char *)APIOut->unMsgType,"22");//Msg Type
	sprintf((char *)APIOut->unSubType,"00");//Sub Type
	fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->unDeviceID);//Device ID
	fnUnPack(&DongleOut->ucDeviceID[2],sizeof(APIOut->unSPID) / 2,APIOut->unSPID);//SP ID
	fnUnPack(ucTxnDateTime,sizeof(APIOut->unTxnDateTime) / 2,APIOut->unTxnDateTime);//Txn Date Time
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->unCardType);//Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->unPersonalProfile);//Personal Profile
	fnUnPack(DongleOut->ucCardID_4,sizeof(DongleOut->ucCardID_4),APIOut->unCardID_8);//Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->unIssuerCode);//Issuer Code
	memcpy(APIOut->unLocationID,LOCATION_ID_BATCH,2);//Location ID
	fnUnPack(&ucLockReason,sizeof(ucLockReason),APIOut->unLockReason);//Lock Reason

	return(inTMOutLen);
}

int inBuildLockCardData5(int inTxnType,LockCard_TM_Out_1 *APIOut,AddValue_APDU_Out *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason)
{
int inTMOutLen;
BYTE bSpace[20];

	inTMOutLen = sizeof(LockCard_TM_Out_1);
	memset(APIOut,0x00,inTMOutLen);
	memset(bSpace,0x20,sizeof(bSpace));
	sprintf((char *)APIOut->unMsgType,"22");//Msg Type
	sprintf((char *)APIOut->unSubType,"00");//Sub Type
	fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->unDeviceID);//Device ID
	fnUnPack(&DongleOut->ucDeviceID[2],sizeof(APIOut->unSPID) / 2,APIOut->unSPID);//SP ID
	fnUnPack(ucTxnDateTime,sizeof(APIOut->unTxnDateTime) / 2,APIOut->unTxnDateTime);//Txn Date Time
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->unCardType);//Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->unPersonalProfile);//Personal Profile
	fnUnPack(DongleOut->ucCardID_4,sizeof(DongleOut->ucCardID_4),APIOut->unCardID_8);//Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->unIssuerCode);//Issuer Code
	memcpy(APIOut->unLocationID,LOCATION_ID_BATCH,2);//Location ID
	fnUnPack(&ucLockReason,sizeof(ucLockReason),APIOut->unLockReason);//Lock Reason

	return(inTMOutLen);
}

int inBuildLockCardData6(int inTxnType,LockCard_TM_Out_1 *APIOut,LockCard_APDU_Out_1 *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason)
{
int inTMOutLen;
BYTE bSpace[20];

	inTMOutLen = sizeof(LockCard_TM_Out_1);
	memset(APIOut,0x00,inTMOutLen);
	memset(bSpace,0x20,sizeof(bSpace));
	sprintf((char *)APIOut->unMsgType,"22");//Msg Type
	sprintf((char *)APIOut->unSubType,"00");//Sub Type
	fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->unDeviceID);//Device ID
	fnUnPack(&DongleOut->ucDeviceID[2],sizeof(APIOut->unSPID) / 2,APIOut->unSPID);//SP ID
	fnUnPack(ucTxnDateTime,sizeof(APIOut->unTxnDateTime) / 2,APIOut->unTxnDateTime);//Txn Date Time
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->unCardType);//Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->unPersonalProfile);//Personal Profile
	fnUnPack(DongleOut->ucCardID_4,sizeof(DongleOut->ucCardID_4),APIOut->unCardID_8);//Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->unIssuerCode);//Issuer Code
	memcpy(APIOut->unLocationID,LOCATION_ID_BATCH,2);//Location ID
	fnUnPack(&ucLockReason,sizeof(ucLockReason),APIOut->unLockReason);//Lock Reason

	return(inTMOutLen);
}

int inBuildReadDongleDeductData(int inTxnType,ReadDongleDeduct_TM_Out *APIOut,ReadDongleDeduct_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(ReadDongleDeduct_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->stSTMC_t.anCardID,sizeof(APIOut->stSTMC_t.anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(DongleOut->ucDeviceID,APIOut->stSTMC_t.anDeviceID,sizeof(APIOut->stSTMC_t.anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(DongleOut->ucCPUDeviceID,APIOut->stSTMC_t.anCPUDeviceID,sizeof(APIOut->stSTMC_t.anCPUDeviceID),LEVEL2);//n_TXN CPU Device ID
	vdCountEVBefore(DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEVBeforeTxn,sizeof(APIOut->stSTMC_t.anEVBeforeTxn),DongleOut->ucMsgType);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.anTxnSN,sizeof(APIOut->stSTMC_t.anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),APIOut->stSTMC_t.anTxnAmt,sizeof(APIOut->stSTMC_t.anTxnAmt),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEV,sizeof(APIOut->stSTMC_t.anEV),' ',10);//n_EV
	vdBuildProcessingCode(Status_AUTHTXNOFFLINE,DongleOut->ucMsgType,DongleOut->ucSubType,DongleOut->ucPersonalProfile,APIOut->stSTMC_t.anProcessignCode);//Processing Code
	fnUnPack(&DongleOut->ucMsgType,sizeof(DongleOut->ucMsgType),APIOut->stSTMC_t.unMsgType);//Msg Type
	fnUnPack(&DongleOut->ucSubType,sizeof(DongleOut->ucSubType),APIOut->stSTMC_t.unSubType);//Sub Type
	fnUnPack(DongleOut->ucDeviceID,sizeof((char *)DongleOut->ucDeviceID),APIOut->stSTMC_t.unDeviceID);//Device ID
	fnUnPack(&DongleOut->ucSPID,sizeof(DongleOut->ucSPID),APIOut->stSTMC_t.unSPID);//SP ID
	fnUnPack(DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime),APIOut->stSTMC_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->stSTMC_t.unCardType);//Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->stSTMC_t.unPersonalProfile);//Personal Profile
	fnUnPack(&DongleOut->ucLocationID,sizeof(DongleOut->ucLocationID),APIOut->stSTMC_t.unLocationID);//Location ID
	fnUnPack(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->stSTMC_t.unCardID);//CPU Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->stSTMC_t.unIssuerCode);//Issuer Code
	if(DongleOut->ucPurseVersionNumber == MIFARE)
	{
		fnUnPack(&DongleOut->ucBankCode,1,APIOut->stSTMC_t.unBankCode);//Bank Code
		fnUnPack(DongleOut->ucLoyaltyCounter,2,APIOut->stSTMC_t.unLoyaltyCounter);//Loyalty Counter
		fnUnPack(DongleOut->ucMAC_HCrypto,10,APIOut->stSTMC_t.unMAC);//MAC
	}
	else
	{
		memset(APIOut->stSTMC_t.unBankCode,0x30,sizeof(APIOut->stSTMC_t.unBankCode));//Bank Counter
		memset(APIOut->stSTMC_t.unLoyaltyCounter,0x30,sizeof(APIOut->stSTMC_t.unLoyaltyCounter));//Loyalty Counter
		memset(APIOut->stSTMC_t.unMAC,0x30,sizeof(APIOut->stSTMC_t.unMAC));//MAC
	}
	memset(APIOut->stSTMC_t.unOrgExpiryDate,0x30,sizeof(APIOut->stSTMC_t.unOrgExpiryDate));//Org Expiry Date
	memset(APIOut->stSTMC_t.unNewExpiryDate,0x30,sizeof(APIOut->stSTMC_t.unNewExpiryDate));//New Expiry Date
	fnUnPack(&DongleOut->ucAreaCode,sizeof(DongleOut->ucAreaCode),APIOut->stSTMC_t.unAreaCode);//Area Code
	fnUnPack(DongleOut->ucTxnAmt,sizeof(DongleOut->ucTxnAmt),APIOut->stSTMC_t.unTxnAmt);//Txn Amt
	fnUnPack(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.unEV);//EV
	fnUnPack(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.unTxnSN);//Txn SN
	fnUnPack(DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),APIOut->stSTMC_t.unCPUDeviceID);//CPU Device ID
	fnUnPack(DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),APIOut->stSTMC_t.unCPUSPID);//CPU SP ID
	fnUnPack(DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID),APIOut->stSTMC_t.unCPULocationID);//CPU Location ID
	fnUnPack(DongleOut->ucPID,sizeof(DongleOut->ucPID),APIOut->stSTMC_t.unPID);//Purse ID
	fnUnPack(DongleOut->ucCTC,sizeof(DongleOut->ucCTC),APIOut->stSTMC_t.unCTC);//CTC
	memset(APIOut->stSTMC_t.unOrgProfileExpiryDate,0x30,sizeof(APIOut->stSTMC_t.unOrgProfileExpiryDate));//Org Profile Expiry Date
	memset(APIOut->stSTMC_t.unNewProfileExpiryDate,0x30,sizeof(APIOut->stSTMC_t.unNewProfileExpiryDate));//New Profile Expiry Date
	fnUnPack(DongleOut->ucSubAreaCode,sizeof(DongleOut->ucSubAreaCode),APIOut->stSTMC_t.unSubAreaCode);//Sub Area Code
	fnUnPack(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.unTxnSNBeforeTxn);//Txn SN Before Txn
	fnUnPack(DongleOut->ucEVBeforeTxn,sizeof(DongleOut->ucEVBeforeTxn),APIOut->stSTMC_t.unEVBeforeTxn);//EV Before Txn
	fnUnPack(DongleOut->ucDeposit,sizeof(DongleOut->ucDeposit),APIOut->stSTMC_t.unDeposit);//Deposit
	fnUnPack(&DongleOut->ucTxnMode,sizeof(DongleOut->ucTxnMode),APIOut->stSTMC_t.unTxnMode);//Txn Mode
	fnUnPack(&DongleOut->ucTxnQuqlifier,sizeof(DongleOut->ucTxnQuqlifier),APIOut->stSTMC_t.unTxnQuqlifier);//Txn Quqlifier
	fnUnPack(&DongleOut->ucSignatureKeyKVN,sizeof(DongleOut->ucSignatureKeyKVN),APIOut->stSTMC_t.unSignatureKeyKVN);//Signature Key KVN
	fnUnPack(DongleOut->ucSignature,sizeof(DongleOut->ucSignature),APIOut->stSTMC_t.unSignature);//Signature
	fnUnPack(DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),APIOut->stSTMC_t.unCPUSAMID);//SAM ID
	if(DongleOut->ucPurseVersionNumber != MIFARE)
	{
		fnUnPack(&DongleOut->ucMAC_HCrypto[0],1,APIOut->stSTMC_t.unHashType);//Hash Type
		fnUnPack(&DongleOut->ucMAC_HCrypto[1],1,APIOut->stSTMC_t.unHostAdminKVN);//Host Admin KVN
		fnUnPack(&DongleOut->ucMAC_HCrypto[2],16,APIOut->stSTMC_t.unCPUMAC);//MAC
	}
	else
	{
		memset(APIOut->stSTMC_t.unHashType,0x30,sizeof(APIOut->stSTMC_t.unHashType));
		memset(APIOut->stSTMC_t.unHostAdminKVN,0x30,sizeof(APIOut->stSTMC_t.unHostAdminKVN));
		memset(APIOut->stSTMC_t.unCPUMAC,0x30,sizeof(APIOut->stSTMC_t.unCPUMAC));//MAC
	}
	fnUnPack(&DongleOut->ucPurseVersionNumber,sizeof(DongleOut->ucPurseVersionNumber),APIOut->stSTMC_t.unPurseVersionNumber);//Purse Version Number
	fnUnPack(&DongleOut->ucCardIDLen,sizeof(DongleOut->ucCardIDLen),APIOut->stSTMC_t.unCardIDLen);//Card ID Len
	memcpy(APIOut->stSTMC_t.ucTMLocationID,DongleOut->ucTMLocationID,sizeof(DongleOut->ucTMLocationID));//TM Location ID
	memcpy(APIOut->stSTMC_t.ucTMID,DongleOut->ucTMID,sizeof(DongleOut->ucTMID));//TM ID
	fnLongToUnix(APIOut->stSTMC_t.ucTMTxnDateTime,(unsigned long *)DongleOut->ucTxnDateTime,14);//TM Txn Date Time
	memcpy(APIOut->stSTMC_t.ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(DongleOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->stSTMC_t.ucTMAgentNumber,DongleOut->ucTMAgentNumber,sizeof(DongleOut->ucTMAgentNumber));//TM Agent Number
	//帳務資料結束,加值重送資料開始
	memcpy(APIOut->unVARMsgType,"0C",2);//VAR Msg Type
	fnUnPack(&DongleOut->stLastCreditTxnLogInfo_t.ucPurseVersionNumber_Index,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucPurseVersionNumber_Index),APIOut->unVARPurseVersionNumber);//VAR PurseVersion Number
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucTxnSN,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucTxnSN),APIOut->unVARTxnSN);//VAR Txn SN
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucTxnDateTime,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucTxnDateTime),APIOut->unVARTxnDateTime);//VAR Txn Date Time
	fnUnPack(&DongleOut->stLastCreditTxnLogInfo_t.ucSubType,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucSubType),APIOut->unVARSubType);//VAR Sub Type
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucTxnAmt,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucTxnAmt),APIOut->unVARTxnAmt);//VAR Txn Amt
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucEV,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucEV),APIOut->unVAREV);//VAR EV
	fnUnPack(DongleOut->ucCardID,sizeof(DongleOut->ucCardID),APIOut->unVARCardID);//VAR Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->unVARIssuerCode);//VAR Issuer Code
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucCPUSPID,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucCPUSPID),APIOut->unVARCPUSPID);//VAR CPU SP ID
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucCPULocationID,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucCPULocationID),APIOut->unVARCPULocationID);//VAR CPU Location ID
	fnUnPack(DongleOut->ucPID,sizeof(DongleOut->ucPID),APIOut->unVARPID);//VAR Purse ID
	fnUnPack(DongleOut->stLastCreditTxnLogInfo_t.ucCPUDeviceID,sizeof(DongleOut->stLastCreditTxnLogInfo_t.ucCPUDeviceID),APIOut->unVARCPUDeviceID);//VAR CPU Device ID
	if(DongleOut->ucPurseVersionNumber == MIFARE)
		fnUnPack(DongleOut->ucLoyaltyCounter,2,APIOut->unVARLoyaltyCounter);//VAR Loyalty Counter
	else
		memset(APIOut->unVARLoyaltyCounter,0x30,sizeof(APIOut->unVARLoyaltyCounter));//VAR Loyalty Counter
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->unVARPersonalProfile);//VAR Personal Profile
	if(DongleOut->ucPurseVersionNumber == MIFARE)
		fnUnPack(&DongleOut->ucBankCode,1,APIOut->unVARBankCode);//VAR Bank Code
	else
		memset(APIOut->unVARBankCode,0x30,sizeof(APIOut->unVARBankCode));//VAR Bank Counter
	fnUnPack(&DongleOut->ucCardIDLen,sizeof(DongleOut->ucCardIDLen),APIOut->unVARCardIDLen);//VAR Card ID Len

	fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->unVAR2DeviceID);//VAR Device ID
	fnUnPack(&DongleOut->ucSPID,sizeof(DongleOut->ucSPID),APIOut->unVAR2SPID);//VAR SP ID
	fnUnPack(&DongleOut->ucLocationID,sizeof(DongleOut->ucLocationID),APIOut->unVAR2LocationID);//VAR SP ID
	fnUnPack(DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID),APIOut->unVAR2CPUDeviceID);//VAR CPU Device ID
	fnUnPack(DongleOut->ucCPUSPID,sizeof(DongleOut->ucCPUSPID),APIOut->unVAR2CPUSPID);//VAR CPU SP ID
	fnUnPack(DongleOut->ucCPULocationID,sizeof(DongleOut->ucCPULocationID),APIOut->unVAR2CPULocationID);//VAR CPU Location ID

	return(inTMOutLen);
}

int inBuildAuthCardSaleData(int inTxnType,AuthCardSale_TM_Out *APIOut,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthCardSale_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.anCardID,sizeof(APIOut->stSTMC_t.anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stSTMC_t.anDeviceID,sizeof(APIOut->stSTMC_t.anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(TxnReqOut->ucCPUDeviceID,APIOut->stSTMC_t.anCPUDeviceID,sizeof(APIOut->stSTMC_t.anCPUDeviceID),LEVEL2);//n_TXN Device ID
	vdIntToAsc(TxnReqOut->ucEV,sizeof(TxnReqOut->ucEV),APIOut->stSTMC_t.anEVBeforeTxn,sizeof(APIOut->stSTMC_t.anEVBeforeTxn),' ',10);//n_TXN SNum
	//vdCountEVBefore(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEVBeforeTxn,sizeof(APIOut->stSTMC_t.anEVBeforeTxn),TxnReqOut->ucMsgType);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.anTxnSN,sizeof(APIOut->stSTMC_t.anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stSTMC_t.anTxnAmt,sizeof(APIOut->stSTMC_t.anTxnAmt),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEV,sizeof(APIOut->stSTMC_t.anEV),' ',10);//n_EV
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->stSTMC_t.anProcessignCode);//Processing Code
	fnUnPack(&TxnReqOut->ucMsgType,sizeof(TxnReqOut->ucMsgType),APIOut->stSTMC_t.unMsgType);//Msg Type
	fnUnPack(&TxnReqOut->ucSubType,sizeof(TxnReqOut->ucSubType),APIOut->stSTMC_t.unSubType);//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stSTMC_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucSPID,sizeof(TxnReqOut->ucSPID),APIOut->stSTMC_t.unSPID);//SP ID
	fnUnPack(DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime),APIOut->stSTMC_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stSTMC_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stSTMC_t.unPersonalProfile);//Personal Profile
	fnUnPack(&TxnReqOut->ucLocationID,sizeof(TxnReqOut->ucLocationID),APIOut->stSTMC_t.unLocationID);//Location ID
	fnUnPack(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.unCardID);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stSTMC_t.unIssuerCode);//Issuer Code
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->stSTMC_t.unBankCode);//Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->stSTMC_t.unLoyaltyCounter);//Loyalty Counter
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		fnUnPack(DongleOut->ucMAC_HCrypto,10,APIOut->stSTMC_t.unMAC);//MAC
	else
		memset(APIOut->stSTMC_t.unMAC,0x30,sizeof(APIOut->stSTMC_t.unMAC));//MAC
	fnUnPack(TxnReqOut->ucExpiryDate,sizeof(TxnReqOut->ucExpiryDate),APIOut->stSTMC_t.unOrgExpiryDate);//Org Expiry Date
	fnUnPack(DongleIn->ucExpiryDate,sizeof(DongleIn->ucExpiryDate),APIOut->stSTMC_t.unNewExpiryDate);//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stSTMC_t.unAreaCode);//Area Code
	fnUnPack(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),APIOut->stSTMC_t.unTxnAmt);//Txn Amt
	fnUnPack(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.unEV);//EV
	fnUnPack(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.unTxnSN);//Txn SN
	fnUnPack(TxnReqOut->ucCPUDeviceID,sizeof(TxnReqOut->ucCPUDeviceID),APIOut->stSTMC_t.unCPUDeviceID);//CPU Device ID
	fnUnPack(TxnReqOut->ucCPUSPID,sizeof(TxnReqOut->ucCPUSPID),APIOut->stSTMC_t.unCPUSPID);//CPU SP ID
	fnUnPack(TxnReqOut->ucCPULocationID,sizeof(TxnReqOut->ucCPULocationID),APIOut->stSTMC_t.unCPULocationID);//CPU Location ID
	fnUnPack(TxnReqOut->ucPID,sizeof(TxnReqOut->ucPID),APIOut->stSTMC_t.unPID);//Purse ID
	fnUnPack(TxnReqOut->ucCTC,sizeof(TxnReqOut->ucCTC),APIOut->stSTMC_t.unCTC);//CTC
	fnUnPack(TxnReqOut->ucProfileExpiryDate,sizeof(TxnReqOut->ucProfileExpiryDate),APIOut->stSTMC_t.unOrgProfileExpiryDate);//Org Profile Expiry Date
	fnUnPack(DongleIn->ucProfileExpiryDate,sizeof(DongleIn->ucProfileExpiryDate),APIOut->stSTMC_t.unNewProfileExpiryDate);//New Profile Expiry Date
	fnUnPack(TxnReqOut->ucSubAreaCode,sizeof(TxnReqOut->ucSubAreaCode),APIOut->stSTMC_t.unSubAreaCode);//Sub Area Code
	fnUnPack(TxnReqOut->ucTxnSN,sizeof(TxnReqOut->ucTxnSN),APIOut->stSTMC_t.unTxnSNBeforeTxn);//Txn SN Before Txn
	fnUnPack(TxnReqOut->ucEV,sizeof(TxnReqOut->ucEV),APIOut->stSTMC_t.unEVBeforeTxn);//EV Before Txn
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stSTMC_t.unDeposit);//Deposit
	fnUnPack(&TxnReqOut->ucTxnMode,sizeof(TxnReqOut->ucTxnMode),APIOut->stSTMC_t.unTxnMode);//Txn Mode
	fnUnPack(&TxnReqOut->ucTxnQuqlifier,sizeof(TxnReqOut->ucTxnQuqlifier),APIOut->stSTMC_t.unTxnQuqlifier);//Txn Quqlifier
	fnUnPack(&TxnReqOut->ucSignatureKeyKVN,sizeof(TxnReqOut->ucSignatureKeyKVN),APIOut->stSTMC_t.unSignatureKeyKVN);//Signature Key KVN
	fnUnPack(DongleOut->ucSignature,sizeof(DongleOut->ucSignature),APIOut->stSTMC_t.unSignature);//Signature
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
		fnUnPack(&DongleOut->ucMAC_HCrypto[0],1,APIOut->stSTMC_t.unHashType);//Hash Type
	else
		memset(APIOut->stSTMC_t.unHashType,0x30,sizeof(APIOut->stSTMC_t.unHashType));
	fnUnPack(DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),APIOut->stSTMC_t.unCPUSAMID);//SAM ID
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
	{
		fnUnPack(&DongleOut->ucMAC_HCrypto[1],1,APIOut->stSTMC_t.unHostAdminKVN);//Host Admin KVN
		fnUnPack(&DongleOut->ucMAC_HCrypto[2],16,APIOut->stSTMC_t.unCPUMAC);//MAC
	}
	else
	{
		memset(APIOut->stSTMC_t.unHostAdminKVN,0x30,sizeof(APIOut->stSTMC_t.unHostAdminKVN));
		memset(APIOut->stSTMC_t.unCPUMAC,0x30,sizeof(APIOut->stSTMC_t.unCPUMAC));//MAC
	}
	fnUnPack(&TxnReqOut->ucPurseVersionNumber,sizeof(TxnReqOut->ucPurseVersionNumber),APIOut->stSTMC_t.unPurseVersionNumber);//Purse Version Number
	fnUnPack(&TxnReqOut->ucCardIDLen,sizeof(TxnReqOut->ucCardIDLen),APIOut->stSTMC_t.unCardIDLen);//Card ID Len
	memcpy(APIOut->stSTMC_t.ucTMLocationID,stStore_DataInfo_t.ucTMLocationID,sizeof(stStore_DataInfo_t.ucTMLocationID));//TM Location ID
	memcpy(APIOut->stSTMC_t.ucTMID,stStore_DataInfo_t.ucTMID,sizeof(stStore_DataInfo_t.ucTMID));//TM ID
	fnLongToUnix(APIOut->stSTMC_t.ucTMTxnDateTime,(unsigned long *)DongleOut->ucTxnDateTime,14);//TM Txn Date Time
	memcpy(APIOut->stSTMC_t.ucTMSerialNumber,stStore_DataInfo_t.ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->stSTMC_t.ucTMAgentNumber,stStore_DataInfo_t.ucTMAgentNumber,sizeof(stStore_DataInfo_t.ucTMAgentNumber));//TM Agent Number
	//帳務資料結束
	//Congirm資料開始
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",81);//Data Len
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	APIOut->ucMsgType = TxnReqOut->ucMsgType;//Msg Type
	APIOut->ucSubType = TxnReqOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,TxnReqOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	memcpy(APIOut->ucTxnDateTime,DongleOut->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->ucMAC,DongleOut->ucMAC_HCrypto,sizeof(APIOut->ucMAC));//MAC
	else
		memset(APIOut->ucMAC,0x00,sizeof(APIOut->ucMAC));//MAC
	memcpy(APIOut->ucConfirmCode,DongleOut->ucConfirmCode,sizeof(APIOut->ucConfirmCode));//Confirm Code
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->ucCTAC,&DongleOut->ucMAC_HCrypto[10],sizeof(APIOut->ucMAC));//CTAC
	else
		memset(APIOut->ucCTAC,0x00,sizeof(APIOut->ucMAC));//CTAC
	memcpy(APIOut->ucCardID,TxnReqOut->ucCardID,sizeof(APIOut->ucCardID));//Card ID
	memcpy(APIOut->ucEV,DongleOut->ucEV,sizeof(APIOut->ucEV));//EV
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN,sizeof(APIOut->ucTxnSN));//Txn SN
	memcpy(APIOut->ucCPUDeviceID,TxnReqOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucPID,TxnReqOut->ucPID,sizeof(APIOut->ucPID));//Purse ID
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
	{
		APIOut->ucHashType = DongleOut->ucMAC_HCrypto[0];//Hash Type
		APIOut->ucHostAdminKVN = DongleOut->ucMAC_HCrypto[1];//Host Admin KVN
		memcpy(APIOut->ucCPUMAC,&DongleOut->ucMAC_HCrypto[2],sizeof(APIOut->ucCPUMAC));//CPU MAC
	}
	else
	{
		APIOut->ucHashType = 0x00;
		APIOut->ucHostAdminKVN = 0x00;
		memset(APIOut->ucCPUMAC,0x00,sizeof(APIOut->ucCPUMAC));//CPU MAC
	}

	return(inTMOutLen);
}

int inBuildSetValueData(int inTxnType,SetValue_TM_Out *APIOut,SetValue_APDU_In *DongleIn,SetValue_APDU_Out *DongleOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(SetValue_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	memcpy(APIOut->ucCommandCode,"05",sizeof(APIOut->ucCommandCode));//Command Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List Version
	APIOut->ucMsgType = DongleIn->ucMsgType;//Msg Type
	APIOut->ucSubType = 0x00;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucDeviceID[2];//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	memcpy(APIOut->ucCardID_4,DongleOut->ucCardID_4,sizeof(APIOut->ucCardID_4));//Card ID 4
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
	memset(APIOut->ucTxnAmt_2,0x00,sizeof(APIOut->ucTxnAmt_2));//Txn Amt 2
	memcpy(APIOut->ucExpiryDate,DongleOut->ucExpiryDate,sizeof(APIOut->ucExpiryDate));//Expiry Date
	APIOut->ucAreaCode = DongleOut->ucAreaCode;//Area Code
	memcpy(APIOut->ucTMLocationID_6,DongleIn->ucTMLocationID_6,sizeof(APIOut->ucTMLocationID_6));//TM Location ID 6
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,stStore_DataInfo_t.ucTMTxnDateTime,sizeof(stStore_DataInfo_t.ucTMTxnDateTime));//TM Date Time
	memcpy(APIOut->ucTMSerialNumber,stStore_DataInfo_t.ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,stStore_DataInfo_t.ucTMAgentNumber,sizeof(stStore_DataInfo_t.ucTMAgentNumber));//TM Agent Number
	memcpy(APIOut->ucEV_2,DongleOut->ucEV_2,sizeof(APIOut->ucEV_2));//EV 2
	memcpy(APIOut->ucSTAC,DongleOut->ucSTAC,sizeof(APIOut->ucSTAC));//S-TAC
	APIOut->ucKeyVersion = DongleOut->ucSAMKeyVersion;//Key Version
	memcpy(APIOut->ucSAMID,DongleOut->ucSAMID,sizeof(APIOut->ucSAMID));//SAM ID
	memcpy(APIOut->ucSAMSN,DongleOut->ucSAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
	memcpy(APIOut->ucSAMCRN,DongleOut->ucSAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader Firmward Version

	return(inTMOutLen);
}

int inBuildAuthSetValueData(int inTxnType,AuthSetValue_TM_Out *APIOut,AuthSetValue_APDU_In *DongleIn,AuthSetValue_APDU_Out *DongleOut,SetValue_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthSetValue_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->anCardID_10,sizeof(APIOut->anCardID_10),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->anDeviceID,sizeof(APIOut->anDeviceID),MIFARE);//n_TXN Device ID
	vdIntToAsc(TxnReqOut->ucEV_2,sizeof(TxnReqOut->ucEV_2),APIOut->anEVBeforeTxn_5,sizeof(APIOut->anEVBeforeTxn_5),' ',10);//n_EV Before TXN
	fnLongToUnix(APIOut->anOrgExpiryDate,(unsigned long *)TxnReqOut->ucExpiryDate,8);//原票卡到期日
	fnLongToUnix(APIOut->anNewExpiryDate,(unsigned long *)DongleIn->ucExpiryDate,8);//新票卡到期日
	vdBuildProcessingCode(inTxnType,0x00,0x00,TxnReqOut->ucPersonalProfile,APIOut->anProcessignCode);//Processing Code
	memcpy(APIOut->unMsgType,"50",sizeof(APIOut->unMsgType));//Msg Type
	memset(APIOut->unSubType,0x30,sizeof(APIOut->unSubType));//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->unDeviceID);//Device ID
	fnUnPack(stStore_DataInfo_t.ucTxnDateTime,sizeof(stStore_DataInfo_t.ucTxnDateTime),APIOut->unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->unPersonalProfile);//Personal Profile
	fnUnPack(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->unCardID_8);//CPU Card ID
	fnUnPack(DongleIn->ucExpiryDate,sizeof(DongleIn->ucExpiryDate),APIOut->unNewExpiryDate);//New Expiry Date

	return(inTMOutLen);
}

int inBuildTxRefundData(int inTxnType,TxRefund_TM_Out *APIOut,TxRefund_APDU_In *DongleIn,TxRefund_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(TxRefund_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	memcpy(APIOut->ucCommandCode,"05",sizeof(APIOut->ucCommandCode));//Command Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List Version
	APIOut->ucMsgType = DongleIn->ucMsgType;//Msg Type
	APIOut->ucSubType = DongleIn->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucDeviceID[2];//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime2,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	memcpy(APIOut->ucCardID_4,DongleOut->ucCardID_4,sizeof(APIOut->ucCardID_4));//Card ID 4
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
	memcpy(APIOut->ucTxnAmt_2,DongleOut->ucTxnAmt2_2,sizeof(APIOut->ucTxnAmt_2));//Txn Amt 2
//	APIOut->ucLocationID = LOCATION_ID;//Location ID
	APIOut->ucBankCode = DongleOut->ucBankCode;//Bank Code
	memcpy(APIOut->ucLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucLoyaltyCounter));//Loyalty Counter
	memcpy(APIOut->ucDeposit,DongleOut->ucDeposit,sizeof(APIOut->ucDeposit));//Deposit
	memcpy(APIOut->ucExpiryDate,DongleOut->ucExpiryDate,sizeof(APIOut->ucExpiryDate));//Expiry Date
	APIOut->ucAreaCode = DongleOut->ucAreaCode;//Area Code
	memcpy(APIOut->ucTMLocationID_6,DongleIn->ucTMLocationID_6,sizeof(APIOut->ucTMLocationID_6));//TM Location ID 6
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleOut->ucTMTxnDateTime,sizeof(DongleOut->ucTMTxnDateTime));//TM Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(DongleOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleOut->ucTMAgentNumber,sizeof(DongleOut->ucTMAgentNumber));//TM Agent Number
	memcpy(APIOut->ucEV_2,DongleOut->ucEV2_2,sizeof(APIOut->ucEV_2));//EV 2
	memcpy(APIOut->ucSTAC,DongleOut->ucSTAC,sizeof(APIOut->ucSTAC));//S-TAC
	APIOut->ucKeyVersion = DongleOut->ucSAMKeyVersion;//Key Version
	memcpy(APIOut->ucSAMID,DongleOut->ucSAMID,sizeof(APIOut->ucSAMID));//SAM ID
	memcpy(APIOut->ucSAMSN,DongleOut->ucSAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
	memcpy(APIOut->ucSAMCRN,DongleOut->ucSAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader Firmward Version
	APIOut->ucCAVRMsgType = 0x0C;//CAVR Msg Type
	APIOut->ucCAVRTxnSNLSB = DongleOut->ucCAVRTxnSNLSB;//CAVR Txn SN LSB
	memcpy(APIOut->ucCAVRTxnDateTime,DongleOut->ucCAVRTxnDateTime,sizeof(APIOut->ucCAVRTxnDateTime));//CAVR Txn Date Time
	APIOut->ucCAVRSubType = DongleOut->ucCAVRSubType;//CAVR Sub Type
	memcpy(APIOut->ucCAVRTxnAmt,DongleOut->ucCAVRTxnAmt,sizeof(APIOut->ucCAVRTxnAmt));//CAVR Txn Amt
	memcpy(APIOut->ucCAVREV,DongleOut->ucCAVREV,sizeof(APIOut->ucCAVREV));//CAVR EV
	memcpy(APIOut->ucCAVRCardID,DongleOut->ucCardID_4,sizeof(APIOut->ucCAVRCardID));//CAVR Card ID
	APIOut->ucCAVRIssuerCode = DongleOut->ucIssuerCode;//CAVR Issuer Code
	APIOut->ucCAVRSPID = DongleOut->ucCAVRSPID;//CAVR SP Code
	APIOut->ucCAVRLocationID = DongleOut->ucCAVRLocationID;//CAVR Location ID
	memcpy(APIOut->ucCAVRDeviceID,DongleOut->ucCAVRDeviceID,sizeof(APIOut->ucCAVRDeviceID));//CAVR Device ID
	APIOut->ucCAVRBankCode = DongleOut->ucBankCode;//CAVR Bank Code
	memcpy(APIOut->ucCAVRLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucCAVRLoyaltyCounter));//CAVR Loyalty Counter
	memcpy(&APIOut->stReaderAVR_t,&DongleOut->stReaderAVR_t,sizeof(APIOut->stReaderAVR_t));//Reader AVR

	return(inTMOutLen);
}

int inBuildAuthTxRefundData(int inTxnType,AuthTxRefund_TM_Out *APIOut,AuthTxRefund_APDU_In *DongleIn,AuthTxRefund_APDU_Out *DongleOut,TxRefund_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthTxRefund_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	//餘退SETM
	vdUIntToAsc(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stTxRefundSETM_t.anCardID_10,sizeof(APIOut->stTxRefundSETM_t.anCardID_10),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stTxRefundSETM_t.anDeviceID,sizeof(APIOut->stTxRefundSETM_t.anDeviceID),MIFARE);//n_TXN Device ID
	vdIntToAsc(TxnReqOut->ucEV2_2,sizeof(TxnReqOut->ucEV2_2),APIOut->stTxRefundSETM_t.anEVBeforeTxn_5,sizeof(APIOut->stTxRefundSETM_t.anEVBeforeTxn_5),' ',10);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN2_2,sizeof(DongleOut->ucTxnSN2_2),APIOut->stTxRefundSETM_t.anTxnSN_5,sizeof(APIOut->stTxRefundSETM_t.anTxnSN_5),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt2_2,sizeof(TxnReqOut->ucTxnAmt2_2),APIOut->stTxRefundSETM_t.anTxnAmt_5,sizeof(APIOut->stTxRefundSETM_t.anTxnAmt_5),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV2_2,sizeof(DongleOut->ucEV2_2),APIOut->stTxRefundSETM_t.anEV_5,sizeof(APIOut->stTxRefundSETM_t.anEV_5),' ',10);//n_EV
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->stTxRefundSETM_t.anProcessignCode);//Processing Code
	fnUnPack(&TxnReqOut->ucMsgType,sizeof(TxnReqOut->ucMsgType),APIOut->stTxRefundSETM_t.unMsgType);//Msg Type
	fnUnPack(&TxnReqOut->ucSubType,sizeof(TxnReqOut->ucSubType),APIOut->stTxRefundSETM_t.unSubType);//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stTxRefundSETM_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucDeviceID[2],sizeof(APIOut->stTxRefundSETM_t.unSPID) / 2,APIOut->stTxRefundSETM_t.unSPID);//SP ID
	fnUnPack(stStore_DataInfo_t.ucTxnDateTime2,sizeof(stStore_DataInfo_t.ucTxnDateTime2),APIOut->stTxRefundSETM_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stTxRefundSETM_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stTxRefundSETM_t.unPersonalProfile);//Personal Profile
	fnUnPack(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stTxRefundSETM_t.unCardID_8);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stTxRefundSETM_t.unIssuerCode);//Issuer Code
	fnUnPack(DongleOut->ucTxnSN2_2,sizeof(DongleOut->ucTxnSN2_2),APIOut->stTxRefundSETM_t.unTxnSN_4);//Txn SN
	fnUnPack(TxnReqOut->ucTxnAmt2_2,sizeof(TxnReqOut->ucTxnAmt2_2),APIOut->stTxRefundSETM_t.unTxnAmt_4);//Txn Amt
	fnUnPack(DongleOut->ucEV2_2,sizeof(DongleOut->ucEV2_2),APIOut->stTxRefundSETM_t.unEV_4);//EV
	memcpy(APIOut->stTxRefundSETM_t.unLocationID,LOCATION_ID_BATCH,sizeof(APIOut->stTxRefundSETM_t.unLocationID));//Location ID
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->stTxRefundSETM_t.unBankCode);//Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->stTxRefundSETM_t.unLoyaltyCounter);//Loyalty Counter
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stTxRefundSETM_t.unDeposit_4);//Deposit
	fnUnPack(DongleOut->ucMAC2,sizeof(DongleOut->ucMAC2),APIOut->stTxRefundSETM_t.unMAC);//MAC
	fnUnPack(TxnReqOut->ucExpiryDate,sizeof(TxnReqOut->ucExpiryDate),APIOut->stTxRefundSETM_t.anOrgExpiryDate);//Org Expiry Date
	fnUnPack(DongleIn->ucRFU4,sizeof(DongleIn->ucRFU4),APIOut->stTxRefundSETM_t.anNewExpiryDate);//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stTxRefundSETM_t.unAreaCode);//Area Code
	fnUnPack(TxnReqOut->ucEV2_2,sizeof(TxnReqOut->ucEV2_2),APIOut->stTxRefundSETM_t.unEVBeforeTxn_4);//EV Before Txn
	//餘退電文
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",53);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,0x00,APIOut->ucProcessignCode);//Processing Code
	memcpy(APIOut->ucCommandCode,"05",sizeof(APIOut->ucCommandCode));//Command Code
	APIOut->ucMsgType = TxnReqOut->ucMsgType;//Msg Type
	APIOut->ucSubType = TxnReqOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,TxnReqOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	memcpy(APIOut->ucTxnDateTime,stStore_DataInfo_t.ucTxnDateTime2,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	memcpy(APIOut->ucCardID_4,TxnReqOut->ucCardID_4,sizeof(APIOut->ucCardID_4));//Card ID
	memcpy(APIOut->ucTxnSN_2,DongleOut->ucTxnSN2_2,sizeof(APIOut->ucTxnSN_2));//Txn SN
	memcpy(APIOut->ucEV_2,DongleOut->ucEV2_2,sizeof(APIOut->ucEV_2));//EV
	memcpy(APIOut->ucMAC,DongleOut->ucMAC2,sizeof(APIOut->ucMAC));//MAC
	memcpy(APIOut->ucConfirmCode,DongleOut->ucConfirmCode2,sizeof(APIOut->ucConfirmCode));//Confirm Code
	memcpy(APIOut->ucCTAC,DongleOut->ucCTAC,sizeof(APIOut->ucCTAC));//CTAC
	//餘扣SETM
	vdUIntToAsc(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stTxDeductSETM_t.anCardID_10,sizeof(APIOut->stTxDeductSETM_t.anCardID_10),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stTxDeductSETM_t.anDeviceID,sizeof(APIOut->stTxDeductSETM_t.anDeviceID),MIFARE);//n_TXN Device ID
	vdIntToAsc(TxnReqOut->ucEV_2,sizeof(TxnReqOut->ucEV_2),APIOut->stTxDeductSETM_t.anEVBeforeTxn_5,sizeof(APIOut->stTxDeductSETM_t.anEVBeforeTxn_5),' ',10);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN_2,sizeof(DongleOut->ucTxnSN_2),APIOut->stTxDeductSETM_t.anTxnSN_5,sizeof(APIOut->stTxDeductSETM_t.anTxnSN_5),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt_2,sizeof(TxnReqOut->ucTxnAmt_2),APIOut->stTxDeductSETM_t.anTxnAmt_5,sizeof(APIOut->stTxDeductSETM_t.anTxnAmt_5),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV_2,sizeof(DongleOut->ucEV_2),APIOut->stTxDeductSETM_t.anEV_5,sizeof(APIOut->stTxDeductSETM_t.anEV_5),' ',10);//n_EV
	memcpy(APIOut->stTxDeductSETM_t.anProcessignCode,"812599",sizeof(APIOut->stTxDeductSETM_t.anProcessignCode));//Processign Code
	memcpy(APIOut->stTxDeductSETM_t.unMsgType,"01",sizeof(APIOut->stTxDeductSETM_t.unMsgType));//Msg Type
	memcpy(APIOut->stTxDeductSETM_t.unSubType,"00",sizeof(APIOut->stTxDeductSETM_t.unSubType));//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stTxDeductSETM_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucDeviceID[2],sizeof(APIOut->stTxDeductSETM_t.unSPID) / 2,APIOut->stTxDeductSETM_t.unSPID);//SP ID
	fnUnPack(stStore_DataInfo_t.ucTxnDateTime,sizeof(stStore_DataInfo_t.ucTxnDateTime),APIOut->stTxDeductSETM_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stTxDeductSETM_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stTxDeductSETM_t.unPersonalProfile);//Personal Profile
	fnUnPack(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stTxDeductSETM_t.unCardID_8);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stTxDeductSETM_t.unIssuerCode);//Issuer Code
	fnUnPack(DongleOut->ucTxnSN_2,sizeof(DongleOut->ucTxnSN_2),APIOut->stTxDeductSETM_t.unTxnSN_4);//Txn SN
	fnUnPack(TxnReqOut->ucTxnAmt_2,sizeof(TxnReqOut->ucTxnAmt_2),APIOut->stTxDeductSETM_t.unTxnAmt_4);//Txn Amt
	fnUnPack(DongleOut->ucEV_2,sizeof(DongleOut->ucEV_2),APIOut->stTxDeductSETM_t.unEV_4);//EV
	memcpy(APIOut->stTxDeductSETM_t.unLocationID,LOCATION_ID_BATCH,sizeof(APIOut->stTxDeductSETM_t.unLocationID));//Location ID
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->stTxDeductSETM_t.unBankCode);//Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->stTxDeductSETM_t.unLoyaltyCounter);//Loyalty Counter
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stTxDeductSETM_t.unDeposit_4);//Deposit
	fnUnPack(DongleOut->ucMAC,sizeof(DongleOut->ucMAC),APIOut->stTxDeductSETM_t.unMAC);//MAC
	memcpy(APIOut->stTxDeductSETM_t.anOrgExpiryDate,"00000000",sizeof(APIOut->stTxDeductSETM_t.anOrgExpiryDate));//Org Expiry Date
	memcpy(APIOut->stTxDeductSETM_t.anNewExpiryDate,"00000000",sizeof(APIOut->stTxDeductSETM_t.anNewExpiryDate));//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stTxDeductSETM_t.unAreaCode);//Area Code
	fnUnPack(TxnReqOut->ucEV_2,sizeof(TxnReqOut->ucEV_2),APIOut->stTxDeductSETM_t.unEVBeforeTxn_4);//EV Before Txn
	memcpy(APIOut->ucTMLocationID_6,TxnReqOut->ucTMLocationID_6,sizeof(APIOut->ucTMLocationID_6));//TM Location ID
	memcpy(APIOut->ucTMID,TxnReqOut->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,TxnReqOut->ucTMTxnDateTime,sizeof(APIOut->ucTMTxnDateTime));//TM Txn Date Time
	memcpy(APIOut->ucTMSerialNumber,TxnReqOut->ucTMSerialNumber,sizeof(APIOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,TxnReqOut->ucTMAgentNumber,sizeof(APIOut->ucTMAgentNumber));//TM Agent Number
	//餘退加值重送
	fnUnPack(&TxnReqOut->ucDeviceID[2],sizeof(TxnReqOut->ucDeviceID[2]),APIOut->unVARSPID);//VAR SP ID
	memcpy(APIOut->unVARLocationID,LOCATION_ID_BATCH,2);//VAR Location ID
	memcpy(APIOut->unVARMsgType,"0C",2);//VAR Msg Type
	fnUnPack(&TxnReqOut->ucCAVRTxnSNLSB,sizeof(TxnReqOut->ucCAVRTxnSNLSB),APIOut->unVARTxnSNLSB);//VAR Txn SN LSB
	fnUnPack(TxnReqOut->ucCAVRTxnDateTime,sizeof(TxnReqOut->ucCAVRTxnDateTime),APIOut->unVARTxnDateTime);//VAR Txn Date Time
	fnUnPack(&TxnReqOut->ucCAVRSubType,sizeof(TxnReqOut->ucCAVRSubType),APIOut->unVARSubType);//VAR Sub Type
	fnUnPack(TxnReqOut->ucCAVRTxnAmt,sizeof(TxnReqOut->ucCAVRTxnAmt),APIOut->unVARTxnAmt_4);//VAR Txn Amt
	fnUnPack(TxnReqOut->ucCAVREV,sizeof(TxnReqOut->ucCAVREV),APIOut->unVAREV_4);//VAR EV
	fnUnPack(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->unVARCardID_8);//VAR Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->unVARIssuerCode);//VAR Issuer Code
	fnUnPack(&TxnReqOut->ucCAVRSPID,sizeof(TxnReqOut->ucCAVRSPID),APIOut->unVAR2SPID);//VAR SP ID
	fnUnPack(&TxnReqOut->ucCAVRLocationID,sizeof(TxnReqOut->ucCAVRLocationID),APIOut->unVAR2LocationID);//VAR Location ID
	fnUnPack(TxnReqOut->ucCAVRDeviceID,sizeof(TxnReqOut->ucCAVRDeviceID),APIOut->unVAR2DeviceID);//VAR Device ID
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->unVARBankCode);//VAR Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->unVARLoyaltyCounter);//VAR Loyalty Counter

	return(inTMOutLen);
}

int inBuildAddValueData(int inTxnType,AddValue_TM_Out *APIOut,AddValue_APDU_In *DongleIn,AddValue_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(AddValue_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	memcpy(APIOut->ucCommandCode,"05",sizeof(APIOut->ucCommandCode));//Command Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List Version
	APIOut->ucMsgType = DongleIn->ucMsgType;//Msg Type
	APIOut->ucSubType = DongleIn->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucDeviceID[2];//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	memcpy(APIOut->ucCardID_4,DongleOut->ucCardID_4,sizeof(APIOut->ucCardID_4));//Card ID 4
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
	memcpy(APIOut->ucTxnAmt_2,DongleOut->ucTxnAmt_2,sizeof(APIOut->ucTxnAmt_2));//Txn Amt 2
//	APIOut->ucLocationID = LOCATION_ID;//Location ID
	APIOut->ucBankCode = DongleOut->ucBankCode;//Bank Code
	memcpy(APIOut->ucLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucLoyaltyCounter));//Loyalty Counter
	memcpy(APIOut->ucExpiryDate,DongleOut->ucExpiryDate,sizeof(APIOut->ucExpiryDate));//Expiry Date
	APIOut->ucAreaCode = DongleOut->ucAreaCode;//Area Code
	memcpy(APIOut->ucTMLocationID_6,DongleIn->ucTMLocationID_6,sizeof(APIOut->ucTMLocationID_6));//TM Location ID 6
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleOut->ucTMTxnDateTime,sizeof(DongleOut->ucTMTxnDateTime));//TM Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(DongleOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleOut->ucTMAgentNumber,sizeof(DongleOut->ucTMAgentNumber));//TM Agent Number
	memcpy(APIOut->ucEV_2,DongleOut->ucEV_2,sizeof(APIOut->ucEV_2));//EV 2
	memcpy(APIOut->ucSTAC,DongleOut->ucSTAC,sizeof(APIOut->ucSTAC));//S-TAC
	APIOut->ucKeyVersion = DongleOut->ucSAMKeyVersion;//Key Version
	memcpy(APIOut->ucSAMID,DongleOut->ucSAMID,sizeof(APIOut->ucSAMID));//SAM ID
	memcpy(APIOut->ucSAMSN,DongleOut->ucSAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
	memcpy(APIOut->ucSAMCRN,DongleOut->ucSAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader Firmward Version
	APIOut->ucCAVRMsgType = 0x0C;//CAVR Msg Type
	APIOut->ucCAVRTxnSNLSB = DongleOut->ucCAVRTxnSNLSB;//CAVR Txn SN LSB
	memcpy(APIOut->ucCAVRTxnDateTime,DongleOut->ucCAVRTxnDateTime,sizeof(APIOut->ucCAVRTxnDateTime));//CAVR Txn Date Time
	APIOut->ucCAVRSubType = DongleOut->ucCAVRSubType;//CAVR Sub Type
	memcpy(APIOut->ucCAVRTxnAmt,DongleOut->ucCAVRTxnAmt,sizeof(APIOut->ucCAVRTxnAmt));//CAVR Txn Amt
	memcpy(APIOut->ucCAVREV,DongleOut->ucCAVREV,sizeof(APIOut->ucCAVREV));//CAVR EV
	memcpy(APIOut->ucCAVRCardID,DongleOut->ucCardID_4,sizeof(APIOut->ucCAVRCardID));//CAVR Card ID
	APIOut->ucCAVRIssuerCode = DongleOut->ucIssuerCode;//CAVR Issuer Code
	APIOut->ucCAVRSPID = DongleOut->ucCAVRSPID;//CAVR SP Code
	APIOut->ucCAVRLocationID = DongleOut->ucCAVRLocationID;//CAVR Location ID
	memcpy(APIOut->ucCAVRDeviceID,DongleOut->ucCAVRDeviceID,sizeof(APIOut->ucCAVRDeviceID));//CAVR Device ID
	APIOut->ucCAVRBankCode = DongleOut->ucBankCode;//CAVR Bank Code
	memcpy(APIOut->ucCAVRLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucCAVRLoyaltyCounter));//CAVR Loyalty Counter
	memcpy(&APIOut->stReaderAVR_t,&DongleOut->stReaderAVR_t,sizeof(APIOut->stReaderAVR_t));//Reader AVR

	return(inTMOutLen);
}

int inBuildAuthAddValueData(int inTxnType,AuthAddValue_TM_Out *APIOut,AuthAddValue_APDU_In *DongleIn,AuthAddValue_APDU_Out *DongleOut,AddValue_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthAddValue_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	//餘加SETM
	vdUIntToAsc(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stAddValueSETM_t.anCardID_10,sizeof(APIOut->stAddValueSETM_t.anCardID_10),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stAddValueSETM_t.anDeviceID,sizeof(APIOut->stAddValueSETM_t.anDeviceID),MIFARE);//n_TXN Device ID
	vdIntToAsc(TxnReqOut->ucEV_2,sizeof(TxnReqOut->ucEV_2),APIOut->stAddValueSETM_t.anEVBeforeTxn_5,sizeof(APIOut->stAddValueSETM_t.anEVBeforeTxn_5),' ',10);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN_2,sizeof(DongleOut->ucTxnSN_2),APIOut->stAddValueSETM_t.anTxnSN_5,sizeof(APIOut->stAddValueSETM_t.anTxnSN_5),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt_2,sizeof(TxnReqOut->ucTxnAmt_2),APIOut->stAddValueSETM_t.anTxnAmt_5,sizeof(APIOut->stAddValueSETM_t.anTxnAmt_5),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV_2,sizeof(DongleOut->ucEV_2),APIOut->stAddValueSETM_t.anEV_5,sizeof(APIOut->stAddValueSETM_t.anEV_5),' ',10);//n_EV
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->stAddValueSETM_t.anProcessignCode);//Processing Code
	fnUnPack(&TxnReqOut->ucMsgType,sizeof(TxnReqOut->ucMsgType),APIOut->stAddValueSETM_t.unMsgType);//Msg Type
	fnUnPack(&TxnReqOut->ucSubType,sizeof(TxnReqOut->ucSubType),APIOut->stAddValueSETM_t.unSubType);//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stAddValueSETM_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucDeviceID[2],sizeof(APIOut->stAddValueSETM_t.unSPID) / 2,APIOut->stAddValueSETM_t.unSPID);//SP ID
	fnUnPack(stStore_DataInfo_t.ucTxnDateTime,sizeof(stStore_DataInfo_t.ucTxnDateTime),APIOut->stAddValueSETM_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stAddValueSETM_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stAddValueSETM_t.unPersonalProfile);//Personal Profile
	fnUnPack(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stAddValueSETM_t.unCardID_8);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stAddValueSETM_t.unIssuerCode);//Issuer Code
	fnUnPack(DongleOut->ucTxnSN_2,sizeof(DongleOut->ucTxnSN_2),APIOut->stAddValueSETM_t.unTxnSN_4);//Txn SN
	fnUnPack(TxnReqOut->ucTxnAmt_2,sizeof(TxnReqOut->ucTxnAmt_2),APIOut->stAddValueSETM_t.unTxnAmt_4);//Txn Amt
	fnUnPack(DongleOut->ucEV_2,sizeof(DongleOut->ucEV_2),APIOut->stAddValueSETM_t.unEV_4);//EV
	memcpy(APIOut->stAddValueSETM_t.unLocationID,LOCATION_ID_BATCH,sizeof(APIOut->stAddValueSETM_t.unLocationID));//Location ID
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->stAddValueSETM_t.unBankCode);//Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->stAddValueSETM_t.unLoyaltyCounter);//Loyalty Counter
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stAddValueSETM_t.unDeposit_4);//Deposit
	fnUnPack(DongleOut->ucMAC,sizeof(DongleOut->ucMAC),APIOut->stAddValueSETM_t.unMAC);//MAC
	fnUnPack(TxnReqOut->ucExpiryDate,sizeof(TxnReqOut->ucExpiryDate),APIOut->stAddValueSETM_t.anOrgExpiryDate);//Org Expiry Date
	fnUnPack(DongleIn->ucExpiryDate,sizeof(DongleIn->ucExpiryDate),APIOut->stAddValueSETM_t.anNewExpiryDate);//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stAddValueSETM_t.unAreaCode);//Area Code
	fnUnPack(TxnReqOut->ucEV_2,sizeof(TxnReqOut->ucEV_2),APIOut->stAddValueSETM_t.unEVBeforeTxn_4);//EV Before Txn
	//餘加電文
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",53);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,0x00,APIOut->ucProcessignCode);//Processing Code
	memcpy(APIOut->ucCommandCode,"05",sizeof(APIOut->ucCommandCode));//Command Code
	APIOut->ucMsgType = TxnReqOut->ucMsgType;//Msg Type
	APIOut->ucSubType = TxnReqOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,TxnReqOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	memcpy(APIOut->ucTxnDateTime,stStore_DataInfo_t.ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	memcpy(APIOut->ucCardID_4,TxnReqOut->ucCardID_4,sizeof(APIOut->ucCardID_4));//Card ID
	memcpy(APIOut->ucTxnSN_2,DongleOut->ucTxnSN_2,sizeof(APIOut->ucTxnSN_2));//Txn SN
	memcpy(APIOut->ucEV_2,DongleOut->ucEV_2,sizeof(APIOut->ucEV_2));//EV
	memcpy(APIOut->ucMAC,DongleOut->ucMAC,sizeof(APIOut->ucMAC));//MAC
	memcpy(APIOut->ucConfirmCode,DongleOut->ucConfirmCode,sizeof(APIOut->ucConfirmCode));//Confirm Code
	memcpy(APIOut->ucCTAC,DongleOut->ucCTAC,sizeof(APIOut->ucCTAC));//CTAC

	return(inTMOutLen);
}

int inBuildAutoloadEnableData(int inTxnType,AutoloadEnable_TM_Out *APIOut,AutoloadEnable_APDU_In *DongleIn,AutoloadEnable_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(AutoloadEnable_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	memcpy(APIOut->ucCommandCode,"05",sizeof(APIOut->ucCommandCode));//Command Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List Version
	APIOut->ucMsgType = DongleIn->ucMsgType;//Msg Type
	APIOut->ucSubType = DongleIn->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucDeviceID[2];//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	memcpy(APIOut->ucCardID_4,DongleOut->ucCardID_4,sizeof(APIOut->ucCardID_4));//Card ID 4
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
	memcpy(APIOut->ucTxnAmt_2,DongleOut->ucTxnAmt_2,sizeof(APIOut->ucTxnAmt_2));//Txn Amt 2
//	APIOut->ucLocationID = LOCATION_ID;//Location ID
	APIOut->ucBankCode = DongleOut->ucBankCode;//Bank Code
	memcpy(APIOut->ucLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucLoyaltyCounter));//Loyalty Counter
	memcpy(APIOut->ucExpiryDate,DongleOut->ucExpiryDate,sizeof(APIOut->ucExpiryDate));//Expiry Date
	APIOut->ucAreaCode = DongleOut->ucAreaCode;//Area Code
	memcpy(APIOut->ucTMLocationID_6,DongleIn->ucTMLocationID_6,sizeof(APIOut->ucTMLocationID_6));//TM Location ID 6
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleOut->ucTMTxnDateTime,sizeof(DongleOut->ucTMTxnDateTime));//TM Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(DongleOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleOut->ucTMAgentNumber,sizeof(DongleOut->ucTMAgentNumber));//TM Agent Number
	memcpy(APIOut->ucEV_2,DongleOut->ucEV_2,sizeof(APIOut->ucEV_2));//EV 2
	memcpy(APIOut->ucSTAC,DongleOut->ucSTAC,sizeof(APIOut->ucSTAC));//S-TAC
	APIOut->ucKeyVersion = DongleOut->ucSAMKeyVersion;//Key Version
	memcpy(APIOut->ucSAMID,DongleOut->ucSAMID,sizeof(APIOut->ucSAMID));//SAM ID
	memcpy(APIOut->ucSAMSN,DongleOut->ucSAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
	memcpy(APIOut->ucSAMCRN,DongleOut->ucSAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader Firmward Version
	APIOut->ucCAVRMsgType = 0x0C;//CAVR Msg Type
	APIOut->ucCAVRTxnSNLSB = DongleOut->ucCAVRTxnSNLSB;//CAVR Txn SN LSB
	memcpy(APIOut->ucCAVRTxnDateTime,DongleOut->ucCAVRTxnDateTime,sizeof(APIOut->ucCAVRTxnDateTime));//CAVR Txn Date Time
	APIOut->ucCAVRSubType = DongleOut->ucCAVRSubType;//CAVR Sub Type
	memcpy(APIOut->ucCAVRTxnAmt,DongleOut->ucCAVRTxnAmt,sizeof(APIOut->ucCAVRTxnAmt));//CAVR Txn Amt
	memcpy(APIOut->ucCAVREV,DongleOut->ucCAVREV,sizeof(APIOut->ucCAVREV));//CAVR EV
	memcpy(APIOut->ucCAVRCardID,DongleOut->ucCardID_4,sizeof(APIOut->ucCAVRCardID));//CAVR Card ID
	APIOut->ucCAVRIssuerCode = DongleOut->ucIssuerCode;//CAVR Issuer Code
	APIOut->ucCAVRSPID = DongleOut->ucCAVRSPID;//CAVR SP Code
	APIOut->ucCAVRLocationID = DongleOut->ucCAVRLocationID;//CAVR Location ID
	memcpy(APIOut->ucCAVRDeviceID,DongleOut->ucCAVRDeviceID,sizeof(APIOut->ucCAVRDeviceID));//CAVR Device ID
	APIOut->ucCAVRBankCode = DongleOut->ucBankCode;//CAVR Bank Code
	memcpy(APIOut->ucCAVRLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucCAVRLoyaltyCounter));//CAVR Loyalty Counter
	memcpy(&APIOut->stReaderAVR_t,&DongleOut->stReaderAVR_t,sizeof(APIOut->stReaderAVR_t));//Reader AVR
	APIOut->ucAutoLoadFlag = DongleOut->ucAutoLoadFlag;////AutoLoad Flag
	memcpy(APIOut->ucAutoLoadAmt_2,DongleOut->ucAutoLoadAmt_2,sizeof(APIOut->ucAutoLoadAmt_2));//AutoLoad Amt

	return(inTMOutLen);
}

int inBuildAuthAutoloadEnableData(int inTxnType,AuthAutoloadEnable_TM_Out *APIOut,AuthAutoloadEnable_APDU_In *DongleIn,AuthAutoloadEnable_APDU_Out *DongleOut,AutoloadEnable_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthAutoloadEnable_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	//自動加值開啟SETM
	vdUIntToAsc(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stAddValueSETM_t.anCardID_10,sizeof(APIOut->stAddValueSETM_t.anCardID_10),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stAddValueSETM_t.anDeviceID,sizeof(APIOut->stAddValueSETM_t.anDeviceID),MIFARE);//n_TXN Device ID
	vdIntToAsc(TxnReqOut->ucEV_2,sizeof(TxnReqOut->ucEV_2),APIOut->stAddValueSETM_t.anEVBeforeTxn_5,sizeof(APIOut->stAddValueSETM_t.anEVBeforeTxn_5),' ',10);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN_2,sizeof(DongleOut->ucTxnSN_2),APIOut->stAddValueSETM_t.anTxnSN_5,sizeof(APIOut->stAddValueSETM_t.anTxnSN_5),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt_2,sizeof(TxnReqOut->ucTxnAmt_2),APIOut->stAddValueSETM_t.anTxnAmt_5,sizeof(APIOut->stAddValueSETM_t.anTxnAmt_5),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV_2,sizeof(DongleOut->ucEV_2),APIOut->stAddValueSETM_t.anEV_5,sizeof(APIOut->stAddValueSETM_t.anEV_5),' ',10);//n_EV
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->stAddValueSETM_t.anProcessignCode);//Processing Code
	fnUnPack(&TxnReqOut->ucMsgType,sizeof(TxnReqOut->ucMsgType),APIOut->stAddValueSETM_t.unMsgType);//Msg Type
	fnUnPack(&TxnReqOut->ucSubType,sizeof(TxnReqOut->ucSubType),APIOut->stAddValueSETM_t.unSubType);//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stAddValueSETM_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucDeviceID[2],sizeof(APIOut->stAddValueSETM_t.unSPID) / 2,APIOut->stAddValueSETM_t.unSPID);//SP ID
	fnUnPack(stStore_DataInfo_t.ucTxnDateTime,sizeof(stStore_DataInfo_t.ucTxnDateTime),APIOut->stAddValueSETM_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stAddValueSETM_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stAddValueSETM_t.unPersonalProfile);//Personal Profile
	fnUnPack(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stAddValueSETM_t.unCardID_8);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stAddValueSETM_t.unIssuerCode);//Issuer Code
	fnUnPack(DongleOut->ucTxnSN_2,sizeof(DongleOut->ucTxnSN_2),APIOut->stAddValueSETM_t.unTxnSN_4);//Txn SN
	fnUnPack(TxnReqOut->ucTxnAmt_2,sizeof(TxnReqOut->ucTxnAmt_2),APIOut->stAddValueSETM_t.unTxnAmt_4);//Txn Amt
	fnUnPack(DongleOut->ucEV_2,sizeof(DongleOut->ucEV_2),APIOut->stAddValueSETM_t.unEV_4);//EV
	memcpy(APIOut->stAddValueSETM_t.unLocationID,LOCATION_ID_BATCH,sizeof(APIOut->stAddValueSETM_t.unLocationID));//Location ID
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->stAddValueSETM_t.unBankCode);//Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->stAddValueSETM_t.unLoyaltyCounter);//Loyalty Counter
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stAddValueSETM_t.unDeposit_4);//Deposit
	fnUnPack(DongleOut->ucMAC,sizeof(DongleOut->ucMAC),APIOut->stAddValueSETM_t.unMAC);//MAC
	fnUnPack(TxnReqOut->ucExpiryDate,sizeof(TxnReqOut->ucExpiryDate),APIOut->stAddValueSETM_t.anOrgExpiryDate);//Org Expiry Date
	memset(APIOut->stAddValueSETM_t.anNewExpiryDate,0x30,sizeof(APIOut->stAddValueSETM_t.anNewExpiryDate));//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stAddValueSETM_t.unAreaCode);//Area Code
	fnUnPack(TxnReqOut->ucEV_2,sizeof(TxnReqOut->ucEV_2),APIOut->stAddValueSETM_t.unEVBeforeTxn_4);//EV Before Txn
	//自動加值開啟電文
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",53);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,0x00,APIOut->ucProcessignCode);//Processing Code
	memcpy(APIOut->ucCommandCode,"05",sizeof(APIOut->ucCommandCode));//Command Code
	APIOut->ucMsgType = TxnReqOut->ucMsgType;//Msg Type
	APIOut->ucSubType = TxnReqOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,TxnReqOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	memcpy(APIOut->ucTxnDateTime,stStore_DataInfo_t.ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	memcpy(APIOut->ucCardID_4,TxnReqOut->ucCardID_4,sizeof(APIOut->ucCardID_4));//Card ID
	memcpy(APIOut->ucTxnSN_2,DongleOut->ucTxnSN_2,sizeof(APIOut->ucTxnSN_2));//Txn SN
	memcpy(APIOut->ucEV_2,DongleOut->ucEV_2,sizeof(APIOut->ucEV_2));//EV
	memcpy(APIOut->ucMAC,DongleOut->ucMAC,sizeof(APIOut->ucMAC));//MAC
	memcpy(APIOut->ucConfirmCode,DongleOut->ucConfirmCode,sizeof(APIOut->ucConfirmCode));//Confirm Code
	memcpy(APIOut->ucCTAC,DongleOut->ucCTAC,sizeof(APIOut->ucCTAC));//CTAC
	APIOut->ucAutoLoadFlag = 0x01;////AutoLoad Flag
	//APIOut->ucAutoLoadFlag = TxnReqOut->ucAutoLoadFlag;////AutoLoad Flag
	memcpy(APIOut->ucAutoLoadAmt_2,TxnReqOut->ucAutoLoadAmt_2,sizeof(APIOut->ucAutoLoadAmt_2));//AutoLoad Amt

	return(inTMOutLen);
}

int inBuildReadCardDeductData(int inTxnType,ReadCardDeduct_TM_Out *APIOut,ReadCardDeduct_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(ReadCardDeduct_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildReadCardBasicData2(0x01,&DongleOut->stCardDeductLog1_t,&APIOut->stCardDeductRecored1_t);
	vdBuildReadCardBasicData2(0x01,&DongleOut->stCardDeductLog2_t,&APIOut->stCardDeductRecored2_t);
	vdBuildReadCardBasicData2(0x01,&DongleOut->stCardDeductLog3_t,&APIOut->stCardDeductRecored3_t);
	vdBuildReadCardBasicData2(0x01,&DongleOut->stCardDeductLog4_t,&APIOut->stCardDeductRecored4_t);
	vdBuildReadCardBasicData2(0x01,&DongleOut->stCardDeductLog5_t,&APIOut->stCardDeductRecored5_t);
	vdBuildReadCardBasicData2(0x01,&DongleOut->stCardDeductLog6_t,&APIOut->stCardDeductRecored6_t);

	return(inTMOutLen);
}

int inBuildReadCodeVersionData(int inTxnType,ReadCodeVersion_TM_Out *APIOut,ReadCodeVersion_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(ReadCodeVersion_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	APIOut->ucSAMAppletVersion = DongleOut->ucSAMAppletVersion;//SAM Applet Version
	APIOut->ucSAMType = DongleOut->ucSAMType;//SAM Type
	APIOut->ucSAMVersion = DongleOut->ucSAMVersion;//SAM Version
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader FW Version
	APIOut->ucHostSpecVersionNo = DongleOut->ucHostSpecVersionNo;//Host Spec Version No

	return(inTMOutLen);
}

int inBuildSetValue2Data(int inTxnType,SetValue2_TM_Out *APIOut,SetValue2_APDU_In *DongleIn,SetValue2_APDU_Out *DongleOut)
{
int inTMOutLen;
BYTE ucLoyaltyCounter[2];

	inTMOutLen = sizeof(SetValue2_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,DongleOut->ucMsgType,DongleOut->ucSubType,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List
	APIOut->ucMsgType = DongleOut->ucMsgType;//Msg Type
	APIOut->ucSubType = DongleOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucSPID;//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
	memcpy(APIOut->ucExpiryDate,DongleOut->ucExpiryDate,sizeof(APIOut->ucExpiryDate));//Expiry Date
	APIOut->ucAreaCode = DongleOut->ucAreaCode;//Area Code
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleIn->ucTMTxnDateTime,sizeof(APIOut->ucTMTxnDateTime));//TM Txn Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(APIOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleIn->ucTMAgentNumber,sizeof(APIOut->ucTMAgentNumber));//TM Agent Number
	if(DongleOut->ucPurseVersionNumber != LEVEL2)
	{
		memcpy(APIOut->ucSTAC,DongleOut->SAMID_STAC,sizeof(APIOut->ucSTAC));//STAC
		APIOut->ucKeyVersion = DongleOut->HostAdminKeyKVN_SAMKVN[0];//SAM KVN
		memcpy(APIOut->ucSAMID,&DongleOut->SVCrypto_SAMCRN_SAMID[8],sizeof(APIOut->ucSAMID));//SAM ID
		memcpy(APIOut->ucSAMSN,DongleOut->SAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
		memcpy(APIOut->ucSAMCRN,DongleOut->SVCrypto_SAMCRN_SAMID,sizeof(APIOut->ucSAMCRN));//SAM CRN
	}
	else
	{
		memset(APIOut->ucSTAC,0x00,sizeof(APIOut->ucSTAC));//STAC
		APIOut->ucKeyVersion = 0;//SAM KVN
		memset(APIOut->ucSAMID,0x00,sizeof(APIOut->ucSAMID));//SAM ID
		memset(APIOut->ucSAMSN,0x00,sizeof(APIOut->ucSAMSN));//SAM SN
		memset(APIOut->ucSAMCRN,0x00,sizeof(APIOut->ucSAMCRN));//SAM CRN
	}
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader FW Version
	memcpy(APIOut->ucCardID,DongleOut->ucCardID,sizeof(APIOut->ucCardID));//Card ID
	memcpy(APIOut->ucTxnAmt,DongleOut->ucTxnAmt,sizeof(APIOut->ucTxnAmt));//Txn Amt
	memcpy(APIOut->ucCPUDeviceID,DongleOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucCPUSPID,DongleOut->ucCPUSPID,sizeof(APIOut->ucCPUSPID));//CPU SP ID
	memcpy(APIOut->ucCPULocationID,DongleOut->ucCPULocationID,sizeof(APIOut->ucCPULocationID));//CPU Location ID
	memcpy(APIOut->ucPID,DongleOut->ucPID,sizeof(APIOut->ucPID));//CPU Purse ID
	memcpy(APIOut->ucCTC,DongleOut->ucCTC,sizeof(APIOut->ucCTC));//CPU CTC
	memcpy(APIOut->ucProfileExpiryDate,DongleOut->ucProfileExpiryDate,sizeof(APIOut->ucProfileExpiryDate));//Profile Expiry Date
	if(DongleOut->ucPurseVersionNumber == LEVEL2)
		memcpy(APIOut->ucSubAreaCode,DongleOut->SubAreaCode_LoyaltyCounter,sizeof(APIOut->ucSubAreaCode));//Sub Area Code
	else
		memset(APIOut->ucSubAreaCode,0x00,sizeof(APIOut->ucSubAreaCode));//Sub Area Code
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN,sizeof(APIOut->ucTxnSN));//Txn SN
	memcpy(APIOut->ucEV,DongleOut->ucEV,sizeof(APIOut->ucEV));//EV
	APIOut->ucCPUAdminKeyKVN = DongleOut->ucCPUAdminKeyKVN;//CPU Admin Key KVN
	APIOut->ucCreditKeyKVN = DongleOut->ucCreditKeyKVN;//Credit Key KVN
	APIOut->ucCPUIssuerKeyKVN = DongleOut->ucCPUIssuerKeyKVN;//CPU Issuer Key KVN
	APIOut->ucTxnMode = DongleOut->ucTxnMode;//Txn Mode
	APIOut->ucTxnQuqlifier = DongleOut->ucTxnQuqlifier;//Txn Quqlifier
	if(DongleOut->ucPurseVersionNumber == LEVEL2)
	{
		memcpy(APIOut->ucCPUSAMID,&DongleOut->SAMID_STAC,sizeof(APIOut->ucCPUSAMID));//CPU SAM ID
		APIOut->ucHostAdminKVN = DongleOut->HostAdminKeyKVN_SAMKVN[0];//Host Admin KVN
	}
	else
	{
		memset(APIOut->ucCPUSAMID,0x00,sizeof(APIOut->ucCPUSAMID));//CPU SAM ID
		APIOut->ucHostAdminKVN = 0x00;//Host Admin KVN
	}
	APIOut->ucPurseVersionNumber = DongleOut->ucPurseVersionNumber;//Purse Version Number
	memcpy(APIOut->ucTMLocationID,DongleIn->ucTMLocationID,sizeof(APIOut->ucTMLocationID));//TM Location ID
	if(DongleOut->ucPurseVersionNumber != LEVEL2)
		memset(APIOut->ucCACrypto,0x00,sizeof(APIOut->ucCACrypto));//CACrypto後8碼
	else
		memcpy(APIOut->ucCACrypto,DongleOut->SVCrypto_SAMCRN_SAMID,sizeof(APIOut->ucCACrypto));//CACrypto
	memset(ucLoyaltyCounter,0x00,sizeof(ucLoyaltyCounter));
	vdBuildCardAVRData(&APIOut->stCardAVRInfo_t,&DongleOut->stLastCreditTxnLogInfo_t,DongleOut->ucCardID,DongleOut->ucIssuerCode,DongleOut->ucCPUSPID,DongleOut->ucCPULocationID,DongleOut->ucPID,ucLoyaltyCounter);//Card AVR Info
	APIOut->ucCardIDLen = DongleOut->ucCardIDLen;//Card ID Len

	return(inTMOutLen);
}

int inBuildAuthSetValue2Data(int inTxnType,AuthSetValue2_TM_Out *APIOut,AuthSetValue2_APDU_In *DongleIn,AuthSetValue2_APDU_Out *DongleOut,SetValue2_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthSetValue2_TM_Out);
	memset(APIOut,0x00,inTMOutLen);

	vdUIntToAsc(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->anCardID,sizeof(APIOut->anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->anDeviceID,sizeof(APIOut->anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(TxnReqOut->ucCPUDeviceID,APIOut->anCPUDeviceID,sizeof(APIOut->anCPUDeviceID),LEVEL2);//n_TXN Device ID
	vdCountEVBefore(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->anEVBeforeTxn,sizeof(APIOut->anEVBeforeTxn),TxnReqOut->ucMsgType);//n_EV Before TXN
	fnLongToUnix(APIOut->anOrgExpiryDate,(unsigned long *)TxnReqOut->ucExpiryDate,8);//原票卡到期日
	fnLongToUnix(APIOut->anNewExpiryDate,(unsigned long *)DongleIn->ucExpiryDate,8);//新票卡到期日

	return(inTMOutLen);
}

int inBuildLockCardData7(int inTxnType,LockCard_TM_Out_2 *APIOut,TxRefund_APDU_Out *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason)
{
int inTMOutLen;
BYTE bSpace[20],ucCardID[7];

	inTMOutLen = sizeof(LockCard_TM_Out_2);
	memset(APIOut,0x00,inTMOutLen);
	memset(bSpace,0x20,sizeof(bSpace));
	memset(APIOut->unPurseVersionNumber,0x30,sizeof(APIOut->unPurseVersionNumber));//Purse Version Number
	sprintf((char *)APIOut->unMsgType,"22");//Msg Type
	sprintf((char *)APIOut->unSubType,"00");//Sub Type
	fnUnPack(DongleOut->ucDeviceID,sizeof(DongleOut->ucDeviceID),APIOut->unDeviceID);//Device ID
	fnUnPack(&DongleOut->ucDeviceID[2],1,APIOut->unSPID);//SP ID
	fnUnPack(ucTxnDateTime,sizeof(APIOut->unTxnDateTime) / 2,APIOut->unTxnDateTime);//Txn Date Time
	memset(ucCardID,0x00,sizeof(ucCardID));
	memcpy(ucCardID,DongleOut->ucCardID_4,sizeof(DongleOut->ucCardID_4));
	fnUnPack(ucCardID,sizeof(ucCardID),APIOut->unCardID);//Card ID
	fnUnPack(&DongleOut->ucIssuerCode,sizeof(DongleOut->ucIssuerCode),APIOut->unIssuerCode);//Issuer Code
	memcpy(APIOut->unLocationID,LOCATION_ID_BATCH,2);//Location ID
	memset(APIOut->unCardIDLen,0x30,sizeof(APIOut->unCardIDLen));//Card ID Len
	memset(APIOut->unCPUDeviceID,0x30,sizeof(APIOut->unCPUDeviceID));//CPU Device ID
	memset(APIOut->unCPUSPID,0x30,sizeof(APIOut->unCPUSPID));//CPU SP ID
	memset(APIOut->unCPULocationID,0x30,sizeof(APIOut->unCPULocationID));//CPU Location ID
	fnUnPack(&DongleOut->ucCardType,sizeof(DongleOut->ucCardType),APIOut->unCardType);//Card Type
	fnUnPack(&DongleOut->ucPersonalProfile,sizeof(DongleOut->ucPersonalProfile),APIOut->unPersonalProfile);//Personal Profile
	memset(APIOut->unPID,0x30,sizeof(APIOut->unPID));//CPU Purse ID
	memset(APIOut->unCTC,0x30,sizeof(APIOut->unCTC));//CTC
	fnUnPack(&ucLockReason,sizeof(ucLockReason),APIOut->unLockReason);//Lock Reason
	memset(APIOut->unBLCFileName,0x20,sizeof(APIOut->unBLCFileName));//BLC File Name
	APIOut->unBLCIDFlag = 0x20;//BLC ID Flag
	memcpy(APIOut->unTMLocationID,DongleOut->ucTMLocationID_6,sizeof(APIOut->unTMLocationID));//TM Location ID
	memcpy(APIOut->unTMID,DongleOut->ucTMID,sizeof(APIOut->unTMID));//TM ID
	memset(APIOut->unRFU,0x20,sizeof(APIOut->unRFU));//RFU

	return(inTMOutLen);
}

int inBuildTxRefundData2(int inTxnType,TxnReqOnline_TM_Out_2 *APIOut,TxRefund_APDU_In *DongleIn,TxRefund2_APDU_Out *DongleOut)
{
int inTMOutLen;

	inTMOutLen = sizeof(TxnReqOnline_TM_Out_2);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,0x00,0x00,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List Version
	APIOut->ucMsgType = DongleIn->ucMsgType;//Msg Type
	APIOut->ucSubType = DongleIn->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucDeviceID[2];//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime2,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
//	APIOut->ucLocationID = LOCATION_ID;//Location ID
	APIOut->ucBankCode = DongleOut->ucBankCode;//Bank Code
	memcpy(APIOut->ucLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucLoyaltyCounter));//Loyalty Counter
	memset(APIOut->ucExpiryDate,0x00,sizeof(APIOut->ucExpiryDate));//Expiry Date
	APIOut->ucAreaCode = DongleOut->ucAreaCode;//Area Code
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleOut->ucTMTxnDateTime,sizeof(DongleOut->ucTMTxnDateTime));//TM Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(DongleOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleOut->ucTMAgentNumber,sizeof(DongleOut->ucTMAgentNumber));//TM Agent Number
	memcpy(APIOut->ucSTAC,DongleOut->ucSTAC,sizeof(APIOut->ucSTAC));//S-TAC
	APIOut->ucKeyVersion = DongleOut->ucSAMKeyVersion;//Key Version
	memcpy(APIOut->ucSAMID,DongleOut->ucSAMID,sizeof(APIOut->ucSAMID));//SAM ID
	memcpy(APIOut->ucSAMSN,DongleOut->ucSAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
	memcpy(APIOut->ucSAMCRN,DongleOut->ucSAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader Firmward Version
	memcpy(APIOut->ucCardID,DongleOut->ucCardID_4,sizeof(DongleOut->ucCardID_4));//Card ID 4
	memcpy(APIOut->ucTxnAmt,DongleOut->ucTxnAmt2_2,sizeof(DongleOut->ucTxnAmt_2));//Txn Amt 2
	if((APIOut->ucTxnAmt[1] & 0x80) == 0x80)
		APIOut->ucTxnAmt[2] = 0xFF;
	memcpy(APIOut->ucCPUDeviceID,DongleOut->ucCPUDeviceID,sizeof(DongleOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucCPUSPID,&DongleOut->ucCPUDeviceID[3],sizeof(APIOut->ucCPUSPID));//CPU SP ID
	memset(APIOut->ucCPULocationID,0x00,sizeof(APIOut->ucCPULocationID));//CPU Location ID
	memset(APIOut->ucPID,0x00,sizeof(APIOut->ucPID));//PID
	memset(APIOut->ucCTC,0x00,sizeof(APIOut->ucCTC));//CTC
	memset(APIOut->ucProfileExpiryDate,0x00,sizeof(APIOut->ucProfileExpiryDate));//Profile Expiry Date
	memset(APIOut->ucSubAreaCode,0x00,sizeof(APIOut->ucSubAreaCode));//Sub Area Code
	memset(APIOut->ucTxnSN,0x00,sizeof(APIOut->ucTxnSN));//Txn SN
	vdAmt2ByteTo3Byte(DongleOut->ucEV2_2,APIOut->ucEV);//EV
	//memcpy(APIOut->ucEV,DongleOut->ucEV2_2,sizeof(DongleOut->ucEV_2));//EV 2
	memcpy(APIOut->ucDeposit,DongleOut->ucDeposit,sizeof(DongleOut->ucDeposit));//Deposit
	APIOut->ucCPUAdminKeyKVN = 0x00;
	APIOut->ucCreditKeyKVN = 0x00;
	APIOut->ucCPUIssuerKeyKVN = 0x00;
	APIOut->ucTxnMode = 0x00;
	APIOut->ucTxnQuqlifier = 0x00;
	APIOut->ucSignatureKeyKVN = DongleOut->ucSAMKeyVersion;
	memset(APIOut->ucCPUSAMID,0x00,sizeof(APIOut->ucCPUSAMID));//Txn SN
	APIOut->ucHostAdminKVN = 0x00;
	APIOut->ucPurseVersionNumber = 0x00;
	memset(APIOut->ucTMLocationID,0x20,sizeof(APIOut->ucTMLocationID));
	memcpy(&APIOut->ucTMLocationID[4],DongleIn->ucTMLocationID_6,sizeof(DongleIn->ucTMLocationID_6));//TM Location ID 6
	memset(APIOut->ucCACrypto,0x00,sizeof(APIOut->ucCACrypto));//CA Crypto

	APIOut->stCardAVRInfo_t.ucMsgType = 0x0C;
	APIOut->stCardAVRInfo_t.ucPurseVersionNumber = 0x00;
	APIOut->stCardAVRInfo_t.ucTxnSN[0] = DongleOut->ucCAVRTxnSNLSB;//CAVR Txn SN LSB
	memcpy(APIOut->stCardAVRInfo_t.ucTxnDateTime,DongleOut->ucCAVRTxnDateTime,sizeof(DongleOut->ucCAVRTxnDateTime));//CAVR Txn Date Time
	APIOut->stCardAVRInfo_t.ucSubType = DongleOut->ucCAVRSubType;
	memcpy(APIOut->stCardAVRInfo_t.ucTxnAmt,DongleOut->ucCAVRTxnAmt,sizeof(DongleOut->ucCAVRTxnAmt));//CAVR Txn Amt
	memcpy(APIOut->stCardAVRInfo_t.ucEV,DongleOut->ucCAVREV,sizeof(DongleOut->ucCAVREV));//CAVR Txn EV
	memcpy(APIOut->stCardAVRInfo_t.ucCardID,DongleOut->ucCardID_4,sizeof(DongleOut->ucCardID_4));//CAVR Card ID 4
	APIOut->stCardAVRInfo_t.ucIssuerCode = DongleOut->ucIssuerCode;//CAVR Issuer Code
	memset(APIOut->stCardAVRInfo_t.ucCPUSPID,0x00,sizeof(APIOut->stCardAVRInfo_t.ucCPUSPID));//CAVR CPU SP ID
	memset(APIOut->stCardAVRInfo_t.ucCPULocationID,0x00,sizeof(APIOut->stCardAVRInfo_t.ucCPULocationID));//CAVR CPU Location ID
	memset(APIOut->stCardAVRInfo_t.ucPID,0x00,sizeof(APIOut->stCardAVRInfo_t.ucPID));//CAVR CPU PID
	memset(APIOut->stCardAVRInfo_t.ucCPUDeviceID,0x00,sizeof(APIOut->stCardAVRInfo_t.ucCPUDeviceID));//CAVR CPU Device ID
	memcpy(APIOut->stCardAVRInfo_t.ucLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucLoyaltyCounter));//CAVR Loyalty Counter
	vdBuildReaderAVRData(&APIOut->stReaderAVRInfo_t,&DongleOut->stReaderAVRInfo_t);//Reader AVR Info
	APIOut->ucCardIDLen = 4;

	return(inTMOutLen);
}

int inBuildAuthTxRefundData2(int inTxnType,AuthTxRefund2_TM_Out *APIOut,AuthTxnOnline_TM_In *DongleIn,AuthTxRefund_APDU_Out *DongleOut,TxRefund2_APDU_Out *TxnReqOut)
{
int inTMOutLen;
//Store_Data stStore_DataInfo_t;
BYTE ucTxnDateTime[4];

	//vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthTxRefund2_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	//餘退STMC開始
	vdUIntToAsc(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stTxRefundSTMC_t.anCardID,sizeof(APIOut->stTxRefundSTMC_t.anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stTxRefundSTMC_t.anDeviceID,sizeof(APIOut->stTxRefundSTMC_t.anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(TxnReqOut->ucCPUDeviceID,APIOut->stTxRefundSTMC_t.anCPUDeviceID,sizeof(APIOut->stTxRefundSTMC_t.anCPUDeviceID),LEVEL2);//n_TXN Device ID
	vdIntToAsc(TxnReqOut->ucEV2_2,sizeof(TxnReqOut->ucEV2_2),APIOut->stTxRefundSTMC_t.anEVBeforeTxn,sizeof(APIOut->stTxRefundSTMC_t.anEVBeforeTxn),' ',10);//n_EV Before TXN
	//vdCountEVBefore(TxnReqOut->ucTxnAmt2_2,sizeof(TxnReqOut->ucTxnAmt2_2),DongleOut->ucEV2_2,sizeof(DongleOut->ucEV2_2),APIOut->stTxRefundSTMC_t.anEVBeforeTxn,sizeof(APIOut->stTxRefundSTMC_t.anEVBeforeTxn),TxnReqOut->ucMsgType);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN2_2,sizeof(DongleOut->ucTxnSN2_2),APIOut->stTxRefundSTMC_t.anTxnSN,sizeof(APIOut->stTxRefundSTMC_t.anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt2_2,sizeof(TxnReqOut->ucTxnAmt2_2),APIOut->stTxRefundSTMC_t.anTxnAmt,sizeof(APIOut->stTxRefundSTMC_t.anTxnAmt),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV2_2,sizeof(DongleOut->ucEV2_2),APIOut->stTxRefundSTMC_t.anEV,sizeof(APIOut->stTxRefundSTMC_t.anEV),' ',10);//n_EV
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->stTxRefundSTMC_t.anProcessignCode);//Processing Code
	fnUnPack(&TxnReqOut->ucMsgType,sizeof(TxnReqOut->ucMsgType),APIOut->stTxRefundSTMC_t.unMsgType);//Msg Type
	fnUnPack(&TxnReqOut->ucSubType,sizeof(TxnReqOut->ucSubType),APIOut->stTxRefundSTMC_t.unSubType);//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stTxRefundSTMC_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucDeviceID[2],1,APIOut->stTxRefundSTMC_t.unSPID);//SP ID
	fngetUnixTimeCnt(ucTxnDateTime,TxnReqOut->ucTMTxnDateTime2);
	fnUnPack(ucTxnDateTime,sizeof(ucTxnDateTime),APIOut->stTxRefundSTMC_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stTxRefundSTMC_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stTxRefundSTMC_t.unPersonalProfile);//Personal Profile
	sprintf((char *)APIOut->stTxRefundSTMC_t.unLocationID,"01");//Location ID
	memset(APIOut->stTxRefundSTMC_t.unCardID,0x30,sizeof(APIOut->stTxRefundSTMC_t.unCardID));//Org Card ID
	fnUnPack(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->stTxRefundSTMC_t.unCardID);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stTxRefundSTMC_t.unIssuerCode);//Issuer Code
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->stTxRefundSTMC_t.unBankCode);//Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->stTxRefundSTMC_t.unLoyaltyCounter);//Loyalty Counter
	fnUnPack(DongleOut->ucMAC2,sizeof(DongleOut->ucMAC2),APIOut->stTxRefundSTMC_t.unMAC);//MAC
	memset(APIOut->stTxRefundSTMC_t.unOrgExpiryDate,0x30,sizeof(APIOut->stTxRefundSTMC_t.unOrgExpiryDate));//Org Expiry Date
	fnUnPack(DongleIn->ucExpiryDate,sizeof(DongleIn->ucExpiryDate),APIOut->stTxRefundSTMC_t.unNewExpiryDate);//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stTxRefundSTMC_t.unAreaCode);//Area Code
	memset(APIOut->stTxRefundSTMC_t.unTxnAmt,0x30,sizeof(APIOut->stTxRefundSTMC_t.unTxnAmt));//Txn Amt
	fnUnPack(TxnReqOut->ucTxnAmt2_2,sizeof(TxnReqOut->ucTxnAmt2_2),APIOut->stTxRefundSTMC_t.unTxnAmt);//Txn Amt
	vdUnPackAmt2ByteTo3Byte(DongleOut->ucEV2_2,APIOut->stTxRefundSTMC_t.unEV);
	//memset(APIOut->stTxRefundSTMC_t.unEV,0x30,sizeof(APIOut->stTxRefundSTMC_t.unEV));//EV
	//fnUnPack(DongleOut->ucEV2_2,sizeof(DongleOut->ucEV2_2),APIOut->stTxRefundSTMC_t.unEV);//EV
	memset(APIOut->stTxRefundSTMC_t.unTxnSN,0x30,sizeof(APIOut->stTxRefundSTMC_t.unTxnSN));//Txn SN
	fnUnPack(DongleOut->ucTxnSN2_2,sizeof(DongleOut->ucTxnSN2_2),APIOut->stTxRefundSTMC_t.unTxnSN);//Txn SN
	fnUnPack(TxnReqOut->ucCPUDeviceID,sizeof(TxnReqOut->ucCPUDeviceID),APIOut->stTxRefundSTMC_t.unCPUDeviceID);//CPU Device ID
	fnUnPack(&TxnReqOut->ucCPUDeviceID[3],3,APIOut->stTxRefundSTMC_t.unCPUSPID);//CPU SP ID
	memset(APIOut->stTxRefundSTMC_t.unCPULocationID,0x30,sizeof(APIOut->stTxRefundSTMC_t.unCPULocationID));//CPU Location ID
	memset(APIOut->stTxRefundSTMC_t.unPID,0x30,sizeof(APIOut->stTxRefundSTMC_t.unPID));//Purse ID
	memset(APIOut->stTxRefundSTMC_t.unCTC,0x30,sizeof(APIOut->stTxRefundSTMC_t.unCTC));//CTC
	memset(APIOut->stTxRefundSTMC_t.unOrgProfileExpiryDate,0x30,sizeof(APIOut->stTxRefundSTMC_t.unOrgProfileExpiryDate));//Org Profile Expiry Date
	fnUnPack(DongleIn->ucProfileExpiryDate,sizeof(DongleIn->ucProfileExpiryDate),APIOut->stTxRefundSTMC_t.unNewProfileExpiryDate);//New Profile Expiry Date
	memset(APIOut->stTxRefundSTMC_t.unSubAreaCode,0x30,sizeof(APIOut->stTxRefundSTMC_t.unSubAreaCode));//Sub Area Code
	memset(APIOut->stTxRefundSTMC_t.unTxnSNBeforeTxn,0x30,sizeof(APIOut->stTxRefundSTMC_t.unTxnSNBeforeTxn));//Txn SN Before Txn
	fnUnPack(TxnReqOut->ucTxmSn2_2,sizeof(TxnReqOut->ucTxmSn2_2),APIOut->stTxRefundSTMC_t.unTxnSNBeforeTxn);//Txn SN Before Txn
	vdUnPackAmt2ByteTo3Byte(TxnReqOut->ucEV2_2,APIOut->stTxRefundSTMC_t.unEVBeforeTxn);
	//memset(APIOut->stTxRefundSTMC_t.unEVBeforeTxn,0x30,sizeof(APIOut->stTxRefundSTMC_t.unEVBeforeTxn));//EV Before Txn
	//fnUnPack(TxnReqOut->ucEV2_2,sizeof(TxnReqOut->ucEV2_2),APIOut->stTxRefundSTMC_t.unEVBeforeTxn);//EV Before Txn
	memset(APIOut->stTxRefundSTMC_t.unDeposit,0x30,sizeof(APIOut->stTxRefundSTMC_t.unDeposit));//Deposit
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stTxRefundSTMC_t.unDeposit);//Deposit
	memset(APIOut->stTxRefundSTMC_t.unTxnMode,0x30,sizeof(APIOut->stTxRefundSTMC_t.unTxnMode));//Txn Mode
	memset(APIOut->stTxRefundSTMC_t.unTxnQuqlifier,0x30,sizeof(APIOut->stTxRefundSTMC_t.unTxnQuqlifier));//Txn Quqlifier
	memset(APIOut->stTxRefundSTMC_t.unSignatureKeyKVN,0x30,sizeof(APIOut->stTxRefundSTMC_t.unSignatureKeyKVN));//Signature Key KVN
	memset(APIOut->stTxRefundSTMC_t.unSignature,0x30,sizeof(APIOut->stTxRefundSTMC_t.unSignature));//Signature
	memset(APIOut->stTxRefundSTMC_t.unHashType,0x30,sizeof(APIOut->stTxRefundSTMC_t.unHashType));
	memset(APIOut->stTxRefundSTMC_t.unCPUSAMID,0x30,sizeof(APIOut->stTxRefundSTMC_t.unCPUSAMID));//SAM ID
	memset(APIOut->stTxRefundSTMC_t.unHostAdminKVN,0x30,sizeof(APIOut->stTxRefundSTMC_t.unHostAdminKVN));
	memset(APIOut->stTxRefundSTMC_t.unCPUMAC,0x30,sizeof(APIOut->stTxRefundSTMC_t.unCPUMAC));//MAC
	sprintf((char *)APIOut->stTxRefundSTMC_t.unPurseVersionNumber,"00");//Purse Version Number
	sprintf((char *)APIOut->stTxRefundSTMC_t.unCardIDLen,"04");//Card ID Len
	memset(APIOut->stTxRefundSTMC_t.ucTMLocationID,0x30,sizeof(APIOut->stTxRefundSTMC_t.ucTMLocationID));//MAC
	memcpy(APIOut->stTxRefundSTMC_t.ucTMLocationID,TxnReqOut->ucTMLocationID_6,sizeof(TxnReqOut->ucTMLocationID_6));//TM Location ID
	memcpy(APIOut->stTxRefundSTMC_t.ucTMID,TxnReqOut->ucTMID,sizeof(TxnReqOut->ucTMID));//TM ID
	memcpy(APIOut->stTxRefundSTMC_t.ucTMTxnDateTime,TxnReqOut->ucTMTxnDateTime2,sizeof(TxnReqOut->ucTMTxnDateTime2));//TM Txn Date Time
	memcpy(APIOut->stTxRefundSTMC_t.ucTMSerialNumber,TxnReqOut->ucTMSerialNumber2,sizeof(TxnReqOut->ucTMSerialNumber2));//TM Serial Number
	memcpy(APIOut->stTxRefundSTMC_t.ucTMAgentNumber,TxnReqOut->ucTMAgentNumber,sizeof(TxnReqOut->ucTMAgentNumber));//TM Agent Number
	//帳務資料結束
	//Congirm資料開始
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",79);//Data Len
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	APIOut->ucMsgType = TxnReqOut->ucMsgType;//Msg Type
	APIOut->ucSubType = TxnReqOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,TxnReqOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	memcpy(APIOut->ucTxnDateTime,ucTxnDateTime,sizeof(ucTxnDateTime));//Txn Date Time
	memcpy(APIOut->ucMAC,DongleOut->ucMAC2,sizeof(APIOut->ucMAC));//MAC
	memcpy(APIOut->ucConfirmCode,DongleOut->ucConfirmCode,sizeof(APIOut->ucConfirmCode));//Confirm Code
	memcpy(APIOut->ucCTAC,DongleOut->ucCTAC,sizeof(APIOut->ucMAC));//CTAC
	memcpy(APIOut->ucCardID,TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4));//Card ID
	vdAmt2ByteTo3Byte(DongleOut->ucEV2_2,APIOut->ucEV);//EV
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN2_2,sizeof(DongleOut->ucTxnSN2_2));//Txn SN
	memcpy(APIOut->ucCPUDeviceID,TxnReqOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memset(APIOut->ucPID,0x00,sizeof(APIOut->ucPID));//Purse ID
	memset(APIOut->ucSignature,0x00,sizeof(APIOut->ucSignature));//Signature
	APIOut->ucHashType = 0x00;
	APIOut->ucHostAdminKVN = 0x00;
	memset(APIOut->ucCPUMAC,0x00,sizeof(APIOut->ucCPUMAC));//CPU MAC

	//餘扣STMC開始
	memcpy(&APIOut->stTxDeductSTMC_t,&APIOut->stTxRefundSTMC_t,sizeof(STMC_t));
	vdCountEVBefore(TxnReqOut->ucTxnAmt_2,sizeof(TxnReqOut->ucTxnAmt_2),DongleOut->ucEV_2,sizeof(DongleOut->ucEV_2),APIOut->stTxDeductSTMC_t.anEVBeforeTxn,sizeof(APIOut->stTxDeductSTMC_t.anEVBeforeTxn),TxnReqOut->ucMsgType);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN_2,sizeof(DongleOut->ucTxnSN_2),APIOut->stTxDeductSTMC_t.anTxnSN,sizeof(APIOut->stTxDeductSTMC_t.anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt_2,sizeof(TxnReqOut->ucTxnAmt_2),APIOut->stTxDeductSTMC_t.anTxnAmt,sizeof(APIOut->stTxDeductSTMC_t.anTxnAmt),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV_2,sizeof(DongleOut->ucEV_2),APIOut->stTxDeductSTMC_t.anEV,sizeof(APIOut->stTxDeductSTMC_t.anEV),' ',10);//n_EV
	fngetUnixTimeCnt(ucTxnDateTime,TxnReqOut->ucTMTxnDateTime);
	fnUnPack(ucTxnDateTime,sizeof(ucTxnDateTime),APIOut->stTxDeductSTMC_t.unTxnDateTime);//Txn Date Time
	fnUnPack(DongleOut->ucMAC,sizeof(DongleOut->ucMAC),APIOut->stTxDeductSTMC_t.unMAC);//MAC
	fnUnPack(TxnReqOut->ucTxnAmt_2,sizeof(TxnReqOut->ucTxnAmt_2),APIOut->stTxDeductSTMC_t.unTxnAmt);//Txn Amt
	vdUnPackAmt2ByteTo3Byte(DongleOut->ucEV_2,APIOut->stTxDeductSTMC_t.unEV);
	//vdUnPackAmt2ByteTo3Byte(DongleOut->ucEV2_2,APIOut->stTxDeductSTMC_t.unEV);
	//fnUnPack(DongleOut->ucEV_2,sizeof(DongleOut->ucEV_2),APIOut->stTxDeductSTMC_t.unEV);//EV
	fnUnPack(DongleOut->ucTxnSN_2,sizeof(DongleOut->ucTxnSN_2),APIOut->stTxDeductSTMC_t.unTxnSN);//Txn SN
	fnUnPack(TxnReqOut->ucTxmSn_2,sizeof(TxnReqOut->ucTxmSn_2),APIOut->stTxDeductSTMC_t.unTxnSNBeforeTxn);//Txn SN Before Txn
	vdUnPackAmt2ByteTo3Byte(TxnReqOut->ucEV_2,APIOut->stTxDeductSTMC_t.unEVBeforeTxn);
	//vdUnPackAmt2ByteTo3Byte(TxnReqOut->ucEV2_2,APIOut->stTxDeductSTMC_t.unEVBeforeTxn);
	//fnUnPack(TxnReqOut->ucEV_2,sizeof(TxnReqOut->ucEV_2),APIOut->stTxDeductSTMC_t.unEVBeforeTxn);//EV Before Txn
	memcpy(APIOut->stTxDeductSTMC_t.anProcessignCode,"813599",sizeof(APIOut->stTxDeductSTMC_t.anProcessignCode));//Processign Code
	memcpy(APIOut->stTxDeductSTMC_t.unMsgType,"01",sizeof(APIOut->stTxDeductSTMC_t.unMsgType));//Msg Type
	memcpy(APIOut->stTxDeductSTMC_t.unSubType,"00",sizeof(APIOut->stTxDeductSTMC_t.unSubType));//Sub Type
	memcpy(APIOut->stTxDeductSTMC_t.ucTMTxnDateTime,TxnReqOut->ucTMTxnDateTime,sizeof(TxnReqOut->ucTMTxnDateTime));//TM Txn Date Time
	memcpy(APIOut->stTxDeductSTMC_t.ucTMSerialNumber,TxnReqOut->ucTMSerialNumber,sizeof(TxnReqOut->ucTMSerialNumber));//TM Serial Number
	//帳務資料結束,加值重送資料開始
	memcpy(APIOut->unVARMsgType,"0C",2);//VAR Msg Type
	sprintf((char *)APIOut->unVARPurseVersionNumber,"00");//VAR PurseVersion Number
	memset(APIOut->unVARTxnSN,0x30,sizeof(APIOut->unVARTxnSN));//VAR Txn SN
	fnUnPack(&TxnReqOut->ucCAVRTxnSNLSB,sizeof(TxnReqOut->ucCAVRTxnSNLSB),APIOut->unVARTxnSN);//VAR Txn SN
	fnUnPack(TxnReqOut->ucCAVRTxnDateTime,sizeof(TxnReqOut->ucCAVRTxnDateTime),APIOut->unVARTxnDateTime);//VAR Txn Date Time
	fnUnPack(&TxnReqOut->ucCAVRSubType,sizeof(TxnReqOut->ucCAVRSubType),APIOut->unVARSubType);//VAR Sub Type
	memset(APIOut->unVARTxnAmt,0x30,sizeof(APIOut->unVARTxnAmt));//VAR Txn Amt
	fnUnPack(TxnReqOut->ucCAVRTxnAmt,sizeof(TxnReqOut->ucCAVRTxnAmt),APIOut->unVARTxnAmt);//VAR Txn Amt
	memset(APIOut->unVAREV,0x30,sizeof(APIOut->unVAREV));//VAR EV
	fnUnPack(TxnReqOut->ucCAVREV,sizeof(TxnReqOut->ucCAVREV),APIOut->unVAREV);//VAR EV
	memset(APIOut->unVARCardID,0x30,sizeof(APIOut->unVARCardID));//VAR Card ID
	fnUnPack(TxnReqOut->ucCardID_4,sizeof(TxnReqOut->ucCardID_4),APIOut->unVARCardID);//VAR Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->unVARIssuerCode);//VAR Issuer Code
	memset(APIOut->unVARCPUSPID,0x30,sizeof(APIOut->unVARCPUSPID));//VAR CPU SP ID
	fnUnPack(&TxnReqOut->ucCAVRSPID,sizeof(TxnReqOut->ucCAVRSPID),APIOut->unVARCPUSPID);//VAR CPU SP ID
	memset(APIOut->unVARCPULocationID,0x30,sizeof(APIOut->unVARCPULocationID));//VAR CPU Location ID
	fnUnPack(&TxnReqOut->ucCAVRLocationID,sizeof(TxnReqOut->ucCAVRLocationID),APIOut->unVARCPULocationID);//VAR CPU Location ID
	memset(APIOut->unVARPID,0x30,sizeof(APIOut->unVARPID));//VAR Purse ID
	memset(APIOut->unVARCPUDeviceID,0x30,sizeof(APIOut->unVARCPUDeviceID));//VAR CPU Device ID
	fnUnPack(TxnReqOut->ucCAVRDeviceID,sizeof(TxnReqOut->ucCAVRDeviceID),APIOut->unVARCPUDeviceID);//VAR CPU Device ID
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->unVARLoyaltyCounter);//VAR Loyalty Counter
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->unVARPersonalProfile);//VAR Personal Profile
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->unVARBankCode);//VAR Bank Code
	sprintf((char *)APIOut->unVARCardIDLen,"04");//VAR Card ID Len

	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->unVAR2DeviceID);//VAR Device ID
	fnUnPack(&TxnReqOut->ucDeviceID[2],1,APIOut->unVAR2SPID);//VAR SP ID
	sprintf((char *)APIOut->unVAR2LocationID,"01");//VAR SP ID
	fnUnPack(TxnReqOut->ucCPUDeviceID,sizeof(TxnReqOut->ucCPUDeviceID),APIOut->unVAR2CPUDeviceID);//VAR CPU Device ID
	fnUnPack(&TxnReqOut->ucCPUDeviceID[3],3,APIOut->unVAR2CPUSPID);//VAR CPU SP ID
	memset(APIOut->unVAR2CPULocationID,0x30,sizeof(APIOut->unVAR2CPULocationID));//VAR CPU Location ID

	return(inTMOutLen);
}

int inBuildAutoloadEnableData2(int inTxnType,AutoloadEnable2_TM_Out *APIOut,TxnReqOnline_APDU_In *DongleIn,TxnReqOnline_APDU_Out *DongleOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	inTMOutLen = sizeof(AutoloadEnable2_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",inTMOutLen - 7);//Data Len
	vdBuildProcessingCode(inTxnType,DongleOut->ucMsgType,DongleOut->ucSubType,DongleOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	fnASCTOBIN(APIOut->ucBLVersion,&gsBlackListVersion[3],5,sizeof(APIOut->ucBLVersion),DECIMAL);//Black List
	APIOut->ucMsgType = DongleOut->ucMsgType;//Msg Type
	APIOut->ucSubType = DongleOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,DongleOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	APIOut->ucSPID = DongleOut->ucSPID;//SP ID
	memcpy(APIOut->ucTxnDateTime,DongleIn->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	APIOut->ucCardType = DongleOut->ucCardType;//Card Type
	APIOut->ucPersonalProfile = DongleOut->ucPersonalProfile;//Personal Profile
	APIOut->ucIssuerCode = DongleOut->ucIssuerCode;//Issuer Code
	APIOut->ucLocationID = DongleOut->ucLocationID;//Location ID
	APIOut->ucBankCode = DongleOut->ucBankCode;//Bank Code
	memcpy(APIOut->ucLoyaltyCounter,DongleOut->ucLoyaltyCounter,sizeof(APIOut->ucLoyaltyCounter));//Loyalty Counter
	memcpy(APIOut->ucExpiryDate,DongleOut->ucExpiryDate,sizeof(APIOut->ucExpiryDate));//Expiry Date
	APIOut->ucAreaCode = DongleOut->ucAreaCode;//Area Code
	memcpy(APIOut->ucTMID,DongleIn->ucTMID,sizeof(APIOut->ucTMID));//TM ID
	memcpy(APIOut->ucTMTxnDateTime,DongleIn->ucTMTxnDateTime,sizeof(APIOut->ucTMTxnDateTime));//TM Txn Date Time
	memcpy(APIOut->ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(APIOut->ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->ucTMAgentNumber,DongleIn->ucTMAgentNumber,sizeof(APIOut->ucTMAgentNumber));//TM Agent Number
	memcpy(APIOut->ucSTAC,DongleOut->ucSTAC,sizeof(APIOut->ucSTAC));//STAC
	APIOut->ucKeyVersion = DongleOut->ucSAMKVN;//SAM KVN
	memcpy(APIOut->ucSAMID,DongleOut->ucSAMID,sizeof(APIOut->ucSAMID));//SAM ID
	memcpy(APIOut->ucSAMSN,DongleOut->ucSAMSN,sizeof(APIOut->ucSAMSN));//SAM SN
	memcpy(APIOut->ucSAMCRN,DongleOut->ucSAMCRN,sizeof(APIOut->ucSAMCRN));//SAM CRN
	memcpy(APIOut->ucReaderFWVersion,DongleOut->ucReaderFWVersion,sizeof(APIOut->ucReaderFWVersion));//Reader FW Version
	APIOut->ucAutoLoadFlag = DongleOut->bAutoLoad;//Auto Load Flag
	memcpy(APIOut->ucAutoLoadAmt_2,DongleOut->ucAutoLoadAmt,sizeof(APIOut->ucAutoLoadAmt_2));//Auto Load Amt
	memcpy(APIOut->ucCardID,DongleOut->ucCardID,sizeof(APIOut->ucCardID));//Card ID
	memcpy(APIOut->ucTxnAmt,DongleOut->ucTxnAmt,sizeof(APIOut->ucTxnAmt));//Txn Amt
	memcpy(APIOut->ucCPUDeviceID,DongleOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucCPUSPID,DongleOut->ucCPUSPID,sizeof(APIOut->ucCPUSPID));//CPU SP ID
	memcpy(APIOut->ucCPULocationID,DongleOut->ucCPULocationID,sizeof(APIOut->ucCPULocationID));//CPU Location ID
	memcpy(APIOut->ucPID,DongleOut->ucPID,sizeof(APIOut->ucPID));//CPU Purse ID
	memcpy(APIOut->ucCTC,DongleOut->ucCTC,sizeof(APIOut->ucCTC));//CPU CTC
	memcpy(APIOut->ucProfileExpiryDate,DongleOut->ucProfileExpiryDate,sizeof(APIOut->ucProfileExpiryDate));//Profile Expiry Date
	memcpy(APIOut->ucSubAreaCode,DongleOut->ucSubAreaCode,sizeof(APIOut->ucSubAreaCode));//Sub Area Code
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN,sizeof(APIOut->ucTxnSN));//Txn SN
	memcpy(APIOut->ucEV,DongleOut->ucEV,sizeof(APIOut->ucEV));//EV
	memcpy(APIOut->ucDeposit,DongleOut->ucDeposit,sizeof(APIOut->ucDeposit));//Deposit
	APIOut->ucCPUAdminKeyKVN = DongleOut->ucCPUAdminKeyKVN;//CPU Admin Key KVN
	APIOut->ucCreditKeyKVN = DongleOut->ucCreditKeyKVN;//Credit Key KVN
	APIOut->ucCPUIssuerKeyKVN = DongleOut->ucCPUIssuerKeyKVN;//CPU Issuer Key KVN
	APIOut->ucTxnMode = DongleOut->ucTxnMode;//Txn Mode
	APIOut->ucTxnQuqlifier = DongleOut->ucTxnQuqlifier;//Txn Quqlifier
	APIOut->ucSignatureKeyKVN = DongleOut->ucSignatureKeyKVN;//Signature Key KVN
	memcpy(APIOut->ucCPUSAMID,DongleOut->ucCPUSAMID,sizeof(APIOut->ucCPUSAMID));//CPU SAM ID
	APIOut->ucHostAdminKVN = DongleOut->ucHostAdminKVN;//Host Admin KVN
	APIOut->ucPurseVersionNumber = DongleOut->ucPurseVersionNumber;//Purse Version Number
	memcpy(APIOut->ucTMLocationID,DongleIn->ucTMLocationID,sizeof(APIOut->ucTMLocationID));//TM Location ID
	memcpy(APIOut->ucCACrypto,DongleOut->ucTxnCrypto,8);//CACrypto前8碼
	memset(&APIOut->ucCACrypto[8],0x00,8);//CACrypto後8碼
	vdBuildCardAVRData(&APIOut->stCardAVRInfo_t,&DongleOut->stLastCreditTxnLogInfo_t,DongleOut->ucCardID,DongleOut->ucIssuerCode,DongleOut->ucCPUSPID,DongleOut->ucCPULocationID,DongleOut->ucPID,APIOut->ucLoyaltyCounter);//Card AVR Info
	vdBuildReaderAVRData(&APIOut->stReaderAVRInfo_t,&DongleOut->stReaderAVRInfo_t);//Reader AVR Info
	//memcpy(&APIOut->stReaderAVRInfo_t,&DongleOut->stReaderAVRInfo_t,sizeof(APIOut->stReaderAVRInfo_t));//Reader AVR Info
	APIOut->ucCardIDLen = DongleOut->ucCardIDLen;//Card ID Len

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	memcpy(stStore_DataInfo_t.ucTMSerialNumber,DongleOut->ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));
	vdSaveReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));

	return(inTMOutLen);
}

int inBuildAuthAutoloadEnableData2(int inTxnType,AuthAutoloadEnable2_TM_Out *APIOut,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthAutoloadEnable2_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.anCardID,sizeof(APIOut->stSTMC_t.anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stSTMC_t.anDeviceID,sizeof(APIOut->stSTMC_t.anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(TxnReqOut->ucCPUDeviceID,APIOut->stSTMC_t.anCPUDeviceID,sizeof(APIOut->stSTMC_t.anCPUDeviceID),LEVEL2);//n_TXN Device ID
	vdCountEVBefore(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEVBeforeTxn,sizeof(APIOut->stSTMC_t.anEVBeforeTxn),TxnReqOut->ucMsgType);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.anTxnSN,sizeof(APIOut->stSTMC_t.anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),APIOut->stSTMC_t.anTxnAmt,sizeof(APIOut->stSTMC_t.anTxnAmt),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEV,sizeof(APIOut->stSTMC_t.anEV),' ',10);//n_EV
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->stSTMC_t.anProcessignCode);//Processing Code
	fnUnPack(&TxnReqOut->ucMsgType,sizeof(TxnReqOut->ucMsgType),APIOut->stSTMC_t.unMsgType);//Msg Type
	fnUnPack(&TxnReqOut->ucSubType,sizeof(TxnReqOut->ucSubType),APIOut->stSTMC_t.unSubType);//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stSTMC_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucSPID,sizeof(TxnReqOut->ucSPID),APIOut->stSTMC_t.unSPID);//SP ID
	fnUnPack(DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime),APIOut->stSTMC_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stSTMC_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stSTMC_t.unPersonalProfile);//Personal Profile
	fnUnPack(&TxnReqOut->ucLocationID,sizeof(TxnReqOut->ucLocationID),APIOut->stSTMC_t.unLocationID);//Location ID
	fnUnPack(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.unCardID);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stSTMC_t.unIssuerCode);//Issuer Code
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->stSTMC_t.unBankCode);//Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->stSTMC_t.unLoyaltyCounter);//Loyalty Counter
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		fnUnPack(DongleOut->ucMAC_HCrypto,10,APIOut->stSTMC_t.unMAC);//MAC
	else
		memset(APIOut->stSTMC_t.unMAC,0x30,sizeof(APIOut->stSTMC_t.unMAC));//MAC
	fnUnPack(TxnReqOut->ucExpiryDate,sizeof(TxnReqOut->ucExpiryDate),APIOut->stSTMC_t.unOrgExpiryDate);//Org Expiry Date
	fnUnPack(DongleIn->ucExpiryDate,sizeof(DongleIn->ucExpiryDate),APIOut->stSTMC_t.unNewExpiryDate);//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stSTMC_t.unAreaCode);//Area Code
	fnUnPack(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),APIOut->stSTMC_t.unTxnAmt);//Txn Amt
	fnUnPack(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.unEV);//EV
	fnUnPack(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.unTxnSN);//Txn SN
	fnUnPack(TxnReqOut->ucCPUDeviceID,sizeof(TxnReqOut->ucCPUDeviceID),APIOut->stSTMC_t.unCPUDeviceID);//CPU Device ID
	fnUnPack(TxnReqOut->ucCPUSPID,sizeof(TxnReqOut->ucCPUSPID),APIOut->stSTMC_t.unCPUSPID);//CPU SP ID
	fnUnPack(TxnReqOut->ucCPULocationID,sizeof(TxnReqOut->ucCPULocationID),APIOut->stSTMC_t.unCPULocationID);//CPU Location ID
	fnUnPack(TxnReqOut->ucPID,sizeof(TxnReqOut->ucPID),APIOut->stSTMC_t.unPID);//Purse ID
	fnUnPack(TxnReqOut->ucCTC,sizeof(TxnReqOut->ucCTC),APIOut->stSTMC_t.unCTC);//CTC
	fnUnPack(TxnReqOut->ucProfileExpiryDate,sizeof(TxnReqOut->ucProfileExpiryDate),APIOut->stSTMC_t.unOrgProfileExpiryDate);//Org Profile Expiry Date
	fnUnPack(DongleIn->ucProfileExpiryDate,sizeof(DongleIn->ucProfileExpiryDate),APIOut->stSTMC_t.unNewProfileExpiryDate);//New Profile Expiry Date
	fnUnPack(TxnReqOut->ucSubAreaCode,sizeof(TxnReqOut->ucSubAreaCode),APIOut->stSTMC_t.unSubAreaCode);//Sub Area Code
	fnUnPack(TxnReqOut->ucTxnSN,sizeof(TxnReqOut->ucTxnSN),APIOut->stSTMC_t.unTxnSNBeforeTxn);//Txn SN Before Txn
	fnUnPack(TxnReqOut->ucEV,sizeof(TxnReqOut->ucEV),APIOut->stSTMC_t.unEVBeforeTxn);//EV Before Txn
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stSTMC_t.unDeposit);//Deposit
	fnUnPack(&TxnReqOut->ucTxnMode,sizeof(TxnReqOut->ucTxnMode),APIOut->stSTMC_t.unTxnMode);//Txn Mode
	fnUnPack(&TxnReqOut->ucTxnQuqlifier,sizeof(TxnReqOut->ucTxnQuqlifier),APIOut->stSTMC_t.unTxnQuqlifier);//Txn Quqlifier
	fnUnPack(&TxnReqOut->ucSignatureKeyKVN,sizeof(TxnReqOut->ucSignatureKeyKVN),APIOut->stSTMC_t.unSignatureKeyKVN);//Signature Key KVN
	fnUnPack(DongleOut->ucSignature,sizeof(DongleOut->ucSignature),APIOut->stSTMC_t.unSignature);//Signature
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
		fnUnPack(&DongleOut->ucMAC_HCrypto[0],1,APIOut->stSTMC_t.unHashType);//Hash Type
	else
		memset(APIOut->stSTMC_t.unHashType,0x30,sizeof(APIOut->stSTMC_t.unHashType));
	fnUnPack(DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),APIOut->stSTMC_t.unCPUSAMID);//SAM ID
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
	{
		fnUnPack(&DongleOut->ucMAC_HCrypto[1],1,APIOut->stSTMC_t.unHostAdminKVN);//Host Admin KVN
		fnUnPack(&DongleOut->ucMAC_HCrypto[2],16,APIOut->stSTMC_t.unCPUMAC);//MAC
	}
	else
	{
		memset(APIOut->stSTMC_t.unHostAdminKVN,0x30,sizeof(APIOut->stSTMC_t.unHostAdminKVN));
		memset(APIOut->stSTMC_t.unCPUMAC,0x30,sizeof(APIOut->stSTMC_t.unCPUMAC));//MAC
	}
	fnUnPack(&TxnReqOut->ucPurseVersionNumber,sizeof(TxnReqOut->ucPurseVersionNumber),APIOut->stSTMC_t.unPurseVersionNumber);//Purse Version Number
	fnUnPack(&TxnReqOut->ucCardIDLen,sizeof(TxnReqOut->ucCardIDLen),APIOut->stSTMC_t.unCardIDLen);//Card ID Len
	memcpy(APIOut->stSTMC_t.ucTMLocationID,stStore_DataInfo_t.ucTMLocationID,sizeof(stStore_DataInfo_t.ucTMLocationID));//TM Location ID
	memcpy(APIOut->stSTMC_t.ucTMID,stStore_DataInfo_t.ucTMID,sizeof(stStore_DataInfo_t.ucTMID));//TM ID
	fnLongToUnix(APIOut->stSTMC_t.ucTMTxnDateTime,(unsigned long *)DongleOut->ucTxnDateTime,14);//TM Txn Date Time
	memcpy(APIOut->stSTMC_t.ucTMSerialNumber,stStore_DataInfo_t.ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->stSTMC_t.ucTMAgentNumber,stStore_DataInfo_t.ucTMAgentNumber,sizeof(stStore_DataInfo_t.ucTMAgentNumber));//TM Agent Number
	//帳務資料結束
	//Congirm資料開始
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",79);//Data Len
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	APIOut->ucMsgType = TxnReqOut->ucMsgType;//Msg Type
	APIOut->ucSubType = TxnReqOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,TxnReqOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	memcpy(APIOut->ucTxnDateTime,DongleOut->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->ucMAC,DongleOut->ucMAC_HCrypto,sizeof(APIOut->ucMAC));//MAC
	else
		memset(APIOut->ucMAC,0x00,sizeof(APIOut->ucMAC));//MAC
	memcpy(APIOut->ucConfirmCode,DongleOut->ucConfirmCode,sizeof(APIOut->ucConfirmCode));//Confirm Code
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->ucCTAC,&DongleOut->ucMAC_HCrypto[10],sizeof(APIOut->ucMAC));//CTAC
	else
		memset(APIOut->ucCTAC,0x00,sizeof(APIOut->ucMAC));//CTAC
	APIOut->ucAutoLoadFlag = 0x01;//AutoLoad Flag
	memcpy(APIOut->ucAutoLoadAmt_2,TxnReqOut->ucAutoLoadAmt,sizeof(APIOut->ucAutoLoadAmt_2));//AutoLoad Amt
	memcpy(APIOut->ucCardID,TxnReqOut->ucCardID,sizeof(APIOut->ucCardID));//Card ID
	memcpy(APIOut->ucEV,DongleOut->ucEV,sizeof(APIOut->ucEV));//EV
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN,sizeof(APIOut->ucTxnSN));//Txn SN
	memcpy(APIOut->ucCPUDeviceID,TxnReqOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucPID,TxnReqOut->ucPID,sizeof(APIOut->ucPID));//Purse ID
	memcpy(APIOut->ucSignature,DongleOut->ucSignature,sizeof(APIOut->ucSignature));//Signature
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
	{
		APIOut->ucHashType = DongleOut->ucMAC_HCrypto[0];//Hash Type
		APIOut->ucHostAdminKVN = DongleOut->ucMAC_HCrypto[1];//Host Admin KVN
		memcpy(APIOut->ucCPUMAC,&DongleOut->ucMAC_HCrypto[2],sizeof(APIOut->ucCPUMAC));//CPU MAC
	}
	else
	{
		APIOut->ucHashType = 0x00;
		APIOut->ucHostAdminKVN = 0x00;
		memset(APIOut->ucCPUMAC,0x00,sizeof(APIOut->ucCPUMAC));//CPU MAC
	}

	return(inTMOutLen);
}

int inBuildAuthAutoloadData(int inTxnType,AuthAutoload_TM_Out *APIOut,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut)
{
int inTMOutLen;
Store_Data stStore_DataInfo_t;

	vdLoadReqData(TXN_DATA_FIELD,(BYTE *)&stStore_DataInfo_t,sizeof(Store_Data));
	inTMOutLen = sizeof(AuthAutoload_TM_Out);
	memset(APIOut,0x00,inTMOutLen);
	vdUIntToAsc(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.anCardID,sizeof(APIOut->stSTMC_t.anCardID),' ',10);//n_Card Physical ID
	fnBINTODEVASC(TxnReqOut->ucDeviceID,APIOut->stSTMC_t.anDeviceID,sizeof(APIOut->stSTMC_t.anDeviceID),MIFARE);//n_TXN Device ID
	fnBINTODEVASC(TxnReqOut->ucCPUDeviceID,APIOut->stSTMC_t.anCPUDeviceID,sizeof(APIOut->stSTMC_t.anCPUDeviceID),LEVEL2);//n_TXN Device ID
	vdCountEVBefore(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEVBeforeTxn,sizeof(APIOut->stSTMC_t.anEVBeforeTxn),TxnReqOut->ucMsgType);//n_EV Before TXN
	vdUIntToAsc(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.anTxnSN,sizeof(APIOut->stSTMC_t.anTxnSN),' ',10);//n_TXN SNum
	vdUIntToAsc(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),APIOut->stSTMC_t.anTxnAmt,sizeof(APIOut->stSTMC_t.anTxnAmt),' ',10);//n_TXN AMT
	vdIntToAsc(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.anEV,sizeof(APIOut->stSTMC_t.anEV),' ',10);//n_EV
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->stSTMC_t.anProcessignCode);//Processing Code
	fnUnPack(&TxnReqOut->ucMsgType,sizeof(TxnReqOut->ucMsgType),APIOut->stSTMC_t.unMsgType);//Msg Type
	fnUnPack(&TxnReqOut->ucSubType,sizeof(TxnReqOut->ucSubType),APIOut->stSTMC_t.unSubType);//Sub Type
	fnUnPack(TxnReqOut->ucDeviceID,sizeof(TxnReqOut->ucDeviceID),APIOut->stSTMC_t.unDeviceID);//Device ID
	fnUnPack(&TxnReqOut->ucSPID,sizeof(TxnReqOut->ucSPID),APIOut->stSTMC_t.unSPID);//SP ID
	fnUnPack(DongleOut->ucTxnDateTime,sizeof(DongleOut->ucTxnDateTime),APIOut->stSTMC_t.unTxnDateTime);//Txn Date Time
	fnUnPack(&TxnReqOut->ucCardType,sizeof(TxnReqOut->ucCardType),APIOut->stSTMC_t.unCardType);//Card Type
	fnUnPack(&TxnReqOut->ucPersonalProfile,sizeof(TxnReqOut->ucPersonalProfile),APIOut->stSTMC_t.unPersonalProfile);//Personal Profile
	fnUnPack(&TxnReqOut->ucLocationID,sizeof(TxnReqOut->ucLocationID),APIOut->stSTMC_t.unLocationID);//Location ID
	fnUnPack(TxnReqOut->ucCardID,sizeof(TxnReqOut->ucCardID),APIOut->stSTMC_t.unCardID);//CPU Card ID
	fnUnPack(&TxnReqOut->ucIssuerCode,sizeof(TxnReqOut->ucIssuerCode),APIOut->stSTMC_t.unIssuerCode);//Issuer Code
	fnUnPack(&TxnReqOut->ucBankCode,sizeof(TxnReqOut->ucBankCode),APIOut->stSTMC_t.unBankCode);//Bank Code
	fnUnPack(TxnReqOut->ucLoyaltyCounter,sizeof(TxnReqOut->ucLoyaltyCounter),APIOut->stSTMC_t.unLoyaltyCounter);//Loyalty Counter
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		fnUnPack(DongleOut->ucMAC_HCrypto,10,APIOut->stSTMC_t.unMAC);//MAC
	else
		memset(APIOut->stSTMC_t.unMAC,0x30,sizeof(APIOut->stSTMC_t.unMAC));//MAC
	fnUnPack(TxnReqOut->ucExpiryDate,sizeof(TxnReqOut->ucExpiryDate),APIOut->stSTMC_t.unOrgExpiryDate);//Org Expiry Date
	fnUnPack(DongleIn->ucExpiryDate,sizeof(DongleIn->ucExpiryDate),APIOut->stSTMC_t.unNewExpiryDate);//New Expiry Date
	fnUnPack(&TxnReqOut->ucAreaCode,sizeof(TxnReqOut->ucAreaCode),APIOut->stSTMC_t.unAreaCode);//Area Code
	fnUnPack(TxnReqOut->ucTxnAmt,sizeof(TxnReqOut->ucTxnAmt),APIOut->stSTMC_t.unTxnAmt);//Txn Amt
	fnUnPack(DongleOut->ucEV,sizeof(DongleOut->ucEV),APIOut->stSTMC_t.unEV);//EV
	fnUnPack(DongleOut->ucTxnSN,sizeof(DongleOut->ucTxnSN),APIOut->stSTMC_t.unTxnSN);//Txn SN
	fnUnPack(TxnReqOut->ucCPUDeviceID,sizeof(TxnReqOut->ucCPUDeviceID),APIOut->stSTMC_t.unCPUDeviceID);//CPU Device ID
	fnUnPack(TxnReqOut->ucCPUSPID,sizeof(TxnReqOut->ucCPUSPID),APIOut->stSTMC_t.unCPUSPID);//CPU SP ID
	fnUnPack(TxnReqOut->ucCPULocationID,sizeof(TxnReqOut->ucCPULocationID),APIOut->stSTMC_t.unCPULocationID);//CPU Location ID
	fnUnPack(TxnReqOut->ucPID,sizeof(TxnReqOut->ucPID),APIOut->stSTMC_t.unPID);//Purse ID
	fnUnPack(TxnReqOut->ucCTC,sizeof(TxnReqOut->ucCTC),APIOut->stSTMC_t.unCTC);//CTC
	fnUnPack(TxnReqOut->ucProfileExpiryDate,sizeof(TxnReqOut->ucProfileExpiryDate),APIOut->stSTMC_t.unOrgProfileExpiryDate);//Org Profile Expiry Date
	fnUnPack(DongleIn->ucProfileExpiryDate,sizeof(DongleIn->ucProfileExpiryDate),APIOut->stSTMC_t.unNewProfileExpiryDate);//New Profile Expiry Date
	fnUnPack(TxnReqOut->ucSubAreaCode,sizeof(TxnReqOut->ucSubAreaCode),APIOut->stSTMC_t.unSubAreaCode);//Sub Area Code
	fnUnPack(TxnReqOut->ucTxnSN,sizeof(TxnReqOut->ucTxnSN),APIOut->stSTMC_t.unTxnSNBeforeTxn);//Txn SN Before Txn
	fnUnPack(TxnReqOut->ucEV,sizeof(TxnReqOut->ucEV),APIOut->stSTMC_t.unEVBeforeTxn);//EV Before Txn
	fnUnPack(TxnReqOut->ucDeposit,sizeof(TxnReqOut->ucDeposit),APIOut->stSTMC_t.unDeposit);//Deposit
	fnUnPack(&TxnReqOut->ucTxnMode,sizeof(TxnReqOut->ucTxnMode),APIOut->stSTMC_t.unTxnMode);//Txn Mode
	fnUnPack(&TxnReqOut->ucTxnQuqlifier,sizeof(TxnReqOut->ucTxnQuqlifier),APIOut->stSTMC_t.unTxnQuqlifier);//Txn Quqlifier
	fnUnPack(&TxnReqOut->ucSignatureKeyKVN,sizeof(TxnReqOut->ucSignatureKeyKVN),APIOut->stSTMC_t.unSignatureKeyKVN);//Signature Key KVN
	fnUnPack(DongleOut->ucSignature,sizeof(DongleOut->ucSignature),APIOut->stSTMC_t.unSignature);//Signature
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
		fnUnPack(&DongleOut->ucMAC_HCrypto[0],1,APIOut->stSTMC_t.unHashType);//Hash Type
	else
		memset(APIOut->stSTMC_t.unHashType,0x30,sizeof(APIOut->stSTMC_t.unHashType));
	fnUnPack(DongleOut->ucCPUSAMID,sizeof(DongleOut->ucCPUSAMID),APIOut->stSTMC_t.unCPUSAMID);//SAM ID
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
	{
		fnUnPack(&DongleOut->ucMAC_HCrypto[1],1,APIOut->stSTMC_t.unHostAdminKVN);//Host Admin KVN
		fnUnPack(&DongleOut->ucMAC_HCrypto[2],16,APIOut->stSTMC_t.unCPUMAC);//MAC
	}
	else
	{
		memset(APIOut->stSTMC_t.unHostAdminKVN,0x30,sizeof(APIOut->stSTMC_t.unHostAdminKVN));
		memset(APIOut->stSTMC_t.unCPUMAC,0x30,sizeof(APIOut->stSTMC_t.unCPUMAC));//MAC
	}
	fnUnPack(&TxnReqOut->ucPurseVersionNumber,sizeof(TxnReqOut->ucPurseVersionNumber),APIOut->stSTMC_t.unPurseVersionNumber);//Purse Version Number
	fnUnPack(&TxnReqOut->ucCardIDLen,sizeof(TxnReqOut->ucCardIDLen),APIOut->stSTMC_t.unCardIDLen);//Card ID Len
	memcpy(APIOut->stSTMC_t.ucTMLocationID,stStore_DataInfo_t.ucTMLocationID,sizeof(stStore_DataInfo_t.ucTMLocationID));//TM Location ID
	memcpy(APIOut->stSTMC_t.ucTMID,stStore_DataInfo_t.ucTMID,sizeof(stStore_DataInfo_t.ucTMID));//TM ID
	fnLongToUnix(APIOut->stSTMC_t.ucTMTxnDateTime,(unsigned long *)DongleOut->ucTxnDateTime,14);//TM Txn Date Time
	memcpy(APIOut->stSTMC_t.ucTMSerialNumber,stStore_DataInfo_t.ucTMSerialNumber,sizeof(stStore_DataInfo_t.ucTMSerialNumber));//TM Serial Number
	memcpy(APIOut->stSTMC_t.ucTMAgentNumber,stStore_DataInfo_t.ucTMAgentNumber,sizeof(stStore_DataInfo_t.ucTMAgentNumber));//TM Agent Number
	//帳務資料結束
	//Congirm資料開始
	vdBuildMessageType(inTxnType,APIOut->ucMessageType);//Message Type ID
	sprintf((char *)APIOut->ucDataLen,"%03d",79);//Data Len
	vdBuildProcessingCode(inTxnType,TxnReqOut->ucMsgType,TxnReqOut->ucSubType,TxnReqOut->ucPersonalProfile,APIOut->ucProcessignCode);//Processing Code
	APIOut->ucMsgType = TxnReqOut->ucMsgType;//Msg Type
	APIOut->ucSubType = TxnReqOut->ucSubType;//Sub Type
	memcpy(APIOut->ucDeviceID,TxnReqOut->ucDeviceID,sizeof(APIOut->ucDeviceID));//Device ID
	memcpy(APIOut->ucTxnDateTime,DongleOut->ucTxnDateTime,sizeof(APIOut->ucTxnDateTime));//Txn Date Time
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->ucMAC,DongleOut->ucMAC_HCrypto,sizeof(APIOut->ucMAC));//MAC
	else
		memset(APIOut->ucMAC,0x00,sizeof(APIOut->ucMAC));//MAC
	memcpy(APIOut->ucConfirmCode,DongleOut->ucConfirmCode,sizeof(APIOut->ucConfirmCode));//Confirm Code
	if(TxnReqOut->ucPurseVersionNumber == MIFARE)
		memcpy(APIOut->ucCTAC,&DongleOut->ucMAC_HCrypto[10],sizeof(APIOut->ucMAC));//CTAC
	else
		memset(APIOut->ucCTAC,0x00,sizeof(APIOut->ucMAC));//CTAC
	memcpy(APIOut->ucCardID,TxnReqOut->ucCardID,sizeof(APIOut->ucCardID));//Card ID
	memcpy(APIOut->ucTxnAmt,TxnReqOut->ucTxnAmt,sizeof(APIOut->ucTxnAmt));//Txn Amt
	memcpy(APIOut->ucEV,DongleOut->ucEV,sizeof(APIOut->ucEV));//EV
	memcpy(APIOut->ucTxnSN,DongleOut->ucTxnSN,sizeof(APIOut->ucTxnSN));//Txn SN
	memcpy(APIOut->ucCPUDeviceID,TxnReqOut->ucCPUDeviceID,sizeof(APIOut->ucCPUDeviceID));//CPU Device ID
	memcpy(APIOut->ucPID,TxnReqOut->ucPID,sizeof(APIOut->ucPID));//Purse ID
	memcpy(APIOut->ucSignature,DongleOut->ucSignature,sizeof(APIOut->ucSignature));//Signature
	if(TxnReqOut->ucPurseVersionNumber != MIFARE)
	{
		APIOut->ucHashType = DongleOut->ucMAC_HCrypto[0];//Hash Type
		APIOut->ucHostAdminKVN = DongleOut->ucMAC_HCrypto[1];//Host Admin KVN
		memcpy(APIOut->ucCPUMAC,&DongleOut->ucMAC_HCrypto[2],sizeof(APIOut->ucCPUMAC));//CPU MAC
	}
	else
	{
		APIOut->ucHashType = 0x00;
		APIOut->ucHostAdminKVN = 0x00;
		memset(APIOut->ucCPUMAC,0x00,sizeof(APIOut->ucCPUMAC));//CPU MAC
	}

	return(inTMOutLen);
}

