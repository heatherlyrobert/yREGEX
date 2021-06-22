/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



/*---(main data structure)------------*/
tREGEX      gre;



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
   strlcpy (t, "[hephaestus ]", 15);
#else
   strlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (yREGEX_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yREGEX_ver;
}

char
yREGEX_clear            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_enter   (__FUNCTION__);
   /*---(comparison text)----------------*/
   strlcpy (gre.text , ""       , LEN_TEXT);
   gre.tlen = 0;
   /*---(scorer)-------------------------*/
   gre.scorer = '?';
   /*---(original)-----------------------*/
   strlcpy (gre.orig , ""       , LEN_REGEX);
   gre.olen = 0;
   /*---(regex)--------------------------*/
   strlcpy (gre.regex, ""       , LEN_REGEX);
   gre.rlen = 0;
   /*---(initialize compiled)------------*/
   for (i = 0; i < LEN_REGEX; ++i) {
      gre.comp [i] =   0;
      gre.indx [i] =   0;
      gre.mods [i] =   0;
      gre.jump [i] =   0;
   }
   gre.clen = 0;
   /*---(initialize grouping)------------*/
   strlcpy (gre.groups, "               ", LEN_LABEL);
   /*---(initialize sets)----------------*/
   yregex_sets_prep ();
   yregex_rule_init ();
   gre.ready = '-';
   /*---(initialize sets)----------------*/
   DEBUG_YREGEX  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          test access                         ----===*/
/*====================------------------------------------====================*/
static void      o___TESTERS_________________o (void) {;}

char*
yREGEX__testloc      (cchar *a_regex, cchar *a_source)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;
   /*---(compile)------------------------*/
   rc = yREGEX_comp (a_regex);
   if (rc <  0)   return "yREGEX_tester    : compilation failed";
   /*---(execute)------------------------*/
   rc = yREGEX_exec (a_source);
   if (rc <  0)   return "yREGEX_tester    : execution failed";
   /*---(question)-----------------------*/
   return yregex_find__unit ("match", 0);
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char         /*-> set up quiet testing ---------------[ light  [uz.210.011.02]*/ /*-[00.0000.00#.A]-*/ /*-[--.---.---.--]-*/
yregex__unit_quiet      (void)
{
   char       *x_args [1]  = { "yREGEX_unit" };
   yURG_logger (1, x_args);
   yURG_urgs   (1, x_args);
   EXEC_init       ();
   yregex_err_init ();
   return 0;
}

char         /*-> set up debugged testing ------------[ light  [uz.211.011.03]*/ /*-[00.0000.00#.2]-*/ /*-[--.---.---.--]-*/
yregex__unit_loud       (void)
{
   char       *x_args [3]  = { "yREGEX_unit", "@@kitchen", "@@YREGEX"    };
   yURG_logger (3, x_args);
   yLOG_info   ("yREGEX"  , yREGEX_version   ());
   yURG_urgs   (3, x_args);
   EXEC_init       ();
   yregex_err_init ();
   return 0;
}

char         /*-> stop testing -----------------------[ light  [uz.211.001.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yregex__unit_end        (void)
{
   yregex_err_wrap ();
   EXEC_wrap       ();
   yLOGS_end     ();
   return 0;
}



/*===============================[[ end code ]]===============================*/
