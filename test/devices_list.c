#include "elog.h"
#include "list.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"

typedef void (*cmd_timeout_handler)(void);

typedef struct 
{
    char name[32];
    uint8_t bd_addr[6];
}dev_info_t;

void dev_info_list_free_handler(void *data)
{
    dev_info_t *dev_info = (dev_info_t *)data;
    free(dev_info);
}

bool get_device_info(void *data,void *context)
{
    dev_info_t *dev_info = data;
    assert(data);
    log_i("name:%s",dev_info->name);
    log_hexdump("dev info",dev_info->bd_addr,6);   
    return true;
}

list_t *paired_dev_list;

bool change_dev_seq(void *data,void *context)
{
    char *dev_name = context;
    log_i("dev name:%s",dev_name);
    dev_info_t *dev_info = data;
    if(strcmp(dev_info->name,dev_name) == 0)
    {
        log_i("change seq");
        list_delete(paired_dev_list,data);
        list_prepend(paired_dev_list,data);
    
        //return false;
    }

    return true;
}


void list_test(list_t **paired_dev_list)
{
    *paired_dev_list = list_new(dev_info_list_free_handler);
    
    dev_info_t bd_addr1 = {"dev1",{1,1,1,1,1,1}};
    dev_info_t bd_addr2 = {"dev2",{2,1,1,1,1,1}};
    dev_info_t bd_addr3 = {"dev3",{3,1,1,1,1,1}};
    dev_info_t bd_addr4 = {"dev4",{4,1,1,1,1,1}};
    dev_info_t bd_addr5 = {"dev5",{5,1,1,1,1,1}};

    dev_info_t *dev1 = malloc(sizeof(dev_info_t));
    dev_info_t *dev2 = malloc(sizeof(dev_info_t));
    dev_info_t *dev3 = malloc(sizeof(dev_info_t));
    dev_info_t *dev4 = malloc(sizeof(dev_info_t));
    dev_info_t *dev5 = malloc(sizeof(dev_info_t));
    
    memcpy(dev1,&bd_addr1,sizeof(dev_info_t));
    memcpy(dev2,&bd_addr2,sizeof(dev_info_t));
    memcpy(dev3,&bd_addr3,sizeof(dev_info_t));
    memcpy(dev4,&bd_addr4,sizeof(dev_info_t));
    memcpy(dev5,&bd_addr5,sizeof(dev_info_t));

    list_append(*paired_dev_list,dev1);
    list_append(*paired_dev_list,dev2);
    list_append(*paired_dev_list,dev3);
    list_append(*paired_dev_list,dev4);
    list_append(*paired_dev_list,dev5);
}

void write_file(char *path,char *data)
{
    FILE *fp = fopen(path,"w");
    if(fp == NULL)
    {
        log_e("open file failed");
        return;
    }
    log_i("len:%d",strlen(data));
    fwrite(data,strlen(data),1,fp);
    fclose(fp);
}

//read_file

void read_file(char *path,char *buf)
{
    FILE *fp = fopen(path,"r");
    if(fp == NULL)
    {
        log_e("open file failed");
        return;
    }
    fread(buf,1,1024,fp);
    int size = ftell(fp);
    log_i("size:%d",size);
    buf[size] = '\0';
    fclose(fp);
}

// read file to buf
void read_file_to_buf(char *path,char *buf,int size)
{
    FILE *fp = fopen(path,"r");
    if(fp == NULL)
    {
        log_e("open file failed");
        return;
    }
    fread(buf,1,size,fp);
    int len = ftell(fp);
    log_i("len:%d",len);
    buf[len] = '\0';
    fclose(fp);
}


// addr_str to array
void addr_str_to_array(char *addr_str,uint8_t *addr)
{
    char *p = addr_str;
    int i = 0;
    while(*p != '\0')
    {
        if(*p == ':')
        {
            p++;
            continue;
        }
        addr[i] = strtol(p,&p,16);
        i++;
    }
}

void parse_json(char *json_str)
{
    //char *json_str;
    //read_file("paired_dev.json",json_str);
    log_i("%s len:%d",json_str,strlen(json_str));
    log_hexdump("json_str",json_str,strlen(json_str));
    cJSON *root = cJSON_Parse(json_str);
    if(root == NULL)
    {
        log_e("parse json failed");
        return;
    }
    cJSON *dev_list = cJSON_GetObjectItem(root,"dev_list");
    int dev_num = cJSON_GetArraySize(dev_list);
    log_i("dev num:%d",dev_num);
    
    //
    paired_dev_list = list_new(dev_info_list_free_handler);
    for(int i = 0;i < dev_num;i++)
    {
        cJSON *dev = cJSON_GetArrayItem(dev_list,i);
        cJSON *name = cJSON_GetObjectItem(dev,"name");
        cJSON *bd_addr = cJSON_GetObjectItem(dev,"bd_addr");
        log_i("name:%s",name->valuestring);
        log_i("bd_addr:%s",bd_addr->valuestring);

        dev_info_t *paired_dev_info = malloc(sizeof(dev_info_t));
        uint8_t bd_addr_array[6];
        addr_str_to_array(bd_addr->valuestring,bd_addr_array);
        strncpy(paired_dev_info->name,name->valuestring,sizeof(paired_dev_info->name) - 1);
        memcpy(paired_dev_info->bd_addr,bd_addr_array,6);
        list_append(paired_dev_list,paired_dev_info);
    }
    cJSON_Delete(root);
}

//is file exist
bool is_file_exist(char *path)
{
    FILE *fp = fopen(path,"r");
    if(fp == NULL)
    {
        return false;
    }
    fclose(fp);
    return true;
}

void create_default_paired_dev(void)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *dev_list = cJSON_CreateArray();
    cJSON_AddItemToObject(root,"dev_list",dev_list);
    cJSON *dev1 = cJSON_CreateObject();
    cJSON_AddItemToArray(dev_list,dev1);
    cJSON_AddStringToObject(dev1,"name","dev1");
    cJSON_AddStringToObject(dev1,"bd_addr","01:01:01:01:01:01");
    cJSON *dev2 = cJSON_CreateObject();
    cJSON_AddItemToArray(dev_list,dev2);
    cJSON_AddStringToObject(dev2,"name","dev2");
    cJSON_AddStringToObject(dev2,"bd_addr","02:01:01:01:01:01");
    cJSON *dev3 = cJSON_CreateObject();
    cJSON_AddItemToArray(dev_list,dev3);
    cJSON_AddStringToObject(dev3,"name","dev3");
    cJSON_AddStringToObject(dev3,"bd_addr","03:01:01:01:01:01");
    cJSON *dev4 = cJSON_CreateObject();
    cJSON_AddItemToArray(dev_list,dev4);
    cJSON_AddStringToObject(dev4,"name","dev4");
    cJSON_AddStringToObject(dev4,"bd_addr","04:01:01:01:01:01");
    cJSON *dev5 = cJSON_CreateObject();
    cJSON_AddItemToArray(dev_list,dev5);
    cJSON_AddStringToObject(dev5,"name","dev5");
    cJSON_AddStringToObject(dev5,"bd_addr","05:01:01:01:01:01");
    log_i("%s",cJSON_Print(root));
    if(!is_file_exist("paired_dev.json"))
    {
        //remove("paired_dev.json");
        write_file("paired_dev.json",cJSON_Print(root));
    }
    cJSON_Delete(root);
}



void paired_dev_init(void)
{
    create_default_paired_dev();
    char json_str[1024];
    read_file("paired_dev.json",json_str);
    parse_json(json_str);
    //list_test(&paired_dev_list);
}

int main(int argc, char const *argv[])
{
    elog_init();
    log_i("this is a device list");

    char input_data[128];

    paired_dev_init();
    list_foreach(paired_dev_list,get_device_info,NULL);
    scanf("%s",input_data);
    log_hexdump("input data",input_data,strlen(input_data));
    list_foreach(paired_dev_list,change_dev_seq,input_data);
    
    list_foreach(paired_dev_list,get_device_info,input_data);
    // test commit
}