#include "ECCAPP.h"


void usbInitial(void *p1)
{
    USB_OBJ *usb = (USB_OBJ*)p1;
    memset(usb, 0x00, sizeof(USB_OBJ));
    
    usb->open = inUsbOpenComport;
    usb->sendData = inUsbSendData;    
    usb->recvData = inUsbRecvData;
    usb->close = inUsbCloseComport;
}
    
int inUsbOpenComport(void *p1)
{
    int result;
    USB_OBJ *usb = (USB_OBJ*)p1;
    
    result=CTOS_USBSelectMode(d_USB_DEVICE_MODE);
    result=usb->close(usb);
    
    if((result = CTOS_USBOpen()) != d_OK)
    {
        /*open fail*/
        CTOS_Beep();
    }
    
    return result; 
}


int inUsbSendData(void *p1, void *p2, ULONG size)
{
    USB_OBJ *usb = (USB_OBJ*)p1;
    BYTE *data = (BYTE*)p2;
    //BYTE *buffer;
    BYTE temp[512];
    USHORT len;
    int i;
    BYTE sendCnt;
    BYTE log[2048];
    
    while(CTOS_USBTxReady() != d_OK);
    if(CTOS_USBTxData(data, size) != d_OK)    
    {              
        CTOS_Beep();        
        return USB_SEND_FAIL;        
    }     
    //free(buffer);
        
    //CTOS_Delay ( 1000 );
   if(usb->waitACKCnt>0)        
    {        
            len=0;     
            sendCnt=2;           
            CTOS_TimeOutSet(TIMER_ID_3, 200);//2 Sec Timeout
            //sprintf(log,"set timer, now tick(%ul)",CTOS_TickGet());
            //CTOS_PrinterPutString(log);
            do
            {                                
                if(CTOS_TimeOutCheck(TIMER_ID_3) == d_YES)//TimeOut
                {
                    //sprintf(log,"Timeout, now tick(%ul)",CTOS_TickGet());
                    //CTOS_PrinterPutString(log);
                    if(sendCnt == 0) break;//already sended 3times, and Time is up, break while loop 
                        
                    //sprintf(log,"tick(%ul)",CTOS_TickGet());                        
                    //CTOS_PrinterPutString(log);                        
                    while(CTOS_USBTxReady() != d_OK);                                                
                    if(CTOS_USBTxData(data, size) != d_OK)                                
                    {                                                             
                        CTOS_Beep();                   
                    }  
                        
                    sendCnt--;                        
                    //sprintf(log,"response Cnt(%d)",sendCnt);
                    //CTOS_PrinterPutString(log);
                    
                    SystemLog("USB_inSendData",log);    
                    CTOS_TimeOutSet(TIMER_ID_3, 200);//2 Sec Timeout  
                    //sprintf(log,"set timer, now tick(%ul)",CTOS_TickGet());
                    //CTOS_PrinterPutString(log);
                }
                else
                {
                    CTOS_USBRxReady(&len);
                    if(len>0)
                    {
                        memset(temp,0x00,sizeof(temp));
                        len = (len>sizeof(temp))?sizeof(temp):len;
                        CTOS_USBRxData(temp, &len);
                        for(i=0; i<len; i++)                    
                            if(temp[i] == ACK) break;//great, got ACK                        
                    
                        if(i!=len)//not equal, got ACK, exit while loop                            
                            break;
                        //else
                        //    CTOS_PrinterPutString("loop, no ACK found");
                    }                
                }            
            }while(sendCnt>=0);
    }
    
     if(sendCnt<=0)//no ACK        
     {          
         //CTOS_PrinterPutString("No ACK");                        
         sprintf(log,"No ACK (%04X)",temp[0]);                                            
         SystemLog("USB_inSendData",log);                        
         return RS232_FORMAT_ERROR;                           
     }
    
    return d_OK;
}

/*
int inUsbSendData(void *p1, void *p2, ULONG size)
{
    
    USB_OBJ *usb = (USB_OBJ*)p1;
    BYTE *data = (BYTE*)p2;
    //BYTE *buffer;
    BYTE temp[16];
    USHORT len;
    int j;
    BYTE sendCnt;
    BYTE log[1024];
    
    //if((buffer=malloc(size+3))==NULL)return COMM_MEMORY_FAIL;
    
    //sprintf(buffer,"%c%s%c",0x02,data,0x03);
    
    while(CTOS_USBTxReady() != d_OK);
    if(CTOS_USBTxData(data, size) != d_OK)    
    {              
        CTOS_Beep();   
        //free(buffer);
        return USB_SEND_FAIL;        
    }     
    //free(buffer);
      
    if(usb->waitACKCnt>0)        
    {        
            len=0;     
            sendCnt=3;
            //CTOS_RS232RxReady(usb->protocal.comport, &len);                
            do
            {                    
                //j=len;            
                CTOS_Delay ( 2000 );             
                CTOS_USBRxReady(&len);
                
                if(len==0)
                {
                    while(CTOS_USBTxReady() != d_OK);                        
                    if(CTOS_USBTxData(data, size) != d_OK)        
                    {                                      
                        CTOS_Beep();                        
                    }  
                    sendCnt--;
                    sprintf(log,"response Cnt(%d)",sendCnt);
                    SystemLog("USB_inSendData",log);
                }
                else
                    break;
                
            }while(sendCnt>0);
            memset(temp,0x00,sizeof(temp));
            CTOS_USBRxData(temp, &len);
            if(temp[0]!=ACK)
            {
                sprintf(log,"not ACK (%04X)",temp[0]);                    
                SystemLog("USB_inSendData",log);
                return USB_FORMAT_ERROR;        
            }
    }
    return d_OK;
}
*/
int inUsbRecvData(void*p1)
{
   USB_OBJ *usb = (USB_OBJ*)p1;    
    
    USHORT len;
    int j;
    int result;
    BYTE temp[16];
    BYTE log[2048]; 
    
    len=0;
    result=COMM_ESCAPE;
    if((CTOS_USBRxReady(&len)) == d_OK && len>0)//got data in
    {        
        /*Recv Data*/
        do
        {
                j=len;
                CTOS_Delay ( 100 ); 
                CTOS_USBRxReady(&len);
        }while(j!=len);  
        
        usb->recvSize = len;
        result = len;                
    }
    else//no data in
        return COMM_ESCAPE;

    sprintf(log,"USB Recv Data Total Len(%d) Finish",len);
    SystemLog("USB_inUsbRecvData",log);
    //allocate memory
    if((usb->recvMsg = calloc(len+1,sizeof(BYTE)))==NULL)
        return COMM_MEMORY_FAIL;
   
    CTOS_USBRxData(usb->recvMsg,&(usb->recvSize));
    
    
    
    //if(usb->recvMsg[0] == 0x02 && usb->recvMsg[usb->recvSize-1] == 0x03)            
    if(inUsbCheckDataCompleteness(usb) == d_OK)
    {    
        /*response ACK*/
        while(CTOS_USBTxReady() != d_OK);
        //sprintf(temp,"%c",ACK);
        memset(temp,0x00,sizeof(temp));
        for(j=0;j<usb->sendACKCnt;j++)sprintf(temp+j,"%c",ACK);
        
        if(CTOS_USBTxData(temp, strlen(temp)) != d_OK)
        {
                //CTOS_Beep();
                //free(usb->recvMsg);
                //usb->recvMsg=NULL;
                return USB_SEND_FAIL;
        }
        /*simulator process received data*/                
        //CTOS_Delay ( 5000 );            
    }            
    else
    {
        //free(usb->recvMsg);
        //usb->recvMsg=NULL;
        /*response NAK*/
        while(CTOS_USBTxReady() != d_OK);
        //sprintf(temp,"%c",NAK);
        memset(temp,0x00,sizeof(temp));
        for(j=0;j<usb->sendACKCnt;j++)sprintf(temp+j,"%c",NAK);
        
        if(CTOS_USBTxData(temp, strlen(temp)) != d_OK)
        {
                CTOS_Beep();
                return USB_SEND_FAIL;
        }        
        return USB_FORMAT_ERROR;
    }
    
    SystemLog("USB_inUsbRecvData","End");
    return d_OK;
    
}

int inUsbCloseComport(void *p1)
{
    USB_OBJ* usb = (USB_OBJ*)p1;
    
    return CTOS_USBClose();
    
}

int inUsbCheckDataCompleteness(void*p1)
{
    USB_OBJ *usb = (USB_OBJ*)p1; 
    int result;
    BYTE buffer[64];
    BYTE lrc;
    int size;
    int i;
    int stxp;
    int etxp;
    
    stxp=-1;
    etxp=-1;
    result = d_OK;        
    if(usb->dataCheckType==ECR_VER_NORMAL)//normal version
    {
        usb->sendACKCnt=1;
        usb->waitACKCnt=1;
        if(usb->recvMsg[0] != 0x02 || usb->recvMsg[usb->recvSize-1] != 0x03)    
        {
            for(i=0; i<usb->recvSize; i++)
            {
                if(usb->recvMsg[i]==STX) stxp=i;
                else if(usb->recvMsg[i]==ETX)
                {
                    etxp=i;
                    break;
                }
            }
            
            if(stxp==-1 || etxp==-1 ) result =-1; //not found STX or ETX, so response NAK
            else
            {
                usb->recvSize = etxp-stxp+1;
                memcpy(usb->recvMsg, usb->recvMsg+stxp, usb->recvSize);
                usb->recvMsg[usb->recvSize] = 0x00;
            }
        }
            
    }
    else if(usb->dataCheckType==ECR_VER_HOSPITAL)//hospital version
    {
        usb->sendACKCnt=2;
        usb->waitACKCnt=2;
        if(usb->recvMsg[0] != 0x02 || usb->recvMsg[usb->recvSize-2] != 0x03)               
        {
            for(i=0; i<usb->recvSize; i++)
            {
                if(usb->recvMsg[i]==STX) stxp=i;
                else if(usb->recvMsg[i]==ETX)
                {
                    etxp=i+1;//next pos was LRC, so,include it.
                    break;
                }
            }
            
            if(stxp==-1 || etxp==-1 ) return -1; //not found STX or ETX, so response NAK
            else
            {
                usb->recvSize = etxp-stxp+1;
                memcpy(usb->recvMsg, usb->recvMsg+stxp, usb->recvSize);
                usb->recvMsg[usb->recvSize] = 0x00;
            }
        
        }
            //result=-1;
        size = usb->recvSize-2;
        lrc = btRs232CalculateLrc(usb->recvMsg+1, &size);
        if(lrc != usb->recvMsg[usb->recvSize-1])
            return -1;
    }
    else
    {
        sprintf(buffer, "!!! error !!!, UnKnowen ECR Version(%d)",usb->dataCheckType);    
        CTOS_PrinterPutString(buffer);
        result=-1;
    }           
    return result;            
}
