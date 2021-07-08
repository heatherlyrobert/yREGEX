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
/*> typedef     struct      cSTATE      tSTATE;                                        <* 
 *> static struct      cSTATE {                                                        <* 
 *>    /+---(basics)-----------------+/                                                <* 
 *>    short       begin;                       /+ starting point                 +/   <* 
 *>    short       level;                       /+ processing depth               +/   <* 
 *>    short       rpos;                        /+ regex position                 +/   <* 
 *>    short       tpos;                        /+ text position                  +/   <* 
 *>    short       tmax;                        /+ max text position              +/   <* 
 *>    /+---(results)----------------+/                                                <* 
 *>    char        ready;                       /+ ready for action/complete      +/   <* 
 *>    char        rc;                          /+ link to shared return codes    +/   <* 
 *>    /+---(connections)------------+/                                                <* 
 *>    int         prev;                        /+ previous state (created this)  +/   <* 
 *>    /+---(done)-------------------+/                                                <* 
 *> };                                                                                 <* 
 *> /+---(static.vars)------+-----------+-+//+-+----------------------------------+/   <* 
 *> static      tSTATE      s_states    [MAX_STATE];   /+ all states              +/   <* 
 *> static      int         s_nstate    = 0;           /+ total number of states  +/   <* 
 *> static      int         s_curr      = 0;           /+ point to current state  +/   <*/




/*> static tSTATE     *s_head     = NULL;                                             <* 
 *> static tSTATE     *s_tail     = NULL;                                             <* 
 *> static tSTATE     *s_curr     = NULL;                                             <* 
 *> static int         s_count    = 0;                                                <*/




static      int         s_begin     = 0;                /* current search begin    */




/*====================------------------------------------====================*/
/*===----                           handlers                           ----===*/
/*====================------------------------------------====================*/
static void      o___HANDLE__________________o (void) {;}

/*> char                                                                                                                                   <* 
 *> yREGEX_dump          (void)                                                                                                            <* 
 *> {                                                                                                                                      <* 
 *>    int         i           = 0;                                                                                                        <* 
 *>    int         c           = 0;                                                                                                        <* 
 *>    char        x_reg       [5];                                                                                                        <* 
 *>    char        x_mod       [5];                                                                                                        <* 
 *>    char        x_txt       [5];                                                                                                        <* 
 *>    char        t           [LEN_TEXT];                                                                                                 <* 
 *>    for (i = 0; i < s_nstate; ++i) {                                                                                                    <* 
 *>       if (s_states [i].prev == i)  c = 0;                                                                                              <* 
 *>       if ((c %  5) == 0)   printf ("\n");                                                                                              <* 
 *>       if ((c % 45) == 0)   printf ("prev  refn  beg  lvl  --  rps  reg  ind  mod  jmp  --  tps  txt  --  rdy  retn  --  found\n\n");   <* 
 *>       if (myREGEX.comp [s_states [i].rpos] >= 32)  sprintf (x_reg, "  %c", myREGEX.comp [s_states [i].rpos]);                          <* 
 *>       else                                     strlcpy (x_reg, "nul", 5);                                                              <* 
 *>       if (myREGEX.mods [s_states [i].rpos] >= 32)  sprintf (x_mod, "  %c", myREGEX.mods [s_states [i].rpos]);                          <* 
 *>       else                                     strlcpy (x_mod, "nul", 5);                                                              <* 
 *>       if (myREGEX.text [s_states [i].tpos] >= 32)  sprintf (x_txt, "  %c", myREGEX.text [s_states [i].tpos]);                          <* 
 *>       else                                     strlcpy (x_txt, "nul", 5);                                                              <* 
 *>       yregex_find_text (i, t);                                                                                                         <* 
 *>       printf ("%4d  %4d  %3d  %3d  --  %3d  %s  %3d  %s  %3d  --  %3d  %s  --    %c   %3d  --  %s\n",                                  <* 
 *>             s_states [i].prev, i, s_states [i].begin ,s_states [i].level,                                                              <* 
 *>             s_states [i].rpos, x_reg,                                                                                                  <* 
 *>             myREGEX.indx [s_states [i].rpos], x_mod, myREGEX.jump [s_states [i].rpos],                                                 <* 
 *>             s_states [i].tpos, x_txt,                                                                                                  <* 
 *>             s_states [i].ready, s_states [i].rc,                                                                                       <* 
 *>             t);                                                                                                                        <* 
 *>       ++c;                                                                                                                             <* 
 *>    }                                                                                                                                   <* 
 *>    return 0;                                                                                                                           <* 
 *> }                                                                                                                                      <*/

/*> char                                                                                                                                   <* 
 *> yregex_exec_list     (void)                                                                                                            <* 
 *> {                                                                                                                                      <* 
 *>    int         i           = 0;                                                                                                        <* 
 *>    int         c           = 0;                                                                                                        <* 
 *>    char        x_reg       [5];                                                                                                        <* 
 *>    char        x_mod       [5];                                                                                                        <* 
 *>    char        x_txt       [5];                                                                                                        <* 
 *>    char        t           [LEN_TEXT];                                                                                                 <* 
 *>    for (i = 0; i < s_nstate; ++i) {                                                                                                    <* 
 *>       if (s_states [i].ready != 'W') continue;                                                                                         <* 
 *>       if ((c %  5) == 0)   printf ("\n");                                                                                              <* 
 *>       if ((c % 45) == 0)   printf ("prev  refn  beg  lvl  --  rps  reg  ind  mod  jmp  --  tps  txt  --  rdy  retn  --  found\n\n");   <* 
 *>       if (myREGEX.comp [s_states [i].rpos] >= 32)  sprintf (x_reg, "  %c", myREGEX.comp [s_states [i].rpos]);                          <* 
 *>       else                                     strlcpy (x_reg, "nul", 5);                                                              <* 
 *>       if (myREGEX.mods [s_states [i].rpos] >= 32)  sprintf (x_mod, "  %c", myREGEX.mods [s_states [i].rpos]);                          <* 
 *>       else                                     strlcpy (x_mod, "nul", 5);                                                              <* 
 *>       if (myREGEX.text [s_states [i].tpos] >= 32)  sprintf (x_txt, "  %c", myREGEX.text [s_states [i].tpos]);                          <* 
 *>       else                                     strlcpy (x_txt, "nul", 5);                                                              <* 
 *>       yregex_find_text (i, t);                                                                                                         <* 
 *>       printf ("%4d  %4d  %3d  %3d  --  %3d  %s  %3d  %s  %3d  --  %3d  %s  --    %c   %3d  --  %s\n",                                  <* 
 *>             s_states [i].prev, i, s_states [i].begin ,s_states [i].level,                                                              <* 
 *>             s_states [i].rpos, x_reg,                                                                                                  <* 
 *>             myREGEX.indx [s_states [i].rpos], x_mod, myREGEX.jump [s_states [i].rpos],                                                 <* 
 *>             s_states [i].tpos, x_txt,                                                                                                  <* 
 *>             s_states [i].ready, s_states [i].rc,                                                                                       <* 
 *>             t);                                                                                                                        <* 
 *>       ++c;                                                                                                                             <* 
 *>    }                                                                                                                                   <* 
 *>    return 0;                                                                                                                           <* 
 *> }                                                                                                                                      <*/

/*> int                                                                               <* 
 *> yregex_exec_index            (int a_index)                                        <* 
 *> {                                                                                 <* 
 *>    return myREGEX.indx [s_states [a_index].rpos];                                 <* 
 *> }                                                                                 <*/


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

/*> char                                                                                                        <* 
 *> yregex_exec_found_NEW   (int a_index)                                                                       <* 
 *> {                                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                 <* 
 *>    int         i           =    0;                                                                          <* 
 *>    int         p           =   -1;                                                                          <* 
 *>    int         x_rpos      =    0;                                                                          <* 
 *>    uchar       x_reg       =  ' ';                                                                          <* 
 *>    int         x_tpos      =    0;                                                                          <* 
 *>    uchar       x_ch        =  ' ';                                                                          <* 
 *>    uchar       x_mod       =  ' ';                                                                          <* 
 *>    int         x_indx      =    0;                                                                          <* 
 *>    int         x_len       =    0;                                                                          <* 
 *>    char        x_text      [LEN_RECD];                                                                      <* 
 *>    char        x_quan      [LEN_RECD];                                                                      <* 
 *>    char        t           [LEN_RECD];                                                                      <* 
 *>    char        q           [LEN_RECD];                                                                      <* 
 *>    /+---(mark tail)----------------------+/                                                                 <* 
 *>    s_states [a_index].ready = 'W';                                                                          <* 
 *>    s_states [a_index].rc    =  1;                                                                           <* 
 *>    /+---(identify groups)----------------+/                                                                 <* 
 *>    i = a_index;                                                                                             <* 
 *>    while ((i = s_states [i].prev) != p) {                                                                   <* 
 *>       /+---(mark solution)---------------+/                                                                 <* 
 *>       p = i;                                                                                                <* 
 *>       s_states [i].ready = '+';                                                                             <* 
 *>       /+---(get  solution)---------------+/                                                                 <* 
 *>       x_rpos = s_states [i].rpos;                                                                           <* 
 *>       x_reg  = myREGEX.comp [x_rpos];                                                                       <* 
 *>       /+---(text)---------------------------+/                                                              <* 
 *>       x_tpos = s_states [i].tpos;                                                                           <* 
 *>       x_ch   = myREGEX.text [x_tpos];                                                                       <* 
 *>       x_indx = myREGEX.indx [x_rpos] - 1;                                                                   <* 
 *>       if (x_indx == 998)  x_indx = 10;                                                                      <* 
 *>       x_mod  = myREGEX.mods [x_rpos];                                                                       <* 
 *>       /+---(handle grouping)----------------+/                                                              <* 
 *>       switch (x_reg) {                                                                                      <* 
 *>       case ')' : case '|' :                                                                                 <* 
 *>          myREGEX.g_end [x_indx] = x_tpos - 1;                                                               <* 
 *>          break;                                                                                             <* 
 *>       case '(' :                                                                                            <* 
 *>          myREGEX.g_beg [x_indx] = x_tpos;                                                                   <* 
 *>          break;                                                                                             <* 
 *>       default  :                                                                                            <* 
 *>          x_text [x_tpos] = x_ch;                                                                            <* 
 *>          x_quan [x_tpos] = x_mod;                                                                           <* 
 *>          break;                                                                                             <* 
 *>       }                                                                                                     <* 
 *>    }                                                                                                        <* 
 *>    /+---(fill groups)--------------------+/                                                                 <* 
 *>    for (i = 0; i <= 10; ++i) {                                                                              <* 
 *>       /+> printf ("%2d %c\n", i, myREGEX.g_mrk [i]);                                     <+/                <* 
 *>       if (myREGEX.g_mrk [i] == ' ') {                                                                       <* 
 *>          yregex_find_addsub (a_index, i, -1    , ""    , ""    );                                           <* 
 *>          continue;                                                                                          <* 
 *>       }                                                                                                     <* 
 *>       x_len = myREGEX.g_end [i] - myREGEX.g_beg [i] + 1;                                                    <* 
 *>       strlcpy (t, x_text + myREGEX.g_beg [i], x_len + 1);                                                   <* 
 *>       strlcpy (q, x_quan + myREGEX.g_beg [i], x_len + 1);                                                   <* 
 *>       /+> printf ("   %3d %3d %3d [%s] [%s]\n", myREGEX.g_beg [i], myREGEX.g_end [i], x_len, t, q);   <+/   <* 
 *>       if (i == 0)  yregex_find_add (a_index, s_states [a_index].begin, t, q);                               <* 
 *>       yregex_find_addsub (a_index, i, myREGEX.g_beg [i], t, q);                                             <* 
 *>    }                                                                                                        <* 
 *>    /+---(complete)-----------------------+/                                                                 <* 
 *>    return 0;                                                                                                <* 
 *> }                                                                                                           <*/

/*> char                                                                                                            <* 
 *> yregex_exec_sub         (int a_index, int a_paren)                                                              <* 
 *> {                                                                                                               <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                     <* 
 *>    char        rc          =    S_SUB_BEFORE;                                                                   <* 
 *>    char        t           [5] = "";                                                                            <* 
 *>    int         x_rpos      =    0;                                                                              <* 
 *>    int         x_tpos      =    0;                                                                              <* 
 *>    uchar       x_ch        =  ' ';                                                                              <* 
 *>    uchar       x_reg       =  ' ';                                                                              <* 
 *>    uchar       x_mod       =  ' ';                                                                              <* 
 *>    int         x_indx      =    0;                                                                              <* 
 *>    /+---(dig to origin)------------------+/                                                                     <* 
 *>    if (a_index != s_states [a_index].prev) {                                                                    <* 
 *>       /+> printf ("      call deeper\n");                                             <+/                       <* 
 *>       rc = yregex_exec_sub (s_states [a_index].prev, a_paren);                                                  <* 
 *>    } else {                                                                                                     <* 
 *>       /+> printf ("      wiping\n");                                                  <+/                       <* 
 *>       /+> strlcpy (g_subf, "", LEN_TEXT);                                             <*                        <* 
 *>        *> strlcpy (g_subq, "", LEN_TEXT);                                             <+/                       <* 
 *>       g_subb     = -1;                                                                                          <* 
 *>       g_subf [0] = '\0';                                                                                        <* 
 *>       g_subq [0] = '\0';                                                                                        <* 
 *>       rc = S_SUB_BEFORE;                                                                                        <* 
 *>    }                                                                                                            <* 
 *>    /+---(filter)-------------------------+/                                                                     <* 
 *>    if (s_states [a_index].ready == 'W')  return rc;                                                             <* 
 *>    if (rc >= S_SUB_AFTER)                return rc;                                                             <* 
 *>    /+---(text)---------------------------+/                                                                     <* 
 *>    x_tpos = s_states [a_index].tpos;                                                                            <* 
 *>    x_ch   = myREGEX.text [x_tpos];                                                                              <* 
 *>    /+---(quantifiers)--------------------+/                                                                     <* 
 *>    x_rpos = s_states [a_index].rpos;                                                                            <* 
 *>    x_reg  = myREGEX.comp [x_rpos];                                                                              <* 
 *>    x_indx = myREGEX.indx [x_rpos];                                                                              <* 
 *>    x_mod  = myREGEX.mods [x_rpos];                                                                              <* 
 *>    /+> printf ("   rpos %-2d, reg %c, indx %-2d, mod %c, rc %-2d\n", x_rpos, x_reg, x_indx, x_mod, rc);   <+/   <* 
 *>    /+---(check for close)----------------+/                                                                     <* 
 *>    if (strchr ("|)", x_reg) != NULL  && x_indx == a_paren) {                                                    <* 
 *>       /+> printf ("      close paren\n");                                             <+/                       <* 
 *>       return S_SUB_AFTER;                                                                                       <* 
 *>    }                                                                                                            <* 
 *>    /+---(check for open)-----------------+/                                                                     <* 
 *>    if (strchr ("(" , x_reg) != NULL  && x_indx == a_paren) {                                                    <* 
 *>       /+> printf ("      open paren\n");                                              <+/                       <* 
 *>       if (g_subb == -1)  g_subb = x_tpos;                                                                       <* 
 *>       return S_SUB_INSIDE;                                                                                      <* 
 *>    }                                                                                                            <* 
 *>    if (rc <= S_SUB_BEFORE) {                                                                                    <* 
 *>       /+> printf ("      skipping\n");                                                <+/                       <* 
 *>       return rc;                                                                                                <* 
 *>    }                                                                                                            <* 
 *>    /+---(handle sets)--------------------+/                                                                     <* 
 *>    if (x_reg == '[') {                                                                                          <* 
 *>       sprintf (t, "%c", x_ch);                                                                                  <* 
 *>       strlcat (g_subf, t, LEN_TEXT);                                                                            <* 
 *>       sprintf (t, "%c", x_mod);                                                                                 <* 
 *>       strlcat (g_subq, t, LEN_TEXT);                                                                            <* 
 *>       return rc;                                                                                                <* 
 *>    }                                                                                                            <* 
 *>    /+---(filter other specials)----------+/                                                                     <* 
 *>    if (x_indx > 0)      return rc;      /+ avoid grouping +/                                                    <* 
 *>    /+---(append result)------------------+/                                                                     <* 
 *>    sprintf (t, "%c", x_ch);                                                                                     <* 
 *>    strlcat (g_subf, t, LEN_TEXT);                                                                               <* 
 *>    sprintf (t, "%c", x_mod);                                                                                    <* 
 *>    strlcat (g_subq, t, LEN_TEXT);                                                                               <* 
 *>    /+---(complete)-----------------------+/                                                                     <* 
 *>    return rc;                                                                                                   <* 
 *> }                                                                                                               <*/

/*> int                                                                                                                   <* 
 *> yregex_exec_tpos        (int a_index, int a_paren, int *a_tbeg, int *a_tend)                                          <* 
 *> {                                                                                                                     <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                           <* 
 *>    int         rc          =   -1;                                                                                    <* 
 *>    int         x_tpos      =    0;                                                                                    <* 
 *>    uchar       x_ch        =  ' ';                                                                                    <* 
 *>    int         x_rpos      =    0;                                                                                    <* 
 *>    uchar       x_reg       =  ' ';                                                                                    <* 
 *>    int         x_indx      =    0;                                                                                    <* 
 *>    uchar       x_mod       =  ' ';                                                                                    <* 
 *>    /+---(text)---------------------------+/                                                                           <* 
 *>    /+> printf ("   index %-3d, paren %-2d, tbeg %-2d, tend %-2d\n", a_index, a_paren, *a_tbeg, *a_tend);   <+/        <* 
 *>    x_tpos = s_states [a_index].tpos;                                                                                  <* 
 *>    /+---(quantifiers)--------------------+/                                                                           <* 
 *>    x_rpos = s_states [a_index].rpos;                                                                                  <* 
 *>    x_reg  = myREGEX.comp [x_rpos];                                                                                    <* 
 *>    x_indx = myREGEX.indx [x_rpos];                                                                                    <* 
 *>    x_mod  = myREGEX.mods [x_rpos];                                                                                    <* 
 *>    /+> printf ("   tpos %-2d, rpos %-2d, reg %c, indx %-2d, mod %c\n", x_tpos, x_rpos, x_reg, x_indx, x_mod);   <+/   <* 
 *>    /+---(check for last marker)----------+/                                                                           <* 
 *>    if (strchr ("|)", x_reg) != NULL && x_indx == a_paren) {                                                           <* 
 *>       /+> printf ("      found CLOSE at %d\n", x_tpos);                               <+/                             <* 
 *>       *a_tend = x_tpos;                                                                                               <* 
 *>       rc = 1;                                                                                                         <* 
 *>    }                                                                                                                  <* 
 *>    /+---(check for paren)----------------+/                                                                           <* 
 *>    if (strchr ("(", x_reg) != NULL && x_indx == a_paren) {                                                            <* 
 *>       /+> printf ("      found OPEN/OR at %d\n", x_tpos);                             <+/                             <* 
 *>       *a_tbeg = x_tpos;                                                                                               <* 
 *>       rc = 2;                                                                                                         <* 
 *>    }                                                                                                                  <* 
 *>    /+---(dig to origin)------------------+/                                                                           <* 
 *>    else if (a_index != s_states [a_index].prev) {                                                                     <* 
 *>       /+> printf ("      call deeper\n");                                             <+/                             <* 
 *>       rc = yregex_exec_tpos (s_states [a_index].prev, a_paren, a_tbeg, a_tend);                                       <* 
 *>    }                                                                                                                  <* 
 *>    /+> printf ("      done with %d\n", rc);                                           <+/                             <* 
 *>    /+---(complete)-----------------------+/                                                                           <* 
 *>    return rc;                                                                                                         <* 
 *> }                                                                                                                     <*/

/*> char                                                                                        <* 
 *> yregex_exec__found      (int a_index)                                                       <* 
 *> {                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *>    char        rc          =    0;                                                          <* 
 *>    char        t           [5] = "";                                                        <* 
 *>    int         x_rpos      =    0;                                                          <* 
 *>    int         x_tpos      =    0;                                                          <* 
 *>    uchar       x_ch        =  ' ';                                                          <* 
 *>    uchar       x_reg       =  ' ';                                                          <* 
 *>    uchar       x_mod       =  ' ';                                                          <* 
 *>    int         x_indx      =    0;                                                          <* 
 *>    /+---(dig to origin)------------------+/                                                 <* 
 *>    if (a_index != s_states [a_index].prev) {                                                <* 
 *>       rc = yregex_exec__found (s_states [a_index].prev);                                    <* 
 *>    } else {                                                                                 <* 
 *>       /+> strlcpy (g_found, "", LEN_TEXT);                                            <*    <* 
 *>        *> strlcpy (g_quans, "", LEN_TEXT);                                            <+/   <* 
 *>       g_found [0] = '\0';                                                                   <* 
 *>       g_quans [0] = '\0';                                                                   <* 
 *>    }                                                                                        <* 
 *>    /+---(filter)-------------------------+/                                                 <* 
 *>    if (rc > 0)                           return rc;                                         <* 
 *>    if (s_states [a_index].ready == 'W')  return 1;                                          <* 
 *>    /+---(mark)---------------------------+/                                                 <* 
 *>    s_states [a_index].ready = '+';                                                          <* 
 *>    /+---(text)---------------------------+/                                                 <* 
 *>    x_tpos = s_states [a_index].tpos;                                                        <* 
 *>    x_ch   = myREGEX.text [x_tpos];                                                          <* 
 *>    /+---(quantifiers)--------------------+/                                                 <* 
 *>    x_rpos = s_states [a_index].rpos;                                                        <* 
 *>    x_reg  = myREGEX.comp [x_rpos];                                                          <* 
 *>    x_indx = myREGEX.indx [x_rpos];                                                          <* 
 *>    x_mod  = myREGEX.mods [x_rpos];                                                          <* 
 *>    /+---(find start of rules)------------+/                                                 <* 
 *>    if (x_reg == ';' && x_indx > 0) {                                                        <* 
 *>       return 1;                                                                             <* 
 *>    }                                                                                        <* 
 *>    /+---(handle sets)--------------------+/                                                 <* 
 *>    if (x_reg == '[') {                                                                      <* 
 *>       sprintf (t, "%c", x_ch);                                                              <* 
 *>       strlcat (g_found, t, LEN_TEXT);                                                       <* 
 *>       sprintf (t, "%c", x_mod);                                                             <* 
 *>       strlcat (g_quans, t, LEN_TEXT);                                                       <* 
 *>       return 0;                                                                             <* 
 *>    }                                                                                        <* 
 *>    /+---(filter other specials)----------+/                                                 <* 
 *>    if (x_indx > 0)  return 0;          /+ avoid grouping +/                                 <* 
 *>    /+---(append result)------------------+/                                                 <* 
 *>    sprintf (t, "%c", x_ch);                                                                 <* 
 *>    strlcat (g_found, t, LEN_TEXT);                                                          <* 
 *>    sprintf (t, "%c", x_mod);                                                                <* 
 *>    strlcat (g_quans, t, LEN_TEXT);                                                          <* 
 *>    /+---(complete)-----------------------+/                                                 <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/



/*===============================[[ end code ]]===============================*/
