/*--------------------------------------------------------------------*/
/* token.c                                                            */
/* Author: Ghassen Jerfel                                             */
/* Token ADT to facilitate the process of parsing the command line    */
/*--------------------------------------------------------------------*/

#include "token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*--------------------------------------------------------------------*/
/* A token is an  object that has a type and a value */
struct Token
{
   /* The type of the token. */
   enum TokenType eType;

   /* The string which is the token's value. */
   int Value;
};

/*--------------------------------------------------------------------*/
/*Create a new Token of the given Type, and value.                    */

Token_T Token_newToken(enum TokenType eTokenType, int Value)
{
   Token_T psToken;

   psToken = (struct Token*)malloc(sizeof(struct Token));
   if (psToken == NULL)
   {fprintf(stderr, "malloc failed"); exit(EXIT_FAILURE);}
   psToken->eType = eTokenType;
   psToken->Value = Value;
   return psToken;
}
/*--------------------------------------------------------------------*/
/*Free the oToken object                                              */
void Token_free(Token_T oToken)
{
   assert(oToken != NULL);
   free(oToken);
}
/*--------------------------------------------------------------------*/
/*Print the oToken object                                             */
void Token_print(Token_T oToken)
{
   assert(oToken != NULL);
   printf("%d ", oToken->Value);
}
/*--------------------------------------------------------------------*/
/*Return the type of the oToken Object                                */
enum TokenType Token_getType(Token_T oToken)
{
   assert(oToken != NULL);
   return oToken->eType;
}
/*--------------------------------------------------------------------*/
/* Return the Value (integer) of a Token object                       */
int Token_getValue(Token_T oToken)
{
   assert(oToken != NULL);
   return oToken->Value;
}
