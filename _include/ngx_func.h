#ifndef __NGX_FUNC__
#define __NGX_FUNC__

#include <stdio.h>
#include <string.h>

// 字符串修剪
char* strTrim(char* str);

void ngx_init_setproctitle();
void ngx_setproctitle(const char* title);


#endif