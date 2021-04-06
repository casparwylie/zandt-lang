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


LexerTest* LexerTest::test_atSourceEnd()
{
  std::string actual = lexer.peek(4);
  while (lexer.cursor < lexer.sourceSize) lexer.advance();
  zassert(lexer.atSourceEnd(), "Source end is detected correctly");
  return this;
}


LexerTest* LexerTest::test_keywordLexeme()
{
  LexemeType result1 = lexer.keywordLexeme("abc");
  LexemeType result2 = lexer.keywordLexeme("false");
  LexemeType result3 = lexer.keywordLexeme("falsee");
  zassert(result1 == WORD, "Word detected correctly");
  zassert(result2 == FALSE, "Keyword detected correctly");
  zassert(result3 == WORD, "Partial keyword not considered");
  return this;
}


LexerTest* LexerTest::test_wordLexeme()
{
  LexemeType result = lexer.wordLexeme();
  zassert(lexer.cursor == 4, "Word correctly advanced over");
  zassert(result == WORD, "Word lexeme type returned");
  return this;
}


LexerTest* LexerTest::test_numberLexeme()
{
  Lexer lexer("123 test");
  LexemeType result = lexer.numberLexeme();
  zassert(lexer.cursor == 3, "Number correctly advanced over");
  zassert(result == NUMBER, "Number lexeme type returned");
  return this;
}


LexerTest* LexerTest::test_stringLexeme()
{
  Lexer lexer1("'test' abc");
  LexemeType result1 = lexer1.stringLexeme(lexer1.source[0]);
  zassert(lexer1.cursor == 6, "Single quoted string correctly advanced over");
  zassert(result1 == STRING, "String lexeme type returned");

  Lexer lexer2("\"test\" abc");
  LexemeType result2 = lexer2.stringLexeme(lexer2.source[0]);
  zassert(lexer2.cursor == 6, "Double quoted string correctly advanced over");

  zassertError([](){
    Lexer lexer3("'test\" abc");
    lexer3.stringLexeme(lexer3.source[0]);
  }, SYNTAX_ERROR, "Unmatched quoted string throws syntax error");

  return this;
}
