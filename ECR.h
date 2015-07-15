/* 
 * File:   ECR.h
 * Author: user
 *
 * Created on 2014年3月5日, 下午 5:43
 */

#ifndef ECR_H
#define	ECR_H

#include "RS232.h" 
#include "Usb.h"

typedef struct
{
    BYTE ER01[16];//ecr switch
    BYTE ER02[16];//ecr interface
    BYTE ER03[16];//ecr version
    BYTE ER04[16];//ecr rs232 settings
    BYTE ER05[16];//ecr AutoSign    
} TMS_UPDATE_FIELD;

typedef struct
{
    BOOL setIt;
    BOOL dhcp;
    BYTE ip[16];
    BYTE gateway[16];
    BYTE mask[16];
    BYTE dns[16];
} EDC_ETHERNET_SETTING;

typedef struct
{
    EDC_ETHERNET_SETTING ethernet;
} EDC_SETTING;

typedef struct
{    
    BOOL response2Pos;
    BYTE pwd[4+1];              //T559503
    BYTE messageType[4+1];      //T0200
    BYTE pCode[6+1];            //T0300 
    LONG txnAmt;                //0400
    ULONG tmTxnSn;              //1101
    
    BYTE tmTxnTime[6+1];        //1201    
    BYTE tmTxnDate[8+1];        //1301
    BYTE tmInvoiceNo[20+1];     //3701 
    BYTE responseCode[4+1];     //3900[4Bytes], different with TRANS_DATA2(ucResponseCode[2Bytes])
    BYTE merchantId[10+1];      //4200
    ULONG tmLocationId;         //5503 STCODE
    BYTE tmId[6+1];             //5504 TM ID
    BYTE tmAgentNumber[4+1];    //5510
    BYTE doesNeedToPrintReceipt[4];//NO
    BYTE errMsg[256];
    BYTE tipMsg[256];
    void *customerDefineField;
    EDC_SETTING edcSetting;
} ECR_NON_GLOBAL_DATA;

typedef struct ecrData
{        
    BOOL isEcrTxn;
    int forcedTxnPCode;    
    TMS_UPDATE_FIELD *tmsUpdateFld;
} ECR_GLOBAL_DATA;

typedef struct
{
    char *processingCode; /* Field Number */
    int *tag; 
} TXN_MUST_FIELD_TABLE;






typedef struct ecrObject
{    
    BOOL ecrOn;//ecr Switch 
    BOOL autoSignOn;//2014.06.25, kobe added for hospital version
    BYTE interface;
    BYTE version;
    BOOL ecrForcedTest;
    BOOL ecrUiStay;//是否要自動pass所有警告訊息
    
    ezxml_t configRoot;//config file
    //ECR_TMS_TAG_UPDATE *tagUpdate;
    //ECR_INTERFACE interface;
    RS232_OBJ rs232;
    USB_OBJ usb;
    
    int ( *ecrRun)(void *);
    int ( *settingInterface)(void *);
    int ( *isDataIn)(void*);
    
    //int ( *responseXml2Pos)(void *);
    int ( *posFld2EdcFld)(void *);
    int ( *clear)(void *);
    int ( *errorResponse)(void *,int);
    int ( *tmsUpdate)(void*,BYTE*,BYTE*);
    int ( *ecrConfigSave)(void*);
    int ( *paraseData)(void *); 
    int ( *processTxn)(void*, void*);
    int ( *successResponse)(void *); 
    int ( *autoExeSignOn)(void *);
    int ( *gotErrorMessageString)(void *,int);
    int ( *menuFunctionSwitch)(void *);
    
    /*=================================*/
    ECR_GLOBAL_DATA gData;
    ECR_NON_GLOBAL_DATA *ngData;
    
    
} ECR_OBJ;


enum{
    RS232,
    USB,
    NO_ECR
}ECR_INTERFACE_TYPE;

enum{
    ECR_VER_NORMAL,
    ECR_VER_HOSPITAL
}ECR_VERSION;

void ecrInitial(void *);
int inEcrRun(void *);
int inEcrSettingInterface(void*);
int inIsDataIn(void*);
int inParaseData(void*);
int inResponseXml2Pos(void*);
int inErrorResponse(void*, int);
int inUnPackPosXml(void*,ezxml_t node);
int inProcessTxn(void*, void*);
int inPosFld2EdcFld(void*);
int inClear(void*);
int inTmsUpdate(void*,BYTE*,BYTE*);
int inEcrConfigSave(void*);
int inEcrReportTxnStatus(void*);
int inEcrQueryRecord(void*);
USHORT usEcrModifyComportUi(void);
int inEdcStatusReport(void*);
int inTmsBecomeEffective(void*,void*);
BYTE btCalculateLrc(void *p1, void *p2);
int inAutoExeSignOn(void*p1);
int inGotErrorMessageString(void*p1, int errcode);
int inMenuFunctionSwitch(void *p1);
void myFree(void **p);
void vdCardBasicData2TransData(void*p1);
USHORT usEcrExceptionTestUi(void);
USHORT remoteSettingEDC(void *p1);
/*2014.06.16, kobe added it for hospital system*/
  int inHospitalParaseData(void*);                   
  int inHospitalErrorResponse(void*, int);                    
  int inHospitalProcessTxn(void*, void*);  
  int inHospitalSuccessResponse(void*);  
  int inHospitalPosFld2EdcFld(void*);
  int inHospitalMenuFunctionSwitch(void *p1);
 /*
typedef struct
{
    BYTE Trans_Item[2+1];
    BYTE Trans_Amount[6+1];
    BYTE Trans_Dpt[4+1];
    BYTE Trans_Turn[1+1];
    BYTE Trans_Room[2+1];
    BYTE Trans_Ro_No[11+1];
    BYTE Trans_Usr_Id[5+1];
    BYTE Trans_Sys_Id[2+1];
    BYTE Print_status[1+1];
} ECR_VER1_HOSPITAL_DEFINED_FIELD;  
  */
#endif	/* ECR_H */

