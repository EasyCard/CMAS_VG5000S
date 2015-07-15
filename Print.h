/* 
 * File:   Print.h
 * Author: T420s
 *
 * Created on 2013年9月30日, 上午 10:54
 */

#ifndef PRINT_H
#define	PRINT_H

#ifdef	__cplusplus
extern "C" {
#endif
    void PrintRemark(void);
void SystemCheck(STR *RS232STR);
void DebugPrint_hex(unsigned char* i_pc_buffer, long len, char* i_pc_title,int DebugMode);
void PrintReceipt(void );
void RePrintReceipt(void );
void PrintDateTime(STR *Date,STR * Time);
//USHORT PrintSettlementReceipt(void);
USHORT PrintSettlementReceipt(Batch_Totle_STRUCT *BatchTotal);
USHORT PrintTransDetail(void);
USHORT PrintDetail(TRANS_DATA2  *TransData);
USHORT PrintTXDetail(void);
//void   PrintReceipt(int ReceiptType);
void Receipt(int ReceiptType,BYTE Reprint);
void PrintTitle(void);
void Drawline(int height);
void Printline(STR *field1,STR * field2,USHORT usFontSize,BYTE bframe);
void PrintStr(int XPos,int YPOS,STR * field,USHORT usFontSize,BYTE bframe);
void SetPrintConfig(void);
USHORT CheckPrintStatus(void);
void PrintEASYCARDLOGO(void);
void PrintTest(void);
USHORT CheckPrintTXDetail(void);
USHORT PrintParameter(void);
USHORT PrintTXDetail2(void);
void PrintDateTime2(STR *Date,STR * Time,USHORT FontSize);
void GetDateTimeStr(STR *Date,STR * Time,STR *DataTimeStr);
void PrintMemoarystatus(int flag);
void thread_PrintLastReceipt(void);
#ifdef	__cplusplus
}
#endif

#endif	/* PRINT_H */

