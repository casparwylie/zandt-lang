#include <iostream>
#include "utils.h"
#include "lexer_test.h"

LexerTest::LexerTest():
  BaseTest("Lexer"),
  lexer(Lexer("test\n1##2##3\nabc\n 'str'\n123"))
{}

LexerTest* LexerTest::test_advance()
{
  
  zassert(lexer.cursor == 0, "Cursor starts at 0");
  lexer.advance(); 
  zassert(lexer.cursor == 1, "Cursor advanced by 1");
  return this;
}

LexerTest* LexerTest::test_peek()
{
  std::string actual = lexer.peek(4); 
  zassert(actual == "test", "Peek matches correct string");
  return this;
}
