#ifndef _STACK_H_
#define _STACK_H_

typedef struct _stack_ Stack;

Stack *stkCreate(int max);

int stkPush(Stack *s, void *elm);

void *stkPop(Stack *s);

void *stkTop(Stack *s);

int stkIsEmpty(Stack *s);

int stkDestroy(Stack *s);

char *revertString(char *c);

int verifyBrackets(char *b);

int isX0Y(char *s);

int defineIAsTop(Stack *s, int i);

int defineIAsSecondItem(Stack *s, int i);

int defineIAsNthItemTop(Stack *s, int n);

int defineIAsNthItem(Stack *s, int n);

int defineIAsOnlyItem(Stack *s, int i);

int defineIAsLastItem(Stack *s, int i);

int defineIAs3thLastItem(Stack *s, int i);

#endif
