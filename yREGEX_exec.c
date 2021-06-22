/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"


/*
 * metis  ww4··  speed up EXEC_sub with iteration, not recursion
 *
 *
 */

#define     MAX_LVL      1000
#define     MAX_STATE   10000

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
typedef     struct      cSTATE      tSTATE;
static struct      cSTATE {
   /*---(basics)-----------------*/
   short       begin;                       /* starting point                 */
   short       level;                       /* processing depth               */
   short       rpos;                        /* regex position                 */
   short       tpos;                        /* text position                  */
   short       tmax;                        /* max text position              */
   /*---(results)----------------*/
   char        ready;                       /* ready for action/complete      */
   char        rc;                          /* link to shared return codes    */
   /*---(connections)------------*/
   int         prev;                        /* previous state (created this)  */
   /*---(done)-------------------*/
};
/*---(static.vars)------+-----------+-*//*-+----------------------------------*/
static      tSTATE      s_states    [MAX_STATE];   /* all states              */
static      int         s_nstate    = 0;           /* total number of states  */
static      int         s_curr      = 0;           /* point to current state  */




/*> static tSTATE     *s_head     = NULL;                                             <* 
 *> static tSTATE     *s_tail     = NULL;                                             <* 
 *> static tSTATE     *s_curr     = NULL;                                             <* 
 *> static int         s_count    = 0;                                                <*/



static      char        s_print     [LEN_RECD] = "";

static      int         s_begin     = 0;                /* current search begin    */

char         /*-> tbd --------------------------------[ shoot  [fe.833.144.30]*/ /*-[01.0000.01#.H]-*/ /*-[--.---.---.--]-*/
yregex_exec__prep    (cchar *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_source"  , a_source);
   /*---(check regex)--------------------*/
   --rce;  if (a_source  == NULL) {
      DEBUG_YREGEX  yLOG_note    ("can not be null");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = strlcpy (gre.text, a_source , LEN_TEXT);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   --rce;  if (rc     <  0   ) {
      DEBUG_YREGEX  yLOG_note    ("truncated copy");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   gre.tlen = strllen (gre.text , LEN_TEXT);
   DEBUG_YREGEX  yLOG_value   ("gre.tlen"  , gre.tlen);
   /*---(state settings)-----------------*/
   s_nstate = 0;
   s_curr   = 0;
   /*---(finds)--------------------------*/
   yregex_find_init ();
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           handlers                           ----===*/
/*====================------------------------------------====================*/
static void      o___HANDLE__________________o (void) {;}

char
yregex_exec__group      (int a_level, int a_rpos, int a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_ndiv      =    0;
   uchar       x_type      =    0;
   int         x_offset    =    0;
   int         i           =    0;
   int         x_end       =    0;
   uchar       x_mod       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d", a_level, a_rpos, a_tpos);
   /*---(prepare)------------------------*/
   x_end       = yregex_comp__group_end (a_rpos);
   DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
   x_mod       = gre.mods [x_end];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   x_ndiv      = gre.mods [a_rpos] - '0';
   DEBUG_YREGEX  yLOG_value   ("x_ndiv"    , x_ndiv);
   /*---(launch each branch)-------------*/
   for (i = 0; i <= x_ndiv; ++i) {
      x_type  = gre.comp [a_rpos + x_offset];
      DEBUG_YREGEX  yLOG_complex ("branch"    , "lvl %d, rpos %2d, type %c, off %2d, r+o %2d", i + 1, a_rpos, x_type, x_offset, a_rpos + x_offset + 1);
      if (strchr ("(|", x_type) != NULL) yregex_exec_push (a_level, a_rpos + x_offset + 1, a_tpos, -1);
      x_offset += gre.jump [a_rpos + x_offset];
   }
   /*---(launch without)-----------------*/
   if (strchr (G_ZERO, x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("always back launch for *@?! types");
      yregex_exec_push (a_level, x_end + 1, a_tpos, -1);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yregex_exec__anchor         (int a_level, int a_rpos, int a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d", a_level, a_rpos, a_tpos);
   /*---(prepare)------------------------*/
   x_ch        = gre.comp [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_chr"     , x_ch);
   /*---(handle)-------------------------*/
   switch (x_ch) {
   case '^' :   /* beginning of line */
      if (a_tpos != 0) {
         DEBUG_YREGEX  yLOG_note    ("FAILED, not at BOL");
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      DEBUG_YREGEX  yLOG_note    ("BOL");
      rc = 1;
      break;
   case '$' :   /* end of line       */
      if (a_tpos < gre.tlen){
         DEBUG_YREGEX  yLOG_note    ("FAILED, not at EOL");
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      DEBUG_YREGEX  yLOG_note    ("EOL");
      rc = 1;
      break;
   }
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   /*---(prepare next)-------------------*/
   yregex_exec_launcher (a_level, a_rpos, a_tpos - 1, rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yregex_exec__literal    (int a_level, int a_rpos, int a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_reg       =    0;
   uchar       x_txt       =    0;
   uchar       x_mod       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d", a_level, a_rpos, a_tpos);
   /*---(prepare)------------------------*/
   x_reg       = gre.comp [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_reg"     , x_reg);
   x_txt       = gre.text [a_tpos];
   DEBUG_YREGEX  yLOG_char    ("x_txt"     , x_txt);
   /*---(test)---------------------------*/
   if (x_reg == x_txt) {
      DEBUG_YREGEX  yLOG_note    ("matches, passed");
      rc = 1;
   } else {
      DEBUG_YREGEX  yLOG_note    ("FAILED");
   }
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   /*---(prepare next)-------------------*/
   yregex_exec_launcher (a_level, a_rpos, a_tpos, rc);
   /*---(return)-------------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         data structure                       ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

char
yregex_exec_push        (short a_level, short a_rpos, short a_tpos, short a_tmax)
{
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (a_level);
   DEBUG_YREGEX  yLOG_sint    (a_rpos);
   DEBUG_YREGEX  yLOG_sint    (a_tpos);
   DEBUG_YREGEX  yLOG_sint    (a_tmax);
   /*---(push)---------------------------*/
   DEBUG_YREGEX  yLOG_sint    (s_nstate);
   s_states [s_nstate].begin = s_begin;
   s_states [s_nstate].level = a_level;
   s_states [s_nstate].rpos  = a_rpos;
   s_states [s_nstate].tpos  = a_tpos;
   s_states [s_nstate].ready = 'y';
   s_states [s_nstate].rc    = 0;
   /*---(handle max)---------------------*/
   if (a_tmax < 0)        s_states [s_nstate].tmax  = s_states [s_curr].tmax;
   else if (a_tmax == 0)  s_states [s_nstate].tmax  = LEN_TEXT;
   else                   s_states [s_nstate].tmax  = a_tmax;
   /*---(connections)--------------------*/
   DEBUG_YREGEX  yLOG_sint    (s_curr);
   s_states [s_nstate].prev  = s_curr;
   /*---(prepare for next)---------------*/
   ++s_nstate;
   DEBUG_YREGEX  yLOG_sint    (s_nstate);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yregex_exec_backpush        (short a_level, short a_rpos, short a_tpos, short a_tmax)
{
   int         x_prev      = 0;
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   yregex_exec_push (a_level, a_rpos, a_tpos, a_tmax);
   x_prev = s_states [s_states [s_nstate - 1].prev].prev;
   DEBUG_YREGEX  yLOG_char    ("x_prev"    , x_prev);
   s_states [s_nstate - 1].prev  = x_prev;
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char    
yREGEX_dump          (void)
{
   int         i           = 0;
   int         c           = 0;
   char        x_reg       [5];
   char        x_mod       [5];
   char        x_txt       [5];
   char        t           [LEN_TEXT];
   for (i = 0; i < s_nstate; ++i) {
      if (s_states [i].prev == i)  c = 0;
      if ((c %  5) == 0)   printf ("\n");
      if ((c % 45) == 0)   printf ("prev  refn  beg  lvl  --  rps  reg  ind  mod  jmp  --  tps  txt  --  rdy  retn  --  found\n\n");
      if (gre.comp [s_states [i].rpos] >= 32)  sprintf (x_reg, "  %c", gre.comp [s_states [i].rpos]);
      else                                     strlcpy (x_reg, "nul", 5);
      if (gre.mods [s_states [i].rpos] >= 32)  sprintf (x_mod, "  %c", gre.mods [s_states [i].rpos]);
      else                                     strlcpy (x_mod, "nul", 5);
      if (gre.text [s_states [i].tpos] >= 32)  sprintf (x_txt, "  %c", gre.text [s_states [i].tpos]);
      else                                     strlcpy (x_txt, "nul", 5);
      yregex_find_text (i, t);
      printf ("%4d  %4d  %3d  %3d  --  %3d  %s  %3d  %s  %3d  --  %3d  %s  --    %c   %3d  --  %s\n",
            s_states [i].prev, i, s_states [i].begin ,s_states [i].level,
            s_states [i].rpos, x_reg,
            gre.indx [s_states [i].rpos], x_mod, gre.jump [s_states [i].rpos],
            s_states [i].tpos, x_txt,
            s_states [i].ready, s_states [i].rc,
            t);
      ++c;
   }
   return 0;
}

char    
yregex_exec_list     (void)
{
   int         i           = 0;
   int         c           = 0;
   char        x_reg       [5];
   char        x_mod       [5];
   char        x_txt       [5];
   char        t           [LEN_TEXT];
   for (i = 0; i < s_nstate; ++i) {
      if (s_states [i].ready != 'W') continue;
      if ((c %  5) == 0)   printf ("\n");
      if ((c % 45) == 0)   printf ("prev  refn  beg  lvl  --  rps  reg  ind  mod  jmp  --  tps  txt  --  rdy  retn  --  found\n\n");
      if (gre.comp [s_states [i].rpos] >= 32)  sprintf (x_reg, "  %c", gre.comp [s_states [i].rpos]);
      else                                     strlcpy (x_reg, "nul", 5);
      if (gre.mods [s_states [i].rpos] >= 32)  sprintf (x_mod, "  %c", gre.mods [s_states [i].rpos]);
      else                                     strlcpy (x_mod, "nul", 5);
      if (gre.text [s_states [i].tpos] >= 32)  sprintf (x_txt, "  %c", gre.text [s_states [i].tpos]);
      else                                     strlcpy (x_txt, "nul", 5);
      yregex_find_text (i, t);
      printf ("%4d  %4d  %3d  %3d  --  %3d  %s  %3d  %s  %3d  --  %3d  %s  --    %c   %3d  --  %s\n",
            s_states [i].prev, i, s_states [i].begin ,s_states [i].level,
            s_states [i].rpos, x_reg,
            gre.indx [s_states [i].rpos], x_mod, gre.jump [s_states [i].rpos],
            s_states [i].tpos, x_txt,
            s_states [i].ready, s_states [i].rc,
            t);
      ++c;
   }
   return 0;
}

int
yregex_exec_index            (int a_index)
{
   return gre.indx [s_states [a_index].rpos];
}


/*====================------------------------------------====================*/
/*===----                       run-time handling                      ----===*/
/*====================------------------------------------====================*/
static void      o___RUNNER__________________o (void) {;}

char  g_found   [LEN_TEXT];
char  g_quans   [LEN_TEXT];

short g_subb    = -1;
char  g_subf    [LEN_TEXT];
char  g_subq    [LEN_TEXT];

#define       S_SUB_BEFORE       0
#define       S_SUB_INSIDE       1
#define       S_SUB_AFTER        2
#define       S_SUB_DONE         3

char    
yregex_exec_found_NEW   (int a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         p           =   -1;
   int         x_rpos      =    0;
   uchar       x_reg       =  ' ';
   int         x_tpos      =    0;
   uchar       x_ch        =  ' ';
   uchar       x_mod       =  ' ';
   int         x_indx      =    0;
   int         x_len       =    0;
   char        x_text      [LEN_RECD];
   char        x_quan      [LEN_RECD];
   char        t           [LEN_RECD];
   char        q           [LEN_RECD];
   /*---(mark tail)----------------------*/
   s_states [a_index].ready = 'W';
   s_states [a_index].rc    =  1;
   /*---(identify groups)----------------*/
   i = a_index;
   while ((i = s_states [i].prev) != p) {
      /*---(mark solution)---------------*/
      p = i;
      s_states [i].ready = '+';
      /*---(get  solution)---------------*/
      x_rpos = s_states [i].rpos;
      x_reg  = gre.comp [x_rpos];
      /*---(text)---------------------------*/
      x_tpos = s_states [i].tpos;
      x_ch   = gre.text [x_tpos];
      x_indx = gre.indx [x_rpos] - 1;
      if (x_indx == 998)  x_indx = 10;
      x_mod  = gre.mods [x_rpos];
      /*---(handle grouping)----------------*/
      switch (x_reg) {
      case ')' : case '|' :
         gre.gends [x_indx] = x_tpos - 1;
         break;
      case '(' :
         gre.gbegs [x_indx] = x_tpos;
         break;
      default  :
         x_text [x_tpos] = x_ch;
         x_quan [x_tpos] = x_mod;
         break;
      }
   }
   /*---(fill groups)--------------------*/
   for (i = 0; i <= 10; ++i) {
      /*> printf ("%2d %c\n", i, gre.groups [i]);                                     <*/
      if (gre.groups [i] == ' ') {
         yregex_find_addsub (a_index, i, -1    , ""    , ""    );
         continue;
      }
      x_len = gre.gends [i] - gre.gbegs [i] + 1;
      strlcpy (t, x_text + gre.gbegs [i], x_len + 1);
      strlcpy (q, x_quan + gre.gbegs [i], x_len + 1);
      /*> printf ("   %3d %3d %3d [%s] [%s]\n", gre.gbegs [i], gre.gends [i], x_len, t, q);   <*/
      if (i == 0)  yregex_find_add (a_index, s_states [a_index].begin, t, q);
      yregex_find_addsub (a_index, i, gre.gbegs [i], t, q);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char    
yregex_exec_sub         (int a_index, int a_paren)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    S_SUB_BEFORE;
   char        t           [5] = "";
   int         x_rpos      =    0;
   int         x_tpos      =    0;
   uchar       x_ch        =  ' ';
   uchar       x_reg       =  ' ';
   uchar       x_mod       =  ' ';
   int         x_indx      =    0;
   /*---(dig to origin)------------------*/
   if (a_index != s_states [a_index].prev) {
      /*> printf ("      call deeper\n");                                             <*/
      rc = yregex_exec_sub (s_states [a_index].prev, a_paren);
   } else {
      /*> printf ("      wiping\n");                                                  <*/
      /*> strlcpy (g_subf, "", LEN_TEXT);                                             <* 
       *> strlcpy (g_subq, "", LEN_TEXT);                                             <*/
      g_subb     = -1;
      g_subf [0] = '\0';
      g_subq [0] = '\0';
      rc = S_SUB_BEFORE;
   }
   /*---(filter)-------------------------*/
   if (s_states [a_index].ready == 'W')  return rc;
   if (rc >= S_SUB_AFTER)                return rc;
   /*---(text)---------------------------*/
   x_tpos = s_states [a_index].tpos;
   x_ch   = gre.text [x_tpos];
   /*---(quantifiers)--------------------*/
   x_rpos = s_states [a_index].rpos;
   x_reg  = gre.comp [x_rpos];
   x_indx = gre.indx [x_rpos];
   x_mod  = gre.mods [x_rpos];
   /*> printf ("   rpos %-2d, reg %c, indx %-2d, mod %c, rc %-2d\n", x_rpos, x_reg, x_indx, x_mod, rc);   <*/
   /*---(check for close)----------------*/
   if (strchr ("|)", x_reg) != NULL  && x_indx == a_paren) {
      /*> printf ("      close paren\n");                                             <*/
      return S_SUB_AFTER;
   }
   /*---(check for open)-----------------*/
   if (strchr ("(" , x_reg) != NULL  && x_indx == a_paren) {
      /*> printf ("      open paren\n");                                              <*/
      if (g_subb == -1)  g_subb = x_tpos;
      return S_SUB_INSIDE;
   }
   if (rc <= S_SUB_BEFORE) {
      /*> printf ("      skipping\n");                                                <*/
      return rc;
   }
   /*---(handle sets)--------------------*/
   if (x_reg == '[') {
      sprintf (t, "%c", x_ch);
      strlcat (g_subf, t, LEN_TEXT);
      sprintf (t, "%c", x_mod);
      strlcat (g_subq, t, LEN_TEXT);
      return rc;
   }
   /*---(filter other specials)----------*/
   if (x_indx > 0)      return rc;      /* avoid grouping */
   /*---(append result)------------------*/
   sprintf (t, "%c", x_ch);
   strlcat (g_subf, t, LEN_TEXT);
   sprintf (t, "%c", x_mod);
   strlcat (g_subq, t, LEN_TEXT);
   /*---(complete)-----------------------*/
   return rc;
}

int
yregex_exec_tpos        (int a_index, int a_paren, int *a_tbeg, int *a_tend)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =   -1;
   int         x_tpos      =    0;
   uchar       x_ch        =  ' ';
   int         x_rpos      =    0;
   uchar       x_reg       =  ' ';
   int         x_indx      =    0;
   uchar       x_mod       =  ' ';
   /*---(text)---------------------------*/
   /*> printf ("   index %-3d, paren %-2d, tbeg %-2d, tend %-2d\n", a_index, a_paren, *a_tbeg, *a_tend);   <*/
   x_tpos = s_states [a_index].tpos;
   /*---(quantifiers)--------------------*/
   x_rpos = s_states [a_index].rpos;
   x_reg  = gre.comp [x_rpos];
   x_indx = gre.indx [x_rpos];
   x_mod  = gre.mods [x_rpos];
   /*> printf ("   tpos %-2d, rpos %-2d, reg %c, indx %-2d, mod %c\n", x_tpos, x_rpos, x_reg, x_indx, x_mod);   <*/
   /*---(check for last marker)----------*/
   if (strchr ("|)", x_reg) != NULL && x_indx == a_paren) {
      /*> printf ("      found CLOSE at %d\n", x_tpos);                               <*/
      *a_tend = x_tpos;
      rc = 1;
   }
   /*---(check for paren)----------------*/
   if (strchr ("(", x_reg) != NULL && x_indx == a_paren) {
      /*> printf ("      found OPEN/OR at %d\n", x_tpos);                             <*/
      *a_tbeg = x_tpos;
      rc = 2;
   }
   /*---(dig to origin)------------------*/
   else if (a_index != s_states [a_index].prev) {
      /*> printf ("      call deeper\n");                                             <*/
      rc = yregex_exec_tpos (s_states [a_index].prev, a_paren, a_tbeg, a_tend);
   }
   /*> printf ("      done with %d\n", rc);                                           <*/
   /*---(complete)-----------------------*/
   return rc;
}

char    
yregex_exec__found      (int a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        t           [5] = "";
   int         x_rpos      =    0;
   int         x_tpos      =    0;
   uchar       x_ch        =  ' ';
   uchar       x_reg       =  ' ';
   uchar       x_mod       =  ' ';
   int         x_indx      =    0;
   /*---(dig to origin)------------------*/
   if (a_index != s_states [a_index].prev) {
      rc = yregex_exec__found (s_states [a_index].prev);
   } else {
      /*> strlcpy (g_found, "", LEN_TEXT);                                            <* 
       *> strlcpy (g_quans, "", LEN_TEXT);                                            <*/
      g_found [0] = '\0';
      g_quans [0] = '\0';
   }
   /*---(filter)-------------------------*/
   if (rc > 0)                           return rc;
   if (s_states [a_index].ready == 'W')  return 1;
   /*---(mark)---------------------------*/
   s_states [a_index].ready = '+';
   /*---(text)---------------------------*/
   x_tpos = s_states [a_index].tpos;
   x_ch   = gre.text [x_tpos];
   /*---(quantifiers)--------------------*/
   x_rpos = s_states [a_index].rpos;
   x_reg  = gre.comp [x_rpos];
   x_indx = gre.indx [x_rpos];
   x_mod  = gre.mods [x_rpos];
   /*---(find start of rules)------------*/
   if (x_reg == ';' && x_indx > 0) {
      return 1;
   }
   /*---(handle sets)--------------------*/
   if (x_reg == '[') {
      sprintf (t, "%c", x_ch);
      strlcat (g_found, t, LEN_TEXT);
      sprintf (t, "%c", x_mod);
      strlcat (g_quans, t, LEN_TEXT);
      return 0;
   }
   /*---(filter other specials)----------*/
   if (x_indx > 0)  return 0;          /* avoid grouping */
   /*---(append result)------------------*/
   sprintf (t, "%c", x_ch);
   strlcat (g_found, t, LEN_TEXT);
   sprintf (t, "%c", x_mod);
   strlcat (g_quans, t, LEN_TEXT);
   /*---(complete)-----------------------*/
   return 0;
}

char
yregex_exec_launcher    (short a_level, short a_rpos, short a_tpos, char a_rc)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_reg       =  ' ';
   uchar       x_mod       =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d, rc %-3d", a_level, a_rpos, a_tpos, a_rc);
   /*---(prepare)------------------------*/
   x_reg       = gre.comp [a_rpos];
   x_mod       = gre.mods [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   /*---(back launch some)---------------*/
   if (x_reg != ';' && strchr (G_ZERO, x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("always back launch for *@?! types");
      yregex_exec_backpush (a_level, a_rpos + 1, a_tpos, -1);
   }
   /*---(always launch if successful)----*/
   if (a_rc > 0) {
      if (x_reg != ';' && strchr (G_MANY, x_mod) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("relaunch for successful *@ types");
         yregex_exec_push (a_level, a_rpos    , a_tpos + 1, -1);
      } else {
         DEBUG_YREGEX  yLOG_note    ("launch next for all successful steps");
         yregex_exec_push (a_level, a_rpos + 1, a_tpos + 1, -1);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return a_rc;
}

char
yregex_exec__branch     (int a_level, int a_rpos, int a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_mod       =    0;
   int         x_beg       =    0;
   int         x_end       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d", a_level, a_rpos, a_tpos);
   /*---(prepare)------------------------*/
   x_mod       = gre.mods [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   /*---(locations)----------------------*/
   x_beg       = yregex_comp__group_beg (a_rpos);
   x_end       = yregex_comp__group_end (a_rpos);
   DEBUG_YREGEX  yLOG_value   ("x_beg"     , x_beg);
   DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
   /*---(always launch if successful)----*/
   if (strchr (G_MANY, x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("relaunch for successful *@ types");
      yregex_exec_push (a_level, x_beg    , a_tpos, 0);
   } else {
      DEBUG_YREGEX  yLOG_note    ("launch next for all successful steps");
      yregex_exec_push (a_level, x_end + 1, a_tpos, 0);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yregex_exec__single     (int a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   int         x_level     =    0;
   int         x_rpos      =    0;
   int         x_tpos      =    0;
   uchar       x_ch        =  ' ';
   int         x_indx      =    0;
   uchar       x_mod       =  ' ';
   int         x_tmax      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_index"   , a_index);
   /*---(prepare)------------------------*/
   x_level = s_states [a_index].level;
   x_rpos  = s_states [a_index].rpos;
   x_tpos  = s_states [a_index].tpos;
   x_ch    = gre.comp [s_states [a_index].rpos];
   x_indx  = gre.indx [s_states [a_index].rpos];
   x_mod   = gre.mods [s_states [a_index].rpos];
   x_tmax  = s_states [a_index].tmax;
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d, tmax %-3d", x_level, x_rpos, x_tpos, x_tmax);
   /*---(check for null)-----------------*/
   if (x_ch == 0) {
      DEBUG_YREGEX  yLOG_note    ("found null");
      yregex_exec_found_NEW (a_index);
      /*> s_states [a_index].ready = 'W';                                                             <* 
       *> s_states [a_index].rc    =  1;                                                              <* 
       *> rc = yregex_exec__found (a_index);                                                          <* 
       *> yregex_find_add (a_index, s_states [a_index].begin, g_found, g_quans);                      <* 
       *> for (i = 1; i <= 10; ++i) {                                                                 <* 
       *>    if (gre.groups [i - 1] == ' ') {                                                         <* 
       *>       yregex_find_addsub (a_index, i - 1, -1    , ""    , ""    );                          <* 
       *>    }                                                                                        <* 
       *>    else {                                                                                   <* 
       *>       rc = yregex_exec_sub (a_index, i);                                                    <* 
       *>       if (rc < S_SUB_AFTER)  yregex_find_addsub (a_index, i - 1, -1    , ""    , ""    );   <* 
       *>       else                   yregex_find_addsub (a_index, i - 1, g_subb, g_subf, g_subq);   <* 
       *>    }                                                                                        <* 
       *> }                                                                                           <* 
       *> if (gre.groups [10] == ' ') {                                                               <* 
       *>    yregex_find_addsub (a_index, i - 1, -1    , ""    , ""    );                             <* 
       *> } else {                                                                                    <* 
       *>    rc = yregex_exec_sub (a_index, GROUP_FOCUS);                                             <* 
       *>    if (rc <= 0)  yregex_find_addsub (a_index, 10, -1    , ""    , ""    );                  <* 
       *>    if (rc >  0)  yregex_find_addsub (a_index, 10, g_subb, g_subf, g_subq);                  <* 
       *> }                                                                                           <*/
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 100;
   }
   /*---(check for overlong ANDs)--------*/
   if (x_tpos == x_tmax) {
      DEBUG_YREGEX  yLOG_note    ("hit a_tmax and must die");
      rc = -1;
   }
   /*---(get literals quick)-------------*/
   else if (x_indx == 0) {
      DEBUG_YREGEX  yLOG_note    ("found literal");
      rc = yregex_exec__literal    (x_level + 1, x_rpos, x_tpos);
   }
   /*---(more complex actions)-----------*/
   else {
      switch (x_ch) {
      case '(' :
         DEBUG_YREGEX  yLOG_note    ("open group");
         rc = yregex_exec__group   (x_level + 1, x_rpos, x_tpos);
         break;
      case ')' : case '|' :
         DEBUG_YREGEX  yLOG_note    ("close branch/group");
         rc = yregex_exec__branch  (x_level + 1, x_rpos, x_tpos);
         break;
      case ';' :
         DEBUG_YREGEX  yLOG_note    ("execute rule");
         rc = yregex_rule_exec     (x_level + 1, x_rpos, x_tpos, a_index);
         break;
      case '^' : case '$' :
         DEBUG_YREGEX  yLOG_note    ("true anchor");
         rc = yregex_exec__anchor  (x_level + 1, x_rpos, x_tpos);
         break;
      case '<' : case '>' :
         DEBUG_YREGEX  yLOG_note    ("set anchor");
         rc = yregex_sets_break    (x_level + 1, x_rpos, x_tpos);
         break;
      case '[' :
         DEBUG_YREGEX  yLOG_note    ("found set");
         rc = yregex_sets_exec     (x_level + 1, x_rpos, x_tpos);
         break;
      default  :
         DEBUG_YREGEX  yLOG_note    ("other");
         rc = yregex_exec__literal (x_level + 1, x_rpos, x_tpos);
         break;
      }
   }
   /*---(finish)-------------------------*/
   s_states [a_index].ready = '-';
   s_states [a_index].rc    = rc;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         main driver                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char 
yregex_exec_driver   (char a_type, cchar *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_char    ("a_type"    , a_type);
   DEBUG_YREGEX  yLOG_point   ("a_source"  , a_source);
   /*---(prepare)------------------------*/
   rc = yregex_exec__prep  (a_source);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(parse)--------------------------*/
   DEBUG_YREGEX  yLOG_info    ("a_source"  , a_source);
   DEBUG_YREGEX  yLOG_value   ("gre.tlen"  , gre.tlen);
   for (s_begin = 0; s_begin < gre.tlen; ++s_begin) {
      DEBUG_YREGEX  yLOG_value   ("BEGIN AT"  , s_begin);
      s_curr = s_nstate;
      yregex_exec_push (0, 0, s_begin, 0);
      for (i = 0; i < s_nstate; ++i) {
         if (s_states [i].ready != 'y') continue;
         s_curr = i;
         rc = yregex_exec__single (i);
         if (a_type == '1' && yregex_find_count () > 0)  return 1;
      }
   }
   rc = yregex_find_count ();
   if (rc > 100) rc == 100;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char yREGEX_exec          (cchar *a_source) { return yregex_exec_driver ('a', a_source); }
char yREGEX_fast          (cchar *a_source) { return yregex_exec_driver ('1', a_source); }



/*===============================[[ end code ]]===============================*/
