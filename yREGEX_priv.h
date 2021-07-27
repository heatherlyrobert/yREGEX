/*===============================[[ beg code ]]===============================*/


/*===[[ BEG_HEADER ]]=========================================================*/

/*===[[ ONE_LINERS ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

#define     P_FOCUS     "RS (run-time supprt)"
#define     P_NICHE     "re (regex matching)"
#define     P_SUBJECT   "regular expression matching"
#define     P_PURPOSE   "provide transparent regular expression text pattern matching"

#define     P_NAMESAKE  "artemis-agrotera (the huntress)"
#define     P_HERITAGE  "artemis is the daughter of zeus and titaness leto, twin of apollo"
#define     P_IMAGERY   "beautiful young woman in a cloak and deer pelt, with bow and spears"
#define     P_REASON    "regex is all about hunting for matches"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (less than 2,000 lines of code)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2014-10"

#define     P_VERMAJOR  "0.--, preparing for serious use"
#define     P_VERMINOR  "0.7-, more advanced abilities"
#define     P_VERNUM    "0.7a"
#define     P_VERTXT    "added pruning states and finds to keep footprint configurably small"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ REASONING ]]==========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/* NEXT STEPS
 *
 * dynamically allocate s_errors to save space
 *
 * create beautified string marking troubles, just like in yEXEC flags
 *
 * dynamically allocate states as a block at beginning and destroy later
 *
 * dynamically allocate states individually
 *
 * dynamically allocate finds
 *
 * create a yREGEX_done to destroy unneeded solution/finds/states after
 *
 * if i need speed, use real compiling into byte-code
 *
 *
 *
 *
 *
 *
 *
 */





/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YREGEX_priv_hguard
#define YREGEX_priv_hguard loaded

#include    "yREGEX.h"

#include    <stdio.h>
#include    <stdlib.h>                  /* getenv()                            */

#include    <yURG.h>                    /* heatherly urgent processing         */
#include    <yLOG.h>                    /* heatherly program logger            */
#include    <ySTR.h>                    /* heatherly string handling           */
#include    <yDLST_solo.h>              /* heatherly linked-list constants     */
#include    <yCOLOR_solo.h>             /* heatherly color constants           */

#define     SIMPLIFIER     /**/

typedef   unsigned char  uchar;

#define     TYPE_ERRS      'e'
#define     TYPE_PATS      'p'
#define     TYPE_RULE      'r'
#define     TYPE_SETS      's'
#define     TYPE_EXEC      'x'
#define     TYPE_FIND      'f'
#define     TYPE_NSUB      'n'

#define     BASE_ENTRY     'b'

#define     MAX_REGEX       20

#define     LEN_REGEX     2000
#define     LEN_TEXT      2000
#define     LEN_PAT        300
#define     LEN_DESC       100
#define     LEN_NAME        20


#define     TYPE_QUANS   "*+?@~!"
#define     MAX_QUAN       255
#define     TYPE_GROUP   "()|"
#define     GROUP_FOCUS    0


#define     G_ANCHOR     "^$<>"
#define     G_GROUP      "(|)"
#define     G_GREEDY     "*+?{"
#define     G_LAZY       "@~!}"
#define     G_ZERO       "*@?!"
#define     G_MANY       "*@"
#define     G_PREFIX     "*?!@"

#define     CAT_LIT     "#LIT"
#define     CAT_GRP     "#GRP"
#define     CAT_SET     "#SET"
#define     CAT_RUL     "#RUL"
#define     CAT_PAT     "#PAT"
#define     CAT_COMP    "#COM"
#define     CAT_EXEC    "#EXE"

#define     HAND_LIT    'L'
#define     HAND_ANC    'A'
#define     HAND_GRP    'G'
#define     HAND_PAS    '+'
#define     HAND_BAD    'x'
#define     HAND_SET    'S'



/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
#define     MAX_LEVEL    2000
#define     MAX_STATE   10000
typedef     struct      cSTATE      tSTATE;
static      struct      cSTATE {
   /*---(basics)-----------------*/
   short       lvl;     
   short       seq;     
   short       beg;     
   short       rpos;                        /* regex position                 */
   short       tpos;                        /* text position                  */
   /*---(results)----------------*/
   char        ready;                       /* ready for action/complete      */
   char        who;                         /* which handler                  */
   char        rc;                          /* return code                    */
   /*---(connections)------------*/
   tSTATE     *parent;
   short       nchild;
   tSTATE     *m_prev;
   tSTATE     *m_next;
   /*---(done)-------------------*/
};

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
typedef     struct      cERROR      tERROR;
struct      cERROR {
   char        level;
   char       *cat;
   uchar       beg;
   uchar       len;
   char       *msg;
   tERROR     *m_prev;
   tERROR     *m_next;
};

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
#define     MAX_SUB       10
typedef     struct      cFIND       tFIND;
struct      cFIND {
   /*---(basics)-----------------*/
   tSTATE     *source;                      /* debugging use                  */
   short       beg;                         /* starting point                 */
   short       end;                         /* ending point                   */
   short       len;                         /* length                         */
   char       *text;                        /* found text                     */
   char       *quan;                        /* quantifiers                    */
   /*---(subs)-------------------*/
   short       s_off    [MAX_SUB];
   short       s_len    [MAX_SUB];
   /*---(master)-----------------*/
   tFIND      *m_prev;
   tFIND      *m_next;
   /*---(done)-------------------*/
};

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
typedef     struct      cSETS       tSETS;
struct      cSETS {
   char        source;
   char        type;
   char        abbr;
   char       *name;
   char       *map;
   uchar       count;
   tSETS      *m_prev;
   tSETS      *m_next;
};

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
typedef struct cPATS  tPATS;
struct cPATS {
   char        source;
   char        abbr;                        /* shortcut name                  */
   char       *name;                        /* pattern name                   */
   short       nlen;                        /* length of name                 */
   char       *pat;                         /* actual pattern                 */
   short       plen;                        /* length of pattern              */
   tPATS      *m_prev;
   tPATS      *m_next;
};

#define    MAX_STR      100
typedef    struct       cRULE       tRULE;
struct cRULE {
   char       *str;
   tRULE      *m_prev;
   tRULE      *m_next;
};

#define     MAX_STACK  100

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
#define     MAX_REGEX   20
typedef     struct      cREGEX      tREGEX;
struct      cREGEX {
   /*---(overall)-----------*/
   char        style;                      /* heading vs waterfall vs shotgun */
   char        finds;                      /* count vs first vs full          */
   char        best;                       /* left, right, long, short        */
   /*---(source text)-------*/
   uchar       text        [LEN_TEXT ];    /* text source                     */
   int         tlen;                       /* length of source text           */
   /*---(solution scorer)---*/
   char        scorer;                     /* solution scoring algorithm      */
   /*---(original regex)----*/
   uchar       orig        [LEN_REGEX];    /* original regex                  */
   int         olen;                       /* length of original regex        */
   /*---(original regex)----*/
   uchar       regex       [LEN_REGEX];    /* regex source                    */
   int         rlen;                       /* length of source regex          */
   /*---(compiled regex)----*/
   char        ready;                      /* compilied correctly and ready   */
   uchar       comp        [LEN_REGEX];    /* compilied regex chars           */
   int         indx        [LEN_REGEX];    /* compilied regex group/set index */
   uchar       mods        [LEN_REGEX];    /* compilied regex modifier        */
   int         jump        [LEN_REGEX];    /* compilied regex group jumps     */
   int         clen;                       /* compliled regex length          */
   /*---(group)-------------*/
   char        g_mrk       [LEN_LABEL];    /* marks for named groups          */
   char        g_lvl;
   int         g_cnt;
   int         g_nam;
   int         g_hid;
   int         g_mul;
   char        g_foc;
   /*---(done)--------------*/
};
extern      tREGEX      myREGEX;


extern char  g_print   [LEN_RECD];
extern char  g_found   [LEN_TEXT];
extern char  g_quans   [LEN_TEXT];
extern char  g_subf    [LEN_TEXT];
extern char  g_subq    [LEN_TEXT];


extern char        yREGEX_ver   [500];
extern char        unit_answer  [LEN_TEXT];


/*---(base)-----------------*/
char*       yREGEX_version       (void);
char*       yREGEX__testloc      (cchar *a_regex, cchar *a_source);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yregex__unit_quiet      (void);
char        yregex__unit_loud       (void);
char        yregex__unit_end        (void);



/*---(memory)---------------*/
char        yregex_share_new        (char a_type, void **r_new, void **a_head, void **a_tail, int *a_count);
char        yregex_share_free       (char a_type, void **r_old, void **a_head, void **a_tail, int *a_count);
/*---(program)--------------*/
char        yregex_share_init       (char a_type, void **a_head, void **a_tail, void **a_curr, int *a_count);
char        yregex_share_purge      (char a_type, void **a_head, void **a_tail, void **a_curr, int *a_count);
char        yregex_share_wrap       (char a_type, void **a_head, void **a_tail, void **a_curr, int *a_count);
/*---(search)---------------*/
char        yregex_share__by_cursor (char a_type, void **a_head, void **a_tail, void **r_curr, void **r_back, char a_move);
char        yregex_share__by_index  (char a_type, void **a_head, void **r_curr, void **r_back, int a_index);
int         yregex_share__by_abbr   (char a_type, void **a_head, void **r_back, char a_abbr);
int         yregex_share__by_name   (char a_type, void **a_head, void **r_back, char *a_name);
/*---(unittest)-------------*/
char*       yregex_share__unit      (char a_type, void *a_head, void *a_tail, int a_count, char *a_question, int a_num);
/*---(done)-----------------*/



/*===[[ COMP ]]===============================*/
/*---(program)--------------*/
char        yregex_comp__prep       (cchar *a_regex);
/*---(structure)------------*/
char        yregex_comp_add         (cchar a_comp, cint a_indx);
char        yregex_comp_mod         (cchar a_mod);
char        yregex_comp__dup_one    (void);
char        yregex_comp__dup_group  (void);
/*---(literal)--------------*/
char        yregex_comp__literal    (int *a_rpos);
/*---(quantifiers)----------*/
char        yregex_comp__quan_simp  (int *a_rpos);
char        yregex_comp__quan_comp  (int *a_rpos);
/*---(groups)---------------*/
char        yregex_comp__extended   (void);
/*---(unittest)-------------*/
char*       yregex_comp__unit       (char *a_question, int a_num);
/*---(done)-----------------*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        yregex_group_init       (void);
char        yregex_group__purge     (void);
char        yregex_group_wrap       (void);
/*---(compile)--------------*/
char        yregex_group__open      (int *a_rpos);
char        yregex_group__branch    (int *a_rpos);
char        yregex_group__close     (int *a_rpos);
char        yregex_group__fix       (int a_grp);
/*---(execute)--------------*/
char        yregex_group_endpoints  (int a_cur, int *a_beg, int *a_end);



/*---(support)--------------*/
char*       yregex_error__memory    (tERROR *a_cur);
char        yregex_error__wipe      (tERROR *a_cur);
/*---(memory)---------------*/
char        yregex_error__new       (tERROR **a_new);
char        yregex_error__free      (tERROR **a_old);
/*---(program)--------------*/
char        yregex_error_init       (void);
char        yregex_error__purge     (void);
char        yregex_error_wrap       (void);
char        yregex_error_reset      (void);
/*---(create)---------------*/
char        yregex_error_add        (char a_level, char *a_cat, int a_beg, int a_len, char *a_msg);
/*---(search)---------------*/
char        yregex_error__by_cursor (char a_move, tERROR **r_back);
char        yregex_error__by_index  (int a_index, tERROR **r_back);
/*---(fancy)----------------*/
char        yregex_error_fancify    (void);
char        yREGEX_fancy            (char *r_fancy);
/*---(unittest)-------------*/
char*       yregex_error__unit      (char *a_question, int n);
/*---(done)-----------------*/



/*---(support)--------------*/
char*       yregex_exec__memory     (tSTATE *a_cur);
char        yregex_exec__wipe       (tSTATE *a_cur);
/*---(memory)---------------*/
char        yregex_exec__new        (tSTATE **r_new);
char        yregex_exec__free       (tSTATE **r_old);
/*---(program)--------------*/
char        yregex_exec_init        (void);
char        yregex_exec__purge      (void);
char        yregex_exec_wrap        (void);
/*---(create)---------------*/
char        yregex_exec__push       (short a_lvl, short a_rpos, short a_tpos);
char        yregex_exec__pushback   (short a_lvl, short a_rpos, short a_tpos);
/*---(search)---------------*/
char        yregex_exec__by_cursor  (char a_move, tSTATE **r_back);
char        yregex_exec__by_index   (int a_index, tSTATE **r_back);
/*---(running)--------------*/
char        yregex_exec_prep        (char *a_source);
char        yregex_exec__next_focus (void);
char        yregex_exec__passed     (char a_who);
char        yregex_exec__failed     (char a_who);
char        yregex_exec__found      (void);
char        yregex_exec__bombed     (void);
char        yregex_exec__prune      (tSTATE *a_focus);
/*---(handlers)-------------*/
char        yregex_exec_launcher    (short a_lvl, short a_rpos, short a_tpos, char a_rc);
char        yregex_exec__literal    (short a_lvl, short a_rpos, short a_tpos);
char        yregex_exec__anchor     (short a_lvl, short a_rpos, short a_tpos);
char        yregex_exec__group      (short a_lvl, short a_rpos, short a_tpos);
char        yregex_exec__branch     (short a_lvl, short a_rpos, short a_tpos);
char        yregex_exec__single     (void);
/*---(drivers)--------------*/
char        yregex_exec__waterfall  (char a_type, int a_begin, int *c);
char        yregex_exec__herding    (char a_type, int a_begin, int *c);
char        yregex_exec__preshotgun (void);
char        yregex_exec__shotgun    (char a_finds, int a_begin, int *c);
char        yREGEX_detail           (char a_style, char a_finds, char *a_source, char a_best, int *r_count, int *r_beg, int *r_len);
char        yREGEX_full             (char *a_source);
char        yREGEX_filter           (char *a_source);
/*---(unittest)-------------*/
char        yregex_exec__setfocus   (short a_seq);
char        yregex_exec__setbegin   (short a_beg);
char*       yregex_exec__unit       (char *a_question, int n);
/*---(done)-----------------*/


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*===[[ EXEC ]]===============================*/
/*---(program)--------------*/
/*> char        yregex_exec__prep       (cchar *a_source);                            <*/
/*---(handlers)-------------*/
/*> char        yregex_exec__group      (int a_level, int a_rpos, int a_tpos);        <* 
 *> char        yregex_exec__anchor     (int a_level, int a_rpos, int a_tpos);        <* 
 *> char        yregex_exec__literal    (int a_level, int a_rpos, int a_tpos);        <*/
/*---(nfa)------------------*/
/*> char        yregex_exec_push        (short a_level, short a_rpos, short a_tpos, short a_tmax);   <* 
 *> char        yregex_exec_backpush    (short a_level, short a_rpos, short a_tpos, short a_tmax);   <* 
 *> char        yregex_exec_launcher    (short a_level, short a_rpos, short a_tpos, char a_rc);      <* 
 *> int         yregex_exec_index       (int a_index);                                               <* 
 *> char        yregex_exec_sub         (int a_index, int a_paren);                                  <* 
 *> int         yregex_exec_tpos        (int a_index, int a_paren, int *a_tbeg, int *a_tend);        <* 
 *> char        yregex_exec__found      (int a_index);                                               <* 
 *> char        yregex_exec__single     (int a_index);                                               <*/


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*===[[ SETS ]]===============================*/
/*---(support)--------------*/
char*       yregex_sets__memory     (void *a_cur);
char        yregex_sets__wipe       (void *a_cur);
/*---(memory)---------------*/
char        yregex_sets__new        (void **a_new);
char        yregex_sets__free       (void **a_old);
/*---(program)--------------*/
char        yregex_sets_reset       (void);
char        yregex_sets_init        (void);
char        yregex_sets__purge      (void);
char        yregex_sets_wrap        (void);
/*---(lookup)---------------*/
char        yregex_sets__by_cursor  (char a_move , tSETS **r_back);
char        yregex_sets__by_index   (int a_index , tSETS **r_back);
int         yregex_sets__by_abbr    (char a_abbr , tSETS **r_back);
int         yregex_sets__by_name    (char *a_name, tSETS **r_back);
int         yregex_sets__by_map     (tSETS **r_back);
int         yregex_sets__standard   (int *a_rpos);
/*---(create)---------------*/
char        yregex_sets__base       (void);
char        yregex_sets__clear      (char a_unmark);
char        yregex_sets__save       (char *a_name);
char        yregex_sets__mapper     (char *a_regex, int *a_rpos);
/*---(compile)--------------*/
char        yregex_sets_backslash   (int *a_rpos);
char        yregex_sets_dot         (int *a_rpos);
char        yregex_sets_comp        (int *a_rpos);
char        yregex_sets_list        (void);
/*---(execute)--------------*/
char        yregex_sets_break       (int a_level, int a_rpos, int a_tpos);
char        yregex_sets_exec        (int a_level, int a_rpos, int a_tpos);
char        yregex_sets_rule        (char a_mod, char *a_text, int a_set);
/*---(unittest)-------------*/
char        yregex_sets__setmap     (char *a_map);
char*       yregex_sets__unit       (char *a_question, int a_num);
/*---(done)-----------------*/



/*===[[ PATS ]]===============================*/
/*---(support)--------------*/
char*       yregex_pats__memory     (void *a_cur);
char        yregex_pats__wipe       (void *a_cur);
/*---(memory)---------------*/
char        yregex_pats__new        (void **a_new);
char        yregex_pats__free       (void **a_old);
/*---(program)--------------*/
char        yregex_pats_reset       (void);
char        yregex_pats_init        (void);
char        yregex_pats__purge      (void);
char        yregex_pats_wrap        (void);
/*---(create)---------------*/
char        yregex_pats__base       (void);
/*---(search)---------------*/
char        yregex_pats__by_cursor  (char a_move , tPATS **r_back);
char        yregex_pats__by_index   (int a_index , tPATS **r_pat);
int         yregex_pats__by_abbr    (char a_abbr , tPATS **r_pat);
int         yregex_pats__by_name    (char *a_name, tPATS **r_pat);
/*---(compile)--------------*/
char        yregex_pats__replace    (char *a_src, char a_run);
char        yregex_pats__named      (char *a_src);
char        yregex_pats_comp        (void);
/*---(unittest)-------------*/
char*       yregex_pats__unit       (char *a_question, int a_num);
/*---(done)-----------------*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*===[[ FIND ]]===============================*/
/*---(support)--------------*/
char*       yregex_find__memory     (tFIND *a_cur);
char        yregex_find__wipe       (tFIND *a_cur);
/*---(memory)---------------*/
char        yregex_find__new        (tFIND **a_new);
char        yregex_find__free       (tFIND **a_old);
/*---(program)--------------*/
char        yregex_find_init        (void);
char        yregex_find__purge      (void);
char        yregex_find_wrap        (void);
/*---(create)---------------*/
char        yregex_find__full       (tSTATE *a_source, short a_beg, char *a_text, char *a_quan);
char        yregex_find__sub        (char a_num, short a_beg, short a_len);
/*---(search)---------------*/
char        yregex_find__by_cursor  (char a_move, tFIND  **r_back);
char        yregex_find__by_index   (int a_index, tFIND  **r_back);
char        yregex_find__by_loc     (short a_beg, short a_len);
int         yREGEX_find             (char a_move, int  *r_beg, int *r_len, int *r_fbeg, int *r_flen);
int         yREGEX_best             (char a_best, int  *r_beg, int *r_len, int *r_fbeg, int *r_flen);
/*---(structure)------------*/
char        yregex_find__reset      (void);
char        yregex_find__trail      (tSTATE *a_focus, char a_mark);
char        yregex_find__save       (tSTATE *a_focus);
char        yregex_find__group      (char a_group);
char        yregex_find_add         (tSTATE *a_focus);
char        yregex_find_group       (tSTATE *a_focus, char a_group, char *r_text);
char        yregex_find_text        (cint a_ref, char *a_text);
int         yregex_find_count       (void);
char*       yregex_find__unit       (char *a_question, int a_num);
/*---(results)--------------*/
char        FIND_first              (int  *a_beg, int *a_len);
char        FIND_next               (int  *a_beg, int *a_len);



/*===[[ RULE ]]===============================*/
/*---(support)--------------*/
char        yregex_rule__wipe       (tRULE *a_cur);
/*---(memory)---------------*/
char        yregex_rule__new        (tRULE  **r_new);
char        yregex_rule__free       (tRULE  **r_old);
/*---(program)--------------*/
char        yregex_rule_init        (void);
char        yregex_rule__purge      (void);
char        yregex_rule_wrap        (void);
/*---(create)---------------*/
short       yregex_rule__add        (short a_beg, short a_len);
/*---(search)---------------*/
char        yregex_rule__by_cursor  (char a_move , tRULE  **r_back);
char        yregex_rule__by_index   (int a_index , tRULE  **r_back);
/*---(compile)--------------*/
char        yregex_rule__ends       (int *a_rpos, char *a_group);
short       yregex_rule__operator   (int *a_rpos);
char        yregex_rule__group      (int *a_rpos);
char        yregex_rule_comp        (int *a_rpos);
/*---(driver)---------------*/
char        yregex_rule_exec        (short a_level, short a_rpos, short a_tpos, tSTATE *a_focus);
/*---(unittest)-------------*/
char*       yregex_rule__memory     (tRULE *a_cur);
char*       yregex_rule__detail     (tRULE *a_cur);
char*       yregex_rule__unit       (char *a_question, int a_num);



#endif

