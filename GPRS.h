/* 
 * File:   GPRS.h
 * Author: T420s
 *
 * Created on 2015年2月6日, 上午 11:19
 */

#ifndef GPRS_H
#define	GPRS_H

#ifdef	__cplusplus
extern "C" {
#endif
USHORT GPRS_StatusCheck(void);
USHORT GPRS_SSLSocketSendandRecv(BYTE bChannel);


#ifdef	__cplusplus
}
#endif

#endif	/* GPRS_H */

