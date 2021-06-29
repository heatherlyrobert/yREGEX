/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"


/*
 *
 *   base = (
 *   indx = group + 1
 *
 *
 *
 *
 *
 */


/*====================------------------------------------====================*/
/*===----                           program level                      ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
yregex_group_init       (void)
{
   yregex_group__purge ();
   return 0;
}

char
yregex_group__purge     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(default)------------------------*/
   myREGEX.g_lvl    =    0;
   myREGEX.g_cnt    =    0;
   myREGEX.g_nam    =    1;
   myREGEX.g_hid    =   10;
   myREGEX.g_mul    =  100;
   myREGEX.g_foc    =  '-';
   strlcpy (myREGEX.g_mrk, "               ", LEN_LABEL);
   for (i = 0; i < LEN_LABEL; ++i) {
      myREGEX.g_beg [i] = -1;
      myREGEX.g_end [i] = -1;
   }
   for (i = 0; i < MAX_STACK; ++i) {
      myREGEX.g_stk [i] = -1;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yregex_group_wrap       (void)
{
   yregex_group__purge ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      compilation phase                       ----===*/
/*====================------------------------------------====================*/
static void      o___COMPILE_________________o (void) {;}

char
yregex_group__open      (int *a_rpos)
{
   /*---(design notes)-------------------*/
   /*
    *   groups   0      = focus
    *            1 - 9  = named groups
    *            10+    = hidden
    *
    *   base = (
    *   indx = group + 1   (for display purposes as uchar 0 means empty)
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_char      =  '-';
   char        x_next      =  '-';
   int         x_grp       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_rpos"    , a_rpos);
   --rce;  if (a_rpos == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   --rce;  if (*a_rpos < 0 || *a_rpos > myREGEX.rlen) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_char = myREGEX.regex [*a_rpos];
   x_next = myREGEX.regex [*a_rpos + 1];
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_char    ("x_char"    , x_char);
   --rce;  if (x_char != '(') {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_char    ("x_next"    , x_next);
   /*---(regex container)----------------*/
   if (*a_rpos == 0) {
      DEBUG_YREGEX  yLOG_note    ("requested open regex container");
      x_grp = (myREGEX.g_hid)++;
      /*> myREGEX.g_mrk [x_grp] = '.';                                                <*/
   }
   /*---(focus group)--------------------*/
   else if (x_next == '>') {
      DEBUG_YREGEX  yLOG_note    ("requested focus group (>´´´<)");
      ++(*a_rpos);
      if (myREGEX.g_foc != 'y') {
         myREGEX.g_foc = 'y';
         x_grp = GROUP_FOCUS;
         myREGEX.g_mrk [x_grp] = 'F';
      } else {
         DEBUG_YREGEX  yLOG_note    ("already had a focus group, had to hide");
         x_next = 0;
      }
   }
   /*---(rule group)---------------------*/
   else if (x_next == ';') {
      DEBUG_YREGEX  yLOG_note    ("requested rule group (;´´´)");
      ++*a_rpos;
      x_grp = (myREGEX.g_hid)++;
   }
   /*---(numbered group)-----------------*/
   else if (x_next == '#') {
      DEBUG_YREGEX  yLOG_note    ("requested numbered group (#´´´)");
      ++(*a_rpos);
      if (myREGEX.g_nam < 10) {
         x_grp = (myREGEX.g_nam)++;
         DEBUG_YREGEX  yLOG_note    ("openning numbered group");
         myREGEX.g_mrk [x_grp] = 'y';
      } else {
         DEBUG_YREGEX  yLOG_note    ("group number too high, had to hide");
         x_next = 0;
      }
   }
   /*---(other second chars)-------------*/
   else  x_next = 0;
   /*---(hidden group)-------------------*/
   if (x_next == 0)  {
      DEBUG_YREGEX  yLOG_note    ("request hidden group (´´´)");
      x_grp = (myREGEX.g_hid)++;
   }
   /*---(update)-------------------------*/
   yregex_comp_add  (x_char, x_grp + 1);
   myREGEX.g_stk [myREGEX.g_lvl] = x_grp;
   ++(myREGEX.g_cnt);
   /*---(increase level)-----------------*/
   ++(myREGEX.g_lvl);
   DEBUG_YREGEX  yLOG_value   ("g_lvl"     , myREGEX.g_lvl);
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yregex_group__branch    (int *a_rpos)
{
   /*---(design notes)-------------------*/
   /*
    *   base = |
    *   indx = group + 1   (for display purposes as uchar 0 means empty)
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_char      =  '-';
   int         x_grp       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_rpos"    , a_rpos);
   --rce;  if (a_rpos == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   --rce;  if (*a_rpos < 0 || *a_rpos > myREGEX.clen) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_char = myREGEX.regex [*a_rpos];
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_char    ("x_char"    , x_char);
   --rce;  if (x_char != '|') {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(OR branch)----------------------*/
   DEBUG_YREGEX  yLOG_note    ("divide branches/matches");
   x_grp = myREGEX.g_stk [myREGEX.g_lvl - 1];
   yregex_comp_add  (x_char, x_grp + 1);
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yregex_group__close     (int *a_rpos)
{
   /*---(design notes)-------------------*/
   /*
    *   base = )
    *   indx = group + 1   (for display purposes as uchar 0 means empty)
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_char      =  '-';
   int         x_grp       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_rpos"    , a_rpos);
   --rce;  if (a_rpos == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   --rce;  if (*a_rpos < 0 || *a_rpos > myREGEX.rlen) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_char = myREGEX.regex [*a_rpos];
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_char    ("x_char"    , x_char);
   --rce;  if (strchr ("<)", x_char) == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(decrease level)-----------------*/
   --(myREGEX.g_lvl);
   DEBUG_YREGEX  yLOG_value   ("g_lvl"     , myREGEX.g_lvl);
   /*---(find group)---------------------*/
   x_grp = myREGEX.g_stk [myREGEX.g_lvl];
   DEBUG_YREGEX  yLOG_value   ("x_grp"     , x_grp);
   /*---(regex container)----------------*/
   --rce;  if (myREGEX.g_lvl == 0) {
      DEBUG_YREGEX  yLOG_note    ("requested close regex container");
   }
   /*---(primary group)------------------*/
   else if (x_char == '<') {
      DEBUG_YREGEX  yLOG_note    ("close focus group (>´´´<>");
      if (x_grp != GROUP_FOCUS) {
         DEBUG_YREGEX  yLOG_note    ("primary focus parens do not match");
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return rce;
      }
      x_char = ')';
      ++(*a_rpos);
   }
   /*---(other groups)-------------------*/
   else if (x_char == ')') {
      DEBUG_YREGEX  yLOG_note    ("close named/normal/hidden group (´´´)");
   }
   /*---(update)-------------------------*/
   yregex_comp_add   (x_char, x_grp + 1);
   yregex_group__fix (x_grp + 1);
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yregex_group__fix       (int a_grp)
{
   /*---(design notes)-------------------*/
   /*
    * updates entries after group closes
    *
    *   mods = count of branches (only at openning)
    *   jump = index increase to next grouping element at same index
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         x_ch        =  ' ';
   int         x_indx      =    0;
   int         x_jump      =    0;
   int         x_or        =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_grp"     , a_grp);
   DEBUG_YREGEX  yLOG_value   ("myREGEX.clen"  , myREGEX.clen);
   /*---(track backwards)----------------*/
   for (i = myREGEX.clen - 1; i >= 0; --i) {
      /*---(prepare)---------------------*/
      x_ch   = myREGEX.comp [i];
      x_indx = myREGEX.indx [i];
      /*---(branch)----------------------*/
      if (x_indx == a_grp && x_ch == '|') {
         myREGEX.jump [i] = x_jump;
         x_jump =  0;
         ++x_or;
      }
      /*---(start)--------------------*/
      else if (x_indx == a_grp && x_ch == '(') {
         myREGEX.jump [i] = x_jump;
         myREGEX.mods [i] = '0' + x_or;
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
yregex_group_comp       (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   uchar       x_char      =  ' ';
   uchar       x_next      =  ' ';
   int         x_grp       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_rpos"    , a_rpos);
   --rce;  if (a_rpos == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   --rce;  if (*a_rpos < 0 || *a_rpos > myREGEX.rlen) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_char = myREGEX.regex [*a_rpos];
   x_next = myREGEX.regex [*a_rpos + 1];
   DEBUG_YREGEX  yLOG_complex ("position"  , "x_char %c, x_next %c", x_char, x_next);
   /*---(defense)------------------------*/
   --rce;  if (*a_rpos == 0 && strchr (">#;", x_next) != NULL){
      DEBUG_YREGEX  yLOG_note    ("prefix greater (>), hash (#), or semi (;), not really group");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   switch (x_char) {
   case '(' :
      rc = yregex_group__open   (a_rpos);
      break;
   case '|' :
      rc = yregex_group__branch (a_rpos);
      break;
   case ')' : case '<' :
      rc = yregex_group__close  (a_rpos);
      break;
   }
   DEBUG_YREGEX  yLOG_complex ("current"   , "lvl %2d, cnt %3d, nrm %2d, hid %2d, mul %3d", myREGEX.g_lvl, myREGEX.g_cnt, myREGEX.g_nam, myREGEX.g_hid, myREGEX.g_mul);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                       execution phase                        ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTE_________________o (void) {;}

char
yregex_group_endpoints  (int a_cur, int *a_beg, int *a_end)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (a_cur);
   /*---(prepare)------------------------*/
   x_lvl       = myREGEX.indx [a_cur];
   DEBUG_YREGEX  yLOG_sint    (x_lvl);
   /*---(beginning)----------------------*/
   if (a_beg != NULL) {
      DEBUG_YREGEX  yLOG_snote   ("begin");
      *a_beg = -1;
      for (i = a_cur - 1; i >= 0; --i) {
         if (myREGEX.indx [i] != x_lvl)  continue;
         if (myREGEX.comp [i] != '('  )  continue;
         *a_beg = i;
      }
      DEBUG_YREGEX  yLOG_sint    (*a_beg);
   }
   /*---(ending)-------------------------*/
   if (a_end != NULL) {
      DEBUG_YREGEX  yLOG_snote   ("end");
      *a_end = -1;
      for (i = a_cur + 1; i < myREGEX.clen; ++i) {
         if (myREGEX.indx [i] != x_lvl)  continue;
         if (myREGEX.comp [i] != ')'  )  continue;
         *a_end = i;
      }
      DEBUG_YREGEX  yLOG_sint    (*a_end);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*        /*-> unit test accessor -----------------[ light  [us.D90.241.L0]*/ /*-[03.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yregex_group__unit      (char *a_question, int a_num)
{
   char        s           [LEN_TERSE] = "";
   char        t           [LEN_HUND]  = "";
   int         i           =    0;
   if        (strncmp (a_question, "stats"     , 20)  == 0) {
      for (i = 0; i < 20; ++i) {
         if (myREGEX.g_stk [i] >= 0)  sprintf (s, " %2d", myREGEX.g_stk [i]);
         else                         sprintf (s, "  -");
         strcat  (t, s);
      }
      snprintf (unit_answer, LEN_TEXT, "GROUP stats      : %2d %3d %2d %3d %3d %c %s",
            myREGEX.g_lvl, myREGEX.g_cnt, myREGEX.g_nam, myREGEX.g_hid, myREGEX.g_mul, myREGEX.g_foc, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


