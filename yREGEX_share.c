/*===============================[[ beg code ]]===============================*/
#include    "yREGEX.h"
#include    "yREGEX_priv.h"



#define  IF_SETS   if      (a_type == TYPE_SETS)
#define  EL_PATS   else if (a_type == TYPE_PATS)
#define  EL_ERRS   else if (a_type == TYPE_ERRS)
#define  EL_FIND   else if (a_type == TYPE_FIND)
#define  EL_RULE   else if (a_type == TYPE_RULE)
#define  ELSE      else 

#define  UNHOOK_NEXT(a)   if (a->m_next != NULL) a->m_next->m_prev  = a->m_prev; else  *a_tail = a->m_prev;
#define  UNHOOK_PREV(a)   if (a->m_prev != NULL) a->m_prev->m_next  = a->m_next; else  *a_head = a->m_next;


/*====================------------------------------------====================*/
/*===----                       allocation/memory                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
yregex_share_new        (char a_type, void **r_new, void **a_head, void **a_tail, int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tERROR     *x_errs      = NULL;
   tFIND      *x_find      = NULL;
   tPATS      *x_pats      = NULL;
   tRULE      *x_rule      = NULL;
   tSETS      *x_sets      = NULL;
   void       *x_new       = NULL;
   int         x_tries     =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (r_new);
   --rce;  if (r_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*r_new);
   --rce;  if (*r_new != NULL) {
      DEBUG_DATA   yLOG_snote   ("already set");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   *r_new = NULL;
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      IF_SETS  x_new = malloc (sizeof (tSETS));
      EL_PATS  x_new = malloc (sizeof (tPATS));
      EL_ERRS  x_new = malloc (sizeof (tERROR));
      EL_FIND  x_new = malloc (sizeof (tFIND));
      EL_RULE  x_new = malloc (sizeof (tRULE));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_sint    (x_tries);
   DEBUG_DATA   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   IF_SETS  yregex_sets__wipe  (x_new);
   EL_PATS  yregex_pats__wipe  (x_new);
   EL_ERRS  yregex_error__wipe (x_new);
   EL_FIND  yregex_find__wipe  (x_new);
   /*---(hook)---------------------------*/
   if    (*a_tail == NULL) {
      DEBUG_DATA   yLOG_snote   ("first entry");
      *a_head = x_new;
   } else {
      DEBUG_DATA   yLOG_snote   ("append to tail");
      IF_SETS  {
         x_sets = (tSETS  *) x_new;    x_sets->m_prev  = *a_tail;
         x_sets = (tSETS  *) *a_tail;  x_sets->m_next = x_new;
      }
      EL_PATS  {
         x_pats = (tPATS  *) x_new;    x_pats->m_prev  = *a_tail;
         x_pats = (tPATS  *) *a_tail;  x_pats->m_next = x_new;
      }
      EL_ERRS  {
         x_errs = (tERROR *) x_new;    x_errs->m_prev  = *a_tail;
         x_errs = (tERROR *) *a_tail;  x_errs->m_next = x_new;
      }
      EL_FIND  {
         x_find = (tFIND  *) x_new;    x_find->m_prev  = *a_tail;
         x_find = (tFIND  *) *a_tail;  x_find->m_next = x_new;
      }
   }
   *a_tail = x_new;
   ++(*a_count);
   /*---(save return)--------------------*/
   *r_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yregex_share_free       (char a_type, void **r_old, void **a_head, void **a_tail, int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tERROR     *x_errs      = NULL;
   tFIND      *x_find      = NULL;
   tPATS      *x_pats      = NULL;
   tRULE      *x_rule      = NULL;
   tSETS      *x_sets      = NULL;
   void       *x_old       = NULL;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (r_old);
   --rce;  if (r_old == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*r_old);
   --rce;  if (*r_old == NULL) {
      DEBUG_DATA   yLOG_snote   ("never set");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(simplify)-----------------------*/
   x_old = (tSETS *) *r_old;
   /*---(detach and decrement)-----------*/
   IF_SETS { x_sets = (tSETS  *) *r_old; UNHOOK_NEXT(x_sets); UNHOOK_PREV(x_sets); }
   EL_PATS { x_pats = (tPATS  *) *r_old; UNHOOK_NEXT(x_pats); UNHOOK_PREV(x_pats); }
   EL_ERRS { x_errs = (tERROR *) *r_old; UNHOOK_NEXT(x_errs); UNHOOK_PREV(x_errs); }
   EL_FIND { x_find = (tFIND  *) *r_old; UNHOOK_NEXT(x_find); UNHOOK_PREV(x_find); }
   EL_RULE { x_rule = (tRULE  *) *r_old; UNHOOK_NEXT(x_rule); UNHOOK_PREV(x_rule); }
   /*---(free details)-------------------*/
   IF_SETS {
      if (x_sets->source != BASE_ENTRY && x_sets->name != NULL)   free (x_sets->name);
      x_sets->name = NULL;
      if (x_sets->source != BASE_ENTRY && x_sets->map  != NULL)   free (x_sets->map );
      x_sets->map  = NULL;
   } EL_PATS {
      if (x_pats->source != BASE_ENTRY && x_pats->name != NULL)   free (x_pats->name);
      x_pats->name = NULL;
      if (x_pats->source != BASE_ENTRY && x_pats->pat  != NULL)   free (x_pats->pat );
      x_pats->pat  = NULL;
   } EL_ERRS {
      if (x_errs->cat  != NULL)  free (x_errs->cat);
      if (x_errs->msg  != NULL)  free (x_errs->msg);
   } EL_FIND {
      for (i = 0; i < MAX_SUB; ++i) {
         if (x_find->subs [i] != NULL) {
            if (x_find->subs [i]->text != NULL)   free (x_find->subs [i]->text);
            x_find->subs [i]->text = NULL;
            if (x_find->subs [i]->quan != NULL)   free (x_find->subs [i]->quan);
            x_find->subs [i]->quan = NULL;
         }
         x_find->subs [i] = NULL;
      }
      if (x_find->text != NULL)   free (x_find->text);
      x_find->text = NULL;
      if (x_find->quan != NULL)   free (x_find->quan);
      x_find->quan = NULL;
   } EL_RULE {
      if (x_rule->str  != NULL)  free (x_rule->str);
   }
   /*---(free and ground)----------------*/
   free (*r_old);
   *r_old = NULL;
   /*---(decrement)----------------------*/
   --(*a_count);
   DEBUG_DATA   yLOG_sint    (*a_count);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
yregex_share_init       (char a_type, void **a_head, void **a_tail, void **a_curr, int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(ground everything)--------------*/
   *a_head  =  *a_tail = *a_curr = NULL;
   *a_count = 0;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yregex_share_purge      (char a_type, void **a_head, void **a_tail, void **a_curr, int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   void       *x_curr      = NULL;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(walk level)---------------------*/
   x_curr = *a_head;
   while (x_curr != NULL) {
      IF_SETS  yregex_sets__free  (&x_curr);
      EL_PATS  yregex_pats__free  (&x_curr);
      EL_ERRS  yregex_error__free (&x_curr);
      EL_FIND  yregex_find__free  (&x_curr);
      x_curr = *a_head;
   }
   /*---(ground everything)--------------*/
   *a_head  =  *a_tail = *a_curr = NULL;
   *a_count = 0;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yregex_share_wrap       (char a_type, void **a_head, void **a_tail, void **a_curr, int *a_count)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   yregex_share_purge (a_type, a_head, a_tail, a_curr, a_count);
   yregex_share_init  (a_type, a_head, a_tail, a_curr, a_count);
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        searching entries                     ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char
yregex_share__by_cursor (char a_type, void **a_head, void **a_tail, void **r_curr, void **r_back, char a_move)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tERROR     *x_errs      = NULL;
   tFIND      *x_find      = NULL;
   tPATS      *x_pats      = NULL;
   tRULE      *x_rule      = NULL;
   tSETS      *x_sets      = NULL;
   void       *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_NORM   yLOG_senter  (__FUNCTION__);
   DEBUG_NORM   yLOG_schar   (a_move);
   /*---(defaults)-----------------------*/
   if (r_back != NULL)  *r_back = NULL;
   /*---(starting point)-----------------*/
   x_curr  = *r_curr;
   /*---(defense)------------------------*/
   DEBUG_NORM   yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      /*---(bounce-types)----------------*/
      switch (a_move) {
      case YDLST_HEAD : case YDLST_DHEAD : case YDLST_NEXT :
         x_curr = *a_head;
         break;
      case YDLST_TAIL : case YDLST_DTAIL : case YDLST_PREV :
         x_curr = *a_tail;
         break;
      }
      /*---(bounce types)----------------*/
      DEBUG_NORM    yLOG_spoint  (x_curr);
      if (x_curr == NULL) {
         DEBUG_NORM    yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(switch)-------------------------*/
   --rce;  switch (a_move) {
   case YDLST_HEAD : case YDLST_DHEAD :
      x_curr = *a_head;
      break;
   case YDLST_PREV : case YDLST_DPREV :
      IF_SETS  { x_sets = (tSETS  *) x_curr;  x_curr = x_sets->m_prev; }
      EL_PATS  { x_pats = (tPATS  *) x_curr;  x_curr = x_pats->m_prev; }
      EL_ERRS  { x_errs = (tERROR *) x_curr;  x_curr = x_errs->m_prev; }
      EL_FIND  { x_find = (tFIND  *) x_curr;  x_curr = x_find->m_prev; }
      break;
   case YDLST_CURR : case YDLST_DCURR :
      break;
   case YDLST_NEXT : case YDLST_DNEXT :
      IF_SETS  { x_sets = (tSETS  *) x_curr;  x_curr = x_sets->m_next; }
      EL_PATS  { x_pats = (tPATS  *) x_curr;  x_curr = x_pats->m_next; }
      EL_ERRS  { x_errs = (tERROR *) x_curr;  x_curr = x_errs->m_next; }
      EL_FIND  { x_find = (tFIND  *) x_curr;  x_curr = x_find->m_next; }
      break;
   case YDLST_TAIL : case YDLST_DTAIL :
      x_curr = *a_tail;
      break;
   default         :
      DEBUG_NORM   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_NORM   yLOG_spoint  (x_curr);
   /*---(check end)----------------------*/
   --rce;  if (x_curr == NULL) {
      /*---(bounce off ends)-------------*/
      if (a_move == YDLST_PREV)  x_curr  = *a_head;
      if (a_move == YDLST_NEXT)  x_curr  = *a_tail;
      /*---(no bounce)-------------------*/
      if (x_curr == NULL) {
         *r_curr = x_curr;
         DEBUG_NORM    yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(mark trouble)----------------*/
      DEBUG_NORM    yLOG_snote   ("BOUNCE");
      rc = rce;
      /*---(done)------------------------*/
   }
   /*---(save back)----------------------*/
   *r_curr = x_curr;
   if (r_back != NULL)  *r_back = x_curr;
   /*---(complete)-----------------------*/
   DEBUG_NORM   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yregex_share__by_index  (char a_type, void **a_head, void **r_curr, void **r_back, int a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tERROR     *x_errs      = NULL;
   tFIND      *x_find      = NULL;
   tPATS      *x_pats      = NULL;
   tRULE      *x_rule      = NULL;
   tSETS      *x_sets      = NULL;
   void       *x_curr      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   DEBUG_DATA   yLOG_sint    (a_index);
   /*---(default)------------------------*/
   if (r_back != NULL)  *r_back = NULL;
   /*---(short-cut)----------------------*/
   --rce;  if (a_index == -1) {
      DEBUG_DATA   yLOG_snote   ("requested current");
      x_curr = *r_curr;
      if (r_back != NULL)  *r_back = x_curr;
      DEBUG_DATA   yLOG_spoint  (x_curr);
      --rce;  if (x_curr == NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   x_curr = *a_head;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_sint    (a_index);
   --rce;  if (a_index < -1) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk data)----------------------*/
   while (x_curr != NULL) {
      if (c == a_index)  break;
      ++c;
      IF_SETS  { x_sets = (tSETS  *) x_curr;  x_curr = x_sets->m_next; }
      EL_PATS  { x_pats = (tPATS  *) x_curr;  x_curr = x_pats->m_next; }
      EL_ERRS  { x_errs = (tERROR *) x_curr;  x_curr = x_errs->m_next; }
      EL_FIND  { x_find = (tFIND  *) x_curr;  x_curr = x_find->m_next; }
   }
   /*---(check result)-------------------*/
   DEBUG_DATA   yLOG_sint    (x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   *r_curr = x_curr;
   if (r_back != NULL)  *r_back = x_curr;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

int          /*-> retrieve pattern by abbeviation ----[ leaf   [fc.632.122.40]*/ /*-[01.0000.01#.8]-*/ /*-[--.---.---.--]-*/
yregex_share__by_abbr   (char a_type, void **a_head, void **r_back, char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =    0;
   char        x_abbr      =    0;
   char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
   tERROR     *x_errs      = NULL;
   tFIND      *x_find      = NULL;
   tPATS      *x_pats      = NULL;
   tRULE      *x_rule      = NULL;
   tSETS      *x_sets      = NULL;
   void       *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter  (__FUNCTION__);
   DEBUG_YREGEX  yLOG_sint    (a_abbr);
   /*---(default)------------------------*/
   if (r_back != NULL)  *r_back = NULL;
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
   /*---(walk through sets)--------------*/
   x_curr = *a_head;
   while (x_curr != NULL) {
      IF_SETS  { x_sets = (tSETS  *) x_curr;  x_abbr = x_sets->abbr; }
      EL_PATS  { x_pats = (tPATS  *) x_curr;  x_abbr = x_pats->abbr; }
      if (x_abbr == a_abbr)  break;
      ++n;
      IF_SETS  { x_sets = (tSETS  *) x_curr;  x_curr = x_sets->m_next; }
      EL_PATS  { x_pats = (tPATS  *) x_curr;  x_curr = x_pats->m_next; }
   }
   /*---(check)--------------------------*/
   DEBUG_YREGEX  yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(saveback)-----------------------*/
   DEBUG_YREGEX  yLOG_snote   ("found");
   if (r_back != NULL)  *r_back = x_curr;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return n;
}

int          /*-> retrieve pattern by name -----------[ leaf   [fe.A53.145.A0]*/ /*-[01.0000.02#.E]-*/ /*-[--.---.---.--]-*/
yregex_share__by_name   (char a_type, void **a_head, void **r_back, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   int         n           =    0;
   char       *x_name      = NULL;
   tERROR     *x_errs      = NULL;
   tFIND      *x_find      = NULL;
   tPATS      *x_pats      = NULL;
   tRULE      *x_rule      = NULL;
   tSETS      *x_sets      = NULL;
   void       *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YREGEX  yLOG_senter   (__FUNCTION__);
   DEBUG_YREGEX  yLOG_spoint   (a_name);
   /*---(default)------------------------*/
   if (r_back != NULL)  *r_back = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL) {
      DEBUG_YREGEX  yLOG_sexitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YREGEX  yLOG_snote    (a_name);
   x_len = strllen (a_name, LEN_NAME);
   DEBUG_YREGEX  yLOG_sint     (x_len);
   --rce;  if (x_len <  2) {
      DEBUG_YREGEX  yLOG_snote    ("too short");
      DEBUG_YREGEX  yLOG_sexitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len >  15) {
      DEBUG_YREGEX  yLOG_snote    ("too long");
      DEBUG_YREGEX  yLOG_sexitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk through sets)--------------*/
   x_curr = *a_head;
   while (x_curr != NULL) {
      IF_SETS  { x_sets = (tSETS  *) x_curr;  x_name = x_sets->name; }
      EL_PATS  { x_pats = (tPATS  *) x_curr;  x_name = x_pats->name; }
      if (strcmp (x_name, a_name) == 0)  break;
      ++n;
      IF_SETS  { x_sets = (tSETS  *) x_curr;  x_curr = x_sets->m_next; }
      EL_PATS  { x_pats = (tPATS  *) x_curr;  x_curr = x_pats->m_next; }
   }
   /*---(check)--------------------------*/
   DEBUG_YREGEX  yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YREGEX  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(saveback)-----------------------*/
   DEBUG_YREGEX  yLOG_snote   ("found");
   if (r_back != NULL)  *r_back = x_curr;
   /*---(complete)-----------------------*/
   DEBUG_YREGEX  yLOG_sexit   (__FUNCTION__);
   return n;
}

