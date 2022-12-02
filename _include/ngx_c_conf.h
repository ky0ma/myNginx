#ifndef __NGX_C_CONF_H__
#define __NGX_C_CONF_H__

#include <vector>
#include "ngx_global.h"

class Config
{
private:
    static Config *m_instance;
public:
    std::vector<LPConfitem> m_configItemVec;

public:
    Config();
    ~Config();

public:
    // 单例模式
    static Config* getInstance()
    {
        if(m_instance == nullptr)
        {
            if(m_instance == nullptr)
            {
                m_instance = new Config();
                static InstanceFree cl;
            }
        }
        return m_instance;
    }
    // 释放单例对象
    class InstanceFree
    {
    private:
        /* data */
    public:
        ~InstanceFree()
        {
            if(Config::m_instance)
            {
                delete Config::m_instance;
                Config::m_instance = nullptr;
            }
        }
    };    

public:
    bool load(const char* p_fileName);
    const char* getString(const char* p_itemName);
    int getIntDefault(const char* p_itemName, const int def);
};

#endif