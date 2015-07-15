
/** 
 **	A Template for developing new terminal application
 **/
#include "ECCAPP.h"
const BYTE *CipherSuites = "AES256-SHA:AES128:SHA:DES-CBC3-SHA:DES-CBC-SHA";

 int sd;
 SSL_CTX *ssl_ctx;   
 SSL *ssl;
#define PPP_TO_MS 45000 //45000ms
#define CONNECT_TO_MS 5000 // 5000ms
#define CONNECT_RETRY 2
 
 unsigned int ip_to_int (const char * ip)
{
    /* The return value. */
    unsigned v = 0;
    /* The count of the number of bytes processed. */
    int i;
    /* A pointer to the next digit to process. */
    const char * start;

    start = ip;
    for (i = 0; i < 4; i++) {
        /* The digit being processed. */
        char c;
        /* The value of this byte. */
        int n = 0;
        while (1) {
            c = * start;
            start++;
            if (c >= '0' && c <= '9') {
                n *= 10;
                n += c - '0';
            }
            /* We insist on stopping at "." if we are still parsing
               the first, second, or third numbers. If we have reached
               the end of the numbers, we will allow any character. */
            else if ((i < 3 && c == '.') || i == 3) {
                break;
            }
            else {
                return 0;
            }
        }
        if (n >= 256) {
            return 0;
        }
        v *= 256;
        v += n;
    }
    return v;
}

USHORT Ethernet_Status_Check()
{
  USHORT ret;
  int kill_rc;      
    DWORD dwStatus;
    if (bgNETWORKChannel == CHANNEL_GPRS){
   
       ret= CTOS_TCP_GPRSSocketStatus(bSocket, &dwStatus);
    }else{
       ret = CTOS_EthernetStatus(&dwStatus);
       if ((dwStatus & d_STATUS_ETHERNET_CONNECTED)==d_STATUS_ETHERNET_CONNECTED){
           return d_OK;
       }
    }  
 // ShowMessage2line(gTransTitle,"網路連線中","請稍候",Type_ComformNONE);
  /*USHORT tret,err;
  err = pthread_join(Thread_Comm,(USHORT) &tret);//祝线程一直阻赛，等待TID1的返回。
  if (err != 0){
        printf("can't join with thread 1\n");
        return err;
  }
  if(tret!=d_OK){
  // ShowMessage2line(gTransTitle,"網路連線中","請稍候",Type_ComformNONE);
   return tret;
  }*/
  int trylimit=50,trycount=0;
  switch(gCOMMSTATUS)
  {
      case COMM_STATUS_StartConnect: 
          break;
      case COMM_STATUS_Connecting:  
         /*  while(1){
                kill_rc = pthread_kill(Thread_Comm,0);
                if(kill_rc==ESRCH) break;
                     //       ShowMessage2line(gTransTitle,"交易進行中..","請勿移動卡片",Type_ComformNONE);
           }*/
        // for(trycount=0;trycount<trylimit;trycount++){
               if(gCOMMSTATUS!=COMM_STATUS_Connecting)
               {
                    if(gCOMMSTATUS==COMM_STATUS_ConnecteOK)
                        return d_OK;
                    else
                        return d_Fail;
               }  
         //      CTOS_Delay(100);
         //  }
           ret=d_Fail;
          break;
      case COMM_STATUS_DISCONNECTED:  
           // ret=SSLSocketConnect();
          break;  
      case COMM_STATUS_ConnecteFail:  
           ShowMessage2line(gTransTitle,"網路連線中","請稍候",Type_ComformNONE);
         //  ret=SSLSocketConnect();
          break; 
      case COMM_STATUS_ConnecteOK: 
          ret=d_OK;
           break;
  }
         
     return ret; 
}
    

USHORT ETH_REBOOT()
{
    ShowMessage2line("網路","網路連線中","請稍候",Type_ComformNONE);
     if(strcmp(gConfig.ETHERNET.EthernetCHANNEL,"GPRS")==0) {
       
        CTOS_TCP_GPRSClose();
    } else {
      
        CTOS_EthernetClose;
    }        
    Eth_Init();

}
/*===================================================================
* FUNCTION NAME: pollStatusResult
* DESCRIPTION: Show the status and return value of GPRSStatus and return until not
get IO_PROCESSING state.
* RETURN: The return value of GPRSStatus
* NOTES: none
*==================================================================*/
USHORT pollStatusResult(BYTE *func, USHORT theRTN)
{
    BYTE key , str[64];
    USHORT usret;
    DWORD status;
   
    memset(str, 0 , sizeof(str));
 
    status = 0;
    while (1)
    {
        usret = CTOS_TCP_GPRSStatus(&status);
        
        if (usret == 0x2321) //keep polling status
        {
        //    sprintf(str , "%s 請稍候.. " ,func, status);
        //    ShowStatusLine(str);    
            CTOS_Delay(500);
            continue;
        }
        else
                break;
    }
return usret;
}

USHORT Eth_TCPConnect(void)
{
  
    USHORT  usRet;
    BYTE baMsg[512];
      /* Set TCP connecting timeout (ms) and retry time */
    usRet = CTOS_TCP_SetConnectTO(CONNECT_TO_MS);
    usRet = CTOS_TCP_SetRetryCounter(CONNECT_RETRY);
    
    usRet=GetHOSTINFO();
    gCOMMSTATUS=COMM_STATUS_StartConnect;
    USHORT usPort=atoi(gHOSTPORT);
    if(bgNETWORKChannel == CHANNEL_GPRS)
    {
      if(strcmp(gConfig.ETHERNET.NETWORKMODE,"INTERNET")==0){
          usRet= CTOS_TCP_GPRSConnectURL(&bSocket,gHOSTIP,usPort);
          usRet = pollStatusResult("GPRS Connect ", usRet);
          if(usRet!=d_OK)
          {
              usRet= CTOS_TCP_GPRSConnectURL(&bSocket,gHOSTURL,usPort);
              usRet = pollStatusResult("GPRS Connect ", usRet);
              if (usRet != d_OK){  
             
                  return usRet;
              }
          }
             return d_OK;
        }else{
              usRet= CTOS_TCP_GPRSConnectURL(&bSocket,gHOSTVIPIP,usPort );
              usRet = pollStatusResult("GPRS Connect ", usRet);
              if (usRet != d_OK){  
                  
                  return usRet;
              }
       }
     }else{
        if(strcmp(gConfig.ETHERNET.NETWORKMODE,"INTERNET")==0){
          usRet= CTOS_EthernetConnectEx(gHOSTIP,strlen(gHOSTIP), gHOSTPORT,strlen(gHOSTPORT) );
          if(usRet!=d_OK)
          {
              usRet= CTOS_EthernetConnectURLPort(gHOSTURL, strlen(gHOSTURL),gHOSTPORT, strlen(gHOSTPORT));
             if (usRet != d_OK){    gCOMMSTATUS=COMM_STATUS_ConnecteFail;
                  return usRet;
              }
          }
      
          
          return d_OK;
        }else{
             usRet= CTOS_EthernetConnectEx (gHOSTVIPIP,strlen(gHOSTVIPIP) , gHOSTPORT,strlen(gHOSTPORT) );
             if (usRet != d_OK){  
                
                  return usRet;
              }
        }
     }    
}

USHORT GPRS_SSLSocketConnect()
{
    BOOL    blRet;
  
    BYTE    bKey, bTypef;
    USHORT  usRet, usBufLen, i;
    SystemLog("GPRS_SSLSocketConnect","Start"); 
    
    gCOMMSTATUS= COMM_STATUS_INIT;

    ShowStatusLine("網路連線中");

  usRet = CTOS_TCP_GPRSConnectEx(&bSocket ,gHOSTIP ,atoi(gHOSTPORT));
  usRet = pollStatusResult("GPRS Connect.....", usRet);
  if(usRet!=d_OK) return usRet;

      
  
  DWORD dwStatus;
  usRet= CTOS_EthernetStatus ( &dwStatus );
   ShowStatusLine("建立SSL連線");
  // usRet = CTOS_SSLNew(d_SSL_CONNECTION_ETHERNET, bSocket);
   usRet = CTOS_SSLNew(d_SSL_CONNECTION_GPRS, bSocket);
    if (usRet != d_OK)
    {
         usRet=d_ERR_SSL_CreateFail;
          return usRet; 
    }
  
  //  CTOS_SSLSetReadTimeout(2000);       //Set the Read Timeout to 2s
    int size=0;
    ULONG Filesize;
    usRet= Get_SSLCA();
    if(usRet==d_OK){
      BYTE ca[2048];
      memset(ca,0x00,sizeof(ca));
      Filesize= File_GetLen(gCAFile);
      if(Filesize==0) return d_ERR_FILE_SIZE_ERR;   
       usRet=usReadFileData(gCAFile,&Filesize,ca);
       usRet = CTOS_SSLLoadObject(d_SSL_OBJ_X509_CERT, ca,Filesize , NULL);
       if (usRet != d_OK){   
            usRet=d_ERR_SSLCA_ERROR;  
            return usRet;
       }
   }else{
     usRet=d_ERR_SSLCA_ERROR;
       return usRet;
   }
   
 
   // CTOS_SSLSetReadTimeout(2000);       //Set the Read Timeout to 2s
   ShowStatusLine("SSL 連接中");
   usRet= CTOS_EthernetStatus ( &dwStatus );
    usRet = CTOS_SSLConnect();
    if (usRet != d_OK)
    {
        usRet=d_ERR_SSL_CreateFail;
         return usRet;
    }
    
    
     ShowStatusLine("Handshake OK");
    return usRet;
}


USHORT GPRS_SSLSocketSendandRecv()
{
    BOOL    blRet;
    BYTE    SendPack[1024*3], baBuf[1024*3];//,RecvPack[1024*10];
    BYTE    bKey, bTypef;
   // BYTE    baStr[128];
    USHORT  usRet, usBufLen, i;
   // int     RetryTime=20; 
    int     RetryTime=20; 
    USHORT sendbufsize=1024*3;
    USHORT recebufsize=1024*3;
    SystemLog("SSLSocketSendandRecv","Start"); 
   // SendPack= malloc(sendbufsize);
   // baBuf= malloc(recebufsize);
   
 
    usRet= GPRS_SSLSocketConnect();  
    if(usRet!=d_OK) return usRet;
    
    int Filesize= File_GetLen(SendFile);
    if(Filesize==0) return d_ERR_FILE_SIZE_ERR;   
    int RemainSize=Filesize;
    ULONG getlen;
   // SendPack=malloc(Filesize);
    do{
        if(RemainSize>2000)
            getlen=2000;
        else
            getlen=RemainSize;       
        
        
        usRet=usReadFileData(SendFile,&getlen,SendPack);
        if(usRet!=d_OK) return usRet;
          ShowStatusLine("資料傳輸中....");
       //ShowMessage2line(gTransTitle,"網路傳輸","資料傳輸中....",Type_ComformNONE);
       RemainSize-=getlen;

        usRet = CTOS_SSLWrite(SendPack, getlen);
        if (usRet != d_OK)
        {
         // sprintf(baStr, "SSL Send NG %04X", usRet);
         // ShowMessage2line(gTransTitle,"網路傳輸",baStr,Type_ComformAnykey);
            goto exit;
        }
    }while(RemainSize!=0);
   
   ///////////////////////////////////////////
   //為了自動加值回應較慢時，可能發生收不到回應封包，在發出資料後，停下來等兩秒後再收資料 
   if(gTransData.ucTXTYPE==TXTYPE_AUTOLOAD)
           CTOS_Delay ( 2000 );
  ////END
    
    ezxml_t ezxml_recv;
 
  //usRet=  CTOS_SSLSetReadTimeout(500);
  // CTOS_Delay ( 1000);
  usRet=  CTOS_SSLSetReadTimeout(2000);
  //  CTOS_SSLEnableCancelKey(1);
    // SSL read
   // do
   // {
            ShowStatusLine("等待接收中.");
       // ShowMessage2line(gTransTitle,"網路傳輸","等待接收中.",Type_ComformNONE);
        //Please make sure that you have large enough buffer to receive the data (Depending on the application specification).
       remove(RecvFile);
       usBufLen = recebufsize;
        do{
             CTOS_Delay ( 500 );
            usRet = CTOS_SSLRead(baBuf, &usBufLen);
            if(usRet==d_OK){
                   if(usBufLen > 0){
                       //  usWriteFile(RecvFile,baBuf,usBufLen);
                        
                      usAppendFile(RecvFile,baBuf,usBufLen);
                       ezxml_recv= ezxml_parse_file(RecvFile);
                       i = fprintf(stderr, "%s", ezxml_error(ezxml_recv));
                       if(i==0)
                       { 
                      
                           CTOS_Beep();
                           if(ezxml_recv!=NULL)
                               ezxml_free(ezxml_recv);
                           goto exit;
                           
                       }
                      SystemLog("SSLSocketSendandRecv","ezxml_free 1"); 
                      if(ezxml_recv!=NULL)
                                 ezxml_free(ezxml_recv);

                  }else{
                      //  gCOMMSTATUS= COMM_STATUS_SSLRECEIVED;	
                       // CTOS_Beep();
                      //  goto exit;
                        ShowStatusLine("等待接收中..");
                        CTOS_Beep();}
             }else{   
                   
                     ShowStatusLine("等待接收中..");
                     CTOS_Beep();
                    
             }
             RetryTime--;
        } while ( usRet != d_SSL_ERROR_CONN_LOST&&RetryTime>0);
        
 //   usRet=d_ERR_ETH_RECV_TIMEOUT;
  //  ShowStatusLine("接收逾時。");
exit:
   //ShowMessage2line(gTransTitle,"網路傳輸","SSL 斷線",Type_ComformNONE);
    // ShowStatusLine("SSL CLOSE..");
   
  //  free(SendPack);    
 //   free(baBuf);
  
    CTOS_SSLDisConnect();
    CTOS_SSLClose();

exit_disconnect:
  //ShowStatusLine("TCP CLOSE .");
  //ShowMessage2line(gTransTitle,"網路傳輸","TCP 斷線",Type_ComformNONE); 
Ethernet_Disconnect();
#ifndef DEBUGMODE      
    
     
    //return d_OK;//debug 時用 ，用gdb 在disconnect會跳不出來，所以debug 階段先跳過
#endif     
//  PrintMemoarystatus(2);
  
    // CTOS_KBDGet(&bKey); 
    return usRet;

}


USHORT GPRS_WaitIOProcess(USHORT usRtn)
{
    BYTE baMsg[32];
    DWORD dwStatus;
    ULONG ulTick;

    ulTick = CTOS_TickGet();
    while (usRtn == d_TCP_IO_PROCESSING) {
        sprintf(baMsg, "%ldms", (CTOS_TickGet() - ulTick) * 10);
      
        ShowLine(0,40+16+30+16,Med_Font_Size,baMsg,FALSE);
        usRtn = CTOS_TCP_GPRSStatus(&dwStatus);
    }

    return usRtn;
}
USHORT Eth_Init()
{
    BYTE baMsg[128];
    memset(baMsg,0x00,sizeof(baMsg));

    USHORT usRtn=d_OK;
    gCOMMSTATUS=COMM_STATUS_INIT;
       USHORT usType;
        BYTE NetworkType;
   
       usRtn= CTOS_MobileSetNetworkType(d_MOBILE_NETWORK_AUTO);
       CTOS_MobileGetNetworkTypeSupport(&usType);
       CTOS_MobileGetNetworkTypeCurrent(&usType); 
        
    ShowTitle("通訊網路"); 
    // ShowSystemMemoryStatus("Eth bf");  
    if(strcmp(gConfig.ETHERNET.EthernetCHANNEL,"GPRS")==0){ 
       ShowLine(0,40+16,Big_Font_Size,"行動網路連線中..",FALSE);
       usRtn= CTOS_TCP_SelectDefaultDevice(d_TCP_DEVICE_GPRS);
        //CTOS_TCP_GPRSInit();
         usRtn = CTOS_GSMOpen(115200, TRUE);
         if (usRtn != d_OK) {
            sprintf(baMsg, "%04X", usRtn);
            MessageBox("通訊網路","行動網路無法啟動" ,"請檢查SIM卡",baMsg,"",d_MB_CHECK);
            gCOMMSTATUS=COMM_STATUS_OPENFAIL;
            return usRtn;
         }
    
        usRtn=GPRS_Regiseter();
        if(usRtn!=d_OK){ 
              gCOMMSTATUS=COMM_STATUS_OPENFAIL; 
            return usRtn;}
        usRtn=  CTOS_GSMGetNetworkType(&NetworkType);
        bgNETWORKChannel= CHANNEL_GPRS; 
        
    }else{
         usRtn= CTOS_TCP_SelectDefaultDevice(d_TCP_DEVICE_ETHERNET);
        bgNETWORKChannel= CHANNEL_ETHERNET;
       
    }
    
    usRtn= Ethernet_OPEN();
    if(usRtn ==d_OK)
         ShowLine(0,40+16,Big_Font_Size,"行動網路連線成功",FALSE);
   //pthread_create(&thread1, NULL, &Thread_Comm, NULL);  
  //   ShowSystemMemoryStatus("Eth af");
   

    return usRtn;

}
USHORT Ethernet_OPEN()
{
    //////////////////////////////////////////////////////////////////////////
    // 1. Channel Open
    //////////////////////////////////////////////////////////////////////////
    USHORT usRtn;
    BYTE baMsg[512];
    BYTE baLocalIP[4] = {0};
    if (bgNETWORKChannel == CHANNEL_GPRS) {
       ShowLine(0,40+16,Big_Font_Size,"行動網路連線中..",FALSE);
         gCOMMSTATUS=COMM_STATUS_TCPOPENING;
         CTOS_TCP_GPRSInit();
         usRtn = CTOS_PPP_SetTO(PPP_TO_MS);
       // usRtn = CTOS_TCP_GPRSOpenEx("\x00\x00\x00\x00", APN, ID, PW);
         usRtn = CTOS_TCP_GPRSOpen("\x00\x00\x00\x00", APN, ID, PW);
        usRtn = GPRS_WaitIOProcess(usRtn);
        if (usRtn != d_OK) {
            sprintf(baMsg, "%04X", usRtn);
            MessageBox("通訊網路","通訊網路無法連線" ,"請重試..","",baMsg,d_MB_CHECK);
            return usRtn;
        }
      usRtn = CTOS_TCP_GPRSGetIP(baLocalIP);
      sprintf(gConfig.ETHERNET.LOCAL.IP, "%d.%d.%d.%d", baLocalIP[0],baLocalIP[1],baLocalIP[2],baLocalIP[3]);
     
      gCOMMSTATUS=COMM_STATUS_TCPOPENOK; 
    } else {
      
        gCOMMSTATUS=COMM_STATUS_TCPOPENING;
       
        if(IsPortable())
            usRtn = CTOS_EthernetOpenEx();
        else
            usRtn = CTOS_EthernetOpen();
        if (usRtn != d_OK) {
             sprintf(baMsg, "%04X", usRtn);
            MessageBox("通訊網路","通訊網路無法連線" ,"請重試..","",baMsg,d_MB_CHECK);
            
          
            return usRtn;
        }
        gCOMMSTATUS=COMM_STATUS_TCPOPENOK; 
        InitEthernetInfo();
       
    }     
      
    return usRtn;
}


/*
 return socket fd
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////
USHORT  Eth_Connect(BYTE bChannel,STR * IP,int PORT)
{
    BYTE    bKey, baStr[64];
    USHORT  usRtn=0;
    int ret, type;
    struct timeval tv;
    fd_set fdset;
    socklen_t oplen;
    struct sockaddr_in sa;
  
    Socketfd=0;
  
    /************************************************************************/
    /* Step 2 to 3 are similar to CTOS_TCP_GPRSConnectEx or                 */
    /* CTOS_EthernetConnectEx                                               */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 2. Open a Linux socket to get a socket fd for further use.
  
 //   ShowStatusLine("Socket Open...");
    Socketfd = socket(PF_INET, SOCK_STREAM, 0);
    if (Socketfd == -1) {
     //   ShowStatusLine("Open Socket NG");
        usRtn=d_ETHERNET_Open_Socket_NG;
        return usRtn;
        //goto CHANNEL_CLOSE;
    }

    //////////////////////////////////////////////////////////////////////////
    // 2.1 Bind socket to device
    // ShowStatusLine("Bind to device...");
    if (bChannel == CHANNEL_GPRS)
        usRtn = CTOS_TCP_BindToDevice(Socketfd, d_TCP_DEVICE_GPRS);
    else
        usRtn = CTOS_TCP_BindToDevice(Socketfd, d_TCP_DEVICE_ETHERNET);

    if (usRtn != d_OK) {
  //      ShowStatusLine("Bind device NG");
         usRtn=d_ETHERNET_Bind_device_NG;
         return usRtn;
         //goto CHANNEL_CLOSE;
    }

    //////////////////////////////////////////////////////////////////////////
    // 3. Connect to server over TCP
 //   ShowStatusLine( "Socket Connect...");
    memset(&sa, 0, sizeof (sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(IP);
    sa.sin_port = htons(PORT);
   
    // 3.1 Set non-blocking
    ret = fcntl(Socketfd, F_GETFL, NULL);
    if (ret < 0) {
   //      ShowStatusLine("Get Sock Flag NG");
         usRtn=d_ETHERNET_Get_Sock_Flag_NG;
         return usRtn;
         //goto CHANNEL_CLOSE;
    }

    ret |= O_NONBLOCK;
    if (fcntl(Socketfd, F_SETFL, ret) < 0) {
  //      ShowStatusLine("Set Sock Flag NG");
        usRtn=d_ETHERNET_Set_Sock_Flag_NG;
         return usRtn;
        //goto CHANNEL_CLOSE;
    }

    // 3.2 Connect
    ret = connect(Socketfd, (struct sockaddr*) &sa, sizeof (sa));
    if (ret < 0) {
        if (errno != EINPROGRESS) {
     //       ShowStatusLine("Connect Failed");
            usRtn=d_ETHERNET_Connect_Failed;
           
            goto SOCKET_CLOSE;
        }

  /*      while (1) {
            tv.tv_sec = 15; //overtime
            tv.tv_usec = 0;
            FD_ZERO(&fdset);
            FD_SET(sd, &fdset);

            ret = select(sd + 1, NULL, &fdset, NULL, &tv);
            if (ret < 0) {
                if (errno != EINTR) {
                   ShowStatusLine( "Connect Failed");
                   usRtn=d_ETHERNET_Connect_Failed;
                    goto SOCKET_CLOSE;
                }
            } else if (ret > 0) {
                // Socket selected for write
                oplen = sizeof (int);
                if (getsockopt(sd, SOL_SOCKET, SO_ERROR, (void*) (&ret), &oplen) < 0) {
                    ShowStatusLine("Connect Failed");
                    usRtn=d_ETHERNET_Connect_Failed;
                    goto SOCKET_CLOSE;
                }

                // Check the value returned...
                if (ret) {
                    ShowStatusLine("Connect Failed");
                    usRtn=d_ETHERNET_Connect_Failed;
                    goto SOCKET_CLOSE;
                }
                 
                break;
            } else {
                ShowStatusLine("Connect Timeout");
                usRtn=d_ETHERNET_Connect_Timeout;
                goto SOCKET_CLOSE;
            }
        }*/
    }

    // 3.3 Set to blocking mode again
   ret = fcntl(Socketfd, F_GETFL, NULL);
    if (ret < 0) {
   //     ShowStatusLine("Get Sock Flag NG");
         usRtn=d_ETHERNET_Get_Sock_Flag_NG;
         return usRtn;//goto CHANNEL_CLOSE;
    }

    ret &= (~O_NONBLOCK);
    if (fcntl(Socketfd, F_SETFL, ret) < 0) {
   //     ShowStatusLine("Set Sock Flag NG");
        usRtn=d_ETHERNET_Set_Sock_Flag_NG;
        return usRtn;// goto CHANNEL_CLOSE;
    }

    return usRtn;

SOCKET_CLOSE:
        /************************************************************************/
        /* Step 22 is similar to CTOS_TCP_GPRSDisconnect or                     */
        /* CTOS_EthernetDisconnect	                                        */
        /************************************************************************/
        //////////////////////////////////////////////////////////////////////////
        // 22. TCP disconnection
    //    ShowStatusLine("Socket Close...");
        shutdown(Socketfd, 2);
CHANNEL_CLOSE:
    //////////////////////////////////////////////////////////////////////////
    // GPRS Close
    if (bChannel == CHANNEL_GPRS) {
   //     CTOS_LCDTPrintXY(1, 1, "GPRS Close...");
        CTOS_TCP_GPRSClose();
    } else {
   //     CTOS_LCDTPrintXY(1, 1, "Ethernet Close...");
        CTOS_EthernetClose;
    }        
        return usRtn;
}
        

USHORT Eth_SSLDisconnect(void)
{
    USHORT ret;
SSL_DISCONNECT:
    /************************************************************************/
    /* Step 19 is similar to CTOS_SSLDisConnect	                            */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 19. SSL disconnection
 //  ShowStatusLine("Shutdown SSL...");
   SSL_shutdown(ssl);

SSL_CLOSE:
    /************************************************************************/
    /* Step 20 and 21 are similar to CTOS_SSLDisConnect	                    */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 20. SSL free
  // ShowStatusLine( "Free SSL...");
    SSL_free(ssl);

CTX_CLOSE:
    //////////////////////////////////////////////////////////////////////////
    // 21. CTX free
 //   ShowStatusLine( "Free SSL CTX...");
    SSL_CTX_free(ssl_ctx);

SOCKET_CLOSE:
    /************************************************************************/
    /* Step 22 is similar to CTOS_TCP_GPRSDisconnect or                     */
    /* CTOS_EthernetDisconnect	                                            */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 22. TCP disconnection
   // ShowStatusLine("Socket Close...");
    shutdown(Socketfd, 2);
/*
CHANNEL_CLOSE:
    //////////////////////////////////////////////////////////////////////////
    // GPRS Close
    if (bChannel == CHANNEL_GPRS) {
       ShowStatusLine("GPRS Close...");
        CTOS_TCP_GPRSClose();
    } else {
       ShowStatusLine("Ethernet Close...");
        CTOS_EthernetClose;
    }
*/
    
   CTOS_LEDSet(d_LED_GREEN,d_OFF);
    return d_OK;
}

/*
 *bChannel = 
 *        CHANNEL_GPRS		1
 *        CHANNEL_ETHERNET	2      
 */
USHORT Eth_SSLSocketConnect() 
{
    BYTE bKey, baMsg[512];
    USHORT usRtn;
    USHORT  usBufLen;
    int  ret, type;
     // SSL_CTX *ssl_ctx;
   //  SSL *ssl;
    const SSL_METHOD *method = NULL;
    
    ULONG i, j, ulSize, ullen;
    FILE *fp;
    X509 *cert = NULL; 
   
    /************************************************************************/
    /* Step 4 to 9 are similar to CTOS_SSLNew                               */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 4. SSL library initialization
 //    ShowStatusLine("SSL Initialization...");
     SSL_library_init();

    ssl = NULL;
    ssl_ctx = NULL;

    //////////////////////////////////////////////////////////////////////////
    // 5. Set SSL protocol method
 //   ShowStatusLine( "Method Constructor...");
    method = TLSv1_method();		// Constructor for the TLSv1 SSL_METHOD structure for combined client and server
   //method = SSLv23_method(); // Constructor for the SSLv2 or SSLv3 SSL_METHOD structure for combined client and server.

    //////////////////////////////////////////////////////////////////////////
    // 6. Create a new SSL_CTX object as framework to establish TLS/SSL enabled connections
   //   ShowStatusLine( "New SSL CTX...");
    ssl_ctx = SSL_CTX_new(method);
    if (!ssl_ctx) {
   //     ShowStatusLine( "New CTX Failed");
        usRtn=d_ETHERNET_New_CTX_Failed;
        goto SOCKET_CLOSE;
    }

    //////////////////////////////////////////////////////////////////////////
    // 7. Create a new SSL structure for a connection 
  //  ShowStatusLine("New SSL...");
    ssl = SSL_new(ssl_ctx);
    if (!ssl) {
  //      ShowStatusLine( "New SSL Failed");
        usRtn=d_ETHERNET_New_SSL_Failed;
        goto CTX_CLOSE;
    }

    //////////////////////////////////////////////////////////////////////////
    // 8. Set Cipher Suites
  //   ShowStatusLine("Set Cipher...");
    if (!SSL_set_cipher_list(ssl, CipherSuites)) {
  //       ShowStatusLine("Set Cipher Failed");
         usRtn=d_ETHERNET_Set_Cipher_Failed;
        goto SSL_CLOSE;
    }

    //////////////////////////////////////////////////////////////////////////
    // 9. Connect the SSL object with a file descriptor 
  //   ShowStatusLine( "Set Socket fd...");
    if (!SSL_set_fd(ssl, Socketfd)) {
  //       ShowStatusLine("Set fd Failed");
        usRtn=d_ETHERNET_Set_fd_Failed;
        goto SSL_CLOSE;
    }

   //  ShowStatusLine(  "SSL Init OK");

    /************************************************************************/
    /* Step 10 to 14 are similar to CTOS_SSLLoadObject	                    */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 10. Set peer certificate verification parameters
    SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_NONE, NULL);

/*
    //////////////////////////////////////////////////////////////////////////
    // 12. Set default locations for trusted CA certificates
    usRtn = SSL_CTX_load_verify_locations(ssl_ctx, gCA, NULL);
    if (!usRtn) {
         ShowStatusLine( "Load CA Failed!!!");
         usRtn=d_ETHERNET_Load_CA_Failed;
        goto SSL_CLOSE;
    }

    //////////////////////////////////////////////////////////////////////////
    // 13. Store certificate to a file and load it.
     ShowStatusLine( "Load Cert...");



    if (SSL_CTX_use_certificate_file(ssl_ctx, FILE_CERT, SSL_FILETYPE_PEM) <= 0) {
        CTOS_LCDTPrintXY(1, 8, "Load Cert Failed");
        usRtn=d_ETHERNET_Load_Cert_Failed;
        goto SSL_CLOSE;
    }

    //////////////////////////////////////////////////////////////////////////
    // 14. Store private key to a file and load it.
    CTOS_LCDTPrintXY(1, 1, "Load Key...");


    if (SSL_CTX_use_PrivateKey_file(ssl_ctx, gCA, SSL_FILETYPE_PEM) <= 0) {
        ShowStatusLine("Load Key Failed");
        usRtn=d_ETHERNET_Load_Key_Failed;
        goto SSL_CLOSE;
    }

    ShowStatusLine( "Load Object OK");
*/

    /************************************************************************/
    /* Step 15 is similar to CTOS_SSLConnect	                            */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 15. Initiate the TLS/SSL handshake with an TLS/SSL server 
  // ShowStatusLine( "SSL Connect...");
    ret = SSL_connect(ssl);
    if (ret == -1) {
       int iret= SSL_get_error(ssl,ret);
  //      ShowStatusLine( "SSL Connect Failed");
         usRtn=d_ETHERNET_SSL_Connect_Failed;
        goto SSL_CLOSE;
    }

  // ShowStatusLine("SSL Connect OK");
   usRtn=d_OK; 
  
    /************************************************************************/
    /* Step 16 is similar to CTOS_SSLConnect	                            */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 16. Verify certificate
   // ShowStatusLine( "Verify...");
    //if (SSL_get_verify_result(ssl) != X509_V_OK || !SSL_get_peer_certificate(ssl)) {
    if (!SSL_get_peer_certificate(ssl)) {
    //   ShowStatusLine( "Verify Failed");
        usRtn=d_ETHERNET_Verify_Failed;
        goto SSL_DISCONNECT;
    }

   // ShowStatusLine( "SSL Verify OK");
    return usRtn;
SSL_DISCONNECT:
    /************************************************************************/
    /* Step 19 is similar to CTOS_SSLDisConnect	                            */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 19. SSL disconnection
   //ShowStatusLine("Shutdown SSL...");
   SSL_shutdown(ssl);

SSL_CLOSE:
    /************************************************************************/
    /* Step 20 and 21 are similar to CTOS_SSLDisConnect	                    */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 20. SSL free
//   ShowStatusLine( "Free SSL...");
    SSL_free(ssl);

CTX_CLOSE:
    //////////////////////////////////////////////////////////////////////////
    // 21. CTX free
 //   ShowStatusLine( "Free SSL CTX...");
    SSL_CTX_free(ssl_ctx);

SOCKET_CLOSE:
        /************************************************************************/
        /* Step 22 is similar to CTOS_TCP_GPRSDisconnect or                     */
        /* CTOS_EthernetDisconnect	                                        */
        /************************************************************************/
        //////////////////////////////////////////////////////////////////////////
        // 22. TCP disconnection
     //   ShowStatusLine("Socket Close...");
        shutdown(Socketfd, 2);

        return usRtn;
   
}
void Eth_SSLSocketDisConnect() 
{

  
    SSL_DISCONNECT:
        /************************************************************************/
        /* Step 19 is similar to CTOS_SSLDisConnect	                            */
        /************************************************************************/
        //////////////////////////////////////////////////////////////////////////
        // 19. SSL disconnection
    //   ShowStatusLine("Shutdown SSL...");
       SSL_shutdown(ssl);

    SSL_CLOSE:
        /************************************************************************/
        /* Step 20 and 21 are similar to CTOS_SSLDisConnect	                    */
        /************************************************************************/
        //////////////////////////////////////////////////////////////////////////
        // 20. SSL free
     //  ShowStatusLine( "Free SSL...");
       SSL_free(ssl);

    CTX_CLOSE:
        //////////////////////////////////////////////////////////////////////////
        // 21. CTX free
    //    ShowStatusLine( "Free SSL CTX...");
        SSL_CTX_free(ssl_ctx);

    SOCKET_CLOSE:
            /************************************************************************/
            /* Step 22 is similar to CTOS_TCP_GPRSDisconnect or                     */
            /* CTOS_EthernetDisconnect	                                        */
            /************************************************************************/
            //////////////////////////////////////////////////////////////////////////
            // 22. TCP disconnection
      //      ShowStatusLine("Socket Close...");
            shutdown(Socketfd, 2);
             CTOS_LEDSet(d_LED_GREEN,d_OFF);
     
}

static int wait_read_socket(int sockfd, int for_recv, long timeout_ms)
{
  struct timeval tv;
  fd_set infd, outfd, errfd;
  int res;
 
  tv.tv_sec = timeout_ms / 1000;
  tv.tv_usec= (timeout_ms % 1000) * 1000;
 
  FD_ZERO(&infd);
  FD_ZERO(&outfd);
  FD_ZERO(&errfd);
 
  FD_SET(sockfd, &errfd); /* always check for error */ 
 
  if(for_recv)
  {
    FD_SET(sockfd, &infd);
  }
  else
  {
    FD_SET(sockfd, &outfd);
  }
 
  /* select() returns the number of signalled sockets or -1 */ 
  res = select(sockfd + 1, &infd, &outfd, &errfd, &tv);
  return res;
}
USHORT Eth_PutDeviecBackOnBase()
{
 BOOL fPortable,fPCI;
   USHORT mkHWSupport;
   USHORT usRet= CTOS_HWSettingGet(&fPortable,&fPCI,&mkHWSupport); 
   if(usRet==d_OK&&fPortable==d_TRUE){//如為移動式設備且採實体網路連線 ，檢查是否放回底座
       if(bgNETWORKChannel==CHANNEL_ETHERNET){ 
              usRet= CTOS_CradleAttached();
              if(usRet==d_NO){
                   CTOS_Beep();
                   CTOS_Beep();
                   usRet= ShowMessage2line(gTransTitle,"網路連線中...","請將設備放回底座",Type_ComformOK);  
                   CTOS_Delay(50);
                   usRet= CTOS_CradleAttached();
                   if(usRet==d_NO)
                   {   
                       ShowMessage2line(gTransTitle,"設備未在底座上.","無法進行連線交易",Type_wait2sec);  
                       return usRet;
                   }
              }
        }
   }
   return d_OK;
}
USHORT Eth_CheckDeviceStatus()
{
   BOOL fPortable,fPCI;
   USHORT mkHWSupport;
   USHORT usRet= CTOS_HWSettingGet(&fPortable,&fPCI,&mkHWSupport); 
   if(usRet==d_OK&&fPortable==d_TRUE){//如為移動式設備且採實体網路連線 ，檢查是否放回底座
       if(bgNETWORKChannel==CHANNEL_ETHERNET){ 
              usRet= CTOS_CradleAttached();
              if(usRet==d_NO){
                  return d_Fail;
                 }
       }
       
   }
   return d_OK;
}

USHORT Eth_CheckDeviceSupport()
{
   BOOL fPortable,fPCI;
   USHORT mkHWSupport;
   USHORT usRet= CTOS_HWSettingGet(&fPortable,&fPCI,&mkHWSupport);  
   return mkHWSupport;
}
USHORT Eth_SocketCheckConnectStatus()
{
  BYTE bState;
  USHORT usRtn;
  BYTE str[5];
   if(strcmp(gConfig.ETHERNET.EthernetCHANNEL,"GPRS")==0) {
       
        usRtn = CTOS_TCP_GPRSStatus(&bState);
        if (usRtn == d_OK)
        { 
            sprintf(str,"%d",bState);
            CTOS_LCDGTextOut(320-(9*7),240-18-18-18,str,d_FONT_9x18,FALSE);
            if(bState!= TCP_GPRS_STATE_ESTABLISHED){
        //sprintf(baStr, "Register: %d", bTmp);
        //CTOS_LCDTPrintXY(1, 2, baStr);
                 return d_ETHERNET_Connect_Failed;
            }
        }
   }else{ 
        struct sockaddr_in guest;  
        socklen_t guest_len = sizeof(guest);  
       // getsockname(sockfd, (struct sockaddr *)&serv, &serv_len);  
       int  iret=getpeername(Socketfd, (struct sockaddr *)&guest, &guest_len);  
       if(iret!=0) return d_ETHERNET_Connect_Failed;
   }
   return d_OK;
}

/*
void  Eth_SSLConnect_SOCKET_thread()
{
    USHORT ret= Eth_SSLConnect_SOCKET();
    pthread_exit((void *)ret);
}
*/
USHORT Eth_SSLConnect_SOCKET()
{
     USHORT usRet;
 /*    USHORT usRet= Eth_SocketCheckConnectStatus();
    if(usRet==d_OK) {
        return usRet;
       //    Eth_SSLSocketDisConnect();
    }*/
   gCOMMSTATUS=COMM_STATUS_Connecting;
   usRet=Eth_Connect(bgNETWORKChannel,gHOSTIP,atoi(gHOSTPORT));
   if(usRet!=d_OK) 
   {
        gCOMMSTATUS=COMM_STATUS_ConnecteFail;
   //    ShowLine(0,40+16,Big_Font_Size,"請重試...",FALSE);     
       return usRet;
   }
   usRet= Eth_SSLSocketConnect(); 
   if(usRet!=d_OK) 
   {
       gCOMMSTATUS=COMM_STATUS_ConnecteFail;
   //    ShowLine(0,40+16,Big_Font_Size,"請重試...",FALSE);      
       return usRet;
   }
   gCOMMSTATUS= COMM_STATUS_ConnecteOK;
   CTOS_LEDSet(d_LED_GREEN,d_ON);
   return d_OK;
}


USHORT Eth_SSLSendandRecv_Socket() 
{
    BYTE bKey, baMsg[512];
    USHORT  usBufLen;
    int  ret, type;
    int   RetryTime=10; 
    
    BYTE  baIP[20], bIPLen;
    ULONG ulTimoeout;
    ULONG i, j, ulSize;
    /************************************************************************/
    /* Step 17 is similar to CTOS_SSLWrite	                                */
    /************************************************************************/
    //////////////////////////////////////////////////////////////////////////
    // 17. Write bytes to a TLS/SSL connection
    USHORT usRet;
    USHORT sendbufsize=2048;
    USHORT recebufsize=2048*5;
    BYTE  SendPack[sendbufsize], baBuf[recebufsize];
    
 //  Eth_Init(); 
   // SendPack=malloc(Filesize);    
  // usRet=Eth_TCPConnect();
 
   usRet= Eth_SocketCheckConnectStatus();
   if(usRet!=d_OK) return usRet;
    if(!wait_on_socket(Socketfd, 0, 20000L))
    {
      return d_ETHERNET_SSL_Write_Failed;
    }
   /**********************************************/
   
   
    ULONG getlen,ilen,Sendlen,offset;
    remove(RecvFile);
    int  Filesize= File_GetLen(SendFile);
    if(Filesize==0) return d_ERR_FILE_SIZE_ERR;   
    int RemainSize=Filesize;
    SendDebugFile(SendFile);
    offset=0;
    //********************************************************** 
    memset(SendPack,0x20,sizeof(SendPack));
    do{
        if(RemainSize>sendbufsize)
            Sendlen=sendbufsize;
        else
            Sendlen=RemainSize;       
        
        
        usRet=usReadFileData2(SendFile,offset,&Sendlen,SendPack);
        if(usRet!=d_OK) return usRet;
          ShowStatusLine("資料傳輸中....");
       RemainSize-=Sendlen;
       offset+=Sendlen;
       if(Sendlen<2048) Sendlen=2048;
       ilen = SSL_write(ssl,SendPack, Sendlen);
       if (ilen == -1) 
        {
          usRet=d_ETHERNET_SSL_Write_Failed;
          return usRet;
        }
    }while(RemainSize!=0);
   
 
   //ShowStatusLine("SSL Write OK");
   
    int iRet;
      //  ShowStatusLine( "SSL Read...");
 //   wait_on_socket(Socketfd, 1, 20000L);
    //  wait_read_socket(sd, 1, 20000L);
    struct timeval timeout;      
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    if (setsockopt(Socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof (timeout)) < 0) {
            ShowStatusLine( "Set Rx TO Failed");
            usRet=d_ETHERNET_Set_Rx_TO_Failed;
            return usRet;
            // goto SSL_DISCONNECT;
   }
      
       /* CTOS_KBDHit(&bKey);
        if (bKey == d_KBD_CANCEL)
             return d_ERR_USERCANCEL;
            //  goto SSL_DISCONNECT;
        * /
        

        /************************************************************************/
        /* Step 18 is similar to CTOS_SSLRead	                                */
        /************************************************************************/
        //////////////////////////////////////////////////////////////////////////
        // 18. Read bytes from a TLS/SSL connection.
      
       
         memset(gReceiveData,0x00,sizeof(gReceiveData));
          memset(baBuf,0x00,sizeof(baBuf));
         ulSize=sizeof(baBuf);
        do{
                ShowStatusLine("等待接收中.");
              //  memset(baBuf,0x00,sizeof(baBuf));

                ilen = SSL_read(ssl, baBuf, ulSize);
                if (ilen==-1){
                    ShowStatusLine( "Read Failed");
                    iRet=SSL_get_error(ssl,  0);
                }
                if(ilen>0){
                     strncat(gReceiveData,baBuf,ulSize);                  
                     int iret= myxml_GetTag(gReceiveData,"TransXML",baBuf);
                     if(iret!=0){
                          CTOS_Beep();
                          return d_OK;
                     }      
                }else{   
                     ShowStatusLine("等待接收中..");
                     CTOS_Beep();
                }

              RetryTime--;
       } while ( getlen != -1 && RetryTime>0);
    ShowStatusLine("接收逾時。"); 
    usRet=d_ETHERNET_SSL_RECEIVE_TIMEOUT;
    return usRet;
}

USHORT GPRS_Regiseter()
{
    USHORT usRtn;
    BYTE baMsg[32];
    if(strcmp(gConfig.ETHERNET.EthernetCHANNEL,"GPRS")==0) {
         //////////////////////////////////////////////////////////////////////////
         // SIM check ready
        //////////////////////////////////////////////////////////////////////////
        ShowLine(0,40+16,Big_Font_Size,"行動網路註冊中..",FALSE);
          if(strcmp(gConfig.ETHERNET.GPRS.SIMSLOT,"SIM2")==0)   
              usRtn = CTOS_GSMSelectSIM(d_GPRS_SIM2);
           else 
              usRtn = CTOS_GSMSelectSIM(d_GPRS_SIM1);

          if (usRtn != d_OK)
            {
               sprintf(baMsg, "%04X ", usRtn);
                MessageBox("通訊網路","GSM無法啟動" ,"請檢查SIM卡",baMsg,"",d_MB_CHECK);
               return usRtn;
            }   

        
           usRtn = CTOS_SIMCheckReady();
           if(usRtn!=d_GSM_SIM_READY){
                if (usRtn == d_GSM_SIM_NOT_READY){
                     MessageBox("通訊網路","SIM異常" ,"請檢查SIM卡",baMsg,"",d_MB_CHECK);
                     return usRtn;  
                }
           }
            ShowLine(0,40+16,Big_Font_Size,"GPRS啟動完成。",FALSE);
          /////////////////////////////////////////////////////////////////////////
           
            usRtn= CTOS_PINGetAuthStatus (  );
            if(usRtn!=d_GSM_NO_AUTH_NEED){
                if(usRtn==d_GSM_AUTH_PIN||usRtn==d_GSM_AUTH_PUK)
                {  
                    usRtn=CTOS_PINVerify(d_GSM_PIN_PUK_1, gConfig.ETHERNET.GPRS.PINCODE, strlen( gConfig.ETHERNET.GPRS.PINCODE));
                    if(usRtn!=0)
                    {
                        sprintf(baMsg, "%04X", usRtn);
                        MessageBox("通訊網路","PIN檢查錯誤","輸入錯誤" ,"請確認!!",baMsg,d_MB_CHECK);
                        return usRtn;
                    }
                }            
            }
            //////////////////////////////////////////////////////////////////////////
            // GPRS Register
        ShowLine(0,40+16,Big_Font_Size,"行動網路註冊中..",FALSE);
           
          DWORD dwStatus;
          ULONG ulTick = CTOS_TickGet();
          int counter;
          do{
                sprintf(baMsg, "%ldms", (CTOS_TickGet() - ulTick) * 10);
                counter=((CTOS_TickGet() - ulTick)/100);
                usRtn = CTOS_GPRSGetRegState(&bGPRSState);
                if (usRtn != d_OK) {
                    sprintf(baMsg, "Register NG %04X", usRtn);
                    MessageBox("通訊網路","GPRS ","" ,"",baMsg,d_MB_CHECK);
                    CTOS_LCDTPrintXY(1, 4, baMsg);
                    return usRtn;
                } else {
                    switch(bGPRSState){
                        case d_GSM_GPRS_STATE_NOT_REG:
                            sprintf(baMsg, "GSM_GPRS_STATE_NOT_REG");
                           // MessageBox("通訊網路","GPRS ","Get Register" ,"尚未完成連線",baMsg,d_MB_CHECK);
                           // usRtn=d_Fail;
                            continue;
                            break;
                        case d_GSM_GPRS_STATE_REG: 
                            usRtn=d_OK;
                            break;
                        case d_GSM_GPRS_STATE_TRYING:
                            sprintf(baMsg, "GSM GPRS STATE TRYING");
                           // MessageBox("通訊網路","GPRS ","Get Register" ,"嘗試連線中",baMsg,d_MB_CHECK);
                           // usRtn=d_Fail; 
                            continue;
                            break;
                        case d_GSM_GPRS_STATE_DENY:
                            sprintf(baMsg, "電信業者拒絕連線");
                            MessageBox("通訊網路","GPRS ","Get Register" ,"",baMsg,d_MB_CHECK);
                            usRtn=d_Fail;
                            break;
                        case d_GSM_GPRS_STATE_UNKNOW: 
                            sprintf(baMsg, "不明錯誤");
                            MessageBox("通訊網路","GPRS ","Get Register" ,"",baMsg,d_MB_CHECK);
                             usRtn=d_Fail;
                            break;
                        case d_GSM_GPRS_STATE_ROAM: 
                            MessageBox("通訊網路","GPRS ","Get Register" ,"Terminal is registered","in roaming condition",d_MB_CHECK);
                            usRtn=d_Fail;
                            break;
                    }
             
                return usRtn;
            }
       }while(counter<60);
      
       
        }   
     return usRtn;
}  

/*CURL*/

static curl_socket_t opensocket(void *clientp,
                                curlsocktype purpose,
                                struct curl_sockaddr *address)
{
  curl_socket_t sockfd;
  (void)purpose;
  (void)address;
  sockfd = *(curl_socket_t *)clientp;
  /* the actual externally set socket is passed in via the OPENSOCKETDATA
     option */ 
  return sockfd;
}
 
static int sockopt_callback(void *clientp, curl_socket_t curlfd,
                            curlsocktype purpose)
{
  (void)clientp;
  (void)curlfd;
  (void)purpose;
  /* This return code was added in libcurl 7.21.5 */ 
  return CURL_SOCKOPT_ALREADY_CONNECTED;
}

static int wait_on_socket(curl_socket_t sockfd, int for_recv, long timeout_ms)
{
  struct timeval tv;
  fd_set infd, outfd, errfd;
  int res;
 
  tv.tv_sec = timeout_ms / 1000;
  tv.tv_usec= (timeout_ms % 1000) * 1000;
 
  FD_ZERO(&infd);
  FD_ZERO(&outfd);
  FD_ZERO(&errfd);
 
  FD_SET(sockfd, &errfd); /* always check for error */ 
 
  if(for_recv)
  {
    FD_SET(sockfd, &infd);
  }
  else
  {
    FD_SET(sockfd, &outfd);
  }
 
  /* select() returns the number of signalled sockets or -1 */ 
  res = select(sockfd + 1, &infd, &outfd, &errfd, &tv);
  return res;
}

USHORT Eth_SocketConnet(char * ip,char *port)
{
  CURLcode res;
 
  BYTE str[64]; 
  struct sockaddr_in servaddr;  /*  socket address structure  */ 
       /* Create the socket "manually" */ 
  if( (Socketfd = socket(AF_INET, SOCK_STREAM, 0)) == CURL_SOCKET_BAD ) {
      printf("Error creating listening socket.\n");
      return d_ETHERNET_Open_Socket_NG;
  }
 
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port   = htons(atoi(port));
 
  if (INADDR_NONE == (servaddr.sin_addr.s_addr = inet_addr(ip)))
      return d_ETHERNET_WRONGADDRESS;
 
    if(connect(Socketfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) 
    {
      close(Socketfd);
      printf("client error: connect: %s\n", strerror(errno));
      return d_ETHERNET_Connect_Failed;
    }
 
  curl = curl_easy_init();
  if(curl) {
    /*
     * Note that libcurl will internally think that you connect to the host
     * and port that you specify in the URL option.
     */ 
  
    sprintf(str,"HTTPS://%s:%s",gHOSTIP,gHOSTPORT);
    curl_easy_setopt(curl, CURLOPT_URL, str);
   
  //  Inet_ntop(AF_INET, &serv.sin_addr, serv_ip, sizeof(serv_ip));  
 //   Inet_ntop(AF_INET, &guest.sin_addr, guest_ip, sizeof(guest_ip));  
       /* call this function to get a socket */ 
    curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, opensocket);
    curl_easy_setopt(curl, CURLOPT_OPENSOCKETDATA, &Socketfd);
    /* call this function to set options for the socket */ 
    curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION, sockopt_callback);
     /* Use SSL  */ 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
   
 
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    
    /* Do not do the transfer - only connect to host */ 
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
    res = curl_easy_perform(curl);
    if(CURLE_OK != res)
    {
      printf("Error: %s\n", strerror(res));
      return d_ETHERNET_SSLConnect_Failed;
    }
  }
    return d_OK;
}
USHORT Eth_SSLSocketSendandRecv_CURL()
{
    CURLcode res;
    curl_socket_t sockfd; /* socket */ 
    long sockextr;
     USHORT usRet= Eth_SocketCheckConnectStatus();
     if(usRet!=d_OK) return usRet;
     
    /* Extract the socket from the curl handle - we'll need it for waiting.
     * Note that this API takes a pointer to a 'long' while we use
     * curl_socket_t for sockets otherwise.
     */ 
    res = curl_easy_getinfo(curl, CURLINFO_LASTSOCKET, &sockextr); 
    if(CURLE_OK != res)
    {
      printf("Error: %s\n", curl_easy_strerror(res));
      return 1;
    } 
    Socketfd = sockextr;
 
    /* wait for the socket to become ready for sending */ 
    if(!wait_on_socket(Socketfd, 0, 60000L))
    {
      printf("Error: timeout.\n");
      return 1;
    }
  
    
    BYTE  SendPack[1024*3], baBuf[1024*10];
   
     memset(SendPack,0x00,sizeof(SendPack));
     memset(baBuf,0x00,sizeof(baBuf));
     int  Filesize= File_GetLen(SendFile);
    if(Filesize==0) return d_ERR_FILE_SIZE_ERR;   
  
  // SendDebugFile(SendFile);
  
    size_t iolen;
    ULONG getlen=sizeof(SendPack);   
     usRet=usReadFileData(SendFile,&getlen,SendPack);
    if(usRet!=d_OK) return usRet;
    
    ShowStatusLine("資料傳輸中....");
    
    res = curl_easy_send(curl, SendPack, getlen, &iolen);
    if(CURLE_OK != res)
    {
      printf("Error: %s\n", curl_easy_strerror(res));
      return 1;
    }
     ShowStatusLine("等待接收中..");
   
    curl_off_t nread;
    ezxml_t ezxml_recv;
    /* read the response */ 
    memset(gReceiveData,0x00,sizeof(gReceiveData));
    for(;;)
    {
      wait_on_socket(Socketfd, 1, 60000L);
      res = curl_easy_recv(curl, baBuf, sizeof(baBuf), &iolen); 
      if(CURLE_OK != res)
        break;
 
      nread = (curl_off_t)iolen;
      strncat(gReceiveData,baBuf,iolen);                  
      int iret= myxml_GetTag(gReceiveData,"TransXML",baBuf);
      if(iret!=0){
        CTOS_Beep();
     //  close(sockfd);
     //  curl_easy_cleanup(curl);
       
       usRet= Eth_SocketCheckConnectStatus();
       if(usRet!=d_OK) return usRet;
       return d_OK;
      }
     // printf("Received %" CURL_FORMAT_CURL_OFF_T " bytes.\n", nread);
    }
   // curl_easy_cleanup(curl);
 
    if(res) {
      printf("libcurl error: %d\n", res);
      return d_ETHERNET_SSL_RECEIVE_TIMEOUT;
    }
  
  return 0;

}

/*
USHORT SSLSocketSendandRecv_fortest(STR * file)
{
  
    BOOL    blRet;
    BYTE    SendPack[1024*3], baBuf[1024*3];
    BYTE    bKey, bTypef;
    USHORT  usRet, usBufLen, i;
    int     RetryTime=10; 
    USHORT sendbufsize=1024*3;
    USHORT recebufsize=1024*3;
    BYTE baMsg[64];
    CTOS_LCDTClearDisplay();
  
   
    CTOS_LCDTPrintXY(1, 1, "Ethernet Open...");
    
    BYTE IP[15+1]   = "211.78.134.165";
    BYTE PORT[4+1]  ="7000";
    BYTE bIP[4];
    bIP[3]=0xa5;
    bIP[2]=0x86;
    bIP[1]=0x4e;
    bIP[0]=0xd3;
    
    CTOS_LCDTPrintXY(1, 8,"網路連線中");
  //  usRet= CTOS_EthernetConnectEx(IP,strlen(IP),PORT,strlen(PORT) );
   usRet= CTOS_TCP_GPRSConnectEx(&bSocket,&bIP,7000);
   usRet = pollStatusResult("GPRS Connect ", usRet);
   if (usRet != d_OK) return usRet; 
 
  
   
   DWORD dwStatus;BYTE bSocket ;
   usRet= CTOS_EthernetStatus ( &dwStatus );
   CTOS_LCDTPrintXY(1, 8,"建立SSL連線");
  // usRet = CTOS_SSLNew(d_SSL_CONNECTION_ETHERNET, bSocket);
   usRet = CTOS_SSLNew(d_SSL_CONNECTION_GPRS, bSocket);
   if (usRet != d_OK) return usRet; 
   
  
  //  CTOS_SSLSetReadTimeout(2000);       //Set the Read Timeout to 2s
    int size=0;
    
    BYTE ca[2048];
    memset(ca,0x00,sizeof(ca));
    ULONG  Filesize= File_GetLen("ck1.cer");
    if(Filesize==0) return 9999;   
    usRet=usReadFileData("ck1.cer",&Filesize,ca);
    usRet = CTOS_SSLLoadObject(d_SSL_OBJ_X509_CERT, ca,Filesize , NULL);
    if (usRet != d_OK) return usRet; 
   
   
 
   // CTOS_SSLSetReadTimeout(2000);       //Set the Read Timeout to 2s
     CTOS_LCDTPrintXY(1, 8,"SSL 連接中");
   usRet= CTOS_EthernetStatus ( &dwStatus );
    usRet = CTOS_SSLConnect();
    if (usRet != d_OK) return usRet; 
    
    CTOS_LCDTPrintXY(1, 8,"Handshake OK");
   // return usRet;
     
    
      Filesize= File_GetLen(file);
    if(Filesize==0) return 9999;   
    int RemainSize=Filesize;
    ULONG getlen;
   // SendPack=malloc(Filesize);    
    do{
        if(RemainSize>2048)
            getlen=2048;
        else
            getlen=RemainSize;       
         sprintf(baMsg,"Send File %s",file);
         CTOS_LCDTPrintXY(1, 2, baMsg);
       
        usRet=usReadFileData(file,&getlen,SendPack);
        if(usRet!=d_OK) return usRet;
          CTOS_LCDTPrintXY(1, 8,"data transfer....");
         RemainSize-=getlen;
         usRet = CTOS_SSLWrite(SendPack, getlen);
       if (usRet != d_OK) 
             goto DISCONNECT;
   }while(RemainSize!=0);
 
  
   
    memset(baBuf,0x00,recebufsize);
    usRet=CTOS_SSLSetReadTimeout(20000);
    CTOS_LCDTPrintXY(1, 8,"rece waiting.");
    usBufLen = recebufsize;
    usRet = CTOS_SSLRead(baBuf, &usBufLen);
    if(usRet==d_OK){
            if (usBufLen == -1) {
                    CTOS_LCDTPrintXY(1, 8, "Read Failed");
                    CTOS_KBDGet(&bKey);
                    goto DISCONNECT;
             } else if (usBufLen > 0) {
                sprintf(baMsg,"receive %d byte",usBufLen);
                CTOS_LCDTPrintXY(1, 3, baMsg);

                CTOS_Beep();
                CTOS_KBDGet(&bKey);
                goto DISCONNECT;
            } else {
                CTOS_LCDTPrintXY(1, 8, "EOF!!");
                CTOS_KBDGet(&bKey);
                goto DISCONNECT;
            }
             
         
         } 
    CTOS_LCDTPrintXY(1, 8,"timeout。");
DISCONNECT:
 //   SSLSocketDisConnect();
//    CTOS_EthernetClose();
   
   
    return 0;
 }*/