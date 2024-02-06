#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int red;
  int green;
  int blue;
} Bag;

int main() {
  FILE *fptr;
  fptr = fopen("./input.txt", "r");
  if (!fptr) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char s[1001];
  Bag config = {12, 13, 14};

  int gameSum = 0;

  while (fgets(s, 1001, fptr)) {
    int gameId;
    char *scopy = malloc(strlen(s) + 1);
    if (scopy != NULL) {
      strcpy(scopy, s);
      char *saveptr1;
      char *gameLabel = strtok_r(scopy, ":", &saveptr1);
      if (gameLabel != NULL && sscanf(gameLabel, "Game %d", &gameId) == 1) {
        int isPossible = 1;

        char *saveptr2;
        char *cubeSet = strtok_r(NULL, ";", &saveptr1);
        while (cubeSet != NULL && isPossible) {
          Bag round = {0, 0, 0};

          char *cubeColorCount = strtok_r(cubeSet, ",", &saveptr2);
          while (cubeColorCount != NULL) {
            int count;
            char color[10];
            if (sscanf(cubeColorCount, "%d %s", &count, color) == 2) {
              if (strcmp(color, "red") == 0) {
                round.red += count;
                if (round.red > config.red)
                  isPossible = 0;
              } else if (strcmp(color, "green") == 0) {
                round.green += count;
                if (round.green > config.green)
                  isPossible = 0;
              } else if (strcmp(color, "blue") == 0) {
                round.blue += count;
                if (round.blue > config.blue)
                  isPossible = 0;
              }
            }
            cubeColorCount = strtok_r(NULL, ",", &saveptr2);
          }

          cubeSet = strtok_r(NULL, ";", &saveptr1);
        }

        if (isPossible) {
          gameSum += gameId;
          printf("Game %d is valid\n", gameId);
        }
      }
      free(scopy);
    } else {
      printf("Memory allocation failed\n");
    }
  }

  printf("SUM: %d\n", gameSum);
  fclose(fptr);
  return 0;
}
