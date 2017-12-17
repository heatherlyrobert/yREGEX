/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"


#define     MAX_LVL     1000
#define     MAX_STATE   1000

/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
typedef     struct      cSTATE      tSTATE;
struct      cSTATE {
   /*---(basics)-----------------*/
   short       begin;                       /* starting point                 */
   short       level;                       /* processing depth               */
   short       rpos;                        /* regex position                 */
   short       tpos;                        /* text position                  */
   /*---(results)----------------*/
   char        ready;                       /* ready for action/complete      */
   char        rc;                          /* link to shared return codes    */
   char        pref;                        /* identify lazy vs greedy pref   */
   /*---(connections)------------*/
   short       prev;                        /* previous state (created this)  */
   /*---(done)-------------------*/
};
/*---(static.vars)------+-----------+-*//*-+----------------------------------*/
static      tSTATE      s_states    [MAX_STATE];   /* all states              */
static      int         s_nstate    = 0;           /* total number of states  */
static      int         s_curr      = 0;           /* point to current state  */


static int         s_begin     = 0;                /* current search begin    */


/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char         /*-> tbd --------------------------------[ shoot  [fe.833.144.30]*/ /*-[01.0000.01#.H]-*/ /*-[--.---.---.--]-*/
EXEC__init           (cchar *a_source)
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
   FIND_init ();
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           handlers                           ----===*/
/*====================------------------------------------====================*/
static void      o___HANDLE__________________o (void) {;}

char
EXEC__group          (int a_level, int a_rpos, int a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_ndiv      =    0;
   int         x_offset    =    0;
   int         i           =    0;
   int         x_end       =    0;
   uchar       x_mod       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d", a_level, a_rpos, a_tpos);
   /*---(prepare)------------------------*/
   x_end       = COMP_group_end (a_rpos);
   DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
   x_mod       = gre.mods [x_end];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   x_ndiv      = gre.mods [a_rpos] - '0';
   DEBUG_YREGEX  yLOG_value   ("x_ndiv"    , x_ndiv);
   /*---(launch each branch)-------------*/
   for (i = 0; i <= x_ndiv; ++i) {
      DEBUG_YREGEX  yLOG_complex ("branch"    , "lvl %d, rpos %2d, off %2d, r+o %2d", i + 1, a_rpos, x_offset, a_rpos + x_offset + 1);
      EXEC_push (a_level, a_rpos + x_offset + 1, a_tpos);
      x_offset += gre.jump [a_rpos + x_offset];
   }
   /*---(launch without)-----------------*/
   if (strchr (G_ZERO, x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("always back launch for *@?! types");
      EXEC_push (a_level, x_end + 1, a_tpos);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
EXEC__anchor         (int a_level, int a_rpos, int a_tpos)
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
   EXEC_launcher (a_level, a_rpos, a_tpos - 1, rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
EXEC__literal        (int a_level, int a_rpos, int a_tpos)
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
   EXEC_launcher (a_level, a_rpos, a_tpos, rc);
   /*---(return)-------------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         data structure                       ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

char
EXEC_push            (short a_level, short a_rpos, short a_tpos)
{
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (a_level);
   DEBUG_YREGEX  yLOG_sint    (a_rpos);
   DEBUG_YREGEX  yLOG_sint    (a_tpos);
   /*---(push)---------------------------*/
   DEBUG_YREGEX  yLOG_sint    (s_nstate);
   s_states [s_nstate].begin = s_begin;
   s_states [s_nstate].level = a_level;
   s_states [s_nstate].rpos  = a_rpos;
   s_states [s_nstate].tpos  = a_tpos;
   s_states [s_nstate].ready = 'y';
   s_states [s_nstate].rc    = 0;
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
EXEC_backpush        (short a_level, short a_rpos, short a_tpos)
{
   int         x_prev      = 0;
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   EXEC_push (a_level, a_rpos, a_tpos);
   x_prev = s_states [s_states [s_nstate - 1].prev].prev;
   DEBUG_YREGEX  yLOG_char    ("x_prev"    , x_prev);
   s_states [s_nstate - 1].prev  = x_prev;
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char    
EXEC__list           (void)
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
      if ((c % 45) == 0)   printf ("refn  begn  lvl-  rpos  tpos  rdy  retn  --  reg  ind  mod  jmp  txt  --  prev\n\n");
      if (gre.comp [s_states [i].rpos] >= 32)  sprintf (x_reg, " %c ", gre.comp [s_states [i].rpos]);
      else                                     strlcpy (x_reg, "nul", 5);
      if (gre.mods [s_states [i].rpos] >= 32)  sprintf (x_mod, " %c ", gre.mods [s_states [i].rpos]);
      else                                     strlcpy (x_mod, "nul", 5);
      if (gre.text [s_states [i].tpos] >= 32)  sprintf (x_txt, " %c ", gre.text [s_states [i].tpos]);
      else                                     strlcpy (x_txt, "nul", 5);
      FIND_text (i, t);
      printf ("%-4d  %-4d  %-4d  %-4d  %-4d   %c   %-4d  --  %-3.3s  %-3d  %-3.3s  %-3d  %-3.3s  --  %-4d  %s\n",
            i,
            s_states [i].begin ,s_states [i].level,
            s_states [i].rpos, s_states [i].tpos,
            s_states [i].ready, s_states [i].rc,
            x_reg, gre.indx [s_states [i].rpos],
            x_mod, gre.jump [s_states [i].rpos],
            x_txt, s_states [i].prev, t);
      ++c;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       run-time handling                      ----===*/
/*====================------------------------------------====================*/
static void      o___RUNNER__________________o (void) {;}

char  s_found   [LEN_TEXT];
char  s_quans   [LEN_TEXT];

char  s_subf    [LEN_TEXT];
char  s_subq    [LEN_TEXT];

#define       S_SUB_BEFORE       0
#define       S_SUB_INSIDE       1
#define       S_SUB_AFTER        2
#define       S_SUB_DONE         3
char    
EXEC_sub             (int a_index, int a_paren)
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
      rc = EXEC_sub (s_states [a_index].prev, a_paren);
   } else {
      /*> printf ("      wiping\n");                                                  <*/
      strlcpy (s_subf, "", LEN_TEXT);
      strlcpy (s_subq, "", LEN_TEXT);
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
   if (x_reg == ')' && x_indx == a_paren) {
      /*> printf ("      close paren\n");                                             <*/
      return S_SUB_AFTER;
   }
   /*---(check for open)-----------------*/
   if (x_reg == '(' && x_indx == a_paren) {
      /*> printf ("      open paren\n");                                              <*/
      return S_SUB_INSIDE;
   }
   if (rc <= S_SUB_BEFORE) {
      /*> printf ("      skipping\n");                                                <*/
      return rc;
   }
   /*---(handle sets)--------------------*/
   if (x_reg == '[') {
      sprintf (t, "%c", x_ch);
      strlcat (s_subf, t, LEN_TEXT);
      sprintf (t, "%c", x_mod);
      strlcat (s_subq, t, LEN_TEXT);
      return rc;
   }
   /*---(filter other specials)----------*/
   if (x_indx > 0)      return rc;      /* avoid grouping */
   /*---(append result)------------------*/
   sprintf (t, "%c", x_ch);
   strlcat (s_subf, t, LEN_TEXT);
   sprintf (t, "%c", x_mod);
   strlcat (s_subq, t, LEN_TEXT);
   /*---(complete)-----------------------*/
   return rc;
}

char    
EXEC__found          (int a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [5] = "";
   int         x_rpos      =    0;
   int         x_tpos      =    0;
   uchar       x_ch        =  ' ';
   uchar       x_reg       =  ' ';
   uchar       x_mod       =  ' ';
   int         x_indx      =    0;
   /*---(dig to origin)------------------*/
   if (a_index != s_states [a_index].prev) {
      EXEC__found (s_states [a_index].prev);
   } else {
      strlcpy (s_found, "", LEN_TEXT);
      strlcpy (s_quans, "", LEN_TEXT);
   }
   /*---(filter)-------------------------*/
   if (s_states [a_index].ready == 'W')  return 0;
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
   /*---(handle sets)--------------------*/
   if (x_reg == '[') {
      sprintf (t, "%c", x_ch);
      strlcat (s_found, t, LEN_TEXT);
      sprintf (t, "%c", x_mod);
      strlcat (s_quans, t, LEN_TEXT);
      return 0;
   }
   /*---(filter other specials)----------*/
   if (x_indx > 0)  return 0;          /* avoid grouping */
   /*---(append result)------------------*/
   sprintf (t, "%c", x_ch);
   strlcat (s_found, t, LEN_TEXT);
   sprintf (t, "%c", x_mod);
   strlcat (s_quans, t, LEN_TEXT);
   /*---(complete)-----------------------*/
   return 0;
}

char
EXEC__prime          (void)
{
   s_nstate = 0;
   s_curr   = -1;
   EXEC_push (0, 0, 0);
   return 0;
}

char
EXEC_launcher        (short a_level, short a_rpos, short a_tpos, char a_rc)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_mod       =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_complex ("header"    , "level %-3d, rpos %-3d, tpos %-3d, rc %-3d", a_level, a_rpos, a_tpos, a_rc);
   /*---(prepare)------------------------*/
   x_mod       = gre.mods [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_mod"     , x_mod);
   /*---(back launch some)---------------*/
   if (strchr (G_ZERO, x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("always back launch for *@?! types");
      EXEC_backpush (a_level, a_rpos + 1, a_tpos);
   }
   /*---(always launch if successful)----*/
   if (a_rc > 0) {
      if (strchr (G_MANY, x_mod) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("relaunch for successful *@ types");
         EXEC_push (a_level, a_rpos    , a_tpos + 1);
      } else {
         DEBUG_YREGEX  yLOG_note    ("launch next for all successful steps");
         EXEC_push (a_level, a_rpos + 1, a_tpos + 1);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return a_rc;
}

char
EXEC__glauncher      (int a_level, int a_rpos, int a_tpos)
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
   x_beg       = COMP_group_beg (a_rpos);
   x_end       = COMP_group_end (a_rpos);
   DEBUG_YREGEX  yLOG_value   ("x_beg"     , x_beg);
   DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
   /*---(always launch if successful)----*/
   if (strchr (G_MANY, x_mod) != NULL) {
      DEBUG_YREGEX  yLOG_note    ("relaunch for successful *@ types");
      EXEC_push (a_level, x_beg    , a_tpos);
   } else {
      DEBUG_YREGEX  yLOG_note    ("launch next for all successful steps");
      EXEC_push (a_level, x_end + 1, a_tpos);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
EXEC__single         (int a_index)
{
   /*---(locals)-----------+------+----+-*/
   char        rc          =     0;
   int         i           =     0;
   int         x_level     =     0;
   int         x_rpos      =     0;
   int         x_tpos      =     0;
   uchar       x_ch        =   ' ';
   int         x_indx      =     0;
   uchar       x_mod       =   ' ';
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
   /*---(check for null)-----------------*/
   if (x_ch == 0) {
      DEBUG_YREGEX  yLOG_note    ("found null");
      s_states [a_index].ready = 'W';
      s_states [a_index].rc    =  1;
      rc = EXEC__found (a_index);
      FIND_add    (a_index, s_states [a_index].begin, s_found, s_quans);
      for (i = 1; i <= 10; ++i) {
         /*> printf ("search for paren %d\n", i);                                     <*/
         rc = EXEC_sub (a_index, i);
         /*> printf ("   index %d, sub %d, rc %d\n", a_index, i, rc);                 <*/
         if (rc < S_SUB_AFTER)  continue;
         FIND_sub (a_index, i - 1, s_subf, s_subq);
      }
      rc = EXEC_sub (a_index, 999);
      if (rc > 0)  FIND_sub (a_index, 10, s_subf, s_subq);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 100;
   }
   /*---(get literals quick)-------------*/
   if (x_indx == 0) {
      DEBUG_YREGEX  yLOG_note    ("found literal");
      rc = EXEC__literal     (x_level + 1, x_rpos, x_tpos);
   }
   /*---(more complex actions)-----------*/
   else {
      switch (x_ch) {
      case '(' :
         DEBUG_YREGEX  yLOG_note    ("open group");
         rc = EXEC__group       (x_level + 1, x_rpos, x_tpos);
         break;
      case ')' : case '|' :
         DEBUG_YREGEX  yLOG_note    ("close branch/group");
         rc = EXEC__glauncher   (x_level + 1, x_rpos, x_tpos);
         break;
      case '^' : case '$' :
         DEBUG_YREGEX  yLOG_note    ("true anchor");
         rc = EXEC__anchor      (x_level + 1, x_rpos, x_tpos);
         break;
      case '<' : case '>' :
         DEBUG_YREGEX  yLOG_note    ("set anchor");
         rc = SETS_break        (x_level + 1, x_rpos, x_tpos);
         break;
      case '[' :
         DEBUG_YREGEX  yLOG_note    ("set");
         rc = SETS_exec         (x_level + 1, x_rpos, x_tpos);
         break;
      default  :
         DEBUG_YREGEX  yLOG_note    ("other");
         rc = EXEC__literal     (x_level + 1, x_rpos, x_tpos);
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
yREGEX_exec          (cchar *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_source"  , a_source);
   /*---(prepare)------------------------*/
   rc = EXEC__init  (a_source);
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
      EXEC_push (0, 0, s_begin);
      for (i = 0; i < s_nstate; ++i) {
         if (s_states [i].ready != 'y') continue;
         s_curr = i;
         rc = EXEC__single (i);
         /*> if (rc == 100)  return 1;                                                   <*/
      }
      /*> if (rc >= 1) break;                                                         <*/
      /*> break;                                                                      <*/
   }
   /*> EXEC__list  ();                                                                <*/
   /*> FIND_list   ();                                                                <*/
   rc = FIND_count ();
   if (rc > 100) rc == 100;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}


/*===============================[[ end code ]]===============================*/
