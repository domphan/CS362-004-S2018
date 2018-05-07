// Dominic Phan
// Testing supplyCount()

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
int main(){
  int seed = 1000;
  int numPlayer = 4;
  int p, r;
  // select kingdom cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
  struct gameState G;

  /* The supplyCount() function must return the correct amount of supply cards currently available.
  * This is important because when 3 supplies are depleted, the game ends, so this function must work 
  ** correctly.
  * Things to note: victory cards and curses have different numbers of cards depending on numPlayer
  *                 curse cards = (numPlayers-1) * 10
  *                 victory cards = 8 for two players; 12 for 3+
  *                 resource cards = 30 gold, 40, silver; 60 - (numplayer * 7)
  *                 nonvictory kingdom cards = 10
  */
  printf("TESTING supplyCount():\n");
  // testing for players 2, 3, 4
  for (p = 2; p <= numPlayer; p++){
    memset(&G, 23, sizeof(struct gameState)); // clear game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize new game
    printf("\tTesting supplyCount() with %d players\n", p);
    // Check resource cards
    printf("\t\tChecking copper, silver, gold\n");
    asserttrue(supplyCount(copper, &G), (60 - (7*numPlayer)));
    asserttrue(supplyCount(silver, &G), 40);
    asserttrue(supplyCount(gold, &G), 30);
    printf("\t\tChecking curse cards\n");
    asserttrue(supplyCount(curse, &G), (numPlayer-1) * 10);
    printf("\t\tChecking a kingdom card\n");
    asserttrue(supplyCount(feast, &G), 10);
    printf("\t\tChecking a victory card\n");
    if (numPlayer == 2) {
      asserttrue(supplyCount(gardens, &G), 8);
    }
    else {
      asserttrue(supplyCount(gardens, &G), 12);
    }

  }
  if (totalFail == 0) {
    printf("FINAL RESULT: All tests passed\n");
  } else {
    printf("FINAL RESULT: %d FAILURES\n", totalFail);
  }
  return 0;
}
