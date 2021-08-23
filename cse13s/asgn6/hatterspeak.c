#include "bf.h"
#include "hash.h"
#include "ll.h"
#include "parser.h"
#include "speck.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "sh::f::mb"
// seeks: number of seeks performed
int seeks = 0;
// avg_seek_len: links searched/total seeks
// avg_ll_len: average length of non-zero linked lists in hash table
// ht_load: percentage of loading for the hash table
// bf_load: percentage of loading for the bloom table
double avg_seek_len = 0, avg_ll_len = 0, ht_load = 0, bf_load = 0;

double nodes_travel = 0, sum_ll_nodes = 0;
bool move_to_front = false;
uint32_t print_stat = 0, ht_size = 10000, bf_size = 0x100000;
char ans1[10000000][50], ans2[2][10000000][50];
int _ans[2];
void cp(char a[], char b[]) {
  int len = strlen(b);
  for (int i = 0; i < len; ++i)
    a[i] = b[i];
  a[len] = 0;
}
int main(int argc, char **argv) {
  // read command argument
  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 's':
      print_stat = 1;
      break;
    case 'h':
      ht_size = atoi(argv[optind]);
      break;
    case 'f':
      bf_size = atoi(argv[optind]);
      break;
    case 'm':
      move_to_front = true;
      break;
    case 'b':
      move_to_front = false;
      break;
    default:
      printf("invalid argument");
      break;
    }
  }

  // create bloom filter and hash table
  BloomFilter bf = *bf_create(bf_size);
  HashTable ht = *ht_create(ht_size);

  // create file for oldspeak.txt and hatterspeak.txt
  FILE *in1 = fopen("oldspeak.txt", "r");
  FILE *in2 = fopen("hatterspeak.txt", "r");
  // create string for store the word
  char s[100], s2[100];

  while (fscanf(in2, "%s%s", s, s2) != -1) {
    // insert in bloom filter
    bf_insert(&bf, s);
    // save words in ls->oldspeak and ls->hatterspeak
    HatterSpeak *ls = malloc(sizeof(HatterSpeak));
    if (!ls) {
      printf("fail malloc ls");
      return -1;
    }
    ls->oldspeak = malloc(100);
    if (ls->oldspeak == NULL) {
      printf("fail malloc ls->oldspeak");
      return -1;
    }
    cp(ls->oldspeak, s);
    ls->hatterspeak = malloc(100);
    if (ls->hatterspeak == NULL) {
      printf("fail malloc ls->hatterspeak");
      return -1;
    }
    cp(ls->hatterspeak, s2);

    // insert to hash table
    ht_insert(&ht, ls);
  }
  while (fscanf(in1, "%s", s) != -1) {

    // find if it is in the hash table
    if (ht_lookup(&ht, s))
      continue;

    // insert to bloom filter
    bf_insert(&bf, s);

    // save word to ls->oldspeak and set ls->hatterspeak to NULL
    HatterSpeak *ls = malloc(sizeof(HatterSpeak));
    ls->oldspeak = malloc(100);
    cp(ls->oldspeak, s);
    ls->hatterspeak = 0;

    // insert to hash table
    ht_insert(&ht, ls);
  }

  // regex
  char *pattern =
      "[a-zA-Z0-9_]+(_?[a-zA-Z0-9_]+)*('?[a-zA-Z0-9_]+)*(-?[a-zA-Z0-9_]+)*";
  // compile regex
  regex_t *regex_comped = (regex_t *)malloc(sizeof(regex_t));
  regcomp(regex_comped, pattern, REG_EXTENDED | REG_ICASE);
  char *lss = NULL; // save the word get from regex

  while ((lss = next_word(stdin, regex_comped))) {
    for (int i = 0; i < (int)strlen(lss); ++i)
      s[i] = lss[i];
    s[strlen(lss)] = 0;

    // if it is not in the bloom filter then skip (safeword)
    if (!bf_probe(&bf, s))
      continue;
    ListNode *ls = ht_lookup(&ht, s);
    // find the ls->oldspeak and ls->hatterspeak and save them to string array
    if (!ls)
      continue;
    if (!ls->gs->hatterspeak)
      cp(ans1[++_ans[0]], ls->gs->oldspeak);
    else {
      cp(ans2[0][++_ans[1]], ls->gs->oldspeak),
          cp(ans2[1][_ans[1]], ls->gs->hatterspeak);
    }
  }
  // print stat of the function
  if (print_stat) {
    // avg_seek_len
    avg_seek_len = nodes_travel / seeks;

    // avg_ll_len
    for (uint32_t i = 0; i < ht.length; i++) {
      ListNode *count = ht.heads[i];
      while (count) {
        sum_ll_nodes++;
        count = count->next;
      }
    }
    avg_ll_len = sum_ll_nodes / ht.length;

    // ht_load
    ht_load = ht_count(&ht);
    ht_load = ht_load * 100 / ht.length;

    // bf_load
    for (uint32_t i = 0; i < bf.filter->length; i++) {
      if (bv_get_bit(bf.filter, i)) {
        bf_load += 1;
      }
    }
    bf_load = bf_load * 100 / bf_size;
    printf("* Seeks: %d\n", seeks);
    printf("* Average seek length: %f\n", avg_seek_len);
    printf("* Average Linked List Length: %f\n", avg_ll_len);
    printf("* Hash table load: %f%%\n", ht_load);
    printf("* Bloom filter load: %f%%\n", bf_load);
    return 0;
  }
  // both error and translation
  if (_ans[1] && _ans[0]) {
    puts("Dear Comrade,\n");
    puts("You have chosen to use words that the queen has decreed oldspeak");
    puts("Due to your infraction you will be sent to the dungeon where you "
         "will be taught hatterspeak\n");
    puts("Your errors:\n");
    for (int i = 1; i <= _ans[0]; ++i) {
      printf("%s\n", ans1[i]);
    }
    puts("\nAppropriate hatterspeak translations.\n");
    for (int i = 1; i <= _ans[1]; ++i) {
      printf("%s -> %s\n", ans2[0][i], ans2[1][i]);
    }
    return 0;
  }

  // error
  if (_ans[0]) {
    puts("Dear Wonderlander,\n");
    puts("You have chosen to use words that the queen has decreed oldspeak.");
    puts("Due to your infraction you will be sent to the dungeon where you "
         "will be taught hatterspeak.\n");
    puts("Your errors:\n");
    for (int i = 1; i <= _ans[0]; ++i) {
      printf("%s\n", ans1[i]);
    }
  }

  // translation
  if (_ans[1]) {
    puts("Dear Wonderlander,\n");
    puts("The decree for hatterspeak finds your message lacking. Some of the "
         "words that you used are not hatterspeak.");
    puts("The list shows how to turn the oldspeak words into hatterspeak\n");
    for (int i = 1; i <= _ans[1]; ++i) {
      printf("%s -> %s\n", ans2[0][i], ans2[1][i]);
    }
  }
}
