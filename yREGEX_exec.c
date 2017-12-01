/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



char        g_source    [LEN_RECD]  = "";
int         g_slen      = -1;
static int  s_begin     =  0;
static int  s_end       =  0;
static int  s_len       =  0;



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
yREGEX__exec_char    (cint a_begin, int a_rpos, int a_tpos)
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
yREGEX__exec_set     (cint a_begin, int a_rpos, int a_tpos)
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
yREGEX__exec_doer    (cint a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend)
{
   /*---(design notes)-------------------*/
   /*
    *   mode = 'r' means recurse and prove
    *   mode = 'c' means just check the match and reply back
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_indx      =    0;
   int         x_tend      = *a_tend;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_begin"   , a_begin);
   DEBUG_YREGEX  yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YREGEX  yLOG_value   ("a_tpos"    , a_tpos);
   DEBUG_YREGEX  yLOG_value   ("a_rpos"    , a_rpos);
   DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
   /*---(defenses)-----------------------*/
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
   /*---(check)--------------------------*/
   if (x_indx > 0)  rc = yREGEX__exec_set  (a_begin, a_rpos, a_tpos);
   else             rc = yREGEX__exec_char (a_begin, a_rpos, a_tpos);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   /*---(resurse)------------------------*/
   if (a_mode == 'r' && rc == 1) {
      ++a_rpos;
      ++a_tpos;
      if (a_rpos >= g_clen) {
         DEBUG_YREGEX  yLOG_note    ("end of compiled regex");
         rc = 1;
         *a_tend = a_tpos - 1;
         DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
      } else  {
         DEBUG_YREGEX  yLOG_note    ("resursing to next level");
         rc = yREGEX__exec_next (a_begin, '-', a_rpos, a_tpos, &x_tend);
         if (rc == 1) {
            *a_tend = x_tend;
            DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
         }
      }
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                     multiple matching                        ----===*/
/*====================------------------------------------====================*/
static void      o___MULTIPLE________________o (void) {;}

char
yREGEX__exec_multi   (int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend) 
{
   /*---(design notes)-------------------*/
   /*
    *   mode = 'L' means lazy matching, shortest possible
    *   mode = 'G' means greedy matching, longest possible
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_tend      = *a_tend;
   int         x_rem       =    0;
   uchar       x_min       =    0;
   uchar       x_max       =    0;
   int         x_pos       = a_tpos;
   int         i           =    0;
   int         x_match     =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_begin"   , a_begin);
   DEBUG_YREGEX  yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YREGEX  yLOG_value   ("a_rpos"    , a_rpos);
   DEBUG_YREGEX  yLOG_value   ("a_tpos"    , a_tpos);
   DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
   /*---(prepare)------------------------*/
   x_rem  = g_slen - a_tpos;
   DEBUG_YREGEX  yLOG_value   ("x_rem"     , x_rem);
   x_min  = g_mins [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_min"     , x_min);
   --rce;  if (x_min > x_rem) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_max  = g_maxs [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_max"     , x_max);
   if (x_max > x_rem) {
      x_max = x_rem;
      DEBUG_YREGEX  yLOG_value   ("x_max (a)" , x_max);
   }
   /*---(check for required)-------------*/
   DEBUG_YREGEX  yLOG_note    ("CHECKING up to the minimum");
   for (i = 0; i < x_min; ++i) {
      DEBUG_YREGEX  yLOG_value   ("looping"   , i);
      rc = yREGEX__exec_doer   (a_begin, 'c', a_rpos, a_tpos++, &x_tend);
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      if (rc <= 0) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      ++x_match;
      DEBUG_YREGEX  yLOG_value   ("x_match"   , x_match);
   }
   /*---(check for additional)-----------*/
   DEBUG_YREGEX  yLOG_note    ("CHECKING the main range");
   for (i = x_min; i <  x_max; ++i) {
      DEBUG_YREGEX  yLOG_value   ("looping"   , i);
      if (a_mode == 'G') {
         rc = yREGEX__exec_doer   (a_begin, 'c', a_rpos, a_tpos++, &x_tend);
         DEBUG_YREGEX  yLOG_value   ("greed rc"  , rc);
         if (rc == 0) break;
      }
      if (a_mode == 'L') {
         rc = yREGEX__exec_doer   (a_begin, 'r', a_rpos, a_tpos++, &x_tend);
         DEBUG_YREGEX  yLOG_value   ("lazy rc"   , rc);
         if (rc == 1) {
            *a_tend = x_tend;
            DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
            DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
            return 1;
         }
      }
      ++x_match;
   }
   /*---(now do greedy for real)---------*/
   if (a_mode == 'G') {
      --a_tpos;
      DEBUG_YREGEX  yLOG_note    ("CHECKING backward run for greedy");
      for (i = x_match; i >= x_min - 1; --i) {
         DEBUG_YREGEX  yLOG_value   ("looping"   , i);
         rc = yREGEX__exec_doer   (a_begin, 'r', a_rpos, a_tpos--, &x_tend);
         DEBUG_YREGEX  yLOG_value   ("greedy rc" , rc);
         if (rc == 1) {
            *a_tend = x_tend;
            DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
            DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
            return 1;
         }
      }
   }
   DEBUG_YREGEX  yLOG_note    ("FELL out of the bottom");
   /*---(failed)-------------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yREGEX__exec_next    (int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend) 
{
   /*---(design notes)-------------------*/
   /*
    * this is launched once for every position/quantifier-inc in the regex
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_tend      = *a_tend;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_begin"   , a_begin);
   DEBUG_YREGEX  yLOG_char    ("a_mode"    , a_mode);
   DEBUG_YREGEX  yLOG_value   ("a_rpos"    , a_rpos);
   DEBUG_YREGEX  yLOG_value   ("a_tpos"    , a_tpos);
   DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
   /*---(launch checkers)----------------*/
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , g_mods [a_rpos]);
   switch (g_mods [a_rpos]) {
   case '*' : case '+' : case '?' : case '{' :
      DEBUG_YREGEX  yLOG_note    ("run a greedy check");
      rc = yREGEX__exec_multi  (a_begin, 'G', a_rpos, a_tpos, &x_tend);
      break;
   case '@' : case '~' : case '!' : case '}' :
      DEBUG_YREGEX  yLOG_note    ("run a lazy check");
      rc = yREGEX__exec_multi  (a_begin, 'L', a_rpos, a_tpos, &x_tend);
      break;
   default  :
      DEBUG_YREGEX  yLOG_note    ("run a single char check");
      rc = yREGEX__exec_doer   (a_begin, 'r', a_rpos, a_tpos, &x_tend);
      break;
   }
   /*---(check)--------------------------*/
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   DEBUG_YREGEX  yLOG_value   ("x_tend"    , x_tend);
   if (rc == 1) {
      *a_tend = x_tend;
      DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
   }
   else           rc    = 0;
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
yREGEX_exec          (cchar *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_begin     =    0;
   int         x_tend      =    0;
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
   DEBUG_YREGEX  yLOG_info    ("a_source"  , a_source);
   DEBUG_YREGEX  yLOG_value   ("g_slen"    , g_slen);
   s_begin = s_end = s_len = -1;
   for (x_begin = 0; x_begin < g_slen; ++x_begin) {
      DEBUG_YREGEX  yLOG_value   ("BEGIN AT"  , x_begin);
      rc = yREGEX__exec_next (x_begin, '-', 0, x_begin, &x_tend);
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      if (rc == 1) {
         s_begin = x_begin;
         s_end   = x_tend;
         s_len   = x_tend - x_begin + 1;
         break;
      }
   }
   DEBUG_YREGEX  yLOG_value   ("s_begin"   , s_begin);
   DEBUG_YREGEX  yLOG_value   ("s_end"     , s_end);
   DEBUG_YREGEX  yLOG_value   ("s_len"     , s_len);
   /*---(check)--------------------------*/
   if (rc != 1) rc = 0;
   DEBUG_YREGEX  yLOG_value   ("return"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /* [------] unit test accessor ------------------------------*/
yREGEX__unitexec   (char *a_question, int a_num)
{
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "REGEX_unitexec, unknown request", 100);
   /*---(mapping)------------------------*/
   if      (strncmp (a_question, "begin"     , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "yREGEX_exec begin: %3d", s_begin);
   }
   else if (strncmp (a_question, "stat"      , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "yREGEX_exec stat : beg=%3d, end=%3d, len=%3d", s_begin, s_end, s_len);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



