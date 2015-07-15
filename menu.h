/* 
 * File:   menu.h
 * Author: bruce-lin
 *
 * Created on 2013年6月18日, 下午 12:02
 */

#ifndef MENU_H
#define	MENU_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "ezxml.h"

#define d_SYSCONFIG_MODIFY      1   
#define d_FAIL                  -1
#define d_ERR_CANCELBYUSER      -2    

#define d_MB_CHECK 1
#define d_MB_CONFIRM 2
  
extern size_t menufunc_count;    
typedef struct
{
	unsigned char itemname[64];
        unsigned char checked;
}Optionmenu_item;
typedef struct
{
        unsigned char TagName[32];
        BOOL enable;
        BOOL visible;
	unsigned char itemname[32];
        BOOL needpassword;
        unsigned char password[15+1];
        ezxml_t node;  
        USHORT (*func)(void);        
        
}menu_item;
typedef struct
{
        unsigned char TagName[32];
        BOOL enable;
        BOOL visible;
	unsigned char itemname[32];
        BOOL needpassword;
        unsigned char password[15+1];
        ezxml_t node;   
      
}menu_item_node;

void init_menudata(void);
USHORT  MainMenu(void);
USHORT  TXSETTINGMenu(void);
USHORT  SETTINGMenu(void);
USHORT  SYSTEMMenu(void);
USHORT  INFOMenu(void);
USHORT  TXMenu(void);
USHORT  DownloadMenu(void);
USHORT NETSETTINGMenu(void);
USHORT DebugMenu(void);
USHORT ECC_SETRTC(void);
USHORT ECC_SETEthernet(void);
USHORT ECC_SETCOMMUNICATION(void);
USHORT ReaderMenu(void);
USHORT BuiltinReaderMenu(void); 
int ECC_ShowListMeun(STR * Title,menu_item * menuitem,int itemcount);
int ECC_ShowMenu(STR * Title,menu_item * menuitem,int itemcount);
int ECC_ShowCheckListMeun(STR * Title,menu_item * menuitem,int itemcount,BYTE SingleCheck,BYTE MustCheck);
int ECC_ShowCheckListMeun2(STR * Title,Optionmenu_item * Opmenuitem,int itemcount,BYTE SingleCheck,BYTE MustCheck);
void GetFunctionSetting(void);
USHORT ShowDeviceInfo(void);
void init_DisplayConfig(void);
USHORT ShowNodeInfo(STR * title,ezxml_t NODE);
USHORT ShowConfigInfo(void);
void ECC_SETDEBUG(void);
int ECC_SelectListMeun(STR * Title,menu_item * menuitem,int itemcount);
USHORT ECC_ShowEthernetConfig(void);
USHORT Show_NodeText(ezxml_t  node);
USHORT SETOPERATIONMODEFunction(void);
USHORT SETAUTODEDUCTAMT(void);
USHORT SETReaderPortFunction(void);
USHORT PrintBarcode(void);
USHORT SETConnectMode(void);
void ECC_ShowIDLE(void);
USHORT ECC_SETFTPDEBUG(void);
USHORT SwitchSettingFunction(void);
USHORT SwitchDebugFunction(void);
USHORT DebugOptionMenu(void);
USHORT DebugModeSet_Print(void);
USHORT DebugModeSet_FTP(void);
USHORT DebugModeSet_SD(void);
USHORT SETDEDUCTAMT(void);
USHORT SETNetWorkMode(void);
USHORT BackupBatchDataUpload(void);
USHORT SelectAuto_FixDeductAMT(void);

USHORT SetADDVALUEFunctionpPassword(void);
USHORT SetDEDUCTFunctionpPassword(void);
USHORT SetRETURNFunctionpPassword(void);
USHORT SetCANCELTXNFunctionpPassword(void);
USHORT SetSETTLENFunctionpPassword(void);
USHORT ChangeTXFunctionpPassword(BYTE * TXNAME);
USHORT RESETTXFunctionpPassword(void);
USHORT SETTxFunctionPassword(void);
USHORT SetReaderCommandPortFunction(void);
USHORT ECC_SETEtherneCHANNEL(void);
USHORT ManufacturerMenu(void);
#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

