#include <iostream>
#include <vector>

#include "includes.h"

Parser::Parser(std::vector<Lexeme> lexemes): lexemes(lexemes)
{
  std::cout << "WORKING" << lexemes.size();
  for (auto i: lexemes)
  {
    std::cout << "Will parse:" << std::endl;
    std::cout << i.literal << std::endl;
  }
}
