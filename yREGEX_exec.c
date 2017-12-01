/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



char        g_source    [LEN_RECD]  = "";
int         g_slen      = -1;



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
yREGEX__exec_init    (cchar *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_source"  , a_source);
   /*---(check regex)--------------------*/
   --rce;  if (a_source  == NULL) {
      DEBUG_YREGEX  yLOG_note    ("can not be null");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_slen = strllen (a_source , LEN_RECD);
   DEBUG_YREGEX  yLOG_value   ("g_slen"    , g_slen);
   --rce;  if (g_slen <= 0   ) {
      DEBUG_YREGEX  yLOG_note    ("can not be empty");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = strlcpy (g_source, a_source , LEN_RECD);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   --rce;  if (rc     <  0   ) {
      DEBUG_YREGEX  yLOG_note    ("truncated copy");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       single matching                        ----===*/
/*====================------------------------------------====================*/
static void      o___SINGLE__________________o (void) {;}

char
yREGEX__exec_char    (int a_depth, int a_tpos, int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (g_comp   [a_rpos]);
   DEBUG_YREGEX  yLOG_schar   (g_source [a_tpos]);
   /*---(test)---------------------------*/
   if (g_comp [a_rpos] == g_source [a_tpos])   rc = 1;
   else                                        rc = 0;
   DEBUG_YREGEX  yLOG_sint    (rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yREGEX__exec_set     (int a_depth, int a_tpos, int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (g_comp   [a_rpos]);
   DEBUG_YREGEX  yLOG_schar   (g_source [a_tpos]);
   /*---(test)---------------------------*/
   if (g_sets [g_indx [a_rpos]].map [g_source [a_tpos]] == '.')  rc = 1;
   else                                                          rc = 0;
   DEBUG_YREGEX  yLOG_sint    (rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yREGEX__exec_doer    (int a_depth, int a_tpos, int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_indx      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_depth"   , a_depth);
   DEBUG_YREGEX  yLOG_value   ("a_tpos"    , a_tpos);
   DEBUG_YREGEX  yLOG_value   ("a_rpos"    , a_rpos);
   /*---(defenses)-----------------------*/
   --rce;  if (a_depth <    0) {
      DEBUG_YREGEX  yLOG_note    ("depth can not be negative");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_depth >= 100) {
      DEBUG_YREGEX  yLOG_note    ("too deep in recursion");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_tpos <  0     ) {
      DEBUG_YREGEX  yLOG_note    ("before beginning of source text");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("g_slen"    , g_slen);
   --rce;  if (a_tpos >= g_slen) {
      DEBUG_YREGEX  yLOG_note    ("past end of source text");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_rpos <  0     ) {
      DEBUG_YREGEX  yLOG_note    ("before beginning of regex");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("g_clen"    , g_clen);
   --rce;  if (a_rpos >= g_clen) {
      DEBUG_YREGEX  yLOG_note    ("past end of regex");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_indx = g_indx [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_indx"    , x_indx);
   /*---(decide)-------------------------*/
   if (x_indx > 0)  rc = yREGEX__exec_set  (a_depth, a_tpos, a_rpos);
   else             rc = yREGEX__exec_char (a_depth, a_tpos, a_rpos);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   /*---(check)--------------------------*/
   if (rc != 1) rc = 0;
   DEBUG_YREGEX  yLOG_value   ("return"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                     multiple matching                        ----===*/
/*====================------------------------------------====================*/
static void      o___MULTIPLE________________o (void) {;}

char
yREGEX__exec_greedy  (int a_depth, int a_tpos, int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       x_min       =    0;
   uchar       x_max       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_depth"   , a_depth);
   DEBUG_YREGEX  yLOG_value   ("a_tpos"    , a_tpos);
   DEBUG_YREGEX  yLOG_value   ("a_rpos"    , a_rpos);
   /*---(prepare)------------------------*/
   x_min  = g_mins [a_rpos];
   x_max  = g_maxs [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_min"     , x_min);
   DEBUG_YREGEX  yLOG_value   ("x_max"     , x_max);
   /*---(loop)---------------------------*/


   /*---(check)--------------------------*/
   if (rc != 1) rc = 0;
   DEBUG_YREGEX  yLOG_value   ("return"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yREGEX__exec_lazy    (int a_depth, int a_tpos, int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       x_min       =    0;
   uchar       x_max       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_depth"   , a_depth);
   DEBUG_YREGEX  yLOG_value   ("a_tpos"    , a_tpos);
   DEBUG_YREGEX  yLOG_value   ("a_rpos"    , a_rpos);
   /*---(prepare)------------------------*/

   x_min  = g_mins [a_rpos];
   x_max  = g_maxs [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_min"     , x_min);
   DEBUG_YREGEX  yLOG_value   ("x_max"     , x_max);
   /*---(loop)---------------------------*/



   /*---(check)--------------------------*/
   if (rc != 1) rc = 0;
   DEBUG_YREGEX  yLOG_value   ("return"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         main driver                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char
yREGEX__exec_regex   (int a_start)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_rpos      =    0;
   uchar       x_mod       =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("g_rlen"    , g_rlen);
   for (x_rpos = 0; x_rpos < g_rlen; ++x_rpos) {
      DEBUG_YREGEX  yLOG_value   ("x_rpos"    , x_rpos);
      x_mod  = g_mods [x_rpos];
      DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
      switch (x_mod) {
      case '*' : case '+' : case '?' : case '{' :
         DEBUG_YREGEX  yLOG_note    ("run a greedy check");
         rc = yREGEX__exec_greedy ( 1, a_start, x_rpos);
         break;
      case '@' : case '~' : case '!' : case '}' :
         DEBUG_YREGEX  yLOG_note    ("run a lazy check");
         rc = yREGEX__exec_lazy   ( 1, a_start, x_rpos);
         break;
      default  :
         DEBUG_YREGEX  yLOG_note    ("run a single char check");
         rc = yREGEX__exec_doer   ( 1, a_start, x_rpos);
         break;
      }
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yREGEX_exec          (cchar *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_start     =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_source"  , a_source);
   /*---(prepare)------------------------*/
   rc = yREGEX__exec_init   (a_source);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(parse)--------------------------*/
   DEBUG_YREGEX  yLOG_value   ("g_slen"    , g_slen);
   for (x_start = 0; x_start < g_clen; ++x_start) {
      DEBUG_YREGEX  yLOG_value   ("START AT"  , x_start);
      rc = yREGEX__exec_regex (x_start);
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      if (rc == 1) break;
   }
   /*---(check)--------------------------*/
   if (rc != 1) rc = 0;
   DEBUG_YREGEX  yLOG_value   ("return"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}
