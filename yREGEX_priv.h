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
#define YREGEX_VER_NUM   "0.2s"
#define YREGEX_VER_TXT   "broke out anchor and end-of-group for separate recursion"



#define     MAX_SETS       250
#define     MAX_CAPS        10
#define     LEN_RECD      2000
#define     LEN_NAME        20


#define     G_ANCHOR     "^$"
#define     S_GROUP      "(|)"
#define     G_GREEDY     "*+?{"
#define     G_LAZY       "@~!}"

/*---(sets)-----------------*/
typedef struct cSETS  tSETS;
struct cSETS {
   char        type;
   char        abbr;
   char        name        [LEN_NAME];
   char        map         [270];
};
extern tSETS     g_sets [MAX_SETS];
extern int       g_nset;


/*---(captures)-------------*/
typedef struct cCAPS  tCAPS;
struct cCAPS {
   int         beg;
   int         end;
   int         len;
};
extern tCAPS     g_caps [MAX_CAPS];
extern int       g_ncap;


/*---(source)---------------*/
extern char      g_source    [LEN_RECD];
extern int       g_slen;

/*---(regex)----------------*/
extern char      g_regex      [LEN_RECD];
extern int       g_rlen;

/*---(compiled)-------------*/
extern char      g_comp      [LEN_RECD];
extern int       g_indx      [LEN_RECD];
extern char      g_mods      [LEN_RECD];
extern int       g_mins      [LEN_RECD];
extern int       g_maxs      [LEN_RECD];
extern int       g_jump      [LEN_RECD];
extern int       g_clen;

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
#define     MAX_REGEX   20
typedef     struct      cREGEX      tREGEX;
struct      cREGEX {
   char        orig        [LEN_RECD];     /* regex source                    */
   int         rlen;                       /* length of source regex          */
   char        text        [LEN_RECD];     /* text source                     */
   int         tlen;                       /* length of source text           */
};
extern      tREGEX      g_RE        [MAX_REGEX];



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
char        yREGEX__exec_doer    (int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend);
char        yREGEX__exec_next    (int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend);
/*---(groups)---------------*/
char        yREGEX__exec_multiple(int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend);
char        yREGEX__exec_branch  (int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend);
char        yREGEX__exec_group   (int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend);
/*---(multiple)-------------*/
char*       yREGEX__unitexec     (char *a_question, int a_num);

char*       yREGEX__testloc      (cchar *a_regex, cchar *a_source);



#endif

