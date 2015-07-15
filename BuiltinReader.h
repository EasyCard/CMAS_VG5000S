/* 
 * File:   BuiltinReader.h
 * Author: T420s
 *
 * Created on 2015年1月23日, 上午 9:04
 */

#ifndef BuiltinREADER_H
#define	BuiltinREADER_H

#ifdef	__cplusplus
extern "C" {
#endif
void Reader_Clear_LED(void);
void Reader_TXN_LED(void);

void Reader_FINISHED_LED(void);
void Reader_ERR_LED(void);
USHORT ReaderCommandMode(void);
USHORT BuiltinReader_ShowInfo(void);
int InitBuiltinReader(void);
int InitReader(void);
USHORT TurnOffReader(void);
int BuiltinReader_CMDSendReceive(BYTE * cmd,int cmdlen,BYTE * Data,int *Datalen);
int BuiltinReader_Answer(unsigned char * adpuBuff,unsigned char cBodyLen);
USHORT Reader_IsSupportBuildinReader(void);
void Reader_CLEAR_LED(void);
#ifdef	__cplusplus
}
#endif

#endif	/* BuiltinREADER_H */

