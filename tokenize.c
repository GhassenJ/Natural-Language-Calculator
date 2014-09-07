/*--------------------------------------------------------------------*/
/* tokenize.c                                                          */
/* Author:  GHASSEN Jerfel                                            */
/* MEMORY LEAK BECAUSE OF PCBUFFER || CASE SENSITIVE || single digits 
   for alphabetical values || LIMITED TO INTEGERS                    
   CAN EASILY INCLUDE PARANTHESIS AND POWERS                    */
/*--------------------------------------------------------------------*/

#include "token.h"
#include "tokenize.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static const int NUMBER_OF_DIGITS = 10;
static char* map_val[10] = {"zero", "one", "two", "three", "four", "five", "six"
                    , "seven", "eight", "nine"};
static char* map_op[4] = {"plus", "minus", "times", "over"};
static enum TokenType map[4] = {PLUS, MINUS, MULT, DIV};
/*-----------------------------------------------------------------*/
/*ISSUE: NO UPPER CASE FOR NOW!!!*/
static int find_val(char *check) {
    int i;
    for (i = 0; i < NUMBER_OF_DIGITS; i++) {
       if (strcmp(check, map_val[i]) == 0) return i;
    }
    return -1;
}
/*-----------------------------------------------------------------*/

static enum TokenType find_op(char *check) {
    int i;
    for (i = 0; i < NUMBER_OF_DIGITS; i++) {
       if (strcmp(check, map_op[i]) == 0) return map[i];
    }
    return ERROR;   
}
/*-----------------------------------------------------------------*/

/* Print all tokens in oTokens to stdout.*/

void tokenize_printTokens(Token_T* oTokens, int length)
{
   int i;
   assert(oTokens != NULL);
   printf("Tokens:  ");
   for (i = 0; i < length; i++)
   {
      Token_print(oTokens[i]);
   }
   printf("\n");
}

/*--------------------------------------------------------------------*/

/* Free all of the tokens in oTokens. */

void tokenize_freeTokens(Token_T *oTokens, int length)
{
   int i;
   assert(oTokens != NULL);
   for (i = 0; i < length; i++)
   {
      Token_free(oTokens[i]);
   }
}

/*--------------------------------------------------------------------*/
/* Lexically analyze string pcLine. */
Token_T* getTokens(const char *pcLine, int length)
{
    enum Statetype  {START, DIG_VALUE, ALPHA_VALUE, OPERATOR, ALPHA_OPERATOR}; 
    char c;
    char *pcBuffer;
    int i = 0;
    int iBufferIndex = 0;
    int count = 0;
    Token_T psToken;
    Token_T *oTokens;
    assert(pcLine != NULL);
    oTokens = (Token_T*)malloc(length * sizeof(Token_T));
    if (oTokens == NULL) {
        fprintf(stderr, "failed malloc");
        return NULL;}
    pcBuffer = (char*)malloc(strlen(pcLine) + 1);
    if (pcBuffer == NULL){
        fprintf(stderr, "failed malloc");
        return NULL;}
    enum Statetype state = START;
    for (;;)
    {
        c = pcLine[i++];
        if (c == '\n' || c == '\0') {
            if (state == DIG_VALUE || state == ALPHA_VALUE) {
                pcBuffer[iBufferIndex] = '\0';
                int result = 0;
                if (state == DIG_VALUE) {
                    while (*pcBuffer) {
                        result *= 10;
                        result += *pcBuffer++ - '0';
                    }
                }
                else result = find_val(pcBuffer);
                psToken = Token_newToken(VALUE, result);
                oTokens[count++] = psToken;
                /*free(pcBuffer);*/ /*SEG FAULT HERE*/
                return oTokens;
            }
            else if (state == OPERATOR || state == START) {
                fprintf(stderr, "Illegal input: operator at the end");
                return NULL;}
        }
        switch(state)
        {
            case START:
                if (c == ' ') state = START;
                else if (isdigit(c)) {
                    pcBuffer[iBufferIndex++] = c;
                    state = DIG_VALUE;}
                else if (isalpha(c)) {
                    pcBuffer[iBufferIndex++] = c;
                    state = ALPHA_VALUE;}
                else {
                    fprintf(stderr, "%c: operator at the beginning or 2 consecutives", c);
                    return NULL;}
                break;
            case DIG_VALUE:
                if (c == ' ') {
                    pcBuffer[iBufferIndex] = '\0';
                    int result = 0;
                    while (*pcBuffer) {
                        result *= 10;
                        result += *pcBuffer++ - '0';
                    } /*MODULARITY*/
                    psToken = Token_newToken(VALUE, result); 
                    oTokens[count++] = psToken;
                    /*CHECK IF IT FAILS?*/
                    iBufferIndex = 0;
                    state = OPERATOR;}
                else if (isdigit(c)) {
                    state = DIG_VALUE;
                    pcBuffer[iBufferIndex++] = c;
                    }
                else {  
                    /*free(pcBuffer);*/
                    tokenize_freeTokens(oTokens, count);
                    free(oTokens);
                    fprintf(stderr, "%c: illegal character after a value", c);
                    return NULL;}
                break;
            case ALPHA_VALUE: /*SINGLE DIGITS FOR NOW*/
                if (c == ' ') {
                    pcBuffer[iBufferIndex] = '\0';
                    psToken = Token_newToken(VALUE, find_val(pcBuffer)); 
                    /*only single digits for now*/
                    oTokens[count++] = psToken;
                    iBufferIndex = 0;
                    state = OPERATOR; } /*i-1 or i-2?*/
                else if (isalpha(c)) {
                    state = ALPHA_VALUE;
                    pcBuffer[iBufferIndex++] = c;
                    }
                else {
                    fprintf(stderr, "%c: illegal character after a value", c);
                    return NULL;}
                break;
            case OPERATOR:
                if (c == '*') {
                    psToken = Token_newToken(MULT, 0);
                    oTokens[count++] = psToken;
                    state = START;
                    }
                else if (c == '+') {
                    psToken = Token_newToken(PLUS, 0);
                    oTokens[count++] = psToken;
                    state = START;
                    }
                else if (c == '-') {
                    psToken = Token_newToken(MINUS, 0);
                    oTokens[count++] = psToken;
                    state = START;
                    }
                else if (c == '/') {
                    psToken = Token_newToken(DIV, 0);
                    oTokens[count++] = psToken;
                    state = START;
                    }
                /*else if (c == '^') psToken = Token_newToken(EXP, 0);*/
                                    /*UNUSED FOR NOW*/
/*                else if (c == '(') {
                    psToken = Token_newToken(OPAREN, 0);
                    oTokens[count++] = psToken;
                    state = START;
                    }
                else if (c == ')') {
                    psToken = Token_newToken(CPAREN, 0);
                    oTokens[count++] = psToken;
                    state = START;
                    }*/
                else if (isalpha(c)) {
                    pcBuffer[iBufferIndex++] = c;
                    state = ALPHA_OPERATOR;}
                else {
                    fprintf(stderr, "%c: illegal character instead of operator", c);
                    return NULL;}
                break;
            case ALPHA_OPERATOR:
                if (c == ' ') {
                    pcBuffer[iBufferIndex] = '\0';
                    enum TokenType type = find_op(pcBuffer);
                    if (type == ERROR) {
                        fprintf(stderr, "%s: invalid operator ", pcBuffer);
                        return NULL;
                        }
                    psToken = Token_newToken(type, 0); 
                    /*only single digits for now*/
                    oTokens[count++] = psToken;
                    iBufferIndex = 0;
                    state = START; } /*i-1 or i-2?*/
                else if (isalpha(c)) {
                    state = ALPHA_OPERATOR;
                    pcBuffer[iBufferIndex++] = c;
                    }
                else {
                    fprintf(stderr, "%c: illegal character after a value", c);
                    return NULL;}
                break;
            default:
                {
                    fprintf(stderr, "you shouldn't be in this state");
                    return NULL;}
      }
   }
   return oTokens;
}
