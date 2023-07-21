#include <unistd.h>
#include "elog.h"
#include "list.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"

typedef struct
{
    char header[5];
    char separator;
    char separator_params;
} at_cmd_define_t;

// at指令解析
typedef struct at_cmd_t
{
    char *cmd;
    char *desc;
    int (*handler)(char *cmd, char *desc, char *result, int len);
} at_cmd_t;

typedef struct
{
#define AT_CMD_PARAMS_MAX_NUM 10
#define AT_CMD_SEPARATOR_HEADER '+'
#define AT_CMD_SEPARATOR_CMD    '='
#define AT_CMD_SEPARATOR_PARAMS ','

    char *header;
    char *cmd;
    char *params[AT_CMD_PARAMS_MAX_NUM];
    int params_num;
} at_cmd_parser_t;

at_cmd_t g_at_cmd;

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
    for (i = 0; i < sizeof(at_cmd_list) / sizeof(at_cmd_list[0]); i++)
    {
        if (strcmp(at_cmd_list[i].cmd, cmd) == 0)
        {
            if (at_cmd_list[i].handler)
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
    switch (status)
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

typedef struct
{
/* check if the given size is left to read in a given parse buffer (starting with 1) */
#define can_read(buffer, size) ((buffer != NULL) && (((buffer)->offset + size) <= (buffer)->length))
/* check if the buffer can be accessed at the given index (starting with 0) */
#define can_access_at_index(buffer, index) ((buffer != NULL) && (((buffer)->offset + index) < (buffer)->length))
#define cannot_access_at_index(buffer, index) (!can_access_at_index(buffer, index))
/* get a pointer to the buffer at the position */
#define buffer_at_offset(buffer) ((buffer)->content + (buffer)->offset)

    unsigned char *content;
    size_t length;
    size_t offset;
} parse_buffer_t;


char *at_cmd_parser_delim(parse_buffer_t *buffer, char delim)
{
    if (buffer == NULL && buffer->offset >= buffer->length)
    {
        return NULL;
    }

    char *ret = NULL;
    unsigned char *ptr = buffer_at_offset(buffer);
    int length;

    if(ptr != NULL)
    {
        // 截取剩余字符串 
        if(delim == '\0')
        {
            length = buffer->length - buffer->offset + 1;
            ret = malloc(length + sizeof(""));
            memcpy(ret, buffer_at_offset(buffer), length);
            ret[length] = '\0';
            buffer->offset += length + 1;
            return ret;
        }

        while (*ptr != '\0')
        {
            if (*ptr == delim)
            {
                length = ptr - buffer_at_offset(buffer);
                ret = malloc(length + sizeof(""));
                memcpy(ret, buffer_at_offset(buffer), length);
                //memcpy_s(ret, buffer_at_offset(buffer), length);
                ret[length] = '\0';
                buffer->offset += length + 1;
                return ret;
            }
            ptr++;
        }     
    }
    return NULL;
}

int at_cmd_parser(at_cmd_parser_t *parser, char *cmd_str)
{
    log_i("cmd_str:%s", cmd_str);
    parse_buffer_t buffer;
    int last_param_len;

    buffer.content = (unsigned char *)cmd_str;
    buffer.length = strlen(cmd_str);
    buffer.offset = 0;

    parser->header = at_cmd_parser_delim(&buffer, AT_CMD_SEPARATOR_HEADER);
    if (parser->header == NULL)
    {
        return -1;
    }

    parser->cmd = at_cmd_parser_delim(&buffer, AT_CMD_SEPARATOR_CMD);
    if (parser->cmd == NULL)
    {
        //if parse fail,the cmd with no params
        parser->cmd = at_cmd_parser_delim(&buffer, '\0');
        printf("%p\n",parser->cmd);
        if(parser->cmd)
        {
            parser->params_num = 0;
            return 0;
        }
        else{
            free(parser->header);
            return -1;
        }
    }

    for (int i = 0; i < AT_CMD_PARAMS_MAX_NUM; i++)
    {
        if ((parser->params[i] = at_cmd_parser_delim(&buffer, AT_CMD_SEPARATOR_PARAMS)) == NULL)
        {
            last_param_len = buffer.length - buffer.offset;
            parser->params[i] = malloc(last_param_len + sizeof(""));
            memcpy(parser->params[i], buffer_at_offset(&buffer), last_param_len);
            parser->params[i][last_param_len] = '\0';
            parser->params_num = i + 1;
            break;
        }

        parser->params_num = i + 1;
    }

    return 0;
}

void at_cmd_parser_free(at_cmd_parser_t *parser)
{
    if (parser->header)
    {
        free(parser->header);
    }
    if (parser->cmd)
    {
        free(parser->cmd);
    }
    for (int i = 0; i < parser->params_num; i++)
    {
        if (parser->params[i])
        {
            free(parser->params[i]);
        }
    }
}

int at_cmd_init()
{
    printf("at_cmd init\n");
}

void at_cmd_handle(at_cmd_parser_t *parser)
{
    if(parser->cmd == NULL)
    {
        return;
    }
    printf("at_cmd_handle:%s\n", parser->cmd);

}

int test_at_cmd_parser(char *cmd_str)
{
    int ret;
    
    at_cmd_parser_t parser;
    ret = at_cmd_parser(&parser, cmd_str);
    log_i("cmd str:%s",cmd_str);
    if (ret == 0)
    {
        log_i("header:%s", parser.header);
        log_i("cmd:%s", parser.cmd);
        log_i("params_num:%d", parser.params_num);
        for (int i = 0; i < parser.params_num; i++)
        {
            log_i("params[%d]:%s", i, parser.params[i]);
        }
        at_cmd_handle(&parser);
        at_cmd_parser_free(&parser);
    }
    else
    {
        log_e("parse error");
    }
}


typedef struct
{
#define MAX_PARAMS_COUNT 10
    char *params[MAX_PARAMS_COUNT];
    uint8_t count;
}params_parser_t;


void parse_params(params_parser_t *params_parser,char *params)
{
    char *p_start = params;
    char *p_end;
    params_parser->count = 0;
    int len;
    for(int i = 0; i < MAX_PARAMS_COUNT;i++)
    {
        p_end = strchr(p_start,',');
        params_parser->count = i + 1;
        if(p_end)
        {
            // parse spilter ',' and malloc memory store it
            len = p_end - p_start;
            params_parser->params[i] = malloc(len + 1);
            strncpy(params_parser->params[i],p_start,len);
            params_parser->params[i][len] = '\0';

            p_start = p_end + 1;
        }
        else
        {
            len = strlen(p_start);
            params_parser->params[i] = malloc(len + 1);
            strncpy(params_parser->params[i],p_start,len);
            params_parser->params[i][len] = '\0';
            break;
        }
    }
}

void test_parse_params(void)
{
    params_parser_t params_parser;
    parse_params(&params_parser,"1,2,3444444,4,,5,6,7,8,9,0");
    log_i("%d",params_parser.count);
    for(int i = 0;i < params_parser.count;i++)
    {
        log_i("params[%d]: %s",i,params_parser.params[i]);
    }
    
    parse_params(&params_parser,"1");
    log_i("%d",params_parser.count);
    for(int i = 0;i < params_parser.count;i++)
    {
        log_i("params[%d]: %s",i,params_parser.params[i]);
    }
    
    parse_params(&params_parser,"");
    
    log_i("%d",params_parser.count);
    for(int i = 0;i < params_parser.count;i++)
    {
        log_i("params[%d]: %s",i,params_parser.params[i]);
    }
}

#define str(s) #s
int main(int argc, char const *argv[])
{
    // 初始化
    elog_init();
    at_cmd_init();
    printf("%s \n", str(TEST1));
    test_parse_params();
    test_at_cmd_parser("AT+TEST=1,2,3,4,5,6,7,8,9,10,11");
    test_at_cmd_parser("AT+TEST=1,2,3,4,5,6,7,8,9,10");
    test_at_cmd_parser("AT+TEST=1,2,3,4,5,6,7,8,9");
    test_at_cmd_parser("AT+TEST=1,2,3,4,5,6,7,8");
    test_at_cmd_parser("AT+TEST=1,2,3,4,5,6,");
    test_at_cmd_parser("AT+TEST=1,2,3,4,5");
    test_at_cmd_parser("AT+TEST=1,2,3,4");
    test_at_cmd_parser("AT+TEST&&");
    test_at_cmd_parser("AT+TEST");
    test_at_cmd_parser("AT+TEST");
    test_at_cmd_parser("AT+BTEST");
    test_at_cmd_parser("TEST");
    sleep(100);
    for(int i = 0;i < 100000;i++)
    {
        test_at_cmd_parser("AT+B TEST 1,2,3,4,123,4224,2424,42,42,24,42,42");
        usleep(7000);
        //sleep(1);
    }
}