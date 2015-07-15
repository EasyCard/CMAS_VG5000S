
#include "ECCAPP.h"

 STR  gHostIP[15+1];
 int gHostPort;
/// STR  gCAFile1[10+1+3+1];
 //STR  gCAFile2[10+1+3+1];

   STR  msgstr[64];
void ShowMemoarystatus()
{
        ULONG ulUsedDiskSize ,ulTotalDiskSize, ulUsedRamSize, ulTotalRamSize; 
           CTOS_SystemMemoryStatus(&ulUsedDiskSize,&ulTotalDiskSize,&ulUsedRamSize,&ulTotalRamSize);
           sprintf( gConfig.DEVICE.MEMORY.USEDDISKSIZE,"%ld",ulUsedDiskSize);
           sprintf( gConfig.DEVICE.MEMORY.TOTALDISKSIZE,"%ld",ulTotalDiskSize);
           sprintf( gConfig.DEVICE.MEMORY.USEDRAMSIZE,"%ld",ulUsedRamSize);
           sprintf( gConfig.DEVICE.MEMORY.TOTALRAMSIZE,"%ld",ulTotalRamSize);
           ShowMessage4line("記憶体資訊",
                   gConfig.DEVICE.MEMORY.USEDDISKSIZE,
                   gConfig.DEVICE.MEMORY.TOTALDISKSIZE,
                   gConfig.DEVICE.MEMORY.USEDRAMSIZE,
                    gConfig.DEVICE.MEMORY.TOTALRAMSIZE,Type_ComformAnykey); 
           return ;
}
USHORT PINGTEST()
{
  BYTE str1[64],str2[64];
  USHORT usRet=GetHOSTINFO();
  if(usRet !=d_OK)
  {
     ECC_CheckAPResponseCode(usRet);
     return 0;
  }
  USHORT  usURLRet= CTOS_EthernetPing ( gHOSTURL, strlen(gHOSTURL));
  
  USHORT usIPRet= CTOS_EthernetPing ( gHOSTIP, strlen(gHOSTIP));
  
   if(usURLRet!=d_OK)
       sprintf(str1,"主機網路不通");
   else
       sprintf(str1,"主機網路連線正常");
       
   if(usIPRet!=d_OK)
       sprintf(str2,"備援主機無回應");
   else
       sprintf(str2,"備援主機連線正常");
   
    usRet=ShowMessage4line("測試網路",str1,str2,"","測試其它ip請按確認",Type_ComformOK);
    if(usRet!=d_OK) return 0;
    BYTE  buff[15+1];
    memset(buff,0x00,sizeof(buff));
    int iret;
    while(1){
     iret= ShowInputBox("測試網路","IP:", buff,15,INPUT_TYPE_NumberWithRadixPoint,0);
    if(iret==d_OK){
                usRet= CTOS_EthernetPing ( buff, strlen(buff));
               if(usRet!=d_OK)
                   sprintf(str1,"此IP無回應!!");
               else
                   sprintf(str1,"網路連線正常!!");  
              
               usRet=ShowMessage4line("測試網路",buff,str1,"","測試其它ip請按確認",Type_ComformOK);     
                  if(usRet!=d_OK) return ;      
           }else{
                 return 0;
           }
    }
 }

 USHORT ShowTerminalInfo()
 {
    BYTE str1[64],str2[64],str3[64],str4[64];
     
  //   ezxml_t  ConfigDATA = ezxml_parse_file(ConfigXML);
  //  if(ConfigDATA ==NULL){       return d_Fail;    }
    memset(str1,0x00,sizeof(str1));
    memset(str2,0x00,sizeof(str2));
    memset(str3,0x00,sizeof(str3));
    memset(str4,0x00,sizeof(str4));
       
  //  ezxml_t ezxml_DATA = ezxml_get(ConfigDATA, "MERCHANT",0,"MERCHANTID",-1);
    sprintf(str1,"特店代號:%s",gConfig.MERCHANT.MERCHANTID);
  
  //  ezxml_DATA = ezxml_get(ConfigDATA, "MERCHANT",0,"NewLocationID",-1);
    sprintf(str2,"分公司代號:%s",gConfig.MERCHANT.NewLocationID);    
   // ezxml_DATA = ezxml_get(ConfigDATA, "MERCHANT",0,"STCODE",-1);
    sprintf(str3,"分店代號:%s",gConfig.MERCHANT.STCODE);
    
   //  ezxml_DATA = ezxml_get(ConfigDATA, "DEVICE",0,"CPU",0,"CPUDEVICEID",-1);
    BYTE TerminalID[16+1];
    BYTE tempbuf[6];
    wub_str_2_hex(gConfig.DEVICE.READER.CPU.CPUDEVICEID,(char *)&tempbuf, strlen(gConfig.DEVICE.READER.CPU.CPUDEVICEID));
    fnBINTODEVASC((char *)tempbuf,TerminalID,16,LEVEL2); 
    sprintf(str4,"設備代號:%s",TerminalID);
    
 //    ezxml_free(ConfigDATA);
    ShowMessage4line("端末機資訊",str1,str2,str3,str4,Type_ComformAnykey);
    return d_OK;
 }

 USHORT ShowDEVICEInfo()
 {
    BYTE str1[128],str2[128],str3[128],str4[128];
     
  
    memset(str1,0x00,sizeof(str1));
     memset(str2,0x00,sizeof(str2));
      memset(str3,0x00,sizeof(str3));
       memset(str4,0x00,sizeof(str4));
       
   
    sprintf(str1,"機器序號:%s",gConfig.DEVICE.EDC.MechineID);
  
  
    sprintf(str2,"磁碟容量:%s",gConfig.DEVICE.MEMORY.TOTALDISKSIZE);
    
  
    sprintf(str3,"磁碟已使用量:%s",gConfig.DEVICE.MEMORY.USEDDISKSIZE);
    
  
    ShowMessage4line("設備資訊",str1,str2,str3,str4,Type_ComformAnykey);
    return d_OK;
 }
 USHORT ShowTMInfo()
 {
    BYTE str1[128],str2[128],str3[128],str4[128];
    memset(str1,0x00,sizeof(str1));
    memset(str2,0x00,sizeof(str2));
    memset(str3,0x00,sizeof(str3));
    memset(str4,0x00,sizeof(str4));
       
    sprintf(str1,"商店代號:%s",gConfig.TM.LocationID);
    sprintf(str2,"收銀機代號:%s",gConfig.TM.bID);
    sprintf(str3,"店名:%s",gConfig.TM.TITLE);
    sprintf(str4,"分店名:%s",gConfig.TM.SUBTITLE);
  
    ShowMessage4line("商店資訊",str1,str2,str3,str4,Type_ComformAnykey);
    return d_OK;
 }

 USHORT ShowAPInfo()
 {
   BYTE str1[128],str2[128],str3[128],str4[128];
     
  
    memset(str1,0x00,sizeof(str1));
    memset(str2,0x00,sizeof(str2));
    memset(str3,0x00,sizeof(str3));
    memset(str4,0x00,sizeof(str4));
    sprintf(str1,"程式名稱:%s",gConfig.CURRVERSION.AP.NAME); 
    sprintf(str2,"程式版本:%s",gConfig.CURRVERSION.AP.VERSION); 
    sprintf(str3,"發行日期:%s",gConfig.CURRVERSION.AP.GeneratedDateTime); 
    sprintf(str4,"所屬公司:%s",gConfig.CURRVERSION.AP.Company);
    ShowMessage4line("程式資訊",str1,str2,str3,str4,Type_ComformAnykey);
   
    return d_OK;
 }
 USHORT ShowVersionInfo()
 {
    BYTE ParaVer[64],APVer[64],BlcVer[64],SSLVer[64];
   
    sprintf(ParaVer,"參數版本號:%s",gConfig.CURRVERSION.PARAMETER);
  
    sprintf(APVer,"主程式版本號:%s",gConfig.CURRVERSION.AP.VERSION);
 
    sprintf(BlcVer,"鎖卡名單版本號:%s",gConfig.CURRVERSION.BLC.VERSION);
 
    sprintf(SSLVer,"SSL憑證版本號:%s",gConfig.CURRVERSION.SSL.VERSION);
  
    ShowMessage4line("版本資訊",ParaVer,APVer,BlcVer,SSLVer,Type_ComformAnykey);
    return d_OK;
 }
 USHORT usSetNEWTransSN()
{
    int sn;
    STR CurrSNStr[32],buff[10];
    memset(buff,0x00,sizeof(buff));
    usGetCurrTransSN(&sn);
    sprintf(CurrSNStr,"目前交易序號:%d",sn);
    USHORT ret=ShowInputBox3line("修改交易序號",CurrSNStr,"","請輸入NEW 交易序號", buff,6,INPUT_TYPE_NumberWithRadixPoint,0);
    if(ret==d_OK){
        sn=atoi(buff);
        SetTransSN(sn);
      
    }
    
    return d_OK;
}
 
 USHORT UpdateTransSN()
{
    ezxml_t  ezxml_DATA;
    BYTE  bTransSn[6+1];
    BYTE buf[10];
    memset(buf,0x00,sizeof(buf));
    USHORT iTransSn,ret;
    memset(bTransSn,0x00,sizeof(bTransSn));
   
    //ret =ECC_GetXMLTag(ConfigXML, "TX","SERIALNO", bTransSn); 
    iTransSn=atol( gConfig.TX.SERIALNO);
    iTransSn++;
    if(iTransSn>=1000000)
        iTransSn=0;
  
    sprintf(gConfig.TX.SERIALNO,"%d",iTransSn);
    ret= SAVETransSn(gConfig.TX.SERIALNO);
   // ECC_SetXMLTag(TXINFO_Path,"TX","SERIALNO",gConfig.TX.SERIALNO);
      // ret= Config_SetData();  
   //ret=SetTXInfo();
   // sprintf(buf,"%d",iTransSn);
   // ret=ECC_SetXMLTag2(ConfigXML, "TX","SERIALNO", buf); 
    return ret;
    
}
 USHORT SAVETransSn(STR* SN)
 {
     USHORT ret= usWriteFile(TransSnFile,SN,strlen(SN));
     ret= usWriteFile(SDTransSnFile,SN,strlen(SN));
     return ret;
 }
 USHORT  GetTransSn(STR* SN)
 {
     ULONG iSize;
     USHORT ret=usReadFileData(TransSnFile,&iSize,SN);
     if(ret!=d_OK){
         ret=usReadFileData(SDTransSnFile,&iSize,SN);
         if(ret!=d_OK){
            sprintf(SN,"0");
         }else{
              USHORT ret= usWriteFile(TransSnFile,SN,strlen(SN));
         }
        SAVETransSn(SN);
     }
     return ret;
 }
USHORT SetTransSN(int SN)
{
 
    int iTransSn=SN;
    if(iTransSn>=1000000)
        return d_ERR_GetDataFail;
    sprintf(gConfig.TX.SERIALNO,"%d",iTransSn);
    USHORT ret= SAVETransSn(gConfig.TX.SERIALNO);
    // ret= Config_SetData();  
   // USHORT ret=ECC_SetXMLTag(TXINFO_Path,"TX","SERIALNO",gConfig.TX.SERIALNO);
    //  USHORT  ret=SetTXInfo();
    return ret;
}
 USHORT usGetCurrTransSN(int * SN)
{
    USHORT ret= GetTransSn(gConfig.TX.SERIALNO);
    if(ret==d_OK)
        *SN=atoi(gConfig.TX.SERIALNO);    
    return d_OK;
}
 USHORT GetRS232Setting()
 {
 
    memset(&gREADERPORT,0x00,sizeof(gREADERPORT));
    gREADERPORT.Portnum=d_COM2;
    gREADERPORT.ulBaudRate=115200;
    gREADERPORT.bParity='N';
    gREADERPORT.bDataBits=8;
    gREADERPORT.bStopBits=1;
    
    if(strcmp(gConfig.DEVICE.READER.bPORT,"COM1")==0)
             gREADERPORT.Portnum=d_COM1;
    else  if(strcmp(gConfig.DEVICE.READER.bPORT,"COM2")==0)
             gREADERPORT.Portnum=d_COM2;
   // else  if(strcmp(gConfig.DEVICE.READER.bPORT,"Builtin")==0)
   //          gREADERPORT.Portnum=d_COM3;
  
     gREADERPORT.ulBaudRate =wub_str_2_long(gConfig.DEVICE.READER.bBAUDRATE);   
     
     
   
 }
 USHORT GetFTPINFO()
{
    USHORT ret;
   memset(gFTPURL,0x00,sizeof(gFTPURL));
    memset(gFTPIP,0x00,sizeof(gFTPIP));
    memset(gFTPVIPIP,0x00,sizeof(gFTPVIPIP));
    memset(gFTPPORT,0x00,sizeof(gFTPPORT));
    memset(gFTPID,0x00,sizeof(gFTPID));
    memset(gFTPPW,0x00,sizeof(gFTPPW));
  if(strcmp(gConfig.ETHERNET.CONNECTHOST,"PRODUCTION")==0){
        sprintf(gFTPIP,"%s",gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP);  
        sprintf(gFTPURL,"%s",gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL);   
        sprintf(gFTPVIPIP,"%s",gConfig.ETHERNET.HOST_PRODUCTION.FTP.VIPIP);   
        sprintf(gFTPPORT,"%s",gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT);   
        sprintf(gFTPID,"%s",gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID);   
        sprintf(gFTPPW,"%s",gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD);   
   }else if(strcmp(gConfig.ETHERNET.CONNECTHOST,"TESTING")==0){
       sprintf(gFTPIP,"%s",gConfig.ETHERNET.HOST_TESTING.FTP.IP);  
        sprintf(gFTPURL,"%s",gConfig.ETHERNET.HOST_TESTING.FTP.URL);   
        sprintf(gFTPVIPIP,"%s",gConfig.ETHERNET.HOST_TESTING.FTP.VIPIP);   
        sprintf(gFTPPORT,"%s",gConfig.ETHERNET.HOST_TESTING.FTP.PORT);   
        sprintf(gFTPID,"%s",gConfig.ETHERNET.HOST_TESTING.FTP.LOGINID);   
        sprintf(gFTPPW,"%s",gConfig.ETHERNET.HOST_TESTING.FTP.LOGINPASSWORD);   
        
   }else if(strcmp(gConfig.ETHERNET.CONNECTHOST,"DEVELOP")==0){
        sprintf(gFTPIP,"%s",gConfig.ETHERNET.HOST_DEVELOP.FTP.IP);  
        sprintf(gFTPURL,"%s",gConfig.ETHERNET.HOST_DEVELOP.FTP.URL); 
        sprintf(gFTPVIPIP,"%s",gConfig.ETHERNET.HOST_DEVELOP.FTP.VIPIP);   
        sprintf(gFTPPORT,"%s",gConfig.ETHERNET.HOST_DEVELOP.FTP.PORT);  
        sprintf(gFTPID,"%s",gConfig.ETHERNET.HOST_DEVELOP.FTP.LOGINID);   
        sprintf(gFTPPW,"%s",gConfig.ETHERNET.HOST_DEVELOP.FTP.LOGINPASSWORD);   
   }
   return d_OK;
}
 
 USHORT GetHOSTINFO()
{
    USHORT ret;
   
    memset(gHOSTURL,0x00,sizeof(gHOSTURL));
    memset(gHOSTVIPIP,0x00,sizeof(gHOSTVIPIP));
    memset(gHOSTIP,0x00,sizeof(gHOSTIP));
    memset(gHOSTPORT,0x00,sizeof(gHOSTPORT));
  /*  sprintf(gHOSTURL,"211.78.134.167");   
     sprintf(gHOSTURLPORT,"7000"); 
     sprintf(gHOSTIP,"211.78.134.167"); 
     sprintf(gHOSTIPPORT,"7000"); 
        return d_OK;*/
   if(strcmp(gConfig.ETHERNET.CONNECTHOST,"PRODUCTION")==0){
        sprintf(gHOSTURL,"%s",gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL);   
        sprintf(gHOSTIP,"%s",gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP);   
        sprintf(gHOSTVIPIP,"%s",gConfig.ETHERNET.HOST_PRODUCTION.HOST.VIPIP);   
        sprintf(gHOSTPORT,"%s",gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT);   
       
   }else  if(strcmp(gConfig.ETHERNET.CONNECTHOST,"TESTING")==0){
        sprintf(gHOSTURL,"%s",gConfig.ETHERNET.HOST_TESTING.HOST.URL);   
        sprintf(gHOSTIP,"%s",gConfig.ETHERNET.HOST_TESTING.HOST.IP);   
        sprintf(gHOSTVIPIP,"%s",gConfig.ETHERNET.HOST_TESTING.HOST.VIPIP);   
        sprintf(gHOSTPORT,"%s",gConfig.ETHERNET.HOST_TESTING.HOST.PORT);   
  
    }else  if(strcmp(gConfig.ETHERNET.CONNECTHOST,"DEVELOP")==0){
        sprintf(gHOSTURL,"%s",gConfig.ETHERNET.HOST_DEVELOP.HOST.URL);   
        sprintf(gHOSTIP,"%s",gConfig.ETHERNET.HOST_DEVELOP.HOST.IP);   
        sprintf(gHOSTVIPIP,"%s",gConfig.ETHERNET.HOST_DEVELOP.HOST.VIPIP);   
        sprintf(gHOSTPORT,"%s",gConfig.ETHERNET.HOST_DEVELOP.HOST.PORT);   
    }
    /////////////////////////////////////////////////////////////////////////////// 
 
     return d_OK;
}

USHORT  SetConfigTag(STR *node,STR * tag,STR * data)
{
     char ERRMSG[32];   
      ezxml_t ConfigDATA = ezxml_parse_file(ConfigXML);
     if(ConfigDATA ==NULL){       return d_Fail;    }
      
     ezxml_t TAG = ezxml_get(ConfigDATA,  node,0,tag, -1);
     if(TAG ==NULL) {    
         sprintf(ERRMSG,"Get NODE %s %s Fail",node,tag);
	 SystemLog("SetConfigTag",ERRMSG);
         ezxml_free(ConfigDATA);
         return d_Fail;
     }else{
         ezxml_set_txt_d(TAG,data);
      
     }
      USHORT ret= ECC_WriteXMLFILE(ConfigXML,ConfigDATA);
      ezxml_free(ConfigDATA);
     return d_OK;
}
USHORT  SetConfigTag2(STR *node1,STR *node2,STR * tag,STR * data)
{
     char ERRMSG[32];   
      ezxml_t ConfigDATA = ezxml_parse_file(ConfigXML);
     if(ConfigDATA ==NULL){       return d_Fail;    }
     
      ezxml_t TAG = ezxml_get(ConfigDATA,  node1,0,node2,0,tag, -1);
     if(TAG ==NULL) {    
         sprintf(ERRMSG,"Get NODE %s %s %s Fail",node1,node2,tag);
	 SystemLog("SetConfigTag",ERRMSG);
          ezxml_free(ConfigDATA);
         return d_Fail;
     }else{
         ezxml_set_txt_d(TAG,data);
        
     } 
      USHORT ret= ECC_WriteXMLFILE(ConfigXML,ConfigDATA);
      ezxml_free(ConfigDATA);
     return ret;
}






USHORT  GetConfigTag(STR *node,STR * tag,STR * data)
{
    
    USHORT ret;

    ezxml_t TAG;
    ezxml_t ConfigDATA = ezxml_parse_file(ConfigXML);
    if(ConfigDATA ==NULL){       return d_Fail;    }
    TAG = ezxml_get(ConfigDATA, node,0, tag, -1);
    if(TAG ==NULL){

       return d_Fail;
    }
     if(strlen(TAG->txt)<=0){
      ezxml_free(ConfigDATA);
      return d_Fail;
    }
    sprintf(data,"%s",TAG->txt);
    ezxml_free(ConfigDATA);
    return d_OK;
}
USHORT  GetConfigTag2(STR *node1,STR * node2,STR * tag,STR * data)
{
    
    USHORT ret;
  
    ezxml_t TAG;
    ezxml_t ConfigDATA = ezxml_parse_file(ConfigXML);
    if(ConfigDATA ==NULL){       return d_Fail;    }
    TAG = ezxml_get(ConfigDATA, node1,0,node2,0, tag, -1);
    if(TAG ==NULL){

       return d_Fail;
    }
     if(strlen(TAG->txt)<=0){
      ezxml_free(ConfigDATA);
      return d_Fail;
    }
    sprintf(data,"%s",TAG->txt);
    ezxml_free(ConfigDATA);
    return d_OK;
}


USHORT  GetConfigTag3(STR *node1,STR * node2,STR * node3,STR * tag,STR * data)
{
    
    USHORT ret;
  
    ezxml_t TAG;
    ezxml_t ConfigDATA = ezxml_parse_file(ConfigXML);
    if(ConfigDATA ==NULL){       return d_Fail;    }
    
    TAG = ezxml_get(ConfigDATA, node1,0,node2,0,node3,0, tag, -1);
    if(TAG ==NULL){
       return d_Fail;
    }
     if(strlen(TAG->txt)<=0){
      ezxml_free(ConfigDATA);
      return d_Fail;
    }
    sprintf(data,"%s",TAG->txt);
   ezxml_free(ConfigDATA);
    return d_OK;
}
USHORT  GetConfigTag4(STR *node1,STR * node2,STR * node3,STR * node4,STR * tag,STR * data)
{
    
    USHORT ret;
    ezxml_t TAG;
    ezxml_t ConfigDATA = ezxml_parse_file(ConfigXML);
    if(ConfigDATA ==NULL){       return d_Fail;    }
    
    TAG = ezxml_get(ConfigDATA, node1,0,node2,0,node3,0,node4,0, tag, -1);
    if(TAG ==NULL){

       return d_Fail;
    }
    if(strlen(TAG->txt)<=0){
      ezxml_free(ConfigDATA);
      return d_Fail;
    }
    sprintf(data,"%s",TAG->txt);
    ezxml_free(ConfigDATA);
    return d_OK;
}


USHORT GetXmlNodeattr_Name(ezxml_t node,STR * Name)
{
      
      if(ezxml_attr(node, "name")!=NULL)     
            sprintf(Name,"%s",ezxml_attr(node, "name"));
        else
            sprintf(Name,"%s",node->name);
      return d_OK;
}
USHORT GetXmlNodeattr_readwrite(ezxml_t node,STR * flag)
{
      
      if(ezxml_attr(node, "readwrite")!=NULL)     
            sprintf(flag,"%s",ezxml_attr(node, "readwrite"));
        else
            sprintf(flag,"%s",node->name);
      return d_OK;
}


USHORT SystemReset()
{   
   USHORT ret;
    
    ret=ShowMessage3line("系統重置","請注意!!","將清除所有資料","回復預設值",Type_Comform0);
    if(ret!=d_OK) return ;
   ret=CTOS_FileDelete ( TransDataFile );
 //  ret=CTOS_FileDelete ( ConfigDataFile );
//   ret=CTOS_FileDelete ( ConfigData2File );
  // ret=CTOS_FileDelete ( ConfigData3File );
    //ret=CTOS_FileDelete ( ConfigV3File );
   ret=CTOS_FileDelete ( ConfigV4File );
   ret=CTOS_FileDelete ( BatchTotleFile );
   ret=CTOS_FileDelete ( FUNCTIONFile );//2014.08.28, kobe added it to remove function Setting

  RemoveSysInfoFile();
  remove(TransSnFile);
  remove(SDTransSnFile);
  remove(BatchSnFile); 
  remove(SDBatchSnFile);  
  remove(TransDataFile);
  remove(SettleFile);
  remove(ReversalFile);    
 
   //2014.04.15,kobe added for ECR
   ret=remove(AROUND_DEVICE_CONFIG);
     CTOS_SystemReset();

     return 0;
}


USHORT InitEthernetInfo()
{
	
	BYTE len=0;
        len=sizeof(gConfig.ETHERNET.LOCAL.IP);	
	memset(gConfig.ETHERNET.LOCAL.IP,0x00,sizeof(gConfig.ETHERNET.LOCAL.IP));   
	USHORT ret = CTOS_EthernetConfigGet((BYTE)d_ETHERNET_CONFIG_IP, (BYTE *)&gConfig.ETHERNET.LOCAL.IP,&len);
       if(ret!=d_OK)  SystemLogInt("GetEthernetInfo",ret,"CTOS_EthernetConfigGet IP fail");
        
      

        len=sizeof(gConfig.ETHERNET.LOCAL.MASK);	
	memset(gConfig.ETHERNET.LOCAL.MASK,0x00,sizeof(gConfig.ETHERNET.LOCAL.MASK));   
        ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_MASK, (BYTE *)&gConfig.ETHERNET.LOCAL.MASK, &len);
		if(ret!=d_OK)  SystemLogInt("GetEthernetInfo",ret,"CTOS_EthernetConfigGet fail");

	len=sizeof(gConfig.ETHERNET.LOCAL.GATEWAY);	
        memset(gConfig.ETHERNET.LOCAL.GATEWAY,0x00,sizeof(gConfig.ETHERNET.LOCAL.GATEWAY));   
       ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_GATEWAY,  (BYTE *)&gConfig.ETHERNET.LOCAL.GATEWAY,&len);

	
	len=sizeof(gConfig.ETHERNET.LOCAL.DNS);	
       memset(gConfig.ETHERNET.LOCAL.DNS,0x00,sizeof(gConfig.ETHERNET.LOCAL.DNS));   
       ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DNSIP, (BYTE *)&gConfig.ETHERNET.LOCAL.DNS,&len);

	
	len=sizeof(gConfig.ETHERNET.LOCAL.MAC);	
        memset(gConfig.ETHERNET.LOCAL.MAC,0x00,sizeof(gConfig.ETHERNET.LOCAL.MAC));   
       ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_MAC, (BYTE *)&gConfig.ETHERNET.LOCAL.MAC,&len);
       
        len=sizeof(gConfig.ETHERNET.LOCAL.DHCP);	
        memset(gConfig.ETHERNET.LOCAL.DHCP,0x00,sizeof(gConfig.ETHERNET.LOCAL.DHCP));   
       ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DHCP, (BYTE *)&gConfig.ETHERNET.LOCAL.DHCP,&len);

	
       return ret;

}
USHORT GetEDCINFO()
{
     USHORT ret;
     BYTE baFactorySN[32];
     BYTE buf[16];
   
     
     memset(baFactorySN,0x00,sizeof(baFactorySN));   
     USHORT usAPIndex; 
     CTOS_stCAPInfo stInfo;
     ret= CTOS_APFind (APPNAME, &usAPIndex );
     if(ret==d_OK){
       ret= CTOS_APSet ( usAPIndex, d_AP_FLAG_DEF_SEL);//Set the AP as default running AP
       ret= CTOS_SetPMEnterPassword ( gConfig.DEVICE.PMPASSWORD, TRUE);//Enable/Disable the password for entering Program Manager
       ret= CTOS_APGet ( usAPIndex, &stInfo );
        sprintf((BYTE *)&gConfig.CURRVERSION.AP.NAME,"%s",stInfo.baExeName);
        ECC_SetXMLTag3(VERSIONINFO_Path,"VERSION","CURRVERSION","AP","NAME",gConfig.CURRVERSION.AP.NAME);
        sprintf(gAPVER,"00%02x%02x",stInfo.baVersion[0],stInfo.baVersion[1]);
        
        sprintf((BYTE *)&gConfig.CURRVERSION.AP.VERSION,"%s",gAPVER);
        ECC_SetXMLTag3(VERSIONINFO_Path,"VERSION","CURRVERSION","AP","VERSION",gConfig.CURRVERSION.AP.VERSION);
        sprintf((BYTE *)&gConfig.CURRVERSION.AP.GeneratedDateTime,"%s",stInfo.baGeneratedDateTime);
        ECC_SetXMLTag3(VERSIONINFO_Path,"VERSION","CURRVERSION","AP","GeneratedDateTime",gConfig.CURRVERSION.AP.GeneratedDateTime);
        sprintf((BYTE *)&gConfig.CURRVERSION.AP.Company,"%s",stInfo.baCompany);
        ECC_SetXMLTag3(VERSIONINFO_Path,"VERSION","CURRVERSION","AP","Company",gConfig.CURRVERSION.AP.Company);
        //SetVERSIONInfo();
     ret= CTOS_GetFactorySN ( baFactorySN);
     if(ret!=d_OK)
         return ret;
     } 
     memcpy( gConfig.DEVICE.EDC.MechineID,baFactorySN,15);
     gConfig.DEVICE.EDC.MechineID[15]=0x00;
     ECC_SetXMLTag2(DEVICEINFO_Path,"DEVICE","EDC","MechineID",gConfig.DEVICE.EDC.MechineID);
     //SetDEVICEInfo();
       return ret;
}
USHORT GetEDCSystemMemoryStatus()
{
     USHORT ret;
     ULONG ulUsedDiskSize ,ulTotalDiskSize, ulUsedRamSize, ulTotalRamSize; 
      ret= CTOS_SystemMemoryStatus(&ulUsedDiskSize,&ulTotalDiskSize,&ulUsedRamSize,&ulTotalRamSize);
     if(ret!=d_OK)
         return ret;
      sprintf( gConfig.DEVICE.MEMORY.USEDDISKSIZE,"%ld",ulUsedDiskSize);
      sprintf( gConfig.DEVICE.MEMORY.TOTALDISKSIZE,"%ld",ulTotalDiskSize);
      sprintf( gConfig.DEVICE.MEMORY.USEDRAMSIZE,"%ld",ulUsedRamSize);
      sprintf( gConfig.DEVICE.MEMORY.TOTALRAMSIZE,"%ld",ulTotalRamSize);
      ECC_SetXMLTag2(DEVICEINFO_Path,"DEVICE","MEMORY","TOTALRAMSIZE",gConfig.DEVICE.MEMORY.TOTALRAMSIZE);
      ECC_SetXMLTag2(DEVICEINFO_Path,"DEVICE","MEMORY","TOTALDISKSIZE",gConfig.DEVICE.MEMORY.TOTALDISKSIZE);
      ECC_SetXMLTag2(DEVICEINFO_Path,"DEVICE","MEMORY","USEDRAMSIZE",gConfig.DEVICE.MEMORY.USEDRAMSIZE);
      ECC_SetXMLTag2(DEVICEINFO_Path,"DEVICE","MEMORY","TOTALRAMSIZE",gConfig.DEVICE.MEMORY.TOTALRAMSIZE);
               
     // ret= Config_SetData();  
        ret=SetDEVICEInfo();
   
       return ret;
}
/*
USHORT InitConfigData()
{
   USHORT ret=Config_GetData();
    
    ret=ConfigFunction_GetData();
    GetEDCSystemMemoryStatus();
    GetEDCINFO();
    InitEthernetInfo();
    ret=GetHOSTINFO();
    ret=GetFTPINFO();
    ret= GetRS232Setting();
    
    int tmp=0;tmp=atoi(gConfig.TX.SIGNONMAXTIME);
    gSignOnlimit=(tmp*60*60*100);
    gDebugPrintFlag=atoi(gConfig.sDEBUG.PRINT.ENABLE);
    gDebugFTPFlag=atoi(gConfig.sDEBUG.FTP.ENABLE);
    gFORCEONLINELIMIT=atoi(gConfig.TX.FORCEONLINELIMIT); 
    gOFFLINETXLIMIT=atoi(gConfig.TX.OFFLINETXLIMIT);
    sprintf(gCAFile,"ck1.cer");
   
    // SSL load object 
   int Filesize;
   ret= Get_SSLCA();
  
//    ret= Config_SetData();
    return ret;
}
*/
USHORT Get_SSLCA()
{
    
   USHORT ret;
 
    BYTE CaExpiry[14+1];  
    unsigned long CurrDate,ExpiryDate; 
    BYTE CA1FileName[12], CA2FileName[12];
    memset(CA1FileName,0x00,sizeof(CA1FileName));
    memset(CA2FileName,0x00,sizeof(CA2FileName));

   sprintf(CA1FileName,"%s",gConfig.CURRVERSION.SSL.CAFILENAME1);     
  //  sprintf(gCAFile,"%s",CA1FileName);
 sprintf(gCAFile,"ck1.cer");
///////////////////////////////////////////    
    memset(gCA,0x00,sizeof(gCA));
   
    ULONG Filesize= File_GetLen(gCAFile);
    if(Filesize==0) return d_ERR_FILE_SIZE_ERR;   
    ret=usReadFileData(gCAFile,&Filesize,(BYTE *)gCA);   
    if(ret==d_OK)
        gCAlen=Filesize;
    ////////////////////////////////////////////
    return d_OK;
    /*
     sprintf(CaExpiry,"%s000000",gConfig.CURRVERSION.SSL.CAEXPIRYDAY1);
     fngetUnixTimeCnt(&ExpiryDate,&CaExpiry);
     
   if(CurrDate<ExpiryDate)
     {
         sprintf(gCAFile,"%s",CA1FileName);
         return d_OK;
     }
 
  
    sprintf(CA2FileName,"%s",gConfig.CURRVERSION.SSL.CAFILENAME2);  
     sprintf(CaExpiry,"%s000000",gConfig.CURRVERSION.SSL.CAEXPIRYDAY1);
     fngetUnixTimeCnt(&ExpiryDate,&CaExpiry);
     
   if(CurrDate<ExpiryDate)
     {
         sprintf(gCAFile,"%s",CA2FileName);
         return d_OK;
     }
     */
     return d_SSL_NOVAILDCA;

}
/*
USHORT ConfigV2_GetInitData( ConfigV2_STRUCT *ConfigV2)
{
   memset(ConfigV2,0x00,sizeof(ConfigV2_STRUCT));

USHORT ret=  GetConfigTag2("DEBUG","PRINT","ENABLE", ConfigV2.sDEBUG.PRINT.ENABLE);
ret=  GetConfigTag2("DEBUG","FTP","ENABLE",ConfigV2.sDEBUG.FTP.ENABLE);
ret=  GetConfigTag2("DEBUG","FTP","IP",ConfigV2.sDEBUG.FTP.IP);
ret=  GetConfigTag2("DEBUG","FTP","ID",ConfigV2.sDEBUG.FTP.ID);
ret=  GetConfigTag2("DEBUG","FTP","PASSWORD",ConfigV2.sDEBUG.FTP.PASSWORD);
ret=  GetConfigTag2("DEBUG","SD","ENABLE",ConfigV2.sDEBUG.SD.ENABLE);


ret=  GetConfigTag("TX","SERIALNO",ConfigV2.TX.SERIALNO);
ret=  GetConfigTag("TX","SIGNONMAXTIME",ConfigV2.TX.SIGNONMAXTIME);
ret=  GetConfigTag("TX","OFFLINETXLIMIT",ConfigV2.TX.OFFLINETXLIMIT);
ret=  GetConfigTag("TX","FORCEONLINELIMIT",ConfigV2.TX.FORCEONLINELIMIT);
ret=  GetConfigTag("TX","MiniunitsADDVALUE",ConfigV2.TX.MiniunitsADDVALUE);


ret=  GetConfigTag("MERCHANT","PASSWORD",ConfigV2.MERCHANT.PASSWORD);
//ret=  GetConfigTag("MERCHANT","MERCHANTID",gConfig.MERCHANT.MERCHANTID);
//ret=  GetConfigTag("MERCHANT","NewLocationID",gConfig.MERCHANT.NewLocationID);
//ret=  GetConfigTag("MERCHANT","STCODE",gConfig.MERCHANT.STCODE);

ret=  GetConfigTag("DEVICE","SSLEnable",ConfigV2.DEVICE.SSLEnable);
ret=  GetConfigTag("DEVICE","SAMSLOT",ConfigV2.DEVICE.SAMSLOT);
ret=  GetConfigTag2("DEVICE","EDC","MechineID",ConfigV2.DEVICE.EDC.MechineID);

ret=  GetConfigTag2("DEVICE","READER","PORT",ConfigV2.DEVICE.READER.bPORT);
ret=  GetConfigTag2("DEVICE","READER","BAUDRATE",ConfigV2.DEVICE.READER.bBAUDRATE);
ret=  GetConfigTag2("DEVICE","READER","PARITY",ConfigV2.DEVICE.READER.bPARITY);
ret=  GetConfigTag2("DEVICE","READER","DATABITS",ConfigV2.DEVICE.READER.bDATABITS);
ret=  GetConfigTag2("DEVICE","READER","STOPBITS",ConfigV2.DEVICE.READER.bSTOPBITS);

ret=  GetConfigTag("COMPORT","READER",ConfigV2.COMPORT.READER);
ret=  GetConfigTag("COMPORT","ECR",ConfigV2.COMPORT.ECR);

ret=  GetConfigTag("BATCH","NO",ConfigV2.BATCH.NO);

ret=  GetConfigTag2("ETHERNET","LOCAL","IP",ConfigV2.ETHERNET.LOCAL.IP);
ret=  GetConfigTag2("ETHERNET","LOCAL","MASK",ConfigV2.ETHERNET.LOCAL.MASK);
ret=  GetConfigTag2("ETHERNET","LOCAL","GATEWAY",ConfigV2.ETHERNET.LOCAL.GATEWAY);
ret=  GetConfigTag2("ETHERNET","LOCAL","DNS",ConfigV2.ETHERNET.LOCAL.DNS);
ret=  GetConfigTag2("ETHERNET","LOCAL","MAC",ConfigV2.ETHERNET.LOCAL.MAC);

ret=  GetConfigTag("ETHERNET","CONNECTMODE",ConfigV2.ETHERNET.CONNECTMODE);
ret=  GetConfigTag3("ETHERNET","COMM","HOST","URL",ConfigV2.ETHERNET.COMM.HOST.URL);
ret=  GetConfigTag3("ETHERNET","COMM","HOST","URLPORT",ConfigV2.ETHERNET.COMM.HOST.URLPORT);
ret=  GetConfigTag3("ETHERNET","COMM","HOST","IP",ConfigV2.ETHERNET.COMM.HOST.IP);
ret=  GetConfigTag3("ETHERNET","COMM","HOST","PORT",ConfigV2.ETHERNET.COMM.HOST.PORT);

ret=  GetConfigTag3("ETHERNET","COMM","FTP","URL",ConfigV2.ETHERNET.COMM.FTP.URL);
ret=  GetConfigTag3("ETHERNET","COMM","FTP","IP",ConfigV2.ETHERNET.COMM.FTP.IP);
ret=  GetConfigTag3("ETHERNET","COMM","FTP","LOGINID",ConfigV2.ETHERNET.COMM.FTP.LOGINID);
ret=  GetConfigTag3("ETHERNET","COMM","FTP","LOGINPASSWORD",ConfigV2.ETHERNET.COMM.FTP.LOGINPASSWORD);


ret=  GetConfigTag3("ETHERNET","COMM_TEST","HOST","URL",ConfigV2.ETHERNET.COMM_TEST.HOST.URL);
ret=  GetConfigTag3("ETHERNET","COMM_TEST","HOST","URLPORT",ConfigV2.ETHERNET.COMM_TEST.HOST.URLPORT);
ret=  GetConfigTag3("ETHERNET","COMM_TEST","HOST","IP",ConfigV2.ETHERNET.COMM_TEST.HOST.IP);
ret=  GetConfigTag3("ETHERNET","COMM_TEST","HOST","PORT",ConfigV2.ETHERNET.COMM_TEST.HOST.PORT);

ret=  GetConfigTag3("ETHERNET","COMM_TEST","FTP","URL",ConfigV2.ETHERNET.COMM_TEST.FTP.URL);
ret=  GetConfigTag3("ETHERNET","COMM_TEST","FTP","IP",ConfigV2.ETHERNET.COMM_TEST.FTP.IP);
ret=  GetConfigTag3("ETHERNET","COMM_TEST","FTP","LOGINID",ConfigV2.ETHERNET.COMM_TEST.FTP.LOGINID);
ret=  GetConfigTag3("ETHERNET","COMM_TEST","FTP","LOGINPASSWORD",ConfigV2.ETHERNET.COMM_TEST.FTP.LOGINPASSWORD);


ret=  GetConfigTag3("ETHERNET","COMM_DEVELOP","HOST","URL",ConfigV2.ETHERNET.COMM_DEVELOP.HOST.URL);
ret=  GetConfigTag3("ETHERNET","COMM_DEVELOP","HOST","URLPORT",ConfigV2.ETHERNET.COMM_DEVELOP.HOST.URLPORT);
ret=  GetConfigTag3("ETHERNET","COMM_DEVELOP","HOST","IP",ConfigV2.ETHERNET.COMM_DEVELOP.HOST.IP);
ret=  GetConfigTag3("ETHERNET","COMM_DEVELOP","HOST","PORT",ConfigV2.ETHERNET.COMM_DEVELOP.HOST.PORT);

ret=  GetConfigTag3("ETHERNET","COMM_DEVELOP","FTP","URL",ConfigV2.ETHERNET.COMM_DEVELOP.FTP.URL);
ret=  GetConfigTag3("ETHERNET","COMM_DEVELOP","FTP","IP",ConfigV2.ETHERNET.COMM_DEVELOP.FTP.IP);
ret=  GetConfigTag3("ETHERNET","COMM_DEVELOP","FTP","LOGINID",ConfigV2.ETHERNET.COMM_DEVELOP.FTP.LOGINID);
ret=  GetConfigTag3("ETHERNET","COMM_DEVELOP","FTP","LOGINPASSWORD",ConfigV2.ETHERNET.COMM_DEVELOP.FTP.LOGINPASSWORD);
return d_OK;
}
*/
/*
USHORT  ConfigV3_GetInitData(ConfigV3_STRUCT * ConfigV3)
{
   memset(ConfigV3,0x00,sizeof(ConfigV3_STRUCT));
USHORT ret=  GetConfigTag2("DEBUG","PRINT","ENABLE", ConfigV3->sDEBUG.PRINT.ENABLE);
ret=  GetConfigTag2("DEBUG","FTP","ENABLE", ConfigV3->sDEBUG.FTP.ENABLE);
ret=  GetConfigTag2("DEBUG","FTP","IP", ConfigV3->sDEBUG.FTP.IP);
ret=  GetConfigTag2("DEBUG","FTP","ID", ConfigV3->sDEBUG.FTP.ID);
ret=  GetConfigTag2("DEBUG","FTP","PASSWORD", ConfigV3->sDEBUG.FTP.PASSWORD);
ret=  GetConfigTag2("DEBUG","SD","ENABLE", ConfigV3->sDEBUG.SD.ENABLE);

ret=  sprintf(ConfigV3->CURRVERSION.PARAMETER,"0000");
ret=  sprintf(ConfigV3->CURRVERSION.AP.VERSION,"0000");
ret=  sprintf(ConfigV3->CURRVERSION.BLC.VERSION,"0000");
ret=  sprintf(ConfigV3->CURRVERSION.SSL.VERSION,"0000");
ret=  sprintf(ConfigV3->CURRVERSION.READERFW.VERSION,"0000");
ret=  sprintf(ConfigV3->MERCHANT.PASSWORD,"0000");
ret=  GetConfigTag("TX","SERIALNO", ConfigV3->TX.SERIALNO);
ret=  GetConfigTag("TX","SIGNONMAXTIME", ConfigV3->TX.SIGNONMAXTIME);
ret=  GetConfigTag("TX","OFFLINETXLIMIT", ConfigV3->TX.OFFLINETXLIMIT);
ret=  GetConfigTag("TX","FORCEONLINELIMIT", ConfigV3->TX.FORCEONLINELIMIT);
ret=  GetConfigTag("TX","MiniunitsADDVALUE", ConfigV3->TX.MiniunitsADDVALUE);
ret=  GetConfigTag("TX","OPERATIONMODE", ConfigV3->TX.OPERATIONMODE);

ret=  GetConfigTag("DEVICE","SSLEnable", ConfigV3->DEVICE.SSLEnable);
ret=  GetConfigTag("DEVICE","SAMSLOT", ConfigV3->DEVICE.SAMSLOT);
//ret=  GetConfigTag2("DEVICE","EDC","MechineID",gConfig.DEVICE.EDC.MechineID);

ret=  GetConfigTag2("DEVICE","READER","PORT", ConfigV3->DEVICE.READER.bPORT);
ret=  GetConfigTag2("DEVICE","READER","BAUDRATE", ConfigV3->DEVICE.READER.bBAUDRATE);
ret=  GetConfigTag2("DEVICE","READER","PARITY", ConfigV3->DEVICE.READER.bPARITY);
ret=  GetConfigTag2("DEVICE","READER","DATABITS", ConfigV3->DEVICE.READER.bDATABITS);
ret=  GetConfigTag2("DEVICE","READER","STOPBITS", ConfigV3->DEVICE.READER.bSTOPBITS);
ret=  GetConfigTag2("DEVICE","ECR","PORT", ConfigV3->DEVICE.ECR.bPORT);
ret=  GetConfigTag2("DEVICE","ECR","BAUDRATE", ConfigV3->DEVICE.ECR.bBAUDRATE);
ret=  GetConfigTag2("DEVICE","ECR","PARITY", ConfigV3->DEVICE.ECR.bPARITY);
ret=  GetConfigTag2("DEVICE","ECR","DATABITS", ConfigV3->DEVICE.ECR.bDATABITS);
ret=  GetConfigTag2("DEVICE","ECR","STOPBITS", ConfigV3->DEVICE.ECR.bSTOPBITS);

ret=  GetConfigTag("TM","ID", ConfigV3->TM.ID);
ret=  GetConfigTag("TM","AgentNumber", ConfigV3->TM.AgentNumber);
ret=  GetConfigTag("TM","TITLE", ConfigV3->TM.TITLE);
ret=  GetConfigTag("TM","SUBTITLE", ConfigV3->TM.SUBTITLE);
ret=  GetConfigTag("TM","RECEIPTNUM", ConfigV3->TM.RECEIPTNUM);
ret=  GetConfigTag("TM","RECEIPTTYPE1", ConfigV3->TM.RECEIPTTYPE1);
ret=  GetConfigTag("TM","RECEIPTTYPE2",ConfigV3->TM.RECEIPTTYPE2);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING1", ConfigV3->TM.RECEIPTREMARK.STRING1);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING2", ConfigV3->TM.RECEIPTREMARK.STRING2);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING3", ConfigV3->TM.RECEIPTREMARK.STRING3);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING4", ConfigV3->TM.RECEIPTREMARK.STRING4);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING5", ConfigV3->TM.RECEIPTREMARK.STRING5);


ret=  GetConfigTag2("ETHERNET","LOCAL","IP", ConfigV3->ETHERNET.LOCAL.IP);
ret=  GetConfigTag2("ETHERNET","LOCAL","MASK", ConfigV3->ETHERNET.LOCAL.MASK);
ret=  GetConfigTag2("ETHERNET","LOCAL","GATEWAY", ConfigV3->ETHERNET.LOCAL.GATEWAY);
ret=  GetConfigTag2("ETHERNET","LOCAL","DNS", ConfigV3->ETHERNET.LOCAL.DNS);
//ret=  GetConfigTag2("ETHERNET","LOCAL","MAC",gConfig.ETHERNET.LOCAL.MAC);

ret=  GetConfigTag("ETHERNET","CONNECTHOST", ConfigV3->ETHERNET.CONNECTHOST);
ret=  GetConfigTag("ETHERNET","NETWORKMODE", ConfigV3->ETHERNET.NETWORKMODE);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","HOST","URL", ConfigV3->ETHERNET.HOST_PRODUCTION.HOST.URL);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","HOST","VIPIP", ConfigV3->ETHERNET.HOST_PRODUCTION.HOST.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","HOST","IP", ConfigV3->ETHERNET.HOST_PRODUCTION.HOST.IP);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","HOST","PORT", ConfigV3->ETHERNET.HOST_PRODUCTION.HOST.PORT);

ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","URL", ConfigV3->ETHERNET.HOST_PRODUCTION.FTP.URL);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","IP", ConfigV3->ETHERNET.HOST_PRODUCTION.FTP.IP);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","VIPIP", ConfigV3->ETHERNET.HOST_PRODUCTION.FTP.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","LOGINID", ConfigV3->ETHERNET.HOST_PRODUCTION.FTP.LOGINID);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","LOGINPASSWORD", ConfigV3->ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD);

ret=  GetConfigTag3("ETHERNET","HOST_TESTING","HOST","URL", ConfigV3->ETHERNET.HOST_TESTING.HOST.URL);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","HOST","IP", ConfigV3->ETHERNET.HOST_TESTING.HOST.IP);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","HOST","VIPIP", ConfigV3->ETHERNET.HOST_TESTING.HOST.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","HOST","PORT", ConfigV3->ETHERNET.HOST_TESTING.HOST.PORT);

ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","URL", ConfigV3->ETHERNET.HOST_TESTING.FTP.URL);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","IP", ConfigV3->ETHERNET.HOST_TESTING.FTP.IP);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","VIPIP", ConfigV3->ETHERNET.HOST_TESTING.FTP.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","LOGINID", ConfigV3->ETHERNET.HOST_TESTING.FTP.LOGINID);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","LOGINPASSWORD", ConfigV3->ETHERNET.HOST_TESTING.FTP.LOGINPASSWORD);

ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","HOST","URL", ConfigV3->ETHERNET.HOST_DEVELOP.HOST.URL);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","HOST","VIPIP", ConfigV3->ETHERNET.HOST_DEVELOP.HOST.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","HOST","IP", ConfigV3->ETHERNET.HOST_DEVELOP.HOST.IP);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","HOST","PORT", ConfigV3->ETHERNET.HOST_DEVELOP.HOST.PORT);

ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","URL", ConfigV3->ETHERNET.HOST_DEVELOP.FTP.URL);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","IP", ConfigV3->ETHERNET.HOST_DEVELOP.FTP.IP);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","VIPIP", ConfigV3->ETHERNET.HOST_DEVELOP.HOST.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","LOGINID", ConfigV3->ETHERNET.HOST_DEVELOP.FTP.LOGINID);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","LOGINPASSWORD", ConfigV3->ETHERNET.HOST_DEVELOP.FTP.LOGINPASSWORD);

return d_OK;
}
 */


USHORT  ConfigV4_GetInitData(ConfigV4_STRUCT * ConfigV4)
{
   memset(ConfigV4,0x00,sizeof(ConfigV4_STRUCT));
USHORT ret=  GetConfigTag2("DEBUG","PRINT","ENABLE", ConfigV4->sDEBUG.PRINT.ENABLE);
ret=  GetConfigTag2("DEBUG","FTP","ENABLE", ConfigV4->sDEBUG.FTP.ENABLE);
ret=  GetConfigTag2("DEBUG","FTP","IP", ConfigV4->sDEBUG.FTP.IP);
//ret=  GetConfigTag2("DEBUG","FTP","ID", ConfigV4->sDEBUG.FTP.ID);
ret=  GetConfigTag2("DEBUG","FTP","PASSWORD", ConfigV4->sDEBUG.FTP.PASSWORD);
ret=  GetConfigTag2("DEBUG","SD","ENABLE", ConfigV4->sDEBUG.SD.ENABLE);

ret=  sprintf(ConfigV4->CURRVERSION.PARAMETER,"0000");
ret=  sprintf(ConfigV4->CURRVERSION.AP.VERSION,"0000");
ret=  sprintf(ConfigV4->CURRVERSION.BLC.VERSION,"0000");
ret=  sprintf(ConfigV4->CURRVERSION.SSL.VERSION,"0000");
ret=  sprintf(ConfigV4->CURRVERSION.READERFW.VERSION,"0000");
ret=  sprintf(ConfigV4->MERCHANT.PASSWORD,"0000");
ret=  GetConfigTag("TX","SERIALNO", ConfigV4->TX.SERIALNO);
ret=  GetConfigTag("TX","SIGNONMAXTIME", ConfigV4->TX.SIGNONMAXTIME);
ret=  GetConfigTag("TX","OFFLINETXLIMIT", ConfigV4->TX.OFFLINETXLIMIT);
ret=  GetConfigTag("TX","FORCEONLINELIMIT", ConfigV4->TX.FORCEONLINELIMIT);
ret=  GetConfigTag("TX","MiniunitsADDVALUE", ConfigV4->TX.MiniunitsADDVALUE);
ret=  GetConfigTag("TX","OPERATIONMODE", ConfigV4->TX.OPERATIONMODE);

ret=  GetConfigTag("DEVICE","SSLEnable", ConfigV4->DEVICE.SSLEnable);
ret=  GetConfigTag("DEVICE","SAMSLOT", ConfigV4->DEVICE.SAMSLOT);
//ret=  GetConfigTag2("DEVICE","EDC","MechineID",gConfig.DEVICE.EDC.MechineID);

ret=  GetConfigTag2("DEVICE","READER","PORT", ConfigV4->DEVICE.READER.bPORT);
ret=  GetConfigTag2("DEVICE","READER","BAUDRATE", ConfigV4->DEVICE.READER.bBAUDRATE);
ret=  GetConfigTag2("DEVICE","READER","PARITY", ConfigV4->DEVICE.READER.bPARITY);
ret=  GetConfigTag2("DEVICE","READER","DATABITS", ConfigV4->DEVICE.READER.bDATABITS);
ret=  GetConfigTag2("DEVICE","READER","STOPBITS", ConfigV4->DEVICE.READER.bSTOPBITS);
ret=  GetConfigTag2("DEVICE","ECR","PORT", ConfigV4->DEVICE.ECR.bPORT);
ret=  GetConfigTag2("DEVICE","ECR","BAUDRATE", ConfigV4->DEVICE.ECR.bBAUDRATE);
ret=  GetConfigTag2("DEVICE","ECR","PARITY", ConfigV4->DEVICE.ECR.bPARITY);
ret=  GetConfigTag2("DEVICE","ECR","DATABITS", ConfigV4->DEVICE.ECR.bDATABITS);
ret=  GetConfigTag2("DEVICE","ECR","STOPBITS", ConfigV4->DEVICE.ECR.bSTOPBITS);

//ret=  GetConfigTag("TM","ID", ConfigV4->TM.ID);
ret=  GetConfigTag("TM","AgentNumber", ConfigV4->TM.AgentNumber);
ret=  GetConfigTag("TM","TITLE", ConfigV4->TM.TITLE);
ret=  GetConfigTag("TM","SUBTITLE", ConfigV4->TM.SUBTITLE);
ret=  GetConfigTag("TM","RECEIPTNUM", ConfigV4->TM.RECEIPTNUM);
ret=  GetConfigTag("TM","RECEIPTTYPE1", ConfigV4->TM.RECEIPTTYPE1);
ret=  GetConfigTag("TM","RECEIPTTYPE2",ConfigV4->TM.RECEIPTTYPE2);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING1", ConfigV4->TM.RECEIPTREMARK.STRING1);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING2", ConfigV4->TM.RECEIPTREMARK.STRING2);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING3", ConfigV4->TM.RECEIPTREMARK.STRING3);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING4", ConfigV4->TM.RECEIPTREMARK.STRING4);
ret=  GetConfigTag2("TM","RECEIPTREMARK","STRING5", ConfigV4->TM.RECEIPTREMARK.STRING5);


ret=  GetConfigTag2("ETHERNET","LOCAL","IP", ConfigV4->ETHERNET.LOCAL.IP);
ret=  GetConfigTag2("ETHERNET","LOCAL","MASK", ConfigV4->ETHERNET.LOCAL.MASK);
ret=  GetConfigTag2("ETHERNET","LOCAL","GATEWAY", ConfigV4->ETHERNET.LOCAL.GATEWAY);
ret=  GetConfigTag2("ETHERNET","LOCAL","DNS", ConfigV4->ETHERNET.LOCAL.DNS);
//ret=  GetConfigTag2("ETHERNET","LOCAL","MAC",gConfig.ETHERNET.LOCAL.MAC);

ret=  GetConfigTag("ETHERNET","CONNECTHOST", ConfigV4->ETHERNET.CONNECTHOST);
ret=  GetConfigTag("ETHERNET","NETWORKMODE", ConfigV4->ETHERNET.NETWORKMODE);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","HOST","URL", ConfigV4->ETHERNET.HOST_PRODUCTION.HOST.URL);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","HOST","VIPIP", ConfigV4->ETHERNET.HOST_PRODUCTION.HOST.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","HOST","IP", ConfigV4->ETHERNET.HOST_PRODUCTION.HOST.IP);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","HOST","PORT", ConfigV4->ETHERNET.HOST_PRODUCTION.HOST.PORT);

ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","URL", ConfigV4->ETHERNET.HOST_PRODUCTION.FTP.URL);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","IP", ConfigV4->ETHERNET.HOST_PRODUCTION.FTP.IP);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","VIPIP", ConfigV4->ETHERNET.HOST_PRODUCTION.FTP.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","LOGINID", ConfigV4->ETHERNET.HOST_PRODUCTION.FTP.LOGINID);
ret=  GetConfigTag3("ETHERNET","HOST_PRODUCTION","FTP","LOGINPASSWORD", ConfigV4->ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD);

ret=  GetConfigTag3("ETHERNET","HOST_TESTING","HOST","URL", ConfigV4->ETHERNET.HOST_TESTING.HOST.URL);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","HOST","IP", ConfigV4->ETHERNET.HOST_TESTING.HOST.IP);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","HOST","VIPIP", ConfigV4->ETHERNET.HOST_TESTING.HOST.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","HOST","PORT", ConfigV4->ETHERNET.HOST_TESTING.HOST.PORT);

ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","URL", ConfigV4->ETHERNET.HOST_TESTING.FTP.URL);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","IP", ConfigV4->ETHERNET.HOST_TESTING.FTP.IP);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","VIPIP", ConfigV4->ETHERNET.HOST_TESTING.FTP.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","LOGINID", ConfigV4->ETHERNET.HOST_TESTING.FTP.LOGINID);
ret=  GetConfigTag3("ETHERNET","HOST_TESTING","FTP","LOGINPASSWORD", ConfigV4->ETHERNET.HOST_TESTING.FTP.LOGINPASSWORD);

ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","HOST","URL", ConfigV4->ETHERNET.HOST_DEVELOP.HOST.URL);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","HOST","VIPIP", ConfigV4->ETHERNET.HOST_DEVELOP.HOST.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","HOST","IP", ConfigV4->ETHERNET.HOST_DEVELOP.HOST.IP);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","HOST","PORT", ConfigV4->ETHERNET.HOST_DEVELOP.HOST.PORT);

ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","URL", ConfigV4->ETHERNET.HOST_DEVELOP.FTP.URL);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","IP", ConfigV4->ETHERNET.HOST_DEVELOP.FTP.IP);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","VIPIP", ConfigV4->ETHERNET.HOST_DEVELOP.HOST.VIPIP);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","LOGINID", ConfigV4->ETHERNET.HOST_DEVELOP.FTP.LOGINID);
ret=  GetConfigTag3("ETHERNET","HOST_DEVELOP","FTP","LOGINPASSWORD", ConfigV4->ETHERNET.HOST_DEVELOP.FTP.LOGINPASSWORD);

return d_OK;
}


USHORT ConfigFuncion_GetInitData()
{
    
   memset(&gConfigFUNCTION,0x00,sizeof(FUNCTION_STRUCT));
  ezxml_t FunctionDATA = ezxml_parse_file(FunctionXML);
  ezxml_t FUNCTION,TYPE;
  int i=0;
  //for ( FUNCTION; FUNCTION = FUNCTION->sibling) {
  FUNCTION = ezxml_child(FunctionDATA, "TXFUNCTION");
  
  TYPE= FUNCTION->child;
  for(i=0;i<20;i++){
              
                if(TYPE==NULL) break;
                       memcpy( gConfigFUNCTION.TXFUNCTION[i].TagName,TYPE->name,strlen(TYPE->txt));

                       gConfigFUNCTION.TXFUNCTION[i].enable=atoi(ezxml_child(TYPE, "enable")->txt);
               
                       gConfigFUNCTION.TXFUNCTION[i].visible=atoi(ezxml_child(TYPE, "visible")->txt);                
                    
                       gConfigFUNCTION.TXFUNCTION[i].needpassword=atoi(ezxml_child(TYPE, "needpassword")->txt);
             
                        memcpy( gConfigFUNCTION.TXFUNCTION[i].itemname,ezxml_child(TYPE, "itemname")->txt,strlen(ezxml_child(TYPE, "itemname")->txt));
             
                        memcpy( gConfigFUNCTION.TXFUNCTION[i].password,ezxml_child(TYPE, "PASSWORD")->txt,strlen(ezxml_child(TYPE, "PASSWORD")->txt));
                TYPE= TYPE->sibling;
          
   } 
    
  ezxml_free(FunctionDATA);

return d_OK;
}

USHORT GetFunction(FUNCTION_STRUCT * Function)
{
    int i;
     for(i=0;i<20;i++){
         if(strcmp( gConfigFUNCTION.TXFUNCTION[i].TagName,Function->TagName)==0)
         {
             Function->enable= gConfigFUNCTION.TXFUNCTION[i].enable;
             Function->visible= gConfigFUNCTION.TXFUNCTION[i].visible;
             Function->needpassword= gConfigFUNCTION.TXFUNCTION[i].needpassword;
             memcpy( Function->itemname,gConfigFUNCTION.TXFUNCTION[i].itemname,strlen(gConfigFUNCTION.TXFUNCTION[i].itemname));
             memcpy( Function->password,gConfigFUNCTION.TXFUNCTION[i].password,strlen(gConfigFUNCTION.TXFUNCTION[i].password));
             
             return TRUE;
         }
     }
     return FALSE;
}
USHORT GetFunctionSwitch(BYTE * function)
{
    int i;
     for(i=0;i<20;i++){
         if(strcmp( gConfigFUNCTION.TXFUNCTION[i].TagName,function)==0)
         {
            if( gConfigFUNCTION.TXFUNCTION[i].enable==TRUE)
                return TRUE;
            else
                return FALSE;
         }     
     }
     return FALSE;
}
USHORT SetFunctionSwitch(BYTE * function,BOOL flag)
{
    int i;
     for(i=0;i<20;i++){
         if(strcmp( gConfigFUNCTION.TXFUNCTION[i].TagName,function)==0)
         {
              gConfigFUNCTION.TXFUNCTION[i].enable=flag;
                CTOS_WriteFile(FUNCTIONFile,(BYTE *)&gConfigFUNCTION,sizeof(gConfigFUNCTION)); 
              return d_OK;
         }     
     }
    
   
     ConfigFunction_GetData();
     return d_OK;
}
USHORT SetFunctionpPasswordSwitch(BYTE * function,BOOL flag)
{
    int i;
     for(i=0;i<20;i++){
         if(strcmp( gConfigFUNCTION.TXFUNCTION[i].TagName,function)==0)
         {
              gConfigFUNCTION.TXFUNCTION[i].needpassword=flag;
               CTOS_WriteFile(FUNCTIONFile,(BYTE *)&gConfigFUNCTION,sizeof(gConfigFUNCTION)); 
              return d_OK;
         }     
     }
   
     ConfigFunction_GetData();
     return d_OK;
} 
USHORT SetFunctionpPassword(unsigned char * function,unsigned char * pw)
{
    int i;
     for(i=0;i<20;i++){
         if(strcmp( gConfigFUNCTION.TXFUNCTION[i].TagName,function)==0)
         {
             
            strcpy( gConfigFUNCTION.TXFUNCTION[i].password,pw);
            CTOS_WriteFile(FUNCTIONFile,(BYTE *)&gConfigFUNCTION,sizeof(gConfigFUNCTION)); 
            return d_OK;
         }     
     }
     //CTOS_WriteFile(FUNCTIONFile,(BYTE *)&gConfigFUNCTION,sizeof(gConfigFUNCTION)); 
     return d_OK;
} 
USHORT CheckFunctionpPassword(BYTE * function,STR *pw)
{
    int i;
     for(i=0;i<20;i++){
         if(strcmp( gConfigFUNCTION.TXFUNCTION[i].TagName,function)==0)
         {
             if(strcmp(gConfigFUNCTION.TXFUNCTION[i].password,pw)!=0)
                 return FALSE;
             else
                 return TRUE;
         }
     }
  
} 
USHORT CheckFunctionpPasswordflag(BYTE * function)
{
    int i;
     for(i=0;i<20;i++){
         if(strcmp( gConfigFUNCTION.TXFUNCTION[i].TagName,function)==0)
         {
             if(  gConfigFUNCTION.TXFUNCTION[i].needpassword==FALSE)
                 return FALSE;
             else
                 return TRUE;
         }
     }
  
} 
USHORT ConfigFunction_GetData()
{
    USHORT ret=CheckConfigFunctionStatus(); 
    if(ret!=d_OK)
    {
       ret= ConfigFuncion_GetInitData();
       if(ret==d_OK){  
             ret= CTOS_WriteFile(FUNCTIONFile,(BYTE *)&gConfigFUNCTION,sizeof(gConfigFUNCTION)); 
          
       }
    } 
     return ret;
} 

USHORT Config_SetData()
{
  
  //USHORT ret= CTOS_WriteFile(ConfigV2File,(BYTE *)&gConfig,sizeof(ConfigV2_STRUCT)); 
 //USHORT ret= CTOS_WriteFile(ConfigV3File,(BYTE *)&gConfig,sizeof(ConfigV3_STRUCT)); 
 USHORT ret= CTOS_WriteFile(ConfigV4File,(BYTE *)&gConfig,sizeof(ConfigV4_STRUCT)); 
  
  
  
  return ret;
}


USHORT CheckConfigFunctionStatus()
{
  
    ULONG size=0;
    USHORT ret= CTOS_FileGetSize(FUNCTIONFile, &size);
    if(size!=sizeof( gConfigFUNCTION) )return d_Fail;
    size=sizeof( FUNCTION_TABLE_STRUCT);
    ret=CTOS_ReadFile(FUNCTIONFile,(BYTE *)&gConfigFUNCTION,&size);
    if(size!=sizeof( FUNCTION_TABLE_STRUCT) )return d_Fail;
    GetFunctionSetting();
   return d_OK;     
}/*
USHORT CheckConfig3Status()
{
  
    ULONG size=0;
    USHORT ret= CTOS_FileGetSize(ConfigData3File, &size);
    if(size!=sizeof( Config3_STRUCT) )return d_Fail;
    size=sizeof( Config3_STRUCT);
    ret=CTOS_ReadFile(ConfigData3File,(BYTE *)&gConfig3,&size);
    if(size!=sizeof( Config3_STRUCT) )return d_Fail;
 

 
   return d_OK;     
}
USHORT CheckConfig2Status()
{
   // Config2_STRUCT Config;
    ULONG size=0;
    USHORT ret= CTOS_FileGetSize(ConfigData2File, &size);
    if(size!=sizeof( Config2_STRUCT) )return d_Fail;
    size=sizeof( Config2_STRUCT);
    ret=CTOS_ReadFile(ConfigData2File,(BYTE *)&gConfig2,&size);
    if(size!=sizeof( Config2_STRUCT) )return d_Fail;
 
   // memcpy(&gConfig2,&Config,sizeof(Config2_STRUCT));
 
   return d_OK;     
}*/

/*
USHORT CheckConfigStatus()
{

    ConfigV2_STRUCT Config;
    ULONG size=0;
    USHORT ret= CTOS_FileGetSize(ConfigV2File, &size);
    if(size!=sizeof( gConfig) )return d_Fail;

    size=sizeof( gConfig);
    ret=CTOS_ReadFile(ConfigV2File,(BYTE *)&Config,&size);
    if(size!=sizeof( gConfig) )return d_Fail;

    if((strlen(Config.ETHERNET.COMM.HOST.URL)==0)&&
       (strlen(Config.ETHERNET.COMM.HOST.URLPORT)==0)&&     
       (strlen(Config.ETHERNET.COMM.HOST.PORT)==0)&&    
       (strlen(Config.ETHERNET.COMM.HOST.IP)==0))   
    {
        return d_Fail;
    }

    memcpy(&gConfig,&Config,sizeof(gConfig));

  //  ret=CheckConfig2Status();

   return ret;     
}
 */



USHORT CheckConfigStatusV4(void)
{
    ConfigV4_STRUCT Config;
    ULONG size=0;
    //檢查v4版參數是否存在
    USHORT ret= CTOS_FileGetSize(ConfigV4File, &size);
    if(size!=sizeof( ConfigV4_STRUCT) )return d_Fail;

    size=sizeof( ConfigV4_STRUCT);
    ret=CTOS_ReadFile(ConfigV4File,(BYTE *)&Config,&size);
    if(size!=sizeof( ConfigV4_STRUCT) )return d_Fail;

    if((strlen(Config.ETHERNET.HOST_PRODUCTION.HOST.URL)==0)&&
       (strlen(Config.ETHERNET.HOST_PRODUCTION.HOST.VIPIP)==0)&&     
       (strlen(Config.ETHERNET.HOST_PRODUCTION.HOST.PORT)==0)&&    
       (strlen(Config.ETHERNET.HOST_PRODUCTION.HOST.IP)==0))   
    {
        return d_Fail;
    }
  
    memcpy(&gConfig,&Config,sizeof(gConfig));
   return ret;     
}  




USHORT TransferConfigV1toV4(void)
{
  Config_STRUCT Configv1;ULONG size=0;
  USHORT ret= CTOS_FileGetSize(ConfigDataFile, &size);
    if(size!=sizeof( Config_STRUCT) )return d_Fail;
 size=sizeof( Config_STRUCT);
 ret=CTOS_ReadFile(ConfigDataFile,(BYTE *)&Configv1,&size);
  if(size==sizeof( Config_STRUCT) )
    {
               memcpy(&gConfig.CURRVERSION.AP.NAME,&Configv1.CURRVERSION.AP.NAME,sizeof(gConfig.CURRVERSION.AP.NAME));
               memcpy(&gConfig.CURRVERSION.AP.VERSION,&Configv1.CURRVERSION.AP.VERSION,sizeof(gConfig.CURRVERSION.AP.VERSION));
               memcpy(&gConfig.CURRVERSION.AP.Company,&Configv1.CURRVERSION.AP.Company,sizeof(gConfig.CURRVERSION.AP.Company));
               memcpy(&gConfig.CURRVERSION.AP.GeneratedDateTime,&Configv1.CURRVERSION.AP.GeneratedDateTime,sizeof(gConfig.CURRVERSION.AP.GeneratedDateTime));
               memcpy(&gConfig.CURRVERSION.AP.FTPPATH,&Configv1.CURRVERSION.AP.FTPPATH,sizeof(gConfig.CURRVERSION.AP.FTPPATH));
               
               memcpy(&gConfig.CURRVERSION.BLC.NAME,&Configv1.CURRVERSION.BLC.NAME,sizeof(gConfig.CURRVERSION.BLC.NAME));
               memcpy(&gConfig.CURRVERSION.BLC.VERSION,&Configv1.CURRVERSION.BLC.VERSION,sizeof(gConfig.CURRVERSION.BLC.VERSION));
               memcpy(&gConfig.CURRVERSION.BLC.TYPE,&Configv1.CURRVERSION.BLC.TYPE,sizeof(gConfig.CURRVERSION.BLC.TYPE));
               memcpy(&gConfig.CURRVERSION.BLC.UPDATETIME,&Configv1.CURRVERSION.BLC.UPDATETIME,sizeof(gConfig.CURRVERSION.BLC.UPDATETIME));
               memcpy(&gConfig.CURRVERSION.BLC.FTPPATH,&Configv1.CURRVERSION.BLC.FTPPATH,sizeof(gConfig.CURRVERSION.BLC.FTPPATH));
              
             
               memcpy(&gConfig.CURRVERSION.SSL.VERSION,&Configv1.CURRVERSION.SSL.VERSION,sizeof(gConfig.CURRVERSION.SSL.VERSION));
               memcpy(&gConfig.CURRVERSION.SSL.CAFILENAME1,&Configv1.CURRVERSION.SSL.CAFILENAME1,sizeof(gConfig.CURRVERSION.SSL.CAFILENAME1));
               memcpy(&gConfig.CURRVERSION.SSL.CAEXPIRYDAY1,&Configv1.CURRVERSION.SSL.CAEXPIRYDAY1,sizeof(gConfig.CURRVERSION.SSL.CAEXPIRYDAY1));
               memcpy(&gConfig.CURRVERSION.SSL.CAFILENAME2,&Configv1.CURRVERSION.SSL.CAFILENAME2,sizeof(gConfig.CURRVERSION.SSL.CAFILENAME2));
               memcpy(&gConfig.CURRVERSION.SSL.CAEXPIRYDAY2,&Configv1.CURRVERSION.SSL.CAEXPIRYDAY2,sizeof(gConfig.CURRVERSION.SSL.CAEXPIRYDAY2));
               memcpy(&gConfig.CURRVERSION.SSL.UPDATETIME,&Configv1.CURRVERSION.SSL.UPDATETIME,sizeof(gConfig.CURRVERSION.SSL.UPDATETIME));
               memcpy(&gConfig.CURRVERSION.SSL.FTPPATH,&Configv1.CURRVERSION.SSL.FTPPATH,sizeof(gConfig.CURRVERSION.SSL.FTPPATH));
               
               memcpy(&gConfig.TMS.AP.NAME,Configv1.CURRVERSION.AP.NAME,sizeof(gConfig.TMS.AP.NAME));
               memcpy(&gConfig.TMS.AP.VERSION,Configv1.CURRVERSION.AP.VERSION,sizeof(gConfig.TMS.AP.VERSION));
               memcpy(&gConfig.TMS.AP.Company,Configv1.CURRVERSION.AP.Company,sizeof(gConfig.TMS.AP.Company));
               memcpy(&gConfig.TMS.AP.GeneratedDateTime,Configv1.CURRVERSION.AP.GeneratedDateTime,sizeof(gConfig.TMS.AP.GeneratedDateTime));
               memcpy(&gConfig.TMS.AP.FTPPATH,Configv1.CURRVERSION.AP.FTPPATH,sizeof(gConfig.TMS.AP.FTPPATH));
               
               memcpy(&gConfig.TMS.BLC.NAME,&Configv1.TMS.BLC.NAME,sizeof(gConfig.TMS.BLC.NAME));
               memcpy(&gConfig.TMS.BLC.VERSION,&Configv1.TMS.BLC.VERSION,sizeof(gConfig.TMS.BLC.VERSION));
               memcpy(&gConfig.TMS.BLC.TYPE,&Configv1.TMS.BLC.TYPE,sizeof(gConfig.TMS.BLC.TYPE));
               memcpy(&gConfig.TMS.BLC.UPDATETIME,&Configv1.TMS.BLC.UPDATETIME,sizeof(gConfig.TMS.BLC.UPDATETIME));
               memcpy(&gConfig.TMS.BLC.FTPPATH,&Configv1.TMS.BLC.FTPPATH,sizeof(gConfig.TMS.BLC.FTPPATH));
              
             
               memcpy(&gConfig.TMS.SSL.VERSION,&Configv1.TMS.SSL.VERSION,sizeof(gConfig.TMS.SSL.VERSION));
               memcpy(&gConfig.TMS.SSL.CAFILENAME1,&Configv1.TMS.SSL.CAFILENAME1,sizeof(gConfig.TMS.SSL.CAFILENAME1));
               memcpy(&gConfig.TMS.SSL.CAEXPIRYDAY1,&Configv1.TMS.SSL.CAEXPIRYDAY1,sizeof(gConfig.TMS.SSL.CAEXPIRYDAY1));
               memcpy(&gConfig.TMS.SSL.CAFILENAME2,&Configv1.TMS.SSL.CAFILENAME2,sizeof(gConfig.TMS.SSL.CAFILENAME2));
               memcpy(&gConfig.TMS.SSL.CAEXPIRYDAY2,&Configv1.TMS.SSL.CAEXPIRYDAY2,sizeof(gConfig.TMS.SSL.CAEXPIRYDAY2));
               memcpy(&gConfig.TMS.SSL.UPDATETIME,&Configv1.TMS.SSL.UPDATETIME,sizeof(gConfig.TMS.SSL.UPDATETIME));
               memcpy(&gConfig.TMS.SSL.FTPPATH,&Configv1.TMS.SSL.FTPPATH,sizeof(gConfig.TMS.SSL.FTPPATH));
               memcpy(&gConfig.TMS.SSL.VERSION,&Configv1.TMS.SSL.VERSION,sizeof(gConfig.TMS.SSL.VERSION));
               
               memcpy(&gConfig.MERCHANT.MERCHANTID,&Configv1.MERCHANT.MERCHANTID,sizeof(gConfig.MERCHANT.MERCHANTID));
               memcpy(&gConfig.MERCHANT.NewLocationID,&Configv1.MERCHANT.NewLocationID,sizeof(gConfig.MERCHANT.NewLocationID));
               memcpy(&gConfig.MERCHANT.PASSWORD,&Configv1.MERCHANT.PASSWORD,sizeof(gConfig.MERCHANT.PASSWORD));
               memcpy(&gConfig.MERCHANT.STCODE,&Configv1.MERCHANT.STCODE,sizeof(gConfig.MERCHANT.STCODE));
               
               memcpy(&gConfig.TX.FORCEONLINELIMIT,&Configv1.TX.FORCEONLINELIMIT,sizeof(gConfig.TX.FORCEONLINELIMIT));
               memcpy(&gConfig.TX.OFFLINETXLIMIT,&Configv1.TX.OFFLINETXLIMIT,sizeof(gConfig.TX.OFFLINETXLIMIT));
               memcpy(&gConfig.TX.SERIALNO,&Configv1.TX.SERIALNO,sizeof(gConfig.TX.SERIALNO));
               memcpy(&gConfig.TX.SIGNONMAXTIME,&Configv1.TX.SIGNONMAXTIME,sizeof(gConfig.TX.SIGNONMAXTIME));
            
               memcpy(&gConfig.DEVICE.EDC.MechineID,&Configv1.DEVICE.EDC.MechineID,sizeof(gConfig.DEVICE.EDC.MechineID));
               memcpy(&gConfig.DEVICE.READER.bPORT,&Configv1.DEVICE.READER.bPORT,sizeof(gConfig.DEVICE.READER.bPORT));
               memcpy(&gConfig.DEVICE.READER.bBAUDRATE,&Configv1.DEVICE.READER.bBAUDRATE,sizeof(gConfig.DEVICE.READER.bBAUDRATE));
               memcpy(&gConfig.DEVICE.READER.bPARITY,&Configv1.DEVICE.READER.bPARITY,sizeof(gConfig.DEVICE.READER. bPARITY));
               memcpy(&gConfig.DEVICE.READER.bDATABITS,&Configv1.DEVICE.READER.bDATABITS,sizeof(gConfig.DEVICE.READER.bDATABITS));
               memcpy(&gConfig.DEVICE.READER.bSTOPBITS,&Configv1.DEVICE.READER.bSTOPBITS,sizeof(gConfig.DEVICE.READER.bSTOPBITS));
               memcpy(&gConfig.DEVICE.READER.bHostSpecVersionNo,&Configv1.DEVICE.READER.bHostSpecVersionNo,sizeof(gConfig.DEVICE.READER.bHostSpecVersionNo));
               memcpy(&gConfig.DEVICE.READER.bREADERID,&Configv1.DEVICE.READER.bREADERID,sizeof(gConfig.DEVICE.READER.bREADERID));
               memcpy(&gConfig.DEVICE.READER.bREADERFWVER,&Configv1.DEVICE.READER.bREADERFWVER,sizeof(gConfig.DEVICE.READER.bREADERFWVER));
               memcpy(&gConfig.DEVICE.READER.MIFARE_SAMID,&Configv1.DEVICE.READER.MIFARE_SAMID,sizeof(gConfig.DEVICE.READER.MIFARE_SAMID));
               memcpy(&gConfig.DEVICE.READER.MIFARE_SAMSN,&Configv1.DEVICE.READER.MIFARE_SAMSN,sizeof(gConfig.DEVICE.READER.MIFARE_SAMSN));
               memcpy(&gConfig.DEVICE.READER.MIFARE_DEVICEID,&Configv1.DEVICE.READER.MIFARE_DEVICEID,sizeof(gConfig.DEVICE.READER.MIFARE_DEVICEID));
               memcpy(&gConfig.DEVICE.READER.MIFARE_SAMKEYVER,&Configv1.DEVICE.READER.MIFARE_SAMKEYVER,sizeof(gConfig.DEVICE.READER.MIFARE_SAMKEYVER));
               memcpy(&gConfig.DEVICE.READER.CPU.CPUDEVICEID,&Configv1.DEVICE.READER.CPU.CPUDEVICEID,sizeof(gConfig.DEVICE.READER.CPU.CPUDEVICEID));
               memcpy(&gConfig.DEVICE.READER.CPU.SAMID,&Configv1.DEVICE.READER.CPU.SAMID,sizeof(gConfig.DEVICE.READER.CPU.SAMID));
               memcpy(&gConfig.DEVICE.READER.CPU.SAMVER,&Configv1.DEVICE.READER.CPU.SAMVER,sizeof(gConfig.DEVICE.READER.CPU.SAMVER));
               
               memcpy(&gConfig.TM.LocationID,&Configv1.TM.LocationID,sizeof(gConfig.TM.LocationID));
               memcpy(&gConfig.TM.LocationID,&Configv1.TM.LocationID,sizeof(gConfig.TM.LocationID));
//               memcpy(&gConfig.TM.bID,&Configv1.TM.ID,sizeof(gConfig.TM.bID));
               memcpy(&gConfig.TM.AgentNumber,&Configv1.TM.AgentNumber,sizeof(gConfig.TM.AgentNumber));
               memcpy(&gConfig.TM.TITLE,&Configv1.TM.TITLE,sizeof(gConfig.TM.TITLE));
               memcpy(&gConfig.TM.SUBTITLE,&Configv1.TM.SUBTITLE,sizeof(gConfig.TM.SUBTITLE));
               memcpy(&gConfig.TM.RECEIPTNUM,&Configv1.TM.RECEIPTNUM,sizeof(gConfig.TM.RECEIPTNUM));
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING1,&Configv1.TM.RECEIPTREMARK.STRING1,sizeof(gConfig.TM.RECEIPTREMARK.STRING1)); 
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING2,&Configv1.TM.RECEIPTREMARK.STRING2,sizeof(gConfig.TM.RECEIPTREMARK.STRING2)); 
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING3,&Configv1.TM.RECEIPTREMARK.STRING3,sizeof(gConfig.TM.RECEIPTREMARK.STRING3)); 
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING4,&Configv1.TM.RECEIPTREMARK.STRING4,sizeof(gConfig.TM.RECEIPTREMARK.STRING4));  
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING5,&Configv1.TM.RECEIPTREMARK.STRING5,sizeof(gConfig.TM.RECEIPTREMARK.STRING5));
               
              memcpy(&gConfig.BATCH.NO,&Configv1.BATCH.NO,sizeof(gConfig.BATCH.NO));
              
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP,&Configv1.ETHERNET.COMM.HOST.IP,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT,&Configv1.ETHERNET.COMM.HOST.PORT,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL,&Configv1.ETHERNET.COMM.HOST.URL,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP,&Configv1.ETHERNET.COMM.FTP.IP,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL,&Configv1.ETHERNET.COMM.FTP.URL,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT,&Configv1.ETHERNET.COMM.FTP.PORT,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID,&Configv1.ETHERNET.COMM.FTP.LOGINID,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD,&Configv1.ETHERNET.COMM.FTP.LOGINPASSWORD,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD));
          
             // remove(ConfigDataFile); remove by bruce at 2014/09/03
              CTOS_FileDelete(ConfigDataFile);
             }
                
             ret= CTOS_WriteFile(ConfigV4File,(BYTE *)&gConfig,sizeof(gConfig)); 
             return d_OK;
 }
 
USHORT TransferConfigV2toV4(void)
{
  ConfigV2_STRUCT Configv2;ULONG size=0;
   USHORT ret= CTOS_FileGetSize(ConfigV2File, &size);
   if(size!=sizeof( ConfigV2_STRUCT) )return d_Fail;
 
   size=sizeof( ConfigV2_STRUCT);
  ret=CTOS_ReadFile(ConfigV2File,(BYTE *)&Configv2,&size);
  if(size==sizeof( ConfigV2_STRUCT) )
    {
               memcpy(&gConfig.CURRVERSION.AP.NAME,&Configv2.CURRVERSION.AP.NAME,sizeof(gConfig.CURRVERSION.AP.NAME));
               memcpy(&gConfig.CURRVERSION.AP.VERSION,&Configv2.CURRVERSION.AP.VERSION,sizeof(gConfig.CURRVERSION.AP.VERSION));
               memcpy(&gConfig.CURRVERSION.AP.Company,&Configv2.CURRVERSION.AP.Company,sizeof(gConfig.CURRVERSION.AP.Company));
               memcpy(&gConfig.CURRVERSION.AP.GeneratedDateTime,&Configv2.CURRVERSION.AP.GeneratedDateTime,sizeof(gConfig.CURRVERSION.AP.GeneratedDateTime));
               memcpy(&gConfig.CURRVERSION.AP.FTPPATH,&Configv2.CURRVERSION.AP.FTPPATH,sizeof(gConfig.CURRVERSION.AP.FTPPATH));
               
               memcpy(&gConfig.CURRVERSION.BLC.NAME,&Configv2.CURRVERSION.BLC.NAME,sizeof(gConfig.CURRVERSION.BLC.NAME));
               memcpy(&gConfig.CURRVERSION.BLC.VERSION,&Configv2.CURRVERSION.BLC.VERSION,sizeof(gConfig.CURRVERSION.BLC.VERSION));
               memcpy(&gConfig.CURRVERSION.BLC.TYPE,&Configv2.CURRVERSION.BLC.TYPE,sizeof(gConfig.CURRVERSION.BLC.TYPE));
               memcpy(&gConfig.CURRVERSION.BLC.UPDATETIME,&Configv2.CURRVERSION.BLC.UPDATETIME,sizeof(gConfig.CURRVERSION.BLC.UPDATETIME));
               memcpy(&gConfig.CURRVERSION.BLC.FTPPATH,&Configv2.CURRVERSION.BLC.FTPPATH,sizeof(gConfig.CURRVERSION.BLC.FTPPATH));
              
             
               memcpy(&gConfig.CURRVERSION.SSL.VERSION,&Configv2.CURRVERSION.SSL.VERSION,sizeof(gConfig.CURRVERSION.SSL.VERSION));
               memcpy(&gConfig.CURRVERSION.SSL.CAFILENAME1,&Configv2.CURRVERSION.SSL.CAFILENAME1,sizeof(gConfig.CURRVERSION.SSL.CAFILENAME1));
               memcpy(&gConfig.CURRVERSION.SSL.CAEXPIRYDAY1,&Configv2.CURRVERSION.SSL.CAEXPIRYDAY1,sizeof(gConfig.CURRVERSION.SSL.CAEXPIRYDAY1));
               memcpy(&gConfig.CURRVERSION.SSL.CAFILENAME2,&Configv2.CURRVERSION.SSL.CAFILENAME2,sizeof(gConfig.CURRVERSION.SSL.CAFILENAME2));
               memcpy(&gConfig.CURRVERSION.SSL.CAEXPIRYDAY2,&Configv2.CURRVERSION.SSL.CAEXPIRYDAY2,sizeof(gConfig.CURRVERSION.SSL.CAEXPIRYDAY2));
               memcpy(&gConfig.CURRVERSION.SSL.UPDATETIME,&Configv2.CURRVERSION.SSL.UPDATETIME,sizeof(gConfig.CURRVERSION.SSL.UPDATETIME));
               memcpy(&gConfig.CURRVERSION.SSL.FTPPATH,&Configv2.CURRVERSION.SSL.FTPPATH,sizeof(gConfig.CURRVERSION.SSL.FTPPATH));
               
               memcpy(&gConfig.TMS.AP.NAME,Configv2.CURRVERSION.AP.NAME,sizeof(gConfig.TMS.AP.NAME));
               memcpy(&gConfig.TMS.AP.VERSION,Configv2.CURRVERSION.AP.VERSION,sizeof(gConfig.TMS.AP.VERSION));
               memcpy(&gConfig.TMS.AP.Company,Configv2.CURRVERSION.AP.Company,sizeof(gConfig.TMS.AP.Company));
               memcpy(&gConfig.TMS.AP.GeneratedDateTime,Configv2.CURRVERSION.AP.GeneratedDateTime,sizeof(gConfig.TMS.AP.GeneratedDateTime));
               memcpy(&gConfig.TMS.AP.FTPPATH,Configv2.CURRVERSION.AP.FTPPATH,sizeof(gConfig.TMS.AP.FTPPATH));
               
               memcpy(&gConfig.TMS.BLC.NAME,&Configv2.TMS.BLC.NAME,sizeof(gConfig.TMS.BLC.NAME));
               memcpy(&gConfig.TMS.BLC.VERSION,&Configv2.TMS.BLC.VERSION,sizeof(gConfig.TMS.BLC.VERSION));
               memcpy(&gConfig.TMS.BLC.TYPE,&Configv2.TMS.BLC.TYPE,sizeof(gConfig.TMS.BLC.TYPE));
               memcpy(&gConfig.TMS.BLC.UPDATETIME,&Configv2.TMS.BLC.UPDATETIME,sizeof(gConfig.TMS.BLC.UPDATETIME));
               memcpy(&gConfig.TMS.BLC.FTPPATH,&Configv2.TMS.BLC.FTPPATH,sizeof(gConfig.TMS.BLC.FTPPATH));
              
             
               memcpy(&gConfig.TMS.SSL.VERSION,&Configv2.TMS.SSL.VERSION,sizeof(gConfig.TMS.SSL.VERSION));
               memcpy(&gConfig.TMS.SSL.CAFILENAME1,&Configv2.TMS.SSL.CAFILENAME1,sizeof(gConfig.TMS.SSL.CAFILENAME1));
               memcpy(&gConfig.TMS.SSL.CAEXPIRYDAY1,&Configv2.TMS.SSL.CAEXPIRYDAY1,sizeof(gConfig.TMS.SSL.CAEXPIRYDAY1));
               memcpy(&gConfig.TMS.SSL.CAFILENAME2,&Configv2.TMS.SSL.CAFILENAME2,sizeof(gConfig.TMS.SSL.CAFILENAME2));
               memcpy(&gConfig.TMS.SSL.CAEXPIRYDAY2,&Configv2.TMS.SSL.CAEXPIRYDAY2,sizeof(gConfig.TMS.SSL.CAEXPIRYDAY2));
               memcpy(&gConfig.TMS.SSL.UPDATETIME,&Configv2.TMS.SSL.UPDATETIME,sizeof(gConfig.TMS.SSL.UPDATETIME));
               memcpy(&gConfig.TMS.SSL.FTPPATH,&Configv2.TMS.SSL.FTPPATH,sizeof(gConfig.TMS.SSL.FTPPATH));
               memcpy(&gConfig.TMS.SSL.VERSION,&Configv2.TMS.SSL.VERSION,sizeof(gConfig.TMS.SSL.VERSION));
               
               memcpy(&gConfig.MERCHANT.MERCHANTID,&Configv2.MERCHANT.MERCHANTID,sizeof(gConfig.MERCHANT.MERCHANTID));
               memcpy(&gConfig.MERCHANT.NewLocationID,&Configv2.MERCHANT.NewLocationID,sizeof(gConfig.MERCHANT.NewLocationID));
               memcpy(&gConfig.MERCHANT.PASSWORD,&Configv2.MERCHANT.PASSWORD,sizeof(gConfig.MERCHANT.PASSWORD));
               memcpy(&gConfig.MERCHANT.STCODE,&Configv2.MERCHANT.STCODE,sizeof(gConfig.MERCHANT.STCODE));
               
               memcpy(&gConfig.TX.FORCEONLINELIMIT,&Configv2.TX.FORCEONLINELIMIT,sizeof(gConfig.TX.FORCEONLINELIMIT));
               memcpy(&gConfig.TX.OFFLINETXLIMIT,&Configv2.TX.OFFLINETXLIMIT,sizeof(gConfig.TX.OFFLINETXLIMIT));
               memcpy(&gConfig.TX.SERIALNO,&Configv2.TX.SERIALNO,sizeof(gConfig.TX.SERIALNO));
               memcpy(&gConfig.TX.SIGNONMAXTIME,&Configv2.TX.SIGNONMAXTIME,sizeof(gConfig.TX.SIGNONMAXTIME));
              
               memcpy(&gConfig.DEVICE.EDC.MechineID,&Configv2.DEVICE.EDC.MechineID,sizeof(gConfig.DEVICE.EDC.MechineID));
               memcpy(&gConfig.DEVICE.READER.bPORT,&Configv2.DEVICE.READER.bPORT,sizeof(gConfig.DEVICE.READER.bPORT));
               memcpy(&gConfig.DEVICE.READER.bBAUDRATE,&Configv2.DEVICE.READER.bBAUDRATE,sizeof(gConfig.DEVICE.READER.bBAUDRATE));
               memcpy(&gConfig.DEVICE.READER.bPARITY,&Configv2.DEVICE.READER.bPARITY,sizeof(gConfig.DEVICE.READER. bPARITY));
               memcpy(&gConfig.DEVICE.READER.bDATABITS,&Configv2.DEVICE.READER.bDATABITS,sizeof(gConfig.DEVICE.READER.bDATABITS));
               memcpy(&gConfig.DEVICE.READER.bSTOPBITS,&Configv2.DEVICE.READER.bSTOPBITS,sizeof(gConfig.DEVICE.READER.bSTOPBITS));
               memcpy(&gConfig.DEVICE.READER.bHostSpecVersionNo,&Configv2.DEVICE.READER.bHostSpecVersionNo,sizeof(gConfig.DEVICE.READER.bHostSpecVersionNo));
               memcpy(&gConfig.DEVICE.READER.bREADERID,&Configv2.DEVICE.READER.bREADERID,sizeof(gConfig.DEVICE.READER.bREADERID));
               memcpy(&gConfig.DEVICE.READER.bREADERFWVER,&Configv2.DEVICE.READER.bREADERFWVER,sizeof(gConfig.DEVICE.READER.bREADERFWVER));
               memcpy(&gConfig.DEVICE.READER.MIFARE_SAMID,&Configv2.DEVICE.READER.MIFARE_SAMID,sizeof(gConfig.DEVICE.READER.MIFARE_SAMID));
               memcpy(&gConfig.DEVICE.READER.MIFARE_SAMSN,&Configv2.DEVICE.READER.MIFARE_SAMSN,sizeof(gConfig.DEVICE.READER.MIFARE_SAMSN));
               memcpy(&gConfig.DEVICE.READER.MIFARE_DEVICEID,&Configv2.DEVICE.READER.MIFARE_DEVICEID,sizeof(gConfig.DEVICE.READER.MIFARE_DEVICEID));
               memcpy(&gConfig.DEVICE.READER.MIFARE_SAMKEYVER,&Configv2.DEVICE.READER.MIFARE_SAMKEYVER,sizeof(gConfig.DEVICE.READER.MIFARE_SAMKEYVER));
               memcpy(&gConfig.DEVICE.READER.CPU.CPUDEVICEID,&Configv2.DEVICE.READER.CPU.CPUDEVICEID,sizeof(gConfig.DEVICE.READER.CPU.CPUDEVICEID));
               memcpy(&gConfig.DEVICE.READER.CPU.SAMID,&Configv2.DEVICE.READER.CPU.SAMID,sizeof(gConfig.DEVICE.READER.CPU.SAMID));
               memcpy(&gConfig.DEVICE.READER.CPU.SAMVER,&Configv2.DEVICE.READER.CPU.SAMVER,sizeof(gConfig.DEVICE.READER.CPU.SAMVER));
               
               memcpy(&gConfig.TM.LocationID,&Configv2.TM.LocationID,sizeof(gConfig.TM.LocationID));
               memcpy(&gConfig.TM.LocationID,&Configv2.TM.LocationID,sizeof(gConfig.TM.LocationID));
//               memcpy(&gConfig.TM.bID,&Configv2.TM.ID,sizeof(gConfig.TM.bID));
               memcpy(&gConfig.TM.AgentNumber,&Configv2.TM.AgentNumber,sizeof(gConfig.TM.AgentNumber));
               memcpy(&gConfig.TM.TITLE,&Configv2.TM.TITLE,sizeof(gConfig.TM.TITLE));
               memcpy(&gConfig.TM.SUBTITLE,&Configv2.TM.SUBTITLE,sizeof(gConfig.TM.SUBTITLE));
               memcpy(&gConfig.TM.RECEIPTNUM,&Configv2.TM.RECEIPTNUM,sizeof(gConfig.TM.RECEIPTNUM));
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING1,&Configv2.TM.RECEIPTREMARK.STRING1,sizeof(gConfig.TM.RECEIPTREMARK.STRING1)); 
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING2,&Configv2.TM.RECEIPTREMARK.STRING2,sizeof(gConfig.TM.RECEIPTREMARK.STRING2)); 
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING3,&Configv2.TM.RECEIPTREMARK.STRING3,sizeof(gConfig.TM.RECEIPTREMARK.STRING3)); 
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING4,&Configv2.TM.RECEIPTREMARK.STRING4,sizeof(gConfig.TM.RECEIPTREMARK.STRING4));  
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING5,&Configv2.TM.RECEIPTREMARK.STRING5,sizeof(gConfig.TM.RECEIPTREMARK.STRING5));
               
              memcpy(&gConfig.BATCH.NO,&Configv2.BATCH.NO,sizeof(gConfig.BATCH.NO));
              
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP,&Configv2.ETHERNET.COMM.HOST.IP,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT,&Configv2.ETHERNET.COMM.HOST.PORT,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL,&Configv2.ETHERNET.COMM.HOST.URL,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP,&Configv2.ETHERNET.COMM.FTP.IP,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL,&Configv2.ETHERNET.COMM.FTP.URL,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT,&Configv2.ETHERNET.COMM.FTP.PORT,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID,&Configv2.ETHERNET.COMM.FTP.LOGINID,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD,&Configv2.ETHERNET.COMM.FTP.LOGINPASSWORD,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD));
          
                // remove(ConfigV2File); remove by bruce at 2014/09/03
              CTOS_FileDelete(ConfigV2File);
         
             }
                
             ret= CTOS_WriteFile(ConfigV4File,(BYTE *)&gConfig,sizeof(gConfig)); 
             return d_OK;
 }

USHORT TransferConfigV3toV4(void)
{
  ConfigV3_STRUCT Configv3;ULONG size=0;
   USHORT ret= CTOS_FileGetSize(ConfigV3File, &size);
   if(size!=sizeof( ConfigV3_STRUCT) )return d_Fail;
 
   size=sizeof( ConfigV4_STRUCT);
   size=sizeof( ConfigV3_STRUCT);
   
  ret=CTOS_ReadFile(ConfigV3File,(BYTE *)&Configv3,&size);
  if(size==sizeof( ConfigV3_STRUCT) )
    {
               memcpy(&gConfig.CURRVERSION.AP.NAME,&Configv3.CURRVERSION.AP.NAME,sizeof(gConfig.CURRVERSION.AP.NAME));
               memcpy(&gConfig.CURRVERSION.AP.VERSION,&Configv3.CURRVERSION.AP.VERSION,sizeof(gConfig.CURRVERSION.AP.VERSION));
               memcpy(&gConfig.CURRVERSION.AP.Company,&Configv3.CURRVERSION.AP.Company,sizeof(gConfig.CURRVERSION.AP.Company));
               memcpy(&gConfig.CURRVERSION.AP.GeneratedDateTime,&Configv3.CURRVERSION.AP.GeneratedDateTime,sizeof(gConfig.CURRVERSION.AP.GeneratedDateTime));
               memcpy(&gConfig.CURRVERSION.AP.FTPPATH,&Configv3.CURRVERSION.AP.FTPPATH,sizeof(gConfig.CURRVERSION.AP.FTPPATH));
               
               memcpy(&gConfig.CURRVERSION.BLC.NAME,&Configv3.CURRVERSION.BLC.NAME,sizeof(gConfig.CURRVERSION.BLC.NAME));
               memcpy(&gConfig.CURRVERSION.BLC.VERSION,&Configv3.CURRVERSION.BLC.VERSION,sizeof(gConfig.CURRVERSION.BLC.VERSION));
               memcpy(&gConfig.CURRVERSION.BLC.TYPE,&Configv3.CURRVERSION.BLC.TYPE,sizeof(gConfig.CURRVERSION.BLC.TYPE));
               memcpy(&gConfig.CURRVERSION.BLC.UPDATETIME,&Configv3.CURRVERSION.BLC.UPDATETIME,sizeof(gConfig.CURRVERSION.BLC.UPDATETIME));
               memcpy(&gConfig.CURRVERSION.BLC.FTPPATH,&Configv3.CURRVERSION.BLC.FTPPATH,sizeof(gConfig.CURRVERSION.BLC.FTPPATH));
              
             
               memcpy(&gConfig.CURRVERSION.SSL.VERSION,&Configv3.CURRVERSION.SSL.VERSION,sizeof(gConfig.CURRVERSION.SSL.VERSION));
               memcpy(&gConfig.CURRVERSION.SSL.CAFILENAME1,&Configv3.CURRVERSION.SSL.CAFILENAME1,sizeof(gConfig.CURRVERSION.SSL.CAFILENAME1));
               memcpy(&gConfig.CURRVERSION.SSL.CAEXPIRYDAY1,&Configv3.CURRVERSION.SSL.CAEXPIRYDAY1,sizeof(gConfig.CURRVERSION.SSL.CAEXPIRYDAY1));
               memcpy(&gConfig.CURRVERSION.SSL.CAFILENAME2,&Configv3.CURRVERSION.SSL.CAFILENAME2,sizeof(gConfig.CURRVERSION.SSL.CAFILENAME2));
               memcpy(&gConfig.CURRVERSION.SSL.CAEXPIRYDAY2,&Configv3.CURRVERSION.SSL.CAEXPIRYDAY2,sizeof(gConfig.CURRVERSION.SSL.CAEXPIRYDAY2));
               memcpy(&gConfig.CURRVERSION.SSL.UPDATETIME,&Configv3.CURRVERSION.SSL.UPDATETIME,sizeof(gConfig.CURRVERSION.SSL.UPDATETIME));
               memcpy(&gConfig.CURRVERSION.SSL.FTPPATH,&Configv3.CURRVERSION.SSL.FTPPATH,sizeof(gConfig.CURRVERSION.SSL.FTPPATH));
               
               memcpy(&gConfig.TMS.AP.NAME,Configv3.CURRVERSION.AP.NAME,sizeof(gConfig.TMS.AP.NAME));
               memcpy(&gConfig.TMS.AP.VERSION,Configv3.CURRVERSION.AP.VERSION,sizeof(gConfig.TMS.AP.VERSION));
               memcpy(&gConfig.TMS.AP.Company,Configv3.CURRVERSION.AP.Company,sizeof(gConfig.TMS.AP.Company));
               memcpy(&gConfig.TMS.AP.GeneratedDateTime,Configv3.CURRVERSION.AP.GeneratedDateTime,sizeof(gConfig.TMS.AP.GeneratedDateTime));
               memcpy(&gConfig.TMS.AP.FTPPATH,Configv3.CURRVERSION.AP.FTPPATH,sizeof(gConfig.TMS.AP.FTPPATH));
               
               memcpy(&gConfig.TMS.BLC.NAME,&Configv3.TMS.BLC.NAME,sizeof(gConfig.TMS.BLC.NAME));
               memcpy(&gConfig.TMS.BLC.VERSION,&Configv3.TMS.BLC.VERSION,sizeof(gConfig.TMS.BLC.VERSION));
               memcpy(&gConfig.TMS.BLC.TYPE,&Configv3.TMS.BLC.TYPE,sizeof(gConfig.TMS.BLC.TYPE));
               memcpy(&gConfig.TMS.BLC.UPDATETIME,&Configv3.TMS.BLC.UPDATETIME,sizeof(gConfig.TMS.BLC.UPDATETIME));
               memcpy(&gConfig.TMS.BLC.FTPPATH,&Configv3.TMS.BLC.FTPPATH,sizeof(gConfig.TMS.BLC.FTPPATH));
              
             
               memcpy(&gConfig.TMS.SSL.VERSION,&Configv3.TMS.SSL.VERSION,sizeof(gConfig.TMS.SSL.VERSION));
               memcpy(&gConfig.TMS.SSL.CAFILENAME1,&Configv3.TMS.SSL.CAFILENAME1,sizeof(gConfig.TMS.SSL.CAFILENAME1));
               memcpy(&gConfig.TMS.SSL.CAEXPIRYDAY1,&Configv3.TMS.SSL.CAEXPIRYDAY1,sizeof(gConfig.TMS.SSL.CAEXPIRYDAY1));
               memcpy(&gConfig.TMS.SSL.CAFILENAME2,&Configv3.TMS.SSL.CAFILENAME2,sizeof(gConfig.TMS.SSL.CAFILENAME2));
               memcpy(&gConfig.TMS.SSL.CAEXPIRYDAY2,&Configv3.TMS.SSL.CAEXPIRYDAY2,sizeof(gConfig.TMS.SSL.CAEXPIRYDAY2));
               memcpy(&gConfig.TMS.SSL.UPDATETIME,&Configv3.TMS.SSL.UPDATETIME,sizeof(gConfig.TMS.SSL.UPDATETIME));
               memcpy(&gConfig.TMS.SSL.FTPPATH,&Configv3.TMS.SSL.FTPPATH,sizeof(gConfig.TMS.SSL.FTPPATH));
               memcpy(&gConfig.TMS.SSL.VERSION,&Configv3.TMS.SSL.VERSION,sizeof(gConfig.TMS.SSL.VERSION));
               
               memcpy(&gConfig.MERCHANT.MERCHANTID,&Configv3.MERCHANT.MERCHANTID,sizeof(gConfig.MERCHANT.MERCHANTID));
               memcpy(&gConfig.MERCHANT.NewLocationID,&Configv3.MERCHANT.NewLocationID,sizeof(gConfig.MERCHANT.NewLocationID));
               memcpy(&gConfig.MERCHANT.PASSWORD,&Configv3.MERCHANT.PASSWORD,sizeof(gConfig.MERCHANT.PASSWORD));
               memcpy(&gConfig.MERCHANT.STCODE,&Configv3.MERCHANT.STCODE,sizeof(gConfig.MERCHANT.STCODE));
               
               memcpy(&gConfig.TX.FORCEONLINELIMIT,&Configv3.TX.FORCEONLINELIMIT,sizeof(gConfig.TX.FORCEONLINELIMIT));
               memcpy(&gConfig.TX.OFFLINETXLIMIT,&Configv3.TX.OFFLINETXLIMIT,sizeof(gConfig.TX.OFFLINETXLIMIT));
               memcpy(&gConfig.TX.SERIALNO,&Configv3.TX.SERIALNO,sizeof(gConfig.TX.SERIALNO));
               memcpy(&gConfig.TX.SIGNONMAXTIME,&Configv3.TX.SIGNONMAXTIME,sizeof(gConfig.TX.SIGNONMAXTIME));
              
               memcpy(&gConfig.DEVICE.EDC.MechineID,&Configv3.DEVICE.EDC.MechineID,sizeof(gConfig.DEVICE.EDC.MechineID));
               memcpy(&gConfig.DEVICE.READER.bPORT,&Configv3.DEVICE.READER.bPORT,sizeof(gConfig.DEVICE.READER.bPORT));
               memcpy(&gConfig.DEVICE.READER.bBAUDRATE,&Configv3.DEVICE.READER.bBAUDRATE,sizeof(gConfig.DEVICE.READER.bBAUDRATE));
               memcpy(&gConfig.DEVICE.READER.bPARITY,&Configv3.DEVICE.READER.bPARITY,sizeof(gConfig.DEVICE.READER. bPARITY));
               memcpy(&gConfig.DEVICE.READER.bDATABITS,&Configv3.DEVICE.READER.bDATABITS,sizeof(gConfig.DEVICE.READER.bDATABITS));
               memcpy(&gConfig.DEVICE.READER.bSTOPBITS,&Configv3.DEVICE.READER.bSTOPBITS,sizeof(gConfig.DEVICE.READER.bSTOPBITS));
               memcpy(&gConfig.DEVICE.READER.bHostSpecVersionNo,&Configv3.DEVICE.READER.bHostSpecVersionNo,sizeof(gConfig.DEVICE.READER.bHostSpecVersionNo));
               memcpy(&gConfig.DEVICE.READER.bREADERID,&Configv3.DEVICE.READER.bREADERID,sizeof(gConfig.DEVICE.READER.bREADERID));
               memcpy(&gConfig.DEVICE.READER.bREADERFWVER,&Configv3.DEVICE.READER.bREADERFWVER,sizeof(gConfig.DEVICE.READER.bREADERFWVER));
               memcpy(&gConfig.DEVICE.READER.MIFARE_SAMID,&Configv3.DEVICE.READER.MIFARE_SAMID,sizeof(gConfig.DEVICE.READER.MIFARE_SAMID));
               memcpy(&gConfig.DEVICE.READER.MIFARE_SAMSN,&Configv3.DEVICE.READER.MIFARE_SAMSN,sizeof(gConfig.DEVICE.READER.MIFARE_SAMSN));
               memcpy(&gConfig.DEVICE.READER.MIFARE_DEVICEID,&Configv3.DEVICE.READER.MIFARE_DEVICEID,sizeof(gConfig.DEVICE.READER.MIFARE_DEVICEID));
               memcpy(&gConfig.DEVICE.READER.MIFARE_SAMKEYVER,&Configv3.DEVICE.READER.MIFARE_SAMKEYVER,sizeof(gConfig.DEVICE.READER.MIFARE_SAMKEYVER));
               memcpy(&gConfig.DEVICE.READER.CPU.CPUDEVICEID,&Configv3.DEVICE.READER.CPU.CPUDEVICEID,sizeof(gConfig.DEVICE.READER.CPU.CPUDEVICEID));
               memcpy(&gConfig.DEVICE.READER.CPU.SAMID,&Configv3.DEVICE.READER.CPU.SAMID,sizeof(gConfig.DEVICE.READER.CPU.SAMID));
               memcpy(&gConfig.DEVICE.READER.CPU.SAMVER,&Configv3.DEVICE.READER.CPU.SAMVER,sizeof(gConfig.DEVICE.READER.CPU.SAMVER));
               
               memcpy(&gConfig.TM.LocationID,&Configv3.TM.LocationID,sizeof(gConfig.TM.LocationID));
               memcpy(&gConfig.TM.LocationID,&Configv3.TM.LocationID,sizeof(gConfig.TM.LocationID));
//               memcpy(&gConfig.TM.bID,&Configv3.TM.ID,sizeof(gConfig.TM.bID));
               memcpy(&gConfig.TM.AgentNumber,&Configv3.TM.AgentNumber,sizeof(gConfig.TM.AgentNumber));
               memcpy(&gConfig.TM.TITLE,&Configv3.TM.TITLE,sizeof(gConfig.TM.TITLE));
               memcpy(&gConfig.TM.SUBTITLE,&Configv3.TM.SUBTITLE,sizeof(gConfig.TM.SUBTITLE));
               memcpy(&gConfig.TM.RECEIPTNUM,&Configv3.TM.RECEIPTNUM,sizeof(gConfig.TM.RECEIPTNUM));
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING1,&Configv3.TM.RECEIPTREMARK.STRING1,sizeof(gConfig.TM.RECEIPTREMARK.STRING1)); 
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING2,&Configv3.TM.RECEIPTREMARK.STRING2,sizeof(gConfig.TM.RECEIPTREMARK.STRING2)); 
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING3,&Configv3.TM.RECEIPTREMARK.STRING3,sizeof(gConfig.TM.RECEIPTREMARK.STRING3)); 
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING4,&Configv3.TM.RECEIPTREMARK.STRING4,sizeof(gConfig.TM.RECEIPTREMARK.STRING4));  
               memcpy(&gConfig.TM.RECEIPTREMARK.STRING5,&Configv3.TM.RECEIPTREMARK.STRING5,sizeof(gConfig.TM.RECEIPTREMARK.STRING5));
               
              memcpy(&gConfig.BATCH.NO,&Configv3.BATCH.NO,sizeof(gConfig.BATCH.NO));
              
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP,&Configv3.ETHERNET.HOST_PRODUCTION.HOST.IP,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT,&Configv3.ETHERNET.HOST_PRODUCTION.HOST.PORT,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL,&Configv3.ETHERNET.HOST_PRODUCTION.HOST.URL,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP,&Configv3.ETHERNET.HOST_PRODUCTION.FTP.IP,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL,&Configv3.ETHERNET.HOST_PRODUCTION.FTP.URL,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT,&Configv3.ETHERNET.HOST_PRODUCTION.FTP.PORT,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.PORT));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID,&Configv3.ETHERNET.HOST_PRODUCTION.FTP.LOGINID,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINID));
              memcpy(&gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD,&Configv3.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD,sizeof(gConfig.ETHERNET.HOST_PRODUCTION.FTP.LOGINPASSWORD));
          
              //V4 added
              memcpy(&gConfig.ETHERNET.CONNECTHOST ,&Configv3.ETHERNET.CONNECTHOST,sizeof(gConfig.ETHERNET.CONNECTHOST));
                      
              // remove(ConfigV3File); remove by bruce at 2014/09/03
              CTOS_FileDelete(ConfigV3File);
             }
                
             ret= CTOS_WriteFile(ConfigV4File,(BYTE *)&gConfig,sizeof(gConfig)); 
             return d_OK;
 }
/*
USHORT Config_GetData()
{
    ULONG size;
   
    USHORT  ret=CheckConfigStatusV4();
    if(ret!=d_OK)
    {
       ret=ConfigV4_GetInitData(&gConfig);
       ret= TransferConfigV1toV4();
       ret= TransferConfigV2toV4();
       ret= TransferConfigV3toV4();
    }
     ret= CTOS_WriteFile(ConfigV4File,(BYTE *)&gConfig,sizeof(ConfigV4_STRUCT)); 
   return ret;
}
*/
