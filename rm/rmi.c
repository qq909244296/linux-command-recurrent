#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/tyeps.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "rmi.h"




void printf_usage(void)
{
    
    fprintf(stderr,"usage...\n");
}
void printf_help(void)
{
    printf("")
}
void printf_err(int err)
{
    fprintf(stderr,"%s\n",strerror(err));
}



int statDir(char *agv,struct stat *stat_buf)
{
    int reval;
    if(stat(agv, stat_buf) < 0)
    {
        printf_err(errno);
    }
    
}