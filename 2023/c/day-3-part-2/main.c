#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_CHARS_LENGTH 1000
#define MAX_UNIQUE_NUMBERS 2

int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                  {0, 1},   {1, -1}, {1, 0},  {1, 1}};

long long findGearRatios(char matrix[MAX_CHARS_LENGTH][MAX_CHARS_LENGTH],
                         int length, int dirs[8][2]);
int parseNumber(char *line, int startingIndex);
int contains(int arr[], int size, int value);
void addUnique(int arr[], int *size, int value);
long long isGear(char matrix[MAX_CHARS_LENGTH][MAX_CHARS_LENGTH], int x, int y,
                 int length, int dirs[8][2]);

int main() {
  FILE *fptr;
  char line[MAX_LINE_LENGTH];
  char matrix[MAX_CHARS_LENGTH][MAX_CHARS_LENGTH];
  int length = 0;
  long long sum = 0;

  fptr = fopen("./input.txt", "r");
  if (fptr == NULL) {
    perror("Error opening file");
    return -1;
  }

  while (fgets(line, MAX_LINE_LENGTH, fptr)) {
    line[strcspn(line, "\n")] = '\0';
    strcpy(matrix[length++], line);
  }
  fclose(fptr);

  for (int x = 0; x < length; x++) {
    int inSymbol = 0;

    char *row = matrix[x];

    for (int y = 0; y < length; y++) {
      inSymbol = matrix[x + 0][y + 0] == '*';

      if (inSymbol) {
        printf("Symbol: %c\n", matrix[x + 0][y + 0]);
        int numFound = isGear(matrix, x, y, length, dirs);
        printf("Numbers found: %d\n", numFound);
        sum += numFound;
      }
    }
  }
  printf("Sum: %lld\n", sum);

  return 0;
}

long long isGear(char matrix[MAX_CHARS_LENGTH][MAX_CHARS_LENGTH], int x, int y,
                 int length, int dirs[8][2]) {
  int uniqueNumbers[MAX_UNIQUE_NUMBERS] = {0};
  int uniqueCount = 0;
  for (int i = 0; i < 8; i++) {
    int adjX = x + dirs[i][0];
    int adjY = y + dirs[i][1];

    if (adjX >= 0 && adjX < length && adjY >= 0 && adjY < length &&
        isdigit(matrix[adjX][adjY])) {
      int completeNumber = parseNumber(matrix[adjX], adjY);
      printf("Adjacent Number: %d, x: %d, y: %d\n", completeNumber, adjX, adjY);
      if (!contains(uniqueNumbers, uniqueCount, completeNumber)) {
        if (uniqueCount < MAX_UNIQUE_NUMBERS) {
          uniqueNumbers[uniqueCount++] = completeNumber;
        }
      }
    }
  }

  printf("Length of uniqueNumbers: %d\n", uniqueCount);

  if (uniqueCount == 2) {
    return uniqueNumbers[0] * uniqueNumbers[1];
  }

  return 0;
}

int parseNumber(char *line, int startingIndex) {
  int leftIndex = startingIndex;
  while (leftIndex > 0 && isdigit(line[leftIndex - 1])) {
    leftIndex--;
  }

  int rightIndex = startingIndex;
  while (isdigit(line[rightIndex]) && rightIndex < MAX_LINE_LENGTH) {
    rightIndex++;
  }
  rightIndex--;

  int numberLength = rightIndex - leftIndex + 1;
  char numberString[numberLength + 1];
  strncpy(numberString, &line[leftIndex], numberLength);
  numberString[numberLength] = '\0';
  int number = atoi(numberString);

  printf("Number: %d\n", number);
  return number;
}

int contains(int arr[], int size, int value) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == value) {
      return 1;
    }
  }
  return 0;
}

void addUnique(int arr[], int *size, int value) {
  if (!contains(arr, *size, value)) {
    arr[(*size)++] = value;
  }
}
