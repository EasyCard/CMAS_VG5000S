#include "ECCAPP.h"
#include "function.h"
#include "apdu.h"
#include "tm.h"
#include "gvar.h"
#include "blc.h"
#include "com.h"
//#include "miniz.c"
//#include <limits.h>
DWORD hPosHandle;
BYTE gsDeviceID[4];

APDU_Response_Data_Len stAPDURespLen[Status_END + 2] = {
//							9000								6103						610F							6304							6305							6308					6403							6406						640E							6415							6418
/* PR_Start */             	{0,									0,							0,								0,								0,								0,						0,								0,							0,								0,								0							},
/* PPR_Reset */            	{sizeof(Reset_APDU_Out),			0,							0,								0,								0,								0,						0,								0,							0,								0,								0							},
/* PPR_SignOn */           	{sizeof(SignOn_APDU_Out),			0,							0,								0,								0,								sizeof(SignOn_APDU_Out),0,								0,							0,								0,								0							},
/* PPR_SignOnQuery */      	{sizeof(SignOnQuery_APDU_Out),		0,							0,								sizeof(SignOnQuery_APDU_Out),	sizeof(SignOnQuery_APDU_Out),	0,						0,								0,							0,								0,								0							},
/* PPR_ReadCardBasicData */	{sizeof(ReadCardBasicData_APDU_Out),sizeof(LockCard_APDU_Out_2),sizeof(LockCard_APDU_Out_3),	0,								0,								0,						0,								0,							sizeof(LockCard_APDU_Out_3),	0,								0							},
/* PPR_TxnReqOnline */     	{sizeof(TxnReqOnline_APDU_Out),		sizeof(LockCard_APDU_Out_2),sizeof(LockCard_APDU_Out_3),	0,								0,								0,						0,								0,							sizeof(LockCard_APDU_Out_3),	sizeof(TxnReqOnline_APDU_Out),	sizeof(LockCard_APDU_Out_3)	},
/* PPR_AuthTxnOnline */    	{sizeof(AuthTxnOnline_APDU_Out),	0,							0,								0,								0,								0,						0,								0,							0,								0,								0							},
/* PPR_TxnReqOffline */    	{sizeof(TxnReqOffline_APDU_Out),	sizeof(LockCard_APDU_Out_2),sizeof(LockCard_APDU_Out_3),	0,								0,								0,						sizeof(TxnReqOffline_APDU_Out),	sizeof(LockCard_APDU_Out_2),sizeof(LockCard_APDU_Out_3),	sizeof(TxnReqOffline_APDU_Out),	sizeof(LockCard_APDU_Out_3)	},
/* PPR_AuthTxnOffline */   	{sizeof(AuthTxnOffline_APDU_Out),	0,							0,								0,								0,								0,						0,								0,							0,								0,								0							},
/* PPR_LockCard */         	{sizeof(LockCard_APDU_Out_2),		0,							0,								0,								0,								0,						0,								0,							0,								0,								0							},
/* PPR_ReadDongleDeduct */ 	{sizeof(ReadDongleDeduct_APDU_Out),	0,							0,								0,								0,								0,						0,								0,							0,								0,								0							},
/* PPR_CardSale */         	{sizeof(TxnReqOnline_APDU_Out),		sizeof(LockCard_APDU_Out_2),sizeof(LockCard_APDU_Out_3),	0,								0,								0,						0,								0,							sizeof(LockCard_APDU_Out_3),	sizeof(TxnReqOnline_APDU_Out),	sizeof(LockCard_APDU_Out_3)	},
/* PPR_AuthCardSale */     	{sizeof(AuthTxnOnline_APDU_Out),	0,							0,								0,								0,								0,						0,								0,							0,								0,								0							},
/* PPR_CancelTxn */        	{sizeof(TxnReqOnline_APDU_Out),		sizeof(LockCard_APDU_Out_2),sizeof(LockCard_APDU_Out_3),	0,								0,								0,						0,								0,							sizeof(LockCard_APDU_Out_3),	sizeof(TxnReqOnline_APDU_Out),	sizeof(LockCard_APDU_Out_3)	},
/* PR_SetValue */          	{sizeof(SetValue_APDU_Out),			11+2,						0,								0,								0,								0,						0,								0,							sizeof(SetValue_APDU_Out),		0,								0,							},
/* PR_AuthSetValue */      	{sizeof(AuthSetValue_APDU_Out),		0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
/* PR_TxRefund */          	{sizeof(TxRefund_APDU_Out),			11+2,						0,								0,								0,								0,						0,								0,							sizeof(TxRefund_APDU_Out),		0,								0,							},
/* PR_AuthTxRefund */      	{sizeof(AuthTxRefund_APDU_Out),		0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
/* PR_TxAddValue */        	{sizeof(AddValue_APDU_Out),			11+2,						0,								0,								0,								0,						0,								0,							sizeof(AddValue_APDU_Out),		0,								0,							},
/* PR_AuthTxAddValue */    	{sizeof(AuthAddValue_APDU_Out),		0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
/* PR_AutoloadEnable */    	{sizeof(AutoloadEnable_APDU_Out),	11+2,						0,								0,								0,								0,						0,								0,							sizeof(AutoloadEnable_APDU_Out),0,								0,							},
/* PR_AuthAutoloadEnable */	{sizeof(AuthAutoloadEnable_APDU_Out),	0,						0,								0,								0,								0,						0,								0,							0,								0,								0,							},
/* PR_AddValue */          	{sizeof(AddValue_APDU_Out),			11+2,						0,								0,								0,								0,						0,								0,							sizeof(AddValue_APDU_Out),		0,								0,							},
///* PR_AuthAddValue */      	{sizeof(AuthAddValue_APDU_Out),		0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
///* PPR_ReadCardDeduct */   	{sizeof(ReadCardDeduct_APDU_Out),	0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
///* PPR_ReadCodeVersion */  	{sizeof(ReadCodeVersion_APDU_Out),	0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
///* PR_Reboot */            	{sizeof(Reboot_APDU_Out),			0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
///* PR_LockCard */         	{sizeof(LockCard_APDU_Out_1),		0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
///* PPR_SetValue */			{0, 								sizeof(LockCard_APDU_Out_2),sizeof(LockCard_APDU_Out_2),	0,								0,								0,						0,								0,							sizeof(LockCard_APDU_Out_3),	sizeof(SetValue2_APDU_Out),		0,							},
///* PPR_AuthSetValue */		{sizeof(AuthSetValue2_APDU_Out), 	0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
///* PPR_TxRefund */			{0,									sizeof(LockCard_APDU_Out_2),sizeof(LockCard_APDU_Out_2),	0,								0,								0,						0,								0,							sizeof(LockCard_APDU_Out_3),	sizeof(TxRefund2_APDU_Out), 	0,							},
///* PPR_TxAuthRefund */		{sizeof(AuthTxRefund_APDU_Out),		0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							},
///* PPR_AutoloadEnable */	{sizeof(TxnReqOnline_APDU_Out), 	sizeof(LockCard_APDU_Out_2),sizeof(LockCard_APDU_Out_3),	0,								0,								0,						0,								0,							sizeof(LockCard_APDU_Out_3),	sizeof(TxnReqOnline_APDU_Out),	sizeof(LockCard_APDU_Out_3) },
///* PPR_AuthAutoloadEnable */{sizeof(AuthTxnOnline_APDU_Out),	0,							0,								0,								0,								0,						0,								0,							0,								0,								0							},
///* PPR_AuthAutoload */		{sizeof(AuthTxnOnline_APDU_Out),	0,							0,								0,								0,								0,						0,								0,							0,								0,								0							},
/* PR_End */               	{0,									0,							0,								0,								0,								0,						0,								0,							0,								0,								0,							}
			};
/*
#define my_max(a,b) (((a) > (b)) ? (a) : (b))
#define my_min(a,b) (((a) < (b)) ? (a) : (b))
#define BUF_SIZE (1024 * 1024)

static unsigned char  s_inbuf[BUF_SIZE];
static unsigned char  s_outbuf[BUF_SIZE];
*/
void TRACE_(const char* msg)
{
	printf("%s", msg);
}
//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  calculate check sum.
	Input parameters:
		. length -- how many lenght to calculate
		. data -- claculate data
	Returned status:
		. >= 0 if OK
		. < 0 on error
--------------------------------------------------------------------- */
BYTE checksum(int length,BYTE data[])
{
	unsigned char chk= 0x00;
	int i= 0x00;

	for(i=0;i<length;i++)
		chk^=data[i];
	return chk;
}

//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  vdPad .
	Input parameters:
		. bInData -- 欲轉換的字串資料
		. inOutSize -- 轉換後的字串總長度
		. fFlag---- TRUE=左靠/FALSE=右靠
		. chFiller---- 用此資料補滿轉換後不足的部份
	Returned status:
		. bOutData -- 轉換後的字串資料
--------------------------------------------------------------------- */
void vdPad(BYTE *bInData,BYTE *bOutData,int inOutSize,char fFlag,char chFiller)
{
int inLen,inCnt = 0;
BYTE bBuf[50];

	memset(bBuf,0x00,sizeof(bBuf));
	inLen = strlen((char *)bInData);
	if(fFlag == FALSE)//右靠
	{
		memset(bBuf,chFiller,inOutSize - inLen);//左補chFiller
		inCnt = inOutSize - inLen;
	}

	memcpy(&bBuf[inCnt],bInData,inLen);
	inCnt += inLen;

	if(fFlag == TRUE)//左靠
		memset(&bBuf[inCnt],chFiller,inOutSize - inLen);//右補chFiller

	memcpy(bOutData,bBuf,inOutSize);
}

//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  vdIntToAsc .
	Input parameters:
		. bInData -- 欲轉換的Binary資料
		. inInSize---- 欲轉換的Byte數
		. inOutSize -- 轉換後的數字字串長度
		. chFiller---- 轉換後的字串將右靠左補的資料
		. inRadix---- 欲轉換成n進制,n=8/10/16
	Returned status:
		. bOutData -- 轉換後的有號數字字串資料
	Special Notes:
		. ex.0x666EB496=>0x31 0x37 0x31 0x38 0x35 0x33 0x31 0x32 0x32 0x32
--------------------------------------------------------------------- */
void vdIntToAsc(BYTE *bInData,int inInSize,BYTE *bOutData,int inOutSize,char chFiller,int inRadix)
{
INT64 llnTmp = 0L;
BYTE bBuf[30],bTmp[10];
int size = 0;

	memset(bBuf,0x00,sizeof(bBuf));
	memset(bTmp,0x00,sizeof(INT64));
	if(bInData[inInSize - 1] >= 0x80)
		memset(bTmp,0xFF,sizeof(INT64));
	memcpy(bTmp,bInData,inInSize);
	memcpy((BYTE *)&llnTmp,bTmp,sizeof(INT64));
	switch(inRadix)
	{
		case 8:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64o",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llo",llnTmp);
#endif
			break;
		case 10:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64d",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%lld",llnTmp);
#endif
			break;
		case 16:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64X",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llX",llnTmp);
#endif
			break;
		default:
//			call_stack("unsupported inRadix %d", inRadix);
			break;
	}

	vdPad(bBuf,bOutData,inOutSize,FALSE,chFiller);
}
void vdIntToAsc2(BYTE *bInData,int inInSize,BYTE *bOutData,int inRadix)
{
INT64 llnTmp = 0L;
BYTE bBuf[30],bTmp[10];
int size = 0;

	memset(bBuf,0x00,sizeof(bBuf));
	memset(bTmp,0x00,sizeof(INT64));
	if(bInData[inInSize - 1] >= 0x80)
		memset(bTmp,0xFF,sizeof(INT64));
	memcpy(bTmp,bInData,inInSize);
	memcpy((BYTE *)&llnTmp,bTmp,sizeof(INT64));
	switch(inRadix)
	{
		case 8:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64o",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llo",llnTmp);
#endif
			break;
		case 10:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64d",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%lld",llnTmp);
#endif
			break;
		case 16:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64X",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llX",llnTmp);
#endif
			break;
		default:
//			call_stack("unsupported inRadix %d", inRadix);
			break;
	}
         memcpy(bOutData,bBuf,strlen(bBuf));
	//vdPad(bBuf,bOutData,inOutSize,FALSE,chFiller);
}

//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  vdUIntToAsc .
	Input parameters:
		. bInData -- 欲轉換的Binary資料
		. inInSize---- 欲轉換的Byte數
		. inOutSize -- 轉換後的數字字串長度
		. chFiller---- 轉換後的字串將右靠左補的資料
		. inRadix---- 欲轉換成n進制,n=8/10/16
	Returned status:
		. bOutData -- 轉換後的無號數字字串資料
	Special Notes:
		. ex.0x666EB496=>0x31 0x37 0x31 0x38 0x35 0x33 0x31 0x32 0x32 0x32
--------------------------------------------------------------------- */
void vdUIntToAsc(BYTE *bInData,int inInSize,BYTE *bOutData,int inOutSize,char chFiller,int inRadix)
{
UINT64 llnTmp = 0L;
BYTE bBuf[30];
int size = 0;

	memset(bBuf,0x00,sizeof(bBuf));
	memcpy((BYTE *)&llnTmp,bInData,inInSize);
	switch(inRadix)
	{
		case 8:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64o",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llo",llnTmp);
#endif
			break;
		case 10:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64u",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llu",llnTmp);
#endif
			break;
		case 16:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64X",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llX",llnTmp);
#endif
			break;
		default:
//			call_stack("unsupported inRadix %d", inRadix);
			break;
	}

	vdPad(bBuf,bOutData,inOutSize,FALSE,chFiller);
     
}
void vdUIntToAsc2(BYTE *bInData,int inInSize,BYTE *bOutData,int inRadix)
{
UINT64 llnTmp = 0L;
BYTE bBuf[30];
int size = 0;

	memset(bBuf,0x00,sizeof(bBuf));
	memcpy((BYTE *)&llnTmp,bInData,inInSize);
	switch(inRadix)
	{
		case 8:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64o",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llo",llnTmp);
#endif
			break;
		case 10:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64u",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llu",llnTmp);
#endif
			break;
		case 16:
#ifdef WINDOWS_API
			size = sprintf((char *)bBuf, "%I64X",llnTmp);
#endif
#ifdef LINUX_API
			size = sprintf((char *)bBuf, "%llX",llnTmp);
#endif
			break;
		default:
//			call_stack("unsupported inRadix %d", inRadix);
			break;
	}

	//vdPad(bBuf,bOutData,inOutSize,FALSE,chFiller);
        memcpy(bOutData,bBuf,strlen(bBuf));
      
}
//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  fnUnPack .
	Input parameters:
		. BINData -- will be tranfefered by BIN DATA
		. BINSize -- input length of BIN Data
	Returned status:
		. ASCDATA -- Transfer Result of ASCData
	Special Notes:
		. ex.0x666EB496=>0x36 0x36 0x36 0x45 0x42 0x34 0x39 0x36
--------------------------------------------------------------------- */
void fnUnPack(BYTE *BINData,int BINSize,BYTE *ASCDATA)
{
static const char* const unpack_table = "0123456789ABCDEF";
const BYTE* src = (const BYTE*)BINData;
char* dst = (char*)ASCDATA;
int i;

	for (i = 0; i < BINSize; i++)
	{
		*dst++ = unpack_table[(src[i] & 0xf0) >> 4];
		*dst++ = unpack_table[src[i] & 0x0f];
	}
}

//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  fnASCTOBIN .
	Input parameters:
		. ASCData -- ASCData Data
		. sizex	  -- ASC SIZE
		. mode	  -- HEX or DEC...
	Returned status:
		. unsigned char Binary Data
    Special Notes:
		. ASCDATA just can transfer for numeral ex.0x31 ~ 0x39.
--------------------------------------------------------------------- */
BOOL fnASCTOBIN(BYTE *OutData,BYTE ASCData[],int sizex,int OffsetBit,int mode)
{
	//tmp = (unsigned char *)malloc((size_t)sizex * sizeof(unsigned char));
	unsigned char tmp[20] ;
	unsigned long ulTmp;
	int i;

	memset(tmp,0,sizeof(tmp));
	memcpy(tmp,ASCData,sizex);
	ulTmp = strtol((char *)tmp,NULL,mode);

	for(i=0;i<OffsetBit;i++)
	{
		OutData[i] = (BYTE )(ulTmp >> (i * 8));
	}

	return ulTmp;
}



//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  fnBINTODEVASC .
	Input parameters:
		. BINData -- will be tranfefered by BIN DATA
		. ASCSize -- output length of ASCII Data
	Returned status:
		. ASCDATA -- Transfer Result of ASCData
	Special Notes:
		. DEVICE is special format of Bin Data
		  ex.0x0053D001=>0083130001=>0x30 0x30 0x38 0x33 0x31 0x33 0x30 0x30 0x30 0x31
--------------------------------------------------------------------- */
void fnBINTODEVASC(BYTE *BINData,BYTE *ASCDATA,int ASCSize,char fPurseVersion)
{
UINT64  lTmp= 0L,lTmp2 = 0L;
int i= 0x00,length= 0x00 ;
char buffer[20];

	memset(buffer,0,sizeof(buffer));
	if(fPurseVersion != LEVEL2)
		lTmp=(BINData[0])+((BINData[1]&0x0F)*256)+((BINData[1]>>4)*10000)+(BINData[2]*1000000);
	else
	{
//		lTmp=(BINData[0]+(BINData[1]*256))+(BINData[2]*100000)+((BINData[3]+(BINData[4]*256)+(BINData[5]*256*256))*100000000);
		lTmp=(BINData[0]+(BINData[1]*256));
		lTmp += (BINData[2]*100000);
		lTmp2 = (BINData[3]+(BINData[4]*256)+(BINData[5]*256*256));
		lTmp2 *= 100000000;
		lTmp += lTmp2;
	}
#ifdef WINDOWS_API
	_i64toa( lTmp, buffer, 10 );
#endif
#ifdef LINUX_API
	sprintf((char *)buffer, "%llu",lTmp);
#endif
	length=strlen(buffer);
	if(fPurseVersion != 0x02)
	{
		vdPad((BYTE *)buffer,ASCDATA,10,FALSE,'0');//ASCDATA的左邊10碼先右靠左補0
		memset(&ASCDATA[10],' ',ASCSize - 10);//ASCDATA的後10碼補空白
	}
	else
		vdPad((BYTE *)buffer,ASCDATA,16,FALSE,'0');//ASCDATA右靠左補0
}

//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  fngetUnixTimeCnt .
	Input parameters:
		. date -- system date format is yymmddhhmmss
	Returned status:
		. total second of unix
--------------------------------------------------------------------- */
UINT fngetUnixTimeCnt(BYTE *OutDate,BYTE *date)
{
	const char init_mdays[]={31,28,31,30,31,30,31,31,30,31,30,31};
	int  year= 0x00,mon= 0x00,day= 0x00,hour= 0x00,min= 0x00,sec= 0x00;
	char temp[14];
	unsigned long tcnt= 0x00;//1.0.5.2
	int  i= 0x00;
	char mdays[12];

	memset(temp,0,sizeof(temp));
	memset(mdays,0,sizeof(mdays));
	memcpy(mdays,init_mdays,12);
	memcpy(temp,date,14);
	sec = atoi(&temp[12]);
	temp[12] = 0;
	min = atoi(&temp[10]);
	temp[10] = 0;
	hour = atoi(&temp[8]);
	temp[8] = 0;
	day = atoi(&temp[6]);
	temp[6] = 0;
	mon = atoi(&temp[4]);
	temp[4] = 0;
	year = atoi(temp);

	tcnt = 0;
	for(i=1970;i<year;i++)
	{

		tcnt += (86400 * 365);//YEAR
		if(i/4*4 == i)
		{
			tcnt += 86400;//閏年
		}
	}
	if(year/4*4 == year){
		mdays[1] = 29;
	}
	for(i=1;i<mon;i++)
		tcnt += (mdays[i-1]*86400);
	tcnt += ((day-1)*86400);
	tcnt += (hour * 3600);
	tcnt += (min * 60);
	tcnt += sec;
  //      tcnt-=(60*60*8);
	OutDate[0] = (BYTE )tcnt;
	OutDate[1] = (BYTE )(tcnt >> 8);
	OutDate[2] = (BYTE )(tcnt >> 16);
	OutDate[3] = (BYTE )(tcnt >> 24);

  	return tcnt;
}



//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  fngetDosDateCnt .
	Input parameters:
		. date -- system date format is yyyymmdd
	Returned status:
		. dosdate
--------------------------------------------------------------------- */
void fngetDosDateCnt(BYTE *date,BYTE *DosDate)
{
	int  year= 0x00,mon= 0x00,day= 0x00;
	char temp[8];

	if(!memcmp(date,"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",14) ||
	   !memcmp(date,"19700101",8))
	{
		memset(DosDate,0x00,2);
		return;
	}

	memset(temp,0,sizeof(temp));
	memset(DosDate,0,sizeof(DosDate));
	memcpy(temp,date,8);
	day = atoi(&temp[6]);
	temp[6] = 0;
	mon = atoi(&temp[4]);
	temp[4] = 0;
	year = atoi(temp);
	if(year >= 1980)
		year -= 1980;
	else
		year = 0;

	DosDate[1] = ((year & 0x7F) << 1) | ((mon & 0x08) >> 3);
	DosDate[0] = ((mon & 0x07) << 5) | (day & 0x1F);
	//return (year * (2 << 8)) + ((0x00 | mon) * 32) + (0x00 | day);

}


//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  fngetDosDate .
	Input parameters:
		. dosdate
	Returned status:
		. date -- system date format is yyyymmdd
--------------------------------------------------------------------- */
void fngetDosDate(BYTE *bDosDate,BYTE *bOutDate)
{
	int  year= 0x00,mon= 0x00,day= 0x00;

	day = (bDosDate[0] & 0x1F);
	mon = ((bDosDate[0] >> 5) & 0x07) + ((bDosDate[1] & 0x01) << 3);
	year = bDosDate[1] >> 1;
	sprintf((char *)bOutDate,"%04d%02d%02d",year + 1980,mon,day);

}


//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  fnLongToUnix .
	Input parameters:
		. Unixdate -- system date format is yymmddhhmmss
		. size     -- return size of  Unixdate
	Returned status:
		. total second of unix
--------------------------------------------------------------------- */
void fnLongToUnix(BYTE Unixdate[],unsigned long *UnixSec,int size)
{
#if 0
unsigned int inD;
unsigned long ulUnixTime,ulTotalDay,ulTolSecond;
unsigned int inDayOfMon[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
int inYear,inMon,inDay,inHour,inMin,inSec;
char   tmpUnix[20];
//	ulUnixTime = (szTime[3] * 256 * 256 * 256) +
//		     (szTime[2] * 256 * 256) +
//		     (szTime[1] * 256) +
//		     (szTime[0]);
	ulUnixTime = *UnixSec;
//	if(ulUnixTime < (10956 * 86400))//10956 * 86400表示從1970年開始到1999年為止的總秒數
//		return;
	ulUnixTime -= (10956 * 86400);//先把1970年開始到1999年為止的總秒數扣掉,表示從2000年開始計算
	ulTotalDay = ulUnixTime / 86400;//86400表示1天24小時的總秒數
	ulTolSecond = ulUnixTime % 86400;//不足一天的總秒數

	//計算inYear
	for(inYear=2000;;inYear++)
	{
		inD = 365;
		if(inTSCCChkSpecialYear(inYear) == 1)//檢查 inYear 是否是閏年
			inD = 366;

		if(ulTotalDay <= inD)//ulTotalDay 總天數少於第 inYear 年的 inD 天數就離開
			break;

		ulTotalDay -= inD;
	}
	//srTime.RTC_Yday = ulTotalDay;

	//計算inMon
	for(inMon=1;;inMon++)
	{
		inDayOfMon[1] = 28;//先設定2月為28天;
		if(inMon == 2)
			if(inTSCCChkSpecialYear(inYear) == 1)//inYear表示該年,檢查該年是否是閏年
				inDayOfMon[1] = 29;//若為閏年,2月為29天

		if(ulTotalDay <= inDayOfMon[inMon - 1])//ulTotalDay 總天數少於該年的第inDayOfMon[inMon - 1]月天數就離開
			break;

		ulTotalDay -= inDayOfMon[inMon - 1];
	}

	//計算inDay
	inDay = ulTotalDay;

	//計算inHour
	inHour = (int )(ulTolSecond / 3600);//一小時有3600秒
	ulTolSecond %= 3600;//不足一小時的總秒數

	//計算inMin
	inMin = (int )(ulTolSecond / 60);//一分鐘有60秒

	//計算inSec
	inSec = (int )(ulTolSecond % 60);//不足一分鐘的總秒數

	memset(tmpUnix,0,sizeof(tmpUnix));
	sprintf(tmpUnix,"%04d%02d%02d%02d%02d%02d",inYear,inMon,inDay,inHour,inMin,inSec);
	memcpy(Unixdate, tmpUnix, size);
#else
	struct tm *lpUTCTime=NULL;
	char   tmpUnix[20];

	memset(tmpUnix,0,sizeof(tmpUnix));
	lpUTCTime=gmtime((time_t *)UnixSec);
	strftime(tmpUnix,20,"%Y%m%d%H%M%S",lpUTCTime);
	memcpy(Unixdate, tmpUnix, size);
#endif

}

int inTSCCChkSpecialYear(int inYear)
{

	if((inYear % 4) != 0)//不是閏年就傳回 VS_ERR
		return(-1);

	//每100年不閏,但每400年要閏
	if((inYear % 100) == 0)//100的倍數
		if((inYear % 400) != 0)//且不是400的倍數,就不閏,傳回 VS_ERR
			return(-1);

	return(1);
}


//---------------------------------------------------------------------//
/* ---------------------------------------------------------------------
  fnfnWriteLog .
	Input parameters:
		. Msg  -- chinese message or others
		. Data -- keep  trace data
		. Len  -- Data length
	Returned status:
		. >= 0 if OK
		. < 0 on error
--------------------------------------------------------------------- */
BOOL  fnWriteLog(BYTE *Msg,BYTE *Data, long Len)
{

	char szMsg[2500];
 	memset(szMsg,0,sizeof(szMsg));
	sprintf(szMsg, "%s\n", Msg);
	fnUnPack(Data,Len,(BYTE *)&szMsg[strlen(szMsg)]);
//	TRACE_((char *)Msg);
//	log_msg("%s",(char *)szMsg);

	return SUCCESS;
}


int inReaderCommand(int inCommandType)
{
	int inCnt = 3;

   
	memset(cAPDU,0,sizeof(cAPDU));
	memcpy(&cAPDU[inCnt],cAPDUHeader,4);
	inCnt += 4;
	if(inLC > 0)
		cAPDU[inCnt++] = inLC;//Lc
	switch(inCommandType)
	{
             case Status_RESET:
			inCnt += inBuildResetCommand((Reset_APDU_In *)&cAPDU[inCnt]);
			break;

             case Status_SIGNON:
			inCnt += inBuildSignOnCommand((SignOn_APDU_In *)&cAPDU[inCnt]);
			break;
             case Status_READCARDBASICDATA:
			inCnt += inBuildReadCardBasicDataCommand((ReadCardBasicData_APDU_In *)&cAPDU[inCnt]);
			break;
	     case Status_TXNREQONLINE:
             case Status_AUTOLOADENABLE:    
             case Status_SETVALUE:         
	     case Status_CARDSALE:       
                        inCnt += inBuildTxnReqOnlineCommand((TxnReqOnline_APDU_In *)&cAPDU[inCnt]);
			break;
             case Status_AUTHTXNONLINE:
	     case Status_AUTHAUTOLOADENABLE:        
             case Status_AUTHAUTOLOAD:          
             case Status_AUTHSETVALUE:        
	     case Status_AUTHCARDSALE:
			inCnt += inBuildAuthTxnOnlineCommand((AuthTxnOnline_APDU_In *)&cAPDU[inCnt]);
			break;
	     case Status_TXNREQOFFLINE:  //購貨
			inCnt += inBuildTxnReqOfflineCommand((TxnReqOffline_APDU_In *)&cAPDU[inCnt]);
			break;
	     case Status_AUTHTXNOFFLINE:  
			inCnt += inBuildAuthTxnOfflineCommand((AuthTxnOffline_APDU_In *)&cAPDU[inCnt]);
			break;
	     case Status_LOCKCARD:        //鎖卡  
			inCnt += inBuildLockCardCommand((LockCard_APDU_In_2 *)&cAPDU[inCnt]);
			break;
	     case Status_READDONGLEDEDUCT:
//			inCnt += inBuildReadDongleDeductCommand((ReadDongleDeduct_APDU_In *)&cAPDU[inCnt],(ReadDongleDeduct_TM_In *)cInputData);
			break;
	     case Status_READCARDDEDUCT:
	//		inCnt += inBuildReadCardDeductCommand((ReadCardDeduct_APDU_In *)&cAPDU[inCnt],(TRANS_DATA *)cInputData);
			break;
            case Status_ReadCardNumber:
                           inCnt += inBuildReadCardCommand((ReadCardNumber_APDU_In *)&cAPDU[inCnt]);
                break;
	     default:
			break;
	}

	if(inLE > 0)
		cAPDU[inCnt++] = inLE;//Le
		
	cAPDU[2] = inCnt - 3;//LEN
	cAPDU[inCnt++] = checksum(inCnt,cAPDU);//EDC

	return(inCnt);
}

void vdBuildMessageType(int inTxnType,BYTE *cOut)
{

	switch(inTxnType)
	{
		case Status_RESET:
			memcpy(cOut,"0800",4);
                        break;
		case Status_SIGNON:
			memcpy(cOut,"0820",4);
			break;
             case Status_SETVALUE:
		case Status_TXNREQONLINE:
		case Status_CARDSALE:
             case Status_AUTOLOADENABLE:
			memcpy(cOut,"0100",4);
			break;
		case Status_AUTHTXNONLINE:
		case Status_AUTHCARDSALE:
		case Status_AUTHAUTOLOADENABLE:
		case Status_AUTHAUTOLOAD:
		case Status_TXNREQOFFLINE:
			memcpy(cOut,"0220",4);
			break;
		
		case Status_LOCKCARD:
			memcpy(cOut,"0320",4);
			break;
	}
}



void vdBuildMessageType2(BYTE inTxnType,BYTE TxnStatus, BYTE *cOut)
{

	switch(inTxnType)
	{
	
		case TXTYPE_SIGNON:
			if(TxnStatus==TransStatus_REQ)
			{
				sprintf(cOut,"0800");
                                sprintf(gWaitMsgType,"0810");
			}else if(TxnStatus==TransStatus_ADVREQ){
				sprintf(cOut,"0820");
                              sprintf(gWaitMsgType,"0820");
			}
			break;
            case TXTYPE_ADD:
            case TXTYPE_AUTOLOAD:    
            case TXTYPE_DEDUCT:
	    case TXTYPE_SETVALUE:
            case TXTYPE_AUTOLOADENABLE:	 
	    case TXTYPE_REFUND:	
	    case TXTYPE_VOID:
			if(TxnStatus==TransStatus_REQ)
			{
				sprintf(cOut,"0100");
                                sprintf(gWaitMsgType,"0110");
			}else if(TxnStatus==TransStatus_ADVREQ){
                                sprintf(cOut,"0220");
                                sprintf(gWaitMsgType,"0230");
                        }
			break;
               
   	    case TXTYPE_LOCKCARD:
            case TXTYPE_REPORT:	
			
				sprintf(cOut,"0320");
                                sprintf(gWaitMsgType,"0330");
			
			break;
            case TXTYPE_SETTLEMENT:	
			if(TxnStatus==TransStatus_REQ)
			{
				sprintf(cOut,"0500");
                                sprintf(gWaitMsgType,"0510");
			}
			
			break;
	}
}


 
void vdBuildProcessingCode2(TRANS_DATA2 *TransData,BYTE *cOut)
{

	switch(TransData->ucTXTYPE)
	{
		//se Status_RESET:
                case TXTYPE_REPORT:
                    sprintf(cOut,"950007");
                          break;
                case TXTYPE_SIGNON:
                    sprintf(cOut,"881999");
			break;
	     	case TXTYPE_ADD:
		case TXTYPE_DEDUCT:
		case TXTYPE_SETVALUE:
              
		case TXTYPE_REFUND:	
		case TXTYPE_VOID:
		case TXTYPE_AUTOLOAD:   	
			if(TransData->ucMsgType== 0x02)//�[�� �۰ʥ[�� �h�f 
			{
				if(TransData->ucSubType == 0x0A)
					sprintf(cOut,"823899");//�ʳf���
				else if(TransData->ucSubType == 0x0B)
					sprintf(cOut,"851999");//�h�f
				else if(TransData->ucSubType == 0x0C)
					sprintf(cOut,"839799");//�l�[
				else if(TransData->ucSubType == 0x30)
				{
					if(TransData->ucBasicData_CardProfile >= 0x01 && TransData->ucBasicData_CardProfile <= 0x03)
						sprintf(cOut,"841799");//���֥d�{���[��
					else
						sprintf(cOut,"811799");//�{���[��
				}
				else if(TransData->ucSubType == 0x40)
					sprintf(cOut,"825799");//自動加值
			}else if(TransData->ucMsgType == 0x07)//��d
				sprintf(cOut,"851799");
			else if(TransData->ucMsgType == 0x09)//��d���
				sprintf(cOut,"851899");
			else if(TransData->ucMsgType == 0x0B)//�[�Ȩ��
				sprintf(cOut,"811899");
                        else if(TransData->ucMsgType == 0x01){//
                          //   if(gTransData.ucTXSTATUS==TransStatus_REQ)//有錯
                               if(TransData->ucTXSTATUS==TransStatus_REQ)//修正後
                                 sprintf(cOut,"816399");
                             else
                                 sprintf(cOut,"811599");  
                       }
			break;
             case TXTYPE_LOCKCARD: 
                  sprintf(cOut,"596100");
                 break;            
            case TXTYPE_SETTLEMENT:
              sprintf(cOut,"900000");
              break;
            case TXTYPE_AUTOLOADENABLE:	  //AUTOLOADENABLE
               sprintf(cOut,"814799");		
              break;
           
	}
}
void vdBuildProcessingCode(int inTxnType,BYTE ucMsgType,BYTE ucSubType,BYTE ucPersonalProfile,BYTE *cOut)
{

	switch(inTxnType)
	{
		//se Status_RESET:
		case TXTYPE_SIGNON:
			sprintf(cOut,"881999");
			break;
	     	case TXTYPE_ADD:
		case TXTYPE_DEDUCT:
		case TXTYPE_SETVALUE:
            case TXTYPE_AUTOLOADENABLE:	 
		case TXTYPE_REFUND:	
		case TXTYPE_VOID:
			
			if(ucMsgType == 0x02)//�[�� �۰ʥ[�� �h�f 
			{
				if(ucSubType == 0x0A)
					sprintf(cOut,"823899");//�ʳf���
				else if(ucSubType == 0x0B)
					sprintf(cOut,"851999");//�h�f
				else if(ucSubType == 0x0C)
					sprintf(cOut,"839799");//�l�[
				else if(ucSubType == 0x30)
				{
					if(ucPersonalProfile >= 0x01 && ucPersonalProfile <= 0x03)
						sprintf(cOut,"841799");//���֥d�{���[��
					else
						sprintf(cOut,"811799");//�{���[��
				}
				else if(ucSubType == 0x40)
					sprintf(cOut,"825799");//自動加值
			}
			else if(ucMsgType == 0x07)//��d
				sprintf(cOut,"851799");
			else if(ucMsgType == 0x09)//��d���
				sprintf(cOut,"851899");
			else if(ucMsgType == 0x0B)//�[�Ȩ��
				sprintf(cOut,"811899");
			break;
		
          
	}
}
void vdCountEVBefore(BYTE *bAmt,int inAmtSize,BYTE *bEV,int inEVSize,BYTE *bEVBefore,int inEVBeforeSize,BYTE ucMsgType)
{

int inSize;
long lnAmt = 0L,lnEV = 0L,lnEVBefore = 0L;
BYTE bBuf[10],bTmp[10];

	memset(bTmp,0x00,sizeof(bTmp));
	memcpy((BYTE *)&lnAmt,bAmt,inAmtSize);
	if(bEV[inEVSize - 1] >= 0x80)
		memset(bTmp,0xFF,sizeof(long));
	memcpy(bTmp,bEV,inEVSize);
	memcpy((BYTE *)&lnEV,bTmp,sizeof(long));
	if(ucMsgType == 0x02)//加值類
		lnEVBefore = lnEV - lnAmt;
	else
		lnEVBefore = lnEV + lnAmt;
//	if(fCreditFlag == TRUE)
//		lnEVBefore = lnEV - lnAmt;
//	else //if(fCreditFlag == FALSE)
//		lnEVBefore = lnEV + lnAmt;

	memset(bBuf,0x00,sizeof(bBuf));
	inSize = sprintf((char *)bBuf,"%ld",lnEVBefore);
	memset(bEVBefore,' ',inEVBeforeSize - inSize);
	memcpy(&bEVBefore[inEVBeforeSize - inSize],bBuf,inSize);
}

int inGetTMInDataLen(int inTxnType)
{
int inLen = 0;

	switch(inTxnType)
	{
		case Status_RESET:
			inLen = sizeof(Reset_TM_In);
			break;
		case Status_SIGNON:
			inLen = sizeof(SignOn_TM_In);
			break;
		case Status_SIGNONQUERY:
			break;
		case Status_READCARDBASICDATA:
			inLen = sizeof(ReadCardBasicData_TM_In);
			break;
		case Status_TXNREQONLINE:
		case Status_CARDSALE:
	
		case Status_AUTHTXNONLINE:
			inLen = sizeof(AuthTxnOnline_TM_In);
			break;
		case Status_AUTHCARDSALE:
			inLen = sizeof(AuthCardSale_TM_In);
			break;
		case Status_TXNREQOFFLINE:
			inLen = sizeof(TxnReqOffline_TM_In);
			break;
		case Status_AUTHTXNOFFLINE:
			inLen = sizeof(AuthTxnOffline_TM_In);
			break;
		
		case Status_READDONGLEDEDUCT:
			inLen = sizeof(ReadDongleDeduct_TM_In);
			break;
	
		case Status_SETVALUE:
			inLen = sizeof(SetValue2_TM_In);
			break;
		case Status_AUTHSETVALUE:
			inLen = sizeof(AuthSetValue2_TM_In);
			break;
	
		case Status_AUTOLOADENABLE:
			inLen = sizeof(AutoloadEnable2_TM_In);
			break;
		case Status_AUTHAUTOLOADENABLE:
			inLen = sizeof(AuthTxnOnline_TM_In);
			break;
		case Status_AUTHAUTOLOAD:
			inLen = sizeof(AuthAutoload_TM_In);
			break;
		default:
			break;
	}

	return(inLen);
}

void vdSaveReqData(char *bFileName,BYTE *bSaveData,int inSaveLen)
{
	int inRetVal;
	FILE *fp = NULL;
	BYTE bBuf[400];

	memset(bBuf,0x00,sizeof(bBuf));
	remove((char *)bFileName);

	fp = fopen((char *)bFileName,"wb");
	if(fp==NULL){
		sprintf((char *)bBuf,"vdSaveReqData [%s](%d) fopen FALSE",bFileName,inSaveLen);
		fnWriteLog(bBuf,bFileName,strlen((char *)bFileName));
		return;
	}

	inRetVal =fwrite(bSaveData,inSaveLen,1,fp);

	if(inRetVal != d_OK)
	{
		inRetVal=fclose(fp);
		fnWriteLog((BYTE *)"vdSaveReqData ferror FALSE",NULL,0);
		return;
	}
	inRetVal=fclose(fp);
}

void vdLoadReqData(char *bFileName,BYTE *bLoadData,int inLoadLen)
{
int inRetVal;
FILE *fp = NULL;
BYTE bBuf[400];

	memset(bBuf,0x00,sizeof(bBuf));
	memset(bLoadData,0x00,inLoadLen);


	fp = fopen((char *)bFileName,"rb");
	if(fp == NULL)
	{
		sprintf((char *)bBuf,"vdLoadReqData [%s](%d) fopen FALSE",bFileName,inLoadLen);
		fnWriteLog(bBuf,bFileName,strlen((char *)bFileName));
		return;
	}
	
	inRetVal = fread(bLoadData,inLoadLen,1,fp);
	inRetVal = ferror(fp);
	if(inRetVal != 0)
	{
		fclose(fp);
		fnWriteLog((BYTE *)"vdLoadReqData ferror FALSE",(BYTE *)&inRetVal,4);
		return;
	}
	fclose(fp);
}

void vdToUpper(char *szOutData,char *szInData)
{
int i;

	for(i=0;i<(int )strlen(szInData);i++)
	{
		szOutData[i] = toupper(szInData[i]);
	}
}


//---------------------------------------------------------------------//

void vdAmt2ByteTo3Byte(BYTE *bIn2Amt,BYTE *bOut3Amt)
{

	memcpy(bOut3Amt,bIn2Amt,2);
	if(bIn2Amt[1] >= 0x80)
		bOut3Amt[2] = 0xFF;
}

void vdUnPackAmt2ByteTo3Byte(BYTE *bIn2Amt,BYTE *bOutAmt)
{
BYTE bBuf[5];

	memset(bBuf,0x00,sizeof(bBuf));
	memcpy(bBuf,bIn2Amt,2);
	if(bIn2Amt[1] >= 0x80)
		bBuf[2] = 0xFF;
	fnUnPack(bBuf,3,bOutAmt);
}

USHORT usWriteFile(BYTE *strFileName,BYTE *bData,int size)
{
   
   int ret=remove(strFileName);
    
   FILE *f = fopen(strFileName, "w+");
    if (f == NULL) return d_ERR_FILE_OPEN;
    
    fseek(f,0,SEEK_SET);
    ret=fwrite(bData,1,size,f);
    fflush(f);
    fclose(f);
    return d_OK;
}
USHORT usReadFileData(BYTE * strFilename,ULONG *iSize,BYTE * bData)
{
    ULONG ulFileSize = 0;
  FILE * f = fopen(strFilename, "r");  if (f == NULL)   return d_Fail;
  
  fseek(f, 0L, SEEK_END);
  ulFileSize = ftell(f);
  if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
  
  //bData=malloc(ulFileSize);
 // ulFileSize= *iSize;
  fseek(f, 0, SEEK_SET );
  *iSize=fread(bData,1,ulFileSize, f);
  fclose(f);
  return d_OK;
}

USHORT usReadFileData2(BYTE * strFilename,int offset,ULONG *iSize,BYTE * bData)
{
  
  ULONG ulFileSize = 0;
 
  FILE * f = fopen(strFilename, "r");  if (f == NULL)   return d_Fail;
  
  fseek(f, 0L, SEEK_END);
  ulFileSize = ftell(f);
  if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
  
  //bData=malloc(ulFileSize);
  ulFileSize= *iSize;
  fseek(f, offset, SEEK_SET );
  *iSize=fread(bData,1,ulFileSize, f);
  fclose(f);
   
  return d_OK;

}
int   CreateDir(const   char   *sPathName)  
  {  
  char   DirName[256]; 
  memset(DirName,0x00,sizeof(DirName));
  strcpy(DirName,   sPathName);  
  int   i,len   =   strlen(DirName);  
  if(DirName[len-1]!='/')  
          strcat(DirName,   "/");  
   
  len   =   strlen(DirName);  
   
  for(i=1;   i<len;   i++)  
  {  
  if(DirName[i]=='/')  
  {  
  DirName[i]   =   0;  
  if(   access(DirName,   0)!=0   )  
  {  
      if(mkdir(DirName,   0755)==-1)  
      {   
                      perror("mkdir   error");   
                      return   -1;   
      }  
  }  
  DirName[i]   =   '/';  
  }  
  }  
   
  return   0;  
  } 
USHORT  File_exist(char *filename)
{  
    FILE *f = NULL;
     f = fopen(filename, "r");
     if (f == NULL)    return d_ERR_FILE_NOTEXIST;
     fclose(f);
     return d_OK;
}
ULONG File_GetLen(char * filename)
{
    ULONG ulFileSize=0;
     FILE *f = fopen(filename, "r");
     if (f == NULL)    return 0;
     
     fseek(f, 0L, SEEK_END);
     ulFileSize = ftell(f);
     if (ulFileSize <= 0) return 0;
     
     fclose(f);
     return ulFileSize;
}

USHORT usAppendFile(BYTE *strFileName,BYTE *bData,int size)
{
     
   FILE *f = fopen(strFileName, "a+");
   if (f == NULL)    return d_ERR_FILE_OPEN;
   fseek(f, 0L, SEEK_END);
   USHORT   ret=fwrite(bData,1,size,f);
   if(ret!=size) return d_ERR_FILE_Write_FAIL;
   fflush(f);
   fclose(f);
   return d_OK;
}


void fnGetRTCUNIXDataTime(unsigned long *UnixSec)
{      
       CTOS_RTC SetRTC;
       BYTE strDateTime[15];
       memset(strDateTime,0x00,sizeof(strDateTime));
       USHORT ret = CTOS_RTCGet(&SetRTC);
       if(ret==0){
           sprintf(strDateTime,"%04d%02d%02d%02d%02d%02d",SetRTC.bYear + 2000,SetRTC.bMonth,SetRTC.bDay,SetRTC.bHour,SetRTC.bMinute,SetRTC.bSecond);
	   fngetUnixTimeCnt((BYTE *)UnixSec,strDateTime); 
      }
       
}
void fnGetRTCDOSData(BYTE *DOSDate)
{
       CTOS_RTC SetRTC;
       BYTE strDateTime[15]; 
       memset(strDateTime,0x00,sizeof(strDateTime));
       USHORT ret = CTOS_RTCGet(&SetRTC);
       if(ret==0){
           sprintf(strDateTime,"%04d%02d%02d%02d%02d%02d",SetRTC.bYear + 2000,SetRTC.bMonth,SetRTC.bDay,SetRTC.bHour,SetRTC.bMinute,SetRTC.bSecond);
	    fngetDosDateCnt(strDateTime,DOSDate);
      }
}
#define BUFFERSIZE 1024
#define COPYMORE 0644
 
 int copyFiles2(char *source, char *destination)
{
   FILE *in_fd;
   FILE *out_fd;

  int n_chars;
  char buf[BUFFERSIZE];
  char *folder;

  printf("[%s,%d] copy %s ---> %s\n",__FUNCTION__,__LINE__,source, destination);
  
  /* open files */
  in_fd = fopen(source, "r");
  if (in_fd == NULL)    
  {
      printf("[%s,%d] d_ERR_FILE_OPEN\n",__FUNCTION__,__LINE__);
     SystemLog("Cannot open ", source);       
     return d_ERR_FILE_OPEN;
  }
 
  out_fd=fopen(destination, "w+");
  if (out_fd == NULL) 
  {
      printf("[%s,%d] d_ERR_FILE_OPEN\n",__FUNCTION__,__LINE__);
       SystemLog("Cannot creat ", destination);
       return d_ERR_FILE_OPEN;
  }
 
 
  /* copy files */
  while(n_chars =fread(buf,1,BUFFERSIZE,in_fd))
  {
    if(fwrite(buf,1,n_chars, out_fd )!= n_chars)  
    {
        printf("[%s,%d] d_ERR_FILE_READ_FAIL\n",__FUNCTION__,__LINE__);
      SystemLog("Write error to ", destination);
      return d_ERR_FILE_READ_FAIL;
    }
 
 
    if( n_chars == -1 )
    {
        printf("[%s,%d] d_ERR_FILE_READ_FAIL\n",__FUNCTION__,__LINE__);
       SystemLog("Read error to ", source);
      return d_ERR_FILE_READ_FAIL;
    }
  }
 
 
    /* close files */
    if( fclose(in_fd) == -1 || fclose(out_fd) == -1 )
    {
      SystemLog("Error closing files", "");
      printf("[%s,%d] d_ERR_FILE_CLOSE\n",__FUNCTION__,__LINE__);
      return d_ERR_FILE_CLOSE;
    }
 
  
    return 1;
}
 
int copyFiles(char *source, char *destination)
{
  int in_fd, out_fd, n_chars;
  char buf[BUFFERSIZE];
  
 
  /* open files */
  if( (in_fd=open(source, O_RDONLY)) == -1 )
  {
     SystemLog("Cannot open ", destination);
       return d_ERR_FILE_OPEN;
  }
  
  if( (out_fd=creat(destination, COPYMORE)) == -1 )
  {
       SystemLog("Cannot creat ", destination);
       return d_ERR_FILE_OPEN;
  }
 
 
  /* copy files */
  while( (n_chars = read(in_fd, buf, BUFFERSIZE)) > 0 )
  {
    if( write(out_fd, buf, n_chars) != n_chars )
    {
      SystemLog("Write error to ", destination);
      return d_ERR_FILE_READ_FAIL;
    }
 
 
    if( n_chars == -1 )
    {
     
       SystemLog("Read error to ", source);
      return d_ERR_FILE_READ_FAIL;
    }
  }
    
    fsync(out_fd);   
 
    /* close files */
    if( close(in_fd) == -1 || close(out_fd) == -1 )
    {
      SystemLog("Error closing files", "");
      return d_ERR_FILE_CLOSE;
    }
 
 
    return 1;
}
USHORT SetRTC(BYTE * Date,BYTE * Time)
{
      CTOS_RTC RTC;
      BYTE baYear[2+1],baMonth[2+1],baDay[2+1],baHour[2+1],baMinute[2+1],baSecond[2+1];
      memset(baYear,0x00,3);
      memset(baMonth,0x00,3);
      memset(baDay,0x00,3);
      memset(baHour,0x00,3);
      memset(baMinute,0x00,3);
      memset(baSecond,0x00,3);
      memcpy(baYear,&Date[2],2);baYear[2]=0x00;
      memcpy(baMonth,&Date[4],2);baMonth[2]=0x00;
      memcpy(baDay,&Date[6],2);baDay[2]=0x00;
      memcpy(baHour,&Time[0],2);baHour[2]=0x00;
      memcpy(baMinute,&Time[2],2);baMinute[2]=0x00;
      memcpy(baSecond,&Time[4],2);baSecond[2]=0x00;
      
      RTC.bYear=atoi(baYear);
      RTC.bMonth=atoi(baMonth);
      RTC.bDay=atoi(baDay);
      RTC.bHour=atoi(baHour);
      RTC.bMinute=atoi(baMinute);
      RTC.bSecond=atoi(baSecond);
      USHORT ret = CTOS_RTCSet(&RTC);
      return ret;
}

USHORT CheckSDCARD()
{
    BYTE inData[100],OutData[100];
    ULONG iSize=sizeof(inData);
    memset(inData,0x11,sizeof(inData));
    USHORT ret=usWriteFile("/media/mdisk/testfile",inData,iSize);
    ret= usReadFileData("/media/mdisk/testfile",&iSize,OutData);
    if(memcmp(inData,OutData,100)==0)
        return d_OK;
    else{
        ShowMessage2line("設備檢查","找不到SDCARD","請確認",Type_ComformAnykey);
        return d_Fail;
    }
       
}
USHORT CheckUSBDISK(void)
{
    BYTE inData[100],OutData[100];
    ULONG iSize=sizeof(inData);
    memset(inData,0x11,sizeof(inData));
    USHORT ret=usWriteFile("/media/udisk/testfile",inData,iSize);
    ret= usReadFileData("/media/udisk/testfile",&iSize,OutData);
    if(memcmp(inData,OutData,100)==0)
        return d_OK;
    else{
        ShowMessage2line("設備檢查","找不到USB FLASH DISK","請確認",Type_ComformAnykey);
        return d_Fail;
    }
       
}

USHORT CTOS_ReadFile(STR * Filename,BYTE * Data,ULONG *Datelen)
{
    ULONG ulHandle;

    USHORT ret =CTOS_FileOpen(Filename , d_STORAGE_FLASH , &ulHandle);
     
   // USHORT ret= CTOS_FileOpenAttrib (Filename, d_STORAGE_FLASH, &ulHandle,d_FA_PUBLIC );
    if (ret != d_OK)    return ret;

    ret = CTOS_FileRead(ulHandle ,Data ,Datelen);
    if (ret != d_OK)    return ret;

    /* Close the opened file */
    CTOS_FileClose(ulHandle);

    return d_OK;
}
USHORT CTOS_WriteFile(STR * Filename,BYTE * Data,ULONG Datelen)
{

  ULONG ulHandle;
  USHORT ret = CTOS_FileOpen(Filename, d_STORAGE_FLASH, &ulHandle);

  if(ret == 0x200B) myDebugPrinter(ERROR,"write %s fail d_FS_NOT_OWNER", Filename);
  //printf("[%s,%d] CTOS_WriteFile fileName=%s\n",__FUNCTION__,__LINE__,Filename);
  if (ret != d_OK){
     printf("[%s,%d] CTOS_FileOpen fail ret=%d\n",__FUNCTION__,__LINE__,ret);
     return ret;
 }
  ret = CTOS_FileSeek(ulHandle ,0 ,d_SEEK_FROM_BEGINNING);
  if (ret != d_OK){
      myDebugPrinter(ERROR,"CTOS_FileSeek %s fail ret=%d", Filename, ret);
      printf("[%s,%d] CTOS_FileSeek fail ret=%d\n",__FUNCTION__,__LINE__,ret);
      return ret;
  }
  ret = CTOS_FileWrite(ulHandle ,Data ,Datelen);
  if (ret != d_OK){
      myDebugPrinter(ERROR,"CTOS_FileWrite %s fail ret=%d", Filename, ret);
      printf("[%s,%d] CTOS_FileWrite fail ret=%d\n",__FUNCTION__,__LINE__,ret);
      return ret;        
  }
  ret=CTOS_FileClose(ulHandle);
  if(ret!=d_OK){      
      printf("[%s,%d] CTOS_FileClose fail ret=%d\n",__FUNCTION__,__LINE__,ret);
  }
  return d_OK;
}

USHORT CopyDirFile(BYTE *Folder)
{
    struct dirent *next_file;
    DIR * theFolder;
    DIR * subFolder;
    char dest[256];
    char USBDISK[]="/media/udisk/";
    char filepath[256];
    int ret;
    char destFolder[256];
    char tmp[32];
  //  do{
    theFolder = opendir(Folder);
    if(theFolder==NULL) return d_Fail;
    while ( next_file = readdir(theFolder) )
    {
        // build the full path for each file in the folder        
        sprintf(filepath, "%s/%s", Folder, next_file->d_name); 
       
      
 //       CTOS_PrinterPutString(filepath);
        if(memcmp(next_file->d_name,".",1)!=0){
               if(memcmp(next_file->d_name,"..",2)!=0){
            if(next_file->d_type==DT_DIR) 
            {
                 sprintf(destFolder,"%s%s",USBDISK,&filepath[13]); 
                 CreateDir(destFolder); 
                 CopyDirFile(filepath);
            }else{
                sprintf(dest,"%s%s",USBDISK,&filepath[13]); 
                ret= copyFiles(filepath, dest);
                if(ret==1){ 
                    sprintf(tmp,"%s 下載成功",next_file->d_name);
                    ShowStatusLine(tmp);                     
                }
            }
           }
        }
    }
    
  // }while(1);

    return 0;

}

USHORT DelectDirFile(BYTE *Folder)
{
    struct dirent *next_file;
    DIR * theFolder;
    DIR * subFolder;
    char filepath[256];
    int ret;
  //  do{
    theFolder = opendir(Folder);
    if(theFolder==NULL) return d_Fail;
    while ( next_file = readdir(theFolder) )
    {
        // build the full path for each file in the folder        
        sprintf(filepath, "%s/%s", Folder, next_file->d_name); 
        //CTOS_PrinterPutString(filepath);
        if(memcmp(next_file->d_name,".",1)!=0){
               if(memcmp(next_file->d_name,"..",2)!=0){
            if(next_file->d_type==DT_DIR)
                  DelectDirFile(filepath);
            else{
                 ret= remove(filepath);
                 //if(ret==0)
                     //CTOS_PrinterPutString("Delete Success!!");
            }
           }
        }
    }
    
  // }while(1);
    return 0;

}
void CheckMemoarystatus()
{
   
    ULONG ulUsedDiskSize ,ulTotalDiskSize, ulUsedRamSize, ulTotalRamSize; 
    CTOS_SystemMemoryStatus(&ulUsedDiskSize,&ulTotalDiskSize,&ulUsedRamSize,&ulTotalRamSize);

   printf("[%s,%d] totalRAMSize(%ld), usedRAMSize(%ld)\n",__FUNCTION__,__LINE__,ulTotalRamSize,ulUsedRamSize);
    if((ulTotalRamSize-ulUsedRamSize)<2000){
     printf("[%s,%d] totalRAMSize(%ld), usedRAMSize(%ld)\n",__FUNCTION__,__LINE__,ulTotalRamSize,ulUsedRamSize);
         ShowMessage2line(gTransTitle,"資料重整","請稍候!",Type_ComformNONE);  
         myDebugFile((char*)__FUNCTION__,__LINE__,"ulTotalRamSize(%ld),ulUsedRamSize(%ld)",ulTotalRamSize,ulUsedRamSize);
         //2014.04.11, kobe modified it for ECR
         //CTOS_SystemReset (  );
         ezSystemReset();
    }
    return ;
}

void Housekeeping()
{
    CTOS_RTC RTC;
    BYTE month,year;
    BYTE DataKeepingMonth=6;
    USHORT ret = CTOS_RTCGet(&RTC);
    if(ret!=0)         return ;
   
    if( RTC.bMonth-DataKeepingMonth<0){ 
        year= RTC.bYear;
        month=RTC.bMonth-DataKeepingMonth;
    }else{
        year= RTC.bYear-1;
        month=12-(DataKeepingMonth-RTC.bMonth);
    }
    BYTE path[32];
    memset(path,0x00,sizeof(path));
    sprintf(path,"/media/mdisk/%04d/%02d",year+2000,month);
    DelectDirFile(path); 
}
USHORT PowerOff()
{
    
   USHORT   ret;
   USHORT  TotalCount;
   
   ret=  Process_SendAdvice3(1);
   
   USHORT TXCount=CheckBatchCount();
   if(TXCount>0){
         ret= ShowMessage3line(gTransTitle,"目前尚有帳務未結","請確認是否需結帳!!","結帳請按<OK>",Type_ComformOK);
         if(ret==d_OK){
                  ret= Process_Settle();
                  if(ret!=d_OK) return 0;
         }
   }
    
   ret= ShowMessage2line("系統關機","是否確認關閉機器?","",Type_ComformOK);
   if(ret==d_OK)       CTOS_PowerOff ();
   return 0;
}
/*
USHORT DecompressionFile(STR * file)
{        // Decompression.
    const char *pMode;
    FILE *pInfile, *pOutfile;
    uint infile_size;
    int level = Z_BEST_COMPRESSION;
    z_stream stream;
    int p = 1;
    const char *pSrc_filename;
    const char *pDst_filename;
    long file_loc;
    uint infile_remaining = infile_size;

    if (inflateInit(&stream))
    {
      printf("inflateInit() failed!\n");
      return d_Fail;
    }

    for ( ; ; )
    {
      int status;
      if (!stream.avail_in)
      {
        // Input buffer is empty, so read more bytes from input file.
        uint n = my_min(BUF_SIZE, infile_remaining);

        if (fread(s_inbuf, 1, n, pInfile) != n)
        {
          printf("Failed reading from input file!\n");
          return d_Fail;
        }

        stream.next_in = s_inbuf;
        stream.avail_in = n;

        infile_remaining -= n;
      }

      status = inflate(&stream, Z_SYNC_FLUSH);

      if ((status == Z_STREAM_END) || (!stream.avail_out))
      {
        // Output buffer is full, or decompression is done, so write buffer to output file.
        uint n = BUF_SIZE - stream.avail_out;
        if (fwrite(s_outbuf, 1, n, pOutfile) != n)
        {
          printf("Failed writing to output file!\n");
          return d_Fail;
        }
        stream.next_out = s_outbuf;
        stream.avail_out = BUF_SIZE;
      }

      if (status == Z_STREAM_END)
        break;
      else if (status != Z_OK)
      {
        printf("inflate() failed with status %i!\n", status);
        return d_Fail;
      }
    }

    if (inflateEnd(&stream) != Z_OK)
    {
      printf("inflateEnd() failed!\n");
      return d_Fail;
    }
  
     fclose(pInfile);
    if (EOF == fclose(pOutfile))
    {
      printf("Failed writing to output file!\n");
      return d_Fail;
    }

    printf("Total input bytes: %u\n", (mz_uint32)stream.total_in);
    printf("Total output bytes: %u\n", (mz_uint32)stream.total_out);
    printf("Success.\n");
    return d_OK;
}*/
//2014.04.11, kobe added for ECR
int ezSystemReset()
{
    
    int result;
    if(ecrObj.gData.isEcrTxn)
        result = ecrObj.successResponse(&ecrObj);
    
    myDebugFile((char*)__FUNCTION__,__LINE__,"CTOS_SystemReset now");
    CTOS_SystemReset();
}

USHORT DumpBackupTxLog2USB()
{
    USHORT ret;
   ret= CTOS_USBSelectMode ( d_USB_HOST_MODE );
    ShowMessage("DUMP FILE","請接上USB FLASH DISK",Type_ComformAnykey);
    ret= CheckUSBDISK();
    if(ret!=d_OK) return ret;
    ShowMessage2line("DUMP FILE","下載備份資料","請稍候!",Type_ComformNONE);  
    ret= CopyDirFile("/media/mdisk");
    ret= CTOS_USBSelectMode ( d_USB_DEVICE_MODE );
    
    return d_OK;
}
void CopyFiletoUSB(char *source, char *destination)
{
  USHORT ret;
  ret= CTOS_USBSelectMode ( d_USB_HOST_MODE );
   ret= copyFiles(source, destination);
  ret= CTOS_USBSelectMode ( d_USB_DEVICE_MODE );
}

void copyFileFromUSB(char *source, char *destination)
{
  USHORT ret;
  ret= CTOS_USBSelectMode ( d_USB_HOST_MODE );
   ret= copyFiles(source, destination);
  ret= CTOS_USBSelectMode ( d_USB_DEVICE_MODE );
}

void ezPowerOff()
{
    int result;
    if(ecrObj.gData.isEcrTxn)
        result = ecrObj.successResponse(&ecrObj);
    USHORT ret=  CTOS_PowerMode(d_PWR_POWER_OFF);
}

BOOL IsPortable()
{
   BOOL fPortable,fPCI;
   USHORT mkHWSupport;
   USHORT usRet= CTOS_HWSettingGet(&fPortable,&fPCI,&mkHWSupport); 
   if(usRet==d_OK&&fPortable==d_TRUE){//如為移動式設備且採實体網路連線 ，檢查是否放回底座
      return d_TRUE;
   }
   return d_FALSE;
}
void dumpByteArrayToHexString(BYTE *data, int dataLen, BYTE *subject)
{
//debug send
        BYTE log[4096]; 
        BYTE temp[32];
        int i;
        memset(log, 0x00, sizeof(log));
        
        for(i=0; i<dataLen; i++)
        {
            sprintf(temp,"(%02X)", data[i]);
            strcat(log,temp);
        }
      printf("[%s,%d] %s=>len(%d),%s\n",__FUNCTION__,__LINE__,subject, dataLen,log);
        //end
}

void deleteOldApp(BYTE *appName){

    USHORT ret = 0;
    USHORT index=999;
    ret = CTOS_APFind(appName, &index);
    if(ret != d_OK) {
        printf("[%s,%d] got AP index fail ret=%d\n",__FUNCTION__,__LINE__,ret);
        return;
    }
    printf("[%s,%d] oldAPP existed @ index=%d\n",__FUNCTION__,__LINE__,index);
    
    ret = CTOS_APDel(index);
    if(ret != d_OK) myDebugPrinter(WARN, "ECCAPP deleted fail, 請通知維修工程師");
    
    return;
}

#if 0 
//@@ i do not know why sdcard not exided, and system tell me existed
int fCheckSDCardInstalled(){
    //BOOL result = d_OK;
    //char *file = "/media/mdisk/SD.ok";
//int doesFileExist(const char *filename) {
    struct stat st;
    int result = stat("/media/mdisk/SD.ok", &st);
    if(result != 0){        
        FILE *f=NULL;
        f = fopen("/media/mdisk/SD.ok", "w+");
        //if (f == NULL) return d_ERR_FILE_NOTEXIST;     
        fclose(f);
        //check again
        result = stat("/media/mdisk/SD.ok", &st);
    }
    
    return (result == 0)?d_OK:d_ERR_FILE_NOTEXIST;
//}    
    /*
    if(File_exist(SD_OK) != d_OK){        
        FILE *f=NULL;
        f = fopen(SD_OK, "w+");
        if (f == NULL) return d_ERR_FILE_NOTEXIST;     
        fclose(f);     
    }
    return result;*/
}
#else

int fCheckSDCardInstalled(){

    char *sdok = "/media/mdisk/SDOK/";
    DIR* dir = opendir(sdok);
    int result = d_OK;

    if (dir){    
        /* Directory exists. */    
        closedir(dir);
    }
    else{    
        CreateDir(sdok);    
        dir = opendir(sdok);
    
        if(dir){//got
        }else result = -1;
}
/*
else if (ENOENT == errno)
{
    //Directory does not exist. 
}
else
{
    // opendir() failed for some other reason. 
}*/

return result;
}




#endif

