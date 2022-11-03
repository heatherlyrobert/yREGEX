/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



/* only one rule stores strings, that's the sub-string rule.
 * therefore, its likely that on 95% of all regex, there will
 * be zero strings stored.
 */

static tRULE      *s_head     = NULL;        /* head of list                 */
static tRULE      *s_tail     = NULL;        /* tail of list                 */
static tRULE      *s_curr     = NULL;        /* curent cursor                */
static int         s_count    =    0;        /* count of sets                */


char  g_subf    [LEN_TEXT];

/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
yregex_rule__wipe       (tRULE *a_cur)
{
   /*---(wipe)---------------------------*/
   a_cur->str      = NULL;
   a_cur->m_prev   = NULL;
   a_cur->m_next   = NULL;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char yregex_rule__new   (tRULE  **r_new) { return yregex_share_new  (TYPE_RULE, r_new, &s_head, &s_tail, &s_count); }
char yregex_rule__free  (tRULE  **r_old) { return yregex_share_free (TYPE_RULE, r_old, &s_head, &s_tail, &s_count); }



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char yregex_rule_init    (void) { return yregex_share_init  (TYPE_RULE, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_rule__purge  (void) { return yregex_share_purge (TYPE_RULE, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_rule_wrap    (void) { return yregex_share_wrap  (TYPE_RULE, &s_head, &s_tail, &s_curr, &s_count); }



/*====================------------------------------------====================*/
/*===----                      creating new strings                    ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE__________________o (void) {;}

short
yregex_rule__add        (short a_beg, short a_len)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   char        t           [LEN_RECD]  = "";
   tRULE      *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_value   ("a_beg"     , a_beg);
   --rce;  if (a_beg <  0 || a_beg >= myREGEX.rlen) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("a_len"     , a_len);
   --rce;  if (a_len <= 0 || a_beg + a_len >= myREGEX.rlen) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pull rule string)---------------*/
   sprintf (t, "%*.*s", a_len, a_len, myREGEX.regex + a_beg);
   DEBUG_YREGEX  yLOG_info    ("t"         , t);
   /*---(create string)------------------*/
   rc = yregex_rule__new (&x_new);
   DEBUG_YREGEX  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->str = strdup (t);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return s_count - 1;
}



/*====================------------------------------------====================*/
/*===----                        finding sets                          ----===*/
/*====================------------------------------------====================*/
static void      o___FINDING_________________o (void) {;}

char yregex_rule__by_cursor  (char a_move , tRULE  **r_back) { return yregex_share__by_cursor (TYPE_RULE, &s_head, &s_tail, &s_curr, r_back, a_move); }
char yregex_rule__by_index   (int a_index , tRULE  **r_back) { return yregex_share__by_index  (TYPE_RULE, &s_head, &s_curr, r_back, a_index); }



/*====================------------------------------------====================*/
/*===----                       rule compilation                       ----===*/
/*====================------------------------------------====================*/
static void      o___COMPILE_________________o (void) {;}

char
yregex_rule__ends       (int *a_rpos, char *a_group)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_ch        =  ' ';
   char        i           =    0;
   char        x_len       =    0;
   char        x_group     =    0;
   char        x_set       =  '-';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_rpos"    , a_rpos);
   --rce;  if (a_rpos == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   --rce;  if (*a_rpos <  1) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_point   ("a_group"   , a_group);
   --rce;  if (a_group == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_group = -1;
   /*---(check start)--------------------*/
   x_ch   = myREGEX.regex [*a_rpos - 1];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != '(') {
      yregex_error_add ('F', CAT_RUL, *a_rpos - 1, 1, "no open parenthesis");
      DEBUG_YREGEX  yLOG_note    ("does not start with open parens");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_ch   = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != ';') {
      yregex_error_add ('F', CAT_RUL, *a_rpos    , 1, "no rule marker");
      DEBUG_YREGEX  yLOG_note    ("does not have the ; rule indicator");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check capture group id)---------*/
   ++(*a_rpos);
   x_group = yregex_rule__group (a_rpos);
   --rce;  if (x_group < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check length)-------------------*/
   for (i = *a_rpos; i < *a_rpos + 100; i ++) {
      x_ch   = myREGEX.regex [i];
      if (x_ch == 0)                                      { rc = -1;  break; }
      if (x_ch == '[')  x_set = 'y';
      if (x_ch == ']')  x_set = '-';
      if (x_set == '-') {
         if (x_ch == '(' && myREGEX.regex [i - 1] != '\\')   { rc = -2;  break; }
         if (x_ch == ')' && myREGEX.regex [i - 1] != '\\')   break;
      }
      ++x_len;
   }
   DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
   --rce;  if (rc == -2) {
      yregex_error_add ('F', CAT_RUL, *a_rpos + x_len, 1, "no nested parenthesis");
      DEBUG_YREGEX  yLOG_note    ("rule does not end with parenthesis");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len >= 100) {
      DEBUG_YREGEX  yLOG_note    ("rule is too long");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update position)----------------*/
   /*> ++(*a_rpos);                                                                   <*/
   /*> DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);                            <*/
   *a_group = x_group;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return x_len;
}

short
yregex_rule__operator   (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_comp1     =    0;
   uchar       x_comp2     =    0;
   int         x_oper      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_rpos"    , a_rpos);
   --rce;  if (a_rpos == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   --rce;  if (*a_rpos <  1) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(check first)--------------------*/
   x_comp1  = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_comp1"   , x_comp1);
   --rce;  if (strchr ("=!<>", x_comp1) == NULL) {
      yregex_error_add ('F', CAT_RUL, *a_rpos, 1, "not valid operator (=!<>)");
      DEBUG_YREGEX  yLOG_note    ("not an operator");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ++(*a_rpos);
   /*---(check second)-------------------*/
   x_comp2  = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_comp2"   , x_comp2);
   if (x_comp2 == '=')  ++(*a_rpos);
   /*---(assign)-------------------------*/
   --rce;  if (x_comp2 == '=') {
      switch (x_comp1) {
      case '=' :
         x_oper = G_KEY_EQ;
         break;
      case '!' :
         x_oper = G_CHAR_NE;
         break;
      case '<' :
         x_oper = G_CHAR_LE;
         break;
      case '>' :
         x_oper = G_CHAR_GE;
         break;
      default  :
         --(*a_rpos);
         yregex_error_add ('F', CAT_RUL, *a_rpos, 2, "invalid 2-char operator");
         DEBUG_YREGEX  yLOG_note    ("not an operator");
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   else {
      switch (x_comp1) {
      case '<' :
         x_oper = G_KEY_LT;
         break;
      case '>' :
         x_oper = G_KEY_GT;
         break;
      default  :
         --(*a_rpos);
         yregex_error_add ('F', CAT_RUL, *a_rpos, 1, "invalid 1-char operator (<>)");
         DEBUG_YREGEX  yLOG_note    ("not an operator");
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check results)------------------*/
   --rce;  if (x_oper <= 0) {
      --(*a_rpos);
      DEBUG_YREGEX  yLOG_note    ("operator not understood");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(readout)------------------------*/
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   DEBUG_YREGEX  yLOG_value   ("x_oper"    , x_oper);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return x_oper;
}

char
yregex_rule__group      (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_ch        =    0;
   char        x_grp       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (*a_rpos);
   /*---(review)-------------------------*/
   x_ch   = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_schar   (x_ch);
   --rce;  if (strchr (YSTR_UPLOW, x_ch) != NULL) {
      yregex_error_add ('F', CAT_RUL, *a_rpos, 1, "alphabetic group number [a-zA-Z]");
      DEBUG_YREGEX  yLOG_snote   ("not a capture group ref");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr ("0123456789", x_ch) == NULL) {
      yregex_error_add ('F', CAT_RUL, *a_rpos, 1, "symbolic group number [^0-9a-zA-Z]");
      DEBUG_YREGEX  yLOG_snote   ("not a capture group ref");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(adjust)-------------------------*/
   DEBUG_YREGEX  yLOG_snote   ("good");
   x_grp  = x_ch  - '0';
   DEBUG_YREGEX  yLOG_sint    (x_grp);
   /*---(move)---------------------------*/
   ++(*a_rpos);
   DEBUG_YREGEX  yLOG_sint    (*a_rpos);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return x_grp;
}

char         /*-> tbd --------------------------------[ ------ [fe.D54.156.65]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_rule_comp        (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   int         i           =    0;
   int         x_ch        =  ' ';
   int         x_ch2       =  ' ';
   int         x_len       =    0;
   char        t           [LEN_NAME] = "";
   char        x_one       =    0;
   char        x_two       =    0;
   int         x_oper      =    0;
   int         x_set       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(check ends)---------------------*/
   x_len = yregex_rule__ends (a_rpos, &x_one);
   if (x_len < 0 || x_one < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, x_one);
      return x_one;
   }
   /*---(grab rule)----------------------*/
   x_ch  = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   /*---(check simple rules)-------------*/
   -rce;
   if (strchr ("=!<>", x_ch) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("group comparison rules");
      x_oper = yregex_rule__operator (a_rpos);
      if (x_oper < 0) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, x_oper);
         return x_oper;
      }
      x_two  = yregex_rule__group    (a_rpos);
      if (x_two  < 0) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, x_two);
         return x_two;
      }
      x_ch = myREGEX.regex [*a_rpos];
      if (x_ch != ')') {
         DEBUG_YREGEX  yLOG_note    ("group comparision has extra chars");
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yregex_comp_add (';', x_one);
      yregex_comp_mod (x_oper);
      myREGEX.jump [myREGEX.clen - 1] = x_two;
      rc = 0;
      --(*a_rpos);
   }
   /*---(check simple backslash set)-----*/
   else if (x_len == 2 && x_ch == '\\') {
      DEBUG_YREGEX  yLOG_note    ("includes backslash set rule");
      ++(*a_rpos);
      x_ch2  = myREGEX.regex [*a_rpos];
      DEBUG_YREGEX  yLOG_char    ("x_ch2"     , x_ch2);
      x_set = yregex_sets__by_abbr (x_ch2, NULL);
      if (x_set <= 0) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, x_set);
         return rce;
      }
      yregex_comp_add (';', x_one);
      yregex_comp_mod ('[');
      myREGEX.jump [myREGEX.clen - 1] = x_set;
      rc = 0;
      /*> ++(*a_rpos);                                                                <*/
   }
   /*---(check custom set)---------------*/
   else if (x_len >  2 && x_ch == '[') {
      DEBUG_YREGEX  yLOG_note    ("includes posix/custom set rule");
      if (myREGEX.regex [*a_rpos + 1] == '^')   x_ch = ']';
      rc = yregex_sets_comp (a_rpos);
      if (rc < 0) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      myREGEX.comp [myREGEX.clen - 1] = ';';
      myREGEX.mods [myREGEX.clen - 1] = x_ch;
      myREGEX.jump [myREGEX.clen - 1] = myREGEX.indx [myREGEX.clen - 1];
      myREGEX.indx [myREGEX.clen - 1] = x_one;
      rc = 0;
   }
   /*---(check substring)----------------*/
   else if (strchr ("+-", x_ch) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("includes substring rule");
      ++(*a_rpos);
      x_set = yregex_rule__add (*a_rpos, x_len - 1);
      yregex_comp_add (';', x_one);
      yregex_comp_mod (x_ch);
      myREGEX.jump [myREGEX.clen - 1] = x_set;
      *a_rpos += x_len - 2;
      rc = 0;
   }
   /*---(now regex)----------------------*/
   /*> else if (x_ch == '&') {                                                        <* 
    *>    DEBUG_YREGEX  yLOG_note    ("additional group filtering");                  <* 
    *>    yregex_comp_add (';', x_one);                                               <* 
    *>    yregex_comp_mod ('&');                                                      <* 
    *>    *a_rpos += x_len - 2;                                                       <* 
    *>    rc = 0;                                                                     <* 
    *> }                                                                              <*/
   /*---(trouble)------------------------*/
   else {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, x_set);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                       rule execution                         ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTE_________________o (void) {;}

char
yregex_rule_exec        (short a_level, short a_rpos, short a_tpos, tSTATE *a_focus)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_one       =    0;
   int         x_two       =    0;
   uchar       x_mod       =    0;
   char        s1          [LEN_TEXT] = "";
   char        s2          [LEN_TEXT] = "";
   int         x_indx      =    0;
   int         x_beg       =   -1;
   int         x_end       =   -1;
   int         x_len       =    0;
   int         x_cmp       =   -1;
   tRULE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d, index %p", a_level, a_rpos, a_tpos, a_focus);
   /*---(prepare)------------------------*/
   x_one       = myREGEX.indx [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_one"     , x_one);
   x_two       = myREGEX.jump [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_two"     , x_two);
   x_mod       = myREGEX.mods [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   /*> rc = yregex_exec_sub (a_index, x_one);                                         <*/
   yregex_find_group (a_focus, x_one, s1);
   DEBUG_YREGEX  yLOG_info    ("s1"        , s1);
   /*---(capture group match-------------*/
   --rce;  if (strchr ("=Þ<>ÜÝ", x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("executing a capture group match");
      yregex_find_group (a_focus, x_two, s2);
      DEBUG_YREGEX  yLOG_info    ("s2"        , s2);
      x_cmp = strcmp  (s1, s2);
      rc = 0;
      switch (x_mod) {
      case G_KEY_EQ  : if (x_cmp == 0)  rc = 1; break;
      case G_CHAR_NE : if (x_cmp != 0)  rc = 1; break;
      case G_KEY_LT  : if (x_cmp <  0)  rc = 1; break;
      case G_KEY_GT  : if (x_cmp >  0)  rc = 1; break;
      case G_CHAR_LE : if (x_cmp <= 0)  rc = 1; break;
      case G_CHAR_GE : if (x_cmp >= 0)  rc = 1; break;
      }
   }
   /*---(has a set)----------------------*/
   --rce;  if (strchr ("[]", x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("executing a has-a match");
      rc = yregex_sets_rule (x_mod, s1, x_two);
   }
   /*---(substring)----------------------*/
   --rce;  if (strchr ("+-", x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("executing a substring match");
      yregex_rule__by_index (x_two, &x_curr);
      if (x_curr == NULL) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      strlcpy (s2, x_curr->str, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s2"        , s2);
      x_cmp = strstr  (s1, s2);
      rc = 0;
      switch (x_mod) {
      case '+'       : if (x_cmp != 0)  rc = 1; break;
      case '-'       : if (x_cmp == 0)  rc = 1; break;
      }
   }
   /*---(execute)------------------------*/
   /*> if (x_mod == '&') {                                                                                              <* 
    *>    DEBUG_YREGEX  yLOG_note    ("executing a freeform match");                                                    <* 
    *>    /+> x_indx  = yregex_exec_index (a_index);                                      <*                            <* 
    *>     *> rc  = yregex_exec_tpos (a_index, x_indx, &x_beg, &x_end);                   <+/                           <* 
    *>    /+> DEBUG_YREGEX  yLOG_complex ("tpos"      , "indx %-3d, beg %-3d, end %-3d", x_indx, x_beg, x_end);   <+/   <* 
    *> }                                                                                                                <*/
   /*---(report)-------------------------*/
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc > 0) {
      DEBUG_YREGEX  yLOG_note    ("pass");
      rc = yregex_exec__passed (HAND_RUL);
   } else {
      DEBUG_YREGEX  yLOG_note    ("FAIL");
      rc = yregex_exec__failed (HAND_RUL);
   }
   /*---(prepare next)-------------------*/
   /*> yregex_exec_launcher (a_level + 1, a_rpos, a_tpos, rc);                        <*/
   /*> if (rc == 1) {                                                                 <* 
    *>    DEBUG_YREGEX  yLOG_note    ("pass");                                        <* 
    *> } else {                                                                       <* 
    *>    DEBUG_YREGEX  yLOG_note    ("FAIL");                                        <* 
    *> }                                                                              <*/
   /*---(prepare next)-------------------*/
   /*> if (x_mod == '&')  yregex_exec_push     (a_level, a_rpos + 1, x_beg, x_end + 1);   <* 
    *> else               yregex_exec_launcher (a_level, a_rpos, a_tpos, rc);             <*/
   yregex_exec_launcher (a_level + 1, a_rpos, a_tpos - 1, rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*
yregex_rule__memory     (tRULE *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   /*---(defense)------------------------*/
   if (a_cur == NULL) {
      strlcpy (g_print, "n/a", LEN_RECD);
      return g_print;
   }
   /*---(defense)------------------------*/
   strlcpy (g_print, "å_.__æ", LEN_RECD);
   ++n;  if (a_cur->str         != NULL)        g_print [n] = 'X';
   ++n;
   ++n;  if (a_cur->m_prev      != NULL)        g_print [n] = 'X';
   ++n;  if (a_cur->m_next      != NULL)        g_print [n] = 'X';
   return g_print;
}

char*
yregex_rule__detail  (tRULE *a_cur)
{
   char        x_self      [LEN_LABEL] = "··········";
   char        x_prev      [LEN_LABEL] = "··········";
   char        x_next      [LEN_LABEL] = "··········";
   if (a_cur != NULL) {
      sprintf (x_self, "%-8.8p", a_cur);
      if (a_cur->m_prev != NULL)  sprintf (x_prev, "%-8.8p", a_cur->m_prev);
      if (a_cur->m_next != NULL)  sprintf (x_next, "%-8.8p", a_cur->m_next);
   }
   snprintf (unit_answer, LEN_RECD, "RULE detail      : self %-10.10s, prev %-10.10s, next %10.10s", x_self, x_prev, x_next);
   return unit_answer;
}

char*
yregex_rule__unit    (char *a_question, int a_num)
{
   /*---(locals)-----------+------+----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tRULE      *x_curr      = NULL;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "RULE__unit, unknown request", 100);
   /*---(mapping)------------------------*/
   if      (strcmp (a_question, "count"    )      == 0) {
      yregex_share__unit (TYPE_RULE, s_head, s_tail, s_count, "count", 0);
   }
   else if (strcmp (a_question, "list"        )   == 0) {
      yregex_share__unit (TYPE_RULE, s_head, s_tail, s_count, "list" , 0);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




/*===============================[[ end code ]]===============================*/
