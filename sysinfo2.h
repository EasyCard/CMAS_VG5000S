/* 
 * File:   sysinfo2.h
 * Author: T420s
 *
 * Created on 2015年2月2日, 下午 2:04
 */

#ifndef SYSINFO2_H
#define	SYSINFO2_H

#ifdef	__cplusplus
extern "C" {
#endif
    typedef struct{
    BYTE ENABLE[1+1];
    BYTE IP[15+1];
    BYTE bID[10+1];
    BYTE PASSWORD[10+1];
}DEBUG_FTP_STRUCT;

typedef struct{
    BYTE ENABLE[1+1];
}DEBUG_PRINT_STRUCT;
typedef struct{
    BYTE ENABLE[1+1];
}DEBUG_SDCARD_STRUCT;
typedef struct{
    DEBUG_PRINT_STRUCT        PRINT;
    DEBUG_FTP_STRUCT          FTP;
    DEBUG_SDCARD_STRUCT       SD;
}SYSINFO_DEBUG_STRUCT;



typedef struct{
    BYTE NAME[10+1];
    BYTE VERSION[6+1];
    BYTE GeneratedDateTime[14+1];
    BYTE Company[10+1];
    BYTE FTPPATH[64+1];
}VERSION_AP_STRUCT;
typedef struct{
    BYTE NAME[10+1];
    BYTE VERSION[6+1];
    BYTE TYPE[6+1];
    BYTE UPDATETIME[14+1];
    BYTE FTPPATH[64+1];
}VERSION_BLC_STRUCT;
typedef struct{
    BYTE VERSION[10+1];
    BYTE CAFILENAME1[16+3+1];
    BYTE CAEXPIRYDAY1[16+1];
    BYTE CAFILENAME2[16+3+1];
    BYTE CAEXPIRYDAY2[16+1];
    BYTE UPDATETIME[14+1];
    BYTE FTPPATH[64+1];
}VERSION_SSL_STRUCT;
typedef struct{
    BYTE NAME[20+1];
    BYTE VERSION[20+1];
    BYTE Company[20+1];
    BYTE FTPPATH[64+1];
}VERSION_READERFW_STRUCT;
typedef struct{
    BYTE PARAMETER[16+1];
    VERSION_AP_STRUCT             AP;
    VERSION_BLC_STRUCT            BLC;
    VERSION_SSL_STRUCT            SSL;
    VERSION_READERFW_STRUCT       READERFW;
}SYSINFO_VERSION_STRUCT;

typedef struct{
    BYTE   PASSWORD[4+1];
    BYTE   MERCHANTID[10+1];
    BYTE   NewLocationID[10+1];
    BYTE   STCODE[20+1];
}SYSINFO_MERCHANT_STRUCT;
  typedef struct{
        BYTE  NAME[36];
        USHORT AREACODE;
        USHORT AMT[10];         
}TX_AMTTABLE_STRUCT;

   typedef struct{
    BYTE   SERIALNO[6+1];
    BYTE   SIGNONMAXTIME[4+1];
    BYTE   OFFLINETXLIMIT[4+1];
    BYTE   FORCEONLINELIMIT[4+1];    
    BYTE   MiniunitsADDVALUE[4+1];
    BYTE   AUTOLOADLIMITAMT[5+1];
    BYTE   OPERATIONMODE[32+1];
 //   TX_AMTTABLE_STRUCT        AMTTABLE[5];
    TX_AMTTABLE_STRUCT        AMTTABLE[15];
   // AMTTABLE_STRUCT        AMTTABLE1;
   // AMTTABLE_STRUCT        AMTTABLE2;
}SYSINFO_TX_STRUCT;

 typedef struct{
     BYTE MechineID[15+1];
 }DEVICE_EDC_STRUCT;

  
 typedef struct{
     BYTE SAMVER[8+1];
     BYTE SAMID[16+1];
     BYTE CPUDEVICEID[16+1];
  }READER_CPU_STRUCT;

#define READERSTATUS_Normal 0
#define READERSTATUS_LOCK   1
 typedef struct{
     BYTE  bPORT[10+1];
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
     READER_CPU_STRUCT       CPU;
     BYTE RemainderAddQuota[6+1];
     BYTE CancelCreditQuota[6+1];
     BYTE bREADERSTATUS; //讀卡機出現6608時須寫為鎖機狀態，不可再作signon
 }DEVICE_READER_STRUCT;
 
 typedef struct{
     BYTE  bPORT[4+1];
     BYTE  bBAUDRATE[6+1];
     BYTE  bPARITY[1+1];
     BYTE  bDATABITS[1+1];
     BYTE  bSTOPBITS[1+1];
 }DEVICE_ECR_STRUCT;
  typedef struct{
      BYTE USEDDISKSIZE[5+1];
      BYTE TOTALDISKSIZE[5+1];
      BYTE USEDRAMSIZE[5+1];
      BYTE TOTALRAMSIZE[5+1];
  }DEVICE_MEMORY_STRUCT;
 
 typedef struct{
    BYTE                SSLEnable[2+1];
    BYTE                SAMSLOT[2+1];
    DEVICE_EDC_STRUCT          EDC;
    DEVICE_READER_STRUCT     READER;
    DEVICE_ECR_STRUCT        ECR;         
    DEVICE_MEMORY_STRUCT     MEMORY;
    BYTE PMPASSWORD[16];
    BYTE SMPASSWORD[16];
    BYTE MMPASSWORD[16];
    BYTE DMPASSWORD[16];
}SYSINFO_DEVICE_STRUCT;
  
    typedef struct{
     BYTE  LastSignonDateTime[16+1];
     BYTE  EDCSTATUS;    
  }SYSINFO_STATUS_STRUCT;

  typedef struct{    
        BYTE STRING1[64+1];  
        BYTE STRING2[64+1];  
        BYTE STRING3[64+1];  
        BYTE STRING4[64+1];  
        BYTE STRING5[64+1];  
   }TM_RECEIPTREMARK_STRUCT;     
  typedef struct{
    BYTE                        LocationID[10+1];
    BYTE                        bID[20+1];
    BYTE                        AgentNumber[20+1];
    BYTE                        TITLE[64];
    BYTE                        SUBTITLE[64];
    BYTE                        RECEIPTNUM[10+1];
    BYTE                        RECEIPTTYPE1[64];
    BYTE                        RECEIPTTYPE2[64];
    BYTE                        RECEIPTTYPE3[64];
    BYTE                        RECEIPTTYPE4[64];
    TM_RECEIPTREMARK_STRUCT      RECEIPTREMARK;            
  }SYSINFO_TM_STRUCT;
    
  typedef struct{
      BYTE READER[1+1];
      BYTE ECR[1+1];
  }SYSINFO_COMPORT_STRUCT;
typedef struct{
      BYTE NO[3+1];
  }SYSINFO_BATCH_STRUCT;
  
  typedef struct{
      BYTE IP[15+1];
      BYTE MASK[15+1];
      BYTE GATEWAY[15+1];
      BYTE DNS[15+1];
      BYTE MAC[10+1];
      BYTE DHCP[2];
  }COMM_LOCAL_STRUCT;
  typedef struct{
      BYTE SIMSLOT[16+1];
      BYTE PINCODE[12+1];
  }COMM_GPRS_STRUCT;
  typedef struct{
     BYTE URL[64+1];
     BYTE IP[15+1];
     BYTE VIPIP[15+1];
     BYTE PORT[6+1];
 }COMM_HOST_STRUCT;
 typedef struct{
     BYTE URL[64+1];
     BYTE IP[15+1];
     BYTE VIPIP[15+1];
     BYTE PORT[6+1];
     BYTE LOGINID[20+1];
     BYTE LOGINPASSWORD[20+1];
 }COMM_COMMFTP_STRUCT;
    
   typedef struct{
    COMM_HOST_STRUCT  HOST;
    COMM_COMMFTP_STRUCT  FTP;
  }SYSINFO_COMM_STRUCT;
  
  typedef struct{
    BYTE             EthernetCHANNEL[20+1];   
    BYTE             CONNECTHOST[20+1];   
    BYTE             NETWORKMODE[20+1];
    COMM_LOCAL_STRUCT     LOCAL;
    COMM_GPRS_STRUCT      GPRS;   
    SYSINFO_COMM_STRUCT    HOST_PRODUCTION;    
    SYSINFO_COMM_STRUCT    HOST_TESTING;
    SYSINFO_COMM_STRUCT    HOST_DEVELOP;
  }SYSINFO_ETHERNET_STRUCT; 

   typedef struct{
        SYSINFO_DEBUG_STRUCT                     sDEBUG;
        SYSINFO_VERSION_STRUCT                  CURRVERSION;
        SYSINFO_VERSION_STRUCT                      TMS;
        SYSINFO_MERCHANT_STRUCT                 MERCHANT;
        SYSINFO_TX_STRUCT                       TX;
        SYSINFO_DEVICE_STRUCT                   DEVICE;
        SYSINFO_STATUS_STRUCT                   STATUS;  
        SYSINFO_TM_STRUCT                       TM;
        SYSINFO_COMPORT_STRUCT                  COMPORT;
        SYSINFO_BATCH_STRUCT                    BATCH;
	SYSINFO_ETHERNET_STRUCT                 ETHERNET;   
        
}SYSINFO_STRUCT;

USHORT GetDEBUGInfo(void);
USHORT SetDEBUGInfo(void);
USHORT GetTXInfo(void);
USHORT SetTXInfo(void);
USHORT GetDEVICEInfo(void);
USHORT SetDEVICEInfo(void);
USHORT GetTMInfo(void);
USHORT SetTMInfo(void);
USHORT GetBATCHInfo(void);
USHORT SetBATCHInfo(void);
USHORT GetETHERNETInfo(void);
USHORT SetETHERNETInfo(void);
USHORT GetCURRVERSIONInfo(void);
USHORT SetCURRVERSIONInfo(void);
USHORT GetTMSVERSIONInfo(void);
USHORT SetTMSVERSIONInfo(void);
USHORT GetMERCHANTInfo(void);
USHORT SetMERCHANTInfo(void);

void Sysinfo2_GetData(void);
void Sysinfo2_SetData(void);
USHORT Sysinfo2_GetEDCSystemMemoryStatus(void);
USHORT Sysinfo2_InitConfigData(void);
USHORT Sysinfo2_InitConfigData(void);
USHORT ResetSysInfoData(STR * FileName,STR * TagName);
void RemoveSysInfoFile(void);
USHORT SetVERSIONInfo(void);
USHORT  GetVERSIONInfo(void);
USHORT SetAMTTABLE(USHORT table,USHORT index,USHORT amt);
USHORT SetAUTOFIXMODE_SelectAMT(USHORT);
#ifdef	__cplusplus
}
#endif

#endif	/* SYSINFO2_H */

