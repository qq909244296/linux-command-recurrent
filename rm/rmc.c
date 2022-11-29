#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "rmi.h"
#include "opt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



int main(int argc, char **argv)
{

    if(argc < 2)
    {
        printf_usage();
    }
    
    struct flag_all *flags;
    struct stat statbuf;
    int err,i;
    int mind_ret;


    flags = get_opt(argc,argv);
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

        if(statDir(argv[i],&statbuf))
        {
            exit(1);
        }
        if(S_ISDIR(statbuf.st_mode))
        {
            if(flags->rflag)
            {
                mind_ret = mind_r(flags->iflag,argv[i]);
                if(mind_ret)
                {
                
                    err = reMove(argv[i]);
                    if(err)
                    {
                        if(flags->fflag == 0)
                            printf_err(err);
                    }
                }
                else
                {
                    exit(0);
                }
            }
            else
            {
                fprintf(stderr,"cannot remove '%s': Is a directory\n",argv[i]);
            }
        }
        else if(S_ISREG(statbuf.st_mode))
            {
                err = reMove(argv[i]);
                if(err)
                {
                    if(flags->fflag == 0)
                        printf_err(err);
                }

            }
            else
            {
                if(flags->fflag == 0)
                {
                    fprintf(stderr,"rm: cannot remove '%s':             \
                                No such file or directory",argv[i]);
                }
            }
        

    }
    exit(0);
}