// Dominic Phan
// Testing fullDeckCount()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void asserttrue(int booleanStatement) {
  if (booleanStatement) {
    printf("Assert Passed\n");
  } else {
    printf("Assert failed\n");
  }
}

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main(){
  int i;
  int seed = 1000;
  int numPlayer = 2;
  int p, r, handCount;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState G;
  int maxHandCount = 5;
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];

  for (i = 0; i < MAX_HAND; i++) {
    coppers[i] = copper;
    silvers[i] = silver;
    golds[i] = gold;
  }
  printf("TESTING fullDeckCount():\n");
  for (p = 0; p < numPlayer; p++){
    memset(&G, 23, sizeof(struct gameState)); // clear game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize new game
    handCount = maxHandCount;
    G.handCount[p] = handCount;
    memcpy(G.hand[p], coppers, sizeof(int) * handCount); // setting all cards to copper
    fullDeckCount(p, 4);

  }

}
