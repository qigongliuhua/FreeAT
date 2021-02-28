# FreeAT

## 介绍
AT指令库
基于STM32 HAL库

## 使用说明
```c
#include "at.h"

extern atStatus atIsInConfigStatus(void);
extern atStatus atSwitchToConfigStaus(void);
extern atStatus atSwitchToCommunicationStatus(void);
extern atStatus atReboot(void);
extern atStatus atRecovery(void);
extern atStatus atClear(void);
extern atStatus atShell(char* shell);

extern atStatus atGetCmdEchoEnable(char* enable);
extern atStatus atSetCmdEchoEnable(char* enable);
extern atStatus atGetWorkMode(char* mode);
extern atStatus atSetWorkMode(char* mode);
extern atStatus atGetPassword(char* pw);
extern atStatus atSetPassword(char* pw);
extern atStatus atGetBootMessage(char* msg);
extern atStatus atSetBootMessage(char* msg);
extern atStatus atGetNoDataRebootTime(uint16_t* time);
extern atStatus atSetNoDataRebootTime(uint16_t time);
extern atStatus atGetSignalIntensity(char* msg);
extern atStatus atGetNetworkInfo(char* info);
extern atStatus atGetSystemConfig(char* info);
extern atStatus atSetSystemConfig(char* info);
extern atStatus atGetSoftworeVersion(char* info);
extern atStatus atGetFotaUpdatePollTime(uint16_t* time);
extern atStatus atSetFotaUpdatePollTime(uint16_t time);
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
extern atStatus atGetSocketAEnable(char* enable);
extern atStatus atSetSocketAEnable(char* enable);
extern atStatus atGetSocketBEnable(char* enable);
extern atStatus atSetSocketBEnable(char* enable);
extern atStatus atGetSocketAKeepalive(char* keepalive);
extern atStatus atSetSocketAKeepalive(char* keepalive);
extern atStatus atGetSocketBKeepalive(char* keepalive);
extern atStatus atSetSocketBKeepalive(char* keepalive);
extern atStatus atGetSocketATCPSelect(char* tcpsl);
extern atStatus atSetSocketATCPSelect(char* tcpsl);
extern atStatus atGetSocketBTCPSelect(char* tcpsl);
extern atStatus atSetSocketBTCPSelect(char* tcpsl);
extern atStatus atGetSocketALinkStatus(char* lksta);
extern atStatus atGetSocketBLinkStatus(char* lksta);
extern atStatus atGetSocketAAutoRelinkTimeOut(uint16_t* time);
extern atStatus atSetSocketAAutoRelinkTimeOut(uint16_t time);
extern atStatus atGetSocketBAutoRelinkTimeOut(uint16_t* time);
extern atStatus atSetSocketBAutoRelinkTimeOut(uint16_t time);
extern atStatus atGetSocketAShortLinkTimeOut(uint16_t* time);
extern atStatus atSetSocketAShortLinkTimeOut(uint16_t time);
extern atStatus atGetSocketBShortLinkTimeOut(uint16_t* time);
extern atStatus atSetSocketBShortLinkTimeOut(uint16_t time);
extern atStatus atGetSocketIndicateDataSourceEnable(char* enable);
extern atStatus atSetSocketIndicateDataSourceEnable(char* enable);
extern atStatus atGetSocketEnable(char* enable);
extern atStatus atSetSocketEnable(char* enable);
extern atStatus atGetSocketRelinkTime(uint16_t* time);
extern atStatus atSetSocketRelinkTime(uint16_t time);
extern atStatus atGetRegisterPackageEnable(char* enable);
extern atStatus atSetRegisterPackageEnable(char* enable);
extern atStatus atGetRegisterPackageType(char* type);
extern atStatus atSetRegisterPackageType(char* type);
extern atStatus atGetRegisterPackageData(char* data);
extern atStatus atSetRegisterPackageData(char* data);
extern atStatus atGetRegisterType(char* type);
extern atStatus atSetRegisterType(char* type);
extern atStatus atGetRegisterType(char* type);
extern atStatus atSetRegisterType(char* type);
extern atStatus atGetCloudParm(char* parm);
extern atStatus atSetCloudParm(char* parm);
extern atStatus atGetUDCID(char* id);
extern atStatus atSetUDCID(char* id);
extern atStatus atGetHeartEnable(char* enable);
extern atStatus atSetHeartEnable(char* enable);
extern atStatus atGetHeartData(char* data);
extern atStatus atSetHeartData(char* data);
extern atStatus atGetHeartType(char* type);
extern atStatus atSetHeartType(char* type);
extern atStatus atGetHeartTime(uint16_t* time);
extern atStatus atSetHeartTime(uint16_t time);
extern atStatus atGetHTTPDType(char* type);
extern atStatus atSetHTTPDType(char* type);
extern atStatus atGetHTTPDUrl(char* url);
extern atStatus atSetHTTPDUrl(char* url);
extern atStatus atGetHTTPDServerParm(char* parm);
extern atStatus atSetHTTPDServerParm(char* parm);
extern atStatus atGetHTTPDRequestHead(char* head);
extern atStatus atSetHTTPDRequestHead(char* head);
extern atStatus atGetHTTPDTimeout(uint16_t* time);
extern atStatus atSetHTTPDTimeout(uint16_t time);
extern atStatus atGetHTTPDFilterHeadEnable(char* enable);
extern atStatus atSetHTTPDFilterHeadEnable(char* enable);
extern atStatus atSendMessageSM(char* msg);
extern atStatus atSendMessageCISMS(char* msg);
extern atStatus atGetModbusEnable(char* enable);
extern atStatus atSetModbusEnable(char* enable);
extern atStatus atGetCurrentTime(char* time);

```
## 联系方式
邮箱: 694606585@qq.com