#include "ex10_ll_cycle.h"
#include <stddef.h>

int ll_has_cycle(node *head) {
  /* TODO: Implement ll_has_cycle */
  if (head == NULL) {
    return 0;
  }

  node *fast_ptr = head->next;
  if (fast_ptr != NULL) {
    fast_ptr = fast_ptr->next;
  } else {
    return 0;
  }
  node *slow_ptr = head->next;

  while (fast_ptr != slow_ptr) {
    if (fast_ptr != NULL) {
      fast_ptr = fast_ptr->next;

      if (fast_ptr != NULL) {
        fast_ptr = fast_ptr->next;
      } else {
        return 0;
      }
    } else {
      return 0;
    }

    slow_ptr = slow_ptr->next;
  }
  return 1;
}
