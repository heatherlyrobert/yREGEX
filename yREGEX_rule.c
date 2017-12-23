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
   /*---(check capture group id)---------*/
   ++(*a_rpos);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (strchr ("0123456789>", gre.regex [*a_rpos]) == NULL) {
      DEBUG_YREGEX  yLOG_note    ("does not have the capture group ref");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (x_ch  == '>')  x_ch  = GROUP_FOCUS;
   else               x_ch  = x_ch  - '0' + 1;
   /*---(check length)-------------------*/
   ++(*a_rpos);
   x_ch2  = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_ch2"     , x_ch2);
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
   /*---(check simple rules)-------------*/
   if (x_len == 2 && x_ch2 == '=') {
      DEBUG_YREGEX  yLOG_note    ("group equality/backref style rule");
      ++(*a_rpos);
      x_ch2  = gre.regex [*a_rpos];
      DEBUG_YREGEX  yLOG_char    ("x_ch2"     , x_ch2);
      if (strchr ("0123456789>", x_ch2) != NULL) {
         if (x_ch2 == '>')  x_ch2 = GROUP_FOCUS;
         else               x_ch2 = x_ch2 - '0' + 1;
         COMP_add (';', x_ch);
         COMP_mod ('=');
         gre.jump [gre.clen - 1] = x_ch2;
      }
      ++(*a_rpos);
   }
   /*---(check simple rules)-------------*/
   else if (x_len == 2 && x_ch2 == '!') {
      DEBUG_YREGEX  yLOG_note    ("group not-equality/backref style rule");
      ++(*a_rpos);
      x_ch2  = gre.regex [*a_rpos];
      DEBUG_YREGEX  yLOG_char    ("x_ch2"     , x_ch2);
      if (strchr ("0123456789>", x_ch2) != NULL) {
         if (x_ch2 == '>')  x_ch2 = GROUP_FOCUS;
         else               x_ch2 = x_ch2 - '0' + 1;
         COMP_add (';', x_ch);
         COMP_mod ('!');
         gre.jump [gre.clen - 1] = x_ch2;
      }
      ++(*a_rpos);
   }
   /*---(check simple backslash set)-----*/
   else if (x_len == 2 && x_ch2 == '\\') {
      DEBUG_YREGEX  yLOG_note    ("includes backslash set rule");
      ++(*a_rpos);
      x_ch2  = gre.regex [*a_rpos];
      DEBUG_YREGEX  yLOG_char    ("x_ch2"     , x_ch2);
      x_set = SETS_by_abbr (x_ch2);
      COMP_add (';', x_ch);
      COMP_mod ('[');
      gre.jump [gre.clen - 1] = x_set;
      ++(*a_rpos);
   }
   /*---(check custom set)---------------*/
   else if (x_len >  2 && x_ch2 == '[') {
      DEBUG_YREGEX  yLOG_note    ("includes custom set rule");
      rc = SETS_comp (a_rpos);
      gre.comp [gre.clen - 1] = ';';
      gre.mods [gre.clen - 1] = '[';
      gre.jump [gre.clen - 1] = gre.indx [gre.clen - 1];
      gre.indx [gre.clen - 1] = x_ch;
   }
   /*---(check substring)----------------*/
   else if (x_len >= 2 && x_ch2 == ':') {
      DEBUG_YREGEX  yLOG_note    ("includes substring rule");
      ++(*a_rpos);
      x_set = RULE__add_str (a_rpos);
      COMP_add (';', x_ch);
      COMP_mod (':');
      gre.jump [gre.clen - 1] = x_set + 1;
   }
   /*---(now regex)----------------------*/
   else {
      DEBUG_YREGEX  yLOG_note    ("additional group filtering");
      COMP_add (';', x_ch);
      COMP_mod ('&');
      --(*a_rpos);
   }
   /*---(failed)-------------------------*/
   --rce;
   DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
   return rce;
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
   /*---(match)--------------------------*/
   if (x_mod == '=') {
      DEBUG_YREGEX  yLOG_note    ("executing a equal/match");
      rc = EXEC_sub (a_index, x_one);
      strlcpy (s1, g_subf, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s1"        , s1);
      rc = EXEC_sub (a_index, x_two);
      strlcpy (s2, g_subf, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s2"        , s2);
      if (strcmp  (s1, s2) == 0) {
         DEBUG_YREGEX  yLOG_note    ("pass");
         rc = 1;
      } else {
         DEBUG_YREGEX  yLOG_note    ("FAIL");
         rc = 0;
      }
      /*---(complete)-----------------------*/
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      /*---(prepare next)-------------------*/
      EXEC_launcher (a_level, a_rpos, a_tpos, rc);
   }
   /*---(not-match)----------------------*/
   else if (x_mod == '!') {
      DEBUG_YREGEX  yLOG_note    ("executing a not-equal/match");
      rc = EXEC_sub (a_index, x_one);
      strlcpy (s1, g_subf, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s1"        , s1);
      rc = EXEC_sub (a_index, x_two);
      strlcpy (s2, g_subf, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s2"        , s2);
      if (strcmp  (s1, s2) == 0) {
         DEBUG_YREGEX  yLOG_note    ("FAIL");
         rc = 0;
      } else {
         DEBUG_YREGEX  yLOG_note    ("pass");
         rc = 1;
      }
      /*---(complete)-----------------------*/
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      /*---(prepare next)-------------------*/
      EXEC_launcher (a_level, a_rpos, a_tpos, rc);
   }
   /*---(has a set)----------------------*/
   else if (x_mod == '[') {
      DEBUG_YREGEX  yLOG_note    ("executing a has-a match");
      rc = EXEC_sub (a_index, x_one);
      strlcpy (s1, g_subf, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s1"        , s1);
      rc = SETS_rule (s1, x_two);
      /*---(complete)-----------------------*/
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      /*---(prepare next)-------------------*/
      EXEC_launcher (a_level, a_rpos, a_tpos, rc);
   }
   /*---(substring)----------------------*/
   else if (x_mod == ':') {
      DEBUG_YREGEX  yLOG_note    ("executing a substring match");
      rc = EXEC_sub (a_index, x_one);
      strlcpy (s1, g_subf, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s1"        , s1);
      strlcpy (s2, s_strs [x_two - 1].str, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s2"        , s2);
      if (strstr  (s1, s2) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("pass");
         rc = 1;
      } else {
         DEBUG_YREGEX  yLOG_note    ("FAIL");
         rc = 0;
      }
      /*---(complete)-----------------------*/
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      /*---(prepare next)-------------------*/
      EXEC_launcher (a_level, a_rpos, a_tpos, rc);
   }
   /*---(execute)------------------------*/
   else if (x_mod == '&') {
      DEBUG_YREGEX  yLOG_note    ("executing a freeform match");
      rc = EXEC_sub (a_index, x_one);
      strlcpy (s1, g_subf, LEN_TEXT);
      DEBUG_YREGEX  yLOG_info    ("s1"        , s1);
      x_indx  = EXEC_indx (a_index);
      /*> printf ("-----------\n");                                                   <*/
      /*> printf ("AND, level %-3d, rpos %-3d, tpos %-3d, indx %-3d\n", a_level, a_rpos, a_tpos, x_indx);   <*/
      rc  = EXEC_tpos (a_index, x_indx, &x_beg, &x_end);
      /*> printf ("AND, returned x_beg %-3d, x_end %-3d\n", x_beg, x_end);            <*/
      DEBUG_YREGEX  yLOG_complex ("tpos"      , "indx %-3d, beg %-3d, end %-3d", x_indx, x_beg, x_end);
      DEBUG_YREGEX  yLOG_note    ("launch next for all successful steps");
      /*---(complete)-----------------------*/
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      EXEC_push (a_level, a_rpos + 1, x_beg, x_end + 1);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   }
   /*---(return)-------------------------*/
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
