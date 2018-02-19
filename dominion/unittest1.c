/* 
Name: Jacob Skinner
Date: 2/2/17
Class: CS362
Desc.: Tests the handCard(...) function defined in dominion.c
*/

// call all header files
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void testHandCard(struct gameState* state, int cards[]) {
	int i = 0, success = 1;
	
	printf("Testing handCard on all cards in hand: ");
	for (i = 0; i < numHandCards(state); i++)
		if(handCard(i, state) != cards[i])
			success = 0;
	if (success)
		printf ("PASSED\n");
	else 
		printf("FAILED\n");

}

void getTempHand(struct gameState* state, int tempHand[]) {
	int i;
	int player = state->whoseTurn;
	int count = state->handCount[player];
		
	memset(tempHand, 0, MAX_HAND * sizeof(int));
	
	for (i = 0; i < count; i++)
		tempHand[i] = state->hand[player][i];
}

int main (int argc, char* argv[]) {
	
	// initialize variables
	int tempHand[MAX_HAND];
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	// Set up gameState
	struct gameState* test;
	test = newGame();
	initializeGame(2, k, -1, test);
	printf("---Running tests for 'handCard()'---\n");
	
	//TEST #1: after initializeGame()
	printf("\nTEST #1: after initializeGame()\n");
	getTempHand(test, tempHand);
	testHandCard(test, tempHand);
	
	//TEST #2: after gaining another card into hand
	printf("\nTEST #2: after gaining another card into hand\n");
	gainCard(smithy, test, 2, test->whoseTurn);
	getTempHand(test, tempHand);
	testHandCard(test, tempHand);
	
	//TEST #3: end turn, new player's hand
	printf("\nTEST #3: end turn, new player's hand\n");
	endTurn(test);
	getTempHand(test, tempHand);
	testHandCard(test, tempHand);
	
	return 0;
}