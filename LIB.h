#ifndef LIB_H
#define LIB_H

#define OPERATION_OK					0x9000		//���\�����R�O
#define CLA_ERR							0x666E		//CLA �Ѽƿ�~(APDU)
#define INS_ERR							0x666D		//INS �Ѽƿ�~(APDU)
#define P1_P2_ERR						0x666C		//P1 P2 �Ѽƿ�~(APDU)
#define LC_LE_ERR						0x6667		//Lc Le �Ѽƿ�~(APDU)
#define DATA_ERR						0x666A		//Data �Ѽƿ�~(APDU)
#define EDC_ERR							0x6668		//EDC��~(APDU)
//uart0
#define UNKNOWN_STA					(0x00000000)		//�������A
#define PROLOG_RECIEVE_STA			(0x00000001)		//����ProLog Byte���A
#define INFO_HEADER_RECIEVE_STA 	(0x00000002)		//����Information Header���A
#define INFO_BODY_RECIEVE_STA		(0x00000003)		//����Information Body���A
#define EDC_RECIEVE_STA				(0x00000004)		//����EDC���� Byte���A




#define SERIAL_PORT_REV_TIMEOUT_ERR	 		(0x7F00)		//
#define SAM_ADPU_COMMAND_ERR				(0x7F01)		//
#define CLADPU_COMMAND_ERR					(0x7F02)		//
#define SERIAL_PORT_AUTO_BAUD_RATE			(0x7F03)		//
#define SERIAL_PORT_NOT_READY_ERR			(0x7F04)		//
#define READER_HW_NO_SUPPORT_ERR 			(0x7F05)
#define SERIAL_PORT_NO_DATA_ERR		 		(0x7F06)		//
#define SERIAL_PORT_ADPU_DATA_FORMAT_ERR 	(0x7F07)		//


#define PRET_CLA_INS_ERR					0x6001	// CLA, INS ERROR
#define PRET_P1_P2_ERR						0x6002	// P1, P2 ERROR

//----------------------------------------------------------------------------------------------------
extern unsigned char Tscc_cAnswerLen;
unsigned short Ts_Uart0InfoProcess (void);
//unsigned short Ts_Uart0InfoProcess(unsigned char* inData,unsigned char* outData,unsigned char*  answerLen,unsigned char serialPortMode);	
void Ts_SystemParamentInialize(void);
void Ts_EraseKey(void);
void Ts_Timer0Handler (void);
//-------=--------------------------------------------------------------------------------------------
//Uart
//RS232�����T��

#pragma  pack(1)  //  align  to  one-byte

//RS232�����T��
typedef struct
{
	unsigned char cProLog[3];		//NAD,PCB,LEN

	unsigned char cInfoHeader[4];	//CLA,INS,P1,P2

	unsigned char cInfoBody[525];	//�T��Buffer���j�p

	unsigned char cEDC;				//����
}UART_RECIEVE_INFO;

//RS232�^���T��
typedef struct
{
	unsigned char cProLog[3]; 		//NAD,PCB,LEN

	unsigned char cInfoBody[525];	//�T��Buffer���j�p

	unsigned char cSW[2];			//���ASW1,SW2

	unsigned char cEDC;
}UART_SEND_INFO;


#pragma  pack()      //  reset  to  default.

//extern UART_RECIEVE_INFO g_sUart0RecieveInfo;					
//extern UART_SEND_INFO    g_sUart0AnswerInfo;

//----------------------------------------------------------------------------------------------------
extern void dV_WDTInit(void);
extern void dV_WDTFeed(void);
extern void IOInit(void);
extern void SystemInitialize(void);
extern void Delay100uS(unsigned int n);
extern void Delay10uS(unsigned int n);
extern void Delay1uS(unsigned int n);
extern void EnableTimer(unsigned char cTimerNum);

/******************************************************************************
*�\��: �w�ɾ���l��(Timer0 ~Timer3)
*��J�G
		 cTimerNum�G	 �w�ɾ��Ǹ�(0~3�GTimer0 ~Timer3)
		 iTimerInterval�GiTimerInterval = Timer*(Fpclk/1000 - 1)ms 		(ms��)
										= Timer*(Fpclk/1000000 - 1)us	(us��)
						(��GTimer���w�q�ɶ���u�Ams�ų�쬰ms�Aus�ų��us)
*��^�G	RS232��l�ƪ��A(TRUE�G���\�AFALSE�G����)
******************************************************************************/

#else
#endif

