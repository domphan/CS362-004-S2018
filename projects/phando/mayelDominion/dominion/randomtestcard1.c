// Testing the village card randomly

#define TEST_ITERATIONS 15000
#define SEED 35
#define MIN_DECK_VILLAGE 1

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

struct failStateMine {
    int failHand;
    int failDeck;
    int failPlayed;
    int failPlayedCount;
    int failAction;
};

void initializeFailStateVillage(struct failStateMine* fail) {
    fail->failHand = 0;
    fail->failDeck = 0;
    fail->failPlayed = 0;
    fail->failPlayedCount = 0;
    fail->failAction = 0;
}

void testOracleVillage(struct gameState *pre, struct failStateMine *fail, int player) {
    struct gameState previousCopy;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handPos = 0;
    previousCopy = *pre;
    cardEffect(village, choice1, choice2, choice3, pre, handPos, &bonus);
    // Need to test that one card was drawn and mine was discarded
    if (previousCopy.handCount[player] != pre->handCount[player]){
        fail->failHand++;
    }
    // Need to test that the deck has one less card
    if (pre->deckCount[player] != previousCopy.deckCount[player] - 1) {
        fail->failDeck++;
    }
    // Need to test that one card was put into the played pile and that one card is mine
    if (pre->playedCardCount == previousCopy.playedCardCount + 1) {
        if (pre->playedCards[pre->playedCardCount-1] != village) {
            fail->failPlayed++;
        }
    } else {
        fail->failPlayedCount++;
    }
    // Need to test that two actions was added
    if (pre->numActions != previousCopy.numActions + 2) {
        fail->failAction++;
    }
}

int main() {
    int i, p, k;
    struct gameState testGame;
    struct failStateMine failures;
    initializeFailStateVillage(&failures);
    srand(SEED);
    for (k = 0; k < TEST_ITERATIONS; k++) {
        memset(&testGame, 23, sizeof(struct gameState));
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&testGame)[i] = rand() % (255 + 1 - 0) + 0;
        }
        p = rand() % (MAX_PLAYERS - 1 + 1 - 1) + 1;
        testGame.discardCount[p] = 0;
        testGame.handCount[p] = rand() % (MAX_HAND - 4 + 1 - 1) + 1;
        testGame.whoseTurn = p;
        testGame.deckCount[p] = rand() % (MAX_DECK + 1 - MIN_DECK_VILLAGE) + MIN_DECK_VILLAGE;
        testGame.playedCardCount = 0;
        testGame.hand[p][0] = village;
        testGame.numActions = 0;
        testOracleVillage(&testGame, &failures, p);
    }
    printf("Testing the village card **%d** times\n", TEST_ITERATIONS);
    printf("\tTesting that 1 card was actually added to the hand and village was removed:\n\t\tNumber of failures: %d\n", failures.failHand);
    printf("\tTesting that the deck has 1 less card: %d\n", failures.failDeck);
    printf("\tTesting that a card was added to the played pile:\n\t\tNumber of failures: %d\n", failures.failPlayedCount);
    printf("\tTesting that the village card was put into the played pile:\n\t\tNumber of failures: %d\n", failures.failPlayed);
    printf("\tTesting that an action was added to the current player's turn:\n\t\tNumber of failures: %d\n", failures.failAction);
}