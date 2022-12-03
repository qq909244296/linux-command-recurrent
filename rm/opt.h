#ifndef OPT_H__
#define OPT_H__

extern char* in_er ;
extern struct flag_all{
    int oflag;
    int fflag;
    int rflag;
    int dflag;
    int vflag;
    int i_flag;
    int iflag;
    int inter_flag;
    int opt_ind;
};
struct flag_all *get_opt(int, char **);



#endif