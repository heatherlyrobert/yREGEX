/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"




tPATS       g_pats [MAX_PATS] = {
   /*      0         1            0         1         2         3         4         5         6         7         8         9         A         B         C         D         E         F                  */
   /*1234  01234567890123456789   01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890        */
   /*abbr  ---name-------------   ---pattern-------------------------------------------------------------------------------------------------------------------------------------------------------  ln sz */
   { '-', "float"              , "(-)?(0|[1-9][0-9]*)([.][0-9]+)?"                                                                                                                                  , 0, 0 },
   { '-', "byte"               , "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])$"                                                                                                              , 0, 0 },
   { '-', "int"                , "(-)?(0|[1-9][0-9]*)"                                                                                                                                              , 0, 0 },
   {  0 , ""                   , ""                                                                                                                                                                 , 0, 0 },
};
int       g_npat      = 0;



tSETS       g_sets [MAX_SETS] = {
   /*           0         1            0               1               2               3               4               5               6               7               8               9               A               B               C               D               E               F                 */
   /*1234 1234  01234567890123456789   0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef  */
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { '-', '-', "---beg---"          , "                                                                                                                                                                                                                                                                " },
   /*---(metas)----------------*/
   /*type type  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { '-', 'n', "return"             , "          . ..                                                                                                                                                                        .                                                                         " },
   { '-', 'e', "escape"             , "                       .                                                                                                                                             .                                                                                          " },
   { '-', 't', "tab"                , "         . .                                                                                                                                                                               .                                                                    " },
   { '-', 'f', "field"              , "                             ...                                                                                                                                      ..                                                                                        " },
   { ':', 's', "space"              , "         .....                  .                                                                                                                                                      .                                                                        " },
   { '-', 'w', "word"               , "                                                ..........       ..........................    . ..........................                                                                                     ................................................" },
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { ':', 'd', "digit"              , "                                                ..........                                                                                                                                                                                                      " },
   { ':', 'l', "lower"              , "                                                                                                 ..........................                                                                                                                                     " },
   { ':', 'u', "upper"              , "                                                                 ..........................                                                                                                                                                                     " },
   { '-', 'g', "greek"              , "                                                                                                                                                                                                                 ..............................................." },
   /*---(categories)-----------*/
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { '-', '-', "dotta"              , " ......... .  ........................................................................................................................................................................ ........................................................................." },
   { ':', 'a', "alpha"              , "                                                                 ..........................      ..........................                                                                                                                                     " },
   { ':', '-', "alnum"              , "                                                ..........       ..........................      ..........................                                                                                                                                     " },
   { ':', '-', "punct"              , "                                 ...............          .......                          ......                          ....                                                                                                                                 " },
   { ':', 'x', "xdigi"              , "                                                ..........       ......                          ......                                                                                                                                                         " },
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { ':', '-', "graph"              , "                                 ..............................................................................................                                  ..............................................................................................." },
   { ':', '-', "print"              , "                                ...............................................................................................                                  ..............................................................................................." },
   { ':', '-', "cntrl"              , " ...............................                                                                                               .                                                                                                                                " },
   { ':', '-', "blank"              , "         .                      .                                                                                                                                                                                                                               " },
   /*---(reversed)-------------*/
   { '-', 'W', "word (not)"         , " ...............................................          .......                          .... .                          .....................................................................................                                                " },
   { '-', 'D', "digit (not)"        , " ...............................................          ......................................................................................................................................................................................................" },
   { '-', 'S', "space (not)"        , " ........     .................. ...................................................................................................................................................... ........................................................................" },
   { '-', 'F', "field (not)"        , " ............................   ......................................................................................................................................  ........................................................................................" },
   { '-', 'G', "greek (not)"        , " ...............................................................................................................................................................................................................                                                " },
   /*---(specialty)------------*/
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { ' ', '-', ""                   , "                                                                                                                                                                                                                                                                " },
   /*---(new ones)-------------*/
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { ' ', '-', ""                   , "                                                                                                                                                                                                                                                                " },
   /*---(done)-----------------*/
   {  0 , '-', ""                   , "                                                                                                                                                                                                                                                                " },
};
int         g_nset      = 0;
#define     BSLASHSET   "entfswdlugaxWDSFG"
#define     MOD_SET      "*+?@~!"
#define     GRP_SET      "()|"
#define     MAX_QUAN    255

char        g_regex     [LEN_RECD]  = "";
int         g_rlen      = -1;

char        g_comp      [LEN_RECD]  = "";
int         g_indx      [LEN_RECD];
char        g_mods      [LEN_RECD]  = "";
int         g_mins      [LEN_RECD];
int         g_maxs      [LEN_RECD];
int         g_jump      [LEN_RECD];
int         g_clen      = -1;

char        s_map       [270] = "";
int         s_mapcount  =  0;

int         s_gstack    [100];
int         s_glevel          =  0;
int         s_ggroup          =  0;
int         s_ghidden         = 10;
char        s_gfocus          = '-';


/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char         /*-> tbd --------------------------------[ shoot  [fe.C73.144.31]*/ /*-[01.0000.01#.Z]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_init    (cchar *a_regex)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_regex"   , a_regex);
   /*---(check regex)--------------------*/
   --rce;  if (a_regex  == NULL) {
      DEBUG_YREGEX  yLOG_note    ("can not be null");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = snprintf (g_regex, LEN_RECD, "(%s)", a_regex);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   --rce;  if (rc     <  0   ) {
      DEBUG_YREGEX  yLOG_note    ("truncated copy");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_rlen = strllen (g_regex , LEN_RECD);
   DEBUG_YREGEX  yLOG_value   ("g_rlen"    , g_rlen);
   --rce;  if (g_rlen <= 0   ) {
      DEBUG_YREGEX  yLOG_note    ("can not be empty");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(initialize compiled)------------*/
   for (i = 0; i < LEN_RECD; ++i) {
      g_comp [i] = ' ';
      g_indx [i] =   0;
      g_mods [i] = ' ';
      g_mins [i] =   0;
      g_maxs [i] =   0;
      g_jump [i] =   0;
   }
   g_comp [0] =  0;
   g_indx [0] =  0;
   g_mods [0] =  0;
   g_mins [0] =  0;
   g_maxs [0] =  0;
   g_jump [0] =  0;
   g_clen = 0;
   /*---(initialize grouping)------------*/
   s_glevel   =  0;
   s_ggroup   =  0;
   s_ghidden  = 10;
   s_gfocus   = '-';
   /*---(initialize sets)----------------*/
   yREGEX__comp_setinit ();
   yREGEX__comp_patinit ();
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fz.632.201.00]*/ /*-[00.0000.06#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_add     (cchar a_comp, cint a_indx)
{
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (a_comp);
   DEBUG_YREGEX  yLOG_sint    (a_indx);
   DEBUG_YREGEX  yLOG_sint    (g_clen);
   g_comp [g_clen] = a_comp;
   g_indx [g_clen] = a_indx;
   g_mods [g_clen] = ' ';
   g_mins [g_clen] = 0;
   g_maxs [g_clen] = 0;
   g_jump [g_clen] = 0;
   ++g_clen;
   DEBUG_YREGEX  yLOG_sint    (g_clen);
   g_comp [g_clen] = 0;
   g_indx [g_clen] = 0;
   g_mods [g_clen] = 0;
   g_mins [g_clen] = 0;
   g_maxs [g_clen] = 0;
   g_jump [g_clen] = 0;
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fz.412.301.00]*/ /*-[00.0000.02#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_mod     (cchar a_mod, uint a_min, uint a_max)
{
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (a_mod);
   DEBUG_YREGEX  yLOG_sint    (a_min);
   DEBUG_YREGEX  yLOG_sint    (a_max);
   g_mods [g_clen - 1] = a_mod;
   g_mins [g_clen - 1] = a_min;
   g_maxs [g_clen - 1] = a_max;
   DEBUG_YREGEX  yLOG_sint    (g_clen - 1);
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      literal handling                        ----===*/
/*====================------------------------------------====================*/
static void      o___LITERAL_________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [fe.833.134.31]*/ /*-[01.0000.01#.6]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_literal (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_ch        =  '-';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(defense)------------------------*/
   --rce;  if (*a_rpos  <  0     ) {
      DEBUG_YREGEX  yLOG_note    ("position before start");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("g_rlen"    , g_rlen);
   --rce;  if (*a_rpos  >= g_rlen) {
      DEBUG_YREGEX  yLOG_note    ("position after end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   x_ch  = g_regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   rc = yREGEX__comp_add  (x_ch, 0);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                       pattern handling                       ----===*/
/*====================------------------------------------====================*/
static void      o___PATTERNS________________o (void) {;}

char         /*-> initialize patterns ----------------[ leaf   [fz.531.021.10]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_patinit (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   /*---(initialize sets)----------------*/
   g_npat = 0;
   for (i = 0; i < MAX_PATS; ++i) {
      if (g_pats [i].abbr == 0)  break;
      ++g_npat;
      g_pats [i].len  = strllen (g_pats [i].name, LEN_NAME);
      g_pats [i].size = strllen (g_pats [i].pat , LEN_PAT );
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         set handling                         ----===*/
/*====================------------------------------------====================*/
static void      o___SETS____________________o (void) {;}

char         /*-> tbd --------------------------------[ leaf   [fz.531.021.10]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_setinit (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   /*---(initialize sets)----------------*/
   g_nset = 0;
   for (i = 0; i < MAX_SETS; ++i) {
      if (g_sets [i].type != 0   && g_sets [i].type != ' ') {
         ++g_nset;
         continue;
      }
      g_sets [i].type     = 0;
      strlcpy (g_sets [i].name, "", LEN_NAME);
      for (j = 0; j < 256;  ++j)   g_sets [i].map [j] = ' ';
      g_sets [i].map [256] = 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fc.632.122.40]*/ /*-[01.0000.01#.8]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_setabbr (cchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_set       =   -1;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_schar   (a_abbr);
   DEBUG_YREGEX  yLOG_sint    (g_nset);
   /*---(walk through sets)--------------*/
   for (i = 0; i < g_nset; ++i) {
      if (g_sets [i].type == 0     )  break;
      if (g_sets [i].abbr == '-'   )  continue;
      if (g_sets [i].abbr == ' '   )  continue;
      if (g_sets [i].abbr != a_abbr)  continue;
      DEBUG_YREGEX  yLOG_snote   ("found");
      DEBUG_YREGEX  yLOG_sint    (i);
      DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
      return i;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_snote   ("not found");
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [fe.B44.145.52]*/ /*-[01.0000.01#.B]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_bslash  (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =    0;
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
   DEBUG_YREGEX  yLOG_value   ("g_rlen"    , g_rlen);
   --rce;  if (*a_rpos  >= g_rlen) {
      DEBUG_YREGEX  yLOG_note    ("current position already past end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_ch  = g_regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != '\\') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a backslash");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(advance)------------------------*/
   ++(*a_rpos);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = g_regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   /*---(check for set)------------------*/
   DEBUG_YREGEX  yLOG_info    ("allowed"   , BSLASHSET);
   if (strchr (BSLASHSET, x_ch) != NULL) {
      x_set = yREGEX__comp_setabbr (x_ch);
   }
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   /*---(append set)---------------------*/
   if (x_set > 0) {
      yREGEX__comp_add ('[', x_set);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(boundaries)---------------------*/
   if (x_ch == 'b') {
      DEBUG_YREGEX  yLOG_note    ("begin word marker");
      yREGEX__comp_add ('<', yREGEX__comp_setabbr ('w'));
      yREGEX__comp_mod ('<', 0, 0);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   if (x_ch == 'B') {
      DEBUG_YREGEX  yLOG_note    ("end word marker");
      yREGEX__comp_add ('>', yREGEX__comp_setabbr ('w'));
      yREGEX__comp_mod ('>', 0, 0);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(literal)------------------------*/
   yREGEX__comp_add (x_ch, 0);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fe.A53.145.A0]*/ /*-[01.0000.02#.E]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_setname (cchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_name"    , a_name);
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_info    ("a_name"    , a_name);
   x_len = strllen (a_name, LEN_NAME);
   DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <= 4) {
      DEBUG_YREGEX  yLOG_note    ("too short");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len >= 6) {
      DEBUG_YREGEX  yLOG_note    ("too long");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   for (i = 0; i < g_nset; ++i) {
      if (g_sets [i].type ==  0 )                break;
      if (g_sets [i].type == ' ')                continue;
      if (g_sets [i].name [0] != a_name [0])     continue;
      if (g_sets [i].name [1] != a_name [1])     continue;
      if (g_sets [i].name [2] != a_name [2])     continue;
      if (g_sets [i].name [3] != a_name [3])     continue;
      if (g_sets [i].name [4] != a_name [4])     continue;
      DEBUG_YREGEX  yLOG_value   ("found"     , i);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return i;
   }
   DEBUG_YREGEX  yLOG_note    ("not found");
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fe.833.044.30]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_setloc  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   x_len = strllen (s_map, LEN_RECD);
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
   for (i = 0; i < g_nset; ++i) {
      if (strcmp (g_sets [i].map, s_map) != 0)   continue;
      DEBUG_YREGEX  yLOG_snote   ("found");
      DEBUG_YREGEX  yLOG_sint    (i);
      DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
      return i;
   }
   DEBUG_YREGEX  yLOG_snote   ("not found");
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [fe.943.034.30]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_setnew  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   x_len = strllen (s_map, LEN_RECD);
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
   DEBUG_YREGEX  yLOG_sint    (g_nset);
   --rce;  if (g_nset >= MAX_SETS) {
      DEBUG_YREGEX  yLOG_snote   ("no room");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(fill out)-----------------------*/
   g_sets [g_nset].type     = ' ';
   g_sets [g_nset].abbr     = '-';
   g_sets [g_nset].name [0] = 0;
   strlcpy (g_sets [g_nset].map, s_map, LEN_RECD);
   /*---(update count)-------------------*/
   DEBUG_YREGEX  yLOG_sint    (g_nset);
   ++g_nset;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return g_nset - 1;
}

char         /*-> tbd --------------------------------[ leaf   [fz.321.111.00]*/ /*-[00.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_setclr  (char a_unmark)
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
yREGEX__comp_setmap  (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
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
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(defense)------------------------*/
   --rce;  if (*a_rpos <  0     ) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (*a_rpos >= g_rlen) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (g_nset  >= MAX_SETS) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defaults)-----------------------*/
   if (g_regex [*a_rpos] == '^') {
      DEBUG_YREGEX  yLOG_note    ("found leading inverse sign");
      x_unmark = '.';
      x_mark   = ' ';
      ++(*a_rpos);
      DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   }
   DEBUG_YREGEX  yLOG_char    ("x_mark"    , x_mark);
   DEBUG_YREGEX  yLOG_char    ("x_unmark"  , x_unmark);
   yREGEX__comp_setclr (x_unmark);
   /*---(map)----------------------------*/
   DEBUG_YREGEX  yLOG_note    ("walk through regex");
   --rce;  for (i = *a_rpos; i < g_rlen; ++i) {
      /*---(prepare)---------------------*/
      x_ch  = g_regex [i];
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
         if      (i <= *a_rpos) {
            DEBUG_YREGEX  yLOG_note    ("found prefix hyphen, process it");
         } else if (i >= g_rlen - 3) {
            DEBUG_YREGEX  yLOG_note    ("found suffix hyphen, process it");
         } else {
            DEBUG_YREGEX  yLOG_note    ("found range hyphen");
            x_range = 'y';
            continue;
         }
      }
      /*---(range)-----------------------*/
      if (x_range == 'y') {
         DEBUG_YREGEX  yLOG_note    ("update range");
         DEBUG_YREGEX  yLOG_char    ("x_sch"     , x_sch);
         if  (x_ch < x_sch) {
            DEBUG_YREGEX  yLOG_note    ("backwards ranges are illegal");
            yREGEX__comp_setclr (x_unmark);
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
   --rce;  if (i == g_rlen) {
      yREGEX__comp_setclr (x_unmark);
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

char         /*-> tbd --------------------------------[ ------ [fe.D55.138.72]*/ /*-[01.0000.01#.A]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_setstd  (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_NAME] = "";
   uchar       x_set       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(defense)------------------------*/
   --rce;  if (*a_rpos  <  1     ) {
      DEBUG_YREGEX  yLOG_note    ("does not leave room to left for [");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("g_rlen"    , g_rlen);
   --rce;  if (*a_rpos  >= g_rlen - 7) {
      DEBUG_YREGEX  yLOG_note    ("not enough room for full name");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (g_regex [*a_rpos - 1] != '[') {
      DEBUG_YREGEX  yLOG_note    ("does not have [ to left");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (g_regex [*a_rpos    ] != ':') {
      DEBUG_YREGEX  yLOG_note    ("does not have : at current position");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (g_regex [*a_rpos + 6] != ':') {
      DEBUG_YREGEX  yLOG_note    ("does not have : near end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (g_regex [*a_rpos + 7] != ']') {
      DEBUG_YREGEX  yLOG_note    ("does not have ] at end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for set)------------------*/
   sprintf (t, "%-5.5s", g_regex + *a_rpos + 1);
   DEBUG_YREGEX  yLOG_info    ("name"      , t);
   x_set = yREGEX__comp_setname (t);
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   /*---(append set)---------------------*/
   if (x_set > 0) {
      yREGEX__comp_add ('[', x_set);
      *a_rpos += 7;
      DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(complete)-----------------------*/
   --rce;
   DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char         /*-> tbd --------------------------------[ ------ [fe.D54.156.65]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_set     (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   uchar       x_set       =    0;
   char        t           [LEN_NAME] = "";
   char        x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = g_regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != '[') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a [");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(advance)------------------------*/
   ++(*a_rpos);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = g_regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   /*---(check standard sets)------------*/
   if (x_ch == ':') {
      DEBUG_YREGEX  yLOG_note    ("is colon (:) posix set indicator");
      rc = yREGEX__comp_setstd (a_rpos);
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      if (rc > 0) {
         DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 1;
      }
   }
   /*---(map the set)--------------------*/
   rc = yREGEX__comp_setmap  (a_rpos);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(try to find existing)-----------*/
   x_set = yREGEX__comp_setloc  ();
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   if (x_set > 0) {
      yREGEX__comp_add ('[', x_set);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(add a new one)------------------*/
   x_set = yREGEX__comp_setnew  ();
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   if (x_set > 0) {
      yREGEX__comp_add ('[', x_set);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(failed)-------------------------*/
   --rce;
   DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char         /*-> tbd --------------------------------[ ------ [fe.632.152.12]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_dot     (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   uchar       x_set       =    0;
   char        t           [LEN_NAME] = "";
   char        x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(defense)------------------------*/
   x_ch   = g_regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   --rce;  if (x_ch != '.') {
      DEBUG_YREGEX  yLOG_note    ("not positioned on a dot");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set)----------------------------*/
   x_set = yREGEX__comp_setname ("dotta");
   yREGEX__comp_add ('[', x_set);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                       modifier handling                      ----===*/
/*====================------------------------------------====================*/
static void      o___MODS____________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [fe.732.151.11]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_smods   (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   uchar       x_set       =    0;
   char        t           [LEN_NAME] = "";
   char        x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = g_regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   switch (x_ch) {
   case '*' : case '@' :
      DEBUG_YREGEX  yLOG_note    ("any modifier * (greedy) and @ (lazy)");
      yREGEX__comp_mod (x_ch, 0, MAX_QUAN);
      break;
   case '+' : case '~' :
      DEBUG_YREGEX  yLOG_note    ("many modifier + (greedy) and ~ (lazy)");
      yREGEX__comp_mod (x_ch, 1, MAX_QUAN);
      break;
   case '?' : case '!' :
      DEBUG_YREGEX  yLOG_note    ("one modifier ? (greedy) and ! (lazy)");
      yREGEX__comp_mod (x_ch, 0, 1       );
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> tbd --------------------------------[ ------ [fe.I86.1C3.D1]*/ /*-[03.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_cmods   (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   uchar       x_set       =    0;
   char        t           [LEN_NAME] = "";
   uchar       x_ch        =  ' ';
   uchar       x_sch       =  ' ';
   int         i           =    0;
   char        x_lazy      =  '-';
   int         x_min       =   -1;
   int         x_max       =   -1;
   int         x_len       =    0;
   char        x_comma     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = g_regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   --rce;  if (x_ch != '{') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a {");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for lazy modifier)--------*/
   x_ch   = g_regex [++(*a_rpos)];
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   if (x_ch == '-') {
      DEBUG_YREGEX  yLOG_note    ("found lazy modifer");
      x_lazy = 'y';
      x_ch   = g_regex [++(*a_rpos)];
      DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
      DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   }
   /*---(walk modifier)------------------*/
   while (1) {
      DEBUG_YREGEX  yLOG_value   ("x_len"     , x_len);
      if (*a_rpos >= g_rlen) {
         DEBUG_YREGEX  yLOG_note    ("hit end of string");
         break;
      }
      if (x_ch == '}') {
         DEBUG_YREGEX  yLOG_note    ("found end of modifier");
         if (x_len > 0) {
            sprintf (t, "%*.*s", x_len, x_len, g_regex + *a_rpos - x_len);
            DEBUG_YREGEX  yLOG_info    ("t"         , t);
            x_max = atoi (t);
         } else {
            x_max = MAX_QUAN;
         }
         DEBUG_YREGEX  yLOG_value   ("x_max"     , x_max);
         break;
      }
      if (x_ch == ',') {
         DEBUG_YREGEX  yLOG_note    ("found comma separator");
         x_comma = 'y';
         if (x_len == 0) {
            DEBUG_YREGEX  yLOG_note    ("min specifier is empty, use zero");
            x_min = 0;
         } else {
            DEBUG_YREGEX  yLOG_note    ("found real min specifier");
            sprintf (t, "%*.*s", x_len, x_len, g_regex + *a_rpos - x_len);
            DEBUG_YREGEX  yLOG_info    ("t"         , t);
            x_min = atoi (t);
         }
         x_len = -1; /* don't count comma */
         DEBUG_YREGEX  yLOG_value   ("x_min"     , x_min);
      }
      x_ch   = g_regex [++(*a_rpos)];
      ++x_len;
      DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
      DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   }
   /*---(check)--------------------------*/
   --rce;  if (x_max <= 0) {
      DEBUG_YREGEX  yLOG_note    ("max can not be empty or zero");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (x_comma == '-')   x_min = x_max;
   /*---(update)-------------------------*/
   DEBUG_YREGEX  yLOG_note    ("update modifier");
   if (x_lazy == 'y')  yREGEX__comp_mod ('}', x_min, x_max);
   else                yREGEX__comp_mod ('{', x_min, x_max);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                         group handling                       ----===*/
/*====================------------------------------------====================*/
static void      o___GROUPS__________________o (void) {;}

char         /*-> tbd --------------------------------[ leaf   [fc.741.141.50]*/ /*-[03.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_gfix    (cint a_grp)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         x_ch        =  ' ';
   int         x_jump      =   -1;
   int         x_or        =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_value   ("a_grp"     , a_grp);
   /*---(track backwards)----------------*/
   for (i = g_clen; i >= 0; --i) {
      x_ch   = g_comp [i];
      if (g_indx [i] == a_grp) {
         if (x_ch == '|') {
            g_jump [i] = x_jump;
            x_jump =  0;
            ++x_or;
         } else if (x_ch == '(') {
            g_jump [i] = x_jump;
            if (x_or > 0) g_mods [i] = 'm';
            else          g_mods [i] = '-';
            g_mins [i] = x_or + 1;
            break;
         }
      }
      ++x_jump;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> tbd --------------------------------[ ------ [fe.B53.141.32]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__comp_group   (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   uchar       x_ch        =  ' ';
   uchar       x_nch       =  ' ';
   int         x_grp       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   x_ch   = g_regex [*a_rpos];
   x_nch  = g_regex [*a_rpos + 1];
   DEBUG_YREGEX  yLOG_complex ("position"  , "pos %2d, ch  %c, nch %c", *a_rpos, x_ch, x_nch);
   switch (x_ch) {
   case '(' :
      ++s_glevel;
      if (x_nch == '#') {
         DEBUG_YREGEX  yLOG_note    ("open hidden group");
         ++*a_rpos;
         x_grp = ++s_ghidden;
      } else if (x_nch == '>') {
         DEBUG_YREGEX  yLOG_note    ("open primary group");
         s_gfocus = 'y';
         ++*a_rpos;
         x_grp = 999;
      } else {
         DEBUG_YREGEX  yLOG_note    ("open normal group");
         x_grp = ++s_ggroup;
         if (s_ggroup > 10)  x_grp = ++s_ghidden;
      }
      rc = yREGEX__comp_add  ('(', x_grp);
      s_gstack [s_glevel] = x_grp;
      DEBUG_YREGEX  yLOG_complex ("current"   , "lvl %2d, nrm %2d, hid %2d, grp %2d", s_glevel, s_ggroup, s_ghidden, x_grp);
      break;
   case '<' :
      DEBUG_YREGEX  yLOG_note    ("close primary group");
      x_grp = s_gstack [s_glevel];
         if (x_grp != 999) {
            DEBUG_YREGEX  yLOG_note    ("primary focus parens do not match");
            DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
            return -1;
         }
      rc = yREGEX__comp_add  (')', x_grp);
      rc = yREGEX__comp_gfix (x_grp);
      DEBUG_YREGEX  yLOG_complex ("current"   , "lvl %2d, nrm %2d, hid %2d, grp %2d", s_glevel, s_ggroup, s_ghidden, x_grp);
      --s_glevel;
      ++*a_rpos;
      break;
   case ')' :
      DEBUG_YREGEX  yLOG_note    ("close normal/hidden group");
      x_grp = s_gstack [s_glevel];
      rc = yREGEX__comp_add  (x_ch, x_grp);
      rc = yREGEX__comp_gfix (x_grp);
      DEBUG_YREGEX  yLOG_complex ("current"   , "lvl %2d, nrm %2d, hid %2d, grp %2d", s_glevel, s_ggroup, s_ghidden, x_grp);
      --s_glevel;
      break;
   case '|' :
      DEBUG_YREGEX  yLOG_note    ("divide branches");
      x_grp = s_gstack [s_glevel];
      rc = yREGEX__comp_add  (x_ch, x_grp);
      DEBUG_YREGEX  yLOG_complex ("current"   , "lvl %2d, nrm %2d, hid %2d, grp %2d", s_glevel, s_ggroup, s_ghidden, x_grp);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                         main driver                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [ge.E54.142.98]*/ /*-[02.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yREGEX_comp          (cchar *a_regex)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   uchar       x_ch        =  ' ';          /* current character              */
   uchar       x_nch       =  ' ';          /* next character                 */
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_point   ("a_regex"   , a_regex);
   /*---(prepare)------------------------*/
   rc = yREGEX__comp_init   (a_regex);
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(parse)--------------------------*/
   DEBUG_YREGEX  yLOG_info    ("g_regex"   , g_regex);
   DEBUG_YREGEX  yLOG_point   ("g_rlen"    , g_rlen);
   for (i = 0; i < g_rlen; ++i) {
      DEBUG_YREGEX  yLOG_value   ("LOOP"      , i);
      /*---(prepare)---------------------*/
      x_ch   = g_regex [i];
      x_nch  = g_regex [i + 1];
      /*---(backslashed metas)-----------*/
      if (x_ch == G_KEY_BSLASH) {
         DEBUG_YREGEX  yLOG_note    ("handle escaped character");
         rc = yREGEX__comp_bslash (&i);
         continue;
      }
      /*---(dot)-------------------------*/
      if (x_ch == '.') {
         DEBUG_YREGEX  yLOG_note    ("handle dot character");
         rc = yREGEX__comp_dot (&i);
         continue;
      }
      /*---(group handling)--------------*/
      if (strchr (GRP_SET, x_ch) != NULL || (x_ch == '<' && x_nch == ')')) {
         DEBUG_YREGEX  yLOG_note    ("handle grouping");
         rc = yREGEX__comp_group (&i);
         if (rc >= 0)  continue;
      }
      /*---(anchors)---------------------*/
      if (strchr (G_ANCHOR, x_ch) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("handle anchors");
         if (x_ch == '<' || x_ch == '>')  yREGEX__comp_add (x_ch, yREGEX__comp_setabbr ('w'));
         else                             yREGEX__comp_add (x_ch, 0);
         yREGEX__comp_mod (x_ch, 0, 0);
         continue;
      }
      /*---(set handling)----------------*/
      if (x_ch == '[') {
         DEBUG_YREGEX  yLOG_note    ("handle character set");
         rc = yREGEX__comp_set (&i);
         if (rc >= 0)  continue;
      }
      /*---(quick modifiers)-------------*/
      if (strchr (MOD_SET, x_ch) != NULL) {
         DEBUG_YREGEX  yLOG_note    ("handle simple modifier");
         rc = yREGEX__comp_smods (&i);
         continue;
      }
      /*---(specific modifiers)----------*/
      if (x_ch == '{') {
         DEBUG_YREGEX  yLOG_note    ("handle complex modifier");
         rc = yREGEX__comp_cmods (&i);
         continue;
      }
      /*---(literals)--------------------*/
      DEBUG_YREGEX  yLOG_note    ("handle character literal");
      rc = yREGEX__comp_literal (&i);
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char        unit_answer  [LEN_RECD];

char         /*-> unit test accessor -----------------[ light  [us.D90.241.L0]*/ /*-[03.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yREGEX__unitmap    (char a_type, int a_value)
{
   char        x_ch        = ' ';
   char       *x_range     = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range2    = " 123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range3    = " .123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ**********************************************************************";
   switch (a_type) {
   case '(' :
      if      (a_value == 999)   x_ch = '<';
      else if (a_value >= 65 )   x_ch = '*';
      else                       x_ch = x_range3 [a_value];
      break;
   case 'i' :
      if      (a_value >= 65 )   x_ch = '*';
      else                       x_ch = x_range2 [a_value];
      break;
   case 'm' : case 'x' : case 'j' :
      if      (a_value ==  0)    x_ch = ' ';
      else if (a_value >= 62)    x_ch = '*';
      else                       x_ch = x_range [a_value];
      break;
   }
   return x_ch;
}

char*        /*-> unit test accessor -----------------[ light  [us.D90.241.L0]*/ /*-[03.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yREGEX__unitcomp   (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   char        t           [100] = "";
   char       *x_range     = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range2    = " 123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range3    = " .123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ**********************************************************************";
   int         c           = 0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "REGEX_unitcomp, unknown request", 100);
   /*---(core data)----------------------*/
   if        (strncmp (a_question, "regex"     , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "yREGEX_comp regex: %2d [%-45.45s]", g_rlen, g_regex);
   }
   /*---(mapping)------------------------*/
   else if (strncmp (a_question, "map"       , 20)  == 0) {
      strlcpy (t, "0123456789abcdef0123456789abcdef", 100);
      if (a_num < 0 || a_num > 15)
         snprintf (unit_answer, LEN_RECD, "yREGEX_comp map  : %x %3d %2d [%-32.32s]", 0    , s_mapcount, 0, "unknown area");
      else
         for (i = 0; i < 32; ++i)  if (s_map [a_num * 32 + i] == '.') {
            t [i] = '_';
            ++c;
         }
      snprintf (unit_answer, LEN_RECD, "yREGEX_comp map  : %x %3d %2d [%-32.32s]", a_num * 2, s_mapcount, c, t);
   }
   /*---(compiled)-----------------------*/
   else if   (strncmp (a_question, "base"      , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "yREGEX_comp base : %2d [%-45.45s]", g_clen, g_comp);
   } else if (strncmp (a_question, "indx"      , 20)  == 0) {
      for (i = 0; i < 45; ++i) {
         if (strchr ("(|)", g_comp [i]) != NULL)  t [i] = yREGEX__unitmap ('(', g_indx [i]);
         else                                     t [i] = yREGEX__unitmap ('i', g_indx [i]);
      }
      t [45] = 0;
      snprintf (unit_answer, LEN_RECD, "yREGEX_comp indx : %2d [%-45.45s]", g_clen, t);
   } else if (strncmp (a_question, "mods"      , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "yREGEX_comp mods : %2d [%-45.45s]", g_clen, g_mods);
   } else if (strncmp (a_question, "mins"      , 20)  == 0) {
      for (i = 0; i < 45; ++i)   t [i] = yREGEX__unitmap ('m', g_mins [i]);
      t [45] = 0;
      snprintf (unit_answer, LEN_RECD, "yREGEX_comp mins : %2d [%-45.45s]", g_clen, t);
   } else if (strncmp (a_question, "maxs"      , 20)  == 0) {
      for (i = 0; i < 45; ++i)   t [i] = yREGEX__unitmap ('x', g_maxs [i]);
      t [45] = 0;
      snprintf (unit_answer, LEN_RECD, "yREGEX_comp maxs : %2d [%-45.45s]", g_clen, t);
   } else if (strncmp (a_question, "jump"      , 20)  == 0) {
      for (i = 0; i < 45; ++i)   t [i] = yREGEX__unitmap ('j', g_jump [i]);
      t [45] = 0;
      snprintf (unit_answer, LEN_RECD, "yREGEX_comp jump : %2d [%-45.45s]", g_clen, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
