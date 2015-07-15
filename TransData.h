/* 
 * File:   TransData.h
 * Author: T420s
 *
 * Created on 2013年8月28日, 上午 9:03
 */

#ifndef TRANSDATA_H
#define	TRANSDATA_H

#ifdef	__cplusplus
extern "C" {
#endif


 void vdBuildReadCardBasicDataOutput2(BYTE ucMsgType,LastTxnLog_t *DongleOutLog,LastTxnRecored_t *APIOutRecored);

USHORT usParseTransFormat(void);
USHORT usBuildTXREQ(TRANS_DATA2 * TransData,BYTE *FileName);
USHORT usGetTagData(ezxml_t xml,  char *txt);
USHORT usFormatTransTag(TRANS_DATA2 *TransData, BYTE * TAG ,BYTE * NAME, ezxml_t TransLog);

USHORT usUnFormatTransTag(TRANS_DATA2 *TransData, ezxml_t node);
USHORT usUnPackResponData(TRANS_DATA2 * TransData);
#ifdef	__cplusplus
}
#endif

#endif	/* TRANSDATA_H */

