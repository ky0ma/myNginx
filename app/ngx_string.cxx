
#include "ngx_func.h"

bool isValid(const char c)
{
    if(c == ' ' || c == '\t' || c == '\n')
        return false;
    return true;
}

char* strTrim(char* str)
{
    size_t len = strlen(str);
    for(int i = len - 1; i >= 0; i--)
    {
        if(!isValid(str[i]))
            str[i] = '\0';
        else
            break;
    }
    char* ptmp = str;
    while (*ptmp != '\0' && !isValid(*ptmp))
        ptmp++;
    return ptmp;
}