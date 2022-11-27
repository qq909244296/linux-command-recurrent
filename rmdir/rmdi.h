/**
 * @copyright Copyright (c) 2022 Jiawshi
 * @author    Jiawshi (jiawshi@126.com)
 * 
 * @file      rmdi.h
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
#ifndef RMDI_H__
#define RMDI_H__
extern int v_flag;
void printf_err(int);
void printf_usage(int);
void printf_help(void);
void vFlag(int,char *);
int rmParent(char *);
int rmDir(char *);



#endif
