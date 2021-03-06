#include "test_utils.h"

const char FILENAME[] = "test_temp_file.mp3";
FILE* FP = NULL;

FILE* open_test_file_in_read_write_mode()
{
  FP = fopen(FILENAME, "wb+");

  return FP;
}

void write_data_to_test_file_and_rewind(const unsigned char* input, const size_t n)
{
  fwrite(input, sizeof(unsigned char), n, FP);
  rewind(FP);
}

void rewind_testfile()
{
  rewind(FP);
}

int close_and_remove_test_file()
{
  if (FP) {
    if (fclose(FP)) {
      return 1;
    }

    FP = NULL;

    if (remove(FILENAME)) {
      return 1;
    }
  }

  return 0;
}
