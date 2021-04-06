#include "../src/lexer.h"

class LexerTest: public BaseTest
{
  public:
    LexerTest();
    Lexer lexer;
    LexerTest* test_advance();
    LexerTest* test_peek();
    LexerTest* test_atSourceEnd();
    LexerTest* test_keywordLexeme();
    LexerTest* test_wordLexeme();
    LexerTest* test_numberLexeme();
    LexerTest* test_stringLexeme();
};

