# homework_project
CoSec 161 Melnikov Lev

## lexics

OPEN_BRACKET (
CLOSE_BRACKET )
PLUS +
MINUS -
DIV /
MUL *
IDENTIFIER [a-z]*
NUMBER [0-9]*


## syntax

expression :
  (expression)
  add
  sub

add :
  term+term

sub :
  term-term

term :
  mul
  div
  expression
  num

mul :
  element*element

div :
  element/element
