/* 
 * File:   SSL.h
 * Author: T420s
 *
 * Created on 2013年8月26日, 下午 4:01
 */

#ifndef SSL_H
#define	SSL_H

#ifdef	__cplusplus
extern "C" {
#endif
 #include <openssl/ssl.h>

BYTE * SSLRead2 (SSL *ssl);
int SSLSendandRecv (void);


#ifdef	__cplusplus
}
#endif

#endif	/* SSL_H */

