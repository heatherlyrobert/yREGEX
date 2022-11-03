/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"
#include    <stdio.h>
#include    <ySTR.h>
#include    <yCOLOR_solo.h>

#include    <regex.h>        /* POSIX  (04) regcomp, regexec, regfree         */



static char s_run        = 'y';
static char s_regex      [LEN_RECD] = "";
static char s_dump       = '-';
static char s_comp       = '-';


char
PROG_urgents            (int argc, char *argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(initialize)---------------------*/
   yURG_all_mute ();
   rc = yURG_logger  (argc, argv);
   rc = yURG_urgs    (argc, argv);
   return 0;
}



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
      if      (strcmp (a, "--base"      ) == 0)  s_run  = '-';
      else if (strcmp (a, "--regcomp"   ) == 0)  s_run  = 'c';
      else if (strcmp (a, "--yregex"    ) == 0)  s_run  = 'y';
      else if (strcmp (a, "--fast"      ) == 0)  s_run  = 'f';
      else if (strcmp (a, "--exec"      ) == 0)  s_run  = 'e';
      else if (strcmp (a, "--show"      ) == 0)  s_run  = 's';
      else if (strcmp (a, "--comped"    ) == 0)  s_comp = 'y';
      else if (strcmp (a, "--dump"      ) == 0)  s_dump = 'y';
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
   char        x_recd      [LEN_RECD]  = "";
   int         x_len       =    0;
   char        x_para      [LEN_RECD]  = "";
   int         x_npara     =    0;
   int         x_beg       =    0;
   int         x_end       =    0;
   int         l           =    0;
   int         a           =    0;
   int         c           =    0;
   regex_t     regex_comp;             /* regex pattern compilied             */
   char        x_empty     =  'y';
   int         x_nfind     =    0;
   int         x_abeg, x_alen;
   int         x_fbeg, x_flen;
   char        x_ftext     [LEN_RECD]  = "";
   int         i           =    0;
   char        x_edots     [LEN_RECD]  = "";
   int         x_left      =    0;
   char        t           [LEN_HUND]  = "";
   int         x_allfinds  =    0;
   int         b, e;
   /*---(defense)------------------------*/
   printf ("%s%s%s%s\n\n", BACK_RED, P_ONELINE, YSTR_EMPTY, BACK_OFF);
   rc = PROG_urgents (a_argc, a_argv);
   rc = PROG_args    (a_argc, a_argv);
   --rce;  if (rc < 0) {
      printf ("must include regex as argument\n");
      return rce;
   }
   /*> printf ("method %c\n"  , s_run);                                               <*/
   printf ("%ssource   %2då%sæ%s\n", BACK_MAG, strlen (s_regex), s_regex, BACK_OFF);
   /*---(prepare)------------------------*/
   for (i = 0; i < 10; ++i)   strlcat (x_edots, YSTR_EDOTS, LEN_RECD);
   /*---(compile)------------------------*/
   switch (s_run) {
   case 'y'  : case 'f'  : case 'e'  :
      rc = yREGEX_comp (s_regex);
      printf ("update   %2då%-.70sæ\n", strlen (myREGEX.orig), myREGEX.orig);
      printf ("\n");
      x_len = strlen (myREGEX.comp);
      printf ("encoded...\n");
      printf ("  base     å%-.70sæ\n", myREGEX.comp);
      for (i = 0; i < LEN_HUND; ++i) {
         if      (strchr ("(|&)"   , myREGEX.comp [i]) != NULL)  t [i] = yregex_comp__unit_map ('(', myREGEX.indx [i]);
         else if (strchr ("[]^$<>;", myREGEX.comp [i]) != NULL)  t [i] = yregex_comp__unit_map ('i', myREGEX.indx [i]);
         else                                                    t [i] = ' ';
      }
      t [x_len]    = 0;
      t [LEN_HUND] = 0;
      printf ("  indx     å%-.70sæ\n", t);
      printf ("  mods     å%-.70sæ\n", myREGEX.mods);
      for (i = 0; i < LEN_HUND; ++i) {
         if      (myREGEX.comp [i] == ';')  t [i] = yregex_comp__unit_map ('i', myREGEX.jump [i]);
         else                               t [i] = yregex_comp__unit_map ('j', myREGEX.jump [i]);
      }
      t [x_len]    = 0;
      t [LEN_HUND] = 0;
      printf ("  jump     å%-.70sæ\n", t);
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
      /*---(read a line)-----------------*/
      fgets (x_recd, LEN_RECD, stdin);
      if (feof (stdin)) break;
      ++a;
      x_len = strlen (x_recd);
      if (x_len > 0 && x_recd [x_len - 1] == '\n') x_recd [--x_len] = '\0';
      strldchg (x_recd, '`', '\'', LEN_RECD);
      strltrim (x_recd, ySTR_SINGLE, LEN_RECD);
      x_len = strlen (x_recd);
      if      (x_len == 0)      { x_empty = 'y';            }
      else if (x_empty == 'y')  { x_beg = a; x_empty = '-'; }
      /*---(group paragraphs)------------*/
      if (x_len > 0) {
         if (l > 0) {
            strlcat (x_para, " ", LEN_RECD);
            ++l;
         }
         strlcat (x_para, x_recd, LEN_RECD);
         l += x_len;
         continue;
      }
      if (l == 0)  continue;
      x_end = a - 1;
      ++x_npara;
      /*---(execute)---------------------*/
      switch (s_run) {
      case 's' :
         printf ("%6da %6db %6de %4dp %4dc %2dr  %s\n", a, x_beg, x_end, x_npara, c, rc, x_para);
         break;
      case 'e' :
         /*> rc = yREGEX_count  (x_para, &x_nfind);                                   <*/
         rc = yREGEX_exec   (x_para, &x_nfind, NULL, NULL);
         rc = yregex_find_count ();
         if (rc  > 0) {
            printf ("\n%s---beg ---end para seq cnt lenåcontents%s>%s\n", BACK_GRN, YSTR_DASH, BACK_OFF);
            printf ("%6d %6d %4d %3d %3d %3då%sæ\n", x_beg, x_end, x_npara, c, x_nfind, l, x_para);
            printf ("    %sfind -beg -len  ( focus  )%s\n", BACK_BLK, BACK_OFF);
            rc = yREGEX_find (YDLST_HEAD, &x_abeg, &x_alen, x_ftext, &x_fbeg, &x_flen);
            i  = 0;
            while (rc >= 0) {
               x_left = l - (x_abeg + x_alen);
               printf ("      %2d  %3d  %3d  (%3d  %3d) ", ++i, x_abeg, x_alen, x_fbeg, x_flen);
               printf ("%-*.*s", x_abeg, x_abeg, x_edots);
               if (x_alen == x_flen) {
                  printf ("%s", x_ftext);
               } else {
                  sprintf (t, "%-*.*s", x_fbeg, x_fbeg, x_ftext);
                  printf ("%s", t);
                  sprintf (t, "%s%-*.*s%s", BOLD_GRN, x_flen, x_flen, x_ftext + x_fbeg, BOLD_OFF);
                  printf ("%s", t);
                  sprintf (t, "%s", x_ftext + x_fbeg + x_flen);
                  printf ("%s", t);
               }
               printf ("%-*.*s\n", x_left, x_left, x_edots);
               rc = yREGEX_find (YDLST_NEXT, &x_abeg, &x_alen, x_ftext, &x_fbeg, &x_flen);
            }
            ++c;
            x_allfinds += x_nfind;
         }
         break;
      case 'f' :
         rc = yREGEX_filter (x_para);
         if (rc  > 0) {
            printf ("%6da %6db %6de %4dp %4dc %2dr  %s\n", a, x_beg, x_end, x_npara, c, rc, x_para);
            ++c;
         }
         break;
         /*> case 'y' :                                                                  <* 
          *>    rc = yREGEX_first (x_para);                                              <* 
          *>    if (rc  > 0)  ++c;                                                       <* 
          *>    break;                                                                   <*/
      case 'c' :
         rc = regexec (&regex_comp, x_para, 0, NULL, 0);
         if (rc == 0) {
            printf ("%6d %4d  %s\n", a, c, x_para);
            ++c;
         }
         break;
      }
      if (s_dump == 'y') {
         /*> yREGEX_dump  ();                                                         <*/
         yREGEX_finds ();
      }
      /*---(clean-up)-------------------*/
      strlcpy (x_para, "", LEN_RECD);
      l = 0;
      /*---(done)-----------------------*/
   }
   if (s_run == 'c') regfree (&regex_comp);
   printf ("\n%d lines reviewed in %d paragrahs; found %d in %d paragraphs\n", a, x_npara, x_allfinds, c);
   /*---(complete)-----------------------*/
   return 0;
}

