#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "rmi.h"
#include <glob.h>

struct flag_all *flags;


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

int findempty(char *path)
{
    int i;
    char newpath[256];
    glob_t globres;
    strcpy(newpath,path);
    strcat(newpath,"/*");
    glob(newpath,0,NULL,&globres);
    strcpy(newpath,path);
    strcat(newpath,"/.*");
    glob(newpath,GLOB_APPEND,NULL,&globres);
    if(globres.gl_pathc > 2)
    {
        //dir not empty
        return 1;
    }
    else
    {
        //dir is empty
        return 0;
    }
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
 
    pos = strrchr(path,'/');
    if(strcmp(pos+1,".") ==0 || strcmp(pos+1,"..") == 0)
    {
        return 1;
    }
    return 0;
}
int re_move(const int arc,const char **arv)
{
    int i,err1,ret,mind_ret;
    for(i=0;i<arc;i++)
    {
        if(!noloop(arv[i]))
        {        
           
            mind_ret = mind_r(flags->iflag,arv[i]);   
            if(mind_ret)
                exit(0);
            err1 = remove(arv[i]);

            if(err1)
            {        
                if(errno == ENOTEMPTY)
                {
                    
                    ret = reMovempty(arv[i]);
                    if(ret)
                    {
                        return errno;
                    }
                    else
                    {
                        printf("%s is remove\n",arv[i]);
                    }
                }
                else
                {
                    fprintf(stderr,"[%s] %s\n",arv[i],strerror(errno));
                    return errno;
                }
            }
            else
            {
                printf("%s is  remove\n",arv[i]);
            }
        }
        
        
    }

}
void glob_(char *path)
{
    char newpath[256];
    glob_t globres;
    strcpy(newpath,path);
    strcat(newpath,"/*");
    glob(newpath,0,NULL,&globres);
    strcpy(newpath,path);
    strcat(newpath,"/.*");
    glob(newpath,GLOB_APPEND,NULL,&globres);
    
    re_move(globres.gl_pathc,globres.gl_pathv);
    
}
int reMovempty(char *path)
{
    struct stat statres;
    int retr,mind_ret;
   
    if(lstat(path,&statres) < 0)
    {
        
        exit(1);
    }
    if(!S_ISDIR(statres.st_mode))
    {
      
        mind_ret = mind_r(flags->iflag,path);
        if(mind_ret)
            exit(1);
        remove(path);
        return 0;
    }
    
    // if(S_ISDIR(statres.st_mode))
    // {
    //     printf("iii\n");
    //     mind_r(flags->iflag,path);
    //     retr = remove(path);
    //     if(retr)
    // }
    // if(errno ==ENOTEMPTY)
    // {   
    glob_(path);
 
    mind_ret = mind_r(flags->iflag,path);
    if(mind_ret)
        exit(0);
    remove(path);       
    //}
    return 0;
}

int reMove(char *path)
{
    char *dirname = path;
    int err,ret,mind_ret;
    mind_ret = mind_r(flags->iflag,path);
    if(mind_ret)
        exit(1);
    
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
    char std_c=0;
    int ret;
    if(flag_r)
    {
        ret = findempty(arg);
        if(ret == 0)
        {
            printf("rm: remove r '%s'?",arg);//到底输出什么还要再测试/*  */
        }
        else
        {
            printf("rm: descend into directory '%s'?",arg);
            
        }
        //std_c = fgetc(stdin);
        printf("y/n:\n");
        scanf("%c\n",&std_c);
       
        while(std_c == 0)
        {

        }
        
        if(std_c == 'y' || std_c == 'Y')
        {
            
             return 0;
                //do something
        }
        else if((char)std_c == 'N'|| (char)std_c == 'n')
            {
                return 1;
                    //not do something
            }
            else
            {
                //yprintf("   %c\n",std_c);
            
                return 2;
                    //not do something
            }
        
    }
    else
    {
        return 0;
    }
}
int mind_i(int i_flag)
{
    char std_c;
    if(i_flag == 1)
    {
        printf("rm: remove 1 argument recursively?");
        scanf("%c\n",&std_c);
        while(std_c == 0)
        {

        }
        
        if(std_c == 'y' || std_c == 'Y')
        {
            
             return 0;
                //do something
        }
        else if((char)std_c == 'N'|| (char)std_c == 'n')
            {
                return 1;
                    //not do something
            }
            else
            {
                //yprintf("   %c\n",std_c);
            
                return 2;
                    //not do something
            }
        
    }
    else
    {
        return 0;
    }
        
    

}