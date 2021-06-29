// Headers for ast

struct Expression {};

struct Infix: Expression
{
  Expression left;
  Lexeme symbol;
  Expression right;
};

struct Unary: Expression
{
  Lexeme symbol;
  Expression right;
};

struct GroupedExpression: Expression
{
  Expression expression;
};

struct Literal: Expression
{
  int value;
};
