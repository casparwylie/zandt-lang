#include <iostream>
#include <vector>

class Parser
{
  public:
    std::vector<Lexeme> lexemes;
    Parser(std::vector<Lexeme> lexemes);
};
