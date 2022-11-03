
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YREGEX_HGUARD
#define YREGEX_HGUARD loaded



typedef   const char     cchar;
typedef   unsigned char  uchar;
typedef   const int      cint;

#define   YREGEX_HERDING     'h'  /* left-to-right starts, one-level at a time   */
#define   YREGEX_WATERFALL   'w'  /* left-to-right starts, pursue all at once    */
#define   YREGEX_SHOTGUN     's'  /* parallel on all starts, one-level at a time */
#define   YREGEX_STYLES      "hws"

#define   YREGEX_FIRST       '1'  /* stop after first find                 */
#define   YREGEX_COUNT       '#'  /* count of finds, no finds or states    */
#define   YREGEX_FIND        'f'  /* all finds but no states               */
#define   YREGEX_STATE       'F'  /* all finds and only their states       */
#define   YREGEX_DEBUG       'A'  /* all finds and all states              */
#define   YREGEX_FINDS       "1#fFA"
#define   YREGEX_NOMISS      "1#fF"
#define   YREGEX_NOSTATE     "1#f"

#define   YREGEX_LLONG       '['
#define   YREGEX_LSHORT      '<'
#define   YREGEX_RSHORT      '>'
#define   YREGEX_RLONG       ']'
#define   YREGEX_ALONG       'L'
#define   YREGEX_ASHORT      'S'
#define   YREGEX_BESTS       "[<>]LS"

#define   YREGEX_BEST        '-'
#define   YREGEX_GREEDY      'G'
#define   YREGEX_LAZY        'L'
#define   YREGEX_MOST        'a'


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yREGEX_clear            (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yREGEX_comp             (cchar *a_regex);
char        yREGEX_fancy            (char *r_fancy);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*
 *  yREGEX_filter   80% of use    just returns simple anything found yes/no
 *  yREGEX_first    15% of use    returns quickly after first find with single answer
 *  yREGEX_exec      5% of use    finds everything AND returns best match
 *  yREGEX_count    uncommon      only returns the count of finds
 *  yREGEX_debug    testing       keeps all data for unit testing
 *  yREGEX_detail   uncommon      to allow low-level configuration
 *
 */
char        yREGEX_filter           (char *a_source);
char        yREGEX_first            (char *a_source, int *r_beg, int *r_len);
char        yREGEX_count            (char *a_source, int *r_count);
char        yREGEX_exec             (char *a_source, int *r_count, int *r_beg, int *r_len);
char        yREGEX_debug            (char *a_source);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yREGEX_detail           (char a_style, char a_finds, char *a_source, char a_best, int *r_count, int *r_beg, int *r_len);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
int         yREGEX_find             (char a_move, int  *r_beg, int *r_len, char *r_text, int *r_fbeg, int *r_flen);
int         yREGEX_best             (char a_best, int  *r_beg, int *r_len, int *r_fbeg, int *r_flen);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yREGEX_free             (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yREGEX_dump             (void);
char        yREGEX_finds            (void);

/*---(depricated)------------------------*/
char        yREGEX_fast             (cchar *a_source);  /* quit on first find  */

#endif

