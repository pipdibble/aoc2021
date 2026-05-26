#include <stdio.h>

int main (int argc, char** argv)
{
  FILE *fp;
  unsigned int depth, count_of_increases = 0, counts[4];
  counts[0] = counts[1] = counts[2] = counts[3] = 0;
  if (argc < 2) {
    printf("Usage: part1 <input file>");
    return 1;
  }
  if ((fp = fopen(argv[1], "r")) == NULL) {
    printf("Could not open file for reading: %s", argv[1]);
    return 1;
  }
  for (int ticker = 0; fscanf(fp, "%d", &depth) != EOF; ticker++) {
    switch (ticker % 4) {
      case 0:
        counts[0] += depth;
        counts[2] += depth;
        counts[3] += depth;
        if (counts[2] > counts[1] && ticker >= 3)
          count_of_increases++;
        counts[1] = 0;
        break;
      case 1:
        counts[0] += depth;
        counts[1] += depth;
        counts[3] += depth;
        if (counts[3] > counts[2] && ticker >= 3)
          count_of_increases++;
        counts[2] = 0;
        break;
      case 2:
        counts[0] += depth;
        counts[1] += depth;
        counts[2] += depth;
        if (counts[0] > counts[3] && ticker >= 3)
          count_of_increases++;
        counts[3] = 0;
        break;
      case 3:
        counts[1] += depth;
        counts[2] += depth;
        counts[3] += depth;
        if (counts[1] > counts[0])
          count_of_increases++;
        counts[0] = 0;
        break;
      default:
        printf("Derp!");
        break;
    }
  }
  printf("Part 2 answer: %d\n", count_of_increases);
  fclose(fp);

  return 0;
}
