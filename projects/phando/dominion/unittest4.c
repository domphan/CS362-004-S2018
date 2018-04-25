// Dominic Phan
// testing discardCard() function

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
int totalFail = 0;
void asserttrue(int a, int b)
{
  if (a == b)
  {
    printf("\t\t\tAssert Passed\n");
  }
  else
  {
    printf("\t\t\tAssert failed, total fails: %d\n", totalFail);
    totalFail++;
  }
}
int main()
{
  int i;
  int seed = 1000;
  int numPlayer = 4;
  int p, r, handpos;
  int handCount = 5;
  int coppers[MAX_HAND];
  int discardCounter;
  int currHandCount;
  // select kingdom cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState state;

  /*
  * The discard card function removes a card from the current player's hand and either trashes it
  * or moves it to the discard pile.
  * We must test both functionalities: discard pile and trashed (removed from game)
  * We must also test that it works for up to four players.
  * It must also work for all valid hand positions.
  */
  memset(&state, 23, sizeof(struct gameState));
  r = initializeGame(numPlayer, k, seed, &state);
  printf("Testing discardCard():\n");
  for (p = 0; p < numPlayer; p++) {
    // Fill hand with coppers
    for (i = 0; i < handCount; i++) {
      state.handCount[p] = handCount;
      memcpy(state.hand[p], coppers, sizeof(int) * handCount);
    }
    for (handpos = 0; handpos < handCount; handpos++) {
      // test sending card to discard pile
      discardCounter = state.discardCount[p];
      currHandCount = state.handCount;
      discardCard(handpos, p, &state, 0);

      // test sending card to trash pile
      discardCard(handpos, p, &state, 1);

    }
  }
  if (totalFail == 0) {
    printf("FINAL RESULT: All tests passed\n");
  }
  else {
    printf("FINAL RESULT: %d FAILURES\n", totalFail);
  }
  return 0;
}
