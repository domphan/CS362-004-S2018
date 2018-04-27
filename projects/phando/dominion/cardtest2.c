// Dominic Phan
// testing adventurer

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
  int handPos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int *bonus = NULL;
  int seed = 1000;
  int numPlayer = 4;
  int p, r;
  int currHandCount;
  int discardCounter;
  int deckTest1[10] = {estate, estate, estate, copper, copper,
                       copper, copper, copper, copper, copper};
  int deckTest2[10] = {copper, copper, copper, copper, copper,
                       copper, copper, estate, estate, estate};
  int discardTest3[10] = {copper, copper, copper, copper, copper, 
                          copper, copper, estate, estate, estate};
  int deckTest4[10] = {copper, estate, estate, estate};
  int discardTest4[10] = {copper, copper, copper, copper, copper, 
                          copper};
  // select kingdom cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState state;
  /*
  * The adventurer kingdom card is supposed to search the deck until two treasures are found
  * it then discards all cards that were not treasures.
  * There are a few situations we need to test:
  * * Top two cards are treasures
  * * Treasures somewhere in the middle of the deck
  * * Empty deck, with rest of cards in discard pile
  * * One treasure in the deck, one treasure in the discard pile.
  * * Preconditions: Each player has a deck with at least two treasure cards (inf loop if not)
  * * Postconditions: The player will have two treasures in their hand and the player will
  * *                 possibly have cards in their discard pile.
  */
  memset(&state, 23, sizeof(struct gameState));
  r = initializeGame(numPlayer, k, seed, &state);
  printf("Testing the adventurer card:\n");
  for (p = 0; p < numPlayer; p++) {
    printf("Testing for player %d\n", p);

    // Test deck scenario 1
    printf("\tTesting adventurer with two treasures at top of deck:\n");
    memcpy(state.deck[p], deckTest1, sizeof(int) * 10);
    state.deckCount[p] = 10;
    discardCounter = state.discardCount[p];
    currHandCount = state.handCount[p];
    cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, bonus);

    printf("\t\tChecking to see if two cards were added to the hand:\n");
    printf("\t\t\tExpected: %d, result: %d", currHandCount + 2, state.handCount[p]);
    asserttrue(state.handCount[p], currHandCount + 2);
    printf("\t\tChecking to see if the last two cards added were copper:\n");
    for (i = 0; i < 2; i++) {
      printf("\t\t\tChecking index %d in the hand:  Expected: %d result: %d\n", (currHandCount+i), copper, state.hand[p][currHandCount + i]);
      asserttrue(copper, state.hand[p][currHandCount + i]);
    }
    printf("\t\tChecking to see that no cards were discarded, since coppers were at top:\n");
    printf("\t\t\tExpected: %d results: %d\n", discardCounter, state.discardCount[p]);
    asserttrue(state.discardCount[p], discardCounter);
    for (i = 0; i < state.discardCount[p]; i++) {
      printf("tihs is in the discard pile: %d\n", state.discard[p][i]);
    }

    // Test deck scenario 2
    printf("\tTesting adventurer with two treasures at the middle of deck:\n");
    memcpy(state.deck[p], deckTest2, sizeof(int) * 10);
    state.deckCount[p] = 10;
    discardCounter = state.discardCount[p];
    currHandCount = state.handCount[p];
    cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, bonus);
    printf("\t\tChecking to see if two cards were added to the hand:\n");
    printf("\t\t\tExpected: %d, result: %d", currHandCount + 2, state.handCount[p]);
    asserttrue(state.handCount[p], currHandCount + 2);
    printf("\t\tChecking to see if the last two cards added were copper:\n");
    for (i = 0; i < 2; i++)
    {
      printf("\t\t\tChecking index %d in the hand:  Expected: %d result: %d\n", (currHandCount + i), copper, state.hand[p][currHandCount + i]);
      asserttrue(copper, state.hand[p][currHandCount + i]);
    }
    printf("\t\tChecking to see that three estate cards were discarded:\n");
    printf("\t\t\tExpected: %d results: %d\n", discardCounter + 3, state.discardCount[p]);
    asserttrue(state.discardCount[p], discardCounter+3);

    // Test deck scenario 3
    printf("\tTesting adventurer with an empty deck.\n");
    state.deckCount[p] = 0;
    memcpy(state.discard[p], discardTest3, sizeof(int) * 10);
    state.discardCount[p] = 10;
    currHandCount = state.handCount[p];
    cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, bonus);
    printf("\t\tChecking to see if two cards were added to the hand:\n");
    printf("\t\t\tExpected: %d, result: %d\n", currHandCount + 2, state.handCount[p]);
    asserttrue(state.handCount[p], currHandCount + 2);
    printf("\t\tChecking to see if the last two cards added were copper:\n");
    for (i = 0; i < 2; i++)
    {
      printf("\t\t\tChecking index %d in the hand:  Expected: %d result: %d\n", (currHandCount + i), copper, state.hand[p][currHandCount + i]);
      asserttrue(copper, state.hand[p][currHandCount + i]);
    }
    // Test deck scenario 4
    printf("\tTesting adventurer with 1 copper in deck and the rest in discard pile\n");
    memcpy(state.discard[p], discardTest4, sizeof(int) * 6);
    state.discardCount[p] = 6;
    memcpy(state.deck[p], deckTest4, sizeof(int) * 4);
    state.deckCount[p] = 4;
    currHandCount = state.handCount[p];
    cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, bonus);
    printf("\t\tChecking to see if two cards were added to the hand:\n");
    printf("\t\t\tExpected: %d, result: %d", currHandCount + 2, state.handCount[p]);
    asserttrue(state.handCount[p], currHandCount + 2);
    printf("\t\tChecking to see if the last two cards added were copper:\n");
    for (i = 0; i < 2; i++)
    {
      printf("\t\t\tChecking index %d in the hand:  Expected: %d result: %d\n", (currHandCount + i), copper, state.hand[p][currHandCount + i]);
      asserttrue(copper, state.hand[p][currHandCount + i]);
    }
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
