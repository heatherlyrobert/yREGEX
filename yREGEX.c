/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"


/*> struct cERROR {                                                                   <* 
 *>    char        id;                                                                <* 
 *>    char        desc;                                                              <* 
 *> } s_errors [MAX_ERRORS] = {                                                       <* 
 *>    {  -11, "source argument is null"                      },                      <* 
 *>    {  -12, "source argument is empty"                     },                      <* 
 *>    {  -13, "regex argument is null"                       },                      <* 
 *>    {  -14, "regex argument is empty"                      },                      <* 
 *>                                                                                   <* 
 *> }                                                                                 <*/

struct cSETS {
   int         id;
   char        type;
   char        name        [LEN_NAME];
   char        map         [256];
} s_sets [MAX_SETS] = {
   /*             0         1            0               1               2               3               4               5               6               7               8               9               A               B               C               D               E               F                 */
   /* -id- type   01234567890123456789   0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef  */
   /*                                                                     !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   /*---(metas)----------------*/
   /* -id- type   ---name-------------                                    !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { 0   , '.', "dot"                , "                                ...............................................................................................                                  ..............................................................................................." },
   { 1   , 'e', "escape"             , "                       .                                                                                                                                                                                                                                        " },
   { 2   , 'n', "return"             , "          . ..                                                                                                                                                                                                                                                  " },
   { 3   , 't', "tab"                , "         . .                                                                                                                                                                                                                                                    " },
   { 4   , 's', "whitespace"         , "         .....                  .                                                                                                                                                                                                                               " },
   { 5   , 'w', "word"               , "                                                ..........       ..........................    . ..........................                                                                                                                                     " },
   /*---(categories)-----------*/
   /* -id- type   ---name-------------                                    !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~½                                 ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ  */
   { 0   , '-', "alpha"              , "                                                                 ..........................      ..........................                                                                                                                                     " },
   { 0   , '-', "alnum"              , "                                                ..........       ..........................      ..........................                                                                                                                                     " },
   { 0   , '-', "digit"              , "                                                ..........                                                                                                                                                                                                      " },
   { 0   , '-', "punct"              , "                                 ...............          .......                          ......                          ....                                                                                                                                 " },
   { 0   , '-', "lower"              , "                                                                                                 ..........................                                                                                                                                     " },
   { 0   , '-', "upper"              , "                                                                 ..........................                                                                                                                                                                     " },
   { 0   , '-', "xdigit"             , "                                                ..........       ......                          ......                                                                                                                                                         " },
   { 0   , '-', "graph"              , "                                 ..............................................................................................                                  ..............................................................................................." },
   { 0   , '-', "print"              , "                                ...............................................................................................                                  ..............................................................................................." },
   { 0   , '-', "cntrl"              , "................................                                                                                               .                                                                                                                                " },
   { 0   , '-', "blank"              , "         .                      .                                                                                                                                                                                                                               " },
   /*---(specialty)------------*/
   /*---(new ones)-------------*/
   { 0   , '-', ""                   , "                                                                                                                                                                                                                                                                " },
   /*---(done)-----------------*/
};
int         s_nset      = 0;

char        s_source    [LEN_RECD]  = "";
int         s_slen      = -1;

char        s_regex     [LEN_RECD]  = "";
int         s_rlen      = -1;

char        s_comp      [LEN_RECD]  = "";
int         s_clen      = -1;

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
   s_rlen = strllen (a_regex , LEN_RECD);
   --rce;  if (s_rlen <= 0   )  return rce;
   rc = strlcpy (s_regex, a_regex , LEN_RECD);
   --rce;  if (rc     <  0   )  return rce;
   /*---(initialize)---------------------*/
   strlcpy (s_comp , s_regex , LEN_RECD);
   s_clen = s_rlen;
   /*---(initialize sets)----------------*/
   s_nset = 0;
   for (i = 0; i < MAX_SETS; ++i) {
      if (s_sets [i].type != ' ') {
         ++s_nset;
         continue;
      }
      s_sets [i].type     = ' ';
      strlcpy (s_sets [i].name, "", LEN_NAME);
      for (j = 0; j < 256;  ++j)   s_sets [i].map [j] = ' ';
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yREGEX__exec_init    (cchar *a_src)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   char        j           =    0;
   /*---(check source)-------------------*/
   --rce;  if (a_src == NULL)  return rce;
   s_slen = strllen (a_src, LEN_RECD);
   --rce;  if (s_slen <= 0   )  return rce;
   rc = strlcpy (s_source, a_src, LEN_RECD);
   --rce;  if (rc     <  0   )  return rce;
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
   /*---(prepare)------------------------*/
   rc = yREGEX__comp_init   (a_regex);
   if (rc < 0)  return rc;
   /*---(parse)--------------------------*/
   /*> for (i = 0; i < s_rlen; ++i) {                                                 <* 
    *>    x_ch = s_regex [i];                                                         <* 
    *>    switch (x_ch) {                                                             <* 
    *>    case '.' :  yREGEX_set_meta ('.'); break;                                   <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*> strlcpy (s_comp , s_regex , LEN_RECD);                                         <* 
    *> s_clen = s_rlen;                                                               <*/
   /*---(complete)-----------------------*/
   return 0;
}

char
yREGEX__literal      (int a_depth, int a_tpos, int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_depth >= 100   )  return rce;
   --rce;  if (a_tpos  <  0     )  return rce;
   --rce;  if (a_tpos  >= s_slen)  return rce;
   --rce;  if (a_rpos  <  0     )  return rce;
   --rce;  if (a_rpos  >= s_clen)  return rce;
   /*---(check)--------------------------*/
   if (s_comp [a_rpos] == s_source [a_tpos]) return 1;
   /*---(complete)-----------------------*/
   return 0;
}

char
yREGEX__set          (int a_depth, int a_tpos, int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   uchar       x_set       =   -1;
   uchar       x_ch        =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_depth >= 100   )           return rce;
   --rce;  if (a_tpos  <  0     )           return rce;
   --rce;  if (a_tpos  >= s_slen)           return rce;
   --rce;  if (a_rpos  <  1     )           return rce;
   --rce;  if (a_rpos  >= s_clen)           return rce;
   --rce;  if (s_comp [a_rpos - 1] != '[')  return rce;
   /*---(get the set)--------------------*/
   x_set = s_comp   [a_rpos];
   --rce;  if (x_set <  0     )             return rce;
   --rce;  if (x_set >= s_nset)             return rce;
   /*---(check)--------------------------*/
   x_ch  = s_source [a_tpos];
   if (s_sets [x_set].map [x_ch] == '.')  return 1;
   /*---(complete)-----------------------*/
   return 0;
}

char
yREGEX_driver        (int a_depth, int a_tpos, int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   rc = yREGEX__literal (a_depth, a_tpos, a_rpos);
   return rc;
}

char
yREGEX_exec          (cchar *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(prepare)------------------------*/
   rc = yREGEX__exec_init   (a_source);
   if (rc < 0)  return rc;
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
yREGEX__unit       (char *a_question, int a_num)
{
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "yREGEX_unit, unknown request", 100);
   /*---(string testing)-----------------*/
   /*> if      (strncmp(a_question, "string"    , 20)  == 0) {                        <* 
    *>    snprintf (unit_answer, LEN_TEXT, "ySTR string      : [%s]", its.strtest);   <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   return unit_answer;
}

char       /*----: set up program urgents/debugging --------------------------*/
yREGEX__unitquiet     (void)
{
   its.logger = yLOG_begin ("ySTR" , yLOG_SYSTEM, yLOG_QUIET);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yREGEX__unitloud      (void)
{
   its.logger = yLOG_begin ("ySTR" , yLOG_SYSTEM, yLOG_NOISE);
   /*> yLOG_info     ("ySTR"    , ySTR_version   ());                                 <*/
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yREGEX__unitend       (void)
{
   yLOG_end     ();
   return 0;
}



/*===============================[[ end code ]]===============================*/
