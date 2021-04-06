enum ErrorType
{
  ERROR,
  SYNTAX_ERROR,
};

namespace Errors
{
  struct BaseError
  {
    BaseError(std::string message);
    std::string message;
    ErrorType type;

    virtual void callback() = 0;
    virtual void show() = 0;
  };
  
  struct Error: BaseError
  {
    Error(std::string message);
    void callback() override;
    void show() override;
  };

  struct SyntaxError: BaseError
  {
    int line;
    SyntaxError(std::string message, int line);
    void callback() override;
    void show() override;
  };
}
