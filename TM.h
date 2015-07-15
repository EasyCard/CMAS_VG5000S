#ifndef __TM_H__
#define __TM_H__

#ifdef __cplusplus
	extern "C" {
#endif

#include "dongle.h"
#include "substruct.h"

/********************************Reset********************************/
typedef struct{
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucLocationID[3];
	BYTE ucCPULocationID[5];
	BYTE ucSPID[3];
	BYTE ucCPUSPID[8];
	BYTE ucSAMSlot[1];
}Reset_TM_In;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1
	BYTE ucProcessignCode[6];		//Field 2
	BYTE ucBLVersion[2];			//Field 6
	BYTE ucMsgType;				//Field 7
	BYTE ucSubType;				//Field 8
	BYTE ucDeviceID[4];			//Field 9
	BYTE ucSPID;				//Field 10
	BYTE ucTxnDateTime[4];			//Field 11
	BYTE ucTMID[2];				//Field 28
	BYTE ucTMTxnDateTime[14];		//Field 29
	BYTE ucTMSerialNumber[6];		//Field 30
	BYTE ucTMAgentNumber[4];		//Field 31
	BYTE ucSTAC[8];				//Field 33
	BYTE ucKeyVersion;			//Field 35
	BYTE ucSAMID[8];			//Field 36
	BYTE ucSAMSN[4];			//Field 37
	BYTE ucSAMCRN[8];			//Field 38
	BYTE ucReaderFWVersion[6];		//Field 39
	BYTE ucNetManagementWorkCode[3];	//Field 46
	TermHost_t stTermHostInfo_t;		//Field 50
	TermPara_t stTermParaInfo_t;		//Field 51
	BYTE ucCardID[7];			//Field 58
	BYTE ucTxnAmt[3];			//Field 59
	BYTE ucCPUDeviceID[6];			//Field 62
	BYTE ucCPUSPID[3];			//Field 63
	BYTE ucEVBeforeTxn[3];			//Field 71
	BYTE ucCPUSAMID[8];			//Field 79
	BYTE ucSTC[4];				//Field 80
	CPUSAMInfo_t stCPUSAMInfo_t;		//Field 81
	BYTE ucRSAM[8];				//Field 82
	BYTE ucRHOST[8];			//Field 83
	BYTE ucAuthCreditLimit[3];		//Field 84-1
	BYTE ucAuthCreditBalance[3];		//Field 84-2
	BYTE ucAuthCreditCumulative[3];		//Field 84-3
	BYTE ucAuthCancelCreditCumulative[3];	//Field 84-4
	BYTE ucSingleCreditTxnAmtLimit[3];	//Field 85
	BYTE ucTMLocationID[10];		//Field 90
	BYTE ucSATOKEN[16];			//Field 91
	LastSingOn_t stLastSignOnInfo_t;	//Field 93
	BYTE ucSAMSignOnControlFlag;		//Field 95
	BYTE ucHostSpecVersionNo;		//Field 96
	BYTE ucOneDayQuotaWrite;		//Field 97
	BYTE ucCPDReadFlag;			//Field 98
}Reset_TM_Out;
/********************************Reset********************************/

/*****************************SignOn***********************************/
typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucHTAC[8];				//Field 34	//8
	BYTE ucResponseCode[2];			//Field 43	//2
	BYTE ucNetManagementWorkCode[3];	//Field 46	//3
	TermHost_t stTermHostInfo_t;		//Field 50	//24
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucSTC[4];				//Field 80	//4
	BYTE ucHashType;			//Field 86	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucHATOKEN[16];			//Field 92	//16
	SAMParaSetting_t stSAMParaSettingInfo_t;//Field 94	//57
	BYTE ucSAMSignOnControlFlag;		//Field 95	//1
	BYTE ucOneDayQuotaWrite;		//Field 97	//1
	BYTE ucCPDReadFlag;			//Field 98	//1
	BYTE ucCPUEDC[3];			//Field 99	//3
}SignOn_TM_In;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 3	//6
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucConfirmCode[2];			//Field 47	//2
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucSTC[4];				//Field 80	//4
	BYTE ucCreditBalanceChangeFlag;		//Field 100	//1
	BYTE ucCACrypto[16];			//Field 101	//16
}SignOn_TM_Out;
/*****************************SignOn***********************************/

/*****************************SignOnQuery******************************/
typedef struct{
	BYTE anAuthCreditLimit[8];
	BYTE anAuthCreditBalance[8];
	BYTE anAuthCreditCumulative[8];
	BYTE anAuthCancelCreditCumulative[8];
	BYTE anCPDReadFlag;
	BYTE anOneDayQuotaWrite;
	BYTE anSAMSignOnControlFlag;
	BYTE anCheckEVFlag;
	BYTE anDeductLimitFlag;
	BYTE anOneDayQuotaFlag;
	BYTE anOneDayQuota[5];
	BYTE anOnceQuotaFlag;
	BYTE anOnceQuota[5];
	BYTE anCheckDeductFlag;
	BYTE anCheckDeductValue[5];
	BYTE anAddQuotaFlag;
	BYTE anAddQuota[8];
	BYTE anRemainderAddQuota[8];
	BYTE anCancelCreditQuota[8];
	BYTE anSPID[3];
	BYTE anCPUSPID[8];
	BYTE anLastTxnDateTime[14];
}SignOnQuery_TM_Out;
/*****************************SignOnQuery******************************/

/**************************ReadCardBasicData***************************/
typedef struct{
	BYTE ucLCDControlFlag;
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
}ReadCardBasicData_TM_In;

typedef struct{
	BYTE ucActivated;
	BYTE ucBlocked;
	BYTE ucRefunded;
	BYTE ucAutoLoad;
	BYTE ucCredit;
	BYTE ucMerchantUseFlag;
	BYTE anAutoLoadAmt[8];
	BYTE anPID[16];
	BYTE anCardID[17];
	BYTE anAreaCode[2];
	BYTE anSubAreaCode[4];
	BYTE anExpiryDate[14];
	BYTE anEV[8];
	BYTE anTxnSN[8];
	BYTE anCardType[2];
	BYTE anPersonalProfile[2];
	BYTE anProfileExpiryDate[14];
	BYTE anDeposit[8];
	BYTE anIssuerCode[2];
	BYTE anBankCode[2];
	BYTE anLoyaltyCounter[5];
	BYTE anCardOneDayQuota[8];
	BYTE anCardOneDayQuotaDate[8];
	BYTE anDebitTxnRecords[2];
	LastTxnRecored_t stLastCreditTxnRecoredInfo_t;//74
	LastTxnRecored_t stLastDebitTxnRecoredInfo_t;//74
}ReadCardBasicData_TM_Out;
/**************************ReadCardBasicData***************************/

/*****************************TxnReqOnline*****************************/
typedef struct{
	BYTE anMsgType[2];
	BYTE anSubType[2];
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE anTxnAmt[8];
	BYTE ucReadPurseFlag;
}TxnReqOnline_TM_In;

typedef struct{
	BYTE anCardID[17];
	BYTE anDeviceID[10];
	BYTE anCPUDeviceID[16];
	BYTE anEVBeforeTxn[8];
	BYTE anTxnSN[8];
	BYTE anTxnAmt[8];
	BYTE ucAutoLoad;
	BYTE anAutoLoadAmt[8];
}TxnReqOnline_TM_Out_1;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucSPID;				//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;			//Field 12	//1
	BYTE ucPersonalProfile;			//Field 13	//1
	BYTE ucIssuerCode;			//Field 15	//1
	BYTE ucLocationID;			//Field 19	//1
	BYTE ucBankCode;			//Field 20	//1
	BYTE ucLoyaltyCounter[2];		//Field 21	//2
	BYTE ucExpiryDate[4];			//Field 24	//4
	BYTE ucAreaCode;			//Field 26	//1
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucSTAC[8];				//Field 33	//8
	BYTE ucKeyVersion;			//Field 35	//1
	BYTE ucSAMID[8];			//Field 36	//8
	BYTE ucSAMSN[4];			//Field 37	//4
	BYTE ucSAMCRN[8];			//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucTxnAmt[3];			//Field 59	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucCPUSPID[3];			//Field 63	//3
	BYTE ucCPULocationID[2];		//Field 64	//2
	BYTE ucPID[8];				//Field 65	//8
	BYTE ucCTC[3];				//Field 66	//3
	BYTE ucProfileExpiryDate[4];		//Field 67	//4
	BYTE ucSubAreaCode[2];			//Field 69	//2
	BYTE ucTxnSN[3];			//Field 70	//3
	BYTE ucEV[3];				//Field 71	//3
	BYTE ucDeposit[3];			//Field 72	//3
	BYTE ucCPUAdminKeyKVN;			//Field 74-1	//1
	BYTE ucCreditKeyKVN;			//Field 74-2	//1
	BYTE ucCPUIssuerKeyKVN;			//Field 74-3	//1
	BYTE ucTxnMode;				//Field 75	//1
	BYTE ucTxnQuqlifier;			//Field 76	//1
	BYTE ucSignatureKeyKVN;			//Field 77	//1
	BYTE ucCPUSAMID[8];			//Field 79	//8
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucCACrypto[16];			//Field 101	//16
	CardAVR_t stCardAVRInfo_t;		//Field 104	//45
	ReaderAVRTM_t stReaderAVRInfo_t;	//Field 105	//83
	BYTE ucCardIDLen;			//Field 106	//1
}TxnReqOnline_TM_Out_2;//For 加值

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucSPID;				//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;			//Field 12	//1
	BYTE ucPersonalProfile;			//Field 13	//1
	BYTE ucIssuerCode;			//Field 15	//1
	BYTE ucLocationID;			//Field 19	//1
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucSTAC[8];				//Field 33	//8
	BYTE ucKeyVersion;			//Field 35	//1
	BYTE ucSAMID[8];			//Field 36	//8
	BYTE ucSAMSN[4];			//Field 37	//4
	BYTE ucSAMCRN[8];			//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucTxnAmt[3];			//Field 59	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucCPUSPID[3];			//Field 63	//3
	BYTE ucCPULocationID[2];		//Field 64	//2
	BYTE ucPID[8];				//Field 65	//8
	BYTE ucCTC[3];				//Field 66	//3
	BYTE ucSubAreaCode[2];			//Field 69	//2
	BYTE ucTxnSN[3];			//Field 70	//3
	BYTE ucEV[3];				//Field 71	//3
	BYTE ucDeposit[3];			//Field 72	//3
	BYTE ucCPUAdminKeyKVN;			//Field 74-1	//1
	BYTE ucCreditKeyKVN;			//Field 74-2	//1
	BYTE ucCPUIssuerKeyKVN;			//Field 74-3	//1
	BYTE ucTxnMode;				//Field 75	//1
	BYTE ucTxnQuqlifier;			//Field 76	//1
	BYTE ucCPUSAMID[8];			//Field 79	//8
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucCACrypto[16];			//Field 101	//16
	ReaderAVRTM_t stReaderAVRInfo_t;	//Field 105	//83
	BYTE ucCardIDLen;			//Field 106	//1
}CardSale_TM_Out;//For 售卡

typedef struct{
	BYTE ucDataLen[3];
	BYTE anCardID[17];
	BYTE anDeviceID[10];
	BYTE anCPUDeviceID[16];
	BYTE anEVBeforeTxn[8];
	BYTE anTxnSN[8];
	BYTE anTxnAmt[8];
	BYTE ucAutoLoad;
	BYTE anAutoLoadAmt[8];
}CancelTxn_TM_Out;//For 取消

/*****************************TxnReqOnline*****************************/

/*****************************AuthTxnOnline****************************/
typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucExpiryDate[4];			//Field 25	//4
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucHTAC[8];				//Field 34	//8
	BYTE ucResponseCode[2];			//Field 43	//2
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];				//Field 65	//8
	BYTE ucProfileExpiryDate[4];		//Field 68	//4
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucHATOKEN[16];			//Field 92	//16
	BYTE ucCardIDLen;			//Field 106	//1
	BYTE ucLCDControlFlag;
}AuthTxnOnline_TM_In;//For 加值

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucHTAC[8];				//Field 34	//8
	BYTE ucResponseCode[2];			//Field 43	//2
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];				//Field 65	//8
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucHATOKEN[16];			//Field 92	//16
	BYTE ucCardIDLen;			//Field 106	//1
	BYTE ucLCDControlFlag;
}AuthCardSale_TM_In;//For 售卡

typedef struct{
	STMC_t stSTMC_t;
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucMAC[10];				//Field 23	//10
	BYTE ucConfirmCode[2];			//Field 47	//2
	BYTE ucCTAC[8];				//Field 48	//8
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucEV[3];				//Field 60	//3
	BYTE ucTxnSN[3];			//Field 61	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];				//Field 65	//8
	BYTE ucSignature[16];			//Field 78	//16
	BYTE ucHashType;			//Field 86	//1
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucCPUMAC[16];			//Field 88	//16
}AuthTxnOnline_TM_Out;

typedef struct{
	STMC_t stSTMC_t;
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucMAC[10];				//Field 23	//10
	BYTE ucConfirmCode[2];			//Field 47	//2
	BYTE ucCTAC[8];				//Field 48	//8
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucEV[3];				//Field 60	//3
	BYTE ucTxnSN[3];			//Field 61	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];				//Field 65	//8
	BYTE ucHashType;			//Field 86	//1
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucCPUMAC[16];			//Field 88	//16
}AuthCardSale_TM_Out;
/*****************************AuthTxnOnline****************************/

/*****************************TxnReqOffline****************************/
typedef struct{
	BYTE anMsgType[2];
	BYTE anSubType[2];
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE anTxnAmt[8];
	BYTE ucReadPurseFlag;
}TxnReqOffline_TM_In;

typedef struct{
	BYTE anCardID[17];
	BYTE anDeviceID[10];
	BYTE anCPUDeviceID[16];
	BYTE anEVBeforeTxn[8];
	BYTE anTxnSN[8];
	BYTE anTxnAmt[8];
	BYTE ucAutoLoad;
	BYTE anAutoLoadAmt[8];
}TxnReqOffline_TM_Out_1;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucSPID;				//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;			//Field 12	//1
	BYTE ucPersonalProfile;			//Field 13	//1
	BYTE ucIssuerCode;			//Field 15	//1
	BYTE ucExpiryDate[4];			//Field 24	//4
	BYTE ucAreaCode;			//Field 26	//1
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucSTAC[8];				//Field 33	//8
	BYTE ucKeyVersion;			//Field 35	//1
	BYTE ucSAMID[8];			//Field 36	//8
	BYTE ucSAMSN[4];			//Field 37	//4
	BYTE ucSAMCRN[8];			//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucTxnAmt[3];			//Field 59	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucCPUSPID[3];			//Field 63	//3
	BYTE ucCPULocationID[2];		//Field 64	//2
	BYTE ucPID[8];				//Field 65	//8
	BYTE ucCTC[3];				//Field 66	//3
	BYTE ucProfileExpiryDate[4];		//Field 67	//4
	BYTE ucSubAreaCode[2];			//Field 69	//2
	BYTE ucTxnSN[3];			//Field 70	//3
	BYTE ucEV[3];				//Field 71	//3
	BYTE ucCPUAdminKeyKVN;			//Field 74-1	//1
	BYTE ucCreditKeyKVN;			//Field 74-2	//1
	BYTE ucCPUIssuerKeyKVN;			//Field 74-3	//1
	BYTE ucTxnMode;				//Field 75	//1
	BYTE ucTxnQuqlifier;			//Field 76	//1
	BYTE ucCPUSAMID[8];			//Field 79	//8
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucCACrypto[16];			//Field 101	//16
	BYTE ucCardOneDayQuota[3];		//Field 103-1	//3
	BYTE ucCardOneDayQuotaDate[2];		//Field 103-1	//2
	CardAVR_t stCardAVRInfo_t;		//Field 104	//45
	BYTE ucCardIDLen;			//Field 106	//1
}TxnReqOffline_TM_Out_2;
/*****************************TxnReqOffline****************************/

/*****************************AuthTxnOffline***************************/
typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucHTAC[8];				//Field 34	//8
	BYTE ucResponseCode[2];			//Field 43	//2
	BYTE ucCardID[7];			//Field 58	//7
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];				//Field 65	//8
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucHVCrypto[16];			//Field 102	//16
	BYTE ucCardIDLen;			//Field 106	//1
	BYTE ucLCDControlFlag;
}AuthTxnOffline_TM_In;

typedef struct{
	STMC_t stSTMC_t;
	//加值重送資料開始
	BYTE unVARMsgType[2];
	BYTE unVARPurseVersionNumber[2];
	BYTE unVARTxnSN[6];
	BYTE unVARTxnDateTime[8];
	BYTE unVARSubType[2];
	BYTE unVARTxnAmt[6];
	BYTE unVAREV[6];
	BYTE unVARCardID[14];
	BYTE unVARIssuerCode[2];
	BYTE unVARCPUSPID[6];
	BYTE unVARCPULocationID[4];
	BYTE unVARPID[16];
	BYTE unVARCPUDeviceID[12];
	BYTE unVARLoyaltyCounter[4];
	BYTE unVARPersonalProfile[2];
	BYTE unVARBankCode[2];
	BYTE unVARCardIDLen[2];
	BYTE unVAR2DeviceID[8];
	BYTE unVAR2SPID[2];
	BYTE unVAR2LocationID[2];
	BYTE unVAR2CPUDeviceID[12];
	BYTE unVAR2CPUSPID[6];
	BYTE unVAR2CPULocationID[4];
}AuthTxnOffline_TM_Out;
/*****************************AuthTxnOffline***************************/

/******************************LockCard 1******************************/
typedef struct{
	BYTE ucTMTxnDateTime[14];
	BYTE ucCardID_4[4];
}LockCard_TM_In_1;

typedef struct{
	BYTE unMsgType[2];
	BYTE unSubType[2];
	BYTE unDeviceID[8];
	BYTE unSPID[2];
	BYTE unTxnDateTime[8];
	BYTE unCardType[2];
	BYTE unPersonalProfile[2];
	BYTE unCardID_8[8];
	BYTE unIssuerCode[2];
	BYTE unLocationID[2];
	BYTE unLockReason[2];
}LockCard_TM_Out_1;
/******************************LockCard 1******************************/

/******************************LockCard 2******************************/
typedef struct{
	BYTE ucCardID[7];
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
}LockCard_TM_In_2;

typedef struct{
	BYTE unPurseVersionNumber[2];//0	//0		//1
	BYTE unMsgType[2];           //1    //1 	//3
	BYTE unSubType[2];           //2    //2 	//5
	BYTE unDeviceID[8];          //3    //3 	//7
	BYTE unSPID[2];              //7    //7 	//15
	BYTE unTxnDateTime[8];       //8    //8 	//17
	BYTE unCardID[14];           //12   //12	//25
	BYTE unIssuerCode[2];        //19   //19	//39
	BYTE unLocationID[2];        //20   //20	//41
	BYTE unCardIDLen[2];         //21   //21	//43
	BYTE unCPUDeviceID[12];      //22   //22	//45
	BYTE unCPUSPID[6];           //28   //28	//57
	BYTE unCPULocationID[4];     //31   //31	//63
	BYTE unCardType[2];          //33   //33	//67
	BYTE unPersonalProfile[2];   //34   //34	//69
	BYTE unPID[16];              //35   //35	//71
	BYTE unCTC[6];               //43   //43	//87
	BYTE unLockReason[2];        //46   //46	//93
	BYTE unBLCFileName[20];      //47   //47	//95
	BYTE unBLCIDFlag;            //57   //67	//115
	BYTE unTMLocationID[10];     //58   //68	//116
	BYTE unTMID[2];              //63   //78	//126
	BYTE unRFU[8];               //64   //80	//128
	BYTE unEV[6];                //68   //88	//136
	BYTE unCPUEV[6];             //71   //91	//142
	BYTE unMSettingPar[2];       //74   //94	//148
	BYTE unCSettingPar[2];       //75   //95	//150
	BYTE unTxnSN[6];             //76   //96	//152
	BYTE unVARTxnSN[6];          //79   //99	//158
	BYTE unVARTxnDateTime[8];    //82   //102	//164
	BYTE unVARSubType[2];        //86   //106	//172
	BYTE unVARTxnAmt[6];         //87   //107	//174
	BYTE unVAREV[6];             //90   //110	//180
	BYTE unVARDeviceID[12];      //93   //113	//186
}LockCard_TM_Out_2;				 //99   //119	//198
/******************************LockCard 2******************************/

/***************************ReadDongleDeduct***************************/
typedef struct{
	BYTE anLogSeqNo[5];
}ReadDongleDeduct_TM_In;

typedef struct{
	STMC_t stSTMC_t;
	//加值重送資料開始
	BYTE unVARMsgType[2];
	BYTE unVARPurseVersionNumber[2];
	BYTE unVARTxnSN[6];
	BYTE unVARTxnDateTime[8];
	BYTE unVARSubType[2];
	BYTE unVARTxnAmt[6];
	BYTE unVAREV[6];
	BYTE unVARCardID[14];
	BYTE unVARIssuerCode[2];
	BYTE unVARCPUSPID[6];
	BYTE unVARCPULocationID[4];
	BYTE unVARPID[16];
	BYTE unVARCPUDeviceID[12];
	BYTE unVARLoyaltyCounter[4];
	BYTE unVARPersonalProfile[2];
	BYTE unVARBankCode[2];
	BYTE unVARCardIDLen[2];
	BYTE unVAR2DeviceID[8];
	BYTE unVAR2SPID[2];
	BYTE unVAR2LocationID[2];
	BYTE unVAR2CPUDeviceID[12];
	BYTE unVAR2CPUSPID[6];
	BYTE unVAR2CPULocationID[4];
}ReadDongleDeduct_TM_Out;
/***************************ReadDongleDeduct***************************/

/********************************SetValue******************************/
typedef struct{
	BYTE anMsgType[2];
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
}SetValue_TM_In;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucCommandCode[2];			//Field 3	//2
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucSPID;				//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;			//Field 12	//1
	BYTE ucPersonalProfile;			//Field 13	//1
	BYTE ucCardID_4[4];			//Field 14	//4
	BYTE ucIssuerCode;			//Field 15	//1
	BYTE ucTxnAmt_2[2];			//Field 17	//2
	BYTE ucExpiryDate[4];			//Field 24	//4
	BYTE ucAreaCode;			//Field 26	//1
	BYTE ucTMLocationID_6[6];		//Field 27	//6
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucEV_2[2];				//Field 32	//2
	BYTE ucSTAC[8];				//Field 33	//8
	BYTE ucKeyVersion;			//Field 35	//1
	BYTE ucSAMID[8];			//Field 36	//8
	BYTE ucSAMSN[4];			//Field 37	//4
	BYTE ucSAMCRN[8];			//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
}SetValue_TM_Out;
/********************************SetValue******************************/

/******************************AuthSetValue****************************/
typedef struct{
	BYTE ucExpiryDate[4];			//Field 25	//4
	BYTE ucHTAC[8];				//Field 34	//8
}AuthSetValue_TM_In;

typedef struct{
	BYTE anCardID_10[10];
	BYTE anDeviceID[10];
	BYTE anEVBeforeTxn_5[5];
	BYTE anOrgExpiryDate[8];
	BYTE anNewExpiryDate[8];
	BYTE anProcessignCode[6];
	BYTE unMsgType[2];
	BYTE unSubType[2];
	BYTE unDeviceID[8];
	BYTE unTxnDateTime[8];
	BYTE unCardType[2];
	BYTE unPersonalProfile[2];
	BYTE unCardID_8[8];
	BYTE unNewExpiryDate[8];
}AuthSetValue_TM_Out;
/******************************AuthSetValue****************************/

/********************************TxRefund******************************/
typedef struct{
	BYTE anMsgType[2];
	BYTE anSubType[2];
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE anTxnAmt_5[5];
	BYTE ucTMTxnDateTime2[14];
	BYTE ucTMSerialNumber2[6];
}TxRefund_TM_In;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucCommandCode[2];			//Field 3	//2
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucSPID;				//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;			//Field 12	//1
	BYTE ucPersonalProfile;			//Field 13	//1
	BYTE ucCardID_4[4];			//Field 14	//4
	BYTE ucIssuerCode;			//Field 15	//1
	BYTE ucTxnAmt_2[2];			//Field 17	//2
	BYTE ucLocationID;			//Field 19	//1
	BYTE ucBankCode;			//Field 20	//1
	BYTE ucLoyaltyCounter[2];		//Field 21	//2
	BYTE ucDeposit[2];			//Field 22	//2
	BYTE ucExpiryDate[4];			//Field 24	//4
	BYTE ucAreaCode;			//Field 26	//1
	BYTE ucTMLocationID_6[6];		//Field 27	//6
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucEV_2[2];				//Field 32	//2
	BYTE ucSTAC[8];				//Field 33	//8
	BYTE ucKeyVersion;			//Field 35	//1
	BYTE ucSAMID[8];			//Field 36	//8
	BYTE ucSAMSN[4];			//Field 37	//4
	BYTE ucSAMCRN[8];			//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
	BYTE ucCAVRMsgType;			//Field 40-1	//1
	BYTE ucCAVRTxnSNLSB;                    //Field 40-2    //1
	BYTE ucCAVRTxnDateTime[4];              //Field 40-3    //4
	BYTE ucCAVRSubType;                     //Field 40-4    //1
	BYTE ucCAVRTxnAmt[2];                   //Field 40-5    //2
	BYTE ucCAVREV[2];                       //Field 40-6    //2
	BYTE ucCAVRCardID[4];                   //Field 40-7    //4
	BYTE ucCAVRIssuerCode;                  //Field 40-8    //1
	BYTE ucCAVRSPID;                        //Field 40-9    //1
	BYTE ucCAVRLocationID;                  //Field 40-10   //1
	BYTE ucCAVRDeviceID[4];                 //Field 40-11   //4
	BYTE ucCAVRBankCode;                    //Field 40-12   //1
	BYTE ucCAVRLoyaltyCounter[2];           //Field 40-13   //2
	ReaderAVR_t stReaderAVR_t;		//Field 41	//38
}TxRefund_TM_Out;
/********************************TxRefund******************************/

/******************************AuthTxRefund****************************/
typedef struct{
	BYTE ucRFU4[4];
	BYTE ucHTAC[8];
	BYTE ucRFU2[2];
	BYTE ucLCDControlFlag;
}AuthTxRefund_TM_In;

typedef struct{
	//餘轉退卡交易
	SETM_t stTxRefundSETM_t;
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucCommandCode[2];			//Field 3	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardID_4[4];			//Field 14	//4
	BYTE ucTxnSN_2[2];			//Field 16	//2
	BYTE ucEV_2[2];				//Field 18	//2
	BYTE ucMAC[10];				//Field 23	//10
	BYTE ucConfirmCode[2];			//Field 47	//2
	BYTE ucCTAC[8];				//Field 48	//8
	//餘轉扣款交易
	SETM_t stTxDeductSETM_t;
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	//加值重送資料開始
	BYTE unVARSPID[2];
	BYTE unVARLocationID[2];
	BYTE unVARMsgType[2];
	BYTE unVARTxnSNLSB[2];
	BYTE unVARTxnDateTime[8];
	BYTE unVARSubType[2];
	BYTE unVARTxnAmt_4[4];
	BYTE unVAREV_4[4];
	BYTE unVARCardID_8[8];
	BYTE unVARIssuerCode[2];
	BYTE unVAR2SPID[2];
	BYTE unVAR2LocationID[2];
	BYTE unVAR2DeviceID[8];
	BYTE unVARBankCode[2];
	BYTE unVARLoyaltyCounter[4];
}AuthTxRefund_TM_Out;
/******************************AuthTxRefund****************************/

/********************************AddValue******************************/
typedef struct{
	BYTE anMsgType[2];
	BYTE anSubType[2];
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE anTxnAmt_5[5];
}AddValue_TM_In;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucCommandCode[2];			//Field 3	//2
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucSPID;				//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;			//Field 12	//1
	BYTE ucPersonalProfile;			//Field 13	//1
	BYTE ucCardID_4[4];			//Field 14	//4
	BYTE ucIssuerCode;			//Field 15	//1
	BYTE ucTxnAmt_2[2];			//Field 17	//2
	BYTE ucLocationID;			//Field 19	//1
	BYTE ucBankCode;			//Field 20	//1
	BYTE ucLoyaltyCounter[2];		//Field 21	//2
	BYTE ucExpiryDate[4];			//Field 24	//4
	BYTE ucAreaCode;			//Field 26	//1
	BYTE ucTMLocationID_6[6];		//Field 27	//6
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucEV_2[2];				//Field 32	//2
	BYTE ucSTAC[8];				//Field 33	//8
	BYTE ucKeyVersion;			//Field 35	//1
	BYTE ucSAMID[8];			//Field 36	//8
	BYTE ucSAMSN[4];			//Field 37	//4
	BYTE ucSAMCRN[8];			//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
	BYTE ucCAVRMsgType;			//Field 40-1	//1
	BYTE ucCAVRTxnSNLSB;                    //Field 40-2    //1
	BYTE ucCAVRTxnDateTime[4];              //Field 40-3    //4
	BYTE ucCAVRSubType;                     //Field 40-4    //1
	BYTE ucCAVRTxnAmt[2];                   //Field 40-5    //2
	BYTE ucCAVREV[2];                       //Field 40-6    //2
	BYTE ucCAVRCardID[4];                   //Field 40-7    //4
	BYTE ucCAVRIssuerCode;                  //Field 40-8    //1
	BYTE ucCAVRSPID;                        //Field 40-9    //1
	BYTE ucCAVRLocationID;                  //Field 40-10   //1
	BYTE ucCAVRDeviceID[4];                 //Field 40-11   //4
	BYTE ucCAVRBankCode;                    //Field 40-12   //1
	BYTE ucCAVRLoyaltyCounter[2];           //Field 40-13   //2
	ReaderAVR_t stReaderAVR_t;		//Field 41	//38
}AddValue_TM_Out;
/********************************AddValue******************************/

/******************************AuthAddValue****************************/
typedef struct{
	BYTE ucExpiryDate[4];
	BYTE ucHTAC[8];
}AuthAddValue_TM_In;

typedef struct{
	BYTE ucExpiryDate[4];
	BYTE ucHTAC[8];
	BYTE ucProfileExpiryDateDOS[2];
	BYTE ucLCDControlFlag;
}TxAuthAddValue_TM_In;

typedef struct{
	//餘轉加值交易
	SETM_t stAddValueSETM_t;
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucCommandCode[2];			//Field 3	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardID_4[4];			//Field 14	//4
	BYTE ucTxnSN_2[2];			//Field 16	//2
	BYTE ucEV_2[2];				//Field 18	//2
	BYTE ucMAC[10];				//Field 23	//10
	BYTE ucConfirmCode[2];			//Field 47	//2
	BYTE ucCTAC[8];				//Field 48	//8
}AuthAddValue_TM_Out;
/******************************AuthAddValue****************************/

/*****************************AutoloadEnable***************************/
typedef struct{
	BYTE anMsgType[2];
	BYTE anSubType[2];
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
}AutoloadEnable_TM_In;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucCommandCode[2];			//Field 3	//2
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucSPID;				//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;			//Field 12	//1
	BYTE ucPersonalProfile;			//Field 13	//1
	BYTE ucCardID_4[4];			//Field 14	//4
	BYTE ucIssuerCode;			//Field 15	//1
	BYTE ucTxnAmt_2[2];			//Field 17	//2
	BYTE ucLocationID;			//Field 19	//1
	BYTE ucBankCode;			//Field 20	//1
	BYTE ucLoyaltyCounter[2];		//Field 21	//2
	BYTE ucExpiryDate[4];			//Field 24	//4
	BYTE ucAreaCode;			//Field 26	//1
	BYTE ucTMLocationID_6[6];		//Field 27	//6
	BYTE ucTMID[2];				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucEV_2[2];				//Field 32	//2
	BYTE ucSTAC[8];				//Field 33	//8
	BYTE ucKeyVersion;			//Field 35	//1
	BYTE ucSAMID[8];			//Field 36	//8
	BYTE ucSAMSN[4];			//Field 37	//4
	BYTE ucSAMCRN[8];			//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
	BYTE ucCAVRMsgType;			//Field 40-1	//1
	BYTE ucCAVRTxnSNLSB;                    //Field 40-2    //1
	BYTE ucCAVRTxnDateTime[4];              //Field 40-3    //4
	BYTE ucCAVRSubType;                     //Field 40-4    //1
	BYTE ucCAVRTxnAmt[2];                   //Field 40-5    //2
	BYTE ucCAVREV[2];                       //Field 40-6    //2
	BYTE ucCAVRCardID[4];                   //Field 40-7    //4
	BYTE ucCAVRIssuerCode;                  //Field 40-8    //1
	BYTE ucCAVRSPID;                        //Field 40-9    //1
	BYTE ucCAVRLocationID;                  //Field 40-10   //1
	BYTE ucCAVRDeviceID[4];                 //Field 40-11   //4
	BYTE ucCAVRBankCode;                    //Field 40-12   //1
	BYTE ucCAVRLoyaltyCounter[2];           //Field 40-13   //2
	ReaderAVR_t stReaderAVR_t;		//Field 41	//38
	BYTE ucAutoLoadFlag;			//Field 53-1	//1
	BYTE ucAutoLoadAmt_2[2];		//Field 53-2	//2
}AutoloadEnable_TM_Out;
/*****************************AutoloadEnable***************************/

/***************************AuthAutoloadEnable*************************/
typedef struct{
	BYTE ucHTAC[8];
	BYTE ucLCDControlFlag;
}AuthAutoloadEnable_TM_In;

typedef struct{
	//餘轉加值交易
	SETM_t stAddValueSETM_t;
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];			//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucCommandCode[2];			//Field 3	//2
	BYTE ucMsgType;				//Field 7	//1
	BYTE ucSubType;				//Field 8	//1
	BYTE ucDeviceID[4];			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardID_4[4];			//Field 14	//4
	BYTE ucTxnSN_2[2];			//Field 16	//2
	BYTE ucEV_2[2];				//Field 18	//2
	BYTE ucMAC[10];				//Field 23	//10
	BYTE ucConfirmCode[2];			//Field 47	//2
	BYTE ucCTAC[8];				//Field 48	//8
	BYTE ucAutoLoadFlag;			//Field 53-1	//1
	BYTE ucAutoLoadAmt_2[2];		//Field 53-2	//2
}AuthAutoloadEnable_TM_Out;
/***************************AuthAutoloadEnable*************************/

/****************************ReadCardDeduct****************************/
typedef struct{
	BYTE ucLogIndex;
}ReadCardDeduct_TM_In;

typedef struct{
	LastTxnRecored_t stCardDeductRecored1_t;//74
	LastTxnRecored_t stCardDeductRecored2_t;//74
	LastTxnRecored_t stCardDeductRecored3_t;//74
	LastTxnRecored_t stCardDeductRecored4_t;//74
	LastTxnRecored_t stCardDeductRecored5_t;//74
	LastTxnRecored_t stCardDeductRecored6_t;//74
}ReadCardDeduct_TM_Out;
/****************************ReadCardDeduct****************************/

/****************************ReadCodeVersion***************************/
typedef struct{
	BYTE ucSAMAppletVersion;
	BYTE ucSAMType;
	BYTE ucSAMVersion;
	BYTE ucReaderFWVersion[6];
	BYTE ucHostSpecVersionNo;
}ReadCodeVersion_TM_Out;
/****************************ReadCodeVersion***************************/

/*******************************SetValue2******************************/
typedef struct{
	BYTE anMsgType[2];
	BYTE anSubType[2];
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucReadPurseFlag;
}SetValue2_TM_In;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];				//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType; 				//Field 7	//1
	BYTE ucSubType; 				//Field 8	//1
	BYTE ucDeviceID[4]; 			//Field 9	//4
	BYTE ucSPID;					//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;				//Field 12	//1
	BYTE ucPersonalProfile; 		//Field 13	//1
	BYTE ucIssuerCode;				//Field 15	//1
	BYTE ucExpiryDate[4];			//Field 24	//4
	BYTE ucAreaCode;				//Field 26	//1
	BYTE ucTMID[2]; 				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucSTAC[8]; 				//Field 33	//8
	BYTE ucKeyVersion;				//Field 35	//1
	BYTE ucSAMID[8];				//Field 36	//8
	BYTE ucSAMSN[4];				//Field 37	//4
	BYTE ucSAMCRN[8];				//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
	BYTE ucCardID[7];				//Field 58	//7
	BYTE ucTxnAmt[3];				//Field 59	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucCPUSPID[3];				//Field 63	//3
	BYTE ucCPULocationID[2];		//Field 64	//2
	BYTE ucPID[8];					//Field 65	//8
	BYTE ucCTC[3];					//Field 66	//3
	BYTE ucProfileExpiryDate[4];	//Field 67	//4
	BYTE ucSubAreaCode[2];			//Field 69	//2
	BYTE ucTxnSN[3];				//Field 70	//3
	BYTE ucEV[3];					//Field 71	//3
	BYTE ucCPUAdminKeyKVN;			//Field 74-1	//1
	BYTE ucCreditKeyKVN;			//Field 74-2	//1
	BYTE ucCPUIssuerKeyKVN; 		//Field 74-3	//1
	BYTE ucTxnMode; 				//Field 75	//1
	BYTE ucTxnQuqlifier;			//Field 76	//1
	BYTE ucCPUSAMID[8]; 			//Field 79	//8
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucCACrypto[16];			//Field 101 //16
	CardAVR_t stCardAVRInfo_t;		//Field 104 //45
	BYTE ucCardIDLen;				//Field 106 //1
}SetValue2_TM_Out;
/*******************************SetValue2******************************/

/*****************************AuthSetValue2***************************/
typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];				//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType; 				//Field 7	//1
	BYTE ucSubType; 				//Field 8	//1
	BYTE ucDeviceID[4]; 			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucExpiryDate[4];			//Field 25	//4
	BYTE ucTMID[2]; 				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucHTAC[8]; 				//Field 34	//8
	BYTE ucResponseCode[2]; 		//Field 43	//2
	BYTE ucCardID[7];				//Field 58	//7
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];					//Field 65	//8
	BYTE ucProfileExpiryDate[4];	//Field 68	//4
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucHVCrypto[16];			//Field 102 //16
	BYTE ucCardIDLen;				//Field 106 //1
	BYTE ucLCDControlFlag;
}AuthSetValue2_TM_In;

typedef struct{
	BYTE anCardID[17];
	BYTE anDeviceID[10];
	BYTE anCPUDeviceID[16];
	BYTE anEVBeforeTxn[8];
	BYTE anOrgExpiryDate[8];
	BYTE anNewExpiryDate[8];
}AuthSetValue2_TM_Out;
/*****************************AuthSetValue2***************************/

/********************************TxRefund2******************************/
typedef struct{
	BYTE anMsgType[2];
	BYTE anSubType[2];
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE anTxnAmt[8];
	BYTE ucTMTxnDateTime2[14];
	BYTE ucTMSerialNumber2[6];
}TxRefund2_TM_In;

/*typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];				//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType; 				//Field 7	//1
	BYTE ucSubType; 				//Field 8	//1
	BYTE ucDeviceID[4]; 			//Field 9	//4
	BYTE ucSPID;					//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;				//Field 12	//1
	BYTE ucPersonalProfile; 		//Field 13	//1
	BYTE ucIssuerCode;				//Field 15	//1
	BYTE ucLocationID;				//Field 19	//1
	BYTE ucBankCode;				//Field 20	//1
	BYTE ucLoyaltyCounter[2];		//Field 21	//2
	BYTE ucExpiryDate[4];			//Field 24	//4
	BYTE ucAreaCode;				//Field 26	//1
	BYTE ucTMID[2]; 				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucSTAC[8]; 				//Field 33	//8
	BYTE ucKeyVersion;				//Field 35	//1
	BYTE ucSAMID[8];				//Field 36	//8
	BYTE ucSAMSN[4];				//Field 37	//4
	BYTE ucSAMCRN[8];				//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
	BYTE ucCardID[7];				//Field 58	//7
	BYTE ucTxnAmt[3];				//Field 59	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucCPUSPID[3];				//Field 63	//3
	BYTE ucCPULocationID[2];		//Field 64	//2
	BYTE ucPID[8];					//Field 65	//8
	BYTE ucCTC[3];					//Field 66	//3
	BYTE ucProfileExpiryDate[4];	//Field 67	//4
	BYTE ucSubAreaCode[2];			//Field 69	//2
	BYTE ucTxnSN[3];				//Field 70	//3
	BYTE ucEV[3];					//Field 71	//3
	BYTE ucDeposit[3];				//Field 72	//3
	BYTE ucCPUAdminKeyKVN;			//Field 74-1//1
	BYTE ucCreditKeyKVN;			//Field 74-2//1
	BYTE ucCPUIssuerKeyKVN; 		//Field 74-3//1
	BYTE ucTxnMode; 				//Field 75	//1
	BYTE ucTxnQuqlifier;			//Field 76	//1
	BYTE ucSignatureKeyKVN;			//Field 77	//1
	BYTE ucCPUSAMID[8]; 			//Field 79	//8
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucCACrypto[16];			//Field 101 //16
	CardAVR_t stCardAVRInfo_t;		//Field 104 //45
	ReaderAVRTM_t stReaderAVRInfo_t;//Field 105	//83
	BYTE ucCardIDLen;				//Field 106 //1
}TxRefund2_TM_Out;*/
/********************************TxRefund2******************************/

/******************************AuthTxRefund2****************************/
/*typedef struct{
	BYTE ucRFU4[4];
	BYTE ucHTAC[8];
	BYTE ucRFU2[2];
	BYTE ucLCDControlFlag;
}AuthTxRefund2_TM_In;*/

typedef struct{
	//餘轉退卡交易
	STMC_t stTxRefundSTMC_t;
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];				//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType; 				//Field 7	//1
	BYTE ucSubType; 				//Field 8	//1
	BYTE ucDeviceID[4]; 			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucMAC[10]; 				//Field 23	//10
	BYTE ucConfirmCode[2];			//Field 47	//2
	BYTE ucCTAC[8]; 				//Field 48	//8
	BYTE ucCardID[7];				//Field 58	//7
	BYTE ucEV[3];					//Field 60	//3
	BYTE ucTxnSN[3];				//Field 61	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];					//Field 65	//8
	BYTE ucSignature[16];			//Field 78	//16
	BYTE ucHashType;				//Field 86	//1
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucCPUMAC[16];				//Field 88	//16
	//餘轉扣款交易
	STMC_t stTxDeductSTMC_t;
	//加值重送資料開始
	BYTE unVARMsgType[2];
	BYTE unVARPurseVersionNumber[2];
	BYTE unVARTxnSN[6];
	BYTE unVARTxnDateTime[8];
	BYTE unVARSubType[2];
	BYTE unVARTxnAmt[6];
	BYTE unVAREV[6];
	BYTE unVARCardID[14];
	BYTE unVARIssuerCode[2];
	BYTE unVARCPUSPID[6];
	BYTE unVARCPULocationID[4];
	BYTE unVARPID[16];
	BYTE unVARCPUDeviceID[12];
	BYTE unVARLoyaltyCounter[4];
	BYTE unVARPersonalProfile[2];
	BYTE unVARBankCode[2];
	BYTE unVARCardIDLen[2];
	BYTE unVAR2DeviceID[8];
	BYTE unVAR2SPID[2];
	BYTE unVAR2LocationID[2];
	BYTE unVAR2CPUDeviceID[12];
	BYTE unVAR2CPUSPID[6];
	BYTE unVAR2CPULocationID[4];
}AuthTxRefund2_TM_Out;
/******************************AuthTxRefund2****************************/

/*****************************AutoloadEnable2***************************/
typedef struct{
	BYTE anMsgType[2];
	BYTE anSubType[2];
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE anTxnAmt[8];
	BYTE ucReadPurseFlag;
}AutoloadEnable2_TM_In;

typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];				//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucBLVersion[2];			//Field 6	//2
	BYTE ucMsgType;					//Field 7	//1
	BYTE ucSubType;					//Field 8	//1
	BYTE ucDeviceID[4];				//Field 9	//4
	BYTE ucSPID;					//Field 10	//1
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucCardType;				//Field 12	//1
	BYTE ucPersonalProfile;			//Field 13	//1
	BYTE ucIssuerCode;				//Field 15	//1
	BYTE ucLocationID;				//Field 19	//1
	BYTE ucBankCode;				//Field 20	//1
	BYTE ucLoyaltyCounter[2];		//Field 21	//2
	BYTE ucExpiryDate[4];			//Field 24	//4
	BYTE ucAreaCode;				//Field 26	//1
	BYTE ucTMID[2];					//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucSTAC[8];					//Field 33	//8
	BYTE ucKeyVersion;				//Field 35	//1
	BYTE ucSAMID[8];				//Field 36	//8
	BYTE ucSAMSN[4];				//Field 37	//4
	BYTE ucSAMCRN[8];				//Field 38	//8
	BYTE ucReaderFWVersion[6];		//Field 39	//6
	BYTE ucAutoLoadFlag;			//Field 53-1//1
	BYTE ucAutoLoadAmt_2[2];		//Field 53-2//2
	BYTE ucCardID[7];				//Field 58	//7
	BYTE ucTxnAmt[3];				//Field 59	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucCPUSPID[3];				//Field 63	//3
	BYTE ucCPULocationID[2];		//Field 64	//2
	BYTE ucPID[8];					//Field 65	//8
	BYTE ucCTC[3];					//Field 66	//3
	BYTE ucProfileExpiryDate[4];	//Field 67	//4
	BYTE ucSubAreaCode[2];			//Field 69	//2
	BYTE ucTxnSN[3];				//Field 70	//3
	BYTE ucEV[3];					//Field 71	//3
	BYTE ucDeposit[3];				//Field 72	//3
	BYTE ucCPUAdminKeyKVN;			//Field 74-1//1
	BYTE ucCreditKeyKVN;			//Field 74-2//1
	BYTE ucCPUIssuerKeyKVN;			//Field 74-3//1
	BYTE ucTxnMode;					//Field 75	//1
	BYTE ucTxnQuqlifier;			//Field 76	//1
	BYTE ucSignatureKeyKVN;			//Field 77	//1
	BYTE ucCPUSAMID[8];				//Field 79	//8
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucCACrypto[16];			//Field 101	//16
	CardAVR_t stCardAVRInfo_t;		//Field 104	//45
	ReaderAVRTM_t stReaderAVRInfo_t;//Field 105	//83
	BYTE ucCardIDLen;				//Field 106	//1
}AutoloadEnable2_TM_Out;
/*****************************AutoloadEnable2***************************/

/***************************AuthAutoloadEnable2*************************/
typedef struct{
	STMC_t stSTMC_t;
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];				//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType; 				//Field 7	//1
	BYTE ucSubType; 				//Field 8	//1
	BYTE ucDeviceID[4]; 			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucMAC[10]; 				//Field 23	//10
	BYTE ucConfirmCode[2];			//Field 47	//2
	BYTE ucCTAC[8]; 				//Field 48	//8
	BYTE ucAutoLoadFlag;			//Field 53-1//1
	BYTE ucAutoLoadAmt_2[2];		//Field 53-2//2
	BYTE ucCardID[7];				//Field 58	//7
	BYTE ucEV[3];					//Field 60	//3
	BYTE ucTxnSN[3];				//Field 61	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];					//Field 65	//8
	BYTE ucSignature[16];			//Field 78	//16
	BYTE ucHashType;				//Field 86	//1
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucCPUMAC[16];				//Field 88	//16
}AuthAutoloadEnable2_TM_Out;
/***************************AuthAutoloadEnable2*************************/

/******************************AuthAutoload*****************************/
typedef struct{
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];				//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType; 				//Field 7	//1
	BYTE ucSubType; 				//Field 8	//1
	BYTE ucDeviceID[4]; 			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucExpiryDate[4];			//Field 25	//4
	BYTE ucTMID[2]; 				//Field 28	//2
	BYTE ucTMTxnDateTime[14];		//Field 29	//14
	BYTE ucTMSerialNumber[6];		//Field 30	//6
	BYTE ucTMAgentNumber[4];		//Field 31	//4
	BYTE ucHTAC[8]; 				//Field 34	//8
	BYTE ucResponseCode[2]; 		//Field 43	//2
	BYTE ucCardID[7];				//Field 58	//7
	BYTE ucTxnAmt[3];				//Field 59	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];					//Field 65	//8
	BYTE ucProfileExpiryDate[4];	//Field 68	//4
	BYTE ucPurseVersionNumber;		//Field 89	//1
	BYTE ucTMLocationID[10];		//Field 90	//10
	BYTE ucHATOKEN[16]; 			//Field 92	//16
	BYTE ucCardIDLen;				//Field 106 //1
	BYTE ucLCDControlFlag;
}AuthAutoload_TM_In;//For 自動加值

typedef struct{
	STMC_t stSTMC_t;
	BYTE ucMessageType[4];
	BYTE ucDataLen[3];				//Field 1	//3
	BYTE ucProcessignCode[6];		//Field 2	//6
	BYTE ucMsgType; 				//Field 7	//1
	BYTE ucSubType; 				//Field 8	//1
	BYTE ucDeviceID[4]; 			//Field 9	//4
	BYTE ucTxnDateTime[4];			//Field 11	//4
	BYTE ucMAC[10]; 				//Field 23	//10
	BYTE ucConfirmCode[2];			//Field 47	//2
	BYTE ucCTAC[8]; 				//Field 48	//8
	BYTE ucCardID[7];				//Field 58	//7
	BYTE ucTxnAmt[3];				//Field 59	//3
	BYTE ucEV[3];					//Field 60	//3
	BYTE ucTxnSN[3];				//Field 61	//3
	BYTE ucCPUDeviceID[6];			//Field 62	//6
	BYTE ucPID[8];					//Field 65	//8
	BYTE ucSignature[16];			//Field 78	//16
	BYTE ucHashType;				//Field 86	//1
	BYTE ucHostAdminKVN;			//Field 87	//1
	BYTE ucCPUMAC[16];				//Field 88	//16
}AuthAutoload_TM_Out;
/******************************AuthAutoload*****************************/

	int inBuildResetData(int inTxnType,Reset_TM_Out *APIOut,Reset_APDU_In *DongleIn,Reset_APDU_Out *DongleOut);
	int inBuildSignOnData(int inTxnType,SignOn_TM_Out *APIOut,SignOn_APDU_In *bDongleIn,SignOn_APDU_Out *bDongleOut);
	int inBuildSignOnQueryData(int inTxnType,SignOnQuery_TM_Out *APIOut,SignOnQuery_APDU_Out *DongleOut);
	int inBuildReadCardBasicDataData(int inTxnType,ReadCardBasicData_TM_Out *APIOut,ReadCardBasicData_APDU_Out *DongleOut);
	void vdBuildReadCardBasicData2(BYTE ucMsgType,LastTxnLog_t *DongleOutLog,LastTxnRecored_t *APIOutRecored);
	int inBuildTxnReqOnlineData1(int inTxnType,TxnReqOnline_TM_Out_1 *APIOut,TxnReqOnline_APDU_Out *DongleOut);
	int inBuildTxnReqOnlineData2(int inTxnType,TxnReqOnline_TM_Out_2 *APIOut,TxnReqOnline_APDU_In *DongleIn,TxnReqOnline_APDU_Out *DongleOut);
	int inBuildTxnReqOnlineData3(int inTxnType,CardSale_TM_Out *APIOut,TxnReqOnline_APDU_In *DongleIn,TxnReqOnline_APDU_Out *DongleOut);
	int inBuildTxnReqOnlineData4(int inTxnType,CancelTxn_TM_Out *APIOut,TxnReqOnline_APDU_Out *DongleOut,BYTE ucMsgType);
	void vdBuildCardAVRData(CardAVR_t *APIOutData,LastTxnLog_t *DongleOutLog,BYTE *ucCardID,BYTE ucIssuerCode,BYTE *ucCPUSPID,BYTE *ucCPULocationID,BYTE *ucPID,BYTE *ucLoyaltyCounter);
	void vdBuildReaderAVRData(ReaderAVRTM_t *APIOutData,ReaderAVRAPDU_t *DongleOutLog);
	int inBuildAuthTxnOnlineData(int inTxnType,AuthTxnOnline_TM_Out *APIOut,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut);
	int inBuildTxnReqOfflineData1(int inTxnType,TxnReqOffline_TM_Out_1 *APIOut,TxnReqOffline_APDU_In *DongleIn,TxnReqOffline_APDU_Out *DongleOut);
	int inBuildTxnReqOfflineData2(int inTxnType,TxnReqOffline_TM_Out_2 *APIOut,TxnReqOffline_APDU_In *DongleIn,TxnReqOffline_APDU_Out *DongleOut);
	int inBuildAuthTxnOfflineData(int inTxnType,AuthTxnOffline_TM_Out *APIOut,AuthTxnOffline_APDU_In *DongleIn,AuthTxnOffline_APDU_Out *DongleOut,TxnReqOffline_APDU_Out *TxnReqOut);
	int inBuildLockCardData1(int inTxnType,LockCard_TM_Out_2 *APIOut,LockCard_APDU_Out_2 *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason,BYTE *ucTMLocationID,BYTE *ucTMID);
	int inBuildLockCardData2(int inTxnType,LockCard_TM_Out_2 *APIOut,LockCard_APDU_Out_3 *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason,BYTE *ucTMLocationID,BYTE *ucTMID);
	int inBuildLockCardData3(int inTxnType,LockCard_TM_Out_2 *APIOut,TxnReqOffline_APDU_Out *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason,BYTE *ucTMLocationID,BYTE *ucTMID);
	int inBuildLockCardData4(int inTxnType,LockCard_TM_Out_1 *APIOut,TxRefund_APDU_Out *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason);
	int inBuildLockCardData5(int inTxnType,LockCard_TM_Out_1 *APIOut,AddValue_APDU_Out *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason);
	int inBuildLockCardData6(int inTxnType,LockCard_TM_Out_1 *APIOut,LockCard_APDU_Out_1 *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason);
	int inBuildLockCardData7(int inTxnType,LockCard_TM_Out_2 *APIOut,TxRefund_APDU_Out *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason);
	int inBuildReadDongleDeductData(int inTxnType,ReadDongleDeduct_TM_Out *APIOut,ReadDongleDeduct_APDU_Out *DongleOut);
	int inBuildAuthCardSaleData(int inTxnType,AuthCardSale_TM_Out *APIOut,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut);
	int inBuildSetValueData(int inTxnType,SetValue_TM_Out *APIOut,SetValue_APDU_In *DongleIn,SetValue_APDU_Out *DongleOut);
	int inBuildAuthSetValueData(int inTxnType,AuthSetValue_TM_Out *APIOut,AuthSetValue_APDU_In *DongleIn,AuthSetValue_APDU_Out *DongleOut,SetValue_APDU_Out *TxnReqOut);
	int inBuildTxRefundData(int inTxnType,TxRefund_TM_Out *APIOut,TxRefund_APDU_In *DongleIn,TxRefund_APDU_Out *DongleOut);
	int inBuildAuthTxRefundData(int inTxnType,AuthTxRefund_TM_Out *APIOut,AuthTxRefund_APDU_In *DongleIn,AuthTxRefund_APDU_Out *DongleOut,TxRefund_APDU_Out *TxnReqOut);
	int inBuildAddValueData(int inTxnType,AddValue_TM_Out *APIOut,AddValue_APDU_In *DongleIn,AddValue_APDU_Out *DongleOut);
	int inBuildAuthAddValueData(int inTxnType,AuthAddValue_TM_Out *APIOut,AuthAddValue_APDU_In *DongleIn,AuthAddValue_APDU_Out *DongleOut,AddValue_APDU_Out *TxnReqOut);
	int inBuildAutoloadEnableData(int inTxnType,AutoloadEnable_TM_Out *APIOut,AutoloadEnable_APDU_In *DongleIn,AutoloadEnable_APDU_Out *DongleOut);
	int inBuildAuthAutoloadEnableData(int inTxnType,AuthAutoloadEnable_TM_Out *APIOut,AuthAutoloadEnable_APDU_In *DongleIn,AuthAutoloadEnable_APDU_Out *DongleOut,AutoloadEnable_APDU_Out *TxnReqOut);
	int inBuildReadCardDeductData(int inTxnType,ReadCardDeduct_TM_Out *APIOut,ReadCardDeduct_APDU_Out *DongleOut);
	int inBuildReadCodeVersionData(int inTxnType,ReadCodeVersion_TM_Out *APIOut,ReadCodeVersion_APDU_Out *DongleOut);
	int inBuildSetValue2Data(int inTxnType,SetValue2_TM_Out *APIOut,SetValue2_APDU_In *DongleIn,SetValue2_APDU_Out *DongleOut);
	int inBuildAuthSetValue2Data(int inTxnType,AuthSetValue2_TM_Out *APIOut,AuthSetValue2_APDU_In *DongleIn,AuthSetValue2_APDU_Out *DongleOut,SetValue2_APDU_Out *TxnReqOut);
	int inBuildTxRefundData2(int inTxnType,TxnReqOnline_TM_Out_2 *APIOut,TxRefund_APDU_In *DongleIn,TxRefund2_APDU_Out *DongleOut);
	int inBuildAuthTxRefundData2(int inTxnType,AuthTxRefund2_TM_Out *APIOut,AuthTxnOnline_TM_In *DongleIn,AuthTxRefund_APDU_Out *DongleOut,TxRefund2_APDU_Out *TxnReqOut);
	int inBuildAutoloadEnableData2(int inTxnType,AutoloadEnable2_TM_Out *APIOut,TxnReqOnline_APDU_In *DongleIn,TxnReqOnline_APDU_Out *DongleOut);
	int inBuildAuthAutoloadEnableData2(int inTxnType,AuthAutoloadEnable2_TM_Out *APIOut,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut);
	int inBuildAuthAutoloadData(int inTxnType,AuthAutoload_TM_Out *APIOut,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut);

#ifdef __cplusplus
	}
#endif // __cplusplus

#endif
