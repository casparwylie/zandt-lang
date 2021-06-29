#include "includes.h"

int main()
{
  TestSummary summary;
  summary.addResult(LexerTest().test_advance());
  summary.addResult(LexerTest().test_peek());
  summary.addResult(LexerTest().test_atSourceEnd());
  summary.addResult(LexerTest().test_keywordLexeme());
  summary.addResult(LexerTest().test_wordLexeme());
  summary.addResult(LexerTest().test_numberLexeme());
  summary.addResult(LexerTest().test_stringLexeme());
  summary.addResult(LexerTest().test_checkNonStaticLexeme());
  summary.addResult(LexerTest().test_checkStaticLexeme());
  summary.addResult(LexerTest().test_scan());

  summary.addResult(ParserTest().test_something());
  summary.report();
  return 0;
}
