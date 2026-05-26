#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  FILE *fp;
  unsigned int line_count = 0;
  int gamma = 0, epsilon = 0;
  if (argc < 3) {
    printf("Usage: part1 <input file> <bit length>\n");
    return 1;
  }
  int bit_depth = atoi(argv[2]);
  unsigned int* one_counts = (unsigned int*) calloc(bit_depth, sizeof(int));
  char* report_line = (char* ) calloc(bit_depth + 1, sizeof(char));
  if ((fp = fopen(argv[1], "r")) == NULL) {
    printf("Error: could not open file %s\n", argv[1]);
    return 1;
  }
  while (fscanf(fp, "%s", report_line) != EOF) {
    for (int i = 0; i < bit_depth; i++) {
      if (report_line[i] == '1')
        one_counts[i]++;
    }
    line_count++;
  }
  fclose(fp);
  for (int i = 0 ; i < bit_depth; i++) {
    gamma = (gamma << 1) | (one_counts[i] > (line_count / 2));
    epsilon = (epsilon << 1) | (one_counts[i] <= (line_count / 2));
  }
  free(one_counts);
  free(report_line);
  printf("Part1 answer: %d\n", (gamma * epsilon));

  return 0;
}
