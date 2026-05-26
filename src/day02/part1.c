#include <stdio.h>

int main(int argc, char** argv)
{
  FILE *fp;
  unsigned int h_pos = 0, depth = 0, file_value;
  char direction[8];
  if (argc < 2) {
    printf("Usage: part1 <input file>\n");
    return 1;
  }
  if((fp = fopen(argv[1], "r")) == NULL) {
    printf("Error: could not open file %s\n", argv[1]);
    return 1;
  }
  while(fscanf(fp, "%s %d", direction, &file_value) != EOF) {
    switch(direction[0]) {
      case 'f':
        h_pos += file_value;
        break;
      case 'u':
        depth -= file_value;
        break;
      case 'd':
        depth += file_value;
        break;
      default:
        printf("Derp!\n");
        break;
    }
  }
  printf("Part1 answer: %d\n", (h_pos * depth));
  fclose(fp);

  return 0;
}
