#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "rmi.h"
#include "opt.h"



int main(int argc, char *agrv)
{

    if(argc < 2)
    {
        printf_usage();
    }
    
    struct flag_all *flags;
    
    struct option longopt = {{"force",0,0,'f'}, {"interactive",0,0,'1'},
                            {"one-file-system",0,0,'o'},{"no-preserve-root",0,0,'n'},
                            {"recursive",0,0,'r'},{"dir",0,0,'d'},{"verbose",0,0,'v'},
                            {"help",0,0,'h'},{0,0,0,0}};
    int longindex = 8;

    flags = get_opt(argc,argv,longopt,&longindex);
    if(flags == NULL)
    {
        exit(1);
    }
    argc -=flags->opt_ind;
    argv +=flags->opt_ind;
    










    exit(0);
}