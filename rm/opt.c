#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "rmi.h"
#include "opt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
char *in_er={"i\0"};
struct flag_all *flags;
struct flag_all *get_opt(int agc, char **agv)
{
    int ch;
    
    flags = malloc(sizeof(*flags));
    if(flags == NULL)
    {
        fprintf(stderr,"malloc() failure.\n");
        return NULL;
    }
    flags->oflag = 0;
    flags->fflag = 0;
    flags->rflag = 0;
    flags->dflag = 0;
    flags->vflag = 0;
    flags->i_flag = 0;
    flags->iflag = 0;
    flags->inter_flag = 0;
    flags->opt_ind = 0;
    struct option longopt[] = {{"force",0,0,'f'}, {"interactive",0,0,'1'},
                            {"one-file-system",0,0,'o'},{"no-preserve-root",0,0,'n'},
                            {"recursive",0,0,'r'},{"dir",0,0,'d'},{"verbose",0,0,'v'},
                            {"help",0,0,'h'},{0,0,0,0}};
    int longindex = 8;
    while((ch = getopt_long(agc,agv,"fiIrRdvh",longopt,&longindex)) != -1)
    {
        switch(ch)
        {
            case '1':
                flags->inter_flag = 1;
                if(optarg != NULL)
                    in_er = optarg;
                break;
            case 'h':
                printf_help();
                exit(0);
            case 'f':
                flags->fflag = 1;
                break;
            case 'o':
                flags->oflag = 1;
                break;
            case 'r':
            case 'R':
                flags->rflag = 1;
                break;
            case 'i':
                flags->iflag = 1;
                break;
            case 'I':
                flags->i_flag = 1;
                break;
            case 'd':
                flags->dflag = 1;
                break;
            case 'v':
                flags->vflag = 1;
                break;
            default :
                printf_help();
                exit(1);
        }
    }
    if((flags->iflag ==1 && flags->i_flag ==1))
    {
        flags->i_flag = 0;
    }
    if(flags->iflag ==1 && flags->fflag == 1)
    {
        flags->fflag = 0;
    }
    if(flags->iflag == 0&&flags->fflag ==1 && flags->i_flag ==1)
    {
        flags->fflag = 1;
    }
    flags->opt_ind = optind;
    return flags;
}