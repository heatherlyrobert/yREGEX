/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"

tSETS       g_sets [MAX_SETS] = {
   /*           0         1            0               1               2               3               4               5               6               7               8               9               A               B               C               D               E               F                 */
   /*1234 1234  01234567890123456789   0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef  */
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { '-', '-', "---beg---"          , "                                                                                                                                                                                                                                                                " },
   /*---(metas)----------------*/
   /*type type  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { '-', 'e', "escape"             , "                       .                                                                                                                                                                                                                                        " },
   { '-', 'n', "return"             , "          . ..                                                                                                                                                                                                                                                  " },
   { '-', 't', "tab"                , "         . .                                                                                                                                                                                                                                                    " },
   { ':', 's', "space"              , "         .....                  .                                                                                                                                                                                                                               " },
   { '-', 'w', "word"               , "                                                ..........       ..........................    . ..........................                                                                                                                                     " },
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { ':', 'd', "digit"              , "                                                ..........                                                                                                                                                                                                      " },
   { ':', 'l', "lower"              , "                                                                                                 ..........................                                                                                                                                     " },
   { ':', 'u', "upper"              , "                                                                 ..........................                                                                                                                                                                     " },
   { '-', 'g', "greek"              , "                                                                                                                                                                                                                 ..............................................." },
   /*---(categories)-----------*/
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { '-', '-', "dot"                , "                                ...............................................................................................                                  ..............................................................................................." },
   { ':', '-', "alpha"              , "                                                                 ..........................      ..........................                                                                                                                                     " },
   { ':', '-', "alnum"              , "                                                ..........       ..........................      ..........................                                                                                                                                     " },
   { ':', '-', "punct"              , "                                 ...............          .......                          ......                          ....                                                                                                                                 " },
   { ':', '-', "xdigi"              , "                                                ..........       ......                          ......                                                                                                                                                         " },
   /*type abbr  ---name-------------   0123456789abcdef0123456789abcde  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { ':', '-', "graph"              , "                                 ..............................................................................................                                  ..............................................................................................." },
   { ':', '-', "print"              , "                                ...............................................................................................                                  ..............................................................................................." },
   { ':', '-', "cntrl"              , "................................                                                                                               .                                                                                                                                " },
   { ':', '-', "blank"              , "         .                      .                                                                                                                                                                                                                               " },
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
#define     BSLASHSET   "entswdlug"

char        g_regex     [LEN_RECD]  = "";
int         g_rlen      = -1;

char        g_comp      [LEN_RECD]  = "";
int         g_clen      = -1;

char        s_map       [270] = "";
int         s_mapcount  =  0;


/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
yREGEX__comp_init    (cchar *a_regex)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   /*---(check regex)--------------------*/
   --rce;  if (a_regex  == NULL)  return rce;
   g_rlen = strllen (a_regex , LEN_RECD);
   --rce;  if (g_rlen <= 0   )  return rce;
   rc = strlcpy (g_regex, a_regex , LEN_RECD);
   --rce;  if (rc     <  0   )  return rce;
   /*---(initialize)---------------------*/
   strlcpy (g_comp , ""      , LEN_RECD);
   g_clen = strllen (g_comp  , LEN_RECD);
   /*---(initialize sets)----------------*/
   yREGEX__comp_setinit ();
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         set handling                         ----===*/
/*====================------------------------------------====================*/
static void      o___SETS____________________o (void) {;}

char
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

char
yREGEX__comp_setabbr (cchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_set       =   -1;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
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

char
yREGEX__comp_bslash  (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =    0;
   char        t           [LEN_NAME] = "";
   uchar       x_ch        =  '-';
   /*---(defense)------------------------*/
   --rce;  if (*a_rpos  <  1     )             return rce;
   --rce;  if (*a_rpos  >= g_rlen)             return rce;
   --rce;  if (g_regex [*a_rpos - 1] != '\\')  return rce;
   /*---(check for set)------------------*/
   x_ch  = g_regex [*a_rpos];
   if (strchr (BSLASHSET, x_ch) != NULL) {
      x_set = yREGEX__comp_setabbr (x_ch);
   }
   /*---(append set)---------------------*/
   if (x_set > 0) {
      sprintf (t, "[%c", x_set);
      strlcat (g_comp, t, LEN_RECD);
      ++(*a_rpos);
      return 1;
   }
   /*---(literal)------------------------*/
   sprintf (t, "%c", x_ch);
   strlcat (g_comp, t, LEN_RECD);
   /*---(complete)-----------------------*/
   ++(*a_rpos);
   return 0;
}

char
yREGEX__comp_setname (cchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
   int         i           =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)  return rce;
   x_len = strllen (a_name, LEN_NAME);
   --rce;  if (x_len <= 4)  return rce;
   --rce;  if (x_len >= 6)  return rce;
   /*---(walk)---------------------------*/
   for (i = 0; i < g_nset; ++i) {
      if (g_sets [i].type == 0)                  break;
      if (g_sets [i].type != ':')                continue;
      if (g_sets [i].name [0] != a_name [0])     continue;
      if (g_sets [i].name [1] != a_name [1])     continue;
      if (g_sets [i].name [2] != a_name [2])     continue;
      if (g_sets [i].name [3] != a_name [3])     continue;
      if (g_sets [i].name [4] != a_name [4])     continue;
      return i;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yREGEX__comp_setloc  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
   int         i           =    0;
   /*---(defense)------------------------*/
   --rce;  if (s_map == NULL)  return rce;
   x_len = strllen (s_map, LEN_NAME);
   --rce;  if (x_len <  256)  return rce;
   --rce;  if (x_len >  256)  return rce;
   /*---(walk)---------------------------*/
   for (i = 0; i < g_nset; ++i) {
      if (strcmp (g_sets [i].map, s_map) != 0)   continue;
      return i;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yREGEX__comp_setnew  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =   -1;
   int         x_len       =    0;
   /*---(defense)------------------------*/
   --rce;  if (s_map == NULL)        return rce;
   x_len = strllen (s_map, LEN_NAME);
   --rce;  if (x_len  <  256)       return rce;
   --rce;  if (x_len  >  256)       return rce;
   --rce;  if (g_nset >= MAX_SETS)  return rce;
   /*---(fill out)-----------------------*/
   g_sets [g_nset].type     = ' ';
   g_sets [g_nset].abbr     = '-';
   g_sets [g_nset].name [0] = 0;
   strlcpy (g_sets [g_nset].map, s_map, LEN_RECD);
   /*---(complete)-----------------------*/
   return ++g_nset;
}

char
yREGEX__comp_setclr  (char a_unmark)
{
   int         i           =    0;
   s_mapcount = 0;
   for (i = 0; i < 256; ++i)   s_map [i] = a_unmark;
   s_map [256] = 0;
   return 0;
}

char
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
   /*---(defense)------------------------*/
   --rce;  if (*a_rpos <  0     )    return rce;
   --rce;  if (*a_rpos >= g_rlen)    return rce;
   --rce;  if (g_nset  >= MAX_SETS)  return rce;
   /*---(defaults)-----------------------*/
   if (g_regex [*a_rpos] == '^') {
      x_unmark = '.';
      x_mark   = ' ';
      ++(*a_rpos);
   }
   yREGEX__comp_setclr (x_unmark);
   /*---(map)----------------------------*/
   --rce;  for (i = *a_rpos; i < g_rlen; ++i) {
      /*---(prepare)---------------------*/
      x_ch  = g_regex [i];
      /*---(backslash)-------------------*/
      if (x_ch == '\\') {
         if (x_bslash != 'y') {
            x_bslash = 'y';
            continue;
         }
      }
      /*---(end)-------------------------*/
      if (x_ch == ']' && x_bslash != 'y')  break;
      /*---(hyphen)----------------------*/
      if (x_ch == '-' && (i > *a_rpos && i < g_rlen - 2)) {
         x_range = 'y';
         continue;
      }
      /*---(range)-----------------------*/
      if (x_range == 'y') {
         if  (x_ch < x_sch) {
            yREGEX__comp_setclr (x_unmark);
            return rce;
         }
         for (j = x_sch; j <= x_ch; ++j)  s_map [j] = x_mark;
      }
      /*---(single)----------------------*/
      else s_map [x_ch] = x_mark;
      /*---(next)------------------------*/
      x_sch = x_ch;
      x_bslash = '-';
      x_range  = '-';
   }
   /*---(check for runon)----------------*/
   --rce;  if (i == g_rlen) {
      yREGEX__comp_setclr (x_unmark);
      return rce;
   }
   *a_rpos = i + 1;
   s_mapcount  = 0;
   for (i = 0; i < 256; ++i)   if (s_map [i] == '.')  ++s_mapcount;
   /*---(complete)-----------------------*/
   return 1;
}

char
yREGEX__comp_setstd  (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_NAME] = "";
   uchar       x_set       =    0;
   /*---(defense)------------------------*/
   --rce;  if (*a_rpos  <  1     )             return rce;
   --rce;  if (*a_rpos  >= g_rlen - 7)         return rce;
   --rce;  if (g_regex [*a_rpos - 1] != '[')   return rce;
   --rce;  if (g_regex [*a_rpos    ] != ':')   return rce;
   --rce;  if (g_regex [*a_rpos + 6] != ':')   return rce;
   --rce;  if (g_regex [*a_rpos + 7] != ']')   return rce;
   /*---(check for set)------------------*/
   sprintf (t, "%-5.5s", g_regex + *a_rpos + 1);
   x_set = yREGEX__comp_setname (t);
   /*---(append set)---------------------*/
   if (x_set > 0) {
      sprintf (t, "[%c", x_set);
      strlcat (g_comp, t, LEN_RECD);
      *a_rpos += 8;
      return 1;
   }
   /*---(complete)-----------------------*/
   --rce;
   return rce;
}

char
yREGEX__comp_set     (int *a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_NAME] = "";
   char        x_ch        =  ' ';
   uchar       x_set       =    0;
   x_ch   = g_regex [*a_rpos];
   if (x_ch == ':') {
      x_set = yREGEX__comp_setstd (a_rpos);
   }
   if (x_set == 0) {
      yREGEX__comp_setmap  (a_rpos);
      x_set = yREGEX__comp_setloc  ();
   }
   if (x_set == 0) {
      x_set = yREGEX__comp_setnew  ();
   }
   if (x_set < 0) return rce;
   sprintf (t, "[%c", x_set);
   strlcat (g_comp, t, LEN_RECD);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                         main driver                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char
yREGEX_comp          (cchar *a_regex)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char        x_ch        =  ' ';
   char        t           [LEN_NAME] = "";
   uchar       x_set       =   -1;
   char        x_bslash    =  '-';
   char        x_setbeg    =  '-';
   char        x_done      =  '-';
   /*---(prepare)------------------------*/
   rc = yREGEX__comp_init   (a_regex);
   if (rc < 0)  return rc;
   /*---(parse)--------------------------*/
   for (i = 0; i < g_rlen; ++i) {
      /*---(prepare)---------------------*/
      x_done = '-';
      x_ch   = g_regex [i];
      x_set  = 0;
      /*---(backslashed metas)-----------*/
      if (x_ch == G_KEY_BSLASH) {
         if (x_bslash != 'y') {
            x_bslash = 'y';
            continue;
         }
         x_bslash = '-';
      }
      if (x_bslash == 'y') {
         rc = yREGEX__comp_bslash (&i);
         continue;
      }
      /*---(set handling)----------------*/
      if (x_ch == '[' && x_setbeg != 'y') {
         x_setbeg  = 'y';
         continue;
      }
      if (x_setbeg == 'y') {
         rc = yREGEX__comp_set (&i);
         if (rc >= 0)  continue;
      }
   }
   /*> strlcpy (g_comp , g_regex , LEN_RECD);                                         <* 
    *> g_clen = g_rlen;                                                               <*/
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

#define       LEN_TEXT  2000
char          unit_answer [ LEN_TEXT ];

char*            /* [------] unit test accessor ------------------------------*/
yREGEX__unitcomp   (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           = 0;
   char        t           [40] = "0123456789abcdef0123456789abcdef";
   int         c           = 0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "REGEX_unitcomp, unknown request", 100);
   /*---(string testing)-----------------*/
   if      (strncmp (a_question, "map"       , 20)  == 0) {
      if (a_num < 0 || a_num > 15)
         snprintf (unit_answer, LEN_TEXT, "yREGEX_comp map  : %x %3d %2d [%-32.32s]", 0    , s_mapcount, 0, "unknown area");
      else
         for (i = 0; i < 32; ++i)  if (s_map [a_num * 32 + i] == '.') {
            t [i] = '_';
            ++c;
         }
      snprintf (unit_answer, LEN_TEXT, "yREGEX_comp map  : %x %3d %2d [%-32.32s]", a_num * 2, s_mapcount, c, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
