/* 
 * File:   Blc.h
 * Author: T420s
 *
 * Created on 2013年7月24日, 上午 10:43
 */

#ifndef BLC_H
#define	BLC_H

#ifdef	__cplusplus
extern "C" {
#endif

#pragma pack(push,1)
#pragma pack(1)
#define BLCFileName "BLCFILE"
typedef struct BLC_HEADER
{
	BYTE ucFileHead[4];
	BYTE ucFileData[8];
	BYTE ucFileTime[6];
	BYTE ucSISVerNo;
	BYTE ucSISSubNo;
	BYTE ucBlockingIDFlag;
	BYTE ucFileEnd[4];
} BLC_HEADER;

typedef struct BLC_DATA
{
	BYTE ucCardID[8];
	BYTE Reason;
} BLC_DATA;

typedef struct BLC_END
{
	BYTE ucFileTail[4];
	BYTE ucCheckCode;
	BYTE ucFileHash[16];
	BYTE ucDataCnt[8];
	BYTE ucFileEnd[3];
} BLC_END;

#pragma pack(pop)

	int compare(const void *arg1, const void *arg2);
	int compare2(const void *a, const void *b);
	int fnMaintainBLC(void);
	char fIsCheckBLC(int inTxnType,BYTE *bAPDUOut);
	int inCheckBLC(BYTE *ucCardID);
	void vdMemoryLog(int inIndex);
	int inBLCLockCard(int inTxnType,BYTE *CardID,BYTE *TxnDateTime);



#ifdef	__cplusplus
}
#endif

#endif	/* BLC_H */

