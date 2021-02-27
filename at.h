#ifndef _AT_H_
#define _AT_H_

#include <stdbool.h>
#include "FreeRTOS.h"

#define AT_OK       0
#define AT_ERR      1
typedef int atStatus;

extern atStatus atIsInConfig(void);
extern atStatus atStartConfig(void);
extern atStatus atStartCommunication(void);
extern atStatus atReboot(void);
extern atStatus atRecovery(void);
extern atStatus atClear(void);
extern atStatus atOpenEcho(void);
extern atStatus atCloseEcho(void);
#define AT_NO       2
#define AT_YES      3
extern atStatus atIsOpenEcho(void);
#define AT_MODE_NET 4
#define AT_MODE_HTTPD   5
#define AT_MODE_UDC     6
extern atStatus atGetWorkMode(void);
extern atStatus atSetWorkMode(int mode);
extern atStatus atGetPassword(char* pw);
extern atStatus atSetPassword(char* pw);
extern atStatus atGetBootMsg(char* msg);
extern atStatus atSetBootMsg(char* msg);
extern atStatus atGetNoDataRebootTime(uint16_t* time);
extern atStatus atSetNoDataRebootTime(uint16_t time);
extern atStatus atGetSignalIntensity(char* msg);
extern atStatus atGetNetworkInfo(char* info);
extern atStatus atGetSystemConfig(char* info);
extern atStatus atSetSystemConfig(char* info);
extern atStatus atGetSoftworeVersion(char* info);
extern atStatus atGetFotaUpdatePollTime(uint16_t* time);
extern atStatus atSetFotaUpdatePollTime(uint16_t time);
extern atStatus atShell(char* shell);
extern atStatus atGetFirmwareVersion(char* info);
extern atStatus atGetSN(char* sn);
extern atStatus atGetICCID(char* iccid);
extern atStatus atGetIMEI(char* imei);
extern atStatus atGetBSPosition(char* position);
extern atStatus atGetLocalIP(char* ip);
extern atStatus atGetUART(char* info);
extern atStatus atSetUART(char* info);
extern atStatus atGetUARTPackTime(uint16_t* time);
extern atStatus atSetUARTPackTime(uint16_t time);
extern atStatus atGetUARTPackLength(uint16_t* len);
extern atStatus atSetUARTPackLength(uint16_t len);
extern atStatus atGetAPN(char* apn);
extern atStatus atSetAPN(char* apn);
extern atStatus atGetSocketAParm(char* parm);
extern atStatus atSetSocketAParm(char* parm);
extern atStatus atGetSocketBParm(char* parm);
extern atStatus atSetSocketBParm(char* parm);



#endif
