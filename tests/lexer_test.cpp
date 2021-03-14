#include <iostream>
#include "../src/lexer.h"
#include "lexer_test.h"

void test_test1()
{
  // TODO: Write proper tests :) 
  Lexer lexer(
    "test\n123\nte i/*st*/\ni   t\n\"gr  r\"\nr");
  lexer.scan();
  for (auto const lex: lexer.lexemes) {
    std::cout << "L: " << lex.literal << "\n";
  }
}
