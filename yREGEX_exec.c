/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



char        g_source    [LEN_RECD]  = "";
int         g_slen      = -1;

char
yREGEX__literal      (int a_depth, int a_tpos, int a_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_depth >= 100   )  return rce;
   --rce;  if (a_tpos  <  0     )  return rce;
   --rce;  if (a_tpos  >= g_slen)  return rce;
   --rce;  if (a_rpos  <  0     )  return rce;
   --rce;  if (a_rpos  >= g_clen)  return rce;
   /*---(check)--------------------------*/
   if (g_comp [a_rpos] == g_source [a_tpos]) return 1;
   /*---(complete)-----------------------*/
   return 0;
}

