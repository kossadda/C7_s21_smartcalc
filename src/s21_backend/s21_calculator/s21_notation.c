#include "s21_calculator.h"

static void add_num_to_stack(num_stack *num, char *token);

/**
 * @brief String parsing function to determine priority and then evaluate arithmetic expressions.
 * 
 * @param[in] str processed string with arithmetic expression.
 * 
 * @return Result of calculations.
*/
double notation(char *str)
{
    lex_stack lex;
    num_stack num;
    num.count = 0;
    lex.count = -1;

    char token[strlen(str) + 1];
    strcpy(token, str);
    add_num_to_stack(&num, token);

    for(size_t i = 0; i < strlen(str); i++) {
        if(check(str[i], ALL_OPERATIONS)) {
            if(str[i] == CHAR_CL_BRCK) {
                bracket_close(&num, &lex, PARS_EXPRESSION);
            } else {
                lex.count++;
            }

            if(str[i] == CHAR_CL_BRCK && lex.stack[lex.count] == CHAR_OP_BRCK) {
                clean_top_stack(&num, NO, &lex, YES);
                if(check(lex.stack[lex.count], TRIGONOMETRIC_CHARS)) {
                    math_trigonometry(&(num.stack[num.count - 1]), lex.stack[lex.count--]);
                }
            }

            if(num.count > 1) {
                math_while_parsing(&num, &lex, str[i], EQUAL_PRIORITY);
                math_while_parsing(&num, &lex, str[i], HIGH_PRIORITY);
            }

            if(str[i] != CHAR_CL_BRCK) {
                lex.stack[lex.count] = str[i];
            }

            if(!check(str[i+1], ALL_OPERATIONS)) {
                add_num_to_stack(&num, NULL);
            }
        }
    }

    bracket_close(&num, &lex, CLOSE_EXPRESSION);
    return num.stack[0];
}

/**
 * @brief Function to add a number to a number stack.
 * 
 * @param num number to add.
 * @param token parse string.
*/
static void add_num_to_stack(num_stack *num, char *token)
{
    char *temp = NULL;
    temp = strtok(token, ALL_OPERATIONS);
    
    if(temp) {
        num->stack[num->count++] = atof(temp);
    }
}

/**
 * @brief Function for clearing the top of stacks.
 * Function have two modes.
 * "decision" = NO (0) - don't clear the top of the stack.
 * "decision" = YES (1) - to clear the top of the stack.
 * 
 * @param num numeric stack.
 * @param num_decision numeric cleaning decision.
 * @param lex lexem stack.
 * @param lex_decision lexem cleaning decision.
*/
void clean_top_stack(num_stack *num, int num_decision, lex_stack *lex, int lex_decision)
{
    if(num_decision == YES) {
        num->stack[num->count--] = 0;
    }

    if(lex_decision == YES) {
        lex->stack[lex->count--] = CHAR_ZERO;
    }
}
