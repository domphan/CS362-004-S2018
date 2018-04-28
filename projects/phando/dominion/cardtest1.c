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
  int i, j;
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
  struct gameState otherPlayersState;
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
    // Store other player's gamestate to test if they are mutated.
    memcpy(otherPlayersState.hand, state.hand, sizeof(int) * MAX_HAND * MAX_PLAYERS);
    memcpy(otherPlayersState.deck, state.deck, sizeof(int) * MAX_DECK * MAX_PLAYERS);
    memcpy(otherPlayersState.discard, state.discard, sizeof(int) * MAX_DECK * MAX_PLAYERS);
    for (i = 0; i < numPlayer; i++) {
      otherPlayersState.handCount[i] = state.handCount[i];
      otherPlayersState.deckCount[i] = state.deckCount[i];
      otherPlayersState.discardCount[i] = state.discardCount[i];
    }
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
    // Check that other player's states were not mutated
    printf("\t\tChecking that other player's states were not mutated:\n");
    for (i = 0; i < numPlayer; i++) {
      if (i != p) {
        printf("\t\t\tChecking player %d's hand:\n", i);
        for (j = 0; j < otherPlayersState.handCount[i]; j++) {
          printf("\t\t\tExpected: %d, result: %d\n", otherPlayersState.hand[i][j], state.hand[i][j]);
          asserttrue(state.hand[i][j], otherPlayersState.hand[i][j]);
        }
        printf("\t\t\tChecking player %d's deck:\n", i);
        for (j = 0; j < otherPlayersState.deckCount[i]; j++) {
          printf("\t\t\tExpected: %d, result: %d\n", otherPlayersState.deck[i][j], state.deck[i][j]);
          asserttrue(otherPlayersState.deck[i][j], state.deck[i][j]);
        }
        printf("\t\t\tChecking player %d's discard:\n", i);
        for (j = 0; j < otherPlayersState.discardCount[i]; j++) {
          printf("\t\t\tExpected: %d, Result: %d\n", otherPlayersState.discard[i][j], state.discard[i][j]);
          asserttrue(otherPlayersState.discard[i][j], state.discard[i][j]);
        }
      }
    }
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
