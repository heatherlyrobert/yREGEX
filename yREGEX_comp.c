/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"

/* NEXT STEPS
 *
 * add formal errors (yregex_error_add)
 *
 *
 *
 *
 *
 */


/*
 *   CHAR       comp  indx  mods  jump
 *     n         n           -
 *
 *   SET        comp  indx  mods  jump
 *     [...]     [     .     -
 *
 *   ANCHORS    comp  indx  mods  jump
 *      ^        ^           ^              BOL
 *      $        $           $              EOL
 *      <        <     6     <              BOW
 *      >        >     6     >              EOW
 *
 *   GROUPS     comp  indx  mods  jump
 *      (        (     .           .
 *      |        |     .           .
 *      )        )     .     -      
 *
 *   QUAN       comp  indx  mods  jump
 *
 *
 *
 *
 */




/*---(group shared variables)---------*/





/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char         /*-> tbd --------------------------------[ shoot  [fe.C73.144.31]*/ /*-[01.0000.01#.Z]-*/ /*-[--.---.---.--]-*/
yregex_comp__prep    (cchar *a_regex)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_regex"   , a_regex);
   /*---(check regex)--------------------*/
   --rce;  if (a_regex  == NULL) {
      DEBUG_YREGEX  yLOG_note    ("can not be null");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (myREGEX.input, a_regex, LEN_REGEX);
   /*---(check scorer)-------------------*/
   if (strchr (G_PREFIX, a_regex [0]) != NULL) {
      myREGEX.scorer = a_regex [0];
      rc = snprintf (myREGEX.orig , LEN_REGEX, "(%s)", a_regex + 1);
   } else {
      myREGEX.scorer = '?';
      rc = snprintf (myREGEX.orig , LEN_REGEX, "(%s)", a_regex);
   }
   /*---(copy regex)---------------------*/
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   --rce;  if (rc     <  0   ) {
      DEBUG_YREGEX  yLOG_note    ("truncated copy");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate extended chars)-------*/
   DEBUG_YREGEX  yLOG_info    ("before"    , myREGEX.orig);
   myREGEX.olen = strllen (myREGEX.orig  , LEN_REGEX);
   DEBUG_YREGEX  yLOG_value   ("myREGEX.olen"  , myREGEX.olen);
   yregex_comp__extended ();
   DEBUG_YREGEX  yLOG_info    ("myREGEX.orig"  , myREGEX.orig);
   myREGEX.olen = strllen (myREGEX.orig  , LEN_REGEX);
   DEBUG_YREGEX  yLOG_value   ("myREGEX.olen"  , myREGEX.olen);
   /*---(copy regex)---------------------*/
   strlcpy  (myREGEX.regex, myREGEX.orig , LEN_REGEX);
   myREGEX.rlen = myREGEX.olen;
   /*---(initialize compiled)------------*/
   for (i = 0; i < LEN_REGEX; ++i) {
      myREGEX.comp [i] =   0;
      myREGEX.indx [i] =   0;
      myREGEX.mods [i] =   0;
      myREGEX.jump [i] =   0;
   }
   myREGEX.clen = 0;
   /*---(initialize grouping)------------*/
   yregex_group_init ();
   /*> myREGEX.g_lvl   =  0;                                                          <* 
    *> myREGEX.g_cnt   =  0;                                                          <* 
    *> myREGEX.g_hid  = 10;                                                           <* 
    *> myREGEX.g_foc   = '-';                                                         <* 
    *> strlcpy (myREGEX.g_mrk, "               ", LEN_LABEL);                         <*/
   /*---(reset elements)-----------------*/
   yregex_error_reset ();
   yregex_sets_reset  ();
   yregex_pats_reset  ();
   yregex_rule_init   ();
   myREGEX.ready = '-';
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        data structure                        ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

char         /*-> tbd --------------------------------[ leaf   [fz.632.201.00]*/ /*-[00.0000.06#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp_add         (cchar a_comp, cint a_indx)
{
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (a_comp);
   DEBUG_YREGEX  yLOG_sint    (a_indx);
   DEBUG_YREGEX  yLOG_sint    (myREGEX.clen);
   myREGEX.comp [myREGEX.clen] = a_comp;
   myREGEX.indx [myREGEX.clen] = a_indx;
   myREGEX.mods [myREGEX.clen] = ' ';
   myREGEX.jump [myREGEX.clen] = 0;
   ++myREGEX.clen;
   DEBUG_YREGEX  yLOG_sint    (myREGEX.clen);
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fz.412.301.00]*/ /*-[00.0000.02#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp_mod         (cchar a_mod)
{
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (a_mod);
   myREGEX.mods [myREGEX.clen - 1] = a_mod;
   DEBUG_YREGEX  yLOG_sint    (myREGEX.clen - 1);
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fz.632.201.00]*/ /*-[00.0000.06#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp__dup_one        (void)
{
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (myREGEX.comp [myREGEX.clen - 1]);
   DEBUG_YREGEX  yLOG_sint    (myREGEX.indx [myREGEX.clen - 1]);
   DEBUG_YREGEX  yLOG_sint    (myREGEX.clen);
   myREGEX.comp [myREGEX.clen] = myREGEX.comp [myREGEX.clen - 1];
   myREGEX.indx [myREGEX.clen] = myREGEX.indx [myREGEX.clen - 1];
   myREGEX.mods [myREGEX.clen] = myREGEX.mods [myREGEX.clen - 1];
   myREGEX.jump [myREGEX.clen] = myREGEX.jump [myREGEX.clen - 1];
   ++myREGEX.clen;
   DEBUG_YREGEX  yLOG_sint    (myREGEX.clen);
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fz.632.201.00]*/ /*-[00.0000.06#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp__dup_group  (void)
{
   int         x_beg       = 0;
   int         x_end       = 0;
   int         i           = 0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("myREGEX.clen"  , myREGEX.clen);
   x_end = myREGEX.clen - 1;
   yregex_group_endpoints (x_end, &x_beg, NULL);
   DEBUG_YREGEX  yLOG_value   ("x_beg"     , x_beg);
   DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
   for (i = x_beg; i <= x_end; ++i) {
      DEBUG_YREGEX  yLOG_value   ("pos"       , i);
      yregex_comp_add (myREGEX.comp [i], myREGEX.indx [i]);
      if (strchr ("(|)", myREGEX.comp [i]) != NULL)  myREGEX.indx [myREGEX.clen - 1] = myREGEX.g_mul;
      yregex_comp_mod (myREGEX.mods [i]);
      myREGEX.jump [myREGEX.clen - 1] = myREGEX.jump [i];
   }
   ++myREGEX.g_mul;
   DEBUG_YREGEX  yLOG_value   ("myREGEX.g_mul", myREGEX.g_mul);
   DEBUG_YREGEX  yLOG_value   ("myREGEX.clen"  , myREGEX.clen);
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      literal handling                        ----===*/
/*====================------------------------------------====================*/
static void      o___LITERAL_________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [fe.833.134.31]*/ /*-[01.0000.01#.6]-*/ /*-[--.---.---.--]-*/
yregex_comp__literal        (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_ch        =  '-';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(check)--------------------------*/
   x_ch  = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   rc = yregex_comp_add  (x_ch, 0);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                       modifier handling                      ----===*/
/*====================------------------------------------====================*/
static void      o___MODS____________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [fe.732.151.11]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp__quan_simp  (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   uchar       x_set       =    0;
   char        t           [LEN_NAME] = "";
   char        x_mod       =  ' ';
   char        x_pch       =  ' ';
   int         x_beg       =   -1;
   int         x_end       =   -1;
   int         x_len       =   -1;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_mod  = myREGEX.regex [*a_rpos];
   x_pch  = myREGEX.regex [*a_rpos - 1];
   DEBUG_YREGEX  yLOG_value   ("x_mod"     , x_mod);
   DEBUG_YREGEX  yLOG_value   ("x_pch"     , x_pch);
   /*---(handle shared)------------------*/
   switch (x_mod) {
   case '*' : case '@' :
      DEBUG_YREGEX  yLOG_note    ("any modifier * (greedy) and @ (lazy)");
      yregex_comp_mod (x_mod);
      break;
   case '?' : case '!' :
      DEBUG_YREGEX  yLOG_note    ("one modifier ? (greedy) and ! (lazy)");
      yregex_comp_mod (x_mod);
      break;
   case '+' : case '~' :
      DEBUG_YREGEX  yLOG_note    ("many modifier + (greedy) and ~ (lazy)");
      if (x_pch == ')')  yregex_comp__dup_group   ();
      else               yregex_comp__dup_one     ();
      if (x_mod == '+')  yregex_comp_mod   ('*');
      else               yregex_comp_mod   ('@');
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> tbd --------------------------------[ ------ [fe.I86.1C3.D1]*/ /*-[03.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp__quan_comp   (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   uchar       x_set       =    0;
   char        t           [LEN_NAME] = "";
   uchar       x_ch        =  ' ';
   uchar       x_mod       =  ' ';
   uchar       x_pch       =  ' ';
   int         i           =    0;
   char        x_lazy      =  '-';
   int         x_min       =   -1;
   int         x_max       =   -1;
   int         x_len       =    0;
   char        x_comma     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   --rce;  if (x_ch != '{') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a {");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_pch  = myREGEX.regex [*a_rpos - 1];
   /*---(check for lazy modifier)--------*/
   x_mod  = myREGEX.regex [++(*a_rpos)];
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   if (x_mod == '-') {
      DEBUG_YREGEX  yLOG_note    ("found lazy modifer");
      x_lazy = 'y';
      x_mod   = myREGEX.regex [++(*a_rpos)];
      DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
      DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   }
   /*---(walk modifier)------------------*/
   while (1) {
      DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
      if (*a_rpos >= myREGEX.rlen) {
         DEBUG_YREGEX  yLOG_note    ("hit end of string");
         break;
      }
      if (x_mod == '}') {
         DEBUG_YREGEX  yLOG_note    ("found end of modifier");
         if (x_len > 0) {
            sprintf (t, "%*.*s", x_len, x_len, myREGEX.regex + *a_rpos - x_len);
            DEBUG_YREGEX  yLOG_info    ("t"         , t);
            x_max = atoi (t);
         } else {
            x_max = MAX_QUAN;
         }
         DEBUG_YREGEX  yLOG_value   ("x_max"     , x_max);
         break;
      }
      if (x_mod == ',') {
         DEBUG_YREGEX  yLOG_note    ("found comma separator");
         x_comma = 'y';
         if (x_len == 0) {
            DEBUG_YREGEX  yLOG_note    ("min specifier is empty, use zero");
            x_min = 0;
         } else {
            DEBUG_YREGEX  yLOG_note    ("found real min specifier");
            sprintf (t, "%*.*s", x_len, x_len, myREGEX.regex + *a_rpos - x_len);
            DEBUG_YREGEX  yLOG_info    ("t"         , t);
            x_min = atoi (t);
         }
         x_len = -1; /* don't count comma */
         DEBUG_YREGEX  yLOG_value   ("x_min"     , x_min);
      }
      x_mod   = myREGEX.regex [++(*a_rpos)];
      ++x_len;
      DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
      DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   }
   /*---(check)--------------------------*/
   --rce;  if (x_max <= 0) {
      DEBUG_YREGEX  yLOG_note    ("max can not be empty or zero");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (x_comma == '-')   x_min = x_max;
   /*---(update)-------------------------*/
   DEBUG_YREGEX  yLOG_note    ("update modifier");
   /*---(zero or more)-------------------*/
   if (x_min == 0) {
      if (x_max >= MAX_QUAN) {
         if (x_lazy == 'y')  yregex_comp_mod ('@');
         else                yregex_comp_mod ('*');
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 1;
      }
      if (x_lazy == 'y')  yregex_comp_mod ('!');
      else                yregex_comp_mod ('?');
      for (i = 1; i < x_max; ++i) {
         if (x_pch == ')')  yregex_comp__dup_group   ();
         else               yregex_comp__dup_one     ();
      }
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(one or more)--------------------*/
   for (i = 1; i < x_min; ++i) {
      if (x_pch == ')')  yregex_comp__dup_group   ();
      else               yregex_comp__dup_one     ();
   }
   if (x_max > x_min) {
      if (x_max >= MAX_QUAN) {
         if (x_pch  == ')')  yregex_comp__dup_group   ();
         else                yregex_comp__dup_one     ();
         if (x_lazy == 'y')  yregex_comp_mod ('@');
         else                yregex_comp_mod ('*');
      } else {
         for (i = x_min; i < x_max; ++i) {
            if (x_pch  == ')')  yregex_comp__dup_group   ();
            else                yregex_comp__dup_one     ();
            if (x_lazy == 'y')  yregex_comp_mod ('!');
            else                yregex_comp_mod ('?');
         }
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                       extended characters                    ----===*/
/*====================------------------------------------====================*/
static void      o___EXTENDED________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [ge.E54.142.98]*/ /*-[02.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yregex_comp__extended   (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   uchar       x_ch        =  ' ';          /* current character              */
   char        t           [LEN_REGEX] = "";
   int         x_len       =    0;
   /*---(translate)----------------------*/
   for (i = 0; i <= myREGEX.olen; ++i) {
      x_ch = myREGEX.orig [i];
      switch (x_ch) {
      case G_CHAR_STORAGE : case G_CHAR_BIGDOT  : case G_CHAR_HALT    :
         /* just a spacer, not used  */
         break;
      case G_CHAR_DBSLASH :  /* delayed backslash      */
         t [x_len++] = '\\';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_DDQUOTE :  /* delayed double quote   */
         t [x_len++] = '\"';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_EQUIV :  /* equal                  */
         t [x_len++] = '=';
         t [x_len++] = '=';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_NE :  /* not equal              */
         t [x_len++] = '!';
         t [x_len++] = '=';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_LE :  /* less than or equal     */
         t [x_len++] = '<';
         t [x_len++] = '=';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_GE :  /* greater than or equal  */
         t [x_len++] = '>';
         t [x_len++] = '=';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_SPACE :  /* space                  */
         t [x_len++] = ' ';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_MASK  :  /* mask */
         t [x_len++] = '.';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_REDACT : /* redacted */
         t [x_len++] = '.';
         t [x_len++] = '*';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_SLPAREN :  /* begin capture group    */
         t [x_len++] = '(';
         t [x_len++] = '#';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_SRPAREN :  /* end capture group      */
         t [x_len++] = ')';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_SLCHEV :  /* begin focus group      */
         t [x_len++] = '(';
         t [x_len++] = '>';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_SRCHEV :  /* end focus group        */
         t [x_len++] = '<';
         t [x_len++] = ')';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_SLBRACK :  /* begin rule group       */
         t [x_len++] = '(';
         t [x_len++] = ';';
         t [x_len  ] =  0 ;
         break;
      case G_CHAR_SRBRACK :  /* end rule group         */
         t [x_len++] = ')';
         t [x_len  ] =  0 ;
         break;
      default  :
         t [x_len++] = x_ch;
         t [x_len  ] =  0 ;
         break;
      }
   }
   /*---(copy over)----------------------*/
   strlcpy (myREGEX.orig, t, LEN_REGEX);
   myREGEX.olen = strllen (myREGEX.orig, LEN_REGEX);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         main driver                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [ge.E54.142.98]*/ /*-[02.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yREGEX_comp          (cchar *a_regex)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   uchar       x_ch        =  ' ';          /* current character              */
   uchar       x_nch       =  ' ';          /* next character                 */
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_regex"   , a_regex);
   /*---(prepare)------------------------*/
   rc = yregex_comp__prep (a_regex);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(translate)----------------------*/
   DEBUG_YREGEX  yLOG_info    ("tranlated" , myREGEX.orig);
   DEBUG_YREGEX  yLOG_value   ("myREGEX.olen"  , myREGEX.olen);
   /*---(pattern run)--------------------*/
   rc = yregex_pats_comp ();
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
      yregex_error_fancify ();
      return rc;
   }
   /*---(parse)--------------------------*/
   DEBUG_YREGEX  yLOG_info    ("myREGEX.regex" , myREGEX.regex);
   DEBUG_YREGEX  yLOG_value   ("myREGEX.rlen"  , myREGEX.rlen);
   for (i = 0; i < myREGEX.rlen; ++i) {
      /*---(check last run)--------------*/
      if (rc < 0) break;
      DEBUG_YREGEX  yLOG_value   ("LOOP"      , i);
      /*---(prepare)---------------------*/
      x_ch   = myREGEX.regex [i];
      x_nch  = myREGEX.regex [i + 1];
      /*---(backslashed metas)-----------*/
      if (x_ch == G_KEY_BSLASH) {
         DEBUG_YREGEX  yLOG_note    ("handle escaped character");
         rc = yregex_sets_backslash (&i);
         continue;
      }
      /*---(dot)-------------------------*/
      if (x_ch == '.') {
         DEBUG_YREGEX  yLOG_note    ("handle dot character");
         rc = yregex_sets_dot (&i);
         continue;
      }
      /*---(rules handling)--------------*/
      if (x_ch == '(' && x_nch == ';' && i > 0) {
         DEBUG_YREGEX  yLOG_note    ("handle special rules");
         rc = yregex_group_comp (&i);
         rc = yregex_rule_comp  (&i);
         continue;
      }
      /*---(group handling)--------------*/
      if (strchr (TYPE_GROUP, x_ch) != NULL || (x_ch == '<' && x_nch == ')')) {
         DEBUG_YREGEX  yLOG_note    ("handle grouping");
         rc = yregex_group_comp (&i);
         if (rc >= 0)  continue;
         if (rc <  0)  break;
      }
      /*---(anchors)---------------------*/
      if (strchr (G_ANCHOR, x_ch) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("handle anchors");
         rc = yregex_comp_add (x_ch, yregex_sets__by_abbr ('w', NULL));
         if (rc >= 0)  continue;
         if (rc <  0)  break;
      }
      /*---(set handling)----------------*/
      if (strchr ("[]", x_ch) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("handle character set");
         rc = yregex_sets_comp (&i);
         if (rc >= 0)  continue;
         if (rc <  0)  break;
      }
      /*---(quick modifiers)-------------*/
      if (strchr (TYPE_QUANS, x_ch) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("handle simple modifier");
         rc = yregex_comp__quan_simp (&i);
         continue;
      }
      /*---(specific quantifiers)--------*/
      if (x_ch == '{') {
         DEBUG_YREGEX  yLOG_note    ("handle complex modifier");
         rc = yregex_comp__quan_comp (&i);
         continue;
      }
      /*---(literals)--------------------*/
      DEBUG_YREGEX  yLOG_note    ("handle character literal");
      rc = yregex_comp__literal (&i);
   }
   /*---(summarize)----------------------*/
   yregex_error_fancify ();
   /*---(check for failure)--------------*/
   myREGEX.ready = 'n';
   --rce;  if (myREGEX.g_lvl != 0) {
      DEBUG_YREGEX  yLOG_note    ("parenthesis do not balance");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_note    ("compilation failed");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   myREGEX.ready = 'y';
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char        unit_answer  [LEN_TEXT];

char         /*-> unit test accessor -----------------[ light  [us.D90.241.L0]*/ /*-[03.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yregex_comp__unit_map   (char a_type, int a_value)
{
   char        x_ch        = ' ';
   char       *x_range     = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range2    = " 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range3    = " .123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ**********************************************************************";
   char       *x_range4    = " 0123456789.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ**********************************************************************";
   switch (a_type) {
   case '(' :
      if      (a_value >= 65 )           x_ch = '*';
      else                               x_ch = x_range4 [a_value];
      break;
   case 'i' :
      if      (a_value >= 65 )           x_ch = '*';
      else                               x_ch = x_range [a_value];
      break;
   case 'm' : case 'x' : case 'j' :
      if      (a_value ==  0)            x_ch = ' ';
      else if (a_value >= 62)            x_ch = '*';
      else                               x_ch = x_range [a_value];
      break;
   }
   return x_ch;
}

char*        /*-> unit test accessor -----------------[ light  [us.D90.241.L0]*/ /*-[03.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yregex_comp__unit       (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   char        t           [100] = "";
   int         c           = 0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "COMP__unit, unknown request", 100);
   /*---(core data)----------------------*/
   if        (strncmp (a_question, "regex"     , 20)  == 0) {
      if (myREGEX.rlen < 100)  sprintf  (t, "%2d", myREGEX.rlen);
      else                 sprintf  (t, "%2s", "++");
      snprintf (unit_answer, LEN_TEXT, "COMP regex       : %2s [%-45.45s]", t, myREGEX.regex);
   }
   /*---(mapping)------------------------*/
   /*> else if (strncmp (a_question, "map"       , 20)  == 0) {                                                                    <* 
    *>    strlcpy (t, "0123456789abcdef0123456789abcdef", 100);                                                                    <* 
    *>    if (a_num < 0 || a_num > 15)                                                                                             <* 
    *>       snprintf (unit_answer, LEN_TEXT, "yREGEX_comp map  : %x %3d %2d [%-32.32s]", 0    , s_mapcount, 0, "unknown area");   <* 
    *>    else                                                                                                                     <* 
    *>       for (i = 0; i < 32; ++i)  if (s_map [a_num * 32 + i] == '.') {                                                        <* 
    *>          t [i] = '_';                                                                                                       <* 
    *>          ++c;                                                                                                               <* 
    *>       }                                                                                                                     <* 
    *>    snprintf (unit_answer, LEN_TEXT, "yREGEX_comp map  : %x %3d %2d [%-32.32s]", a_num * 2, s_mapcount, c, t);               <* 
    *> }                                                                                                                           <*/
   /*---(compiled)-----------------------*/
   else if   (strncmp (a_question, "base"      , 20)  == 0) {
      snprintf (unit_answer, LEN_TEXT, "COMP base        : %2d [%-45.45s]", myREGEX.clen, myREGEX.comp);
   } else if (strncmp (a_question, "indx"      , 20)  == 0) {
      for (i = 0; i < 45; ++i) {
         if      (strchr ("(|&)"   , myREGEX.comp [i]) != NULL)  t [i] = yregex_comp__unit_map ('(', myREGEX.indx [i]);
         else if (strchr ("[]^$<>;", myREGEX.comp [i]) != NULL)  t [i] = yregex_comp__unit_map ('i', myREGEX.indx [i]);
         else                                                    t [i] = ' ';
      }
      t [45] = 0;
      snprintf (unit_answer, LEN_TEXT, "COMP indx        : %2d [%-45.45s]", myREGEX.clen, t);
   } else if (strncmp (a_question, "mods"      , 20)  == 0) {
      snprintf (unit_answer, LEN_TEXT, "COMP mods        : %2d [%-45.45s]", myREGEX.clen, myREGEX.mods);
   } else if (strncmp (a_question, "jump"      , 20)  == 0) {
      for (i = 0; i < 45; ++i) {
         if      (myREGEX.comp [i] == ';')  t [i] = yregex_comp__unit_map ('i', myREGEX.jump [i]);
         else                               t [i] = yregex_comp__unit_map ('j', myREGEX.jump [i]);
      }
      t [45] = 0;
      snprintf (unit_answer, LEN_TEXT, "COMP jump        : %2d [%-45.45s]", myREGEX.clen, t);
   } else if (strncmp (a_question, "groups"    , 20)  == 0) {
      snprintf (unit_answer, LEN_TEXT, "COMP groups      : [%-10.10s]", myREGEX.g_mrk);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



/*===============================[[ end code ]]===============================*/
