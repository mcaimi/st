/*
   utilities
*/

#include "utils.h"

ImageList *last(ImageList *element) {
  if(ISNULL(element->next)) {
    return element;
  } else {
    return last(element->next);
  }
}

ImageList *first(ImageList *element) {
  if (ISNULL(element->prev)) {
    return element;
  } else {
    return first(element->prev);
  }
}
