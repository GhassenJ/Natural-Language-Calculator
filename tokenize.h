/*------------------------------------------
  tokenize.h
  Ghassen Jerfel
  tokenize.h is the interface of the lexical.c
  -----------------------------------------*/
#ifndef TOKENIZE_INCLUDED
#define TOKENIZE_INCLUDED

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Free all of the tokens in oTokens. */
void tokenize_freeTokens(Token_T* oTokens, int length);

/*--------------------------------------------------------------------*/

/* Print all tokens in oTokens to stdout.  First print the number
   tokens; then print the word tokens. */
void tokenize_printTokens(Token_T* oToken, int length);

/*--------------------------------------------------------------------*/
/* Lexically analyze string pcLine.  If pcLine contains a lexical
   error, then return NULL.  Otherwise return a DynArray object
   containing the tokens in pcLine.  The caller owns the DynArray
   object and the tokens that it contains. */
Token_T* getTokens(const char *pcLine, int length);

#endif
