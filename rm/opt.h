#ifndef OPT_H__
#define OPT_H__

extern char* in_er ;
extern struct flag_all{
    int oflag;          //
    int fflag;          //对应 -f --force
    int rflag;          //对应  -r -R --recursive
    int dflag;          //-d, --dir
    int vflag;          //-v, --verbose
    int i_flag;         //-I
    int iflag;          //-i
    int inter_flag;     //--interactive
    int opt_ind;        //存放optind
}c;//使用c 是为了消除警告。
/**
 * @fn        
 * @brief     用于从终端读取参数的选项
 * 
 * 
 * @return    struct flag_all* 
 */
struct flag_all *get_opt(int, char **);



#endif