#include <_ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 500
#define MAX_CHARS_LENGTH 500

int isCharNumber(char c);
int isDot(char c);
int checkAdjacentSymbols(char matrix[MAX_CHARS_LENGTH][MAX_CHARS_LENGTH], int x,
                         int y, int length, int dirs[8][2]);

int main() {
  FILE *file;
  char matrix[MAX_CHARS_LENGTH][MAX_CHARS_LENGTH];
  char line[MAX_LINE_LENGTH];
  int length = 0;
  int sum = 0;

  int dirs[8][2] = {{0, 1}, {0, -1}, {1, 0},  {-1, 0},
                    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

  file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return -1;
  }

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    line[strcspn(line, "\n")] = 0;

    // Copy characters to matrix
    strcpy(matrix[length], line);
    length++;
  }

  fclose(file);

  for (int x = 0; x < length; x++) {
    int isNumber = 0;

    char *row = matrix[x];

    for (int y = 0; y < strlen(row); y++) {
      isNumber = isCharNumber(matrix[x + 0][y + 0]);
      if (isNumber) {
        int numStart = y;
        while (y < strlen(matrix[x]) && isdigit(matrix[x][y])) {
          y++;
        }

        int numEnd = y;
        char numStr[20];
        strncpy(numStr, &matrix[x][numStart], numEnd - numStart);
        numStr[numEnd - numStart] = '\0';
        int num = atoi(numStr);
        int hasAdjacentSymbol = 0;
        for (int i = numStart; i < numEnd && !hasAdjacentSymbol; i++) {
          hasAdjacentSymbol = checkAdjacentSymbols(matrix, x, i, length, dirs);
        }

        if (hasAdjacentSymbol) {
          sum += num;
        }
      }
    }
  }

  printf("Sum: %d\n", sum);
}

int isCharNumber(char c) {
  if (isdigit(c) > 0) {
    return 1;
  }
  return 0;
}

int isDot(char c) { return c == '.'; }

int checkAdjacentSymbols(char matrix[MAX_CHARS_LENGTH][MAX_CHARS_LENGTH], int x,
                         int y, int length, int dirs[8][2]) {
  for (int i = 0; i < 8; i++) {
    int dx = x + dirs[i][0];
    int dy = y + dirs[i][1];
    if (dx >= 0 && dx < length && dy >= 0 && dy < strlen(matrix[dx]) &&
        !isDot(matrix[dx][dy]) && !isCharNumber(matrix[dx][dy])) {

      printf("Symbol at:\nx: %d\ny: %d\n", dx, dy);
      return 1;
    }
  }
  return 0;
}
