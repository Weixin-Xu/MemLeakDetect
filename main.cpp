#include <cstdio>
#include <cstdlib>
#include <cstring>
//#include "MemDebug.h"

#include <new>

int main()
{
    char * p = new char;

    char *str = (char *) malloc (sizeof(char) * 4);

    free(p);

    char *p2 = new (std::nothrow) char;
    char *p3 = new (sizeof(char) * 10, std::nothrow);
    return 0;
}
