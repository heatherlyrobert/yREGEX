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



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yREGEX_ver   [500];

char*        /*-> return library versioning ----------[ leaf   [gs.420.012.00]*/ /*-[00.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yREGEX_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strlcpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 15);
#else
   strlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (yREGEX_ver, 100, "%s   %s : %s", t, YREGEX_VER_NUM, YREGEX_VER_TXT);
   return yREGEX_ver;
}






/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char         /*-> set up quiet testing ---------------[ light  [uz.210.011.02]*/ /*-[00.0000.00#.A]-*/ /*-[--.---.---.--]-*/
yREGEX__unitquiet     (void)
{
   char       *x_args [1]  = { "yREGEX_unit" };
   yURG_logger (1, x_args);
   yURG_urgs   (1, x_args);
   return 0;
}

char         /*-> set up debugged testing ------------[ light  [uz.211.011.03]*/ /*-[00.0000.00#.2]-*/ /*-[--.---.---.--]-*/
yREGEX__unitloud      (void)
{
   char       *x_args [3]  = { "yREGEX_unit", "@@kitchen", "@@YREGEX"    };
   yURG_logger (3, x_args);
   yLOG_info   ("yREGEX"  , yREGEX_version   ());
   yURG_urgs   (3, x_args);
   return 0;
}

char         /*-> stop testing -----------------------[ light  [uz.211.001.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yREGEX__unitend       (void)
{
   yLOG_end     ();
   return 0;
}



/*===============================[[ end code ]]===============================*/
