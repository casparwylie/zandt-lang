#include <iostream>
#include <map>
#include <unordered_map>

#include "lexer.h"
#include "errors.h"


typedef std::unordered_map<
  std::string, LexemeType>::const_iterator iter_keyword;

struct SymbolDictComparator
{
  bool operator()(
    const std::string& subject, const std::string& object) const
  {
    int subjectSize = subject.size();
    int objectSize = object.size();
    if (subjectSize == objectSize) return subject < object;
    return subjectSize > objectSize;
  }
};

std::map<std::string, LexemeType, SymbolDictComparator> SYMBOL_DICTIONARY = 
{
  {"!=", NOT_EQUAL},
  {"##", MULTILINE_COMMENT},
  {"@", AT},
  {"\n", NEWLINE},
  {" ", SPACE},
  {"#", HASH},
  {"{", OPEN_BRACE},
  {"}", CLOSE_BRACE},
  {"=", EQUAL},
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
    throw Errors::SyntaxError(
      "Unexpected character " + std::string(1, source[cursor]), line);
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
            advance(lexemeSize);
            while (peek(2) != "##") {
              if (atSourceEnd()) throw Errors::SyntaxError(
                "Unclosed multi-line comment", line);
              advance();
            };          
            advance(2);
            break;
        case HASH:
            while (!atSourceEnd() && source[cursor] != '\n') advance();
            break;
        case NEWLINE:
            line ++;
            advance();
            break;
        case SPACE:
            advance();
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
  char character = source[cursor];
  switch (character)
  {
    case '"':
    case '\'':
      lexeme = stringLexeme(character);
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

LexemeType Lexer::stringLexeme(char &startChar)
{
  char nextChar;
  do {
    if (atSourceEnd()) throw Errors::SyntaxError("Unclosed string", line);
    advance();
    nextChar = source[cursor];
  }
  while ((startChar == '"' && nextChar != '"') ||
         (startChar == '\'' && nextChar != '\''));
  advance();
  return STRING;
}

LexemeType Lexer::numberLexeme()
{
  while (!atSourceEnd() && isdigit(source[cursor])) advance();
  return NUMBER;
}

LexemeType Lexer::wordLexeme()
{
  while (!atSourceEnd() && isalpha(source[cursor])) advance();
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
