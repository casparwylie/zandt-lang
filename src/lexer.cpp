#include <iostream>
#include <map>
#include <unordered_map>

#include "lexer.h"

typedef std::unordered_map<std::string, LexemeType>::const_iterator iter_keyword;

std::map<std::string, LexemeType> SYMBOL_DICTIONARY = 
{
  {"@", AT},
  {"\n", NEWLINE},
  {" ", SPACE},
  {"#", HASH},
  {"{", OPEN_BRACE},
  {"}", CLOSE_BRACE},
  {"=", EQUAL},
  {"!=", NOT_EQUAL},
  {"/*", MULTILINE_COMMENT},
};

std::unordered_map<std::string, LexemeType> KEYWORD_DICTIONARY =
{
  {"false", FALSE},
  {"true", TRUE},
};

Lexer::Lexer(std::string source): source(source)
{
  cursor = 0;
  line = 1;
  sourceSize = source.size();
}

void Lexer::scan()
{
  while (!atSourceEnd()) {
    if (checkStaticLexeme()) continue;
    if (checkNonStaticLexeme()) continue;
    std::cout << "\n\n Invalid syntax, line " << line << "\n\n";
    break;
  }
}

bool Lexer::checkStaticLexeme()
{
  for (auto const & [value, lexeme]: SYMBOL_DICTIONARY) 
  {
    int lexemeSize = value.size();
    if (peek(lexemeSize) == value) {
      
      switch (lexeme)
      {
        case MULTILINE_COMMENT:
            while (!atSourceEnd() && peek(2) != "*/") advance(1);          
            advance(2);
            break;
        case HASH:
            while (!atSourceEnd() && peek(1)[0] != '\n') advance(1);          
            advance(1);
            break;
        case NEWLINE:
            line ++;
            advance(1);
            break;
        case SPACE:
            advance(1);
            break;
        default:
          lexemes.push_back(Lexeme{lexeme, value});
          advance(lexemeSize);
      }
      return true;
     }
  }
  return false;
}

bool Lexer::checkNonStaticLexeme()
{
  LexemeType lexeme = _;
  int startCursor = cursor;
  char character = peek(1)[0];
  advance(1);
  switch (character)
  {
    case '"':
      lexeme = stringLexeme();
      break;
    default:
      if (isdigit(character))
      {
        lexeme = numberLexeme();
      } else if (isalpha(character))
      {
        lexeme = wordLexeme();
      }
  }
  if(lexeme == _) return false;
  std::string value = source.substr(startCursor, cursor - startCursor);
  if (lexeme == WORD) lexeme = keywordLexeme(value);
  lexemes.push_back(Lexeme{lexeme, value});
  return true;
}

LexemeType Lexer::stringLexeme()
{
  while (!atSourceEnd() && peek(1)[0] != '"') advance(1);
  advance(1);
  return STRING;
}

LexemeType Lexer::numberLexeme()
{
  while (!atSourceEnd() && isdigit(peek(1)[0])) advance(1);
  return NUMBER;
}

LexemeType Lexer::wordLexeme()
{
  while (!atSourceEnd() && isalpha(peek(1)[0])) advance(1);
  return WORD;
}

LexemeType Lexer::keywordLexeme(std::string value) 
{
  iter_keyword keyword = KEYWORD_DICTIONARY.find(value);
  if (keyword == KEYWORD_DICTIONARY.end()) return WORD;
  return keyword->second;
}

std::string Lexer::peek(int distance)
{
  return source.substr(cursor, distance);
}

void Lexer::advance(int distance)
{
  cursor += distance;
}

bool Lexer::atSourceEnd()
{
  return sourceSize <= cursor;
}
