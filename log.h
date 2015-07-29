/* 
 * File:   log.h
 * Author: T420s
 *
 * Created on 2013年7月30日, 上午 9:56
 */

#ifndef LOG_H
#define	LOG_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "ezxml.h"
#include "trans.h"
USHORT usUpdataTxData(TRANS_DATA2 * TransData); 
USHORT UpdateAdviceTxStatus(void);
   USHORT BuildAdviceTxFile(void);
void vSetTxMessage(BYTE TXTYPE);
void vGetTxTitleStr(BYTE TXTYPE,STR * Title);
void vGetTxInfo(BYTE TXTYPE);
USHORT	usGetTXTYPE_TRANSTYPE(USHORT inTxnType);
USHORT usGetTransStatusSTR(int TransType,int TransStatus,STR * TransStatusSTR);

USHORT usSaveTxData(TRANS_DATA2 * TransData);
USHORT usGetTxData(TRANS_DATA2 * TransData,ULONG TxSN);
USHORT CheckUnuploadTxCount(void);
USHORT usInitTxData(BYTE TXTYPE);
USHORT GetLastTransData( TRANS_DATA2 *TransData);
USHORT SaveBackupTxData(TRANS_DATA2 *TransData);
void TestMakeTransData(void);
USHORT SaveBackupTxData(TRANS_DATA2 *TransData);
void Debug_SendData(char * title,char * Data,int len);
USHORT SaveTCPDatatoSD(char* SendFILE,char * ReceiveData,int ReceiveDatalen);
USHORT FLASHERROR(void);
USHORT CheckFLASHSTATUS(void);
#ifdef	__cplusplus
}
#endif

#endif	/* LOG_H */

