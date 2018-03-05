#include "dominion.h"
#include "dominion_helpers.h"
#include "randomtesting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int testPlayMine(struct gameState* state, struct gameState* copy) {
	int mineIndex, treasureIndex, newCard;
	
	// if no mine card, return 0 (nothing happened);
	mineIndex = cardHandIndex(mine, state);
	if (mineIndex < 0) {
		gainCard(mine, state, 2, state->whoseTurn);
		mineIndex = cardHandIndex(mine, state);
	}

	// find treasures in hand, make sure able to upgrade
	treasureIndex = cardHandIndex(copper, state);
	if (treasureIndex < 0) {
		treasureIndex = cardHandIndex(silver, state);
		if (treasureIndex < 0) {
			treasureIndex = cardHandIndex(gold, state);
			if (treasureIndex < 0)
				return (playMine(state->whoseTurn, 0, 0, 0, state) == -1); // should return 0; invalid input
			else
				return (playMine(state->whoseTurn, treasureIndex, 27, 0, state) == -1);
		}
		else
			newCard = gold;
	}
	else
		newCard = silver;
	
	copyState(state, copy);
	
	// play mine
	playMine(state->whoseTurn, treasureIndex, newCard, mineIndex, state);
	
	// test for expected changes
	if (state->supplyCount[newCard] != copy->supplyCount[newCard] - 1) {
		printf("playMine failed: supplyCount not decremented\n");
		return 0;
	}
	updateCoins(state->whoseTurn, state, 0);
	if (state->coins != copy->coins + 1) {
		printf("playMine failed: coins not updated correctly\n");
		return 0;
	}
	if (state->playedCards[state->playedCardCount-1] != mine) {
		printf("playMine failed: mine not played\n");
		printState(state);
		return 0;
	}
	
	if (fullDeckCount(state->whoseTurn, newCard, state) != fullDeckCount(state->whoseTurn, newCard, copy) + 1) {
		printf("playMine failed: new treasure not added\n");
		return 0;
	}
	
	if (fullDeckCount(state->whoseTurn, newCard-1, state) != fullDeckCount(state->whoseTurn, newCard-1, copy) - 1) {
		printf("playMine failed: old treasure not trashed\n");
		return 0;
	}
	
	return 2; // return normally
}

int main(int argc, char* argv[]) {
	int i, result, success = 0, failed = 0;
	srand(time(NULL));
	struct gameState *test, *copy;
	test = newGame();
	copy = newGame();
	for (i = 0; i < 1000; i++) {
		randomState(test);
		result = testPlayMine(test, copy);
		if (result == 2)
			success++;
		else if (result == 0) {
			printf("%d\n", i);
			printState(test);
			failed++;
		}
	}
	
	printf("Tested 1000 times\n");
	printf("Played mine successfully %d times\n", success);
	printf("Failed with bad input %d times\n", 1000-success-failed);
	printf("Failed unexpectedly %d tests\n", failed);
	return 0;
}