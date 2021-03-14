#include <iostream>
#include "../src/lexer.h"
#include "lexer_test.h"

void test_test1()
{
  // TODO: Write proper tests :) 
  Lexer lexer(
    "test\n1##23\nte i\"5st\ni  tgr  r\nr###");
  lexer.scan();
  for (auto const lex: lexer.lexemes) {
    std::cout << "L: " << lex.literal << "\n";
  }
}
