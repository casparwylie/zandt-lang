#include <iostream>
#include "errors.h"


Errors::BaseError::BaseError(std::string message): message(message){};

Errors::Error::Error(std::string message): BaseError(message)
{
  type = ERROR;
  show();
  callback();
}

void Errors::Error::callback() {};
void Errors::Error::show()
{
  std::cout << message + "\n";
}


Errors::SyntaxError::SyntaxError(std::string message, int line):
  BaseError(message), line(line)
{
  type = SYNTAX_ERROR;
  show();
  callback();
}

void Errors::SyntaxError::show()
{
  std::cout << "* Syntax Error *: ";
  std::cout << message + " on line " << line << std::endl;
}

void Errors::SyntaxError::callback()
{
  std::cout << "\nExiting";
}
