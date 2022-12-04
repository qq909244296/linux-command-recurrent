/**
 * @copyright Copyright (c) 2022 Jiawshi
 * @author    Jiawshi (jiawshi@126.com)
 * 
 * @file      rmi.c
 * @brief     
 * 
 * @version   V0.01
 * @date      2022-12-04
 * 
 * @note      历史记录 ：
 *            - [2022-12-04] [Jiawshi] 创建初始版本：
 * @warning         在这个程序中有一些exit(0),或者exit(1),这个是可以被return一个非零值优化的，   
 * @par       修改记录： 
 * <table>
 * <tr><th>date          <th>Version    <th>Author      <th>Description    </tr>
 * <tr><td>2022-12-04    <td>V0.01      <td>Jiawshi       <td>创建初始版本    </tr>
 * </table>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "rmi.h"
#include <glob.h>

struct flag_all *flags;//全局变量，来自于opt.h


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
/**
 * @fn        findempty
 * @brief     验证当前目录是否为空目录
 * 
 * @param     [in] path      目录
 * 
 * @return    int            0为空目录，1为非空目录
 */
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
/**
 * @fn        statDir
 * @brief     得到文件的相关属性
 * 
 * @param     [in] agv       文件名
 * @param     [in] stat_buf  struct stat * 存放的地址  
 * @param     [in] fflag     那个标记选项，这里这个参数可以被优化掉，因为前面有个全局结构体变量
 * 
 * @return    int            
 */
int statDir(char *agv,struct stat *stat_buf,int fflag)
{
    //调用stat 或者lstat 似乎lstat更好，在处理符号链接的时候
    if(stat(agv, stat_buf) < 0)
    {
        if(fflag == 0)
            printf_err(errno);
        return -1;
    }
    return 0;
}
/**
 * @fn        noloop
 * @brief     判断是否是 . 或  .. 
 * 
 * @param     [in] path      
 * 
 * @return    int       是返回1 不是返回0
 */
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
/**
 * @fn        re_move
 * @brief     一个递归删除的函数，本来在reMovempty中后来太长，后来拆分
 * 
 * @param     [in] arc       
 * @param     [in] arv       
 * 
 * @return    int        成功返回0 失败为返回errno或者直接退出（这里需要优化）
 */
int re_move(const int arc,const char **arv)
{
    int i,err1,ret,mind_ret;
    for(i=0;i<arc;i++)
    {
        if(!noloop(arv[i]))
        {        
           
            mind_ret = mind_r(flags->iflag,arv[i]);   
            if(mind_ret)
                exit(1);        //可以被优化
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
    return 0;
}
/**
 * @fn        glob_
 * @brief     本来也是在reMovempty中调用，后来拆分，主要是获得该路径下的目录，并调用re_move删除
 * 
 * @param     [in] path      
 * 
 */
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
    globfree(&globres);
}
/**
 * @fn        reMovempty（glob_ 和 re_move 从这个函数中拆分出来的）
 * @brief     用来处理非空目录的删除函数
 * 
 * @param     [in] path      
 * 
 * @return    int            0为成功  否则退出，这里需要优化，可以返回非零在main中处理这个异常
 */
int reMovempty(char *path)
{
    struct stat statres;
    int retr,mind_ret;
   
    if(lstat(path,&statres) < 0)
    {
        
        exit(1);    //可以被优化
    }
    if(!S_ISDIR(statres.st_mode))
    {
      
        mind_ret = mind_r(flags->iflag,path);
        if(mind_ret)
            exit(1);
        remove(path);
        return 0;
    }
    
  
    glob_(path);
 
    mind_ret = mind_r(flags->iflag,path);
    if(mind_ret)
        exit(0);
    remove(path);       
    //}
    return 0;
}
/**
 * @fn        reMove
 * @brief     删除函数，有main 函数调用
 * 
 * @param     [in] path      需要删除的文件或目录
 * 
 * @return    int            成功返回0 失败返回errno
 */
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
/**
 * @fn        mind_f
 * @brief     处理-i 选项用到的函数
 * 
 * @param     [in] flag_r    
 * @param     [in] arg       
 * 
 * @return    int            
 */
int mind_r(int flag_i,char *arg)
{   
    char std_c=0;
    int ret;
    if(flag_i)
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
            
             return 0;      //do it
        }
        else if((char)std_c == 'N'|| (char)std_c == 'n')
            {
                return 1;   //not do it
            }
            else
            {
                return 2;   //无效的输入   not do anything
            }
        
    }
    else
    {
        return 0;
    }
}
/**
 * @fn        mind_i
 * @brief     处理-I选项的函数
 * 
 * @param     [in] i_flag    
 * 
 * @return    int            
 */
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
            
             return 0;  //do it
        }
        else if((char)std_c == 'N'|| (char)std_c == 'n')
            {
                return 1;       //not do it
            }
            else
            {
                return 2;       //无效的输入 not do anything
            }
        
    }
    else
    {
        return 0;
    }
        
    

}