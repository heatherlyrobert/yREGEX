/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"


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
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(check group)--------------------*/
   x_ch   = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != '(') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a (");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check rule marker)--------------*/
   ++(*a_rpos);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
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
      ++(*a_rpos);
      x_ch2  = gre.regex [*a_rpos];
      DEBUG_YREGEX  yLOG_char    ("x_ch2"     , x_ch2);
      if (strchr ("0123456789>", x_ch2) != NULL) {
         if (x_ch  == '>')  x_ch  = GROUP_FOCUS;
         else               x_ch  = x_ch  - '0' + 1;
         if (x_ch2 == '>')  x_ch2 = GROUP_FOCUS;
         else               x_ch2 = x_ch2 - '0' + 1;
         COMP_add (';', x_ch);
         COMP_mod ('=');
         gre.jump [gre.clen - 1] = x_ch2;
      }
      *a_rpos += 2;
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
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_one       = gre.indx [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_one"     , x_one);
   x_two       = gre.jump [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_two"     , x_two);
   x_mod       = gre.mods [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   /*---(execute)------------------------*/
   if (x_mod == '=') {
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
   }
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   /*---(prepare next)-------------------*/
   EXEC_launcher (a_level, a_rpos, a_tpos, rc);
   /*---(return)-------------------------*/
   return rc;
}



/*===============================[[ end code ]]===============================*/
