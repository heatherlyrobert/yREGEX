/*===============================[[ beg code ]]===============================*/

/*===[[ PURPOSE ]]==========================================================*/

/*   goals
 *   -- short and clean
 *   -- easy to maintain
 *   -- speed is secondary
 *   -- include all posix ere features
 *   -- add my own enhancements that mirror other places (vim, perl, ...)
 *   -- lots of error checking everywhere
 *   -- lots of phreaking debugging
 *
 *   intent
 *   -- 8bit ascii only, no other incodings (fucking do not care)
 *   -- no character equivalents (since no utf, unicode, etc)
 *   -- start simple and build up (evolutionary)
 *   -- nothing can be nested
 *   -- use recursion to avoid dynamic memory and crazy tracking shit
 *
 *
 *   heavily influenced by the ideas and code of nasciiboy
 *
 *   standard ERE characters     .[]   *+?  {}   ^$   ()|   \
 *   added characters                  @%!       <>     &
 *
 *
 *   quantifiers (suffixes)
 *   .         match any one char except newline or null
 *   [...]     match any one char in the set
 *   [^...]    match any one char not in the set
 *   ?  (!)    zero or one of the previous atom (greedy vs lazy)
 *   *  (@)    zero or more of the previous atom (greedy vs lazy)
 *   +  (%)    one or more of the previous atom (greedy vs lazy)
 *   ^         beginning of string anchor
 *   $         end of string anchor
 *   {n,m}
 *   (...)
 *   |
 *
 *
 *   compiled...
 *      set [a-z]       >>>    [n    where <n> is the set number
 *
 *
 *
 */

/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YREGEX_HGUARD
#define YREGEX_HGUARD loaded

typedef   const char     cchar;
typedef   unsigned char  uchar;
typedef   const int      cint;

char        yREGEX_comp          (cchar *a_regex);
char        yREGEX_exec          (cchar *a_source);

#endif
/*===============================[[ end code ]]===============================*/
