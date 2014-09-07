/*--------------------------------------------------------------------*/
/* calc.c                                                             */
/* Author: Ghassen Jerfel                                             */
/*NOTES : DO NOT USE * in command line but rather use '*'             */
/*MEMORY LEAK BECAUSE OF PCBUFFER || CASE SENSITIVE || single digits  */
/*  for alphabetical values || LIMITED TO INTEGERS                    */
/*   CAN EASILY INCLUDE PARANTHESIS AND POWERS                        */
/*--------------------------------------------------------------------*/

#define _GNU_SOURCE
#include "stack.h"
#include "token.h"
#include "tokenize.h"
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*return 1 if Token_T v1 has a higher precedence than Token_T v2 assuming 
both are of OPERATOR TYPES*/
static int precedence(Token_T v1, Token_T v2) {
    enum TokenType type1, type2;
    assert(v1 != NULL);
    assert(v2 != NULL);
    type1 = Token_getType(v1);
    type2 = Token_getType(v2);
    if ((type1 == MULT || type1 == DIV) && (type2 == PLUS || type2 == MINUS))
        return 1;
    else return 0;
}
/*-------------------------------------------------------------------*/
/*                  EVALUATE THE EXPRESSION:                         */
static void evaluate(Token_T* oTokens, int length) {
    Stack_T oStack1;
    Stack_T oStack2;
    int i;
   /* Create and use a Stack of tokens. */
    assert(oTokens != NULL);
    oStack1 = Stack_new();
    oStack2 = Stack_new();
    for (i = 0; i < length; i++) {
        if (Token_getType(oTokens[i]) == VALUE) 
            Stack_push(oStack1, oTokens[i]);
        else if (Stack_isEmpty(oStack2))
            Stack_push(oStack2, oTokens[i]);
        else if (precedence(oTokens[i], Stack_top(oStack2)))
            Stack_push(oStack2, oTokens[i]);
        else { /*ERROR HANDLING?*/
            int result;
            Token_T value_1 = (Token_T)Stack_top(oStack1);
            Stack_pop(oStack1);
            Token_T operator = (Token_T)Stack_top(oStack2);
            Stack_pop(oStack2);
            Token_T value_2 = (Token_T)Stack_top(oStack1);
            Stack_pop(oStack1);
            switch (Token_getType(operator))
            {  /*LEFT TO RIGHT EVALUATION*/
                case MULT:
                    result = Token_getValue(value_1) * Token_getValue(value_2);
                    break;
                case DIV:
                    result = Token_getValue(value_2) / Token_getValue(value_1);
                    break;
                case PLUS:
                    result = Token_getValue(value_1) + Token_getValue(value_2);
                    break;
                case MINUS:
                    result = Token_getValue(value_2) - Token_getValue(value_1);
                    break;
                default: assert(0);
            }
            Stack_push(oStack1, Token_newToken(VALUE, result));
            Stack_push(oStack2, oTokens[i]);
        }
    }
    while (!Stack_isEmpty(oStack2)){ /*ERROR HANDLING? + MODULARITY MUCH????*/
            int result;
            Token_T value_1 = (Token_T)Stack_top(oStack1);
            Stack_pop(oStack1);
            Token_T operator = (Token_T)Stack_top(oStack2);
            Stack_pop(oStack2);
            Token_T value_2 = (Token_T)Stack_top(oStack1);
            Stack_pop(oStack1);
            switch (Token_getType(operator))
            {  /*LEFT TO RIGHT EVALUATION*/
                case MULT:
                    result = Token_getValue(value_1) * Token_getValue(value_2);
                    break;
                case DIV:
                    result = Token_getValue(value_2) / Token_getValue(value_1);
                    break;
                case PLUS:
                    result = Token_getValue(value_1) + Token_getValue(value_2);
                    break;
                case MINUS:
                    result = Token_getValue(value_2) - Token_getValue(value_1);
                    break;
                default: assert(1);
            }
            Stack_push(oStack1, Token_newToken(VALUE, result));
        }
    printf("%d\n", Token_getValue((Token_T)Stack_top(oStack1)));
    Stack_free(oStack1);
    Stack_free(oStack2);
}
    
/*--------------------------------------------------------------------*/
/*This main calls the getTokens to get an Array oTokens of Tokens objects
defined in the token ADT. The main later evaluates the expression of the
tokens by calling evaluate and returns the result. The Input that is being
tokenized is the command line. We are assuming tokens are separated by 
spaces. */
int main(int argc, char *argv[])
{
   int i, len;
   if (argc < 4) {
    fprintf(stderr,"not enough arguments");
    return 0;
    }
   for (i = 1; i < argc; i++) len += strlen(argv[i]);
   char* pcLine = malloc(len + argc);
   strcpy(pcLine, argv[1]);
   for (i = 2; i < argc; i++) {
    strcat(pcLine, " ");
    strcat(pcLine, argv[i]);
    }
   /*printf("%s\n", pcLine);*/
   Token_T* oTokens = getTokens(pcLine, argc - 1);
   /*printf("\n");*/
   if (oTokens == NULL) return 0;
   else{
    evaluate(oTokens, argc-1);
    /*tokenize_printTokens(oTokens, argc - 1);*/
    tokenize_freeTokens(oTokens, argc - 1);
    free(oTokens);
   }
   free(pcLine);
   return 0;
}
