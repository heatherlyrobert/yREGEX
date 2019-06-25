/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    <stdio.h>
#include    <ySTR.h>

#include    <regex.h>        /* POSIX  (04) regcomp, regexec, regfree         */



static char s_run        = 'y';
static char s_regex      [LEN_RECD] = "";



char         /*-> process the command line args ------[ ------ [gz.952.251.B4]*/ /*-[01.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG_args          (int argc, char *argv[])
{
   /*---(locals)-------------------------*/
   int         i           = 0;
   char       *a           = NULL;
   int         x_total     = 0;
   int         x_args      = 0;
   /*---(process)------------------------*/
   for (i = 1; i < argc; ++i) {
      a = argv[i];
      ++x_total;
      if (a[0] == '@')  continue;
      ++x_args;
      if      (strcmp (a, "--base"      ) == 0)  s_run = '-';
      else if (strcmp (a, "--regcomp"   ) == 0)  s_run = 'c';
      else if (strcmp (a, "--yregex"    ) == 0)  s_run = 'y';
      else if (strcmp (a, "--fast"      ) == 0)  s_run = 'f';
      else if (a[0] != '-'              )  strlcpy (s_regex , argv[i]  , LEN_RECD);
   }
   if (strlen (s_regex) == 0) return -10;
   /*---(complete)-----------------------*/
   return 0;
}

char
main          (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   int         x_beg       =    0;
   int         a           =    0;
   int         c           =    0;
   regex_t     regex_comp;             /* regex pattern compilied             */
   /*---(defense)------------------------*/
   printf ("prog   [%s]\n", a_argv [0]);
   rc = PROG_args (a_argc, a_argv);
   --rce;  if (rc < 0) {
      printf ("must include regex as argument\n");
      return rce;
   }
   printf ("regex  [%s]\n", s_regex);
   printf ("method %c\n"  , s_run);
   /*---(compile)------------------------*/
   switch (s_run) {
   case 'y'  : case 'f'  :
      rc = yREGEX_comp (s_regex);
      break;
   case 'c'  :
      rc = regcomp (&regex_comp, s_regex, REG_EXTENDED);
      break;
   }
   --rce;  if (rc < 0) {
      printf ("regular expression could not be compiled\n");
      return rce;
   }
   /*---(run through text)---------------*/
   while (1) {
      /*---(standard)--------------------*/
      fgets (x_recd, LEN_RECD, stdin);
      if (feof (stdin)) break;
      x_len = strlen (x_recd);
      if (x_len > 0)  x_recd [--x_len] = '\0';
      /*---(execute)---------------------*/
      ++a;
      switch (s_run) {
      case 'f' :
         rc = yREGEX_fast (x_recd);
         if (rc  > 0)  ++c;
         break;
      case 'y' :
         rc = yREGEX_exec (x_recd);
         if (rc  > 0)  ++c;
         break;
      case 'c' :
         rc = regexec (&regex_comp, x_recd, 0, NULL, 0);
         if (rc == 0)  ++c;
         break;
      }
      /*> if (a % 100  == 0)  printf ("%06d (%06d)\n", a, c);                         <*/
   }
   if (s_run == 'c') regfree (&regex_comp);
   printf ("read %d, found %d\n", a, c);
   /*---(complete)-----------------------*/
   return 0;
}

