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
#define     MAX_SUB       11

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
typedef     struct      cFIND       tFIND;
struct      cFIND {
   /*---(tie to exec)------------*/
   short       ref;                         /* ref from exec                  */
   /*---(basics)-----------------*/
   short       beg;                         /* starting point                 */
   short       end;                         /* ending point                   */
   short       len;                         /* length                         */
   char        text        [LEN_TEXT];      /* found text                     */
   char        quan        [LEN_TEXT];      /* quantifiers                    */
   /*---(stats)------------------*/
   short       count;                       /* count of times requested       */
   short       lazy;                        /* count of lazy markers          */
   short       greedy;                      /* count of greedy markers        */
   short       balance;                     /* greedy/lazy balance            */
   short       score;                       /* calculated score               */
   /*---(subs)-------------------*/
   struct cSUB {
      short       beg;
      short       len;
      char        text        [LEN_TEXT];
      char        quan        [LEN_TEXT];
   }           sub         [MAX_SUB];
   /*---(done)-------------------*/
};
/*---(static.vars)------+-----------+-*//*-+----------------------------------*/
static      tFIND       s_finds     [MAX_FIND];    /* all finds               */
static      int         s_nfind     = 0;           /* total number of states  */
static      int         s_curr      = 0;           /* point to current state  */



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
yregex_find_init        (void)
{
   int         i           =     0;
   int         j           =     0;
   s_nfind = 0;
   /*> for (i = 0; i < MAX_FIND; ++i) {                                                         <* 
    *>    s_finds [i].ref     = -1;                                                             <* 
    *>    s_finds [i].beg     = -1;                                                             <* 
    *>    s_finds [i].end     = -1;                                                             <* 
    *>    s_finds [i].len     = -1;                                                             <* 
    *>    /+> strlcpy (s_finds [i].text, "", LEN_TEXT);                                   <*    <* 
    *>     *> strlcpy (s_finds [i].quan, "", LEN_TEXT);                                   <+/   <* 
    *>    s_finds [i].text [0] = '\0';                                                          <* 
    *>    s_finds [i].quan [0] = '\0';                                                          <* 
    *>    s_finds [i].count   = 0;                                                              <* 
    *>    s_finds [i].lazy    = 0;                                                              <* 
    *>    s_finds [i].greedy  = 0;                                                              <* 
    *>    s_finds [i].balance = 0;                                                              <* 
    *>    s_finds [i].score   = 0;                                                              <* 
    *>    for (j = 0; j < MAX_SUB; ++j) {                                                       <* 
    *>       /+> strlcpy (s_finds [i].sub [j].text, "", LEN_TEXT);                        <*    <* 
    *>        *> strlcpy (s_finds [i].sub [j].quan, "", LEN_TEXT);                        <+/   <* 
    *>       s_finds [i].sub [j].text [0] = '\0';                                               <* 
    *>       s_finds [i].sub [j].quan [0] = '\0';                                               <* 
    *>    }                                                                                     <* 
    *> }                                                                                        <*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        data structure                        ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

int
yregex_find__dup        (cint a_beg, cint a_len)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(check)--------------------------*/
   for (i = 0; i < s_nfind; ++i) {
      if (a_beg != s_finds [i].beg)   continue;
      if (a_len != s_finds [i].len)   continue;
      return i;
   }
   /*---(complete)-----------------------*/
   return -1;
}

char
yregex_find_add         (cint a_ref, cint a_beg, cchar *a_text, cchar *a_quan)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   int         i           =    0;
   int         x_lazy      =    0;
   int         x_greedy    =    0;
   int         x_ref       =   -1;
   /*---(defense)------------------------*/
   --rce;  if (a_text == NULL)  return rce;
   --rce;  if (a_quan == NULL)  return rce;
   /*---(check dups)---------------------*/
   x_len = strllen (a_text, LEN_TEXT);
   x_ref = yregex_find__dup (a_beg, x_len);
   if (x_ref >= 0) {
      ++(s_finds [x_ref].count);
      return 0;
   }
   /*---(save)---------------------------*/
   s_finds [s_nfind].ref    = a_ref;
   s_finds [s_nfind].beg    = a_beg;
   strlcpy (s_finds [s_nfind].text, a_text, LEN_TEXT);
   strlcpy (s_finds [s_nfind].quan, a_quan, LEN_TEXT);
   s_finds [s_nfind].len    = x_len;
   s_finds [s_nfind].end    = a_beg + x_len + 1;
   s_finds [s_nfind].count  = 1;
   /*---(classify)-----------------------*/
   if (x_len > 0) {
      for (i = 0; i < x_len; ++i) {
         if (strchr (G_GREEDY, a_quan [i]) != NULL)  ++x_greedy;
         if (strchr (G_LAZY  , a_quan [i]) != NULL)  ++x_lazy;
      }
   }
   s_finds [s_nfind].lazy     = x_lazy;
   s_finds [s_nfind].greedy   = x_greedy;
   s_finds [s_nfind].balance  = x_greedy - x_lazy;
   s_finds [s_nfind].score    = 0;
   /*---(link)---------------------------*/
   s_curr = s_nfind;
   /*---(update)-------------------------*/
   ++s_nfind;
   /*---(complete)-----------------------*/
   return 0;
}

char
yregex_find_addsub      (cint a_ref, cint a_num, short a_beg, cchar *a_text, cchar *a_quan)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         x_len       =   -1;
   static int  x_ref       =    0;
   static int  x_curr      =    0;
   /*---(find)---------------------------*/
   if (a_num < 0 || a_num >= MAX_SUB)  return -2;
   if (a_ref != x_ref) {
      for (i = 0; i < s_nfind; ++i) {
         if (s_finds [i].ref != a_ref)  continue;
         x_ref  = a_ref;
         x_curr = i;
         break;
      }
   }
   if (a_ref != x_ref)  return -1;
   /*---(update)-------------------------*/
   s_finds [x_curr].sub [a_num].beg  = a_beg;
   if (a_text != NULL)  strlcpy (s_finds [x_curr].sub [a_num].text, a_text, LEN_TEXT);
   if (a_quan != NULL)  strlcpy (s_finds [x_curr].sub [a_num].quan, a_quan, LEN_TEXT);
   if (a_text != NULL)  x_len = strllen (a_text, LEN_TEXT);
   s_finds [x_curr].sub [a_num].len  = x_len;
   /*---(complete)-----------------------*/
   return 0;
}

char
yregex_find_text        (cint a_ref, char *a_text)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =     0;
   static int  x_ref       =    -1;
   static int  x_curr      =    -1;
   /*---(defense)------------------------*/
   if (a_text == NULL) return 0;
   /*---(shortcut)-----------------------*/
   if (x_ref == a_ref) {
      strlcpy (a_text, s_finds [x_curr].text, LEN_TEXT);
      return 0;
   }
   /*---(prepare)------------------------*/
   strlcpy (a_text, "", LEN_TEXT);
   /*---(find)---------------------------*/
   for (i = 0; i < s_nfind; ++i) {
      if (s_finds [i].ref != a_ref)  continue;
      strlcpy (a_text, s_finds [i].text, LEN_TEXT);
      x_ref  = a_ref;
      x_curr = i;
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

int
yregex_find_count       (void)
{
   return s_nfind;
}

char
yregex_find__listall    (char a_detail)
{
   int         i           =     0;
   int         j           =     0;
   printf ("num  ---text/quan-----------------------------------\n\n");
   for (i = 0; i < s_nfind; ++i) {
      if (s_finds [i].beg < 0) break;
      printf ("%-4d %-4d  text %-3d[%s]\n", i, s_finds [i].ref, strlen (s_finds [i].text), s_finds [i].text);
      printf ("     b%-4d quan %-3d[%s]\n", s_finds [i].beg, strlen (s_finds [i].quan), s_finds [i].quan);
      printf ("     e%-4d l %-3d, g %-3d, b %-3d\n", s_finds [i].end, s_finds [i].lazy, s_finds [i].greedy, s_finds [i].balance);
      if (a_detail == 'y') {
         for (j = 0; j < 11; ++j) {
            if (s_finds [i].sub [j].len >= 0) {
               printf ("     sub%2d b%-4d text %-3d[%s]\n", j, s_finds [i].sub [j].beg, s_finds [i].sub [j].len, s_finds [i].sub [j].text);
               printf ("                 quan %-3d[%s]\n",    s_finds [i].sub [j].len, s_finds [i].sub [j].quan);
            }
         }
      }
      printf ("\n");
   }
   return 0;
}

char yREGEX_finds (void) { return yregex_find__listall ('y'); }

int
yregex_find__solution   (char a_scorer, int a_pos, int  *a_beg, int *a_len, int *a_fbeg, int *a_flen)
{
   /*---(locals)-----------+------+----+-*/
   char        rce         =   -10;
   int         i           =     0;
   int         x_pos       =    -1;
   int         x_best      =    -1;
   int         x_score     = -100000;
   int         x_top       = +100000;
   int         x_left      = +100000;
   int         x_right     = -100000;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_beg  != NULL)  *a_beg  = -1;
   if (a_len  != NULL)  *a_len  = -1;
   if (a_fbeg != NULL)  *a_fbeg = -1;
   if (a_flen != NULL)  *a_flen =  0;
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_value   ("a_scorer"  , a_scorer);
   --rce;  if (a_scorer == 0 || strchr ("$*?+@!~", a_scorer) == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_char    ("a_scorer"  , a_scorer);
   /*---(prepare)------------------------*/
   DEBUG_YREGEX  yLOG_value   ("a_pos"     , a_pos);
   --rce;  if (a_pos < 0) {
      DEBUG_YREGEX  yLOG_note    ("reset a negative position");
      switch (a_scorer) {
      case '$' :             a_pos = 0;         break;
      case '?' : case '!' :  a_pos = 0;         break;
      case '+' : case '~' :  a_pos = +100000;   break;
      case '*' : case '@' :  a_pos = 0;         break;
      }
      DEBUG_YREGEX  yLOG_value   ("a_pos"     , a_pos);
   }
   /*---(find outer bounds)--------------*/
   DEBUG_YREGEX  yLOG_note    ("find outermost acceptable boundaries");
   for (i = 0; i < s_nfind; ++i) {
      /*---(first left)------------------*/
      x_pos = s_finds [i].beg;
      if (x_pos >= a_pos && x_pos < x_left )  x_left  = x_pos;
      /*---(then right)------------------*/
      x_pos = s_finds [i].end;
      if (x_pos <= a_pos && x_pos > x_right)  x_right = x_pos;
      /*---(done)------------------------*/
   }
   DEBUG_YREGEX  yLOG_value   ("x_left"    , x_left);
   DEBUG_YREGEX  yLOG_value   ("x_right"   , x_right);
   /*---(set boundaries)-----------------*/
   DEBUG_YREGEX  yLOG_note    ("reset acceptable boundaries based on scorer");
   switch (a_scorer) {
   case '$' : case '*' : case '@' : x_left  = x_right = -1; break;
   case '?' : case '!' :                      x_right = -1; break;
   case '+' : case '~' :            x_left  =           -1; break;
   }
   DEBUG_YREGEX  yLOG_value   ("x_left"    , x_left);
   DEBUG_YREGEX  yLOG_value   ("x_right"   , x_right);
   /*---(set initial score)--------------*/
   DEBUG_YREGEX  yLOG_note    ("set top score based on scorer");
   switch (a_scorer) {
   case '$' : case '*' : case '+' : case '?' :  x_top = -100000;  break;
   case '@' : case '~' : case '!' :             x_top = +100000;  break;
   }
   DEBUG_YREGEX  yLOG_value   ("x_top"     , x_top);
   /*---(locate)-------------------------*/
   for (i = 0; i < s_nfind; ++i) {
      DEBUG_YREGEX  yLOG_complex ("match"     , "%3d, %3d, %3d", i, s_finds [i].beg, s_finds [i].end);
      /*---(filter)----------------------*/
      if (x_left  >= 0 && s_finds [i].beg != x_left ) {
         DEBUG_YREGEX  yLOG_note    ("does not match left side, skip");
         continue;
      }
      if (x_right >= 0 && s_finds [i].end != x_right) {
         DEBUG_YREGEX  yLOG_note    ("does not match right side, skip");
         continue;
      }
      /*---(gather)----------------------*/
      if (a_scorer == '$')  x_score  = s_finds [i].balance;
      else                  x_score  = s_finds [i].greedy + s_finds [i].lazy;
      DEBUG_YREGEX  yLOG_value   ("x_score"   , x_score);
      DEBUG_YREGEX  yLOG_value   ("x_top"     , x_top);
      /*---(filter, too)-----------------*/
      switch (a_scorer) {
      case '$' : case '*' : case '+' : case '?' :
         if (x_score <= x_top) {
            DEBUG_YREGEX  yLOG_note    ("greedy and score is less than top, skip");
            continue;
         }
         break;
      case '@' : case '~' : case '!' :
         if (x_score >= x_top) {
            DEBUG_YREGEX  yLOG_note    ("lazy and score is more than top, skip");
            continue;
         }
         break;
      }
      /*---(update)----------------------*/
      DEBUG_YREGEX  yLOG_note    ("new best match");
      x_top   = x_score;
      x_best  = i;
   }
   /*---(return)-------------------------*/
   DEBUG_YREGEX  yLOG_note    ("set return variables");
   if (a_beg  != NULL)  *a_beg  = s_finds [x_best].beg;
   if (a_len  != NULL)  *a_len  = s_finds [x_best].len;
   if (a_fbeg != NULL)  *a_fbeg = s_finds [x_best].sub [10].beg;
   if (a_flen != NULL)  *a_flen = s_finds [x_best].sub [10].len;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return x_best;
}

char
yREGEX_best          (cchar a_type, cchar a_dir, int  *a_beg, int *a_len, int *a_fbeg, int *a_flen)
{
   int         rc          =   0;
   char        x_scorer    = '-';
   switch (a_type) {
   case  YREGEX_BEST   :
      x_scorer = '$';
      break;
   case  YREGEX_GREEDY :
      switch (a_dir) {
      case YREGEX_MOST  : x_scorer = '*'; break;
      case YREGEX_LEFT  : x_scorer = '?'; break;
      case YREGEX_RIGHT : x_scorer = '+'; break;
      default           : return -1;      break;
      }
      break;
   case  YREGEX_LAZY   :
      switch (a_dir) {
      case YREGEX_MOST  : x_scorer = '@'; break;
      case YREGEX_LEFT  : x_scorer = '!'; break;
      case YREGEX_RIGHT : x_scorer = '~'; break;
      default           : return -1;      break;
      }
      break;
   default :
      return -1;
      break;
   }
   rc = yregex_find__solution (x_scorer, -1, a_beg, a_len, a_fbeg, a_flen);
   if (rc < 0)  return -1;
   return 0;
}

static char   s_method   = YREGEX_GREEDY;
static char   s_scorer   = '*';
static int    s_index    =  -1;
static int    s_pos      =   0;

int
yregex_find__target     (char a_dir, int a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         x_orig      =    0;
   int         x_targ      =    0;
   int         x_pos       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (a_dir);
   DEBUG_YREGEX  yLOG_sint    (a_pos);
   /*---(find next right)----------------*/
   if (strchr ("[>", a_dir) != NULL) {
      DEBUG_YREGEX  yLOG_snote   ("right");
      x_orig = x_targ = +100000;
      if (a_pos == -1)  a_pos = -x_orig;
      for (i = 0; i < s_nfind; ++i) {
         x_pos = s_finds [i].beg;
         if (x_pos < a_pos)            continue;
         if (x_pos > x_targ)           continue;
         DEBUG_YREGEX  yLOG_sint    (i);
         DEBUG_YREGEX  yLOG_sint    (x_targ);
         x_targ = x_pos;
      }
   }
   /*---(find next left)-----------------*/
   else if (strchr ("<]", a_dir) != NULL) {
      DEBUG_YREGEX  yLOG_snote   ("left");
      x_orig = x_targ = -100000;
      if (a_pos == -1)  a_pos = -x_orig;
      for (i = 0; i < s_nfind; ++i) {
         x_pos = s_finds [i].beg;
         if (x_pos > a_pos)            continue;
         if (x_pos < x_targ)           continue;
         x_targ = x_pos;
         DEBUG_YREGEX  yLOG_sint    (i);
         DEBUG_YREGEX  yLOG_sint    (x_targ);
      }
   }
   /*---(output)-------------------------*/
   else {
      DEBUG_YREGEX  yLOG_snote   ("direction unknown");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
   }
   /*---(output)-------------------------*/
   --rce;  if (x_targ == x_orig) {
      DEBUG_YREGEX  yLOG_snote   ("FAILED");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return x_targ;
}

int
yregex_find__score      (char a_method, int a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         x_pos       =    0;
   int         x_score     =    0;
   int         x_top       =    0;
   int         x_best      =   -1;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (a_method);
   DEBUG_YREGEX  yLOG_sint    (a_pos);
   /*---(prepare)------------------------*/
   switch (a_method) {
   case YREGEX_LAZY :  x_top = +100000;  break;
   default          :  x_top = -100000;  break;
   }
   /*---(find next left)-----------------*/
   for (i = 0; i < s_nfind; ++i) {
      /*---(filter position)-------------*/
      x_pos = s_finds [i].beg;
      if (x_pos != a_pos)           continue;
      /*---(score)-----------------------*/
      if (s_method == YREGEX_BEST)    x_score  = s_finds [i].balance;
      else                            x_score  = s_finds [i].greedy + s_finds [i].lazy;
      /*---(filter score)----------------*/
      switch (s_method) {
      case YREGEX_GREEDY : case YREGEX_BEST :
         if (x_score <= x_top)  continue;
         break;
      case YREGEX_LAZY   :
         if (x_score >= x_top)  continue;
         break;
      }
      /*---(update)----------------------*/
      x_top  = x_score;
      x_best = i;
      DEBUG_YREGEX  yLOG_sint    (x_top);
      /*---(done)------------------------*/
   }
   /*---(save values)--------------------*/
   s_index = x_best;
   s_pos   = x_pos;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return x_best;
}

char
yREGEX_method           (char a_type)
{
   if      (s_method == YREGEX_LAZY)  s_method = a_type;
   else if (s_method == YREGEX_BEST)  s_method = a_type;
   else                               s_method = YREGEX_GREEDY;
   return 0;
}

char
yREGEX_cursor           (char a_dir, int *a_beg, int *a_len, int *a_fbeg, int *a_flen)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_pos       =    0;
   int         x_best      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_char    ("s_method"  , s_method);
   DEBUG_YREGEX  yLOG_value   ("s_index"   , s_index);
   /*---(default)------------------------*/
   if (a_beg  != NULL)  *a_beg  = -1;
   if (a_len  != NULL)  *a_len  = -1;
   if (a_fbeg != NULL)  *a_fbeg = -1;
   if (a_flen != NULL)  *a_flen =  0;
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_value   ("a_dir"     , a_dir);
   --rce;  if (a_dir == 0 || strchr ("[>.<]", a_dir) == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_char    ("a_dir"     , a_dir);
   --rce;  if (s_index < 0 && strchr ("><.", a_dir) != NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(current)------------------------*/
   --rce;  if (a_dir == '.') {
      DEBUG_YREGEX  yLOG_note    ("seeking current value (.)");
      if (a_beg  != NULL)  *a_beg  = s_finds [s_index].beg;
      if (a_len  != NULL)  *a_len  = s_finds [s_index].len;
      if (a_fbeg != NULL)  *a_fbeg = s_finds [s_index].sub [10].beg;
      if (a_flen != NULL)  *a_flen = s_finds [s_index].sub [10].len;
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(update position)----------------*/
   x_pos = s_pos;
   switch (a_dir) {
   case '[' : x_pos = -1;  break;
   case '<' :  --x_pos;    break;
   case '>' :  ++x_pos;    break;
   case ']' : x_pos = -1;  break;
   }
   /*---(find solution)------------------*/
   DEBUG_YREGEX  yLOG_value   ("x_pos"     , x_pos);
   x_pos = yregex_find__target (a_dir, x_pos);
   DEBUG_YREGEX  yLOG_value   ("x_targ"    , x_pos);
   --rce;  if (x_pos < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_best = yregex_find__score (s_method, x_pos);
   DEBUG_YREGEX  yLOG_value   ("x_best"    , x_best);
   /*---(update)-------------------------*/
   s_index = x_best;
   s_pos   = x_pos;
   if (a_beg  != NULL)  *a_beg  = s_finds [s_index].beg;
   if (a_len  != NULL)  *a_len  = s_finds [s_index].len;
   if (a_fbeg != NULL)  *a_fbeg = s_finds [s_index].sub [10].beg;
   if (a_flen != NULL)  *a_flen = s_finds [s_index].sub [10].len;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*
yregex_find__unit    (char *a_question, int a_num)
{
   /*---(locals)-----------+------+----+-*/
   int         x_find      =     0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "FIND__unit, unknown request", 100);
   /*---(mapping)------------------------*/
   if (strncmp (a_question, "match"     , 20)  == 0) {
      if (a_num >= s_nfind)  snprintf (unit_answer, LEN_TEXT, "FIND match  (%2d) : %3d %3d[%-.40s]", a_num, -1, -1, "");
      else                   snprintf (unit_answer, LEN_TEXT, "FIND match  (%2d) : %3d %3d[%-.40s]", a_num, s_finds [a_num].beg, s_finds [a_num].len, s_finds [a_num].text);
   }
   else if (strncmp (a_question, "quans"     , 20)  == 0) {
      if (a_num >= s_nfind)  snprintf (unit_answer, LEN_TEXT, "FIND quans  (%2d) :     %3d[%-.40s]", a_num, -1, "");
      else                   snprintf (unit_answer, LEN_TEXT, "FIND quans  (%2d) :     %3d[%-.40s]", a_num, s_finds [a_num].len, s_finds [a_num].quan);
   }
   else if (strncmp (a_question, "score"     , 20)  == 0) {
      if (a_num >= s_nfind)  snprintf (unit_answer, LEN_TEXT, "FIND score  (%2d) : %3dg, %3dl, %3db, %3ds", a_num, 0, 0, 0, 0);
      else                   snprintf (unit_answer, LEN_TEXT, "FIND score  (%2d) : %3dg, %3dl, %3db, %3ds", a_num, s_finds [a_num].greedy, s_finds [a_num].lazy, s_finds [a_num].balance, s_finds [a_num].score);
   }
   else if (strncmp (a_question, "scorer"    , 20)  == 0) {
      x_find = yregex_find__solution (a_num, -1, NULL, NULL, NULL, NULL);
      if (x_find < 0) {
         snprintf (unit_answer, LEN_TEXT, "FIND scorer (%2d) : %c unknown solution", x_find, a_num);
      } else {
         snprintf (unit_answer, LEN_TEXT, "FIND scorer (%2d) : %c %3d %3d[%-.38s]", x_find, a_num, s_finds [x_find].beg, s_finds [x_find].len, s_finds [x_find].text);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




/*===============================[[ end code ]]===============================*/
