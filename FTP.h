/* 
 * File:   FTP.h
 * Author: T420s
 *
 * Created on 2013年11月12日, 上午 11:30
 */

#ifndef FTP_H
#define	FTP_H

#ifdef	__cplusplus
extern "C" {
#endif

//int ftpsget(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL);
int ftpsget(void);
USHORT ECC_FTPGetFile2(STR * Localfilename, STR * Remofilename);
USHORT ECC_FTPGetFile(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL);
USHORT ECC_FTPGetFileforDebug(STR * Localfilename, STR * Remofilename);
//int FTPGET(void);
//int FTPUPLOAD2(void);
int FTPsUPLOAD(BYTE * id,BYTE *pw,BYTE *ip,BYTE * file ,BYTE *RemoName);
USHORT ECC_FTPGetFileTest(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL);
USHORT ECC_FTPGetFileTest2(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL);
USHORT ECC_FTPGetFileShowStatus(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL);
USHORT ECC_FTPGetFileShowStatusForTest(STR *title,STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL);
USHORT ECC_FTPGetFileShowStatus_S(STR *ip,STR *id,STR *pw,STR * Localfilename, STR * Remofilename,BYTE isSSL);
//////////////////////////////////
int SendMailtest(void);
#ifdef	__cplusplus
}
#endif

#endif	/* FTP_H */

