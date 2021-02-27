#ifndef _ATCMD_H_
#define _ATCMD_H_

#define CMD_AT                      "AT"                //测试指令
#define CMD_AT_H                    "AT+H"              //帮助指令
#define CMD_AT_Z                    "AT+Z"              //重启模块
#define CMD_AT_REBOOT               "AT+REBOOT"         //重启模块系统
#define CMD_AT_E                    "AT+E"              //查询/设置 AT 指令回显
#define CMD_AT_ENTM                 "AT+ENTM"           //退出临时 AT 指令模式
#define CMD_AT_WKMOD                "AT+WKMOD"          //查询/设置模块工作模式
#define CMD_AT_CMDPW                "AT+CMDPW"          //设置/查询串口指令密码
#define CMD_AT_STMSG                "AT+STMSG"          //设置/查询开机信息
#define CMD_AT_RSTIM                "AT+RSTIM"          //设置/查询无数据重启时间
#define CMD_AT_CSQ                  "AT+CSQ"            //查询信号强度
#define CMD_AT_SYSINFO              "AT+SYSINFO"        //查询设备网络信息
#define CMD_AT_SYSCONFIG            "AT+SYSCONFIG"      //设置命令设置系统模式、网络接入次序、漫游支持和 domain 等特性。
#define CMD_AT_ZVERSION             "AT+ZVERSION"       //查询内部软件版本号
#define CMD_AT_FOTATIME             "AT+FOTATIME"       //查询/设置 fota 升级轮询时间
#define CMD_AT_SHELL                "AT+SHELL"          //执行 Shell 指令，主要用于执行 linux下的命令操作
#define CMD_AT_RELD                 "AT+RELD"           //恢复出厂设置
#define CMD_AT_CLEAR                "AT+CLEAR"          //恢复出厂设置
#define CMD_AT_VER                  "AT+VER"            //查询固件版本号
#define CMD_AT_SN                   "AT+SN"             //查询模块 SN 码
#define CMD_AT_ICCID                "AT+ICCID"          //读取 ICCID
#define CMD_AT_IMEI                 "AT+IMEI"           //读取 IMEI
#define CMD_AT_LBS                  "AT+LBS"            //查询基站定位信息
#define CMD_AT_LOCIP                "AT+LOCIP"          //查询本地 IP 地址
#define CMD_AT_UART                 "AT+UART"           //设置/查询串口参数
#define CMD_AT_UARTFT               "AT+UARTFT"         //设置/查询打包时间
#define CMD_AT_UARTFL               "AT+UARTFL"         //设置/查询打包长度
#define CMD_AT_APN                  "AT+APN"            //设置/查询 APN 码
#define CMD_AT_SOCKA                "AT+SOCKA"          //设置/查询 socketA 参数
#define CMD_AT_SOCKB                "AT+SOCKB"          //设置/查询 socketB 参数
#define CMD_AT_SOCKAEN              "AT+SOCKAEN"        //设置/查询 socketA 使能
#define CMD_AT_SOCKBEN              "AT+SOCKBEN"        //设置/查询 socketB 使能
#define CMD_AT_KEEPALIVEA           "AT+KEEPALIVEA"     //设置/查询 SOCKA keepalive 参数
#define CMD_AT_KEEPALIVEB           "AT+KEEPALIVEB"     //设置/查询 SOCKB keepalive 参数
#define CMD_AT_SOCKASL              "AT+SOCKASL"        //设置/查询 socketA TCP 连接方式
#define CMD_AT_SOCKBSL              "AT+SOCKBSL"        //设置/查询 socketB TCP 连接方式
#define CMD_AT_SOCKALK              "AT+SOCKALK"        //查询 socketA 连接状态
#define CMD_AT_SOCKBLK              "AT+SOCKBLK"        //查询 socketB 连接状态
#define CMD_AT_SOCKATO              "AT+SOCKATO"        //设置/查询 socketA 超时重连时间
#define CMD_AT_SOCKBTO              "AT+SOCKBTO"        //设置/查询 socketB 超时重连时间
#define CMD_AT_SHORATO              "AT+SHORATO"        //设置/查询 socketA 短连接超时时间
#define CMD_AT_SHORBTO              "AT+SHORBTO"        //设置/查询 socketB 短连接超时时间
#define CMD_AT_SOCKIND              "AT+SOCKIND"        //设置/查询指示透传数据来源 socket 使能
#define CMD_AT_SDPEN                "AT+SDPEN"          //设置/查询套接字使能
#define CMD_AT_SOCKRSTIM            "AT+SOCKRSTIM"      //设置/查询套接字使能
#define CMD_AT_REGEN                "AT+REGEN"          //设置/查询注册包使能
#define CMD_AT_REGTP                "AT+REGTP"          //设置/查询注册包类型
#define CMD_AT_REGDT                "AT+REGDT"          //设置/查询注册包内容
#define CMD_AT_REGSND               "AT+REGSND"         //设置/查询注册方式
#define CMD_AT_CLOUD                "AT+CLOUD"          //设置/查询透传云参数
#define CMD_AT_ID                   "AT+ID"             //查询/设置 UDC 模式下设备 ID
#define CMD_AT_HEARTEN              "AT+HEARTEN"        //设置/查询心跳包使能
#define CMD_AT_HEARTDT              "AT+HEARTDT"        //设置/查询心跳包内容
#define CMD_AT_HEARTSND             "AT+HEARTSND"       //设置/查询心跳方式
#define CMD_AT_HEARTTM              "AT+HEARTTM"        //设置/查询心跳时间
#define CMD_AT_HTPTP                "AT+HTPTP"          //设置/查询 HTTPD 请求方式
#define CMD_AT_HTPURL               "AT+HTPURL"         //设置/查询 HTTPD 请求 URL
#define CMD_AT_HTPSV                "AT+HTPSV"          //设置/查询 HTTPD 服务器参数
#define CMD_AT_HTPHD                "AT+HTPHD"          //设置/查询 HTTPD 请求包头
#define CMD_AT_HTPTO                "AT+HTPTO"          //设置/查询 HTTPD 超时断开时间
#define CMD_AT_HTPFLT               "AT+HTPFLT"         //设置/查询 HTTPD 回复信息过滤包头使能
#define CMD_AT_SMSEND               "AT+SMSEND"         //发送短信息
#define CMD_AT_CISMSSEND            "AT+CISMSSEND"      //发送短信息
#define CMD_AT_MODBUSEN             "AT+MODBUSEN"       //查询/设置是否使能 Modbus 协议转换功能。
#define CMD_AT_CCLK                 "AT+CCLK"           //查询基站当前时间

#endif
