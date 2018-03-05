/*

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "randomtesting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randNum(int max) {
	if (max > 0) 
		return rand() % max + 1;
	return 0;
}

int getStartingSupply(int card, int players) {
	if (card >= 0 && card <= 26) {
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

void printState (struct gameState *state) {
	int i, player;
	printf ("-----Printing State-----\n");
	printf ("\tPlayers = %d\n", state->numPlayers);
	printf ("\tWhoseTurn = %d\n", state->whoseTurn);
	for (i = 0; i < treasure_map+1; i++)
		if (state->supplyCount[i] > 0)
			printf ("\tSupplyCount[%d] = %d\n", i, state->supplyCount[i]);
	for (player = 0; player < state->numPlayers; player++) {
		printf("Player %d:\n", player+1);
		
		printf("\tHand: ");
		for (i = 0; i < state->handCount[player]; i++)
			printf("%d ", state->hand[player][i]);
		
		printf("\n\tDeck: ");
		for (i = 0; i < state->deckCount[player]; i++)
			printf("%d ", state->deck[player][i]);
			
		printf("\n\tDiscard: ");
		for (i = 0; i < state->discardCount[player]; i++)
			printf("%d ", state->discard[player][i]);
		printf("\n");
		
		if (player == state->whoseTurn)
			printf("\tPlayed: ");
			for (i = 0; i < state->playedCardCount; i++)
				printf("%d ", state->playedCards[i]);
			printf("\n");
	}
}

void randomState (struct gameState *state) {
	int i, player;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	// get a random number of players 1-4
	state->numPlayers = randNum(MAX_PLAYERS);
	
	// set supply (& embargo tokens to 0)
	for (i = curse; i < treasure_map+1; i++) {
		state->embargoTokens[i] = 0;
		if (i > gold)
			state->supplyCount[i] = -1;
		else
			state->supplyCount[i] = getStartingSupply(i, state->numPlayers);
	}
	for (i = 0; i < 10; i++)
		state->supplyCount[k[i]] = getStartingSupply(k[i], state->numPlayers);
	
	// for each player
	for (player = 0; player < state->numPlayers; player++) {
		int count = randNum(20) - 1;
		state->discardCount[player] = 0;
		state->deckCount[player] = 0;
		state->handCount[player] = 0;
		// set deck (7 copper, 3 estate, random others)
		for (i = 0; i < 7; i++) gainCard(copper, state, 1, player);
		for (i = 0; i < 3; i++) gainCard(estate, state, 1, player);
		for (i = 0; i < count; i++)
			gainCard(randNum(treasure_map+1)-1, state, 1, player);
		shuffle(player, state);
		
		// set discard (random cards)
		count = randNum(10) - 1;
		for (i = 0; i < count; i++)
			gainCard(randNum(treasure_map+1)-1, state, 0, player);
	}
	
	// random players turn
	state->whoseTurn = randNum(state->numPlayers)-1;
	
	// initialize first player's turn
	state->outpostPlayed = 0;
	state->phase = 0;
	state->numActions = 1;
	state->numBuys = 1;
	state->playedCardCount = 0;
	state->whoseTurn = 0;
	state->handCount[state->whoseTurn] = 0;
	
	// set hand for current player (draw 5 cards from deck)
	for (i = 0; i < 5; i++)
		drawCard(state->whoseTurn, state);
	updateCoins(state->whoseTurn, state, 0);
}

void copyState (struct gameState *original, struct gameState *copy) {
	int i, player;
	copy->numPlayers = original->numPlayers;
	copy->whoseTurn = original->whoseTurn;
	copy->outpostPlayed = original->outpostPlayed;
	copy->phase = original->phase;
	copy->numActions = original->numActions;
	copy->coins = original->coins;
	copy->numBuys = original->numBuys;
	copy->playedCardCount = original->playedCardCount;
	
	for (i = 0; i < treasure_map+1; i++) {
		copy->supplyCount[i] = original->supplyCount[i];
		copy->embargoTokens[i] = original->embargoTokens[i]; 
	}
	
	for (i = 0; i < copy->playedCardCount; i++)
		copy->playedCards[i] = original->playedCards[i];
	
	for (player = 0; player < original->numPlayers; player++) {
		copy->handCount[player] = original->handCount[player];
		copy->deckCount[player] = original->deckCount[player];
		copy->discardCount[player] = original->discardCount[player];
		for (i = 0; i < copy->handCount[player]; i++)
			copy->hand[player][i] = original->hand[player][i];
		for (i = 0; i < copy->deckCount[player]; i++)
			copy->deck[player][i] = original->deck[player][i];
		for (i = 0; i < copy->discardCount[player]; i++)
			copy->discard[player][i] = original->discard[player][i];
	}
}

int cardHandIndex (int card, struct gameState *state) {
	int i;
	for (i = 0; i < state->handCount[state->whoseTurn]; i++)
		if (state->hand[state->whoseTurn][i] == card)
			return i;
	return -1;
}

