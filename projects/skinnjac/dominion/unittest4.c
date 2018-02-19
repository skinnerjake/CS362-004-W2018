/* 
Name: Jacob Skinner
Date: 2/2/17
Class: CS362
Desc.: Tests the isGameOver(...) function defined in dominion.c
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>

void setSupply(int amount, struct gameState* state) {
	enum CARD c;
	for (c = curse; c <= treasure_map; c++)
		state->supplyCount[c] = amount;
}

void testIsGameOver(int expected, struct gameState* state) {\
	int result = isGameOver(state);
	printf("Testing if game is over: ");
	if (result == expected)
		printf ("PASSED: ");
	else printf("FAILED: ");
	printf ("got %d, expected %d\n", result, expected);
}


int main (int argc, char* argv[]) {
	
	struct gameState* test;
	test = newGame();
	
	// Run tests
	printf("TESTING 'isGameOver()':\n\n");
	
	// Test 1: all supplies empty (game ends)
	setSupply(0, test);
	printf("TEST 1: all supplies empty (game should end):\n");
	testIsGameOver(1, test);
	
	// TEST 2: 3 supply (not province) are empty (game ends)
	setSupply(1, test);
	test->supplyCount[estate] = 0;
	test->supplyCount[copper] = 0;
	test->supplyCount[feast] = 0;
	printf("TEST 2: 3 supply (not province) are empty (game should end):\n");
	testIsGameOver(1, test);
	
	// TEST 3: only province supply is empty (game ends)
	setSupply(1, test);
	test->supplyCount[province] = 0;
	printf("TEST 3: only province supply is empty (game should end):\n");
	testIsGameOver(1, test);
	
	// TEST 4: all supply have cards (game continues)
	setSupply(1, test);
	printf("TEST 4: all supply have cards (game should continue):\n");
	testIsGameOver(0, test);
	
	// TEST 5: two supply (not province) are empty (game continues)
	setSupply(1, test);
	test->supplyCount[steward] = 0;
	test->supplyCount[village] = 0;
	printf("TEST 5: two supply (not province) are empty (game should continue):\n");
	testIsGameOver(0, test);
	
	return 0;
}