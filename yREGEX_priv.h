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
#define     P_VERMINOR  "0.6-, keep advancing"
#define     P_VERNUM    "0.6i"
#define     P_VERTXT    "added errors/fancify to sets and unit tested"

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
 * allocate states differently/smaller for yREGEX_fast
 *
 * dynamically allocate finds
 *
 * create a yREGEX_done to destroy unneeded solution/finds/states after
 *
 *
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


typedef   unsigned char  uchar;



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


typedef    struct   cERROR   tERROR;
struct cERROR {
   char        level;
   char       *cat;
   uchar       beg;
   uchar       len;
   char       *msg;
   tERROR     *m_prev;
   tERROR     *m_next;
};

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

#define     MAX_STACK  100

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
#define     MAX_REGEX   20
typedef     struct      cREGEX      tREGEX;
struct      cREGEX {
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
   int         g_beg       [LEN_LABEL];    /* actual group beginnings         */
   int         g_end       [LEN_LABEL];    /* actual group endings            */
   int         g_stk       [MAX_STACK];
   char        g_lvl;
   int         g_cnt;
   int         g_nam;
   int         g_hid;
   int         g_mul;
   char        g_foc;
   /*---(done)--------------*/
};
extern      tREGEX      myREGEX;


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
char*       yregex_error__memory    (void *a_cur);
char        yregex_error__wipe      (void *a_cur);
/*---(memory)---------------*/
char        yregex_error__new       (void **a_new);
char        yregex_error__free      (void **a_old);
/*---(program)--------------*/
char        yregex_error_init       (void);
char        yregex_error__purge     (void);
char        yregex_error_wrap       (void);
char        yregex_error_reset      (void);
/*---(create)---------------*/
char        yregex_error_add        (char a_level, char *a_cat, int a_beg, int a_len, char *a_msg);
/*---(search)---------------*/
char        yregex_error__by_cursor (void **r_curr, char a_move);
char        yregex_error__by_index  (void **r_curr, int a_index);
/*---(fancy)----------------*/
char        yregex_error_fancify    (void);
char        yREGEX_fancy            (char *a_fancy);
/*---(unittest)-------------*/
char*       yregex_error__unit      (char *a_question, int n);
/*---(done)-----------------*/



/*---(support)--------------*/
char*       EXEC__memory            (void *a_cur);
char        EXEC__wipe              (void *a_cur);
/*---(memory)---------------*/
char        EXEC__new               (void **a_new, short a_lvl);
char        EXEC__free              (void **a_old);
/*---(program)--------------*/
char        EXEC_init               (void);
char        EXEC__purge             (void);
char        EXEC_wrap               (void);
/*---(create)---------------*/
char        EXEC__push              (short a_lvl, short a_rpos, short a_tpos);
char        EXEC__push_for_zero     (short a_lvl, short a_rpos, short a_tpos);
/*---(search)---------------*/
char        EXEC__by_index          (void **r_curr, short a_lvl, short a_index);
/*---(running)--------------*/
char        EXEC__prep              (cchar *a_source);
char        EXEC__passed            (char a_who);
char        EXEC__failed            (char a_who);
char        EXEC__found             (void);
char        EXEC__bombed            (void);
/*---(handlers)-------------*/
char        EXEC__literal           (short a_lvl, short a_rpos, short a_tpos);
char        EXEC__anchor            (short a_lvl, short a_rpos, short a_tpos);
char        EXEC__group             (short a_lvl, short a_rpos, short a_tpos);
char        EXEC__branch            (short a_lvl, short a_rpos, short a_tpos);
char        EXEC__single            (void);
/*---(drivers)--------------*/
char        EXEC__driver            (char a_type, cchar *a_source);
char        yREGEX_full             (cchar *a_source);
char        yREGEX_filter           (cchar *a_source);
/*---(unittest)-------------*/
char        EXEC__setfocus          (short a_lvl, short a_index);
char        EXEC__setbegin          (short a_beg);
char*       EXEC__unit              (char *a_question, int n, int m);
/*---(done)-----------------*/


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*===[[ EXEC ]]===============================*/
/*---(program)--------------*/
char        yregex_exec__prep       (cchar *a_source);
/*---(handlers)-------------*/
char        yregex_exec__group      (int a_level, int a_rpos, int a_tpos);
char        yregex_exec__anchor     (int a_level, int a_rpos, int a_tpos);
char        yregex_exec__literal    (int a_level, int a_rpos, int a_tpos);
/*---(nfa)------------------*/
char        yregex_exec_push        (short a_level, short a_rpos, short a_tpos, short a_tmax);
char        yregex_exec_backpush    (short a_level, short a_rpos, short a_tpos, short a_tmax);
char        yregex_exec_launcher    (short a_level, short a_rpos, short a_tpos, char a_rc);
int         yregex_exec_index       (int a_index);
char        yregex_exec_sub         (int a_index, int a_paren);
int         yregex_exec_tpos        (int a_index, int a_paren, int *a_tbeg, int *a_tend);
char        yregex_exec__found      (int a_index);
char        yregex_exec__single     (int a_index);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*===[[ SETS ]]===============================*/
/*---(support)--------------*/
char*       yregex_sets__memory     (void *a_cur);
char        yregex_sets__wipe       (void *a_cur);
/*---(memory)---------------*/
char        yregex_sets__new        (void **a_new);
char        yregex_sets__free       (void **a_old);
/*---(program)--------------*/
char        yregex_sets__prep       (void);
char        yregex_sets_init        (void);
char        yregex_sets__purge      (void);
char        yregex_sets_wrap        (void);
/*---(lookup)---------------*/
char        yregex_sets__by_index   (cint a_index , tSETS **r_set);
int         yregex_sets__by_abbr    (cchar a_abbr , tSETS **r_set);
int         yregex_sets__by_name    (cchar *a_name, tSETS **r_set);
int         yregex_sets__by_map     (tSETS **r_set);
int         yregex_sets__standard   (int *a_rpos);
/*---(create)---------------*/
char        yregex_sets__base       (void);
char        yregex_sets__clear      (char a_unmark);
char        yregex_sets__save       (void);
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
/*---(program)--------------*/
char        yregex_pats_init        (void);
/*---(lookup)---------------*/
int         yregex_pats__by_abbr    (cchar a_abbr);
int         yregex_pats__by_name    (cchar *a_name);
/*---(workhorse)------------*/
char        yregex_pats__named_ref  (int *a_rpos);
char        PATS__back_ref          (int *a_rpos);
/*---(driver)---------------*/
char        yregex_pats_comp        (void);



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*===[[ FIND ]]===============================*/
/*---(support)--------------*/
char*       yregex_find__memory     (void *a_cur);
char        yregex_find__wipe       (void *a_cur);
/*---(memory)---------------*/
char        yregex_find__new        (void **a_new);
char        yregex_find__free       (void **a_old);
/*---(program)--------------*/
char        yregex_find_init        (void);
char        yregex_find__purge      (void);
/*---(structure)------------*/
char        yregex_find_add         (cint a_ref, cint a_beg, cchar *a_text, cchar *a_quan);
char        yregex_find_addsub      (cint a_ref, cint a_num, short a_beg, cchar *a_text, cchar *a_quan);
char        yregex_find_text        (cint a_ref, char *a_text);
int         yregex_find_count       (void);
char*       yregex_find__unit       (char *a_question, int a_num);
/*---(results)--------------*/
char        FIND_first              (int  *a_beg, int *a_len);
char        FIND_next               (int  *a_beg, int *a_len);



/*===[[ RULE ]]===============================*/
int         yregex_rule__group      (int *a_rpos);
int         yregex_rule__operator   (int *a_rpos);
/*---(driver)---------------*/
char        yregex_rule_init        (void);
char        yregex_rule_comp        (int *a_rpos);
char        yregex_rule_exec        (short a_level, short a_rpos, short a_tpos, short a_index);
char        RULE_regex              (short a_level, short a_rpos, short a_tpos, short a_index);



#endif

