#include "gStack.h"
#include <stdio.h>
#include <string.h>

#define TRUE 0
#define FALSE 1

int main(void) {
  char str[100] = "Joel";

  // remove '\n' character of string
  str[strcspn(str, "\n")] = '\0';
  revertString(str);

  printf("%s\n", str);

  char brackets[100] = "{[()]}";
  brackets[strcspn(brackets, "\n")] = '\0';
  int bracketsVerified = verifyBrackets(brackets);

  if (bracketsVerified) {
    printf("Ok!\n");
  } else {
    printf("Oops!\n");
  }

  char palindromo[100] = "12221122022112221";
  palindromo[strcspn(palindromo, "\n")] = '\0';
  int isx0y = isX0Y(palindromo);

  if (isx0y) {
    printf("It is a X0Y");
  } else {
    printf("It isn't a X0Y");
  }

  return 0;
}