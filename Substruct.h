#ifndef __SUBSTRUCT_H__
#define __SUBSTRUCT_H__

#ifdef __cplusplus
	extern "C" {
#endif

#include "dongle.h"
//TM.h與APDU.h會用到的結構都放在這裡
 typedef struct{
        BYTE ucTMLocationID[10+1];
        BYTE ucTMID[2+1];
	BYTE ucTMTxnDateTime[14+1];
	BYTE ucTMSerialNumber[6+1];
	BYTE ucTMAgentNumber[4+1];
 }TM_INFO;
typedef struct{
	BYTE ucOneDayQuotaFlag;
	BYTE ucOneDayQuota[2];
	BYTE ucOnceQuotaFlag;
	BYTE ucOnceQuota[2];
	BYTE ucCheckEVFlag;
	BYTE ucAddQuotaFlag;
	BYTE ucAddQuota[3];
	BYTE ucCheckDeductFlag;
	BYTE ucCheckDeductValue[2];
	BYTE ucDeductLimitFlag;
	BYTE ucAPIVersion[4];
	BYTE ucRFU[5];
}TermHost_t;

typedef struct{
	BYTE ucRemainderAddQuota[3];
	BYTE ucDeMAC[8];
        BYTE ucCancelCreditQuota[3]; //add for CMAS
	BYTE ucRFU[21];
}TermPara_t;

typedef struct{
	BYTE ucPreCPUDeviceID[6];
	BYTE ucPreSTC[4];
	BYTE ucPreTxnDateTime[4];
	BYTE ucPreCreditBalanceChangeFlag;
	BYTE ucPreConfirmCode[2];
	BYTE ucPreCACrypto[16];
}LastSingOn_t;

typedef struct{
	BYTE ucSAMUpdateOption;
	BYTE ucNewSAMValue[40];
	BYTE ucUpdateSAMValueMAC[16];
}SAMParaSetting_t;

typedef struct{
	BYTE bCPDReadFlag0		:1;
	BYTE bCPDReadFlag1		:1;
	BYTE bOneDayQuotaWrite2		:1;
	BYTE bOneDayQuotaWrite3		:1;
	BYTE bSAMSignOnControlFlag4	:1;
	BYTE bSAMSignOnControlFlag5	:1;
	BYTE bCheckEVFlag6		:1;
	BYTE bDeductLimitFlag7		:1;
	BYTE bOneDayQuotaFlag0		:1;
	BYTE bOneDayQuotaFlag1		:1;
	BYTE bOnceQuotaFlag2		:1;
	BYTE bCheckDeductFlag3		:1;
	BYTE bRFU24			:1;
	BYTE bRFU25			:1;
	BYTE bRFU26			:1;
	BYTE bRFU27			:1;
	BYTE ucOneDayQuota[2];
	BYTE ucOnceQuota[2];
	BYTE ucCheckDeductValue[2];
	BYTE ucAddQuotaFlag;
	BYTE ucAddQuota[3];
}SAMParameter_t;

typedef struct{
	BYTE ucSAMVersion;
	BYTE ucSAMUsageControl[3];
	BYTE ucSAMAdminKVN;
	BYTE ucSAMIssuerKVN;
	BYTE ucTagListTable[40];
	BYTE ucSAMIssuerSpecData[32];
}CPUSAMInfo_t;

typedef struct{
	BYTE ucPurseVersionNumber_Index;
	BYTE ucTxnSN[3];
	BYTE ucTxnDateTime[4];
	BYTE ucSubType;
	BYTE ucTxnAmt[3];
	BYTE ucEV[3];
	BYTE ucCPUSPID[3];
	BYTE ucCPULocationID[2];
	BYTE ucCPUDeviceID[6];
	BYTE ucRFU;
	BYTE ucEV2[3];
	BYTE ucTSQN2[3];
}LastTxnLog_t;

typedef struct{
	BYTE anTxnSN[8];
	BYTE anTxnDateTime[14];
	BYTE anSubType[2];
	BYTE anEVBeforeTxn[8];
	BYTE anTxnAmt[8];
	BYTE anEV[8];
	BYTE anCPUSPID[8];
	BYTE anLocationID[5];
	BYTE anCPUDeviceID[16];
}LastTxnRecored_t;

typedef struct{
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucDeviceID[4];
	BYTE ucCPUDeviceID[6];
	BYTE ucTxnDateTime[4];
	BYTE ucPurseVersionNumber;
	BYTE ucCardID[7];
	BYTE ucCardIDLen;
	BYTE ucTxnSN[3];
	BYTE ucEV[3];
	BYTE ucStatusCode[2];
	BYTE ucPID[8];
	BYTE ucSignature[16];
	BYTE ucSAMID[8];
	BYTE ucMAC_HCrypto[18];
}ReaderAVRAPDU_t;

typedef struct{
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucDeviceID[4];
	BYTE ucCPUDeviceID[6];
	BYTE ucTxnDateTime[4];
	BYTE ucPurseVersionNumber;
	BYTE ucCardID[7];
	BYTE ucTxnSN[3];
	BYTE ucEV[3];
	BYTE ucStatusCode[2];
	BYTE ucPID[8];
	BYTE ucSignature[16];
	BYTE ucSAMID[8];
	BYTE ucMAC_HCrypto[18];
	BYTE ucCardIDLen;
}ReaderAVRTM_t;

typedef struct{
	BYTE ucMsgType;
	BYTE ucPurseVersionNumber;
	BYTE ucTxnSN[3];//5
	BYTE ucTxnDateTime[4];//9
	BYTE ucSubType;//10
	BYTE ucTxnAmt[3];//13
	BYTE ucEV[3];//16
	BYTE ucCardID[7];//23
	BYTE ucIssuerCode;//24
	BYTE ucCPUSPID[3];//27
	BYTE ucCPULocationID[2];//29
	BYTE ucPID[8];//37
	BYTE ucCPUDeviceID[6];//43
	BYTE ucLoyaltyCounter[2];//45
}CardAVR_t;//45

typedef struct{
	BYTE ucRAVRMsgType;
	BYTE ucRAVRSubType;
	BYTE ucRAVRDeviceID[4];
	BYTE ucRAVRTxnDateTime[4];
	BYTE ucRAVRCardID[4];
	BYTE ucRAVRTxnSN[2];
	BYTE ucRAVREV[2];
	BYTE ucRAVRMAC[10];
	BYTE ucRAVRConfirmCode[2];
	BYTE ucRAVRCTAC[8];
}ReaderAVR_t;

typedef struct{
	BYTE anCardID_10[10];
	BYTE anDeviceID[10];
	BYTE anEVBeforeTxn_5[5];
	BYTE anTxnSN_5[5];
	BYTE anTxnAmt_5[5];
	BYTE anEV_5[5];
	BYTE anProcessignCode[6];
	BYTE unMsgType[2];
	BYTE unSubType[2];
	BYTE unDeviceID[8];
	BYTE unSPID[2];
	BYTE unTxnDateTime[8];
	BYTE unCardType[2];
	BYTE unPersonalProfile[2];
	BYTE unCardID_8[8];
	BYTE unIssuerCode[2];
	BYTE unTxnSN_4[4];
	BYTE unTxnAmt_4[4];
	BYTE unEV_4[4];
	BYTE unLocationID[2];
	BYTE unBankCode[2];
	BYTE unLoyaltyCounter[4];
	BYTE unDeposit_4[4];
	BYTE unMAC[20];
	BYTE anOrgExpiryDate[8];
	BYTE anNewExpiryDate[8];
	BYTE unAreaCode[2];
	BYTE unEVBeforeTxn_4[4];
}SETM_t;

typedef struct{
	BYTE anCardID[17];
	BYTE anDeviceID[10];
	BYTE anCPUDeviceID[16];
	BYTE anEVBeforeTxn[8];
	BYTE anTxnSN[8];
	BYTE anTxnAmt[8];
	BYTE anEV[8];
	BYTE anProcessignCode[6];
	BYTE unMsgType[2];
	BYTE unSubType[2];
	BYTE unDeviceID[8];
	BYTE unSPID[2];
	BYTE unTxnDateTime[8];
	BYTE unCardType[2];
	BYTE unPersonalProfile[2];
	BYTE unLocationID[2];
	BYTE unCardID[14];
	BYTE unIssuerCode[2];
	BYTE unBankCode[2];
	BYTE unLoyaltyCounter[4];
	BYTE unMAC[20];
	BYTE unOrgExpiryDate[8];
	BYTE unNewExpiryDate[8];
	BYTE unAreaCode[2];
	BYTE unTxnAmt[6];
	BYTE unEV[6];
	BYTE unTxnSN[6];
	BYTE unCPUDeviceID[12];
	BYTE unCPUSPID[6];
	BYTE unCPULocationID[4];
	BYTE unPID[16];
	BYTE unCTC[6];
	BYTE unOrgProfileExpiryDate[8];
	BYTE unNewProfileExpiryDate[8];
	BYTE unSubAreaCode[4];
	BYTE unTxnSNBeforeTxn[6];
	BYTE unEVBeforeTxn[6];
	BYTE unDeposit[6];
	BYTE unTxnMode[2];
	BYTE unTxnQuqlifier[2];
	BYTE unSignatureKeyKVN[2];
	BYTE unSignature[32];
	BYTE unCPUSAMID[16];
	BYTE unHashType[2];
	BYTE unHostAdminKVN[2];
	BYTE unCPUMAC[32];
	BYTE unPurseVersionNumber[2];
	BYTE unCardIDLen[2];
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
}STMC_t;
/********************************Reset********************************/
  typedef struct {
        BYTE bCPDReadFlag0 : 1;
        BYTE bCPDReadFlag1 : 1;
        BYTE bOneDayQuotaWrite2 : 1;
        BYTE bOneDayQuotaWrite3 : 1;
        BYTE bSAMSignOnControlFlag4 : 1;
        BYTE bSAMSignOnControlFlag5 : 1;
        BYTE bCheckEVFlag6 : 1;
        BYTE bDeductLimitFlag7 : 1;
        BYTE bOneDayQuotaFlag0 : 1;
        BYTE bOneDayQuotaFlag1 : 1;
        BYTE bOnceQuotaFlag2 : 1;
        BYTE bCheckDeductFlag3 : 1;
        BYTE bRFU24 : 1;
        BYTE bRFU25 : 1;
        BYTE bRFU26 : 1;
        BYTE bRFU27 : 1;
        BYTE ucOneDayQuota[2];
        BYTE ucOnceQuota[2];
        BYTE ucCheckDeductValue[2];
        BYTE ucAddQuotaFlag;
        BYTE ucAddQuota[3];
    } SAMParameter_DATA_t;
 typedef struct{
	BYTE ucPreCPUDeviceID[6];
	BYTE ucPreSTC[4];
	BYTE ucPreTxnDateTime[4];
	BYTE ucPreCreditBalanceChangeFlag;
	BYTE ucPreConfirmCode[2];
	BYTE ucPreCACrypto[16];
}LastSingOn_DATA_t;
typedef struct{
	BYTE ucSAMUpdateOption;
	BYTE ucNewSAMValue[40];
	BYTE ucUpdateSAMValueMAC[16];
}SAMParaSetting_DATA_t;
typedef struct{
	BYTE ucRAVRMsgType;
	BYTE ucRAVRSubType;
	BYTE ucRAVRDeviceID[4];
	BYTE ucRAVRTxnDateTime[4];
	BYTE ucRAVRCardID[4];
	BYTE ucRAVRTxnSN[2];
	BYTE ucRAVREV[2];
	BYTE ucRAVRMAC[10];
	BYTE ucRAVRConfirmCode[2];
	BYTE ucRAVRCTAC[8];
}ReaderAVR_DATA_t;
 typedef struct{
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucTxnDateTime[4];
	BYTE ucLocationID;
	BYTE ucCPULocationID[2];
	BYTE ucSPID;
	BYTE ucCPUSPID[3];
	BYTE ucRFU1[5];
	BYTE ucSAMSlot[1];
	BYTE ucRFU2[11];
}Reset_APDU_In;


typedef struct{
	BYTE ucHostSpecVersionNo;//4820
	BYTE ucReaderID[4];//4104
	BYTE ucReaderFWVersion[6];//config   t6000
	BYTE ucSAMID[8];//5361
	BYTE ucSAMSN[4];//53662
	BYTE ucSAMCRN[8];//5663
	BYTE ucDeviceID[4];//4101
	BYTE ucSAMKeyVersion;//5301
	BYTE ucSTAC[8];//6400
	BYTE ucSAMVersion;//5364-1
	BYTE ucCPUSAMID[8];//5361
	BYTE ucSAMUsageControl[3];//5364-2
	BYTE ucSAMAdminKVN;//5364-3
	BYTE ucSAMIssuerKVN;//5364-4
	BYTE ucAuthCreditLimit[3];//5365-1
	BYTE ucSingleCreditTxnAmtLimit[3];//5366
	BYTE ucAuthCreditBalance[3];//5365-2
	BYTE ucAuthCreditCumulative[3];//5365-3
	BYTE ucAuthCancelCreditCumulative[3];//5365-4
	BYTE ucCPUDeviceID[6];//4100
	BYTE ucTagListTable[40];//5364-5
	BYTE ucSAMIssuerSpecData[32];//5364-6
	BYTE ucSTC[4];//5368
	BYTE ucRSAM[8];//5307
	BYTE ucRHOST[8];//5308
	BYTE ucSATOKEN[16];//6408
	SAMParameter_DATA_t stSAMParameterInfo_t;//12   6002 6003
        BYTE ucRemainderAddQuota[3];
	BYTE ucCancelCreditQuota[3];//6003-3
	BYTE ucDeMAC[8];//6003-2
	BYTE ucLastTxnDateTime[4];//				?????
	LastSingOn_DATA_t stLastSignOnInfo_t;//5370
	BYTE ucStatusCode[2];
}Reset_APDU_Out;
/****************************************************************/

/*****************************SignOn***********************************/
typedef struct{
	BYTE ucHTAC[8];    //6401
	BYTE ucHATOKEN[16];	//6409
	SAMParaSetting_DATA_t stSAMParaSettingInfo_t;//57 
	SAMParameter_DATA_t stSAMParameterInfo_t;//12   6002 6003
	BYTE ucRFU[31];
	BYTE ucHashType;//5303
	BYTE ucCPUEDC[3];//5306
}SignOn_APDU_In;

typedef struct{
	BYTE ucCreditBalanceChangeFlag;//4825
	BYTE ucAuthCreditLimit[3];//5365-1
	BYTE ucAuthCreditBalance[3];//5365-2
	BYTE ucAuthCreditCumulative[3];//5365-3
	BYTE ucAuthCancelCreditCumulative[3];//5365-4
	BYTE ucCACrypto[16];//6406
	BYTE ucStatusCode[2];
}SignOn_APDU_Out;
/****************************************************************/

/*****************************SignOnQuery******************************/

typedef struct{
	BYTE ucAuthCreditLimit[3];//5365-1
	BYTE ucAuthCreditBalance[3];//5365-2
	BYTE ucAuthCreditCumulative[3];//5365-3
	BYTE ucAuthCancelCreditCumulative[3];//5365-4
	SAMParameter_DATA_t stSAMParameterInfo_t;//12  6002 6003
	BYTE ucLastTxnDateTime[4]; //�P�_�W��signon �ɶ���
	BYTE ucSPID; //
	BYTE ucCPUSPID[3];//4200
	BYTE ucRFU[2];//
	BYTE ucRemainderAddQuota[3];//6003-1
	BYTE ucCancelCreditQuota[3];//6003-3
	BYTE ucStatusCode[2];
}SignOnQuery_APDU_Out;
/****************************************************************/
/**************************ReadCardNumber****************************/
typedef struct{
    BYTE ucTXNAMT[3];
    BYTE LCDContralFalg;
}ReadCardNumber_APDU_In;

typedef struct{
    BYTE ucCardID[7];
    BYTE ucCardIDLength;
    BYTE ucCardLevel;
}ReadCardNumber_APDU_Out;

/**************************ReadCardBasicData***************************/
typedef struct{
	BYTE ucLCDControlFlag;
}ReadCardBasicData_APDU_In;

typedef struct{
	BYTE ucPurseVersionNumber;//4800
	BYTE bActivated			:1;
	BYTE bBlocked			:1;
	BYTE bRefunded			:1;
	BYTE bAutoLoad			:1;//0212
	BYTE bCredit			:1;
	BYTE bRFU5			:1;
	BYTE bRFU6			:1;
	BYTE bRFU7			:1;
	BYTE ucAutoLoadAmt[3];//4822-2 & 0409
	BYTE ucPID[8];//0211
	BYTE ucCPUAdminKeyKVN;//5302-1
	BYTE ucCreditKeyKVN;//5302-2
	BYTE ucSignatureKeyKVN;//5305
	BYTE ucCPUIssuerKeyKVN;
	BYTE ucDebitTxnRecords;//�d��iŪ�X�����ڸ��
	BYTE ucMinBalanceAllowed[3];//�̤p�l�B����
	BYTE ucSubAreaCode[2];//4805
	BYTE ucIssuedDate[4];//
	BYTE ucExpiryDate[4];//1400
	BYTE ucEV[3];
	BYTE ucTxnSN[3];//4808;
	BYTE ucCardType;//0213
	BYTE ucPersonalProfile;//0214
	BYTE ucProfileExpiryDate[4];//1402
	BYTE ucAreaCode;//4804
	BYTE ucCardID[7];//0200
	BYTE ucCardIDLen;//4826
	BYTE ucDeposit[3];//4816
	BYTE ucIssuerCode;//4802
	BYTE ucBankCode;//4803
	BYTE ucLoyaltyCounter[2];//4813
	LastTxnLog_t  stLastCreditTxnLogInfo_t;//33  4801
	LastTxnLog_t stLastDebitTxnLogInfo_t;//33  
	BYTE ucCardOneDayQuota[3];//4827-1
	BYTE ucCardOneDayQuotaDate[2];//4827-2
	BYTE ucMerchantUseFlag;
	BYTE ucIssueStatus;
	BYTE ucBlockStatus;
	BYTE AutoloadCounter;//
	BYTE AutoloadDate[2];
	//BYTE ucRFU[5];
	BYTE ucStatusCode[2];
}ReadCardBasicData_APDU_Out;
/**************************ReadCardBasicData***************************/

/*****************************TxnReqOnline*****************************/
typedef struct{
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucTxnDateTime[4];
	BYTE ucTxnAmt[3];
	BYTE ucReadPurseFlag;
	BYTE ucRFU[18];
}TxnReqOnline_APDU_In;

typedef struct{
	BYTE ucPurseVersionNumber;//4800
	BYTE bActivated			:1;
	BYTE bBlocked			:1;
	BYTE bRefunded			:1;
	BYTE bAutoLoad			:1;//0212
	BYTE bCredit			:1;
	BYTE bRFU5			:1;
	BYTE bRFU6			:1;
	BYTE bRFU7			:1;
	BYTE ucAutoLoadAmt[3];//4822-2 & 0409
	BYTE ucPID[8];//0211
	BYTE ucCPUAdminKeyKVN;//5302-1
	BYTE ucCreditKeyKVN;//5302-2
	BYTE ucSignatureKeyKVN;//5302-3
	BYTE ucCPUIssuerKeyKVN;
	BYTE ucCTC[3];//4812
	BYTE ucTxnMode;//4809
	BYTE ucTxnQuqlifier;//4810
	BYTE ucSubAreaCode[2];//4805
	BYTE ucExpiryDate[4];//1400
	BYTE ucEV[3];//0408
	BYTE ucTxnSN[3];//4808
	BYTE ucCardType;//0213
	BYTE ucPersonalProfile;//0214
	BYTE ucProfileExpiryDate[4];//1402
	BYTE ucAreaCode;//4804
	BYTE ucCardID[7];//0200
	BYTE ucCardIDLen;//4826
	BYTE ucTxnAmt[3];//0400
	BYTE ucHostSpecVersionNo;//4820
	BYTE ucReaderFWVersion[6];//6000
	BYTE ucDeviceID[4];//4101
	BYTE ucCPUDeviceID[6];//4100
	BYTE ucSPID;//
	BYTE ucCPUSPID[3];//4200
	BYTE ucLocationID;//
	BYTE ucCPULocationID[2];//4210
	BYTE ucDeposit[3];//4816
	BYTE ucIssuerCode;//4802
	BYTE ucBankCode;//4803
	BYTE ucLoyaltyCounter[2];//4813
	BYTE ucSAMID[8];//5361
	BYTE ucSAMSN[4];//5362
	BYTE ucSAMCRN[8];//5363
	BYTE ucSAMKVN;//5301
	BYTE ucSTAC[8];//6400
	BYTE ucTMSerialNumber[6];//1100
	LastTxnLog_t stLastCreditTxnLogInfo_t;//33
	ReaderAVRAPDU_t stReaderAVRInfo_t;//83  6001
	BYTE ucMsgType;//
	BYTE ucSubType;
	BYTE ucCPUSAMID[8];
	BYTE ucHostAdminKVN;//5304
	BYTE ucTxnCrypto[8];//cacrypto
	BYTE ucStatusCode[2];
}TxnReqOnline_APDU_Out;
/*****************************TxnReqOnline*****************************/

/*****************************AuthTxnOnline****************************/
typedef struct{
	BYTE ucExpiryDate[4];
	BYTE ucProfileExpiryDate[4];
	BYTE ucProfileExpiryDateDOS[2];
	BYTE ucTxnToken[16];
	BYTE ucHTAC[8];
	BYTE ucLCDControlFlag;
	BYTE ucRFU[5];
}AuthTxnOnline_APDU_In;

typedef struct{
	BYTE ucTxnSN[3];//4808
	BYTE ucEV[3];//0408
	BYTE ucConfirmCode[2];
	BYTE ucSignature[16];//6405
	BYTE ucCPUSAMID[8];//
	BYTE ucMAC_HCrypto[18];// 6403 & 6407
	BYTE ucTxnDateTime[4]; //1300
	BYTE ucRFU[10];
	BYTE ucStatusCode[2];
}AuthTxnOnline_APDU_Out;
/*****************************AuthTxnOnline****************************/

/*****************************TxnReqOffline****************************/
typedef struct{
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucTxnDateTime[4];
	BYTE ucTxnAmt[3];
	BYTE ucReadPurseFlag;
	BYTE ucRefundFee[3];
	BYTE ucBrokenFee[3];
	BYTE ucLCDControlFlag;
	BYTE ucRFU[11];
}TxnReqOffline_APDU_In;

typedef struct{
	BYTE ucPurseVersionNumber;//4800
	BYTE bActivated			:1;
	BYTE bBlocked			:1;
	BYTE bRefunded			:1;
	BYTE bAutoLoad			:1;
	BYTE bCredit			:1;
	BYTE bRFU5			:1;
	BYTE bRFU6			:1;
	BYTE bRFU7			:1;
	BYTE ucAutoLoadAmt[3];//0212
	BYTE ucPID[8];//0211
	BYTE ucCPUAdminKeyKVN;//5302-1
	BYTE ucCreditKeyKVN;//5302-2
	BYTE ucSignatureKeyKVN;//5305
	BYTE ucCPUIssuerKeyKVN;
	BYTE ucCTC[3];//4812
	BYTE ucTxnMode;//4809
	BYTE ucTxnQuqlifier;//4810
	BYTE ucSubAreaCode[2];//4805
	BYTE ucExpiryDate[4];//1400
	BYTE ucEV[3];//0408
	BYTE ucTxnSN[3];//4808
	BYTE ucCardType;//0213
	BYTE ucPersonalProfile;//0214
	BYTE ucProfileExpiryDate[4];//1402
	BYTE ucAreaCode;//4804
	BYTE ucCardID[7];//0200
	BYTE ucCardIDLen;//4826
	BYTE ucTxnAmt[3];//0400
	BYTE ucHostSpecVersionNo;//4820
	BYTE ucReaderFWVersion[6];//6000
	BYTE ucDeviceID[4];//4101
	BYTE ucCPUDeviceID[6];//4100
	BYTE ucSPID;
	BYTE ucCPUSPID[3];//4200
	BYTE ucLocationID;
	BYTE ucCPULocationID[2];//4210
	BYTE ucDeposit[3];//4816
	BYTE ucIssuerCode;//4802
	BYTE ucBankCode_HostAdminKVN; //bank code 4803 hostAdminkvn 5304
	BYTE ucCPDReadFlag;//4824
	BYTE ucCPD_SAMID[16];//
	BYTE ucCPDRAN_SAMCRN[8]; //SAM CRN 5363
	BYTE ucCPDKVN_SAMKVN;///SAMEKVN 5301
	BYTE ucSID_STAC[8];//STAC 6400
	BYTE ucTMSerialNumber[6];//1100
	LastTxnLog_t stLastCreditTxnLogInfo_t;//33  card avr
	BYTE ucSVCrypto[16];//6406
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucCardOneDayQuota[3];   //4821-1
	BYTE ucCardOneDayQuotaDate[2];//4821-2
	BYTE ucRFU[73];
	BYTE ucStatusCode[2];
}TxnReqOffline_APDU_Out;
/*****************************TxnReqOffline****************************/

/*****************************AuthTxnOffline***************************/
typedef struct{
	BYTE ucHVCrypto_HTAC[16]; //6407
	BYTE ucLCDControlFlag;
	BYTE ucRFU[5];
}AuthTxnOffline_APDU_In;

typedef struct{
	BYTE ucTxnSN[3];//4808
	BYTE ucEV[3];//0408
	BYTE ucConfirmCode[2];
	BYTE ucSignature[16];//6405
	BYTE ucCPUSAMID[8];//
	BYTE ucMAC_HCrypto[18];//6404
	BYTE ucTxnDateTime[4];//1200
	BYTE ucCardOneDayQuota[3];//4821-1
	BYTE ucCardOneDayQuotaDate[2];//4821-2
	BYTE ucRFU[5];
	BYTE ucStatusCode[2];
}AuthTxnOffline_APDU_Out;
/*****************************AuthTxnOffline***************************/

/******************************LockCard 1******************************/
typedef struct{
	BYTE ucCardID_4[4]; 
	BYTE ucLockReason;
}LockCard_APDU_In_1;

typedef struct{
	BYTE ucDeviceID[4];
	BYTE ucCardType;
	BYTE ucPersonalProfile;
	BYTE ucCardID_4[4];
	BYTE ucIssuerCode;
	BYTE ucStatusCode[2];
}LockCard_APDU_Out_1;
/******************************LockCard 1******************************/

/******************************LockCard 2******************************/
typedef struct{
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucCardID[7]; //0200
	BYTE ucTxnDateTime[4];//1200
	BYTE ucLockReason;//4817
}LockCard_APDU_In_2;

typedef struct{
	BYTE ucPurseVersionNumber;//4800
	BYTE ucPID[8];//0211
	BYTE ucCTC[3];//4812
	BYTE ucCardType;//0213
	BYTE ucPersonalProfile;//0214
	BYTE ucCardID[7];//0200
	BYTE ucCardIDLen;//4826
	BYTE ucDeviceID[4];//4101
	BYTE ucCPUDeviceID[6];//4100
	BYTE ucSPID;//
	BYTE ucCPUSPID[3];//4200
	BYTE ucLocationID;
	BYTE ucCPULocationID[2];//4210
	BYTE ucIssuerCode;//4803
	BYTE ucStatusCode[2];
}LockCard_APDU_Out_2;

typedef struct{
	BYTE ucPurseVersionNumber;//4800
	BYTE bActivated			:1;
	BYTE bBlocked			:1;
	BYTE bRefunded			:1;
	BYTE bAutoLoad			:1;//0212
	BYTE bCredit			:1;
	BYTE bRFU5			:1;
	BYTE bRFU6			:1;
	BYTE bRFU7			:1;
	BYTE ucAutoLoadAmt[3];//0409
	BYTE ucPID[8];//0211
	BYTE ucCPUIssuerKeyKVN;//
	BYTE ucSubAreaCode[2];//4805
	BYTE ucExpiryDate[4];//1400
	BYTE ucEV[3];//0403
	BYTE ucTxnSN[3];//4808
	BYTE ucCardType;//0213
	BYTE ucPersonalProfile;//0214
	BYTE ucProfileExpiryDate[4];//1402
	BYTE ucAreaCode;//4084
	BYTE ucCardID[7];//0200
	BYTE ucCardIDLen;//4826
	BYTE ucDeviceID[4];//4101
	BYTE ucCPUDeviceID[6];//4100
	BYTE ucSPID;
	BYTE ucCPUSPID[3];//4200
	BYTE ucLocationID;
	BYTE ucCPULocationID[2];//4210
	BYTE ucDeposit[3];//4816
	BYTE ucIssuerCode;//4802
	BYTE ucBankCode;//4803
	BYTE ucLoyaltyCounter[2];//4813
	LastTxnLog_t stLastCreditTxnLogInfo_t;//33  4801
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucEV2[3];
	BYTE ucMifareSettingParameter;//4828-1
	BYTE ucCPUSettingParameter;//4829-1
	BYTE ucRFU[15];
	BYTE ucStatusCode[2];
}LockCard_APDU_Out_3;
/******************************LockCard 2******************************/

/***************************ReadDongleDeduct***************************/
typedef struct{
	BYTE ucLogSeqNo[2];
}ReadDongleDeduct_APDU_In;

typedef struct{
	BYTE ucLogSeqNo[2];
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucPurseVersionNumber;
	BYTE ucPID[8];
	BYTE ucSignatureKeyKVN;
	BYTE ucCTC[3];
	BYTE ucTxnMode;
	BYTE ucTxnQuqlifier;
	BYTE ucSubAreaCode[2];
	BYTE ucTxnDateTime[4];
	BYTE ucEVBeforeTxn[3];
	BYTE ucTxnSNBeforeTxn[3];
	BYTE ucCardType;
	BYTE ucPersonalProfile;
	BYTE ucAreaCode;
	BYTE ucCardID[7];
	BYTE ucCardIDLen;
	BYTE ucTxnAmt[3];
	BYTE ucDeviceID[4];
	BYTE ucCPUDeviceID[6];
	BYTE ucSPID;
	BYTE ucCPUSPID[3];
	BYTE ucLocationID;
	BYTE ucCPULocationID[2];
	BYTE ucDeposit[3];
	BYTE ucIssuerCode;
	BYTE ucBankCode;
	BYTE ucLoyaltyCounter[2];
	BYTE ucTxnSN[3];
	BYTE ucEV[3];
	BYTE ucSignature[16];
	BYTE ucCPUSAMID[8];
	BYTE ucMAC_HCrypto[18];
	LastTxnLog_t stLastCreditTxnLogInfo_t;//33
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucRFU[16];
	BYTE ucStatusCode[2];
}ReadDongleDeduct_APDU_Out;
/***************************ReadDongleDeduct***************************/

/********************************SetValue******************************/
typedef struct{
	BYTE ucMsgType;
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTxnDateTime[4];
}SetValue_APDU_In;

typedef struct{
	BYTE ucCardType;
	BYTE ucPersonalProfile;
	BYTE ucCardID_4[4];
	BYTE ucIssuerCode;
	BYTE ucEV_2[2];
	BYTE ucExpiryDate[4];
	BYTE ucAreaCode;
	BYTE ucReaderFWVersion[6];
	BYTE ucSAMID[8];
	BYTE ucSAMSN[4];
	BYTE ucSAMCRN[8];
	BYTE ucDeviceID[4];
	BYTE ucSAMKeyVersion;
	BYTE ucSTAC[8];
	BYTE ucStatusCode[2];
}SetValue_APDU_Out;
/********************************SetValue******************************/

/******************************AuthSetValue****************************/
typedef struct{
	BYTE ucExpiryDate[4];
	BYTE ucHTAC[8];
	BYTE ucExpiryDateDOS[2];
}AuthSetValue_APDU_In;

typedef struct{
	BYTE ucStatusCode[2];
}AuthSetValue_APDU_Out;
/******************************AuthSetValue****************************/

/********************************TxRefund******************************/
typedef struct{
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucTxnDateTime[4];
	BYTE ucTxnAmt_2[2];
	BYTE ucTMTxnDateTime2[14];
	BYTE ucTMSerialNumber2[6];
	BYTE ucTxnDateTime2[4];
}TxRefund_APDU_In;

typedef struct{
	BYTE ucCardType;//0213
	BYTE ucPersonalProfile;//0214
	BYTE ucCardID_4[4];
	BYTE ucIssuerCode;
	BYTE ucBankCode;
	BYTE ucLoyaltyCounter[2];
	BYTE ucDeposit[2];
	BYTE ucEV_2[2];
	BYTE ucTxnAmt_2[2];
	BYTE ucExpiryDate[4];
	BYTE ucAreaCode;
	BYTE ucReaderFWVersion[6];
	BYTE ucSAMID[8];
	BYTE ucSAMSN[4];
	BYTE ucSAMCRN[8];
	BYTE ucDeviceID[4];
	BYTE ucSAMKeyVersion;
	BYTE ucSTAC[8];
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucCAVRTxnSNLSB;
	BYTE ucCAVRTxnDateTime[4];
	BYTE ucCAVRSubType;
	BYTE ucCAVRTxnAmt[2];
	BYTE ucCAVREV[2];
	BYTE ucCAVRSPID;
	BYTE ucCAVRLocationID;
	BYTE ucCAVRDeviceID[4];//108
	ReaderAVR_DATA_t stReaderAVR_t;//38
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucEV2_2[2];
	BYTE ucTxnAmt2_2[2];
	BYTE ucTMTxnDateTime2[14];
	BYTE ucTMSerialNumber2[6];
	BYTE ucStatusCode[2];
}TxRefund_APDU_Out;
/********************************TxRefund******************************/

/******************************AuthTxRefund****************************/
typedef struct{
	BYTE ucRFU4[4];
	BYTE ucHTAC[8];
	BYTE ucRFU2[2];
	BYTE ucLCDControlFlag;
}AuthTxRefund_APDU_In;

typedef struct{
	BYTE ucTxnSN_2[2];
	BYTE ucEV_2[2];
	BYTE ucMAC[10];
	BYTE ucConfirmCode[2];
	BYTE ucTxnSN2_2[2];
	BYTE ucEV2_2[2];
	BYTE ucMAC2[10];
	BYTE ucConfirmCode2[2];
	BYTE ucCTAC[8];
	BYTE ucStatusCode[2];
}AuthTxRefund_APDU_Out;
/******************************AuthTxRefund****************************/

/*****************************AutoloadEnable***************************/
typedef struct{
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucTxnDateTime[4];
}AutoloadEnable_APDU_In;

typedef struct{
	BYTE ucCardType;
	BYTE ucPersonalProfile;
	BYTE ucCardID_4[4];
	BYTE ucIssuerCode;
	BYTE ucBankCode;
	BYTE ucLoyaltyCounter[2];
	BYTE ucDeposit[2];
	BYTE ucEV_2[2];
	BYTE ucTxnAmt_2[2];
	BYTE ucExpiryDate[4];
	BYTE ucAreaCode;
	BYTE ucReaderFWVersion[6];
	BYTE ucSAMID[8];
	BYTE ucSAMSN[4];
	BYTE ucSAMCRN[8];
	BYTE ucDeviceID[4];
	BYTE ucSAMKeyVersion;
	BYTE ucSTAC[8];
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucCAVRTxnSNLSB;
	BYTE ucCAVRTxnDateTime[4];
	BYTE ucCAVRSubType;
	BYTE ucCAVRTxnAmt[2];
	BYTE ucCAVREV[2];
	BYTE ucCAVRSPID;
	BYTE ucCAVRLocationID;
	BYTE ucCAVRDeviceID[4];//108
	ReaderAVR_DATA_t stReaderAVR_t;//38
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucAutoLoadFlag;
	BYTE ucAutoLoadAmt_2[2];
	BYTE ucStatusCode[2];
}AutoloadEnable_APDU_Out;
/*****************************AutoloadEnable***************************/

/***************************AuthAutoloadEnable*************************/
typedef struct{
	BYTE ucHTAC[8];
	BYTE ucLCDControlFlag;
}AuthAutoloadEnable_APDU_In;

typedef struct{
	BYTE ucTxnSN_2[2];
	BYTE ucEV_2[2];
	BYTE ucMAC[10];
	BYTE ucConfirmCode[2];
	BYTE ucCTAC[8];
	BYTE ucStatusCode[2];
}AuthAutoloadEnable_APDU_Out;
/***************************AuthAutoloadEnable*************************/

/********************************AddValue******************************/
typedef struct{
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucTxnDateTime[4];
	BYTE ucTxnAmt_2[2];
}AddValue_APDU_In;

typedef struct{
	BYTE ucCardType;
	BYTE ucPersonalProfile;
	BYTE ucCardID_4[4];
	BYTE ucIssuerCode;
	BYTE ucBankCode;
	BYTE ucLoyaltyCounter[2];
	BYTE ucDeposit[2];
	BYTE ucEV_2[2];
	BYTE ucTxnAmt_2[2];
	BYTE ucExpiryDate[4];
	BYTE ucAreaCode;
	BYTE ucReaderFWVersion[6];
	BYTE ucSAMID[8];
	BYTE ucSAMSN[4];
	BYTE ucSAMCRN[8];
	BYTE ucDeviceID[4];
	BYTE ucSAMKeyVersion;
	BYTE ucSTAC[8];
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucCAVRTxnSNLSB;
	BYTE ucCAVRTxnDateTime[4];
	BYTE ucCAVRSubType;
	BYTE ucCAVRTxnAmt[2];
	BYTE ucCAVREV[2];
	BYTE ucCAVRSPID;
	BYTE ucCAVRLocationID;
	BYTE ucCAVRDeviceID[4];//108
	ReaderAVR_DATA_t stReaderAVR_t;//38
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucStatusCode[2];
}AddValue_APDU_Out;
/********************************AddValue******************************/

/******************************AuthAddValue****************************/
typedef struct{
	BYTE ucExpiryDate[4];
	BYTE ucHTAC[8];
	BYTE ucProfileExpiryDateDOS[2];
	BYTE ucLCDControlFlag;
}AuthAddValue_APDU_In;

typedef struct{
	BYTE ucTxnSN_2[2];
	BYTE ucEV_2[2];
	BYTE ucMAC[10];
	BYTE ucConfirmCode[2];
	BYTE ucCTAC[8];
	BYTE ucStatusCode[2];
}AuthAddValue_APDU_Out;
/******************************AuthAddValue****************************/

/****************************ReadCardDeduct****************************/
typedef struct{
	BYTE ucLogIndex;
}ReadCardDeduct_APDU_In;

typedef struct{
	LastTxnLog_t stCardDeductLog1_t;//33
	LastTxnLog_t stCardDeductLog2_t;//33
	LastTxnLog_t stCardDeductLog3_t;//33
	LastTxnLog_t stCardDeductLog4_t;//33
	LastTxnLog_t stCardDeductLog5_t;//33
	LastTxnLog_t stCardDeductLog6_t;//33
	BYTE ucStatusCode[2];
}ReadCardDeduct_APDU_Out;
/****************************ReadCardDeduct****************************/

/****************************ReadCodeVersion***************************/
typedef struct{
	BYTE ucSAMAppletVersion;
	BYTE ucSAMType;
	BYTE ucSAMVersion;
	BYTE ucReaderFWVersion[6];
	BYTE ucHostSpecVersionNo;
	BYTE ucStatusCode[2];
}ReadCodeVersion_APDU_Out;
/****************************ReadCodeVersion***************************/

/********************************Reboot********************************/
typedef struct{
	BYTE ucStatusCode[2];
}Reboot_APDU_Out;
/********************************Reboot********************************/

/*******************************SetValue2******************************/
typedef struct{
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucTxnDateTime[4];
	BYTE ucTxnAmt[3];
	BYTE ucReadPurseFlag;
	BYTE ucRefundFee[3];
	BYTE ucBrokenFee[3];
	BYTE ucLCDControlFlag;
	BYTE ucRFU[11];
}SetValue2_APDU_In;

typedef struct{
	BYTE ucPurseVersionNumber;
	BYTE bActivated			:1;
	BYTE bBlocked			:1;
	BYTE bRefunded			:1;
	BYTE bAutoLoad			:1;
	BYTE bCredit			:1;
	BYTE bRFU5			:1;
	BYTE bRFU6			:1;
	BYTE bRFU7			:1;
	BYTE ucAutoLoadAmt[3];
	BYTE ucPID[8];
	BYTE ucCPUAdminKeyKVN;
	BYTE ucCreditKeyKVN;
	BYTE ucCPUIssuerKeyKVN;
	BYTE ucCTC[3];
	BYTE ucTxnMode;
	BYTE ucTxnQuqlifier;
	BYTE ucExpiryDate[4];
	BYTE ucEV[3];
	BYTE ucTxnSN[3];
	BYTE ucCardType;
	BYTE ucPersonalProfile;
	BYTE ucProfileExpiryDate[4];
	BYTE ucAreaCode;
	BYTE ucCardID[7];
	BYTE ucCardIDLen;
	BYTE ucTxnAmt[3];
	BYTE ucHostSpecVersionNo;
	BYTE ucReaderFWVersion[6];
	BYTE ucDeviceID[4];
	BYTE ucCPUDeviceID[6];
	BYTE ucSPID;
	BYTE ucCPUSPID[3];
	BYTE ucLocationID;
	BYTE ucCPULocationID[2];
	BYTE ucDeposit[3];
	BYTE ucIssuerCode;
	BYTE HostAdminKeyKVN_SAMKVN[1];
	BYTE SAMID_STAC[8];
	BYTE SVCrypto_SAMCRN_SAMID[16];
	BYTE SAMSN[4];
	BYTE SubAreaCode_LoyaltyCounter[2];
	BYTE ucTMSerialNumber[6];
	LastTxnLog_t stLastCreditTxnLogInfo_t;//33
	//ReaderAVRAPDU_t stReaderAVRInfo_t;//83
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucRFU[31];
	BYTE ucStatusCode[2];
}SetValue2_APDU_Out;
/*******************************SetValue2******************************/

/******************************AuthSetValue2***************************/
typedef struct{
	BYTE ucExpiryDate[4];
	BYTE ucProfileExpiryDate[4];
	BYTE ucProfileExpiryDateDOS[2];
	BYTE ucTxnToken[16];
	BYTE ucHTAC[8];
	BYTE ucLCDControlFlag;
	BYTE ucRFU[5];
}AuthSetValue2_APDU_In;

typedef struct{
	BYTE ucTxnSN[3];
	BYTE ucEV[3];
	BYTE ucTxnDateTime[4];
	BYTE ucRFU[22];
	BYTE ucStatusCode[2];
}AuthSetValue2_APDU_Out;
/******************************AuthSetValue2***************************/

/********************************TxRefund2*****************************/
typedef struct{
	BYTE ucCardType;
	BYTE ucPersonalProfile;
	BYTE ucCardID_4[4];
	BYTE ucIssuerCode;
	BYTE ucBankCode;
	BYTE ucLoyaltyCounter[2];
	BYTE ucDeposit[2];
	BYTE ucEV_2[2];
	BYTE ucTxnAmt_2[2];
	BYTE ucTxmSn_2[2];
	BYTE ucRFU[2];
	BYTE ucAreaCode;
	BYTE ucReaderFWVersion[6];
	BYTE ucSAMID[8];
	BYTE ucSAMSN[4];
	BYTE ucSAMCRN[8];
	BYTE ucDeviceID[4];
	BYTE ucCPUDeviceID[6];
	BYTE ucSAMKeyVersion;
	BYTE ucSTAC[8];
	BYTE ucTMLocationID_6[6];
	BYTE ucTMID[2];
	BYTE ucTMTxnDateTime[14];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucCAVRTxnSNLSB;
	BYTE ucCAVRTxnDateTime[4];
	BYTE ucCAVRSubType;
	BYTE ucCAVRTxnAmt[2];
	BYTE ucCAVREV[2];
	BYTE ucCAVRSPID;
	BYTE ucCAVRLocationID;
	BYTE ucCAVRDeviceID[4];//108
	ReaderAVRAPDU_t stReaderAVRInfo_t;//83
	BYTE ucMsgType;
	BYTE ucSubType;
	BYTE ucEV2_2[2];
	BYTE ucTxnAmt2_2[2];
	BYTE ucTxmSn2_2[2];
	BYTE ucTMTxnDateTime2[14];
	BYTE ucTMSerialNumber2[6];
	BYTE ucStatusCode[2];
}TxRefund2_APDU_Out;
#ifdef __cplusplus
	}
#endif // __cplusplus

#endif
