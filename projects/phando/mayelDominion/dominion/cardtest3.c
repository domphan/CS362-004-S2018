// Dominic Phan
// testing village

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
  int p = 0;
  int handPos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int *bonus = NULL;
  int seed = 1000;
  int numPlayer = 4;
  int r;
  int currHandCount;
  int playedCounter;
  int actionCounter;
  int discardTestPile[MAX_DECK] = {copper, copper, copper, copper, copper,
                                   copper, copper, copper, copper, copper};

  // select kingdom cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState state;
  struct gameState otherPlayersState;
  /*
  * The village kingdom card allows the player to draw one card from the deck and gain two 
  * actions.
  * Precondition: valid gamestate
  * post condition: two actions added and one card added to hand. village should be added to 
  *                 played pile.
  */
  memset(&state, 23, sizeof(struct gameState));
  r = initializeGame(numPlayer, k, seed, &state);
  printf("Testing the village card:\n");

  memcpy(otherPlayersState.hand, state.hand, sizeof(int) * MAX_HAND * MAX_PLAYERS);
  memcpy(otherPlayersState.deck, state.deck, sizeof(int) * MAX_DECK * MAX_PLAYERS);
  memcpy(otherPlayersState.discard, state.discard, sizeof(int) * MAX_DECK * MAX_PLAYERS);
  for (i = 0; i < numPlayer; i++)
  {
    otherPlayersState.handCount[i] = state.handCount[i];
    otherPlayersState.deckCount[i] = state.deckCount[i];
    otherPlayersState.discardCount[i] = state.discardCount[i];
  }

  // Testing with a regular deck
  state.hand[0][0] = village;
  currHandCount = state.handCount[0];
  actionCounter = state.numActions;
  playedCounter = state.playedCardCount;
  cardEffect(village, choice1, choice2, choice3, &state, handPos, bonus);
  printf("\tChecking with a regular deck:\n");
  printf("\t\tChecking that a card was drawn and added to the hand:\n");
  printf("\t\t\tExpected: %d result: %d:\n", currHandCount, state.handCount[0]);
  asserttrue(currHandCount, state.handCount[0]);
  printf("\t\tChecking that two actions were added:\n");
  printf("\t\t\tExpected: %d, result: %d\n", actionCounter + 2, state.numActions);
  asserttrue(actionCounter + 2, state.numActions);
  printf("\t\tChecking that village was put in the played pile:\n");
  printf("\t\t\tExpected: %d, result: %d\n", village, state.playedCards[playedCounter]);
  asserttrue(village, state.playedCards[playedCounter]);

  // Check that other player's states were not mutated
  printf("\t\tChecking that other player's states were not mutated:\n");
  for (i = 0; i < numPlayer; i++)
  {
    if (i != p)
    {
      printf("\t\t\tChecking player %d's hand:\n", i);
      for (j = 0; j < otherPlayersState.handCount[i]; j++)
      {
        printf("\t\t\tExpected: %d, result: %d\n", otherPlayersState.hand[i][j], state.hand[i][j]);
        asserttrue(state.hand[i][j], otherPlayersState.hand[i][j]);
      }
      printf("\t\t\tChecking player %d's deck:\n", i);
      for (j = 0; j < otherPlayersState.deckCount[i]; j++)
      {
        printf("\t\t\tExpected: %d, result: %d\n", otherPlayersState.deck[i][j], state.deck[i][j]);
        asserttrue(otherPlayersState.deck[i][j], state.deck[i][j]);
      }
      printf("\t\t\tChecking player %d's discard:\n", i);
      for (j = 0; j < otherPlayersState.discardCount[i]; j++)
      {
        printf("\t\t\tExpected: %d, Result: %d\n", otherPlayersState.discard[i][j], state.discard[i][j]);
        asserttrue(otherPlayersState.discard[i][j], state.discard[i][j]);
      }
    }
  }

  // Testing with an empty deck
  memcpy(state.discard[0], discardTestPile, sizeof(int) * 10);
  state.discardCount[0] = 10;
  state.deckCount[0] = 0;
  state.hand[0][0] = village;
  currHandCount = state.handCount[0];
  actionCounter = state.numActions;
  playedCounter = state.playedCardCount;
  cardEffect(village, choice1, choice2, choice3, &state, handPos, bonus);
  printf("\n\tChecking with an empty deck:\n");
  printf("\t\tChecking that a card was drawn and added to the hand:\n");
  printf("\t\t\tExpected: %d result: %d:\n", currHandCount, state.handCount[0]);
  asserttrue(currHandCount, state.handCount[0]);
  printf("\t\tChecking that two actions were added:\n");
  printf("\t\t\tExpected: %d, result: %d\n", actionCounter + 2, state.numActions);
  asserttrue(actionCounter + 2, state.numActions);
  printf("\t\tChecking that village was put in the played pile:\n");
  printf("\t\t\tExpected: %d, result: %d\n", village, state.playedCards[playedCounter]);
  asserttrue(village, state.playedCards[playedCounter]);

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
