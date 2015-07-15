
#include <curl/curl.h>
#include <ctosapi.h>
# include "ECCAPP.h"
struct FtpFile {
  const char *filename;
  FILE *stream;
};
USHORT ECC_FTPGetFileforDebug(STR * Localfilename, STR * Remofilename)
{
     STR IP[36],PORT[6+1],URL[36+1],URLPORT[6+1],sID[32],pw[32],URLIP[36];
    BYTE urliplen;
    memset(IP,0x00,sizeof(IP));
    memset(URLIP,0x00,sizeof(URLIP));
    memset(PORT,0x00,sizeof(PORT));
    memset(sID,0x00,sizeof(sID));
    memset(pw,0x00,sizeof(pw));
    BYTE isSSL=0;
    int flag;
   
     
 
      flag=atoi(gConfig.sDEBUG.FTP.ENABLE);   
      if(flag==0) return 0;
           
     sprintf(IP,"%s",gConfig.sDEBUG.FTP.IP);   
     sprintf(sID,"%s",gConfig.sDEBUG.FTP.bID);   
     sprintf(pw,"%s",gConfig.sDEBUG.FTP.PASSWORD);   
   

   USHORT   usRet=ECC_FTPGetFile(IP,sID,pw,Localfilename, Remofilename,0);
     if(usRet!=d_OK){
                usRet=ECC_FTPGetFile(IP,sID,pw,Localfilename, Remofilename,0);
     }        
     return usRet;
}
USHORT ECC_FTPGetFile2(STR * Localfilename, STR * Remofilename)
{
   
 //   BYTE urliplen;
  //  
  //   STR IP[36],PORT[6+1],URL[36+1],URLPORT[6+1],ID[32],pw[32],URLIP[36];
  /*  memset(IP,0x00,sizeof(IP));
    memset(URLIP,0x00,sizeof(URLIP));
    memset(PORT,0x00,sizeof(PORT));
    memset(ID,0x00,sizeof(ID));
    memset(pw,0x00,sizeof(pw));
    BYTE isSSL=0;
 
  
     
   
    // sprintf(URL,"%s",gConfig.ETHERNET.COMM.FTP.URL);   
     sprintf(URL,"%s",g);  
    
     sprintf(IP,"%s",gConfig.ETHERNET.COMM.FTP.IP);   
 //     sprintf(IP,"211.78.134.167");   
  
     sprintf(ID,"%s",gConfig.ETHERNET.COMM.FTP.LOGINID);   
    
     sprintf(pw,"%s",gConfig.ETHERNET.COMM.FTP.LOGINPASSWORD);   
    _EXTERN STR gFTPIP[36];
_EXTERN STR gFTPPORT[6+1];
_EXTERN STR gFTPID[32];
_EXTERN STR gFTPPW[32];
  */  
    BYTE isSSL=0;
     GetFTPINFO();  
  //  USHORT usRet=ECC_FTPGetFile(gFTPIP,gFTPID,gFTPPW,Localfilename, Remofilename,isSSL);
   
    USHORT usRet=ECC_FTPGetFileShowStatus(gFTPIP,gFTPID,gFTPPW,Localfilename, Remofilename,isSSL);
     if(usRet!=d_OK){
          usRet=ECC_FTPGetFileShowStatus(gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL,gFTPID,gFTPPW,Localfilename, Remofilename,isSSL);
     
     }        
     return usRet;
}
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb,
                        void *stream)
{
  struct FtpFile *out=(struct FtpFile *)stream;
  if(out && !out->stream) {
    /* open file for writing */
    out->stream=fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure, can't open file to write */
  }
  return fwrite(buffer, size, nmemb, out->stream);
}


//int ftpsget(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL)
USHORT ECC_FTPGetFile(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL)
{
  CURL *curl;
  CURLcode res;
  struct FtpFile ftpfile={
    "tmpfile", /* name to store the file as if succesful */
    NULL
  };

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    /*
     * You better replace the URL with one that works! Note that we use an
     * FTP:// URL with standard explicit FTPS. You can also do FTPS:// URLs if
     * you want to do the rarer kind of transfers: implicit.
     */
      BYTE URL[128];
      BYTE IDPW[64];
      BYTE errstr[64];
      memset(URL,0x00,sizeof(URL));
      sprintf(URL,"FTPS://%s%s",ip,Remofilename);
      memset(IDPW,0x00,sizeof(IDPW));
      sprintf(IDPW,"%s:%s",id,pw);
     curl_easy_setopt(curl, CURLOPT_URL,URL);
     curl_easy_setopt(curl, CURLOPT_USERPWD,IDPW);
    // curl_easy_setopt(curl, d,1);
  
 // curl_easy_setopt(curl, CURLOPT_MAX_SEND_SPEED_LARGE, 1024*1024*2);
   //curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, 1024*1024*2);
  // curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 1024*50);
    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

    /* cert is stored PEM coded in file... */
      /* since PEM is default, we needn't set it for PEM */
  //    curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
  //    curl_easy_setopt(curl,CURLOPT_SSLCERT,"CMAS-FTP.pem");
  /* if we use a key stored in a crypto engine,
         we must set the key type to "ENG" */
  //    curl_easy_setopt(curl,CURLOPT_SSLKEYTYPE,"PEM");

      /* set the private key (file or ID in engine) */
 //     curl_easy_setopt(curl,CURLOPT_SSLKEY,"CMAS-FTP.pem");

      /* set the cert for client authentication */
  //     curl_easy_setopt(curl,CURLOPT_CAINFO,"CMAS-FTP.pem"); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
   //  curl_easy_setopt(curl,CURLOPT_SSLCERT,"CMAS-FTP.pem");
   /* We activate SSL and we require it for both control and data */
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
  
    
    //   curl_easy_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, 1);
    //   curl_easy_setopt(curl, CURLOPT_CONV_FROM_UTF8_FUNCTION, 1);
  
    // curl_easy_setopt(curl, CURLOPT_FTPSSLAUTH,"AUTH TLS");
  
   //  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
   
    /* Switch on full protocol/debug output */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);
   
    if(CURLE_OK != res) {
      /* we failed */
      sprintf(errstr, "curl told us %d\n",(int ) res);
      SystemLog("ECC_FTPGetFile",errstr);
      return d_Fail;
    }
  }

  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */
 //  rename(ftpfile.filename,Localfilename);
 
    ULONG lsize=File_GetLen((char *)ftpfile.filename);
    if(lsize<=0) return d_Fail; 
    remove(Localfilename); 
   int iret= copyFiles((char *)ftpfile.filename, Localfilename);
   remove(ftpfile.filename); 
  curl_global_cleanup();

  return d_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* parse headers for Content-Length */

/* discard downloaded data */
size_t discardfunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
  return size * nmemb;
}

/* read data to upload */
size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
  FILE *f = stream;
  size_t n;

  if (ferror(f))
    return CURL_READFUNC_ABORT;

  n = fread(ptr, size, nmemb, f) * size;

  return n;
}
int upload(CURL *curlhandle, const char * remotepath, const char * localpath,
           long timeout, long tries)
{
  FILE *f;
  long uploaded_len = 0;
  CURLcode r = CURLE_GOT_NOTHING;
  int c;

  f = fopen(localpath, "rb");
  if (f == NULL) {
    perror(NULL);
    return 0;
  }

  curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);

  curl_easy_setopt(curlhandle, CURLOPT_URL, remotepath);

  if (timeout)
    curl_easy_setopt(curlhandle, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);

 // curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION, getcontentlengthfunc);
  curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &uploaded_len);

  curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, discardfunc);

  curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
  curl_easy_setopt(curlhandle, CURLOPT_READDATA, f);

  curl_easy_setopt(curlhandle, CURLOPT_FTPPORT, "-"); /* disable passive mode */
  curl_easy_setopt(curlhandle, CURLOPT_FTP_CREATE_MISSING_DIRS, 1L);
  // curl_easy_setopt(curlhandle, CURLOPT_USE_SSL, CURLUSESSL_ALL);
  curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L);

  for (c = 0; (r != CURLE_OK) && (c < tries); c++) {
    /* are we resuming? */
    if (c) { /* yes */
      /* determine the length of the file already written */

      /*
       * With NOBODY and NOHEADER, libcurl will issue a SIZE
       * command, but the only way to retrieve the result is
       * to parse the returned Content-Length header. Thus,
       * getcontentlengthfunc(). We need discardfunc() above
       * because HEADER will dump the headers to stdout
       * without it.
       */
      curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 1L);
      curl_easy_setopt(curlhandle, CURLOPT_HEADER, 1L);

      r = curl_easy_perform(curlhandle);
      if (r != CURLE_OK)
        continue;

      curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 0L);
      curl_easy_setopt(curlhandle, CURLOPT_HEADER, 0L);

      fseek(f, uploaded_len, SEEK_SET);

      curl_easy_setopt(curlhandle, CURLOPT_APPEND, 1L);
    }
    else { /* no */
      curl_easy_setopt(curlhandle, CURLOPT_APPEND, 0L);
    }

    r = curl_easy_perform(curlhandle);
  }

  fclose(f);

  if (r == CURLE_OK)
    return 1;
  else {
    fprintf(stderr, "%s\n", curl_easy_strerror(r));
    return 0;
  }
}
int FTPsUPLOAD(BYTE * id,BYTE *pw,BYTE *ip,BYTE * file ,BYTE *RemoName)
{
   CURL *curlhandle = NULL;
   BYTE str[128];
  curl_global_init(CURL_GLOBAL_ALL);
  curlhandle = curl_easy_init();
  sprintf(str,"ftp://%s:%s@%s/%s",id,pw,ip,RemoName);
  upload(curlhandle,str, file, 0, 3);

  curl_easy_cleanup(curlhandle);
  curl_global_cleanup();



}



/*
 * This is an example showing how to check a single file's size and mtime
 * from an FTP server.
 */

static size_t throw_away(void *ptr, size_t size, size_t nmemb, void *data)
{
  (void)ptr;
  (void)data;
  /* we are not interested in the headers itself,
     so we only return the size we would have saved ... */
  return (size_t)(size * nmemb);
}
//int ftpsget(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL)

USHORT ECC_FTPGetFileTest(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL)
{
  CURL *curl;
  CURLcode res;
  BYTE statusline1[64];
  BYTE statusline2[64];
  long filetime = -1;
  double filesize = 0.0;
  struct FtpFile ftpfile={
    "tmpfile", /* name to store the file as if succesful */
    NULL
  };

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    /*
     * You better replace the URL with one that works! Note that we use an
     * FTP:// URL with standard explicit FTPS. You can also do FTPS:// URLs if
     * you want to do the rarer kind of transfers: implicit.
     */
      BYTE URL[128];
      BYTE IDPW[64];
      BYTE errstr[64];
    
      memset(URL,0x00,sizeof(URL));
      sprintf(URL,"FTPS://%s%s",ip,Remofilename);
     const char *filename = strrchr(URL, '/') + 1;
      memset(IDPW,0x00,sizeof(IDPW));
      sprintf(IDPW,"%s:%s",id,pw);
     curl_easy_setopt(curl, CURLOPT_URL,URL);
     curl_easy_setopt(curl, CURLOPT_USERPWD,IDPW);
   
   curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, 1024*1024*2);
   curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 1024*50);
  
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
   
    /* No download if the file */
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    /* Ask for filetime */
    curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
    
     /* No header output: TODO 14.1 http-style HEAD output for ftp */
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, throw_away);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
    /* Switch on full protocol/debug output */
    /* curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); */
    /* cert is stored PEM coded in file... */
      /* since PEM is default, we needn't set it for PEM */
  //    curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
  //    curl_easy_setopt(curl,CURLOPT_SSLCERT,"CMAS-FTP.pem");
  /* if we use a key stored in a crypto engine,
         we must set the key type to "ENG" */
  //    curl_easy_setopt(curl,CURLOPT_SSLKEYTYPE,"PEM");

      /* set the private key (file or ID in engine) */
 //     curl_easy_setopt(curl,CURLOPT_SSLKEY,"CMAS-FTP.pem");

      /* set the cert for client authentication */
  //     curl_easy_setopt(curl,CURLOPT_CAINFO,"CMAS-FTP.pem"); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
   //  curl_easy_setopt(curl,CURLOPT_SSLCERT,"CMAS-FTP.pem");
   /* We activate SSL and we require it for both control and data */
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
  
    
   
   // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);
   
    if(CURLE_OK == res) {
      /* http://curl.haxx.se/libcurl/c/curl_easy_getinfo.html */
      res = curl_easy_getinfo(curl, CURLINFO_FILETIME, &filetime);
      if((CURLE_OK == res) && (filetime >= 0)) {
        time_t file_time = (time_t)filetime;
        sprintf(statusline1,"filetime %s: %s", filename, ctime(&file_time));
      }
      res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &filesize);
      if((CURLE_OK == res) && (filesize>0.0))
       sprintf(statusline2,"filesize %s: %0.0f bytes\n", filename, filesize);
    } else {
      /* we failed */
      fprintf(stderr, "curl told us %d\n", res);
    }
  }

  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */
 //  rename(ftpfile.filename,Localfilename);
 
    ULONG lsize=File_GetLen((char *)ftpfile.filename);
    if(lsize<=0) return d_Fail; 
    remove(Localfilename); 
   int iret= copyFiles((char *)ftpfile.filename, Localfilename);
   remove(ftpfile.filename); 
  curl_global_cleanup();

  return d_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
struct callback_data {
  FILE *output;
};

static long file_is_comming(struct curl_fileinfo *finfo,
                            struct callback_data *data,
                            int remains);

static long file_is_downloaded(struct callback_data *data);

static size_t write_it(char *buff, size_t size, size_t nmemb,
                       void *cb_data);
struct my_progress_data_struct
{
    /* Some data fields */
};
static int my_progress_func(
                     void * pd  ,
                     double t, /* dltotal */
                     double d, /* dlnow */
                     double ultotal,
                     double ulnow)
{
    int step=0;
    int progress=0;
    BYTE str[32];
    memset(str,0x00,sizeof(str));
   
    if(d>0){
        progress=d*100/t;
       // sprintf (str,"%.0f/%.0f Bytes %.0f%%",d,t, d*100/t); 
        if(progress%10==0)
        {  
            step=progress/10;   
            CTOS_LCDGSetBox(0,40+40+40+16+10,(320/10)*step,Med_Font_Ysize,TRUE); //Draw a rectangle //
        }
      // sprintf (str,"%.0f%%",d*100/t); 

    }else{
      //  sprintf (str,"準備中"); 
      //  ShowLine(32*4,40+40+40+16+10,Med_Font_Size,str,FALSE);
    }
  
  return 0;
}

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
 
USHORT ECC_FTPGetFileShowStatus_S(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL)
{
  CURL *curl;
  CURLcode res;
  double filesize = 0.0;
  double totaltime = 0.0;
  BYTE statusline2[64];
  struct FtpFile ftpfile={
    "tmpfile", /* name to store the file as if succesful */
    NULL
  };
   CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
   CTOS_LCDGClearCanvas();
   ShowTitle(gTransTitle);
   ShowLine(0,40+16,Big_Font_Size,"資料下載中.",FALSE);
  
   ShowLine(0,40+40+16+10,Med_Font_Size,"下載進度",FALSE);
   curl_global_init(CURL_GLOBAL_DEFAULT);
   BYTE processstr[32];
  
   USHORT  ret= Eth_Connect(bgNETWORKChannel,ip,990);
    curl_socket_t sockfd=Socketfd;
   curl = curl_easy_init();
   if(curl) {
      BYTE URL[128];
      BYTE IDPW[64];
      BYTE DNS[64];
      BYTE *errstr;
      memset(URL,0x00,sizeof(URL));
      sprintf(URL,"FTPS://%s%s",ip,Remofilename);
      memset(IDPW,0x00,sizeof(IDPW));
      sprintf(IDPW,"%s:%s",id,pw);
     curl_easy_setopt(curl, CURLOPT_URL,URL);
     curl_easy_setopt(curl, CURLOPT_USERPWD,IDPW);
  
   
    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
    BYTE len=sizeof(DNS);
    USHORT ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DNSIP, DNS,&len);
   
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); 
   /* call this function to get a socket */ 
    curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, opensocket);
    curl_easy_setopt(curl, CURLOPT_OPENSOCKETDATA, &sockfd);
    /* call this function to set options for the socket */ 
    curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION, sockopt_callback);
    curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 2024L); 
    curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 10); 
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3); 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 600); 
 
    curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, 0L); 
    curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, DNS); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, my_progress_func);
   
    /* Switch on full protocol/debug output */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);
  
    if(CURLE_OK != res) {
      /* we failed */      
       errstr=(char*)curl_easy_strerror(res);
        ErrorMessageBox(gTransTitle,"錯誤訊息",errstr,"","",d_MB_CHECK);
        SystemLog("ECC_FTPGetFile",errstr);
      return d_Fail;
    }   
    res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &filesize);
    if((CURLE_OK == res) && (filesize>0.0))
    {
     sprintf(statusline2,"filesize : %0.0f bytes\n", filesize);
     ShowLine(0,40+40+40+16+10,Med_Font_Size,statusline2,FALSE);
    }
    
     res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &totaltime);
    if((CURLE_OK == res) && (totaltime>0.0))
    {
     sprintf(statusline2,"totaltime : %0.0f sec\n", totaltime);
     ShowLine(0,40+40+40+40+16+10,Med_Font_Size,statusline2,FALSE);
    }
  }
 
  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */
 //  rename(ftpfile.filename,Localfilename);
 
    ULONG lsize=File_GetLen((char *)ftpfile.filename);
    if(lsize<=0) return d_Fail; 
    remove(Localfilename); 
   int iret= copyFiles((char *)ftpfile.filename, Localfilename);
   remove(ftpfile.filename); 
     /* always cleanup */
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  CTOS_Delay(2000);
  return d_OK;
}


USHORT ECC_FTPGetFileShowStatus(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL)
{
  CURL *curl;
  CURLcode res;
  double filesize = 0.0;
  double totaltime = 0.0;
  BYTE statusline2[64];
  struct FtpFile ftpfile={
    "tmpfile", /* name to store the file as if succesful */
    NULL
  };
   CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
   CTOS_LCDGClearCanvas();
   ShowTitle(gTransTitle);
   ShowLine(0,40+16,Big_Font_Size,"資料下載中.",FALSE);
  
   ShowLine(0,40+40+16+10,Med_Font_Size,"下載進度",FALSE);
   curl_global_init(CURL_GLOBAL_DEFAULT);
   BYTE processstr[32];
   curl = curl_easy_init();
   if(curl) {
      BYTE URL[128];
      BYTE IDPW[64];
      BYTE DNS[64];
      BYTE *errstr;
      memset(URL,0x00,sizeof(URL));
      sprintf(URL,"FTPS://%s%s",ip,Remofilename);
      memset(IDPW,0x00,sizeof(IDPW));
      sprintf(IDPW,"%s:%s",id,pw);
     curl_easy_setopt(curl, CURLOPT_URL,URL);
     curl_easy_setopt(curl, CURLOPT_USERPWD,IDPW);
  
   
    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
    BYTE len=sizeof(DNS);
    USHORT ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DNSIP, DNS,&len);
   
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); 
  
      curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 1024L*1000); 
   

    curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 60); 
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 60); 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60*10); 
    curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, DNS); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, my_progress_func);
   
    /* Switch on full protocol/debug output */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);
  
    if(CURLE_OK != res) {
      /* we failed */      
       errstr=(char*)curl_easy_strerror(res);
        ErrorMessageBox(gTransTitle,"錯誤訊息",errstr,"","",d_MB_CHECK);
        SystemLog("ECC_FTPGetFile",errstr);
      return d_Fail;
    }   
    res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &filesize);
    if((CURLE_OK == res) && (filesize>0.0))
    {
     sprintf(statusline2,"filesize : %0.0f bytes\n", filesize);
     ShowLine(0,40+40+40+16+10,Med_Font_Size,statusline2,FALSE);
    }
    
     res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &totaltime);
    if((CURLE_OK == res) && (totaltime>0.0))
    {
     sprintf(statusline2,"totaltime : %0.0f sec\n", totaltime);
     ShowLine(0,40+40+40+40+16+10,Med_Font_Size,statusline2,FALSE);
    }
  }
 
  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */
 //  rename(ftpfile.filename,Localfilename);
 
    ULONG lsize=File_GetLen((char *)ftpfile.filename);
    if(lsize<=0) return d_Fail; 
    remove(Localfilename); 
   int iret= copyFiles((char *)ftpfile.filename, Localfilename);
   remove(ftpfile.filename); 
     /* always cleanup */
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  CTOS_Delay(2000);
  return d_OK;
}
USHORT ECC_FTPGetFileShowStatusForTest(STR *title,STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL)
{
  CURL *curl;
  CURLcode res;
  double totaltime,filesize;
  BYTE statusline2[64];
  struct FtpFile ftpfile={
    "tmpfile", /* name to store the file as if succesful */
    NULL
  };
   CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
   CTOS_LCDGClearCanvas();
   ShowTitle(title);
   ShowLine(0,40+16,Big_Font_Size,"資料下載中.",FALSE);
  
   ShowLine(0,40+40+16+10,Med_Font_Size,"下載進度",FALSE);
   curl_global_init(CURL_GLOBAL_DEFAULT);
   BYTE processstr[32];
   curl = curl_easy_init();
   if(curl) {
      BYTE URL[128];
      BYTE IDPW[64];
      BYTE DNS[64];
      BYTE *errstr;
      memset(URL,0x00,sizeof(URL));
      sprintf(URL,"FTPS://%s%s",ip,Remofilename);
 
      memset(IDPW,0x00,sizeof(IDPW));
      sprintf(IDPW,"%s:%s",id,pw);
     curl_easy_setopt(curl, CURLOPT_URL,URL);
     curl_easy_setopt(curl, CURLOPT_USERPWD,IDPW);
  
   
    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
    BYTE len=sizeof(DNS);
    USHORT ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DNSIP, DNS,&len);
   
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); 
   curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 1024L*1000); 
    curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 600); 
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 600); 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 600); 
    curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, DNS); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, my_progress_func);
   
    /* Switch on full protocol/debug output */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);
  
    if(CURLE_OK != res) {
      /* we failed */      
       errstr=(BYTE*)curl_easy_strerror(res);
        ErrorMessageBox(gTransTitle,"錯誤訊息",errstr,"","",d_MB_CHECK);
        CTOS_PrinterPutString (errstr);
        SystemLog("ECC_FTPGetFile",errstr);
        return res;
    }   
    res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &filesize);
    if((CURLE_OK == res) && (filesize>0.0))
    {
     sprintf(statusline2,"filesize : %0.0f bytes", filesize);
     ShowLine(0,40+40+40+16+10,Med_Font_Size,statusline2,FALSE);
       CTOS_PrinterPutString (statusline2);
    }
    
    res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &totaltime);
    if((CURLE_OK == res) && (totaltime>0.0))
    {
     sprintf(statusline2,"totaltime : %0.0f sec", totaltime);
     ShowLine(0,40+40+40+40+16+10,Med_Font_Size,statusline2,FALSE);
     CTOS_PrinterPutString (statusline2);
    }
  }

  //curl_easy_cleanup(curl);
  curl_global_cleanup();
  CTOS_Delay(2000);
  return d_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define FROM    "<sender@example.org>"
#define TO      "<bruce912@gmail.com>"
#define CC      ""

static const char *payload_text[]={
  "Date: Mon, 29 Nov 2010 21:54:29 +1100\n",
  "To: " TO "\n",
  "From: " FROM "(Example User)\n",
  "Cc: " CC "(Another example User)\n",
  "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\n",
  "Subject: SMTP TLS example message\n",
  "\n", /* empty line to divide headers from body, see RFC5322 */
  "The body of the message starts here.\n",
  "\n",
  "It could be a lot of lines, could be MIME encoded, whatever.\n",
  "Check RFC5322.\n",
  NULL
};

struct upload_status {
  int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;

  if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }

  data = payload_text[upload_ctx->lines_read];

  if (data) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read ++;
    return len;
  }
  return 0;
}


int SendMailtest(void)
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *recipients = NULL;
  struct upload_status upload_ctx;

  upload_ctx.lines_read = 0;

  curl = curl_easy_init();
  if (curl) {
    /* This is the URL for your mailserver. Note the use of port 587 here,
     * instead of the normal SMTP port (25). Port 587 is commonly used for
     * secure mail submission (see RFC4403), but you should use whatever
     * matches your server configuration. */
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");

    /* In this example, we'll start with a plain text connection, and upgrade
     * to Transport Layer Security (TLS) using the STARTTLS command. Be careful
     * of using CURLUSESSL_TRY here, because if TLS upgrade fails, the transfer
     * will continue anyway - see the security discussion in the libcurl
     * tutorial for more details. */
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_TRY);

    /* If your server doesn't have a valid certificate, then you can disable
     * part of the Transport Layer Security protection by setting the
     * CURLOPT_SSL_VERIFYPEER and CURLOPT_SSL_VERIFYHOST options to 0 (false).
     *   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
     *   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
     * That is, in general, a bad idea. It is still better than sending your
     * authentication details in plain text though.
     * Instead, you should get the issuer certificate (or the host certificate
     * if the certificate is self-signed) and add it to the set of certificates
     * that are known to libcurl using CURLOPT_CAINFO and/or CURLOPT_CAPATH. See
     * docs/SSLCERTS for more information.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  //  curl_easy_setopt(curl, CURLOPT_CAINFO, "/path/to/certificate.pem");

    /* A common reason for requiring transport security is to protect
     * authentication details (user names and passwords) from being "snooped"
     * on the network. Here is how the user name and password are provided: */
    curl_easy_setopt(curl, CURLOPT_USERNAME, "bruce912@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "linhungyi");

    /* value for envelope reverse-path */
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);
    /* Add two recipients, in this particular case they correspond to the
     * To: and Cc: addressees in the header, but they could be any kind of
     * recipient. */
    recipients = curl_slist_append(recipients, TO);
    recipients = curl_slist_append(recipients, CC);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    /* In this case, we're using a callback function to specify the data. You
     * could just use the CURLOPT_READDATA option to specify a FILE pointer to
     * read from.
     */
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);

    /* Since the traffic will be encrypted, it is very useful to turn on debug
     * information within libcurl to see what is happening during the transfer.
     */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    /* send the message (including headers) */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* free the list of recipients and clean up */
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
  }
  return 0;
}