/*--------------------------------------------------------------------*/
/* token.h                                                            */
/* Author: Ghassen Jerfel                                             */
/* Token ADT to facilitate the process of parsing the command line    */
/*--------------------------------------------------------------------*/

#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED

#include <stddef.h>

/* A Token object can be either a calue or an operator or an error if no
match found */
enum TokenType {ERROR, VALUE, OPAREN, CPAREN, EXP, MULT, DIV, PLUS, MINUS};

/* A token is an  object that has a type and a value */
typedef struct Token *Token_T;

/*--------------------------------------------------------------------*/
/*Create a new Token of the given Type, and value.                    */

Token_T Token_newToken(enum TokenType eTokenType, int Value);

/*--------------------------------------------------------------------*/
/*Free A Token object                                                 */
void Token_free(Token_T oToken);

/*--------------------------------------------------------------------*/
/*Print A Token object                                                */
void Token_print(Token_T oToken);

/*--------------------------------------------------------------------*/
/*Return the type of a Token Object                                   */
enum TokenType Token_getType(Token_T oToken);

/*--------------------------------------------------------------------*/
/* Return the Value (integer) of a Token object                       */
int Token_getValue(Token_T oToken);

#endif
