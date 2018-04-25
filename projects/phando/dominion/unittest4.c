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
  int i;
  int seed = 1000;
  int numPlayer = 4;
  int p, r, handpos;
  int handCount = 5;
  int coppers[MAX_HAND] = {copper, copper, copper, copper, copper};
  int playedCounter;
  int currHandCount;
  // select kingdom cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState state;
  /*
  * The discard card function removes a card from the current player's hand and either trashes it
  * or moves it to the discard pile.
  * We must test both functionalities: played pile and trashed (removed from game)
  * We must also test that it works for up to four players.
  * It must also work for all valid hand positions.
  */
  memset(&state, 23, sizeof(struct gameState));
  r = initializeGame(numPlayer, k, seed, &state);
  printf("Testing discardCard() with a full hand:\n");
  for (p = 0; p < numPlayer; p++) {
    // Fill hand with coppers
    for (i = 0; i < handCount; i++) {
      state.handCount[p] = handCount;
      memcpy(state.hand[p], coppers, sizeof(int) * handCount);
      printf("This is what's in the hand: %d\n", state.hand[p][i]);
    }
    for (handpos = handCount-1; handpos >= 0; handpos--) {
      // test sending card to played pile
      playedCounter = state.playedCardCount;
      currHandCount = state.handCount[p];
      printf("\ttesting discardCard() [TO PLAYED] player %d with hand position %d:\n", p, handpos);
      discardCard(handpos, p, &state, 0);
      printf("\t\tChecking that the card was played:\n");
      asserttrue(playedCounter + 1, state.playedCardCount); // check that card was played
      printf("\t\tChecking that the newly played card is copper:\n");
      printf("\t\t\tExpected: %d, result: %d", (int)copper, state.playedCards[playedCounter]);
      asserttrue(copper, state.playedCards[playedCounter]); // check that newly played card was copper
      printf("\t\tChecking that the card was removed from the hand:\n");
      asserttrue(currHandCount - 1, state.handCount[p]); // check that the card was removed fromt he hand

      for (i = 0; i < handCount; i++) {
        state.handCount[p] = handCount;
        memcpy(state.hand[p], coppers, sizeof(int) * handCount);
      }

      playedCounter = state.playedCardCount;
      currHandCount = state.handCount[p];
      printf("\ttesting discardCard() [TO TRASH] player %d with hand position %d:\n", p, handpos);
      discardCard(handpos, p, &state, 1);
      printf("\t\tTesting that the card was removed from the hand:\n");
      asserttrue(currHandCount - 1, state.handCount[p]); // check that card is removed from hand
      printf("\t\tTesting that the card was not played:\n");
      asserttrue(playedCounter, state.playedCardCount); // make sure card was not played
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
