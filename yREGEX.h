
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YREGEX_HGUARD
#define YREGEX_HGUARD loaded



typedef   const char     cchar;
typedef   unsigned char  uchar;
typedef   const int      cint;

#define   YREGEX_HERDING     'h'  /* left-to-right starts, one-level at a time   */
#define   YREGEX_WATERFALL   'w'  /* left-to-right starts, pursue all at once    */
#define   YREGEX_SHOTGUN     's'  /* parallel on all starts, one-level at a time */

#define   YREGEX_FIRST       '1'  /* stop after first find                 */
#define   YREGEX_COUNT       '#'  /* count of finds, no finds or states    */
#define   YREGEX_FINDS       'f'  /* all finds but no states               */
#define   YREGEX_STATE       'F'  /* all finds and only their states       */
#define   YREGEX_DEBUG       'A'  /* all finds and all states              */

#define   YREGEX_BEST        '-'
#define   YREGEX_GREEDY      'G'
#define   YREGEX_LAZY        'L'
#define   YREGEX_MOST        'a'
#define   YREGEX_LEFT        'l'
#define   YREGEX_RIGHT       'r'


char        yREGEX_clear         (void);

char        yREGEX_comp          (cchar *a_regex);
char        yREGEX_fancy         (char *r_fancy);

char        yREGEX_first         (cchar *a_source);  /* quit on first find  */
char        yREGEX_count         (cchar *a_source);  /* only count finds    */
char        yREGEX_exec          (cchar *a_source);  /* save all finds      */
char        yREGEX_debug         (cchar *a_source);  /* save all states     */
char        yREGEX_detail        (char a_style, char a_finds, cchar *a_source);

char        yREGEX_free          (void);

char        yREGEX_best          (cchar a_type, cchar a_dir, int  *a_beg, int *a_len, int *a_fbeg, int *a_flen);

char        yREGEX_cursor        (char a_dir, int *a_beg, int *a_len, int *a_fbeg, int *a_flen);

char        yREGEX_dump          (void);
char        yREGEX_finds         (void);

/*---(depricated)------------------------*/
char        yREGEX_fast          (cchar *a_source);  /* quit on first find  */

#endif

