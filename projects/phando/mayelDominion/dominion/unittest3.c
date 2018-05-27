// Dominic phan
// gainCard() unit test

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
    totalFail++;
    printf("\t\t\tAssert failed, total fails: %d\n", totalFail);
  }
}

int main()
{
  int seed = 1000;
  int numPlayer = 4;
  int p, r, handCount;
  int successFlag;
  int initialCount;
  int supplyCounter;
  // select kingdom cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState state;
  handCount = 5;

  /* Testing code goes here*/

  /*
  * gainCard uses supplyPos, state, toFlag, and player
  * We must test gainCard with multiple players
  * gainCard takes a card from the supply pile and adds it to the discard pile
  * We must check that supply from supplypos is decremented and the player's discard pile
  * is incremented.
  */
  for (p = 0; p < numPlayer; p++) {
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &state);
    // Check discard pile and check that it was removed from supply
    printf("Testing gainCard() to discard pile:\n");
    initialCount = state.discardCount[p];
    supplyCounter = supplyCount(feast, &state);
    successFlag = gainCard(feast, &state, 0, p);
    printf("\tThis indicates that the function returned a correct value for success:\n");
    asserttrue(successFlag, 0);
    printf("\tThis indicates that the supply card was found in the discard pile:\n");
    printf("\t\tExpected: %d, result: %d\n", feast, state.discard[p][initialCount]);
    asserttrue(state.discard[p][initialCount], feast);
    printf("\tThis indicates that the supply count has decremented meaning a card has been taken out:\n");
    printf("\t\tExpected: %d, result: %d\n", supplyCounter-1, supplyCount(feast, &state));
    asserttrue(supplyCount(feast, &state), supplyCounter - 1);

    // Check deck and check that it was removed from supply
    printf("Testing gainCard() to deck pile:\n");
    initialCount = state.deckCount[p];
    supplyCounter = supplyCount(gardens, &state);
    successFlag = gainCard(gardens, &state, 1, p);
    printf("\tThis indicates that the function returned a correct value for success:\n");
    asserttrue(successFlag, 0);
    printf("\tThis indicates that the supply card was found in the deck pile:\n");
    printf("\t\tExpected: %d, result: %d\n", gardens, state.deck[p][initialCount]);
    asserttrue(state.deck[p][initialCount], gardens);
    printf("\tThis indicates that the supply count has decremented meaning a card has been taken out:\n");
    printf("\t\tExpected: %d, result: %d\n", supplyCounter - 1, supplyCount(gardens, &state));
    asserttrue(supplyCount(gardens, &state), supplyCounter - 1);

    // Check hand and check that it was removed from supply
    printf("Testing gainCard() to hand:\n");
    initialCount = state.handCount[p];
    supplyCounter = supplyCount(baron, &state);
    successFlag = gainCard(baron, &state, 2, p);
    printf("\tThis indicates that the function returned a correct value for success:\n");
    asserttrue(successFlag, 0);
    printf("\tThis indicates that the supply card was found in the hand:\n");
    printf("\t\tExpected: %d, result: %d\n", baron, state.hand[p][initialCount]);
    asserttrue(state.hand[p][initialCount], baron);
    printf("\tThis indicates that the supply count has decremented meaning a card has been taken out:\n");
    printf("\t\tExpected: %d, result: %d\n", supplyCounter - 1, supplyCount(baron, &state));
    asserttrue(supplyCount(baron, &state), supplyCounter - 1);

    // Check what happens during invalid value (supply is out or name is wrong)
    successFlag = gainCard(-1000, &state, 0, p);
    printf("\tThis indicates that the function handled an error situation *invalid value*:\n");
    asserttrue(successFlag, -1); // testing invalid value
    state.supplyCount[baron] = 0;
    successFlag = gainCard(baron, &state, 0, p);
    printf("\tThis indicates that the function handled and error situation *empty supply pile*:\n");
    asserttrue(successFlag, -1); // testing a supply pile that should be empty.
  }



  if (totalFail == 0)
  {
    printf("FINAL RESULT: All tests passed\n");
  }
  else
  {
    printf("FINAL RESULT: %d FAILURES\n", totalFail);
  }
  return 0;
}
