# include <stdio.h>
# include <time.h>
# include <dirent.h>
# include <string.h>
//# include <io.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/stat.h>

#include "function.h"
#include "apdu.h"
#include "tm.h"
#include "gvar.h"
#include "blc.h"
#include "com.h"




//compare black list version
int compare(const void *arg1, const void *arg2)
{
    
	 return(strcmp(*(char**)arg2,*(char**)arg1));
}



//compare card nb of black list content
int compare2(const void *a, const void *b)
{
INT64 llnA = 0L,llnB = 0L;

	memcpy((char *)&llnA,*(char**)a,7);
	memcpy((char *)&llnB,(char**)b,7);
	if(llnA > llnB)
		return(1);
	else if(llnA < llnB)
		return(-1);
	else
		return(0);

}

//---------------------------------------------------------------------//


char fIsCheckBLC(int inTxnType,BYTE *bAPDUOut)
{

	if(inTxnType != Status_TXNREQOFFLINE)
		return(FALSE);//不檢查黑名單

	if(bAPDUOut[2] != sizeof(TxnReqOffline_APDU_Out))
		return(FALSE);//不檢查黑名單

	if(!memcmp(&bAPDUOut[OUT_DATA_OFFSET + bAPDUOut[2] - 2],"\x90\x00",2))
		return(TRUE);//需檢查黑名單

	if(!memcmp(&bAPDUOut[OUT_DATA_OFFSET + bAPDUOut[2] - 2],"\x64\x03",2))
		return(TRUE);//需檢查黑名單

	return(FALSE);//不檢查黑名單
}




int inCheckBLC(BYTE *ucCardID)
{
  
        int inRetVal;
        long lnFileLength,lnBLCCnt;
        FILE *fp = NULL;
        BLC_DATA *lpBLC = NULL,*lpsBLC = NULL,srBLC;
        BLC_HEADER srBLCHeader;
        BLC_END srBLCEnd;
  
//	if(fnMaintainBLC() != SUCCESS)
//		return(DONGLE_BLOCKCARD_NOT_FIND);
        fp = fopen((char *)BLCFILE,"rb");
 	
	if(fp ==NULL)
	{
		fnWriteLog((BYTE *)"inCheckBLC  fopen FALSE",BLCFILE,strlen((char *)BLCFILE));
		return DONGLE_OPENFILE_ERROR;
	}

	inRetVal = fseek(fp,0,SEEK_END);
	if(inRetVal != 0)
	{
		fclose(fp);
		fnWriteLog((BYTE *)"inCheckBLC  fseek FALSE",NULL,0);
		return DONGLE_FSEEK_ERROR;
	}

 	lnFileLength = ftell(fp);//取得檔案大小 單位byte
 	if((lnFileLength - (sizeof(BLC_HEADER) + sizeof(BLC_END))) % sizeof(BLC_DATA))
 	{
 		fclose(fp);
		fnWriteLog((BYTE *)"inCheckBLC  lnFileLength FALSE",(BYTE *)&lnFileLength,4);
		return DONGLE_FSEEK_ERROR;
 	}

 	lnBLCCnt = (lnFileLength - (sizeof(BLC_HEADER) + sizeof(BLC_END))) / sizeof(BLC_DATA);
   	rewind(fp);//移動指標回檔案起始
	//lpBLC = (BLC_DATA*)malloc(lnBLCCnt * sizeof(BLC_DATA));
        lpBLC = malloc(lnBLCCnt * sizeof(BLC_DATA));
	if(lpBLC == NULL)
	{
		fclose(fp);
		fnWriteLog((BYTE *)"inCheckBLC  malloc FALSE",NULL,0);
		return DONGLE_MALLOC_ERROR;
	}
#if 1
    
	memset(&srBLCHeader,0x00,sizeof(BLC_HEADER));
	inRetVal = fread(&srBLCHeader,sizeof(BLC_HEADER),1,fp);
	gsBlackListVersion[20] = srBLCHeader.ucBlockingIDFlag;
#else
	fseek(fp,sizeof(BLC_HEADER),SEEK_SET);
#endif
 
	//inRetVal = fread(lpBLC,sizeof(BLC_DATA),lnBLCCnt,fp);
        inRetVal = fread(lpBLC,1,lnBLCCnt*sizeof(BLC_DATA),fp);
	inRetVal = ferror(fp);
	if(inRetVal != 0)
	{
		fclose(fp);
		free(lpBLC);
		fnWriteLog((BYTE *)"inCheckBLC  ferror FALSE",NULL,0);
		return DONGLE_FERROR_ERROR;
	}
#if 1
     
	memset(&srBLCEnd,0x00,sizeof(BLC_END));
	inRetVal = fread(&srBLCEnd,sizeof(BLC_END),1,fp);
#endif
       
	fclose(fp);
	lpsBLC = (BLC_DATA*)bsearch(&ucCardID,lpBLC,lnBLCCnt,sizeof(BLC_DATA),compare2);
	memset(&srBLC,0x00,sizeof(BLC_DATA));
	if(lpsBLC == NULL)
	{
		free(lpBLC);
 		return DONGLE_BLOCKCARD_NOT_FIND;
	}
      
	memcpy(&srBLC,lpsBLC,sizeof(BLC_DATA));
	free(lpBLC);

	if(!memcmp(ucCardID,srBLC.ucCardID,7))
		return(SUCCESS);

	return DONGLE_BLOCKCARD_NOT_FIND;
}




int inBLCLockCard(int inTxnType,BYTE *CardID,BYTE *TxnDateTime)
{
int inRetVal;
USHORT inCnt = 3;
BYTE ucCardID[7],ucTxnDateTime[4];
#ifdef LINUX_API
USHORT inOutLen,inStatus;
#endif

	memcpy(ucCardID,CardID,sizeof(ucCardID));
	memcpy(ucTxnDateTime,TxnDateTime,sizeof(ucTxnDateTime));
	memset(cAPDU,0,sizeof(cAPDU));
	memcpy(&cAPDU[inCnt],"\x80\x41\x01\x00\x0E",5);
	inCnt += 5;
	cAPDU[inCnt++] = 0x22;//Msg Type
	cAPDU[inCnt++] = 0x00;//Sub Type
	memcpy(&cAPDU[inCnt],ucCardID,sizeof(ucCardID));
	inCnt += 7;//Card ID
	memcpy(&cAPDU[inCnt],ucTxnDateTime,sizeof(ucTxnDateTime));
	inCnt += 4;//Txn Date Time
//	cAPDU[inCnt++] = 0x01;//Reason
        cAPDU[inCnt++] = gucLockReason;//Reason
	cAPDU[inCnt++] = 0x28;//Le
	cAPDU[2] = inCnt - 3;//LEN
	cAPDU[inCnt++] = checksum(inCnt,cAPDU);//EDC


	inStatus = inCMD_STATUS;
	inCMD_STATUS = Status_LOCKCARD;
        tTxnTimeout = DEFAULT_TIMEOUT;
	inRetVal = inSendRecvAPDU(cAPDU,inCnt,cOutputData,(int *)&inOutLen,tTxnTimeout);

	if(inRetVal != SUCCESS)
		return inRetVal;
	//memcpy(((LockCard_APDU_Out_2 *)&cOutputData[OUT_DATA_OFFSET])->ucStatusCode,"\x64\x06",2);
	//cOutputData[cOutputData[2]+3] = checksum(cOutputData[2] + 3,cOutputData);//EDC
        inRetVal = (cOutputData[cOutputData[2]+1]<<8) | (cOutputData[cOutputData[2]+2]);
	
	return(inRetVal);
}
