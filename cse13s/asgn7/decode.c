#include "code.h"
#include "io.h"
#include "word.h"
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define OPTIONS "vi::o::"

//
// Get the binary lenth to store a code
//
// code: input number
// return: the lenth needed
//
uint8_t bit_len(int code);

// determinant whether to display the stat
int display = 0;

// file name of input and outfile
char *file_input = NULL, *file_output = NULL;

// initialize the input file and output file value
int infile, outfile;

// stat count
uint64_t total_bits, total_syms;

int main(int argc, char **argv) {
  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'v':
      // display compression statistics
      display = 1;
      break;
    case 'i':
      // specify input to compress
      file_input = argv[optind];
      break;
    case 'o':
      // specify output of compressed input
      file_output = argv[optind];
      break;
    default:
      puts("invalid argument pass in");
      exit(-1);
      break;
    }
  }

  // open infile
  if (file_input) {
    infile = open(file_input, O_RDONLY);
  } else {
    infile = STDIN_FILENO;
  }
  if (infile < 0) {
    puts("failed open infile");
    exit(-1);
  }

  // get the file header info and check magic number
  FileHeader *header = (FileHeader *)calloc(1, sizeof(FileHeader));
  read_header(infile, header);
  if (header->magic != MAGIC) {
    puts("magic numbers are not the same, cannot decode");
    exit(0);
  }

  // open out file
  if (file_output) {
    outfile = open(file_output, O_WRONLY | O_CREAT | O_TRUNC);
  } else {
    outfile = STDOUT_FILENO;
  }
  if (outfile < 0) {
    puts("failed open outfile");
    exit(-1);
  }

  // change the permission of the file
  fchmod(outfile, header->protection);

  // free memory allocaed for header
  free(header);
  header = NULL;

  // initialize the stat counter
  total_bits = 0;
  total_syms = 0;

  WordTable *table = wt_create();
  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;
  while (read_pair(infile, &curr_code, &curr_sym, bit_len(next_code))) {
    if (curr_code == 0) {
      // reach the end of the file, exit the loop
      break;
    }
    // save the word reads to buffer
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    buffer_word(outfile, table[next_code]);
    next_code = next_code + 1;

    // if next code reach the max value, then reset the word table
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }

  // flush any words reaming in the buffer
  flush_words(outfile);

  close(infile);
  close(outfile);

  // free memory allocated for word table
  wt_delete(table);

  if (display) {
    printf("Compressed file size: %lu bytes\n",
           total_syms + 8); // header for 8bytes
    printf("Uncompressed file size: %lu bytes\n", total_bits);
    double b = (double)(total_syms + 8) / (double)total_bits;
    printf("Compression ratio: %f%%\n", 100 * (1 - b));
  }
}

uint8_t bit_len(int code) {
  if (code == 0) {
    return 1;
  }
  uint8_t cnt = 0;
  while (code > 0) {
    code /= 2;
    cnt++;
  }
  return cnt;
}
