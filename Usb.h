/* 
 * File:   Usb.h
 * Author: user
 *
 * Created on 2014年4月15日, 下午 3:53
 */

#ifndef USB_H
#define	USB_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{    
    BYTE *recvMsg;
    USHORT recvSize;
    //BOOL waitACK;//for send
    BYTE waitACKCnt;//for send
    //BOOL sendACK;//for receive    
    BYTE sendACKCnt;//for receive    
    BYTE dataCheckType;
    
    int ( *open)(void *);
    int ( *sendData)(void *,void*,ULONG);
    //int ( *recvDataLen)(void *p1);
    int ( *recvData)(void *);
    int ( *close)(void *);
} USB_OBJ;

void usbInitial(void *);
int inUsbOpenComport(void *);
int inUsbSendData(void *, void *, ULONG);
int inUsbRecvData(void*);
int inUsbCloseComport(void *);
int inUsbCheckDataCompleteness(void*);
#ifdef	__cplusplus
}
#endif

#endif	/* USB_H */

