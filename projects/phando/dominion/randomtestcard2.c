// Dominic Phan
// Testing smithy

#define SEED 35
#define TEST_ITERATIONS 15000

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct failState {
    int handTreasureFail;
    int handCountFail;
    int deckFail;
    int playedCardFail;
};

void initializeFailState(struct failState* fail)
{
    fail->handTreasureFail = 0;
    fail->handCountFail = 0;
    fail->deckFail = 0;
    fail->playedCardFail = 0;
}

void testOracleSmithy(struct gameState pre*, struct failState* fail, int player) {

}

int main(){
    int i, p, k;
    struct gameState testGame;
    struct failState failures;
    initializeFailState(&failures);
    srand(SEED);
    for (k = 0; k < TEST_ITERATIONS; k++) {
        memset(&testGAme, 23, sizeof(struct gameState));
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&testGame)[i] = rand() % (255 + 1 - 0) + 0;
        }
        p = rand() % (MAX_PLAYERS-1 + 1 - 1) + 1;
        
    }
}