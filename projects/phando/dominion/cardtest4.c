// Dominic Phan
// Testing Mine
// uses choice1, choice2, currentPlayer, handPos

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

int calculateEndAmount(int j, int k) {
  if (j == k) {
    return 1;
  } 
  else {
    return 2;
  }
}
int main()
{
  int i, j, k, m;
  char innerLoopName[10];
  char outerLoopName[10];
  int handCount = 5;
  int handPos = 0; // position of mine
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int *bonus = NULL;
  int seed = 1000;
  int numPlayer = 4;
  int r;
  int p = 0;
  int currHandCount;
  int discardCounter;
  int playedCounter;
  int currDeckCounter;
  int endResult = 0; // Holds the amount of treasure that we should have in the hand.
  // select kingdom cards
  int kingdom[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  int testHand[MAX_HAND] = {mine, copper, silver, gold, estate};
  struct gameState state, otherPlayersState;
  int successFlag;

  /*
  * The mine kingdom card allows a player to trash (remove from play) a treasure card and gain
  * a treasure card (up to +3 cost of trashed card) to your hand.
  * Preconditions: The player must have a treasure card in their hand
  * Postconditions: The plyaer will gain a new treasure card that is within +3 cost of trashed card.
  * We need to test what happens with copper, silver, gold in the player's hand.
  * We need to test that the treasure was removed from play, so not in discard pile or hand still.
  * We need to test that a new treasure was added to the player's hand pile (gained).
  * We need to test that mine was added to the played pile.
  * We need to test that none of the other player's states were changed.
  */
  memset(&state, 23, sizeof(struct gameState));
  r = initializeGame(numPlayer, kingdom, seed, &state);
  printf("Testing the mine card:\n");
  for (j = copper; j <= gold; j++) {
    for (k = copper; k <= gold; k++) {
      if (j == copper) {
        strncpy(outerLoopName, "copper\0", 7);
      } else if (j == silver) {
        strncpy(outerLoopName, "silver\0", 7);
      } else {
        strncpy(outerLoopName, "gold\0", 5);
      }
      if (k == copper) {
        strncpy(innerLoopName, "copper\0", 7);
      } else if (k == silver) {
        strncpy(innerLoopName, "silver\0", 7);
      } else {
        strncpy(innerLoopName, "gold\0", 5);
      }
      if (j == copper && k == gold) {
        continue;
      }
      memcpy(otherPlayersState.hand, state.hand, sizeof(int) * MAX_HAND * MAX_PLAYERS);
      memcpy(otherPlayersState.deck, state.deck, sizeof(int) * MAX_DECK * MAX_PLAYERS);
      memcpy(otherPlayersState.discard, state.discard, sizeof(int) * MAX_DECK * MAX_PLAYERS);
      for (i = 0; i < numPlayer; i++)
      {
        otherPlayersState.handCount[i] = state.handCount[i];
        otherPlayersState.deckCount[i] = state.deckCount[i];
        otherPlayersState.discardCount[i] = state.discardCount[i];
      }
      // --------------------------- Tests ---------------------------
      printf("Testing Mine converting %s to %s:\n", outerLoopName, innerLoopName);
      memcpy(state.hand[0], testHand, sizeof(int) * handCount);
      state.handCount[0] = 5;
      choice1 = j - 3; // position of treasure that will be sacrificed
      handPos = 0;     // Position of the mine card
      choice2 = k;
      discardCounter = state.discardCount[0];
      currHandCount = state.handCount[0];
      playedCounter = state.playedCardCount;
      currDeckCounter = state.deckCount[0];
      cardEffect(mine, choice1, choice2, choice3, &state, handPos, bonus);
      printf("\tTesting that %s was removed from the hand along with mine:\n", outerLoopName);
      printf("\t\tCards in hand --> Expected: %d result: %d\n", currHandCount - 1, state.handCount[0]);
      asserttrue(currHandCount - 1, state.handCount[0]);

      printf("\tTesting that %s was removed from the hand:\n", outerLoopName);
      successFlag = 1;
      for (i = 0; i < state.handCount[0]; i++) {
        if (state.hand[0][i] == j) {
          successFlag = 0;
        }
      }
      printf("\t\tExpected: %d Result: %d\n", 1, successFlag);
      asserttrue(successFlag, 1);

      printf("\tTesting that %s was removed from play:\n", outerLoopName);
      successFlag = 1;
      for (i = 0; i < state.discardCount[0]; i++) {
        if (state.discard[0][i] == j){
          successFlag = 0;
        }
      }
      printf("\t\tChecking the discard pile for %s --> Expected: %d result :%d\n", outerLoopName, 1, successFlag);
      asserttrue(1, successFlag);

      printf("\tTesting that the %s was added to the hand:\n", innerLoopName);
      endResult = 0;
      for (int i = 0; i < state.handCount[0]; i++) {
        if (state.hand[0][i] == k) {
          endResult++;
        }
      }
      printf("\t\tChecking the hand for %s --> Expected: %d Result: %d\n", innerLoopName, calculateEndAmount(j,k), endResult);
      asserttrue(calculateEndAmount(j, k), endResult);

      printf("\tTesting that mine was added to the played pile:\n");
      printf("\t\tChecking the played pile for mine --> Expected: %d Result: %d\n", mine, state.playedCards[playedCounter]);
      asserttrue(mine, state.playedCards[playedCounter]);

      // Check that other player's states were not mutated
      printf("\t\tChecking that other player's states were not mutated:\n");
      for (i = 0; i < numPlayer; i++)
      {
        if (i != p)
        {
          printf("\t\t\tChecking player %d's hand:\n", i);
          for (m = 0; m < otherPlayersState.handCount[i]; m++)
          {
            printf("\t\t\tExpected: %d, result: %d\n", otherPlayersState.hand[i][m], state.hand[i][m]);
            asserttrue(state.hand[i][m], otherPlayersState.hand[i][m]);
          }
          printf("\t\t\tChecking player %d's deck:\n", i);
          for (m = 0; m < otherPlayersState.deckCount[i]; m++)
          {
            printf("\t\t\tExpected: %d, result: %d\n", otherPlayersState.deck[i][m], state.deck[i][m]);
            asserttrue(otherPlayersState.deck[i][m], state.deck[i][m]);
          }
          printf("\t\t\tChecking player %d's discard:\n", i);
          for (m = 0; m < otherPlayersState.discardCount[i]; m++)
          {
            printf("\t\t\tExpected: %d, Result: %d\n", otherPlayersState.discard[i][m], state.discard[i][m]);
            asserttrue(otherPlayersState.discard[i][m], state.discard[i][m]);
          }
        }
      }
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
