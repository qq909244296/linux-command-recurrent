/**
 * @copyright Copyright (c) 2022 Jiawshi
 * @author    Jiawshi (jiawshi@126.com)
 * 
 * @file      rmdi.c
 * @brief     实现函数的功能
 * 
 * @version   V0.01
 * @date      2022-11-26
 * 
 * @note      历史记录 ：
 *            - [2022-11-26] [Jiawshi] 创建初始版本：
 * @warning   
 * @par       修改记录： 
 * <table>
 * <tr><th>date          <th>Version    <th>Author      <th>Description    </tr>
 * <tr><td>2022-11-26    <td>V0.01      <td>Jiawshi       <td>创建初始版本    </tr>
 * </table>
 */
#include <stdio.h>
#include <stdlib.h>
#include "rmdi.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
static int _flag = 0;
int v_flag = 0;
static int strlong;
void printf_err(int err)
{
    fprintf(stderr,"%s\n",strerror(err));
}
void printf_usage(int num)
{
    if(num < 2 )
    {
        fprintf(stderr,"rmdir:missing operand\nTry 'rmdir --help'       \
                for more information\n");
    }
}
/**
 * @fn        vFlag
 * @brief     处理 -v --verbose
 * 
 * @param     [in] flag      vflag
 * @param     [in] path      dirname
 * 
 */
void vFlag(int flag,char *path)
{
    if(flag)
    {
        printf("rmdir: removing directory,'%s'\n",path);
    }

}
void printf_help(void)
{
    printf("--ignore :ignore when error happen      \
            -p --parents :remove include partent dir        \
            -v --verbose :view result       \
            --help:print help\n");
}
/**
 * @fn        rmParent
 * @brief     deal with -p --parent parameter
 * 
 * @param     [in] dirName   
 * 
 * @return    int      success yes(return 0) or no(errno)      
 */
int rmParent(char *dirName)
{
    char *temPath = dirName;
    int retVal;
    int i;
    DIR *dirp;
    struct dirent *dirn;
    strlong = strlen(temPath);
    
    if(temPath[strlong-1] == '/')
    {
        _flag = 1; 
        temPath[strlong-1] = '\0';
    }
    while(temPath != NULL)
    {
        // if(strcmp(temPath,".") == 0)
        // {
        //     temPath = NULL;
        //     return 0;
        // }
        if(strcmp(temPath,"./") ==0 || strcmp(temPath,"..") ==0||strcmp(temPath,".")==0)
        {   temPath = NULL;
            return 0;
        }
        retVal = rmDir(temPath);
        if(retVal < 0)
        {
            //do something
            return errno;
        }

        strlong = strlen(temPath);
        for(i = strlong -1;i>=0;i--)
        {
            if(temPath[i] == '/'&& i != 0)
            { 
                //printf("hhh\n");
                temPath[i] = '\0';
                break;
            }
            if(i == 0)
            {
                temPath = NULL;
                
            } 
        }

    }

    return 0;
}

/**
 * @fn        rmDir
 * @brief     remove dirname
 * 
 * @param     [in] dirName   
 * 
 * @return    int       success yes(return 0) or no(errno)      
 */
int rmDir(char *dirName)
{
    char *temPath = dirName;
    int reVal;
    reVal = rmdir(temPath);
    if(reVal==0)
    {   
        if(_flag)
        {
            temPath[strlong-1]  = '/';
        }
        vFlag(v_flag,temPath);
        if(_flag)
        {   _flag = 0;
            temPath[strlong-1]  = '\0';
        }
    }
    return reVal;

}