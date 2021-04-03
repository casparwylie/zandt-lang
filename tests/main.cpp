#include "includes.h"

int main() {
  TestSummary summary;
  summary.addResult(LexerTest().test_advance());
  summary.addResult(LexerTest().test_peek());
  summary.report();
  return 0;
}
