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



/* rapidly evolving version number to aid with visual change confirmation     */
#define YREGEX_VER_NUM   "0.2a"
#define YREGEX_VER_TXT   "very slim basics of multi and lazy matches"



#define     MAX_SETS       250
#define     LEN_RECD      2000
#define     LEN_NAME        20



typedef struct cSETS  tSETS;
struct cSETS {
   char        type;
   char        abbr;
   char        name        [LEN_NAME];
   char        map         [270];
};
extern tSETS     g_sets [MAX_SETS];
extern int       g_nset;

extern char      g_source    [LEN_RECD];
extern int       g_slen;

extern char      g_regex     [LEN_RECD];
extern int       g_rlen;

extern char      g_comp      [LEN_RECD];
extern char      g_mods      [LEN_RECD];
extern uchar     g_indx      [LEN_RECD];
extern uchar     g_mins      [LEN_RECD];
extern uchar     g_maxs      [LEN_RECD];
extern int       g_clen;



typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char        debug;
   int         logger;
};
extern  tLOCAL its;



extern char        yREGEX_ver   [500];
extern char        unit_answer  [LEN_RECD];


/*---(program)--------------*/
char        yREGEX__comp_init    (cchar *a_regex);
/*---(literals)-------------*/
char        yREGEX__comp_literal (int *a_rpos);
/*---(sets)-----------------*/
char        yREGEX__comp_setinit (void);
char        yREGEX__comp_setabbr (cchar  a_abbr);
char        yREGEX__comp_bslash  (int   *a_rpos);
char        yREGEX__comp_setname (cchar *a_name);
char        yREGEX__comp_setstd  (int   *a_rpos);
char        yREGEX__comp_setmap  (int   *a_rpos);
char        yREGEX__comp_dot     (int   *a_rpos);
char*       yREGEX__unitcomp     (char *a_question, int a_num);


/*---(program)--------------*/
char        yREGEX__exec_init    (cchar *a_source);
/*---(single)---------------*/
char        yREGEX__exec_char    (int a_begin, int a_tpos, int a_rpos);
char        yREGEX__exec_set     (int a_begin, int a_tpos, int a_rpos);
char        yREGEX__exec_doer    (int a_begin, char a_mode, int a_tpos, int a_rpos, int *a_len);
char        yREGEX__exec_multi   (int a_begin, char a_mode, int a_tpos, int a_rpos, int *a_len);
char        yREGEX__exec_next    (int a_begin, char a_mode, int a_tpos, int a_rpos, int *a_len);
/*---(multiple)-------------*/
char*       yREGEX__unitexec     (char *a_question, int a_num);



#endif
