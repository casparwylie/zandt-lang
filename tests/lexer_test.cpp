#include <iostream>

#include "includes.h"

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

  zassertError([]()
  {
    Lexer lexer3("'test\" abc");
    lexer3.stringLexeme(lexer3.source[0]);
  }, SYNTAX_ERROR, "Unmatched single quoted string throws syntax error");

  zassertError([]()
  {
    Lexer lexer3("\"test' abc");
    lexer3.stringLexeme(lexer3.source[0]);
  }, SYNTAX_ERROR, "Unmatched double quoted string throws syntax error");

  return this;
}


LexerTest* LexerTest::test_checkNonStaticLexeme()
{
  auto test = [=](
    std::string source,
    std::string expectedLiteral,
    LexemeType expectedLexemeType,
    std::string message)
  {
    Lexer lexer(source);
    bool result = lexer.checkNonStaticLexeme();
    Lexeme actualLexeme = lexer.lexemes[0];
    zassert(
      result &&
      actualLexeme.type == expectedLexemeType &&
      actualLexeme.literal == expectedLiteral, message);
  };

  test("'test' abc", "'test'", STRING, "Non-static string lexeme detected and registered");
  test("123 'test'", "123", NUMBER, "Non-static number lexeme detected and registered");
  test("abc 123", "abc", WORD, "Non-static word lexeme detected and registered");
  test("true abc", "true", TRUE, "Non-static keyword lexeme detected and registered");
  zassert(!Lexer(" $ abc").checkNonStaticLexeme(), "Static lexeme undetected and ignored");
  return this;
}


LexerTest* LexerTest::test_checkStaticLexeme()
{
  Lexer lexer1("!=@{}##!==##@  =");
  while(!lexer1.atSourceEnd()) lexer1.checkStaticLexeme();
  zassert(
    lexer1.lexemes[0].type == NOT_EQUAL &&
    lexer1.lexemes[1].type == AT &&
    lexer1.lexemes[2].type == OPEN_BRACE &&
    lexer1.lexemes[3].type == CLOSE_BRACE &&
    lexer1.lexemes[4].type == AT &&
    lexer1.lexemes[5].type == EQUAL,
    "Static lexemes are consumed while comments and spaces skipped");

  Lexer lexer2("!=# ignore this \n @");
  while(!lexer2.atSourceEnd()) lexer2.checkStaticLexeme();
  zassert(
    lexer2.lexemes[0].type == NOT_EQUAL &&
    lexer2.lexemes[1].type == AT,
  "Single line comment is correctly ignored");

  zassertError([]()
  {
    Lexer lexer3("!=##ignore this \n @");
    while(true) lexer3.checkStaticLexeme();
  }, SYNTAX_ERROR, "Unclosed multi-line comment throws syntax error");

  return this;
}


LexerTest* LexerTest::test_scan()
{
  Lexer lexer1("abc  123 @ != = ## test ## ? 'str'");
  lexer1.scan();
  zassert(
    lexer1.lexemes[0].type == WORD && lexer1.lexemes[0].literal == "abc" &&
    lexer1.lexemes[1].type == NUMBER && lexer1.lexemes[1].literal == "123" &&
    lexer1.lexemes[2].type == AT &&
    lexer1.lexemes[3].type == NOT_EQUAL &&
    lexer1.lexemes[4].type == EQUAL &&
    lexer1.lexemes[5].type == QUESTION &&
    lexer1.lexemes[6].type == STRING && lexer1.lexemes[6].literal == "'str'",
    "All lexemes are correctly scanned");

  zassertError([]()
  {
    Lexer lexer2("abc  123 ~ @ != = ## test ## ? 'str'");
    lexer2.scan();
  }, SYNTAX_ERROR, "Unexpected character throws syntax error");
  return this;
}
