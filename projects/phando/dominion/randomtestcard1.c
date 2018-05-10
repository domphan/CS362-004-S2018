// Testing the mine card randomly
#define TEST_ITERATIONS 15000
#define SEED 35
#define MIN_DECK_MINE 1

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

void initializeFailStateMine(struct failStateMine* fail) {
    fail->failHand = 0;
    fail->failDeck = 0;
    fail->failPlayed = 0;
    fail->failPlayedCount = 0;
    fail->failAction = 0;
}

void testOracleMine(struct gameState *pre, struct failStateMine *fail, int player) {
    // Need to test that one card was drawn and mine was discarded
    // Need to test that the deck has one less card
    // Need to test that one card was put into the played pile and that one card is mine
    // Need to test that an action was added
}

int main() {
    int i, p, k;
    struct gameState testGame;
    struct failStateMine failures;
    initializeFailStateMine(&failures);
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
        testGame.deckCount[p] = rand() % (MAX_DECK + 1 - MIN_DECK_MINE) + MIN_DECK_MINE;
        testGame.playedCardCount = 0;
        testGame.hand[p][0] = mine;
        testGame.numActions = 0;
        testOracleMine(&testGame, &failures, p);
    }
}