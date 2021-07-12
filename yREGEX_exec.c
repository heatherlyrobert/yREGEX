/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"





static tSTATE     *s_head     = NULL;        /* full head                    */
static tSTATE     *s_tail     = NULL;        /* tail of list                 */
static tSTATE     *s_curr     = NULL;        /* curent cursor at level       */
static tSTATE     *s_focus    = NULL;        /* current focus of matching    */
static int         s_count    =    0;        /* full count at level          */
static int         s_ready    =    0;
static int         s_begin    =    0;        /* current text beginning point */



static      char        s_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char*
yregex_exec__memory     (tSTATE *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   /*---(defense)------------------------*/
   if (a_cur == NULL) {
      strlcpy (s_print, "n/a", LEN_RECD);
      return s_print;
   }
   /*---(defense)------------------------*/
   strlcpy (s_print, "å_____.___.__.__æ", LEN_RECD);
   ++n;  if (a_cur->lvl         >= 0)           s_print [n] = 'X';
   ++n;  if (a_cur->seq         >= 0)           s_print [n] = 'X';
   ++n;  if (a_cur->beg         >= 0)           s_print [n] = 'X';
   ++n;  if (a_cur->rpos        >= 0)           s_print [n] = 'X';
   ++n;  if (a_cur->tpos        >= 0)           s_print [n] = 'X';
   ++n;
   ++n;  if (a_cur->ready       != '-')         s_print [n] = 'X';
   ++n;  if (a_cur->who         != '-')         s_print [n] = 'X';
   ++n;  if (a_cur->rc          != -66)         s_print [n] = 'X';
   ++n;
   ++n;  if (a_cur->parent      != NULL)        s_print [n] = 'X';
   ++n;  if (a_cur->nchild      >= 1)           s_print [n] = 'X';
   ++n;
   ++n;  if (a_cur->m_prev      != NULL)        s_print [n] = 'X';
   ++n;  if (a_cur->m_next      != NULL)        s_print [n] = 'X';
   return s_print;
}

char
yregex_exec__wipe       (tSTATE *a_cur)
{
   /*---(wipe)---------------------------*/
   a_cur->lvl      = -1;
   a_cur->seq      = -1;
   a_cur->beg      = -1;
   a_cur->rpos     = -1;
   a_cur->tpos     = -1;
   a_cur->ready    = '-';
   a_cur->who      = '-';
   a_cur->rc       = -66;
   a_cur->parent   = NULL;
   a_cur->nchild   = 0;
   a_cur->m_prev   = NULL;
   a_cur->m_next   = NULL;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char yregex_exec__new   (tSTATE **r_new) { return yregex_share_new  (TYPE_EXEC, r_new, &s_head, &s_tail, &s_count); }
char yregex_exec__free  (tSTATE **r_old) { return yregex_share_free (TYPE_EXEC, r_old, &s_head, &s_tail, &s_count); }



/*====================------------------------------------====================*/
/*===----                          program wide                        ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char yregex_exec_init   (void) { return yregex_share_init  (TYPE_EXEC, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_exec__purge (void) { return yregex_share_purge (TYPE_EXEC, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_exec_wrap   (void) { return yregex_share_wrap  (TYPE_EXEC, &s_head, &s_tail, &s_curr, &s_count); }



/*====================------------------------------------====================*/
/*===----                       run-time support                       ----===*/
/*====================------------------------------------====================*/
static void  o___HELPERS_________o () { return; }

char         /*-> tbd --------------------------------[ shoot  [fe.833.144.30]*/ /*-[01.0000.01#.H]-*/ /*-[--.---.---.--]-*/
yregex_exec_prep        (char *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_source"  , a_source);
   /*---(default)------------------------*/
   strlcpy (myREGEX.text, "" , LEN_TEXT);
   myREGEX.tlen  = 0;
   /*---(check regex)--------------------*/
   --rce;  if (a_source  == NULL) {
      DEBUG_YREGEX  yLOG_note    ("can not be null");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = strlcpy (myREGEX.text, a_source , LEN_TEXT);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   --rce;  if (rc     <  0   ) {
      DEBUG_YREGEX  yLOG_note    ("truncated copy");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   myREGEX.tlen = strllen (myREGEX.text , LEN_TEXT);
   DEBUG_YREGEX  yLOG_value   ("myREGEX.tlen"  , myREGEX.tlen);
   /*---(state settings)-----------------*/
   yregex_exec__purge ();
   s_focus = NULL;
   s_ready = 0;
   /*---(finds)--------------------------*/
   yregex_find__purge ();
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yregex_exec__setfocus   (short a_seq)
{
   tSTATE     *x_focus     = NULL;
   s_focus = x_focus;
   yregex_exec__by_index (a_seq, &x_focus);
   if (x_focus != NULL)   s_focus = x_focus;
   else                   return -1;
   return 0;
}

char
yregex_exec__setbegin   (short a_beg)
{
   s_begin = a_beg;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        pushing states                        ----===*/
/*====================------------------------------------====================*/
static void      o___PUSH____________________o (void) {;}

char
yregex_exec__push       (short a_lvl, short a_rpos, short a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tSTATE     *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_value   ("a_lvl"     , a_lvl);
   DEBUG_YREGEX  yLOG_value   ("a_rpos"    , a_rpos);
   DEBUG_YREGEX  yLOG_value   ("a_tpos"    , a_tpos);
   /*---(add error)----------------------*/
   yregex_exec__new (&x_new);
   DEBUG_YREGEX  yLOG_point   ("x_new"     , x_new);
   if (x_new == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(push)---------------------------*/
   x_new->lvl   = a_lvl;
   x_new->seq   = s_count - 1;
   x_new->beg   = s_begin;
   x_new->rpos  = a_rpos;
   x_new->tpos  = a_tpos;
   x_new->ready = 'y';
   ++s_ready;
   /*---(connections)--------------------*/
   if (a_lvl > 0) {
      DEBUG_YREGEX  yLOG_point   ("s_focus"   , s_focus);
      x_new->parent  = s_focus;
      ++(x_new->parent->nchild);
   }
   /*---(update)-------------------------*/
   if (s_focus == NULL)  s_focus = x_new;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yregex_exec__pushback   (short a_lvl, short a_rpos, short a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTATE     *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(push)---------------------------*/
   rc = yregex_exec__push (a_lvl, a_rpos, a_tpos);
   DEBUG_YREGEX  yLOG_value   ("push"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set current)--------------------*/
   x_curr = s_tail;
   DEBUG_YREGEX  yLOG_point   ("x_curr"    , x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check parent)-------------------*/
   DEBUG_YREGEX  yLOG_value   ("lvl"       , x_curr->lvl);
   DEBUG_YREGEX  yLOG_point   ("parent"    , x_curr->parent);
   --rce;  if (x_curr->lvl <= 0 || x_curr->parent == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update parent)------------------*/
   --(x_curr->parent->nchild);
   x_curr->parent = x_curr->parent->parent;
   if (x_curr->parent != NULL)  ++(x_curr->parent->nchild);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        state markers                         ----===*/
/*====================------------------------------------====================*/
static void      o___MARKERS_________________o (void) {;}

char
yregex_exec__next_focus (void)
{
   char        rce         =  -10;
   --rce;  if (s_tail  == NULL)  return rce;
   --rce;  if (s_focus == NULL)  s_focus = s_tail;
   while (s_focus != NULL && s_focus->ready != 'y') {
      s_focus = s_focus->m_next;
   }
   if (s_focus == NULL)  s_focus = s_tail;
   return 0;
}

char
yregex_exec__passed     (char a_who)
{
   char        rce         =  -10;
   if (s_focus == NULL)  return rce;
   s_focus->who   = a_who;
   s_focus->rc    = 1;
   s_focus->ready = '-';
   --s_ready;
   return 1;
}

char
yregex_exec__failed     (char a_who)
{
   char        rce         =  -10;
   if (s_focus == NULL)  return rce;
   s_focus->who   = a_who;
   s_focus->rc    = 0;
   s_focus->ready = '-';
   --s_ready;
   return 0;
}

char
yregex_exec__found      (void)
{
   char        rce         =  -10;
   if (s_focus == NULL)  return rce;
   s_focus->who   = HAND_PAS;
   s_focus->rc    = 100;
   s_focus->ready = '-';
   --s_ready;
   return 1;
}

char
yregex_exec__bombed     (void)
{
   char        rce         =  -10;
   if (s_focus == NULL)  return rce;
   s_focus->who   = HAND_BAD;
   s_focus->rc    = -100;
   s_focus->ready = '-';
   --s_ready;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           handlers                           ----===*/
/*====================------------------------------------====================*/
static void      o___HANDLE__________________o (void) {;}

char
yregex_exec_launcher    (short a_lvl, short a_rpos, short a_tpos, char a_rc)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_reg       =  ' ';
   uchar       x_mod       =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d, rc %-3d", a_lvl, a_rpos, a_tpos, a_rc);
   /*---(prepare)------------------------*/
   x_reg       = myREGEX.comp [a_rpos];
   x_mod       = myREGEX.mods [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   /*---(back launch some)---------------*/
   if (x_reg != ';' && strchr (G_ZERO, x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("always back launch for *@?! types");
      yregex_exec__pushback (a_lvl, a_rpos + 1, a_tpos);
   }
   /*---(always launch if successful)----*/
   if (a_rc > 0) {
      if (x_reg != ';' && strchr (G_MANY, x_mod) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("relaunch for successful *@ types");
         yregex_exec__push (a_lvl, a_rpos    , a_tpos + 1);
      } else {
         DEBUG_YREGEX  yLOG_note    ("launch next for all successful steps");
         yregex_exec__push (a_lvl, a_rpos + 1, a_tpos + 1);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return a_rc;
}

char
yregex_exec__literal    (short a_lvl, short a_rpos, short a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_reg       =    0;
   uchar       x_txt       =    0;
   uchar       x_mod       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "lvl %-3d, rpos %-3d, tpos %-3d", a_lvl, a_rpos, a_tpos);
   /*---(prepare)------------------------*/
   x_reg       = myREGEX.comp [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_reg"     , x_reg);
   x_txt       = myREGEX.text [a_tpos];
   DEBUG_YREGEX  yLOG_char    ("x_txt"     , x_txt);
   /*---(test)---------------------------*/
   if (x_reg == x_txt) {
      DEBUG_YREGEX  yLOG_note    ("matches, passed");
      rc = yregex_exec__passed (HAND_LIT);
   } else {
      DEBUG_YREGEX  yLOG_note    ("FAILED");
      rc = yregex_exec__failed (HAND_LIT);
   }
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   /*---(prepare next)-------------------*/
   yregex_exec_launcher (a_lvl + 1, a_rpos, a_tpos, rc);
   /*---(return)-------------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yregex_exec__anchor         (short a_lvl, short a_rpos, short a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d", a_lvl, a_rpos, a_tpos);
   /*---(prepare)------------------------*/
   x_ch        = myREGEX.comp [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_chr"     , x_ch);
   /*---(handle)-------------------------*/
   switch (x_ch) {
   case '^' :   /* beginning of line */
      if (a_tpos != 0) {
         DEBUG_YREGEX  yLOG_note    ("FAILED, not at BOL");
         rc = yregex_exec__failed (HAND_ANC);
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      DEBUG_YREGEX  yLOG_note    ("at BOL, success, set tpos back one");
      rc = yregex_exec__passed (HAND_ANC);
      break;
   case '$' :   /* end of line       */
      if (a_tpos < myREGEX.tlen){
         DEBUG_YREGEX  yLOG_note    ("FAILED, not at EOL");
         rc = yregex_exec__failed (HAND_ANC);
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      DEBUG_YREGEX  yLOG_note    ("at EOL, success");
      rc = yregex_exec__passed (HAND_ANC);
      break;
   default  : /* anything else */
      DEBUG_YREGEX  yLOG_note    ("non-anchor character, FAILED");
      rc = yregex_exec__failed (HAND_ANC);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   }
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   /*---(prepare next)-------------------*/
   yregex_exec_launcher (a_lvl + 1, a_rpos, a_tpos - 1, rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yregex_exec__group      (short a_lvl, short a_rpos, short a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_ndiv      =    0;
   uchar       x_type      =    0;
   int         x_offset    =    0;
   int         i           =    0;
   int         x_end       =    0;
   uchar       x_mod       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d", a_lvl, a_rpos, a_tpos);
   /*---(prepare)------------------------*/
   yregex_group_endpoints (a_rpos, NULL, &x_end);
   DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
   x_mod       = myREGEX.mods [x_end];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   x_ndiv      = myREGEX.mods [a_rpos] - '0';
   DEBUG_YREGEX  yLOG_value   ("x_ndiv"    , x_ndiv);
   /*---(launch each branch)-------------*/
   for (i = 0; i <= x_ndiv; ++i) {
      x_type  = myREGEX.comp [a_rpos + x_offset];
      DEBUG_YREGEX  yLOG_complex ("branch"    , "lvl %d, rpos %2d, type %c, off %2d, r+o %2d", i + 1, a_rpos, x_type, x_offset, a_rpos + x_offset + 1);
      if (strchr ("(|", x_type) != NULL) {
         rc = yregex_exec__passed (HAND_GRP);
         yregex_exec__push (a_lvl + 1, a_rpos + x_offset + 1, a_tpos);
      }
      x_offset += myREGEX.jump [a_rpos + x_offset];
   }
   /*---(launch without)-----------------*/
   if (strchr (G_ZERO, x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("always back launch for *@?! types");
      rc = yregex_exec__passed (HAND_GRP);
      yregex_exec__push (a_lvl + 1, x_end + 1, a_tpos);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yregex_exec__branch     (short a_lvl, short a_rpos, short a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       x_mod       =    0;
   int         x_beg       =    0;
   int         x_end       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d", a_lvl, a_rpos, a_tpos);
   /*---(prepare)------------------------*/
   x_mod       = myREGEX.mods [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   /*---(locations)----------------------*/
   yregex_group_endpoints (a_rpos, &x_beg, &x_end);
   DEBUG_YREGEX  yLOG_value   ("x_beg"     , x_beg);
   DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
   /*---(always launch if successful)----*/
   if (strchr (G_MANY, x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("relaunch for successful *@ types");
      rc = yregex_exec__passed (HAND_GRP);
      yregex_exec__push (a_lvl + 1, x_beg    , a_tpos);
   } else {
      DEBUG_YREGEX  yLOG_note    ("launch next for all successful steps");
      rc = yregex_exec__passed (HAND_GRP);
      yregex_exec__push (a_lvl + 1, x_end + 1, a_tpos);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yregex_exec__single     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         r           =    0;
   int         t           =    0;
   uchar       c           =  ' ';
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("s_focus"   , s_focus);
   --rce;  if (s_focus == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   l  = s_focus->lvl;
   r  = s_focus->rpos;
   t  = s_focus->tpos;
   c  = myREGEX.comp [r];
   i  = myREGEX.indx [r];
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d, tmax %-3d", l, r, t, myREGEX.tlen);
   /*---(check for null)-----------------*/
   if (c == 0 || r == myREGEX.rlen) {
      DEBUG_YREGEX  yLOG_note    ("success, found end of regex and/or null");
      yregex_exec__found ();
      yregex_find_add (s_focus);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 100;
   }
   /*---(check for overlong ANDs)--------*/
   if (t > myREGEX.tlen) {
      DEBUG_YREGEX  yLOG_note    ("hit a_tmax and must die");
      yregex_exec__bombed ();
      rc = -100;
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(get literals quick)-------------*/
   else if (i == 0) {
      DEBUG_YREGEX  yLOG_note    ("found literal");
      rc = yregex_exec__literal (l, r, t);
   }
   /*---(more complex actions)-----------*/
   else {
      switch (c) {
      case '(' :
         DEBUG_YREGEX  yLOG_note    ("open group");
         rc = yregex_exec__group   (l, r, t);
         break;
      case ')' : case '|' :
         DEBUG_YREGEX  yLOG_note    ("close branch/group");
         rc = yregex_exec__branch  (l, r, t);
         break;
      case ';' :
         DEBUG_YREGEX  yLOG_note    ("execute rule");
         /*> rc = yregex_rule_exec     (l + 1, r, t, a_index);                        <*/
         break;
      case '^' : case '$' :
         DEBUG_YREGEX  yLOG_note    ("true anchor");
         rc = yregex_exec__anchor  (l, r, t);
         break;
      case '<' : case '>' :
         DEBUG_YREGEX  yLOG_note    ("set anchor");
         rc = yregex_sets_break (l, r, t);
         break;
      case '[' :
         DEBUG_YREGEX  yLOG_note    ("found set");
         /*> rc = yregex_sets_exec     (l + 1, r, t);                                 <*/
         break;
      default  :
         DEBUG_YREGEX  yLOG_note    ("other");
         rc = yregex_exec__literal (l, r, t);
         break;
      }
   }
   /*---(finish)-------------------------*/
   /*> if (rc <= 0)  yregex_exec__failed ();                                                 <* 
    *> else          yregex_exec__passed ();                                                 <*/
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        searching entries                     ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char yregex_exec__by_cursor  (char a_move, tSTATE **r_back) { return yregex_share__by_cursor (TYPE_EXEC, &s_head, &s_tail, &s_curr, r_back, a_move); }
char yregex_exec__by_index   (int a_index, tSTATE **r_back) { return yregex_share__by_index  (TYPE_EXEC, &s_head, &s_curr, r_back, a_index); }



/*====================------------------------------------====================*/
/*===----                         main driver                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char 
yregex_exec__driver  (char a_type, cchar *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;
   int         i           =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_char    ("a_type"    , a_type);
   DEBUG_YREGEX  yLOG_point   ("a_source"  , a_source);
   /*---(prepare)------------------------*/
   rc = yregex_exec_prep  (a_source);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(parse)--------------------------*/
   DEBUG_YREGEX  yLOG_info    ("a_source"  , a_source);
   DEBUG_YREGEX  yLOG_value   ("myREGEX.tlen"  , myREGEX.tlen);
   /*---(walk beginning points)----------*/
   for (s_begin = 0; s_begin < myREGEX.tlen; ++s_begin) {
      /*---(prepare)---------------------*/
      DEBUG_YREGEX  yLOG_value   ("BEGIN AT"  , s_begin);
      yregex_exec__push (0, 0, s_begin);
      /*---(walk levels)-----------------*/
      DEBUG_YREGEX  yLOG_complex ("LEVEL"     , "%4d, %4d, %p", i, s_count, s_head);
      /*---(walk states)--------------*/
      while (s_focus != NULL) {
         DEBUG_YREGEX  yLOG_complex ("checking"  , "%-10p, %c", s_focus, s_focus->ready);
         if (s_focus->ready == 'y') {
            rc = yregex_exec__single ();
            if (rc == 100)  ++c;
            DEBUG_YREGEX  yLOG_value   ("single"    , rc);
            if (a_type == '1' && yregex_find_count () > 0) {
               DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
               return 1;
            }
         }
         s_focus = s_focus->m_next;
      }
      s_focus = s_tail;
   }
   /*> rc = yregex_find_count ();                                                     <*/
   if (c > 100)  c = 100;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return c;
}

char yREGEX_full          (cchar *a_source) { return yregex_exec__driver ('a', a_source); }
char yREGEX_filter        (cchar *a_source) { return yregex_exec__driver ('1', a_source); }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> unit testing accessor --------------[ ------ [gs.HA0.1B3.K5]*/ /*-[02.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yregex_exec__unit       (char *a_question, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      = 0;
   int         x_back      = 0;
   tSTATE     *x_curr      = NULL;
   char        rc          =    0;
   int         c           =    0;
   char        t           [LEN_RECD]  = "[]";
   char        s           [LEN_RECD]  = "";
   char        u           [LEN_RECD]  = "";
   char        w           [LEN_RECD]  = "";
   int         i           =    0;
   /*---(preprare)-----------------------*/
   strcpy (unit_answer, "ERR              : question not understood");
   /*---(dependency list)----------------*/
   if      (strcmp (a_question, "count"    )      == 0) {
      x_curr = s_head; while (x_curr != NULL) { ++x_fore; x_curr = x_curr->m_next; }
      x_curr = s_tail; while (x_curr != NULL) { ++x_back; x_curr = x_curr->m_prev; }
      snprintf (unit_answer, LEN_RECD, "EXEC count       : num=%4d, fore=%4d, back=%4d, ready=%4d", s_count, x_fore, x_back, s_ready);
   }
   else if (strcmp (a_question, "list"        )   == 0) {
      snprintf (unit_answer, LEN_RECD, "EXEC list        : num=%4d, head=%-10p, tail=%p", s_count, s_head, s_tail);
   }
   /*> else if (strcmp (a_question, "levels"      )   == 0) {                         <* 
    *>    for (i = 0; i < 20; ++i) {                                                  <* 
    *>       if      (s_count [i] <= 0)    sprintf (t, "   -");                       <* 
    *>       else if (s_count [i] >  999)  sprintf (t, " %3d", 999);                  <* 
    *>       else                          sprintf (t, " %3d", s_count [i]);          <* 
    *>       strcat (s, t);                                                           <* 
    *>    }                                                                           <* 
    *>    snprintf (unit_answer, LEN_RECD, "EXEC levels      :%s", s);                <* 
    *> }                                                                              <*/
   else if (strcmp (a_question, "text"        )   == 0) {
      snprintf (unit_answer, LEN_RECD, "EXEC text        : %2då%sæ", myREGEX.tlen, myREGEX.text);
   }
   else if (strcmp (a_question, "state"    )      == 0) {
      yregex_exec__by_index (n, &x_curr);
      strcpy (s, "(nil)         -n    -m");
      if (x_curr != NULL) {
         if (x_curr->parent != NULL)  sprintf (s, "%-10p   %2dn   %2dm", x_curr->parent, x_curr->parent->seq, x_curr->parent->lvl);
         if (x_curr->rc == -66)   strcpy  (t, "   -");
         else                     sprintf (t, "%4d", x_curr->rc);
         snprintf (unit_answer, LEN_RECD, "EXEC state  (%2d) : %2d  %3db  %3dr  %3dt   %c %c  %4src  %2dc  %s",
               x_curr->seq, x_curr->lvl, x_curr->beg, x_curr->rpos, x_curr->tpos, x_curr->ready, x_curr->who, t, x_curr->nchild, s);
      } else {
         snprintf (unit_answer, LEN_RECD, "EXEC state  (%2d) :  -    -b    -r    -t   - -     -rc   -c  %s", n, s);
      }
      return unit_answer;
   }
   else if (strcmp (a_question, "focus"    )      == 0) {
      x_curr = s_focus;
      strcpy (s, "(nil)         -n    -m");
      if (x_curr != NULL) {
         if (x_curr->parent != NULL)  sprintf (s, "%-10p   %2dn   %2dm", x_curr->parent, x_curr->parent->seq, x_curr->parent->lvl);
         if (x_curr->rc == -66)   strcpy  (t, "   -");
         else                     sprintf (t, "%4d", x_curr->rc);
         snprintf (unit_answer, LEN_RECD, "EXEC focus  (%2d) : %2d  %3db  %3dr  %3dt   %c %c  %4src  %2dc  %s",
               x_curr->seq, x_curr->lvl, x_curr->beg, x_curr->rpos, x_curr->tpos, x_curr->ready, x_curr->who, t, x_curr->nchild, s);
      } else {
         snprintf (unit_answer, LEN_RECD, "EXEC focus  (%2d) :  -    -b    -r    -t   - -     -rc   -c  %s", -1, s);
      }
      return unit_answer;
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




