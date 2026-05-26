#include <stdio.h>

int main (int argc, char** argv)
{
  FILE *fp;
  unsigned int depth = 0, last_depth = 0;
  unsigned int count_of_increases = 0;

  if (argc < 2) {
    printf("Usage: part1 <input file>");
    return 1;
  }
  if ((fp = fopen(argv[1], "r")) == NULL) {
    printf("Could not open file for reading: %s", argv[1]);
    return 1;
  }
  fscanf(fp, "%d", &last_depth);
  while(fscanf(fp, "%d", &depth) != EOF) {
    if (depth > last_depth)
      count_of_increases++;
    last_depth = depth;
  }
  printf("Part 01: %d", count_of_increases);

  return 0;
}
