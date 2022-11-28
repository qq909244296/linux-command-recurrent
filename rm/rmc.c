#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "rmi.h"
#include "opt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



int main(int argc, char *agrv)
{

    if(argc < 2)
    {
        printf_usage();
    }
    
    struct flag_all *flags;
    struct stat statbuf;
    
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
    if(argc == 0)
    {
        printf_usage();
    }
    for(i=0;i<argc;i++)
    {
        // if(flags->iflag)
        // {
        //     printf("rm: remove r '%s'\n",agrv[i]);//到底输出什么还要再测试
        //     std_c = fgetc(stdin);
        //     if((char)std_c == 'y' || (char)std_c == "Y")
        //     {
        //         //do something
        //     }
        //     else if((char)std_c == 'N'|| (char)std_c == 'n')
        //         {
        //             //not do something
        //         }
        //         else
        //         {
        //             //not do something
        //         }
        
        // }
        if(flags->rflag)
        {

        }









    }
    exit(0);
}