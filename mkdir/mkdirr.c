/**
 * @copyright Copyright (c) 2022 Jiawshi
 * @author    Jiawshi (jiawshi@126.com)
 * 
 * @file      mkdirr.c
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
#include "mkdirn.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>


/**
 * @fn        
 * @brief     
 * 
 * @param     [in] argc      
 * @param     [in] argv      
 * 
 * @return    int            
 */
 int main(int argc, char **argv)
 {
    int ch,pflag=0,vflag=0,i,err;
    char *modeStat = NULL;
    mode_t mode;
    while((ch=getopt(argc,argv,"m:pvh")) != -1)
    {
        switch(ch)
        {
            case 'm':
                modeStat = optarg;
                break;
            case 'p':
                pflag = 1;
                break;
            case 'v':
                vflag = 1;
                break;
            case 'h':
                print_help();
                exit(1);
            default:
                usage();
                break;
        }
    }
    argc -=optind;
    argv +=optind;
    if(argc == 0)
    {
        printf_usage();
    }
    if(modeStat == NULL)
    {
        mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;
    }
    for(i=0;i<argc;i++)
        if(pflag)
        {
            err = createDir(argv[i],mode);
            if(err == 0)
                flag(vflag,argv[i]);
            else
            {
                printf_err(err);
            }
        }
        else 
        {
            err = mkDir(argv[i],mode);
            if(err == 0)
                flag(vflag,argv[i]);
            else
            {
                printf_err(err);
            }
        }

 }