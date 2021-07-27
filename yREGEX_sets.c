/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"

/*
 * metis  mw2∑∑  invesigate if i can switch s_sets to const to save run-time space
 * metis  tw2#∑  check ranges for A-Za-z0-9 endpoints, or just make three singles
 * metis  tw2#∑  make sure backslash sets are working inside custom sets
 *
 *
 *
 */




/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
#define     LEN_MAP     270
#define     MAX_SETS    25
static const tSETS s_sets [MAX_SETS] = {
   /*                      0         1            0               1               2               3               4               5               6               7               8               9               A               B               C               D               E               F                 */
   /*           1234 1234  01234567890123456789   0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef  */
   /*---(metas)----------------*/
   /*--------  type  type  ---name-------------   ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑ !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ΩÄÅÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ∞±≤≥¥µ∂∑∏π∫ªºΩæø¿¡¬√ƒ≈∆«»… ÀÃÕŒœ–—“”‘’÷◊ÿŸ⁄€‹›ﬁﬂ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛ˇ  */
   { BASE_ENTRY, '-', 'n', "return"             , "          . ..                                                                                                                                                        .                                                                                         ", 0, NULL, NULL },
   { BASE_ENTRY, '-', 'e', "escape"             , "                       .                                                                                                                                             .                                                                                          ", 0, NULL, NULL },
   { BASE_ENTRY, '-', 't', "tab"                , "         . .                                                                                                                                                               .                                                                                    ", 0, NULL, NULL },
   { BASE_ENTRY, '-', 'f', "field"              , "                             ...                                                                                                                                       .                          .                                                             ", 0, NULL, NULL },
   { BASE_ENTRY, ':', 's', "space"              , "         .....                  .                                                                                                                                                        .                                                                      ", 0, NULL, NULL },
   { BASE_ENTRY, '-', 'w', "word"               , "                                                ..........       ..........................    . ..........................                                                                                                                                     ", 0, NULL, NULL },
   /*--------  type  type  ---name-------------   ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑ !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ΩÄÅÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ∞±≤≥¥µ∂∑∏π∫ªºΩæø¿¡¬√ƒ≈∆«»… ÀÃÕŒœ–—“”‘’÷◊ÿŸ⁄€‹›ﬁﬂ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛ˇ  */
   { BASE_ENTRY, ':', 'd', "digit"              , "                                                ..........                                                                                                                                                                                                      ", 0, NULL, NULL },
   { BASE_ENTRY, ':', 'l', "lower"              , "                                                                                                 ..........................                                                                                                                                     ", 0, NULL, NULL },
   { BASE_ENTRY, ':', 'u', "upper"              , "                                                                 ..........................                                                                                                                                                                     ", 0, NULL, NULL },
   { BASE_ENTRY, '-', 'g', "greek"              , "                                                                                                                                                                                                                                        ........................", 0, NULL, NULL },
   /*---(categories)-----------*/
   /*--------  type  type  ---name-------------   ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑ !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ΩÄÅÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ∞±≤≥¥µ∂∑∏π∫ªºΩæø¿¡¬√ƒ≈∆«»… ÀÃÕŒœ–—“”‘’÷◊ÿŸ⁄€‹›ﬁﬂ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛ˇ  */
   { BASE_ENTRY, '-', '-', "dotta"              , " ......... .  ........................................................................................................................................................ .........................................................................................", 0, NULL, NULL },
   { BASE_ENTRY, ':', 'a', "alpha"              , "                                                                 ..........................      ..........................                                                                                                                                     ", 0, NULL, NULL },
   { BASE_ENTRY, ':', '-', "alnum"              , "                                                ..........       ..........................      ..........................                                                                                                                                     ", 0, NULL, NULL },
   { BASE_ENTRY, ':', 'p', "punct"              , "                                 ...............          .......                          ......                          ....                                                                                                                                 ", 0, NULL, NULL },
   { BASE_ENTRY, '-', 'q', "rpunc"              , "                                ..      ..  . .           ..   .                           . .                             . .                                                                                                                                  ", 0, NULL, NULL },
   { BASE_ENTRY, ':', 'x', "xdigi"              , "                                                ..........       ......                          ......                                                                                                                                                         ", 0, NULL, NULL },
   /*--------  type  type  ---name-------------   ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑ !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ΩÄÅÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ∞±≤≥¥µ∂∑∏π∫ªºΩæø¿¡¬√ƒ≈∆«»… ÀÃÕŒœ–—“”‘’÷◊ÿŸ⁄€‹›ﬁﬂ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛ˇ  */
   { BASE_ENTRY, ':', '-', "graph"              , "                                 ..............................................................................................                                  ...............................................................................................", 0, NULL, NULL },
   { BASE_ENTRY, ':', '-', "print"              , "                                ...............................................................................................                                  ...............................................................................................", 0, NULL, NULL },
   { BASE_ENTRY, ':', 'c', "cntrl"              , " ...............................                                                                                               .                                                                                                                                ", 0, NULL, NULL },
   { BASE_ENTRY, ':', '-', "blank"              , "         .                      .                                                                                                                                                        .                                                                      ", 0, NULL, NULL },
   /*---(reversed)-------------*/
   /*--------  type  type  ---name-------------   ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑ !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ΩÄÅÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ∞±≤≥¥µ∂∑∏π∫ªºΩæø¿¡¬√ƒ≈∆«»… ÀÃÕŒœ–—“”‘’÷◊ÿŸ⁄€‹›ﬁﬂ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛ˇ  */
   { BASE_ENTRY, '-', 'W', "word (not)"         , " ...............................................          .......                          .... .                          .............................................................................................................                        ", 0, NULL, NULL },
   { BASE_ENTRY, '-', 'D', "digit (not)"        , " ...............................................          ......................................................................................................................................................................................................", 0, NULL, NULL },
   { BASE_ENTRY, '-', 'S', "space (not)"        , " ........     .................. ..................................................................................................................................................... .........................................................................", 0, NULL, NULL },
   { BASE_ENTRY, '-', 'F', "field (not)"        , " ............................   ......................................................................................................................................  .............................................................. .........................", 0, NULL, NULL },
   { BASE_ENTRY, '-', 'G', "greek (not)"        , " .......................................................................................................................................................................................................................................                        ", 0, NULL, NULL },
   /*---(done)-----------------*/
   { 0        ,  0 , 0  , NULL                 , NULL                                                                                                                                                                                                                                                              , 0, NULL, NULL },
};
static int         s_nset      = 0;
static char        s_allowed   [LEN_HUND] = "";



static char        s_map       [LEN_MAP ] = "";
static int         s_mapcount  =  0;



static tSETS      *s_head     = NULL;        /* head of list                 */
static tSETS      *s_tail     = NULL;        /* tail of list                 */
static tSETS      *s_curr     = NULL;        /* curent cursor                */
static int         s_count    =    0;        /* count of sets                */



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
yregex_sets__wipe       (void *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   tSETS      *x_cur       = NULL;
   /*---(cast)---------------------------*/
   x_cur = (tSETS *) a_cur;
   /*---(wipe)---------------------------*/
   x_cur->type     = '-';
   x_cur->abbr     = '-';
   x_cur->name     = NULL;
   x_cur->map      = NULL;
   x_cur->count    = 0;
   x_cur->m_prev   = NULL;
   x_cur->m_next   = NULL;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char yregex_sets__new   (void **r_new) { return yregex_share_new  (TYPE_SETS, r_new, &s_head, &s_tail, &s_count); }
char yregex_sets__free  (void **r_old) { return yregex_share_free (TYPE_SETS, r_old, &s_head, &s_tail, &s_count); }



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char yregex_sets_init    (void) { return yregex_share_init  (TYPE_SETS, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_sets__purge  (void) { return yregex_share_purge (TYPE_SETS, &s_head, &s_tail, &s_curr, &s_count); }
char yregex_sets_wrap    (void) { return yregex_share_wrap  (TYPE_SETS, &s_head, &s_tail, &s_curr, &s_count); }

char         /*-> tbd --------------------------------[ leaf   [fz.531.021.10]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_sets_reset    (void)
{
   yregex_sets__purge ();
   yregex_sets__base  ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       creating new sets                      ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE__________________o (void) {;}

char
yregex_sets__base       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   tSETS      *x_new       = NULL;
   char        t           [LEN_LABEL];
   int         j           =    0;
   /*---(defense)------------------------*/
   if (s_head != NULL)   return 0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   strlcpy (s_allowed, "", LEN_HUND);
   /*---(walk base)----------------------*/
   for (i = 0; i < MAX_SETS; ++i) {
      /*---(check for end)---------------*/
      if (s_sets [i].abbr == 0)  break;
      /*---(add a new one)---------------*/
      x_new = NULL;
      rc = yregex_sets__new (&x_new);
      if (x_new == NULL)  continue;
      /*---(populate)--------------------*/
      x_new->source   = s_sets [i].source;
      x_new->type     = s_sets [i].type;
      x_new->abbr     = s_sets [i].abbr;
      x_new->name     = s_sets [i].name;
      x_new->map      = s_sets [i].map;
      /*---(count included)--------------*/
      for (j = 0; j < LEN_MAP; ++j) {
         if (x_new->map [j] == 0)    break;
         if (x_new->map [j] == '.')  ++(x_new->count);
      }
      /*---(allowed abbr)----------------*/
      if (x_new->abbr != '-') {
         sprintf (t, "%c", s_sets [i].abbr);
         strlcat (s_allowed, t, LEN_HUND);
      }
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fe.943.034.30]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_sets__save       (char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_set       =   -1;
   int         x_len       =    0;
   tSETS      *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   x_len = strllen (s_map, LEN_MAP );
   DEBUG_YREGEX  yLOG_sint    (x_len);
   --rce;  if (x_len  <  256) {
      DEBUG_YREGEX  yLOG_snote   ("too short");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len  >  256) {
      DEBUG_YREGEX  yLOG_snote   ("too long");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_sint    (s_nset);
   --rce;  if (s_nset >= MAX_SETS) {
      DEBUG_YREGEX  yLOG_snote   ("no room");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(add a new one)------------------*/
   rc = yregex_sets__new (&x_new);
   DEBUG_YREGEX  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->map      = strdup (s_map);
   x_new->name     = strdup (a_name);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return s_count - 1;
}

char         /*-> tbd --------------------------------[ leaf   [fz.321.111.00]*/ /*-[00.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_sets__clear      (char a_unmark)
{
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   s_mapcount = 0;
   for (i = 0; i < 256; ++i)   s_map [i] = a_unmark;
   s_map [256] = 0;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [fe.LA5.196.D1]*/ /*-[03.0000.01#.D]-*/ /*-[--.---.---.--]-*/
yregex_sets__mapper     (char *a_regex, int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         l           =    0;
   int         i           =    0;
   int         j           =    0;
   char        x_bslash    =  '-';
   char        x_range     =  '-';
   uchar       x_sch       =    0;
   uchar       x_ch        =    0;
   char        x_unmark    =  ' ';
   char        x_mark      =  '.';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_regex"   , a_regex);
   --rce;  if (a_regex == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_info    ("a_regex"   , a_regex);
   l = strlen (a_regex);
   DEBUG_YREGEX  yLOG_value   ("l"         , l);
   DEBUG_YREGEX  yLOG_point   ("a_rpos"    , a_rpos);
   --rce;  if (a_rpos == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   --rce;  if (*a_rpos <  0     ) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (*a_rpos >= l) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_regex [*a_rpos] != '[') {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ++(*a_rpos);
   /*---(defaults)-----------------------*/
   if (a_regex [*a_rpos] == '^') {
      DEBUG_YREGEX  yLOG_note    ("found leading inverse sign");
      x_unmark = '.';
      x_mark   = ' ';
      ++(*a_rpos);
      DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   }
   DEBUG_YREGEX  yLOG_char    ("x_mark"    , x_mark);
   DEBUG_YREGEX  yLOG_char    ("x_unmark"  , x_unmark);
   yregex_sets__clear (x_unmark);
   /*---(map)----------------------------*/
   DEBUG_YREGEX  yLOG_note    ("walk through regex");
   --rce;  for (i = *a_rpos; i < l; ++i) {
      /*---(prepare)---------------------*/
      x_ch  = a_regex [i];
      DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
      /*---(backslash)-------------------*/
      if (x_ch == '\\') {
         DEBUG_YREGEX  yLOG_note    ("found backslash");
         if (x_bslash != 'y') {
            x_bslash = 'y';
            continue;
         }
      }
      /*---(end)-------------------------*/
      if (x_ch == ']' && x_bslash != 'y') {
         DEBUG_YREGEX  yLOG_note    ("found right square bracket");
         break;
      }
      /*---(hyphen)----------------------*/
      if (x_ch == '-') {
         if      (a_regex [i - 1] == '[') {
            DEBUG_YREGEX  yLOG_note    ("found prefix hyphen, process it");
         } else if (a_regex [i + 1] == ']') {
            DEBUG_YREGEX  yLOG_note    ("found suffix hyphen, process it");
         } else if (strchr (YSTR_LOWER , a_regex [i - 1]) != NULL && strchr (YSTR_LOWER , a_regex [i + 1]) != NULL) {
            DEBUG_YREGEX  yLOG_complex ("range"     , "lower case %c to %c", a_regex [i - 1], a_regex [i + 1]);
            x_ch    = a_regex [++i];
            x_range = 'y';
         } else if (strchr (YSTR_UPPER , a_regex [i - 1]) != NULL && strchr (YSTR_UPPER , a_regex [i + 1]) != NULL) {
            DEBUG_YREGEX  yLOG_complex ("range"     , "upper case %c to %c", a_regex [i - 1], a_regex [i + 1]);
            x_ch    = a_regex [++i];
            x_range = 'y';
         } else if (strchr (YSTR_NUMBER, a_regex [i - 1]) != NULL && strchr (YSTR_NUMBER, a_regex [i + 1]) != NULL) {
            DEBUG_YREGEX  yLOG_complex ("range"     , "numeric %c to %c", a_regex [i - 1], a_regex [i + 1]);
            x_ch    = a_regex [++i];
            x_range = 'y';
         } else if (strchr (YSTR_GREEK , a_regex [i - 1]) != NULL && strchr (YSTR_GREEK , a_regex [i + 1]) != NULL) {
            DEBUG_YREGEX  yLOG_complex ("range"     , "greek %c to %c", a_regex [i - 1], a_regex [i + 1]);
            x_ch    = a_regex [++i];
            x_range = 'y';
         } else {
            DEBUG_YREGEX  yLOG_note    ("range end not A-Za-z0-9Ë-ˇ, just a hyphen");
            yregex_error_add ('w', CAT_SET, i, 1, "not a range, just a hyphen");
         }
      }
      /*---(range)-----------------------*/
      if (x_range == 'y') {
         DEBUG_YREGEX  yLOG_note    ("update range");
         DEBUG_YREGEX  yLOG_char    ("x_sch"     , x_sch);
         DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
         if  (x_ch < x_sch) {
            DEBUG_YREGEX  yLOG_note    ("backwards ranges are illegal");
            yregex_error_add ('F', CAT_SET, i - 2, 3, "backwards range is illegal");
            yregex_sets__clear (x_unmark);
            DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         for (j = x_sch; j <= x_ch; ++j)  s_map [j] = x_mark;
      }
      /*---(single)----------------------*/
      else {
         DEBUG_YREGEX  yLOG_note    ("update single");
         s_map [x_ch] = x_mark;
      }
      /*---(next)------------------------*/
      DEBUG_YREGEX  yLOG_note    ("get ready for next run");
      x_sch = x_ch;
      x_bslash = '-';
      x_range  = '-';
   }
   /*---(check for runon)----------------*/
   --rce;  if (i == l) {
      yregex_error_add ('F', CAT_SET, i - 1, 1, "no set end marker, run-on");
      yregex_sets__clear (x_unmark);
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_rpos = i;
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   s_mapcount  = 0;
   for (i = 0; i < 256; ++i)   if (s_map [i] == '.')  ++s_mapcount;
   DEBUG_YREGEX  yLOG_value   ("mapcount"  , s_mapcount);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                        finding sets                          ----===*/
/*====================------------------------------------====================*/
static void      o___FINDING_________________o (void) {;}

char yregex_sets__by_cursor  (char a_move , tSETS  **r_back) { return yregex_share__by_cursor (TYPE_SETS, &s_head, &s_tail, &s_curr, r_back, a_move); }
char yregex_sets__by_index   (int a_index , tSETS  **r_back) { return yregex_share__by_index  (TYPE_SETS, &s_head, &s_curr, r_back, a_index); }
int  yregex_sets__by_abbr    (char a_abbr , tSETS  **r_back) { return yregex_share__by_abbr   (TYPE_SETS, &s_head, r_back, a_abbr); }
int  yregex_sets__by_name    (char *a_name, tSETS  **r_back) { return yregex_share__by_name   (TYPE_SETS, &s_head, r_back, a_name); }

int          /*-> tbd --------------------------------[ leaf   [fe.833.044.30]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_sets__by_map     (tSETS **r_back)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_set       =   -1;
   int         x_len       =    0;
   int         n           =    0;
   tSETS      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_back != NULL)  *r_back = NULL;
   /*---(defense)------------------------*/
   x_len = strllen (s_map, LEN_MAP );
   DEBUG_YREGEX  yLOG_sint    (x_len);
   --rce;  if (x_len <  256) {
      DEBUG_YREGEX  yLOG_snote   ("too short");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len >  256) {
      DEBUG_YREGEX  yLOG_snote   ("too long");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   x_curr = s_head;
   while (x_curr != NULL) {
      if (strcmp (x_curr->map, s_map) == 0) break;
      ++n;
      x_curr = x_curr->m_next;
   }
   /*---(check)--------------------------*/
   DEBUG_YREGEX  yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(saveback)-----------------------*/
   DEBUG_YREGEX  yLOG_snote   ("found");
   if (r_back != NULL)  *r_back = x_curr;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return n;
}



/*====================------------------------------------====================*/
/*===----                         other elements                       ----===*/
/*====================------------------------------------====================*/
static void      o___OTHER___________________o (void) {;}

int          /*-> tbd --------------------------------[ ------ [fe.D55.138.72]*/ /*-[01.0000.01#.A]-*/ /*-[--.---.---.--]-*/
yregex_sets__standard   (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_NAME] = "";
   int         x_set       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YREGEX  yLOG_point   ("a_rpos"    , a_rpos);
   --rce;  if (a_rpos == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   --rce;  if (*a_rpos  <  0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("myREGEX.rlen"    , myREGEX.rlen);
   --rce;  if (*a_rpos  >= myREGEX.rlen - 7) {
      DEBUG_YREGEX  yLOG_note    ("not enough room for full name");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (myREGEX.regex [*a_rpos    ] != '[') {
      DEBUG_YREGEX  yLOG_note    ("does not have [ to left");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (myREGEX.regex [*a_rpos + 1] != ':') {
      DEBUG_YREGEX  yLOG_note    ("does not have : at current position");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (myREGEX.regex [*a_rpos + 7] != ':') {
      DEBUG_YREGEX  yLOG_note    ("does not have : near end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (myREGEX.regex [*a_rpos + 8] != ']') {
      DEBUG_YREGEX  yLOG_note    ("does not have ] at end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for set)------------------*/
   sprintf (t, "%-5.5s", myREGEX.regex + *a_rpos + 2);
   DEBUG_YREGEX  yLOG_info    ("name"      , t);
   x_set = yregex_sets__by_name (t, NULL);
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   --rce;  if (x_set < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(append set)---------------------*/
   yregex_comp_add ('[', x_set);
   *a_rpos += 8;
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                          compilation                         ----===*/
/*====================------------------------------------====================*/
static void      o___COMPILE_________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [fe.B44.145.52]*/ /*-[01.0000.01#.B]-*/ /*-[--.---.---.--]-*/
yregex_sets_backslash   (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_set       =    0;
   char        t           [LEN_NAME] = "";
   uchar       x_ch        =  '-';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(defense)------------------------*/
   --rce;  if (*a_rpos  <  0     ) {
      DEBUG_YREGEX  yLOG_note    ("before the beginning of the regex");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("myREGEX.rlen"  , myREGEX.rlen);
   --rce;  if (*a_rpos  >= myREGEX.rlen) {
      DEBUG_YREGEX  yLOG_note    ("current position already past end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_ch  = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != '\\') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a backslash");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(advance)------------------------*/
   ++(*a_rpos);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   /*---(check for set)------------------*/
   DEBUG_YREGEX  yLOG_info    ("allowed"   , s_allowed);
   if (strchr (s_allowed, x_ch) != NULL) {
      x_set = yregex_sets__by_abbr (x_ch, NULL);
   }
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   /*---(append set)---------------------*/
   if (x_set > 0) {
      yregex_comp_add ('[', x_set);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(boundaries)---------------------*/
   if (x_ch == 'b') {
      DEBUG_YREGEX  yLOG_note    ("begin word marker");
      yregex_comp_add ('<', yregex_sets__by_abbr ('w', NULL));
      yregex_comp_mod ('<');
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   if (x_ch == 'B') {
      DEBUG_YREGEX  yLOG_note    ("end word marker");
      yregex_comp_add ('>', yregex_sets__by_abbr ('w', NULL));
      yregex_comp_mod ('>');
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(literal)------------------------*/
   yregex_comp_add (x_ch, 0);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [fe.632.152.12]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_sets_dot         (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   int         x_set       =    0;
   char        t           [LEN_NAME] = "";
   char        x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(defense)------------------------*/
   x_ch   = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   --rce;  if (x_ch != '.') {
      DEBUG_YREGEX  yLOG_note    ("not positioned on a dot");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set)----------------------------*/
   x_set = yregex_sets__by_name ("dotta", NULL);
   yregex_comp_add ('[', x_set);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> tbd --------------------------------[ ------ [fe.D54.156.65]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yregex_sets_comp        (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   int         x_set       =    0;
   char        t           [LEN_NAME] = "";
   char        x_ch        =  ' ';
   char        x_beg       =    0;
   char        x_end       =    0;
   char        x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = myREGEX.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch == ']') {
      yregex_error_add ('F', CAT_SET, *a_rpos, 1, "closing never openned set");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_ch != '[') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a [");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(advance)------------------------*/
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_beg  = *a_rpos;
   x_ch   = myREGEX.regex [*a_rpos + 1];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   /*---(check standard sets)------------*/
   if (x_ch == ':') {
      DEBUG_YREGEX  yLOG_note    ("is colon (:) posix set indicator");
      rc = yregex_sets__standard (a_rpos);
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      if (rc > 0) {
         DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 1;
      }
   }
   /*---(map the set)--------------------*/
   rc = yregex_sets__mapper  (myREGEX.regex, a_rpos);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_end  = *a_rpos;
   /*---(try to find existing)-----------*/
   x_set = yregex_sets__by_map  (NULL);
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   if (x_set > 0) {
      yregex_comp_add ('[', x_set);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(add a new one)------------------*/
   x_len = x_end - x_beg + 1;
   sprintf (t, "%*.*s", x_len, x_len, myREGEX.regex + x_beg);
   x_set = yregex_sets__save  (t);
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   if (x_set > 0) {
      yregex_comp_add ('[', x_set);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(failed)-------------------------*/
   --rce;
   DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}



/*====================------------------------------------====================*/
/*===----                           execution                          ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTE_________________o (void) {;}

char
yregex_sets_break       (int a_lvl, int a_rpos, int a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       x_reg       =    0;
   int         x_indx      =    0;
   uchar       x_txt       =    0;
   char        x_txtrc     =    0;
   uchar       x_oth       =    0;
   char        x_othrc     =    0;
   tSETS      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_reg       = myREGEX.comp [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_reg"     , x_reg);
   x_indx      = myREGEX.indx [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_indx"    , x_indx);
   x_txt       = myREGEX.text [a_tpos];
   DEBUG_YREGEX  yLOG_char    ("x_txt"     , x_txt);
   rc = yregex_sets__by_index (x_indx, &x_curr);
   x_txtrc     = x_curr->map [x_txt];
   DEBUG_YREGEX  yLOG_char    ("x_txtrc"   , x_txtrc);
   x_oth       = myREGEX.text [a_tpos - 1];
   DEBUG_YREGEX  yLOG_char    ("x_oth"     , x_oth);
   x_othrc     = x_curr->map [x_oth];
   DEBUG_YREGEX  yLOG_char    ("x_othrc"   , x_othrc);
   /*---(execute)------------------------*/
   switch (x_reg) {
   case '<' :
      if (a_tpos <= 0) {
         DEBUG_YREGEX  yLOG_note    ("BOW at BOL");
         yregex_exec__passed (HAND_ANC);
         rc = 1;
         break;
      }
      if (x_othrc == '.' || x_txtrc == ' ') {
         DEBUG_YREGEX  yLOG_note    ("not BOW");
         yregex_exec__failed (HAND_ANC);
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      DEBUG_YREGEX  yLOG_note    ("BOW");
      yregex_exec__passed (HAND_ANC);
      rc = 1;
      break;
   case '>' :
      if (x_txt == 0) {
         DEBUG_YREGEX  yLOG_note    ("EOW at EOL");
         yregex_exec__passed (HAND_ANC);
         rc = 1;
         break;
      }
      if (x_othrc == ' ' || x_txtrc == '.') {
         DEBUG_YREGEX  yLOG_note    ("not EOW");
         yregex_exec__failed (HAND_ANC);
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      DEBUG_YREGEX  yLOG_note    ("EOW");
      yregex_exec__passed (HAND_ANC);
      rc = 1;
      break;
   }
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   /*---(prepare next)-------------------*/
   yregex_exec_launcher (a_lvl + 1, a_rpos, a_tpos - 1, rc);
   /*---(return)-------------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yregex_sets_exec     (int a_level, int a_rpos, int a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       x_reg       =    0;
   int         x_indx      =    0;
   uchar       x_txt       =    0;
   tSETS      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_reg       = myREGEX.comp [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_reg"     , x_reg);
   x_indx      = myREGEX.indx [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_indx"    , x_indx);
   x_txt       = myREGEX.text [a_tpos];
   DEBUG_YREGEX  yLOG_char    ("x_txt"     , x_txt);
   /*---(execute)------------------------*/
   rc = yregex_sets__by_index (x_indx, &x_curr);
   if (x_curr->map [x_txt] == '.')  rc = 1;
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc > 0) {
      DEBUG_YREGEX  yLOG_note    ("pass");
      rc = yregex_exec__passed (HAND_SET);
   } else {
      DEBUG_YREGEX  yLOG_note    ("FAIL");
      rc = yregex_exec__failed (HAND_SET);
   }
   /*---(prepare next)-------------------*/
   yregex_exec_launcher (a_level + 1, a_rpos, a_tpos, rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yregex_sets_rule        (char a_mod, char *a_text, int a_set)
{
   /*---(design notes)-------------------*/
   /*
    *  after already being vetted for set in main regex
    *  this allows checking for special exceptions
    *
    *
    *  ∫À[¥¥¥]ª   means capture group À includes a letter in the set
    *  ∫À[^¥¥¥]ª  means capture group À does not include a letter in the set
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   uchar       x_txt       =    0;
   uchar       x_mark      =    0;
   int         i           =    0;
   tSETS      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   --rce;  if (a_text == NULL    )  return rce;
   x_len = strllen (a_text, LEN_TEXT);
   DEBUG_YREGEX  yLOG_complex ("a_text"    , "%2dÂ%sÊ", x_len, a_text);
   yregex_sets__by_index (a_set, &x_curr);
   DEBUG_YREGEX  yLOG_complex ("set"       , "%2d, %-10p, %s", a_set, x_curr, x_curr->name);
   DEBUG_YREGEX  yLOG_info    ("map"       , x_curr->map);
   if (a_mod == '[')  {
      DEBUG_YREGEX  yLOG_note    ("normal has-a match");
      rc = 0;
   } else {
      DEBUG_YREGEX  yLOG_note    ("inverse does-not-have-a match");
      rc = 1;
   }
   DEBUG_YREGEX  yLOG_complex ("mod"       , "%c, %d", a_mod, rc);
   for (i = 0; i < x_len; ++i) {
      x_txt  = a_text [i];
      x_mark = x_curr->map [x_txt];
      if (a_mod == '[' && x_mark == '.')   rc = 1;
      if (a_mod == ']' && x_mark == ' ')   rc = 0;
   }
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*
yregex_sets__memory     (void *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   tSETS      *x_cur       = NULL;
   /*---(cast)---------------------------*/
   x_cur = (tSETS *) a_cur;
   /*---(defense)------------------------*/
   if (x_cur == NULL) {
      strlcpy (g_print, "n/a", LEN_RECD);
      return g_print;
   }
   /*---(defense)------------------------*/
   strlcpy (g_print, "Â__.___.__Ê", LEN_RECD);
   ++n;  if (x_cur->type        != '-')         g_print [n] = 'X';
   ++n;  if (x_cur->abbr        != '-')         g_print [n] = 'X';
   ++n;
   ++n;  if (x_cur->name        != NULL)        g_print [n] = 'X';
   ++n;  if (x_cur->map         != NULL)        g_print [n] = 'X';
   ++n;  if (x_cur->count       != 0)           g_print [n] = 'X';
   ++n;
   ++n;  if (x_cur->m_prev      != NULL)        g_print [n] = 'X';
   ++n;  if (x_cur->m_next      != NULL)        g_print [n] = 'X';
   return g_print;
}

char
yregex_sets__setmap     (char *a_map)
{
   strlcpy (s_map, a_map, LEN_MAP);
   return 0;
}

char*        /*-> unit test accessor -----------------[ light  [us.D90.241.L0]*/ /*-[03.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yregex_sets__unit       (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   char        r           [LEN_TERSE] = "";
   char        s           [LEN_TERSE] = "";
   char        t           [LEN_HUND]  = "";
   int         c           = 0;
   int         n           =    0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "SETS unit, unknown request", 100);
   /*---(mapping)------------------------*/
   if      (strcmp (a_question, "count"    )      == 0) {
      yregex_share__unit (TYPE_SETS, s_head, s_tail, s_count, "count", 0);
   }
   else if (strcmp (a_question, "list"        )   == 0) {
      yregex_share__unit (TYPE_SETS, s_head, s_tail, s_count, "list" , 0);
   }
   else if (strncmp (a_question, "map"       , 20)  == 0) {
      if (a_num < 0 || a_num > 3)
         snprintf (unit_answer, LEN_TEXT, "SETS map         : unknown area");
      else {
         for (i = 0; i < 64; ++i) {
            n = (a_num * 64) + i;
            if (s_map [n] == '.') {
               switch (n) {
               case 127 : t [i] = '¥';  break;
               case 160 : t [i] = '†';  break;
               default :  t [i] = YSTR_FULL [n];  break;
               }
               ++c;
            } else {
               t [i]     = '∑';
            }
            t [i + 1] = '\0';
         }
         if (s_mapcount > 0)  sprintf (r, "%3d", s_mapcount);
         else                 sprintf (r, "  -");
         if (c          > 0)  sprintf (s, "%2d", c);
         else                 sprintf (s, " -");
         snprintf (unit_answer, LEN_TEXT, "SETS map    (%02x) : %s %sÂ%sÊ", a_num * 64, r, s, t);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===============================[[ end code ]]===============================*/
