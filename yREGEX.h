
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YREGEX_HGUARD
#define YREGEX_HGUARD loaded



typedef   const char     cchar;
typedef   unsigned char  uchar;
typedef   const int      cint;



#define   YREGEX_BEST    '-'
#define   YREGEX_GREEDY  'G'
#define   YREGEX_LAZY    'L'
#define   YREGEX_MOST    'a'
#define   YREGEX_LEFT    'l'
#define   YREGEX_RIGHT   'r'


char        yREGEX_clear         (void);

char        yREGEX_comp          (cchar *a_regex);

char        yREGEX_full          (cchar *a_source);
char        yREGEX_filter        (cchar *a_source);

char        yREGEX_free          (void);

char        yREGEX_best          (cchar a_type, cchar a_dir, int  *a_beg, int *a_len, int *a_fbeg, int *a_flen);

char        yREGEX_method        (char a_method);    /* greedy vs lazy        */
char        yREGEX_cursor        (char a_dir, int *a_beg, int *a_len, int *a_fbeg, int *a_flen);

char        yREGEX_dump          (void);
char        yREGEX_finds         (void);

/*===[[ DEPRECATED ]]========================================*/

char        yREGEX_exec          (cchar *a_source);  /* count all matches      */
char        yREGEX_fast          (cchar *a_source);  /* stop after first match */

#endif

