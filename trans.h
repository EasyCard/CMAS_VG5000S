/* 
 * File:   trans.h
 * Author: T420s
 *
 * Created on 2013年8月16日, 下午 2:54
 */

#ifndef TRANS_H
#define	TRANS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Apdu.h"
#include "Substruct.h"   
    
typedef struct{
	BYTE ucOneDayQuotaFlag[2];
	BYTE ucOneDayQuota[4];
	BYTE ucOnceQuotaFlag[2];
	BYTE ucOnceQuota[4];
	BYTE ucCheckEVFlag[2];
	BYTE ucAddQuotaFlag[2];
	BYTE ucAddQuota[6];
	BYTE ucCheckDeductFlag[2];
	BYTE ucCheckDeductValue[4];
	BYTE ucDeductLimitFlag[2];
	BYTE ucAPIVersion[8];
	BYTE ucRFU[10];
        BYTE empty;
}TERMHOST;
typedef struct{
	BYTE ucAdminKeyKVN[2];
	BYTE ucCreditKeyKVN[2];
	BYTE ucDebitKeyKVN[2];
}CPUCARDKEY_INFO;
typedef struct{
	BYTE ucRemainderAddQuota[6];
	BYTE ucDeMAC[16];
        BYTE ucCancelCreditQuota[6];
        BYTE ucRFU[36];
        BYTE empty;
}TERMPARA;

       typedef struct{
        BYTE ucSAMVersion[2];            
        BYTE SAMUsageControl[6];
        BYTE ucSAMAdminKVN[2];
        BYTE SAMIssuerKVN[2];
        BYTE TagListtable[80];
        BYTE ucSAMIssuerSpecData[64];    
        BYTE empty;
    }CPUSAMINFO;

    typedef struct{
        BYTE ucAuthCreditLimit[6];
        BYTE ucAuthCreditBalance[6];
        BYTE ucAuthCreditCumulative[6];
        BYTE ucAuthCancelCreditCumulative[6];
        BYTE null;
    }SAMTRANSINFO;
     typedef struct{
        BYTE ucAuthCreditLimit[3];
        BYTE ucAuthCreditBalance[3];
        BYTE ucAuthCreditCumulative[3];
        BYTE ucAuthCancelCreditCumulative[3];
     }SAMTRANSINFO2;
    typedef struct{
        BYTE SAMUPDATEOPTION[2];
        BYTE NEWSAMVALUE[80];
        BYTE UpdateSAMVALUEMAC[32];
        BYTE empty;
    }CPUSAMPARAMETERSETTINGDATA;
 typedef struct{
        BYTE SAMUPDATEOPTION[1];
        BYTE NEWSAMVALUE[40];
        BYTE UpdateSAMVALUEMAC[16];
      
    }CPUSAMPARAMETERSETTINGDATA2;
 
     typedef struct{
        BYTE ucPreCPUDeviceID[12 ];
        BYTE ucPreSTC[8];
        BYTE ucPreTxnDateTime[8];
        BYTE ucPreCreditBalanceChangeFlag[2];
        BYTE ucPreConfirmCode[4];
        BYTE ucPreCACrypto[32];
        BYTE empty;
    }CPULASTSIGNONINFO;
  typedef struct{
        BYTE ucPreCPUDeviceID[6 ];
        BYTE ucPreSTC[4];
        BYTE ucPreTxnDateTime[4];
        BYTE ucPreCreditBalanceChangeFlag;
        BYTE ucPreConfirmCode[2];
        BYTE ucPreCACrypto[16];
     
    }CPULASTSIGNONINFO2;
 
    
  typedef struct{
        USHORT usBATCHNO; 
        BYTE ucTXTYPE;
	ULONG usTXSN; 
        BYTE ucTXSTATUS;
        BYTE ucAdviceFLAG;	
        BYTE ucMsgType;
        BYTE ucSubType;
        BYTE ucReadPurseFlag;
        BYTE ucLCDControlFlag;
        BYTE ucMessageType[4+1];                                //0100
        BYTE ucCardID[7];                                    //0200
        BYTE ucPID[8+1];                                       //0211
        BYTE ucBasicData_Autoloadflag;                     //0212        
        BYTE ucBasicData_CardType;                         //0213
        BYTE ucBasicData_CardProfile;                      //0214
        BYTE ucProcessCode[6+1];       			 //0300
       // UINT uiDongleVersion;      //0301
        LONG lTxnAmt;            //0400
        LONG lDeductAMT;         //0403
        LONG lADDAMT;            //0407
        LONG lEVafterTxn;          //0408
        LONG lAutoloadAMT;         //0409        
        LONG lEVBeforeTxn;         //0410
        BYTE ucTxnDateTime[14+1];       //0700
        ULONG ulTerminalInvoiceNum;      //1100
        ULONG  ulTMTxnSN;            //1101
        BYTE ucTxnTime[6+1];       //1200
        BYTE ucTMTxnTime[6+1];       //1201
        BYTE ucTxnData[8+1];       //1300 
        BYTE ucTMTxnData[8+1];       //1300 
        BYTE ucCardExpiryDate[4];     //1401 n4 yymm
        BYTE ucCardVaildDate[4];      //1402 
        BYTE ucCardVaildDateAfterSet[4]; //1403 yyyymmdd
        BYTE ucRRN[14+1];               //3700 T1300+T1100
        BYTE ucTMINVOICENO[20+1];              //3701        
        BYTE ucTxnAuthNum[6+1];         //3800
        BYTE ucResponseCode[2+1];       //3900
        BYTE ucSVCSResponseCode[2+1];   //3903
        BYTE ucCPUDeviceID[6];         //4100 NEW DEVICE ID ucTerminalID
        BYTE ucDeviceID[4];         //4100 NEW DEVICE ID ucTerminalID
        BYTE ucTerminalIP[15+1];         //4102                                  //4101
        BYTE ucMechineID[20];           //4103
        BYTE ucReaderSN[4];            //4104
        BYTE POSID[30];                //4017 POS ID 20150522新增 for 司機代碼 or 路線代碼       
        BYTE ucCPUSPID[3];                                                //4200 ucMerchantID
        BYTE ucSPID;
        BYTE ucSubMerchantID[2];        //4210
        BYTE ucLocationID;
        BYTE ucCPUPurseVersionNUM; //4800
        BYTE ucCardAVRDATA[45];           //4801
        BYTE ucIssuerCode;         //4802
        BYTE ucBankCode;           //4803
        BYTE ucAreaCode;           //4804
        BYTE ucCPUSubAreaCode[2];     //4805
        BYTE ulProfileExpiryDate[4];  //4806
        BYTE ucNEWProfileExpiryDate[4];//4807
        ULONG  ulCardTxnSN;          //4808
        BYTE ucCPUTxnMode;         //4809
        BYTE ucCPUTQ;              //4810
        ULONG  ulSNBeforeTxn;        //4811
        BYTE ucCTC[3];                //4812
        USHORT usLoyaltyCounter;    //4813
        LONG ulDepositValue;      //4814
         USHORT usCustomerFee;    //4817
        BYTE ucANOTHEREV[3];     //4818
        BYTE ucLockReason;		//4819
        BYTE ucHostSpecVersionNo;  //4820
     
	 BYTE ucCardParameter_CardOneDayQuota[3];	//4821
	 BYTE ucCardParameter_CardOneDayQuotaDate[2]; //4821�魭�B�B�� ���  

	 BYTE ucCardAutoloadParameters_AutoloadFlag;//4822
	 BYTE ucCardAutoloadParameters_AutoloadValue;//4822
        BYTE ucOneDayQuotaWrite;//4823
        BYTE ucCPDReadFlag;        //4824     
        BYTE ucCPUCreditBalanceChangeFlag;//4825
        BYTE ucChipIDLength;       //4826
      //  BYTE ucCPUCardParameters[10+1];//4827

        BYTE CardOneDayQuota_BeforeTX[3];//4827
	 BYTE CardOneDayQuotaDate_BeforeTX[2];//4827
        BYTE ucPersonalProfileAuth;//4828
        BYTE ucMicroPaymentSetting;//4829
        BYTE ucKeyVersion;         //5301
        BYTE ucAdminKeyKVN;	//5302
	 BYTE ucCreditKeyKVN;	//5302
	 BYTE ucDebitKeyKVN;    //5302
        BYTE ucCPUHashTYPE;        //5303
        BYTE ucCPUHostadminKVN;    //5304
        BYTE ucSigntureKeyKVN;     //5305
        BYTE ucCPUEDC[3];             //5306
        BYTE ucRSAM[8];              //5307
        BYTE ucRHOST[8];            //5308
        BYTE ucSAMID[8];             //5361
        BYTE ucSAMSN[4];            //5363
        BYTE ucSAMCRN[8];            //5363
        CPUSAMInfo_t CPUSAMINFOData;        //5364             
        SAMTRANSINFO2  SAMtransInfoData;   //5365      
        BYTE ucSingleCreditTxnAmtLimit[3]; //5366
        CPUSAMPARAMETERSETTINGDATA2 CSAMPARA;    //5367
        BYTE ucSTC[4];      //5368
        BYTE ucSAMSignOnControlFlag;             //5369
        CPULASTSIGNONINFO2 CPULastSignonInfoData;//5370
        BYTE ucCPUSAMID[8];                   //未加入       
        BYTE ucBatchNo[8+1];                    //5501
        ULONG ulSTCode;                    //5503 STCODE
        BYTE ucTMPOSID[6+1];                         //5504 �T�w 000000
        BYTE EDCTYPE;                      //5509
        BYTE ucTMAgentNumber[4+1];                                       //5510        
        BYTE ucTMTxnDateTime[8+1];                                        //5514
        BYTE ucOrgTxnTerminalID[6];           //5581
        BYTE ucOrgTxnRRN[14+1];                 //5582
        BYTE ucOrgTxnDate[8+1];                 //5583
     
        BYTE ucDeductStatus;               //558901
        ULONG ulSettle_TotleCnt;              //5591
        LONG  lSettle_TotleAmt;            //5592
      
  
        BYTE ucReaderFWVersion[6];           //6000
        BYTE ReaderAVRDATA[33];              //6001
        TermHost_t stTermHostInfo_t;		//6002
	TermPara_t stTermParaInfo_t;		//6003  
        ULONG ulBLVersion;                                        //6004
        BYTE ucSTAC[8];                        //6400
        BYTE HTAC[8];                        //6401
        BYTE CTAC[8];                        //6402
        BYTE MAC[4];                         //6403        
        BYTE CPUMAC_HCrypto[16];              //6404
        BYTE CPUSignature[16];                //6405
        BYTE CPUTermCrypto[16];               //6406  ucCACrypto
        BYTE HostCrypto[16];                  //6407
        BYTE ucSATOKEN[16];                   //6408
        BYTE HostToken[16];                   //6409  
     
        BYTE end;
    }TRANS_DATA2;
USHORT CheckResponseCode(STR * TYPE, USHORT Respcode);
USHORT SaveTransData(TRANS_DATA2 *TransData);
USHORT Function_Signon(void);
USHORT Trans_DeductOffline(void);
USHORT CheckCMASResponseCode(char * Respcode);
USHORT Trans_Deduct(void);
USHORT Trans_Cancel(void);
USHORT Trans_Refund(void);
USHORT ShowBalance(void);  
USHORT ShowTXBalance(int amt);
USHORT Function_Signon_forMaintenance(void);
USHORT Trans_ADD(void);
USHORT Trans_AutoloadEnable(void);
USHORT ShowBalanceAndInputAmt(int TxType,USHORT *amt);
USHORT InputAMT(int TxType,USHORT *amt);
USHORT GetAutoDeductAmt(void);
USHORT CheckCardProfile(int PersonalProfile,int CardType);
USHORT GetCard_PersonalProfile(BYTE *strPersonalProfileName);
USHORT CheckSVCSResponseCode(STR * TYPE, BYTE *Respcode);
USHORT Trans_SetValue(void);
int iProcessWaitCardwithTimer(int sec);
void Process_AfterTXSueeess(void);
USHORT Trans_Deduct2(void);//購貨交易
USHORT Trans_Deduct_Auto(void);
USHORT checkTxnLimit(void);
USHORT Trans_Deduct_Auto4Speed(void);//購貨交易;
#ifdef	__cplusplus
}
#endif

#endif	/* TRANS_H */

