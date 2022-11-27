#ifndef OPT_H__
#define OPT_H__

char* inter = "i\0" ;
struct flag_all{
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
struct flag_all *get_opt(int, const char **,
            const struct option *, int *);



#endif