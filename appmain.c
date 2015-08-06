/** 
 **	A Template for developing new terminal application
 **/
#define  _TXMAIN_
#include "ECCAPP.h"
#include <CTOS_CLAPI.h>
#include <pthread.h>
#include <signal.h>
#define d_BUFF_SIZE 32	      //Buffer Size
BYTE babuff[d_BUFF_SIZE];


/* ==================================================================                                    
 * FUNCTION NAME: FileRead                                                                              
 * DESCRIPTION: Read data from the opened file 
 * RETURN:      d_USER_CANCEL --> Cancel to Read the file
 *              d_FILE_NO_FILES --> No any files by the same application
 *              d_FS_FILE_NOT_FOUND --> User select wrong file item
 *              ret --> Return other messages                                                                
 * NOTES:       none.                                                                             
 * ================================================================ */

/*
 ULONG ulHandle , ulbuffLen;
 BYTE key;
 USHORT ret;
 USHORT usTotal;
 BYTE babuff[d_BUFF_SIZE];
 BYTE baFileBuff[d_BUFF_SIZE];*/


void checkEccappToEccapp2(void) {

    ULONG size = 0;
    USHORT ret = 0;
    BYTE filename[] = "bkDeviceInfo.txt";
    ULONG pulFileHandle = 0;
    ret = CTOS_FileGetSize(filename, &size);

    if (ret != d_OK) {
        printf("[%s,%d]\n CTOS_FileGetSize fail:ret=%d", __FUNCTION__, __LINE__, ret);
        return;
    }
    printf("[%s,%d]got file, size=%lu\n", __FUNCTION__, __LINE__, size);

    

    //copy ECCAPP origSetting
    ret = CTOS_FileOpenAttrib(filename, d_STORAGE_FLASH, &pulFileHandle, d_FA_PUBLIC);
    if (ret != d_OK) printf("[%s,%d]\n CTOS_FileOpenAttrib fail:ret=%d", __FUNCTION__, __LINE__, ret);
    else printf("[%s,%d] CTOS_FileOpenAttrib OK\n", __FUNCTION__, __LINE__);

    ret = CTOS_FileSeek(pulFileHandle, 0, d_SEEK_FROM_BEGINNING);
    if (ret != d_OK) printf("[%s,%d]\n CTOS_FileSeek fail:ret=%d", __FUNCTION__, __LINE__, ret);
    else printf("[%s,%d] CTOS_FileSeek OK\n", __FUNCTION__, __LINE__);

    ULONG expLen = 8 + 1 + 10 + 1 + 4 + 1 + 1 + 1 + 1; //00010001,0000100001,5909,1,0
    ULONG len = expLen;
    BYTE data[expLen];
    ret = CTOS_FileRead(pulFileHandle, data, &len);
    if (ret != d_OK || len != expLen) {
        printf("[%s,%d]\n CTOS_FileRead fail:ret=%d or len=%lu not the same expLen=%lu", __FUNCTION__, __LINE__, ret, len, expLen);
        return;
    } else printf("[%s,%d] CTOS_FileRead OK\n", __FUNCTION__, __LINE__);
    if (data[8] != ',' || data[19] != ',' || data[24] != ',') {
        printf("[%s,%d] index 8,9,24,26 mube be ','\n", __FUNCTION__, __LINE__);
    }

    printf("[%s,%d]read data:%s \n", __FUNCTION__, __LINE__, data);

    //SPID
    memcpy(gConfig.MERCHANT.MERCHANTID, data, 8);
    ECC_SetXMLTag(MERCHANTINFO_Path, "MERCHANT", "MERCHANTID", gConfig.MERCHANT.MERCHANTID);
    printf("[%s,%d] now SPID=%s\n", __FUNCTION__, __LINE__, gConfig.MERCHANT.MERCHANTID);
    //TMLocationID
    memcpy(gConfig.MERCHANT.STCODE, data + 9, 10);
    ECC_SetXMLTag(MERCHANTINFO_Path, "MERCHANT", "STCODE", gConfig.MERCHANT.STCODE);
    printf("[%s,%d] now TMLocationID=%s\n", __FUNCTION__, __LINE__, gConfig.MERCHANT.STCODE);
    //Pwd
    memcpy(gConfig.MERCHANT.PASSWORD, data + 20, 4);
    SetFunctionpPassword("SIGNON", gConfig.MERCHANT.PASSWORD);
    printf("[%s,%d] now SIGNON PWD=%s\n", __FUNCTION__, __LINE__, gConfig.MERCHANT.PASSWORD);

    //netWorkMode
    if (data[25] == '0') sprintf(gConfig.ETHERNET.NETWORKMODE, "INTERNET");
    else sprintf(gConfig.ETHERNET.NETWORKMODE, "VPN");
    printf("[%s,%d] now NETWORKMODE=%s\n", __FUNCTION__, __LINE__, gConfig.ETHERNET.NETWORKMODE);

    //remove /home/ap/pub/bkDeviceInfo.txt
    remove("/home/ap/pub/bkDeviceInfo.txt");

    //if origAP ECCAPP ecrOn was FALSE, return
    if(data[27]=='0') return;

    //upgrade ECR setting file
    remove(AROUND_DEVICE_CONFIG); //delete AROUND_DEVICE_CONFIG first, if existed

    BYTE sourcePath[64];
    BYTE destPath[64];
    USHORT apIndex = 0;
    ret = CTOS_APFind(APPNAME, &apIndex);
    if (ret != d_OK) printf("[%s,%d] CTOS_APFind fail:%d", __FUNCTION__, __LINE__, ret);
    printf("[%s,%d] %s index=%d", __FUNCTION__, __LINE__, APPNAME, apIndex);

    sprintf(sourcePath, "/home/ap/pub/%s", AROUND_DEVICE_CONFIG);
    sprintf(destPath, "/home/ap/%d/%s", apIndex, AROUND_DEVICE_CONFIG);
    copyFiles2(sourcePath, destPath);




    FILE *fp2 = NULL;
    fp2 = fopen((char *) destPath, "rb");
    if (fp2 == NULL) {
        printf("[%s,%d] fopen not found file\n", __FUNCTION__, __LINE__);
        myDebugPrinter(ERROR, "%s missing",destPath);
    } else {
        char buf[1024];
        memset(buf, 0x00, sizeof (buf));
        int n_chars = fread(buf, 1, 1024, fp2);
        printf("[%s,%d] %s: size=%d, data=%s\n", __FUNCTION__, __LINE__, destPath, n_chars, buf);

        fclose(fp2);
        fp2 = NULL;
        printf("[%s,%d] great! file %s existed \n", __FUNCTION__, __LINE__, destPath);
    }


    return;
}

void Init(void) {
    //設定畫面顯示參數
    init_DisplayConfig();
    CTOS_KBDSetSound(d_ON);
    CTOS_BackLightSet(d_BKLIT_LCD, d_ON);
    CTOS_BackLightSet(d_BKLIT_KBD, d_ON);
    //設定列表顏色深度    
    CTOS_PrinterSetHeatLevel(6);

    // 讀取 ResponseCode 資料  

    parse_ResponseCode("AP");

    parse_ResponseCode("CMAS");

    parse_ResponseCode("READER");

    parse_ResponseCode("ECR");

    parse_ResponseCode("SVCS");

    //讀取 TransFormat 交易格式表
    usParseTransFormat();

    //檢查備份資料區是否要清理
    Housekeeping();

    // 系統參數載入
    Sysinfo2_InitConfigData();

    //啟動網路  
    Eth_Init();

    //載入交易批次資料
    GetBatchTotal();
    MechineStatus |= Status_SignOnFail;
    if (CheckFLASHSTATUS() == d_OK)
        MechineStatus |= Status_FLASH_ERROR;

    //V15, added it for upgrade ECCAPP -> ECCAPP2
    checkEccappToEccapp2();

    /* 2014.04.03, kobe ECR Obj*/
    int result;
    ecrInitial(&ecrObj);
    if ((result = ecrObj.settingInterface(&ecrObj)) == d_OK) {
        if ((result = ecrObj.ecrRun(&ecrObj)) != d_OK)
            ecrObj.ecrOn = FALSE;
    }
    else ecrObj.ecrOn = FALSE;
    /* 2014.04.03, kobe ECR Obj end*/
}

void PowerSaving() {
    UCHAR bSrc;
    USHORT ret = CTOS_PowerSource(&bSrc);
    if (ret == d_OK && bSrc == d_PWRSRC_BATTERY) {
        CTOS_PowerMode(d_PWR_SLEEP_MODE);
        if (strcmp(gConfig.DEVICE.READER.bPORT, "Builtin") == 0) {
            CTOS_CLInit(); //wakeup之後要下CLInit 讀卡機才會正常使用
            ECC_ShowIDLE();
        }
    }
}

/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {

    USHORT ret;
    int Sleeptime = 100 * 60; //60秒 
    int kill_rc;

    //CTOS_PrinterFline(5);
    //myDebugPrinter(WARN, "app main start, the warnning words just testing printer function working fine or not");
    //delete ECCAPP
    deleteOldApp("ECCAPP");

    //init config
    Init();




    ret = Process_ReBootCheckStatus();
    //pthread_t thread1;     // 宣告執行緒
    //pthread_create(&thread1, NULL, (void*)ShowDataTime, NULL);    // 執行緒 SSLSocketConnect  
    ShowUPStatusbar();



    init_menudata();
    ret = SystemLog("SYSTEM", "POWER ON");
    gScrpitTesting = 0;

    pthread_create(&thread_SendAdvice, NULL, (void *) SendAdvice_Background, NULL); // 執行緒 SSLSocketConnect   


    if (ecrObj.ecrOn) {
        if (ecrObj.autoSignOn) {
            ecrObj.autoExeSignOn(&ecrObj);
        }
        else MessageBox("執行登入", "請使用收銀機", "發送登入...", "", "", 0);
    }



    CTOS_TimeOutSet(TIMER_ID_2, Sleeptime);
    CTOS_TimeOutSet(TIMER_ID_1, gSignOnlimit);

    BYTE buff[8 + 1];
    int iSw;
    BYTE key;
    ECC_ShowIDLE();
    while (1) {
        key = 0;
        CTOS_KBDHit(&key);
        if (key != 0xff) {
            CTOS_BackLightSet(d_BKLIT_LCD, d_ON);
            CTOS_BackLightSet(d_BKLIT_KBD, d_ON);
        }
        switch (key) {
            case d_KBD_F1:
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = TRUE;
                gIDLE = FALSE;
                if (MechineStatus & Status_FLASH_ERROR)
                    ErrorMessageBox("設備故障", "記憶體故障", "設備禁用", "請報修", "", d_MB_CHECK);
                else {
                    TXMenu();
                    CheckFLASHSTATUS();
                }
                printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = FALSE;
                printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
                ECC_ShowIDLE();

                printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
                break;
            case d_KBD_F2:
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = TRUE;
                gIDLE = FALSE;

                ShowBalance();
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = FALSE;
                ECC_ShowIDLE();

                break;
            case d_KBD_F3:
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = TRUE;
                gIDLE = FALSE;

                RePrintReceipt();
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = FALSE;
                ECC_ShowIDLE();
                break;
            case d_KBD_F4:
                //ret=Process_SignOn(); 
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = TRUE;
                gIDLE = FALSE;
                CheckPrintTXDetail();
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = FALSE;
                ECC_ShowIDLE();
                break;
            case d_KBD_5:
                //2014.07.30, fixed bug, reopen it 
                memset(buff, 0x00, sizeof (buff));
                ret = ShowInputBox("", "請輸入密碼", buff, 10, INPUT_TYPE_Number, '*');
                if (strcmp(buff, gConfig.DEVICE.DMPASSWORD) != 0) {
                    ShowMessage("", "密碼錯誤", TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);

                    ECC_ShowIDLE();
                    break;
                }

                gIDLE = FALSE;
                ShowTestCase();
                ECC_ShowIDLE();
                break;
            case d_KBD_6:
                gIDLE = FALSE;
                memset(buff, 0x00, sizeof (buff));
                ret = ShowInputBox("", "請輸入密碼", buff, 10, INPUT_TYPE_Number, '*');
                if (strcmp(buff, gConfig.DEVICE.DMPASSWORD) != 0) {
                    ShowMessage("", "密碼錯誤", TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);
                    ECC_ShowIDLE();
                    break;
                }
                ReaderCommandMode();
                break;
            case d_KBD_0:
                memset(buff, 0x00, sizeof (buff));
                ret = ShowInputBox("", "請輸入密碼", buff, 10, INPUT_TYPE_Number, '*');
                if (strcmp(buff, gConfig.DEVICE.MMPASSWORD) != 0) {
                    ShowMessage("", "密碼錯誤", TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);
                    ECC_ShowIDLE();
                    break;
                }
                exit(0);
                break;
            case d_KBD_2:
                ShowTerminalInfo();
                ECC_ShowIDLE();
                break;
            case d_KBD_3:
                ShowVersionInfo();
                ECC_ShowIDLE();
                break;
            case d_KBD_7:
                gIDLE = FALSE;
                memset(buff, 0x00, sizeof (buff));
                ret = ShowInputBox("", "請輸入密碼", buff, 10, INPUT_TYPE_Number, '*');
                if (strcmp(buff, gConfig.DEVICE.DMPASSWORD) != 0) {
                    ShowMessage("", "密碼錯誤", TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);
                    ECC_ShowIDLE();
                    break;
                }
                SwitchDebugFunction();
                ECC_ShowIDLE();
                break;
            case d_KBD_8:
                gIDLE = FALSE;
                memset(buff, 0x00, sizeof (buff));
                ret = ShowInputBox("", "請輸入密碼", buff, 10, INPUT_TYPE_Number, '*');
                if (strcmp(buff, gConfig.DEVICE.SMPASSWORD) != 0) {
                    ShowMessage("", "密碼錯誤", TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);
                    ECC_ShowIDLE();
                    break;
                }

                if (ecrObj.ecrOn) ecrObj.ecrUiStay = TRUE;
                SwitchSettingFunction();
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = FALSE;
                ECC_ShowIDLE();

                break;

            case d_KBD_9:

                gIDLE = FALSE;
                memset(buff, 0x00, sizeof (buff));
                ret = ShowInputBox("", "請輸入密碼", buff, 10, INPUT_TYPE_Number, '*');
                if (strcmp(buff, gConfig.DEVICE.MMPASSWORD) != 0) {
                    ShowMessage("", "密碼錯誤", TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);
                    ECC_ShowIDLE();
                    break;
                }

                if (ecrObj.ecrOn) ecrObj.ecrUiStay = TRUE;
                ManufacturerMenu();
                if (ecrObj.ecrOn) ecrObj.ecrUiStay = FALSE;
                ECC_ShowIDLE();

                break;
            case d_KBD_DOT:

                break;
            case d_KBD_CANCEL:
                //    exit(0);b
                break;

        }

        if (CTOS_TimeOutCheck(TIMER_ID_1) == d_YES) {
            if (ecrObj.ecrOn) {
                if (ecrObj.autoSignOn) ecrObj.autoExeSignOn(&ecrObj);
                else {
                    //  ShowTitle("請執行登入");
                    //  CTOS_LCDGTextOut(0,40*1,"距上次登入系統",Med_Font_Size,FALSE);    
                    //  CTOS_LCDGTextOut(0,40*2,"已超過規定時間!!",Med_Font_Size,FALSE);    
                    //  CTOS_LCDGTextOut(0,40*3,"請使用收銀機",Med_Font_Size,FALSE);                              
                    //  CTOS_LCDGTextOut(0,40*4,"發送登入...",Med_Font_Size,FALSE);
                    ecrObj.gData.forcedTxnPCode = 881999; //forced singon
                    //  while(ecrObj.isDataIn(&ecrObj)!=d_OK){}
                }
            }
            else {
                if (MechineStatus & Status_SignOnFail) {

                } else {
                    ret = MessageBox(gTransTitle, "距上次登入系統", "已超過規定時間!!", "將進行系統登入動作", "", d_MB_CHECK);
                    if (ret == d_OK) {
                        // Function_Signon();     
                        ResetDongle();
                        MechineStatus = Status_SignOnFail;
                        ECC_ShowIDLE();
                    }
                }
            }

        }


        if (ecrObj.isDataIn(&ecrObj) == d_OK) {
            printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
            ECC_ShowIDLE();
            printf("[%s,%d] trace...\n", __FUNCTION__, __LINE__);
        }


        if (key != 0xff) {
            printf("[%s,%d] reset Timer", __FUNCTION__, __LINE__);
            CTOS_TimeOutSet(TIMER_ID_2, Sleeptime);

        }

        if (CTOS_TimeOutCheck(TIMER_ID_2) == d_YES) {
            if (!ecrObj.ecrOn) PowerSaving();

            ECC_ShowIDLE();
            // 宣告執行緒
            ret = Eth_CheckDeviceStatus();
            if (ret == d_OK) {
                printf("[%s,%d] check Thread alive\n", __FUNCTION__, __LINE__);
                kill_rc = pthread_kill(thread_SendAdvice, 0);
                if (kill_rc == ESRCH) {
                    printf("[%s,%d] create Thread\n", __FUNCTION__, __LINE__);
                    pthread_create(&thread_SendAdvice, NULL, (void *) SendAdvice_Background, NULL); // 執行緒 SSLSocketConnect 
                }
            }
            printf("[%s,%d] reset Timer", __FUNCTION__, __LINE__);
            CTOS_TimeOutSet(TIMER_ID_2, Sleeptime);


        }
    }

    // exit(0);
}
