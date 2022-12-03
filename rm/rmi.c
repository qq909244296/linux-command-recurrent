#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "rmi.h"
#include <glob.h>




void printf_usage(void)
{
    
    fprintf(stderr,"usage...\n");
}
void printf_help(void)
{
    printf("-f, --force:ignore nonexistent files and arguments, never prompt.");
    printf("-i:prompt before every removal.");                                              
    printf("-I:prompt once before removing more than three files,");                        
    printf("or when removing recursively; less intrusive.");
    printf("than -i, while still giving protection against most mistakes.");
    printf("--interactive[=WHEN]:prompt according to WHEN: never, once");                   
    printf("(-I), or always (-i); without WHEN, prompt always.");
    printf("--one-file-system:when  removing  a  hierarchy recursively,");
    printf("skip any directory that is on a file system different");                       
    printf("from that of the corresponding command line argument.");
    printf("--no-preserve-root:do not treat '/' specially.");                               
    printf("--preserve-root[=all]:do not remove '/'");                                     
    printf("(default); with 'all'");                                                               
    printf("reject any command line argument on a separate  device") ;                   
    printf("from its parent.");                                                             
    printf("-r, -R, --recursive:remove directories and their");              
    printf("contents recursively.");                                              
    printf("-d, --dir:remove empty directories.");                                          
    printf("-v, --verbose:explain what is being done.");
    printf("--help:display this help and exit.\n");
}
void printf_err(int err)
{
    fprintf(stderr,"%s\n",strerror(err));
}



int statDir(char *agv,struct stat *stat_buf,int fflag)
{
    int reval;
    if(stat(agv, stat_buf) < 0)
    {
        if(fflag == 0)
            printf_err(errno);
        return -1;
    }
    return 0;
}
int noloop(const char *path)
{
    
    char *path1 = path;
    char *pos;
    if(path1 == NULL)
    {
        exit(1);
    }
    puts(path);
    pos = strrchr(path,'/');
    if(strcmp(pos+1,".") ==0 || strcmp(pos+1,"..") == 0)
    {
        return 1;
    }
    return 0;
}
int reMovempty(char *path)
{
    struct stat statres;
    if(lstat(path,&statres) < 0)
    {
        exit(1);
    }
    if(!S_ISDIR(statres.st_mode))
    {
        remove(path);
        return 0;
    }
    int retr;
    if(S_ISDIR(statres.st_mode))
    {
        retr = remove(path);
    }
    if(errno ==ENOTEMPTY)
    {    
    char newpath[256];
    int i;
    int err1;
    glob_t globres;
    
    strcpy(newpath,path);
    strcat(newpath,"/*");
    int ret;

    glob(newpath,0,NULL,&globres);
    strcpy(newpath,path);
    strcat(newpath,"/.*");
    glob(newpath,GLOB_APPEND,NULL,&globres);
    for(i=0;i<globres.gl_pathc;i++)
    {
        if(!noloop(globres.gl_pathv[i]))
        {           
            err1 = remove(globres.gl_pathv[i]);
            if(err1)
            {   
                  
                if(errno == ENOTEMPTY)
                {
                    
                    ret = reMovempty(globres.gl_pathv[i]);
                    if(ret)
                    {
                        return errno;
                    }
                    else
                    {
                        printf("%s is remove\n",globres.gl_pathv[i]);
                    }
                }
                else
                {
                    fprintf(stderr,"[%s] %s\n",globres.gl_pathv[i],strerror(errno));
                    return errno;
                }
            }
            else
            {
                printf("%s is  remove\n",globres.gl_pathv[i]);
            }
        }
        remove(path);
        
        
    }

    }
    return 0;
}

int reMove(char *path)
{
    char *dirname = path;
    int err,ret;
    err = remove(path);
    if(err)
    {
        if(errno == ENOTEMPTY)
        {
            
            ret = reMovempty(path);
            if(ret)
            {
                return errno;
            }
            else
            {
                printf("%s is removed\n",path);

            }
        }
        else
            return errno;
    }
    return 0;
    
    
}

int mind_r(int flag_r,char *arg)
{   
    int std_c;
    if(flag_r)
    {
        printf("rm: remove r '%s'\n",arg);//到底输出什么还要再测试
        std_c = fgetc(stdin);
        if((char)std_c == 'y' || (char)std_c == 'Y')
        {
             return 1;
                //do something
        }
        else if((char)std_c == 'N'|| (char)std_c == 'n')
            {
                return 0;
                    //not do something
            }
            else
            {
                return 0;
                    //not do something
            }
        
    }
    else
    {
        return 2;
    }
}