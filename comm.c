
/** These two files are necessary for calling CTOS API **/
#include "ECCAPP.h"
#include "Eth.h"
/*
 * This is an example showing how to get a single file from an FTP server.
 * It delays the actual destination file creation until the first write
 * callback so that it won't create an empty file in case the remote file
 * doesn't exist or something else fails.
 */
#define LOCAL_FILE      SendFile
#define UPLOAD_FILE_AS  "send.xml"
#define REMOTE_URL      "ftps://user:1234@192.168.2.1/"   UPLOAD_FILE_AS
#define RENAME_FILE_TO  "bibib.bmp"
//CA&apos;s Certificate used to verify the Server&apos;s Certificate



USHORT Ethernet_Check()
{  
    USHORT ret;
    BYTE retstr[64];
    BYTE URLIP[15],DNSIP[15];
    BYTE URL[64]="cmas-gateway.easycard.com.tw";
   
    ret= GetFTPINFO();
    if(ret!=d_OK) return ret;
    ret= GetHOSTINFO();
    if(ret!=d_OK) return ret;
    BYTE len=sizeof(DNSIP);
    //檢查DNS是否設定
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DNSIP, DNSIP,&len);
    if(ret!=d_OK){
         sprintf(retstr,"Get DNS Fail %d",ret);
         CTOS_PrinterPutString (retstr);
         return ret;
    }
    if(strcmp(gConfig.ETHERNET.NETWORKMODE,"INTERNET")==0){
            //檢查GATEWAY URL 是否可連上
            len=sizeof(gHOSTURL);
            ret= CTOS_EthernetConnectURLPort(gHOSTURL, strlen(gHOSTURL),gHOSTPORT, strlen(gHOSTPORT));
            if(ret!=d_OK){
                 sprintf(retstr,"%s Connect Fail %d",gHOSTURL,ret);
                 CTOS_PrinterPutString (retstr);        
            }else{
                 CTOS_EthernetDisconnect();
                 CTOS_PrinterPutString ("URL Connect OK");  
                 len=sizeof(gHOSTURL);
                 memset(URLIP,0x00,sizeof(URLIP));
                 ret=CTOS_EthernetURL2IP (gHOSTURL, strlen(gHOSTURL),URLIP, &len );
                 sprintf(retstr,"DNS 解析結果%s",URLIP);
                 CTOS_PrinterPutString (retstr);
            }
            //檢查GATEWAY IP是否通暢
           ret= CTOS_EthernetConnectEx (gHOSTIP,strlen(gHOSTIP) , gHOSTPORT,strlen(gHOSTPORT) );
           if(ret!=d_OK){
                 sprintf(retstr,"%s Connect Fail %d",gHOSTIP,ret);
                 CTOS_PrinterPutString (retstr);        
           }else{
                 CTOS_EthernetDisconnect();
                 CTOS_PrinterPutString ("IP Connect OK");           
           }
           
            sprintf(retstr,"URL FTP 下載測試:");
            CTOS_PrinterPutString (retstr);
            ret= ECC_FTPGetFileShowStatusForTest("URL FTP DOWNLOAD 使用URL ",gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL,"ftp_edc","Cmas@2013","test_001m.zip", "/out/speedtest/test_001m.zip",1);
            sprintf(retstr,"IP FTP 下載測試:");
            CTOS_PrinterPutString (retstr);
            ret= ECC_FTPGetFileShowStatusForTest("FTP DOWNLOAD 使用IP",gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP,"ftp_edc","Cmas@2013","test_001m.zip", "/out/speedtest/test_001m.zip",1);

    }else{
            ret= CTOS_EthernetConnectEx (gHOSTVIPIP,strlen(gHOSTVIPIP) , gHOSTPORT,strlen(gHOSTPORT) );
           if(ret!=d_OK){
                 sprintf(retstr,"%s Connect Fail %d",gHOSTIP,ret);
                 CTOS_PrinterPutString (retstr);        
           }else{
                 CTOS_EthernetDisconnect();
                 CTOS_PrinterPutString ("VIP IP Connect OK");           
           }
            sprintf(retstr,"VIPIP FTP 下載測試:");
            CTOS_PrinterPutString (retstr);
            ret= ECC_FTPGetFileShowStatusForTest("FTP DOWNLOAD 使用IP",gConfig.ETHERNET.HOST_PRODUCTION.FTP.VIPIP,"ftp_edc","Cmas@2013","test_001m.zip", "/out/speedtest/test_001m.zip",1);

    }
  
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
USHORT Ethernet_Connect(void)
{
    BYTE    bKey, baStr[64];
    USHORT  usRet;
    usRet=GetHOSTINFO();
    
        if(strcmp(gConfig.ETHERNET.NETWORKMODE,"INTERNET")==0){
          usRet= CTOS_EthernetConnectEx(gHOSTIP,strlen(gHOSTIP), gHOSTPORT,strlen(gHOSTPORT) );
          if(usRet!=d_OK)
          {
              usRet= CTOS_EthernetConnectURLPort(gHOSTURL, strlen(gHOSTURL),gHOSTPORT, strlen(gHOSTPORT));
              if (usRet != d_OK)   return usRet;
          }
             return d_OK;
        }else{
             usRet= CTOS_EthernetConnectEx (gHOSTVIPIP,strlen(gHOSTVIPIP) , gHOSTPORT,strlen(gHOSTPORT) );
             if(usRet!=d_OK)  return usRet;
        }
         
}

USHORT Ethernet_Disconnect(void)
{
     USHORT ret;
    if (bgNETWORKChannel == CHANNEL_GPRS) {
          ret= CTOS_TCP_GPRSDisconnect(bSocket);
    }else{
          ret=CTOS_EthernetDisconnect();
    }

    return ret;
}

/*
void* SSLSocketConnect_thread()
{
   
    SSLSocketDisConnect();    
    
    USHORT ret= SSLSocketConnect();
    pthread_exit((void *)&ret);
}
void* SSLSocketConnect_thread2()
{
   
    SSLSocketDisConnect();    
    USHORT ret= SSLSocketConnect();
    if(ret!=d_OK|| gCOMMSTATUS!=COMM_STATUS_ConnecteOK){
         pthread_exit((void *)ret);
    }
    while(1){
        switch(gCOMM_CMD){
            case COMM_CMD_Send:
                gCOMM_CMD=COMM_CMD_IDLE;
                ret= SSLSocketSendandRecv2(0);
                break;
            case COMM_CMD_DISCONNECT:
                gCOMM_CMD=COMM_CMD_IDLE;
                SSLSocketDisConnect();  
                pthread_exit((void *)ret);
                break;
        }
      
    }
    pthread_exit((void *)ret);
}
  
USHORT WaitSSLCONNECT()
{
    int trycount,trylimit=100;
    ShowMessage2line(gTransTitle,"網路連線中","請稍候",Type_ComformNONE);
    for(trycount=0;trycount<trylimit;trycount++)
    {
               if((gCOMMSTATUS!=COMM_STATUS_Connecting)||(gCOMMSTATUS!=COMM_STATUS_StartConnect))
               {
                    if(gCOMMSTATUS==COMM_STATUS_ConnecteOK){
                        ShowMessage2line(gTransTitle,"網路連線完成","",Type_ComformNONE);
                        return d_OK;
                    }else{
                     //   return d_Fail;
                    }
               }  
               CTOS_Delay(100);
    }
    return d_Fail;
}
*/
USHORT WaitSSLSendReceive()
{
    USHORT usRet;
    while(1){
     if(gCOMMSTATUS==COMM_STATUS_ConnecteOK){
            gCOMM_CMD=COMM_CMD_Send;
            while(1){
                 if(gCOMMSTATUS==COMM_STATUS_SendandRecvOK){
                        return d_OK;
                        
                }else  if(gCOMMSTATUS==COMM_STATUS_SendandRecvFail){
                       return d_Fail;
                }
             }
             break;
     }else if(gCOMMSTATUS==COMM_STATUS_Connecting){
            continue;
     }else{
       
          break;
     }
    }   
    return usRet;
}
USHORT SSLSocketConnect()
{
    USHORT  usRet;
    void *threadResult;
    printf("[%s,%d] sslConnect start !\n",__FUNCTION__,__LINE__);
    usRet=  Eth_PutDeviecBackOnBase();
    if(usRet!=d_OK) return usRet;
    int result=0;
    if(pthread_self() != thread_SendAdvice){
       result = pthread_join(thread_SendAdvice, &threadResult);
       if(result != 0){
           printf("[%s,%d] thread_SendAdvice join fail(%d)\n ",__FUNCTION__,__LINE__,result);
           //return d_NO;
       } else printf("[%s,%d] join OK, return msg(%s)\n",__FUNCTION__,__LINE__,(char*)threadResult);
    } else printf("[%s,%d] thread_SendAdvice cannot join itself, so go head\n",__FUNCTION__,__LINE__);
    /*
    if(pthread_self() != thread_AfterTxSuccess){
       result = pthread_join(thread_AfterTxSuccess, &threadResult);
       if(result != 0){
           printf("[%s,%d] thread_SendAdvice join fail(%d)\n ",__FUNCTION__,__LINE__,result);
           //return d_NO;
       } else printf("[%s,%d] join OK, return msg(%s)\n",__FUNCTION__,__LINE__,(char*)threadResult);
    } else printf("[%s,%d] thread_SendAdvice cannot join itself, so go head\n",__FUNCTION__,__LINE__);
    */
    SSLSocketDisConnect();     
    if(Eth_CheckDeviceStatus()!=d_OK)
    {
        gCOMMSTATUS=COMM_STATUS_ConnecteFail;
        return usRet;
    }
  
    gCOMMSTATUS=COMM_STATUS_StartConnect;
    BYTE baMsg[64];
   //ShowStatusLine("網路連線中");
    usRet= Eth_TCPConnect();  
    if (usRet !=d_OK)
    {   
        gCOMMSTATUS=COMM_STATUS_ConnecteFail;
      
        return usRet;
    }
  
    gCOMMSTATUS=COMM_STATUS_Connecting;
            
   //ShowStatusLine("建立SSL連線");
   if (bgNETWORKChannel == CHANNEL_GPRS) {
         usRet = CTOS_SSLNew(d_SSL_CONNECTION_GPRS, bSocket); 
   }else{
         usRet = CTOS_SSLNew(d_SSL_CONNECTION_ETHERNET, bSocket);
   }
   if (usRet !=d_OK)
    {   
       gCOMMSTATUS=COMM_STATUS_ConnecteFail;
       goto DISCONNECT;
    } 

/*
    BYTE ca[2048];
    memset(ca,0x00,sizeof(ca));
    int  Filesize= File_GetLen("ck1.cer");
    if(Filesize==0) return d_ERR_SSLCA_ERROR;   
    usRet=usReadFileData("ck1.cer",&Filesize,ca);
 */ 
 /*   usRet = CTOS_SSLLoadObject(d_SSL_OBJ_X509_CERT, gCA,gCAlen , NULL);
    if (usRet != d_OK){   
          usRet=d_ERR_SSLCA_ERROR;  
          gCOMMSTATUS=COMM_STATUS_ConnecteFail;
          goto DISCONNECT;
    }
  */
   

   // CTOS_SSLSetReadTimeout(2000);       //Set the Read Timeout to 2s
   //ShowStatusLine("SSL 連接中");
 
    usRet = CTOS_SSLConnect();
    if (usRet != d_OK)
    {
        usRet=d_ERR_SSL_CreateFail;
        gCOMMSTATUS=COMM_STATUS_ConnecteFail;
        goto DISCONNECT;
    }
    gCOMMSTATUS=COMM_STATUS_ConnecteOK;
  //  ShowStatusLine("Handshake OK");
    CTOS_LEDSet(d_LED_GREEN,d_ON);

   
    return usRet;
DISCONNECT:

    Ethernet_Disconnect();
    return usRet;
}
USHORT SSLSocketSendandRecv2(BYTE DisplayStatus)
{
    USHORT  usRet, usBufLen, i;
    int     RetryTime=20; 
    USHORT sendbufsize=1024*10;
    USHORT recebufsize=1024*10;  
    BYTE    SendPack[sendbufsize], baBuf[recebufsize];
    SystemLog("SSLSocketSendandRecv2","Start"); 
    CTOS_SSLEnableCancelKey(0);
    //CTOS_Delay(500);
    gCOMMSTATUS =COMM_STATUS_Sending;
    if( Eth_CheckDeviceStatus()!=d_OK)
        return d_OK;
     SystemLog("SSLSocketSendandRecv2","Eth_CheckDeviceStatus=ok"); 
    memset(gReceiveData,0x00,sizeof(gReceiveData));
    int  Filesize= File_GetLen(SendFile);
    if(Filesize==0) return d_ERR_FILE_SIZE_ERR;   
     int RemainSize=Filesize;
    ULONG getlen;
   // SendPack=malloc(Filesize);    
    do{
        if(RemainSize>2048)
            getlen=2048;
        else
            getlen=RemainSize;       
        
         CTOS_LEDSet(d_LED_ORANG,d_ON);
        usRet=usReadFileData(SendFile,&getlen,SendPack);
        if(usRet!=d_OK) return usRet;
         SystemLog("SSLSocketSendandRecv2","usReadFileData=ok"); 
        if(DisplayStatus)
                  ShowStatusLine("資料傳輸中....");
       RemainSize-=getlen;
       usRet = CTOS_SSLWrite(SendPack, getlen);
         SystemLog("SSLSocketSendandRecv2","CTOS_SSLWrite=ok"); 
       if (usRet != d_OK)
        {
            CTOS_LEDSet(d_LED_RED,d_OFF);
            return usRet;
        }
         CTOS_LEDSet(d_LED_ORANG,d_OFF);
    }while(RemainSize!=0);

    CTOS_Delay(100);
    
    remove(RecvFile);
   
    memset(baBuf,0x00,recebufsize);
     usRet=CTOS_SSLSetReadTimeout(500);
    do{
       if(DisplayStatus)
          ShowStatusLine("等待接收中.");
        usBufLen = recebufsize;
         CTOS_LEDSet(d_LED_RED,d_ON);
        usRet = CTOS_SSLRead(baBuf, &usBufLen);
          SystemLog("SSLSocketSendandRecv2","CTOS_SSLRead=ok"); 
         if(usRet==d_OK){
             if(usBufLen>0){
                  strncat(gReceiveData,baBuf,usBufLen);                  
                  int iret= myxml_GetTag(gReceiveData,"TransXML",baBuf);
                  if(iret!=0){
                     // CTOS_Beep();
                        CTOS_LEDSet(d_LED_RED,d_OFF);
                        SystemLog("SSLSocketSendandRecv2","receive=ok"); 
                        gCOMMSTATUS=COMM_STATUS_SendandRecvOK;
                      return d_OK;
                  }
             }else{           
                  if(DisplayStatus){
                     ShowStatusLine("等待接收中..");
                     CTOS_Beep();      
                  } 
             }
         }
  
       RetryTime--;
    } while ( usRet != d_SSL_ERROR_CONN_LOST && RetryTime>0);
     if(DisplayStatus)
        ShowStatusLine("接收逾時。");
   
    return d_ERR_ETH_RECV_TIMEOUT;
 }
USHORT SSLSocketDisConnect()
{
    USHORT ret;
    DWORD dwStatus;
   
   //if(gCOMMSTATUS!=COMM_STATUS_ConnecteOK)
  //      return d_OK;
    ret=CTOS_SSLDisConnect();
   // if(ret !=d_OK) return ret;
    ret=CTOS_SSLClose();
   //   if(ret !=d_OK) return ret;
   ret=Ethernet_Disconnect();
   //   if(ret !=d_OK) return ret;
   gCOMMSTATUS= COMM_STATUS_DISCONNECTED;   
   CTOS_LEDSet(d_LED_GREEN,d_OFF);
   return d_OK;
}
USHORT SSLSocketSendandRecv1(void)
{
    BOOL    blRet;
    BYTE    *SendPack, *baBuf;//,RecvPack[1024*10];
    BYTE    bKey, bTypef;
   // BYTE    baStr[128];
    USHORT  usRet, usBufLen, i;
    int     RetryTime=10; 
    USHORT sendbufsize=1024*3;
    USHORT recebufsize=1024*3;
    PrintMemoarystatus(0);
    SystemLog("Process_TransComm","Start"); 
    SendPack= malloc(sendbufsize);
    baBuf= malloc(recebufsize);
   
 
    // TCP connection
 //  CTOS_EthernetOpen();
  //ShowMessage2line(gTransTitle,"網路傳輸","資料上傳中",Type_ComformNONE);
     ShowStatusLine("資料上傳中");
   
    usRet = Ethernet_Connect();
    if (usRet !=d_OK)
    {   
         return usRet;
    }
    
 
  gCOMMSTATUS= COMM_STATUS_ConnecteOK;
    // SSL new
     // ShowMessage2line(gTransTitle,"網路傳輸", "建立SSL連線",Type_ComformNONE);
   ShowStatusLine("建立SSL連線");
    
    usRet = CTOS_SSLNew(d_SSL_CONNECTION_ETHERNET, bSocket);
    if (usRet != d_OK)
    {
        //"Error: Client context is invalid\n"
        // ShowMessage2line(gTransTitle,"網路傳輸", "SSL連立失敗",Type_ComformAnykey);
        usRet=d_ERR_SSL_CreateFail;
         goto exit_disconnect;
    }
 
    
 int size=0;
    // SSL load object 
 /*int size=0;
    // SSL load object 
  int Filesize;
   usRet= Get_SSLCA();
   if(usRet==d_OK){

       BYTE ca[2048];
       memset(ca,0x00,sizeof(ca));
      Filesize= File_GetLen(gCAFile);
      if(Filesize==0) return d_ERR_FILE_SIZE_ERR;   
       usRet=usReadFileData(gCAFile,&Filesize,ca); */
    // usRet = CTOS_SSLLoadObject(d_SSL_OBJ_X509_CERT, ca,Filesize , NULL); 
       usRet = CTOS_SSLLoadObject(d_SSL_OBJ_X509_CERT, gCA,gCAlen , NULL);
        if (usRet != d_OK){   
            usRet=d_ERR_SSLCA_ERROR;  
            goto exit;
        }
  /*      
   }else{
     usRet=d_ERR_SSLCA_ERROR;
       goto exit;
   }*/


      // SSL Connect
  //  ShowMessage2line(gTransTitle,"網路傳輸", "SSL 連接中",Type_ComformNONE);
    ShowStatusLine("SSL 連接中");
    
    usRet = CTOS_SSLConnect();
    if (usRet != d_OK)
    {
      //  sprintf(baStr, "SSL Conn NG %04X", usRet);
      //  ShowMessage2line(gTransTitle,"網路傳輸",baStr,Type_ComformAnykey);
        usRet=d_ERR_SSL_CreateFail;
        goto exit;
    }

    ShowStatusLine("Handshake OK");
   // ShowMessage2line(zzgTransTitle,"網路傳輸", "Handshake OK",Type_ComformNONE);
 
    int    Filesize= File_GetLen(SendFile);
    if(Filesize==0) return d_ERR_FILE_SIZE_ERR;   
     int RemainSize=Filesize;
    ULONG getlen;
   
   // SendPack=malloc(Filesize);
    do{
        if(RemainSize>2048)
            getlen=2048;
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

 //   CTOS_Delay ( 500 );
  
   usRet=CTOS_SSLSetReadTimeout(200);
  //  CTOS_SSLEnableCancelKey(1);
    // SSL read
    remove(RecvFile);
    do
    {
            ShowStatusLine("等待接收中.");
       // ShowMessage2line(gTransTitle,"網路傳輸","等待接收中.",Type_ComformNONE);
        //Please make sure that you have large enough buffer to receive the data (Depending on the application specification).
        usBufLen = recebufsize;
        usRet = CTOS_SSLRead(baBuf, &usBufLen);
        if((usRet==d_OK)&& (usBufLen > 0)){
                usWriteFile(RecvFile,baBuf,usBufLen);
           
                CTOS_Beep();
                goto exit;
         }else{        //usBufLen = 0
            
                 ShowStatusLine("等待接收中..");
                 CTOS_Beep();
         }
       RetryTime--;
    } while ( usRet != d_SSL_ERROR_CONN_LOST && RetryTime>0);
    usRet=d_ERR_ETH_RECV_TIMEOUT;
    ShowStatusLine("接收逾時。");
exit:
   //ShowMessage2line(gTransTitle,"網路傳輸","SSL 斷線",Type_ComformNONE);
    // ShowStatusLine("SSL CLOSE..");
   
    free(SendPack);    
    free(baBuf);
    usRet=CTOS_SSLDisConnect();
    usRet=CTOS_SSLClose();

exit_disconnect:
  //ShowStatusLine("TCP CLOSE .");
  //ShowMessage2line(gTransTitle,"網路傳輸","TCP 斷線",Type_ComformNONE); 
Ethernet_Disconnect();
#ifndef DEBUGMODE      
    
     
    //return d_OK;//debug 時用 ，用gdb 在disconnect會跳不出來，所以debug 階段先跳過
#endif     
  
   
    // CTOS_KBDGet(&bKey); 
    return usRet;

}
USHORT SSLSocketSendandRecv()
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
   
   
    // TCP connection
  // CTOS_EthernetOpen();
  //ShowMessage2line(gTransTitle,"網路傳輸","資料上傳中",Type_ComformNONE);
     ShowStatusLine("資料上傳中");
   // usRet = Ethernet_Connect();
  /* usRet= Eth_TCPConnect();
   if (usRet !=d_OK)
    {   
         return usRet;
    }*/
    
 

    // SSL new
     // ShowMessage2line(gTransTitle,"網路傳輸", "建立SSL連線",Type_ComformNONE);
   
  ShowStatusLine("建立SSL連線");
   if (bgNETWORKChannel == CHANNEL_GPRS) {
         usRet = CTOS_SSLNew(d_SSL_CONNECTION_GPRS, bSocket); 
   }else{
         usRet = CTOS_SSLNew(d_SSL_CONNECTION_ETHERNET, bSocket);
   }
    
    if (usRet != d_OK)
    {
        //"Error: Client context is invalid\n"
        // ShowMessage2line(gTransTitle,"網路傳輸", "SSL連立失敗",Type_ComformAnykey);
        usRet=d_ERR_SSL_CreateFail;
         goto exit_disconnect;
    }

//    CTOS_SSLSetReadTimeout(2000);       //Set the Read Timeout to 2s
 /*int size=0;
    // SSL load object 
  int Filesize;
   usRet= Get_SSLCA();
   if(usRet==d_OK){

       BYTE ca[2048];
       memset(ca,0x00,sizeof(ca));
      Filesize= File_GetLen(gCAFile);
      if(Filesize==0) return d_ERR_FILE_SIZE_ERR;   
       usRet=usReadFileData(gCAFile,&Filesize,ca); */
    // usRet = CTOS_SSLLoadObject(d_SSL_OBJ_X509_CERT, ca,Filesize , NULL); 
       usRet = CTOS_SSLLoadObject(d_SSL_OBJ_X509_CERT, gCA,gCAlen , NULL);
        if (usRet != d_OK){   
            usRet=d_ERR_SSLCA_ERROR;  
            goto exit;
        }
  /*      
   }else{
     usRet=d_ERR_SSLCA_ERROR;
       goto exit;
   }*/
   
//PrintMemoarystatus(1);

      // SSL Connect
  //  ShowMessage2line(gTransTitle,"網路傳輸", "SSL 連接中",Type_ComformNONE);
   ShowStatusLine("SSL 連接中");
    usRet = CTOS_SSLConnect();
    if (usRet != d_OK)
    {
      //  sprintf(baStr, "SSL Conn NG %04X", usRet);
      //  ShowMessage2line(gTransTitle,"網路傳輸",baStr,Type_ComformAnykey);
        usRet=d_ERR_SSL_CreateFail;
        goto exit;
    }
  
    ShowStatusLine("Handshake OK");
   // ShowMessage2line(zzgTransTitle,"網路傳輸", "Handshake OK",Type_ComformNONE);
 
    
     
    // SSL Vrify certificate
/*   
    usRet = CTOS_SSLVerifyCert();
    if( usRet!=d_OK)
    {
        usRet=d_ERR_SSL_CreateFail;
        goto exit;
    }
  */  
    
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
  usRet=  CTOS_SSLSetReadTimeout(20000);
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
  
  //  CTOS_SSLDisConnect();
  //  CTOS_SSLClose();

exit_disconnect:
  //ShowStatusLine("TCP CLOSE .");
  //ShowMessage2line(gTransTitle,"網路傳輸","TCP 斷線",Type_ComformNONE); 
 //       Ethernet_Disconnect();
#ifndef DEBUGMODE      
    
     
    //return d_OK;//debug 時用 ，用gdb 在disconnect會跳不出來，所以debug 階段先跳過
#endif     
//  PrintMemoarystatus(2);
   
    // CTOS_KBDGet(&bKey); 
    return usRet;

}

USHORT TestHostConnect()
{
   USHORT ret= Ethernet_Connect();
   if(ret!=d_OK)
   {
 
      return ret;
   }
   ret= Ethernet_Disconnect();
   return ret;
}