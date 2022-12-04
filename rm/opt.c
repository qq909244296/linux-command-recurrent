/**
 * @copyright Copyright (c) 2022 Jiawshi
 * @author    Jiawshi (jiawshi@126.com)
 * 
 * @file      opt.c
 * @brief     
 * 
 * @version   V0.01
 * @date      2022-12-04
 * 
 * @note      历史记录 ：
 *            - [2022-12-04] [Jiawshi] 创建初始版本：
 * @warning   
 * @par       修改记录： 
 * <table>
 * <tr><th>date          <th>Version    <th>Author      <th>Description    </tr>
 * <tr><td>2022-12-04    <td>V0.01      <td>Jiawshi       <td>创建初始版本    </tr>
 * </table>
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "rmi.h"
#include "opt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
char *in_er={"i\0"};        //对应于--interactive 中的默认选项
struct flag_all *flags;     //用来记录标记选项
/**
 * @fn        get_opt
 * @brief     分析命令行参数
 * 
 * @param     [in] agc       
 * @param     [in] agv       
 * 
 * @return    struct flag_all* 
 */
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
    struct option longopt[] = {{"force",0,0,'f'}, {"interactive",1,0,'1'},
                            {"one-file-system",0,0,'o'},{"no-preserve-root",0,0,'n'},
                            {"recursive",0,0,'r'},{"dir",0,0,'d'},{"verbose",0,0,'v'},
                            {"help",0,0,'h'},{0,0,0,0}};
    int longindex = 8;//这里写0吧
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
    //下面的处理只是为了处理当用户使用了一些选项他们的功能类似，但不能同时设置的问题，从而
    //设置了优先权-i > -I > -f 在--interactive中-i是默认参数
    if(flags->inter_flag)
    {
        if(strcmp(in_er,"i")==0)
        {
            flags->iflag = 1;
        }
        if(strcmp(in_er,"once") ==0 )
        {
            flags->i_flag = 1;
        }
        if(strcmp(in_er,"never") == 0)
        {
            flags->iflag = 0;
            flags->i_flag = 0;
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
        flags->fflag = 0;
    }
    if(flags->rflag ==1&& flags->dflag ==1)
    {
        flags->dflag = 0;
    }



    flags->opt_ind = optind;
    return flags;
}