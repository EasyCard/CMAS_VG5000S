/* 
 * File:   gvar.h
 * Author: bruce-lin
 *
 * Created on 2013年7月9日, 下午 1:41
 */

#ifndef GVAR_H
#define	GVAR_H


#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef _TXMAIN_
	#define _EXTERN 
#else
	#define _EXTERN extern
#endif

#include "sysinfo.h"
#include "menu.h"
#include "wub_lib.h"
#include "comm.h"
#include "ezxml.h"
#include "Substruct.h"
    #include "Apdu.h"
#include "Trans.h"
#include "Com.h"
#include "Batch.h"
#include "ECR.h"
#include "sysinfo2.h"
#include <openssl/ssl.h>
#include "ResponseCode.h"    
#include <curl/curl.h>
#include <pthread.h>
#define APPNAME         "ECCAPP2"         
#define LOCAL_FILE      SendFile
#define UPLOAD_FILE_AS  "send.xml"
#define REMOTE_URL      "ftps://user:1234@192.168.2.1/"   UPLOAD_FILE_AS
#define RENAME_FILE_TO  "bibib.bmp"    
#define BackgroundPIC   "bg1.bmp"
#define IDLEPIC         "bibi.bmp"  
// #define IDLEPIC         "easycard.bmp"  
//#define d_FONT_KAIU_TTF  "kaiu.ttf"
//#define d_FONT_TTF  "msjhbd.ttf"
 #define d_FONT_TTF  "PMingLiU-TW.ttf"
//  #define d_FONT_TTF   "kaiu.ttf"
// #define d_FONT_TTF  "LiHeiProPC.ttf"

//#define ConfigXML	 	"config.xml" 
#define ConfigXML	 	"default.xml" 

#define  FilePath               "/home/ap/pub/"            
//#define  APFILE                 "/home/ap/pub/ap.cap"    
#define  APFILE                 "/media/mdisk/ap.cap"    
#define SDPATH                  "/media/mdisk/"
#define  SSLCertFile      	"ck1.cer"
#define  BLCFILE                "blc.dat"   
    
//#define  FunctionFile 		"function.xml"   
#define  FunctionXML		"function.xml"   
#define  TransFormatFile         "transformat.xml"   
#define  ResponseCodeFile        "ResponseCode.xml"    
#define  ResponseCodeJson        "ResponseCode.json" 
#define TestScrpitFile		"TestScript.xml"
#define BatchFile       	"BatchFle"       
//#define TransDataFile    	"/media/mdisk/Trans.dat"  
#define TransDataFile    	"Trans.dat"      
#define SendFile         	"SendFile"       
#define ReversalFile		"ReversalFile"
#define RecvFile         	"RecvFile"
#define TMSFILE     		"TMS.xml"
#define SettleFile              "SettleFile"    
    
    
#define ConfigDataFile          "ConfigDataFile"    
#define ConfigData2File         "ConfigData2File"   
#define ConfigData3File         "ConfigData3File"   

#define ConfigV2File            "ConfigV2"  
#define ConfigV3File            "ConfigV3"  
#define ConfigV4File            "ConfigV4"  
#define FUNCTIONFile            "FUNCTIONFile" 
#define BatchTotleFile          "BatchTotleFile"
#define SDConfigDataFile          "/media/mdisk/ConfigDataFile"   
#define SDConfigData2File         "/media/mdisk/ConfigData2File"
#define SDBatchTotleFile          "/media/mdisk/BatchTotleFile"  
#define SDConfigXML               "/media/mdisk/config.xml"  
#define ConfigXMLBACKUP           "config.bak"  
    
#define SDBatchSnFile               "/media/mdisk/batchSn"
#define BatchSnFile                 "batchSn"
#define SDTransSnFile               "/media/mdisk/TransSn"
#define TransSnFile                 "TransSn"    
#define SDFLASHSTATUS               "/media/mdisk/FLASHFAIL.xml"        
/*
 #define BATCHINFO_Path          "/Config/batch.xml"
#define DEBUGINFO_Path          "/Config/debug.xml"
#define TXINFO_Path             "/Config/tx.xml"
#define DEVICEINFO_Path         "/Config/device.xml"
#define ETHERNETINFO_Path       "/Config/ethernet.xml"     
#define TMINFO_Path             "/Config/tm.xml"      
#define MERCHANTINFO_Path       "/Config/merchant.xml"
#define VERSIONINFO_Path        "/Config/version.xml"

*/
#define BATCHINFO_Path          "batch.xml"
#define DEBUGINFO_Path          "debug.xml"
#define TXINFO_Path             "tx.xml"
#define DEVICEINFO_Path         "device.xml"
#define ETHERNETINFO_Path       "ethernet.xml"     
#define TMINFO_Path             "tm.xml"      
#define MERCHANTINFO_Path       "merchant.xml"
#define VERSIONINFO_Path        "version.xml"

#define d_Fail                 					0x9999            
#define d_ERR_GetTAG            				0x9998      
#define d_ERR_FILE_NOTEXIST     				0x9997
#define d_ERR_FILE_SIZE_ERR     				0x9996    
#define d_ERR_FILE_READ_FAIL    				0x9995
#define d_ERR_FILE_Write_FAIL   				0x9994
#define d_ERR_FILE_OPEN         				0x9993
#define d_ERR_FILE_CLOSE                                        0x9992
#define d_ERR_SSLCA_ERROR       				0x9989
#define d_ERR_SSL_CreateFail                                    0x9988
#define d_SSL_NOVAILDCA                                         0x9987   
#define d_ERR_USERCANCEL        				0x9986
#define d_ERR_AUTOLOADNOTSUPPORT                                0x9985
#define d_ERR_EVNOTENOGHT       				0x9984
#define d_ERR_AUTOLOADNOTALLOW                                  0x9983
#define d_ERR_AUTOLOADNOTNEED                                   0x9982
#define d_ERR_WRONGPASSWORD                                     0x9981    
#define d_ERR_XMLError          				0x9980    
#define d_ERR_RESP_LOCKCARD                                     0x9979 
#define d_ERR_RESP_REJECT       				0x9978    
#define d_ERR_RESP_ABORT        				0x9977
#define d_ERR_RESP_REBOOT       				0x9976
#define d_ERR_RESP_SECURTERR                                    0x9975
#define d_ERR_RESP_SIGNON       				0x9974
    
#define d_ERR_GETRTC            				0x9973    

#define d_ERR_createdir         				0x9972
#define d_ERR_eCOM_recv_Fail    				0x9971
#define d_ERR_RecvAPDU_ERROR                                    0x9970
#define d_ERR_SendAPDU_ERROR                                    0x9969
#define d_ERR_RS232_OPEN_ERROR                                  0x9968
#define d_ERR_Param             				0x9967
#define d_ERR_GetDataFail       				0x9966
#define d_ERR_BATCHFULL         				0x9965  
#define d_ERR_BATCH_LIMIT_SETTLE_FIRST                          0x9964  
#define d_ERR_PRE_SETTLE_FAIL_TRY_AGAIN                         0x9963  
//#define d_ERR_UNDEFINEDRESPOSECODE                              0x9962    
#define d_ERR_NOTNEEDUPDATEPARAMETER                            0x9961
#define d_TAG_NOTFOUND                                          0x9960    
#define d_ERR_PARAMETER_NOTVaild                                0x9959    
#define d_ERR_WRONG_MESSAGE                                     0x9958     
#define d_ERR_ETH_RECV_TIMEOUT                                  0x9957    
#define d_ERR_BATCHNOTEMPTY                                     0x9956
#define d_ERR_TX_CANNOT_FIND                                    0x9955
#define d_ERR_DEVICE_CHANGED                                    0x9954
#define d_ERR_RESP_RETRY                    			0x9953  
#define d_ERR_CANNOT_FINDTX                                     0x9952 
#define d_ERR_CMAS_RESPONSE_ERROR      				0x9951
#define d_ERR_NO_PASSWORD             				0x9950   
#define d_ERR_SYSTEM_ERROR             				0x9949
#define d_ERR_FTP_DL_FAIL                                       0x9948
#define d_ERR_ETH_NOTCONNECT                                    0x4202
#define SW_ERROR  						0xffff
#define d_ERR_READER_6608                                       0x6608        

#define INPUT_TYPE_Number                 0
#define INPUT_TYPE_NumberWithRadixPoint   1
#define INPUT_TYPE_NumberWithENGLISH   2
#define TransType_AUTH           1
#define TransType_VERIFY         2
#define TransType_TXADVICE       3
#define TransType_SIGNON         4       
#define TransType_STATUSREPORT   5
#define TransType_TMS            6
#define TransType_LOCKCARDADVICE 7    
#define TransType_DEBUG          8           
#define TransType_SETTLEMENT     9  

#define TransStatus_INIT          0
#define TransStatus_REQ        	  1
#define TransStatus_RSP           2 
#define TransStatus_ADVREQ        3
#define TransStatus_ADVRSP         4      
#define TransStatus_OK             5      
#define TransStatus_VOIDED          6
    
    
    
#define TXTYPE_TMS                 0        
#define TXTYPE_SIGNON              1
#define TXTYPE_ADD                 2
#define TXTYPE_DEDUCT              3                
#define TXTYPE_VOID                4
#define TXTYPE_SETVALUE            5
#define TXTYPE_SETTLEMENT          6
#define TXTYPE_AUTOLOADENABLE      7
#define TXTYPE_REFUND              8
#define TXTYPE_LOCKCARD            9         
#define TXTYPE_REPORT              10          
#define TXTYPE_DEBUG		   11
#define TXTYPE_DEDUCTVOID          12
#define TXTYPE_ADDVOID           13   
#define TXTYPE_AUTOLOAD          14           
    
#define MsgType_TransCancel   "00"
#define MsgType_TransDeduct   "01"
#define MsgType_TransAdd      "02"
#define MsgType_TransReturn   "03" //退卡
#define MsgType_TransEnable   "04" //開卡
#define MsgType_TransFine     "05" //罰款   

#define SubType_CashADD       "30" //現金加值 
#define SubType_debitADD      "31" //金融卡加值
#define SubType_CreditADD     "32" //信用卡加值 
    
#define Title_SIGNON    "系統登入"
#define Title_DEDUCT    "購貨"
#define Title_ADD       "加值"
#define Title_Cancle    "取消"
#define Title_Refund    "退貨"    
#define Title_AUTOLOAD    "自動加值"  
#define Title_SETTLEMENT    "結帳"  
#define Title_SETVALUE     "展期"
#define Title_AUTOLOADENABLE     "自動加值功能啟用"    
    
#define Type_ComformNONE					0    
#define Type_Comform0						1
#define Type_ComformOK						2
#define Type_ComformAnykey					3
#define Type_ComformCheck					4
#define Type_RemoveCard                                         5
#define Type_wait2sec                                           6
//2014.08.05, added by kobe
#define TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY                       7
#define TYPE_ECR_FORCE_TO_CONFIRM_OK                            8
#define TYPE_ECR_FORCE_TO_CONFIRM_0                             9
    
#define COMM_STATUS_INIT				0
#define COMM_STATUS_OPENFAIL                            1
#define COMM_STATUS_TCPClosed                           2
#define COMM_STATUS_TCPOPENING                          4
#define COMM_STATUS_TCPOPENOK                           5
#define COMM_STATUS_DISCONNECTED                        5  
#define COMM_STATUS_StartConnect                        6   
#define COMM_STATUS_Connecting                          7
#define COMM_STATUS_ConnecteFail			8
#define COMM_STATUS_ConnecteOK                          9
#define COMM_STATUS_READY                               9
#define COMM_STATUS_Sending                             10
#define COMM_STATUS_SendandRecvOK                       11
#define COMM_STATUS_SendandRecvFail                     12
 



    
    
#define COMM_CMD_IDLE                                   0   
#define COMM_CMD_CONNECT                                1
#define COMM_CMD_Send                                   2
#define COMM_CMD_DISCONNECT                             3
    
#define SIZE_TMPBUFFER  32  
//#define DEBUGMODE     
#define TESTMODE 1    
#define DEF_Font_SIZE	d_FONT_16x32
#define Big_Font_Size   0x1830
#define Big_Font_Xsize  0x18
#define Big_Font_Ysize  0x30    
#define Med_Font_Size   0x101e
#define Med_Font_Xsize  0x10
#define Med_Font_Ysize  0x1e 
    
    
#define Status_IDLE                     0x0000 
#define Status_SignOnFail               0x0001
#define Status_READER_Disconnect        0x0010
//#define Status_ETHERNET_Disconnect      0x0100
#define Status_FLASH_ERROR               0x0100
#define Status_Parameter_ERROR          0x1000
    
#define DebugMode_TX                    0x01
#define DebugMode_Reader                0x02
#define DebugMode_TestScrpit            0x03    
#define DebugMode_ALL                   0x04     
//#define ForeGndColor                    0xe8a000 
#define ForeGndColor                    d_LCD_BLACK    
//#define BackGroundColor                 0xFFFFFF  
//#define BackGroundColor                0x00ffff       
//#define BackGroundColor                0x00e0c0       
#define BackGroundColor                  0xe8a000  
 //#define BackGroundColor                 0xFF9428
#define  Color_ezblue                   0xe8a000
#define  Color_black                    d_LCD_BLACK   
#define  Color_red                      0x0003DC
#define  Color_yellow                   0x37fffd    
#define  Color_white                    0xFFFFFF    
    
#define CHANNEL_GPRS		1
#define CHANNEL_ETHERNET	2    
    
_EXTERN BYTE gDebugPrintFlag;
_EXTERN BYTE gDebugFTPFlag;
_EXTERN ezxml_t gezxml_TMS;
_EXTERN ezxml_t gTestAction;    
_EXTERN BYTE gtmpstr[SIZE_TMPBUFFER];
	
_EXTERN STR        gCAFile[10+1+3+1];

_EXTERN STR        gHostIP[15+1];
_EXTERN int        gHostPort;
//_EXTERN ezxml_t    gFunctionDATA;
_EXTERN ezxml_t    gTransFormatDATA;
//_EXTERN ezxml_t    gConfigDATA;
//_EXTERN ezxml_t    gBatchStore;     
//_EXTERN ezxml_t    gBatchInfo;  
_EXTERN Batch_Totle_STRUCT gBatchTotal;
_EXTERN BYTE       isModify;   
_EXTERN STR 	   gucDeviceID[4];
_EXTERN int	   gCOMMSTATUS;
_EXTERN BYTE       gScrpitTesting;     
_EXTERN BYTE       gECR; //定義是否開啟收銀機連線
_EXTERN ReadCardBasicData_APDU_Out  gBasicData;
_EXTERN  TRANS_DATA2  gTransData;
_EXTERN STR gTransTitle[32];
_EXTERN int inCMD_STATUS;//1.0.5.6
//_EXTERN BYTE  cInputData[256];	//input pArguments data
_EXTERN BYTE   bTMInputData[200];
_EXTERN BYTE   cAPDU[300]; //APDU COMMAND DATA
_EXTERN BYTE   cOutputData[300]; //output data
_EXTERN BYTE   cAPDUHeader[5]; //CLA INS P1 P2
_EXTERN int inInputLen,inLC,inLE;//LC LE
_EXTERN int tTxnTimeout;
_EXTERN BYTE gsBlackListVersion[30];
 _EXTERN RS232Setting gREADERPORT;
_EXTERN BYTE gECRPORT;
_EXTERN BYTE gTMS_ParmVER[11+1];               //559501
_EXTERN BYTE gTMS_ParmID[20+1];                //559502
_EXTERN BYTE gTMS_ParmData[50+1];
_EXTERN BYTE gTMS_ParmVaildStartDate[8+1]; 
_EXTERN BYTE gTransfer_TotlePackCnt[8+1];        //559601
_EXTERN BYTE gTransfer_SendedPackCnt[8+1];       //5596002
_EXTERN BYTE gTransfer_ReceivedPackCnt[8+1];     //559603
_EXTERN BYTE gTransfer_SendPackSN[8+1];    
_EXTERN BYTE gTMS_ParmVaildStartDate[8+1];     //559504
_EXTERN BYTE gTMS_ParmVaildENDDate[8+1];    
_EXTERN BYTE gSAMSlot;
_EXTERN BYTE gucTMS_ParmVER[11+1];               //559501
_EXTERN BYTE gucTMS_ParmID[20+1];                //559502
_EXTERN BYTE gucTMS_ParmData[50+1];
_EXTERN BYTE gucTMS_ParmVaildStartDate[8+1];     //559504
_EXTERN BYTE gucTMS_ParmVaildENDDate[8+1];       //559505
_EXTERN BYTE gTransfer_TotlePackCnt[8+1];        //559601
_EXTERN BYTE gTransfer_SendedPackCnt[8+1];       //5596002
_EXTERN BYTE gTransfer_ReceivedPackCnt[8+1];     //559603
_EXTERN BYTE gTransfer_SendPackSN[8+1];          //559604
_EXTERN STR gSPID[15+1];
_EXTERN STR gSubMerchantID[8+1];
_EXTERN STR gSTCODE[8+1];
//_EXTERN ezxml_t gezxml_TMS;
_EXTERN STR gFTPURL[64];
_EXTERN STR gFTPIP[36];
_EXTERN STR gFTPIP[36];
_EXTERN STR gFTPVIPIP[36];
_EXTERN STR gFTPPORT[6+1];
_EXTERN STR gFTPID[32];
_EXTERN STR gFTPPW[32];
_EXTERN STR gHOSTURL[64];
_EXTERN STR gHOSTIP[32];
_EXTERN STR gHOSTVIPIP[36];
_EXTERN STR gHOSTPORT[32];
_EXTERN long gCardRemainEV;
_EXTERN long gTXAMT;
_EXTERN STR gWaitMsgType[4+1];
_EXTERN unsigned long  gSignOnlimit;
_EXTERN USHORT   MechineStatus;
_EXTERN STR   gIDELSTR1[32];
_EXTERN STR    gIDELSTR2[32];
_EXTERN SignOnQuery_APDU_Out  gSOQ_OUT;
//_EXTERN STR   gBatchPath[64];
_EXTERN BYTE gSaveReversalflag;
_EXTERN USHORT  gOFFLINETXLIMIT;
_EXTERN USHORT  gFORCEONLINELIMIT;
_EXTERN USHORT  gBATCHTXLIMIT;
_EXTERN BYTE  gAPVER[6+1];
_EXTERN BYTE  gTxnData[8+1];
_EXTERN BYTE  gTxnTime[6+1];
_EXTERN BYTE gNEWAPFALG;
//_EXTERN long   gUnuploadTXs[1000];
_EXTERN USHORT gUnuploadTXCount;
//_EXTERN Config_STRUCT gConfigV1;
//_EXTERN Config2_STRUCT gConfig2;
//_EXTERN Config3_STRUCT gConfig3;


_EXTERN FUNCTION_TABLE_STRUCT gConfigFUNCTION;
_EXTERN BYTE gucLCDControlFlag;
_EXTERN BYTE    bSocket;
_EXTERN BYTE  gCA[2048];
_EXTERN USHORT gCAlen;
_EXTERN LONG gAutoloadAMT;
_EXTERN LONG gEVBeforeAutoload;
//_EXTERN ConfigV2_STRUCT gConfig;
//_EXTERN ConfigV3_STRUCT gConfig;
//_EXTERN ConfigV4_STRUCT gConfig;
_EXTERN   SYSINFO_STRUCT gConfig;
_EXTERN BYTE gTXCardProfile;
/*added by kobe for ECR*/
_EXTERN  ECR_OBJ ecrObj;
 _EXTERN BYTE gucLockReason;
_EXTERN BYTE gREADERLOCKED;//讀卡機出現6608時即將上鎖不再使用，須報修更換讀卡機
/*PT*/
_EXTERN BYTE bGPRSStrength;
_EXTERN BYTE bGPRSState; 
_EXTERN BYTE bgNETWORKChannel;
_EXTERN int Socketfd;
_EXTERN CURL *curl;
_EXTERN ResponseCode_STRUCT AP_RESPCODE[150];
_EXTERN ResponseCode_STRUCT CMAS_RESPCODE[40];
_EXTERN ResponseCode_STRUCT READER_RESPCODE[100];
_EXTERN ResponseCode_STRUCT ECR_RESPCODE[25];
_EXTERN ResponseCode_STRUCT SVCS_RESPCODE[30];
_EXTERN BYTE gTMSData[1024*5];
_EXTERN BYTE gReceiveData[1024*10];
_EXTERN BYTE gCOMM_CMD;
_EXTERN BYTE gIDLE;
_EXTERN  pthread_t Thread_Comm;
_EXTERN  pthread_t thread_AfterTxSuccess;
_EXTERN  pthread_t thread_SendAdvice;  
_EXTERN ReadCardNumber_APDU_Out gCardNumberInfo;
_EXTERN BYTE gSelectTable;
//_EXTERN UINT gUNUPLOADCOUNT;
#ifdef	__cplusplus
}
#endif

#endif	/* GVAR_H */

