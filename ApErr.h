/* 
 * File:   ApErr.h
 * Author: user
 *
 * Created on 2014年4月22日, 下午 1:39
 */

#ifndef APERR_H
#define	APERR_H

#ifdef	__cplusplus
extern "C" {
#endif

//Commom err Code    0xFFFF~0xFFAF
#define COMM_ERR                0xFFFE
#define COMM_ESCAPE             0xFFFD
#define COMM_MEMORY_FAIL        0xFFFC
    
//RS232 err code -50~-100 FFAE~FF5F
#define RS232_SEND_FAIL         0xFFAE
#define RS232_RECV_FAIL         0xFFAD    
#define RS232_FORMAT_ERROR      0xFFAC
#define RS232_PARAM_ERROR       0xFFAB

//ECR err Code -101~-150 0xFF5E~0xFF0E
#define ECR_FORMAT_ERROR        0xFF5E
#define ECR_DATA_INCOMPLETE     0xFF5D
#define ECR_DATA_WRONG          0xFF5C
#define ECR_INTERFACE_NOT_SUPPORT       0xFF5B  
#define ECR_TXN_AMT_WRONG       0xFF5A
#define ECR_TXN_TYPE_NOT_SUPPORT       0xFF59    
#define ECR_TXN_NO_SUCCESS_BEFORE        0xFF58
#define ECR_TXN_TYPE_WRONG      0xFF57
#define ECR_TMS_PARAMETERS_WRONG      0xFF56  
#define ECR_VERSION_NOT_SUPPORT       0xFF55
#define ECR_NO_RECORD_NO_NEEDED_SETTLE  0xFF54
#define ECR_TRY_SETTLE_AGAIN 0xFF53
#define ECR_ERR_FILE_OPEN       0xFF52
    
//USB err code 0xFF0D~FEBD
#define USB_SEND_FAIL         0xFF0D
#define USB_RECV_FAIL         0xFF0C    
#define USB_FORMAT_ERROR      0xFF0B
#define USB_PARAM_ERROR       0xFF0A



  
    
#ifdef	__cplusplus
}
#endif

#endif	/* APERR_H */

