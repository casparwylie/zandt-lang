#include <iostream>
#include <vector>

enum TestStatus { PASSED, FAILED };


struct TestResult
{
  TestStatus status;
  std::string message;
  std::string group;
};


class BaseTest
{
  public:
    BaseTest(std::string name);
    std::vector<TestResult> results;
    std::string name;
  protected:
    void zassert(bool condition, std::string description);
    void zassertError(void (*test)(), ErrorType expectedErrorType, std::string message);
};


class TestSummary
{
  public:
    TestSummary();
    std::vector<TestResult> results;
    void addResult(BaseTest* test);
    void report();

    int failed;
  private:
    int getTotalCount();
};
