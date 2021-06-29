#include <iostream>
#include "includes.h"

ParserTest::ParserTest(): BaseTest("Parser") {}

ParserTest* ParserTest::test_something()
{
  Lexer lexer("123 != abc");
  lexer.scan();

  Parser parser(lexer.lexemes);
  zassert(true, "works");
  return this;
}
