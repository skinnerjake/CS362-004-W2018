/* 
Name: Jacob Skinner
Date: 2/2/17
Class: CS362
Desc.: Tests the playSmithy(...) function defined in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


void testPlaySmithy(struct gameState* state, int handPos) {
	// make copy of hand
	int dCount, hCount, player = whoseTurn(state);
	
	// save variables
	dCount = state->deckCount[player] + state->discardCount[player];
	if (dCount > 3) dCount = 3;
	hCount = state->handCount[player];
	
	// Play Smithy Card
	smithyPlay(state, handPos);
	
	// tests 
	printf("Testing card was removed from hand and played: ");
	if (state->playedCards[state->playedCardCount - 1] == smithy)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("Testing new cards were added: ");
	if (state->handCount[player] == hCount + dCount - 1)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	printf("Testing the played card is the SMITHY card: ");
	if (state->playedCards[state->playedCardCount-1] == smithy)
		printf("PASSED\n");
	else printf("FAILED\n");
}

void printHand (struct gameState* state) {
	int player = whoseTurn(state), i;
	printf("Hand Count = %d\n", state->handCount[player]);
	for (i = 0; i < numHandCards(state); i++)
		printf("Card %d = %d\n", i+1, state->hand[player][i]);
	printf("Discard Count = %d\n", state->discardCount[player]);
	for (i = 0; i < state->discardCount[player]; i++)
		printf("Card %d = %d\n", i+1, state->discard[player][i]);
	printf("Deck Count = %d\n", state->deckCount[player]);
	for (i = 0; i < state->deckCount[player]; i++)
		printf("Card %d = %d\n", i+1, state->deck[player][i]);
	printf("Played Count = %d\n", state->playedCardCount);
	for (i = 0; i < state->playedCardCount; i++)
		printf("Card %d = %d\n", i+1, state->playedCards[i]);

}

int main(int argc, char* argv[]) {
	
	// initialize variables
	int i;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	// Set up gameState
	struct gameState* test;
	test = newGame();
	initializeGame(2, k, -1, test);
	// get a sufficiently large deck to draw cards
	for (i = 0; i < 10; i++)
		gainCard(copper, test, 1, whoseTurn(test));
	
	
	printf("---Running tests for 'playSmithy()'---\n");
	
	// Test1: One Smithy
	printf("\nTest case 1: one smithy in hand, played normally\n");
	gainCard(smithy, test, 2, whoseTurn(test));
	testPlaySmithy(test, numHandCards(test)-1);
	
	printf("\nTest case 2: play card that isn't smithy (should fail)\n");
	testPlaySmithy(test, numHandCards(test)-1);
	
	// Test3: Play one of multiple smithies
	printf("\nTest case 3: multiple smithies in hand, only one played\n");
	gainCard(smithy, test, 2, whoseTurn(test));
	gainCard(smithy, test, 2, whoseTurn(test));
	testPlaySmithy(test, numHandCards(test)-1);
	
	return 0;
}



