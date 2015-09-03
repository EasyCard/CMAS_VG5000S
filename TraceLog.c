#include "ECCAPP.h"
void Debug_SendData(char * title,char * Data,int len)
{
    USHORT ret= usWriteFile(title,Data,len) ;   
    SendDebugFile(title);
    remove(title);
}
void SendDebugFile(STR *LOCALFILE){
	
	BYTE filename[64];
        CTOS_RTC SetRTC;  
        char USBDISK[]="/media/udisk/";
        char dest[256];
	memset(filename,0x00,sizeof(filename));
	USHORT ret = CTOS_RTCGet(&SetRTC);
	if(ret!=0)         return ;
	sprintf(filename,"/log/%s%02d%02d%02d.xml",LOCALFILE,SetRTC.bHour,SetRTC.bMinute,SetRTC.bSecond);
        gDebugFTPFlag=atoi(gConfig.sDEBUG.FTP.ENABLE); 
	
        if(gDebugFTPFlag){
		       FTPsUPLOAD(gConfig.sDEBUG.FTP.bID,gConfig.sDEBUG.FTP.PASSWORD,gConfig.sDEBUG.FTP.IP,LOCALFILE,filename);
        }  
      
}
void SaveDebugData(TRANS_DATA2* TransData)
{

      if(gDebugFTPFlag){
            TransData->ucTXTYPE=TXTYPE_DEBUG;
            SaveTransData(TransData);
        }

}

void myDebugFile(char* function,int line, const char* fmt, ...) {
    char szLog[1024];
    //char szEvent[512];
    va_list marker;

    memset(szLog, 0x00, sizeof (szLog));    
    va_start(marker, fmt);
    vsprintf(szLog, fmt, marker);
    va_end(marker);

    //sprintf(szEvent,"[%s,%d]",function, line);

    //SystemLog(szEvent, szLog);
    STR path[32];
    STR filename[46];
    STR logstr[2048];
    STR time[32];
    USHORT ret;
    int iret;
    CTOS_RTC GetRTC;   
    FILE * f;
 
    ret = CTOS_RTCGet(&GetRTC);
    if(ret!=0){
        return ;
    }    
    memset(path,0x00,sizeof(path));
    sprintf(path,"/media/mdisk/%04d/%02d/%02d/Log",GetRTC.bYear+2000,GetRTC.bMonth,GetRTC.bDay);
    iret=CreateDir(path);  
    if(iret!=0){
        ret=d_ERR_createdir;       
    }
    
    memset(filename,0x00,sizeof(filename));
    sprintf(filename,"%s/debugLog.xml",path);
    sprintf(time,"%02d:%02d:%02d",GetRTC.bHour,GetRTC.bMinute,GetRTC.bSecond);
    
    snprintf(logstr,1024,"[%s %s,%d] %s",time,function,line, szLog);//V15, modified by kobe, sprintf -> snprintf
  
  
    f = fopen(filename, "at+");  
    if (f == NULL)          
        return;
   
    fprintf(f,"%s\n",logstr);   
    fflush(f);   
    fsync(fileno(f));   
    fclose(f);   
    return;
}


USHORT SystemLog(STR * EVENT,STR * DATA)
{
    
    STR path[32];
    STR filename[46];
    
    STR time[32];
    USHORT ret;
    int iret;
    CTOS_RTC GetRTC;
   
    FILE * f;
 
    ret = CTOS_RTCGet(&GetRTC);
    if(ret!=0){
        return d_ERR_GETRTC;
    }    
    memset(path,0x00,sizeof(path));
    sprintf(path,"/media/mdisk/%04d/%02d/%02d/Log",GetRTC.bYear+2000,GetRTC.bMonth,GetRTC.bDay);
    iret=CreateDir(path);  
    if(iret!=0)
         ret=d_ERR_createdir;       
    
    
    memset(filename,0x00,sizeof(filename));
    sprintf(filename,"%s/log%02d.xml",path,GetRTC.bHour);
    sprintf(time,"%02d:%02d:%02d",GetRTC.bHour,GetRTC.bMinute,GetRTC.bSecond);
    STR logstr[2048];
    snprintf(logstr,sizeof(logstr),"%s %s=%s",time,EVENT,DATA);//V15, modified by kobe, sprintf -> snprintf
  
  f = fopen(filename, "at+");
  if (f == NULL) 
          return -1;
   fprintf(f,"%s\n",logstr);
   fflush(f);
   fsync(fileno(f));
   fclose(f);
   return ret;
}

USHORT SystemLogInt(STR * EVENT,int  digi,STR * str)
{
   
    USHORT ret;
    
    STR strbuf[1024];
    sprintf(strbuf,"%d:%s",digi,str);
    ret=SystemLog(EVENT,strbuf);
    return 0;
}
USHORT SystemLogHex(STR * EVENT,unsigned char* DATA,int len)
{
 //   return 0;
    USHORT ret;
    STR strbuf[1000]; 
    
 
    memset(strbuf,0x00,sizeof(strbuf));
    wub_hex_2_str(DATA, strbuf, len);
    SystemLogInt(EVENT,len,strbuf);
    
    return 0;
}


