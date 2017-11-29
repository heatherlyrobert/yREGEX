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
   g_slen = strllen (a_src, LEN_RECD);
   --rce;  if (g_slen <= 0   )  return rce;
   rc = strlcpy (g_source, a_src, LEN_RECD);
   --rce;  if (rc     <  0   )  return rce;
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
   --rce;  if (a_tpos  >= g_slen)           return rce;
   --rce;  if (a_rpos  <  1     )           return rce;
   --rce;  if (a_rpos  >= g_clen)           return rce;
   --rce;  if (g_comp [a_rpos - 1] != '[')  return rce;
   /*---(get the set)--------------------*/
   x_set = g_comp   [a_rpos];
   --rce;  if (x_set <  0     )             return rce;
   --rce;  if (x_set >= g_nset)             return rce;
   /*---(check)--------------------------*/
   x_ch  = g_source [a_tpos];
   if (g_sets [x_set].map [x_ch] == '.')  return 1;
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
