/* 
 * File:   comm.h
 * Author: bruce-lin
 *
 * Created on 2013年6月25日, 下午 3:43
 */

#ifndef COMM_H
#define	COMM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
//   void Thread_Comm(void);
USHORT Connect_CallCOMMThread(void);
USHORT Disconnect_CallCOMMThread(void);
USHORT SendReceiveData_CallCOMMThread(void);   

USHORT Ethernet_OPEN(void);
USHORT Ethernet_Disconnect(void);

int SocketSendRecv(STR * HostIP,int  PORT,int *Recvlen);
USHORT SSLSocketSendandRecv(void);
void* SSLSocketConnect_thread(void);
USHORT SSLSocketConnect(void);
USHORT SSLSocketSendandRecv2(BYTE DisplayStatus);
USHORT SSLSocketDisConnect(void);
//int GetFTPFilelist(void);
USHORT TestHostConnect(void);
USHORT Ethernet_Check(void);
USHORT SSLSocketSendandRecv1(void);
void* SSLSocketConnect_thread2(void);
USHORT WaitSSLSendReceive(void);
#ifdef	__cplusplus
}
#endif

#endif	/* COMM_H */

