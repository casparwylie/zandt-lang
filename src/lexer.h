#include <vector>
#include <unordered_map>


enum LexemeType {
  // 0
  _,

  // 1 - 5
  AT, NEWLINE, SPACE, OPEN_BRACE, CLOSE_BRACE,
  EQUAL, NOT_EQUAL, MULTILINE_COMMENT, HASH,
  
  // 6 - 7
  TRUE, FALSE,
  
  // 8 - 11
  WORD, NUMBER, STRING
};

struct Lexeme {
  LexemeType type;
  std::string literal;
};

class Lexer {
  public:
    std::string source;
    int sourceSize;
    
    Lexer(std::string source);
    std::vector<Lexeme> lexemes;
    int cursor;
    int line;

    void scan();
    bool checkStaticLexeme();
    bool checkNonStaticLexeme();
    bool atSourceEnd();
    std::string peek(int distance);
    void advance(int distance = 1);
    LexemeType stringLexeme(char &startChar);
    LexemeType numberLexeme();
    LexemeType wordLexeme();
    LexemeType keywordLexeme(std::string value);
};
