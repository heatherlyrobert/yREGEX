
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YREGEX_HGUARD
#define YREGEX_HGUARD loaded



typedef   const char     cchar;
typedef   unsigned char  uchar;
typedef   const int      cint;



#define   YREGEX_GREEDY  'G'
#define   YREGEX_LAZY    'L'
#define   YREGEX_MOST    'a'
#define   YREGEX_LEFT    'l'
#define   YREGEX_RIGHT   'r'



char        yREGEX_comp          (cchar *a_regex);
char        yREGEX_exec          (cchar *a_source);
int         yREGEX_find          (cchar a_type, cchar a_start, int  *a_beg, int *a_len);



#endif

