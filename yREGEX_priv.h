/*===============================[[ beg code ]]===============================*/
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YREGEX_priv_hguard
#define YREGEX_priv_hguard loaded

#include    "yREGEX.h"

#include    <stdio.h>
#include    <stdlib.h>                  /* getenv()                            */

#include    <yURG.h>                    /* heatherly urgent processing         */
#include    <yLOG.h>                    /* heatherly program logger            */
#include    <ySTR.h>                    /* heatherly string handling           */


typedef   unsigned char  uchar;


/* rapidly evolving version number to aid with visual change confirmation     */
#define YREGEX_VER_NUM   "0.5d"
#define YREGEX_VER_TXT   "simple rule working for comparing equality of two groups (backref)"


#define     MAX_REGEX       20

#define     LEN_REGEX     2000
#define     LEN_TEXT      2000
#define     LEN_PAT        300
#define     LEN_DESC       100
#define     LEN_NAME        20


#define     TYPE_QUANS   "*+?@~!"
#define     MAX_QUAN       255
#define     TYPE_GROUP   "()|&"
#define     GROUP_FOCUS    999

#define     BACKSLASH_SETS   "entfswdlugaxWDSFG"

#define     G_ANCHOR     "^$<>"
#define     G_GROUP      "(|)"
#define     G_GREEDY     "*+?{"
#define     G_LAZY       "@~!}"
#define     G_ZERO       "*@?!"
#define     G_MANY       "*@"
#define     G_PREFIX     "*?!@"


/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
#define     MAX_REGEX   20
typedef     struct      cREGEX      tREGEX;
struct      cREGEX {
   /*---(source text)--------------------*/
   uchar       text        [LEN_TEXT ];    /* text source                     */
   int         tlen;                       /* length of source text           */
   /*---(solution scorer)----------------*/
   char        scorer;                     /* solution scoring algorithm      */
   /*---(original regex)-----------------*/
   uchar       orig        [LEN_REGEX];    /* original regex                  */
   int         olen;                       /* length of original regex        */
   /*---(original regex)-----------------*/
   uchar       regex       [LEN_REGEX];    /* regex source                    */
   int         rlen;                       /* length of source regex          */
   /*---(compiled regex)-----------------*/
   uchar       comp        [LEN_REGEX];    /* compilied regex chars           */
   int         indx        [LEN_REGEX];    /* compilied regex group/set index */
   uchar       mods        [LEN_REGEX];    /* compilied regex modifier        */
   int         jump        [LEN_REGEX];    /* compilied regex group jumps     */
   int         clen;                       /* compliled regex length          */
};
extern      tREGEX      gre;


extern char  g_found   [LEN_TEXT];
extern char  g_quans   [LEN_TEXT];
extern char  g_subf    [LEN_TEXT];
extern char  g_subq    [LEN_TEXT];


extern char        yREGEX_ver   [500];
extern char        unit_answer  [LEN_TEXT];


/*---(base)-----------------*/
char*       yREGEX_version       (void);
char*       yREGEX__testloc      (cchar *a_regex, cchar *a_source);




/*===[[ COMP ]]===============================*/
/*---(program)--------------*/
char        COMP__init           (cchar *a_regex);
char        COMP_error           (cchar *a_func, cint a_line, cchar *a_marker, cchar *a_message);
/*---(structure)------------*/
char        COMP_add             (cchar a_comp, cint a_indx);
char        COMP_mod             (cchar a_mod);
char        COMP__dup_one        (void);
char        COMP__dup_group      (void);
/*---(literal)--------------*/
char        COMP__literal        (int *a_rpos);
/*---(quantifiers)----------*/
char        COMP__quan_simple    (int *a_rpos);
char        COMP__quan_complex   (int *a_rpos);
/*---(groups)---------------*/
int         COMP_group_beg       (int  a_rpos);
int         COMP_group_end       (int  a_rpos);



/*===[[ EXEC ]]===============================*/
/*---(program)--------------*/
char        EXEC__init           (cchar *a_source);
/*---(handlers)-------------*/
char        EXEC__group          (int a_level, int a_rpos, int a_tpos);
char        EXEC__anchor         (int a_level, int a_rpos, int a_tpos);
char        EXEC__literal        (int a_level, int a_rpos, int a_tpos);
/*---(nfa)------------------*/
char        EXEC_push            (short a_level, short a_rpos, short a_tpos, short a_tmax);
char        EXEC_backpush        (short a_level, short a_rpos, short a_tpos, short a_tmax);
char        EXEC_launcher        (short a_level, short a_rpos, short a_tpos, char a_rc);
char        EXEC__solution       (int a_index);
char        EXEC_sub             (int a_index, int a_paren);
int         EXEC__tpos           (int a_index, int a_paren, int *a_tbeg, int *a_tend);
char        EXEC__found          (int a_index);
char        EXEC__list           (void);
char        EXEC__prime          (void);
char        EXEC__single         (int a_index);


/*===[[ SETS ]]===============================*/
/*---(program)--------------*/
char        SETS_init            (void);
/*---(lookup)---------------*/
char        SETS_by_abbr         (cchar a_abbr);
char        SETS__by_name        (cchar *a_name);
char        SETS__by_map         (void);
char        SETS__standard       (int *a_rpos);
/*---(mapping)--------------*/
char        SETS__clear          (char a_unmark);
char        SETS__save           (void);
char        SETS__mapper         (int *a_rpos);
/*---(compile)--------------*/
char        SETS_backslash       (int *a_rpos);
char        SETS_dot             (int *a_rpos);
char        SETS_comp            (int *a_rpos);
/*---(execute)--------------*/
char        SETS_break           (int a_level, int a_rpos, int a_tpos);
char        SETS_exec            (int a_level, int a_rpos, int a_tpos);
/*---(done)-----------------*/



/*===[[ PATS ]]===============================*/
/*---(program)--------------*/
char        PATS__init           (void);
/*---(lookup)---------------*/
int         PATS__by_abbr        (cchar a_abbr);
int         PATS__by_name        (cchar *a_name);
/*---(workhorse)------------*/
char        PATS__named_ref      (int *a_rpos);
char        PATS__back_ref       (int *a_rpos);
/*---(driver)---------------*/
char        PATS_comp            (void);



/*===[[ FIND ]]===============================*/
/*---(program)--------------*/
char        FIND_init            (void);
/*---(structure)------------*/
char        FIND_add             (cint a_ref, cint a_beg, cchar *a_text, cchar *a_quan);
char        FIND_list            (void);
char        FIND_text            (cint a_ref, char *a_text);
int         FIND_count           (void);
char*       FIND__unit           (char *a_question, int a_num);
/*---(results)--------------*/
char        FIND_first           (int  *a_beg, int *a_len);
char        FIND_next            (int  *a_beg, int *a_len);



/*===[[ RULE ]]===============================*/
/*---(driver)---------------*/
char        RULE_comp            (int *a_rpos);
char        RULE_exec            (short a_level, short a_rpos, short a_tpos, short a_index);



#endif

