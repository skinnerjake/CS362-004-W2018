#include "dominion.h"
#include "dominion_helpers.h"
#include "randomtesting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int testPlayAdventurer(struct gameState* state, struct gameState* copy) {
	int player = state->whoseTurn;
	int adventurerIndex = cardHandIndex(adventurer, state);
	if (adventurerIndex < 0) {
		gainCard(adventurer, state, 2, player);
		adventurerIndex = cardHandIndex(adventurer, state);
	}
	
	int i;
	int count = randNum(state->deckCount[player]);
	for (i = 0; i < count; i++) {
		state->discard[player][state->discardCount[player]++] = state->deck[player][--state->deckCount[player]];
	}
	
	copyState(state, copy);
	
	adventurerPlay(state);
	
	// tests
	if (state->playedCards[state->playedCardCount-1] != adventurer) {
		// adventurer wasn't discarded into played stack
		printf("Adventurer wasn't discarded into played cards\n");
		return 0;
	}
	
	if (state->handCount[player] != copy->handCount[player] + 1) {
		// two cards weren't added
		printf("Hand did not increment by two after discard\n");
		return 0;
	}
	
	int card1 = state->hand[player][state->handCount[player]-1];
	int card2 = state->hand[player][state->handCount[player]-2];
	
	if ((card1 < copper || card1 > gold) || (card2 < copper || card2 > gold)) {
		// cards added weren't treasures
		printf("Cards added to hand weren't treasures\n");
		return 0;
	}
	
	updateCoins(player, state, 0);
	if (state->coins != copy->coins + (card1 + card2 - 6)) {
		// value of new coins is not correct
		printf("Value of coins in hands is unexpected\n");
		return 0;
	}
	
	int cardCount1 = state->deckCount[player] + state->handCount[player] + state->discardCount[player] + state->playedCardCount;
	
	int cardCount2 = copy->deckCount[player] + copy->handCount[player] + copy->discardCount[player] + copy->playedCardCount;
	
	if (cardCount1 != cardCount2) {
		printf("Temp hand not returned\n");
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
		result = testPlayAdventurer(test, copy);
		if (result == 1)
			success++;
		else if (result == 0)
			failed++;
	}
	
	printf("Tested 1000 times\n");
	printf("Played adventurer successfully %d times\n", success);
	printf("Failed unexpectedly %d tests\n", failed);
	return 0;
}