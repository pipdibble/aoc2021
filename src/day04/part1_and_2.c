#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int number;
  bool dabbed;
} DabberNumber;

typedef struct {
  DabberNumber grid[25];
  bool winner;
} DabberGrid;

DabberNumber newDabberNumber(int number);
DabberGrid newDabberGrid(int* numbers);
bool dabNumber(DabberGrid *g, int number);
bool winnerCheck(DabberGrid *g);
long calcScore(DabberGrid *g, int last_number);

int main (int argc, char **argv)
{
  struct {
    DabberGrid *player;
    int num_players;
    int *nums_called;
    int num_nums;
  } bingo;
  bingo.num_players = 0;
  bingo.num_nums = 0;
  FILE *fp;
  int file_char;
  int number = 0;
  if (argc < 2) {
    printf("Usage: part1 <input filename>\n");
    return 1;
  }
  if ((fp = fopen(argv[1], "r")) == NULL) {
    perror("fopen");
    return 1;
  }
  char file_line[1000];
  fscanf(fp, "%999s", file_line);
  int line_length = strnlen(file_line, 999);
  char *next = file_line;
  while (next < (file_line + line_length)) {
    if (*next == ',')
      next++;
    int a = strtol(next, &next, 10);
    if (errno == EINVAL || errno == ERANGE) {
      perror("strtol");
      fclose(fp);
      return 1;
    }
    if (bingo.num_nums == 0) {
      bingo.nums_called = (int*) malloc((bingo.num_nums + 1) * sizeof(int));
    } else {
      bingo.nums_called = (int*) realloc(bingo.nums_called, (bingo.num_nums + 1) * sizeof(int));
    }
    *(bingo.nums_called + bingo.num_nums) = a;
    bingo.num_nums++;
  }
  int num_per_grid = 0;
  while (fscanf(fp, "%999s", file_line) != 0 && !feof(fp)) {
    int a = strtol(file_line, NULL, 10);
    if (a == 0 && errno == EINVAL)
      continue;
    if (bingo.num_players == 0) {
      bingo.player = (DabberGrid*) malloc((bingo.num_players + 1) * sizeof(DabberGrid));
      bingo.num_players++;
    }
    if (num_per_grid == 25) {
      num_per_grid = 0;
      bingo.player = (DabberGrid*) realloc(bingo.player, (bingo.num_players + 1) * sizeof(DabberGrid));
      bingo.num_players++;
    }
    bingo.player[bingo.num_players - 1].grid[num_per_grid] = newDabberNumber(a);
    bingo.player[bingo.num_players - 1].winner = false;
    num_per_grid++;
  }
  bool found = false;
  for (int numbers = 0; numbers < bingo.num_nums; numbers++) {
    int number = bingo.nums_called[numbers];
    for (int players = 0; players < bingo.num_players; players++) {
      if (bingo.player[players].winner)
        continue;
      bool hit = dabNumber(&bingo.player[players], number);
      if (hit) {
        bool winner = winnerCheck(&bingo.player[players]);
        if (winner) {
          printf("Player %d wins!\n", (players + 1));
          long score = calcScore(&bingo.player[players], number);
          printf("Score: %ld\n", score);
          bingo.player[players].winner = true;
        }
      }
    }
  }

  fclose(fp);
  free(bingo.nums_called);
  free(bingo.player);
  return 0;
}

DabberNumber newDabberNumber(int number)
{
  DabberNumber newNum = { number, false };
  return newNum;
}

DabberGrid newDabberGrid(int* numbers)
{
  DabberGrid newGrid;
  for (int i = 0; i < 25; i++) {
    newGrid.grid[i] = newDabberNumber(numbers[i]);
  }
}

bool dabNumber(DabberGrid *g, int number)
{
  for(int i = 0; i < 25; i++) {
    if (g->grid[i].number == number) {
      return (g->grid[i].dabbed = true);
    }
  }
  return false;
}

bool winnerCheck(DabberGrid *g)
{
  for (int row = 0; row < 5; row++) {
    for (int column = 0; column < 5; column++) {
      if (!g->grid[(row * 5) + column].dabbed)
        break;
      if (column == 4)
        return true;
    }
  }
  for (int column = 0; column < 5; column++) {
    for (int row = 0; row < 5; row++) {
      if (!g->grid[(row * 5) + column].dabbed)
        break;
      if (row == 4)
        return true;
    }
  }
  return false;
}

long calcScore(DabberGrid *g, int last_number)
{
  long score = 0;
  for (int row = 0; row < 5; row++) {
    for (int column = 0; column < 5; column++) {
      int offset = (row * 5) + column;
      if (!g->grid[offset].dabbed){
        score += g->grid[offset].number;
      }
    }
  }
  score *= last_number;
  return score;
}
