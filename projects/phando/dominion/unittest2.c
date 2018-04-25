// Dominic Phan
// Testing handCard

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
      printf("Assert Passed\n");
  }
  else
  {
      printf("Assert failed, total fails: %d\n", totalFail);
      totalFail++;
  }
}

int main()
{
  int i;
  int seed = 1000;
  int numPlayer = 2;
  int p, r, handCount;
  p = 0;
  int testCard;
  // select kingdom cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
  struct gameState state;
  int testHand[MAX_HAND] = {adventurer, copper, silver, gold, great_hall};
  handCount = 5;

  /* Testing code goes here*/

  /*
  * The handCard() function returns a card at a certain position from the current player's hand.
  * To test this, simply add 5 unique cards to the hand and verify that the cards are in the right 
  * position.
  * Doesn't need to be tested for invalid inputs (out of range) because it's only used to discard / get
  * the card that will be played, so handPos will always be valid.
  */
  memset(&state, 23, sizeof(struct gameState));
  r = initializeGame(numPlayer, k, seed, &state);
  state.handCount[0] = handCount;
  memcpy(state.hand[0], testHand, sizeof(int) * handCount);
  printf("Testing handCard()\n");
  for (i = 0; i < 5; i++) {
    testCard = handCard(i, &state);
    printf("Comparing result: %d to expected: %d\n", testCard, testHand[i]);
    asserttrue(testCard, testHand[i]);
  }
 
  if (totalFail == 0) {
    printf("FINAL RESULT: All tests passed\n");
  }
  else {
    printf("FINAL RESULT: %d FAILURES\n", totalFail);
  }
  return 0;

}
