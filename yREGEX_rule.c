/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



#define    MAX_STR      100
typedef    struct       cSTR        tSTR;
struct cSTR {
   char        str         [LEN_TEXT];
};
tSTR        s_strs      [MAX_STR];
int         s_nstr      = 0;



char
RULE_init            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   for (i = 0; i < MAX_STR; ++i) {
      strlcpy (s_strs [i].str, "", LEN_TEXT);
   }
   s_nstr = 0;
   return 0;
}

int          /*-> tbd --------------------------------[ ------ [fe.D54.156.65]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
RULE__add_str        (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   int         i           =    0;
   int         x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(check rule marker)--------------*/
   for (i = 0; i < LEN_TEXT; ++i) {
      x_ch   = gre.regex [*a_rpos];
      /*> printf ("check %c (%3d)\n", x_ch, x_ch);                                    <*/
      DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
      if (x_ch == 0  )   break;
      if (x_ch == ')')   break;
      s_strs [s_nstr].str [i    ] = x_ch;
      s_strs [s_nstr].str [i + 1] = 0;
      /*> printf ("adding\n");                                                        <*/
      ++(*a_rpos);
   }
   ++s_nstr;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return s_nstr - 1;
}

int
RULE__operator       (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_comp1     =    0;
   uchar       x_comp2     =    0;
   int         x_oper      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (*a_rpos);
   /*---(check first)--------------------*/
   x_comp1  = gre.regex [*a_rpos];
   --rce;  if (x_comp1 <= 30 || x_comp1 > 126) {
      DEBUG_YREGEX  yLOG_snote   ("illegal character");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_schar   (x_comp1);
   --rce;  if (strchr ("=!<>", x_comp1) == NULL) {
      DEBUG_YREGEX  yLOG_snote   ("not an operator");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ++(*a_rpos);
   /*---(check second)-------------------*/
   x_comp2  = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_schar   (x_comp2);
   if (x_comp2 == '=')  ++(*a_rpos);
   /*---(assign)-------------------------*/
   if (x_comp2 == '=') {
      switch (x_comp1) {
      case '=' :  x_oper = G_KEY_EQ;      break;
      case '!' :  x_oper = G_CHAR_NE;     break;
      case '<' :  x_oper = G_CHAR_LE;     break;
      case '>' :  x_oper = G_CHAR_GE;     break;
      }
   }
   else {
      switch (x_comp1) {
      case '<' :  x_oper = G_KEY_LT;      break;
      case '>' :  x_oper = G_KEY_GT;      break;
      }
   }
   /*---(check results)------------------*/
   --rce;  if (x_oper <= 0) {
      --(*a_rpos);
      DEBUG_YREGEX  yLOG_snote   ("operator not understood");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(readout)------------------------*/
   DEBUG_YREGEX  yLOG_sint    (*a_rpos);
   DEBUG_YREGEX  yLOG_sint    (x_oper);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return x_oper;
}

int
RULE__group          (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_ch        =    0;
   int         x_grp       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (*a_rpos);
   /*---(review)-------------------------*/
   x_ch   = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_schar   (x_ch);
   --rce;  if (strchr ("0123456789>", x_ch) == NULL) {
      DEBUG_YREGEX  yLOG_snote   ("not a capture group ref");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(adjust)-------------------------*/
   DEBUG_YREGEX  yLOG_snote   ("good");
   if (x_ch  == '>')  x_grp  = GROUP_FOCUS;
   else               x_grp  = x_ch  - '0' + 1;
   DEBUG_YREGEX  yLOG_sint    (x_grp);
   /*---(move)---------------------------*/
   ++(*a_rpos);
   DEBUG_YREGEX  yLOG_sint    (*a_rpos);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return x_grp;
}

char         /*-> tbd --------------------------------[ ------ [fe.D54.156.65]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
RULE_comp            (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   int         i           =    0;
   int         x_ch        =  ' ';
   int         x_ch2       =  ' ';
   int         x_len       =    0;
   char        t           [LEN_NAME] = "";
   int         x_one       =    0;
   int         x_two       =    0;
   int         x_oper      =    0;
   int         x_set       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(check rule marker)--------------*/
   x_ch   = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != ';') {
      DEBUG_YREGEX  yLOG_note    ("does not have the ; rule indicator");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ++(*a_rpos);
   /*---(check capture group id)---------*/
   x_one = RULE__group (a_rpos);
   if (x_one < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, x_one);
      return x_one;
   }
   /*---(check length)-------------------*/
   for (i = 0; i < 100; i ++) {
      if (gre.regex [*a_rpos + i] == 0  ) break;
      if (gre.regex [*a_rpos + i] == ')') break;
      ++x_len;
   }
   DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len >= 99) {
      DEBUG_YREGEX  yLOG_note    ("rule is too long");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_ch  = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   /*---(check simple rules)-------------*/
   -rce;
   if (strchr ("=!<>", x_ch) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("group comparison rules");
      x_oper = RULE__operator (a_rpos);
      if (x_oper < 0) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, x_oper);
         return x_oper;
      }
      x_two  = RULE__group    (a_rpos);
      if (x_two  < 0) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, x_two);
         return x_two;
      }
      if (gre.regex [*a_rpos] != ')') {
         DEBUG_YREGEX  yLOG_note    ("does not end with paren");
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      COMP_add (';', x_one);
      COMP_mod (x_oper);
      gre.jump [gre.clen - 1] = x_two;
      rc = 0;
      --(*a_rpos);
   }
   /*---(check simple backslash set)-----*/
   else if (x_len == 2 && x_ch == '\\') {
      DEBUG_YREGEX  yLOG_note    ("includes backslash set rule");
      ++(*a_rpos);
      x_ch2  = gre.regex [*a_rpos];
      DEBUG_YREGEX  yLOG_char    ("x_ch2"     , x_ch2);
      x_set = SETS_by_abbr (x_ch2);
      if (x_set <= 0) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, x_set);
         return rce;
      }
      COMP_add (';', x_one);
      COMP_mod ('[');
      gre.jump [gre.clen - 1] = x_set;
      rc = 0;
      /*> ++(*a_rpos);                                                                <*/
   }
   /*---(check custom set)---------------*/
   else if (x_len >  2 && x_ch == '[') {
      DEBUG_YREGEX  yLOG_note    ("includes posix/custom set rule");
      if (gre.regex [*a_rpos + 1] == '^')   x_ch = ']';
      rc = SETS_comp (a_rpos);
      if (rc < 0) {
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      gre.comp [gre.clen - 1] = ';';
      gre.mods [gre.clen - 1] = x_ch;
      gre.jump [gre.clen - 1] = gre.indx [gre.clen - 1];
      gre.indx [gre.clen - 1] = x_one;
      rc = 0;
   }
   /*---(check substring)----------------*/
   else if (strchr ("+-", x_ch) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("includes substring rule");
      ++(*a_rpos);
      x_set = RULE__add_str (a_rpos);
      COMP_add (';', x_one);
      COMP_mod (x_ch);
      gre.jump [gre.clen - 1] = x_set + 1;
      --(*a_rpos);
      rc = 0;
   }
   /*---(now regex)----------------------*/
   else {
      DEBUG_YREGEX  yLOG_note    ("additional group filtering");
      COMP_add (';', x_one);
      COMP_mod ('&');
      --(*a_rpos);
      rc = 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
RULE_exec            (short a_level, short a_rpos, short a_tpos, short a_index)
{
   /*---(locals)-----------+-----+-----+-*/
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
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d, index %-3d", a_level, a_rpos, a_tpos, a_index);
   /*---(prepare)------------------------*/
   x_one       = gre.indx [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_one"     , x_one);
   x_two       = gre.jump [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_two"     , x_two);
   x_mod       = gre.mods [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   rc = EXEC_sub (a_index, x_one);
   strlcpy (s1, g_subf, LEN_TEXT);
   DEBUG_YREGEX  yLOG_info    ("s1"        , s1);
   /*---(capture group match-------------*/
   if (strchr ("=п<>но", x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("executing a capture group match");
      rc = EXEC_sub (a_index, x_two);
      strlcpy (s2, g_subf, LEN_TEXT);
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
   else if (strchr ("[]", x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("executing a has-a match");
      switch (x_mod) {
      case '[' :  rc = SETS_rule     (s1, x_two);   break;
      case ']' :  rc = SETS_rule_rev (s1, x_two);   break;
      }
   }
   /*---(substring)----------------------*/
   else if (strchr ("+-", x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("executing a substring match");
      strlcpy (s2, s_strs [x_two - 1].str, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s2"        , s2);
      x_cmp = strstr  (s1, s2);
      rc = 0;
      switch (x_mod) {
      case '+'       : if (x_cmp != 0)  rc = 1; break;
      case '-'       : if (x_cmp == 0)  rc = 1; break;
      }
   }
   /*---(execute)------------------------*/
   else if (x_mod == '&') {
      DEBUG_YREGEX  yLOG_note    ("executing a freeform match");
      x_indx  = EXEC_indx (a_index);
      rc  = EXEC_tpos (a_index, x_indx, &x_beg, &x_end);
      DEBUG_YREGEX  yLOG_complex ("tpos"      , "indx %-3d, beg %-3d, end %-3d", x_indx, x_beg, x_end);
   }
   /*---(report)-------------------------*/
   if (rc == 1)  DEBUG_YREGEX  yLOG_note    ("pass");
   else          DEBUG_YREGEX  yLOG_note    ("FAIL");
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   /*---(prepare next)-------------------*/
   if (x_mod == '&')  EXEC_push     (a_level, a_rpos + 1, x_beg, x_end + 1);
   else               EXEC_launcher (a_level, a_rpos, a_tpos, rc);
   /*---(complete)-----------------------*/
   return rc;
}

/*> char                                                                                                         <* 
 *> EXEC__and            (int a_level, int a_rpos, int a_tpos, int a_index)                                      <* 
 *> {                                                                                                            <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                  <* 
 *>    char        rc          =    0;                                                                           <* 
 *>    int         x_tpos      =   -1;                                                                           <* 
 *>    int         x_indx      =    0;                                                                           <* 
 *>    /+> int         x_tmax      =   -1;                                                <+/                    <* 
 *>    int         x_beg       =   -1;                                                                           <* 
 *>    int         x_end       =   -1;                                                                           <* 
 *>    /+---(header)-------------------------+/                                                                  <* 
 *>    DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);                                                                <* 
 *>    DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d", a_level, a_rpos, a_tpos);   <* 
 *>    /+---(prepare)------------------------+/                                                                  <* 
 *>    x_indx  = EXEC_indx (a_index);                                                                            <* 
 *>    /+> x_indx  = gre.indx [s_states [a_index].rpos];                                  <+/                    <* 
 *>    printf ("-----------\n");                                                                                 <* 
 *>    printf ("AND, level %-3d, rpos %-3d, tpos %-3d, indx %-3d\n", a_level, a_rpos, a_tpos, x_indx);           <* 
 *>    rc  = EXEC_tpos (a_index, x_indx, &x_beg, &x_end);                                                        <* 
 *>    printf ("AND, returned x_beg %-3d, x_end %-3d\n", x_beg, x_end);                                          <* 
 *>    DEBUG_YREGEX  yLOG_complex ("tpos"      , "indx %-3d, beg %-3d, end %-3d", x_indx, x_beg, x_end);         <* 
 *>    /+---(launch)-------------------------+/                                                                  <* 
 *>    DEBUG_YREGEX  yLOG_note    ("launch next for all successful steps");                                      <* 
 *>    /+> x_tmax  = s_states [a_index].tmax;                                             <+/                    <* 
 *>    /+> printf ("AND, tmax %-3d\n", x_tmax);                                           <+/                    <* 
 *>    /+> if (x_tmax == LEN_TEXT)  EXEC_push (a_level, a_rpos + 1, x_beg, a_tpos + 1);   <*                     <* 
 *>     *> else                     EXEC_push (a_level, a_rpos + 1, x_beg, x_tmax);       <+/                    <* 
 *>    EXEC_push (a_level, a_rpos + 1, x_beg, x_end + 1);                                                        <* 
 *>    /+---(complete)-----------------------+/                                                                  <* 
 *>    DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);                                                                <* 
 *>    return 1;                                                                                                 <* 
 *> }                                                                                                            <*/



/*===============================[[ end code ]]===============================*/
