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



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
yregex_find__wipe       (tFIND *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(wipe)---------------------------*/
   a_cur->source   = NULL;
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
yregex_find__full       (tSTATE *a_source, short a_beg, char *a_text, char *a_quan)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   tFIND      *x_new       = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_beg    < 0 || a_beg >= myREGEX.tlen)  return rce;
   --rce;  if (a_text   == NULL)                       return rce;
   --rce;  if (a_quan   == NULL)                       return rce;
   l = strlen (a_text);
   --rce;  if (l != strlen (a_quan))                   return rce;
   /*---(find existing)------------------*/
   rc = yregex_find__by_loc (a_beg, l);
   --rce;  if (rc == 1)                                return rce;
   /*---(create a find)------------------*/
   rc = yregex_find__new (&x_new);
   --rce;  if (x_new == NULL) {
      return rce;
   }
   /*---(check dups)---------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_spoint  (a_source);
   DEBUG_YREGEX  yLOG_snote   (a_text);
   x_new->source = a_source;
   x_new->beg    = a_beg;
   x_new->len    = strlen (a_text);
   x_new->end    = a_beg + x_new->len - 1;
   x_new->text   = strdup (a_text);
   x_new->quan   = strdup (a_quan);
   DEBUG_YREGEX  yLOG_sint    (a_beg);
   DEBUG_YREGEX  yLOG_sint    (x_new->len);
   DEBUG_YREGEX  yLOG_sint    (x_new->end);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
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

int yregex_find_count       (void)  { return s_count; }

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

/*> char                                                                                                  <* 
 *> yREGEX_best          (cchar a_type, cchar a_dir, int  *a_beg, int *a_len, int *a_fbeg, int *a_flen)   <* 
 *> {                                                                                                     <*/
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
/*> }                                                                                 <*/



/*====================------------------------------------====================*/
/*===----                        searching entries                     ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char yregex_find__by_cursor  (char a_move, tFIND  **r_back) { return yregex_share__by_cursor (TYPE_FIND, &s_head, &s_tail, &s_curr, r_back, a_move); }
char yregex_find__by_index   (int a_index, tFIND  **r_back) { return yregex_share__by_index  (TYPE_FIND, &s_head, &s_curr, r_back, a_index); }

char
yregex_find__by_loc     (short a_beg, short a_len)
{
   /*---(locals)-----------+-----+-----+-*/
   tFIND      *x_curr      = NULL;
   /*---(prepare)------------------------*/
   x_curr = s_tail;
   while (x_curr != NULL) {
      if (x_curr->beg == a_beg) {
         if (x_curr->len == a_len) {
            return 1;
         }
      }
      x_curr = x_curr->m_prev;
   }
   return 0;
}

int
yREGEX_find             (char a_move, int  *r_beg, int *r_len, int *r_fbeg, int *r_flen)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFIND      *x_curr      = NULL;
   rc = yregex_find__by_cursor (a_move, &x_curr);
   --rce;  if (rc < 0 || x_curr == NULL)  return rce;
   if (r_beg  != NULL)  *r_beg  = x_curr->beg;
   if (r_len  != NULL)  *r_len  = x_curr->len;
   if (r_fbeg != NULL) {
      if (x_curr->s_off [0] >= 0)  *r_fbeg = x_curr->s_off [0];
      else                         *r_fbeg = x_curr->beg;
   }
   if (r_flen != NULL) {
      if (x_curr->s_len [0] >= 0)  *r_flen = x_curr->s_len [0];
      else                         *r_flen = x_curr->len;
   }
   return s_count;
}

int
yREGEX_best             (char a_best, int  *r_beg, int *r_len, int *r_fbeg, int *r_flen)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFIND      *x_curr      = NULL;
   int         b           =    0;
   int         l           =    0;
   int         c           =    0;
   int         x_beg       =    0;
   int         x_len       =    0;
   tFIND      *x_found     = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (r_beg  != NULL)  *r_beg  = -1;
   if (r_len  != NULL)  *r_len  = -1;
   if (r_fbeg != NULL)  *r_fbeg = -1;
   if (r_flen != NULL)  *r_flen = -1;
   /*---(set boundaries)-----------------*/
   switch (a_best) {
   case YREGEX_LLONG  : b = 10000; l = 0;       break;
   case YREGEX_LSHORT : b = 10000; l = 10000;   break;
   case YREGEX_RSHORT : b = 0;     l = 10000;   break;
   case YREGEX_RLONG  : b = 0;     l = 0;       break;
   case YREGEX_ALONG  : b = 0;     l = 0;       break;
   case YREGEX_ASHORT : b = 0;     l = 10000;   break;
   }
   DEBUG_YREGEX  yLOG_complex ("bounds"    , "b=%5d, l=%5d", b, l);
   /*---(walk finds)---------------------*/
   x_curr = s_head;
   while (x_curr != NULL) {
      /*---(prepare values)--------------*/
      x_beg = x_curr->beg;
      if (x_curr->s_off [0] >= 0)  x_beg += x_curr->s_off [0];
      x_len = x_curr->len;
      if (x_curr->s_len [0] >= 0)  x_len  = x_curr->s_len [0];
      DEBUG_YREGEX  yLOG_complex ("curr"      , "c=%5d, %-10p, b=%5d, l=%5d", c, x_curr, x_beg, x_len);
      /*---(check position)--------------*/
      switch (a_best) {
      case YREGEX_LLONG  : case YREGEX_LSHORT :
         if (x_beg < b)  { x_found = x_curr;  b = x_beg;  l = x_len; }
         break;
      case YREGEX_RSHORT : case YREGEX_RLONG  : 
         if (x_beg > b)  { x_found = x_curr;  b = x_beg;  l = x_len; }
         break;
      }
      /*---(check length)----------------*/
      switch (a_best) {
      case YREGEX_LSHORT : case YREGEX_RSHORT :
         if (x_len < l && x_beg == b)  { x_found = x_curr;  l = x_len; }
         break;
      case YREGEX_ASHORT :
         if (x_len < l)  { x_found = x_curr;  b = x_beg;  l = x_len; }
         break;
      case YREGEX_LLONG  : case YREGEX_RLONG  : 
         if (x_len > l && x_beg == b)  { x_found = x_curr;  l = x_len; }
         break;
      case YREGEX_ALONG  :
         if (x_len > l)  { x_found = x_curr;  b = x_beg;  l = x_len; }
         break;
      }
      /*---(next)------------------------*/
      DEBUG_YREGEX  yLOG_complex ("found"     , "%-10p, b=%5d, l=%5d", x_found, b, l);
      ++c;
      x_curr = x_curr->m_next;
      /*---(done)------------------------*/
   }
   /*---(never found)--------------------*/
   --rce;  if (x_found == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(saveback)-----------------------*/
   if (r_beg  != NULL)  *r_beg  = x_found->beg;
   if (r_len  != NULL)  *r_len  = x_found->len;
   if (r_fbeg != NULL) {
      if (x_found->s_off [0] >= 0)  *r_fbeg = x_found->beg + x_found->s_off [0];
      else                          *r_fbeg = x_found->beg;
   }
   if (r_flen != NULL) {
      if (x_found->s_len [0] >= 0)  *r_flen = x_found->s_len [0];
      else                          *r_flen = x_found->len;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return s_count;
}



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
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   s_beg = 0;
   for (i = 0; i < LEN_TEXT; ++i)   s_text [i] = s_quan [i] = '\0';
   for (i = 0; i < 10      ; ++i)   s_gbeg [i] = s_gend [i] = -1;
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yregex_find__trail      (tSTATE *a_focus, char a_mark)
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
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (a_mark);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_spoint  (a_focus);
   --rce;  if (a_focus == NULL) {
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   if (a_mark == 'y') {
      a_focus->ready = '¼';
      DEBUG_YREGEX  yLOG_schar   (a_focus->ready);
   }
   s_beg  = a_focus->beg;
   x_curr = a_focus->parent;
   /*---(walk solution)------------------*/
   while (x_curr != NULL) {
      /*---(mark)------------------------*/
      if (a_mark == 'y') {
         x_curr->ready = '´';
         DEBUG_YREGEX  yLOG_schar   (x_curr->ready);
      }
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
         if (x_indx < 10) {
            if (s_gend [x_indx] >= 0)  s_gbeg [x_indx] = n;
         }
         break;
      case ')' : case '|' :
         if (x_indx < 10)  s_gend [x_indx] = n - 1;
         break;
      case '<' : case '>' :
         break;
      default  :
         s_text [n] = x_char;
         if (x_char != '\0')  s_quan [n] = x_mods;
         break;
      }
      /*---(prev)------------------------*/
      x_curr = x_curr->parent;
      /*---(done)------------------------*/
   }
   DEBUG_YREGEX  yLOG_snote   (s_text);
   DEBUG_YREGEX  yLOG_snote   (s_quan);
   DEBUG_YREGEX  yLOG_sint    (strlen (s_text));
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yregex_find__save       (tSTATE *a_focus)
{
   char        rc          =    0;
   int         i           =    0;
   int         x_len       =    0;
   char        t           [LEN_RECD]  = "";
   char        q           [LEN_RECD]  = "";
   char        c           =    0;
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   rc = yregex_find__full (a_focus, s_beg, s_text, s_quan);
   DEBUG_YREGEX  yLOG_value   ("full"      , rc);
   if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   for (i = 0; i < 10; ++i) {
      if (s_gbeg [i] <  0)  continue;
      x_len = s_gend [i] - s_gbeg [i] + 1;
      yregex_find__sub (i, s_gbeg [i], x_len);
      DEBUG_YREGEX  yLOG_complex ("sub"       , "%d, %d", i, rc);
      ++c;
   }
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return c;
}

char
yregex_find_add         (tSTATE *a_focus)
{
   char        rc          =    0;
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   if (rc >= 0)  rc = yregex_find__reset ();
   DEBUG_YREGEX  yLOG_value   ("reset"     , rc);
   if (rc >= 0)  rc = yregex_find__trail (a_focus, 'y');
   DEBUG_YREGEX  yLOG_value   ("trail"     , rc);
   if (rc >= 0)  rc = yregex_find__save  (a_focus);
   DEBUG_YREGEX  yLOG_value   ("save"      , rc);
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yregex_find_group       (tSTATE *a_focus, char a_group, char *r_text)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_focus"   , a_focus);
   --rce;  if (a_focus == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("a_group"   , a_group);
   --rce;  if (a_group < 0 || a_group > 9) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_point   ("r_text"    , r_text);
   --rce;  if (r_text == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (r_text, "", LEN_TEXT);
   /*---(setup)--------------------------*/
   rc = yregex_find__reset ();
   DEBUG_YREGEX  yLOG_value   ("reset"     , rc);
   rc = yregex_find__trail (a_focus, '-');
   DEBUG_YREGEX  yLOG_value   ("trail"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_complex ("s_text"    , "%2då%sæ", strlen (s_text), s_text);
   for (i = 0; i < 10; ++i) {
      DEBUG_YREGEX  yLOG_complex ("sub"       , "%d, %d, %d", i, s_gbeg [i], s_gend [i]);
   }
   DEBUG_YREGEX  yLOG_value   ("s_gbeg"    , s_gbeg [a_group]);
   --rce;  if (s_gbeg [a_group] <  0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("s_gend"    , s_gend [a_group]);
   /*---(parse out)----------------------*/
   x_len = s_gend [a_group] - s_gbeg [a_group] + 1;
   sprintf (r_text, "%*.*s", x_len, x_len, s_text + s_gbeg [a_group]);
   DEBUG_YREGEX  yLOG_complex ("r_text"    , "%2då%sæ", x_len, r_text);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    execution support                         ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTE_________________o (void) {;}




/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*
yregex_find__memory     (tFIND *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   int         i           =    0;
   /*---(defense)------------------------*/
   if (a_cur == NULL) {
      strlcpy (g_print, "n/a", LEN_RECD);
      return g_print;
   }
   /*---(defense)------------------------*/
   strlcpy (g_print, "å______.__________.__æ", LEN_RECD);
   ++n;  if (a_cur->source      != NULL)        g_print [n] = 'X';
   ++n;  if (a_cur->beg         >= 0)           g_print [n] = 'X';
   ++n;  if (a_cur->end         >= 0)           g_print [n] = 'X';
   ++n;  if (a_cur->len         >= 0)           g_print [n] = 'X';
   ++n;  if (a_cur->text        != NULL)        g_print [n] = 'X';
   ++n;  if (a_cur->quan        != NULL)        g_print [n] = 'X';
   ++n;
   for (i = 0; i < MAX_SUB; ++i) {
      ++n;  if (a_cur->s_off [i]     >= 0)        g_print [n] = 'X';
   }
   ++n;
   ++n;  if (a_cur->m_prev      != NULL)        g_print [n] = 'X';
   ++n;  if (a_cur->m_next      != NULL)        g_print [n] = 'X';
   return g_print;
}

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
      yregex_share__unit (TYPE_FIND, s_head, s_tail, s_count, "count", 0);
   }
   else if (strcmp (a_question, "list"        )   == 0) {
      yregex_share__unit (TYPE_FIND, s_head, s_tail, s_count, "list" , 0);
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
