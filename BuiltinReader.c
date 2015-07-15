
#define APDU_CMD_DELAY_TIME				(2)

//#include "type.h"

#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>
#include <ctos_clapi.h>
#include "ECCAPP.h"

UART_RECIEVE_INFO g_sUart0RecieveInfo;
UART_SEND_INFO    g_sUart0AnswerInfo;

volatile unsigned int g_iUart0TimeOutDelay	= 0;
volatile unsigned int g_iUart0RecieveOK		= 0;
volatile unsigned int g_iRecieveSta			= 0;
volatile unsigned int g_iExpectedByteCount	= 0;
volatile unsigned int g_iCurrentByteCount	= 0;
volatile unsigned char g_cUart0XORCheck		= 0;
volatile unsigned char g_iEDCErrFlag		= 0;
volatile unsigned char  g_AutoBaudrate		= 0;
unsigned char g_cCheckBaudFlag		 = 0;		//????i?S?v?x
unsigned int  g_iBaudFlagCounters = 0;			//add for KMS autoBaudRate at 20080409
unsigned char g_cProtectFlag		 = 0;		//?}?a?O?@?x
unsigned char g_SerialPortMode;

void Reader_CLEAR_LED()
{
    
    USHORT mkHWSupport=Eth_CheckDeviceSupport();
    
   if(( mkHWSupport & d_MK_HW_CONTACTLESS)!=d_MK_HW_CONTACTLESS)
       return;
    
	CTOS_CLLEDSet(0x0f, d_CL_LED_BLUE);	
//	CTOS_CLLEDSet(d_LED1|d_LED2|d_LED3,d_OFF);

	return;
}

void Reader_TXN_LED()
{
    USHORT mkHWSupport=Eth_CheckDeviceSupport();
     if(( mkHWSupport & d_MK_HW_CONTACTLESS)!=d_MK_HW_CONTACTLESS)
       return;
     CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);	
    
}

void Reader_FINISHED_LED()
{
   USHORT mkHWSupport=Eth_CheckDeviceSupport();
    if(( mkHWSupport & d_MK_HW_CONTACTLESS)!=d_MK_HW_CONTACTLESS)
       return;
    CTOS_LEDSet(0x0f, d_CL_LED_GREEN);
        return;
}

void Reader_ERR_LED()
{
    USHORT mkHWSupport=Eth_CheckDeviceSupport();
    if(( mkHWSupport & d_MK_HW_CONTACTLESS)!=d_MK_HW_CONTACTLESS)
       return;
  
	CTOS_LEDSet(0x0f, d_CL_LED_RED);
	CTOS_CLSound(1200, 20);
	
	return;
}
void SerialPortDataSend(unsigned char* cData,unsigned short lenght)
{
	
	ULONG StartTime;
	USHORT recLen=0, RTN ;
	
	StartTime  = CTOS_TickGet();

	do
	{
		if(g_SerialPortMode==2)
			RTN = CTOS_RS232TxReady( d_COM1 );
		else
			RTN = CTOS_USBTxReady();
		
	}
	while(((StartTime+APDU_CMD_DELAY_TIME) > CTOS_TickGet()) && RTN != d_OK );

	if(RTN == d_OK)
	{
		if(g_SerialPortMode==2)
			CTOS_RS232TxData( d_COM1, cData, lenght );
		else
			CTOS_USBTxData( cData, lenght );
	}
	
	if(g_SerialPortMode==2)
		CTOS_RS232FlushRxBuffer(d_COM1);
	else
		CTOS_USBRxFlush();
		
}


void SerialPortAnswer(unsigned char cBodyLen)
{
	unsigned short i;
	unsigned char cXorCheck = 0;
	unsigned char adpuBuff[300];

	g_sUart0AnswerInfo.cProLog[0] = 0x00;
	g_sUart0AnswerInfo.cProLog[1] = 0x00;
	g_sUart0AnswerInfo.cProLog[2] = cBodyLen+2;

	//?p?????
	cXorCheck ^= g_sUart0AnswerInfo.cProLog[0];
	cXorCheck ^= g_sUart0AnswerInfo.cProLog[1];
	cXorCheck ^= g_sUart0AnswerInfo.cProLog[2];
	cXorCheck ^= g_sUart0AnswerInfo.cSW[0];
	cXorCheck ^= g_sUart0AnswerInfo.cSW[1];

	for(i=0; i<cBodyLen; i++)
	{
		cXorCheck ^= g_sUart0AnswerInfo.cInfoBody[i];
	}

	g_sUart0AnswerInfo.cEDC = cXorCheck;
	
	i = 0 ;
	memcpy(adpuBuff,g_sUart0AnswerInfo.cProLog,3);
	i+=3;
	memcpy(adpuBuff+i,g_sUart0AnswerInfo.cInfoBody,cBodyLen);
	i+=cBodyLen;	
	//send SW1,SW2
	memcpy(adpuBuff+i,g_sUart0AnswerInfo.cSW,2);
	i+=2;	
	//send EDC
	memcpy(adpuBuff+i,&g_sUart0AnswerInfo.cEDC,1);
	i+=1;	
	SerialPortDataSend(adpuBuff,i);
	return;
}
unsigned short CheckSerialPortMode(void)
{
	
	unsigned short iSw;
	USHORT recLen=0;
	int transfer_cnt = 0;
	
	// Wait until the ent zire command header is arrived in the driver buffer
	//g_SerialPortMode = 0;		//0~1:???w, 2:RS232, 3:USB
	if(g_SerialPortMode==2)
	{
		do
		{
			iSw = CTOS_RS232RxReady(d_COM1, &recLen);
			transfer_cnt++;
			if(transfer_cnt>1000) return SERIAL_PORT_NO_DATA_ERR;
		} while ( ( iSw != d_OK ) || ( recLen < 3 ) );
	}
	else if(g_SerialPortMode==3)
	{
		do
		{
			iSw = CTOS_USBRxReady(&recLen);
			transfer_cnt++;
			if(transfer_cnt>1000) return SERIAL_PORT_NO_DATA_ERR;
		} while ( ( iSw != d_OK ) || ( recLen < 3 ) );
	}
	else
	{
		do
		{
			if(g_SerialPortMode == 0)
			{
				iSw = CTOS_RS232RxReady(d_COM1, &recLen);
				g_SerialPortMode = 1;
			}
			else
			{
				iSw = CTOS_USBRxReady(&recLen);
				g_SerialPortMode = 0;
			}
	
			transfer_cnt++;
			if(transfer_cnt>100) return SERIAL_PORT_NO_DATA_ERR;
	
		} while ( ( iSw != d_OK ) || ( recLen < 3 ) );
	}
	
	if(g_SerialPortMode == 0)
		g_SerialPortMode = 3;
	else if(g_SerialPortMode == 1)
		g_SerialPortMode = 2;

	return OPERATION_OK;
}

unsigned short getADPUDataFromSerialPort(void)
{
	
	unsigned short iSw;
	
	
	USHORT recLen=0, temp = 0, data_field_length=0, RTN , revTotalLenght =0;
	BYTE recBuf[300];
	unsigned char CheckEDC = 0;
	int i, transfer_cnt = 0;	
	ULONG tick;	
	ULONG StartTime;	


	g_iUart0RecieveOK = 0;
	
	iSw = CheckSerialPortMode();
	if(iSw != OPERATION_OK )
		return iSw;

	revTotalLenght = 0;
	StartTime  = CTOS_TickGet();
	while(1)
	{

		if(g_SerialPortMode==2)
			RTN = CTOS_RS232RxReady(d_COM1, &recLen);
		else
			RTN = CTOS_USBRxReady(&recLen);
		if(RTN ==d_OK)
		{
			if(g_SerialPortMode==2)
				RTN = CTOS_RS232RxData(d_COM1, &recBuf[revTotalLenght], &recLen);
			else
				RTN = CTOS_USBRxData(&recBuf[revTotalLenght], &recLen);
			if(RTN==d_OK)
			{
				revTotalLenght += recLen;
				/*reflash timer*/
				if(recLen > 0)
					StartTime  = CTOS_TickGet();
				
				/*First data = 0*/
				if(revTotalLenght==0)
					return SERIAL_PORT_NO_DATA_ERR;
			}
		}
		
		if(revTotalLenght >=7)
		{
			/*check auto baudrate*/
			if((memcmp(recBuf,"\x55\x55\x55\x55\x55\x55\x55",7)==0) ||
				(revTotalLenght >=9 && (memcmp(recBuf,"\x55\x55\x55\x55\x55\x55\x55\x55\x55",9)==0))  )
			{				
				//CTOS_LCDTPrintXY(1, 1, "XXXXXXXXXXXX");
				/*因為spec 有7 or 9 byte 0x55需要把後面的收完*/
				/*CTOS_Delay(APDU_CMD_DELAY_TIME*10);*/	
				if(g_SerialPortMode==2)
					CTOS_RS232FlushRxBuffer(d_COM1);
				else
					CTOS_USBRxFlush();					
				iSw = OPERATION_OK;
				g_sUart0AnswerInfo.cSW[0] = (unsigned char)(iSw >>8);
				g_sUart0AnswerInfo.cSW[1] = (unsigned char)iSw;
				//Main_Uart0Answer(0);
				
				return SERIAL_PORT_AUTO_BAUD_RATE;
			}
			else
			{
				/*check fist 2 bytes and len byte range*/
				if(memcmp(recBuf,"\x00\x00",2)!=0 || recBuf[2] < 4)
				//if(memcmp(recBuf,"\x00\x00",2)!=0 || recBuf[2] < 5)
				{
					CTOS_Delay(APDU_CMD_DELAY_TIME*10);
					if(g_SerialPortMode==2)
						CTOS_RS232FlushRxBuffer(d_COM1);
					else
						CTOS_USBRxFlush();
					return SERIAL_PORT_ADPU_DATA_FORMAT_ERR;
				}
				
				/*check adpu data*/
				if(revTotalLenght >= (recBuf[2] + 1 + 3))
				{
					CheckEDC = 0;
					for ( i = 0 ; i < (recBuf[2] + 3) ; i++ )
					{
						CheckEDC = CheckEDC ^ recBuf[i];
					}
					if (CheckEDC != recBuf[(recBuf[2] + 3)])
					{
						//CTOS_LCDTPrintXY(1, 1, "1");
						//U0Printf("CheckEDC=%02X--%02X",CheckEDC,recBuf[(recBuf[2] + 3)]);
						//U0Printf("%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X",recBuf[0],recBuf[1],recBuf[2],recBuf[3],recBuf[4],recBuf[5],recBuf[6],recBuf[7],recBuf[8]);
						iSw = EDC_ERR;
						g_sUart0AnswerInfo.cSW[0] = (unsigned char)(iSw >>8);
						g_sUart0AnswerInfo.cSW[1] = (unsigned char)iSw;
						//Main_Uart0Answer(0);
						return iSw;						
					}
					break;		
				}
			}
		}


		
		/*Rev Data Timeout*/
		if((StartTime+APDU_CMD_DELAY_TIME) < CTOS_TickGet())
		{
			/*REV > 1 have data shift*/
			if(revTotalLenght!=0)
			{
				CTOS_Delay(APDU_CMD_DELAY_TIME*10);
				if(g_SerialPortMode==2)
					CTOS_RS232FlushRxBuffer(d_COM1);
				else
					CTOS_USBRxFlush();
			}
			return SERIAL_PORT_REV_TIMEOUT_ERR;
		}
	}

	/*
	if(g_SerialPortMode==2)
		CTOS_RS232FlushRxBuffer(d_COM1);
	else
		CTOS_USBRxFlush();
	*/
	memcpy( g_sUart0RecieveInfo.cProLog, recBuf, 3 );
	memcpy( g_sUart0RecieveInfo.cInfoHeader, recBuf+3, 4 );
	memcpy( g_sUart0RecieveInfo.cInfoBody, recBuf+7, recBuf[2] - 4 );

	g_sUart0RecieveInfo.cEDC=CheckEDC;
	g_iUart0RecieveOK = 1;
	
	/*=================================================================================================================================================*/
	/*=================================================================================================================================================*/
	return OPERATION_OK;
}

int BuiltinReader_Answer(unsigned char * adpuBuff,unsigned char cBodyLen)
{
	unsigned short i;
	unsigned char cXorCheck = 0;
	//unsigned char adpuBuff[300];
 
	g_sUart0AnswerInfo.cProLog[0] = 0x00;
	g_sUart0AnswerInfo.cProLog[1] = 0x00;
	g_sUart0AnswerInfo.cProLog[2] = cBodyLen+2;

	//?p?????
	cXorCheck ^= g_sUart0AnswerInfo.cProLog[0];
	cXorCheck ^= g_sUart0AnswerInfo.cProLog[1];
	cXorCheck ^= g_sUart0AnswerInfo.cProLog[2];
	cXorCheck ^= g_sUart0AnswerInfo.cSW[0];
	cXorCheck ^= g_sUart0AnswerInfo.cSW[1];

	for(i=0; i<cBodyLen; i++)
	{
		cXorCheck ^= g_sUart0AnswerInfo.cInfoBody[i];
	}

	g_sUart0AnswerInfo.cEDC = cXorCheck;
	
	i = 0 ;
	memcpy(adpuBuff,g_sUart0AnswerInfo.cProLog,3);
	i+=3;
	memcpy(adpuBuff+i,g_sUart0AnswerInfo.cInfoBody,cBodyLen);
	i+=cBodyLen;	
	//send SW1,SW2
	memcpy(adpuBuff+i,g_sUart0AnswerInfo.cSW,2);
	i+=2;	
	//send EDC
	memcpy(adpuBuff+i,&g_sUart0AnswerInfo.cEDC,1);
	i+=1;	
	
	return i;
}

int BuiltinReader_CMDSendReceive(BYTE * cmd,int cmdlen,BYTE * Data,int *Datalen)
{
    unsigned short swcode;	
    unsigned char RspAnswerLen;
    unsigned char SWStr[16];
    unsigned char key;
    int iret;
  
    memset(&g_sUart0RecieveInfo,0x00,sizeof(g_sUart0RecieveInfo));
   // memcpy(&g_sUart0RecieveInfo.cProLog,&cmd[0],3);
  
   // memcpy(&g_sUart0RecieveInfo.cInfoHeader,&cmd[3],4);
  
  //  memcpy(&g_sUart0RecieveInfo.cInfoBody,&cmd[3+4],cmdlen-3-4-1);

    memcpy( g_sUart0RecieveInfo.cProLog, cmd, 3 );
    memcpy( g_sUart0RecieveInfo.cInfoHeader, cmd+3, 4 );
    memcpy( g_sUart0RecieveInfo.cInfoBody, cmd+7, cmd[2] - 4 );

    unsigned char CheckEDC;
    int i;
    CheckEDC = 0;
    for ( i = 0 ; i < (cmd[2] + 3) ; i++ )
	{
		CheckEDC = CheckEDC ^ cmd[i];
	}
	if (CheckEDC != cmd[(cmd[2] + 3)])
	{
		
         int   iSw = EDC_ERR;
	   g_sUart0AnswerInfo.cSW[0] = (unsigned char)(iSw >>8);
	   g_sUart0AnswerInfo.cSW[1] = (unsigned char)iSw;
	   return iSw;						
        }


    
    g_sUart0RecieveInfo.cEDC=CheckEDC;
    g_iUart0RecieveOK = 1;
   
 //   DebugPrint_hex(&g_sUart0RecieveInfo.cProLog,sizeof(g_sUart0RecieveInfo.cProLog),"cProLog",DebugMode_ALL);  
 //   DebugPrint_hex(&g_sUart0RecieveInfo.cInfoHeader,sizeof(g_sUart0RecieveInfo.cInfoHeader),"cInfoHeader",DebugMode_ALL);  
 //   DebugPrint_hex(&g_sUart0RecieveInfo.cInfoBody,sizeof(g_sUart0RecieveInfo.cInfoBody),"cInfoBody",DebugMode_ALL);  
 //   DebugPrint_hex(&g_sUart0RecieveInfo.cEDC,sizeof(g_sUart0RecieveInfo.cEDC),"cEDC",DebugMode_ALL);  
unsigned long ulTick = CTOS_TickGet();   
int p1=ulTick;
BYTE  baMsg[16];
 

    swcode = Ts_Uart0InfoProcess();       
    RspAnswerLen=Tscc_cAnswerLen;
    sprintf(SWStr,"%04x",swcode);
  //   DebugPrint_hex(&swcode,sizeof(swcode),"swcode",DebugMode_ALL); 
 //   ShowMessage2line("讀卡機模式","SW:",SWStr,Type_ComformNONE);
 /*  p1=(CTOS_TickGet() - ulTick) ;      
    sprintf(baMsg, "Ts_Uart0InfoProcess:%ldms", p1);
    CTOS_PrinterPutString(baMsg);      
*/

    *Datalen=BuiltinReader_Answer(Data,RspAnswerLen);
    
    g_iUart0RecieveOK = 0;
    return SUCCESS;
}
USHORT ReaderCommandMode()
{
  
	unsigned short swcode;	
	unsigned char RspAnswerLen;
      
	CTOS_RS232Close( d_COM1 );
	
	CTOS_RS232Open( d_COM1, 115200, 'N', 8, 1 );		
	
	CTOS_USBClose(  );
	
	CTOS_USBOpen(  );
	/*==============================================================*/
	g_SerialPortMode = 2;	
	g_iUart0RecieveOK = 0;
	/*==============================================================*/
	Ts_SystemParamentInialize();	     
        ShowMessage2line("讀卡機模式","請由USB或RS232","發送指令",Type_ComformNONE);
        unsigned char SWStr[16];
        unsigned char key;
        int iret;
	while(1)
	{       
             
                memset(SWStr,0x00,sizeof(SWStr));
		swcode =getADPUDataFromSerialPort();
		if(g_iUart0RecieveOK != 0)/*??command*/
		{			
			//unsigned char loop;	
  //  DebugPrint_hex(&g_sUart0RecieveInfo.cProLog,sizeof(g_sUart0RecieveInfo.cProLog),"cProLog",DebugMode_ALL);  
 //   DebugPrint_hex(&g_sUart0RecieveInfo.cInfoHeader,sizeof(g_sUart0RecieveInfo.cInfoHeader),"cInfoHeader",DebugMode_ALL);  
  //  DebugPrint_hex(&g_sUart0RecieveInfo.cInfoBody,sizeof(g_sUart0RecieveInfo.cInfoBody),"cInfoBody",DebugMode_ALL);  
  ///  DebugPrint_hex(&g_sUart0RecieveInfo.cEDC,sizeof(g_sUart0RecieveInfo.cEDC),"cEDC",DebugMode_ALL);  
	   	     //  CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
                    USHORT  mkHWSupport=Eth_CheckDeviceSupport();
                     
                    if(( mkHWSupport & d_MK_HW_CONTACTLESS)==d_MK_HW_CONTACTLESS)
                    {   
                       CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
                    }
                      swcode = Ts_Uart0InfoProcess();
			RspAnswerLen=Tscc_cAnswerLen;
                        sprintf(SWStr,"%04x",swcode);
                        if(swcode==0x9000)
                            Reader_FINISHED_LED();
                       else
                            Reader_ERR_LED();
  //  DebugPrint_hex(&swcode,sizeof(swcode),"swcode",DebugMode_ALL);  
                        ShowMessage2line("讀卡機模式","SW:",SWStr,Type_ComformNONE);
		/*	if(swcode == CLA_ERR || swcode == INS_ERR || swcode == P1_P2_ERR || swcode == PRET_CLA_INS_ERR || swcode == PRET_P1_P2_ERR)
			{
                       
			}*/                  
                        //U0Printf("*g_sUart0AnswerInfo =%X",g_sUart0AnswerInfo);
			SerialPortAnswer(RspAnswerLen);
                        g_iUart0RecieveOK = 0;
                        CTOS_KBDHit(&key);
                        if(key==d_KBD_CANCEL){
                            iret = ShowMessage3line("讀卡機模式","是否退出讀卡機模式?","繼續請按<OK>","",Type_ComformOK);
                            if(iret==d_FAIL){
                                  break;
                                }
                        } 
		}
	}
       
	return 0;
}
USHORT BuiltinReader_ShowInfo()
{
    USHORT ret;
    return ret;
}
USHORT TurnOffReader()
{
   USHORT ret= CTOS_CLPowerOff();
     CTOS_CLCloseComm();
   return ret;
}
int InitBuiltinReader()
{
      BYTE baSCK[16] = {"EASYCARDEASYCARD"};
      int  iSw = CTOS_CLInitComm(38400);
      if(iSw != d_OK&& iSw!=0x833c)
      {
          BYTE SWStr[16];  
          sprintf(SWStr,"%04x",iSw);
          ShowMessage2line("讀卡機","SW:",SWStr,Type_ComformCheck);
           return iSw;
      }
      CTOS_CLInit();
     //重建讀卡機加密session key
     USHORT ret = CTOS_InjectSecureCommKey(baSCK, 16);
      if(ret != d_OK)
      {
          BYTE SWStr[16];  
          sprintf(SWStr,"%04x",iSw);
          ShowMessage2line("讀卡機","ICS SW:",SWStr,Type_ComformCheck);
          return iSw;
      }
     
        
      ret = CTOS_EstablishSecureComm();
       if(ret != d_OK)
      {
          BYTE SWStr[16];  
          sprintf(SWStr,"%04x",iSw);
          ShowMessage2line("讀卡機","ESC SW:",SWStr,Type_ComformCheck);
          return iSw;
      }
      //
      iSw=CTOS_CLPowerOn();
      //INIT_NEW_HW_SYSTEM();
      Ts_SystemParamentInialize();
     
      int i;
     CTOS_CLLEDSet(0x0f, d_CL_LED_RED);
     CTOS_CLLEDSet(0x0f, d_CL_LED_GREEN);
     CTOS_CLLEDSet(0x0f, d_CL_LED_YELLOW);
     CTOS_CLLEDSet(0x0f, d_CL_LED_BLUE);
   
    
  
      return iSw;
}
USHORT Reader_IsSupportBuildinReader()
{
   BOOL fPortable,fPCI;
   USHORT mkHWSupport;
   USHORT usRet= CTOS_HWSettingGet(&fPortable,&fPCI,&mkHWSupport);  
   if((mkHWSupport &d_MK_HW_CONTACTLESS)==d_MK_HW_CONTACTLESS)
       return TRUE;
   else 
       return FALSE;
 
}
int InitReader()
{
  int inRetVal ;
    USHORT ret;
    BYTE RS232STR[64];
    memset(RS232STR,0x00,sizeof(RS232STR));
   // MechineStatus=0;
  //  sprintf(gConfig.DEVICE.READER.bPORT,"Builtin");
   if(Reader_IsSupportBuildinReader())
   {    
     if(strcmp(gConfig.DEVICE.READER.bPORT,"COM2")==0){
         sprintf(gConfig.DEVICE.READER.bPORT,"Builtin");
         ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE","READER","PORT",gConfig.DEVICE.READER.bPORT);
     }
   }else{
      if(strcmp(gConfig.DEVICE.READER.bPORT,"Builtin")==0){
         sprintf(gConfig.DEVICE.READER.bPORT,"COM2");
         ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE","READER","PORT",gConfig.DEVICE.READER.bPORT);
     } 
   }
  
    if(strcmp(gConfig.DEVICE.READER.bPORT,"Builtin")==0){
       inRetVal= InitBuiltinReader();
    }else{
      
         inRetVal= CTOS_RS232Open(gREADERPORT.Portnum,gREADERPORT.ulBaudRate , gREADERPORT.bParity, gREADERPORT.bDataBits, gREADERPORT.bStopBits);
         if(inRetVal!=d_OK){ 
            SystemLogInt("InitReader",inRetVal,"CTOS_RS232Open Fail");
            MechineStatus |= Status_READER_Disconnect;
            memset(RS232STR,0x00,sizeof(RS232STR));
            sprintf(RS232STR,"讀卡機測試:COM PORT無法開啟");
         }
           
       return inRetVal;
    }
    return inRetVal;
}