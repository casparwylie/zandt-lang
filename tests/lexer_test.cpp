#include <iostream>
#include "../src/lexer.h"
#include "lexer_test.h"

void test_test1()
{
  // TODO: Write proper tests :) 
  Lexer lexer(
    "test\n1)##2##3\nte 7i5st\ni \"e\ng  r\nr#");
  lexer.scan();
  for (auto const lex: lexer.lexemes) {
    std::cout << "L: " << lex.literal << "\n";
  }
}
