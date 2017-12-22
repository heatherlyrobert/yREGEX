/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



/*---(struct.re)--------+-----------+-*//*-+----------------------------------*/
#define     LEN_MAP     270
#define     MAX_SETS    250
typedef     struct      cSETS       tSETS;
struct      cSETS {
   char        type;
   char        abbr;
   char        name        [LEN_NAME];
   char        map         [LEN_MAP ];
};
static tSETS       s_sets [MAX_SETS] = {
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
static int         s_nset      = 0;



static char        s_map       [LEN_MAP ] = "";
static int         s_mapcount  =  0;



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char         /*-> tbd --------------------------------[ leaf   [fz.531.021.10]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
SETS_init            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   /*---(initialize sets)----------------*/
   s_nset = 0;
   for (i = 0; i < MAX_SETS; ++i) {
      if (s_sets [i].type != 0   && s_sets [i].type != ' ') {
         ++s_nset;
         continue;
      }
      s_sets [i].type     = 0;
      strlcpy (s_sets [i].name, "", LEN_NAME);
      for (j = 0; j < 256;  ++j)   s_sets [i].map [j] = ' ';
      s_sets [i].map [256] = 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        finding sets                          ----===*/
/*====================------------------------------------====================*/
static void      o___FINDING_________________o (void) {;}

char         /*-> tbd --------------------------------[ leaf   [fc.632.122.40]*/ /*-[01.0000.01#.8]-*/ /*-[--.---.---.--]-*/
SETS_by_abbr         (cchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         i           =    0;
   char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (a_abbr);
   /*---(defense)------------------------*/
   --rce;  if (a_abbr == 0) {
      DEBUG_YREGEX  yLOG_snote   ("can not be null");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr (x_valid, a_abbr) == NULL) {
      DEBUG_YREGEX  yLOG_snote   ("abbr must be [A-Za-z]");
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_schar   (a_abbr);
   DEBUG_YREGEX  yLOG_sint    (s_nset);
   /*---(walk through sets)--------------*/
   DEBUG_YREGEX  yLOG_snote   ("searching");
   for (i = 0; i < s_nset; ++i) {
      if (s_sets [i].type == 0     )  break;
      if (s_sets [i].abbr == '-'   )  continue;
      if (s_sets [i].abbr == ' '   )  continue;
      if (s_sets [i].abbr != a_abbr)  continue;
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

char         /*-> tbd --------------------------------[ leaf   [fe.A53.145.A0]*/ /*-[01.0000.02#.E]-*/ /*-[--.---.---.--]-*/
SETS__by_name        (cchar *a_name)
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
      DEBUG_YREGEX  yLOG_snote   ("can not be null");
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
   for (i = 0; i < s_nset; ++i) {
      if (s_sets [i].type ==  0 )                break;
      if (s_sets [i].type == ' ')                continue;
      if (s_sets [i].name [0] != a_name [0])     continue;
      if (s_sets [i].name [1] != a_name [1])     continue;
      if (s_sets [i].name [2] != a_name [2])     continue;
      if (s_sets [i].name [3] != a_name [3])     continue;
      if (s_sets [i].name [4] != a_name [4])     continue;
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
SETS__by_map         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
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
   for (i = 0; i < s_nset; ++i) {
      if (strcmp (s_sets [i].map, s_map) != 0)   continue;
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




/*====================------------------------------------====================*/
/*===----                         set mapping                          ----===*/
/*====================------------------------------------====================*/
static void      o___MAPPING_________________o (void) {;}

char         /*-> tbd --------------------------------[ leaf   [fz.321.111.00]*/ /*-[00.0000.01#.!]-*/ /*-[--.---.---.--]-*/
SETS__clear          (char a_unmark)
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

char         /*-> tbd --------------------------------[ leaf   [fe.943.034.30]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
SETS__save           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
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
   /*---(fill out)-----------------------*/
   s_sets [s_nset].type     = ' ';
   s_sets [s_nset].abbr     = '-';
   s_sets [s_nset].name [0] = 0;
   strlcpy (s_sets [s_nset].map, s_map, LEN_MAP );
   /*---(update count)-------------------*/
   DEBUG_YREGEX  yLOG_sint    (s_nset);
   ++s_nset;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return s_nset - 1;
}

char         /*-> tbd --------------------------------[ ------ [fe.LA5.196.D1]*/ /*-[03.0000.01#.D]-*/ /*-[--.---.---.--]-*/
SETS__mapper         (int *a_rpos)
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
   --rce;  if (*a_rpos >= gre.rlen) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (s_nset  >= MAX_SETS) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defaults)-----------------------*/
   if (gre.regex [*a_rpos] == '^') {
      DEBUG_YREGEX  yLOG_note    ("found leading inverse sign");
      x_unmark = '.';
      x_mark   = ' ';
      ++(*a_rpos);
      DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   }
   DEBUG_YREGEX  yLOG_char    ("x_mark"    , x_mark);
   DEBUG_YREGEX  yLOG_char    ("x_unmark"  , x_unmark);
   SETS__clear (x_unmark);
   /*---(map)----------------------------*/
   DEBUG_YREGEX  yLOG_note    ("walk through regex");
   --rce;  for (i = *a_rpos; i < gre.rlen; ++i) {
      /*---(prepare)---------------------*/
      x_ch  = gre.regex [i];
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
         } else if (i >= gre.rlen - 3) {
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
            SETS__clear (x_unmark);
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
   --rce;  if (i == gre.rlen) {
      SETS__clear (x_unmark);
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
/*===----                         other elements                       ----===*/
/*====================------------------------------------====================*/
static void      o___OTHER___________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [fe.D55.138.72]*/ /*-[01.0000.01#.A]-*/ /*-[--.---.---.--]-*/
SETS__standard       (int *a_rpos)
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
   DEBUG_YREGEX  yLOG_value   ("gre.rlen"    , gre.rlen);
   --rce;  if (*a_rpos  >= gre.rlen - 7) {
      DEBUG_YREGEX  yLOG_note    ("not enough room for full name");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (gre.regex [*a_rpos - 1] != '[') {
      DEBUG_YREGEX  yLOG_note    ("does not have [ to left");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (gre.regex [*a_rpos    ] != ':') {
      DEBUG_YREGEX  yLOG_note    ("does not have : at current position");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (gre.regex [*a_rpos + 6] != ':') {
      DEBUG_YREGEX  yLOG_note    ("does not have : near end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (gre.regex [*a_rpos + 7] != ']') {
      DEBUG_YREGEX  yLOG_note    ("does not have ] at end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for set)------------------*/
   sprintf (t, "%-5.5s", gre.regex + *a_rpos + 1);
   DEBUG_YREGEX  yLOG_info    ("name"      , t);
   x_set = SETS__by_name (t);
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   /*---(append set)---------------------*/
   if (x_set > 0) {
      COMP_add ('[', x_set);
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



/*====================------------------------------------====================*/
/*===----                          compilation                         ----===*/
/*====================------------------------------------====================*/
static void      o___COMPILE_________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [fe.B44.145.52]*/ /*-[01.0000.01#.B]-*/ /*-[--.---.---.--]-*/
SETS_backslash       (int *a_rpos)
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
   DEBUG_YREGEX  yLOG_value   ("gre.rlen"  , gre.rlen);
   --rce;  if (*a_rpos  >= gre.rlen) {
      DEBUG_YREGEX  yLOG_note    ("current position already past end");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_ch  = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != '\\') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a backslash");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(advance)------------------------*/
   ++(*a_rpos);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   /*---(check for set)------------------*/
   DEBUG_YREGEX  yLOG_info    ("allowed"   , BACKSLASH_SETS);
   if (strchr (BACKSLASH_SETS, x_ch) != NULL) {
      x_set = SETS_by_abbr (x_ch);
   }
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   /*---(append set)---------------------*/
   if (x_set > 0) {
      COMP_add ('[', x_set);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(boundaries)---------------------*/
   if (x_ch == 'b') {
      DEBUG_YREGEX  yLOG_note    ("begin word marker");
      COMP_add ('<', SETS_by_abbr ('w'));
      COMP_mod ('<');
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   if (x_ch == 'B') {
      DEBUG_YREGEX  yLOG_note    ("end word marker");
      COMP_add ('>', SETS_by_abbr ('w'));
      COMP_mod ('>');
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(literal)------------------------*/
   COMP_add (x_ch, 0);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [fe.632.152.12]*/ /*-[01.0000.01#.!]-*/ /*-[--.---.---.--]-*/
SETS_dot             (int *a_rpos)
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
   x_ch   = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_ch"      , x_ch);
   --rce;  if (x_ch != '.') {
      DEBUG_YREGEX  yLOG_note    ("not positioned on a dot");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set)----------------------------*/
   x_set = SETS__by_name ("dotta");
   COMP_add ('[', x_set);
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> tbd --------------------------------[ ------ [fe.D54.156.65]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
SETS_comp            (int *a_rpos)
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
   x_ch   = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch != '[') {
      DEBUG_YREGEX  yLOG_note    ("does not start with a [");
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(advance)------------------------*/
   ++(*a_rpos);
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   x_ch   = gre.regex [*a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_ch"      , x_ch);
   /*---(check standard sets)------------*/
   if (x_ch == ':') {
      DEBUG_YREGEX  yLOG_note    ("is colon (:) posix set indicator");
      rc = SETS__standard (a_rpos);
      DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
      if (rc > 0) {
         DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 1;
      }
   }
   /*---(map the set)--------------------*/
   rc = SETS__mapper  (a_rpos);
   --rce;  if (rc < 0) {
      DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_value   ("*a_rpos"   , *a_rpos);
   /*---(try to find existing)-----------*/
   x_set = SETS__by_map  ();
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   if (x_set > 0) {
      COMP_add ('[', x_set);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(add a new one)------------------*/
   x_set = SETS__save  ();
   DEBUG_YREGEX  yLOG_value   ("x_set"     , x_set);
   if (x_set > 0) {
      COMP_add ('[', x_set);
      DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(failed)-------------------------*/
   --rce;
   DEBUG_YREGEX  yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char         /*-> tbd --------------------------------[ ------ [fe.D54.156.65]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
SETS_list            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   for (i = 0; i < s_nset; ++i) {
      if (s_sets [i].type == 0) break;
      printf ("re  a  ---name-----  0123456789abcdef0123456789abcdef !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ \n");
      printf ("%-2d  %c  %-12.12s  ", i, s_sets [i].abbr, s_sets [i].name);
      for (j =   0; j < 128; ++j) {
         printf ("%c", s_sets [i].map [j]);
      }
      printf ("\n");
      printf ("                     0123456789abcdef0123456789abcdef ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ\n");
      printf ("                     ");
      for (j = 128; j < 256; ++j) {
         printf ("%c", s_sets [i].map [j]);
      }
      printf ("\n");
   }
   return 0;
}


/*====================------------------------------------====================*/
/*===----                           execution                          ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTE_________________o (void) {;}

char
SETS_break           (int a_level, int a_rpos, int a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       x_reg       =    0;
   int         x_indx      =    0;
   uchar       x_txt       =    0;
   char        x_txtrc     =    0;
   uchar       x_oth       =    0;
   char        x_othrc     =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_reg       = gre.comp [a_rpos];
   DEBUG_YREGEX  yLOG_char    ("x_reg"     , x_reg);
   x_indx      = gre.indx [a_rpos];
   DEBUG_YREGEX  yLOG_value   ("x_indx"    , x_indx);
   x_txt       = gre.text [a_tpos];
   DEBUG_YREGEX  yLOG_char    ("x_txt"     , x_txt);
   x_txtrc     = s_sets [x_indx].map [x_txt];
   DEBUG_YREGEX  yLOG_char    ("x_txtrc"   , x_txtrc);
   x_oth       = gre.text [a_tpos - 1];
   DEBUG_YREGEX  yLOG_char    ("x_oth"     , x_oth);
   x_othrc     = s_sets [x_indx].map [x_oth];
   DEBUG_YREGEX  yLOG_char    ("x_othrc"   , x_othrc);
   /*---(execute)------------------------*/
   switch (x_reg) {
   case '<' :
      if (a_tpos <= 0) {
         DEBUG_YREGEX  yLOG_note    ("BOW at BOL");
         rc = 1;
         break;
      }
      if (x_othrc == '.' || x_txtrc == ' ') {
         DEBUG_YREGEX  yLOG_note    ("not BOW");
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      DEBUG_YREGEX  yLOG_note    ("BOW");
      rc = 1;
      break;
   case '>' :
      if (x_txt == 0) {
         DEBUG_YREGEX  yLOG_note    ("EOW at EOL");
         rc = 1;
         break;
      }
      if (x_othrc == ' ' || x_txtrc == '.') {
         DEBUG_YREGEX  yLOG_note    ("not EOW");
         DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      DEBUG_YREGEX  yLOG_note    ("EOW");
      rc = 1;
      break;
      /*> case '>' :                                                                     <* 
       *>    if (x_txt == 0) {                                                           <* 
       *>       DEBUG_YREGEX  yLOG_note    ("EOW at EOL");                               <* 
       *>       rc = 1;                                                                  <* 
       *>       break;                                                                   <* 
       *>    }                                                                           <* 
       *>    x_oth       = gre.text [a_tpos + 1];                                        <* 
       *>    DEBUG_YREGEX  yLOG_char    ("x_oth"     , x_oth);                           <* 
       *>    x_othrc     = s_sets [x_indx].map [x_oth];                                  <* 
       *>    DEBUG_YREGEX  yLOG_char    ("x_othrc"   , x_othrc);                         <* 
       *>    if (x_othrc == '.' || x_txtrc == ' ') {                                     <* 
       *>       DEBUG_YREGEX  yLOG_note    ("not EOW");                                  <* 
       *>       DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);                               <* 
       *>       return 0;                                                                <* 
       *>    }                                                                           <* 
       *>    DEBUG_YREGEX  yLOG_note    ("EOW");                                         <* 
       *>    rc = 1;                                                                     <* 
       *>    break;                                                                      <*/
   }
   DEBUG_YREGEX  yLOG_value   ("rc"        , rc);
   /*---(prepare next)-------------------*/
   EXEC_launcher (a_level, a_rpos, a_tpos - 1, rc);
   /*---(return)-------------------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return rc;
}

char
SETS_exec            (int a_level, int a_rpos, int a_tpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       x_reg       =    0;
   int         x_indx      =    0;
   uchar       x_txt       =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_reg       = gre.comp [a_rpos];
   DEBUG_YREGEX  yLOG_schar   (x_reg);
   x_indx      = gre.indx [a_rpos];
   DEBUG_YREGEX  yLOG_sint    (x_indx);
   x_txt       = gre.text [a_tpos];
   DEBUG_YREGEX  yLOG_schar   (x_txt);
   /*---(execute)------------------------*/
   if (s_sets [x_indx].map [x_txt] == '.')  rc = 1;
   DEBUG_YREGEX  yLOG_sint    (rc);
   if (rc > 0)  DEBUG_YREGEX  yLOG_snote   ("pass");
   else         DEBUG_YREGEX  yLOG_snote   ("FAIL");
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   /*---(prepare next)-------------------*/
   EXEC_launcher (a_level, a_rpos, a_tpos, rc);
   /*---(return)-------------------------*/
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*        /*-> unit test accessor -----------------[ light  [us.D90.241.L0]*/ /*-[03.0000.00#.#]-*/ /*-[--.---.---.--]-*/
SETS__unit         (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   char        t           [100] = "";
   char       *x_range     = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range2    = " 123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ***********************************************************************";
   char       *x_range3    = " .123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ**********************************************************************";
   int         c           = 0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "SETS unit, unknown request", 100);
   /*---(mapping)------------------------*/
   if (strncmp (a_question, "map"       , 20)  == 0) {
      strlcpy (t, "0123456789abcdef0123456789abcdef", 100);
      if (a_num < 0 || a_num > 15)
         snprintf (unit_answer, LEN_TEXT, "SETS map         : %x %3d %2d [%-32.32s]", 0    , s_mapcount, 0, "unknown area");
      else {
         for (i = 0; i < 32; ++i)  if (s_map [a_num * 32 + i] == '.') {
            t [i] = '_';
            ++c;
         }
         snprintf (unit_answer, LEN_TEXT, "SETS map         : %x %3d %2d [%-32.32s]", a_num * 2, s_mapcount, c, t);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===============================[[ end code ]]===============================*/
