// Dominic Phan
// testing smithy

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
    printf("\t\t\t***Assert Passed***\n\n");
  }
  else
  {
    totalFail++;
    printf("\t\t\t***Assert failed, total fails***: %d\n\n", totalFail);
  }
}
int main()
{
  int handPos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int* bonus = NULL;
  int seed = 1000;
  int numPlayer = 4;
  int p, r;
  int currHandCount;
  int playedCounter;
  // select kingdom cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState state;
  

  /*
  * The smithy kingdom card is supposed to draw three cards. This means that +3 are added to the current player's
  * hand. This also means that the smithy card must be removed from the current player's hand. We will test both
  * of these functionalities.
  */
  memset(&state, 23, sizeof(struct gameState));
  r = initializeGame(numPlayer, k, seed, &state);
  printf("Testing the smithy card:\n");
  // Test smithy for each player. 
  for (p = 0; p < numPlayer; p++) {
    state.hand[p][handPos] = smithy;
    currHandCount = state.handCount[p];
    printf("\tTesting for PLAYER %d:\n", p);
    currHandCount = state.handCount[p];
    playedCounter = state.playedCardCount;
    printf("playedCounter = %d\n", playedCounter);
    cardEffect(smithy, choice1, choice2, choice3, &state, handPos, bonus);
    // Check that the cards were added to the hand
    printf("\t\tChecking that three cards were added to the hand and smithy was removed:\n");
    printf("\t\t\tExpected: %d, result: %d\n", currHandCount + 2, state.handCount[p]);
    asserttrue(state.handCount[p], currHandCount + 2);
    // Check the played pile for smithy
    printf("\t\tChecking that smithy was added to the played pile:\n");
    printf("\t\t\tExpected: %d, result: %d\n", smithy, state.playedCards[playedCounter]);
    asserttrue(state.playedCards[playedCounter], smithy);
    endTurn(&state);
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
