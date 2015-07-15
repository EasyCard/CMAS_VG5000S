#include "ECCAPP.h"


void Script_Test(void)
{
	
 ezxml_t  TestScript,TestCase;
 TestScript=LoadXMLFile(TestScrpitFile);
 CTOS_PrinterPutString("TEST SCPRIT ");
 CTOS_PrinterPutString(TestScript->name);
 TestCase=TestScript->child;
 while(TestCase!=NULL)
 {
        CTOS_PrinterPutString("________________________");
        ReadTestCase(TestCase);
       	TestCase=TestCase->next;
        CTOS_PrinterPutString("________________________");
 }
 ezxml_free(TestScript);
}
//USHORT ShowActionMessage(STR * title,ezxml_t * Action)
USHORT ShowActionMessage(STR * title,ezxml_t Action)
 {
    BYTE str1[128],str2[128],str3[128],str4[128];
    
    memset(str1,0x00,sizeof(str1));
    memset(str2,0x00,sizeof(str2));
    memset(str3,0x00,sizeof(str3));
    memset(str4,0x00,sizeof(str4));
    ezxml_t  ezxml_DATA = ezxml_child((ezxml_t)Action, "message");
    if(ezxml_DATA==NULL) return d_Fail;
    ezxml_DATA = ezxml_get((ezxml_t)Action,"message",0, "message1",-1);
    sprintf(str1,"%s",ezxml_txt(ezxml_DATA));
  
    ezxml_DATA = ezxml_get((ezxml_t)Action,"message",0, "message2",-1);
    sprintf(str2,"%s",ezxml_txt(ezxml_DATA));
    
   ezxml_DATA = ezxml_get((ezxml_t)Action,"message",0, "message3",-1);
   sprintf(str3,"%s",ezxml_txt(ezxml_DATA));
   
    ezxml_DATA = ezxml_get((ezxml_t)Action,"message",0, "message4",-1);
    sprintf(str4,"%s",ezxml_txt(ezxml_DATA));
   
   
    USHORT ret=ShowMessage4line(title,str1,str2,str3,str4,Type_ComformOK);
    return ret;
 }
void ReadTestCase(ezxml_t TestCase)
{	
    ezxml_t ezAction =TestCase->child;
    int loop;
    const char *loopstr;
    STR * ActionName;
    STR str[128];
    BYTE key;
    memset(str,0x00,sizeof(str));
     ULONG ulUsedDiskSize ,ulTotalDiskSize, ulUsedRamSize, ulTotalRamSize; 
    while(ezAction!=NULL)
    {     
            ActionName=(STR*)ezxml_attr(ezAction, "name");
            if (ActionName== NULL) continue;
            
           loopstr= ezxml_attr(ezAction,"LOOP");
           if(loopstr!=NULL)
               loop=atoi(loopstr);
           else
               loop=1;
           
          ShowActionMessage(ActionName,ezAction);
          gScrpitTesting=1;   
          gDebugPrintFlag=DebugMode_TestScrpit;  
          gTestAction=ezAction;
        //  CTOS_PrinterPutString("ACTION NAME");
        //  CTOS_PrinterPutString(ezAction->name);
           do{
            if(strcmp(ActionName,"SIGNON")==0){
                   Function_Signon();
            }else if(strcmp(ActionName,"DEDUCT")==0){
                   Trans_Deduct();
            }else if(strcmp(ActionName,"VOID")==0){
                   Trans_Cancel();
            } else if(strcmp(ActionName,"SETTLEMENT")==0){
                Process_Settle();
            } 
            loop--;
            gScrpitTesting=0;   
            gDebugPrintFlag=0;
            sprintf(str,"LOOP剩餘次數:%d",loop);
             ShowMessage4line("單元測試","測試項目",ActionName,str,"欲中斷請按(X)",Type_ComformNONE); 
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
                    gConfig.DEVICE.MEMORY.TOTALRAMSIZE,Type_ComformNONE); 
  
            CTOS_KBDHit(&key);
            if(key==d_KBD_CANCEL) return ;
            
           }while(loop>0);
            ezAction=ezAction->next;
    }
}


USHORT ShowTestCaseNodeInfo(STR * title,ezxml_t NODE)
{
   // System_struct SysInfo;
    USHORT ret;
    BYTE key;
    menu_item menu[20];
    ezxml_t N,ITEM;
    STR titleName[16];
    int i;
    memset(menu,0x00,sizeof(menu));
    
    i=0;
  
    N=NODE;
    while(N!=NULL)     
        {  
           GetXmlNodeattr_Name(N,menu[i].itemname);
           menu[i].enable=TRUE;
           menu[i].visible=TRUE;
           menu[i].node=N;
           N=N->sibling;     
           i++;
        }     
    STR *loopstr;
    STR str[128];
    memset(str ,0x00,sizeof(str));
   int selectitem; 
  
   int loop=0;
  do{
       selectitem= ECC_SelectListMeun(title,menu,i);
       if(selectitem <0)
           break;
      loopstr =(STR*)ezxml_attr(menu[selectitem].node,"LOOP");
      if(loopstr!=NULL)
           loop= atoi(loopstr);
      else
           loop=1;
       do{
              ReadTestCase( menu[selectitem].node);
              CTOS_Delay(1000);
            sprintf(str,"剩餘次數:%d/%s",loop,loopstr);
             ShowMessage4line("單元測試","測試劇本",menu[selectitem].itemname,str,"欲中斷請按(X)",Type_ComformNONE); 
     
          CTOS_KBDHit(&key);
          if(key==d_KBD_CANCEL) break ;
              loop--;
       }while(loop>0);
       
   }while(1);
   
   return ret;
}

USHORT ShowTestCase(void)
{
   // System_struct SysInfo;
    USHORT ret;
    int iret;
    BYTE key;

    ezxml_t NODE;
    STR title[16]="";
    int i;
    ezxml_t  TestScript;
    TestScript=LoadXMLFile(TestScrpitFile);
  
    i=0;

   NODE=TestScript;
    if(NODE ==NULL)
    {return -1;}
   
    
   GetXmlNodeattr_Name(NODE,title);
   NODE =NODE->child;
   ret= ShowTestCaseNodeInfo(title,NODE);
  
   ezxml_free(TestScript);
  
    return 0;
}