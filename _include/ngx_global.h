#ifndef __NGX_GLOBAL_H__
#define __NGX_GLOBAL_H__

// 保存config信息的结构体
typedef struct 
{
    char itemName[50];
    char itemVal[500];
}ConfItem, *LPConfitem;

//外部全局量声明
extern char  **g_os_argv;   // 保存argv
extern char  *gp_envmem;    // 保存环境变量
extern int   g_environlen;  // 环境变量长度

#endif