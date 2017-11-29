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
#define YREGEX_VER_NUM   "0.1b"
#define YREGEX_VER_TXT   "started with a literal character match and unit test for it"


typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char        debug;
   int         logger;
};
extern  tLOCAL its;

#define     MAX_SETS       250

#define     LEN_RECD      2000
#define     LEN_NAME        20

char        yREGEX__comp_init    (cchar *a_regex);
char        yREGEX__exec_init    (cchar *a_source);
char        yREGEX__literal      (int a_depth, int a_tpos, int a_rpos);

#endif
