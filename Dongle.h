/* 
 * File:   Reader.h
 * Author: T420s
 *
 * Created on 2013年7月23日, 下午 2:32
 */

#ifndef READER_H
#define	READER_H

#ifdef	__cplusplus
extern "C" {
#endif

 #include <ctosapi.h>  
 #include "Substruct.h"
    //typedef char			BOOL;
//typedef unsigned long		DWORD;
//typedef unsigned int		UINT;
//typedef unsigned char		BYTE;
typedef long long 		INT64;
typedef unsigned long long	UINT64;
typedef void 			PVOID;

#define LOG_FILE_PATTERN "^Dongle[[:digit:]]{8}\\.log$"
#define MAX_LOG_FILE     (30)

#define TRUE		1
#define FALSE		0

#define MAX_MSG            (10240)
#define MAX_TRACE_DEPTH    (128)
#define DEFAULT_LOG_FILENO (STDOUT_FILENO)

typedef enum {
	PORT_OPENED_ERROR                   = -1,
	PORT_DEVICE_ERROR                   = -2,
	PORT_SETCOMM_ERROR                  = -3,
	PORT_NOTOPEN_ERROR                  = -4,
	PORT_PURGECOMM_ERROR                = -5,
	PORT_GETCOMTIMEOUT_ERROR            = -6,
	PORT_SETCOMTIMEOUT_ERROR            = -7,
	PORT_GETCOMMSTATE_ERROR             = -8,
	PORT_SETCOMMSTATE_ERROR             = -9,
	PORT_CREATEWRITEEVENT_ERROR         = -10,
	PORT_CLOSEHANDLE_ERROR              = -11,
	PORT_NOTWRITEPENDING_ERROR          = -12,
	PORT_WRITEOVERLAPPED_ERROR          = -13,
	PORT_WRITETIMEOUT_ERROR             = -14,
	PORT_WRITEWAITOBJECT_ERROR          = -15,
	PORT_CREATEREADEVENT_ERROR          = -16,
	PORT_NOTREADPENDING_ERROR           = -17,
	PORT_READOVERLAPPED_ERROR           = -18,
	PORT_READTIMEOUT_ERROR              = -19,
	PORT_READWAITOBJECT_ERROR           = -20,
	PORT_WRITEFILEOR                    = -21,
	PORT_READFILE_ERROR                 = -22,
	PORT_LOG_ERROR                      = -23,
	DONGLE_CONFIRM_ADDVALUE_ERROR       = -24,
	DONGLE_CONFIRM_CANCELADDVALUE_ERROR = -25,
	DONGLE_CONFIRM_CARDSALE_ERROR       = -26,
	DONGLE_CONFIRM_CANCELCARDSALE_ERROR = -27,
	DONGLE_BLOCKCARD_NOT_FIND           = -28,
	DONGLE_CHDIR_ERROR                  = -29,
	DONGLE_OPENFILE_ERROR               = -30,
	DONGLE_FSEEK_ERROR                  = -31,
	DONGLE_FERROR_ERROR                 = -32,
	DONGLE_NO_BLACKLISTR                = -33,
	DONGLE_PARGUMENTS_ERROR             = -34,
	DONGLE_MALLOC_ERROR                 = -35,

	DONGLE_UNFORMAT_ERROR               = -36,
	AP_FAILURE                          = -37,
	AP_INTERRUPTED                      = -38,

	SUCCESS                             = 0x0090,
	DONGLE_LOCKCARD                     = 0x0664,
	DONGLE_BALANCE_INSUFFICIENT         = 0X0364,
	DONGLE_VERIFY_LOCKCARD        = 0X0E64,
	DONGLE_VERIFY_ONLINE        = 0X1564
} dongle_errno_t;
/*
void show_usage(const char* program);

const char* const signal_strerror(int sig);
bool set_signal_handler(int sig, struct sigaction* sig_action);
void signal_handler(int sig, siginfo_t* sig_info, void* other_info);
static const char* const regerror_msg(const regex_t* reg, int err);
 
 static bool compile_ere(regex_t* reg,const char* pattern,bool case_sensitive,bool no_detail);
bool ere_matches(const char* str, const char* pattern, bool case_sensitive);
int log_filter(const struct dirent* entry);
static void close_log(void);
bool set_log(const char* pathname);
bool init(int argc, char** argv);
bool parse_cmd_line(int argc, char** argv);
void TRACE_(const char* fmt, ...);
void TRACE0_(const char* msg);
void call_stack(const char* fmt, ...);
void log_msg(const char* fmt, ...);
void finalizer(void);
const char* const dongle_ret_error(int16_t err);
void reverse_int16(u_int16_t* uint16);
const char* const dongle_strerror(int16_t err);
bool run(void);
*/  
//int inPPR_Reset( BYTE * lpOutData ,int * inOutLen );
int inPPR_Reset(BYTE ONLINEFLAG);
int inPPR_SignOn(void);
int inPPR_SignOnQuery(void);
int inPPR_ReadCardBasicData(void);
int inPPR_TxnReqOnline(void);
int inPPR_AuthTxnOnline(void);
int inPPR_TxnReqOffline(void);
int inPPR_AuthTxnOffline(void);
int inPPR_LockCard(void);
int inPPR_ReadDongleDeduct(BYTE *lpOutData,int *inOutLen);
int inPPR_CardSale(BYTE *lpOutData,int *inOutLen);
int inPPR_AuthCardSale(BYTE *lpOutData,int *inOutLen);
int inPPR_CancelTxn(BYTE *lpOutData,int *inOutLen);
int inPR_SetValue(BYTE *lpOutData,int *inOutLen);
int inPR_AuthSetValue(BYTE *lpOutData,int *inOutLen);
int inPR_TxRefund(BYTE *lpOutData,int *inOutLen);
int inPR_TxAuthRefund(BYTE *lpOutData,int *inOutLen);
int inPR_TxAddValue(BYTE *lpOutData,int *inOutLen);
int inPR_TxAuthAddValue(BYTE *lpOutData,int *inOutLen);
int inPR_AutoloadEnable(BYTE *lpOutData,int *inOutLen);
int inPR_AuthAutoloadEnable(BYTE *lpOutData,int *inOutLen);
int inPR_AddValue(BYTE *lpOutData,int *inOutLen);
int inPR_AuthAddValue(BYTE *lpOutData,int *inOutLen);
int inPPR_ReadCardDeduct(BYTE *lpOutData,int *inOutLen);
int inPPR_ReadCodeVersion(BYTE *lpOutData,int *inOutLen);
int inPR_Reboot(BYTE *lpOutData,int *inOutLen);
int inPR_LockCard(BYTE *lpOutData,int *inOutLen);
int inPPR_SetValue(void);
int inPPR_AuthSetValue(void);
int inPPR_TxRefund(BYTE *lpOutData,int *inOutLen);
int inPPR_TxAuthRefund(BYTE *lpOutData,int *inOutLen);
int inPPR_AutoloadEnable(BYTE *lpOutData,int *inOutLen);
int inPPR_AuthAutoloadEnable(BYTE *lpOutData,int *inOutLen);
int inPPR_AuthAutoload(BYTE *lpOutData,int *inOutLen);
int inPPR_ReadCardNumber(void);
USHORT CheckReaderResponseCode(USHORT Respcode);
USHORT ResetDongle(void);
int inPPR_ReadCardNumber2(void);

#ifdef	__cplusplus
}
#endif

#endif	/* READER_H */

