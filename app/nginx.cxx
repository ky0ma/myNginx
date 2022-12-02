#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "ngx_c_conf.h"
#include "ngx_func.h"

using namespace std;

char **g_os_argv;            //原始命令行参数数组,在main中会被赋值
char *gp_envmem = NULL;      //指向自己分配的env环境变量的内存
int  g_environlen = 0;       //环境变量所占内存大小

int main(int argc, char *const *argv)
{

    // 读取配置文件
    Config *p_config = Config::getInstance();
    if(p_config->load("nginx.conf") == false)
    {
        printf("load configuration file failed !\n");
        exit(1);
    }

    // // 文件读取测试
    // cout<<p_config->m_configItemVec.size()<<endl;
    // for(int i = 0; i < p_config->m_configItemVec.size(); i++)
    // {
    //     cout<<i<<" "<<p_config->m_configItemVec[i]->itemName<<" = "
    //         << p_config->m_configItemVec[i]->itemVal<<endl;
    // }

    // ----------------------设置进程名称------------------------
    // 保存指向argv的指针
    g_os_argv = (char **) argv;
    // 设置进程标题
    ngx_init_setproctitle();    // 将环境变量存放到另外的位置
    ngx_setproctitle("myNginx: master");
    // ---------------------------------------------------------

    while(1)
    {
        sleep(10);
        cout<<"sleep 10s"<<endl;
    }


    printf("hello world!\n");
    return 0;
}


