#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int* indicies;
  int size;
} Rating;

typedef struct {
  char *contents;
  long size;
} FileContents;

void processRating(FileContents *fc, Rating *rating, bool type, int index);

int main (int argc, char** argv)
{
  FILE *fp;
  unsigned long line_count = 0;
  int bit_length = 0;
  FileContents file_contents;
  Rating oxygen_generator_rating = { NULL, 0 }, co2_scrubber_rating = { NULL, 0};

  if (argc < 2) {
    printf("Usage: part2 <input file>");
    return 1;
  }
  if ((fp = fopen(argv[1], "rb")) == NULL) {
    printf("Error: could not open file %s\n", argv[1]);
    return 1;
  }
  file_contents.size = 1;
  file_contents.contents = (char*) malloc(file_contents.size * sizeof(char));
  int file_byte, c = 0;
  while ((file_byte = fgetc(fp)) != EOF) {
    if (file_byte == '0' || file_byte == '1') {
      if (c >= file_contents.size) {
        file_contents.size = c + 1;
        file_contents.contents = (char*) realloc(file_contents.contents, file_contents.size * sizeof(char));
      }
      file_contents.contents[c++] = (char) file_byte;
    } else {
      if (bit_length == 0)
        bit_length = c;
      if (file_byte == '\n')
        line_count++;
    }
  }
  file_contents.contents = (char*) realloc(file_contents.contents, (file_contents.size + 1) * sizeof(char));
  file_contents.contents[file_contents.size] = '\0';
  fclose(fp);
  oxygen_generator_rating.indicies = (int*) malloc(line_count * sizeof(int));
  oxygen_generator_rating.size = line_count;
  co2_scrubber_rating.indicies = (int*) malloc(line_count * sizeof(int));
  co2_scrubber_rating.size = line_count;
  for (int i = 0; i < line_count; i++){
    *(oxygen_generator_rating.indicies + i) = i * bit_length;
    *(co2_scrubber_rating.indicies + i) = i * bit_length;
  }
  for (int index = 0; index < bit_length && oxygen_generator_rating.size > 1; index++) {
    processRating(&file_contents, &oxygen_generator_rating, true, index);
  }
  for (int index = 0; index < bit_length && co2_scrubber_rating.size > 1; index++) {
    processRating(&file_contents, &co2_scrubber_rating, false, index);
  }
  int oxygen = 0, carbon = 0;
  for (int i = 0; i < bit_length; i++) {
    oxygen = (oxygen << 1) | (*(file_contents.contents + oxygen_generator_rating.indicies[0] + i) == '1');
    carbon = (carbon << 1) | (*(file_contents.contents + co2_scrubber_rating.indicies[0] + i) == '1');
  }
  printf("Part2 answer: %d\n", oxygen * carbon);

  free(file_contents.contents);
  free(oxygen_generator_rating.indicies);
  free(co2_scrubber_rating.indicies);
  return 0;
}

void processRating(FileContents *fc, Rating *rating, bool type, int index)
{
  const bool GAMMA = true;
  Rating ones = { NULL, 0 }, zeroes = { NULL, 0 };
  for (int i = 0; i < rating->size; i++) {
    if (fc->contents[rating->indicies[i] + index] == '1') {
      if (ones.indicies == NULL)
        ones.indicies = (int*) malloc((ones.size + 1) * sizeof(int));
      else 
        ones.indicies = (int*) realloc(ones.indicies, (ones.size + 1) * sizeof(int));
      ones.indicies[ones.size] = rating->indicies[i];
      ones.size++;
    } else {
      if (zeroes.indicies == NULL)
        zeroes.indicies = (int*) malloc((zeroes.size + 1) * sizeof(int));
      else
        zeroes.indicies = (int*) realloc(zeroes.indicies, (zeroes.size + 1) * sizeof(int));
      zeroes.indicies[zeroes.size] = rating->indicies[i];
      zeroes.size++;
    }
  }
  free(rating->indicies);
  if (type == GAMMA) {
    if (ones.size >= zeroes.size) {
      rating->indicies = ones.indicies;
      rating->size = ones.size;
      if (zeroes.indicies != NULL)
        free(zeroes.indicies);
    } else {
      rating->indicies = zeroes.indicies;
      rating->size = zeroes.size;
      if (ones.indicies != NULL)
        free(ones.indicies);
    }
  } else {
    if (ones.size < zeroes.size) {
      rating->indicies = ones.indicies;
      rating->size = ones.size;
      if (zeroes.indicies != NULL)
        free(zeroes.indicies);
    } else {
      rating->indicies = zeroes.indicies;
      rating->size = zeroes.size;
      if (ones.indicies != NULL)
        free(ones.indicies);
    }
  }
  return;
}
