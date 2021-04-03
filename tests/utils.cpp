#include <iostream>
#include <vector>
#include "utils.h"

TestSummary::TestSummary(): failed(0) {};


void TestSummary::addResult(BaseTest* test)
{
  for (auto const result: test->results)
  {
    if (result.status == FAILED) failed ++;
    results.push_back(result);
  }
}


void TestSummary::report()
{
  for (auto const result: results)
  {
    std::string displayStatus = (result.status == PASSED) ? 
      "PASSED               " : "* FAILED *           ";
    std::string fullTestSignature = result.group + ": " + result.message;
    std::cout << displayStatus << fullTestSignature << "\n";
  }
  
  int total = getTotalCount();
  if (failed)
  {
    std::cout << "\n" << failed << "/" << total << " FAILED!";
  } else {
    std::cout << "\n" << "ALL TESTS PASSED! (" << total << ")";
  }
}


int TestSummary::getTotalCount()
{
  return results.size();
}


BaseTest::BaseTest(std::string name): name(name) {}


void BaseTest::zassert(bool condition, std::string description)
{
  TestStatus status = (condition) ? PASSED: FAILED;
  results.push_back(TestResult{status, description, name});
}
