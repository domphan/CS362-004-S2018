// Testing the adventurer card with randomly generated inputs
#define SEED 35
#define TEST_ITERATIONS 15000
#define MIN_DECK_FOR_ADVENTURER 3
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct failState {
    int handTreasureFail;
    int handCountFail;
    int deckFail;
    int playedCardFail;
};

void initializeFailState(struct failState* fail) {
    fail->handTreasureFail = 0;
    fail->handCountFail = 0;
    fail->deckFail = 0;
    fail->playedCardFail = 0;
}

void testOracleAdventurer(struct gameState* pre, struct failState* fail, int player) {
    int i;
    int treasureCount = 0;
    struct gameState previousCopy;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handPos = 0;
    previousCopy = *pre; // I know this isn't how to do a deep copy of a struct, but I only need the counts and not arrays.
    cardEffect(adventurer, choice1, choice2, choice3, pre, handPos, &bonus);
    // Test that two treasures were actually added to the hand and that nothing else was added.


    if (previousCopy.handCount[player] != pre->handCount[player] - 2) {
        fail->handCountFail++;
    }
    for (i = previousCopy.handCount[player] - 1; i < pre->handCount[player]; i++) {
        if (pre->hand[player][i] == copper || pre->hand[player][i] == silver || pre->hand[player][i] == gold) {
            treasureCount++;
        }
    }
    if (treasureCount != 2) {
        fail->handTreasureFail++;
    }

    // Check that the deck has the same number of cards minus two + what was discarded.
    if (previousCopy.deckCount[player] != pre->deckCount[player] - 2 + pre->discardCount[player]) {
        fail->deckFail++;
    }


    // Test that the adventurer card goes into the played pile.
    if (pre->playedCardCount != 1) {
        fail->playedCardFail++;
    }
}

int main(){
    int i, p, k;
    struct gameState testGame;
    struct failState failures;
    initializeFailState(&failures);
    int treasureOptions[3] = {copper, gold, silver};
    srand(SEED);
    for (k = 0; k < TEST_ITERATIONS; k++) {
        memset(&testGame, 23, sizeof(struct gameState));
        // Set up preconditions
        // randomize gamestate
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&testGame)[i] = (rand() % (255 + 1 - 0) + 0);
        }
        // select random player
        p = (rand() % (MAX_PLAYERS-1 + 1 - 1) + 1);

        testGame.discardCount[p] = 0;
        testGame.handCount[p] = (rand() % (MAX_HAND + 1));
        testGame.whoseTurn = p;

        // limit number of cards in deck for player
        testGame.deckCount[p] = (rand() % (MAX_DECK + 1 - MIN_DECK_FOR_ADVENTURER) + MIN_DECK_FOR_ADVENTURER);

        // How many treasure we're testing for the deck.
        int treasures = (rand() % (testGame.deckCount[p] + 1 - MIN_DECK_FOR_ADVENTURER) + MIN_DECK_FOR_ADVENTURER);
        // place randomly in deck
        for (i = 0; i < treasures; i++) {
            testGame.deck[p][rand() % ((testGame.deckCount[p]-1 + 1 - 0)) + 0] = treasureOptions[rand() % (2 + 1 - 0)+ 0];
        }
        testOracleAdventurer(&testGame, &failures, p);
        
    }

    // Print out error totals.
    printf("Testing the adventurer card **%d** times\n", TEST_ITERATIONS);
    printf("\tTesting that two cards were actually added to the hand:\n\t\tNumber of failures: %d\n", failures.handCountFail);
    printf("\tTesting that the cards added were actually two treasures:\n\t\tNumber of failures: %d\n", failures.handTreasureFail);
    printf("\tTesting that the deck has the same number of cards minus the treasures and those discarded:\n\t\tNumber of failures: %d\n", failures.deckFail);
    printf("\tTesting that the adventurer card was put into the played pile:\n\t\tNumber of failures: %d\n", failures.playedCardFail);


}