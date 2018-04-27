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
