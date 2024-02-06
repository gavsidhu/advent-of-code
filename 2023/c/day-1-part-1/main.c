#include <ctype.h>
#include <stdio.h>
#include <string.h>

int getFirstDigit(char string[]);
int getLastDigit(char string[]);

int main() {
  FILE *fptr;
  int sum = 0;

  fptr = fopen("input.txt", "r");

  char s[100];

  while (fgets(s, 100, fptr)) {
    int firstDigit = getFirstDigit(s);
    int lastDigit = getLastDigit(s);

    int combinedNumber = firstDigit * 10 + lastDigit;

    sum = sum + combinedNumber;
  };

  fclose(fptr);

  printf("%d\n", sum);

  return 0;
}

int getFirstDigit(char string[]) {
  for (int i = 0; i < strlen(string); i++) {
    if (isdigit(string[i])) {
      return string[i] - '0';
    }
  }
  return -1;
}

int getLastDigit(char string[]) {
  for (int i = strlen(string) - 1; i >= 0; i--) {
    if (isdigit(string[i])) {
      return string[i] - '0';
    }
  }

  return -1;
}
