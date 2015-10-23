/* 
 * File:   Com.h
 * Author: T420s
 *
 * Created on 2013年7月23日, 下午 3:26
 */

#ifndef COM_H
#define	COM_H

#ifdef	__cplusplus
extern "C" {
#endif
    typedef struct{
        BYTE Portnum;
        ULONG ulBaudRate;
        BYTE bParity;
        BYTE bDataBits;
        BYTE bStopBits;        
    }RS232Setting;
int OpenCom(const char* device, DWORD post_handle);
int CloseCom(void);

USHORT send_apdu(BYTE COMPORT,const BYTE* buf, USHORT buf_size);
USHORT recv_from(BYTE COMPORT,BYTE* buf,USHORT recv_size,int inTimeout);
USHORT recv_apdu(BYTE COMPORT,BYTE* buf,int inTimeout);

static void finalizer_(void);
int inTSendRecvAPDU(BYTE *bSendData,int inSendLen,BYTE *bRecvData,int * inRecvLen,int inTimeOut,STR * TESTACTIONNAME,int Outputlen,BOOL saved);
int inSendRecvAPDU(BYTE *bSendData,int  inSendLen,BYTE *bRecvData,int*inRecvLen,int inTimeOut,BOOL saved);


#ifdef	__cplusplus
}
#endif

#endif	/* COM_H */

