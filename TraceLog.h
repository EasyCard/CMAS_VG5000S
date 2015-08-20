/* 
 * File:   TraceLog.h
 * Author: T420s
 *
 * Created on 2013年9月5日, 上午 8:08
 */

#ifndef TRACELOG_H
#define	TRACELOG_H

#ifdef	__cplusplus
extern "C" {
#endif
void SendDebugFile(STR *LOCALFILE);
USHORT SystemLog(STR * EVENT,STR * DATA);

USHORT SystemLogInt(STR * EVENT,int  digi,STR * str);
USHORT SystemLogHex(STR * EVENT,unsigned char* DATA,int len);
void myDebugFile(char* function,int line, const char* fmt, ...);
#ifdef	__cplusplus
}
#endif

#endif	/* TRACELOG_H */

