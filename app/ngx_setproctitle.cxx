#include <stdlib.h>
#include <unistd.h>  //env
#include "ngx_func.h"
#include "ngx_global.h"

// 把环境变量和argv移动到新内存中去
void ngx_init_setproctitle()
{
    // g_environlen 全局变量，记录环境变量长度
    for(int i = 0; environ[i]; i++)
        g_environlen += strlen(environ[i]) + 1; // +1因为末尾有\0
    
    // 申请空间，将环境变量放入
    gp_envmem = new char[g_environlen];
    memset(gp_envmem, 0, g_environlen);

    // 将环境变量拷贝到新内存中
    char* ptmp = gp_envmem;
    for (int i = 0; environ[i]; i++)
    {
        strcpy(ptmp, environ[i]);
        environ[i] = ptmp;
        ptmp += strlen(environ[i]) + 1;
    }
}


void ngx_setproctitle(const char* title)
{
    // 计算原有内存大小 argv + environ 的大小
    size_t memLen = g_environlen;
    for(int i = 0; g_os_argv[i]; i++)
        memLen += strlen(g_os_argv[i]) + 1;

    // 新标题大小
    size_t titelLen = strlen(title);

    if(titelLen >= memLen)  // 标题过长，设置失败 
        return;
    
    // 设置argv[0]之后的内容都为空
    g_os_argv[1] = NULL;

    char *ptmp = *g_os_argv;
    memset(ptmp, 0, memLen);
    strcpy(ptmp, title);
}