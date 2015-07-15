/* 
 * File:   Eth.h
 * Author: T420s
 *
 * Created on 2015年1月30日, 下午 1:37
 */



#ifndef ETH_H
#define	ETH_H

#ifdef	__cplusplus
extern "C" {
#endif
#define APN			"internet"
#define ID			""
#define PW			""


#define FILE_CA_DER		"CA.der"
#define FILE_CA_PEM		"CA.pem"
#define FILE_CERT		"Cert"
#define FILE_KEY		"Key"



#define  d_ETHERNET_Open_Socket_NG      0x9800   
#define  d_ETHERNET_Get_Sock_Flag_NG    0x9801
#define  d_ETHERNET_Set_Sock_Flag_NG    0x9802
#define  d_ETHERNET_Connect_Failed      0x9803
#define  d_ETHERNET_Bind_device_NG      0x9805
#define  d_ETHERNET_Connect_Timeout     0x9806
#define  d_ETHERNET_New_CTX_Failed      0x9807
#define  d_ETHERNET_Set_Cipher_Failed   0x9808
#define  d_ETHERNET_New_SSL_Failed      0x9809
#define  d_ETHERNET_Set_fd_Failed       0x9810
#define  d_ETHERNET_Load_CA_Failed      0x9811
#define  d_ETHERNET_Load_Cert_Failed    0x9812
#define  d_ETHERNET_Load_Key_Failed     0x9813
#define  d_ETHERNET_SSL_Connect_Failed  0x9814
#define  d_ETHERNET_Verify_Failed       0x9815
#define  d_ETHERNET_SSL_Write_Failed    0x9816
#define  d_ETHERNET_Set_Rx_TO_Failed    0x9817
#define  d_ETHERNET_SSL_RECEIVE_TIMEOUT 0x9818
#define  d_ETHERNET_WRONGADDRESS        0x9819   
#define  d_ETHERNET_SSLConnect_Failed   0x9820
USHORT Eth_CheckDeviceStatus(void);    
USHORT Eth_SocketConnet(char * ip,char *port);
unsigned int ip_to_int (const char * ip);
USHORT GPRS_WaitIOProcess(USHORT usRtn);
USHORT  CMAS_Ethernet_Connect(void);
USHORT  Eth_Connect(BYTE bChannel,STR * IP,int PORT); 
USHORT  Eth_Disconnect(void);
USHORT  Eth_SSLSocketConnect(void);
void  Eth_SSLSocketDisConnect(void); 
USHORT  GPRS_Regiseter(void);
USHORT  GPRS_SSLSocketSendandRecv(void);
USHORT SSLSocketSendandRecv_fortest(STR * file);
USHORT Eth_TCPConnect(void);
USHORT Eth_SocketCheckConnectStatus(void);
USHORT Eth_SSLSendandRecv_Socket(void);
static int wait_on_socket(curl_socket_t sockfd, int for_recv, long timeout_ms);
USHORT ETH_REBOOT(void);
USHORT Eth_Init(void);
void  Eth_SSLConnect_SOCKET_thread(void);
USHORT Eth_SSLConnect_SOCKET(void);
USHORT Eth_CheckDeviceOnBase(void);
USHORT Eth_PutDeviecBackOnBase(void);
USHORT Ethernet_Status_Check(void);
USHORT Eth_SSLSocketSendandRecv_CURL(void);
USHORT GPRS_SSLSocketConnect(void);
USHORT Eth_CheckDeviceSupport(void);
#ifdef	__cplusplus
}
#endif

#endif	/* ETH_H */

