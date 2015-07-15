#ifndef __APDU_H__
#define __APDU_H__

#ifdef __cplusplus
	extern "C" {
#endif

#include "dongle.h"
#include "Substruct.h"
            

            
#define Status_START						0
#define Status_RESET						1
#define Status_SIGNON						2
#define Status_SIGNONQUERY					3
#define Status_READCARDBASICDATA                                4
#define Status_TXNREQONLINE                                     5
#define Status_AUTHTXNONLINE                                    6
#define Status_TXNREQOFFLINE                                    7
#define Status_AUTHTXNOFFLINE                                   8
#define Status_LOCKCARD						9
#define Status_READDONGLEDEDUCT                                 10
#define Status_CARDSALE						11
#define Status_AUTHCARDSALE                                     12
#define Status_READCARDDEDUCT                                   13
#define Status_READCODEVERSION                                  14
#define Status_REBOOT						15
#define Status_SETVALUE						16
#define Status_AUTHSETVALUE					17
#define Status_AUTOLOADENABLE                                   18
#define Status_AUTHAUTOLOADENABLE                               19
#define Status_AUTHAUTOLOAD                                     20
#define Status_ONLINEDEDUCTVERIFY                               21    
#define Status_ReadCardNumber                                   22        
#define Status_END						23
            

/********************************TxRefund2*****************************/
        int inBuildReadCardCommand(ReadCardNumber_APDU_In * bAPDUReq);
 	int inBuildResetCommand(Reset_APDU_In *bAPDUReq);
       int inBuildSignOnCommand(SignOn_APDU_In *bAPDUReq);
       int inBuildReadCardBasicDataCommand(ReadCardBasicData_APDU_In *bAPDUReq);
	int inBuildTxnReqOnlineCommand(TxnReqOnline_APDU_In *bAPDUReq);
	int inBuildAuthTxnOnlineCommand(AuthTxnOnline_APDU_In *bAPDUReq);
	int inBuildTxnReqOfflineCommand(TxnReqOffline_APDU_In *bAPDUReq);
	int inBuildAuthTxnOfflineCommand(AuthTxnOffline_APDU_In *bAPDUReq);
      int inBuildLockCardCommand(LockCard_APDU_In_2 *bAPDUReq);
      int inBuildReadCardDeductCommand(ReadCardDeduct_APDU_In *bAPDUReq);
      int inGetTMInDataLen(int inTxnType);
	void vdSaveReqData(char *bFileName,BYTE *bSaveData,int inSaveLen);
	 void vdLoadReqData(char *bFileName,BYTE *bLoadData,int inLoadLen);
	 void vdToUpper(char *szOutData,char *szInData);
         USHORT usBuildTMInfo(TM_INFO *tm);
//	extern void vdSaveTxnData(int inTxnField,BYTE *bSaveData);
//	extern void vdLoadTxnData(int inTxnField,BYTE *bLoadData);
	
	
#ifdef __cplusplus
	}
#endif // __cplusplus

#endif
