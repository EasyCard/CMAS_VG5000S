#include "ECCAPP.h"

const BYTE OPTION_UNCHECKED[] = {//Width=30, Height=4
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0xE0, 0x18, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x18, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x07, 0x18, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const BYTE OPTION_CHECKED[] = {//Width=30, Height=4
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
    0xE0, 0xE0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x07, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};



static menu_item InitMainMenuItem[] = {
    {"TX", TRUE, TRUE, "交易", FALSE, "", NULL, TXMenu},
    {"INFO", TRUE, TRUE, "查詢", FALSE, "", NULL, INFOMenu},
    {"SETTLE", TRUE, TRUE, "結帳", FALSE, "", NULL, Process_Settle},
    {"SYSTEM", TRUE, TRUE, "系統", FALSE, "", NULL, SYSTEMMenu},
    {"SETTING", TRUE, TRUE, "設定", TRUE, "", NULL, SETTINGMenu}
};

#define TOTAL_InitMainMenuItem		(sizeof(InitMainMenuItem)/sizeof(menu_item))

static menu_item InitTXMenuItem[] = {
    {"SIGNON", FALSE, FALSE, "登入", FALSE, "", NULL, Function_Signon},
    {"ADDVALUE", FALSE, FALSE, "加值", FALSE, "", NULL, Trans_ADD},
    {"DEDUCT", FALSE, FALSE, "購貨", FALSE, "", NULL, Trans_Deduct},
    //  {"DEDUCT",FALSE ,FALSE, "購貨二",FALSE,"",NULL,Trans_Deduct2},
    {"CANCELTXN", FALSE, FALSE, "取消", FALSE, "", NULL, Trans_Cancel},
    {"RETURN", FALSE, FALSE, "退貨", FALSE, "", NULL, Trans_Refund},
    {"AUTOLOADENABLE", FALSE, TRUE, "自動加值開啟", FALSE, "", NULL, Trans_AutoloadEnable},
    {"AUTOLOAD", FALSE, FALSE, "自動加值", FALSE, "", NULL, NULL},
    {"SETVALUE", FALSE, FALSE, "展期", FALSE, "", NULL, NULL},
    {"SETTLE", TRUE, TRUE, "結帳", FALSE, "", NULL, Process_Settle},
    {"POWEROFF", TRUE, TRUE, "關機", FALSE, "", NULL, PowerOff},
    {"INFORMATION", TRUE, TRUE, "資訊", FALSE, "", NULL, INFOMenu},
    {"SETTING", FALSE, FALSE, "設定", TRUE, "5909", NULL, SETTINGMenu},
    {"DEBUG", FALSE, FALSE, "DBG", TRUE, "7076", NULL, DebugMenu},
    {"ETHREBOOT", TRUE, TRUE, "通訊連線", FALSE, "", NULL, ETH_REBOOT}
};

size_t menufunc_count = sizeof (InitTXMenuItem) / sizeof (menu_item);
#define TOTAL_InitTXMenuItem	(sizeof(InitTXMenuItem)/sizeof(menu_item))	

static menu_item InitINFOMenuItem[] = {
    {"BATCHINFO", TRUE, TRUE, "總帳查詢", FALSE, "", NULL, Show_BatchData},
    {"MERCHANTINFO", TRUE, TRUE, "商店資訊", FALSE, "", NULL, ShowTMInfo},
    {"TERMINALINFO", TRUE, TRUE, "端末機資訊", FALSE, "", NULL, ShowTerminalInfo},
    {"READER", TRUE, TRUE, "設備資訊", FALSE, "", NULL, ShowDEVICEInfo},
    {"ETHERNET", TRUE, TRUE, "網路設定", FALSE, "", NULL, ECC_ShowEthernetConfig},
    {"VERSION", TRUE, TRUE, "版本資訊", FALSE, "", NULL, ShowVersionInfo},
    {"APINFO", TRUE, TRUE, "程式資訊", FALSE, "", NULL, ShowAPInfo},
    {"", TRUE, TRUE, "連續扣款票價設定", FALSE, "", NULL, SETDEDUCTAMT},
    {"", TRUE, TRUE, "交易密碼變更", FALSE, "", NULL, SETTxFunctionPassword}
};

#define TOTAL_InitINFOMenuItem		(sizeof(InitINFOMenuItem)/sizeof(menu_item))	

static menu_item InitSETTINGMenuItem[] = {
    {"", TRUE, TRUE, "SIGNON", FALSE, "", NULL, Function_Signon_forMaintenance},
    {"", TRUE, TRUE, "網路設定", FALSE, "", NULL, NETSETTINGMenu},
    {"", TRUE, TRUE, "修改時間", FALSE, "", NULL, ECC_SETRTC},
    {"", TRUE, TRUE, "系統重置", FALSE, "", NULL, SystemReset},
    {"", TRUE, TRUE, "參數列印", FALSE, "", NULL, PrintParameter},
    {"", TRUE, TRUE, "交易功能設定", FALSE, "", NULL, TXSETTINGMenu},
    {"", TRUE, TRUE, "讀卡機設定", FALSE, "", NULL, ReaderMenu},
    {"", TRUE, TRUE, "DUMP SD DATA", FALSE, "", NULL, DumpBackupTxLog2USB},
    {"", TRUE, TRUE, "交易補登", FALSE, "", NULL, BackupBatchDataUpload},
    {"", TRUE, TRUE, "收銀機連線設定", FALSE, "", NULL, usEcrModifyComportUi}, //2014.04.13 kobe added for ECR
    {"", TRUE, TRUE, "收銀機例外測試", FALSE, "", NULL, usEcrExceptionTestUi}, //2014.04.13 kobe added for ECR
    {"", TRUE, TRUE, "重設交易密碼", FALSE, "", NULL, RESETTXFunctionpPassword}
};

#define TOTAL_InitSETTINGMenuItem		(sizeof(InitSETTINGMenuItem)/sizeof(menu_item))
static menu_item InitManufacturerMenuItem[] = {
    {"", TRUE, TRUE, "SIGNON", FALSE, "", NULL, Function_Signon_forMaintenance},
    {"", TRUE, TRUE, "網路設定", FALSE, "", NULL, NETSETTINGMenu},
    {"", TRUE, TRUE, "參數列印", FALSE, "", NULL, PrintParameter},
    {"", TRUE, TRUE, "DUMP SD DATA", FALSE, "", NULL, DumpBackupTxLog2USB},
    {"", TRUE, TRUE, "交易補登", FALSE, "", NULL, BackupBatchDataUpload},
    {"", TRUE, TRUE, "收銀機連線設定", FALSE, "", NULL, usEcrModifyComportUi}, //2014.04.13 kobe added for ECR    
};
#define TOTAL_InitManufacturerMenuItem		(sizeof(InitManufacturerMenuItem)/sizeof(menu_item))

static menu_item InitReaderMenuItem[] = {
    {"", TRUE, TRUE, "內建讀卡機", FALSE, "", NULL, BuiltinReaderMenu},
    {"", TRUE, TRUE, "讀卡機連接埠", FALSE, "", NULL, SETReaderPortFunction}
};

#define TOTAL_InitReaderMenuItem		(sizeof(InitReaderMenuItem)/sizeof(menu_item))

static menu_item InitBuiltinReaderMenuItem[] = {
    {"", TRUE, TRUE, "錄碼模式", FALSE, "", NULL, ReaderCommandMode},
    {"", TRUE, TRUE, "內建式讀卡機資訊", FALSE, "", NULL, BuiltinReader_ShowInfo}
};

#define TOTAL_InitBuiltinReaderMenuItem		(sizeof(InitReaderMenuItem)/sizeof(menu_item))

static menu_item InitNETSETTINGMenuItem[] = {
    {"", TRUE, TRUE, "網路類型", FALSE, "", NULL, ECC_SETEtherneCHANNEL},
    {"", TRUE, TRUE, "本機網路", FALSE, "", NULL, ECC_SETEthernet},
    {"", TRUE, TRUE, "連線模式", FALSE, "", NULL, SETNetWorkMode},
    {"", TRUE, TRUE, "通訊參數設定", FALSE, "", NULL, ECC_SETCOMMUNICATION},
    {"", TRUE, TRUE, "網路測試", FALSE, "", NULL, Ethernet_Check}
};

#define TOTAL_InitNETSETTINGMenuItem		(sizeof(InitNETSETTINGMenuItem)/sizeof(menu_item))

static menu_item InitTXSETTINGMenuItem[] = {
    {"", TRUE, TRUE, "操作模式", FALSE, "", NULL, SETOPERATIONMODEFunction},
    {"", TRUE, TRUE, "票價設定", FALSE, "", NULL, SETDEDUCTAMT},
    {"", TRUE, TRUE, "連續扣款扣款票價", FALSE, "", NULL, SelectAuto_FixDeductAMT}
};
#define TOTAL_InitTXSETTINGMenuItem		(sizeof(InitTXSETTINGMenuItem)/sizeof(menu_item))


static menu_item InitDebugMenuItem[] = {
    {"", TRUE, TRUE, "修改交易序號", FALSE, "", NULL, usSetNEWTransSN},
    {"", TRUE, TRUE, "下載測試參數", FALSE, "", NULL, DownloadMenu},
    {"", TRUE, TRUE, "DEBUG 功能設定", FALSE, "", NULL, DebugOptionMenu},
    {"", TRUE, TRUE, "DEBUG FTP設定", FALSE, "", NULL, ECC_SETFTPDEBUG},
    {"", TRUE, TRUE, "連線主機", FALSE, "", NULL, SETConnectMode}

};
#define TOTAL_InitDebugMenuItem		(sizeof(InitDebugMenuItem)/sizeof(menu_item))
static menu_item InitDebugModeItem[] = {
    {"", TRUE, TRUE, "PRINT", FALSE, "", NULL, DebugModeSet_Print},
    {"", TRUE, TRUE, "FTP", FALSE, "", NULL, DebugModeSet_FTP},
    {"", TRUE, TRUE, "SD", FALSE, "", NULL, DebugModeSet_SD}
};
#define TOTAL_InitDebugModeItem		(sizeof(InitDebugModeItem)/sizeof(menu_item))

static menu_item InitDOWNLOADPARAMenuItem[] = {
    {"", TRUE, TRUE, "系統參數", FALSE, "", NULL, Process_DownloadConfig},
    {"", TRUE, TRUE, "測試劇本", FALSE, "", NULL, Process_DownloadScript}
};
#define TOTAL_InitDOWNLOADPARAMenuItem		(sizeof(InitDOWNLOADPARAMenuItem)/sizeof(menu_item))

static menu_item InitCommMenuItem[] = {
    {"", TRUE, TRUE, "系統參數", FALSE, "", NULL, Process_DownloadConfig},
    {"", TRUE, TRUE, "測試劇本", FALSE, "", NULL, Process_DownloadScript}
};
#define TOTAL_InitDOWNLOADPARAMenuItem		(sizeof(InitDOWNLOADPARAMenuItem)/sizeof(menu_item))
/*  Optionmenu_item  TXConfigMenuItem []= {
  { "交易功能設定",TRUE},
  { "通訊設定",TRUE},
  { "",TRUE},
  { "退貨",TRUE},
  { "結帳",FALSE},
  { "設定",FALSE}};
 */

static menu_item InitTXFunctionSetMenuItem[] = {
    {"ADDVALUE", TRUE, TRUE, "加值", FALSE, "", NULL, SetADDVALUEFunctionpPassword},
    {"DEDUCT", TRUE, TRUE, "購貨", FALSE, "", NULL, SetDEDUCTFunctionpPassword},
    {"CANCELTXN", TRUE, TRUE, "取消", FALSE, "", NULL, SetCANCELTXNFunctionpPassword},
    {"RETURN", TRUE, TRUE, "退貨", FALSE, "", NULL, SetRETURNFunctionpPassword},
    {"SETTLE", TRUE, TRUE, "結帳", FALSE, "", NULL, SetSETTLENFunctionpPassword},
};
#define TOTAL_InitTXFunctionSetMenuItem		(sizeof(InitTXFunctionSetMenuItem)/sizeof(menu_item))

#define MAXMENUITEM  15
// ezxml_t CurrNode;



menu_item MMI[TOTAL_InitMainMenuItem],
TMI[TOTAL_InitTXMenuItem],
IQI[TOTAL_InitINFOMenuItem],
STI[TOTAL_InitSETTINGMenuItem],
MTI[TOTAL_InitManufacturerMenuItem],
TSI[TOTAL_InitTXSETTINGMenuItem];
//Declare Global Variable //
//const STR *keyboardLayoutEnglish[]={" 0", "qzQZ1", "abcABC2", "defDEF3", "ghiGHI4","jklJKL5", "mnoMNO6", "prsPRS7", "tuvTUV8", "wxyWXY9", ":;/\\|?,.<>", ".!@#$%^&*()"};
//numeric keyboard (0123456789) and radix point '.'
//const STR *keyboardLayoutNumberWithRadixPoint[]={"0", "1", "2", "3", "4", "5", "6", "7","8", "9", "", "."};
//numeric keyboard (0123456789) without radix point
//const STR *keyboardLayoutNumber[]={"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "",""};

void init_DisplayConfig() {
    CTOS_LCDTTFSelect(d_FONT_TTF, 0);
    CTOS_LCDFontSelectMode(d_FONT_TTF_MODE);
    CTOS_LCDSelectMode(d_LCD_GRAPHIC_320x240_MODE);
    //  CTOS_PrinterFontSelectMode(d_FONT_TTF_MODE);
    // CTOS_PrinterTTFSelect(d_FONT_TTF,0);
    // CTOS_LanguagePrinterFontSize(d_FONT_16x30,0,d_FONT_TYPE1);

}

void init_menudata() {

    //     memset(MMI,0x00,sizeof(MMI));
    //     memcpy((unsigned char *)&MMI,(unsigned char *)&InitMainMenuItem,sizeof(InitMainMenuItem));

    memset(TMI, 0x00, sizeof (TMI));
    memcpy((unsigned char *) &TMI, (unsigned char *) &InitTXMenuItem, sizeof (InitTXMenuItem));

    memset(IQI, 0x00, sizeof (IQI));
    memcpy((unsigned char *) &IQI, (unsigned char *) &InitINFOMenuItem, sizeof (InitINFOMenuItem));

    memset(STI, 0x00, sizeof (STI));
    memcpy((unsigned char *) &STI, (unsigned char *) &InitSETTINGMenuItem, sizeof (InitSETTINGMenuItem));

    memset(MTI, 0x00, sizeof (MTI));
    memcpy((unsigned char *) &MTI, (unsigned char *) &InitManufacturerMenuItem, sizeof (InitManufacturerMenuItem));

    memset(TSI, 0x00, sizeof (TSI));
    memcpy((unsigned char *) &TSI, (unsigned char *) &InitTXSETTINGMenuItem, sizeof (InitTXSETTINGMenuItem));

    GetFunctionSetting();
}

void GetFunctionSetting() {
    FUNCTION_STRUCT func;
    int i;

    for (i = 0; i < TOTAL_InitTXMenuItem; i++) {
        GetFunction((FUNCTION_STRUCT *) & TMI[i]);
    }
}

/*
void GetFunctionSetting_old()
{
  
    int i;
 SystemLog("GetFunctionSetting_old","Start");
     gFunctionDATA = ezxml_parse_file(FunctionXML);
     ezxml_t FUNCTION,TYPE;
    
    for (FUNCTION = ezxml_child(gFunctionDATA, "MAINFUNCTION"); FUNCTION; FUNCTION = FUNCTION->sibling) {
        for(i=0;i<TOTAL_InitMainMenuItem;i++){
            TYPE= ezxml_child(FUNCTION, MMI[i].TagName);
            if(TYPE!=NULL){
                if(ezxml_child(TYPE, "enable")!=NULL)
                          MMI[i].enable=atoi(ezxml_child(TYPE, "enable")->txt);
                if(ezxml_child(TYPE, "visible")!=NULL)
                          MMI[i].visible=atoi(ezxml_child(TYPE, "visible")->txt);
                 if(ezxml_child(TYPE, "needpassword")!=NULL)
                          MMI[i].needpassword=atoi(ezxml_child(TYPE, "needpassword")->txt);
                if(ezxml_child(TYPE, "itemname")!=NULL)
                        memcpy( MMI[i].itemname,ezxml_child(TYPE, "itemname")->txt,strlen(ezxml_child(TYPE, "itemname")->txt));
                if(ezxml_child(TYPE, "PASSWORD")!=NULL)
                        memcpy( MMI[i].password,ezxml_child(TYPE, "PASSWORD")->txt,strlen(ezxml_child(TYPE, "PASSWORD")->txt));
            }
        } 
    }
    
    for (FUNCTION = ezxml_child(gFunctionDATA, "TXFUNCTION"); FUNCTION; FUNCTION = FUNCTION->sibling) {
        for(i=0;i<TOTAL_InitTXMenuItem;i++){
            TYPE= ezxml_child(FUNCTION, TMI[i].TagName);
            if(TYPE!=NULL){
                if(ezxml_child(TYPE, "enable")!=NULL)
                          TMI[i].enable=atoi(ezxml_child(TYPE, "enable")->txt);
                if(ezxml_child(TYPE, "visible")!=NULL)
                          TMI[i].visible=atoi(ezxml_child(TYPE, "visible")->txt);
                 if(ezxml_child(TYPE, "needpassword")!=NULL)
                          TMI[i].needpassword=atoi(ezxml_child(TYPE, "needpassword")->txt);
                if(ezxml_child(TYPE, "itemname")!=NULL)
                        memcpy( TMI[i].itemname,ezxml_child(TYPE, "itemname")->txt,strlen(ezxml_child(TYPE, "itemname")->txt));
                if(ezxml_child(TYPE, "PASSWORD")!=NULL)
                        memcpy( TMI[i].password,ezxml_child(TYPE, "PASSWORD")->txt,strlen(ezxml_child(TYPE, "PASSWORD")->txt));
            }
        } 
    }
   ezxml_free(gFunctionDATA);
   
}
 */
USHORT ShowConfigInfo() {
    // System_struct SysInfo;
    USHORT ret;
    int iret;
    BYTE key;

    ezxml_t NODE, ITEM;
    STR title[16] = "";
    int i;

    i = 0;
    ezxml_t ConfigDATA = ezxml_parse_file(ConfigXML);
    if (ConfigDATA == NULL) {
        return d_Fail;
    }

    NODE = ConfigDATA;
    if (NODE == NULL) {
        return -1;
    }

    GetXmlNodeattr_Name(NODE, title);
    NODE = NODE->child;
    isModify = 0;

    ret = ShowNodeInfo(title, NODE);
    if (ret == d_SYSCONFIG_MODIFY) {

        iret = MessageBox("系統資訊", "", "資料已修改", "是否需要存檔?", "", d_MB_CONFIRM);
        if (iret == d_OK) {
            ret = ECC_WriteXMLFILE(ConfigXML, ConfigDATA);
            if (ret == d_OK)
                Sysinfo2_GetData();
            //  Config_GetData();
        }
    }
    ezxml_free(ConfigDATA);
    return 0;
}

USHORT ShowNodeInfo(STR * title, ezxml_t NODE) {
    // System_struct SysInfo;
    USHORT ret;
    BYTE key;
    menu_item menu[20];
    ezxml_t N, ITEM;
    STR titleName[16];
    int i;
    memset(menu, 0x00, sizeof (menu));

    i = 0;

    N = NODE;
    while (N != NULL) {
        GetXmlNodeattr_Name(N, menu[i].itemname);
        menu[i].enable = TRUE;
        menu[i].visible = TRUE;
        menu[i].node = N;
        N = N->sibling;
        i++;
    }

    int selectitem;
    do {
        selectitem = ECC_SelectListMeun(title, menu, i);
        if (selectitem < 0)
            break;
        ITEM = menu[selectitem].node;
        memset(titleName, 0x00, sizeof (titleName));
        if (ezxml_attr(ITEM, "name") != NULL)
            sprintf(titleName, "%s", ezxml_attr(ITEM, "name"));
        else
            sprintf(titleName, "%s", ITEM->name);

        if (ITEM->child != NULL) {
            ShowNodeInfo(titleName, ITEM->child);
            ret = 0;
        } else {
            ret = Show_NodeText(ITEM);
            if (ret == d_SYSCONFIG_MODIFY) {
                isModify = 1;
                return ret;
            }
        }
    } while (1);

    return ret;
}

USHORT Show_NodeText(ezxml_t node) {
    BYTE key;
    BYTE buff[16];

    BYTE Title[16];
    BYTE line[32 + 1];
    ;
    int MaxLne;
    USHORT ret;
    FILE * pFile;
    STR NAME[16];
    STR TYPE[8 + 1];
    //Declare Global Variable //
    STR * keyboardLayoutEnglish[] = {" 0", "qzQZ1", "abcABC2", "defDEF3", "ghiGHI4", "jklJKL5", "mnoMNO6", "prsPRS7", "tuvTUV8", "wxyWXY9", ":;/\\|?,.<>", ".!@#$%^&*()"};
    //numeric keyboard (0123456789) and radix point '.'
    STR * keyboardLayoutNumberWithRadixPoint[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "", "."};
    //numeric keyboard (0123456789) without radix point
    STR * keyboardLayoutNumber[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "", ""};
    STR **InputType;

    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    CTOS_LCDTSelectFontSize(d_FONT_16x30);
    CTOS_LCDTClearDisplay();

    CTOS_LCDTSetReverse(TRUE);
    GetXmlNodeattr_Name(node, NAME);
    CTOS_LCDTPrintXY(3, 1, (UCHAR *) NAME);

    CTOS_LCDTSetReverse(FALSE);

    memset(buff, 0x00, 16);
    if (ezxml_attr(node, "readwrite") != NULL)
        sprintf(buff, "%s", ezxml_attr(node, "readwrite"));
    memset(TYPE, 0x00, sizeof (TYPE));
    if (ezxml_attr(node, "type") != NULL)
        sprintf(TYPE, "%s", ezxml_attr(node, "type"));

    if ((buff != NULL) && strcmp(buff, "rw") == 0) {
        CTOS_LCDTPrintXY(1, 3, node->txt);
        CTOS_LCDTPrintXY(1, 8, "(x)離開，(0)修改");
        do {
            CTOS_KBDGet(&key);
            if (key == d_KBD_CANCEL) return d_ERR_CANCELBYUSER;
            if (key == d_KBD_0) {
                if (strcmp(TYPE, "str") == 0) {
                    InputType = keyboardLayoutEnglish;

                } else {
                    InputType = keyboardLayoutNumberWithRadixPoint;
                }
                MaxLne = (int) wub_str_2_long((unsigned char *) ezxml_attr(node, "maxlen"));
                memset(buff, 0x00, sizeof (buff));
                ret = CTOS_UIKeypad(3, 5, (STR **) & keyboardLayoutNumberWithRadixPoint, 200, 1, d_FALSE, d_FALSE, 0, 0, buff, MaxLne + 1);
                if (ret == d_OK && (strlen(buff) > 0)) {
                    ezxml_set_txt_d(node, buff);
                    return d_SYSCONFIG_MODIFY;
                }
            }
        } while (1);


    } else {
        CTOS_LCDTPrintXY(1, 3, node->txt);
        CTOS_LCDTPrintXY(1, 8, "(x)離開");
        CTOS_KBDGet(&key);
    }



    return d_ERR_CANCELBYUSER;
}

void ECC_ShowIDLE() {
    int Windowwidth = 240;
    int Windowlenght = 320;
    int Xoffset = 0;
    STR Title[32];



    gIDLE = TRUE;

    CTOS_LCDTClearDisplay();

    CTOS_LCDGClearCanvas();

    //    Reader_CLEAR_LED();


    /*   BYTE Date[64+1];
       CTOS_RTC SetRTC;
       USHORT ret = CTOS_RTCGet(&SetRTC);
       if(ret==0){
              sprintf(Date,"%04d/%02d/%02d  %02d:%02d      V%s",SetRTC.bYear + 2000,SetRTC.bMonth,SetRTC.bDay,SetRTC.bHour,SetRTC.bMinute,gAPVER);
         
          }
       sprintf(Title,Date);
       CTOS_LCDGClearCanvas();*/
    //remove by bruce 20140905
    /*   if( MechineStatus & Status_READER_Disconnect){
            CTOS_LCDGTextOut(0,45,"讀卡機發生錯誤",0x1830,FALSE);
            CTOS_LCDGTextOut(0,45+50+10,"請檢查讀卡機連線",0x1830,FALSE);
       }else if(MechineStatus & Status_ETHERNET_Disconnect){
           CTOS_LCDGTextOut(0,45,"網路無法連線",0x1830,FALSE);
            CTOS_LCDGTextOut(0,45+50+10,"請確認!!!",0x1830,FALSE);
       }else if(MechineStatus & Status_SignOnFail){
            CTOS_LCDGTextOut(0,45,"系統登入未完成",0x1830,FALSE);
            CTOS_LCDGTextOut(0,45+50+10,"請重新開機!!!",0x1830,FALSE);
       }else{
          CTOS_LCDGShowBMPPic(0, 30, "bibi2.bmp" );
       }*/

    if (ecrObj.ecrOn) {
        Setcolor(Color_white, Color_black);
        CTOS_LCDSelectMode(d_LCD_GRAPHIC_320x240_MODE);

        CTOS_LCDGTextOut(0, 50, "收銀機命令", 0x2424, FALSE);
        CTOS_LCDGTextOut(0, 50 * 2, "等待中...", 0x2424, FALSE);
        CTOS_LCDGTextOut(0, 240 - 18, "F1:功能目錄", d_FONT_9x18, TRUE);
        CTOS_LCDGTextOut(80, 240 - 18, "F2:查詢餘額", d_FONT_9x18, TRUE);
        CTOS_LCDGTextOut(80 * 2, 240 - 18, "F3:重印帳單", d_FONT_9x18, TRUE);
        CTOS_LCDGTextOut(80 * 3, 240 - 18, "F4:交易明細", d_FONT_9x18, TRUE);
        return;
    } else {
        CTOS_LCDSelectMode(d_LCD_GRAPHIC_320x240_MODE);
        CTOS_LCDGShowBMPPic(0, 18, "bibi2.bmp");
    }
    //   printf("[%s,%d] trace...\n",__FUNCTION__,__LINE__);
    /*   else if( Process_SignOnRequest(&gTransData)!=d_OK){
           CTOS_LCDTClearDisplay();
            CTOS_LCDGTextOut(0,45,"系統登入未完成",0x1830,FALSE);
            CTOS_LCDGTextOut(0,45+50+10,"請重試登入!!!",0x1830,FALSE);
       }*/

    // Xoffset=(Windowlenght/2)-(((strlen(Title)/3)*24));

    //  CTOS_LCDGTextOut(0,0,Title,d_FONT_16x30,FALSE); 
    //  CTOS_LCDGSetBox(0,0,320,30,d_LCD_FILL_XOR);  
    Setcolor(Color_ezblue, Color_yellow);

    //  Sysinfo2_GetEDCSystemMemoryStatus();
    //  CTOS_LCDGTextOut(0,240-18-18-30,gConfig.DEVICE.MEMORY.USEDRAMSIZE,d_FONT_9x18,FALSE);


    Setcolor(Color_ezblue, Color_black);

    // CTOS_LCDGTextOut(30,96,gIDELSTR1,0x1830,FALSE);
    // CTOS_LCDGTextOut(30,96+50+10,gIDELSTR2,0x1830,FALSE);
    /*    
     CTOS_LCDGTextOut(0,240-18-18,"F1      ",d_FONT_9x18,FALSE);
     CTOS_LCDGTextOut(80,240-18-18,"F2      ",d_FONT_9x18,FALSE);
     CTOS_LCDGTextOut(80*2,240-18-18,"F3      ",d_FONT_9x18,FALSE);
     CTOS_LCDGTextOut(80*3,240-18-18,"F4      ",d_FONT_9x18,FALSE);
     */
    Setcolor(Color_ezblue, Color_black);
    //   printf("[%s,%d] trace...\n",__FUNCTION__,__LINE__);
    CTOS_LCDGTextOut(0, 240 - 18, "F1:功能目錄", d_FONT_9x18, FALSE);
    CTOS_LCDGTextOut(80, 240 - 18, "F2:查詢餘額", d_FONT_9x18, FALSE);
    CTOS_LCDGTextOut(80 * 2, 240 - 18, "F3:重印帳單", d_FONT_9x18, FALSE);
    CTOS_LCDGTextOut(80 * 3, 240 - 18, "F4:交易明細", d_FONT_9x18, FALSE);
    //    printf("[%s,%d] trace...\n",__FUNCTION__,__LINE__);

    ShowUPStatusbar();
    //    printf("[%s,%d] trace...\n",__FUNCTION__,__LINE__);
}

int ECC_ShowMenu(STR * Title, menu_item * menuitem, int itemcount) {

    BYTE key;
    BYTE buff[128];
    BYTE str1[16];
    int ret, len;
    int Btnwidth = 60;
    int Btnlenght = 106;
    int Windowwidth = 240;
    int Windowlenght = 320;
    int x = 0, y = 30;
    int Column, Row, currentItem;
    int pagestart, itemoffset;
    //Clear Canvas //
    int Xoffset = 0;
    int Titlesize = strlen(Title); //utf8
    BYTE ItemName[12 + 1];
    memset(str1, 0x00, sizeof (str1));
    Setcolor(Color_white, Color_black);

    //Draw a pixel on the canvas //
    pagestart = 0;
    itemoffset = 0;

    int i, EnableItemCount;
    i = 0;
    EnableItemCount = 0;
    menu_item menu[MAXMENUITEM];
    memset(menu, 0x00, sizeof (menu));
    for (i = 0; i < itemcount; i++) {
        if ((menuitem[i].enable == TRUE) && (menuitem[i].visible == TRUE)) {
            memcpy((BYTE *) & menu[EnableItemCount++], (BYTE *) & menuitem[i], sizeof (menu_item));
        }
    }


    do {
        CTOS_LCDGClearCanvas();
        CTOS_LCDGShowBMPPic(0, 0, BackgroundPIC);
        Xoffset = (Windowlenght / 2)-(((Titlesize / 3)*30));
        CTOS_LCDGTextOut(Xoffset, 0, Title, d_FONT_16x30, FALSE);
        // CTOS_LCDGSetBox(0,0,320,30,d_LCD_FILL_XOR);  
        for (Row = 0; Row < 3; Row++) {
            y = 30;
            if (Row > 0)
                y += Btnwidth * Row;
            else
                y = 30;
            for (Column = 0; Column < 3; Column++) {
                x = 0;
                if (Column > 0)
                    x += Btnlenght * Column;
                else
                    x = 0;
                //CTOS_LCDGSetBox(x,y,Btnlenght,Btnwidth,1);  
                //CTOS_LCDGShowPic(x,y,BTN,sizeof(BTN),Btnlenght);
                if (Row == 0) {
                    itemoffset = pagestart + Column;
                } else {
                    itemoffset = pagestart + (Column + (Row * 3));
                }
                memset(ItemName, 0x00, sizeof (ItemName));

                sprintf(ItemName, "%d.%s", (itemoffset % 9) + 1, menu[itemoffset].itemname);
                len = strlen(menu[itemoffset].itemname);
                if ((strlen(menu[itemoffset].itemname) <= (3 * 3 + 1))) {
                    if (strlen(menu[itemoffset].itemname) != 0) {
                        memcpy(str1, menu[itemoffset].itemname, strlen(menu[itemoffset].itemname));
                        sprintf(ItemName, "%d.%s", (itemoffset % 9) + 1, str1);
                        CTOS_LCDGTextOut(x + 5, y + 16, ItemName, d_FONT_16x30, FALSE);
                    }
                } else if ((strlen(menu[itemoffset].itemname) == (4 * 3))) {

                    memcpy(str1, menu[itemoffset].itemname, strlen(menu[itemoffset].itemname));
                    sprintf(ItemName, "%d.", (itemoffset % 9) + 1);
                    CTOS_LCDGTextOut(x + 5, y + 16, ItemName, d_FONT_16x30, FALSE);
                    CTOS_LCDGTextOut(x + 5 + (16 + 2), y + 16, str1, d_FONT_12x24, FALSE);
                } else if (strcmp(menu[itemoffset].itemname, "自動加值功能開啟") == 0) {
                    sprintf(ItemName, "%d.", (itemoffset % 9) + 1);
                    CTOS_LCDGTextOut(x + 5, y + 16, ItemName, d_FONT_16x30, FALSE);
                    CTOS_LCDGTextOut(x + 5 + (16 + 2), y + 5, "自動加值", d_FONT_12x24, FALSE);
                    CTOS_LCDGTextOut(x + 5 + (16 + 2), y + 30, "功能開啟", d_FONT_12x24, FALSE);
                }/*else{
                
                    CTOS_LCDGTextOut(x+5,y+16,ItemName,d_FONT_16x30,FALSE);
                }*/
                //   CTOS_LCDGTextOut(x+5,y+16,menu[itemoffset].itemname,d_FONT_16x30,FALSE);
            }
            if (itemoffset >= EnableItemCount - 1)
                break;
        }


        CTOS_LCDGTextOut(16, 210 + 8, "F1 上一頁", d_FONT_8x16, FALSE);
        CTOS_LCDGTextOut(106 + 16, 210 + 8, "F2 下一頁", d_FONT_8x16, FALSE);
        CTOS_LCDGTextOut(212 + 16, 210 + 8, "X  離開", d_FONT_8x16, FALSE);
        CTOS_TimeOutSet(TIMER_ID_4, 100 * 30);
keyin:

        while (1) {
            CTOS_KBDHit(&key);
            if (key != 0xff) {
                CTOS_TimeOutSet(TIMER_ID_4, 100 * 30);
                break;
            }
            if (CTOS_TimeOutCheck(TIMER_ID_4) == d_YES)
                return d_ERR_CANCELBYUSER;
        }
        //CTOS_KBDGet(&key);
        switch (key) {
            case '1':
                //   CTOS_LCDGSetBox ( 0+5, 30+4, 106-10,60-8, d_LCD_FILL_XOR);
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                currentItem = pagestart + (key - 0x30 - 1);
                memset(buff, 0x00, sizeof (buff));
                if (menu[currentItem].needpassword == TRUE) {

                    ret = ShowInputBox(menu[currentItem].itemname, "請輸入密碼", buff, 10 + 1, 0, '*');
                    if (ret == d_ERR_CANCELBYUSER) {
                        ret = MessageBox(menu[currentItem].itemname, "", "使用者取消輸入", "請確認!!", "", d_MB_CHECK);
                        break;
                    }
                    if (strcmp(buff, menu[currentItem].password) != 0) {
                        ret = MessageBox(menu[currentItem].itemname, "", "密碼錯誤", "請確認!!", "", d_MB_CHECK);
                        break;
                    }
                }
                // ret =pagestart+(key-0x30);

                if (menu[currentItem].func != NULL)
                    ret = (*menu[currentItem].func)();
                printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
                return d_ERR_CANCELBYUSER;
                //return d_OK;  
                break;

            case d_KBD_F1:
                if (pagestart >= 9)
                    pagestart -= 9;
                else {
                    goto keyin;
                }
                break;
            case d_KBD_F2:
                if (EnableItemCount > 9 && ((pagestart / 9)<(EnableItemCount / 9)))
                    pagestart += 9;
                else {

                    goto keyin;
                }
                break;
            case d_KBD_CANCEL:
                return d_ERR_CANCELBYUSER;
        }

    } while (1);
}

int ECC_ShowListMeun(STR * Title, menu_item * menuitem, int itemcount) {
    BYTE key;
    int ret;
    int Btnwidth = 30;
    int Btnlenght = 320;
    int Windowwidth = 240;
    int Windowlenght = 320;
    int x = 0, y = 30;
    int Row;
    int pagestart, itemoffset, cursor;
    //Clear Canvas //
    int Xoffset = 0, Yoffset;

    int Titlesize = strlen(Title); //utf8
    int i, EnableItemCount;
    BYTE REDRAW = TRUE;
    i = 0;
    EnableItemCount = 0;
    menu_item menu[MAXMENUITEM];
    for (i = 0; i < itemcount; i++) {
        if (menuitem[i].enable == TRUE) {
            memcpy((BYTE *) & menu[EnableItemCount++], (BYTE *) & menuitem[i], sizeof (menu_item));
        }
    }

    Setcolor(Color_white, Color_black);
    //Draw a pixel on the canvas //
    pagestart = 0; //頁面起點
    itemoffset = 0; //
    cursor = 0; //焦點

    do {

        // CTOS_LCDGClearCanvas();
        if (REDRAW == TRUE) {
            CTOS_LCDGShowBMPPic(0, 0, BackgroundPIC);
            Xoffset = (Windowlenght / 2)-(((Titlesize / 3)*24));
            CTOS_LCDGTextOut(Xoffset, 0, Title, d_FONT_16x30, FALSE);
            CTOS_LCDGSetBox(0, 0, 320, 30, d_LCD_FILL_XOR);
            REDRAW = FALSE;
        }

        for (Row = 0; Row < 6; Row++) {
            x = 0;
            y = 30;
            if (Row > 0)
                y += Btnwidth * Row;
            else
                y = 30;

            //CTOS_LCDGSetBox(x,y,Btnlenght,Btnwidth,1);  
            //CTOS_LCDGShowPic(x,y,BTN,sizeof(BTN),Btnlenght);

            itemoffset = pagestart + Row;
            CTOS_LCDGSetBox(x, y, 320, 30, 0);
            if (itemoffset >= EnableItemCount)
                CTOS_LCDGTextOut(x + 5, y, "               ", d_FONT_16x30, FALSE);
            else
                CTOS_LCDGTextOut(x + 5, y, menu[itemoffset].itemname, d_FONT_16x30, FALSE);

            if (cursor == Row) {
                CTOS_LCDGSetBox(x, y, 320, 30, d_LCD_FILL_XOR);
            }



        }

        CTOS_LCDGTextOut(16, 210 + 8, "UP", d_FONT_8x16, TRUE);
        CTOS_LCDGTextOut(106 + 16, 210 + 8, "DOWN", d_FONT_8x16, TRUE);
        CTOS_LCDGTextOut(212 + 16, 210 + 8, "X  離開", d_FONT_8x16, TRUE);


keyin:

        CTOS_KBDGet(&key);
        switch (key) {

            case d_KBD_UP:
                if (cursor >= 0) {
                    cursor--;
                    if (cursor < 0) {
                        if (pagestart > 0) {
                            cursor = 5;
                            pagestart -= 6;
                        } else
                            cursor = 0;


                    }
                    continue;
                } else {
                    goto keyin;
                }
                break;
            case d_KBD_DOWN:

                if (cursor <= 5) {

                    if ((pagestart + cursor + 1) >= EnableItemCount) {
                        goto keyin;
                    } else {
                        cursor++;
                        if (cursor >= 6) {
                            pagestart += 6;
                            cursor = 0;
                        }
                        continue;
                    }
                } else {
                    goto keyin;
                }
                break;
            case d_KBD_ENTER:

                ret = (*menu[pagestart + cursor].func)();
                REDRAW = TRUE;
                break;
            case d_KBD_CANCEL:
                return d_ERR_CANCELBYUSER;
        }

    } while (1);
}

int ECC_SelectListMeun(STR * Title, menu_item * menuitem, int itemcount) {
    BYTE key;
    int ret;
    int Btnwidth = 30;
    int Btnlenght = 320;
    int Windowwidth = 240;
    int Windowlenght = 320;
    int x = 0, y = 30;
    int Row;
    int pagestart, itemoffset, cursor;
    //Clear Canvas //
    int Xoffset = 0, Yoffset;

    int Titlesize = strlen(Title); //utf8
    int i, EnableItemCount;
    BYTE REDRAW = TRUE;
    i = 0;
    EnableItemCount = 0;
    menu_item menu[MAXMENUITEM];
    for (i = 0; i < itemcount; i++) {
        if (menuitem[i].enable == TRUE) {
            memcpy((BYTE *) & menu[EnableItemCount++], (BYTE *) & menuitem[i], sizeof (menu_item));
        }
    }

    Setcolor(Color_white, Color_black);
    //Draw a pixel on the canvas //
    pagestart = 0; //頁面起點
    itemoffset = 0; //
    cursor = 0; //焦點

    do {

        // CTOS_LCDGClearCanvas();
        if (REDRAW == TRUE) {
            CTOS_LCDGShowBMPPic(0, 0, BackgroundPIC);
            Xoffset = (Windowlenght / 2)-(((Titlesize / 3)*24));
            CTOS_LCDGTextOut(Xoffset, 0, Title, d_FONT_16x30, FALSE);
            CTOS_LCDGSetBox(0, 0, 320, 30, d_LCD_FILL_XOR);
            REDRAW = FALSE;

        }

        for (Row = 0; Row < 6; Row++) {
            x = 0;
            y = 30;
            if (Row > 0)
                y += Btnwidth * Row;
            else
                y = 30;

            //CTOS_LCDGSetBox(x,y,Btnlenght,Btnwidth,1);  
            //CTOS_LCDGShowPic(x,y,BTN,sizeof(BTN),Btnlenght);

            itemoffset = pagestart + Row;
            CTOS_LCDGSetBox(x, y, 320, 30, 0);
            if (itemoffset >= EnableItemCount)
                CTOS_LCDGTextOut(x + 5, y, "               ", d_FONT_16x30, FALSE);
            else
                CTOS_LCDGTextOut(x + 5, y, menu[itemoffset].itemname, d_FONT_16x30, FALSE);

            if (cursor == Row) {
                CTOS_LCDGSetBox(x, y, 320, 30, d_LCD_FILL_XOR);
            }



        }

        CTOS_LCDGTextOut(16, 210 + 8, "UP", d_FONT_8x16, TRUE);
        CTOS_LCDGTextOut(106 + 16, 210 + 8, "DOWN", d_FONT_8x16, TRUE);
        CTOS_LCDGTextOut(212 + 16, 210 + 8, "X  離開", d_FONT_8x16, TRUE);


keyin:

        CTOS_KBDGet(&key);
        switch (key) {

            case d_KBD_UP:
                if (cursor >= 0) {
                    cursor--;
                    if (cursor < 0) {
                        if (pagestart > 0) {
                            cursor = 5;
                            pagestart -= 6;
                        } else
                            cursor = 0;


                    }
                    continue;
                } else {
                    goto keyin;
                }
                break;
            case d_KBD_DOWN:

                if (cursor <= 5) {

                    if ((pagestart + cursor + 1) >= EnableItemCount) {
                        goto keyin;
                    } else {
                        cursor++;
                        if (cursor >= 6) {
                            pagestart += 6;
                            cursor = 0;
                        }
                        continue;
                    }
                } else {
                    goto keyin;
                }
                break;
            case d_KBD_ENTER:
                return pagestart + cursor;
                break;
            case d_KBD_CANCEL:
                return d_ERR_CANCELBYUSER;
        }

    } while (1);
}

int ECC_ShowCheckListMeun(STR * Title, menu_item * menuitem, int itemcount, BYTE SingleCheck, BYTE MustCheck) {
    BYTE key;
    int Btnwidth = 30;
    int Btnlenght = 320;
    int Windowwidth = 240;
    int Windowlenght = 320;
    int x = 0, y = 30;
    int Row, i;
    int pagestart, itemoffset, cursor;
    int checkedcount;
    //Clear Canvas //
    int Xoffset = 0, Yoffset;

    int Titlesize = strlen(Title); //utf8
    Setcolor(Color_white, Color_black);

    //Draw a pixel on the canvas //
    pagestart = 0; //頁面起點
    itemoffset = 0; //
    cursor = 0; //焦點
    CTOS_LCDGShowBMPPic(0, 0, BackgroundPIC);
    Xoffset = (Windowlenght / 2)-(((Titlesize / 3)*24));
    CTOS_LCDGTextOut(Xoffset, 0, Title, d_FONT_16x30, FALSE);
    CTOS_LCDGSetBox(0, 0, 320, 30, d_LCD_FILL_XOR);
    do {

        // CTOS_LCDGClearCanvas();


        for (Row = 0; Row < 6; Row++) {
            x = 0;
            y = 30;
            if (Row > 0)
                y += Btnwidth * Row;
            else
                y = 30;

            //CTOS_LCDGSetBox(x,y,Btnlenght,Btnwidth,1);  
            //CTOS_LCDGShowPic(x,y,BTN,sizeof(BTN),Btnlenght);

            itemoffset = pagestart + Row;
            CTOS_LCDGSetBox(x + 30, y, 320, 30, 0);
            if (itemoffset >= itemcount)
                CTOS_LCDGTextOut(x + 5, y, "                              ", 0x1218, FALSE);
            else {
                if (menuitem[itemoffset].enable == TRUE) {
                    CTOS_LCDGShowPic(x, y, (BYTE *) & OPTION_CHECKED, sizeof (OPTION_CHECKED), 30);
                    CTOS_LCDGTextOut(x + 30 + 5, y, menuitem[itemoffset].itemname, 0x1218, FALSE);
                } else {
                    CTOS_LCDGShowPic(x, y, (BYTE*) & OPTION_UNCHECKED, sizeof (OPTION_UNCHECKED), 30);
                    CTOS_LCDGTextOut(x + 30 + 5, y, menuitem[itemoffset].itemname, 0x1218, FALSE);
                }

            }
            if (cursor == Row) {
                CTOS_LCDGSetBox(x + 30, y, 320, 30, d_LCD_FILL_XOR);
            }



        }

        CTOS_LCDGTextOut(16, 210 + 8, "UP 向上", d_FONT_8x16, TRUE);
        CTOS_LCDGTextOut(80 + 16, 210 + 8, "DOWN 向下", d_FONT_8x16, TRUE);
        CTOS_LCDGTextOut(160 + 16, 210 + 8, " (OK)選擇 (X)離開", d_FONT_8x16, TRUE);


keyin:

        CTOS_KBDGet(&key);
        switch (key) {

            case d_KBD_UP:
                if (cursor >= 0) {
                    cursor--;
                    if (cursor < 0) {
                        if (pagestart > 0) {
                            cursor = 5;
                            pagestart -= 6;
                        } else
                            cursor = 0;


                    }
                    continue;
                } else {
                    goto keyin;
                }
                break;
            case d_KBD_DOWN:

                if (cursor <= 5) {

                    if ((pagestart + cursor + 1) >= itemcount) {
                        goto keyin;
                    } else {
                        cursor++;
                        if (cursor >= 6) {
                            pagestart += 6;
                            cursor = 0;
                        }
                        continue;
                    }
                } else {
                    goto keyin;
                }
                break;

            case d_KBD_ENTER:
                if (menuitem[pagestart + cursor].enable == TRUE) {
                    if (MustCheck == TRUE) {
                        checkedcount = 0;
                        for (i = 0; i < itemcount; i++) {
                            if (menuitem[i].enable == TRUE) {
                                checkedcount++;
                            }
                        }
                        if (checkedcount > 1) {
                            menuitem[pagestart + cursor].enable = FALSE;

                        }

                    }
                    break;
                } else {
                    if (SingleCheck == TRUE) {
                        for (i = 0; i < itemcount; i++) {
                            menuitem[i].enable = FALSE;
                        }
                        menuitem[pagestart + cursor].enable = TRUE;
                    } else {
                        menuitem[pagestart + cursor].enable = TRUE;
                    }
                }


                break;


            case d_KBD_CANCEL:
                return d_OK;
            default:
                continue;
        }

    } while (1);
}

int ECC_ShowCheckListMeun2(STR * Title, Optionmenu_item * Opmenuitem, int itemcount, BYTE SingleCheck, BYTE MustCheck) {
    BYTE key;
    int Btnwidth = 30;
    int Btnlenght = 320;
    int Windowwidth = 240;
    int Windowlenght = 320;
    int x = 0, y = 30;
    int Row, i;
    int pagestart, itemoffset, cursor;
    int checkedcount;
    //Clear Canvas //
    int Xoffset = 0, Yoffset;

    int Titlesize = strlen(Title); //utf8

    Setcolor(Color_white, Color_black);
    //Draw a pixel on the canvas //
    pagestart = 0; //頁面起點
    itemoffset = 0; //
    cursor = 0; //焦點
    CTOS_LCDGShowBMPPic(0, 0, BackgroundPIC);
    Xoffset = (Windowlenght / 2)-(((Titlesize / 3)*24));
    CTOS_LCDGTextOut(Xoffset, 0, Title, d_FONT_24x24, FALSE);
    CTOS_LCDGSetBox(0, 0, 320, 30, d_LCD_FILL_XOR);
    do {

        // CTOS_LCDGClearCanvas();


        for (Row = 0; Row < 6; Row++) {
            x = 0;
            y = 30;
            if (Row > 0)
                y += Btnwidth * Row;
            else
                y = 30;

            //CTOS_LCDGSetBox(x,y,Btnlenght,Btnwidth,1);  
            //CTOS_LCDGShowPic(x,y,BTN,sizeof(BTN),Btnlenght);

            itemoffset = pagestart + Row;
            CTOS_LCDGSetBox(x + 30, y, 320, 30, 0);
            if (itemoffset >= itemcount)
                CTOS_LCDGTextOut(x + 5, y, "                              ", 0x1218, FALSE);
            else {
                if (Opmenuitem[itemoffset].checked == TRUE) {
                    CTOS_LCDGShowPic(x, y, (BYTE *) & OPTION_CHECKED, sizeof (OPTION_CHECKED), 30);
                    CTOS_LCDGTextOut(x + 30 + 5, y, Opmenuitem[itemoffset].itemname, 0x1218, FALSE);
                } else {
                    CTOS_LCDGShowPic(x, y, (BYTE *) & OPTION_UNCHECKED, sizeof (OPTION_UNCHECKED), 30);
                    CTOS_LCDGTextOut(x + 30 + 5, y, Opmenuitem[itemoffset].itemname, 0x1218, FALSE);
                }

            }
            if (cursor == Row) {
                CTOS_LCDGSetBox(x + 30, y, 320, 30, d_LCD_FILL_XOR);
            }


        }

        CTOS_LCDGTextOut(16, 210 + 8, "UP 向上", d_FONT_8x16, TRUE);
        CTOS_LCDGTextOut(80 + 16, 210 + 8, "DOWN 向下", d_FONT_8x16, TRUE);
        CTOS_LCDGTextOut(160 + 16, 210 + 8, " (OK)選擇 (X)離開", d_FONT_8x16, TRUE);


keyin:

        CTOS_KBDGet(&key);
        switch (key) {

            case d_KBD_UP:
                if (cursor >= 0) {
                    cursor--;
                    if (cursor < 0) {
                        if (pagestart > 0) {
                            cursor = 5;
                            pagestart -= 6;
                        } else
                            cursor = 0;


                    }
                    continue;
                } else {
                    goto keyin;
                }
                break;
            case d_KBD_DOWN:

                if (cursor <= 5) {

                    if ((pagestart + cursor + 1) >= itemcount) {
                        goto keyin;
                    } else {
                        cursor++;
                        if (cursor >= 6) {
                            pagestart += 6;
                            cursor = 0;
                        }
                        continue;
                    }
                } else {
                    goto keyin;
                }
                break;

            case d_KBD_ENTER:
                if (Opmenuitem[pagestart + cursor].checked == TRUE) {
                    if (MustCheck == TRUE) {
                        checkedcount = 0;
                        for (i = 0; i < itemcount; i++) {
                            if (Opmenuitem[i].checked == TRUE) {
                                checkedcount++;
                            }
                        }
                        if (checkedcount > 1) {
                            Opmenuitem[pagestart + cursor].checked = FALSE;

                        }

                    }
                    break;
                } else {
                    if (SingleCheck == TRUE) {
                        for (i = 0; i < itemcount; i++) {
                            Opmenuitem[i].checked = FALSE;
                        }
                        Opmenuitem[pagestart + cursor].checked = TRUE;
                    } else {
                        Opmenuitem[pagestart + cursor].checked = TRUE;
                    }
                }


                break;


            case d_KBD_CANCEL:
                return d_OK;
            default:
                continue;
        }

    } while (1);
}

/* ==========================================================================
 *
 * FUNCTION NAME: SetRTC
 *
 * DESCRIPTION:   Use this function to set the real-time clock's data and time.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */

USHORT ECC_SETRTC() {
    USHORT ret;
    BYTE key, len;
    CTOS_RTC SetRTC;
    BYTE baYear[4 + 1], baMonth[2 + 1], baDay[2 + 1], baHour[2 + 1], baMinute[2 + 1], baSecond[2 + 1];
    int MaxLen;
    STR Title[16] = "時間設定";
    BYTE line[32 + 1];
    BYTE babuff[32 + 1], babuff2[32 + 1];
    BYTE isSet = FALSE;

    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    CTOS_BackLightSet(d_BKLIT_LCD, d_ON); //turn on backlight
    CTOS_LanguageConfig(d_FONT_CHINESE_TAIWAN, d_FONT_16x30, 0, FALSE);
    CTOS_LCDTSelectFontSize(d_FONT_16x30);
    CTOS_LCDTClearDisplay();


    CTOS_LCDTSetReverse(TRUE);
    CTOS_LCDTPrintXY(5, 1, Title);
    CTOS_LCDTSetReverse(FALSE);


    ret = CTOS_RTCGet(&SetRTC);

    sprintf(babuff, "%04d年%02d月%02d日", SetRTC.bYear + 2000, SetRTC.bMonth, SetRTC.bDay);

    sprintf(babuff2, "%02d時%02d分%02d秒", SetRTC.bHour, SetRTC.bMinute, SetRTC.bSecond);

    ret = ShowMessage3line("修改時間", "目前時間", babuff, babuff2, Type_ComformOK);
    if (ret != d_OK) return ret;
    memset(babuff, 0x00, sizeof (babuff));
    MaxLen = 2;
    int year;
    sprintf(line, "年:%d", SetRTC.bYear + 2000);
    ret = ShowInputBox(Title, "請輸入西元年後二碼", babuff, MaxLen, 0, 0);
    if (ret == d_OK) {
        SetRTC.bYear = atoi(babuff);
        isSet = TRUE;
    }

    MaxLen = 2;
    sprintf(line, "月:%d", SetRTC.bMonth);
    ret = ShowInputBox(Title, "請輸入月份", babuff, MaxLen, 0, 0);
    if (ret == d_OK) {
        SetRTC.bMonth = atoi(babuff);
        isSet = TRUE;
    }


    MaxLen = 2;
    sprintf(line, "日:%d", SetRTC.bDay);
    ret = ShowInputBox(Title, "請輸入目前日期", babuff, MaxLen, 0, 0);
    if (ret == d_OK) {
        //   wub_str_2_hex(&babuff, &SetRTC.bDay, 2);
        SetRTC.bDay = atoi(babuff);
        isSet = TRUE;
    }


    MaxLen = 2;
    sprintf(line, "時:%d", SetRTC.bHour);
    ret = ShowInputBox(Title, "請輸入時", babuff, MaxLen, 0, 0);
    if (ret == d_OK) {
        //   wub_str_2_hex(&babuff, &SetRTC.bHour, 2);
        SetRTC.bHour = atoi(babuff);
        isSet = TRUE;
    }


    MaxLen = 2;
    sprintf(line, "月:%d", SetRTC.bMinute);
    ret = ShowInputBox(Title, "請輸入分", babuff, MaxLen, 0, 0);
    if (ret == d_OK) {
        //  wub_str_2_hex(&babuff, &SetRTC.bMinute, 2);
        SetRTC.bMinute = atoi(babuff);
        isSet = TRUE;
    }

    MaxLen = 2;
    sprintf(line, "秒:%d", SetRTC.bSecond);
    ret = ShowInputBox(Title, "請輸入秒", babuff, MaxLen, 0, 0);
    if (ret == d_OK) {
        // wub_str_2_hex(&babuff, &SetRTC.bSecond, 2);
        SetRTC.bSecond = atoi(babuff);
        isSet = TRUE;
    }

    if (isSet) {
        //Set the date and time //
        if (CTOS_RTCSet(&SetRTC) == d_OK) {
            ret = CTOS_RTCGet(&SetRTC);
            sprintf(babuff, "%04d年%02d月%02d日", SetRTC.bYear + 2000, SetRTC.bMonth, SetRTC.bDay);
            sprintf(babuff2, "%02d時%02d分%02d秒", SetRTC.bHour, SetRTC.bMinute, SetRTC.bSecond);

            ShowMessage3line("修改時間", babuff, babuff2, "時間修改成功", Type_ComformAnykey);

        } else {
            ShowMessage2line("修改時間", "", "時間修改失敗", Type_ComformAnykey);
            isSet = FALSE;
        }

    }





    return isSet;
}

USHORT ECC_SETCOMMUNICATION() {

    BYTE babuff[32 + 1];
    memset(babuff, 0x00, sizeof (babuff));

    USHORT ret = ShowInputBox3line("修改通訊主機IP", "目前設定", gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP, "", babuff, 15, INPUT_TYPE_NumberWithRadixPoint, 0);
    if (ret == d_OK) {
        memset(gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP, 0x00, sizeof (gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP));
        memcpy(gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP, babuff, strlen(babuff));
    }
    memset(babuff, 0x00, sizeof (babuff));
    ret = ShowInputBox3line("修改通訊主機PORT", "目前設定", gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT, "", babuff, 5, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        memset(gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT, 0x00, sizeof (gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT));
        memcpy(gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT, babuff, strlen(babuff));
    }

    return 0;
}

USHORT ECC_ShowEthernetConfig() {
    BYTE key, len;
    BYTE buff[64 + 1];
    STR DHCP[64 + 1] = "";
    USHORT ret;
    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    CTOS_BackLightSet(d_BKLIT_LCD, d_ON); //turn on backlight
    CTOS_LanguageConfig(d_FONT_CHINESE_TAIWAN, d_FONT_16x16, 0, FALSE);
    CTOS_LCDTSelectFontSize(d_FONT_12x24);
    CTOS_LCDTClearDisplay();


    CTOS_LCDTSetReverse(TRUE);
    CTOS_LCDTPrintXY(5, 1, "本機網路設定");
    CTOS_LCDTSetReverse(FALSE);

    len = sizeof (buff);

    memset(buff, 0x00, sizeof (buff));

    ret = CTOS_EthernetConfigGet((BYTE) d_ETHERNET_CONFIG_IP, (BYTE *) buff, &len);
    CTOS_LCDTPrintXY(1, 2, "本機IP:");
    CTOS_LCDTPrintXY(6, 2, buff);
    memset(buff, 0x00, sizeof (buff));
    len = sizeof (buff);
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_MASK, buff, &len);
    CTOS_LCDTPrintXY(1, 3, "MASK:");
    CTOS_LCDTPrintXY(6, 3, buff);
    memset(buff, 0x00, sizeof (buff));
    len = sizeof (buff);
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_GATEWAY, buff, &len);
    CTOS_LCDTPrintXY(1, 4, "GATEWAY:");
    CTOS_LCDTPrintXY(9, 4, buff);
    memset(buff, 0x00, sizeof (buff));
    len = sizeof (buff);
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DNSIP, buff, &len);
    CTOS_LCDTPrintXY(1, 5, "DNS:");
    CTOS_LCDTPrintXY(5, 5, buff);
    memset(buff, 0x00, sizeof (buff));
    len = sizeof (buff);
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_MAC, buff, &len);
    CTOS_LCDTPrintXY(1, 6, "MAC:");
    CTOS_LCDTPrintXY(5, 6, buff);
    memset(buff, 0x00, sizeof (buff));
    len = sizeof (buff);
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_VERSION, buff, &len);
    CTOS_LCDTPrintXY(1, 7, "VERSION:");
    CTOS_LCDTPrintXY(9, 7, buff);

    memset(buff, 0x00, sizeof (buff));
    len = sizeof (buff);
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DHCP, buff, &len);
    if (buff[0] == 0x31) {
        sprintf(DHCP, "DHCP:ON");
    } else {
        sprintf(DHCP, "DHCP:OFF");
    }
    CTOS_LCDTPrintXY(1, 8, DHCP);
    CTOS_LCDTPrintXY(1, 9, "欲修改設定請按(OK)");
    CTOS_LCDTPrintXY(1, 10, "其它鍵退出");
    CTOS_KBDGet(&key);
    if (key != d_KBD_ENTER)
        return d_Fail;
    return d_OK;
}

USHORT ECC_SETEthernet() {
    USHORT ret;
    BYTE key, len;
    int line;
    STR IP[64 + 1] = "";
    STR MASK[64 + 1] = "";
    STR GATEWAY[64 + 1] = "";
    STR DNS[64 + 1] = "";
    STR DHCP[64 + 1] = "";
    BYTE buff[64 + 1];
    BYTE buff2[64 + 1];
    int MaxLen = 16 + 1;
    Optionmenu_item MenuItem[2] = {
        { "DHCP自動取得IP", TRUE},
        { "手動設定", TRUE},
    };
    STR Title[64 + 1] = "網路設定";



    CTOS_LCDSelectMode(d_LCD_TEXT_320x240_MODE);
    CTOS_BackLightSet(d_BKLIT_LCD, d_ON); //turn on backlight
    CTOS_LanguageConfig(d_FONT_CHINESE_TAIWAN, d_FONT_16x16, 0, FALSE);
    CTOS_LCDTSelectFontSize(d_FONT_12x24);
    CTOS_LCDTClearDisplay();


    CTOS_LCDTSetReverse(TRUE);
    CTOS_LCDTPrintXY(5, 1, Title);
    CTOS_LCDTSetReverse(FALSE);

    len = sizeof (buff);
    do {
        memset(buff, 0x00, sizeof (buff));

        ret = CTOS_EthernetConfigGet((BYTE) d_ETHERNET_CONFIG_IP, (BYTE *) buff, &len);
        CTOS_LCDTPrintXY(1, 2, "本機IP:");
        CTOS_LCDTPrintXY(6, 2, buff);
        memset(buff, 0x00, sizeof (buff));
        len = sizeof (buff);
        ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_MASK, buff, &len);
        CTOS_LCDTPrintXY(1, 3, "MASK:");
        CTOS_LCDTPrintXY(6, 3, buff);
        memset(buff, 0x00, sizeof (buff));
        len = sizeof (buff);
        ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_GATEWAY, buff, &len);
        CTOS_LCDTPrintXY(1, 4, "GATEWAY:");
        CTOS_LCDTPrintXY(9, 4, buff);
        memset(buff, 0x00, sizeof (buff));
        len = sizeof (buff);
        ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DNSIP, buff, &len);
        CTOS_LCDTPrintXY(1, 5, "DNS:");
        CTOS_LCDTPrintXY(5, 5, buff);
        memset(buff, 0x00, sizeof (buff));
        len = sizeof (buff);
        ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_MAC, buff, &len);
        CTOS_LCDTPrintXY(1, 6, "MAC:");
        CTOS_LCDTPrintXY(5, 6, buff);
        memset(buff, 0x00, sizeof (buff));
        len = sizeof (buff);
        ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_VERSION, buff, &len);
        CTOS_LCDTPrintXY(1, 7, "VERSION:");
        CTOS_LCDTPrintXY(9, 7, buff);


        memset(buff, 0x00, sizeof (buff));
        len = sizeof (buff);
        ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DHCP, buff, &len);
        if (buff[0] == 0x31) {
            sprintf(DHCP, "DHCP:ON");

            MenuItem[0].checked = TRUE;
            MenuItem[1].checked = FALSE;
        } else {
            sprintf(DHCP, "DHCP:OFF");
            MenuItem[1].checked = TRUE;
            MenuItem[0].checked = FALSE;
        }
        CTOS_LCDTPrintXY(1, 8, DHCP);
        CTOS_LCDTPrintXY(1, 9, "欲修改設定請按(OK)");
        CTOS_LCDTPrintXY(1, 10, "其它鍵退出");
        CTOS_KBDGet(&key);
        if (key != d_KBD_ENTER)
            return;




        ret = ECC_ShowCheckListMeun2("IP取得模式", MenuItem, 2, TRUE, TRUE);
        if (MenuItem[0].checked == TRUE) {
            memset(buff, 0x00, sizeof (buff));
            buff[0] = 0x31;
            len = strlen(buff);
            ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_DHCP, buff, len);
            memset(buff, 0x00, sizeof (buff));
            ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DHCP, buff, &len);
            if (buff[0] == 0x31) {
                sprintf(DHCP, "DHCP:ON");
            } else {
                sprintf(DHCP, "DHCP:OFF");
            }

        } else {
            CTOS_LCDTClearDisplay();


            CTOS_LCDTSetReverse(TRUE);
            CTOS_LCDTPrintXY(5, 1, Title);
            CTOS_LCDTSetReverse(FALSE);

            len = sizeof (buff);

            buff[0] = 0x30;
            len = strlen(buff);
            ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_DHCP, buff, len);

            memset(buff, 0x00, sizeof (buff));
            memset(buff2, 0x00, sizeof (buff2));
            len = sizeof (buff);
            ret = CTOS_EthernetConfigGet((BYTE) d_ETHERNET_CONFIG_IP, (BYTE *) buff, &len);
            sprintf(IP, "本機IP:");
            ret = ShowInputBox3line(Title, IP, buff, "請輸入NEW IP", buff2, MaxLen, INPUT_TYPE_NumberWithRadixPoint, 0);
            if (ret == d_OK) {
                len = strlen(buff2);
                ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_IP, buff2, len);
                sprintf(IP, "本機IP:%s", buff2);
            }
            memset(buff, 0x00, sizeof (buff));
            memset(buff2, 0x00, sizeof (buff2));
            len = sizeof (buff);
            ret = CTOS_EthernetConfigGet((BYTE) d_ETHERNET_CONFIG_MASK, (BYTE *) buff, &len);
            sprintf(MASK, "子網路遮罩:");
            ret = ShowInputBox3line(Title, MASK, buff, "請輸入NEW MASK", buff2, MaxLen, INPUT_TYPE_NumberWithRadixPoint, 0);
            if (ret == d_OK) {
                len = strlen(buff2);
                ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_MASK, buff2, len);
                sprintf(MASK, "子網路遮罩:%s", buff2);
            }
            memset(buff, 0x00, sizeof (buff));
            memset(buff2, 0x00, sizeof (buff2));
            len = sizeof (buff);
            ret = CTOS_EthernetConfigGet((BYTE) d_ETHERNET_CONFIG_GATEWAY, (BYTE *) buff, &len);
            sprintf(GATEWAY, "預設閘道:");
            ret = ShowInputBox3line(Title, GATEWAY, buff, "請輸入NEW GATEWAY", buff2, MaxLen, INPUT_TYPE_NumberWithRadixPoint, 0);
            if (ret == d_OK) {
                len = strlen(buff2);
                ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_GATEWAY, buff2, len);
                sprintf(GATEWAY, "預設閘道:%s", buff2);
            }
            memset(buff, 0x00, sizeof (buff));
            memset(buff2, 0x00, sizeof (buff2));
            len = sizeof (buff);
            ret = CTOS_EthernetConfigGet((BYTE) d_ETHERNET_CONFIG_DNSIP, (BYTE *) buff, &len);
            sprintf(DNS, "DNS:");
            ret = ShowInputBox3line(Title, DNS, buff, "請輸入NEW DNS", buff2, MaxLen, INPUT_TYPE_NumberWithRadixPoint, 0);
            if (ret == d_OK) {
                len = strlen(buff2);
                ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_DNSIP, buff2, len);
                sprintf(DNS, "DNS:%s", buff2);
            }
        }
        STR * Line[] = {IP, MASK, GATEWAY, DNS, DHCP, "", "", "確定修改請按(OK)", "放棄修改請按(X)"};
        BYTE key = Displaymuiltlie(d_LCD_FONT_12x24, Title, Line);
        if (key == d_KBD_ENTER) {
            ret = CTOS_EthernetConfigSet(d_ETHERNET_CONFIG_UPDATE_EXIT, buff, 0);
            if (ret != d_OK) {
                CTOS_LCDTPrintXY(1, 8, "修改失敗");
                return d_FAIL;
            }
            return d_OK;
        } else {
            return d_ERR_CANCELBYUSER;
        }

    } while (1);


    return ret;
}

USHORT MainMenu() {

    int ret;
    do {
        //   ret= ECC_ShowListMeun("功能選單",MMI,TOTAL_InitMainMenuItem);
        ret = ECC_ShowMenu("功能選單", MMI, TOTAL_InitMainMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);

}

USHORT TXMenu() {
    int ret;

    if (ecrObj.ecrOn)
        ecrObj.menuFunctionSwitch(&ecrObj);
    else
        GetFunctionSetting();
    do {

        ret = ECC_ShowMenu("", TMI, TOTAL_InitTXMenuItem);
        if (ret == d_ERR_CANCELBYUSER) {
            //printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
            return d_OK;
        }
    } while (1);
}

USHORT INFOMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("資訊", IQI, TOTAL_InitINFOMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return d_OK;
    } while (1);
}

USHORT SYSTEMMenu() {
    int ret;
    do {
        // ret= ECC_ShowListMeun("設定",SMI,TOTAL_InitSYSTEMMenuItem);
        // ret= ShowConfigInfo();
        //if(ret==d_ERR_CANCELBYUSER)
        return;
    } while (1);
}

USHORT ReaderMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("讀卡機", (menu_item *) & InitReaderMenuItem, TOTAL_InitReaderMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);
}

USHORT BuiltinReaderMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("內建式讀卡機", (menu_item *) & InitBuiltinReaderMenuItem, TOTAL_InitBuiltinReaderMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);
}

USHORT SETTINGMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("設定", STI, TOTAL_InitSETTINGMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);
}

USHORT ManufacturerMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("廠商設定", MTI, TOTAL_InitManufacturerMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);
}

USHORT TXSETTINGMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("交易功能設定", TSI, TOTAL_InitTXSETTINGMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);
}

USHORT SwitchMainfunction(void) {
    int ret;
    ret = ECC_ShowCheckListMeun("功能設定選單", MMI, TOTAL_InitMainMenuItem, FALSE, FALSE);
}

USHORT DebugMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("DEBUG MODE", (menu_item *) & InitDebugMenuItem, TOTAL_InitDebugMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);
}

USHORT DebugOptionMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("DEBUG OPTION", (menu_item *) & InitDebugModeItem, TOTAL_InitDebugModeItem);
        if (ret == d_ERR_CANCELBYUSER)
            return 0;
    } while (1);

}

USHORT DownloadMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("下載參數", (menu_item *) & InitDOWNLOADPARAMenuItem, TOTAL_InitDOWNLOADPARAMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);
}

USHORT NETSETTINGMenu() {
    int ret;
    do {
        ret = ECC_ShowListMeun("網路設定", (menu_item *) & InitNETSETTINGMenuItem, TOTAL_InitNETSETTINGMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);
}

USHORT PrintBarcode() {
    BYTE Content[32 + 1];
    USHORT ret = ShowInputBox("code 128 測試", "請輸條碼", Content, 32, INPUT_TYPE_Number, 0);

    ret = CTOS_PrinterCode128Barcode(0, 0, Content, 32, 2, 3, TRUE);
}

USHORT SwitchSettingFunction() {
    BYTE buff[10 + 1];
    memset(buff, 0x00, sizeof (buff));
    int limit = 10;
    /*  
     int ret= ShowInputBox("開啟設定功能","請輸入密碼",  buff,limit,INPUT_TYPE_Number,0);
     if(strcmp(buff,"70765909")!=0){
         ShowMessage("開啟設定功能","密碼錯誤",Type_ComformAnykey);
         return d_Fail;
     }*/
    SETTINGMenu();
    return d_OK;
}

USHORT SwitchDebugFunction() {
    BYTE buff[10 + 1];
    memset(buff, 0x00, sizeof (buff));
    int limit = 10;
    /*  
     int ret= ShowInputBox("DEBUG","請輸入密碼",  buff,limit,INPUT_TYPE_Number,0);
     if(strcmp(buff,"70765909")!=0){
         ShowMessage("開啟設定功能","密碼錯誤",Type_ComformAnykey);
         return d_Fail;
     }*/
    DebugMenu();
    return d_OK;
}

USHORT OptionSwitch(STR * OptionName, BYTE *Option) {

    Optionmenu_item MenuItem[2] = {
        { "開啟", FALSE},
        { "關閉", FALSE}
    };

    if (*Option == 0x31) {
        MenuItem[0].checked = TRUE;
        MenuItem[1].checked = FALSE;
    } else {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = TRUE;
    }
    USHORT ret = ECC_ShowCheckListMeun2(OptionName, MenuItem, 2, TRUE, TRUE);
    if (MenuItem[0].checked == TRUE) {
        sprintf(Option, "1");
    } else if (MenuItem[1].checked = TRUE) {
        sprintf(Option, "0");
    }
    return d_OK;
}

USHORT DebugModeSet_Print() {

    USHORT ret = OptionSwitch("PRINT", (BYTE *) & gConfig.sDEBUG.PRINT.ENABLE[0]);

    // ret= Config_SetData();  
    // ret=SetDEBUGInfo();
    ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "PRINT", "ENABLE", gConfig.sDEBUG.PRINT.ENABLE);
    return 0;
}

USHORT DebugModeSet_FTP() {

    USHORT ret = OptionSwitch("FTP", (BYTE *) & gConfig.sDEBUG.FTP.ENABLE[0]);

    // ret= Config_SetData();  
    //ret=SetDEBUGInfo();
    ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "FTP", "ENABLE", gConfig.sDEBUG.FTP.ENABLE);
    return 0;
}

USHORT DebugModeSet_SD() {

    USHORT ret = OptionSwitch("SD", (BYTE *) & gConfig.sDEBUG.SD.ENABLE[0]);

    // ret= Config_SetData();  
    //ret=SetDEBUGInfo();
    ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "SD", "ENABLE", gConfig.sDEBUG.SD.ENABLE);
    return 0;
}

USHORT SETOPERATIONMODEFunction() {
    int opmode = atoi(gConfig.TX.OPERATIONMODE);
    Optionmenu_item MenuItem[4] = {
        { "手動輸入交易金額", TRUE},
        { "自動扣款-固定票價", TRUE},
        { "自動扣款-依票種判別", TRUE},
        { "手動扣款-接條碼掃描器", TRUE},
    };

    if (strcmp(gConfig.TX.OPERATIONMODE, "MANUAL") == 0) {
        MenuItem[0].checked = TRUE;
        MenuItem[1].checked = FALSE;
        MenuItem[2].checked = FALSE;
        MenuItem[3].checked = FALSE;
    } else if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0) {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = TRUE;
        MenuItem[2].checked = FALSE;
        MenuItem[3].checked = FALSE;
    } else if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = FALSE;
        MenuItem[2].checked = TRUE;
        MenuItem[3].checked = FALSE;
    } else if (strcmp(gConfig.TX.OPERATIONMODE, "BARCODESCANNER") == 0) {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = FALSE;
        MenuItem[2].checked = FALSE;
        MenuItem[3].checked = TRUE;
    }

    USHORT ret = ECC_ShowCheckListMeun2("交易模式設定", MenuItem, 4, TRUE, TRUE);
    if (MenuItem[0].checked == TRUE) {
        memset(gConfig.TX.OPERATIONMODE, 0x00, sizeof (gConfig.TX.OPERATIONMODE));
        sprintf(gConfig.TX.OPERATIONMODE, "MANUAL");
    } else if (MenuItem[1].checked == TRUE) {
        memset(gConfig.TX.OPERATIONMODE, 0x00, sizeof (gConfig.TX.OPERATIONMODE));
        sprintf(gConfig.TX.OPERATIONMODE, "AUTO_FIX");
    } else if (MenuItem[2].checked == TRUE) {
        memset(gConfig.TX.OPERATIONMODE, 0x00, sizeof (gConfig.TX.OPERATIONMODE));
        sprintf(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE");
    } else if (MenuItem[3].checked == TRUE) {
        memset(gConfig.TX.OPERATIONMODE, 0x00, sizeof (gConfig.TX.OPERATIONMODE));
        sprintf(gConfig.TX.OPERATIONMODE, "BARCODESCANNER");
    }

    // ret= Config_SetData();  
    ECC_SetXMLTag(TXINFO_Path, "TX", "OPERATIONMODE", gConfig.TX.OPERATIONMODE);
    //  SetTXInfo();
    // InitConfigData();
    return ret;
}

USHORT SelectAuto_FixDeductAMT() {
    Optionmenu_item MenuItem[10];
    BYTE i = 0;
    //   USHORT SelectAmtOption=atoi(gConfig.TX.AMTTABLE[0].AREACODE);

    for (i = 0; i < 10; i++) {
        sprintf(MenuItem[i].itemname, "[%d] %d", i + 1, gConfig.TX.AMTTABLE[0].AMT[i]);
        if (gConfig.TX.AMTTABLE[0].AREACODE == i)
            MenuItem[i].checked = TRUE;
    }



    USHORT ret = ECC_ShowCheckListMeun2("自動扣款金額", MenuItem, 10, TRUE, TRUE);
    for (i = 0; i < 10; i++) {
        if (MenuItem[i].checked == TRUE) {//modify by bruce
            gConfig.TX.AMTTABLE[0].AREACODE = i;

            // sprintf(gConfig.TX.AMTTABLE[0].AREACODE,"%d",i);
        }
    }
    // ret= Config_SetData();  
    // ret=SetTXInfo();
    //   InitConfigData();
    SetAUTOFIXMODE_SelectAMT(gConfig.TX.AMTTABLE[0].AREACODE);
    return ret;
}

USHORT SelectAMTTABLE() {
    Optionmenu_item MenuItem[20];
    BYTE i = 0;
    //   USHORT SelectAmtOption=atoi(gConfig.TX.AMTTABLE[0].AREACODE);

    for (i = 0; i < 15; i++) {        
        sprintf(MenuItem[i].itemname, "[%d] %s", i + 1, gConfig.TX.AMTTABLE[i].NAME);
        if (gSelectTable == i)
            MenuItem[i].checked = TRUE;
    }



    USHORT ret = ECC_ShowCheckListMeun2("請選擇票價表", MenuItem, 15, TRUE, TRUE);
    for (i = 0; i < 15; i++) {
        if (MenuItem[i].checked == TRUE) {//modify by bruce
            gConfig.TX.AMTTABLE[0].AREACODE = i;


            gSelectTable = i;
            // sprintf(gConfig.TX.AMTTABLE[0].AREACODE,"%d",i);
        }
    }


    // ret= Config_SetData();  
    // ret=SetTXInfo();
    //   InitConfigData();
    // SetAUTOFIXMODE_SelectAMT( gConfig.TX.AMTTABLE[0].AREACODE);
    return ret;
}

USHORT SETReaderPortFunction() {


    Optionmenu_item MenuItem[3] = {
        { "COM1", TRUE},
        { "COM2", TRUE},
        { "Builtin", TRUE}
    };

    if (strcmp(gConfig.DEVICE.READER.bPORT, "COM1") == 0) {
        MenuItem[0].checked = TRUE;
        MenuItem[1].checked = FALSE;
        MenuItem[2].checked = FALSE;
    } else if (strcmp(gConfig.DEVICE.READER.bPORT, "COM2") == 0) {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = TRUE;
        MenuItem[2].checked = FALSE;
    } else if (strcmp(gConfig.DEVICE.READER.bPORT, "Builtin") == 0) {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = FALSE;
        MenuItem[2].checked = TRUE;
    }

    USHORT ret = ECC_ShowCheckListMeun2("讀卡機連接埠", (Optionmenu_item*) & MenuItem, 3, TRUE, TRUE);
    if (MenuItem[0].checked == TRUE) {
        sprintf(gConfig.DEVICE.READER.bPORT, "COM1");
    } else if (MenuItem[1].checked == TRUE) {
        sprintf(gConfig.DEVICE.READER.bPORT, "COM2");
    } else if (MenuItem[2].checked == TRUE) {
        sprintf(gConfig.DEVICE.READER.bPORT, "Builtin");
    }
    ECC_SetXMLTag2(DEVICEINFO_Path, "DEVICE", "READER", "PORT", gConfig.DEVICE.READER.bPORT);
    // ret= Config_SetData();  
    //   ret=SetDEVICEInfo();
    //  InitConfigData();
    return ret;
}

USHORT SETAUTODEDUCTAMT() {

    BYTE babuff[32 + 1];
    memset(babuff, 0x00, sizeof (babuff));
    BYTE tmp[4 + 1];
    //modify by bruce 

    if ((strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") != 0) && (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") != 0)) {
        ShowMessage("非連續扣款模式，", "無需操作此設定功能", Type_ComformOK);
        return d_OK;
    }

    USHORT ret;
    ret = CheckSignOnPassword();
    if (ret != d_OK) {
        ECC_CheckAPResponseCode(ret);
        return ret;
    }

    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[0]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價一", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = ShowInputBox3line("普通票票價", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        //  memset(gConfig.TX.AMTTABLE[0].AMT[0],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[0]));
        //modify by bruce 

        gConfig.TX.AMTTABLE[0].AMT[0] = atoi(babuff);
        SetAMTTABLE(0, 0, gConfig.TX.AMTTABLE[0].AMT[0]);
        //  sprintf(gConfig.TX.AMTTABLE[0].AMT[0],"%s",babuff);
        // memcpy(gConfig.TX.OPMODE.DEDUCTAMT0,babuff,strlen(babuff));
        // Config_SetData();
        ret = ShowMessage("設定完成!", "是否繼續設定其它票價", Type_ComformOK);
        if (ret != d_OK) return ret;
    }

    //modify by bruce 
    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[1]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價二", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = ShowInputBox3line("敬老(一)票票價", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        // memset(gConfig.TX.AMTTABLE[0].AMT[1],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[1]));

        //modify by bruce 
        gConfig.TX.AMTTABLE[0].AMT[1] = atoi(babuff);
        SetAMTTABLE(0, 1, gConfig.TX.AMTTABLE[0].AMT[1]);
        // memcpy(gConfig.TX.AMTTABLE[0].AMT[1],babuff,strlen(babuff));
        ret = ShowMessage("設定完成!", "是否繼續設定其它票價", Type_ComformOK);
        if (ret != d_OK) return ret;
    }

    //modify by bruce 
    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[2]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價三", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = ShowInputBox3line("敬老(二)票票價", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        // memset(gConfig.TX.AMTTABLE[0].AMT[2],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[2]));
        //modify by bruce 
        gConfig.TX.AMTTABLE[0].AMT[2] = atoi(babuff);
        SetAMTTABLE(0, 2, gConfig.TX.AMTTABLE[0].AMT[2]);
        ret = ShowMessage("設定完成!", "是否繼續設定其它票價", Type_ComformOK);
        if (ret != d_OK) return ret; //  memcpy(gConfig.TX.AMTTABLE[0].AMT[2],babuff,strlen(babuff));

    }

    //modify by bruce 
    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[3]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價四", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = ShowInputBox3line("愛心票票價", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        //   memset(gConfig.TX.AMTTABLE[0].AMT[3],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[3]));
        //modify by bruce 
        gConfig.TX.AMTTABLE[0].AMT[3] = atoi(babuff);
        SetAMTTABLE(0, 3, gConfig.TX.AMTTABLE[0].AMT[3]);
        //  memcpy(gConfig.TX.AMTTABLE[0].AMT[3],babuff,strlen(babuff));
        ret = ShowMessage("設定完成!", "是否繼續設定其它票價", Type_ComformOK);
        if (ret != d_OK) return ret;
    }

    //modify by bruce 
    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[4]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價五", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = ShowInputBox3line("愛心陪伴票票價", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        //   memset(gConfig.TX.AMTTABLE[0].AMT[4],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[4]));
        //modify by bruce 
        gConfig.TX.AMTTABLE[0].AMT[4] = atoi(babuff);
        SetAMTTABLE(0, 4, gConfig.TX.AMTTABLE[0].AMT[4]);
        //  memcpy(gConfig.TX.AMTTABLE[0].AMT[4],babuff,strlen(babuff));
        ret = ShowMessage("設定完成!", "是否繼續設定其它票價", Type_ComformOK);
        if (ret != d_OK) return ret;
    }

    //modify by bruce 
    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[5]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價六", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = ShowInputBox3line("學生票價", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        //    memset(gConfig.TX.AMTTABLE[0].AMT[5],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[5]));
        //modify by bruce 
        gConfig.TX.AMTTABLE[0].AMT[5] = atoi(babuff);
        SetAMTTABLE(0, 5, gConfig.TX.AMTTABLE[0].AMT[5]);
        // memcpy(gConfig.TX.AMTTABLE[0].AMT[5],babuff,strlen(babuff));
        ret = ShowMessage("設定完成!", "是否繼續設定其它票價", Type_ComformOK);
        if (ret != d_OK) return ret;
    }

    //modify by bruce 
    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[6]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價七", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = d_Fail;
    if (ret == d_OK) {
        //    memset(gConfig.TX.AMTTABLE[0].AMT[6],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[6]));
        //modify by bruce 
        gConfig.TX.AMTTABLE[0].AMT[6] = atoi(babuff);
        SetAMTTABLE(0, 6, gConfig.TX.AMTTABLE[0].AMT[6]);
        //memcpy(gConfig.TX.AMTTABLE[0].AMT[6],babuff,strlen(babuff));
        ret = ShowMessage("設定完成!", "是否繼續設定其它票價", Type_ComformOK);
        if (ret != d_OK) return ret;
    }


    //modify by bruce 
    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[7]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價八", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = ShowInputBox3line("優待票票價", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    if (ret == d_OK) {
        //    memset(gConfig.TX.AMTTABLE[0].AMT[7],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[7]));
        //modify by bruce 
        gConfig.TX.AMTTABLE[0].AMT[7] = atoi(babuff);
        SetAMTTABLE(0, 7, gConfig.TX.AMTTABLE[0].AMT[7]);
        // memcpy(gConfig.TX.AMTTABLE[0].AMT[7],babuff,strlen(babuff));
        ret = ShowMessage("設定完成!", "是否繼續設定其它票價", Type_ComformOK);
        if (ret != d_OK) return ret;
    }


    //modify by bruce 
    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[8]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價九 ", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = d_Fail;

    if (ret == d_OK) {
        //    memset(gConfig.TX.AMTTABLE[0].AMT[8],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[8]));
        //modify by bruce 
        gConfig.TX.AMTTABLE[0].AMT[8] = atoi(babuff);
        SetAMTTABLE(0, 8, gConfig.TX.AMTTABLE[0].AMT[8]);
        // memcpy(gConfig.TX.AMTTABLE[0].AMT[8],babuff,strlen(babuff));
        ret = ShowMessage("設定完成!", "是否繼續設定其它票價", Type_ComformOK);
        if (ret != d_OK) return ret;
    }

    //modify by bruce 
    sprintf(tmp, "%d", gConfig.TX.AMTTABLE[0].AMT[9]);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0)
        ret = ShowInputBox3line("設定自動扣款票價九 ", "目前設定", tmp, "", babuff, 5, INPUT_TYPE_Number, 0);
    else
        ret = d_Fail;
    if (ret == d_OK) {
        //    memset(gConfig.TX.AMTTABLE[0].AMT[9],0x00,sizeof(gConfig.TX.AMTTABLE[0].AMT[9]));
        //modify by bruce 
        gConfig.TX.AMTTABLE[0].AMT[9] = atoi(babuff);
        SetAMTTABLE(0, 9, gConfig.TX.AMTTABLE[0].AMT[9]);
        // memcpy(gConfig.TX.AMTTABLE[0].AMT[9],babuff,strlen(babuff));

    }
    return ret;
}

USHORT SETDEDUCTAMT() {
    USHORT ret = SETAUTODEDUCTAMT();
    if (ret == d_OK) {
        // ret= Config_SetData();  
        ret = SetTXInfo();
    }
    return ret;
}

USHORT SETConnectMode() {



    Optionmenu_item MenuItem[4] = {
        { "正式套", TRUE},
        { "測試套", TRUE},
        { "開發套", TRUE}
    };

    if (strcmp(gConfig.ETHERNET.CONNECTHOST, "PRODUCTION") == 0) {
        MenuItem[0].checked = TRUE;
        MenuItem[1].checked = FALSE;
        MenuItem[2].checked = FALSE;
    } else if (strcmp(gConfig.ETHERNET.CONNECTHOST, "TESTING") == 0) {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = TRUE;
        MenuItem[2].checked = FALSE;
    } else if (strcmp(gConfig.ETHERNET.CONNECTHOST, "DEVELOP") == 0) {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = FALSE;
        MenuItem[2].checked = TRUE;
    }

    USHORT ret = ECC_ShowCheckListMeun2("連線主機", (Optionmenu_item *) & MenuItem, 3, TRUE, TRUE);
    memset(gConfig.ETHERNET.CONNECTHOST, 0x00, sizeof (gConfig.ETHERNET.CONNECTHOST));
    if (MenuItem[0].checked == TRUE) {
        sprintf(gConfig.ETHERNET.CONNECTHOST, "PRODUCTION");
    } else if (MenuItem[1].checked == TRUE) {
        sprintf(gConfig.ETHERNET.CONNECTHOST, "TESTING");
    } else if (MenuItem[2].checked == TRUE) {
        sprintf(gConfig.ETHERNET.CONNECTHOST, "DEVELOP");
    }

    // ret= Config_SetData();  
    ECC_SetXMLTag(ETHERNETINFO_Path, "ETHERNET", "CONNECTHOST", gConfig.ETHERNET.CONNECTHOST);
    //  ret=SetETHERNETInfo();
    //  InitConfigData();
    return ret;
}

USHORT ECC_SETEtherneCHANNEL() {
    Optionmenu_item MenuItem[2] = {
        { "ETHERNET", TRUE},
        { "GPRS", TRUE},
    };

    if (strcmp(gConfig.ETHERNET.EthernetCHANNEL, "ETHERNET") == 0) {
        MenuItem[0].checked = TRUE;
        MenuItem[1].checked = FALSE;
    } else if (strcmp(gConfig.ETHERNET.EthernetCHANNEL, "GPRS") == 0) {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = TRUE;
    }

    USHORT ret = ECC_ShowCheckListMeun2("網路連線方式", (Optionmenu_item *) & MenuItem, 2, TRUE, TRUE);
    memset(gConfig.ETHERNET.EthernetCHANNEL, 0x00, sizeof (gConfig.ETHERNET.EthernetCHANNEL));
    if (MenuItem[0].checked == TRUE) {
        sprintf(gConfig.ETHERNET.EthernetCHANNEL, "ETHERNET");
    } else if (MenuItem[1].checked == TRUE) {
        sprintf(gConfig.ETHERNET.EthernetCHANNEL, "GPRS");
    }
    ECC_SetXMLTag(ETHERNETINFO_Path, "ETHERNET", "EthernetCHANNEL", gConfig.ETHERNET.EthernetCHANNEL);
    ETH_REBOOT();
    // ret= Config_SetData();  
    // ret=SetETHERNETInfo();
    //  InitConfigData();
    return ret;
}

USHORT SETNetWorkMode() {

    Optionmenu_item MenuItem[2] = {
        { "INTERNET", TRUE},
        { "VPN", TRUE},
    };

    if (strcmp(gConfig.ETHERNET.NETWORKMODE, "INTERNET") == 0) {
        MenuItem[0].checked = TRUE;
        MenuItem[1].checked = FALSE;
    } else if (strcmp(gConfig.ETHERNET.NETWORKMODE, "VPN") == 0) {
        MenuItem[0].checked = FALSE;
        MenuItem[1].checked = TRUE;
    }

    USHORT ret = ECC_ShowCheckListMeun2("網路模式", (Optionmenu_item *) & MenuItem, 2, TRUE, TRUE);
    memset(gConfig.ETHERNET.NETWORKMODE, 0x00, sizeof (gConfig.ETHERNET.NETWORKMODE));
    if (MenuItem[0].checked == TRUE) {
        sprintf(gConfig.ETHERNET.NETWORKMODE, "INTERNET");
    } else if (MenuItem[1].checked == TRUE) {
        sprintf(gConfig.ETHERNET.NETWORKMODE, "VPN");
    }
    ECC_SetXMLTag(ETHERNETINFO_Path, "ETHERNET", "NETWORKMODE", gConfig.ETHERNET.NETWORKMODE);
    // ret= Config_SetData();  
    // ret=SetETHERNETInfo();
    //  InitConfigData();
    return ret;
}

USHORT ECC_SETFTPDEBUG() {
    BYTE buff[15 + 1];
    memset(buff, 0x00, sizeof (buff));
    USHORT ret = ShowInputBox3line("設定DEBUG FTP IP ", "", gConfig.sDEBUG.FTP.IP, "", buff, 15, INPUT_TYPE_NumberWithRadixPoint, 0);
    if (ret == d_OK) {
        memset(gConfig.sDEBUG.FTP.IP, 0x00, sizeof (gConfig.sDEBUG.FTP.IP));
        memcpy(gConfig.sDEBUG.FTP.IP, buff, strlen(buff));
        ECC_SetXMLTag2(DEBUGINFO_Path, "DEBUG", "FTP", "IP", gConfig.sDEBUG.FTP.IP);
    }/*
    memset(buff,0x00,sizeof(buff));
     ret=ShowInputBox3line("設定DEBUG FTP ID ","",gConfig.sDEBUG.FTP.ID,"",buff,15,INPUT_TYPE_Number,0);
   if(ret==d_OK){
       memset(gConfig.sDEBUG.FTP.ID,0x00,sizeof(gConfig.sDEBUG.FTP.ID));
       memcpy(gConfig.sDEBUG.FTP.ID,buff,strlen(buff));
   }
       memset(buff,0x00,sizeof(buff));
   ret=ShowInputBox3line("設定DEBUG FTP PASSWORD ","",gConfig.sDEBUG.FTP.PASSWORD,"",buff,15,INPUT_TYPE_Number,0);
   if(ret==d_OK){
       memset(gConfig.sDEBUG.FTP.PASSWORD,0x00,sizeof(gConfig.sDEBUG.FTP.PASSWORD));
       memcpy(gConfig.sDEBUG.FTP.PASSWORD,buff,strlen(buff));
   }*/
    // ret= Config_SetData();  
    // ret=SetDEBUGInfo();
    return 0;
}

USHORT RESETTXFunctionpPassword() {
    USHORT ret = ShowMessage("重設交易密碼", "請確認是否重設交易密碼", Type_ComformOK);
    if (ret == d_OK) {
        ret = SetFunctionpPassword("ADDVALUE", "0000");
        if (ret != d_OK) return ret;
        ret = SetFunctionpPassword("DEDUCT", "0000");
        if (ret != d_OK) return ret;
        ret = SetFunctionpPassword("CANCELTXN", "0000");
        if (ret != d_OK) return ret;
        ret = SetFunctionpPassword("RETURN", "0000");
        if (ret != d_OK) return ret;
        ret = SetFunctionpPassword("SETTLE", "0000");
        if (ret != d_OK) return ret;
        ShowMessage("重設交易密碼", "交易密碼已重設!!", Type_ComformOK);
    }
    return ret;
}

USHORT ChangeTXFunctionpPassword(BYTE * TXNAME) {
    BYTE buff1[10 + 1];
    BYTE buff2[10 + 1];

    memset(buff1, 0x00, sizeof (buff1));
    BOOL ret = CheckFunctionpPasswordflag(TXNAME);
    if (ret != TRUE) {
        ShowMessage("交易密碼功能未開啟", "不需更換密碼", Type_ComformOK);
        return ret;
    }

    ret = ShowInputBox("交易密碼變更", "請輸入原交易密碼", buff1, 10, INPUT_TYPE_Number, '*');
    if (ret != d_OK) {
        ShowMessage("使用者取消操作", "", Type_ComformOK);
    } else {
        ret = CheckFunctionpPassword(TXNAME, buff1);
        if (ret != TRUE) {
            MessageBox("交易密碼變更", "", "密碼錯誤", "請確認!!", "", d_MB_CHECK);

        } else {
            memset(buff1, 0x00, sizeof (buff1));
            ret = ShowInputBox("", "請輸入新交易密碼", buff1, 10, INPUT_TYPE_Number, '*');
            memset(buff2, 0x00, sizeof (buff2));
            ret = ShowInputBox("", "請再輸入新交易密碼", buff2, 10, INPUT_TYPE_Number, '*');
            if (strcmp(buff1, buff2) == 0) {
                ret = SetFunctionpPassword(TXNAME, buff1);
                if (ret == d_OK) {
                    ConfigFunction_GetData();
                    MessageBox("交易密碼變更", "", "密碼已完成修改", "請使用新密碼進行操作!!", "", d_MB_CHECK);

                } else {
                    MessageBox("交易密碼變更", "", "密碼修改失敗!!", "", "", d_MB_CHECK);

                }
            } else {
                MessageBox("交易密碼變更", "密碼輸入錯誤", "請確認兩次密碼是否相同", "", "", d_MB_CHECK);
            }
        }
    }

    return ret;
}

USHORT SetADDVALUEFunctionpPassword() {
    USHORT ret = ChangeTXFunctionpPassword("ADDVALUE");
    return ret;
}

USHORT SetDEDUCTFunctionpPassword() {
    USHORT ret = ChangeTXFunctionpPassword("DEDUCT");
    return ret;
}

USHORT SetRETURNFunctionpPassword() {
    USHORT ret = ChangeTXFunctionpPassword("RETURN");
    return ret;
}

USHORT SetCANCELTXNFunctionpPassword() {
    USHORT ret = ChangeTXFunctionpPassword("CANCELTXN");
    return ret;
}

USHORT SetSETTLENFunctionpPassword() {
    USHORT ret = ChangeTXFunctionpPassword("SETTLE");
    return ret;
}

USHORT SETTxFunctionPassword() {


    int ret;
    do {
        ret = ECC_ShowListMeun("交易功能密碼設定", InitTXFunctionSetMenuItem, TOTAL_InitTXFunctionSetMenuItem);
        if (ret == d_ERR_CANCELBYUSER)
            return;
    } while (1);
    return ret;
}

/*
 for 讀卡機錄碼使用
 * 選擇使用連接埠
 */
USHORT SetReaderCommandPortFunction() {


    Optionmenu_item MenuItem[3] = {
        { "COM1", TRUE},
        { "USB", TRUE}
    };
    MenuItem[0].checked = TRUE;
    MenuItem[1].checked = FALSE;

    USHORT ret = ECC_ShowCheckListMeun2("讀卡機連接埠", MenuItem, 2, TRUE, TRUE);
    if (MenuItem[0].checked == TRUE) {
        return 1;
    } else if (MenuItem[1].checked = TRUE) {
        return 2;
    }

    return ret;
}
