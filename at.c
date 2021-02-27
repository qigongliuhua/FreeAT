
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "atcmd.h"
#include "at.h"
#include "usart.h"

#define athuart huart3

#define USE_DEBUG

uint8_t rec_pc_data;
uint8_t rec_at_data;

#define AT_ID "[USR-7S4 V2]"

#define BUF_SIZE    64
#define WAIT_TIME 500
#define DELAY_TIME  500

#ifdef USE_DEBUG
static void atprintf(const char* msg, ...)
{
    char logbuf[128];
    va_list valist;
    va_start(valist, msg);
    vsprintf(logbuf, msg, valist);
    HAL_UART_Transmit(&huart1, (uint8_t*)logbuf, strlen(logbuf), 1000);
}
#else
static void atprintf(char* str, ...)
{
    UNUSED(str);
}
#endif

#define ERR(msg, ...) atprintf("[AT][ERROR][%s]" msg "\n", __func__, ##__VA_ARGS__)
#define INFO(msg, ...) atprintf("[AT][INFO][%s]" msg "\n", __func__, ##__VA_ARGS__)

#define Delayms(time)  HAL_Delay(time)

#define InitBuffer(size) uint8_t buf[size];\
                        uint32_t buf_len = size

#define ClearBuffer()   memset(buf, 0, buf_len)

#define AssertExist(str) if(strstr((const char*)buf, str) == NULL)\
                        {\
                            ERR("expect '%s', not '%s'",str ,(const char*)buf);\
                            return AT_ERR;\
                        }\

#define Len(str) strlen(str)

#define Transmit(str)   ClearBuffer();\
                        while(HAL_UART_Transmit(&athuart, (uint8_t*)str, Len(str), 100) != HAL_OK)

#define Receive(len)    HAL_UART_Receive(&athuart, buf, len > buf_len ? buf_len : len, WAIT_TIME)

#define ReturnOK()      Delayms(DELAY_TIME);\
                        INFO("success");\
                        return AT_OK

#define Strcat(stra, strb) (stra##strb)

static atStatus _atStartConfig(void)
{
    InitBuffer(BUF_SIZE);
    Transmit("+++");
    Receive(Len("a"));
    AssertExist("a");
    Transmit("a");
    Receive(Len("+ok"));
    AssertExist("+ok");
    ReturnOK();
}

static atStatus _atStartCommunication(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT_ENTM,"\n"));
    Receive(buf_len);
    AssertExist("OK");
    ReturnOK();
}

atStatus atIsInConfig(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT,"\n"));
    Receive(buf_len);
    Delayms(DELAY_TIME);
    if(strstr((const char*)buf, "OK") == NULL)
    {
        INFO("not in config status");
        return AT_ERR;
    }
    INFO("has been in config status");
    return AT_OK;
}

atStatus atStartConfig(void)
{
    if(atIsInConfig() == AT_ERR && _atStartConfig() == AT_ERR)
    {
        ERR("fail to start config");
        return AT_ERR;
    }
    INFO("success to start config");
    return AT_OK;
}

atStatus atStartCommunication(void)
{
    if(atIsInConfig() == AT_OK && _atStartCommunication() == AT_ERR)
    {
        ERR("fail to start communication");
        return AT_ERR;
    }
    INFO("success to start communication");
    return AT_OK;
}

atStatus atReboot(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT_REBOOT,"\n"));
    Receive(buf_len);
    AssertExist("OK");
    Delayms(20000);
    INFO("success");
    return AT_OK;
}

atStatus atOpenEcho(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT_E,"=ON\n"));
    Receive(buf_len);
    AssertExist("OK");
    ReturnOK();
}

atStatus atCloseEcho(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT_E,"=OFF\n"));
    Receive(buf_len);
    AssertExist("OK");
    ReturnOK();
}

atStatus atIsOpenEcho(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT_E,"\n"));
    Receive(buf_len);
    Delayms(DELAY_TIME);
    if(strstr((const char*)buf, "+E:ON") == NULL)
    {
        INFO("has opened echo");
        return AT_YES;
    }
    else if(strstr((const char*)buf, "+E:OFF") == NULL)
    {
        INFO("has closed echo");
        return AT_NO;
    }
    return AT_ERR;
}

atStatus atGetWorkMode(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT_WKMOD,"\n"));
    Receive(buf_len);
    Delayms(DELAY_TIME);
    if(strstr((const char*)buf, "+WKMOD:NET") == NULL)
    {
        INFO("in NET mode");
        return AT_MODE_NET;
    }
    else if(strstr((const char*)buf, "+WKMOD:HTTPD") == NULL)
    {
        INFO("in HTTPD mode");
        return AT_MODE_HTTPD;
    }
    else if(strstr((const char*)buf, "+WKMOD:UDC") == NULL)
    {
        INFO("in UDC mode");
        return AT_MODE_UDC;
    }
    return AT_ERR;
}

atStatus atSetWorkMode(int mode)
{
    InitBuffer(BUF_SIZE);
    switch (mode)
    {
    case AT_MODE_NET:
        Transmit(Strcat(CMD_AT_WKMOD,"=NET\n"));
        break;
    case AT_MODE_HTTPD:
        Transmit(Strcat(CMD_AT_WKMOD,"=HTTPD\n"));
        break;
    case AT_MODE_UDC:
        Transmit(Strcat(CMD_AT_WKMOD,"=UDC\n"));
        break;
    default:
        ERR("%d mode not defined", mode);
        return AT_ERR;
    }
    Receive(buf_len);
    AssertExist("OK");
    ReturnOK();
}

#define _StdSetStringAndReturnOK(atcmd, value)\
    char cmd[64];\
    InitBuffer(BUF_SIZE);\
    snprintf(cmd, 64, "%s=%s\n", atcmd, value);\
    Transmit(cmd);\
    Receive(buf_len);\
    AssertExist("OK");\
    ReturnOK()

#define _StdGetString(atcmd, value, len, tag, info)\
    char *temp;\
    InitBuffer(BUF_SIZE);\
    Transmit(Strcat(atcmd,"\n"));\
    Receive(buf_len);\
    Delayms(DELAY_TIME);\
    if((temp = strstr((const char*)buf, tag)) != NULL)\
    {\
        temp = &temp[strlen(tag)];\
        strncpy(value, temp, len);\
        value[strlen(value)-4] == '\0';\
        INFO("%s:%s", info, value);\
        return AT_OK;\
    }\
    return AT_ERR

atStatus atGetPassword(char* pw)
{
    _StdGetString(CMD_AT_CMDPW, pw, 10, "+CMDPW:", "password");
}


atStatus atSetPassword(char* pw)
{
    _StdSetStringAndReturnOK(CMD_AT_CMDPW, pw);
}


atStatus atGetBootMsg(char* msg)
{
    _StdGetString(CMD_AT_STMSG, msg, 20, "+STMSG:", "boot message");
}


atStatus atSetBootMsg(char* msg)
{
    _StdSetStringAndReturnOK(CMD_AT_STMSG, msg);
}

#define _StdGetU16(atcmd, val, tag, info)\
    char value[16];\
    char *temp;\
    InitBuffer(BUF_SIZE);\
    Transmit(Strcat(atcmd,"\n"));\
    Receive(buf_len);\
    Delayms(DELAY_TIME);\
    if((temp = strstr((const char*)buf, tag)) != NULL)\
    {\
        temp = &temp[strlen(tag)];\
        strncpy(value, temp, 16);\
        value[strlen(value)-4] == '\0';\
        INFO("%s:%s", info, value);\
        sscanf(value, "%u", (unsigned int*)val);\
        return AT_OK;\
    }\
    return AT_ERR


#define _StdSetU16AndReturnOK(atcmd, value)\
    char val_buf[10];\
    snprintf(val_buf, 10, "%u", value);\
    _StdSetStringAndReturnOK(atcmd, val_buf)

atStatus atSetNoDataRebootTime(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_RSTIM, time);
}

atStatus atGetNoDataRebootTime(uint16_t* time)
{
    _StdGetU16(CMD_AT_RSTIM, time, "+RSTIM:", "reset time");
}

atStatus atGetSignalIntensity(char* msg)
{
    _StdGetString(CMD_AT_CSQ, msg, 15, "+CSQ:", "intensity");
}

atStatus atGetNetworkInfo(char* info)
{
    _StdGetString(CMD_AT_SYSINFO, info, 15, "+SYSINFO:", "net info");
}

atStatus atSetSystemConfig(char* info)
{
    _StdSetStringAndReturnOK(CMD_AT_SYSCONFIG, info);
}

atStatus atGetSystemConfig(char* info)
{
    _StdGetString(CMD_AT_SYSCONFIG, info, 15, "+SYSCONFIG:", "sysconfig");
}

atStatus atGetSoftworeVersion(char* info)
{
    _StdGetString(CMD_AT_ZVERSION, info, 30, "+ZVERSION:", "softver");
}

atStatus atGetFotaUpdatePollTime(uint16_t* time)
{
    _StdGetU16(CMD_AT_FOTATIME, time, "+FOTATIME:", "fota time");
}

atStatus atSetFotaUpdatePollTime(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_FOTATIME, time);
}

atStatus atShell(char* shell)
{
    _StdSetStringAndReturnOK(CMD_AT_SHELL, shell);
}

atStatus atRecovery(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT_RELD,"\n"));
    Receive(buf_len);
    AssertExist("OK");
    Delayms(20000);
    INFO("success");
    return AT_OK;
}

atStatus atClear(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT_CLEAR,"\n"));
    Receive(buf_len);
    AssertExist("OK");
    Delayms(20000);
    INFO("success");
    return AT_OK;
}

atStatus atGetFirmwareVersion(char* info)
{
    _StdGetString(CMD_AT_VER, info, 30, "+VER:", "firmver");
}

atStatus atGetSN(char* sn)
{
    _StdGetString(CMD_AT_SN, sn, 30, "+SN:", "SN");
}

atStatus atGetICCID(char* iccid)
{
    _StdGetString(CMD_AT_ICCID, iccid, 30, "+ICCID:", "ICCID");
}

atStatus atGetIMEI(char* imei)
{
    _StdGetString(CMD_AT_IMEI, imei, 30, "+IMEI:", "IMEI");
}

atStatus atGetBSPosition(char* position)
{
    _StdGetString(CMD_AT_LBS, position, 30, "+LBS:", "bs postion");
}

atStatus atGetLocalIP(char* ip)
{
    _StdGetString(CMD_AT_LOCIP, ip, 20, "+LOCIP:", "local ip");
}

atStatus atGetUART(char* info)
{
    _StdGetString(CMD_AT_UART, info, 30, "+UART:", "uart");
}

atStatus atSetUART(char* info)
{
    _StdSetStringAndReturnOK(CMD_AT_UART, info);
}

atStatus atGetUARTPackTime(uint16_t* time)
{
    _StdGetU16(CMD_AT_UARTFT, time, "+UARTFT:", "pack time");
}

atStatus atSetUARTPackTime(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_UARTFT, time);
}

atStatus atGetUARTPackLength(uint16_t* len)
{
    _StdGetU16(CMD_AT_UARTFL, len, "+UARTFL:", "pack len");
}

atStatus atSetUARTPackLength(uint16_t len)
{
    _StdSetU16AndReturnOK(CMD_AT_UARTFL, len);
}

atStatus atGetAPN(char* apn)
{
    _StdGetString(CMD_AT_APN, apn, 30, "+APN:", "APN");
}

atStatus atSetAPN(char* apn)
{
    _StdSetStringAndReturnOK(CMD_AT_APN, apn);
}

atStatus atGetSocketAParm(char* parm)
{
    _StdGetString(CMD_AT_SOCKA, parm, 120, "+SOCKA:", "sockaparm");
}

atStatus atSetSocketAParm(char* parm)
{
    _StdSetStringAndReturnOK(CMD_AT_SOCKA, parm);
}

atStatus atGetSocketBParm(char* parm)
{
    _StdGetString(CMD_AT_SOCKB, parm, 120, "+SOCKB:", "sockbparm");
}

atStatus atSetSocketBParm(char* parm)
{
    _StdSetStringAndReturnOK(CMD_AT_SOCKB, parm);
}

