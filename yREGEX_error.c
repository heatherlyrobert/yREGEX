/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"

/* NEXT STEPS
 *
 * add beautify/fancy to display return troubles
 *
 *
 *
 *
 *
 */



static tERROR     *s_head     = NULL;
static tERROR     *s_tail     = NULL;
static tERROR     *s_curr     = NULL;
static int         s_count    = 0;



static      char        s_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char*
yregex_err__memory      (void *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   tERROR     *x_cur       = NULL;
   /*---(cast)---------------------------*/
   x_cur = (tERROR *) a_cur;
   /*---(defense)------------------------*/
   if (x_cur == NULL) {
      strlcpy (s_print, "n/a", LEN_RECD);
      return s_print;
   }
   /*---(defense)------------------------*/
   strlcpy (s_print, "�__.____.__�", LEN_RECD);
   ++n;  if (x_cur->func        != NULL)        s_print [n] = 'X';
   ++n;  if (x_cur->line        >  0)           s_print [n] = 'X';
   ++n;
   ++n;  if (x_cur->mark        != NULL)        s_print [n] = 'X';
   ++n;  if (x_cur->beg         >  0)           s_print [n] = 'X';
   ++n;  if (x_cur->len         >  0)           s_print [n] = 'X';
   ++n;  if (x_cur->msg         != NULL)        s_print [n] = 'X';
   ++n;
   ++n;  if (x_cur->m_prev      != NULL)        s_print [n] = 'X';
   ++n;  if (x_cur->m_next      != NULL)        s_print [n] = 'X';
   return s_print;
}

char
yregex_err__wipe        (void *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   tERROR     *x_cur       = NULL;
   /*---(cast)---------------------------*/
   x_cur = (tERROR *) a_cur;
   /*---(wipe)---------------------------*/
   x_cur->func     = NULL;
   x_cur->line     = -1;
   x_cur->mark     = NULL;
   x_cur->msg      = NULL;
   x_cur->beg      = 0;
   x_cur->len      = 0;
   x_cur->m_prev   = NULL;
   x_cur->m_next   = NULL;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
yregex_err__new         (void **a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tERROR     *x_new       = NULL;
   int         x_tries     =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_new);
   --rce;  if (*a_new != NULL) {
      DEBUG_DATA   yLOG_snote   ("already set");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   *a_new = NULL;
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = malloc (sizeof (tERROR));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_sint    (x_tries);
   DEBUG_DATA   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe, attach, and increment)----*/
   yregex_err__wipe (x_new);
   if    (s_tail == NULL) {
      DEBUG_DATA   yLOG_snote   ("first entry");
      s_head = x_new;
   } else {
      DEBUG_DATA   yLOG_snote   ("append to tail");
      x_new->m_prev  = s_tail;
      s_tail->m_next = x_new;
   }
   s_tail = x_new;
   ++s_count;
   /*---(save return)--------------------*/
   *a_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yregex_err__free        (void **a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tERROR     *x_old       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_DATA   yLOG_snote   ("never set");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(simplify)-----------------------*/
   x_old = (tERROR *) *a_old;
   /*---(detach and decrement)-----------*/
   if (x_old->m_next != NULL) x_old->m_next->m_prev   = x_old->m_prev;
   else                       s_tail                  = x_old->m_prev;
   if (x_old->m_prev != NULL) x_old->m_prev->m_next   = x_old->m_next;
   else                       s_head                  = x_old->m_next;
   --s_count;
   DEBUG_DATA   yLOG_sint    (s_count);
   /*---(gound links)--------------------*/
   x_old->m_prev = NULL;
   x_old->m_next = NULL;
   /*---(free and ground)----------------*/
   if (x_old->func != NULL)  free (x_old->func);
   if (x_old->mark != NULL)  free (x_old->mark);
   if (x_old->msg  != NULL)  free (x_old->msg);
   free (*a_old);
   /*---(ground)-------------------------*/
   *a_old = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          program wide                        ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
yregex_err_init         (void)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yregex_err__purge       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tERROR     *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   --rce;
   x_curr = s_head;
   while (x_curr != NULL) {
      yregex_err__free (&x_curr);
      x_curr = s_head;
   }
   /*---(ground everything)--------------*/
   s_head   = s_tail   = NULL;
   s_count  = 0;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yregex_err_wrap         (void)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   yregex_err__purge ();
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         create message                       ----===*/
/*====================------------------------------------====================*/
static void  o___CREATE__________o () { return; }

char         /*-> tbd --------------------------------[ leaf   [fz.632.201.00]*/ /*-[00.0000.06#.!]-*/ /*-[--.---.---.--]-*/
yregex_err_add    (cchar *a_func, cint a_line, cchar *a_mark, cint a_beg, cint a_len, cchar *a_msg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tERROR     *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_info    ("a_func"    , a_func);
   DEBUG_YREGEX  yLOG_point   ("a_mark"    , a_mark);
   --rce;  if (a_mark == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_info    ("a_mark"    , a_mark);
   DEBUG_YREGEX  yLOG_point   ("a_msg"     , a_msg);
   --rce;  if (a_msg  == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_info    ("a_msg"     , a_msg);
   /*---(add error)----------------------*/
   yregex_err__new (&x_new);
   DEBUG_YREGEX  yLOG_point   ("x_new"     , x_new);
   if (x_new == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->func = strdup (a_func);
   x_new->line = a_line;
   x_new->mark = strdup (a_mark);
   x_new->beg  = a_beg;
   x_new->len  = a_len;
   x_new->msg  = strdup (a_msg);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        searching entries                     ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char
yregex_err__by_cursor   (void **r_curr, char a_move)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tERROR     *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_NORM   yLOG_senter  (__FUNCTION__);
   DEBUG_NORM   yLOG_schar   (a_move);
   /*---(defaults)-----------------------*/
   if (r_curr != NULL)  *r_curr = NULL;
   /*---(starting point)-----------------*/
   x_curr  = s_curr;
   /*---(defense)------------------------*/
   DEBUG_NORM   yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      /*---(bounce-types)----------------*/
      switch (a_move) {
      case YDLST_HEAD : case YDLST_DHEAD : case YDLST_NEXT :
         x_curr = s_head;
         break;
      case YDLST_TAIL : case YDLST_DTAIL : case YDLST_PREV :
         x_curr = s_tail;
         break;
      }
      /*---(bounce types)----------------*/
      DEBUG_NORM    yLOG_spoint  (x_curr);
      if (x_curr == NULL) {
         DEBUG_NORM    yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(switch)-------------------------*/
   --rce;  switch (a_move) {
   case YDLST_HEAD : case YDLST_DHEAD :
      x_curr = s_head;
      break;
   case YDLST_PREV : case YDLST_DPREV :
      x_curr = x_curr->m_prev;
      break;
   case YDLST_CURR : case YDLST_DCURR :
      break;
   case YDLST_NEXT : case YDLST_DNEXT :
      x_curr = x_curr->m_next;
      break;
   case YDLST_TAIL : case YDLST_DTAIL :
      x_curr = s_tail;
      break;
   default         :
      DEBUG_NORM   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_NORM   yLOG_spoint  (x_curr);
   /*---(check end)----------------------*/
   --rce;  if (x_curr == NULL) {
      /*---(bounce off ends)-------------*/
      if (a_move == YDLST_PREV)  x_curr  = s_head;
      if (a_move == YDLST_NEXT)  x_curr  = s_tail;
      /*---(no bounce)-------------------*/
      if (x_curr == NULL) {
         s_curr = x_curr;
         DEBUG_NORM    yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(mark trouble)----------------*/
      DEBUG_NORM    yLOG_snote   ("BOUNCE");
      rc = rce;
      /*---(done)------------------------*/
   }
   /*---(normal result)------------------*/
   s_curr = x_curr;
   /*---(save back)----------------------*/
   if (r_curr != NULL)  *r_curr = x_curr;
   /*---(complete)-----------------------*/
   DEBUG_NORM   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yregex_err__by_index    (void **r_curr, int a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tERROR     *x_curr      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   DEBUG_DATA   yLOG_sint    (a_index);
   /*---(default)------------------------*/
   if (r_curr != NULL)  *r_curr = NULL;
   /*---(short-cut)----------------------*/
   --rce;  if (a_index == -1) {
      DEBUG_DATA   yLOG_snote   ("requested current");
      x_curr = s_curr;
      if (r_curr != NULL)  *r_curr = x_curr;
      DEBUG_DATA   yLOG_spoint  (x_curr);
      --rce;  if (x_curr == NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   x_curr = s_head;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_sint    (a_index);
   --rce;  if (a_index < -1) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk data)----------------------*/
   while (x_curr != NULL) {
      if (c == a_index)  break;
      ++c;
      x_curr = x_curr->m_next;
   }
   /*---(check result)-------------------*/
   DEBUG_DATA   yLOG_sint    (x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save current)-------------------*/
   s_curr = x_curr;
   if (r_curr != NULL)  *r_curr = x_curr;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> unit testing accessor --------------[ ------ [gs.HA0.1B3.K5]*/ /*-[02.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yregex_err__unit        (char *a_question, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      = 0;
   int         x_back      = 0;
   tERROR     *x_err       = NULL;
   char        rc          =    0;
   int         c           =    0;
   char        t           [LEN_RECD]  = "[]";
   char        s           [LEN_RECD]  = "";
   char        u           [LEN_RECD]  = "";
   char        w           [LEN_RECD]  = "";
   /*---(preprare)-----------------------*/
   strcpy (unit_answer, "ERR              : question not understood");
   /*---(dependency list)----------------*/
   if      (strcmp (a_question, "count"    )      == 0) {
      x_err = s_head; while (x_err != NULL) { ++x_fore; x_err = x_err->m_next; }
      x_err = s_tail; while (x_err != NULL) { ++x_back; x_err = x_err->m_prev; }
      snprintf (unit_answer, LEN_RECD, "ERR count        : num=%4d, fore=%4d, back=%4d", s_count, x_fore, x_back);
   }
   else if (strcmp (a_question, "list"        )   == 0) {
      snprintf (unit_answer, LEN_RECD, "ERR list         : num=%4d, head=%-10p, tail=%p", s_count, s_head, s_tail);
   }
   else if (strcmp (a_question, "entry"    )      == 0) {
      yregex_err__by_index (&x_err, n);
      if (x_err != NULL) {
         sprintf (s, "%2d�%.10s�", strlen (x_err->func), x_err->func);
         sprintf (t, "%2d�%.10s�", strlen (x_err->mark), x_err->mark);
         sprintf (u, "%2d�%.20s�", strlen (x_err->msg) , x_err->msg);
         snprintf (unit_answer, LEN_RECD, "ERR entry   (%2d) : %-14.14s  %4d  %-14.14s  %3d %3d  %s",
               n, s, x_err->line, t, x_err->beg, x_err->len, u);
      } else {
         snprintf (unit_answer, LEN_RECD, "ERR entry   (%2d) :  -��               -   -��              -   -   -��", n);
      }
      return unit_answer;
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


