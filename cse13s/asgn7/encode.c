#include "code.h"
#include "io.h"
#include "trie.h"
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

// open file for infile and outfile
int infile, outfile;

// stat count
uint64_t total_syms = 0, total_bits = 0;

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

  // get the file header info
  struct stat file_stat;
  fstat(infile, &file_stat);
  FileHeader *header = (FileHeader *)calloc(1, sizeof(FileHeader));
  if (!header) {
    puts("failed calloc header in encode.c");
    exit(-1);
  }
  header->magic = MAGIC;
  header->protection = file_stat.st_mode;

  // open outfile
  if (file_output) {
    outfile = open(file_output, O_WRONLY | O_CREAT | O_TRUNC);
  } else {
    outfile = STDOUT_FILENO;
  }
  if (outfile < 0) {
    puts("failed open outfile");
    exit(-1);
  }

  // write header
  write_header(outfile, header);
  free(header);
  header = NULL;

  // initialize the counter for stat
  total_bits = 0;
  total_syms = 0;

  // initialize the trie
  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;
  TrieNode *next_node = NULL;

  // variable to catch previous and current symbol
  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;

  while (read_sym(infile, &curr_sym)) {
    next_node = trie_step(curr_node, curr_sym);
    if (next_node != NULL) {
      // if next_node exit means it is exited in trie already, then find the
      // last symbol in the trie
      prev_node = curr_node;
      curr_node = next_node;
    } else {
      // store the symbol and code into trie and write_buffer
      buffer_pair(outfile, curr_node->code, curr_sym, bit_len(next_code));
      curr_node->children[curr_sym] = trie_node_create(next_code);
      curr_node = root;
      next_code = next_code + 1;
    }
    if (next_code == MAX_CODE) {
      // if trie is full, reset the trie to all zero
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }
    // store the symbol if it reaches the end of the file
    prev_sym = curr_sym;
  }

  // it means it reach the end of the file, save the last one
  if (curr_node != root) {
    buffer_pair(outfile, prev_node->code, prev_sym, bit_len(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }
  // write the stop code and zeros symbol to the buffer
  buffer_pair(outfile, STOP_CODE, 0, bit_len(next_code));

  // flush any symbols and codes remaining to the outfiel
  flush_pairs(outfile);

  // free memory allocated to the tree
  trie_delete(root);

  if (display) {
    int a;
    if (total_bits % 8 == 0) {
      a = total_bits / 8;
    } else {
      a = total_bits / 8 + 1;
      // it may not integer byte
    }
    a += 8; // header size of 8 bytes;
    printf("Compressed file size: %d bytes\n", a);
    printf("Uncompressed file size: %lu bytes\n", total_syms);
    double b = (double)a / (double)total_syms;
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
