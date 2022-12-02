#include<stdio.h>
#include<string.h>

#include "ngx_c_conf.h"
#include "ngx_func.h"

Config *Config::m_instance = nullptr;

Config::Config()
{
}

// 析构，释放存储配置的容器
Config::~Config()
{
    while (!m_configItemVec.empty())
    {
        delete m_configItemVec.back();
        m_configItemVec.pop_back();
    }
}

bool Config::load(const char* p_fileName)
{
    FILE *fp;
    fp = fopen(p_fileName, "r");

    // 打开文件失败
    if(fp == NULL)
        return false;

    char buf[500];
    while (!feof(fp))
    {
        if(fgets(buf, 500, fp) == NULL)
            continue;
        if(buf[0] == 0)
            continue;
        if(buf[0] == '#' || *buf == ';' || *buf == '\t' || *buf == '\n')
            continue;
        if(buf[0] == '[')
            continue;
        // 对每一行进行处理
        char *p_tmp = strchr(buf, '=');
        if(p_tmp != NULL)
        {
            LPConfitem p_configItem = new ConfItem;
            memset(p_configItem, 0, sizeof(ConfItem));
            // 先将值拷贝到item里面
            strncpy(p_configItem->itemName, buf, (int)(p_tmp - buf));
            strcpy(p_configItem->itemVal, p_tmp + 1);
            // 再在item中修剪
            strTrim(p_configItem->itemName);
            strTrim(p_configItem->itemVal);

            m_configItemVec.push_back(p_configItem);
        }
    }
    fclose(fp);    
    return true;
}