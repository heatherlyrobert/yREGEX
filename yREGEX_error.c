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



char        g_print     [LEN_RECD] = "";
static      char        s_fancy     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
yregex_error__wipe      (tERROR *a_cur)
{
   /*---(wipe)---------------------------*/
   a_cur->level    =  '-';
   a_cur->cat      = NULL;
   a_cur->beg      = 0;
   a_cur->len      = 0;
   a_cur->msg      = NULL;
   a_cur->m_prev   = NULL;
   a_cur->m_next   = NULL;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char yregex_error__new  (tERROR **r_new) { return yregex_share_new  (TYPE_ERRS, r_new, &s_head, &s_tail, &s_count); }
char yregex_error__free (tERROR **r_old) { return yregex_share_free (TYPE_ERRS, r_old, &s_head, &s_tail, &s_count); }



/*====================------------------------------------====================*/
/*===----                          program wide                        ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char yregex_error_init   (void) { return yregex_share_init  (TYPE_ERRS, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_error__purge (void) { return yregex_share_purge (TYPE_ERRS, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_error_wrap   (void) { return yregex_share_wrap  (TYPE_ERRS, &s_head, &s_tail, &s_curr, &s_count); }

char
yregex_error_reset      (void)
{
   char        rc          =    0;
   rc = yregex_error_wrap ();
   strlcpy (s_fancy, "", LEN_RECD);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         create message                       ----===*/
/*====================------------------------------------====================*/
static void  o___CREATE__________o () { return; }

char         /*-> tbd --------------------------------[ leaf   [fz.632.201.00]*/ /*-[00.0000.06#.!]-*/ /*-[--.---.---.--]-*/
yregex_error_add        (char a_level, char *a_cat, int a_beg, int a_len, char *a_msg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tERROR     *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_cat"     , a_cat);
   --rce;  if (a_cat == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_info    ("a_cat"     , a_cat);
   DEBUG_YREGEX  yLOG_point   ("a_msg"     , a_msg);
   --rce;  if (a_msg  == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_info    ("a_msg"     , a_msg);
   /*---(add error)----------------------*/
   yregex_error__new (&x_new);
   DEBUG_YREGEX  yLOG_point   ("x_new"     , x_new);
   if (x_new == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->level = a_level;
   x_new->cat   = strdup (a_cat);
   x_new->beg   = a_beg;
   x_new->len   = a_len;
   x_new->msg   = strdup (a_msg);
   /*---(update current)-----------------*/
   s_curr = x_new;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        searching entries                     ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char yregex_error__by_cursor (char a_move, tERROR **r_back) { return yregex_share__by_cursor (TYPE_ERRS, &s_head, &s_tail, &s_curr, r_back, a_move); }
char yregex_error__by_index  (int a_index, tERROR **r_back) { return yregex_share__by_index  (TYPE_ERRS, &s_head, &s_curr, r_back, a_index); }



/*====================------------------------------------====================*/
/*===----                       fancy reporting                        ----===*/
/*====================------------------------------------====================*/
static void  o___FANCY___________o () { return; }

char
yregex_error_fancify    (void)
{
   char        rc          =    0;
   tERROR     *x_err       = NULL;
   int         x_last      =   -1;
   int         x_len       =   -1;
   char        x_level     =  '-';
   char        t           [LEN_RECD]  = "";
   char        c           [LEN_LABEL] = "";
   rc = yregex_error__by_cursor (YDLST_DHEAD, &x_err);
   while (x_err != NULL && rc >= 0) {
      /*---(update level/color)----------*/
      switch (x_err->level) {
      case 'w' : 
         if (x_level == '-')  x_level = x_err->level;
         strlcpy (c, BOLD_CYN, LEN_LABEL);
         break;
      case 'F' :
         x_level = x_err->level;
         strlcpy (c, BOLD_ERR, LEN_LABEL);
         break;
      }
      /*---(catch up from last)----------*/
      if (x_last < 0)  x_last = 0;
      x_len = x_err->beg - x_last;
      if (x_len > 0) {
         sprintf (t, "%s%*.*s%s", BOLD_GRN, x_len, x_len, myREGEX.regex + x_last, BOLD_OFF);
         strlcat (s_fancy, t, LEN_RECD);
      }
      /*---(add this trouble)------------*/
      sprintf (t, "%s%*.*s%s", c, x_err->len, x_err->len, myREGEX.regex + x_err->beg, BOLD_OFF);
      strlcat (s_fancy, t, LEN_RECD);
      /*---(prepare for next)------------*/
      x_last = x_err->beg + x_err->len;
      rc = yregex_error__by_cursor (YDLST_DNEXT, &x_err);
      /*---(done)------------------------*/
   }
   /*---(no errors)----------------------*/
   if (x_level == '-') {
      sprintf (s_fancy, "%s%s%s", BOLD_GRN, myREGEX.regex, BOLD_OFF);
      rc = 0;
   }
   /*---(finish)-------------------------*/
   else if (x_last < myREGEX.rlen) {
      switch (x_level) {
      case 'w' :  strlcpy (c, BOLD_GRN, LEN_LABEL);   rc =  1;  break;
      case 'F' :  strlcpy (c, BOLD_MAG, LEN_LABEL);   rc = -1;  break;
      }
      sprintf (t, "%s%s%s", c, myREGEX.regex + x_last, BOLD_OFF);
      strlcat (s_fancy, t, LEN_RECD);
   }
   /*---(complete)-----------------------*/
   return rc;
}

char yREGEX_fancy   (char *r_fancy) { strlcpy (r_fancy, s_fancy, LEN_RECD); return 0; }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*
yregex_error__memory    (tERROR *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   /*---(defense)------------------------*/
   if (a_cur == NULL) {
      strlcpy (g_print, "n/a", LEN_RECD);
      return g_print;
   }
   /*---(defense)------------------------*/
   strlcpy (g_print, "å_.____.__æ", LEN_RECD);
   ++n;  if (a_cur->level       != '-')         g_print [n] = 'X';
   ++n;
   ++n;  if (a_cur->cat         != NULL)        g_print [n] = 'X';
   ++n;  if (a_cur->beg         >  0)           g_print [n] = 'X';
   ++n;  if (a_cur->len         >  0)           g_print [n] = 'X';
   ++n;  if (a_cur->msg         != NULL)        g_print [n] = 'X';
   ++n;
   ++n;  if (a_cur->m_prev      != NULL)        g_print [n] = 'X';
   ++n;  if (a_cur->m_next      != NULL)        g_print [n] = 'X';
   return g_print;
}

char*        /*-> unit testing accessor --------------[ ------ [gs.HA0.1B3.K5]*/ /*-[02.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yregex_error__unit      (char *a_question, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   tERROR     *x_err       = NULL;
   char        rc          =    0;
   int         c           =    0;
   char        t           [LEN_RECD]  = "[]";
   char        s           [LEN_RECD]  = "";
   char        u           [LEN_RECD]  = "";
   char        w           [LEN_RECD]  = "";
   /*---(preprare)-----------------------*/
   strcpy (unit_answer, "ERROR            : question not understood");
   /*---(dependency list)----------------*/
   if      (strcmp (a_question, "count"    )      == 0) {
      yregex_share__unit (TYPE_ERRS, s_head, s_tail, s_count, "count", 0);
   }
   else if (strcmp (a_question, "list"        )   == 0) {
      yregex_share__unit (TYPE_ERRS, s_head, s_tail, s_count, "list" , 0);
   }
   else if (strcmp (a_question, "entry"    )      == 0) {
      yregex_error__by_index (n, &x_err);
      if (x_err != NULL) {
         sprintf (t, "%2då%.10sæ", strlen (x_err->cat ), x_err->cat );
         sprintf (u, "%2då%.40sæ", strlen (x_err->msg) , x_err->msg);
         snprintf (unit_answer, LEN_RECD, "ERROR entry (%2d) : %c %-14.14s  %3d %3d  %s",
               n, x_err->level, t, x_err->beg, x_err->len, u);
      } else {
         snprintf (unit_answer, LEN_RECD, "ERROR entry (%2d) : -  -åæ              -   -   -åæ", n);
      }
      return unit_answer;
   }
   else if (strcmp (a_question, "fancy"    )      == 0) {
      snprintf (unit_answer, LEN_RECD, "ERROR fancy      : å%sæ", s_fancy);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



