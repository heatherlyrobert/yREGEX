/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"

tSETS       g_sets [MAX_SETS] = {
   /*       0         1            0               1               2               3               4               5               6               7               8               9               A               B               C               D               E               F                 */
   /*type   01234567890123456789   0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef  */
   /*                                                                     !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { '-', "---beg---"          , "                                                                                                                                                                                                                                                                " },
   /*---(metas)----------------*/
   /*type   ---name-------------                                    !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { 'e', "escape"             , "                       .                                                                                                                                                                                                                                        " },
   { 'n', "return"             , "          . ..                                                                                                                                                                                                                                                  " },
   { 't', "tab"                , "         . .                                                                                                                                                                                                                                                    " },
   { 's', "whitespace"         , "         .....                  .                                                                                                                                                                                                                               " },
   { 'w', "word"               , "                                                ..........       ..........................    . ..........................                                                                                                                                     " },
   /*---(categories)-----------*/
   /*type   ---name-------------                                    !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { '-', "dot"                , "                                ...............................................................................................                                  ..............................................................................................." },
   { '-', "alpha"              , "                                                                 ..........................      ..........................                                                                                                                                     " },
   { '-', "alnum"              , "                                                ..........       ..........................      ..........................                                                                                                                                     " },
   { '-', "digit"              , "                                                ..........                                                                                                                                                                                                      " },
   { '-', "punct"              , "                                 ...............          .......                          ......                          ....                                                                                                                                 " },
   { '-', "lower"              , "                                                                                                 ..........................                                                                                                                                     " },
   { '-', "upper"              , "                                                                 ..........................                                                                                                                                                                     " },
   { '-', "xdigit"             , "                                                ..........       ......                          ......                                                                                                                                                         " },
   { '-', "graph"              , "                                 ..............................................................................................                                  ..............................................................................................." },
   { '-', "print"              , "                                ...............................................................................................                                  ..............................................................................................." },
   { '-', "cntrl"              , "................................                                                                                               .                                                                                                                                " },
   { '-', "blank"              , "         .                      .                                                                                                                                                                                                                               " },
   /*---(specialty)------------*/
   { ' ', ""                   , "                                                                                                                                                                                                                                                                " },
   /*---(new ones)-------------*/
   { ' ', ""                   , "                                                                                                                                                                                                                                                                " },
   /*---(done)-----------------*/
   {  0 , ""                   , "                                                                                                                                                                                                                                                                " },
};
int         g_nset      = 0;

char        g_regex     [LEN_RECD]  = "";
int         g_rlen      = -1;

char        g_comp      [LEN_RECD]  = "";
int         g_clen      = -1;


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
   g_nset = 0;
   for (i = 0; i < MAX_SETS; ++i) {
      if (g_sets [i].type != 0   && g_sets [i].type != ' ') {
         ++g_nset;
         continue;
      }
      g_sets [i].type     = 0;
      strlcpy (g_sets [i].name, "", LEN_NAME);
      for (j = 0; j < 256;  ++j)   g_sets [i].map [j] = ' ';
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yREGEX__comp_abbr    (cchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_set       =   -1;
   int         i           =    0;
   for (i = 0; i < g_nset; ++i) {
      if (g_sets [i].type == 0     )  break;
      if (g_sets [i].type == '-'   )  continue;
      if (g_sets [i].type == ' '   )  continue;
      if (g_sets [i].type != a_abbr)  continue;
      return i;
   }
   return 0;
}

char
yREGEX__comp_bslash  (cint a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_set       =    0;
   char        t           [LEN_NAME] = "";
   uchar       x_ch        =  '-';
   /*---(defense)------------------------*/
   --rce;  if (a_rpos  <  1     )             return rce;
   --rce;  if (a_rpos  >= g_rlen)             return rce;
   --rce;  if (g_regex [a_rpos - 1] != '\\')  return rce;
   /*---(check for set)------------------*/
   x_ch  = g_regex [a_rpos];
   if (strchr ("entsw", x_ch) != NULL) {
      x_set = yREGEX__comp_abbr (x_ch);
   }
   /*---(append set)---------------------*/
   if (x_set > 0) {
      sprintf (t, "[%c", x_set);
      strlcat (g_comp, t, LEN_RECD);
      return 1;
   }
   /*---(literal)------------------------*/
   sprintf (t, "%c", x_ch);
   strlcat (g_comp, t, LEN_RECD);
   /*---(complete)-----------------------*/
   return 0;
}

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
   char        x_done      =  '-';
   /*---(prepare)------------------------*/
   rc = yREGEX__comp_init   (a_regex);
   if (rc < 0)  return rc;
   /*---(parse)--------------------------*/
   for (i = 0; i < g_rlen; ++i) {
      /*---(prepare)---------------------*/
      x_done = '-';
      x_ch   = g_regex [i];
      /*---(backslashed metas)-----------*/
      if (x_ch == '\\') {
         if (x_bslash != 'y') {
            x_bslash = 'y';
            continue;
         }
         x_bslash = '-';
      }
      if (x_bslash == 'y') {
         yREGEX__comp_bslash (i);
         continue;
      }
   }
   /*> strlcpy (g_comp , g_regex , LEN_RECD);                                         <* 
    *> g_clen = g_rlen;                                                               <*/
   /*---(complete)-----------------------*/
   return 0;
}
