/**
 * @copyright Copyright (c) 2022 Jiawshi
 * @author    Jiawshi (jiawshi@126.com)
 * 
 * @file      rmd.c
 * @brief     主程序
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
#include <getopt.h>
#include "rmdi.h"
#include <errno.h>

int main(int argc, char **argv)
{
    int ch,i,err;
    int pflag = 0;
 
    int ignore = 0;
    int help = 0;
    int longindex;
    printf_usage(argc);

    struct option longopts[] = {{"ignore",0,0,'i'},{"parents",0,0,'p'},   
                                {"verbose",0,0,'v'}, {"help",0,0,'h'},  
                                {0,0,0,0}};
    longindex = 4;

    while((ch = getopt_long(argc, argv,"pv",longopts,&longindex)) != -1)
    {
        
        switch(ch)
        {
            case 'p':
                pflag = 1;
                break;
            case 'v':
                v_flag = 1;
                break;
            case 'h':
                printf_help();;
                break;
            case 'i':
                ignore = 1;
                break;
            default :
                printf("Try 'rmdir --help' for more information\n");
                exit(1);
        }
    }
    argc -= optind;
    argv += optind;
    if(argc == 0)
    {
        printf_usage();
    }
    for(i=0;i<argc;i++)
    {
        if(pflag)
        {
            err = rmParent(argv[i]);
            if(err)
            {   if(ignore == 0)
                {
                    printf_err(err);
                }
            }
            
            
        }
        else
        {
            err = rmDir(argv[i]);
            if(err)
            {
                if(ignore==0)
                {
                    printf_err(errno);
                }
            }
            

        }


    }
}