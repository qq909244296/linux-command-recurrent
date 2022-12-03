#ifndef RMI_H__
#define RMI_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "opt.h"
void printf_usage(void);
void printf_help(void);
void printf_err(int);
int findempty(char *);
int statDir(char *,struct stat *,int);
int reMovempty(char *);
int reMove(char *);
int mind_r(int, char *);
int mind_i(int );
#endif