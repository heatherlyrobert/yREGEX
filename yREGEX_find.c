/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



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
   int         count;                       /* count of times requested       */
   int         lazy;                        /* count of lazy markers          */
   int         greedy;                      /* count of greedy markers        */
   int         balance;                     /* final score                    */
   /*---(subs)-------------------*/
   struct cSUB {
      int         len;
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
FIND_init            (void)
{
   int         i           =     0;
   int         j           =     0;
   s_nfind = 0;
   for (i = 0; i < MAX_FIND; ++i) {
      s_finds [i].ref     = -1;
      s_finds [i].beg     = -1;
      s_finds [i].end     = -1;
      s_finds [i].len     = -1;
      strlcpy (s_finds [i].text, "", LEN_TEXT);
      strlcpy (s_finds [i].quan, "", LEN_TEXT);
      s_finds [i].count   = 0;
      s_finds [i].lazy    = 0;
      s_finds [i].greedy  = 0;
      s_finds [i].balance = 0;
      for (j = 0; j < MAX_SUB; ++j) {
         strlcpy (s_finds [i].sub [j].text, "", LEN_TEXT);
         strlcpy (s_finds [i].sub [j].quan, "", LEN_TEXT);
      }
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        data structure                        ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

int
FIND__dup            (cint a_beg, cint a_len)
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
FIND_add             (cint a_ref, cint a_beg, cchar *a_text, cchar *a_quan)
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
   x_ref = FIND__dup (a_beg, x_len);
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
   s_finds [s_nfind].balance  = x_greedy + x_lazy;
   /*---(link)---------------------------*/
   s_curr = s_nfind;
   /*---(update)-------------------------*/
   ++s_nfind;
   /*---(complete)-----------------------*/
   return 0;
}

char
FIND_sub             (cint a_ref, cint a_num, cchar *a_text, cchar *a_quan)
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
   if (a_text != NULL)  strlcpy (s_finds [x_curr].sub [a_num].text, a_text, LEN_TEXT);
   if (a_quan != NULL)  strlcpy (s_finds [x_curr].sub [a_num].quan, a_quan, LEN_TEXT);
   if (a_text != NULL)  x_len = strllen (a_text, LEN_TEXT);
   s_finds [x_curr].sub [a_num].len  = x_len;
   /*---(complete)-----------------------*/
   return 0;
}

char
FIND_text            (cint a_ref, char *a_text)
{
   int         i           =     0;
   if (a_text == NULL) return 0;
   strlcpy (a_text, "", LEN_TEXT);
   for (i = 0; i < s_nfind; ++i) {
      if (s_finds [i].ref != a_ref)  continue;
      strlcpy (a_text, s_finds [i].text, LEN_TEXT);
      break;
   }
   return 0;
}

int
FIND_count           (void)
{
   return s_nfind;
}

char
FIND_list            (void)
{
   int         i           =     0;
   int         j           =     0;
   printf ("num  ---text/quan-----------------------------------\n\n");
   for (i = 0; i < s_nfind; ++i) {
      if (s_finds [i].beg < 0) break;
      printf ("%-4d %-4d  text %-3d[%s]\n", i, s_finds [i].ref, strlen (s_finds [i].text), s_finds [i].text);
      printf ("     b%-4d quan %-3d[%s]\n", s_finds [i].beg, strlen (s_finds [i].quan), s_finds [i].quan);
      printf ("     e%-4d l %-3d, g %-3d, b %-3d\n", s_finds [i].end, s_finds [i].lazy, s_finds [i].greedy, s_finds [i].balance);
      for (j = 0; j < 11; ++j) {
         if (s_finds [i].sub [j].len >= 0) {
            printf ("     sub%2d text %-3d[%s]\n", j, s_finds [i].sub [j].len, s_finds [i].sub [j].text);
            printf ("           quan %-3d[%s]\n",    s_finds [i].sub [j].len, s_finds [i].sub [j].quan);
         }
      }
      printf ("\n");
   }
   return 0;
}

int
FIND_solution        (char a_scorer, int a_pos, int  *a_beg, int *a_len)
{
   /*---(locals)-----------+------+----+-*/
   int         i           =     0;
   int         x_pos       =    -1;
   int         x_best      =    -1;
   int         x_score     =    -1;
   int         x_top       = 10000;
   int         x_left      = 10000;
   int         x_right     =    -1;
   /*---(prepare)------------------------*/
   /*> printf ("FIND_solution\n");                                                    <*/
   /*> printf ("   a_pos   = %3d\n", a_pos);                                          <*/
   if (a_pos < 0) {
      switch (a_scorer) {
      case '?' : case '!' :  a_pos = 0;         break;
      case '+' : case '~' :  a_pos = gre.olen;  break;
      case '*' : case '@' :  a_pos = 0;         break;
      default  :             return -1;         break;
      }
   }
   /*> printf ("   a_pos   = %3d\n", a_pos);                                          <*/
   /*---(find marks)---------------------*/
   for (i = 0; i < s_nfind; ++i) {
      /*---(first left)------------------*/
      x_pos = s_finds [i].beg;
      if (x_pos >= a_pos && x_pos < x_left )  x_left  = x_pos;
      /*---(then right)------------------*/
      x_pos = s_finds [i].end;
      if (x_pos <= a_pos && x_pos > x_right)  x_right = x_pos;
      /*---(done)------------------------*/
   }
   /*> printf ("   x_left  = %3d, x_right = %3d\n", x_left, x_right);                 <*/
   /*---(set mark)-----------------------*/
   switch (a_scorer) {
   case '*' : case '@' : x_left  = x_right = -1; break;
   case '?' : case '!' :           x_right = -1; break;
   case '+' : case '~' : x_left  =           -1; break;
   }
   /*> printf ("   x_left  = %3d, x_right = %3d\n", x_left, x_right);                 <*/
   /*---(set initial score)--------------*/
   switch (a_scorer) {
   case '*' : case '+' : case '?' :  x_top = 0;       break;
   case '@' : case '~' : case '!' :  x_top = 1000000; break;
   }
   /*> printf ("   x_top   = %3d\n", x_top);                                          <*/
   /*---(locate)-------------------------*/
   for (i = 0; i < s_nfind; ++i) {
      /*---(gather)----------------------*/
      x_score  = s_finds [i].greedy + s_finds [i].lazy;
      /*> printf ("   loop    = %3d, score   = %3d\n", i, x_score);                   <*/
      /*---(filter)----------------------*/
      if (x_left  >= 0 && s_finds [i].beg != x_left )   continue;
      if (x_right >= 0 && s_finds [i].end != x_right)   continue;
      /*---(filter, too)-----------------*/
      switch (a_scorer) {
      case '*' : case '+' : case '?' : if (x_score <= x_top) continue; break;
      case '@' : case '~' : case '!' : if (x_score >= x_top) continue; break;
      }
      /*---(update)----------------------*/
      x_top   = x_score;
      x_best  = i;
      /*> printf ("   x_top   = %3d, x_best  = %3d\n", x_top, x_best);                <*/
   }
   /*---(return)-------------------------*/
   /*> printf ("   DONE, x_top   = %3d, x_best  = %3d\n", x_top, x_best);             <*/
   if (a_beg != NULL)  *a_beg = s_finds [x_best].beg;
   if (a_len != NULL)  *a_len = s_finds [x_best].len;
   /*---(complete)-----------------------*/
   return x_best;
}

int
yREGEX_find          (cchar a_type, cchar a_dir, int  *a_beg, int *a_len)
{
   char        x_scorer    = '-';
   switch (a_type) {
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
   return FIND_solution (x_scorer, -1, a_beg, a_len);
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*
FIND__unit           (char *a_question, int a_num)
{
   /*---(locals)-----------+------+----+-*/
   int         x_find      =     0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "FIND__unit, unknown request", 100);
   /*---(mapping)------------------------*/
   if (strncmp (a_question, "match"     , 20)  == 0) {
      /*> snprintf (unit_answer, LEN_RECD, "yREGEX_exec stat : beg=%3d, end=%3d, len=%3d", s_begin, s_end, s_len);   <*/
      if (a_num >= s_nfind) {
         snprintf (unit_answer, LEN_TEXT, "FIND match  (%2d) : unknown solution", a_num);
      } else {
         snprintf (unit_answer, LEN_TEXT, "FIND match  (%2d) : %3d %3d[%-.40s]", a_num, s_finds [a_num].beg, s_finds [a_num].len, s_finds [a_num].text);
      }
   }
   else if (strncmp (a_question, "scorer"    , 20)  == 0) {
      x_find = FIND_solution (a_num, -1, NULL, NULL);
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
