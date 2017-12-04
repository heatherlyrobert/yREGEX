/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



char        g_source    [LEN_RECD]  = "";
int         g_slen      = -1;
static int  s_begin     =  0;
static int  s_end       =  0;
static int  s_len       =  0;




#define     S_CHAR_CHECK    'c'
#define     S_BRANCH_CHECK  'g'
#define     S_FULL_RECURSE  'r'



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char         /*-> tbd --------------------------------[ shoot  [fe.833.144.30]*/ /*-[01.0000.01#.H]-*/ /*-[--.---.---.--]-*/
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
/*===----                       normal matching                        ----===*/
/*====================------------------------------------====================*/
static void      o___NORMAL__________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [fe.B44.545.72]*/ /*-[01.0000.03#.#]-*/ /*-[--.---.---.--]-*/
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
   uchar       x_reg       =    0;
   uchar       x_src       =    0;
   int         x_tend      = *a_tend;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (a_begin);
   DEBUG_YREGEX  yLOG_schar   (a_mode);
   DEBUG_YREGEX  yLOG_sint    (a_tpos);
   DEBUG_YREGEX  yLOG_sint    (a_rpos);
   DEBUG_YREGEX  yLOG_sint    (*a_tend);
   /*---(defenses)-----------------------*/
   --rce;  if (a_tpos <  0     ) {
      DEBUG_YREGEX  yLOG_snote   ("before source begin");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_tpos >= g_slen) {
      DEBUG_YREGEX  yLOG_snote   ("past source end");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_rpos <  0     ) {
      DEBUG_YREGEX  yLOG_snote   ("before regex begin");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_rpos >= g_clen) {
      DEBUG_YREGEX  yLOG_snote   ("past regex end");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_reg   = g_comp   [a_rpos];
   DEBUG_YREGEX  yLOG_schar   (x_reg);
   x_src   = g_source [a_tpos];
   DEBUG_YREGEX  yLOG_schar   (x_src);
   /*---(test sets)----------------------*/
   if (x_reg == '[') {
      DEBUG_YREGEX  yLOG_snote   ("SETS");
      if (g_sets [g_indx [a_rpos]].map [x_src] == '.')  rc = 1;
   }
   else {
      DEBUG_YREGEX  yLOG_snote   ("CHAR");
      if (x_reg == x_src)                               rc = 1;
   }
   /*---(check)--------------------------*/
   DEBUG_YREGEX  yLOG_sint    (rc);
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   if (rc == 1) {
      /*---(update values)---------------*/
      *a_tend = a_tpos;
      ++a_rpos;
      ++a_tpos;
      ++x_tend;
      /*---(tail resurse)----------------*/
      if (a_rpos < g_clen) {
         switch (a_mode) {
         case S_CHAR_CHECK   :
            break;
         case S_BRANCH_CHECK :
         case S_FULL_RECURSE :
            rc = yREGEX__exec_next (a_begin, a_mode, a_rpos, a_tpos, &x_tend);
            if (rc == 1) *a_tend = x_tend;
            break;
         }
      }
   }
   /*---(complete)-----------------------*/
   return rc;
}

char         /*-> tbd --------------------------------[ ------ [fe.K96.5D5.91]*/ /*-[03.0000.02#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__exec_multiple(int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend) 
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_ch        =  ' ';
   uchar       x_mod       =  ' ';
   char        x_meth      =  '-';
   int         x_rem       =    0;
   uchar       x_min       =    0;
   uchar       x_max       =    0;
   int         x_pos       = a_tpos;
   int         i           =    0;
   int         x_match     =    0;
   int         x_tend      =    0;
   char        x_gmods     =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_note    ("MULTIPLE");
   /*---(prepare)------------------------*/
   x_tend      = *a_tend;
   x_ch        = g_comp [a_rpos];
   x_gmods     = a_rpos;
   if (x_ch == '(')  x_gmods = yREGEX__exec_gscan (a_rpos);
   x_mod       = g_mods [x_gmods];
   if      (strchr (G_GREEDY, x_mod) != NULL)   x_meth = 'G';
   else if (strchr (G_LAZY  , x_mod) != NULL)   x_meth = 'L';
   DEBUG_YREGEX  yLOG_complex ("CURRENT"   , "ch %c, mod %c is %c, x_tend %3d", x_ch, x_mod, x_meth, x_tend);
   /*---(lengths)------------------------*/
   x_rem   = g_slen - a_tpos;
   x_min   = g_mins [x_gmods];
   x_max   = g_maxs [x_gmods];
   if (x_max > x_rem)  x_max = x_rem;
   if (x_mod == ' ' )  x_min = x_max = 1;
   DEBUG_YREGEX  yLOG_complex ("LIMITS"    , "rem %3d, min %3d to max %3d", x_rem, x_min, x_max);
   --rce;  if (x_min > x_rem) {
      DEBUG_YREGEX  yLOG_note    ("MULTIPLE, leave looping, minimum to large");
      return rce;
   }
   /*---(check up to minimum)------------*/
   if (x_min > 0)  DEBUG_YREGEX  yLOG_note    ("MINIMUM -----------------------------------");
   for (i = 0; i < x_min; ++i) {
      DEBUG_YREGEX  yLOG_value   ("LOOP"      , i);
      if (x_ch == '(')  rc = yREGEX__exec_branch (a_begin, S_BRANCH_CHECK, a_rpos, a_tpos + i, &x_tend);
      else              rc = yREGEX__exec_doer   (a_begin, S_CHAR_CHECK  , a_rpos, a_tpos + i, &x_tend);
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      if (rc <= 0) {
         DEBUG_YREGEX  yLOG_note    ("failed before min was completed");
         return rc;
      }
      x_match = i;
   }
   /*---(check target range)-------------*/
   DEBUG_YREGEX  yLOG_note    ("RANGE -------------------------------------");
   for (i = x_min; i < x_max; ++i) {
      DEBUG_YREGEX  yLOG_value   ("LOOP"      , i);
      if (x_meth == 'G') {
         if (x_ch == '(')  rc = yREGEX__exec_branch (a_begin, S_BRANCH_CHECK, a_rpos, a_tpos + i, &x_tend);
         else              rc = yREGEX__exec_doer   (a_begin, S_CHAR_CHECK  , a_rpos, a_tpos + i, &x_tend);
         DEBUG_YREGEX  yLOG_value   ("greedy rc" , rc);
         if (rc <= 0) break;
      }
      if (x_meth == 'L') {
         if (x_ch == '(')  rc = yREGEX__exec_branch (a_begin, S_FULL_RECURSE, a_rpos, a_tpos + i, &x_tend);
         else              rc = yREGEX__exec_doer   (a_begin, S_FULL_RECURSE, a_rpos, a_tpos + i, &x_tend);
         DEBUG_YREGEX  yLOG_value   ("lazy rc"   , rc);
         if (rc == 1) {
            *a_tend = x_tend;
            DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
            DEBUG_YREGEX  yLOG_note    ("MULTIPLE, returning lazy success");
            return 1;
         }
      }
      x_match = i;
   }
   /*---(check greedy for real)----------*/
   if (x_match == 0 && strchr ("?!", x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("MULTIPLE, zero matches valid for ?!");
      rc = yREGEX__exec_next   (a_begin, S_FULL_RECURSE, a_rpos + 1, a_tpos, &x_tend);
      if (rc == 1) {
         *a_tend = x_tend;
         DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
         DEBUG_YREGEX  yLOG_note    ("MULTIPLE, returning zero width success");
         return 1;
      }
   }
   if (x_meth == 'L') {
      DEBUG_YREGEX  yLOG_note    ("MULTIPLE, lazy failure");
      return 0;
   }
   /*---(check greedy for real)----------*/
   DEBUG_YREGEX  yLOG_note    ("GREEDY REVERSE ----------------------------");
   for (i = x_match; i >= x_min - 1; --i) {
      DEBUG_YREGEX  yLOG_value   ("LOOP"      , i);
      if (x_ch == '(')  rc = yREGEX__exec_branch (a_begin, S_FULL_RECURSE, a_rpos, a_tpos + i, &x_tend);
      else              rc = yREGEX__exec_doer   (a_begin, S_FULL_RECURSE, a_rpos, a_tpos + i, &x_tend);
      DEBUG_YREGEX  yLOG_value   ("greedy rc" , rc);
      if (rc == 1) {
         *a_tend = x_tend;
         DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
         DEBUG_YREGEX  yLOG_note    ("MULTIPLE, returning greedy success");
         return 1;
      }
   }
   /*---(failed)-------------------------*/
   DEBUG_YREGEX  yLOG_note    ("MULTIPLE, fell out bottom");
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [fc.D53.553.B4]*/ /*-[01.0000.03#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__exec_next    (int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend) 
{
   /*---(design notes)-------------------*/
   /*
    * this is launched once for every position/quantifier-inc in the regex
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_ch        =  ' ';
   char        x_mod       =  ' ';
   int         x_tend      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "%-3d, %c, %-3d, %-3d, %-3d", a_begin, a_mode, a_rpos, a_tpos, *a_tend);
   /*---(prepare)------------------------*/
   x_tend      = *a_tend;
   x_ch        = g_comp [a_rpos];
   x_mod       = g_mods [a_rpos];
   DEBUG_YREGEX  yLOG_complex ("current"   , "%c (%c) %3d", x_ch, x_mod, x_tend);
   /*---(anchors)------------------------*/
   if (strchr (G_ANCHOR, x_ch) != NULL) {
      switch (x_ch) {
      case '^' :
         if (a_tpos != 0) {
            DEBUG_YREGEX  yLOG_note    ("not anchored at beginning, failed");
            DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
            return 0;
         }
         DEBUG_YREGEX  yLOG_note    ("beginning of line, continue");
         ++a_rpos;
         break;
      case '$' :
         if (a_tpos < (g_slen - 1)){
            DEBUG_YREGEX  yLOG_note    ("not anchored at end, failed");
            DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
            return 0;
         }
         --(*a_tend);
         DEBUG_YREGEX  yLOG_note    ("end of line, success");
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 1;
      }
   }
   /*---(new group)----------------------*/
   if (x_ch == '(') {
      DEBUG_YREGEX  yLOG_note    ("beginning a new group");
      rc = yREGEX__exec_group (a_begin, a_mode, a_rpos, a_tpos, &x_tend);
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      if (rc == 1) {
         *a_tend = x_tend;
         DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
      }
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(end of branch)------------------*/
   while (strchr ("|)", x_ch) != NULL) {
      if (x_ch == '|') {
         if (a_mode == S_BRANCH_CHECK) {
            DEBUG_YREGEX  yLOG_note    ("end of branch, check only, return");
            DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
            return 1;
         }
         DEBUG_YREGEX  yLOG_note    ("end of branch, jump to end of group");
         a_rpos      = yREGEX__exec_gscan (a_rpos) + 1;
      } else if (x_ch == ')') {
         if (a_mode == S_BRANCH_CHECK) {
            DEBUG_YREGEX  yLOG_note    ("end of branch, check only, return");
            DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
            return 1;
         }
         DEBUG_YREGEX  yLOG_note    ("end of group, continue");
         ++a_rpos;
      }
      if (a_rpos >= g_clen) {
         *a_tend = a_tpos - 1;
         /*> *a_tend = x_tend;                                                        <*/
         /*> --(*a_tend);                                                             <*/
         DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
         DEBUG_YREGEX  yLOG_note    ("end of regex, success");
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 1;
      }
      x_ch        = g_comp [a_rpos];
      x_mod       = g_mods [a_rpos];
      DEBUG_YREGEX  yLOG_complex ("after grp" , "%c (%c) %3d", x_ch, x_mod, x_tend);
   }
   /*---(launch checkers)----------------*/
   switch (x_mod) {
   case '*' : case '+' : case '?' : case '{' :
      DEBUG_YREGEX  yLOG_note    ("greedy character check");
      rc = yREGEX__exec_multiple (a_begin, a_mode, a_rpos, a_tpos, &x_tend);
      break;
   case '@' : case '~' : case '!' : case '}' :
      DEBUG_YREGEX  yLOG_note    ("lazy character check");
      rc = yREGEX__exec_multiple (a_begin, a_mode, a_rpos, a_tpos, &x_tend);
      break;
   default  :
      DEBUG_YREGEX  yLOG_note    ("single character check");
      rc = yREGEX__exec_doer     (a_begin, a_mode, a_rpos, a_tpos, &x_tend);
      break;
   }
   /*---(check)--------------------------*/
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc == 1) {
      *a_tend = x_tend;
      DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        group handlers                        ----===*/
/*====================------------------------------------====================*/
static void      o___GROUPING________________o (void) {;}

int          /*-> tbd --------------------------------[ ------ [fn.320.131.21]*/ /*-[00.0000.04#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__exec_gscan   (int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_ndiv      =    0;
   int         x_len       =    0;
   int         x_end       =    0;
   /*---(parse)--------------------------*/
   x_len  = g_jump [a_rpos];
   if (x_len > 0)   x_end = yREGEX__exec_gscan  (a_rpos + x_len);
   else             x_end = a_rpos;
   return x_end;
}

char         /*-> tbd --------------------------------[ ------ [fc.732.551.21]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__exec_branch  (int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend) 
{
   /*---(design notes)-------------------*/
   /*
    * launched for each open parenthesis
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_ndiv      =    0;
   int         x_offset    =    0;
   int         i           =    0;
   int         x_tend      =    0;
   /*---(prepare)------------------------*/
   x_tend      = *a_tend;
   x_ndiv = g_mins [a_rpos];
   /*---(launch branches)----------------*/
   for (i = 0; i < x_ndiv; ++i) {
      DEBUG_YREGEX  yLOG_complex ("branch"    , "num %2d of %2d, a_rpos %3d, off %3d, loc %3d", i + 1, x_ndiv, a_rpos, x_offset, a_rpos + x_offset);
      rc = yREGEX__exec_next (a_begin, a_mode, a_rpos + x_offset + 1, a_tpos, &x_tend);
      if (rc == 1) break;
      x_offset += g_jump [a_rpos + x_offset];
   }
   /*---(tail resurse)-------------------*/
   /*> ++a_rpos;                                                                      <* 
    *> ++a_tpos;                                                                      <* 
    *> if (rc == 1 && a_mode == 'r') {                                                <* 
    *>    if (a_rpos >= g_clen) {                                                     <* 
    *>       rc = 1;                                                                  <* 
    *>       *a_tend = a_tpos - 1;                                                    <* 
    *>    } else {                                                                    <* 
    *>       rc = yREGEX__exec_next (a_begin, '-', a_rpos, a_tpos, &x_tend);          <* 
    *>       if (rc == 1) *a_tend = x_tend;                                           <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(update)-------------------------*/
   DEBUG_YREGEX  yLOG_value   ("done"      , rc);
   if (rc == 1) {
      *a_tend = x_tend;
   }
   /*---(complete)-----------------------*/
   return rc;
}

char         /*-> distribute grouping metas ----------[ ------ [fc.D53.553.B4]*/ /*-[01.0000.03#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__exec_group   (int a_begin, char a_mode, int a_rpos, int a_tpos, int *a_tend) 
{
   /*---(design notes)-------------------*/
   /*
    *  distributes grouping vs non-grouping
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_ch        =  ' ';
   char        x_gmods     =  ' ';
   char        x_mod       =  ' ';
   int         x_tend      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "%-3d, %c, %-3d, %-3d, %-3d", a_begin, a_mode, a_rpos, a_tpos, *a_tend);
   /*---(prepare)------------------------*/
   x_tend      = *a_tend;
   x_ch        = g_comp [a_rpos];
   x_gmods     = yREGEX__exec_gscan (a_rpos);
   x_mod       = g_mods [x_gmods];
   DEBUG_YREGEX  yLOG_complex ("current"   , "ch %c, mod %c, x_tend %3d", x_ch, x_mod, x_tend);
   /*---(defense)------------------------*/
   --rce;  if (x_ch != '(') {
      DEBUG_YREGEX  yLOG_note    ("not the start of a group");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle multiplier)-----------*/
   switch (x_mod) {
   case '*' : case '+' : case '?' : case '{' :
      DEBUG_YREGEX  yLOG_note    ("greedy group check");
      rc = yREGEX__exec_multiple (a_begin, a_mode, a_rpos, a_tpos, &x_tend);
      break;
   case '@' : case '~' : case '!' : case '}' :
      DEBUG_YREGEX  yLOG_note    ("lazy group check");
      rc = yREGEX__exec_multiple (a_begin, a_mode, a_rpos, a_tpos, &x_tend);
      break;
   default  :
      DEBUG_YREGEX  yLOG_note    ("single group check");
      rc = yREGEX__exec_branch (a_begin, a_mode, a_rpos, a_tpos, &x_tend);
      break;
   }
   /*---(check)--------------------------*/
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc == 1) {
      *a_tend = x_tend;
      DEBUG_YREGEX  yLOG_value   ("a_tend"    , *a_tend);
   }
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
      x_tend = x_begin;
      rc = yREGEX__exec_next (x_begin, S_FULL_RECURSE, 0, x_begin, &x_tend);
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



