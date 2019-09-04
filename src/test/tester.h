#ifndef TESTER_H
#define TESTER_H

typedef struct testcase_t {
  char* test_name;
  int* tk_result;
}TestCase;

extern TestCase testCase;

#endif
