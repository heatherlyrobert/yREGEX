/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"

/*> c  =  ,x···0·vf"··hd··f"··lD··0i   { BASE_ENTRY, '-', ¥··A         , 0 , ¥··40|··dw··0··,y   <*/
/*> d  =  ,x···0·vf"··hd··$hD··k··dd··kÕJ··A                                                                                                                                                                   , 0, NULL, NULL },¥··204|··dw··0··j·dd·dd·k··,y   <*/


/*---(patterns)-------------*/
#define     MAX_PATS       20
static const tPATS       s_pats [MAX_PATS] = {
   /*                  0         1            0         1         2         3         4         5         6         7         8         9         A         B         C         D         E         F                  */
   /*            1234  01234567890123456789   01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890        */
   /*--source--  abbr  ---name-------------   ---pattern-------------------------------------------------------------------------------------------------------------------------------------------------------  ln sz */
   { BASE_ENTRY, 'f', "float"          , 0 , "(+|-)?(0|[1-9][0-9]*)([.][0-9]+)?"                                                                                                                           , 0, NULL, NULL },
   { BASE_ENTRY, 'b', "byte"           , 0 , "25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9]"                                                                                                            , 0, NULL, NULL },
   { BASE_ENTRY, 'i', "int"            , 0 , "(+|-)?(0|[1-9][0-9]*)"                                                                                                                                       , 0, NULL, NULL },
   { BASE_ENTRY, 'w', "word"           , 0 , "<\\w*>"                                                                                                                                                      , 0, NULL, NULL },
   { BASE_ENTRY, 'F', "field"          , 0 , "\\F*\\f"                                                                                                                                                     , 0, NULL, NULL },
   { BASE_ENTRY, '-', "path"           , 0 , "[/]?[A-Za-z][/A-Za-z0-9_.-]*"                                                                                                                                , 0, NULL, NULL },
   { BASE_ENTRY, '-', "mypath"         , 0 , "[/]?[A-Za-z][/a-zA-Z0-9_.]*"                                                                                                                                 , 0, NULL, NULL },
   { BASE_ENTRY, '-', "email"          , 0 , "[A-Za-z0-9_.-]+[@][A-Za-z0-9_.-]+.[A-Za-z]{2,4}"                                                                                                             , 0, NULL, NULL },
   { BASE_ENTRY, '-', "file"           , 0 , "[.]?[A-Za-z][A-Za-z0-9_.-]{0,62}[A-Za-z0-9]"                                                                                                                 , 0, NULL, NULL },
   { BASE_ENTRY, '-', "phone"          , 0 , "([(]?[2-9][0-9]{2}[)]?[-. ])?[0-9]{3}[-. ][0-9]{4}"                                                                                                          , 0, NULL, NULL },
   { BASE_ENTRY, '-', "zip"            , 0 , "[1-9][0-9]{4}([-][0-9]{4})?"                                                                                                                                 , 0, NULL, NULL },
   { BASE_ENTRY, '-', "ip"             , 0 , "(&b)\\.(&b)\\.(&b)\\.(&b)"                                                                                                                                   , 0, NULL, NULL },
   { BASE_ENTRY, '-', "alnum"          , 0 , "^[a-zA-Z0-9]+$"                                                                                                                                              , 0, NULL, NULL },
   { BASE_ENTRY, '-', "basic"          , 0 , "^[A-Za-z0-9][a-zA-Z0-9_ -]*$"                                                                                                                                , 0, NULL, NULL },
   { BASE_ENTRY, '-', "punct"          , 0 , "^[A-Za-z0-9][A-Za-z0-9_ .,:;!?-]*$"                                                                                                                          , 0, NULL, NULL },
   { BASE_ENTRY, '-', "exten"          , 0 , "^[A-Za-z0-9][A-Za-z0-9_ .,:;@()-]*$"                                                                                                                         , 0, NULL, NULL },
   { BASE_ENTRY, '-', "field"          , 0 , "^[a-z][a-z0-9_]{0,10}[a-z0-9]$"                                                                                                                              , 0, NULL, NULL },
   { BASE_ENTRY, '-', "string"         , 0 , "^[A-Za-z0-9][A-Za-z0-9+=&%][A-Za-z0-9]*$"                                                                                                                    , 0, NULL, NULL },
   { 0         , 0  , NULL             , 0 , NULL                                                                                                                                                          , 0, NULL, NULL },
};

/*---(static.vars)------+-----------+-*//*-+----------------------------------*/
static      tPATS      *s_head      = NULL;        /* head of list                 */
static      tPATS      *s_tail      = NULL;        /* tail of list                 */
static      tPATS      *s_curr      = NULL;        /* curent cursor                */
static      int         s_count     =    0;        /* count of sets                */

static      char        s_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char*
yregex_pats__memory     (void *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   tPATS      *x_cur       = NULL;
   /*---(cast)---------------------------*/
   x_cur = (tPATS *) a_cur;
   /*---(defense)------------------------*/
   if (x_cur == NULL) {
      strlcpy (s_print, "n/a", LEN_RECD);
      return s_print;
   }
   /*---(defense)------------------------*/
   strlcpy (s_print, "å_.___.__.__æ", LEN_RECD);
   ++n;  if (x_cur->source      != '-')         s_print [n] = 'X';
   ++n;
   ++n;  if (x_cur->abbr        != '-')         s_print [n] = 'X';
   ++n;  if (x_cur->name        != NULL)        s_print [n] = 'X';
   ++n;  if (x_cur->nlen        != 0)           s_print [n] = 'X';
   ++n;
   ++n;  if (x_cur->pat         != NULL)        s_print [n] = 'X';
   ++n;  if (x_cur->plen        != 0)           s_print [n] = 'X';
   ++n;
   ++n;  if (x_cur->m_prev      != NULL)        s_print [n] = 'X';
   ++n;  if (x_cur->m_next      != NULL)        s_print [n] = 'X';
   return s_print;
}

char
yregex_pats__wipe       (void *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   tPATS      *x_cur       = NULL;
   /*---(cast)---------------------------*/
   x_cur = (tPATS *) a_cur;
   /*---(wipe)---------------------------*/
   x_cur->source   = '-';
   x_cur->abbr     = '-';
   x_cur->name     = NULL;
   x_cur->nlen     = 0;
   x_cur->pat      = NULL;
   x_cur->plen     = 0;
   x_cur->m_prev   = NULL;
   x_cur->m_next   = NULL;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char yregex_pats__new   (void **r_new) { return yregex_share_new  (TYPE_PATS, r_new, &s_head, &s_tail, &s_count); }
char yregex_pats__free  (void **r_old) { return yregex_share_free (TYPE_PATS, r_old, &s_head, &s_tail, &s_count); }



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char yregex_pats_init    (void) { return yregex_share_init  (TYPE_PATS, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_pats__purge  (void) { return yregex_share_purge (TYPE_PATS, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_pats_wrap    (void) { return yregex_share_wrap  (TYPE_PATS, &s_head, &s_tail, &s_curr, &s_count); }

char         /*-> tbd --------------------------------[ leaf   [fz.531.021.10]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_pats_reset       (void)
{
   yregex_pats__purge ();
   yregex_pats__base  ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       creating new sets                      ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE__________________o (void) {;}

char
yregex_pats__base       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   tPATS      *x_new       = NULL;
   char        t           [LEN_LABEL];
   int         j           =    0;
   /*---(defense)------------------------*/
   if (s_head != NULL)   return 0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(walk base)----------------------*/
   for (i = 0; i < MAX_PATS; ++i) {
      /*---(check for end)---------------*/
      if (s_pats [i].abbr == 0)  break;
      /*---(add a new one)---------------*/
      x_new = NULL;
      rc = yregex_pats__new (&x_new);
      if (x_new == NULL)  continue;
      /*---(populate)--------------------*/
      x_new->source   = s_pats [i].source;
      x_new->abbr     = s_pats [i].abbr;
      x_new->name     = s_pats [i].name;
      x_new->nlen     = strlen (s_pats [i].name);
      x_new->pat      = s_pats [i].pat;
      x_new->plen     = strlen (s_pats [i].pat);
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fe.943.034.30]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_pats__save       (cchar *a_pattern, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   tPATS      *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   x_len = strllen (a_pattern, LEN_PAT );
   DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len  <  1) {
      DEBUG_YREGEX  yLOG_note   ("too short");
      DEBUG_YREGEX  yLOG_exitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len  >= LEN_PAT) {
      DEBUG_YREGEX  yLOG_note   ("too long");
      DEBUG_YREGEX  yLOG_exitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(add a new one)------------------*/
   rc = yregex_pats__new (&x_new);
   DEBUG_YREGEX  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->source = 's';
   x_new->abbr   = '0' + a_num;
   x_new->pat    = strdup (a_pattern);
   x_new->plen   = strlen (a_pattern);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return s_count - 1;
}



/*====================------------------------------------====================*/
/*===----                      finding patterns                        ----===*/
/*====================------------------------------------====================*/
static void      o___FINDING_________________o (void) {;}

char yregex_pats__by_cursor  (char a_move , tPATS  **r_back) { return yregex_share__by_cursor (TYPE_PATS, &s_head, &s_tail, &s_curr, r_back, a_move); }
char yregex_pats__by_index   (int a_index , tPATS  **r_back) { return yregex_share__by_index  (TYPE_PATS, &s_head, &s_curr, r_back, a_index); }
int  yregex_pats__by_abbr    (char a_abbr , tPATS  **r_back) { return yregex_share__by_abbr   (TYPE_PATS, &s_head, r_back, a_abbr); }
int  yregex_pats__by_name    (char *a_name, tPATS  **r_back) { return yregex_share__by_name   (TYPE_PATS, &s_head, r_back, a_name); }


/*> int          /+-> retrieve pattern by abbeviation ----[ leaf   [fc.632.122.40]+/ /+-[01.0000.01#.8]-+/ /+-[--.---.---.--]-+/   <* 
 *> yregex_pats__by_abbr    (cchar a_abbr, tPATS **r_pat)                                                                          <* 
 *> {                                                                                                                              <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                    <* 
 *>    char        rce         =  -10;                                                                                             <* 
 *>    int         n           =    0;                                                                                             <* 
 *>    char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";                                 <* 
 *>    tPATS      *x_curr      = NULL;                                                                                             <* 
 *>    /+---(header)-------------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);                                                                                  <* 
 *>    DEBUG_YREGEX  yLOG_sint    (a_abbr);                                                                                        <* 
 *>    /+---(default)------------------------+/                                                                                    <* 
 *>    if (r_pat != NULL)  *r_pat = NULL;                                                                                          <* 
 *>    /+---(defense)------------------------+/                                                                                    <* 
 *>    --rce;  if (a_abbr == 0) {                                                                                                  <* 
 *>       DEBUG_YREGEX  yLOG_snote   ("can not be null");                                                                          <* 
 *>       DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    --rce;  if (strchr (x_valid, a_abbr) == NULL) {                                                                             <* 
 *>       DEBUG_YREGEX  yLOG_snote   ("abbr must be [A-Za-z]");                                                                    <* 
 *>       DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    DEBUG_YREGEX  yLOG_schar   (a_abbr);                                                                                        <* 
 *>    /+---(walk through sets)--------------+/                                                                                    <* 
 *>    x_curr = s_head;                                                                                                            <* 
 *>    while (x_curr != NULL) {                                                                                                    <* 
 *>       if (x_curr->abbr == a_abbr)  break;                                                                                      <* 
 *>       ++n;                                                                                                                     <* 
 *>       x_curr = x_curr->m_next;                                                                                                 <* 
 *>    }                                                                                                                           <* 
 *>    /+---(check)--------------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_spoint  (x_curr);                                                                                        <* 
 *>    --rce;  if (x_curr == NULL) {                                                                                               <* 
 *>       DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    /+---(saveback)-----------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_snote   ("found");                                                                                       <* 
 *>    if (r_pat != NULL)  *r_pat = x_curr;                                                                                        <* 
 *>    /+---(complete)-----------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);                                                                                  <* 
 *>    return n;                                                                                                                   <* 
 *> }                                                                                                                              <*/

/*> int          /+-> retrieve pattern by name -----------[ leaf   [fe.A53.145.A0]+/ /+-[01.0000.02#.E]-+/ /+-[--.---.---.--]-+/   <* 
 *> yregex_pats__by_name    (cchar *a_name, tPATS **r_pat)                                                                         <* 
 *> {                                                                                                                              <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                    <* 
 *>    char        rce         =  -10;                                                                                             <* 
 *>    int         x_len       =    0;                                                                                             <* 
 *>    int         n           =    0;                                                                                             <* 
 *>    tPATS      *x_curr      = NULL;                                                                                             <* 
 *>    /+---(header)-------------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_senter   (__FUNCTION__);                                                                                 <* 
 *>    DEBUG_YREGEX  yLOG_spoint   (a_name);                                                                                       <* 
 *>    /+---(default)------------------------+/                                                                                    <* 
 *>    if (r_pat != NULL)  *r_pat = NULL;                                                                                          <* 
 *>    /+---(defense)------------------------+/                                                                                    <* 
 *>    --rce;  if (a_name == NULL) {                                                                                               <* 
 *>       DEBUG_YREGEX  yLOG_sexitr   (__FUNCTION__, rce);                                                                         <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    DEBUG_YREGEX  yLOG_snote    (a_name);                                                                                       <* 
 *>    x_len = strllen (a_name, LEN_NAME);                                                                                         <* 
 *>    DEBUG_YREGEX  yLOG_sint     (x_len);                                                                                        <* 
 *>    --rce;  if (x_len <  2) {                                                                                                   <* 
 *>       DEBUG_YREGEX  yLOG_snote    ("too short");                                                                               <* 
 *>       DEBUG_YREGEX  yLOG_sexitr   (__FUNCTION__, rce);                                                                         <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    --rce;  if (x_len >  15) {                                                                                                  <* 
 *>       DEBUG_YREGEX  yLOG_snote    ("too long");                                                                                <* 
 *>       DEBUG_YREGEX  yLOG_sexitr   (__FUNCTION__, rce);                                                                         <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    /+---(walk through sets)--------------+/                                                                                    <* 
 *>    x_curr = s_head;                                                                                                            <* 
 *>    while (x_curr != NULL) {                                                                                                    <* 
 *>       if (strcmp (x_curr->name, a_name) == 0)  break;                                                                          <* 
 *>       ++n;                                                                                                                     <* 
 *>       x_curr = x_curr->m_next;                                                                                                 <* 
 *>    }                                                                                                                           <* 
 *>    /+---(check)--------------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_spoint  (x_curr);                                                                                        <* 
 *>    --rce;  if (x_curr == NULL) {                                                                                               <* 
 *>       DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    /+---(saveback)-----------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_snote   ("found");                                                                                       <* 
 *>    if (r_pat != NULL)  *r_pat = x_curr;                                                                                        <* 
 *>    /+---(complete)-----------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);                                                                                  <* 
 *>    return n;                                                                                                                   <* 
 *> }                                                                                                                              <*/



/*====================------------------------------------====================*/
/*===----                       compilation support                    ----===*/
/*====================------------------------------------====================*/
static void      o___COMPILE_________________o (void) {;}

/*> char         /+-> compile a pattern ------------------[ ------ [fe.D54.156.65]+/ /+-[02.0000.01#.!]-+/ /+-[--.---.---.--]-+/   <* 
 *> yregex_pats__abbr_ref   (int *a_rpos)                                                                                          <* 
 *> {                                                                                                                              <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                    <* 
 *>    char        rce         =  -10;                                                                                             <* 
 *>    char        rc          =   -1;                                                                                             <* 
 *>    int         i           =    0;                                                                                             <* 
 *>    int         x_pat       =    0;                                                                                             <* 
 *>    char        x_abbr      =  ' ';                                                                                             <* 
 *>    char        x_ch        =  ' ';                                                                                             <* 
 *>    char        x_pch       =    0;                                                                                             <* 
 *>    char        x_ppch      =    0;                                                                                             <* 
 *>    /+---(header)-------------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);                                                                                  <* 
 *>    DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);                                                                         <* 
 *>    x_ch   = myREGEX.orig [*a_rpos];                                                                                            <* 
 *>    DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);                                                                            <* 
 *>    --rce;  if (x_ch != '&') {                                                                                                  <* 
 *>       yregex_error_add ('F', CAT_PAT, 0, 0, "no lead ampersand (&´)");                                                         <* 
 *>       DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    if (*a_rpos > 0)   x_pch  = myREGEX.orig [*a_rpos - 1];                                                                     <* 
 *>    if (*a_rpos > 1)   x_ppch = myREGEX.orig [*a_rpos - 2];                                                                     <* 
 *>    /+---(find name)----------------------+/                                                                                    <* 
 *>    ++(*a_rpos);                                                                                                                <* 
 *>    x_abbr   = myREGEX.orig [*a_rpos];                                                                                          <* 
 *>    /+---(abbreviated name)---------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_note    ("using abbreviated name");                                                                      <* 
 *>    x_pat = yregex_pats__by_abbr (x_abbr, NULL);                                                                                <* 
 *>    DEBUG_YREGEX  yLOG_value   ("x_pat"     , x_pat);                                                                           <* 
 *>    if (x_pat < 0) {                                                                                                            <* 
 *>       yregex_error_add ('F', CAT_PAT, 0, 0, "not valid pattern abbreviation");                                                 <* 
 *>       ++(*a_rpos);                                                                                                             <* 
 *>       strlcat (myREGEX.regex, CAT_PAT, LEN_REGEX);                                                                             <* 
 *>       DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    /+---(full name)----------------------+/                                                                                    <* 
 *>    ++(*a_rpos);                                                                                                                <* 
 *>    x_ch   = myREGEX.orig [*a_rpos];                                                                                            <* 
 *>    if        (x_pch  == '(' && x_ch  == ')') {                                                                                 <* 
 *>       strlcat (myREGEX.regex, s_pats [x_pat].pat, LEN_REGEX);                                                                  <* 
 *>    } else if (x_ppch == '(' && x_pch == '#' && x_ch == ')') {                                                                  <* 
 *>       strlcat (myREGEX.regex, s_pats [x_pat].pat, LEN_REGEX);                                                                  <* 
 *>    } else {                                                                                                                    <* 
 *>       strlcat (myREGEX.regex, "("               , LEN_REGEX);                                                                  <* 
 *>       strlcat (myREGEX.regex, s_pats [x_pat].pat, LEN_REGEX);                                                                  <* 
 *>       strlcat (myREGEX.regex, ")"               , LEN_REGEX);                                                                  <* 
 *>    }                                                                                                                           <* 
 *>    /+---(complete)-----------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);                                                                                  <* 
 *>    return 1;                                                                                                                   <* 
 *> }                                                                                                                              <*/

/*> char         /+-> compile a pattern ------------------[ ------ [fe.D54.156.65]+/ /+-[02.0000.01#.!]-+/ /+-[--.---.---.--]-+/   <* 
 *> yregex_pats__named_ref  (int *a_rpos)                                                                                          <* 
 *> {                                                                                                                              <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                    <* 
 *>    char        rce         =  -10;                                                                                             <* 
 *>    char        rc          =   -1;                                                                                             <* 
 *>    int         i           =    0;                                                                                             <* 
 *>    int         x_pat       =    0;                                                                                             <* 
 *>    char        x_name      [LEN_NAME] = "";                                                                                    <* 
 *>    char        x_ch        =  ' ';                                                                                             <* 
 *>    int         x_len       =    0;                                                                                             <* 
 *>    int         x_beg       =   -1;                                                                                             <* 
 *>    /+---(header)-------------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);                                                                                  <* 
 *>    DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);                                                                         <* 
 *>    x_ch   = myREGEX.orig [*a_rpos];                                                                                            <* 
 *>    DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);                                                                            <* 
 *>    --rce;  if (x_ch != '&') {                                                                                                  <* 
 *>       yregex_error_add ('F', CAT_PAT, 0, 0, "does not lead with an ampersand");                                                <* 
 *>       DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    x_beg  = *a_rpos;                                                                                                           <* 
 *>    /+---(find name)----------------------+/                                                                                    <* 
 *>    ++(*a_rpos);                                                                                                                <* 
 *>    --rce;  for (i = 0; i < LEN_NAME; ++i) {                                                                                    <* 
 *>       x_ch   = myREGEX.orig [*a_rpos + i];                                                                                     <* 
 *>       DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);                                                                         <* 
 *>       if (x_ch == ')')  break;                                                                                                 <* 
 *>       x_name [i]     = x_ch;                                                                                                   <* 
 *>       x_name [i + 1] = 0;                                                                                                      <* 
 *>       DEBUG_YREGEX  yLOG_info    ("x_name"    , x_name);                                                                       <* 
 *>       ++x_len;                                                                                                                 <* 
 *>    }                                                                                                                           <* 
 *>    /+---(troubles)-----------------------+/                                                                                    <* 
 *>    --rce;  if (x_len == 0) {                                                                                                   <* 
 *>       yregex_error_add ('F', CAT_PAT, 0, 0, "could not parse name");                                                           <* 
 *>       DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    --rce;  if (x_ch  != ')') {                                                                                                 <* 
 *>       yregex_error_add ('F', CAT_PAT, 0, 0, "could not find close paren");                                                     <* 
 *>       DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    /+---(abbreviated name)---------------+/                                                                                    <* 
 *>    --rce;  if (x_len == 1) {                                                                                                   <* 
 *>       DEBUG_YREGEX  yLOG_note    ("using abbreviated name");                                                                   <* 
 *>       x_pat = yregex_pats__by_abbr (x_name [0], NULL);                                                                         <* 
 *>       DEBUG_YREGEX  yLOG_value   ("x_pat"     , x_pat);                                                                        <* 
 *>       if (x_pat < 0) {                                                                                                         <* 
 *>          yregex_error_add ('F', CAT_PAT, 0, 0, "not a valid pattern abbreviation");                                            <* 
 *>          ++(*a_rpos);                                                                                                          <* 
 *>          strlcat (myREGEX.regex, CAT_PAT, LEN_REGEX);                                                                          <* 
 *>          DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);                                                                       <* 
 *>          return rce;                                                                                                           <* 
 *>       }                                                                                                                        <* 
 *>       ++(*a_rpos);                                                                                                             <* 
 *>       strlcat (myREGEX.regex, s_pats [x_pat].pat, LEN_REGEX);                                                                  <* 
 *>       DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);                                                                               <* 
 *>       return 1;                                                                                                                <* 
 *>    }                                                                                                                           <* 
 *>    /+---(full name)----------------------+/                                                                                    <* 
 *>    --rce;                                                                                                                      <* 
 *>    DEBUG_YREGEX  yLOG_note    ("trying pattern name");                                                                         <* 
 *>    x_pat = yregex_pats__by_name (x_name, NULL);                                                                                <* 
 *>    DEBUG_YREGEX  yLOG_value   ("x_pat"     , x_pat);                                                                           <* 
 *>    if (x_pat < 0) {                                                                                                            <* 
 *>       yregex_error_add ('F', CAT_PAT, 0, 0, "not a valid pattern name");                                                       <* 
 *>       *a_rpos += x_len;                                                                                                        <* 
 *>       strlcat (myREGEX.regex, CAT_PAT, LEN_REGEX);                                                                             <* 
 *>       DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);                                                                          <* 
 *>       return rce;                                                                                                              <* 
 *>    }                                                                                                                           <* 
 *>    /+---(full name)----------------------+/                                                                                    <* 
 *>    *a_rpos += x_len;                                                                                                           <* 
 *>    strlcat (myREGEX.regex, s_pats [x_pat].pat, LEN_REGEX);                                                                     <* 
 *>    /+---(complete)-----------------------+/                                                                                    <* 
 *>    DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);                                                                                  <* 
 *>    return 1;                                                                                                                   <* 
 *> }                                                                                                                              <*/

char
yregex_pats__replace    (char *a_src, char a_run)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   int         l           =    0;
   uchar       x_char      =  ' ';          /* curr character                 */
   uchar       x_prev      =  ' ';          /* prev character                 */
   uchar       x_next      =  ' ';          /* prev-prev character            */
   uchar       x_far       =  ' ';          /* prev-prev character            */
   int         x_len       =    0;
   char        t           [LEN_REGEX] = "";
   char        x_done      =  '-';
   char        x_name      [LEN_LABEL] = "";
   tPATS      *x_pat       = NULL;
   char        x_dst       [LEN_REGEX] = "";
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (a_src);
   DEBUG_YREGEX  yLOG_complex ("a_src"     , "%3då%sæ", l, a_src);
   --rce;  if (l <= 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (x_dst, "", LEN_REGEX);
   /*---(walk regex)---------------------*/
   --rce;  for (i = 0; i < l; ++i) {
      /*---(prepare)---------------------*/
      if (i > 0)  x_prev = a_src [i - 1];
      x_char = a_src [i];
      x_next = a_src [i + 1];
      x_far  = a_src [i + 2];
      DEBUG_YREGEX  yLOG_complex ("LOOP"      , "%3d, %c, %c, %c", i, x_prev, x_char, x_next);
      sprintf (t, "%c", x_char);
      /*---(filter)----------------------*/
      if (x_prev != '(')  { strlcat (x_dst, t, LEN_REGEX);  continue; }
      if (x_char != '&')  { strlcat (x_dst, t, LEN_REGEX);  continue; }
      /*---(abbr)------------------------*/
      if (x_far == ')') {
         DEBUG_YREGEX  yLOG_note    ("finding an abbreviation-based pattern");
         if (a_run == 0) {
            if (strchr (YSTR_NUMBER, x_next) != NULL) {
               DEBUG_YREGEX  yLOG_note    ("named, skipping in normal run");
               strlcat (x_dst, t, LEN_REGEX);
               continue;
            }
            if (strchr (YSTR_UPLOW, x_next) == NULL) {
               yregex_error_add ('F', CAT_PAT, i - 1, 4, "invalid pattern abbreviation");
               DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
               return rce;
            }
         } else {
            if (strchr (YSTR_CHARS, x_next) == NULL) {
               yregex_error_add ('F', CAT_PAT, i - 1, 4, "invalid pattern abbreviation");
               DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
               return rce;
            }
         }
         yregex_pats__by_abbr (x_next, &x_pat);
         if (x_pat == NULL) {
            yregex_error_add ('F', CAT_PAT, i - 1, 4, "pattern abbreviation not found");
            DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         strlcat (x_dst, x_pat->pat, LEN_REGEX);
         ++i;
         continue;
      }
      /*---(named)-----------------------*/
      DEBUG_YREGEX  yLOG_note    ("finding a name-based pattern");
      x_done = '-';
      x_len  = 0;
      strlcpy (x_name, "", LEN_LABEL);
      for (j = i + 1; j <= i + 11; ++j) {
         if (a_src [j] == ')')  { x_done = 'y'; break; }
         if (strchr (YSTR_ALNUM, a_src [j]) == NULL)  break;
         sprintf (t, "%c", a_src [j]);
         strlcat (x_name, t, LEN_LABEL);
         ++x_len;
      }
      DEBUG_YREGEX  yLOG_info    ("x_name"    , x_name);
      if (x_done != 'y') {
         if (x_len >= 10)  yregex_error_add ('F', CAT_PAT, i, 10, "pattern name too long (>10)");
         else              yregex_error_add ('F', CAT_PAT, j,  1, "illegal pattern name character");
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yregex_pats__by_name (x_name, &x_pat);
      DEBUG_YREGEX  yLOG_point   ("x_pat"     , x_pat);
      if (x_pat == NULL) {
         yregex_error_add ('F', CAT_PAT, i - 1, x_len + 3, "pattern name not found");
         DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      strlcat (x_dst, x_pat->pat, LEN_REGEX);
      i += x_len;
      continue;
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   strlcpy (myREGEX.regex, x_dst, LEN_REGEX);
   myREGEX.rlen = strllen (myREGEX.regex, LEN_REGEX);
   DEBUG_YREGEX  yLOG_complex ("regex"     , "%3då%sæ", myREGEX.rlen, myREGEX.regex);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yregex_pats__named      (char *a_src)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   int         j           =    0;
   uchar       x_char      =  ' ';          /* curr character                 */
   uchar       x_prev      =  ' ';          /* prev character                 */
   uchar       x_next      =  ' ';          /* next character                 */
   int         x_len       =    0;
   char        r           [LEN_LABEL] = "";
   char        s           [LEN_LABEL] = "";
   char        t           [LEN_REGEX] = "";
   int         x_beg       =    0;
   int         x_end       =    0;
   int         n           =    1;
   int         x_num       =    0;
   int         x_nest      =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (a_src);
   DEBUG_YREGEX  yLOG_complex ("a_src"     , "%3då%sæ", l, a_src);
   --rce;  if (l <= 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk regex)---------------------*/
   --rce;  for (i = 0; i < l; ++i) {
      /*---(prepare)---------------------*/
      if (i > 0)  x_prev = a_src [i - 1];
      x_char = a_src [i];
      x_next = a_src [i + 1];
      DEBUG_YREGEX  yLOG_complex ("LOOP"      , "%3d, %c, %c, %c", i, x_prev, x_char, x_next);
      sprintf (t, "%c", x_char);
      /*---(filter)----------------------*/
      if (x_prev != '(')                  continue;
      if (strchr ("#>", x_char) == NULL)  continue;
      /*---(find beg)--------------------*/
      DEBUG_YREGEX  yLOG_note    ("found capture group, save pattern");
      x_beg  = i + 1;
      DEBUG_YREGEX  yLOG_value   ("x_beg"     , x_beg);
      x_end  = -1;
      x_nest = 0;
      strlcpy (r, "", LEN_REGEX);
      /*---(find end)-----------------*/
      for (j = x_beg; j < l; ++j) {
         /*---(prepare)---------------*/
         x_prev = a_src [j - 1];
         x_char = a_src [j];
         x_next = a_src [j + 1];
         /*---(grouping)--------------*/
         switch (x_char) {
         case '(' :
            ++x_nest;
            break;
         case ')' :
            if (x_nest == 0) {
               if (x_prev == '<') { x_end = j - 2; x_num = 0;   }
               else               { x_end = j - 1; x_num = n++; }
            }
            --x_nest;
         }
         if (x_end >= 0) break;
         /*---(skipping)--------------*/
         if  (x_prev == '(' && strchr ("#>", x_char) != NULL)  continue;
         if  (x_next == ')' && strchr ("<" , x_char) != NULL)  continue;
         /*---(adding chars)----------*/
         sprintf (s, "%c", x_char);
         strlcat (r, s, LEN_REGEX);
         /*---(done)------------------*/
      }
      /*---(save pattern)-------------*/
      DEBUG_YREGEX  yLOG_value   ("x_end"     , x_end);
      if (x_end >= 0) {
         x_len = x_end - x_beg + 1;
         DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
         DEBUG_YREGEX  yLOG_info    ("r"         , r);
         yregex_pats__save (r, x_num);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yregex_pats_comp        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_REGEX] = "";
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   yregex_pats_reset ();
   /*---(double clean)-------------------*/
   rc = yregex_pats__replace (myREGEX.regex, 0);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yregex_pats__replace (myREGEX.regex, 0);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save named)---------------------*/
   rc = yregex_pats__named   (myREGEX.regex);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(replace named)------------------*/
   rc = yregex_pats__replace (myREGEX.regex, 1);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                                     <* 
 *> yregex_pats_comp_OLD    (void)                                                                           <* 
 *> {                                                                                                        <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                              <* 
 *>    char        rce         =  -10;                                                                       <* 
 *>    char        rc          =    0;                                                                       <* 
 *>    int         i           =    0;                                                                       <* 
 *>    uchar       x_ch        =  ' ';          /+ curr character                 +/                         <* 
 *>    uchar       x_pch       =  ' ';          /+ prev character                 +/                         <* 
 *>    uchar       x_ppch      =  ' ';          /+ prev-prev character            +/                         <* 
 *>    int         x_prev      =    0;                                                                       <* 
 *>    int         x_len       =    0;                                                                       <* 
 *>    char        t           [LEN_REGEX] = "";                                                             <* 
 *>    /+---(header)-------------------------+/                                                              <* 
 *>    DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);                                                            <* 
 *>    yregex_pats_reset ();                                                                                 <* 
 *>    /+> yregex_pats__save_run ();                                                      <+/                <* 
 *>    /+---(parse)--------------------------+/                                                              <* 
 *>    DEBUG_YREGEX  yLOG_info    ("myREGEX.orig"  , myREGEX.orig);                                          <* 
 *>    DEBUG_YREGEX  yLOG_value   ("myREGEX.olen"  , myREGEX.olen);                                          <* 
 *>    strlcpy (myREGEX.regex , "", LEN_REGEX);                                                              <* 
 *>    for (i = 0; i < myREGEX.olen; ++i) {                                                                  <* 
 *>       DEBUG_YREGEX  yLOG_value   ("LOOP"      , i);                                                      <* 
 *>       /+---(prepare)---------------------+/                                                              <* 
 *>       x_ppch = x_pch = x_ch = 0;                                                                         <* 
 *>       if (i > 1) x_ppch = myREGEX.orig [i - 2];                                                          <* 
 *>       if (i > 0) x_pch  = myREGEX.orig [i - 1];                                                          <* 
 *>       x_ch   = myREGEX.orig [i];                                                                         <* 
 *>       /+---(named pattern)---------------+/                                                              <* 
 *>       if (( x_ppch == '(' && x_pch == '#' && x_ch == '&')  ||                                            <* 
 *>             (x_pch == '(' && x_ch  == '&')) {                                                            <* 
 *>          DEBUG_YREGEX  yLOG_note    ("found named potenial pattern");                                    <* 
 *>          x_len = i - x_prev;                                                                             <* 
 *>          DEBUG_YREGEX  yLOG_complex ("stats"     , "beg %3d, end %3d, len %3d", x_prev, i - 1, x_len);   <* 
 *>          sprintf (t, "%-*.*s", x_len, x_len, myREGEX.orig + x_prev);                                     <* 
 *>          DEBUG_YREGEX  yLOG_info    ("t"         , t);                                                   <* 
 *>          strlcat (myREGEX.regex, t, LEN_REGEX);                                                          <* 
 *>          DEBUG_YREGEX  yLOG_info    ("myREGEX.regex"   , myREGEX.regex);                                 <* 
 *>          rc     = yregex_pats__named_ref (&i);                                                           <* 
 *>          x_prev = i;                                                                                     <* 
 *>          DEBUG_YREGEX  yLOG_value   ("x_prev"    , x_prev);                                              <* 
 *>          DEBUG_YREGEX  yLOG_info    ("myREGEX.regex"   , myREGEX.regex);                                 <* 
 *>          myREGEX.rlen = strllen (myREGEX.regex, LEN_REGEX);                                              <* 
 *>       }                                                                                                  <* 
 *>       /+---(named pattern)---------------+/                                                              <* 
 *>       else if (x_pch != '\\' && x_ch == '&') {                                                           <* 
 *>          DEBUG_YREGEX  yLOG_note    ("found abbr pattern");                                              <* 
 *>          x_len = i - x_prev;                                                                             <* 
 *>          DEBUG_YREGEX  yLOG_complex ("stats"     , "beg %3d, end %3d, len %3d", x_prev, i - 1, x_len);   <* 
 *>          sprintf (t, "%-*.*s", x_len, x_len, myREGEX.orig + x_prev);                                     <* 
 *>          DEBUG_YREGEX  yLOG_info    ("t"         , t);                                                   <* 
 *>          strlcat (myREGEX.regex, t, LEN_REGEX);                                                          <* 
 *>          DEBUG_YREGEX  yLOG_info    ("myREGEX.regex"   , myREGEX.regex);                                 <* 
 *>          rc     = yregex_pats__abbr_ref (&i);                                                            <* 
 *>          x_prev = i;                                                                                     <* 
 *>          DEBUG_YREGEX  yLOG_value   ("x_prev"    , x_prev);                                              <* 
 *>          DEBUG_YREGEX  yLOG_info    ("myREGEX.regex"   , myREGEX.regex);                                 <* 
 *>          myREGEX.rlen = strllen (myREGEX.regex, LEN_REGEX);                                              <* 
 *>       }                                                                                                  <* 
 *>       /+---(done)------------------------+/                                                              <* 
 *>    }                                                                                                     <* 
 *>    /+---(copy last)----------------------+/                                                              <* 
 *>    DEBUG_YREGEX  yLOG_complex ("stats"     , "beg %3d", x_prev);                                         <* 
 *>    sprintf (t, "%s", myREGEX.orig + x_prev);                                                             <* 
 *>    DEBUG_YREGEX  yLOG_info    ("t"         , t);                                                         <* 
 *>    strlcat (myREGEX.regex, t, LEN_REGEX);                                                                <* 
 *>    myREGEX.rlen = strllen (myREGEX.regex, LEN_REGEX);                                                    <* 
 *>    /+---(show)---------------------------+/                                                              <* 
 *>    DEBUG_YREGEX  yLOG_info    ("myREGEX.regex"   , myREGEX.regex);                                       <* 
 *>    DEBUG_YREGEX  yLOG_value   ("myREGEX.rlen"    , myREGEX.rlen);                                        <* 
 *>    /+---(complete)-----------------------+/                                                              <* 
 *>    DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);                                                            <* 
 *>    return 0;                                                                                             <* 
 *> }                                                                                                        <*/



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*        /*-> unit test accessor -----------------[ light  [us.D90.241.L0]*/ /*-[03.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yregex_pats__unit       (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   char        r           [LEN_TERSE] = "";
   char        s           [LEN_TERSE] = "";
   char        t           [LEN_HUND]  = "";
   int         c           = 0;
   int         x_fore      = 0;
   int         x_back      = 0;
   tPATS      *x_curr      = NULL;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "PATS unit, unknown request", 100);
   /*---(mapping)------------------------*/
   if      (strcmp (a_question, "count"    )      == 0) {
      x_curr = s_head; while (x_curr != NULL) { ++x_fore; x_curr = x_curr->m_next; }
      x_curr = s_tail; while (x_curr != NULL) { ++x_back; x_curr = x_curr->m_prev; }
      snprintf (unit_answer, LEN_RECD, "PATS count       : num=%4d, fore=%4d, back=%4d", s_count, x_fore, x_back);
   }
   else if (strcmp (a_question, "list"        )   == 0) {
      snprintf (unit_answer, LEN_RECD, "PATS list        : num=%4d, head=%-10p, tail=%p", s_count, s_head, s_tail);
   }
   else if (strcmp (a_question, "entry"    )      == 0) {
      yregex_pats__by_index (a_num, &x_curr);
      if (x_curr != NULL) {
         sprintf (r, "%2då%.10sæ", x_curr->nlen, x_curr->name);
         sprintf (s, "%2då%.40sæ", x_curr->plen , x_curr->pat);
         snprintf (unit_answer, LEN_RECD, "PATS entry  (%2d) : %c  %c  %-14.14s  %s",
               a_num, x_curr->source, x_curr->abbr, r, s);
      } else {
         snprintf (unit_answer, LEN_RECD, "PATS entry  (%2d) : -  -   -åæ             -åæ", a_num);
      }
      return unit_answer;
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




/*===============================[[ end code ]]===============================*/
