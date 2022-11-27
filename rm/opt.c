#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "rmi.h"
#include "opt.h"

extern  char *inter;
struct flag_all *get_opt(int agc, const char **arv,
            const struct option *long_opts, int *optindex)
{
    int ch;
    struct flag_all *flags;
    flags = malloc(sizeof(*flag));
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
    flags->intter_flag = 0;
    flags->opt_ind = 0;
    while((ch = getopt_long(argc,argv,"fiIrRdvh",longopt,&longindex)) != -1)
    {
        switch(ch)
        {
            case '1':
                intter_flag = 1;
                if(optarg != NULL)
                    inter = optarg;
                break;
            case 'h':
                printf_help();
                exit(0);
            case 'f':
                fflag = 1;
                break;
            case 'o':
                oflag = 1;
                break;
            case 'r':
            case 'R':
                rflag = 1;
                break;
            case 'i':
                iflag = 1;
                break;
            case 'I':
                i_flag = 1;
                break;
            case 'd':
                dflag = 1;
                break;
            case 'v':
                vflag = 1;
                break;
            default :
                printf_help();
                exit(1);
        }
    }
    flags->opt_ind = optind;
    return flags;
}