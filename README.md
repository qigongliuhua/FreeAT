# FreeAT

## 介绍
AT指令库
基于STM32 HAL库

## 使用说明
```c
#include "at.h"

atStatus atIsInConfig(void);            //是否在设置状态
atStatus atStartConfig(void);           //进入设置状态
atStatus atStartCommunication(void);    //进入通讯状态
atStatus atReboot(void);                //重启
atStatus atRecovery(void);              //恢复出厂设置
atStatus atClear(void);                 //恢复出厂设置
atStatus atOpenEcho(void);              //打开回显
atStatus atCloseEcho(void);             //关闭回显
atStatus atIsOpenEcho(void);            //是否打开了回显
atStatus atGetWorkMode(void);           //获取工作模式
atStatus atSetWorkMode(int mode);       //设置工作模式
atStatus atGetPassword(char* pw);       //获取串口密码
atStatus atSetPassword(char* pw);       //设置串口密码
atStatus atGetBootMsg(char* msg);       //获取启动信息
atStatus atSetBootMsg(char* msg);       //设置启动信息
atStatus atGetNoDataRebootTime(uint16_t* time); //获取无数据重启时间
atStatus atSetNoDataRebootTime(uint16_t time);  //设置无数据重启时间
atStatus atGetSignalIntensity(char* msg);       //获取信号强度
atStatus atGetNetworkInfo(char* info);          //获取网络信息
atStatus atGetSystemConfig(char* info);         //获取设备配置
atStatus atSetSystemConfig(char* info);         //设置设备配置
atStatus atGetSoftworeVersion(char* info);      //获取内部软件版本号
atStatus atGetFotaUpdatePollTime(uint16_t* time);   //获取fota升级轮询时间
atStatus atSetFotaUpdatePollTime(uint16_t time);    //设置fota升级轮询时间
atStatus atShell(char* shell);                      //运行linux shell命令
atStatus atGetFirmwareVersion(char* info);          //获取固件版本号
atStatus atGetSN(char* sn);             //获取SN号
atStatus atGetICCID(char* iccid);       //获取ICCID号
atStatus atGetIMEI(char* imei);         //获取IMEI号
atStatus atGetBSPosition(char* position);   //获取基站位置
atStatus atGetLocalIP(char* ip);        //获取本地IP
atStatus atGetUART(char* info);         //获取串口信息
atStatus atSetUART(char* info);         //设置串口信息
atStatus atGetUARTPackTime(uint16_t* time); //获取串口打包时间
atStatus atSetUARTPackTime(uint16_t time);  //设置串口打包时间
atStatus atGetUARTPackLength(uint16_t* len);    //获取串口打包长度
atStatus atSetUARTPackLength(uint16_t len);     //设置串口打包长度
atStatus atGetAPN(char* apn);   //获取APN
atStatus atSetAPN(char* apn);   //设置APN
atStatus atGetSocketAParm(char* parm);  //获取SocketA参数
atStatus atSetSocketAParm(char* parm);  //设置SocketA参数
atStatus atGetSocketBParm(char* parm);  //获取SocketB参数
atStatus atSetSocketBParm(char* parm);  //设置SocketB参数

```
## 联系方式
邮箱: 694606585@qq.com