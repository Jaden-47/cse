// sequence.c print out each kind of prime by commoand line
//

#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "spn::"

// check the value if it is fibonacci
//
int isfibo(int m);

// generate the nth fibonacci number
//
int fibonacci(int n);

// generate the nth lucas number
//
int lucas(int m);

// check the value if it is a lucas number
//
int islucas(int n);

// check the value if it is a mersenne number
//
int ismersenne(int p);

// Decimal to binary
//
char *d_to_b(int n);
char base2[32];
int u = 0;

// Decimal to base 9
//
char *d_to_9(int n);
char base9[32];
int v = 0;

// Decimal to base 22
//
char *d_to_22(int n);
char base22[32];
int w = 0;

// determine whethe the number is palindrome
//
int ispalin(char *str);

// these two decide which to print out
int option_s = 0;
int option_p = 0;

// store the value of the largest value to consider
// which is 1000 as default
int l_val = 1000;

int main(int argc, char **argv) {
  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    // get the command from the command line
    switch (c) {
    case 's':
      // print out all the primes and whether they are interesting
      option_s = 1;
      break;
    case 'p':
      option_p = 1;
      break;
    case 'n':
      l_val = atoi(argv[optind]);
      break;
    default:
      break;
    }
  }

  if (option_s) {
    // print out all primes and whether they are interesting
    BitVector *prime_list = bv_create(l_val);
    sieve(prime_list);
    for (int i = 0; i < l_val; i++) {
      // print out as the sequence
      // prime -> mersenne-> lucas -> fibonacci
      if (bv_get_bit(prime_list, i)) {
        if (isfibo(i)) {
          if (islucas(i)) {
            if (ismersenne(i)) {
              printf("%d: prime, mersenne, lucas, fibonacci\n", i);
            } else {
              printf("%d: prime, lucas, fibonacci\n", i);
            }
          } else {
            if (ismersenne(i)) {
              printf("%d: prime, mersenne, fibonacci\n", i);
            } else {
              printf("%d: prime, fibonacci\n", i);
            }
          }
        } else {
          if (islucas(i)) {
            if (ismersenne(i)) {
              printf("%d: prime, mersenne, lucas\n", i);
            } else {
              printf("%d: prime, lucas\n", i);
            }
          } else {
            if (ismersenne(i)) {
              printf("%d: prime, mersenne\n", i);
            } else {
              printf("%d: prime\n", i);
            }
          }
        }
      }
    }
    bv_delete(prime_list);
  }

  if (option_p) {
    // print out palindromic primes in bases 2,9,10
    // and first letter of my last name +10 which is 22
    BitVector *prime_list = bv_create(l_val);
    sieve(prime_list);
    // print out as the sequence
    // base 2 -> base 9 -> base 10 -> base 22 ->
    printf("Base  2\n");
    printf("---- --\n");
    for (int i = 0; i < l_val; i++) {
      if (bv_get_bit(prime_list, i)) {
        u = 0;
        if (ispalin(d_to_b(i))) {
          u = 0;
          printf("%d = %s\n", i, d_to_b(i));
        }
      }
    }

    printf("\n");

    printf("Base  9\n");
    printf("---- --\n");
    for (int i = 0; i < l_val; i++) {
      if (bv_get_bit(prime_list, i)) {
        v = 0;
        if (ispalin(d_to_9(i))) {
          v = 0;
          printf("%d = %s\n", i, d_to_9(i));
        }
      }
    }

    printf("\n");

    printf("Base 10\n");
    printf("---- --\n");
    int x = 0, y = 0;
    for (int i = 0; i < l_val; i++) {
      if (bv_get_bit(prime_list, i)) {
        x = i;
        y = 0;
        while (x > 0) {
          y = y * 10 + x % 10;
          x = x / 10;
        }
        if (y == i) {
          printf("%d = %d\n", i, y);
        }
      }
    }

    printf("\n");

    printf("Base 22\n");
    printf("---- --\n");
    for (int i = 0; i < l_val; i++) {
      if (bv_get_bit(prime_list, i)) {
        w = 0;
        if (ispalin(d_to_22(i))) {
          w = 0;
          printf("%d = %s\n", i, d_to_22(i));
        }
      }
    }
    bv_delete(prime_list);
  }

  return 0;
}

int fibonacci(int n) {
  // generate the nth fibonacci number
  //
  if (n == 1) {
    return 0;
  }
  if (n == 2) {
    return 1;
  }
  if (n > 2) {
    return fibonacci(n - 1) + fibonacci(n - 2);
  }
  return 0;
}

int isfibo(int m) {
  // deternmine whether m is fibonacci number
  for (int i = 0; fibonacci(i) < m; i++) {
    if (fibonacci(i + 1) == m) {
      return 1;
    }
  }
  return 0;
}

int lucas(int n) {
  // generate the nth lucas number
  if (n == 1) {
    return 2;
  }
  if (n == 2) {
    return 1;
  }
  if (n > 2) {
    return lucas(n - 1) + lucas(n - 2);
  }
  return 0;
}

int islucas(int m) {
  // deternmine whetehr m is lucas number
  //
  if (m == 1 || m == 2) {
    return 1;
  }
  for (int i = 2; lucas(i) < m; i++) {
    if (lucas(i + 1) == m) {
      return 1;
    }
  }
  return 0;
}

int ismersenne(int p) {
  // determine whether p is merseene number
  //
  if (p == 2) {
    return 0;
  }
  if (p % 2 == 1) {
    p += 1;
  }

  while (p > 1 && (p % 2 == 0)) {
    p /= 2;
  }
  if (p == 1) {
    return 1;
  }
  return 0;
}

char *d_to_b(int n) {
  // convert n from decimal to string binary
  //
  if (n < 2) {
    base2[u] = n + '0';
  } else {
    d_to_b(n / 2);
    u++;
    n %= 2;
    base2[u] = n + '0';
  }
  return base2;
}

char *d_to_9(int n) {
  // convert decimal n to base 9 string
  //
  if (n < 9) {
    base9[v] = n + '0';
  } else {
    d_to_9(n / 9);
    v++;
    n %= 9;
    base9[v] = n + '0';
  }
  return base9;
}

char *d_to_22(int n) {
  // conver deciaml n to base 22 string
  if (n < 22) {
    if (n < 10) {
      base22[w] = n + '0';
    } else {
      base22[w] = n + 'a' - 10;
    }

  } else {
    d_to_22(n / 22);
    w++;
    n %= 22;
    if (n < 10) {
      base22[w] = n + '0';
    } else {
      base22[w] = n - 10 + 'a';
    }
  }
  return base22;
}

int ispalin(char *str) {
  // determine whether a sting is palindrome
  //
  int i, j, n;
  n = strlen(str);
  for (i = 0, j = n - 1; i < j; i++, j--) {
    if (str[i] != str[j]) {
      return 0;
    }
  }
  return 1;
}
