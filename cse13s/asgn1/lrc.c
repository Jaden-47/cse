#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char *names[] = {"Happy",      "Sleepy",      "Sneezy", "Dopey",
                       "Bashful",    "Grumpy",      "Doc",    "Mirror Mirror",
                       "Snow White", "Wicked Queen"};

uint32_t right(uint32_t pos, uint32_t players);
uint32_t left(uint32_t pos, uint32_t players);
uint32_t get_pt();

int main(void) {
  int rand_seed;
  printf("Random seed: ");
  scanf("%d", &rand_seed);
  srand(rand_seed); // random seed set
  typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
  faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS}; // faces of die set
  int pot_coin = 0;                                      // pot coin initialize
  int coin[10] = {3, 3, 3, 3, 3,
                  3, 3, 3, 3, 3}; // coin for each player initialize
  int pos_ply = 0;                // position of players initialize
  int ply_num;
  printf("How many players? ");
  scanf("%d", &ply_num);
  int ply_rem = ply_num; // player remain
  int roll_pt;           // roll point initialize
  int i = 0;             // iteration initialize
  int cp_coin;
  while (ply_rem > 1) {
    pos_ply = pos_ply % ply_num;
    cp_coin = coin[pos_ply];
    if (cp_coin > 3) {
      cp_coin = 3;
    }
    if (coin[pos_ply] == 0) {
      ++pos_ply;
      continue;
    } else {
      printf("%s rolls... ", names[pos_ply]);
      for (i = 0; i < cp_coin; ++i) {
        roll_pt = get_pt();
        switch (die[roll_pt]) {
        case LEFT:
          if (coin[left(pos_ply, ply_num)] == 0) {
            ++ply_rem;
          }
          ++coin[left(pos_ply, ply_num)];
          --coin[pos_ply];
          if (i < cp_coin - 1) {
            printf("gives $1 to %s ", names[left(pos_ply, ply_num)]);
          } else {
            printf("gives $1 to %s", names[left(pos_ply, ply_num)]);
          }
          if (coin[pos_ply] == 0) {
            --ply_rem;
          }
          break;
        case RIGHT:
          if (coin[right(pos_ply, ply_num)] == 0) {
            ++ply_rem;
          }
          --coin[pos_ply];
          ++coin[right(pos_ply, ply_num)];
          if (i < cp_coin - 1) {
            printf("gives $1 to %s ", names[right(pos_ply, ply_num)]);
          } else {
            printf("gives $1 to %s", names[right(pos_ply, ply_num)]);
          }
          if (coin[pos_ply] == 0) {
            --ply_rem;
          }

          break;
        case CENTER:
          ++pot_coin;
          --coin[pos_ply];
          if (i < (cp_coin - 1)) {
            printf("puts $1 in the pot ");
          } else {
            printf("puts $1 in the pot");
          }

          if (coin[pos_ply] == 0) {
            --ply_rem;
          }
          break;
        case PASS:
          if (i < cp_coin - 1) {
            printf("gets a pass ");
          } else {
            printf("gets a pass");
          }
          break;
        default:
          break;
        }
      }
      printf("\n");
      ++pos_ply;
    }
  }
  int k;
  for (k = 0; k < ply_num; ++k) {
    if (coin[k] != 0) {
      pos_ply = k;
    }
  }
  printf("%s wins the $%i pot with $%i left in the bank!\n", names[pos_ply],
         pot_coin, coin[pos_ply % ply_num]);

  return 0;
}

uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
}

uint32_t right(uint32_t pos, uint32_t players) { return ((pos + 1) % players); }

uint32_t get_pt(void) {
  int a = rand();
  return (a % 6);
}
