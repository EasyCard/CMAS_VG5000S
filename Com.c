
#include "ECCAPP.h"

/**
 * send data to serial port.
 *
 * @param buf
 *        a pointer to memory area that will be sent.
 * @param buf_size
 *        length of data in bytes to be sent.
 * @param timeout
 *        timeout in seconds.
 *
 * @return SUCCESS for success, or error code defined in dongle_errno_t.
 */
#include "gvar.h"


ULONG APDUReceiveTime, APDUSendTime;

USHORT send_apdu(BYTE COMPORT, const BYTE* buf, USHORT buf_size) {
    USHORT ret;

    //if(gDebugFlag == 0x01)            
        myDebugFile((char*)__FUNCTION__,__LINE__,"Call ReadySend port(%d)",COMPORT);
    if (CTOS_RS232TxReady(COMPORT) != d_OK) {
        //if(gDebugFlag == 0x01)                    
            myDebugFile((char*)__FUNCTION__,__LINE__,"Call ReadySend fail");
        //CTOS_RS232Close (COMPORT);
        //ret = CTOS_RS232Open(COMPORT,gREADERPORT.ulBaudRate , gREADERPORT.bParity, gREADERPORT.bDataBits, gREADERPORT.bStopBits);
        /*if(ret!=d_OK){ 
            SystemLogInt("inSendRecvAPDU",ret,"CTOS_RS232Open Fail");
            MechineStatus |= Status_READER_Disconnect;
             return d_ERR_RS232_OPEN_ERROR;
        }*/
    }
    // Send data via COM2 port  //
    APDUSendTime = CTOS_TickGet();
    
    myDebugFile((char*)__FUNCTION__,__LINE__,"Call CTOS Send size(%d)",buf_size);
    ret = CTOS_RS232TxData(COMPORT, (BYTE *) buf, buf_size);
    //if(gDebugFlag == 0x01)//for readBasicData
    myDebugFile((char*)__FUNCTION__,__LINE__,"Call CTOS Send ok");

    if (ret != d_OK) {
        SystemLogInt("send_apdu", ret, "CTOS_RS232TxData Fail");
        return ret;
    }
    printf("[%s,%d] CTOS_RS232TxData time(%lu)\n",__FUNCTION__,__LINE__, APDUSendTime);
    
    //DebugPrint_hex((BYTE *) buf, buf_size, "Send to Reader", DebugMode_TX);

    SystemLogHex("Sendto Reader  form EDC", (BYTE *) buf, buf_size);
    return SUCCESS;
}

USHORT recv_from(BYTE COMPORT, BYTE * buf, USHORT recv_size, int inTimeout) {
    USHORT ret;
    BYTE recvbuf[256];

    memset(recvbuf, 0x00, sizeof (recvbuf));
    int retry_count = inTimeout * 10;
    int i = 0;
    //USHORT data_len = recv_size;
    USHORT data_len = 0;
    
    do {
        CTOS_Delay(10);
           
       
        myDebugFile((char*)__FUNCTION__,__LINE__,"Call ReadyRead wantedLen(%d)",recv_size);
        ret = CTOS_RS232RxReady(COMPORT, &data_len);        
        myDebugFile((char*)__FUNCTION__,__LINE__,"Call ReadyRead OK,nowLen(%d)",data_len);
        
        /* no needed it
        if (data_len >= recv_size) {
            printf("[%s,%d] data_len(%d) >= recv_size (%d)\n",__FUNCTION__,__LINE__,data_len, recv_size);
            break;
        }*/
        i++;
        if (i == retry_count) {
            myDebugFile((char*)__FUNCTION__,__LINE__,"ERROR, Call ReadyRead, retryCnt got)");
            printf("[%s,%d] no recv anything~~i(%d), recv_size(%d),data_len(%d) \n", __FUNCTION__, __LINE__, i, recv_size, data_len);
            return 0;
        }
    }while(data_len < recv_size);//while (data_len <= 0);
    //printf("[%s,%d] data_len(%d) == recv_size (%d)\n",__FUNCTION__,__LINE__,recv_size, data_len);
    
    data_len = recv_size;
    
    myDebugFile((char*)__FUNCTION__,__LINE__,"Call CTOS Read totalLen(%d)",data_len);
    ret = CTOS_RS232RxData(COMPORT, recvbuf, &data_len);   
    myDebugFile((char*)__FUNCTION__,__LINE__,"Call CTOS Read OK");
    if (ret != d_OK) {
        printf("[%s,%d] CTOS_RS232RxData fail~~ret(%d)\n", __FUNCTION__, __LINE__, ret);
        SystemLogInt("recv_from", ret, "CTOS_RS232RxData Fail");
        return 0;
    }
    recv_size = data_len;
    memcpy(buf, recvbuf, data_len);

    //DebugPrint_hex(buf, data_len, "RECV from Reader", DebugMode_TX);

    SystemLogHex("Recv form Reader", buf, data_len);

    return recv_size;
}

/**
 * receive data from serial port.
 *
 * @param buf
 *        a pointer to memory area that will store the received inbound data
 *        if successful.
 * @param timeout
 *        timeout in seconds.
 * @param recv_size
 *        a pointer to size_t object that will store the length of received
 *        inbound data if successful
 *
 * @return SUCCESS for success, or error code defined in dongle_errno_t.
 */
USHORT recv_apdu(BYTE COMPORT, BYTE* buf, int inTimeout) {
    USHORT ret;
    USHORT ret2;
    USHORT recv_size = 0;

    if ((ret = recv_from(COMPORT, buf, OUT_DATA_OFFSET, inTimeout)) != OUT_DATA_OFFSET) {
        return 0;
    }
    recv_size += buf[2] + 1;
    
    // read info. and epilog
    if ((ret = recv_from(COMPORT, &buf[OUT_DATA_OFFSET], recv_size, 100)) != recv_size){
        printf("[%s,%d] recv APDU header size(%d)\n",__FUNCTION__,__LINE__,recv_size);
        printf("[%s,%d] recv APDU data body size(%d)\n",__FUNCTION__,__LINE__,ret);
        dumpByteArrayToHexString(buf, ret+OUT_DATA_OFFSET, "SizeWrong Body");
        return 0;
    }
    APDUReceiveTime = CTOS_TickGet();
    printf("[%s,%d] recv APDU time(%lu)\n",__FUNCTION__,__LINE__,APDUReceiveTime);
    recv_size += OUT_DATA_OFFSET/*sizeof(epilog_t)*/;
    
    //dumpByteArrayToHexString(cOutputData, recv_size, "recv from reader");
    return recv_size;
}
#ifdef TESTMODE

int inTSendRecvAPDU(BYTE *bSendData, int inSendLen, BYTE *bRecvData, int * inRecvLen, int inTimeOut, STR * TESTACTIONNAME, int Outputlen) {
    int inRetVal;


    myDebugFile((char*)__FUNCTION__,__LINE__,"Cmd:%s start",TESTACTIONNAME);
    memset(cOutputData, 0x00, sizeof(cOutputData));
    printf("[%s,%d] inTSendRecvAPDU apduName(%s)\n",__FUNCTION__,__LINE__, TESTACTIONNAME);
    if ((gScrpitTesting == 1) && (ezxml_get(gTestAction, TESTACTIONNAME, -1) != NULL)) {
        ezxml_t APDURESP = ezxml_get(gTestAction, TESTACTIONNAME, -1);
        BYTE *strbuf = ezxml_txt(APDURESP);
        int len = strlen(strbuf);

        if (strcmp(strbuf, "default") == 0) {
            memset(cOutputData, 0x00, Outputlen);
            cOutputData[2] = sizeof (Outputlen);
            cOutputData[cOutputData[2] + 1] = 0x90;
            cOutputData[cOutputData[2] + 2] = 0x00;
        } else {
            wub_str_2_hex(strbuf, cOutputData, len);
        }
        // ezxml_free(APDURESP);
        return SUCCESS;
    } else {
        inRetVal = inSendRecvAPDU(bSendData, inSendLen, bRecvData, inRecvLen, inTimeOut);
        //printf("[%s,%d] inSendRecvAPDU result(%04X)\n",__FUNCTION__,__LINE__, inRetVal);
        if (inRetVal != SUCCESS) {
            return inRetVal;
        }
        return SUCCESS;
    }

}

#endif

int inSendRecvAPDU(BYTE *bSendData, int inSendLen, BYTE *bRecvData, int * inRecvLen, int inTimeOut) {
    int inRetVal;

    int iRet;
    //   BYTE buff[1024];
    USHORT recelen = 0;
    //ShowSystemMemoryStatus("inSendRecvAPDU1 ");
    MechineStatus &= (~(Status_READER_Disconnect));
    if (strcmp(gConfig.DEVICE.READER.bPORT, "Builtin") == 0) {
        inRetVal = BuiltinReader_CMDSendReceive(bSendData, inSendLen, bRecvData, inRecvLen);
    } else {        
        CTOS_RS232FlushTxBuffer(gREADERPORT.Portnum);
        CTOS_RS232FlushRxBuffer(gREADERPORT.Portnum);
        if ((inRetVal = send_apdu(gREADERPORT.Portnum, bSendData, inSendLen)) != SUCCESS) {
            SystemLogInt("inSendRecvAPDU", inRetVal, "send_apdu Fail");
            //	CTOS_RS232Close (gREADERPORT.Portnum );
            //  USHORT ret= CTOS_RS232Close(gREADERPORT.Portnum);             
            //  ret = CTOS_RS232Open(gREADERPORT.Portnum,gREADERPORT.ulBaudRate , gREADERPORT.bParity, gREADERPORT.bDataBits, gREADERPORT.bStopBits);
            //  if(ret!=d_OK) return ret;
            MechineStatus |= Status_READER_Disconnect;
            printf("[%s,%d] d_ERR_SendAPDU_ERROR \n",__FUNCTION__,__LINE__);
            return d_ERR_SendAPDU_ERROR;
        }
        //  CTOS_Delay(500);
        if ((inRetVal = recv_apdu(gREADERPORT.Portnum, bRecvData, inTimeOut)) == 0) {
            //    CTOS_RS232Close (gREADERPORT.Portnum );
            //  USHORT ret= CTOS_RS232Close(gREADERPORT.Portnum);             
            // ret = CTOS_RS232Open(gREADERPORT.Portnum,gREADERPORT.ulBaudRate , gREADERPORT.bParity, gREADERPORT.bDataBits, gREADERPORT.bStopBits);
            //if(ret!=d_OK) return ret;
            MechineStatus |= Status_READER_Disconnect;
            printf("[%s,%d] d_ERR_RecvAPDU_ERROR \n",__FUNCTION__,__LINE__);
            return d_ERR_RecvAPDU_ERROR;
        }
        
        //dumpByteArrayToHexString(bRecvData, inRetVal, "Recv APDU Success");
        CTOS_RS232FlushTxBuffer(gREADERPORT.Portnum);
        CTOS_RS232FlushRxBuffer(gREADERPORT.Portnum);       
    }
    // ShowSystemMemoryStatus("inSendRecvAPDU2 ");
    inRetVal = SUCCESS;
    return (inRetVal);
}
