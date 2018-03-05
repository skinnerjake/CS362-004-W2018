#include "dominion.h"
#include "dominion_helpers.h"
#include "randomtesting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int testPlayVillage(struct gameState* state, struct gameState* copy) {
	
	int player = state->whoseTurn;
	int villageIndex = cardHandIndex(village, state);
	if (villageIndex < 0) {
		gainCard(village, state, 2, player);
		villageIndex = cardHandIndex(village, state);
	}
	
	copyState(state, copy);
	villagePlay(state, villageIndex);
	
	// test for differences
	if (state->playedCards[state->playedCardCount - 1] != village) {
		printf("Village not in played cards pile\n");
		return 0;
	}
	
	if (state->handCount[player] != copy->handCount[player]) { 
		printf("Did not draw card\n");
		return 0;
	}

	if (state->numActions != copy->numActions + 2){
		printf("Actions not incremented correctly\n");
		return 0;
	}
	
	return 1;
}


int main(int argc, char* argv[]) {
	int i, result, success = 0, failed = 0;
	srand(time(NULL));
	struct gameState *test, *copy;
	test = newGame();
	copy = newGame();
	for (i = 0; i < 1000; i++) {
		randomState(test);
		result = testPlayVillage(test, copy);
		if (result == 1)
			success++;
		else if (result == 0) {
			failed++;
		}
	}
	
	printf("Tested 1000 times\n");
	printf("Played village successfully %d times\n", success);
	printf("Failed unexpectedly %d tests\n", failed);
	return 0;
}