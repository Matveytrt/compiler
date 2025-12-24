#ifndef _STRUCT_H_
#define _STRUCT_H_

struct Str_info_t 
{
    char *str_ptr;
    size_t str_len;
    int orig_num;
};

struct File_Info_t 
{
    int nlines;
    size_t buff_size;
    char *buff;
    Str_info_t *str_data;
};

#endif