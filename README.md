# homework_project
CoSec 161 Melnikov Lev


## lexics
* OPEN_BRACKET (
* CLOSE_BRACKET )
* PLUS +
* MINUS -
* DIV /
* MUL *
* IDENTIFIER [a-z]*
* NUMBER [0-9]*


## syntax
expression :
 * add_sub
 * mul_div
 * leaf

add_sub :
 * [mul_div, brackets, leaf] [+,-] [expression, brackets, leaf]

mul_div :
 * [brackets, leaf] [*,/] [mul_div, brackets, leaf]

brackets :
 * (expression)

leaf :
 * number
 * func_call

func_call :
 * identifier brackets

