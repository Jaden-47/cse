#include "io.h"
#include <stdio.h>

#define BLOCK 4096
#define BYTE 8

static uint8_t read_buf[BLOCK] = {0};
static int read_index = 0;

static uint8_t write_buf[BLOCK] = {0};
static int write_index = 0;

//
// Wrapper for the read() syscall.
// Loops to read the specified number of bytes, or until input is exhausted.
// Returns the number of bytes read.
//
// infile:  File descriptor of the input file to read from.
// buf:     Buffer to store read bytes into.
// to_read: Number of bytes to read.
// returns: Number of bytes read.
//
int read_bytes(int infile, uint8_t *buf, int to_read) {
  int bytes_read = 1;
  int cnt = to_read;
  int total = 0;

  while ((total != to_read) && (bytes_read != 0)) {
    bytes_read = read(infile, buf + total, cnt);
    total += bytes_read;
    cnt -= bytes_read;
  }
  return total;
}

//
// Wrapper for the write() syscall.
// Loops to write the specified number of bytes, or until nothing is written.
// Returns the number of bytes written.
//
// outfile:   File descriptor of the output file to write to.
// buf:       Buffer that stores the bytes to write out.
// to_write:  Number of bytes to write.
// returns:   Number of bytes written.
//
int write_bytes(int outfile, uint8_t *buf, int to_write) {
  int bytes_write = 1;
  int cnt = to_write;
  int total = 0;
  while ((total != to_write) && (bytes_write != 0)) {
    bytes_write = write(outfile, buf + total, cnt);
    total += bytes_write;
    cnt -= bytes_write;
  }
  return total;
}

//
// Reads in a FileHeader from the input file.
//
// infile:  File descriptor of input file to read header from.
// header:  Pointer to memory where the bytes of the read header should go.
// returns: Void.
//
void read_header(int infile, FileHeader *header) {
  read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
}

//
// Writes a FileHeader to the output file.
//
// outfile: File descriptor of output file to write header to.
// header:  Pointer to the header to write out.
// returns: Void.
//
void write_header(int outfile, FileHeader *header) {
  write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader));
}

//
// "Reads" a symbol from the input file.
// The "read" symbol is placed into the pointer to sym (pass by reference).
// In reality, a block of symbols is read into a buffer.
// An index keeps track of the currently read symbol in the buffer.
// Once all symbols are processed, another block is read.
// If less than a block is read, the end of the buffer is updated.
// Returns true if there are symbols to be read, false otherwise.
//
// infile:  File descriptor of input file to read symbols from.
// sym:     Pointer to memory which stores the read symbol.
// returns: True if there are symbols to be read, false otherwise.
//
bool read_sym(int infile, uint8_t *byte) {
  // mostly inpired in TA section
  static bool check;
  static int temp = 0;
  if (read_index == 0) {
    int num_bytes_read = read_bytes(infile, read_buf, BLOCK);
    total_syms += num_bytes_read; // stat counter
    if (num_bytes_read == BLOCK) {
      check = true;
    } else {
      temp = num_bytes_read;
      check = false;
    }
  }
  *byte = read_buf[read_index];
  read_index = (read_index + 1) % BLOCK;
  // return either successfully read 4096 bytes or didn't reach the end of the
  // file
  return check || (read_index != temp + 1);
}

//
// Buffers a pair. A pair is comprised of a symbol and an index.
// The bits of the symbol are buffered first, starting from the LSB.
// The bits of the index are buffered next, also starting from the LSB.
// bit_len bits of the index are buffered to provide a minimal representation.
// The buffer is written out whenever it is filled.
//
// outfile: File descriptor of the output file to write to.
// sym:     Symbol of the pair to buffer.
// index:   Index of the pair to buffer.
// bit_len: Number of bits of the index to buffer.
// returns: Void.
//
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bit_len) {
  int index = 0, bit = 0, code_len = 0;

  // get the code length
  uint16_t code_cp = code;
  if (code == 0) {
    code_len = 1;
  }
  while (code_cp > 0) {
    code_cp /= 2;
    code_len++;
  }

  // buffer the code
  for (int i = 0; i < bit_len; i++) {
    if (i < code_len) {
      // copy the code to buffer from LSB to MSB
      index = write_index / 8;
      bit = code & (1 << i);
      // if the bit is 1 then pass 1, 0 pass 0
      if (bit) {
        write_buf[index] |= (1 << (write_index % 8));
      } else {
        write_buf[index] &= ~(1 << (write_index % 8));
      }
    }

    //  padding zeors
    if (i >= code_len) {
      index = write_index / 8;
      write_buf[index] &= ~(1 << (write_index % 8));
    }
    write_index++;

    total_bits++; // stat counter increment

    if (write_index / 8 == BLOCK) {
      write_bytes(outfile, write_buf, BLOCK);
      write_index = 0;
    }
  }

  // buffer the sym
  for (int i = 0; i < 8; i++) {
    index = write_index / 8;
    bit = sym & (1 << (i % 8));

    // copy from LSB to MSB
    if (bit) {
      write_buf[index] |= (1 << (write_index % 8));
    } else {
      write_buf[index] &= ~(1 << (write_index % 8));
    }

    write_index++;

    total_bits++; // stat counter increment

    if (write_index / 8 == BLOCK) {
      write_bytes(outfile, write_buf, BLOCK);
      write_index = 0;
    }
  }
}

//
// Writes out any remaining pairs of symbols and indexes to the output file.
//
// outfile: File descriptor of the output file to write to.
// returns: Void.
//
void flush_pairs(int outfile) {
  int use_bytes = 0;

  // determine the write index is a integer byte
  if (write_index / 8 == 0) {
    use_bytes = write_index / 8;
  } else {
    use_bytes = write_index / 8 + 1;
  }

  if (write_index != 0) {
    write_bytes(outfile, write_buf, use_bytes);
  }
  write_index = 0;
}

//
// "Reads" a pair (symbol and index) from the input file.
// The "read" symbol is placed in the pointer to sym (pass by reference).
// The "read" index is placed in the pointer to index (pass by reference).
// In reality, a block of pairs is read into a buffer.
// An index keeps track of the current bit in the buffer.
// Once all bits have been processed, another block is read.
// The first 8 bits of the pair constitute the symbol, starting from the LSB.
// The next bit_len bits constitutes the index, starting from the the LSB.
// Returns true if there are pairs left to read in the buffer, else false.
// There are pairs left to read if the read index is not STOP_INDEX.
//
// infile:  File descriptor of the input file to read from.
// sym:     Pointer to memory which stores the read symbol.
// index:   Pointer to memory which stores the read index.
// bit_len: Length in bits of the index to read.
// returns: True if there are pairs left to read, false otherwise.
//
bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bit_len) {
  int index = 0, bit = 0;
  *code = 0, *sym = 0;

  // read the code
  for (int i = 0; i < bit_len; i++) {
    if (read_index == 0) {
      for (int j = 0; j < BLOCK; j++) {
        read_buf[j] = 0;
      }
      int num_bytes_read = read_bytes(infile, read_buf, BLOCK);
      total_syms += num_bytes_read; // stat counter increment
    }
    // bit manipulation for read code
    index = read_index / 8;
    bit = read_buf[index] & (1 << (read_index % 8));
    if (bit) {
      *code |= 1 << i;
    }
    read_index++;

    // clear the read_buf if it is full
    if (read_index / 8 == BLOCK) {
      for (int i = 0; i < BLOCK; i++) {
        read_buf[i] = 0;
      }
      read_index = 0;
    }
  }

  // read the sym
  for (int i = 0; i < 8; i++) {
    if (read_index == 0) {
      for (int j = 0; j < BLOCK; j++) {
        read_buf[j] = 0;
      }
      int num_bytes_read = read_bytes(infile, read_buf, 4096);
      total_syms += num_bytes_read;
    }
    // bit manipulation for read symbol
    index = read_index / 8;
    bit = read_buf[index] & (1 << (read_index % 8));
    if (bit) {
      *sym |= 1 << i;
    }
    read_index++;

    // clear the read_buf if it's full
    if (read_index / 8 == BLOCK) {
      for (int j = 0; j < BLOCK; j++) {
        read_buf[j] = 0;
      }
      read_index = 0;
    }
  }

  // return if read the stop code, which is zero
  if (*code == 0) {
    return false;
  } else {
    return true;
  }
}

//
// Buffers a Word, or more specifically, the symbols of a Word.
// Each symbol of the Word is placed into a buffer.
// The buffer is written out when it is filled.
//
// outfile: File descriptor of the output file to write to.
// w:       Word to buffer.
// returns: Void.
//
void buffer_word(int outfile, Word *w) {
  for (uint32_t i = 0; i < w->len; i++) {
    write_buf[write_index] = w->syms[i]; // copy the value to word struct
    write_index++;
    total_bits++; // stat counter increment
                  // write out if the write_buffer is full
    if (write_index == BLOCK) {
      write_bytes(outfile, write_buf, BLOCK);
      write_index = 0;
    }
  }
}

//
// Writes out any remaining symbols in the buffer.
//
// outfile: File descriptor of the output file to write to.
// returns: Void.
//
void flush_words(int outfile) {
  if (write_index != 0) {
    write_bytes(outfile, write_buf, write_index);
    // reset the write buffer
    for (int i = 0; i < write_index; i++) {
      write_buf[i] = 0;
    }
    write_index = 0;
  }
}
