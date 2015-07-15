/* 
 * File:   sysinfo.h
 * Author: bruce-lin
 *
 * Created on 2013年6月27日, 上午 9:07
 */

#ifndef SYSINFO_H
#define	SYSINFO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>
#include "ezxml.h"

#ifdef	__cplusplus
extern "C" {
#endif
#define FALSE	0
#define TRUE	1
    
#define ACTIONFLAG_GETTEXT 0x00
#define ACTIONFLAG_REPLACE 0x01
#define ACTIONFLAG_REMOVE  0x02
#define ACTIONFLAG_ADD     0x04


typedef struct{
    BYTE ENABLE[1+1];
    BYTE IP[15+1];
    BYTE ID[10+1];
    BYTE PASSWORD[10+1];
}FTP_STRUCT;

typedef struct{
    BYTE ENABLE[1+1];
}PRINT_STRUCT;
typedef struct{
    BYTE ENABLE[1+1];
}SDCARD_STRUCT;
typedef struct{
    PRINT_STRUCT        PRINT;
    FTP_STRUCT          FTP;
    SDCARD_STRUCT       SD;
}DEBUG_STRUCT;
typedef struct{
    BYTE NAME[20+1];
    BYTE VERSION[20+1];
    BYTE GeneratedDateTime[14+1];
    BYTE Company[20+1];
    BYTE FTPPATH[64+1];
}AP_STRUCT;
typedef struct{
    BYTE NAME[20+1];
    BYTE VERSION[20+1];
    BYTE TYPE[6+1];
    BYTE UPDATETIME[14+1];
    BYTE FTPPATH[64+1];
}BLC_STRUCT;
typedef struct{
    BYTE VERSION[20+1];
    BYTE CAFILENAME1[16+3+1];
    BYTE CAEXPIRYDAY1[16+1];
    BYTE CAFILENAME2[16+3+1];
    BYTE CAEXPIRYDAY2[16+1];
    BYTE UPDATETIME[14+1];
    BYTE FTPPATH[64+1];
}SSL_STRUCT;
typedef struct{
    BYTE PARAMETER[16+1];
    AP_STRUCT   AP;
    BLC_STRUCT  BLC;
    SSL_STRUCT  SSL;
}CURRVERSION_STRUCT;

typedef struct{
    BYTE PARAMETER[16+1];
    AP_STRUCT   AP;
    BLC_STRUCT  BLC;
    SSL_STRUCT  SSL;
}TMS_STRUCT;

typedef struct{
    BYTE   PASSWORD[10+1];
    BYTE   MERCHANTID[20+1];
    BYTE   NewLocationID[20+1];
    BYTE   STCODE[20+1];
}MERCHANT_STRUCT;

typedef struct{
    BYTE   SERIALNO[20+1];
    BYTE   SIGNONMAXTIME[20+1];
    BYTE   OFFLINETXLIMIT[20+1];
    BYTE   FORCEONLINELIMIT[20+1];    
}TX_STRUCT;
 typedef struct{
     BYTE MechineID[20+1];
 }EDC_STRUCT;
 

  
 typedef struct{
     BYTE SAMVER[8+1];
     BYTE SAMID[16+1];
     BYTE CPUDEVICEID[24+1];
  }CPU_STRUCT;
  typedef struct{
     BYTE SAMID[10+1];
     BYTE SAMSN[12+1];
     BYTE DEVICEID[20+1];
     BYTE SAMKEYVER[8+1];
  }MIFARE_STRUCT;
 typedef struct{
     BYTE  bPORT[8+1];
     BYTE  bBAUDRATE[12+1];
     BYTE  bPARITY[4+1];
     BYTE  bDATABITS[4+1];
     BYTE  bSTOPBITS[4+1];
     BYTE  bHostSpecVersionNo[4+1];
     BYTE  bREADERID[20+1];
     BYTE  bREADERFWVER[20+1];
   //  MIFARE_STRUCT    MIFARE;
     BYTE MIFARE_SAMID[8+1];
     BYTE MIFARE_SAMSN[12+1];
     BYTE MIFARE_DEVICEID[2+1];
     BYTE MIFARE_SAMKEYVER[2+1];
     CPU_STRUCT       CPU;
     BYTE RemainderAddQuota[12+1];
     BYTE CancelCreditQuota[12+1];
 }READER_STRUCT;
 
  typedef struct{
      BYTE USEDDISKSIZE[20+1];
      BYTE TOTALDISKSIZE[20+1];
      BYTE USEDRAMSIZE[20+1];
      BYTE TOTALRAMSIZE[20+1];
  }MEMORY_STRUCT;
 
 
 typedef struct{
    BYTE                SSLEnable[2+1];
    BYTE                SAMSLOT[2+1];
    EDC_STRUCT          EDC;
    READER_STRUCT       READER;
    MEMORY_STRUCT       MEMORY;
}DEVICE_STRUCT;
  
  typedef struct{
     BYTE  LastSignonDateTime[33];
  }STATUS_STRUCT;

          
   typedef struct{    
        BYTE STRING1[128];  
        BYTE STRING2[128];  
        BYTE STRING3[128];  
        BYTE STRING4[128];  
        BYTE STRING5[128];  
   }RECEIPTREMARK_STRUCT;     
  typedef struct{
    BYTE                        LocationID[10+1];
    BYTE                        ID[20+1];
    BYTE                        AgentNumber[20+1];
    BYTE                        TITLE[128];
    BYTE                        SUBTITLE[128];
    BYTE                        RECEIPTNUM[10+1];
    BYTE                        RECEIPTTYPE1[64];
    BYTE                        RECEIPTTYPE2[64];
    RECEIPTREMARK_STRUCT        RECEIPTREMARK;            
  }TM_STRUCT;
  
  typedef struct{
      BYTE READER[1+1];
      BYTE ECR[1+1];
  }COMPORT_STRUCT;

typedef struct{
      BYTE NO[3+1];
  }BATCH_STRUCT;
  
  typedef struct{
      BYTE IP[15+1];
      BYTE MASK[15+1];
      BYTE GATEWAY[15+1];
      BYTE DNS[15+1];
      BYTE MAC[10+1];
      BYTE DHCP[2];
  }LOCAL_STRUCT;
 typedef struct{
     BYTE URL[64+1];
     BYTE URLPORT[6+1];
     BYTE IP[15+1];
     BYTE PORT[6+1];
 }HOST_STRUCT;
 typedef struct{
     BYTE URL[64+1];
     BYTE IP[64+1];
     BYTE PORT[6+1];
     BYTE LOGINID[20+1];
     BYTE LOGINPASSWORD[20+1];
 }COMMFTP_STRUCT;
 
  typedef struct{
    HOST_STRUCT  HOST;
    COMMFTP_STRUCT  FTP;
  }COMM_STRUCT;
 typedef struct{
    LOCAL_STRUCT   LOCAL;
    COMM_STRUCT    COMM;     
 }ETHERNET_STRUCT; 

 
typedef struct{
        DEBUG_STRUCT            sDEBUG;
        CURRVERSION_STRUCT       CURRVERSION;
        TMS_STRUCT              TMS;
        MERCHANT_STRUCT        MERCHANT;
        TX_STRUCT               TX;
        DEVICE_STRUCT           DEVICE;
        STATUS_STRUCT           STATUS;  
        TM_STRUCT               TM;
        COMPORT_STRUCT          COMPORT;
        BATCH_STRUCT            BATCH;
	ETHERNET_STRUCT         ETHERNET;
}Config_STRUCT;

 //////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct{
    BYTE ENABLE[1+1];
    BYTE IP[15+1];
    BYTE ID[10+1];
    BYTE PASSWORD[10+1];
}FTPv2_STRUCT;

typedef struct{
    BYTE ENABLE[1+1];
}PRINTv2_STRUCT;
typedef struct{
    BYTE ENABLE[1+1];
}SDCARDv2_STRUCT;
typedef struct{
    PRINTv2_STRUCT        PRINT;
    FTPv2_STRUCT          FTP;
    SDCARDv2_STRUCT       SD;
}DEBUGv2_STRUCT;
typedef struct{
    BYTE NAME[10+1];
    BYTE VERSION[6+1];
    BYTE GeneratedDateTime[14+1];
    BYTE Company[10+1];
    BYTE FTPPATH[64+1];
}APv2_STRUCT;
typedef struct{
    BYTE NAME[10+1];
    BYTE VERSION[6+1];
    BYTE TYPE[6+1];
    BYTE UPDATETIME[14+1];
    BYTE FTPPATH[64+1];
}BLCv2_STRUCT;
typedef struct{
    BYTE VERSION[10+1];
    BYTE CAFILENAME1[16+3+1];
    BYTE CAEXPIRYDAY1[16+1];
    BYTE CAFILENAME2[16+3+1];
    BYTE CAEXPIRYDAY2[16+1];
    BYTE UPDATETIME[14+1];
    BYTE FTPPATH[64+1];
}SSLv2_STRUCT;


typedef struct{
    BYTE   PASSWORD[4+1];
    BYTE   MERCHANTID[10+1];
    BYTE   NewLocationID[10+1];
    BYTE   STCODE[20+1];
}MERCHANTv2_STRUCT;


 typedef struct{
     BYTE MechineID[15+1];
 }EDCv2_STRUCT;

  
 typedef struct{
     BYTE SAMVER[8+1];
     BYTE SAMID[16+1];
     BYTE CPUDEVICEID[16+1];
  }CPUv2_STRUCT;
  typedef struct{
     BYTE SAMID[10+1];
     BYTE SAMSN[12+1];
     BYTE DEVICEID[10+1];
     BYTE SAMKEYVER[8+1];
  }MIFAREv2_STRUCT;
 typedef struct{
     BYTE  bPORT[4+1];
     BYTE  bBAUDRATE[6+1];
     BYTE  bPARITY[1+1];
     BYTE  bDATABITS[1+1];
     BYTE  bSTOPBITS[1+1];
     BYTE  bHostSpecVersionNo[4+1];
     BYTE  bREADERID[10+1];
     BYTE  bREADERFWVER[10+1];
   //  MIFARE_STRUCT    MIFARE;
     BYTE MIFARE_SAMID[8+1];
     BYTE MIFARE_SAMSN[12+1];
     BYTE MIFARE_DEVICEID[2+1];
     BYTE MIFARE_SAMKEYVER[2+1];
     CPUv2_STRUCT       CPU;
     BYTE RemainderAddQuota[6+1];
     BYTE CancelCreditQuota[6+1];
 }READERv2_STRUCT;
#define READERSTATUS_Normal 0
#define READERSTATUS_LOCK   1
 typedef struct{
     BYTE  bPORT[4+1];
     BYTE  bBAUDRATE[6+1];
     BYTE  bPARITY[1+1];
     BYTE  bDATABITS[1+1];
     BYTE  bSTOPBITS[1+1];
     BYTE  bHostSpecVersionNo[4+1];
     BYTE  bREADERID[10+1];
     BYTE  bREADERFWVER[10+1];
   //  MIFARE_STRUCT    MIFARE;
     BYTE MIFARE_SAMID[8+1];
     BYTE MIFARE_SAMSN[12+1];
     BYTE MIFARE_DEVICEID[10+1];//V4 for MIFARE_DEVICEID, len=2->len=10
     BYTE MIFARE_SAMKEYVER[2+1];
     CPUv2_STRUCT       CPU;
     BYTE RemainderAddQuota[6+1];
     BYTE CancelCreditQuota[6+1];
     BYTE bREADERSTATUS; //讀卡機出現6608時須寫為鎖機狀態，不可再作signon
 }READERv3_STRUCT;
 

 
 
  typedef struct{
      BYTE USEDDISKSIZE[5+1];
      BYTE TOTALDISKSIZE[5+1];
      BYTE USEDRAMSIZE[5+1];
      BYTE TOTALRAMSIZE[5+1];
  }MEMORYv2_STRUCT;
 
 

 typedef struct{
    BYTE                SSLEnable[2+1];
    BYTE                SAMSLOT[2+1];
    EDCv2_STRUCT          EDC;
    READERv2_STRUCT       READER;
    MEMORYv2_STRUCT       MEMORY;
}DEVICEv2_STRUCT;
  
  typedef struct{
     BYTE  LastSignonDateTime[16+1];
     BYTE  EDCSTATUS;    
  }STATUSv2_STRUCT;

          
   typedef struct{    
        BYTE STRING1[64+1];  
        BYTE STRING2[64+1];  
        BYTE STRING3[64+1];  
        BYTE STRING4[64+1];  
        BYTE STRING5[64+1];  
   }RECEIPTREMARKv2_STRUCT;     
  typedef struct{
    BYTE                        LocationID[4+1];
    BYTE                        ID[10+1];
    BYTE                        AgentNumber[4+1];
    BYTE                        TITLE[32];
    BYTE                        SUBTITLE[32];
    BYTE                        RECEIPTNUM[2+1];
    BYTE                        RECEIPTTYPE1[32];
    BYTE                        RECEIPTTYPE2[32];
    RECEIPTREMARKv2_STRUCT        RECEIPTREMARK;            
  }TMv2_STRUCT;
  
  typedef struct{
      BYTE READER[1+1];
      BYTE ECR[1+1];
  }COMPORTv2_STRUCT;

typedef struct{
      BYTE NO[3+1];
  }BATCHv2_STRUCT;
  
  typedef struct{
      BYTE IP[15+1];
      BYTE MASK[15+1];
      BYTE GATEWAY[15+1];
      BYTE DNS[15+1];
      BYTE MAC[10+1];
      BYTE DHCP[2];
  }LOCALv2_STRUCT;
 typedef struct{
     BYTE URL[64+1];
     BYTE URLPORT[6+1];
     BYTE IP[15+1];
     BYTE PORT[6+1];
 }HOSTv2_STRUCT;
 typedef struct{
     BYTE URL[64+1];
     BYTE IP[15+1];
     BYTE PORT[6+1];
     BYTE LOGINID[20+1];
     BYTE LOGINPASSWORD[20+1];
 }COMMFTPv2_STRUCT;
 
  typedef struct{
    HOSTv2_STRUCT  HOST;
    COMMFTPv2_STRUCT  FTP;
  }COMMv2_STRUCT;
 
typedef struct{
        BYTE MODE[2+1];
        BYTE DEDUCTAMT0[5+1];     
        BYTE DEDUCTAMT1[5+1];
        BYTE DEDUCTAMT2[5+1];
        BYTE DEDUCTAMT3[5+1]; 
        BYTE DEDUCTAMT4[5+1];
        BYTE DEDUCTAMT5[5+1];
        BYTE DEDUCTAMT6[5+1];
        BYTE DEDUCTAMT7[5+1];
        BYTE DEDUCTAMT8[5+1];     
        BYTE DEDUCTAMT9[5+1];     
}OPERATIONv2_STRUCT;
typedef struct
{
    unsigned char       TagName[32];
    BOOL                enable;
    BOOL                visible;
    unsigned char       itemname[32];
    BOOL                needpassword;
    unsigned char       password[15+1];
}FUNCTION_STRUCT;
typedef struct{
   FUNCTION_STRUCT       TXFUNCTION[20];
 }FUNCTION_TABLE_STRUCT;
 
typedef struct{
    OPERATIONv2_STRUCT        OPMODE;
    BYTE                    CONNECTMODE[2+1];
    COMM_STRUCT             COMM_TEST;
}Config2_STRUCT;

typedef struct{
    BYTE NAME[20+1];
    BYTE VERSION[20+1];
    BYTE Company[20+1];
    BYTE FTPPATH[64+1];
}READERFWv2_STRUCT;
typedef struct{
   //FUNCTION_STRUCT       TXFUNCTION[20];
   USHORT                MiniunitsADDVALUE; 
   READERFWv2_STRUCT       CURR_READERFW;
   READERFWv2_STRUCT       TMS_READERFW;
}Config3_STRUCT;

 typedef struct{
    BYTE           CONNECTMODE[2+1];
    LOCAL_STRUCT   LOCAL;
    COMMv2_STRUCT    COMM;    
    COMMv2_STRUCT    COMM_TEST;
    COMMv2_STRUCT    COMM_DEVELOP;
 }ETHERNETv2_STRUCT; 
 typedef struct{
    BYTE   SERIALNO[6+1];
    BYTE   SIGNONMAXTIME[4+1];
    BYTE   OFFLINETXLIMIT[4+1];
    BYTE   FORCEONLINELIMIT[4+1];    
    BYTE   MiniunitsADDVALUE[4+1]; 
    OPERATIONv2_STRUCT        OPMODE;
}TXv2_STRUCT;
typedef struct{
    BYTE PARAMETER[16+1];
    APv2_STRUCT                   AP;
    BLCv2_STRUCT                  BLC;
    SSLv2_STRUCT                  SSL;
    READERFWv2_STRUCT             READERFW;
}CURRVERSIONv2_STRUCT;

typedef struct{
    BYTE PARAMETER[16+1];
    APv2_STRUCT             AP;
    BLCv2_STRUCT            BLC;
    SSLv2_STRUCT            SSL;
    READERFWv2_STRUCT       READERFW;
}TMSv2_STRUCT;

typedef struct{
        DEBUG_STRUCT                    sDEBUG;
        CURRVERSIONv2_STRUCT           CURRVERSION;
        TMSv2_STRUCT                   TMS;
        MERCHANTv2_STRUCT                 MERCHANT;
        TXv2_STRUCT                     TX;
        DEVICEv2_STRUCT                   DEVICE;
        STATUSv2_STRUCT                   STATUS;  
        TMv2_STRUCT                       TM;
        COMPORTv2_STRUCT                  COMPORT;
        BATCHv2_STRUCT                    BATCH;
	ETHERNETv2_STRUCT               ETHERNET;        
}ConfigV2_STRUCT;
///////////////////////////////////////////////////////////////////////////////////
 typedef struct{
    BYTE                        LocationID[10+1];
    BYTE                        ID[20+1];
    BYTE                        AgentNumber[20+1];
    BYTE                        TITLE[64];
    BYTE                        SUBTITLE[64];
    BYTE                        RECEIPTNUM[10+1];
    BYTE                        RECEIPTTYPE1[64];
    BYTE                        RECEIPTTYPE2[64];
    BYTE                        RECEIPTTYPE3[64];
    BYTE                        RECEIPTTYPE4[64];
    RECEIPTREMARKv2_STRUCT      RECEIPTREMARK;            
  }TMv3_STRUCT;
  
typedef struct{
     BYTE URL[64+1];
     BYTE IP[15+1];
     BYTE VIPIP[15+1];
     BYTE PORT[6+1];
 }HOSTv3_STRUCT;
 typedef struct{
     BYTE URL[64+1];
     BYTE IP[15+1];
     BYTE VIPIP[15+1];
     BYTE PORT[6+1];
     BYTE LOGINID[20+1];
     BYTE LOGINPASSWORD[20+1];
 }COMMFTPv3_STRUCT;
  
   typedef struct{
    HOSTv3_STRUCT  HOST;
    COMMFTPv3_STRUCT  FTP;
  }COMMv3_STRUCT;
  typedef struct{
        USHORT AREACODE;
        USHORT AMT[10];         
}AMTTABLE_STRUCT;

 typedef struct{
     BYTE  bPORT[4+1];
     BYTE  bBAUDRATE[6+1];
     BYTE  bPARITY[1+1];
     BYTE  bDATABITS[1+1];
     BYTE  bSTOPBITS[1+1];
 }ECRv1_STRUCT;
 

 typedef struct{
    BYTE                SSLEnable[2+1];
    BYTE                SAMSLOT[2+1];
    EDC_STRUCT          EDC;
    READERv2_STRUCT     READER;
    ECRv1_STRUCT        ECR;         
    MEMORYv2_STRUCT     MEMORY;
  
}DEVICEv3_STRUCT;

 typedef struct{
    BYTE                SSLEnable[2+1];
    BYTE                SAMSLOT[2+1];
    EDC_STRUCT          EDC;
    READERv3_STRUCT     READER;
    ECRv1_STRUCT        ECR;         
    MEMORYv2_STRUCT     MEMORY;
  
}DEVICEv4_STRUCT;
  

   typedef struct{
    BYTE   SERIALNO[6+1];
    BYTE   SIGNONMAXTIME[4+1];
    BYTE   OFFLINETXLIMIT[4+1];
    BYTE   FORCEONLINELIMIT[4+1];    
    BYTE   MiniunitsADDVALUE[4+1];
    BYTE   AREACODE[2+1];
    BYTE   OPERATIONMODE[32+1];
    AMTTABLE_STRUCT        AMTTABLE[5];
   // AMTTABLE_STRUCT        AMTTABLE1;
   // AMTTABLE_STRUCT        AMTTABLE2;
}TXv3_STRUCT;
typedef struct{
    BYTE             CONNECTHOST[10+1];   
    BYTE             NETWORKMODE[10+1];
    LOCAL_STRUCT     LOCAL;
    COMMv3_STRUCT    HOST_PRODUCTION;    
    COMMv3_STRUCT    HOST_TESTING;
    COMMv3_STRUCT    HOST_DEVELOP;
  }ETHERNETv3_STRUCT; 
  typedef struct{
        DEBUG_STRUCT                     sDEBUG;
        CURRVERSIONv2_STRUCT             CURRVERSION;
        TMSv2_STRUCT                      TMS;
        MERCHANTv2_STRUCT                 MERCHANT;
        TXv3_STRUCT                       TX;
        DEVICEv3_STRUCT                   DEVICE;
        STATUSv2_STRUCT                   STATUS;  
        TMv3_STRUCT                       TM;
        COMPORTv2_STRUCT                  COMPORT;
        BATCHv2_STRUCT                    BATCH;
	ETHERNETv3_STRUCT                 ETHERNET;        
}ConfigV3_STRUCT;


  
  typedef struct{
        DEBUG_STRUCT                     sDEBUG;
        CURRVERSIONv2_STRUCT             CURRVERSION;
        TMSv2_STRUCT                      TMS;
        MERCHANTv2_STRUCT                 MERCHANT;
        TXv3_STRUCT                       TX;
        DEVICEv4_STRUCT                   DEVICE;
        STATUSv2_STRUCT                   STATUS;  
        TMv3_STRUCT                       TM;
        COMPORTv2_STRUCT                  COMPORT;
        BATCHv2_STRUCT                    BATCH;
	ETHERNETv3_STRUCT                 ETHERNET;        
}ConfigV4_STRUCT;

typedef struct{
    BYTE             EthernetCHANNEL[10+1];   
    BYTE             CONNECTHOST[10+1];   
    BYTE             NETWORKMODE[10+1];
    LOCAL_STRUCT     LOCAL;
    COMMv3_STRUCT    HOST_PRODUCTION;    
    COMMv3_STRUCT    HOST_TESTING;
    COMMv3_STRUCT    HOST_DEVELOP;
  }ETHERNETv4_STRUCT; 

  typedef struct{
        DEBUG_STRUCT                     sDEBUG;
        CURRVERSIONv2_STRUCT             CURRVERSION;
        TMSv2_STRUCT                      TMS;
        MERCHANTv2_STRUCT                 MERCHANT;
        TXv3_STRUCT                       TX;
        DEVICEv4_STRUCT                   DEVICE;
        STATUSv2_STRUCT                   STATUS;  
        TMv3_STRUCT                       TM;
        COMPORTv2_STRUCT                  COMPORT;
        BATCHv2_STRUCT                    BATCH;
	ETHERNETv4_STRUCT                 ETHERNET;        
}ConfigV5_STRUCT;

USHORT GetRS232Setting(void);
//USHORT ConfigV2_GetInitData(void);
USHORT ConfigV2_GetInitData( ConfigV2_STRUCT *ConfigV2);
USHORT Config_GetData(void);
USHORT Config_SetData(void);

 USHORT GetHOSTINFO(void);
 USHORT GetFTPINFO(void);
USHORT GetEDCSystemMemoryStatus(void);
USHORT GetEDCINFO(void);
USHORT  GetConfigTag(STR *node,STR * tag,STR * data);
USHORT GetXmlNodeattr_Name(ezxml_t node,STR * Name);
USHORT InitConfigFile(void);
USHORT SaveConfigFile(void);
USHORT LoadConfigFile(void);
USHORT InitConfigData(void);
USHORT InitEthernetInfo(void);
USHORT GetParameterVer(STR *DATA);
USHORT  SetConfigTag(STR *node,STR * tag,STR * data);
USHORT  GetConfigTag2(STR *node1,STR * node2,STR * tag,STR * data);
USHORT    SystemReset(void);

USHORT  SetConfigTag2(STR *node1,STR *node2,STR * tag,STR * data);
USHORT  Get_SSLCA(void);
USHORT UpdateTransSN(void);
USHORT SetTransSN(int SN);
USHORT usGetCurrTransSN(int * SN);
USHORT usSetNEWTransSN(void);
USHORT ShowVersionInfo(void);
USHORT ShowDEVICEInfo(void);
USHORT ShowTMInfo(void);
USHORT ShowETHERNETInfo(void);
USHORT ShowAPInfo(void);
USHORT PINGTEST(void);
USHORT ShowTerminalInfo(void);
USHORT Config_XML2STRUCT(void);
USHORT CheckConfigStatus(void);
USHORT CheckConfigFunctionStatus(void);
USHORT CheckSDConfigStatus(void);
USHORT CheckSDConfig2Status(void);
USHORT Config_GetInitData(void);
USHORT Config2_GetInitData(void);
USHORT Config3_GetInitData(void);
USHORT ConfigFuncion_GetInitData(void);
void ShowMemoarystatus(void);
USHORT SetFunctionSwitch(BYTE * function,BOOL flag);
USHORT GetFunctionSwitch(BYTE * function);
USHORT GetFunction(FUNCTION_STRUCT * Function);
USHORT ConfigFunction_GetData(void);

USHORT SetFunctionpPasswordSwitch(BYTE * function,BOOL flag);
USHORT SetFunctionpPassword(BYTE * function,STR *PW);
USHORT CheckFunctionpPassword(BYTE * function,STR *PW);
USHORT CheckFunctionpPasswordflag(BYTE * function);
USHORT CheckConfigStatusV4(void);
USHORT TransferConfigV1toV4(void);
USHORT TransferConfigV2toV4(void);
USHORT TransferConfigV3toV4(void);
USHORT SAVETransSn(STR* SN);
USHORT  GetTransSn(STR* SN);
//
//USHORT XML_GetTag(STR * File,STR *Text[],int Nodecount,STR * tag[],BYTE ActionFlag);
/*USHORT XML_AddTag(STR * File,STR * NodeName,STR *NodeText,int Nodecount,STR * tag[]);
USHORT XML_GetTag(STR * File,STR * RepleaseText,STR *Text[],int Nodecount,STR * tag[],BYTE ActionFlag);
//USHORT XML_GetTagText(STR * File,char *Text[],int Nodecount,STR * node[]);
USHORT XML_GetTAG2(STR * file,STR * FatherTAG,STR *TAG,STR *data);
USHORT XML_GetTAG(XMLNode * FatherNode,STR *TAG,STR *data);
USHORT XML_RemoveTag(STR * file,STR * FatherTAG,STR *TAG);
USHORT XML_UpdateTag(STR * file,STR * FatherTAG,STR *TAG,STR * data);
USHORT XML_ADDTag(STR * file,STR * FatherTAG,STR *TAG,STR * data);
*/
  #ifdef	__cplusplus
}
#endif

#endif	/* SYSINFO_H */

