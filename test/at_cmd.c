#include "elog.h"
#include "list.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"

// at指令解析
typedef struct at_cmd_t
{
    char *cmd;
    char *desc;
    int (*handler)(char *cmd, char *desc, char *result, int len);
} at_cmd_t;

// at指令列表
at_cmd_t at_cmd_list[] = 
{
    {"AT+NAME", "设置蓝牙名称", NULL},
    {"AT+PASS", "设置蓝牙密码", NULL},
    {"AT+POWER", "设置蓝牙开关", NULL},
    {"AT+PAIR", "配对蓝牙", NULL},
    {"AT+UNPAIR", "取消配对", NULL},
    {"AT+DEV", "获取已配对设备列表", NULL},
    {"AT+CONNECT", "连接蓝牙", NULL},
    {"AT+DISCONNECT", "断开蓝牙", NULL},
    {"AT+SEND", "发送数据", NULL},
    {"AT+RECV", "接收数据", NULL},
    {"AT+RSSI", "获取信号强度", NULL},
    {"AT+RESET", "重置蓝牙", NULL},
    {"AT+VERSION", "获取版本号", NULL},
    {"AT+TEST", "测试", NULL},
    {"AT+TEST2", "测试2", NULL},
    {"AT+TEST3", "测试3", NULL},
    {"AT+TEST4", "测试4", NULL},
    {"AT+TEST5", "测试5", NULL},
    {"AT+TEST6", "测试6", NULL},
    {"AT+TEST7", "测试7", NULL},
    {"AT+TEST8", "测试8", NULL},
    {"AT+TEST9", "测试9", NULL},
};

// at指令解析函数
int at_cmd_handler(char *cmd, char *desc, char *result, int len)
{
    int i;
    for(i = 0; i < sizeof(at_cmd_list)/sizeof(at_cmd_list[0]); i++)
    {
        if(strcmp(at_cmd_list[i].cmd, cmd) == 0)
        {
            if(at_cmd_list[i].handler)
            {
                return at_cmd_list[i].handler(cmd, desc, result, len);
            }
            else
            {
                return -1;
            }
        }
    }
    return -1;
}

typedef enum 
{
    AT_CMD_OK = 0,
    AT_CMD_ERROR,
    AT_CMD_TIMEOUT,
    AT_CMD_UNKNOWN,
} at_cmd_status_t;


#define str(s) #s

char *get_at_cmd_status(at_cmd_status_t status)
{
    switch(status)
    {
        case AT_CMD_OK:
            return str(AT_CMD_OK);
        case AT_CMD_ERROR:
            return str(AT_CMD_ERROR);
        case AT_CMD_TIMEOUT:
            return str(AT_CMD_TIMEOUT);
        case AT_CMD_UNKNOWN:
            return str(AT_CMD_UNKNOWN);
        default:
            return str(AT_CMD_UNKNOWN);
    }
    return str(AT_CMD_UNKNOWN);
}


int main(int argc, char const *argv[])
{
    // 初始化
    elog_init();
    log_i("%s",get_at_cmd_status(AT_CMD_OK));
}

// at指令解析
