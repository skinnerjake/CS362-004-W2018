/* 
Name: Jacob Skinner
Date: 2/2/17
Class: CS362
Desc.: Tests the endTurn(...) function defined in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void testEndTurn(struct gameState* state) {
	// get variables
	int prevPlayer = whoseTurn(state);
	int count = state->handCount[prevPlayer];
	int nextPlayer = (prevPlayer + 1) % state->numPlayers;
	printf("\tending turn...\n");
	int val = endTurn(state);
	int i;
	int success;
	
	// tests
	printf("\tTesting value is correct: ");
	if(val == 0) 
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("\tTesting player incremented correctly: ");
	if (whoseTurn(state) == nextPlayer)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("\tTesting previous player's hand reset: ");
	success = 1;
	for(i = 0; i < count; i++) {
		if(state->hand[prevPlayer][i] == -1)
			success = 0;
	}
	if(success == 0) 
		printf("PASSED\n");
	else printf("FAILED\n");
		
	printf("\tTesting previous player handcount = 0: ");
	if(state->handCount[prevPlayer] == 0)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("\tTesting phase reset: ");
	if(state->phase == 0)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("\tTesting numActions reset: ");
	if(state->numActions == 1)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("\tTesting numBuys reset: ");
	if(state->numBuys == 1)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("\tTesting playedCardCount reset: ");
	if(state->playedCardCount == 0)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("\tTesting new player drew cards: ");
	if(state->handCount[nextPlayer] == 5)
		printf("PASSED\n");
	else printf("FAILED\n");
}

int main (int argc, char* argv[]) {
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	struct gameState* test;
	test = newGame();
	initializeGame(2, k, 1, test);
	printf("\n---Running tests for 'endTurn()'---\n");
	
	// Test 1: end turn after initialization
	printf("Test 1: end turn after initialization\n");
	testEndTurn(test);
	
	// Test 2: end different player's turn after making moves
	printf("Test 2: end different player's turn after making moves\n");
	int player = whoseTurn(test);
	gainCard(gold, test, 2, player);
	gainCard(gold, test, 2, player);
	discardCard(test->handCount[player] - 1, player, test, 1);
	testEndTurn(test);
	
	// Test 3: set different values to make sure they reset
	printf("Test 3: set different values to make sure they reset\n");
	test->phase = -1;
	test->numActions =-1;
	test->numBuys = -1;
	test->playedCardCount = -1;
	testEndTurn(test);
	
	return 0;
}