/**
 * @copyright Copyright (c) 2022 Jiawshi
 * @author    Jiawshi (jiawshi@126.com)
 * 
 * @file      mkdirn.c
 * @brief     
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
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "mkdirn.h"
/**
 * @fn        
 * @brief     print err if create file failure
 * 
 * @param     [in] err       err = errno
 * 
 */
void printf_err(int err)
{
    if(err == EEXIST)
        fprintf(stderr,"%s\n",strerror(err));
    else
    {
        fprintf(stderr,"create err! use help\n");
    }
}
/**
 * @fn        
 * @brief     
 * 
 * @param     [in] vflag     -v option symbol
 * @param     [in] dir       dirname
 * 
 */
void flag(int vflag,char *dir)
{   
    if(vflag)
    {
        
        printf("mkdir: created directory '%s'\n",dir);
        
    }
}
void usage(void)
{
    fprintf(stderr,"usage....,you can use mkdir -h to print help.\n");
}
void print_help(void)
{
    printf("-m set file mode,it need a mode after -m  \
            -p make parnet directories \
            -v print a message for each directory that be created\
            -h print help\n");
}
/**
 * @fn        
 * @brief     
 * 
 * @param     [in] path      dirname which need be create
 * @param     [in] mode      permission for the dirname
 * 
 * @return    int            
 */
int mkDir(char *path,mode_t mode)
{
    if((mkdir(path,mode)) < 0)
    {  
        if((mkdir(path,mode)) < 0)
        {
            if(errno == EEXIST)
                return EEXIST;
            else
            {
                return -1;  
            }      
        }        
    }
    return 0;

}
int createDir(char *path,mode_t mode)
{
    int first,end,err;
    char *dirPath = path;
    
    if(*dirPath == '/')
    {
        dirPath++;
    }

    for(first=0,end=0;first <= strlen(path);first++)
    {
        if(dirPath[first] == '\0')
        {
            end = 1;      
        }
        else if(dirPath[first] != '/')
        {
            continue;
        }
        dirPath[first] = '\0';
        err = mkDir(path,mode);
        
        if(err != 0)
        {
            if(err == EEXIST)
            {   
                if(end)
                {
                    return EEXIST;
                }
            }
            else
                return -1;
        }

        if(!end)
        {
            dirPath[first] = '/'; 
        }
        if(end)
            break;
    }
    return 0;
}