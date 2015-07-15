#include "ECCAPP.h"

void parse_ResponseCode(STR *TYPE)
{
  
   BYTE ResponseCodeData[30*1024];
   int offset=0;
  // char *actionstr, *numstr;
  // char *msgstr1,*msgstr2,*msgstr3;
   ULONG filelen =File_GetLen(ResponseCodeFile);   
   memset(ResponseCodeData,0x00,sizeof(ResponseCodeData));
   USHORT usRet=usReadFileData2(ResponseCodeFile,offset,&filelen,ResponseCodeData);   
   ResponseCode_STRUCT * RESPCODE;
   if(strcmp(TYPE,"AP")==0){
       RESPCODE=AP_RESPCODE;
   }else if(strcmp(TYPE,"CMAS")==0){
        RESPCODE=CMAS_RESPCODE;
   }else if(strcmp(TYPE,"READER")==0){
        RESPCODE=READER_RESPCODE;
   }else if(strcmp(TYPE,"ECR")==0){
        RESPCODE=ECR_RESPCODE;
   }else if(strcmp(TYPE,"SVCS")==0){
        RESPCODE=SVCS_RESPCODE;
   }
   ezxml_t ResponseCode=ezxml_parse_str(ResponseCodeData, sizeof(ResponseCodeData));
   ezxml_t codeNode= ezxml_get(ResponseCode,TYPE,-1);
   codeNode=codeNode->child;
   int i=0;
    while(codeNode!=NULL)
    {   
        memset(&RESPCODE[i],0x00,sizeof(ResponseCode_STRUCT));
        strcpy( RESPCODE[i].Element,codeNode->name);
        strcpy( RESPCODE[i].NUMCODE, (char*)ezxml_attr(codeNode,(const char *)"num"));   
        strcpy( RESPCODE[i].ACTIONCODE, (char*)ezxml_attr(codeNode,(const char *)"action"));   
        ezxml_t String1Node= ezxml_get(codeNode,"STRING1",-1);
        if(String1Node!=NULL){
               strcpy( RESPCODE[i].STRING1, String1Node->txt);
               
        }
         ezxml_t String2Node= ezxml_get(codeNode,"STRING2",-1);
        if(String2Node!=NULL)
               strcpy( RESPCODE[i].STRING2, String2Node->txt);
        
         ezxml_t String3Node= ezxml_get(codeNode,"STRING3",-1);
        if(String3Node!=NULL)
               strcpy( RESPCODE[i].STRING3,String3Node->txt);
           
         i++;
        codeNode=codeNode->sibling;
    }
   ezxml_free(ResponseCode);
 
   return ;
   
}

USHORT ECC_CheckAPResponseCode(USHORT Respcode)
{
    char tmp[10];
    BYTE str[32];
    memset(tmp,0x00,sizeof(tmp));
    memset(str,0x00,sizeof(str));
     sprintf(tmp,"CODE%04x",Respcode);
    vdToUpper(str,tmp);
    return ECC_CheckResponseCode("AP", (BYTE *)str);
}
USHORT ECC_CheckReaderResponseCode(USHORT Respcode)
{
     char tmp[10];
    char str[32];
    memset(tmp,0x00,sizeof(tmp));
    memset(str,0x00,sizeof(str));
    sprintf(tmp,"CODE%02x",Respcode);
    vdToUpper(str,tmp);
    return ECC_CheckResponseCode("READER", str);
}
USHORT ECC_CheckCMASResponseCode(BYTE * Respcode)
{
    char tmp[10];
    char str[32];
    USHORT rspcode=atoi(Respcode);  
    
    memset(tmp,0x00,sizeof(tmp));
    sprintf(tmp,"CODE%02d",rspcode);
    memset(str,0x00,sizeof(str));  
    vdToUpper(str,tmp);
     
    return ECC_CheckResponseCode("CMAS", str);
}
USHORT ECC_CheckSVCSResponseCode(BYTE *Respcode)
{ 
    char tmp[10];
    char str[32];
    memset(tmp,0x00,sizeof(tmp));
    memset(str,0x00,sizeof(str));
       sprintf(tmp,"CODE00%s",Respcode);
    vdToUpper(str,tmp);
    return ECC_CheckResponseCode("SVCS", str);
}
USHORT ECC_CheckResponseCode(STR * TYPE, BYTE * Respcode)
{
    USHORT ret;
   USHORT mkHWSupport;
    SystemLog("CheckResponseCode","Start");
    char line1[64],line2[64],line3[64],line4[64];
   
  
    memset(line1,0x00,sizeof(line1));
    memset(line2,0x00,sizeof(line2));
    memset(line3,0x00,sizeof(line3));
  
 
    ResponseCode_STRUCT * RESPCODE;
   if(strcmp(TYPE,"AP")==0){
       RESPCODE=AP_RESPCODE;
   }else if(strcmp(TYPE,"CMAS")==0){
       
        RESPCODE=CMAS_RESPCODE;
   }else if(strcmp(TYPE,"READER")==0){
        
        RESPCODE=READER_RESPCODE;
   }else if(strcmp(TYPE,"ECR")==0){
        RESPCODE=ECR_RESPCODE;
   }else if(strcmp(TYPE,"SVCS")==0){
    
        RESPCODE=SVCS_RESPCODE;
   } 
    
   int i=0;
   while(strlen(RESPCODE[i].Element)>0){
       if(strcmp(RESPCODE[i].Element,Respcode)==0)
       {
            if(strcmp(RESPCODE[i].ACTIONCODE,"OK")==0)
            {  
                
                return d_OK;
            }else if((strcmp(RESPCODE[i].ACTIONCODE,"LOCK")==0)||(strcmp(RESPCODE[i].ACTIONCODE,"LOCKCARD")==0)){
                SystemLog("CheckResponseCode",Respcode);
               if(strcmp(TYPE,"READER")==0){
                   // Reader_ERR_LED();
                    mkHWSupport=Eth_CheckDeviceSupport();
                    if(( mkHWSupport & d_MK_HW_CONTACTLESS)==d_MK_HW_CONTACTLESS)
                    {   
                         CTOS_CLLEDSet(0x0f, d_CL_LED_RED);
                    }
                }
                BYTE ucCardID[7];
                memset(ucCardID,0x00,sizeof(ucCardID));
                gucLockReason=0x03;
                memcpy(ucCardID,gTransData.ucCardID,7);
                iProcess_LockCard(ucCardID);
                ret=d_ERR_RESP_LOCKCARD;
            }else if(strcmp(RESPCODE[i].ACTIONCODE,"RETRY")==0){   
                 SystemLog("CheckResponseCode",Respcode);
                 ret=d_ERR_RESP_RETRY;
            }else if(strcmp(RESPCODE[i].ACTIONCODE,"SVCS")==0){
              
                ECC_CheckSVCSResponseCode(gTransData.ucSVCSResponseCode);
          
                  return ret;
            }else if(strcmp(RESPCODE[i].ACTIONCODE,"REBOOT")==0){
                ret=d_ERR_RESP_REBOOT;
            }else if(strcmp(RESPCODE[i].ACTIONCODE,"REJECT")==0){ 
                if(strcmp(TYPE,"READER")==0){
                     // Reader_ERR_LED();
                    mkHWSupport=Eth_CheckDeviceSupport();
                    if(( mkHWSupport & d_MK_HW_CONTACTLESS)==d_MK_HW_CONTACTLESS)
                    {   
                         CTOS_CLLEDSet(0x0f, d_CL_LED_RED);
                    }
                }
                ret=d_ERR_RESP_REJECT;
            }else if(strcmp(RESPCODE[i].ACTIONCODE,"SECURTERR")==0){    
                if(strcmp(TYPE,"READER")==0){
                     // Reader_ERR_LED();
                    mkHWSupport=Eth_CheckDeviceSupport();
                    if(( mkHWSupport & d_MK_HW_CONTACTLESS)==d_MK_HW_CONTACTLESS)
                    {   
                         CTOS_CLLEDSet(0x0f, d_CL_LED_RED);
                    }
                }
                 ret=d_ERR_RESP_SECURTERR;   
            }else if(strcmp(RESPCODE[i].ACTIONCODE,"SECURTERR2")==0){ 
                if(strcmp(TYPE,"READER")==0){
                    // Reader_ERR_LED();
                    mkHWSupport=Eth_CheckDeviceSupport();
                    if(( mkHWSupport & d_MK_HW_CONTACTLESS)==d_MK_HW_CONTACTLESS)
                    {   
                         CTOS_CLLEDSet(0x0f, d_CL_LED_RED);
                    }
                }
                BYTE tmp[2+1];
                gConfig.DEVICE.READER.bREADERSTATUS=READERSTATUS_LOCK;
                sprintf(tmp,"%d", gConfig.DEVICE.READER.bREADERSTATUS);
                ret= ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE","READER","READERSTATUS",(STR *)tmp);
              
                ret=d_ERR_RESP_SECURTERR;   
            }else if(strcmp(RESPCODE[i].ACTIONCODE,"SIGNON")==0){    
                 ret=d_ERR_RESP_SIGNON;       
            }else{          
                  if(strcmp(TYPE,"READER")==0){
                     // Reader_ERR_LED();
                    mkHWSupport=Eth_CheckDeviceSupport();
                    if(( mkHWSupport & d_MK_HW_CONTACTLESS)==d_MK_HW_CONTACTLESS)
                    {   
                         CTOS_CLLEDSet(0x0f, d_CL_LED_RED);
                    }
                }
                  ret=d_ERR_RESP_REJECT;
            }

          sprintf(line1,"%s",RESPCODE[i].STRING1); 
          sprintf(line2,"%s",RESPCODE[i].STRING2); 
          sprintf(line3,"%s",RESPCODE[i].STRING3); 
          sprintf(line4,"錯誤代碼:%s",RESPCODE[i].NUMCODE);
          if((strcmp(gConfig.TX.OPERATIONMODE,"AUTO_BYTYPE")==0)||(strcmp(gConfig.TX.OPERATIONMODE,"AUTO_FIX")==0))
              ErrorMessageBox("錯誤訊息",line1,line2,line3,line4,Type_wait2sec);
          else
              ErrorMessageBox("錯誤訊息",line1,line2,line3,line4,d_MB_CHECK);
          if(ecrObj.gData.isEcrTxn){
               if(strlen(ecrObj.ngData->errMsg)==0)       
                   sprintf(ecrObj.ngData->errMsg,"%s!%s!%s!%s",line1,line2,line3,line4);
           }
           return ret; 
       }else{
           i++;
       }
   }
   if(strcmp(TYPE,"READER")==0){
       // Reader_ERR_LED();
       mkHWSupport=Eth_CheckDeviceSupport();
       if(( mkHWSupport & d_MK_HW_CONTACTLESS)==d_MK_HW_CONTACTLESS)
       {   
          CTOS_CLLEDSet(0x0f, d_CL_LED_RED);
       }
   }
   SystemLog("CheckResponseCode","XML Get RESPONSE CODE FAIL.");
   SystemLog("UNDEFINEDRESPOSECODE",Respcode);
          
   sprintf(line4,"錯誤代碼:%s",Respcode);
   if((strcmp(gConfig.TX.OPERATIONMODE,"AUTO_BYTYPE")==0)||(strcmp(gConfig.TX.OPERATIONMODE,"AUTO_FIX")==0))
             ErrorMessageBox("錯誤訊息","未定義之錯誤代碼","","",line4,d_MB_CHECK);
          else
              ErrorMessageBox("錯誤訊息","未定義之錯誤代碼","","",line4,d_MB_CHECK);
  
   //2014.04.28, kobe added it for POS to display errorMeg    
   if(ecrObj.gData.isEcrTxn)
   {
                if(strlen(ecrObj.ngData->errMsg)==0)                
                    sprintf(ecrObj.ngData->errMsg,"未定義之錯誤代碼");
   }
 
   return d_FAIL;
}
