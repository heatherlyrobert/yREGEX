/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"

/* NEXT STEPS
 *
 * add formal errors (yregex_err_add)
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
#define     MAX_STACK  100
static int         s_gstack    [MAX_STACK];
static char        s_glevel          =    0;
static int         s_ggroup          =    0;
static int         s_ghidden         =   10;
static int         s_gmulti          =  100;
static char        s_gfocus          =  '-';  /* focus group used (y/-)      */





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
   /*---(check scorer)-------------------*/
   if (strchr (G_PREFIX, a_regex [0]) != NULL) {
      gre.scorer = a_regex [0];
      rc = snprintf (gre.orig , LEN_REGEX, "(%s)", a_regex + 1);
   } else {
      gre.scorer = '?';
      rc = snprintf (gre.orig , LEN_REGEX, "(%s)", a_regex);
   }
   /*---(copy regex)---------------------*/
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   --rce;  if (rc     <  0   ) {
      DEBUG_YREGEX  yLOG_note    ("truncated copy");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate extended chars)-------*/
   DEBUG_YREGEX  yLOG_info    ("before"    , gre.orig);
   gre.olen = strllen (gre.orig  , LEN_REGEX);
   DEBUG_YREGEX  yLOG_value   ("gre.olen"  , gre.olen);
   yregex_comp__extended ();
   DEBUG_YREGEX  yLOG_info    ("gre.orig"  , gre.orig);
   gre.olen = strllen (gre.orig  , LEN_REGEX);
   DEBUG_YREGEX  yLOG_value   ("gre.olen"  , gre.olen);
   /*---(copy regex)---------------------*/
   strlcpy  (gre.regex, gre.orig , LEN_REGEX);
   gre.rlen = gre.olen;
   /*---(initialize compiled)------------*/
   for (i = 0; i < LEN_REGEX; ++i) {
      gre.comp [i] =   0;
      gre.indx [i] =   0;
      gre.mods [i] =   0;
      gre.jump [i] =   0;
   }
   gre.clen = 0;
   /*---(initialize grouping)------------*/
   s_glevel   =  0;
   s_ggroup   =  0;
   s_ghidden  = 10;
   s_gfocus   = '-';
   strlcpy (gre.groups, "               ", LEN_LABEL);
   /*---(initialize sets)----------------*/
   yregex_sets_prep ();
   yregex_rule_init ();
   gre.ready = '-';
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
   DEBUG_YREGEX  yLOG_sint    (gre.clen);
   gre.comp [gre.clen] = a_comp;
   gre.indx [gre.clen] = a_indx;
   gre.mods [gre.clen] = ' ';
   gre.jump [gre.clen] = 0;
   ++gre.clen;
   DEBUG_YREGEX  yLOG_sint    (gre.clen);
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fz.412.301.00]*/ /*-[00.0000.02#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp_mod         (cchar a_mod)
{
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (a_mod);
   gre.mods [gre.clen - 1] = a_mod;
   DEBUG_YREGEX  yLOG_sint    (gre.clen - 1);
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fz.632.201.00]*/ /*-[00.0000.06#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp__dup_one        (void)
{
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (gre.comp [gre.clen - 1]);
   DEBUG_YREGEX  yLOG_sint    (gre.indx [gre.clen - 1]);
   DEBUG_YREGEX  yLOG_sint    (gre.clen);
   gre.comp [gre.clen] = gre.comp [gre.clen - 1];
   gre.indx [gre.clen] = gre.indx [gre.clen - 1];
   gre.mods [gre.clen] = gre.mods [gre.clen - 1];
   gre.jump [gre.clen] = gre.jump [gre.clen - 1];
   ++gre.clen;
   DEBUG_YREGEX  yLOG_sint    (gre.clen);
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fz.632.201.00]*/ /*-[00.0000.06#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp__dup_group      (void)
{
   int         x_beg       = 0;
   int         x_end       = 0;
   int         i           = 0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("gre.clen"  , gre.clen);
   x_end = gre.clen - 1;
   x_beg = yregex_comp__group_beg (x_end);
   DEBUG_YREGEX  yLOG_value   ("x_beg"     , x_beg);
   DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
   for (i = x_beg; i <= x_end; ++i) {
      DEBUG_YREGEX  yLOG_value   ("pos"       , i);
      yregex_comp_add (gre.comp [i], gre.indx [i]);
      if (strchr ("(|)", gre.comp [i]) != NULL)  gre.indx [gre.clen - 1] = s_gmulti;
      yregex_comp_mod (gre.mods [i]);
      gre.jump [gre.clen - 1] = gre.jump [i];
   }
   ++s_gmulti;
   DEBUG_YREGEX  yLOG_value   ("s_gmulti"  , s_gmulti);
   DEBUG_YREGEX  yLOG_value   ("gre.clen"  , gre.clen);
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
   x_ch  = gre.regex [*a_rpos];
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
   x_mod  = gre.regex [*a_rpos];
   x_pch  = gre.regex [*a_rpos - 1];
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
   x_ch   = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   --rce;  if (x_ch != '{') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a {");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_pch  = gre.regex [*a_rpos - 1];
   /*---(check for lazy modifier)--------*/
   x_mod  = gre.regex [++(*a_rpos)];
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   if (x_mod == '-') {
      DEBUG_YREGEX  yLOG_note    ("found lazy modifer");
      x_lazy = 'y';
      x_mod   = gre.regex [++(*a_rpos)];
      DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
      DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   }
   /*---(walk modifier)------------------*/
   while (1) {
      DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
      if (*a_rpos >= gre.rlen) {
         DEBUG_YREGEX  yLOG_note    ("hit end of string");
         break;
      }
      if (x_mod == '}') {
         DEBUG_YREGEX  yLOG_note    ("found end of modifier");
         if (x_len > 0) {
            sprintf (t, "%*.*s", x_len, x_len, gre.regex + *a_rpos - x_len);
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
            sprintf (t, "%*.*s", x_len, x_len, gre.regex + *a_rpos - x_len);
            DEBUG_YREGEX  yLOG_info    ("t"         , t);
            x_min = atoi (t);
         }
         x_len = -1; /* don't count comma */
         DEBUG_YREGEX  yLOG_value   ("x_min"     , x_min);
      }
      x_mod   = gre.regex [++(*a_rpos)];
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
         return 1;
      }
      if (x_lazy == 'y')  yregex_comp_mod ('!');
      else                yregex_comp_mod ('?');
      for (i = 1; i < x_max; ++i) {
         if (x_pch == ')')  yregex_comp__dup_group   ();
         else               yregex_comp__dup_one     ();
      }
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
/*===----                         group handling                       ----===*/
/*====================------------------------------------====================*/
static void      o___GROUPS__________________o (void) {;}

int
yregex_comp__group_beg  (int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;
   int         i           =    0;
   /*---(prepare)------------------------*/
   x_lvl       = gre.indx [a_rpos];
   for (i = a_rpos - 1; i >= 0; --i) {
      if (gre.indx [i] != x_lvl)  continue;
      if (gre.comp [i] != '('  )  continue;
      return i;
   }
   return -1;
}

int
yregex_comp__group_end  (int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;
   int         i           =    0;
   /*---(prepare)------------------------*/
   if (gre.comp [a_rpos] == ')')  return a_rpos;
   /*---(prepare)------------------------*/
   x_lvl       = gre.indx [a_rpos];
   for (i = a_rpos + 1; i < gre.clen; ++i) {
      if (gre.indx [i] != x_lvl)  continue;
      if (gre.comp [i] != ')'  )  continue;
      return i;
   }
   return -1;
}

char         /*-> tbd --------------------------------[ leaf   [fc.741.141.50]*/ /*-[03.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp__group_fix  (cint a_grp)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         x_ch        =  ' ';
   int         x_indx      =    0;
   int         x_jump      =    0;
   int         x_or        =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_grp"     , a_grp);
   DEBUG_YREGEX  yLOG_value   ("gre.clen"  , gre.clen);
   /*---(track backwards)----------------*/
   for (i = gre.clen - 1; i >= 0; --i) {
      /*---(prepare)---------------------*/
      x_ch   = gre.comp [i];
      x_indx = gre.indx [i];
      /*> DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);                            <*/
      /*> DEBUG_YREGEX  yLOG_value   ("x_indx"    , x_indx);                          <*/
      /*> DEBUG_YREGEX  yLOG_value   ("x_jump"    , x_jump);                          <*/
      /*---(branch)----------------------*/
      if (x_indx == a_grp && x_ch == '|') {
         gre.jump [i] = x_jump;
         x_jump =  0;
         ++x_or;
      }
      /*---(start)--------------------*/
      else if (x_indx == a_grp && x_ch == '(') {
         gre.jump [i] = x_jump;
         gre.mods [i] = '0' + x_or;
         break;
      }
      /*---(otherwise)----------------*/
      ++x_jump;
      /*---(done)---------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> tbd --------------------------------[ ------ [fe.B53.141.32]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_comp__group      (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   uchar       x_ch        =  ' ';
   uchar       x_nch       =  ' ';
   int         x_grp       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   x_ch   = gre.regex [*a_rpos];
   x_nch  = gre.regex [*a_rpos + 1];
   DEBUG_YREGEX  yLOG_complex ("position"  , "pos %2d, ch  %c, nch %c", *a_rpos, x_ch, x_nch);
   /*---(defense)------------------------*/
   --rce;  if (*a_rpos == 0 && strchr ("#;", x_nch) != NULL){
      DEBUG_YREGEX  yLOG_note    ("prefix hash (#) or semi (;), not really group");
      x_nch = '?';
   }
   /*---(check)--------------------------*/
   switch (x_ch) {
   case '(' :
      ++s_glevel;
      switch (x_nch) {
      case '#' :
         x_grp = ++s_ggroup;
         if (s_ggroup > 10) {
            DEBUG_YREGEX  yLOG_note    ("group number too high, had to hide");
            x_grp = ++s_ghidden;
         } else {
            DEBUG_YREGEX  yLOG_note    ("open normal group");
            gre.groups [x_grp - 1] = 'y';
         }
         ++*a_rpos;
         break;
      case '>' :
         DEBUG_YREGEX  yLOG_note    ("open primary group");
         s_gfocus = 'y';
         x_grp = GROUP_FOCUS;
         gre.groups [10] = 'F';
         ++*a_rpos;
         break;
      case ';' :
         DEBUG_YREGEX  yLOG_note    ("open rule group");
         x_grp = ++s_ghidden;
         ++*a_rpos;
         break;
      default  :
         if (*a_rpos == 0) {
            DEBUG_YREGEX  yLOG_note    ("open full regex container");
            x_grp = ++s_ggroup;
            gre.groups [x_grp - 1] = '.';
         } else {
            DEBUG_YREGEX  yLOG_note    ("open hidden group");
            x_grp = ++s_ghidden;
         }
         break;
      }
      rc = yregex_comp_add  ('(', x_grp);
      s_gstack [s_glevel] = x_grp;
      break;
   case '<' :
      DEBUG_YREGEX  yLOG_note    ("close primary group");
      x_grp = s_gstack [s_glevel];
      if (x_grp != GROUP_FOCUS) {
         DEBUG_YREGEX  yLOG_note    ("primary focus parens do not match");
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return -1;
      }
      rc = yregex_comp_add  (')', x_grp);
      rc = yregex_comp__group_fix  (x_grp);
      --s_glevel;
      ++*a_rpos;
      break;
   case ')' :
      DEBUG_YREGEX  yLOG_note    ("close normal/hidden group");
      x_grp = s_gstack [s_glevel];
      rc = yregex_comp_add  (x_ch, x_grp);
      rc = yregex_comp__group_fix  (x_grp);
      --s_glevel;
      break;
   case '|' :
      DEBUG_YREGEX  yLOG_note    ("divide branches/matches");
      x_grp = s_gstack [s_glevel];
      rc = yregex_comp_add  (x_ch, x_grp);
      break;
   }
   DEBUG_YREGEX  yLOG_complex ("current"   , "lvl %2d, nrm %2d, hid %2d, grp %2d", s_glevel, s_ggroup, s_ghidden, x_grp);
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
   for (i = 0; i <= gre.olen; ++i) {
      x_ch = gre.orig [i];
      switch (x_ch) {
      case G_CHAR_STORAGE : case G_CHAR_BIGDOT  :
      case G_CHAR_HALT    : case G_CHAR_MASK    :  /* just a spacer, not used  */
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
   strlcpy (gre.orig, t, LEN_REGEX);
   gre.olen = strllen (gre.orig, LEN_REGEX);
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
   DEBUG_YREGEX  yLOG_info    ("tranlated" , gre.orig);
   DEBUG_YREGEX  yLOG_point   ("gre.olen"  , gre.olen);
   /*---(pattern run)--------------------*/
   rc = yregex_pats_comp ();
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(parse)--------------------------*/
   DEBUG_YREGEX  yLOG_info    ("gre.regex" , gre.regex);
   DEBUG_YREGEX  yLOG_point   ("gre.rlen"  , gre.rlen);
   for (i = 0; i < gre.rlen; ++i) {
      /*---(check last run)--------------*/
      if (rc < 0) break;
      DEBUG_YREGEX  yLOG_value   ("LOOP"      , i);
      /*---(prepare)---------------------*/
      x_ch   = gre.regex [i];
      x_nch  = gre.regex [i + 1];
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
         rc = yregex_comp__group (&i);
         rc = yregex_rule_comp  (&i);
         continue;
      }
      /*---(group handling)--------------*/
      if (strchr (TYPE_GROUP, x_ch) != NULL || (x_ch == '<' && x_nch == ')')) {
         DEBUG_YREGEX  yLOG_note    ("handle grouping");
         rc = yregex_comp__group (&i);
         if (rc >= 0)  continue;
      }
      /*---(anchors)---------------------*/
      if (strchr (G_ANCHOR, x_ch) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("handle anchors");
         rc = yregex_comp_add (x_ch, yregex_sets__by_abbr ('w'));
         if (rc >= 0)  continue;
      }
      /*---(set handling)----------------*/
      if (x_ch == '[') {
         DEBUG_YREGEX  yLOG_note    ("handle character set");
         rc = yregex_sets_comp (&i);
         if (rc >= 0)  continue;
      }
      /*---(quick modifiers)-------------*/
      if (strchr (TYPE_QUANS, x_ch) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("handle simple modifier");
         rc = yregex_comp__quan_simp (&i);
         continue;
      }
      /*---(specific modifiers)----------*/
      if (x_ch == '{') {
         DEBUG_YREGEX  yLOG_note    ("handle complex modifier");
         rc = yregex_comp__quan_comp (&i);
         continue;
      }
      /*---(literals)--------------------*/
      DEBUG_YREGEX  yLOG_note    ("handle character literal");
      rc = yregex_comp__literal (&i);
   }
   /*---(check for failure)--------------*/
   gre.ready = 'n';
   --rce;  if (s_glevel != 0) {
      DEBUG_YREGEX  yLOG_note    ("parenthesis do not balance");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_note    ("compilation failed");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   gre.ready = 'y';
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
   char       *x_range2    = " 123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range3    = " .123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ**********************************************************************";
   switch (a_type) {
   case '(' :
      if      (a_value == GROUP_FOCUS)   x_ch = '<';
      else if (a_value >= 65 )           x_ch = '*';
      else                               x_ch = x_range3 [a_value];
      break;
   case 'i' :
      if      (a_value >= 65 )           x_ch = '*';
      else                               x_ch = x_range2 [a_value];
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
   char       *x_range     = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range2    = " 123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range3    = " .123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ**********************************************************************";
   int         c           = 0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "COMP__unit, unknown request", 100);
   /*---(core data)----------------------*/
   if        (strncmp (a_question, "regex"     , 20)  == 0) {
      if (gre.rlen < 100)  sprintf  (t, "%2d", gre.rlen);
      else                 sprintf  (t, "%2s", "++");
      snprintf (unit_answer, LEN_TEXT, "COMP regex       : %2s [%-45.45s]", t, gre.regex);
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
      snprintf (unit_answer, LEN_TEXT, "COMP base        : %2d [%-45.45s]", gre.clen, gre.comp);
   } else if (strncmp (a_question, "indx"      , 20)  == 0) {
      for (i = 0; i < 45; ++i) {
         if (strchr ("(|&)", gre.comp [i]) != NULL)  t [i] = yregex_comp__unit_map ('(', gre.indx [i]);
         else                                        t [i] = yregex_comp__unit_map ('i', gre.indx [i]);
      }
      t [45] = 0;
      snprintf (unit_answer, LEN_TEXT, "COMP indx        : %2d [%-45.45s]", gre.clen, t);
   } else if (strncmp (a_question, "mods"      , 20)  == 0) {
      snprintf (unit_answer, LEN_TEXT, "COMP mods        : %2d [%-45.45s]", gre.clen, gre.mods);
   } else if (strncmp (a_question, "jump"      , 20)  == 0) {
      for (i = 0; i < 45; ++i)   t [i] = yregex_comp__unit_map ('j', gre.jump [i]);
      t [45] = 0;
      snprintf (unit_answer, LEN_TEXT, "COMP jump        : %2d [%-45.45s]", gre.clen, t);
   } else if (strncmp (a_question, "groups"    , 20)  == 0) {
      snprintf (unit_answer, LEN_TEXT, "COMP groups      : [%-11.11s]", gre.groups);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



/*===============================[[ end code ]]===============================*/
