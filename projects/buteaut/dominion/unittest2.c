/* 
Name: Jacob Skinner
Date: 2/2/17
Class: CS362
Desc.: Tests the fullDeckCount(...) function defined in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

/*
function works but is not needed

int getStartingSupply(int card, struct gameState* state) {
	int players = state->numPlayers;
	if (card >= 0 && card <= 26 && supplyCount(card, state) >= 0) {
		switch (card) {
			case curse:
				if (players == 2)
					return 10;
				else if (players == 3)
					return 20;
				else
					return 30;
				
			case estate:
				if (players == 2)
					return 11;
				else
					return 15;
			case duchy:
			case province:
			case gardens:
			case great_hall:
				if (players == 2)
					return 8;
				else
					return 12;
			
			case copper:
				return (67 - 7 * (players));
			case silver:
				return 40;
			case gold:
				return 30;
			
			default:
				return 10;
		}
	}
	else return -1;
}
*/

void testFullDeckCount(int player, int card, int expected, struct gameState* state) {
	int count = fullDeckCount(player, card, state);
	printf("Testing for card #%d: ", card);
	if (count == expected)
		printf ("PASSED: ");
	else printf("FAILED: ");
	printf ("got %d, expected %d\n", count, expected);
}

int main (int argc, char* argv[]) {

	// Set up Game
	int i;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState* test;
	test = newGame();
	initializeGame(2, k, 1, test);
	int player = whoseTurn(test);
	
	
	// Tests
	printf("\n---Running tests for 'fullDeckCount()'---\n");
	
	// Test 1: count of initialized deck (7 copper, 3 estate)
	printf("\nTest 1: count from initialized deck (7 copper)\n");
	testFullDeckCount(player, copper, 7, test);
	
	// Test 2: count after adding an existing card (copper)
	printf("\nTest 2: count after adding an existing card (+1 copper)\n");
	gainCard(copper, test, 1, player);
	testFullDeckCount(player, copper, 8, test);
	
	// Test 3: count after adding a new card (smithy)
	printf("\nTest 3: count after adding a new card (smithy)\n");
	gainCard(smithy, test, 2, player);
	testFullDeckCount(player, smithy, 1, test);
	
	// Test 4: Test after removing card (-1 copper)
	printf("\nTest 4: count after trashing card (-1 copper)\n");
	for (i = 0; i < numHandCards(test); i++)
		if (handCard(i, test) == copper)
			break;
	discardCard(i, player, test, 1);
	testFullDeckCount(player, copper, 7, test);
	
	// Test 5: Test for a card not in the deck or supply (remodel)
	printf("\nTest 5: count card not in the deck or supply (remodel)\n");
	testFullDeckCount(player, remodel, 0, test);
	
	// Test 6: 
	printf("\nTest 6: count card for player other than current (smithy = 0) \n");
	player++;
	if (player >= test->numPlayers) player -= test->numPlayers;
	testFullDeckCount(player, smithy, 0, test);
	
	// Test 7:
	printf("\nTest 7: test for a card that doesn't exist (>26)\n");
	testFullDeckCount(player, 30, 0, test);
	
	return 0;
}