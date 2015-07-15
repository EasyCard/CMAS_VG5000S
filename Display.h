/* 
 * File:   Display.h
 * Author: T420s
 *
 * Created on 2013年10月15日, 上午 11:25
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif
void Setcolor(ULONG BackGnd,ULONG ForeGnd);
void ShowInternetStatus(void);
void ShowStatus_Thread(void);
void ShowSystemMemoryStatus(STR * flagname);
void ShowTitle(STR * Title);
void ShowStatusLine(STR * line);
void ShowLine(USHORT usX,USHORT usY,USHORT usFontSize,STR * line,BYTE bFill);
int MessageBox(STR *Title,STR * line1,STR * line2,STR * line3,STR * line4,USHORT MBTYPE);
BYTE Displaymuiltlie(USHORT usFontSize,STR *Title,STR *Line[]);
//int ShowInputBox(STR *Title,STR * line1,STR * line2, BYTE * buff,int limit,STR *pcaKeyboardLayout[]);
int InputString(USHORT usX, USHORT usY, BYTE isMask, BYTE *pbaStr, USHORT *usStrLen);
//int ShowMessage(USHORT usFontSize,STR *Title,STR * line[],int linenum,BYTE ComformType);
int ErrorMessageBox(STR * Title,STR * line1,STR * line2,STR * line3,STR * line4,USHORT MBTYPE);
int ShowMessage(STR *Title,STR * line1,BYTE ComformType);
int ShowMessage4line(STR *Title,STR * line1,STR * line2,STR * line3,STR * line4,BYTE ComformType);
int ShowMessage3line(STR *Title,STR * line1,STR * line2,STR * line3,BYTE ComformType);
int ShowMessage2line(STR *Title,STR * line1,STR * line2,BYTE ComformType);
int ShowInputBox3line(STR *Title,STR * line1,STR * line2,STR *line3, BYTE * buff,int limit,int InputType,BYTE bPasswordMask);
int ShowInputBox(STR *Title,STR * line, BYTE * buff,int limit,int InputType,BYTE bPasswordMask);
int ShowInputBox2(STR *Title,STR * line1,STR * line2, BYTE * buff,int limit,int InputType,BYTE bPasswordMask);
void WaitRemoveCard(STR *Line1,STR *Line2);
void ShowUPStatusbar(void);
void ShowBatteryStatus(void);
void ShowDataTime(void);
void ShowGSMSignal(void);
void ShowNetWorkTypeStatus(void);
void ShowUnUploadCount(void);
void ShowAPVersion(void);
#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

