/* 
 * File:   Batch.h
 * Author: T420s
 *
 * Created on 2013年9月5日, 上午 8:09
 */

#ifndef BATCH_H
#define	BATCH_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "ezxml.h"
    
typedef struct{
    USHORT usBatchSN;
    BYTE  ucBatchSN[8+1];
    BYTE  DEVICEID[6+1];
    ULONG TotleCnt;
    ULONG TotleAMT;
    ULONG ADDVALUENETCnt;
    ULONG ADDVALUENETAMT;
    ULONG DEDUCTNETCnt;
    ULONG DEDUCTNETAMT;
    ULONG ADDCnt;
    ULONG ADDAMT;
    ULONG DEDUCTCnt;
    ULONG DEDUCTAMT;
   // ULONG VOIDCnt;
  //  ULONG VOIDAMT;	
    ULONG ADDVOIDCnt;
    ULONG ADDVOIDAMT;	
    ULONG DEDUCTVOIDCnt;
    ULONG DEDUCTVOIDAMT;	
    ULONG REFUNDCnt;
    ULONG REFUNDAMT;
    ULONG BLACKCARDCNT;  
    ULONG AUTOLOADCnt;
    ULONG AUTOLOADAMT;
    ULONG AUTOLOADENABLECNT;
    ULONG SALECARDCnt;
    ULONG SALECARDAMT;
    ULONG RETURNCARDCnt;
    ULONG RETURNCARDAMT;    
    ULONG SETVALUECNT;   
    ULONG CntByProfile[10];
    ULONG AMTByProfile[10];	
  }Batch_Totle_STRUCT;  
      

  
  
USHORT  usUpdateBatchSN(void);
USHORT  Disp_BatchData( Batch_Totle_STRUCT *BatchTotal);
USHORT   usCloseBatch(void);
USHORT Show_BatchData(void);
USHORT CheckBatchCount(void);
USHORT InitBatchTotal(void);
USHORT GetBatchTotal(void);
USHORT SavetBatchTotal(void);
USHORT SavetBatchTotal(void);
USHORT usSetCurrBatchDevID2(BYTE * DeviceID);
USHORT GetBatchTotal_DevID(BYTE * DeviceID);
USHORT BatchUpdateCounterData(BYTE TxType,int AMT);
USHORT usGetCurrBatchSN(BYTE * bBatchSN,USHORT * usBatchSN );
USHORT SaveBackupBatchData(void);
USHORT PrintSettlementReceipt(Batch_Totle_STRUCT *BatchTotal);
USHORT  GetBatchSN(STR*);
USHORT SAVEBatchSN(STR*);
#ifdef	__cplusplus
}
#endif

#endif	/* BATCH_H */

