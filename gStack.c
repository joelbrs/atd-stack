#include "gStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct _stack_ {
  int maxItems;
  int top;
  void **items;
} Stack;

Stack *stkCreate(int max) {
  Stack *s;

  if (max > 0) {
    s = (Stack *)malloc(sizeof(Stack));

    if (s != NULL) {
      s->items = (void **)malloc(sizeof(void *) * max);
      s->maxItems = max;
      s->top = -1;

      return s;
    }
  }

  return NULL;
};

int stkPush(Stack *s, void *elm) {
  if (s != NULL && s->top < s->maxItems - 1) {
    s->top++;
    s->items[s->top] = elm;

    return TRUE;
  }

  return FALSE;
};

void *stkPop(Stack *s) {
  if (s != NULL && s->top >= 0) {
    void *aux = s->items[s->top];
    s->top--;

    return aux;
  }

  return NULL;
};

void *stkTop(Stack *s) {
  if (s != NULL && s->top >= 0) {
    void *aux = s->items[s->top];
    return aux;
  }

  return NULL;
};

int stkIsEmpty(Stack *s) {
  if (s != NULL && s->top < 0) {
    return TRUE;
  }
  return FALSE;
};

int stkDestroy(Stack *s) {
  if (s != NULL && s->top < 0) {
    free(s->items);
    free(s);

    return TRUE;
  }

  return FALSE;
};

char *revertString(char *c) {
  int length = strlen(c);
  Stack *stack = stkCreate(length);

  if (stack != NULL) {
    for (int i = 0; i < length; i++) {
      char *ch = (char *)malloc(sizeof(char));
      if (ch != NULL) {
        *ch = c[i];
        stkPush(stack, ch);
      }
    }

    for (int j = 0; j < length; j++) {
      char *ch = (char *)stkPop(stack);
      c[j] = *ch;
      free(ch);
    }

    stkDestroy(stack);
    return c;
  }
  return NULL;
};

int verifyBrackets(char *b) {
  Stack *s = stkCreate(strlen(b));

  if (s != NULL) {
    for (int i = 0; i < strlen(b); i++) {
      if (b[i] == '(' || b[i] == '[' || b[i] == '{') {
        char *aux = (char *)malloc(sizeof(char));

        if (aux != NULL) {
          *aux = b[i];
          stkPush(s, aux);
        }
      } else {
        if (b[i] == ')' || b[i] == ']' || b[i] == '}') {
          if (stkIsEmpty(s)) {
            stkDestroy(s);
            return FALSE;
          } else {
            char *top = (char *)stkTop(s);

            if (*top == '(' && b[i] == ')' || *top == '[' && b[i] == ']' ||
                *top == '{' && b[i] == '}') {
              stkPop(s);
            } else {
              break;
            }
          }
        }
      }
    }

    if (stkIsEmpty(s)) {
      stkDestroy(s);
      return TRUE;
    }
  }

  return FALSE;
};

int isX0Y(char *s) {
  int len = strlen(s), i = 0;
  char *c;

  Stack *stk = stkCreate(len);

  if (stk != NULL) {
    while (s[i] != '0' && i < len) {
      stkPush(stk, (void *)&s[i]);
      i++;
    }

    if (s[i] == '0') {
      i++;
    }

    c = stkPop(stk);
    while (i < len && c != NULL) {
      if (*c != s[i]) {
        break;
      }
      i++;
      c = stkPop(stk);
    }

    if (i == len) {
      return TRUE;
    }
  }
  return FALSE;
};

int defineIAsTop(Stack *s, int i) {
  Stack *auxStk;
  int k = 0;
  char *aux;

  if (s != NULL) {
    auxStk = stkCreate(s->maxItems);
    if (auxStk != NULL) {
      while (stkIsEmpty(s) != TRUE && k < i) {
        stkPush(auxStk, stkPop(s));
        k++;
      }

      aux = stkPop(auxStk);
      while (stkIsEmpty(auxStk) != TRUE) {
        stkPush(s, stkPop(auxStk));
      }

      stkPop(s);
      stkPop(s);
      stkPush(s, aux);
      return TRUE;
    }
  }
  return FALSE;
};

int defineIAsSecondItem(Stack *s, int i) {
  Stack *auxStk;
  int k = 0;
  void *auxItemI, *auxSecondItem;
  if (s != NULL) {
    auxStk = stkCreate(s->maxItems);
    if (auxStk != NULL) {
      while (!stkIsEmpty(s) && k < i) {
        stkPush(auxStk, stkPop(s));
        k++;
      }
      auxItemI = stkPop(auxStk);
      while (!stkIsEmpty(auxStk)) {
        stkPush(s, stkPop(auxStk));
      }

      auxSecondItem = stkPop(s);
      stkPush(s, auxItemI);
      stkPush(s, auxSecondItem);
      stkDestroy(auxStk);
      return TRUE;
    }
  }
  return FALSE;
};

int defineIAsNthItemTop(Stack *s, int n) {
  Stack *auxStk;
  int k = 0;
  void *auxItemI;
  if (s != NULL && n > 0) {
    auxStk = stkCreate(s->maxItems);
    if (auxStk != NULL) {
      while (!stkIsEmpty(s) && k < n) {
        stkPush(auxStk, stkPop(s));
        k++;
      }

      auxItemI = stkPop(auxStk);
      while (!stkIsEmpty(auxStk)) {
        stkPush(s, stkPop(auxStk));
      }
      k = 0;
      while (k < n) {
        stkPop(s);
        k++;
      }
      stkPush(s, auxItemI);
      stkDestroy(auxStk);
      return TRUE;
    }
  }
  return FALSE;
};

int defineIAsNthItem(Stack *s, int n) {
  Stack *auxStk;
  int k = 0;
  if (s != NULL && n > 0) {
    auxStk = stkCreate(s->maxItems);
    if (auxStk != NULL) {
      while (!stkIsEmpty(s) && k < n) {
        stkPush(auxStk, stkPop(s));
        k++;
      }
      stkPush(s, stkPop(auxStk));
      while (!stkIsEmpty(auxStk)) {
        stkPush(s, stkPop(auxStk));
      }
      stkDestroy(auxStk);
      return TRUE;
    }
  }

  return FALSE;
};

int defineIAsOnlyItem(Stack *s, int i) {
  Stack *auxStk;
  int k = 0;
  if (s != NULL) {
    auxStk = stkCreate(s->maxItems);
    if (auxStk != NULL) {
      while (!stkIsEmpty(s) && k < i) {
        stkPush(auxStk, stkPop(s));
        k++;
      }
      stkPush(s, stkPop(auxStk));
      while (!stkIsEmpty(auxStk)) {
        stkPop(auxStk);
      }
      stkDestroy(auxStk);
      return TRUE;
    }
  }
  return FALSE;
};

int defineIAsLastItem(Stack *s, int i) {
  Stack *auxStk;
  int k = 0;
  if (s != NULL) {
    auxStk = stkCreate(s->maxItems);
    if (auxStk != NULL) {
      while (!stkIsEmpty(s) && k < i) {
        stkPush(auxStk, stkPop(s));
        k++;
      }
      stkPush(s, stkPop(auxStk));
      while (!stkIsEmpty(auxStk)) {
        stkPush(s, stkPop(auxStk));
      }
      stkDestroy(auxStk);
      return TRUE;
    }
  }
  return FALSE;
};

int defineIAs3thLastItem(Stack *s, int i) {
  Stack *auxStk;
  int k = 0;
  void *auxItemI;
  if (s != NULL) {
    auxStk = stkCreate(s->maxItems);
    if (auxStk != NULL) {
      while (!stkIsEmpty(s) && k < i) {
        stkPush(auxStk, stkPop(s));
        k++;
      }
      auxItemI = stkPop(auxStk);
      for (int j = 0; j < 3; j++) {
        stkPush(s, stkPop(auxStk));
      }
      stkPush(s, auxItemI);
      while (!stkIsEmpty(auxStk)) {
        stkPush(s, stkPop(auxStk));
      }
      stkDestroy(auxStk);
      return TRUE;
    }
  }
  return FALSE;
};