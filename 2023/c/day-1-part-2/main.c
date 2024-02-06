#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getFirstNumber(char str[]);
int getLastNumber(char str[]);

int main() {
  FILE *fptr;
  int sum = 0;

  fptr = fopen("input.txt", "r");

  char s[100];

  while (fgets(s, 100, fptr)) {
    printf("string: %s", s);
    int firstDigit = getFirstNumber(s);
    int lastDigit = getLastNumber(s);

    int combinedNumber = firstDigit * 10 + lastDigit;

    sum = sum + combinedNumber;
  };

  fclose(fptr);

  printf("%d\n", sum);

  return 0;
}

int wordToNumber(char *word) {
  if (strstr(word, "one") != NULL)
    return 1;
  if (strstr(word, "two") != NULL)
    return 2;
  if (strstr(word, "three") != NULL)
    return 3;
  if (strstr(word, "four") != NULL)
    return 4;
  if (strstr(word, "five") != NULL)
    return 5;
  if (strstr(word, "six") != NULL)
    return 6;
  if (strstr(word, "seven") != NULL)
    return 7;
  if (strstr(word, "eight") != NULL)
    return 8;
  if (strstr(word, "nine") != NULL)
    return 9;
  return -1;
}

int getFirstNumber(char str[]) {
  int len = strlen(str);

  // Allocate memory based on the length of str
  char *word = (char *)malloc(len + 1);

  // Handle memory allocation failure
  if (!word) {
    return -1;
  }

  int wordIndex = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (isdigit(str[i])) {
      return str[i] - '0';
    } else if (isalpha(str[i])) {
      word[wordIndex] = str[i];
      wordIndex++;
      word[wordIndex] = '\0';
      int number = wordToNumber(word);
      if (number != -1)
        return number;
    }
  }
  return -1;
}

int getLastNumber(char str[]) {
  int len = strlen(str);

  char *word = (char *)malloc(len + 1);

  if (!word) {
    return -1;
  }

  int wordIndex = 0;

  for (int i = len - 1; i >= 0; i--) {
    if (isdigit(str[i])) {
      return str[i] - '0';
    } else if (isalpha(str[i])) {
      memmove(word + 1, word, wordIndex);
      word[0] = str[i];
      wordIndex++;
      word[wordIndex] = '\0';
      int number = wordToNumber(word);
      if (number != -1) {
        return number;
      }
    }
  }
  return -1;
}
