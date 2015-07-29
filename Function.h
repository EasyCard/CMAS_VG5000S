/* 
 * File:   Function.h
 * Author: T420s
 *
 * Created on 2013年7月23日, 下午 3:34
 */

#ifndef FUNCTION_H
#define	FUNCTION_H

#ifdef	__cplusplus
extern "C" {
#endif
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "dongle.h"
#include "apdu.h"
#include "tm.h"
#include "trans.h"
#define LINUX_API		1
#define API_VERSION		"\x02\x01\x03"

	#pragma pack(push,1)
	#pragma pack(1)
	typedef struct BLC
	{
	UINT CardNb;
	BYTE Reason;
	} BLC;
	#pragma pack(pop)

typedef struct{//將資料儲存在此,好讓下一個交易使用!!
	BYTE ucDeviceID[4];
	BYTE ucTxnDateTime[4];
	BYTE ucTxnDateTime2[4];
	BYTE ucCPUDeviceID[6];
	BYTE ucSTC[4];
	BYTE ucTMLocationID[10];
	BYTE ucTMID[2];
	BYTE ucTMSerialNumber[6];
	BYTE ucTMAgentNumber[4];
	BYTE ucTMTxnDateTime[14];
}Store_Data;

typedef struct{
	int inResponseLen_9000;//OK
	int inResponseLen_6103;//CPD
	int inResponseLen_610F;//二代卡餘額異常
	int inResponseLen_6304;//未先Reset
	int inResponseLen_6305;//未先SignOn
	int inResponseLen_6308;//更新參數
	int inResponseLen_6403;//餘額不足
	int inResponseLen_6406;//API鎖卡
	int inResponseLen_640E;//餘額檢查錯誤
	int inResponseLen_6415;//Online
	int inResponseLen_6418;//通路限制使用
}APDU_Response_Data_Len;

#define WM_DONGLE_GETDATA    WM_APP+9001
#define WM_DONGLE_ERROR      WM_APP+9002
#define WM_DONGLE_TIMEOUT    WM_APP+9003//1.0.5.5

#define Plus		0x2b
#define Minus		0x2d
#define DECIMAL     10
#define HEX         16

#define MIFARE		0x00
#define LEVEL1		0x01
#define LEVEL2		0x02

#define DEFAULT_TIMEOUT			240
#define SEARCH_CARD_TIMEOUT		1100

#define API_STATUS_CNT			4

#define API_STATUS_START		0
#define API_STATUS_REQUEST_OK		1
#define API_STATUS_REPONSE_OK		2
#define API_STATUS_TIMEOUT		3

#define OUT_DATA_OFFSET		3
#define IN_DATA_OFFSET		8

#define NETWORK_MANAGEMENT_CODE		"079"

#define TXN_REQ_DATA		"TxnReqData"
#define TXN_DATA_FIELD		"TxnDataField"
#define TXN_INPUT_DATA		"TMInputData"
#define TXN_INPUT_DATA_LEN		200

//#define LOCATION_ID			0x01
#define LOCATION_ID_BATCH		"01"

typedef union
{
	short Value;
	unsigned char Buf[2];
}UnionShort;
         USHORT SetRTC(BYTE * Date,BYTE * Time);
	extern BYTE   checksum(int length,BYTE data[]);
	extern BOOL   fnWriteLog(BYTE *Msg,BYTE *Data, long Len);
	extern void   vdPad(BYTE *bInData,BYTE *bOutData,int inOutSize,char fFlag,char chFiller);
	extern BOOL   fnASCTOBIN(BYTE *OutData,BYTE ASCData[],int sizex,int OffsetBit,int mode);
	extern void   fnBINTODEVASC(BYTE *BINData,BYTE *ASCDATA,int ASCSize,char fPurseVersion);
	extern UINT   fngetUnixTimeCnt(BYTE *OutDate,BYTE *date);
	extern void   fngetDosDateCnt(BYTE *date,BYTE *DosDate);
	extern int inTSCCChkSpecialYear(int inYear);
	extern int    fnLogFileProcedure(int inPort,char *chPath);
	extern void   fnLogResult(unsigned long ulHandle, unsigned int uiResult ,  unsigned int uiErrNb , long iRfu) ;
	extern void   fnLongToUnix(BYTE Unixdate[],unsigned long *UnixSec,int size);
	extern void vdIntToAsc(BYTE *bInData,int inInSize,BYTE *bOutData,int inOutSize,char chFiller,int inRadix);
	extern void vdUIntToAsc(BYTE *bInData,int inInSize,BYTE *bOutData,int inOutSize,char chFiller,int inRadix);
        extern void vdUIntToAsc2(BYTE *bInData,int inInSize,BYTE *bOutData,int inRadix);
	extern void   fnUnPack(BYTE *BINData,int BINSize,BYTE *ASCDATA);
	extern void fngetDosDate(BYTE *bDosDate,BYTE *bOutDate);
	extern char *chGetAPITypeName(int inIndex);
	extern int inRequestFlowCkeck(int inAPITxnType);
	extern int inReponseFlowCkeck(int inAPITxnType);
	extern int inGetAPIType(PVOID *pArguments);
	extern int inReaderCommand(int inTxnType);
	extern void vdWriteDongleLog(int inTxnType,int inRet,char *sTxnName,BYTE *bWriteData,int inWriteLen);
	extern int inReponseDefaultCkeck(BYTE *cOutputData,int inAPITxnType);
        
#ifdef WINDOWS_API
	extern DWORD   WINAPI    ThdRequestFunction(PVOID *pArguments);
#endif
	extern void vdBuildMessageType(int inTxnType,BYTE *cOut);
        extern void vdBuildMessageType2(BYTE inTxnType,BYTE TxnStatus,BYTE *cOut);
        void vdBuildProcessingCode2(TRANS_DATA2 *TransData,BYTE *cOut);
	extern void vdBuildProcessingCode(int inTxnType,BYTE ucMsgType,BYTE ucSubType,BYTE ucPersonalProfile,BYTE *cOut);
	extern int inGetDongleInData(int inTxnType,int inDataName);
	extern int inGetDongleOutData(int inTxnType,int inDataName);
	extern void vdCountEVBefore(BYTE *bAmt,int inAmtSize,BYTE *bEV,int inEVSize,BYTE *bEVBefore,int inEVBeforeSize,BYTE ucMsgType);

	
	extern void vdAmt2ByteTo3Byte(BYTE *bIn2Amt,BYTE *bOut3Amt);
	extern void vdUnPackAmt2ByteTo3Byte(BYTE *bIn2Amt,BYTE *bOutAmt);
       
      void TRACE_(const char* msg);
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       USHORT  File_exist(char *filename);
       ULONG File_GetLen(char * filename);
       USHORT usReadFileData(BYTE * strFilename,ULONG *iSize,BYTE * bData);
       int   CreateDir(const   char   *sPathName);
       USHORT usAppendFile(BYTE *strFileName,BYTE *bData,int size);
       USHORT usWriteFile(BYTE *strFileName,BYTE *bData,int size);

	void fnGetRTCDOSData(BYTE *DOSDate);
	void fnGetRTCUNIXDataTime(unsigned long *UnixSec);
        int copyFiles(char *source, char *destination);
        void oops(char *s1, char *s2);
        USHORT UpdateAP(void);
        USHORT CheckSDCARD(void);
        USHORT CTOS_ReadFile(STR * Filename,BYTE * Data,ULONG *Datelen);
        USHORT CTOS_WriteFile(STR * Filename,BYTE * Data,ULONG Datelen);
        void CheckMemoarystatus(void);
        void Housekeeping(void);
        USHORT PowerOff(void);
        void BarcodeScannerInput(void);
        USHORT DumpBackupTxLog2USB(void);
        int ezSystemReset(void);//2014.04.11, kobe added for ECR
        USHORT DumpBackupTxLog2USB(void);
        void ezPowerOff(void);
        USHORT usReadFileData2(BYTE * strFilename,int offset,ULONG *iSize,BYTE * bData);
        BOOL IsPortable(void);
        void dumpByteArrayToHexString(BYTE *, int, BYTE *);
        void PowerSaving(void);
        void CopyFiletoUSB(char *source, char *destination);
        void copyFileFromUSB(char *source, char *destination);         
        int copyFiles2(char *source, char *destination);
#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTION_H */

