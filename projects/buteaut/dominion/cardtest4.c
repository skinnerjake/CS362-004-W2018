/* 
Name: Jacob Skinner
Date: 2/2/17
Class: CS362
Desc.: Tests the playGardens(...) function defined in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int testPlayGardens(struct gameState* state) {
	int value;
	
	// play card
	value = playGardens();
	
	// gardens is victory card, should not be played in playedCards[]
	printf("Testing the last played card is not garden: ");
	if (state->playedCardCount > 0 && state->playedCards[state->playedCardCount - 1] == gardens)
		printf("FAILED\n");
	else printf("PASSED\n");
	
	// return value should be -1
	printf("Testing the return value is correct: ");
	if (value == -1)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	return 0;
}

int main(int argc, char* argv[]) {
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	// Set up gameState
	struct gameState* test;
	test = newGame();
	initializeGame(2, k, -1, test);	
	
	// Run tests
	printf("---Running tests for 'garden()'---\n");
	
	printf("\nTest case 1: one garden in hand, played normally\n");
	gainCard(gardens, test, 2, whoseTurn(test));
	testPlayGardens(test);
	
	return 0;
}