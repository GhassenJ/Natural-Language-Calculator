A natural language calculator.
Limited functionnality:
*only single digits for literal expressions: one + two
*can only take integers (no floats/doubles for now)
*literal expressions are case sensitive:{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"} 
for the digits and {"plus", "minus", "times", "over"} for the operators.
*Tokenization assumes tokens are separated by spaces: no multiple tokens in one block + no tokens with spaces inside.
*A small memory leak because of pcBuffer in tokenize.c (13 bytes) but freeing pcBuffer causes a seg fault.
Possible future improvements:
*It is easy to include the exponent "^" and paranthesis at this point.
*Fixing the memory leak might be easy.
*increasing teh spectrum of the possible inputs.
Files:
makefile
stack.h and stack.c (by Rob Dondero from COS 217 / Princeton)
token.c and token.h
tokenize.c and tokenize.h
calc.c

Build: call "make"
Run: 
*calc 100 + 255 * 9
*calc one plus 2
*calc 2 minus 3
*calc five + seven
Invalid inputs: 
*operator at end or beginning
*consecutive operators
*consecutive values

Total time spent: ~6 hours.
Reason for formal tokenization (DFA approach): to be able to improve tokenization by recognizing multiple-digit literal 
expressions and expressions without spaces.

Evaluation of the expression is done with the infix evaluation algorithm:
Until the end of the expression is reached, get one character and perform only one of the following steps
- If the character is an operand, push it onto the operand stack.
- If the character is an operator, and the operator stack is empty then push it onto the operator stack.
- If the character is an operator and the operator stack is not empty, and the character's precedence is 
greater than the precedence of the stack top of operator stack, then push the character onto the operator stack.
- IF NOTHING APPLIES: (i) pop operand stack once (value1) (ii) pop operator stack once (operator) 
(iii) pop operand stack again (value2) (iv) compute value1 operator  value2 (v) push the value obtained in operand stack.

When we are done with the tokens, we redo the last step until the oeprator stack is empty, at which point we only have the 
final value in the operand stack.