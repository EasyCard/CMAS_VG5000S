/* 
 * File:   TransData2.h
 * Author: T420s
 *
 * Created on 2013年9月27日, 上午 8:32
 */

#ifndef TRANSDATA2_H
#define	TRANSDATA2_H

#ifdef	__cplusplus
extern "C" {
#endif

void T5595GetParameter(void);    
USHORT UnpackTMSParameter(void);    
USHORT usUnFormatTMSTag(ezxml_t Tag);
USHORT  usFormatTransTag3(TRANS_DATA2 * TransData,BYTE * TAG,BYTE * NAME, BYTE * TransLog);
USHORT usFormatTransTag2(TRANS_DATA2 *TransData, BYTE * TAG ,BYTE * NAME, ezxml_t TransLog);
USHORT usUnFormatTransTag2(TRANS_DATA2 *TransData, ezxml_t node);
USHORT usUnFormatTransTag3(TRANS_DATA2 *TransData,char* NodeName,char * NodeData);
int inBuildResetOutput_2(int inTxnType,TRANS_DATA2 *Trans, Reset_APDU_In *DongleIn, Reset_APDU_Out *DongleOut);
int inBuildSignOnOutput_2(int inTxnType,TRANS_DATA2 *Trans,SignOn_APDU_In *DongleIn,SignOn_APDU_Out *DongleOut);
int inBuildSignOnQueryOutput_2(int inTxnType,SignOnQuery_APDU_Out *Trans,SignOnQuery_APDU_Out *DongleOut);
int inBuildTxnReqOnlineOutput_2(int inTxnType,TRANS_DATA2 *Trans,TxnReqOnline_APDU_In *DongleIn,TxnReqOnline_APDU_Out *DongleOut);
int inBuildAuthTxnOnlineOutput_2(int inTxnType,TRANS_DATA2*Trans,AuthTxnOnline_APDU_In *DongleIn,AuthTxnOnline_APDU_Out *DongleOut,TxnReqOnline_APDU_Out *TxnReqOut);
int BuildTxnReqOfflineOutput_2(int inTxnType,TRANS_DATA2 *Trans,TxnReqOffline_APDU_In *DongleIn,TxnReqOffline_APDU_Out *DongleOut);//
int inBuildAuthTxnOfflineOutPut_2(int inTxnType,TRANS_DATA2 *Trans,AuthTxnOffline_APDU_In *DongleIn,AuthTxnOffline_APDU_Out *DongleOut);//,TxnReqOffline_APDU_Out *TxnReqOut
//int inBuildLockCardDataOutput1_2(int inTxnType,TRANS_DATA2 *Trans,LockCard_APDU_Out_2 *DongleOut,BYTE *ucTxnDateTime,BYTE ucLockReason,BYTE *ucTMLocationID,BYTE *ucTMID);
int inBuildLockCardDataOutput1_2(TRANS_DATA2 *Trans,LockCard_APDU_Out_2 *DongleOut,BYTE ucLockReason);
int inBuildLockCardDataOutput2_2(TRANS_DATA2 *Trans,LockCard_APDU_Out_3 *DongleOut,BYTE ucLockReason);
int inBuildSetValueData_2(TRANS_DATA2 *Trans,SetValue_APDU_Out *DongleOut);
int inBuildAuthSetValueData_2(TRANS_DATA2 *Trans,AuthSetValue_APDU_Out *DongleOut);
//USHORT usUnFormatTransTag2(TRANS_DATA *TransData, ezxml_t node);
long BYTE3Data2LONG(BYTE * data);
USHORT UpdateSystemInfo(void);
USHORT CheckConfig2Status(void);
USHORT CheckConfig3Status(void);
#ifdef	__cplusplus
}
#endif

#endif	/* TRANSDATA2_H */

