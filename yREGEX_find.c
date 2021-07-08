/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"

/*
 *
 * metis  mw4··  additional unit testing and debugging on find algorithm
 * metis  mw4··  external function to return primary focus group pos/len
 * metis  ml1··  investigate switching to malloc for find results
 * metis  ww4#·  look at speeding up FIND__dup for overall performance
 *
 *
 */

#define     MAX_FIND    1000



/*---(static.vars)------+-----------+-*//*-+----------------------------------*/
static      tFIND      *s_head      = NULL;
static      tFIND      *s_tail      = NULL;
static      tFIND      *s_curr      = NULL;
static      int         s_count     =    0;



static      char        s_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char*
yregex_find__memory     (tFIND *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   int         i           =    0;
   /*---(defense)------------------------*/
   if (a_cur == NULL) {
      strlcpy (s_print, "n/a", LEN_RECD);
      return s_print;
   }
   /*---(defense)------------------------*/
   strlcpy (s_print, "å_____.__________.__æ", LEN_RECD);
   ++n;  if (a_cur->beg         >= 0)           s_print [n] = 'X';
   ++n;  if (a_cur->end         >= 0)           s_print [n] = 'X';
   ++n;  if (a_cur->len         >= 0)           s_print [n] = 'X';
   ++n;  if (a_cur->text        != NULL)        s_print [n] = 'X';
   ++n;  if (a_cur->quan        != NULL)        s_print [n] = 'X';
   ++n;
   for (i = 0; i < MAX_SUB; ++i) {
      ++n;  if (a_cur->s_off [i]     >= 0)        s_print [n] = 'X';
   }
   ++n;
   ++n;  if (a_cur->m_prev      != NULL)        s_print [n] = 'X';
   ++n;  if (a_cur->m_next      != NULL)        s_print [n] = 'X';
   return s_print;
}

char
yregex_find__wipe       (tFIND *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(wipe)---------------------------*/
   a_cur->beg      = -1;
   a_cur->end      = -1;
   a_cur->len      = -1;
   a_cur->text     = NULL;
   a_cur->quan     = NULL;
   for (i = 0; i < MAX_SUB; ++i) {
      a_cur->s_off [i]     = -1;
      a_cur->s_len [i]     = -1;
   }
   a_cur->m_prev   = NULL;
   a_cur->m_next   = NULL;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char yregex_find__new   (tFIND **r_new) { return yregex_share_new  (TYPE_FIND, r_new, &s_head, &s_tail, &s_count); }
char yregex_find__free  (tFIND **r_old) { return yregex_share_free (TYPE_FIND, r_old, &s_head, &s_tail, &s_count); }



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char yregex_find_init    (void) { return yregex_share_init  (TYPE_FIND, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_find__purge  (void) { return yregex_share_purge (TYPE_FIND, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_find_wrap    (void) { return yregex_share_wrap  (TYPE_FIND, &s_head, &s_tail, &s_curr, &s_count); }



/*====================------------------------------------====================*/
/*===----                       creating finds                         ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE__________________o (void) {;}

char
yregex_find__full       (short a_beg, char *a_text, char *a_quan)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFIND      *x_new       = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_beg < 0 || a_beg >= myREGEX.tlen)  return rce;
   --rce;  if (a_text == NULL)  return rce;
   --rce;  if (a_quan == NULL)  return rce;
   --rce;  if (strlen (a_text) != strlen (a_quan))  return rce;
   /*---(create a find)------------------*/
   rc = yregex_find__new (&x_new);
   --rce;  if (x_new == NULL) {
      return rce;
   }
   /*---(check dups)---------------------*/
   x_new->beg   = a_beg;
   x_new->len   = strlen (a_text);
   x_new->end   = a_beg + x_new->len - 1;
   x_new->text  = strdup (a_text);
   x_new->quan  = strdup (a_quan);
   /*---(complete)-----------------------*/
   return 0;
}

char
yregex_find__sub        (char a_num, short a_off, short a_len)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFIND      *x_cur       = NULL;
   x_cur = s_tail;
   /*---(defense)------------------------*/
   --rce;  if (x_cur == NULL)                       return rce;
   --rce;  if (a_num < 0 || a_num > 9)              return rce;
   --rce;  if (a_off < 0 || a_off >= x_cur->len)    return rce;
   --rce;  if (a_len < 1 || a_off + a_len - 1 >= x_cur->len)    return rce;
   /*---(update)-------------------------*/
   x_cur->s_off [a_num]  = a_off;
   x_cur->s_len [a_num]  = a_len;
   /*---(complete)-----------------------*/
   return 0;
}

int yregex_find_count       (void) { return s_count; }

char
yregex_find__listall    (char a_detail)
{
   /*> int         i           =     0;                                                                                                           <* 
    *> int         j           =     0;                                                                                                           <* 
    *> printf ("num  ---text/quan-----------------------------------\n\n");                                                                       <* 
    *> for (i = 0; i < s_nfind; ++i) {                                                                                                            <* 
    *>    if (s_finds [i].beg < 0) break;                                                                                                         <* 
    *>    printf ("%-4d %-4d  text %-3d[%s]\n", i, s_finds [i].ref, strlen (s_finds [i].text), s_finds [i].text);                                 <* 
    *>    printf ("     b%-4d quan %-3d[%s]\n", s_finds [i].beg, strlen (s_finds [i].quan), s_finds [i].quan);                                    <* 
    *>    printf ("     e%-4d l %-3d, g %-3d, b %-3d\n", s_finds [i].end, s_finds [i].lazy, s_finds [i].greedy, s_finds [i].balance);             <* 
    *>    if (a_detail == 'y') {                                                                                                                  <* 
    *>       for (j = 0; j < 11; ++j) {                                                                                                           <* 
    *>          if (s_finds [i].sub [j].len >= 0) {                                                                                               <* 
    *>             printf ("     sub%2d b%-4d text %-3d[%s]\n", j, s_finds [i].sub [j].beg, s_finds [i].sub [j].len, s_finds [i].sub [j].text);   <* 
    *>             printf ("                 quan %-3d[%s]\n",    s_finds [i].sub [j].len, s_finds [i].sub [j].quan);                             <* 
    *>          }                                                                                                                                 <* 
    *>       }                                                                                                                                    <* 
    *>    }                                                                                                                                       <* 
    *>    printf ("\n");                                                                                                                          <* 
    *> }                                                                                                                                          <* 
    *> return 0;                                                                                                                                  <*/
}

char yREGEX_finds (void) { return yregex_find__listall ('y'); }

int
yregex_find__solution   (char a_scorer, int a_pos, int  *a_beg, int *a_len, int *a_fbeg, int *a_flen)
{
   /*> /+---(locals)-----------+------+----+-+/                                                              <* 
    *> char        rce         =   -10;                                                                      <* 
    *> int         i           =     0;                                                                      <* 
    *> int         x_pos       =    -1;                                                                      <* 
    *> int         x_best      =    -1;                                                                      <* 
    *> int         x_score     = -100000;                                                                    <* 
    *> int         x_top       = +100000;                                                                    <* 
    *> int         x_left      = +100000;                                                                    <* 
    *> int         x_right     = -100000;                                                                    <* 
    *> /+---(header)-------------------------+/                                                              <* 
    *> DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);                                                            <* 
    *> /+---(default)------------------------+/                                                              <* 
    *> if (a_beg  != NULL)  *a_beg  = -1;                                                                    <* 
    *> if (a_len  != NULL)  *a_len  = -1;                                                                    <* 
    *> if (a_fbeg != NULL)  *a_fbeg = -1;                                                                    <* 
    *> if (a_flen != NULL)  *a_flen =  0;                                                                    <* 
    *> /+---(defense)------------------------+/                                                              <* 
    *> DEBUG_YREGEX  yLOG_value   ("a_scorer"  , a_scorer);                                                  <* 
    *> --rce;  if (a_scorer == 0 || strchr ("$*?+@!~", a_scorer) == NULL) {                                  <* 
    *>    DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);                                                    <* 
    *>    return rce;                                                                                        <* 
    *> }                                                                                                     <* 
    *> DEBUG_YREGEX  yLOG_char    ("a_scorer"  , a_scorer);                                                  <* 
    *> /+---(prepare)------------------------+/                                                              <* 
    *> DEBUG_YREGEX  yLOG_value   ("a_pos"     , a_pos);                                                     <* 
    *> --rce;  if (a_pos < 0) {                                                                              <* 
    *>    DEBUG_YREGEX  yLOG_note    ("reset a negative position");                                          <* 
    *>    switch (a_scorer) {                                                                                <* 
    *>    case '$' :             a_pos = 0;         break;                                                   <* 
    *>    case '?' : case '!' :  a_pos = 0;         break;                                                   <* 
    *>    case '+' : case '~' :  a_pos = +100000;   break;                                                   <* 
    *>    case '*' : case '@' :  a_pos = 0;         break;                                                   <* 
    *>    }                                                                                                  <* 
    *>    DEBUG_YREGEX  yLOG_value   ("a_pos"     , a_pos);                                                  <* 
    *> }                                                                                                     <* 
    *> /+---(find outer bounds)--------------+/                                                              <* 
    *> DEBUG_YREGEX  yLOG_note    ("find outermost acceptable boundaries");                                  <* 
    *> for (i = 0; i < s_nfind; ++i) {                                                                       <* 
    *>    /+---(first left)------------------+/                                                              <* 
    *>    x_pos = s_finds [i].beg;                                                                           <* 
    *>    if (x_pos >= a_pos && x_pos < x_left )  x_left  = x_pos;                                           <* 
    *>    /+---(then right)------------------+/                                                              <* 
    *>    x_pos = s_finds [i].end;                                                                           <* 
    *>    if (x_pos <= a_pos && x_pos > x_right)  x_right = x_pos;                                           <* 
    *>    /+---(done)------------------------+/                                                              <* 
    *> }                                                                                                     <* 
    *> DEBUG_YREGEX  yLOG_value   ("x_left"    , x_left);                                                    <* 
    *> DEBUG_YREGEX  yLOG_value   ("x_right"   , x_right);                                                   <* 
    *> /+---(set boundaries)-----------------+/                                                              <* 
    *> DEBUG_YREGEX  yLOG_note    ("reset acceptable boundaries based on scorer");                           <* 
    *> switch (a_scorer) {                                                                                   <* 
    *> case '$' : case '*' : case '@' : x_left  = x_right = -1; break;                                       <* 
    *> case '?' : case '!' :                      x_right = -1; break;                                       <* 
    *> case '+' : case '~' :            x_left  =           -1; break;                                       <* 
    *> }                                                                                                     <* 
    *> DEBUG_YREGEX  yLOG_value   ("x_left"    , x_left);                                                    <* 
    *> DEBUG_YREGEX  yLOG_value   ("x_right"   , x_right);                                                   <* 
    *> /+---(set initial score)--------------+/                                                              <* 
    *> DEBUG_YREGEX  yLOG_note    ("set top score based on scorer");                                         <* 
    *> switch (a_scorer) {                                                                                   <* 
    *> case '$' : case '*' : case '+' : case '?' :  x_top = -100000;  break;                                 <* 
    *> case '@' : case '~' : case '!' :             x_top = +100000;  break;                                 <* 
    *> }                                                                                                     <* 
    *> DEBUG_YREGEX  yLOG_value   ("x_top"     , x_top);                                                     <* 
    *> /+---(locate)-------------------------+/                                                              <* 
    *> for (i = 0; i < s_nfind; ++i) {                                                                       <* 
    *>    DEBUG_YREGEX  yLOG_complex ("match"     , "%3d, %3d, %3d", i, s_finds [i].beg, s_finds [i].end);   <* 
    *>    /+---(filter)----------------------+/                                                              <* 
    *>    if (x_left  >= 0 && s_finds [i].beg != x_left ) {                                                  <* 
    *>       DEBUG_YREGEX  yLOG_note    ("does not match left side, skip");                                  <* 
    *>       continue;                                                                                       <* 
   *>    }                                                                                                  <* 
      *>    if (x_right >= 0 && s_finds [i].end != x_right) {                                                  <* 
         *>       DEBUG_YREGEX  yLOG_note    ("does not match right side, skip");                                 <* 
            *>       continue;                                                                                       <* 
            *>    }                                                                                                  <* 
            *>    /+---(gather)----------------------+/                                                              <* 
            *>    if (a_scorer == '$')  x_score  = s_finds [i].balance;                                              <* 
            *>    else                  x_score  = s_finds [i].greedy + s_finds [i].lazy;                            <* 
            *>    DEBUG_YREGEX  yLOG_value   ("x_score"   , x_score);                                                <* 
            *>    DEBUG_YREGEX  yLOG_value   ("x_top"     , x_top);                                                  <* 
            *>    /+---(filter, too)-----------------+/                                                              <* 
            *>    switch (a_scorer) {                                                                                <* 
               *>    case '$' : case '*' : case '+' : case '?' :                                                        <* 
                  *>       if (x_score <= x_top) {                                                                         <* 
                     *>          DEBUG_YREGEX  yLOG_note    ("greedy and score is less than top, skip");                      <* 
                        *>          continue;                                                                                    <* 
                        *>       }                                                                                               <* 
                        *>       break;                                                                                          <* 
                        *>    case '@' : case '~' : case '!' :                                                                   <* 
                        *>       if (x_score >= x_top) {                                                                         <* 
                           *>          DEBUG_YREGEX  yLOG_note    ("lazy and score is more than top, skip");                        <* 
                              *>          continue;                                                                                    <* 
                              *>       }                                                                                               <* 
                              *>       break;                                                                                          <* 
                              *>    }                                                                                                  <* 
                              *>    /+---(update)----------------------+/                                                              <* 
                              *>    DEBUG_YREGEX  yLOG_note    ("new best match");                                                     <* 
                              *>    x_top   = x_score;                                                                                 <* 
                              *>    x_best  = i;                                                                                       <* 
                              *> }                                                                                                     <* 
                              *> /+---(return)-------------------------+/                                                              <* 
                              *> DEBUG_YREGEX  yLOG_note    ("set return variables");                                                  <* 
                              *> if (a_beg  != NULL)  *a_beg  = s_finds [x_best].beg;                                                  <* 
                              *> if (a_len  != NULL)  *a_len  = s_finds [x_best].len;                                                  <* 
                              *> if (a_fbeg != NULL)  *a_fbeg = s_finds [x_best].sub [10].beg;                                         <* 
                              *> if (a_flen != NULL)  *a_flen = s_finds [x_best].sub [10].len;                                         <* 
                              *> /+---(complete)-----------------------+/                                                              <* 
                              *> DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);                                                            <* 
                              *> return x_best;                                                                                        <*/
}

char
yREGEX_best          (cchar a_type, cchar a_dir, int  *a_beg, int *a_len, int *a_fbeg, int *a_flen)
{
   /*> int         rc          =   0;                                                 <* 
    *> char        x_scorer    = '-';                                                 <* 
    *> switch (a_type) {                                                              <* 
    *> case  YREGEX_BEST   :                                                          <* 
    *>    x_scorer = '$';                                                             <* 
    *>    break;                                                                      <* 
    *> case  YREGEX_GREEDY :                                                          <* 
    *>    switch (a_dir) {                                                            <* 
    *>    case YREGEX_MOST  : x_scorer = '*'; break;                                  <* 
    *>    case YREGEX_LEFT  : x_scorer = '?'; break;                                  <* 
    *>    case YREGEX_RIGHT : x_scorer = '+'; break;                                  <* 
    *>    default           : return -1;      break;                                  <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> case  YREGEX_LAZY   :                                                          <* 
    *>    switch (a_dir) {                                                            <* 
    *>    case YREGEX_MOST  : x_scorer = '@'; break;                                  <* 
    *>    case YREGEX_LEFT  : x_scorer = '!'; break;                                  <* 
    *>    case YREGEX_RIGHT : x_scorer = '~'; break;                                  <* 
    *>    default           : return -1;      break;                                  <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> default :                                                                      <* 
    *>    return -1;                                                                  <* 
    *>    break;                                                                      <* 
    *> }                                                                              <* 
    *> rc = yregex_find__solution (x_scorer, -1, a_beg, a_len, a_fbeg, a_flen);       <* 
    *> if (rc < 0)  return -1;                                                        <* 
    *> return 0;                                                                      <*/
}



/*====================------------------------------------====================*/
/*===----                        searching entries                     ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char yregex_find__by_cursor  (char a_move, tFIND  **r_back) { return yregex_share__by_cursor (TYPE_FIND, &s_head, &s_tail, &s_curr, r_back, a_move); }
char yregex_find__by_index   (int a_index, tFIND  **r_back) { return yregex_share__by_index  (TYPE_FIND, &s_head, &s_curr, r_back, a_index); }



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___MARKING_________________o (void) {;}

static short s_beg   = 0;
static char  s_text  [LEN_TEXT] = "";
static char  s_quan  [LEN_TEXT] = "";
static short s_gbeg  [LEN_LABEL];
static short s_gend  [LEN_LABEL];

char
yregex_find__reset      (void)
{
   int         i           =    0;
   s_beg = 0;
   for (i = 0; i < LEN_TEXT; ++i)   s_text [i] = s_quan [i] = '\0';
   for (i = 0; i < 10      ; ++i)   s_gbeg [i] = s_gend [i] = -1;
   return 0;
}

char
yregex_find__trail      (tSTATE *a_focus)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tSTATE     *x_curr      = NULL;
   int         x_rpos      =    0;
   int         x_tpos      =    0;
   uchar       x_char      =  ' ';
   uchar       x_comp      =  ' ';
   int         x_indx      =    0;
   uchar       x_mods      =  ' ';
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_focus"   , a_focus);
   --rce;  if (a_focus == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   a_focus->ready = '¼';
   s_beg  = a_focus->beg;
   x_curr = a_focus->parent;
   /*---(walk solution)------------------*/
   while (x_curr != NULL) {
      /*---(mark)------------------------*/
      x_curr->ready = '´';
      /*---(positions)-------------------*/
      x_rpos = x_curr->rpos;
      x_tpos = x_curr->tpos;
      /*---(contents)-----------------------*/
      x_char = myREGEX.text [x_tpos];
      x_comp = myREGEX.comp [x_rpos];
      x_indx = myREGEX.indx [x_rpos] - 1;
      x_mods = myREGEX.mods [x_rpos];
      /*---(capture)---------------------*/
      n      = x_tpos - s_beg;
      switch (x_comp) {
      case '(' :
         if (x_indx < 10)  s_gbeg [x_indx] = n;
         break;
      case ')' : case '|' :
         if (x_indx < 10)  s_gend [x_indx] = n;
         break;
      default  :
         s_text [n] = x_char;
         s_quan [n] = x_mods;
         break;
      }
      /*---(prev)------------------------*/
      x_curr = x_curr->parent;
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yregex_find__parse      (void)
{
   int         i           =    0;
   int         x_len       =    0;
   char        t           [LEN_RECD]  = "";
   char        q           [LEN_RECD]  = "";
   char        c           =    0;
   yregex_find__full (s_beg, s_text, s_quan);
   for (i = 0; i < 10; ++i) {
      if (s_gbeg [i] <  0)  continue;
      x_len = s_gend [i] - s_gbeg [i] + 1;
      yregex_find__sub (i, s_gbeg [i], x_len);
      ++c;
   }
   return c;
}

char
yregex_find_add         (tSTATE *a_focus)
{
   char        rc          =    0;
   if (rc >= 0)  rc = yregex_find__reset ();
   if (rc >= 0)  rc = yregex_find__trail (a_focus);
   if (rc >= 0)  rc = yregex_find__parse ();
   return rc;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*
yregex_find__unit    (char *a_question, int a_num)
{
   /*---(locals)-----------+------+----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tFIND      *x_curr      = NULL;
   int         x_find      =     0;
   char        t           [LEN_HUND]  = "";
   char        q           [LEN_HUND]  = "";
   char        n           [LEN_HUND]  = "";
   int         i           =     0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "FIND__unit, unknown request", 100);
   /*---(mapping)------------------------*/
   if      (strcmp (a_question, "count"    )      == 0) {
      x_curr = s_head; while (x_curr != NULL) { ++x_fore; x_curr = x_curr->m_next; }
      x_curr = s_tail; while (x_curr != NULL) { ++x_back; x_curr = x_curr->m_prev; }
      snprintf (unit_answer, LEN_RECD, "FIND count       : num=%4d, fore=%4d, back=%4d", s_count, x_fore, x_back);
   }
   else if (strcmp (a_question, "list"        )   == 0) {
      snprintf (unit_answer, LEN_RECD, "FIND list        : num=%4d, head=%-10p, tail=%p", s_count, s_head, s_tail);
   }
   else if (strcmp (a_question, "text"        )   == 0) {
      snprintf (unit_answer, LEN_RECD, "FIND text        : %2då%sæ", strlen (s_text), s_text);
   }
   else if (strcmp (a_question, "quan"        )   == 0) {
      snprintf (unit_answer, LEN_RECD, "FIND quan        : %2då%sæ", strlen (s_quan), s_quan);
   }
   else if (strcmp (a_question, "entry"    )      == 0) {
      yregex_find__by_index (a_num, &x_curr);
      if (x_curr != NULL) {
         sprintf (t, "%2då%-.20sæ", strlen (x_curr->text), x_curr->text);
         sprintf (q, "%2då%-.20sæ", strlen (x_curr->quan), x_curr->quan);
         for (i = 0; i < LEN_HUND; ++i) n [i] = '\0';
         for (i = 0; i < 10; ++i) {
            if (x_curr->s_off [i] == -1)  n [i] = '·';
            else                          n [i] = 'X';
         }
         snprintf (unit_answer, LEN_RECD, "FIND entry  (%2d) : %2d %2d %2d %-24.24s %-24.24s å%sæ",
               a_num, x_curr->beg, x_curr->end, x_curr->len, t, q, n);
      } else {
         snprintf (unit_answer, LEN_RECD, "FIND entry  (%2d) :  -  -  -  -åæ                      -åæ                     åæ", a_num);
      }
      return unit_answer;
   }
   else if (strcmp (a_question, "subs"     )      == 0) {
      yregex_find__by_index (a_num, &x_curr);
      if (x_curr != NULL) {
         for (i = 0; i < 10; ++i) {
            if (x_curr->s_off [i] >= 0) {
               sprintf (t, "%d·%2d/%-2d ", i, x_curr->s_off [i], x_curr->s_len [i]);
            } else {
               sprintf (t, "·· ·/·  ");
            }
            strlcat (q, t, LEN_HUND);
         }
         q [strlen (q) - 1] = '\0';
         snprintf (unit_answer, LEN_RECD, "FIND subs   (%2d) : å%sæ", a_num, q);
      } else {
         snprintf (unit_answer, LEN_RECD, "FIND subs   (%2d) : å·· ·/·  ·· ·/·  ·· ·/·  ·· ·/·  ·· ·/·  ·· ·/·  ·· ·/·  ·· ·/·  ·· ·/·  ·· ·/· æ", a_num);
      }
      return unit_answer;
   }
   /*> else if (strncmp (a_question, "match"     , 20)  == 0) {                                                                                                                    <* 
    *>    if (a_num >= s_nfind)  snprintf (unit_answer, LEN_TEXT, "FIND match  (%2d) : %3d %3d[%-.40s]", a_num, -1, -1, "");                                                       <* 
    *>    else                   snprintf (unit_answer, LEN_TEXT, "FIND match  (%2d) : %3d %3d[%-.40s]", a_num, s_finds [a_num].beg, s_finds [a_num].len, s_finds [a_num].text);   <* 
    *> }                                                                                                                                                                           <*/
   /*> else if (strncmp (a_question, "quans"     , 20)  == 0) {                                                                                               <* 
    *>    if (a_num >= s_nfind)  snprintf (unit_answer, LEN_TEXT, "FIND quans  (%2d) :     %3d[%-.40s]", a_num, -1, "");                                      <* 
    *>    else                   snprintf (unit_answer, LEN_TEXT, "FIND quans  (%2d) :     %3d[%-.40s]", a_num, s_finds [a_num].len, s_finds [a_num].quan);   <* 
    *> }                                                                                                                                                      <*/
   /*---(complete)-----------------------*/
   return unit_answer;
}




/*===============================[[ end code ]]===============================*/
