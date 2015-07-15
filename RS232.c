#include "ECCAPP.h"
#include <signal.h>

pthread_t MONITOR_COMPORT_STATUS;
void rs232Initial(void *p1)
{
    RS232_OBJ *rs232 = (RS232_OBJ*)p1;
    memset(rs232, 0x00, sizeof(RS232_OBJ));
    
    rs232->openComport = inOpenComport;
    rs232->sendData = inSendData;
    //rs232->recvDataLen = inRecvDataLen;
    rs232->recvData = inRecvDataV2;
    //rs232->recvData = inRecvData;
    rs232->closeComport = inCloseComport;

}
    
int inOpenComport(void *p1)
{
    int result;
    RS232_OBJ *rs232 = (RS232_OBJ*)p1;
    
    result=rs232->closeComport(rs232);
    
    if((result = CTOS_RS232Open(rs232->protocal.comport, rs232->protocal.baudRate, rs232->protocal.parity, rs232->protocal.dataBits, rs232->protocal.stopBits)) != d_OK)
    {
        /*open fail*/
        CTOS_Beep();
    }
    
    //thread for monitor RS232 Status
    printf("[%s,%d] monitorRS232Status thread Create\n",__FUNCTION__,__LINE__);
    pthread_create(&MONITOR_COMPORT_STATUS, NULL, (void *)monitorRS232Status, p1);
    
    return result; 
}
/*
int inSendData(void *p1, void *p2, ULONG size)
{
    RS232_OBJ *rs232 = (RS232_OBJ*)p1;
    BYTE *data = (BYTE*)p2;
    //BYTE *buffer;
    BYTE temp[16];
    USHORT len;
    int j;
    BYTE sendCnt;
    BYTE log[2048];
    //if((buffer=malloc(size+3))==NULL)return COMM_MEMORY_FAIL;
    
    //sprintf(buffer,"%c%s%c",0x02,data,0x03);
    
    while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);
    if(CTOS_RS232TxData(rs232->protocal.comport, data, size) != d_OK)    
    {              
        CTOS_Beep();   
        //free(buffer);
        return RS232_SEND_FAIL;        
    }     
    //free(buffer);
        
    //CTOS_Delay ( 1000 );
    if(rs232->waitACKCnt>0)        
    {        
            len=0;     
            sendCnt=3;
            //CTOS_RS232RxReady(rs232->protocal.comport, &len);                
            do
            {                    
                //j=len;            
                CTOS_Delay ( 2000 );//wait 2sec             
                CTOS_RS232RxReady(rs232->protocal.comport, &len);
                
                if(len==0)
                {
                    while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);                        
                    if(CTOS_RS232TxData(rs232->protocal.comport, data, size) != d_OK)        
                    {                                      
                        CTOS_Beep();                   
                        //return RS232_SEND_FAIL;                        
                    }  
                    sendCnt--;
                    sprintf(log,"response Cnt(%d)",sendCnt);
                    SystemLog("RS232_inSendData",log);
                }
                else
                    break;
                
            }while(sendCnt>0);
            memset(temp,0x00,sizeof(temp));
            CTOS_RS232RxData(rs232->protocal.comport, temp, &len);
            if(temp[0]!=ACK)
            {
//                /CTOS_PrinterPutString("No ACK");
                sprintf(log,"not ACK (%04X)",temp[0]);                    
                SystemLog("RS232_inSendData",log);
                return RS232_FORMAT_ERROR;        
            }
    }
    
    return d_OK;
}
*/
int inSendData(void *p1, void *p2, ULONG size)
{
    RS232_OBJ *rs232 = (RS232_OBJ*)p1;
    BYTE *data = (BYTE*)p2;
    //BYTE *buffer;
    BYTE temp[512];
    USHORT len;
    int i;
    BYTE sendCnt;
    BYTE log[2048];
    //if((buffer=malloc(size+3))==NULL)return COMM_MEMORY_FAIL;
    
    //sprintf(buffer,"%c%s%c",0x02,data,0x03);
    
    printf("[%s,%d] RS232(%d) send data start\n",__FUNCTION__,__LINE__,rs232->protocal.comport);
    
    //dumpByteArrayToHexString(data, size, "RS232 send");
    
    //while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);
    //while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK){
    //    printf("[%s,%d] RS232 TxReady not OK~~\n",__FUNCTION__,__LINE__);
    //}
    
    if(checkRS232TxReady(rs232) == FALSE){
        printf("[%s,%d] check Rs232 Tx Ready fail\n",__FUNCTION__,__LINE__);
        return RS232_SEND_FAIL;
    }
    
    
    printf("[%s%d] RS232 Ready finish\n",__FUNCTION__,__LINE__);
    if(CTOS_RS232TxData(rs232->protocal.comport, data, size) != d_OK)    
    {              
        CTOS_Beep();   
        printf("[%s,%d] send fail\n",__FUNCTION__,__LINE__);
        return RS232_SEND_FAIL;        
    }     
    printf("[%s%d] RS232 Tx Data\n",__FUNCTION__,__LINE__);
        
    //CTOS_Delay ( 1000 );
    if(rs232->waitACKCnt>0)        
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
                        
                    
                    
                    //while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);                        
                    while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK){                        
                        printf("[%s,%d] RS232 TxReady not OK~~\n",__FUNCTION__,__LINE__);    
                    }
                    if(CTOS_RS232TxData(rs232->protocal.comport, data, size) != d_OK)                                
                    {                                                             
                        CTOS_Beep();                   
                            //return RS232_SEND_FAIL;                                                
                    }  
                        
                    sendCnt--;                        
                    //sprintf(log,"response Cnt(%d)",sendCnt);
                    //CTOS_PrinterPutString(log);
                    
                    SystemLog("RS232_inSendData",log);    
                    CTOS_TimeOutSet(TIMER_ID_3, 200);//2 Sec Timeout  
                    //sprintf(log,"set timer, now tick(%ul)",CTOS_TickGet());
                   // CTOS_PrinterPutString(log);
                }
                else
                {
                    CTOS_RS232RxReady(rs232->protocal.comport, &len);
                    if(len>0)
                    {
                        memset(temp,0x00,sizeof(temp));
                        len = (len>sizeof(temp))?sizeof(temp):len;
                        CTOS_RS232RxData(rs232->protocal.comport, temp, &len);
                        for(i=0; i<len; i++)                    
                            if(temp[i] == ACK) break;//great, got ACK                        
                    
                        if(i!=len)//not equal, got ACK, exit while loop                            
                            break;
                       // else
                        //    CTOS_PrinterPutString("loop, no ACK found");
                    }                
                }            
            }while(sendCnt>=0);
            
            if(sendCnt<=0)//no ACK                        
            {                          
                CTOS_PrinterPutString(".");  //noACK         
                sprintf(log,"No ACK (%04X)",temp[0]);                                                     
                SystemLog("RS232_inSendData",log);    
                printf("[%s,%d] No ACK\n",__FUNCTION__,__LINE__);
                return RS232_FORMAT_ERROR;     
            }
    }
    
    printf("[%s,%d] send data finish\n",__FUNCTION__,__LINE__);
     
    
    return d_OK;
}

/*dynamic realloc ...not finish stop
int myDynamicDataCat(BYTE* dest, int destIndex, BYTE* src, int srcLen)
{
    BYTE *temp;
    temp = realloc(dest, sizeof(BYTE)*(destIndex+srcLen));
    if(!temp) return COMM_MEMORY_FAIL;
    
    dest = temp;
    memcpy(dest+destIndex, src, srcLen);
    
    return d_OK;
}


int inRecvDataV2(void*p1)
{
   RS232_OBJ *rs232 = (RS232_OBJ*)p1;    
    
    USHORT len;
    int j;
    int result;
    BYTE temp[16];
    BYTE printBuf[512];
    BYTE temp2[16];
    BYTE recvBufferTemp[512];
    int l;
    int t;
    int recvBufferTempLen;
    int c;
    BOOL gotEtx;
    
    len=0;
    l=1;
    t=0;
    gotEtx = FALSE;
    recvBufferTempLen= sizeof(recvBufferTemp);
    result=COMM_ESCAPE;
    if((CTOS_RS232RxReady(rs232->protocal.comport, &j)) == d_OK && j>0)//got data in
    {        
        //Recv Data
        while(1)
        {    
            c = CTOS_RS232RxData(rs232->protocal.comport, temp2, &l);
            if(c>0)
            {
                if(temp2[0] == STX)//start
                {
                    recvBufferTemp[t++] = temp2[0];
                    len++;
                    while(1)
                    {
                        c = CTOS_RS232RxData(rs232->protocal.comport, temp2, &l);
                        if(c<=0) 
                        {
                            if(myDynamicDataCat(rs232->recvMsg, len))
                            break;
                        }
                        if(temp[0] == ETX){
                            recvBufferTemp[t++] = temp2[0];
                            len++;
                            rs232->recvMsg = realloc(rs232->recvMsg, sizeof(BYTE)*len);
                            if(!rs232->recvMsg) {                            
                                return COMM_MEMORY_FAIL;
                            }
                            memcpy(rs232->recvMsg+(len-(len%recvBufferTempLen)), recvBufferTemp, t);
                                
                            gotEtx = TRUE;
                            break;//stop
                        } 

                        recvBufferTemp[t] = temp2[0];
                        t++;
                        len++;

                        if(t>=recvBufferTempLen)
                        {
                            rs232->recvMsg = realloc(rs232->recvMsg, sizeof(BYTE)*recvBufferTempLen);
                            if(!rs232->recvMsg) {                            
                                return COMM_MEMORY_FAIL;
                            }
                            memcpy(rs232->recvMsg+((int)(len/recvBufferTempLen)*recvBufferTempLen), recvBufferTemp, recvBufferTempLen);
                            //reset tempBuffer and index
                            memset(recvBufferTemp, 0x00, recvBufferTempLen);
                            t=0;
                        }
                    }
                }
            }
            else
                break;
        }   
       // }while(j!=len);  
        
        rs232->recvSize = len;
        result = len;                
    }
    else//no data in
        return COMM_ESCAPE;

    //allocate memory
    //if((rs232->recvMsg = calloc(len+1,sizeof(BYTE)))==NULL)
    //    return COMM_MEMORY_FAIL;
   
    //CTOS_RS232RxData(rs232->protocal.comport,rs232->recvMsg,&(rs232->recvSize));
    
    CTOS_RS232FlushRxBuffer(rs232->protocal.comport);
    CTOS_RS232FlushTxBuffer(rs232->protocal.comport);
    
    
    if(inCheckDataCompleteness(rs232) == d_OK)
    {    
        //response ACK
        while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);
        memset(temp,0x00,sizeof(temp));
        for(j=0;j<rs232->sendACKCnt;j++)sprintf(temp+j,"%c",ACK);
        
        if(CTOS_RS232TxData(rs232->protocal.comport, temp, strlen(temp)) != d_OK)
        {
                CTOS_Beep();
                if(rs232->recvMsg) free(rs232->recvMsg);
                rs232->recvMsg=NULL;
                return RS232_SEND_FAIL;
        }        
    }            
    else
    {
        if(rs232->recvMsg) free(rs232->recvMsg);
        rs232->recvMsg=NULL;
        //response NAK
        while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);
        memset(temp,0x00,sizeof(temp));
        for(j=0;j<rs232->sendACKCnt;j++)sprintf(temp+j,"%c",NAK);
        
        if(CTOS_RS232TxData(rs232->protocal.comport, temp, strlen(temp)) != d_OK)
        {
                CTOS_Beep();
                return RS232_SEND_FAIL;
        }        
        return RS232_FORMAT_ERROR;
    }
    
    return d_OK;
    
}
*/

int inRecvDataV2(void*p1)
{
   RS232_OBJ *rs232 = (RS232_OBJ*)p1;    
    
    USHORT len;
    int j;
    int result;
    BYTE temp[16];
    BYTE log[2048];
    
    
    
    len=0;
    result=COMM_ESCAPE;
    if((CTOS_RS232RxReady(rs232->protocal.comport, &len)) == d_OK && len>0)//got data in
    {        
        //Recv Data
        do
        {    
            j=len;               
            CTOS_Delay ( 100 );                
            CTOS_RS232RxReady(rs232->protocal.comport, &len);
        }while(j!=len);  
        
        rs232->recvSize = len;
        result = len;                
    }
    else//no data in
        return COMM_ESCAPE;

    //2014.12.04, kobe added fot testing EDC Response No ACK to POS
    if(rs232->exceptionTestMode == EX_RESP_NO_ACK)
    {        
        return COMM_ESCAPE;
    }
    
    
    sprintf(log,"RS232 Recv Data Total Len(%d) Finish",len);
    SystemLog("RS232_inRecvDataV2",log);
    //allocate memory
    if((rs232->recvMsg = calloc(len+1,sizeof(BYTE)))==NULL)
        return COMM_MEMORY_FAIL;
   
    
    CTOS_RS232RxData(rs232->protocal.comport,rs232->recvMsg,&(rs232->recvSize));

            
    if(inCheckDataCompleteness(rs232) == d_OK)
    {    
        //response ACK
        while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);
        memset(temp,0x00,sizeof(temp));
        for(j=0;j<rs232->sendACKCnt;j++)sprintf(temp+j,"%c",ACK);
        
        if(CTOS_RS232TxData(rs232->protocal.comport, temp, strlen(temp)) != d_OK)
        {
                //CTOS_Beep();
                //if(rs232->recvMsg) free(rs232->recvMsg);
                //rs232->recvMsg=NULL;
                return RS232_SEND_FAIL;
        }
    }
    else
    {        
        //response NAK
        while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);
        memset(temp,0x00,sizeof(temp));
        for(j=0;j<rs232->sendACKCnt;j++)sprintf(temp+j,"%c",NAK);
        
        if(CTOS_RS232TxData(rs232->protocal.comport, temp, strlen(temp)) != d_OK)
        {
                CTOS_Beep();
                return RS232_SEND_FAIL;
        }        
        return RS232_FORMAT_ERROR;
    }
    
    SystemLog("RS232_inRecvDataV2","End");
    return d_OK;
    
}



/*
 * orig function backup
int inRecvDataV2(void*p1)
{
   RS232_OBJ *rs232 = (RS232_OBJ*)p1;    
    
    USHORT len;
    int j;
    int result;
    BYTE temp[16];
    BYTE printBuf[512];
    BYTE temp2[16];
    
    len=0;
    result=COMM_ESCAPE;
    if((CTOS_RS232RxReady(rs232->protocal.comport, &len)) == d_OK && len>0)//got data in
    {        
        //Recv Data
        do
        {    
            j=len;               
            CTOS_Delay ( 100 );                
            CTOS_RS232RxReady(d_COM1, &len);
        }while(j!=len);  
        
        rs232->recvSize = len;
        result = len;                
    }
    else//no data in
        return COMM_ESCAPE;

    //allocate memory
    if((rs232->recvMsg = calloc(len+1,sizeof(BYTE)))==NULL)
        return COMM_MEMORY_FAIL;
   
    CTOS_RS232RxData(rs232->protocal.comport,rs232->recvMsg,&(rs232->recvSize));
    
   
    
    if(inCheckDataCompleteness(rs232) == d_OK)
    {    
        //response ACK
        while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);
        memset(temp,0x00,sizeof(temp));
        for(j=0;j<rs232->sendACKCnt;j++)sprintf(temp+j,"%c",ACK);
        
        if(CTOS_RS232TxData(rs232->protocal.comport, temp, strlen(temp)) != d_OK)
        {
                CTOS_Beep();
                free(rs232->recvMsg);
                rs232->recvMsg=NULL;
                return RS232_SEND_FAIL;
        }        
    }            
    else
    {
        free(rs232->recvMsg);
        rs232->recvMsg=NULL;
        //response NAK
        while(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK);
        memset(temp,0x00,sizeof(temp));
        for(j=0;j<rs232->sendACKCnt;j++)sprintf(temp+j,"%c",NAK);
        
        if(CTOS_RS232TxData(rs232->protocal.comport, temp, strlen(temp)) != d_OK)
        {
                CTOS_Beep();
                return RS232_SEND_FAIL;
        }        
        return RS232_FORMAT_ERROR;
    }
    
    return d_OK;
    
}

int inCheckDataCompleteness(void*p1)
{
    RS232_OBJ* rs232 = (RS232_OBJ*)p1;
    int result;
    BYTE buffer[64];
    
    BYTE lrc;
    int size;
    result = d_OK;            
   
    if(rs232->dataCheckType==ECR_VER_NORMAL)//normal version
    {
        rs232->sendACKCnt=1;
        rs232->waitACKCnt=1;
        if(rs232->recvMsg[0] != 0x02 || rs232->recvMsg[rs232->recvSize-1] != 0x03)    
            result =-1;       
    }
    else if(rs232->dataCheckType==ECR_VER_HOSPITAL)//hospital version
    {
        rs232->sendACKCnt=2;
        rs232->waitACKCnt=2;
        if(rs232->recvMsg[0] != 0x02 || rs232->recvMsg[rs232->recvSize-2] != 0x03)               
            result=-1;
        size = rs232->recvSize-2;
        lrc = btRs232CalculateLrc(rs232->recvMsg+1, &size);
        if(lrc != rs232->recvMsg[rs232->recvSize-1])
            return -1;
    }
    else
    {
        sprintf(buffer, "!!! error !!!, UnKnowen ECR Version(%d)",rs232->dataCheckType);    
        CTOS_PrinterPutString(buffer);
        result=-1;
    }           
    return result;            
}
*/

int inCloseComport(void *p1)
{
    RS232_OBJ* rs232 = (RS232_OBJ*)p1;
    
    return CTOS_RS232Close(rs232->protocal.comport);
    
}

int inCheckDataCompleteness(void*p1)
{
    RS232_OBJ* rs232 = (RS232_OBJ*)p1;
    int result;
    BYTE buffer[64];
    
    BYTE lrc;
    int size;
    int stxp=-1;
    int etxp=-1;
    int i;
    
    result = d_OK;
    
    //2014.12.04, kobe added fot testing EDC Response NAK to POS
    if(rs232->exceptionTestMode == EX_RESP_NAK)
    {
        CTOS_PrinterPutString("Exception Test Mode(Resp NAK)");
        return -1;
    }
    if(rs232->dataCheckType==ECR_VER_NORMAL)//normal version
    {
        rs232->sendACKCnt=1;
        rs232->waitACKCnt=1;
        if(rs232->recvMsg[0] != STX || rs232->recvMsg[rs232->recvSize-1] != ETX)//not into if{} was perfect status, no any noise
        {
            for(i=0; i<rs232->recvSize; i++)
            {
                if(rs232->recvMsg[i]==STX) stxp=i;
                else if(rs232->recvMsg[i]==ETX)
                {
                    etxp=i;
                    break;
                }
            }
            
            if(stxp==-1 || etxp==-1 ) result =-1; //not found STX or ETX, so response NAK
            else
            {
                rs232->recvSize = etxp-stxp+1;
                memcpy(rs232->recvMsg, rs232->recvMsg+stxp, rs232->recvSize);
                rs232->recvMsg[rs232->recvSize] = 0x00;
            }
        }
    }
    else if(rs232->dataCheckType==ECR_VER_HOSPITAL)//hospital version
    {
        rs232->sendACKCnt=2;
        rs232->waitACKCnt=2;
        if(rs232->recvMsg[0] != 0x02 || rs232->recvMsg[rs232->recvSize-2] != 0x03) //not into if{} was perfect status, no any noise
        {                
            for(i=0; i<rs232->recvSize; i++)
            {
                if(rs232->recvMsg[i]==STX) stxp=i;
                else if(rs232->recvMsg[i]==ETX)
                {
                    etxp=i+1;//next pos was LRC, so,include it.
                    break;
                }
            }
            
            if(stxp==-1 || etxp==-1 ) return -1; //not found STX or ETX, so response NAK
            else
            {
                rs232->recvSize = etxp-stxp+1;
                memcpy(rs232->recvMsg, rs232->recvMsg+stxp, rs232->recvSize);
                rs232->recvMsg[rs232->recvSize] = 0x00;
            }
        }
        
        size = rs232->recvSize-2;//skip STX and LRC
        lrc = btRs232CalculateLrc(rs232->recvMsg+1, &size);
        if(lrc != rs232->recvMsg[rs232->recvSize-1])
            return -1;
    }
    else
    {
        sprintf(buffer, "!!! error !!!, UnKnowen ECR Version(%d)",rs232->dataCheckType);    
        CTOS_PrinterPutString(buffer);
        result=-1;
    }           
    return result;            
}

/*
int inCheckDataCompleteness(void*p1)
{
    RS232_OBJ* rs232 = (RS232_OBJ*)p1;
    int result;
    BYTE buffer[64];
    
    BYTE lrc;
    int size;
    result = d_OK;            
   
    if(rs232->dataCheckType==ECR_VER_NORMAL)//normal version
    {
        rs232->sendACKCnt=1;
        rs232->waitACKCnt=1;
        if(rs232->recvMsg[0] != 0x02 || rs232->recvMsg[rs232->recvSize-1] != 0x03)    
            result =-1;       
    }
    else if(rs232->dataCheckType==ECR_VER_HOSPITAL)//hospital version
    {
        rs232->sendACKCnt=2;
        rs232->waitACKCnt=2;
        if(rs232->recvMsg[0] != 0x02 || rs232->recvMsg[rs232->recvSize-2] != 0x03)               
            result=-1;
        size = rs232->recvSize-2;
        lrc = btRs232CalculateLrc(rs232->recvMsg+1, &size);
        if(lrc != rs232->recvMsg[rs232->recvSize-1])
            return -1;
    }
    else
    {
        sprintf(buffer, "!!! error !!!, UnKnowen ECR Version(%d)",rs232->dataCheckType);    
        CTOS_PrinterPutString(buffer);
        result=-1;
    }           
    return result;            
}
*/
BYTE btRs232CalculateLrc(void *p1, void *p2)
{
    BYTE *data = (BYTE*) p1;
    int dataSize = *(int*)p2;
    int i;
    BYTE lrc;
    
    lrc=0x00;
    for(i=0; i<dataSize; i++)
    {
       lrc=lrc^data[i]; 
    }
    return lrc;
}

void monitorRS232Status(void *p1){

    RS232_OBJ* rs232 = (RS232_OBJ*)p1;
    
    printf("[%s,%d] monitorRS232Status Start\n",__FUNCTION__,__LINE__);
    while(1){    
        rs232->fTxReady = FALSE;
        //printf("[%s,%d]ready loop forever\n",__FUNCTION__,__LINE__);
        
        //simulate  CTOS_RS232TxReady fail
        //while(1){
        //    CTOS_Delay(1000);
        //    printf("[%s,%d]ready loop forever\n",__FUNCTION__,__LINE__);
        //}
        if(CTOS_RS232TxReady(rs232->protocal.comport) != d_OK){
            printf("[%s,%d] RS232 TxReady not OK~~\n",__FUNCTION__,__LINE__);            
        }
        else
            rs232->fTxReady = TRUE;        
        CTOS_Delay(1000);
    }
    
    pthread_exit("monitor rs232 thread exist");
    return;
}

BOOL checkRS232TxReady(void *p1){

    int result;
    BOOL txReady;
    
    int kill_rc;
    RS232_OBJ* rs232 = (RS232_OBJ*)p1;
     
    CTOS_TimeOutSet(TIMER_ID_3, 500);//5 Sec Timeout            
            
    while(1){  
        if(rs232->fTxReady == TRUE){
            txReady = TRUE;
            break;
        } else if(CTOS_TimeOutCheck(TIMER_ID_3) == d_YES){
            printf("[%s,%d] check RS232 TxReady Timeout, maybe comport something wrong, closed it & opened it again\n",__FUNCTION__,__LINE__);
        
            //result = pthread_join(MONITOR_COMPORT_STATUS, &threadResult);
            result = pthread_cancel(MONITOR_COMPORT_STATUS);
            printf("[%s,%d] monitor thread cancel result(%d)\n",__FUNCTION__,__LINE__,result);
            //close comport
            //if((result=rs232->closeComport(rs232)) != d_OK){
            //    printf("[%s,%d] close comport fail(%d)\n",__FUNCTION__,__LINE__,result);
            //}
            
            if((result=rs232->openComport(rs232)) != d_OK){
                printf("[%s,%d] open comport fail(%d)\n",__FUNCTION__,__LINE__,result);                 
                CTOS_SystemReset();//reboot
            }
            
             kill_rc = pthread_kill(MONITOR_COMPORT_STATUS,0);
             if(kill_rc==ESRCH){                        
                 printf("[%s,%d] create monitor Thread\n",__FUNCTION__,__LINE__);                        
                 pthread_create(&MONITOR_COMPORT_STATUS, NULL, (void *)monitorRS232Status, rs232);             
             }
            
            printf("[%s,%d] reOpened comport Success\n",__FUNCTION__,__LINE__);
            txReady = TRUE;
            break;
        }
    } 
    
    return txReady;
}