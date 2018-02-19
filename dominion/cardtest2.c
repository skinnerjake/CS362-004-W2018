/* 
Name: Jacob Skinner
Date: 2/2/17
Class: CS362
Desc.: Tests the playAdventurer(...) function defined in dominion.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

int countDeckDiscard(struct gameState* state, int cardCount[]) {
	int total = 0;
	int i;
	int player = whoseTurn(state);
	for (i = 0; i < state->deckCount[player]; i++) {
		cardCount[state->deck[player][i]]++;
		total++;
	}
	
	for (i = 0; i < state->discardCount[player]; i++) {
		cardCount[state->discard[player][i]]++;
		total++;
	}
	
	return total;
}


int testPlayAdventurer (struct gameState* state, int handPos) {
	int i,
		count = 0,
		success,
		player = whoseTurn(state),
		preHandCount = numHandCards(state);
	int beforeCards[27];
	int afterCards [27];

	for (i = 0; i < 27; i++) {
		beforeCards[i] = 0;
		afterCards[i] = 0;
	}
	
	// get available cards from deck/discard before
	countDeckDiscard(state, beforeCards);
	// play Adventure Card
	playAdventurer(player, handPos, state);
	// get available cards from deck/discard after
	countDeckDiscard(state, afterCards);
	
	/*
	for (i = 0; i < 27; i++) 
		printf("%d %d\n", beforeCards[i], afterCards[i]);
	*/
	//Tests
	printf("Testing all cards are present between deck and discard: ");
	success = 1;
	for ( i = 0; i < 27; i++) {
		if ( i < 4 && i > 6) {
			if (beforeCards[i] != afterCards[i])
				success = 0;
		}
		else
			count += beforeCards[i] - afterCards[i];
	}
	if (success && count <= 2)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	
	printf("Testing played card was adventurer: ");
	if (state->playedCards[state->playedCardCount - 1] == adventurer)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	
	printf("Testing hand has new cards added: ");
	if (numHandCards(state) == (preHandCount + count) - 1)
		printf("PASSED\n");
	else printf("FAILED\n");
	
	
	printf("Testing new cards in hand are treasures: ");
	success = 1;
	for(i = 1; i < count+1; i++) {
		int card = state->hand[player][numHandCards(state)-i];
		if (card < copper || card > gold)
			success = 0;
	}
	if (success)
		printf("PASSED\n");
	else printf("FAILED\n");
	return 0;
}

int main(int argc, char* argv[]) {
	// initialize variables
	int i;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	// Set up gameState
	struct gameState* test;
	test = newGame();
	initializeGame(2, k, -1, test);	
	
	for (i = 0; i < 10; i++)
		gainCard(copper, test, 1, whoseTurn(test));
	
	// Run tests
	printf("---Running tests for 'playAdventurer()'---\n");
	
	// Test1: One Card, nothing discarded
	printf("\nTest case 1: one adventurer in hand, played normally\n");
	gainCard(adventurer, test, 2, whoseTurn(test));
	testPlayAdventurer(test, numHandCards(test)-1);
	
	// Test2: played the wrong card (should fail)
	printf("\nTest case 2: play card that isn't adventurer (should fail)\n");
	testPlayAdventurer(test, numHandCards(test)-1);
	
	// Test3: Play adventure, not last card in hand and several cards are discarded
	printf("\nTest case 3: several cards in deck are discarded\n");
	gainCard(smithy, test, 1, whoseTurn(test));
	gainCard(smithy, test, 1, whoseTurn(test));	
	gainCard(adventurer, test, 2, whoseTurn(test));
	testPlayAdventurer(test, numHandCards(test)-1);
	
	return 0;
}