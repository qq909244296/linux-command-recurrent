/**
 * @copyright Copyright (c) 2022 Jiawshi
 * @author    Jiawshi (jiawshi@126.com)
 * 
 * @file      mkdirn.h
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
#ifndef MKDIRL_H__
#define MKDIRN_H__
#include <sys/stat.h>
#include <sys/types.h>
void printf_err(int);
void usage(void);
void print_help(void);
void flag(int ,char *);
int mkDir(char *,mode_t);
int createDir(char *,mode_t);


#endif
