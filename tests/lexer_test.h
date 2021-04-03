#include "../src/lexer.h"

class LexerTest: public BaseTest
{
  public:
    LexerTest();
    Lexer lexer;
    LexerTest* test_advance();
    LexerTest* test_peek();
};

