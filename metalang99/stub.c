#include "datatype99.h"
#include "metalang99/list.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

// clang-format off
datatype(
    List,
    (Nil),
    (Cons, void*, void*)
);
// clang-format on

#define BOXED_NUMBER_COUNT 128

#define BOXED_NUMBER_IMPL(_n, i) v(int *_##i = (int *)calloc(1, sizeof(int));)
#define BOXED_NUMBER_ARITY 2

#define BOXED_NUMBER_INIT_IMPL(_n, i) v(*_##i = i;)
#define BOXED_NUMBER_INIT_ARITY 2

void print_list(List head) {
  match(head) {
    of(Nil) return;
    of(Cons, lhs, rhs) {
      printf("%d, ", *(int *)*lhs);
      print_list(*(List *)*rhs);
    }
  }
}

int main() {
  ML99_LIST_EVAL(ML99_listMapI(v(BOXED_NUMBER),
                               ML99_listReplicate(v(BOXED_NUMBER_COUNT), v(0))))
  ML99_LIST_EVAL(ML99_listMapI(v(BOXED_NUMBER_INIT),
                               ML99_listReplicate(v(BOXED_NUMBER_COUNT), v(0))))

  List nil = Nil();
  List t0 = Cons(_1, &nil);
  List t1 = Cons(_2, &t0);
  List t2 = Cons(_3, &t1);
  List t3 = Cons(_4, &t2);
  List example = Cons(_5, &t3);
  print_list(example);
}
