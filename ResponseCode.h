/* 
 * File:   ResponseCode.h
 * Author: T420s
 *
 * Created on 2015年2月25日, 上午 9:49
 */

#ifndef RESPONSECODE_H
#define	RESPONSECODE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct{
    BYTE Element[16];
    BYTE NUMCODE[8+1];
    BYTE ACTIONCODE[24+1];
    BYTE STRING1[64+1];
    BYTE STRING2[64+1];
    BYTE STRING3[64+1];
}ResponseCode_STRUCT;
void parse_ResponseCode(STR *TYPE);

//void parse_ResponseCode(void);
USHORT ECC_CheckResponseCode(STR * TYPE, BYTE* Respcode);
USHORT ECC_CheckAPResponseCode(USHORT Respcode);
USHORT ECC_CheckReaderResponseCode(USHORT Respcode);
USHORT ECC_CheckCMASResponseCode(BYTE * Respcode);
USHORT ECC_CheckSVCSResponseCode(BYTE *Respcode);
#ifdef	__cplusplus
}
#endif

#endif	/* RESPONSECODE_H */

