
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


static atStatus _atSwitchToConfigStaus(void)
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

static atStatus _atSwitchToCommunicationStatus(void)
{
    InitBuffer(BUF_SIZE);
    Transmit(Strcat(CMD_AT_ENTM,"\n"));
    Receive(buf_len);
    AssertExist("OK");
    ReturnOK();
}

atStatus atIsInConfigStatus(void)
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

atStatus atSwitchToConfigStaus(void)
{
    if(atIsInConfigStatus() == AT_ERR && _atSwitchToConfigStaus() == AT_ERR)
    {
        ERR("fail to start config");
        return AT_ERR;
    }
    INFO("success to start config");
    return AT_OK;
}

atStatus atSwitchToCommunicationStatus(void)
{
    if(atIsInConfigStatus() == AT_OK && _atSwitchToCommunicationStatus() == AT_ERR)
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

#if 0
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
#else
atStatus atGetCmdEchoEnable(char* enable)
{
    _StdGetString(CMD_AT_E, enable, 5, "+E:", "echo enable");
}

atStatus atSetCmdEchoEnable(char* enable)
{
    _StdSetStringAndReturnOK(CMD_AT_E, enable);
}

#endif



#if 0
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
#else
atStatus atGetWorkMode(char* mode)
{
    _StdGetString(CMD_AT_WKMOD, mode, 10, "+WKMOD:", "work mode");
}

atStatus atSetWorkMode(char* mode)
{
    _StdSetStringAndReturnOK(CMD_AT_WKMOD, mode);
}

#endif


atStatus atGetPassword(char* pw)
{
    _StdGetString(CMD_AT_CMDPW, pw, 10, "+CMDPW:", "password");
}


atStatus atSetPassword(char* pw)
{
    _StdSetStringAndReturnOK(CMD_AT_CMDPW, pw);
}


atStatus atGetBootMessage(char* msg)
{
    _StdGetString(CMD_AT_STMSG, msg, 20, "+STMSG:", "boot message");
}


atStatus atSetBootMessage(char* msg)
{
    _StdSetStringAndReturnOK(CMD_AT_STMSG, msg);
}


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

atStatus atGetSocketAEnable(char* enable)
{
    _StdGetString(CMD_AT_SOCKAEN, enable, 4, "+SOCKAEN:", "sockaenable");
}

atStatus atSetSocketAEnable(char* enable)
{
    _StdSetStringAndReturnOK(CMD_AT_SOCKAEN, enable);
}

atStatus atGetSocketBEnable(char* enable)
{
    _StdGetString(CMD_AT_SOCKBEN, enable, 4, "+SOCKBEN:", "sockbenable");
}

atStatus atSetSocketBEnable(char* enable)
{
    _StdSetStringAndReturnOK(CMD_AT_SOCKBEN, enable);
}

atStatus atGetSocketAKeepalive(char* keepalive)
{
    _StdGetString(CMD_AT_KEEPALIVEA, keepalive, 20, "+KEEPALIVEA:", "sockakeepalive");
}

atStatus atSetSocketAKeepalive(char* keepalive)
{
    _StdSetStringAndReturnOK(CMD_AT_KEEPALIVEA, keepalive);
}

atStatus atGetSocketBKeepalive(char* keepalive)
{
    _StdGetString(CMD_AT_KEEPALIVEB, keepalive, 20, "+KEEPALIVEB:", "sockbkeepalive");
}

atStatus atSetSocketBKeepalive(char* keepalive)
{
    _StdSetStringAndReturnOK(CMD_AT_KEEPALIVEB, keepalive);
}

atStatus atGetSocketATCPSelect(char* tcpsl)
{
    _StdGetString(CMD_AT_SOCKASL, tcpsl, 10, "+SOCKASL:", "sockatcpselect");
}

atStatus atSetSocketATCPSelect(char* tcpsl)
{
    _StdSetStringAndReturnOK(CMD_AT_SOCKASL, tcpsl);
}

atStatus atGetSocketBTCPSelect(char* tcpsl)
{
    _StdGetString(CMD_AT_SOCKBSL, tcpsl, 10, "+SOCKBSL:", "sockbtcpselect");
}

atStatus atSetSocketBTCPSelect(char* tcpsl)
{
    _StdSetStringAndReturnOK(CMD_AT_SOCKBSL, tcpsl);
}

atStatus atGetSocketALinkStatus(char* lksta)
{
    _StdGetString(CMD_AT_SOCKALK, lksta, 5, "+SOCKALK:", "sockalink");
}

atStatus atGetSocketBLinkStatus(char* lksta)
{
    _StdGetString(CMD_AT_SOCKBLK, lksta, 5, "+SOCKBLK:", "sockblink");
}

atStatus atGetSocketAAutoRelinkTimeOut(uint16_t* time)
{
    _StdGetU16(CMD_AT_SOCKATO, time, "+SOCKATO:", "sockaautotime");
}

atStatus atSetSocketAAutoRelinkTimeOut(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_SOCKATO, time);
}

atStatus atGetSocketBAutoRelinkTimeOut(uint16_t* time)
{
    _StdGetU16(CMD_AT_SOCKBTO, time, "+SOCKBTO:", "sockbautotime");
}

atStatus atSetSocketBAutoRelinkTimeOut(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_SOCKBTO, time);
}

atStatus atGetSocketAShortLinkTimeOut(uint16_t* time)
{
    _StdGetU16(CMD_AT_SHORATO, time, "+SHORATO:", "sockashortto");
}

atStatus atSetSocketAShortLinkTimeOut(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_SHORATO, time);
}

atStatus atGetSocketBShortLinkTimeOut(uint16_t* time)
{
    _StdGetU16(CMD_AT_SHORBTO, time, "+SHORBTO:", "sockbshortto");
}

atStatus atSetSocketBShortLinkTimeOut(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_SHORBTO, time);
}


extern atStatus atGetSocketIndicateDataSourceEnable(char* enable)
{
    _StdGetString(CMD_AT_SOCKIND, enable, 5, "+SOCKIND:", "socketind");
}

extern atStatus atSetSocketIndicateDataSourceEnable(char* enable)
{
    _StdSetStringAndReturnOK(CMD_AT_SOCKIND, enable);
}

extern atStatus atGetSocketEnable(char* enable)
{
    _StdGetString(CMD_AT_SDPEN, enable, 5, "+SDPEN:", "socketenable");
}

extern atStatus atSetSocketEnable(char* enable)
{
    _StdSetStringAndReturnOK(CMD_AT_SDPEN, enable);
}

atStatus atGetSocketRelinkTime(uint16_t* time)
{
    _StdGetU16(CMD_AT_SOCKRSTIM, time, "+SOCKRSTIM:", "socketrstime");
}

atStatus atSetSocketRelinkTime(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_SOCKRSTIM, time);
}

atStatus atGetRegisterPackageEnable(char* enable)
{
    _StdGetString(CMD_AT_REGEN, enable, 5, "+REGEN:", "regpackenable");
}

atStatus atSetRegisterPackageEnable(char* enable)
{
    _StdSetStringAndReturnOK(CMD_AT_REGEN, enable);
}

atStatus atGetRegisterPackageType(char* type)
{
    _StdGetString(CMD_AT_REGTP, type, 10, "+REGTP:", "regpacktype");
}

atStatus atSetRegisterPackageType(char* type)
{
    _StdSetStringAndReturnOK(CMD_AT_REGTP, type);
}

atStatus atGetRegisterPackageData(char* data)
{
    _StdGetString(CMD_AT_REGDT, data, 100, "+REGUSR:", "regpackdata");
}

atStatus atSetRegisterPackageData(char* data)
{
    _StdSetStringAndReturnOK(CMD_AT_REGDT, data);
}

atStatus atGetRegisterType(char* type)
{
    _StdGetString(CMD_AT_REGSND, type, 10, "+REGSND:", "regtype");
}

atStatus atSetRegisterType(char* type)
{
    _StdSetStringAndReturnOK(CMD_AT_REGSND, type);
}

atStatus atGetCloudParm(char* parm)
{
    _StdGetString(CMD_AT_CLOUD, parm, 40, "+CLOUD:", "cloudparm");
}

atStatus atSetCloudParm(char* parm)
{
    _StdSetStringAndReturnOK(CMD_AT_CLOUD, parm);
}

atStatus atGetUDCID(char* id)
{
    _StdGetString(CMD_AT_ID, id, 20, "+ID:", "UDCid");
}

atStatus atSetUDCID(char* id)
{
    _StdSetStringAndReturnOK(CMD_AT_ID, id);
}

atStatus atGetHeartEnable(char* enable)
{
    _StdGetString(CMD_AT_HEARTEN, enable, 5, "+HEARTEN:", "heartenable");
}

atStatus atSetHeartEnable(char* enable)
{
    _StdSetStringAndReturnOK(CMD_AT_HEARTEN, enable);
}

atStatus atGetHeartData(char* data)
{
    _StdGetString(CMD_AT_HEARTDT, data, 100, "+REGUSR:", "heartenable");
}

atStatus atSetHeartData(char* data)
{
    _StdSetStringAndReturnOK(CMD_AT_HEARTDT, data);
}

atStatus atGetHeartType(char* type)
{
    _StdGetString(CMD_AT_HEARTSND, type, 10, "+HEARTSND:", "hearttype");
}

atStatus atSetHeartType(char* type)
{
    _StdSetStringAndReturnOK(CMD_AT_HEARTSND, type);
}

atStatus atGetHeartTime(uint16_t* time)
{
    _StdGetU16(CMD_AT_HEARTTM, time, "+HEARTTM:", "hearttime");
}

atStatus atSetHeartTime(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_HEARTTM, time);
}

atStatus atGetHTTPDType(char* type)
{
    _StdGetString(CMD_AT_HTPTP, type, 10, "+HTPTP:", "httpd type");
}

atStatus atSetHTTPDType(char* type)
{
    _StdSetStringAndReturnOK(CMD_AT_HTPTP, type);
}

atStatus atGetHTTPDUrl(char* url)
{
    _StdGetString(CMD_AT_HTPURL, url, 120, "+HTPURL:", "httpd url");
}

atStatus atSetHTTPDUrl(char* url)
{
    _StdSetStringAndReturnOK(CMD_AT_HTPURL, url);
}

atStatus atGetHTTPDServerParm(char* parm)
{
    _StdGetString(CMD_AT_HTPSV, parm, 130, "+HTPSV:", "httpd serparam");
}

atStatus atSetHTTPDServerParm(char* parm)
{
    _StdSetStringAndReturnOK(CMD_AT_HTPSV, parm);
}


atStatus atGetHTTPDRequestHead(char* head)
{
    _StdGetString(CMD_AT_HTPHD, head, 220, "+HTPHD:", "httpd head");
}

atStatus atSetHTTPDRequestHead(char* head)
{
    _StdSetStringAndReturnOK(CMD_AT_HTPHD, head);
}

atStatus atGetHTTPDTimeout(uint16_t* time)
{
    _StdGetU16(CMD_AT_HTPTO, time, "+HTPTO:", "httpd timeout");
}

atStatus atSetHTTPDTimeout(uint16_t time)
{
    _StdSetU16AndReturnOK(CMD_AT_HTPTO, time);
}

atStatus atGetHTTPDFilterHeadEnable(char* enable)
{
    _StdGetString(CMD_AT_HTPFLT, enable, 5, "+HTPFLT:", "httpd filter");
}

atStatus atSetHTTPDFilterHeadEnable(char* enable)
{
    _StdSetStringAndReturnOK(CMD_AT_HTPFLT, enable);
}

atStatus atSendMessageSM(char* msg)
{
    _StdSetStringAndReturnOK(CMD_AT_SMSEND, msg);
}

atStatus atSendMessageCISMS(char* msg)
{
    _StdSetStringAndReturnOK(CMD_AT_CISMSSEND, msg);
}

atStatus atGetModbusEnable(char* enable)
{
    _StdGetString(CMD_AT_MODBUSEN, enable, 5, "+MODBUSEN:", "modbus enable");
}

atStatus atSetModbusEnable(char* enable)
{
    _StdSetStringAndReturnOK(CMD_AT_MODBUSEN, enable);
}

atStatus atGetCurrentTime(char* time)
{
    _StdGetString(CMD_AT_CCLK, time, 30, "+CCLK:", "time");
}
