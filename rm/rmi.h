#ifndef RMI_H__
#define RMI_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
void printf_usage(void);
void printf_help(void);
void printf_err(int);

int statDir(char *,struct stat *);

int reMove(char *);
int mind_r(int, char *);
#endif