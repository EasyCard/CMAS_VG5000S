#include "ECCAPP.h"
//Declare Global Variable //
 const STR *keyboardLayoutEnglish[]={" 0", "qzQZ1", "abcABC2", "defDEF3", "ghiGHI4","jklJKL5", "mnoMNO6", "prsPRS7", "tuvTUV8", "wxyWXY9", ":;/\\|?,.<>", ".!@#$%^&*()"};
//numeric keyboard (0123456789) and radix point '.'
 const STR *keyboardLayoutNumberWithRadixPoint[]={"0", "1", "2", "3", "4", "5", "6", "7","8", "9", "", "."};
//numeric keyboard (0123456789) without radix point
const STR *keyboardLayoutNumber[]={"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "",""};
void Setcolor(ULONG BackGnd,ULONG ForeGnd)
{
    CTOS_LCDForeGndColor(ForeGnd);
    CTOS_LCDBackGndColor(BackGnd);
}

void WaitRemoveCard(STR *Line1,STR *Line2)
{
   int iret;
   ShowLine(0,32,Med_Font_Size,Line1,TRUE);
   ShowLine(0,40+32,Med_Font_Size,Line2,TRUE);
   Setcolor(Color_black,Color_red);
   do{
       iret=inPPR_ReadCardNumber();
       if(iret!=0x9000) return ;
       CTOS_Beep();
     }while(1);
}

/*
void ShowECRStatus()
{
   if(ecrObj.ecrOn)
        CTOS_LCDGShowBMPPic(55+18, 0, "POS.bmp" );
   
}
*/
void ShowInternetStatus()
{
    USHORT ret=Eth_SocketCheckConnectStatus();
    if(ret ==d_OK)
        CTOS_LCDGShowBMPPic(55+20, 0, "internet_18.bmp" );
    else
        CTOS_LCDGShowBMPPic(55+20, 0, "stop.bmp" );
}
void ShowGSMSignal()
{
    BYTE bStrength;
    USHORT ret=CTOS_GSMSignalQuality(&bStrength);
    if(ret==d_OK){
        switch(bStrength){
            case 0:
                 CTOS_LCDGShowBMPPic(55, 0, "3g1.bmp" );
                break;
            case 1:  
                CTOS_LCDGShowBMPPic(55, 0, "3g2.bmp" );
                break;
            case 2 ...15:
                 CTOS_LCDGShowBMPPic(55, 0, "3g3.bmp" );
                break;
            case 16 ... 30: 
               CTOS_LCDGShowBMPPic(55, 0, "3g4.bmp" );
                break;
            case 31:
                 CTOS_LCDGShowBMPPic(55, 0, "3g5.bmp" );
                 break;
            case 99: 
                 CTOS_LCDGShowBMPPic(55, 0, "3g0.bmp" );
                 break;
                    
        }
    }
}
void ShowNetWorkTypeStatus()
{
      USHORT NetworkType; 
      DWORD dwStatus=0;
      USHORT ret;
    if(bgNETWORKChannel== CHANNEL_ETHERNET){
         CTOS_LCDGShowBMPPic(0, 0, "ETH.bmp" );
        if(Eth_CheckDeviceStatus()!=d_OK){
           CTOS_LCDGShowBMPPic(45, 0, "No_networks.bmp" );
           return ;
       }
       ret=CTOS_EthernetStatus(&dwStatus);
        if(!(dwStatus && d_STATUS_ETHERNET_PHYSICAL_ONLINE))
        {
            CTOS_LCDGShowBMPPic(45, 0, "No_networks.bmp" );
        }else{
            CTOS_LCDGShowBMPPic(45, 0, "networks.bmp" );
        }
    }else if(  bgNETWORKChannel== CHANNEL_GPRS){
        ret=   CTOS_MobileGetNetworkTypeCurrent(&NetworkType);
        if(NetworkType==d_MOBILE_NETWORK_GPRS){
            CTOS_LCDGTextOut(0,4,"GPRS",0x0a0a,FALSE);
              // CTOS_LCDGShowBMPPic(0, 0, "gprs.bmp" );
        }else if(NetworkType==d_MOBILE_NETWORK_UMTS) 
                CTOS_LCDGTextOut(0,4,"3G",0x0a0a,FALSE);
        else if(NetworkType==d_GSM_NETWORK_EGPRS){
        } 
             
     printf("[%s,%d] trace...\n",__FUNCTION__,__LINE__);
       ShowGSMSignal();
       ShowInternetStatus();
       printf("[%s,%d] trace...\n",__FUNCTION__,__LINE__);
    }
}
void ShowUnUploadCount()
{ 
  
   Setcolor(Color_ezblue,Color_yellow);
    BYTE VerStr[8+1];
    int iUNUPLOADCOUNT= CheckUnuploadTxCount();
    sprintf(VerStr,"%d",iUNUPLOADCOUNT);
    CTOS_LCDGTextOut(0,240-18-18,VerStr,d_FONT_9x18,FALSE);
     Setcolor(Color_ezblue,Color_black);
}
void ShowAPVersion()
{
    BYTE VerStr[8+1];
    Setcolor(Color_ezblue,Color_yellow);
    sprintf(VerStr,"V%s",gAPVER);
    CTOS_LCDGTextOut(320-(9*7),240-18-18,VerStr,d_FONT_9x18,FALSE);
      Setcolor(Color_ezblue,Color_black);
}
void ShowUPStatusbar()
{   
    printf("[%s,%d] trace...\n",__FUNCTION__,__LINE__); 
    if(ecrObj.ecrOn) return;
    
    Setcolor(Color_white,Color_ezblue);
    CTOS_LCDGSetBox(0,0,320,18,d_LCD_FILL_0);  
    ShowNetWorkTypeStatus();
    
  //  ShowECRStatus();
    
  //  ShowInternetStatus();
 
    ShowDataTime();
    
    ShowBatteryStatus();
    
    ShowUnUploadCount();
    
  
    ShowAPVersion();
    
     Setcolor(Color_ezblue,Color_black);
      printf("[%s,%d] trace...\n",__FUNCTION__,__LINE__);  
}
void ShowDataTime()
{
   
    BYTE Date[64+1];
    BYTE time[64+1];
    BYTE VerStr[7+1];
    CTOS_RTC SetRTC;
    USHORT ret = CTOS_RTCGet(&SetRTC);
    if(ret==0){
       // CTOS_LCDForeGndColor(d_LCD_BLACK);
         Setcolor(Color_ezblue,Color_yellow);
     //    CTOS_LCDGSetBox(0,0,320,18,d_LCD_FILL_0);  
        //  sprintf(Date,"%04d/%02d/%02d  %02d:%02d      V%s",SetRTC.bYear + 2000,SetRTC.bMonth,SetRTC.bDay,SetRTC.bHour,SetRTC.bMinute,gAPVER);
         sprintf(Date,"%04d/%02d/%02d",SetRTC.bYear+2000,SetRTC.bMonth,SetRTC.bDay);
         sprintf(time,"%02d:%02d",SetRTC.bHour,SetRTC.bMinute);
         if(gConfig.DEVICE.READER.bREADERSTATUS==READERSTATUS_LOCK)
        {
              Setcolor(Color_ezblue,Color_red);
              CTOS_LCDGTextOut(0,18+7,"讀卡機故障!!",0x2424,FALSE);
           
        }else if(MechineStatus & Status_SignOnFail){
              Setcolor(Color_ezblue,Color_red);
              CTOS_LCDGTextOut(0,18+7,"請先執行登入",0x2424,FALSE);
        }else  if(MechineStatus & Status_FLASH_ERROR){
              Setcolor(Color_ezblue,Color_red);
              CTOS_LCDGTextOut(0,18+7,"記憶體故障請報修",0x1e1e,FALSE);
        }else{
              Setcolor(Color_ezblue,Color_yellow);
              CTOS_LCDGTextOut(180-90,18+7,time,0x2424,FALSE);
        }
         Setcolor(Color_white,Color_black);
         CTOS_LCDGTextOut(135,0,Date,d_FONT_9x18,FALSE);
       }
}
/*void ShowDataTime()
{
   
    BYTE Date[64+1];
    BYTE time[64+1];
    BYTE VerStr[7+1];
    CTOS_RTC SetRTC;
    USHORT ret = CTOS_RTCGet(&SetRTC);
    if(ret==0){
       // CTOS_LCDForeGndColor(d_LCD_BLACK);
         Setcolor(Color_ezblue,Color_yellow);
     //    CTOS_LCDGSetBox(0,0,320,18,d_LCD_FILL_0);  
        //  sprintf(Date,"%04d/%02d/%02d  %02d:%02d      V%s",SetRTC.bYear + 2000,SetRTC.bMonth,SetRTC.bDay,SetRTC.bHour,SetRTC.bMinute,gAPVER);
         sprintf(Date,"%04d/%02d/%02d",SetRTC.bYear+2000,SetRTC.bMonth,SetRTC.bDay);
         sprintf(time,"%02d:%02d",SetRTC.bHour,SetRTC.bMinute);
         if(MechineStatus & Status_SignOnFail){
                 CTOS_LCDGTextOut(0,18+7,"請先執行登入",0x2424,FALSE);
         }else{
                  CTOS_LCDGTextOut(180-90,18+7,time,0x2424,FALSE);
         }
         Setcolor(Color_white,Color_black);
         CTOS_LCDGTextOut(135,0,Date,d_FONT_9x18,FALSE);
       }
}*/
/*/
#define d_PWRSRC_DCJACK      			0
#define d_PWRSRC_CRADLE      			1
#define d_PWRSRC_BATTERY     			2*/
void ShowBatteryStatus()
{  
    DWORD dwStatus;
    UCHAR bSrc;
    USHORT ret=CTOS_PowerSource(&bSrc);
    if((bSrc==d_PWRSRC_DCJACK)||(bSrc ==d_PWRSRC_CRADLE)){
       CTOS_LCDGShowBMPPic(320-35,0, "plugin.bmp" );
    }else if(bSrc ==d_PWRSRC_BATTERY){//20150409 modify by bruce
       ret= CTOS_BatteryStatus(&dwStatus);
        if( ret==d_OK){
            if(dwStatus ==d_MK_BATTERY_EXIST){
                BYTE bPercentage;
                BYTE percentageStr[5];
                ret= CTOS_BatteryGetCapacity(&bPercentage);
                if(ret==d_OK){
                    switch(bPercentage){
                        case 0 ... 25: 
                           CTOS_LCDGShowBMPPic(320-35,0, "battery2.bmp" );
                            break;
                        case 26 ... 50: 
                            CTOS_LCDGShowBMPPic(320-35,0, "battery3.bmp" );
                            break;
                        case 51 ... 75:
                              CTOS_LCDGShowBMPPic(320-35,0, "battery4.bmp" );
                            break;
                        case 76 ... 100:
                            CTOS_LCDGShowBMPPic(320-35,0, "battery5.bmp" );
                            break;
                    }
                    sprintf(percentageStr,"%d%%",bPercentage);
                    CTOS_LCDGTextOut(320-35-27,0,percentageStr,d_FONT_9x18,FALSE);  
                }

            }else  if(dwStatus ==d_MK_BATTERY_CHARGE){
               CTOS_LCDGShowBMPPic(320-55,0, "battery_charge.bmp" );
            }
        }
    }
}

void ShowSystemMemoryStatus(STR * flagname)
{
   
        Sysinfo2_GetEDCSystemMemoryStatus();
        char buffer[64];
        sprintf(buffer,"%s:=%s\n",flagname,gConfig.DEVICE.MEMORY.USEDRAMSIZE);
       // CTOS_PrinterPutString(buffer);
        SystemLog("MemoryStatu",buffer);
       /* ShowMessage4line("記憶体資訊",
                   gConfig.DEVICE.MEMORY.USEDDISKSIZE,
                   gConfig.DEVICE.MEMORY.TOTALDISKSIZE,
                   gConfig.DEVICE.MEMORY.USEDRAMSIZE,
                    gConfig.DEVICE.MEMORY.TOTALRAMSIZE,Type_ComformNONE); 
        */ 
         
}

void ShowStatus_Thread()
{
    while(1){
        if(!gIDLE){
             CTOS_Delay(60*1000);
             continue;
        } 
        
       ShowUPStatusbar();
       CTOS_Delay(60*1000);
    }
}
void ShowTitle(STR * Title)
{

    int Btnwidth=40;
    int Btnlenght=320;
    
    int Windowwidth=240;
    int Windowlenght=320;
    
    int Xoffset=0,Yoffset;
    int Titlesize=strlen(Title);
    
    CTOS_LCDGClearCanvas();
    CTOS_LCDGSetBox(0,0,320,Btnwidth,1); //Draw a rectangle //
    Xoffset=(Windowlenght/2)-(((Titlesize/3)*16));
    CTOS_LCDGTextOut(Xoffset,0,"                  ",Med_Font_Size,d_TRUE); 
    CTOS_LCDGTextOut(Xoffset,0,Title,Med_Font_Size,d_TRUE); 
    
    return ;
}
void ShowStatusLine(STR * line)
{

    CTOS_LCDGSetBox(0,240-40,320,40,1); //Draw a rectangle //
    CTOS_LCDGTextOut(0,240-40,"                 ",Med_Font_Size,d_TRUE); 
    CTOS_LCDGTextOut(0,240-40,line,Med_Font_Size,d_TRUE); 
    return ;
}
void ShowLine(USHORT usX,USHORT usY,USHORT usFontSize,STR * line,BYTE bFill)
{
    USHORT xSize,ySize;

    if(usFontSize==Big_Font_Size)
    {
        xSize=Big_Font_Xsize;
        ySize=Big_Font_Ysize;
    }
    else if(usFontSize==Med_Font_Size){
      xSize=Med_Font_Xsize;
        ySize=Med_Font_Ysize;
    }
        
    CTOS_LCDGSetBox(usX,usY,320,ySize,bFill); //Draw a rectangle //
    CTOS_LCDGTextOut(0,usY,"                     ",usFontSize,bFill); 
    CTOS_LCDGTextOut(0,usY,line,usFontSize,bFill); 
}
int ShowMessage2line(STR *Title,STR * line1,STR * line2,BYTE ComformType)
{
    BYTE key;int i;
    Setcolor(Color_white,Color_black);
    USHORT usFontSize=Big_Font_Size;
   if((gScrpitTesting==1&&gDebugPrintFlag==DebugMode_TestScrpit) ||
      ecrObj.ecrForcedTest==TRUE)
    {     
      //  CTOS_PrinterPutString(Title);
      //  CTOS_PrinterPutString(line1);
      //  CTOS_PrinterPutString(line2);
        return d_OK;
    }
    CTOS_KBDBufFlush();
   // CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
    //CTOS_LCDBackGndColor(d_LCD_WHITE);
    //CTOS_LCDForeGndColor(d_LCD_BLUE);
    CTOS_LCDGClearCanvas();
    ShowTitle(Title);
    CTOS_LCDGTextOut(0,40+16,line1,usFontSize,FALSE); 
    CTOS_LCDGTextOut(0,120+16,line2,usFontSize,FALSE);     
  
    
    CTOS_LCDGSetBox(0,200,320,40,1); //Draw a rectangle // 
    //2014.04.07,kobe added for ECR, if response2Pos was false, must response to POS first        
    if(ecrObj.ecrOn==TRUE && ecrObj.ecrUiStay==FALSE)            
        if(ComformType==Type_Comform0 || 
           ComformType==Type_ComformOK ||
           ComformType==Type_ComformAnykey)         
        {
            //CTOS_Delay(2000);
            return d_OK;
        }
    
    if(ComformType==Type_Comform0 ||
       ComformType==TYPE_ECR_FORCE_TO_CONFIRM_0){
	    CTOS_LCDGTextOut(0,200,"確認請按0 取消請按X",Med_Font_Size,TRUE); 
     }else  if(ComformType==Type_ComformOK ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_OK){
    	   CTOS_LCDGTextOut(0,200,"確認請按OK 取消請按X",Med_Font_Size,TRUE); 
     }else  if(ComformType==Type_ComformAnykey ||
             ComformType==TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY){
    	   CTOS_LCDGTextOut(0,200,"請按任意鍵",Med_Font_Size,TRUE);  
     }else if(ComformType==Type_RemoveCard){
         CTOS_LCDGTextOut(0,200,"請記得帶走卡片",Med_Font_Size,TRUE);
     }else if(ComformType==Type_wait2sec){
         CTOS_Delay(2000);
     }
    if(ComformType==Type_ComformNONE){
	return d_OK;
    }
 CTOS_TimeOutSet(TIMER_ID_4, 100*30);
  while(1){
        if(CTOS_TimeOutCheck(TIMER_ID_4)==d_YES )
                 return d_FAIL;
            if(ComformType==Type_Comform0 ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_0){
                CTOS_KBDHit(&key);  
                   if(key==d_KBD_0) 
                           return d_OK;
                    else if(key==d_KBD_CANCEL)
                           return  d_FAIL;
           }else  if(ComformType==Type_ComformOK ||
                   ComformType==TYPE_ECR_FORCE_TO_CONFIRM_OK){
                CTOS_KBDHit(&key);   
                  if(key==d_KBD_ENTER) 
                           return d_OK;
                  else if(key==d_KBD_CANCEL)
                           return  d_FAIL;
           }else if(ComformType==Type_ComformAnykey ||
                   ComformType==TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY){
               CTOS_KBDHit(&key);  
                       if(key!=0) return d_OK;
           }else if(ComformType==Type_RemoveCard){
               //if(ecrObj.ecrForcedTest) return d_OK;
               int iret;
               do{
                   iret=inPPR_ReadCardNumber();
                   if(iret!=0x9000) return d_OK;
                   CTOS_Beep();
               }while(1);
           }else if(ComformType==Type_wait2sec){
               CTOS_Delay(2000); return d_OK;
           }  
        
    }
	return d_OK;
}
int ShowMessage3line(STR *Title,STR * line1,STR * line2,STR * line3,BYTE ComformType)
{

    BYTE key;int i;USHORT usFontSize=Big_Font_Size;
     int Btnwidth=53;   
     Setcolor(Color_white,Color_black);
   if((gScrpitTesting==1&&gDebugPrintFlag==DebugMode_TestScrpit) ||
       ecrObj.ecrForcedTest==TRUE)
    {     
     //   CTOS_PrinterPutString(Title);
    //    CTOS_PrinterPutString(line1);
    //   CTOS_PrinterPutString(line2);
     //   CTOS_PrinterPutString(line3);
      
        return d_OK;
    }
    CTOS_KBDBufFlush();
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
   //  CTOS_LCDBackGndColor(d_LCD_WHITE);
   // CTOS_LCDForeGndColor(d_LCD_BLUE);
    CTOS_LCDGClearCanvas();
    ShowTitle(Title);
   
    CTOS_LCDGTextOut(0,40,line1,usFontSize,FALSE); 
    CTOS_LCDGTextOut(0,40+Btnwidth,line2,usFontSize,FALSE);     
    CTOS_LCDGTextOut(0,40+Btnwidth*2,line3,usFontSize,FALSE);     
    
    CTOS_LCDGSetBox(0,200,320,40,1); //Draw a rectangle // 
    //2014.04.07,kobe added for ECR    
    //if(ecrObj.gData.isEcrTxn && !ecrObj.ngData->response2Pos) return d_OK;
    if(ecrObj.ecrOn==TRUE && ecrObj.ecrUiStay==FALSE)
        if(ComformType==Type_Comform0 || 
           ComformType==Type_ComformOK ||
           ComformType==Type_ComformAnykey) {
            //CTOS_Delay(2000);//for buildIn Reader
            return d_OK;
        }
   
     if(ComformType==Type_Comform0 ||
        ComformType==TYPE_ECR_FORCE_TO_CONFIRM_0){
	    CTOS_LCDGTextOut(0,200,"確認請按0 取消請按X",Med_Font_Size,TRUE); 
     }else  if(ComformType==Type_ComformOK ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_OK){
    	   CTOS_LCDGTextOut(0,200,"確認請按OK 取消請按X",Med_Font_Size,TRUE); 
     }else  if(ComformType==Type_ComformAnykey ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY){
    	   CTOS_LCDGTextOut(0,200,"請按任意鍵",Med_Font_Size,TRUE);  
     }else if(ComformType==Type_RemoveCard){
         CTOS_LCDGTextOut(0,200,"請記得帶走卡片",Med_Font_Size,TRUE);
     }
    if(ComformType==Type_ComformNONE){
	return d_OK;
    }
    int iret=0;
  int counter;
  CTOS_TimeOutSet(TIMER_ID_4, 100*30);
  while(1){
        if(CTOS_TimeOutCheck(TIMER_ID_4)==d_YES )
                 return d_FAIL;
            if(ComformType==Type_Comform0 ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_0){
                CTOS_KBDHit(&key);  
                   if(key==d_KBD_0) 
                           return d_OK;
                    else if(key==d_KBD_CANCEL)
                           return  d_FAIL;
           }else  if(ComformType==Type_ComformOK ||
                     ComformType==TYPE_ECR_FORCE_TO_CONFIRM_OK){
                CTOS_KBDHit(&key);   
                  if(key==d_KBD_ENTER) 
                           return d_OK;
                  else if(key==d_KBD_CANCEL)
                           return  d_FAIL;
           }else if(ComformType==Type_ComformAnykey ||
                    ComformType==TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY){
                    CTOS_KBDHit(&key);  
                    if(key!=d_KBD_INVALID) return d_OK;
           }else if(ComformType==Type_RemoveCard){
               //if(ecrObj.ecrForcedTest) return d_OK;
               int iret;
               do{
                   iret=inPPR_ReadCardNumber();
                   if(iret!=0x9000) return d_OK;
                   CTOS_Beep();
               }while(1);
           }else if(ComformType==Type_wait2sec){
               CTOS_Delay(2000); return d_OK;
           }  
        
    }
	return d_OK;
}
int ShowMessage(STR *Title,STR * line1,BYTE ComformType){
   Setcolor(Color_white,Color_black);
    BYTE key;int i;USHORT usFontSize=Med_Font_Size;
     int Btnwidth=53;
      if((gScrpitTesting==1&&gDebugPrintFlag==DebugMode_TestScrpit) ||
         ecrObj.ecrForcedTest==TRUE)
    {     
     //   CTOS_PrinterPutString(Title);
      //  CTOS_PrinterPutString(line1);
        return d_OK;
    }
    CTOS_KBDBufFlush();
   
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
//    CTOS_LCDBackGndColor(d_LCD_WHITE);
 //   CTOS_LCDForeGndColor(d_LCD_BLUE);
    CTOS_LCDGClearCanvas();
    ShowTitle(Title);
   
    CTOS_LCDGTextOut(0,96,line1,usFontSize,FALSE); 
   
    //2014.04.07,kobe added for ECR, if response2Pos was false, must response to POS first    
    if(ecrObj.ecrOn==TRUE && ecrObj.ecrUiStay==FALSE)
        if(ComformType==Type_Comform0 || 
           ComformType==Type_ComformOK ||
           ComformType==Type_ComformAnykey) {
            //CTOS_Delay(2000);
            return d_OK;
        }
    if(ComformType==Type_Comform0 ||
       ComformType==TYPE_ECR_FORCE_TO_CONFIRM_0){
	    CTOS_LCDGTextOut(0,200,"確認請按0 取消請按X",Med_Font_Size,TRUE); 
     }else  if(ComformType==Type_ComformOK ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_OK){
    	   CTOS_LCDGTextOut(0,200,"確認請按OK 取消請按X",Med_Font_Size,TRUE); 
     }else  if(ComformType==Type_ComformAnykey ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY){
    	   CTOS_LCDGTextOut(0,200,"請按任意鍵",Med_Font_Size,TRUE);  
     }else if(ComformType==Type_RemoveCard){
         CTOS_LCDGTextOut(0,200,"請記得帶走卡片",Med_Font_Size,TRUE);
     }
    if(ComformType==Type_ComformNONE){
	return d_OK;
    }
  CTOS_TimeOutSet(TIMER_ID_4, 100*30);
  while(1){
        if(CTOS_TimeOutCheck(TIMER_ID_4)==d_YES )
                 return d_FAIL;
        
            if(ComformType==Type_Comform0 ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_0){
                CTOS_KBDHit(&key);  
                   if(key==d_KBD_0) 
                           return d_OK;
                    else if(key==d_KBD_CANCEL)
                           return  d_FAIL;
           }else  if(ComformType==Type_ComformOK ||
                     ComformType==TYPE_ECR_FORCE_TO_CONFIRM_OK){
                CTOS_KBDHit(&key);   
                  if(key==d_KBD_ENTER) 
                           return d_OK;
                  else if(key==d_KBD_CANCEL)
                           return  d_FAIL;
           }else if(ComformType==Type_ComformAnykey ||
                    ComformType==TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY){
                    CTOS_KBDHit(&key);  
                       if(key!=d_KBD_INVALID) return d_OK;
           }else if(ComformType==Type_RemoveCard){
               //if(ecrObj.ecrForcedTest) return d_OK;
               int iret;
               do{
                   iret=inPPR_ReadCardNumber();
                   if(iret!=0x9000) return d_OK;
                   CTOS_Beep();
               }while(1);
           }else if(ComformType==Type_wait2sec){
               CTOS_Delay(2000); return d_OK;
           }  
        
    }
	return d_OK;
}
int ShowMessage4line(STR *Title,STR * line1,STR * line2,STR * line3,STR * line4,BYTE ComformType)
{
       Setcolor(Color_white,Color_black); 
    BYTE key;int i;USHORT usFontSize=Med_Font_Size;
     int Btnwidth=40;
    CTOS_KBDBufFlush();
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
   if((gScrpitTesting==1&&gDebugPrintFlag==DebugMode_TestScrpit) ||
      ecrObj.ecrForcedTest==TRUE)
    {     
      //  CTOS_PrinterPutString(Title);
       // CTOS_PrinterPutString(line1);
       // CTOS_PrinterPutString(line2);
       // CTOS_PrinterPutString(line3);
       // CTOS_PrinterPutString(line4);
        return d_OK;
    }
//    CTOS_LCDBackGndColor(d_LCD_WHITE);
//    CTOS_LCDForeGndColor(d_LCD_BLUE);
    CTOS_LCDGClearCanvas();
    ShowTitle(Title);
     
    CTOS_LCDGTextOut(0,40,line1,usFontSize,FALSE); 
    CTOS_LCDGTextOut(0,40+Btnwidth,line2,usFontSize,FALSE);     
    CTOS_LCDGTextOut(0,40+Btnwidth*2,line3,usFontSize,FALSE);     
    CTOS_LCDGTextOut(0,40+Btnwidth*3,line4,usFontSize,FALSE);     
    CTOS_LCDGSetBox(0,200,320,40,1); //Draw a rectangle // 
    //2014.04.07,kobe added for ECR, if response2Pos was false, must response to POS first    
    if(ecrObj.ecrOn==TRUE && ecrObj.ecrUiStay==FALSE)
        if(ComformType==Type_Comform0 || 
           ComformType==Type_ComformOK ||
           ComformType==Type_ComformAnykey) {
            //CTOS_Delay(2000);
            return d_OK;
        }
    /*
    if(ecrObj.ecrOn)
        if(ComformType==Type_Comform0 || 
           ComformType==Type_ComformOK ||
           ComformType==Type_ComformAnykey) return d_OK;
    */
     if(ComformType==Type_Comform0 ||
        ComformType==TYPE_ECR_FORCE_TO_CONFIRM_0){
	    CTOS_LCDGTextOut(0,200,"確認請按0 取消請按X",Med_Font_Size,TRUE); 
     }else  if(ComformType==Type_ComformOK ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_OK){
    	   CTOS_LCDGTextOut(0,200,"確認請按OK 取消請按X",Med_Font_Size,TRUE); 
     }else  if(ComformType==Type_ComformAnykey ||
             ComformType==TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY){
    	   CTOS_LCDGTextOut(0,200,"請按任意鍵",Med_Font_Size,TRUE);  
     }else if(ComformType==Type_RemoveCard){
         CTOS_LCDGTextOut(0,200,"請記得帶走卡片",Med_Font_Size,TRUE);
     }
    if(ComformType==Type_ComformNONE){
	return d_OK;
    }
  CTOS_TimeOutSet(TIMER_ID_4, 100*30);
  while(1){
        if(CTOS_TimeOutCheck(TIMER_ID_4)==d_YES )
                 return d_FAIL;
            
        
            if(ComformType==Type_Comform0 ||
               ComformType==TYPE_ECR_FORCE_TO_CONFIRM_0){
                CTOS_KBDHit(&key);  
                   if(key==d_KBD_0) 
                           return d_OK;
                    else if(key==d_KBD_CANCEL)
                           return  d_FAIL;
           }else  if(ComformType==Type_ComformOK ||
                     ComformType==TYPE_ECR_FORCE_TO_CONFIRM_OK){
                  CTOS_KBDHit(&key);   
                  if(key==d_KBD_ENTER) 
                           return d_OK;
                  else if(key==d_KBD_CANCEL)
                           return  d_FAIL;
           }else if(ComformType==Type_ComformAnykey ||
                   ComformType==TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY){
               CTOS_KBDHit(&key);  
                       if(key!=d_KBD_INVALID) return d_OK;
           }else if(ComformType==Type_RemoveCard){
               //if(ecrObj.ecrForcedTest) return d_OK;
               int iret;
               do{
                   iret=inPPR_ReadCardNumber();
                   if(iret!=0x9000) return d_OK;
                   CTOS_Beep();
               }while(1);
           }else if(ComformType==Type_wait2sec){
               CTOS_Delay(2000); return d_OK;
           }    
        
    }
	return d_OK;
}
BYTE Displaymuiltlie(USHORT usFontSize,STR *Title,STR * line[]){

    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
    CTOS_LCDTSelectFontSize(usFontSize);
     CTOS_KBDBufFlush();
    CTOS_LCDTClearDisplay();
  //    CTOS_LCDBackGndColor(d_LCD_WHITE);
  //  CTOS_LCDForeGndColor(d_LCD_BLUE);
  
    ShowTitle(Title);
   
    CTOS_LCDTSetReverse(FALSE);
    
    CTOS_LCDTPrintXY(1,2,line[0]);
    CTOS_LCDTPrintXY(1,3,line[1]);
    
    CTOS_LCDTPrintXY(1,4,line[2]);
    CTOS_LCDTPrintXY(1,5,line[3]);
    
    CTOS_LCDTPrintXY(1,6,line[4]);
    CTOS_LCDTPrintXY(1,7,line[5]);
    
    CTOS_LCDTPrintXY(1,8,line[6]);
    CTOS_LCDTPrintXY(1,9,line[7]);
    
    CTOS_LCDTPrintXY(1,10,line[8]);
  
    
   BYTE key=0; 
    while(key==0){
        CTOS_KBDGet(&key);
    }
    return key;
}

int ErrorMessageBox(STR * Title,STR * line1,STR * line2,STR * line3,STR * line4,USHORT MBTYPE){
    BYTE key;
    USHORT usFontSize=Med_Font_Size;
    USHORT Xoffset;
 
   if(gScrpitTesting==1&&gDebugPrintFlag==DebugMode_TestScrpit)
    {     
    /*    CTOS_PrinterPutString(Title);
        CTOS_PrinterPutString(line1);
        CTOS_PrinterPutString(line2);
        CTOS_PrinterPutString(line3);
        CTOS_PrinterPutString(line4);
      */  return d_OK;
    }
 
    Setcolor(Color_yellow,Color_red);
    CTOS_LCDSelectMode(d_LCD_GRAPHIC_320x240_MODE);
    CTOS_KBDBufFlush();
    USHORT ret = CTOS_Sound(1500, 100);

    int    Btnwidth;
    if(usFontSize==Big_Font_Size)
        Btnwidth=48;
    else if(usFontSize==Med_Font_Size)
        Btnwidth=40;
    ShowTitle(Title);
    CTOS_LCDGTextOut(0,48*1,line1,Big_Font_Size,FALSE);
    CTOS_LCDGTextOut(0,48*2,line2,Big_Font_Size,FALSE);
 
    
    CTOS_LCDGTextOut(0,Btnwidth*4,line4,usFontSize,FALSE);
    
    if(MBTYPE==0)
		return d_OK;
    CTOS_LCDGSetBox(0,Btnwidth*5,320,240,1); //Draw a rectangle // 
    //2014.04.07,kobe added for ECR, if response2Pos was false, must response to POS first    
    if(ecrObj.ecrOn==TRUE && ecrObj.ecrUiStay==FALSE)
    {    
        //CTOS_Delay(2000);
        return d_OK;
    }     
    if(MBTYPE==d_MB_CHECK){
             CTOS_LCDGTextOut(0,Btnwidth*5,"請按任意鍵離開",usFontSize,TRUE); 
      }else if(MBTYPE==d_MB_CONFIRM){
            CTOS_LCDGTextOut(0,Btnwidth*5,"確認請按0 取消請按X",usFontSize,TRUE); 
     }
  unsigned long ulTick=CTOS_TickGet();
  CTOS_TimeOutSet(TIMER_ID_4, 100*5);
  while(1){
        if(CTOS_TimeOutCheck(TIMER_ID_4)==d_YES )
                 return d_FAIL;
       
     
        if(MBTYPE==d_MB_CHECK){
            // CTOS_LCDGTextOut(0,Btnwidth*5,"請按任意鍵",usFontSize,TRUE); 
          
            CTOS_KBDHit(&key);  
            if(key!=d_KBD_INVALID){ 
                Setcolor(Color_white,Color_black);
                return d_OK; 
            }
           
        }else if(MBTYPE==d_MB_CONFIRM){
            CTOS_LCDGTextOut(0,Btnwidth*5,"確認請按0 取消請按X",usFontSize,TRUE); 
            CTOS_KBDHit(&key);  
            if(key==d_KBD_0){
                  Setcolor(Color_white,Color_black);
                  return d_OK;
            }else if(key==d_KBD_CANCEL){
                  Setcolor(Color_white,Color_black);
                  return  d_ERR_USERCANCEL;
            }
        }else if(MBTYPE==Type_wait2sec){
               CTOS_Delay(2000);
               Setcolor(Color_white,Color_black);
               return d_ERR_USERCANCEL;
           }    
    }
    Setcolor(Color_white,Color_black);
    return d_OK;
}
int MessageBox(STR * Title,STR * line1,STR * line2,STR * line3,STR * line4,USHORT MBTYPE){
    BYTE key;
    USHORT usFontSize=Med_Font_Size;
    USHORT Xoffset;

    if(gScrpitTesting==1&&gDebugPrintFlag==DebugMode_TestScrpit)
    {     
     /*   CTOS_PrinterPutString(Title);
        CTOS_PrinterPutString(line1);
        CTOS_PrinterPutString(line2);
        CTOS_PrinterPutString(line3);
        CTOS_PrinterPutString(line4);
       */ return d_OK;
    }
    
    CTOS_LCDSelectMode(d_LCD_GRAPHIC_320x240_MODE);
    CTOS_KBDBufFlush();
    USHORT ret = CTOS_Sound(1500, 100);
 //     CTOS_LCDBackGndColor(d_LCD_WHITE);
 //   CTOS_LCDForeGndColor(d_LCD_BLUE);
      Setcolor(Color_white,Color_black);
    int    Btnwidth;
    if(usFontSize==Big_Font_Size)
        Btnwidth=48;
    else if(usFontSize==Med_Font_Size)
        Btnwidth=40;
    
    ShowTitle(Title);
    CTOS_LCDGTextOut(0,Btnwidth*1,line1,usFontSize,FALSE);
    CTOS_LCDGTextOut(0,Btnwidth*2,line2,usFontSize,FALSE);
    CTOS_LCDGTextOut(0,Btnwidth*3,line3,usFontSize,FALSE);
    
    CTOS_LCDGTextOut(0,Btnwidth*4,line4,usFontSize,FALSE);
    
   //2014.04.07,kobe added for ECR, if response2Pos was false, must response to POS first    
   if(ecrObj.ecrOn==TRUE && ecrObj.ecrUiStay==FALSE){
       //CTOS_Delay(2000);
       return d_OK;
   }
    
    if(MBTYPE==0)		
        return d_OK;
     CTOS_LCDGSetBox(0,Btnwidth*5,320,240,1); //Draw a rectangle // 
     if(MBTYPE==d_MB_CHECK){
             CTOS_LCDGTextOut(0,Btnwidth*5,"請按任意鍵離開",usFontSize,TRUE); 
      }else if(MBTYPE==d_MB_CONFIRM){
            CTOS_LCDGTextOut(0,Btnwidth*5,"確認請按0 取消請按X",usFontSize,TRUE); 
      }
  CTOS_TimeOutSet(TIMER_ID_4, 100*30);
  while(1){
        if(CTOS_TimeOutCheck(TIMER_ID_4)==d_YES )
                 return d_FAIL;
     
       if(MBTYPE==d_MB_CHECK){
            CTOS_KBDHit(&key);  
            if(key!=d_KBD_INVALID){ 
                Setcolor(Color_white,Color_black);
                return d_OK; 
            }
        }else if(MBTYPE==d_MB_CONFIRM){
       
            CTOS_KBDHit(&key);  
            if(key==d_KBD_0){
                  Setcolor(Color_white,Color_black);
                  return d_OK;
            }else if(key==d_KBD_CANCEL){
                  Setcolor(Color_white,Color_black);
                  return  d_ERR_USERCANCEL;
            }
        }else if(MBTYPE==Type_wait2sec){
               CTOS_Delay(2000);
               Setcolor(Color_white,Color_black);
               return d_ERR_USERCANCEL;
        }       
           
           
    }
    return d_OK;
}
int ShowInputBox3line(STR *Title,STR * line1,STR * line2,STR *line3, BYTE * buff,int limit,int InputType,BYTE bPasswordMask)
{
    int ret;

CTOS_KBDBufFlush();
  Setcolor(Color_white,Color_black);
 #ifdef TESTMODE
  
   if((gScrpitTesting==1)&&( ezxml_get(gTestAction, "AMT",-1)!=NULL)) 
{       
        ezxml_t ezxml_amt = ezxml_get(gTestAction, "AMT",-1);
        BYTE  *strbuf=ezxml_txt(ezxml_amt);   
        memcpy(buff,strbuf,strlen(strbuf));
		return d_OK;
}
#endif	
    BYTE key;int i;USHORT usFontSize=d_FONT_16x30;
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
    CTOS_LCDTSelectFontSize(usFontSize);
    CTOS_LCDTClearDisplay();
    int Btnwidth = 30;
    int Btnlenght=320;
    int Windowwidth=240;
    int Windowlenght=320;
    int x=0,y=30;
    int  Row; 
    int Xoffset=0,Yoffset;
    int Titlesize=strlen(Title);//utf8
 //   CTOS_LCDBackGndColor (0x00e0c0 );
 //Draw a pixel on the canvas //
    Xoffset=(Windowlenght/2)-(((Titlesize/3)*16));
   
    CTOS_LCDTSetReverse(FALSE);
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
    CTOS_LCDTSelectFontSize(usFontSize);
    CTOS_LCDTClearDisplay();
     x = strlen(Title)/3;
     x=10-(x/2);
     CTOS_LCDTSetReverse(TRUE);
         CTOS_LCDTPrintXY(x,1,Title);
    CTOS_LCDTSetReverse(FALSE);
    
    CTOS_LCDTPrintXY(1,2,line1);
    CTOS_LCDTPrintXY(1,3,line2);
    CTOS_LCDTPrintXY(1,4,line3);
    CTOS_LCDTSetReverse(TRUE);
    CTOS_LCDTPrintXY(1,8,"請按OK確定或按X取消");
      CTOS_LCDTSetReverse(FALSE);
  
 
    if(InputType==0)
           ret = CTOS_UIKeypad(6, 6,(STR **)keyboardLayoutNumber,200, 1, d_FALSE, d_FALSE, 0,bPasswordMask, buff,limit+1);
    else if(InputType==1)
           ret = CTOS_UIKeypad(6, 6,(STR **)keyboardLayoutNumberWithRadixPoint,200, 1, d_FALSE, d_FALSE, 0,bPasswordMask, buff,limit+1);
    else if(InputType==2)
          ret = CTOS_UIKeypad(6, 6,(STR **)keyboardLayoutEnglish,200, 1, d_FALSE, d_FALSE, 0,bPasswordMask, buff,limit+1);
 
    if(strlen(buff)==0)
        return d_ERR_CANCELBYUSER;
    return  ret;
    
}

int ShowInputBox(STR *Title,STR * line, BYTE * buff,int limit,int InputType,BYTE bPasswordMask)
{
    int ret;

    CTOS_KBDBufFlush();
  Setcolor(Color_white,Color_black);
 #ifdef TESTMODE
 
  if((gScrpitTesting==1)&&( ezxml_get(gTestAction, "AMT",-1)!=NULL)) 
{       
        ezxml_t ezxml_amt = ezxml_get(gTestAction, "AMT",-1);
        BYTE  *strbuf=ezxml_txt(ezxml_amt);   
        memcpy(buff,strbuf,strlen(strbuf));
      //  ezxml_free(ezxml_amt);
		return d_OK;
}
#endif	
    BYTE key;int i;USHORT usFontSize=Big_Font_Size;//d_FONT_16x30;
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
    CTOS_LCDTSelectFontSize(usFontSize);
    CTOS_LCDTClearDisplay();
    int Btnwidth = 30;
    int Btnlenght=320;
    int Windowwidth=240;
    int Windowlenght=320;
    int x=0,y=30;
    int  Row; 
    int Xoffset=0,Yoffset;
    int Titlesize=strlen(Title);//utf8
 //   CTOS_LCDBackGndColor (0x00e0c0 );
 //Draw a pixel on the canvas //
    Xoffset=(Windowlenght/2)-(((Titlesize/3)*16));
   
    CTOS_LCDTSetReverse(FALSE);
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
    CTOS_LCDTSelectFontSize(usFontSize);
    CTOS_LCDTClearDisplay();
     x = strlen(Title)/3;
     x=10-(x/2);
     CTOS_LCDTSetReverse(TRUE);
         CTOS_LCDTPrintXY(x,1,Title);
    CTOS_LCDTSetReverse(FALSE);
    
    CTOS_LCDTPrintXY(1,2,line);
  
   
    CTOS_LCDTPrintXY(1,5,"請按OK或按X    ");
     
  
 
    if(InputType==0)
           ret = CTOS_UIKeypad(6, 4,(STR **)keyboardLayoutNumber,200, 1, d_FALSE, d_FALSE, 0,bPasswordMask, buff,limit+1);
    else  if(InputType==1)
           ret = CTOS_UIKeypad(6, 4,(STR **)keyboardLayoutNumberWithRadixPoint,200, 1, d_FALSE, d_FALSE, 0,bPasswordMask, buff,limit+1);
    if(strlen(buff)==0)
        return d_ERR_CANCELBYUSER;
    return  ret;
    
}

int ShowInputBox2(STR *Title,STR * line1,STR * line2, BYTE * buff,int limit,int InputType,BYTE bPasswordMask)
{
    int ret;

    CTOS_KBDBufFlush();
    Setcolor(Color_white,Color_black);
 #ifdef TESTMODE
  
  if((gScrpitTesting==1)&&( ezxml_get(gTestAction, "AMT",-1)!=NULL)) 
{       
        ezxml_t ezxml_amt = ezxml_get(gTestAction, "AMT",-1);
        BYTE  *strbuf=ezxml_txt(ezxml_amt);   
        memcpy(buff,strbuf,strlen(strbuf));
     //   ezxml_free(ezxml_amt);
		return d_OK;
}
#endif	
    BYTE key;int i;USHORT usFontSize=Big_Font_Size;//d_FONT_16x30;
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
    CTOS_LCDTSelectFontSize(usFontSize);
    CTOS_LCDTClearDisplay();
    int Btnwidth = 30;
    int Btnlenght=320;
    int Windowwidth=240;
    int Windowlenght=320;
    int x=0,y=30;
    int  Row; 
    int Xoffset=0,Yoffset;
    int Titlesize=strlen(Title);//utf8
 //   CTOS_LCDBackGndColor (0x00e0c0 );
 //Draw a pixel on the canvas //
    Xoffset=(Windowlenght/2)-(((Titlesize/3)*16));
   
    CTOS_LCDTSetReverse(FALSE);
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE); 
    CTOS_LCDTSelectFontSize(usFontSize);
    CTOS_LCDTClearDisplay();
     x = strlen(Title)/3;
     x=10-(x/2);
     CTOS_LCDTSetReverse(TRUE);
         CTOS_LCDTPrintXY(x,1,Title);
    CTOS_LCDTSetReverse(FALSE);
    
    CTOS_LCDTPrintXY(1,2,line1);
    CTOS_LCDTPrintXY(1,3,line2);
    CTOS_LCDTSelectFontSize(Med_Font_Size);
    CTOS_LCDTSetReverse(TRUE);
    if(InputType!=2){
         CTOS_LCDTPrintXY(1,8,"請按<OK>確認或按<X>離開");
    }
    CTOS_LCDTSetReverse(FALSE);
     CTOS_LCDTSelectFontSize(usFontSize);
  
 
    if(InputType==0)
           ret = CTOS_UIKeypad(20, 4,(STR **)keyboardLayoutNumber,200, 1, d_FALSE, d_FALSE, 0,bPasswordMask, buff,limit+1);
    else  if(InputType==1)
           ret = CTOS_UIKeypad(20, 4,(STR **)keyboardLayoutNumberWithRadixPoint,200, 1, d_FALSE, d_FALSE, 0,bPasswordMask, buff,limit+1);
    else if(InputType==2){//for barcode reader use
          ret= CTOS_USBSelectMode ( d_USB_HOST_MODE );
//          gets(buff);
          ret= CTOS_USBSelectMode ( d_USB_DEVICE_MODE );
    }
    if(strlen(buff)==0)
        return d_ERR_CANCELBYUSER;
    
   
    return  ret;
    
}

