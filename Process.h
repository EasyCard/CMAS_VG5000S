/* 
 * File:   Process.h
 * Author: T420s
 *
 * Created on 2013年9月22日, 上午 12:14
 */

#ifndef PROCESS_H
#define	PROCESS_H

#ifdef	__cplusplus
extern "C" {
#endif
USHORT Process_Autoload(int amt);
    USHORT Process_SendReversal(void);
    USHORT Process_SendOfflineTxAdvice(void);
    USHORT Process_ReBootCheckStatus(void);
    USHORT Process_CheckStatus(void);
    USHORT GetUnuploadTx(USHORT * Count);
    USHORT Process_SendAdvice3(BYTE SettleFlag);
    USHORT CheckNewVersionAP(void);
 USHORT Process_DownloadConfig(void);
USHORT Process_DownloadScript(void);
USHORT Process_TransComm(TRANS_DATA2 *TransData,BYTE dispstatus);
USHORT Process_TransComm2(TRANS_DATA2 *TransData,BYTE dispstatus);
int Process_SignOnRequest(TRANS_DATA2 *TransData);
int iProcess_ReadCardBasicData(void );
int iProcess_CheckBlockCard(BYTE * CardID);
int iProcess_LogLockCardData(int isw);
USHORT CheckSignOnPassword(void);
USHORT Process_Settle(void);
USHORT Process_StatusReport(void);
USHORT Process_SignOn(void);
USHORT Process_DownloadBLC(void);
USHORT Process_DownloadTMS(void);
USHORT Process_SendAdvice2(BYTE SettleFlag);
USHORT CheckNewVersionFile(void);
USHORT Process_SendAdvice(BYTE SettleFlag);
int iProcess_LockCard(BYTE * CardID);
USHORT Process_SendBackupTXLOGAdvice(STR * TxLogfile);
USHORT Process_SignOn2(void);
int iProcessWaitCard(void);
void* SendAdvice_Background(void);
USHORT Process_SendCurrentTxAdvice(void);
USHORT GetUnuploadTx2(USHORT *Count,long *UnuploadList);
USHORT Process_SendCurrentTxAdvice2(void);
void  Thread_SendCurrentTxAdvice(void);
void checkReaderChanged(void);
#ifdef	__cplusplus
}
#endif

#endif	/* PROCESS_H */

