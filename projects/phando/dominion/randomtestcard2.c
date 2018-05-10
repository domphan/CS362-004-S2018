// Dominic Phan
// Testing smithy

#define SEED 35
#define TEST_ITERATIONS 15000
#define MIN_DECK_SMITHY 5

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct failStateSmithy {
    int handCountFail;
    int deckFail;
    int playedCardCountFail;
    int playedCardFail;
};

void initializeFailStateSmithy(struct failStateSmithy* fail)
{
    fail->handCountFail = 0;
    fail->deckFail = 0;
    fail->playedCardCountFail = 0;
    fail->playedCardFail = 0;
}

void testOracleSmithy(struct gameState* pre, struct failStateSmithy* fail, int player) {
    struct gameState previousCopy;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handPos = 0;
    previousCopy = *pre;
    cardEffect(smithy, choice1, choice2, choice3, pre, handPos, &bonus);
    // Test that three cards were added to the hand and smithy was removed
    if (previousCopy.handCount[player] + 2 != pre->handCount[player]) {
        fail->handCountFail++;
    }
    // Test that smithy was added to the played pile
    if (pre->playedCardCount != previousCopy.playedCardCount + 1) {
        fail->playedCardCountFail++;
    } else {
        if (pre->playedCards[pre->playedCardCount-1] != smithy) {
            fail->playedCardFail++;
        }
    }
    // Test that the deckCount is the 3 less.
    if (pre->deckCount[player] != previousCopy.deckCount[player] - 3) {
        fail->deckFail++;
    }
}

int main(){
    int i, p, k;
    struct gameState testGame;
    struct failStateSmithy failures;
    initializeFailStateSmithy(&failures);
    srand(SEED);
    for (k = 0; k < TEST_ITERATIONS; k++) {
        memset(&testGame, 23, sizeof(struct gameState));
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&testGame)[i] = rand() % (255 + 1 - 0) + 0;
        }
        p = rand() % (MAX_PLAYERS-1 + 1 - 1) + 1;
        testGame.discardCount[p] = 0;
        testGame.handCount[p] = rand() % (MAX_HAND-4 + 1 - 1) + 1;
        testGame.whoseTurn = p;
        testGame.deckCount[p] = rand() % (MAX_DECK + 1 - MIN_DECK_SMITHY) + MIN_DECK_SMITHY;
        testGame.playedCardCount = 0;
        testGame.hand[p][0] = smithy;
        printf("%d\n", k);
        testOracleSmithy(&testGame, &failures, p);
        printf("%d\n", k);
    }
    printf("Testing the smithy card **%d** times\n", TEST_ITERATIONS);
    printf("\tTesting that 3 cards were actually added to the hand and smithy was removed:\n\t\tNumber of failures: %d\n", failures.handCountFail);
    printf("\tTesting that the deck has 3 less cards: %d\n", failures.deckFail);
    printf("\tTesting that a card was added to the played pile:\n\t\tNumber of failures: %d\n", failures.playedCardCountFail);
    printf("\tTesting that the smithy card was put into the played pile:\n\t\tNumber of failures: %d\n", failures.playedCardFail);
}
