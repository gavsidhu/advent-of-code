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

  int gamepower = 0;

  while (fgets(s, 1001, fptr)) {
    int gameId;
    int minSum = 0;
    char *scopy = malloc(strlen(s) + 1);
    if (scopy != NULL) {
      strcpy(scopy, s);
      char *saveptr1;
      char *gameLabel = strtok_r(scopy, ":", &saveptr1);
      if (gameLabel != NULL && sscanf(gameLabel, "Game %d", &gameId) == 1) {
        int isPossible = 1;

        Bag minimumCubes = {0, 0, 0};

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
                round.red = count;
                if (round.red > minimumCubes.red)
                  minimumCubes.red = round.red;
              } else if (strcmp(color, "green") == 0) {
                round.green = count;
                if (round.green > minimumCubes.green)
                  minimumCubes.green = round.green;
              } else if (strcmp(color, "blue") == 0) {
                round.blue = count;
                if (round.blue > minimumCubes.blue)
                  minimumCubes.blue = round.blue;
              }
            }
            cubeColorCount = strtok_r(NULL, ",", &saveptr2);
          }

          cubeSet = strtok_r(NULL, ";", &saveptr1);
        }

        minSum = minimumCubes.red + minimumCubes.green + minimumCubes.blue;
        gamepower += minimumCubes.red * minimumCubes.green * minimumCubes.blue;

        printf("Game Minimum Sum: %d\n", minSum);
      }
      free(scopy);
    } else {
      printf("Memory allocation failed\n");
    }
  }

  printf("Power: %d\n", gamepower);
  fclose(fptr);
  return 0;
}
