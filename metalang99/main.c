#include "metalang99.h"

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define BOXED_NUMBER_COUNT 128

#define BOXED_NUMBER_IMPL(i) v(int *_##i = (int *)malloc(sizeof(int));)
#define BOXED_NUMBER_ARITY 1

#define BOXED_NUMBER_INIT_IMPL(i) v(*_##i = i;)
#define BOXED_NUMBER_INIT_ARITY 1

int main(int argc, char **argv) {

  ML99_EVAL(ML99_repeat(v(BOXED_NUMBER_COUNT), v(BOXED_NUMBER)));
  ML99_EVAL(ML99_repeat(v(BOXED_NUMBER_COUNT), v(BOXED_NUMBER_INIT)));

  return 0;
}
