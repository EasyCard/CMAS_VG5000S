/* 
 * File:   RS232.h
 * Author: user
 *
 * Created on 2014年3月17日, 上午 11:35
 */

#ifndef RS232_H
#define	RS232_H

#ifdef	__cplusplus
extern "C" {
#endif
#define AROUND_DEVICE_CONFIG "AroundDeviceConfig.xml"
#define AROUND_DEVICE_CONFIG_BK "AroundDeviceConfigBk.xml"
#define SI              0x0F
#define SO              0x0E
#define STX 		0x02
#define ETX 		0x03
#define EOT 		0x04
#define ENQ 		0x05
#define ACK 		0x06
#define NAK 		0x15


/*2014-03-27 added by kobe*/

typedef struct rs232Protocal
{
    BYTE comport;
    ULONG baudRate;
    BYTE parity;
    BYTE dataBits;
    BYTE stopBits;
}RS232_PROTOCOL;
    
    
typedef struct rs232Object
{
    RS232_PROTOCOL protocal;
    BYTE *sendMsg;
    BYTE *recvMsg;
    USHORT recvSize;
    //BOOL waitACK;//for send
    BYTE waitACKCnt;//for send
    //BOOL sendACK;//for receive
    BYTE sendACKCnt;//for receive
    BYTE dataCheckType;
    BYTE exceptionTestMode;
    BOOL fTxReady;//for buildin reader 
    BOOL fRxReady;//for buildin reader 
   
    int ( *openComport)(void *p1);
    int ( *sendData)(void *,void*,ULONG);
    //int ( *recvDataLen)(void *p1);
    int ( *recvData)(void *p1);
    int ( *closeComport)(void *p1);
} RS232_OBJ;

typedef enum{
    EX_NORMAL,//0
    EX_RESP_NAK,//1
    EX_RESP_NO_ACK,//2   
}ECR_EXCEPTION_TEST_MODE;

void rs232Initial(void *p1);
int inOpenComport(void *p1);
int inSendData(void *p1, void *p2, ULONG size);
int inRecvDataLen(void *p1);
int inRecvData(void *p1, void *p2, ULONG size);
int inCloseComport(void *);
int inRecvDataV2(void*);
/*2014.06.16, kobe added it*/
int inCheckDataCompleteness(void*p1);
//2014.06.27, kobe added it
BYTE btRs232CalculateLrc(void *p1, void *p2);

void monitorRS232Status(void *p1);
BOOL checkRS232TxReady(void *p1);
#ifdef	__cplusplus
}
#endif

#endif	/* RS232_H */

