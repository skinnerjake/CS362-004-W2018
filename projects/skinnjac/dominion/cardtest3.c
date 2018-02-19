/* 
Name: Jacob Skinner
Date: 2/2/17
Class: CS362
Desc.: Tests the playVillage(...) function defined in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int testPlayVillage(int player, int handPos, struct gameState* state){
	int handCount = state->handCount[player],
		actions = state->numActions,
		played = state->playedCardCount,
		value;
	// play card
	value = playVillage(player, handPos, state);
	
	printf("Testing the return value is correct: ");
	if (value == 0)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("Testing the number of cards in hand is correct: ");
	if (handCount == state->handCount[player])
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("Testing the number of actions increased by 2: ");
	if (actions + 2 == state->numActions)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("Testing the last played card is a village: ");
	if (state->playedCards[played] == village && played + 1 == state->playedCardCount)
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
	printf("---Running tests for 'playVillage()'---\n");
	
	printf("\nTest case 1: one village in hand, played normally\n");
	gainCard(village, test, 2, whoseTurn(test));
	testPlayVillage(whoseTurn(test), numHandCards(test)-1, test);
	
	printf("\nTest case 2: play wrong card (should fail)\n");
	testPlayVillage(whoseTurn(test), numHandCards(test)-1, test);
	
	printf("\nTest case 3: set actions to 0 (should still play)\n");
	test->numActions = 0;
	gainCard(village, test, 2, whoseTurn(test));
	testPlayVillage(whoseTurn(test), numHandCards(test)-1, test);

	return 0;
}