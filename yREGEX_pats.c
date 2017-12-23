/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



/*---(patterns)-------------*/
#define     MAX_PATS       250
typedef struct cPATS  tPATS;
struct cPATS {
   char        abbr;                        /* shortcut name                  */
   char        name        [LEN_NAME];      /* pattern name                   */
   char        pat         [LEN_PAT ];      /* actual pattern                 */
   int         len;                         /* length of name                 */
   int         size;                        /* length of pattern              */
};
static tPATS       s_pats [MAX_PATS] = {
   /*      0         1            0         1         2         3         4         5         6         7         8         9         A         B         C         D         E         F                  */
   /*1234  01234567890123456789   01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890        */
   /*abbr  ---name-------------   ---pattern-------------------------------------------------------------------------------------------------------------------------------------------------------  ln sz */
   { '-', "----empty----"      , ""                                                                                                                                                                 , 0, 0 },
   { 'f', "float"              , "(-)?(0|[1-9][0-9]*)([.][0-9]+)?"                                                                                                                                  , 0, 0 },
   { 'b', "byte"               , "25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9]"                                                                                                                 , 0, 0 },
   { 'i', "int"                , "(-)?(0|[1-9][0-9]*)"                                                                                                                                              , 0, 0 },
   { 'w', "word"               , "<\\w*>"                                                                                                                                                           , 0, 0 },
   {  0 , ""                   , ""                                                                                                                                                                 , 0, 0 },
};
static int       s_npat      = 0;
static int       s_nsave     = 0;



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char         /*-> initialize pattern database --------[ leaf   [fz.531.021.10]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
PATS__init           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   char       *x_valid     = "-abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(initialize sets)----------------*/
   s_npat = 0;
   for (i = 0; i < MAX_PATS; ++i) {
      if (s_pats [i].abbr == 0)  break;
      if (strchr (x_valid, s_pats [i].abbr) == NULL)  break;
      ++s_npat;
      s_pats [i].len  = strllen (s_pats [i].name, LEN_NAME);
      s_pats [i].size = strllen (s_pats [i].pat , LEN_PAT );
      DEBUG_YREGEX  yLOG_info    ("check"     , s_pats [i].name);
   }
   DEBUG_YREGEX  yLOG_value   ("s_npat"    , s_npat);
   /*---(other)--------------------------*/
   s_nsave = 0;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      finding patterns                        ----===*/
/*====================------------------------------------====================*/
static void      o___FINDING_________________o (void) {;}

int          /*-> retrieve pattern by abbeviation ----[ leaf   [fc.632.122.40]*/ /*-[01.0000.01#.8]-*/ /*-[--.---.---.--]-*/
PATS__by_abbr        (cchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (a_abbr);
   /*---(defense)------------------------*/
   --rce;  if (a_abbr == 0) {
      DEBUG_YREGEX  yLOG_snote   ("can not be null");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr (x_valid, a_abbr) == NULL) {
      DEBUG_YREGEX  yLOG_snote   ("abbr must be [A-Za-z]");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_schar   (a_abbr);
   DEBUG_YREGEX  yLOG_sint    (s_npat);
   /*---(walk through sets)--------------*/
   for (i = 0; i < s_npat; ++i) {
      if (s_pats [i].abbr == 0     )  break;
      if (s_pats [i].abbr == '-'   )  continue;
      if (s_pats [i].abbr != a_abbr)  continue;
      DEBUG_YREGEX  yLOG_snote   ("found");
      DEBUG_YREGEX  yLOG_sint    (i);
      DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
      return i;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_snote   ("not found");
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return -1;
}

int          /*-> retrieve pattern by name -----------[ leaf   [fe.A53.145.A0]*/ /*-[01.0000.02#.E]-*/ /*-[--.---.---.--]-*/
PATS__by_name        (cchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_name"    , a_name);
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_info    ("a_name"    , a_name);
   x_len = strllen (a_name, LEN_NAME);
   DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <  3) {
      DEBUG_YREGEX  yLOG_note    ("too short");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len >  15) {
      DEBUG_YREGEX  yLOG_note    ("too long");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   for (i = 0; i < s_npat; ++i) {
      if (s_pats [i].abbr ==  0 )                     break;
      if (s_pats [i].len      != x_len     )          continue;
      if (s_pats [i].name [0] != a_name [0])          continue;
      if (strcmp (s_pats [i].name, a_name) != 0)      continue;
      DEBUG_YREGEX  yLOG_value   ("found"     , i);
      DEBUG_YREGEX  yLOG_sint    (i);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return i;
   }
   DEBUG_YREGEX  yLOG_note    ("not found");
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return -1;
}

char         /*-> compile a pattern ------------------[ ------ [fe.D54.156.65]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
PATS__abbr_ref       (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   int         i           =    0;
   int         x_pat       =    0;
   char        x_abbr      =  ' ';
   char        x_ch        =  ' ';
   char        x_pch       =    0;
   char        x_ppch      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = gre.orig [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != '&') {
      COMP_error (__FUNCTION__, a_rpos, "#PAT", "does not lead with a dollar sign");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (*a_rpos > 0)   x_pch  = gre.orig [*a_rpos - 1];
   if (*a_rpos > 1)   x_ppch = gre.orig [*a_rpos - 2];
   /*---(find name)----------------------*/
   ++(*a_rpos);
   x_abbr   = gre.orig [*a_rpos];
   /*---(abbreviated name)---------------*/
   DEBUG_YREGEX  yLOG_note    ("using abbreviated name");
   x_pat = PATS__by_abbr (x_abbr);
   DEBUG_YREGEX  yLOG_value   ("x_pat"     , x_pat);
   if (x_pat < 0) {
      COMP_error (__FUNCTION__, a_rpos, "#PAT", "not a valid pattern abbreviation");
      ++(*a_rpos);
      strlcat (gre.regex, "#PAT", LEN_REGEX);
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(full name)----------------------*/
   ++(*a_rpos);
   x_ch   = gre.orig [*a_rpos];
   if        (x_pch  == '(' && x_ch  == ')') {
      strlcat (gre.regex, s_pats [x_pat].pat, LEN_REGEX);
   } else if (x_ppch == '(' && x_pch == '#' && x_ch == ')') {
      strlcat (gre.regex, s_pats [x_pat].pat, LEN_REGEX);
   } else {
      strlcat (gre.regex, "("               , LEN_REGEX);
      strlcat (gre.regex, s_pats [x_pat].pat, LEN_REGEX);
      strlcat (gre.regex, ")"               , LEN_REGEX);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> compile a pattern ------------------[ ------ [fe.D54.156.65]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
PATS__named_ref      (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   int         i           =    0;
   int         x_pat       =    0;
   char        x_name      [LEN_NAME] = "";
   char        x_ch        =  ' ';
   int         x_len       =    0;
   int         x_beg       =   -1;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = gre.orig [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != '&') {
      COMP_error (__FUNCTION__, a_rpos, "#PAT", "does not lead with an ampersand");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_beg  = *a_rpos;
   /*---(find name)----------------------*/
   ++(*a_rpos);
   --rce;  for (i = 0; i < LEN_NAME; ++i) {
      x_ch   = gre.orig [*a_rpos + i];
      DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
      if (x_ch == ')')  break;
      x_name [i]     = x_ch;
      x_name [i + 1] = 0;
      DEBUG_YREGEX  yLOG_info    ("x_name"    , x_name);
      ++x_len;
   }
   /*---(troubles)-----------------------*/
   --rce;  if (x_len == 0) {
      COMP_error (__FUNCTION__, a_rpos, "#PAT", "could not parse name");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_ch  != ')') {
      COMP_error (__FUNCTION__, a_rpos, "#PAT", "could not find close paren");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(abbreviated name)---------------*/
   --rce;  if (x_len == 1) {
      DEBUG_YREGEX  yLOG_note    ("using abbreviated name");
      x_pat = PATS__by_abbr (x_name [0]);
      DEBUG_YREGEX  yLOG_value   ("x_pat"     , x_pat);
      if (x_pat < 0) {
         COMP_error (__FUNCTION__, a_rpos, "#PAT", "not a valid pattern abbreviation");
         ++(*a_rpos);
         strlcat (gre.regex, "#PAT", LEN_REGEX);
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++(*a_rpos);
      strlcat (gre.regex, s_pats [x_pat].pat, LEN_REGEX);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(full name)----------------------*/
   --rce;
   DEBUG_YREGEX  yLOG_note    ("trying pattern name");
   x_pat = PATS__by_name (x_name);
   DEBUG_YREGEX  yLOG_value   ("x_pat"     , x_pat);
   if (x_pat < 0) {
      COMP_error (__FUNCTION__, a_rpos, "#PAT", "not a valid pattern name");
      *a_rpos += x_len;
      strlcat (gre.regex, "#PAT", LEN_REGEX);
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(full name)----------------------*/
   *a_rpos += x_len;
   strlcat (gre.regex, s_pats [x_pat].pat, LEN_REGEX);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                       saving patterns                        ----===*/
/*====================------------------------------------====================*/
static void      o___SAVING__________________o (void) {;}

char         /*-> tbd --------------------------------[ leaf   [fe.943.034.30]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
PATS__save           (cchar *a_pattern)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
   char        t           [5] = "";
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   x_len = strllen (a_pattern, LEN_PAT );
   DEBUG_YREGEX  yLOG_sint    (x_len);
   --rce;  if (x_len  <  1) {
      DEBUG_YREGEX  yLOG_snote   ("too short");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len  >= LEN_PAT) {
      DEBUG_YREGEX  yLOG_snote   ("too long");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_sint    (s_nsave);
   --rce;  if (s_nsave >= 10) {
      DEBUG_YREGEX  yLOG_snote   ("can only save 9 patterns");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_sint    (s_npat);
   --rce;  if (s_npat >= MAX_PATS) {
      DEBUG_YREGEX  yLOG_snote   ("no room");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(fill out)-----------------------*/
   sprintf (t, "saved_%d", s_npat + 1);
   s_pats [s_npat].abbr     = '1' + s_nsave;
   strlcpy (s_pats [s_npat].name, t        , LEN_NAME);
   s_pats [s_npat].len      = 7;
   strlcpy (s_pats [s_npat].pat , a_pattern, LEN_PAT );
   s_pats [s_npat].size     = x_len;
   /*---(update count)-------------------*/
   ++s_nsave;
   ++s_npat;
   DEBUG_YREGEX  yLOG_sint    (s_nsave);
   DEBUG_YREGEX  yLOG_sint    (s_npat);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return s_npat - 1;
}

char
PATS__save_run       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   uchar       x_ch        =  ' ';          /* curr character                 */
   uchar       x_pch       =  ' ';          /* prev character                 */
   int         x_prev      =    0;
   int         x_len       =    0;
   char        t           [LEN_REGEX] = "";
   int         x_beg       =    0;
   int         x_end       =    0;
   int         x_nest      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(parse)--------------------------*/
   DEBUG_YREGEX  yLOG_info    ("gre.orig"  , gre.orig);
   DEBUG_YREGEX  yLOG_value   ("gre.olen"  , gre.olen);
   for (i = 0; i < gre.olen; ++i) {
      DEBUG_YREGEX  yLOG_value   ("LOOP"      , i);
      /*---(prepare)---------------------*/
      x_pch  = gre.orig [i - 1];
      x_ch   = gre.orig [i];
      /*---(find beg)--------------------*/
      if (x_pch == '(' && x_ch == '#') {
         DEBUG_YREGEX  yLOG_note    ("found capture group, save pattern");
         x_beg  = i + 1;
         DEBUG_YREGEX  yLOG_value   ("x_beg"     , x_beg);
         x_end  = -1;
         x_nest = 0;
         /*---(find end)-----------------*/
         for (j = x_beg; j < gre.olen; ++j) {
            x_ch  = gre.orig [j];
            switch (x_ch) {
            case '(' :
               ++x_nest;
               break;
            case ')' :
               if (x_nest == 0)  x_end = j - 1;
               --x_nest;
            }
            if (x_end >= 0) break;
         }
         /*---(save pattern)-------------*/
         DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
         if (x_end >= 0) {
            x_len = x_end - x_beg + 1;
            DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
            sprintf (t, "%-*.*s", x_len, x_len, gre.orig + x_beg);
            DEBUG_YREGEX  yLOG_info    ("t"         , t);
            PATS__save (t);
         }
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         main driver                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char
PATS_comp            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   uchar       x_ch        =  ' ';          /* curr character                 */
   uchar       x_pch       =  ' ';          /* prev character                 */
   uchar       x_ppch      =  ' ';          /* prev-prev character            */
   int         x_prev      =    0;
   int         x_len       =    0;
   char        t           [LEN_REGEX] = "";
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   PATS__init     ();
   PATS__save_run ();
   /*---(parse)--------------------------*/
   DEBUG_YREGEX  yLOG_info    ("gre.orig"  , gre.orig);
   DEBUG_YREGEX  yLOG_value   ("gre.olen"  , gre.olen);
   strlcpy (gre.regex , "", LEN_REGEX);
   for (i = 0; i < gre.olen; ++i) {
      DEBUG_YREGEX  yLOG_value   ("LOOP"      , i);
      /*---(prepare)---------------------*/
      x_ppch = x_pch = x_ch = 0;
      if (i > 1) x_ppch = gre.orig [i - 2];
      if (i > 0) x_pch  = gre.orig [i - 1];
      x_ch   = gre.orig [i];
      /*---(named pattern)---------------*/
      if (( x_ppch == '(' && x_pch == '#' && x_ch == '&')  ||
            (x_pch == '(' && x_ch  == '&')) {
         DEBUG_YREGEX  yLOG_note    ("found named potenial pattern");
         x_len = i - x_prev;
         DEBUG_YREGEX  yLOG_complex ("stats"     , "beg %3d, end %3d, len %3d", x_prev, i - 1, x_len);
         sprintf (t, "%-*.*s", x_len, x_len, gre.orig + x_prev);
         DEBUG_YREGEX  yLOG_info    ("t"         , t);
         strlcat (gre.regex, t, LEN_REGEX);
         DEBUG_YREGEX  yLOG_info    ("gre.regex"   , gre.regex);
         rc     = PATS__named_ref (&i);
         x_prev = i;
         DEBUG_YREGEX  yLOG_value   ("x_prev"    , x_prev);
         DEBUG_YREGEX  yLOG_info    ("gre.regex"   , gre.regex);
         gre.rlen = strllen (gre.regex, LEN_REGEX);
      }
      /*---(named pattern)---------------*/
      else if (x_pch != '\\' && x_ch == '&') {
         DEBUG_YREGEX  yLOG_note    ("found abbr pattern");
         x_len = i - x_prev;
         DEBUG_YREGEX  yLOG_complex ("stats"     , "beg %3d, end %3d, len %3d", x_prev, i - 1, x_len);
         sprintf (t, "%-*.*s", x_len, x_len, gre.orig + x_prev);
         DEBUG_YREGEX  yLOG_info    ("t"         , t);
         strlcat (gre.regex, t, LEN_REGEX);
         DEBUG_YREGEX  yLOG_info    ("gre.regex"   , gre.regex);
         rc     = PATS__abbr_ref   (&i);
         x_prev = i;
         DEBUG_YREGEX  yLOG_value   ("x_prev"    , x_prev);
         DEBUG_YREGEX  yLOG_info    ("gre.regex"   , gre.regex);
         gre.rlen = strllen (gre.regex, LEN_REGEX);
      }
      /*---(done)------------------------*/
   }
   /*---(copy last)----------------------*/
   DEBUG_YREGEX  yLOG_complex ("stats"     , "beg %3d", x_prev);
   sprintf (t, "%s", gre.orig + x_prev);
   DEBUG_YREGEX  yLOG_info    ("t"         , t);
   strlcat (gre.regex, t, LEN_REGEX);
   gre.rlen = strllen (gre.regex, LEN_REGEX);
   /*---(show)---------------------------*/
   DEBUG_YREGEX  yLOG_info    ("gre.regex"   , gre.regex);
   DEBUG_YREGEX  yLOG_value   ("gre.rlen"    , gre.rlen);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*===============================[[ end code ]]===============================*/
